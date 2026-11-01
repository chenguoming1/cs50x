"""Generate an offline progress page from a gradebook snapshot and local files.

Run: python scripts/progress.py
Or:  python scripts/progress.py --text
This reads files only; it does not run/check/submit coursework or contact CS50.
"""

import argparse
import hashlib
import html
import json
import posixpath
import re
import zipfile
from datetime import datetime, timedelta, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def v(problem, title, *patterns):
    return {"problem": problem, "title": title, "patterns": patterns}


CATALOG = [
    (0, "Scratch", [("Starting from Scratch", [v("scratch", "Scratch", "*.sb3")])]),
    (1, "C", [
        ("Hello, Me", [v("me", "Hello, Me", "hello.c")]),
        ("Mario", [v("mario/less", "Less comfortable", "mario.c"), v("mario/more", "More comfortable", "mario.c")]),
        ("Cash or Credit", [v("cash", "Cash", "cash.c"), v("credit", "Credit", "credit.c")]),
    ]),
    (2, "Arrays", [
        ("Scrabble", [v("scrabble", "Scrabble", "scrabble.c")]),
        ("Readability", [v("readability", "Readability", "readability.c")]),
        ("Caesar or Substitution", [v("caesar", "Caesar", "caesar.c"), v("substitution", "Substitution", "substitution.c")]),
    ]),
    (3, "Algorithms", [
        ("Sort", [v("sort", "Sort", "answers.txt")]),
        ("Plurality", [v("plurality", "Plurality", "plurality.c")]),
        ("Runoff or Tideman", [v("runoff", "Runoff", "runoff.c"), v("tideman", "Tideman", "tideman.c")]),
    ]),
    (4, "Memory", [
        ("Volume", [v("volume", "Volume", "volume.c")]),
        ("Filter", [v("filter/less", "Less comfortable", "helpers.c"), v("filter/more", "More comfortable", "helpers.c")]),
        ("Recover", [v("recover", "Recover", "recover.c")]),
    ]),
    (5, "Data Structures", [
        ("Inheritance", [v("inheritance", "Inheritance", "inheritance.c")]),
        ("Speller", [v("speller", "Speller", "dictionary.c", "dictionary.h")]),
    ]),
    (6, "Python", [
        ("Hello, Again", [v("hello", "Hello", "hello.py")]),
        ("Mario in Python", [v("mario/less", "Less comfortable", "mario.py"), v("mario/more", "More comfortable", "mario.py")]),
        ("Cash or Credit in Python", [v("cash", "Cash", "cash.py"), v("credit", "Credit", "credit.py")]),
        ("Readability in Python", [v("readability", "Readability", "readability.py")]),
        ("DNA", [v("dna", "DNA", "dna.py")]),
    ]),
    (7, "SQL", [
        ("Songs", [v("songs", "Songs", "*.sql", "answers.txt")]),
        ("Movies", [v("movies", "Movies", "*.sql")]),
        ("Fiftyville", [v("fiftyville", "Fiftyville", "log.sql", "answers.txt")]),
    ]),
    (8, "HTML, CSS, JavaScript", [
        ("Trivia", [v("trivia", "Trivia", "*.html", "*.css", "*.js")]),
        ("Homepage", [v("homepage", "Homepage", "**/*.html", "**/*.css", "**/*.js", "specification.txt")]),
    ]),
    (9, "Flask", [
        ("Birthdays", [v("birthdays", "Birthdays", "app.py", "templates/**/*.html", "static/**/*.css", "static/**/*.js")]),
        ("Finance", [v("finance", "Finance", "app.py", "helpers.py", "templates/**/*.html", "static/**/*.css", "static/**/*.js")]),
    ]),
    ("FP", "Final Project", [("Final Project", [v("project", "Final Project", "**/*.py", "**/*.c", "**/*.js", "**/*.html", "README.md")])]),
]


def digest(data):
    return hashlib.sha256(data.replace(b"\r\n", b"\n")).hexdigest()


