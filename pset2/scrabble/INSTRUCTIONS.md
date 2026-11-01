# Scrabble

[Complete official specification](https://cs50.harvard.edu/x/psets/2/scrabble/)
| [Problem Set 2 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create scrabble.c. Ask two players for a word, score letters using the point values in the specification, and announce Player 1 wins!, Player 2 wins!, or Tie!. Uppercase and lowercase letters have the same value; nonletters score zero. The official page provides code and hints inline rather than a ZIP.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset2/scrabble
code scrabble.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make scrabble
./scrabble
style50-cli scrabble.c
```

Try mixed-case words, punctuation, equal scores, and a win for each player.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/scrabble
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/scrabble
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
