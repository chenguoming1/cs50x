# Cash

[Complete official specification](https://cs50.harvard.edu/x/psets/6/cash/)
| [Problem Set 6 guide](../README.md)

## Your task

Create `cash.py`. Use CS50's `get_float` to ask how much change is owed in dollars,
such as `0.41`. Ask again for invalid or negative input. Determine the minimum
number of coins needed using denominations of 25, 10, 5, and 1 cents. The final
output line must contain only that number and a newline.

Choose Cash or Credit; only one is required.

## Open and edit

```bash
cd /workspaces/cs50x/pset6/cash
code cash.py
```

Save your program with Ctrl+S.

## Run and check

```bash
python cash.py
style50-cli cash.py
check50 --local cs50/problems/2026/x/sentimental/cash
```

For example, `0.41` should need 4 coins, and `0.15` should need 2 coins.
Also test zero, negative input, and text.

## Submit when ready

```bash
submit50 cs50/problems/2026/x/sentimental/cash
```
