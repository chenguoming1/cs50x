# Credit

[Complete official specification](https://cs50.harvard.edu/x/psets/1/credit/)
| [Problem Set 1 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create credit.c. Request a credit card number and validate it using the checksum, lengths, and starting digits described in the specification. Print exactly AMEX, MASTERCARD, VISA, or INVALID, followed by a newline.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset1/credit
code credit.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make credit
./credit
style50-cli credit.c
```

Use the official sample numbers to exercise each card type, incorrect lengths, and invalid checksums.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/credit
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/credit
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
