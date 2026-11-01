# Mario: less comfortable

[Complete official specification](https://cs50.harvard.edu/x/psets/6/mario/less/)
| [Problem Set 6 guide](../../README.md)

## Your task

Create `mario.py`. Use CS50's `get_int` to request a height from 1 through 8.
Keep asking when the height is invalid. Print a right-aligned half-pyramid using
`#` characters, without trailing spaces. For height 3:

```text
  #
 ##
###
```

Choose this version or Mario more; only one is required.

## Open and edit

```bash
cd /workspaces/cs50x/pset6/mario/less
code mario.py
```

Save your program with Ctrl+S.

## Run and check

```bash
python mario.py
style50-cli mario.py
check50 --local cs50/problems/2026/x/sentimental/mario/less
```

Try heights 1, 2, and 8, and invalid inputs such as -1, 0, 9, and text.

## Submit when ready

```bash
submit50 cs50/problems/2026/x/sentimental/mario/less
```
