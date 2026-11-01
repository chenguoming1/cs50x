# Readability

[Complete official specification](https://cs50.harvard.edu/x/psets/6/readability/)
| [Problem Set 6 guide](../README.md)

## Your task

Create `readability.py`. Ask for text using CS50's `get_string` and report its
reading grade using the Coleman-Liau index:

```text
index = 0.0588 * L - 0.296 * S - 15.8
```

Here, `L` is letters per 100 words and `S` is sentences per 100 words. Count English
letters a-z and A-Z; spaces separate words; `.`, `!`, and `?` end sentences.
Round the index to the nearest integer. Print `Grade X`, using `Grade 16+` for
16 or above and `Before Grade 1` for an index below 1.

## Open and edit

```bash
cd /workspaces/cs50x/pset6/readability
code readability.py
```

Save your program with Ctrl+S.

## Run and check

```bash
python readability.py
style50-cli readability.py
check50 --local cs50/problems/2026/x/sentimental/readability
```

Use the sample passages and expected grades from the official specification.

## Submit when ready

```bash
submit50 cs50/problems/2026/x/sentimental/readability
```
