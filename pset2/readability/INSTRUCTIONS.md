# Readability

[Complete official specification](https://cs50.harvard.edu/x/psets/2/readability/)
| [Problem Set 2 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create readability.c. Request text and calculate its reading level with the Coleman-Liau index: 0.0588 * L - 0.296 * S - 15.8. L is letters per 100 words and S is sentences per 100 words. Apply the specification's counting and rounding rules. Output Grade X, Grade 16+, or Before Grade 1 as appropriate.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset2/readability
code readability.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make readability
./readability
style50-cli readability.c
```

Compare your program with the official sample passages and expected grades, including the lowest and highest grade ranges.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/readability
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/readability
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
