# Problem Set 7: SQL

[Official problem set](https://cs50.harvard.edu/x/psets/7/) | [All problem sets](../PROBLEMS.md)

These local guides summarize the requirements and adapt the course commands to
this workspace. The official specifications have the complete examples and rules.
Checked on 25 October 2026.

## Open the container terminal

1. Start Docker Desktop and open this workspace in VS Code.
2. Confirm the title includes **[Dev Container: CS50x Local]**. Otherwise use
   **Ctrl+Shift+P > Dev Containers: Reopen in Container**.
3. Select **Terminal > New Terminal**, or press **Ctrl+`** to show the terminal.
4. Click beside the Bash `$` prompt before typing. Do not type the `$` itself.

The workspace is `/workspaces/cs50x` inside the container. Each problem guide
starts with an absolute `cd` command, so it works from any current directory.
Use `pwd` to see your location and `ls` to list its files.

## What to complete

Complete Songs, Movies, and Fiftyville in that order.

| Task | Local instructions | Files to work on |
| --- | --- | --- |
| Songs | [Open guide](songs/INSTRUCTIONS.md) | `1.sql answers.txt` |
| Movies | [Open guide](movies/INSTRUCTIONS.md) | `1.sql` |
| Fiftyville | [Open guide](fiftyville/INSTRUCTIONS.md) | `log.sql answers.txt` |

## How to work

Edit the numbered SQL files and save with Ctrl+S. Execute a query from Bash
with `sqlite3 DATABASE.db < NUMBER.sql`, using the problem's actual filenames.
For interactive exploration, run `sqlite3 DATABASE.db`; use `.tables`, `.schema`,
and `.quit` at its prompt. SQL statements end with semicolons.

The supplied SQL files are placeholders; add your own queries. Keep an
investigation log for Fiftyville and complete the required text answers.
SQLite exercises need no web server or forwarded port.

## Checking and submission

Use the exact commands in each problem's guide. `check50 --local` downloads
checks and runs them on your computer; it needs internet for the downloads.
Running checks does not submit anything.

When ready to submit, sign in and authorize CS50 at
[submit.cs50.io](https://submit.cs50.io/), then follow the problem's submission
steps and any authentication prompts yourself. Scratch uses a browser upload;
the other submitted problems use the listed submit50 command.

For setup troubleshooting, see the [workspace guide](../README.md).
