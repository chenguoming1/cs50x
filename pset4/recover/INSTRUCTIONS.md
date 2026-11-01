# Recover

[Complete official specification](https://cs50.harvard.edu/x/psets/4/recover/)
| [Problem Set 4 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete recover.c to recover JPEGs from a forensic image. Accept exactly one input filename, handle an unreadable file or wrong argument count with the specified error behavior, and write recovered images as 000.jpg, 001.jpg, and so on. Avoid memory leaks.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset4/recover
code recover.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make recover
./recover card.raw
style50-cli recover.c
```

Run on the supplied card.raw and open the recovered JPEGs. Also test missing or extra arguments and an input file that does not exist.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/recover
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/recover
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
