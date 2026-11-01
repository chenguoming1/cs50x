# Inheritance

[Complete official specification](https://cs50.harvard.edu/x/psets/5/inheritance/)
| [Problem Set 5 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete create_family and free_family in inheritance.c. Model the requested family generations with allocated person records. The oldest generation gets random alleles; each younger person inherits one allele from each parent. Release the entire family when finished, following the starter interfaces.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset5/inheritance
code inheritance.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make inheritance
./inheritance
style50-cli inheritance.c
```

Run repeatedly and inspect the family tree for valid inheritance. After implementing it, use valgrind ./inheritance to check memory handling.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/inheritance
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/inheritance
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
