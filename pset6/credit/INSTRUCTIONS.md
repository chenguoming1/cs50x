# Credit

[Complete official specification](https://cs50.harvard.edu/x/psets/6/credit/)
| [Problem Set 6 guide](../README.md)

## Your task

Create `credit.py`. Ask for a credit card number and determine whether it is a
valid American Express, MasterCard, or Visa number, using the validation rules
from the linked specification and Problem Set 1. Implement this version in Python.
The final line must be exactly one of `AMEX`, `MASTERCARD`, `VISA`, or `INVALID`,
followed by a newline. Input contains digits without hyphens.

Choose Credit or Cash; only one is required.

## Open and edit

```bash
cd /workspaces/cs50x/pset6/credit
code credit.py
```

Save your program with Ctrl+S.

## Run and check

```bash
python credit.py
style50-cli credit.py
check50 --local cs50/problems/2026/x/sentimental/credit
```

Use the example numbers in the official specification to test each card type
and invalid input manually.

## Submit when ready

```bash
submit50 cs50/problems/2026/x/sentimental/credit
```
