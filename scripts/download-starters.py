"""Download only CS50's published starter files; never replace existing work."""

import concurrent.futures
import hashlib
import json
import re
import shutil
import urllib.request
import zipfile
from html.parser import HTMLParser
from pathlib import Path
from urllib.parse import urljoin

ROOT = Path(__file__).resolve().parent.parent
CACHE = ROOT / ".downloads"
BASE = "https://cs50.harvard.edu/x/"


class Links(HTMLParser):
    def __init__(self):
        super().__init__()
        self.links = []

    def handle_starttag(self, tag, attrs):
        if tag == "a":
            self.links.append(dict(attrs).get("href", ""))


def fetch(url):
    with urllib.request.urlopen(url, timeout=120) as response:
        return response.read().decode("utf-8")


def discover(number):
    url = f"{BASE}psets/{number}/"
    parser = Links()
    parser.feed(fetch(url))
    problems = sorted(
        {urljoin(url, link) for link in parser.links
         if urljoin(url, link).startswith(url)
         and urljoin(url, link) != url and "#" not in link}
    )
    entries = []
    for problem in problems:
        relative = problem.removeprefix(url).rstrip("/")
        destination = ROOT / f"pset{number}" / relative
        destination.mkdir(parents=True, exist_ok=True)
        archives = sorted(set(re.findall(
            r"wget\s+(https://cdn\.cs50\.net/[^\s<\"']+\.zip)", fetch(problem)
        )))
        for archive in archives:
            entries.append({"pset": number, "problem": relative,
                            "specification": problem, "url": archive})
    return number, problems, entries


def download(entry):
    number, problem, url = entry["pset"], entry["problem"], entry["url"]
    archive = CACHE / f"pset{number}-{problem.replace('/', '-')}.zip"
    if not archive.exists():
        partial = archive.with_suffix(".partial")
        with urllib.request.urlopen(url, timeout=120) as response, partial.open("wb") as out:
            shutil.copyfileobj(response, out)
        partial.replace(archive)
    destination = ROOT / f"pset{number}" / problem
    with zipfile.ZipFile(archive) as bundle:
        members = [m for m in bundle.infolist()
                   if not m.filename.startswith("__MACOSX/")]
        # Course archives normally contain a single enclosing problem directory.
        prefixes = {m.filename.split("/")[0] for m in members if m.filename}
        strip_root = len(prefixes) == 1 and any("/" in m.filename for m in members)
        for member in members:
            name = member.filename.split("/", 1)[1] if strip_root else member.filename
            if not name:
                continue
            target = (destination / name).resolve()
            if not target.is_relative_to(destination.resolve()):
                raise ValueError(f"Unsafe archive path: {member.filename}")
            if member.is_dir():
                target.mkdir(parents=True, exist_ok=True)
            elif not target.exists():
                target.parent.mkdir(parents=True, exist_ok=True)
                with bundle.open(member) as source, target.open("xb") as out:
                    shutil.copyfileobj(source, out)
                permissions = (member.external_attr >> 16) & 0o777
                if permissions:
                    target.chmod(permissions)
    entry["sha256"] = hashlib.sha256(archive.read_bytes()).hexdigest()
    entry["bytes"] = archive.stat().st_size
    print(f"Ready: pset{number}/{problem} ({entry['bytes']:,} bytes)", flush=True)
    return entry


def main():
    CACHE.mkdir(exist_ok=True)
    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:
        discovered = sorted(pool.map(discover, range(10)))
    entries = [entry for _, _, group in discovered for entry in group]
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        completed = list(pool.map(download, entries))
    (CACHE / "manifest.json").write_text(json.dumps(completed, indent=2) + "\n")
    lines = ["# CS50x problem sets", "", "## Local guides", "",
             "Open a problem set guide for the task order and container terminal steps.", "",
             "| Problem set | Local guide |", "| --- | --- |"]
    for number in range(10):
        if (ROOT / f"pset{number}" / "README.md").exists():
            lines.append(f"| {number} | [Start here](pset{number}/README.md) |")
    lines += ["", "## Problems", "", "Official specifications and local folders.", "",
             "Starter code and datasets are downloaded only where the assignment supplies them.",
             "For other problems, create the source file yourself in the listed folder.", "",
             "| Problem set | Problem | Local folder | Local instructions |",
             "| --- | --- | --- | --- |"]
    for number, problems, _ in discovered:
        url = f"{BASE}psets/{number}/"
        for problem in problems:
            relative = problem.removeprefix(url).rstrip("/")
            folder = f"pset{number}/{relative}"
            instructions = f"{folder}/INSTRUCTIONS.md"
            guide = f"[Instructions]({instructions})" if (ROOT / instructions).exists() else "-"
            lines.append(f"| {number} | [{relative}]({problem}) | `{folder}` | {guide} |")
    (ROOT / "PROBLEMS.md").write_text("\n".join(lines) + "\n")
    print(f"Downloaded and extracted {len(completed)} official archives. Existing files were preserved.")


if __name__ == "__main__":
    main()
