# Sort

[Complete official specification](https://cs50.harvard.edu/x/psets/3/sort/)
| [Problem Set 3 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Investigate the supplied sort1, sort2, and sort3 executables to determine which uses selection sort, bubble sort, and merge sort. Fill the TODOs in answers.txt with your conclusions and explanations. These programs are already compiled; you do not write or compile a sorting implementation.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset3/sort
code answers.txt
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
time ./sort1 random5000.txt > /dev/null
time ./sort2 random5000.txt > /dev/null
time ./sort3 random5000.txt > /dev/null
```

Compare behavior on random, sorted, and reverse-sorted inputs at several sizes. Explain your reasoning without changing the supplied programs. On this ARM computer the supplied Intel binaries run through emulation, so focus on patterns rather than absolute timing.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/sort
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/sort
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
