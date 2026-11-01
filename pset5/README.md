# Problem Set 5: Data Structures

[Official problem set](https://cs50.harvard.edu/x/psets/5/) | [All problem sets](../PROBLEMS.md)

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

Complete Inheritance, then Speller.

| Task | Local instructions | Files to work on |
| --- | --- | --- |
| Inheritance | [Open guide](inheritance/INSTRUCTIONS.md) | `inheritance.c` |
| Speller | [Open guide](speller/INSTRUCTIONS.md) | `dictionary.c dictionary.h` |

## How to work

Open the source file from the relevant guide, make your changes, and save
with Ctrl+S. Use `make PROGRAM` to compile, then `./PROGRAM` to run the result.
Type requested input in the terminal and press Enter. Run `make` again after
changing C code. Use Ctrl+C to interrupt a program.

The Sort exercise uses supplied executables and a text answer file, so it does
For problems with a supplied Makefile, use it as instructed in the problem guide.

After manual testing, use the guide's `style50-cli` and `check50 --local`
commands where provided. C terminal programs need no forwarded web port.

## Checking and submission

Use the exact commands in each problem's guide. `check50 --local` downloads
checks and runs them on your computer; it needs internet for the downloads.
Running checks does not submit anything.

When ready to submit, sign in and authorize CS50 at
[submit.cs50.io](https://submit.cs50.io/), then follow the problem's submission
steps and any authentication prompts yourself. Scratch uses a browser upload;
the other submitted problems use the listed submit50 command.

For setup troubleshooting, see the [workspace guide](../README.md).