def inline_md(text, source):
    text = html.escape(text)
    text = re.sub(r"`([^`]+)`", r"<code>\1</code>", text)
    text = re.sub(r"\*\*([^*]+)\*\*", r"<strong>\1</strong>", text)

    def link(match):
        label, url = match.groups()
        if not url.startswith(("https://", "http://")):
            url = posixpath.normpath(posixpath.join(source.parent.relative_to(ROOT).as_posix(), url))
        return f'<a href="{url}" target="_blank" rel="noopener">{label}</a>'

    return re.sub(r"\[([^]]+)\]\(([^)]+)\)", link, text)


def render_guide(source):
    if not source.exists():
        return "<p>Use the official course page for this assignment.</p>"
    output, paragraph, code = [], [], None

    def flush():
        if paragraph:
            output.append("<p>" + inline_md(" ".join(paragraph), source) + "</p>")
            paragraph.clear()

    for line in source.read_text(encoding="utf-8").splitlines():
        if line.startswith("```"):
            flush()
            if code is None:
                code = []
            else:
                output.append("<pre><code>" + html.escape("\n".join(code)) + "</code></pre>")
                code = None
        elif code is not None:
            code.append(line)
        elif re.match(r"^#{1,6} ", line):
            flush()
            level = min(len(line.split(" ", 1)[0]) + 1, 4)
            output.append(f"<h{level}>" + inline_md(line.lstrip("# "), source) + f"</h{level}>")
        elif not line.strip():
            flush()
        else:
            paragraph.append(line)
    flush()
    return "".join(output)


def collect():
    gradebook = json.loads((ROOT / "progress/gradebook.json").read_text())
    passed = {}
    for slug in gradebook["passed"]:
        parts = slug.split("/")
        passed["/".join(parts[4:])] = {"year": int(parts[2]), "slug": slug}
    import_path = ROOT / ".downloads/submitted-solutions/manifest.json"
    imported = json.loads(import_path.read_text())["files"] if import_path.exists() else []
    imported_by_path = {item["local_file"]: item for item in imported}
    starter_path = ROOT / ".downloads/manifest.json"
    starters = json.loads(starter_path.read_text()) if starter_path.exists() else []
    starter_by_folder = {(item["pset"], item["problem"]): item for item in starters}
    weeks, local_count = [], 0
    for number, topic, tasks in CATALOG:
        week = {"id": str(number), "topic": topic, "tasks": []}
        for task_title, variants in tasks:
            task = {"name": task_title, "variants": [], "passed": False}
            for definition in variants:
                problem = definition["problem"]
                folder = ROOT / (f"pset{number}/{problem}" if number != "FP" else "final-project")
                paths = sorted({p for pattern in definition["patterns"] for p in folder.glob(pattern) if p.is_file()})
                starter_hashes = {}
                if (number, problem) in starter_by_folder:
                    archive = ROOT / ".downloads" / f"pset{number}-{problem.replace('/', '-')}.zip"
                    if archive.exists():
                        names = {p.relative_to(folder).as_posix() for p in paths}
                        with zipfile.ZipFile(archive) as bundle:
                            for item in bundle.infolist():
                                relative = item.filename.split("/", 1)[-1]
                                if relative in names and not item.is_dir():
                                    starter_hashes[relative] = digest(bundle.read(item))
                changed, restored, unchanged_import = [], [], []
                for path in paths:
                    relative = path.relative_to(ROOT).as_posix()
                    content = path.read_bytes()
                    if relative in imported_by_path:
                        restored.append(relative)
                        if hashlib.sha256(content).hexdigest() == imported_by_path[relative]["sha256"]:
                            unchanged_import.append(relative)
                    if digest(content) != starter_hashes.get(path.relative_to(folder).as_posix()):
                        changed.append(relative)
                if restored:
                    local = "Imported solution" if len(unchanged_import) == len(restored) else "Edited imported solution"
                    kind = "imported"
                    local_count += 1
                elif changed:
                    local, kind = "Work in progress", "working"
                elif paths:
                    local, kind = "Starter only", "starter"
                else:
                    local, kind = "No solution saved", "missing"
                grade_key = ("sentimental/" + problem) if number == 6 and problem != "dna" else problem
                official = passed.get(grade_key)
                if official:
                    task["passed"] = True
                source = folder / "INSTRUCTIONS.md"
                spec = (f"https://cs50.harvard.edu/x/psets/{number}/{problem}/" if number != "FP"
                        else "https://cs50.harvard.edu/x/project/")
                variant = {"title": definition["title"], "problem": problem, "local": local,
                           "localKind": kind, "files": [p.relative_to(ROOT).as_posix() for p in paths],
                           "official": official, "spec": spec, "guide": render_guide(source),
                           "command": f"cd /workspaces/cs50x/{folder.relative_to(ROOT).as_posix()} && code INSTRUCTIONS.md" if source.exists() else None}
                if official:
                    variant["submission"] = "https://submit.cs50.io/users/" + gradebook["username"] + "/" + official["slug"]
                task["variants"].append(variant)
            week["tasks"].append(task)
        week["complete"] = all(task["passed"] for task in week["tasks"])
        weeks.append(week)
    complete = sum(week["complete"] for week in weeks)
    if complete != gradebook["weeks_complete"]:
        raise ValueError("Gradebook snapshot and mapped weeks disagree; review the snapshot before generating.")
    return {"gradebook": gradebook, "scannedAt": datetime.now(timezone(timedelta(hours=8))).isoformat(timespec="seconds"),
            "weeks": weeks, "importedCount": local_count,
            "passedCount": sum(task["passed"] for week in weeks for task in week["tasks"]),
            "taskCount": sum(len(week["tasks"]) for week in weeks)}


