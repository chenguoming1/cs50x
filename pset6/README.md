# Problem Set 6: Python

Start here: [official Problem Set 6 instructions](https://cs50.harvard.edu/x/psets/6/).
This guide adapts the course workflow to your local container. The linked course
pages contain the complete specifications, demonstrations, and test examples.
Instructions checked on 25 October 2026.

Keep the [Python cheat sheet](../cheatsheets/PYTHON.md) and
[strings and collections reference](../cheatsheets/PYTHON-COLLECTIONS.md)
nearby while working through these exercises.

## Open the container terminal

1. Open this workspace in VS Code. Its title should include
   **[Dev Container: CS50x Local]**.
2. Select **Terminal > New Terminal**, or press **Ctrl+`** to show the existing
   terminal. The Bash terminal with the `$` prompt runs inside the container.
3. Click beside `$` before typing a command. Do not type the `$` itself.

To confirm your location, run:

```bash
pwd
```

The workspace root is `/workspaces/cs50x`. The `cd` commands below work from any
folder in the container. Use `ls` to see the current folder's contents.

## What to complete

Complete these five tasks in order. Choose one Mario version and one of Cash or
Credit; both alternatives have prepared folders.

| Order | Task | Local instructions | Source file |
| --- | --- | --- | --- |
| 1 | Hello, Again | [Hello](hello/INSTRUCTIONS.md) | `hello/hello.py` |
| 2 | Mario, less comfortable | [Mario less](mario/less/INSTRUCTIONS.md) | `mario/less/mario.py` |
| 2 | Mario, more comfortable | [Mario more](mario/more/INSTRUCTIONS.md) | `mario/more/mario.py` |
| 3 | Cash, less comfortable | [Cash](cash/INSTRUCTIONS.md) | `cash/cash.py` |
| 3 | Credit, more comfortable | [Credit](credit/INSTRUCTIONS.md) | `credit/credit.py` |
| 4 | Readability | [Readability](readability/INSTRUCTIONS.md) | `readability/readability.py` |
| 5 | DNA | [DNA](dna/INSTRUCTIONS.md) | `dna/dna.py` |

Each problem folder now has an `INSTRUCTIONS.md` with its requirements and exact
run, check, and submit commands. DNA's `dna.py`, `databases/`, and `sequences/`
are already downloaded. Create the other Python source files yourself as you
reach each task.

The course names the first few folders `sentimental-hello`, `sentimental-cash`,
and so on. This workspace organizes them under `pset6` with shorter names; run
the commands from the appropriate folder, keeping the required `.py` filename
and the exact check50/submit50 identifier.

## Start with Hello

In the container terminal:

```bash
cd /workspaces/cs50x/pset6/hello
code hello.py
```

Write your program in the editor and save it with **Ctrl+S**. Then click the
terminal again and run:

```bash
python hello.py
```

When the program asks for input, type your answer in the terminal and press
**Enter**. Python programs run directly; you do not use `make`.

After testing your program manually:

```bash
style50-cli hello.py
check50 --local cs50/problems/2026/x/sentimental/hello
```

`style50-cli` checks formatting. `check50 --local` downloads the official tests
and runs them on this computer. A failed check is feedback to help you revise
your program. To interrupt a program that is stuck or waiting for input, press
**Ctrl+C** in its terminal.

## Submit when ready

First sign in at [submit.cs50.io](https://submit.cs50.io/) with your GitHub account
and authorize CS50. From the Hello folder, run:

```bash
submit50 cs50/problems/2026/x/sentimental/hello
```

Follow the authentication and file confirmation prompts yourself. Each problem's
`INSTRUCTIONS.md` lists its own submission command. Checking and submitting are
separate actions; running check50 does not submit your work.

## Common setup questions

- **Do I need a web port?** No. Problem Set 6 runs in the terminal.
- **Do I need to install Python or cs50?** No. Both are installed in the container.
- **The source file is missing.** Create it with the exact name listed above.
  Opening a new file with `code` does not save it until you press Ctrl+S.
- **Python cannot find my file.** Use the problem's `cd` command, then `ls` to check
  that the source file is saved in that folder.
- **I see `>>>` instead of `$`.** You opened Python's interactive prompt. Type
  `exit()` and press Enter, then run `python filename.py` at the Bash prompt.
- **VS Code is no longer connected.** Start Docker Desktop, open this workspace,
  and select **Ctrl+Shift+P > Dev Containers: Reopen in Container**.

For container setup details, see the [workspace guide](../README.md).
