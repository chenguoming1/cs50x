# Speller

[Complete official specification](https://cs50.harvard.edu/x/psets/5/speller/)
| [Problem Set 5 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Implement load, hash, size, check, and unload in dictionary.c using a hash table. Keep the required function signatures, leave speller.c and Makefile unchanged, and follow the permitted dictionary.h changes. Dictionary matching must be case-insensitive and memory must be released. Aim for correct results and efficient performance.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset5/speller
code dictionary.c dictionary.h
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make speller
./speller texts/cat.txt
style50-cli dictionary.c dictionary.h
```

Start with a short supplied text, then try larger texts and alternate dictionaries. Compare reported words with the supplied keys. Use valgrind ./speller texts/cat.txt to check memory handling.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/speller
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/speller
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
