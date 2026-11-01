# Tideman

[Complete official specification](https://cs50.harvard.edu/x/psets/3/tideman/)
| [Problem Set 3 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete vote, record_preferences, add_pairs, sort_pairs, lock_pairs, and print_winner in tideman.c. Simulate the ranked-pairs election defined in the specification: record preferences, order victories by strength, and build the locked graph without cycles before reporting its source. Keep the required function signatures.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset3/tideman
code tideman.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make tideman
./tideman Alice Bob Charlie
style50-cli tideman.c
```

Try different rankings, invalid names, tied pairwise preferences, different victory strengths, and cases where an edge would create a cycle.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/tideman
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/tideman
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
