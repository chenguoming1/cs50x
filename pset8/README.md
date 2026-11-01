# Problem Set 8: HTML, CSS, JavaScript

[Official problem set](https://cs50.harvard.edu/x/psets/8/) | [All problem sets](../PROBLEMS.md)

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

Complete Trivia, then Homepage.

| Task | Local instructions | Files to work on |
| --- | --- | --- |
| Trivia | [Open guide](trivia/INSTRUCTIONS.md) | `index.html styles.css` |
| Homepage | [Open guide](homepage/INSTRUCTIONS.md) | `index.html styles.css` |

## How to work

Change to the problem directory and run `http-server`.
In VS Code's **Ports** panel, open **8080** in your browser. Keep the server
terminal running while you test. Use Ctrl+C to stop it, or open another
terminal for other commands. Stop one problem's server before starting
another on the same port.

Save edits with Ctrl+S and refresh the browser. Check your browser console and
server terminal when something fails. Individual guides say whether automated
checks are available; do not assume every web assignment has check50.

## Checking and submission

Use the exact commands in each problem's guide. `check50 --local` downloads
checks and runs them on your computer; it needs internet for the downloads.
Running checks does not submit anything.

When ready to submit, sign in and authorize CS50 at
[submit.cs50.io](https://submit.cs50.io/), then follow the problem's submission
steps and any authentication prompts yourself. Scratch uses a browser upload;
the other submitted problems use the listed submit50 command.

For setup troubleshooting, see the [workspace guide](../README.md).
