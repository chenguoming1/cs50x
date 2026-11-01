# Cash

[Complete official specification](https://cs50.harvard.edu/x/psets/1/cash/)
| [Problem Set 1 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create cash.c. Ask for a non-negative integer amount of change in cents and print the minimum number of 25-, 10-, 5-, and 1-cent coins needed. Ask again when the input is invalid. This C version takes cents; the Python version in Problem Set 6 takes dollars.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset1/cash
code cash.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make cash
./cash
style50-cli cash.c
```

Check that 0 needs 0 coins, 25 needs 1, and 26 needs 2. Also try a negative number and text.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/cash
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/cash
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
