# DNA

[Complete official specification](https://cs50.harvard.edu/x/psets/6/dna/)
| [Problem Set 6 guide](../README.md)

## Your task

Complete the provided `dna.py` so that it identifies a person by comparing a DNA
sequence with STR counts in a CSV database. The program takes two command-line
arguments: the database path and the sequence path. Report incorrect command-line
usage. For each STR in the database header, compare the longest consecutive run
in the sequence against the people's profiles. Print the matching name, or
`No match` when no profile matches.

The starter program includes TODO comments and a `longest_match` helper.
The supplied `databases/` and `sequences/` folders are already downloaded.

## Open and edit

```bash
cd /workspaces/cs50x/pset6/dna
code dna.py
```

Save your changes with Ctrl+S.

## Run and check

```bash
python dna.py databases/small.csv sequences/1.txt
style50-cli dna.py
check50 --local cs50/problems/2026/x/dna
```

Use the official specification's database/sequence combinations and expected
results for manual testing. Also test missing and extra command-line arguments.

## Submit when ready

```bash
submit50 cs50/problems/2026/x/dna
```
