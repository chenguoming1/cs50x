# Caesar

[Complete official specification](https://cs50.harvard.edu/x/psets/2/caesar/)
| [Problem Set 2 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create caesar.c. Accept one non-negative integer key as a command-line argument, request plaintext, and print its Caesar-cipher ciphertext. Wrap alphabetically, preserve letter case, and leave nonletters unchanged. Reject invalid keys or argument counts with the error behavior in the specification.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset2/caesar
code caesar.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make caesar
./caesar 13
style50-cli caesar.c
```

Try key 0, keys larger than 26, mixed-case text, punctuation, a missing key, a nonnumeric key, and extra arguments.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/caesar
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/caesar
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