def markdown(data):
    g = data["gradebook"]
    lines = ["# Your CS50x progress", "", f"**{g['weeks_complete']} of {g['weeks_total']} weeks complete** on the official gradebook.",
             f"Official source: [{g['source']}]({g['source']}); observed {g['observed_on']}.",
             f"Local file scan: {data['scannedAt']}.", "", "Passing grades below come from that saved gradebook snapshot.",
             "Local files show availability or edits; their presence does not establish a passing grade.", "",
             "| Week | Topic | Official status | Local work |", "| --- | --- | --- | --- |"]
    for week in data["weeks"]:
        completed = sum(task["passed"] for task in week["tasks"])
        copies = sum(v["localKind"] == "imported" for task in week["tasks"] for v in task["variants"])
        lines.append(f"| {week['id']} | {week['topic']} | {completed}/{len(week['tasks'])} requirements passed | {copies} imported solutions |")
    for week in data["weeks"]:
        lines += ["", f"## Week {week['id']}: {week['topic']}", ""]
        for task in week["tasks"]:
            lines.append(f"- [{'x' if task['passed'] else ' '}] **{task['name']}**")
            for variant in task["variants"]:
                local = ", ".join(variant["files"]) if variant["files"] else "no source files"
                lines.append(f"  - {variant['title']}: {variant['local']} ({local}).")
    lines += ["", "Next incomplete requirement in course order: **Speller (Week 5)**." if not data["weeks"][5]["tasks"][1]["passed"] else "",
              "", "Run `python scripts/progress.py` to refresh the local scan and rebuild progress.html.",
              "The official gradebook snapshot changes only when refreshed from the signed-in CS50 gradebook.",
              "[Interactive local page](progress.html) | [Problem instructions](PROBLEMS.md)"]
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--text", action="store_true", help="also print a compact terminal summary")
    args = parser.parse_args()
    data = collect()
    serialized = json.dumps(data, ensure_ascii=True).replace("<", "\\u003c")
    template = (ROOT / "progress/template.html").read_text(encoding="utf-8")
    (ROOT / "progress.html").write_text(template.replace("__PROGRESS_DATA__", serialized), encoding="utf-8")
    (ROOT / "PROGRESS.md").write_text(markdown(data), encoding="utf-8")
    if args.text:
        print(f"CS50x: {data['gradebook']['weeks_complete']}/11 weeks complete; {data['passedCount']}/{data['taskCount']} requirements passed.")
        for week in data["weeks"]:
            count = sum(task["passed"] for task in week["tasks"])
            print(f"Week {week['id']:>2}  {week['topic']:<24} {count}/{len(week['tasks'])} passed")
    print(f"Updated {ROOT / 'progress.html'}")
    print(f"Local scan refreshed; official results remain the {data['gradebook']['observed_on']} gradebook snapshot.")


if __name__ == "__main__":
    main()
