# Mario: less comfortable

[Complete official specification](https://cs50.harvard.edu/x/psets/1/mario/less/)
| [Problem Set 1 guide](../../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create mario.c. Ask for a positive integer height, asking again for invalid input, and print a right-aligned half-pyramid made of # characters. Avoid trailing spaces. Follow the current C specification: it asks for a positive height; the Python version in Problem Set 6 separately specifies a range of 1 through 8.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset1/mario/less
code mario.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make mario
./mario
style50-cli mario.c
```

Try negative numbers, zero, positive heights, text, and an empty input. Compare the alignment with the official examples.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/mario/less
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/mario/less
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
