# Runoff

[Complete official specification](https://cs50.harvard.edu/x/psets/3/runoff/)
| [Problem Set 3 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete the TODO functions in runoff.c to simulate an instant-runoff election from ranked ballots. Account for valid preferences, vote totals, a majority winner, ties, and elimination of the lowest-ranked remaining candidates. Keep the supplied interfaces and other code as required.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset3/runoff
code runoff.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make runoff
./runoff Alice Bob Charlie
style50-cli runoff.c
```

Try invalid candidate names, a first-round winner, a winner after elimination, and a tie among all remaining candidates.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/runoff
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/runoff
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
