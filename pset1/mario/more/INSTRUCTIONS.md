# Mario: more comfortable

[Complete official specification](https://cs50.harvard.edu/x/psets/1/mario/more/)
| [Problem Set 1 guide](../../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create mario.c. Ask for a height from 1 through 8, asking again until it is valid. Print two half-pyramids of hashes, separated by exactly two spaces. Do not leave spaces after the final hash on each line.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset1/mario/more
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

Try heights 1, 2, and 8, then invalid values such as -1, 0, 9, text, and an empty input.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/mario/more
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/mario/more
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
