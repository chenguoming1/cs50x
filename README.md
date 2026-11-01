# CS50x locally

This folder is configured for CS50x 2026 on your Windows ARM computer using
CS50's official Linux Docker image. Your source files stay in this Windows folder;
the compiler and course tools run inside the container.

## Start in VS Code

1. Start Docker Desktop.
2. Open this folder in VS Code (`code .` from PowerShell).
3. Press **Ctrl+Shift+P**, select **Dev Containers: Reopen in Container**.
4. Open **Terminal > New Terminal**. Use the commands from the assignments here.

The Linux workspace is `/workspaces/cs50x`. The first VS Code connection may
download its server and extensions; the course image is already downloaded.

VS Code's user setting `dev.containers.mountWaylandSocket` is disabled on this
computer. Its automatic WSL graphics socket mount caused Docker to fail with
`distro-services/ubuntu.sock: no such file or directory`. CS50x uses the terminal
and browser ports and does not require this optional graphics mount.

## Start from PowerShell

Run this in this folder:

```powershell
.\cs50.ps1
```

This opens a Linux terminal in the same container without requiring the editor.
Type `exit` to leave it. You can also run one command:

```powershell
.\cs50.ps1 check50 --version
```

If your PowerShell execution policy blocks the local launcher, use:

```powershell
powershell -ExecutionPolicy Bypass -File .\cs50.ps1
```

This applies only to that PowerShell process.

## See your progress

Open [progress.html](progress.html) in Chrome for an offline view of completed
weeks, passing grades, local solution files, and each problem's instructions.
[PROGRESS.md](PROGRESS.md) provides the same status as a readable checklist.

From PowerShell in this folder, refresh the local scan and open the tracker with:

```powershell
.\progress.ps1
```

From the container terminal, you can also rebuild it and print a summary:

```bash
cd /workspaces/cs50x
python scripts/progress.py --text
```

The tracker is a self-contained HTML file; it does not require a server or web
port. Source files are rescanned when you run the launcher. Official passing
grades come from the signed-in gradebook snapshot saved in
`progress/gradebook.json` on 25 October 2026. Those grades do not update
automatically when you edit code, run check50, or rebuild the local page.

## Work on a problem

Keep the [C cheat sheet](cheatsheets/C.md) nearby for syntax, library functions,
pointers, memory, and compile/debug commands.

Your [imported solutions](SOLUTIONS.md) lists the six submissions restored from
your downloaded ZIPs, their course years, and backups of the original starters.

[PROBLEMS.md](PROBLEMS.md) indexes the local guides for problem sets 0-9 and
links every assignment to its folder, official specification, and instructions.
Each problem set's `README.md` explains its task order and terminal workflow;
each problem's `INSTRUCTIONS.md` lists its requirements and applicable run,
check, and submit commands.

All 18 official distribution ZIPs, including both Filter variants and the SQL databases,
have been downloaded and extracted. Problems without distribution ZIPs have
empty folders ready for your own source files. The Scrabble specification supplies
its starter code inline; copy that official skeleton when you reach it.

The Movies database is kept locally and excluded from Git because it exceeds
GitHub's file size limit. After cloning this repository, restore missing course
data with `python scripts/download-starters.py`. Existing files are preserved.

For example, after writing `hello.c` for Hello, It's Me, run these in the Linux
terminal:

```bash
cd /workspaces/cs50x/pset1/me
make hello
./hello
style50-cli hello.c
check50 --local cs50/problems/2026/x/me
```

`make hello` compiles `hello.c`; `./hello` runs it. CS50's C library is already
installed, so `#include <cs50.h>` works with the course's `make` command.

In VS Code, `style50 hello.c` opens the graphical style view; `style50-cli hello.c`
also works in a standalone terminal. `debug50 ./hello` uses the VS Code debugger.

For later weeks, the environment includes Python and the `cs50` package, SQLite,
Flask, Flask-Session, Pillow, requests, and the C debugging tools. Examples:

```bash
python your_program.py
sqlite3 /workspaces/cs50x/pset7/songs/songs.db
# In the appropriate web problem's folder:
http-server
# In a Flask problem's folder:
flask run --host=0.0.0.0
```

In VS Code, use the **Ports** panel to open port 8080 or 5000 in your browser.
The PowerShell launcher does not forward web ports; use VS Code for web problems.
If a problem provides `requirements.txt`, run `pip install -r requirements.txt`
inside the container as its specification instructs.

## Checking and submitting

`check50 --local SLUG` runs tests on your machine, downloading the checks from
GitHub as needed. Without `--local`, check50 uploads your work for remote checking.
Copy each problem's exact check50/submit50 slug from its current specification.

When you choose to submit, first sign in at [submit.cs50.io](https://submit.cs50.io/)
with your GitHub account and authorize CS50. Then, from that problem's directory:

```bash
submit50 cs50/problems/2026/x/me
```

Follow any authentication prompts from the tool. No account has been connected
and no coursework has been submitted during this setup. Running programs works
offline; initial test downloads and submissions need internet access.

Problem set 0 uses [Scratch](https://scratch.mit.edu/) separately in the browser.
Save your `.sb3` project in `pset0/scratch`.

## Downloads and maintenance

- `.devcontainer.json` pins the official course image and configures VS Code.
- `.devcontainer/setup.sh` installs the small x86 Linux runtime needed by the
  published Sort binaries on ARM. Docker Desktop supplies CPU emulation, so those
  binaries may run slower than native ARM code.
- `.downloads/` caches the original distribution ZIPs and their SHA-256 manifest.
- `python scripts/download-starters.py` downloads any missing official archives
  and extracts missing files, preserving existing files. It reads the current
  course pages; check the course year before reusing it in a later year.
- Automatic GitDoc commits are disabled for this local workspace. Back up your
  work yourself; this is separate from CS50's cloud Codespace backups.
- The upstream Docker socket mount and start hook were omitted: CS50x does not
  need nested Docker or the hook's extra R images and host image pruning.

Installed and checked on 25 October 2026: ARM64 course container, C compilation
and input through libcs50, local check50, style50-cli, Python course imports,
SQLite movies database, and the supplied x86 Sort executable. Tool versions:
Clang 18.1.3, Python 3.13.15, check50 3.5.0, style50 3.0.0, submit50 3.2.1.
Remote submission and the graphical debugger require your own interactive use.

Official setup reference: [CS50's local Docker instructions](https://cs50.readthedocs.io/cs50.dev/#offline-with-docker).
