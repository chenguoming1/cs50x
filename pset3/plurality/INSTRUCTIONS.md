# Plurality

[Complete official specification](https://cs50.harvard.edu/x/psets/3/plurality/)
| [Problem Set 3 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete vote and print_winner in the provided plurality.c. Count valid votes for named candidates and print every candidate tied for the highest total. Follow the allowed-edit rules in the specification.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset3/plurality
code plurality.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make plurality
./plurality Alice Bob Charlie
style50-cli plurality.c
```

Try different candidate counts, valid and invalid names, one winner, and tied winners.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/plurality
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/plurality
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
