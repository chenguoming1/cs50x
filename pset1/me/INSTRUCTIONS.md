# Hello, It's Me

[Complete official specification](https://cs50.harvard.edu/x/psets/1/me/)
| [Problem Set 1 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Create hello.c. Ask the user for their name and print a greeting containing it, ending with a newline. For the name Adele, the greeting should be hello, Adele.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset1/me
code hello.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make hello
./hello
style50-cli hello.c
```

Try several different names and check capitalization, punctuation, and the final newline.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/me
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/me
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
