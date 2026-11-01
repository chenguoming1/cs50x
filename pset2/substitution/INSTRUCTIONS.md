# Substitution

[Complete official specification](https://cs50.harvard.edu/x/psets/2/substitution/)
| [Problem Set 2 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create substitution.c. Accept one key consisting of 26 distinct alphabetic characters, with validation independent of case. Request plaintext and replace its letters using that alphabet mapping. Preserve the case of the message and leave nonletters unchanged. Handle invalid keys and argument counts as specified.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset2/substitution
code substitution.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make substitution
./substitution NQXPOMAFTRHLZGECYJIUWSKDVB
style50-cli substitution.c
```

Try a valid alphabet mapping, mixed-case text, punctuation, keys of the wrong length, duplicate letters, nonletters, and missing or extra arguments.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/substitution
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/substitution
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
