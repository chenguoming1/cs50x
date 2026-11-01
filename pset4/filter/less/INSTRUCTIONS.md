# Filter: less comfortable

[Complete official specification](https://cs50.harvard.edu/x/psets/4/filter/less/)
| [Problem Set 4 guide](../../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Implement grayscale, sepia, horizontal reflection, and box blur in helpers.c. Change only that file and keep all function signatures. Use the supplied Makefile to build the filter program.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset4/filter/less
code helpers.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make filter
./filter -g images/yard.bmp out.bmp
style50-cli helpers.c
```

Test all four filters on the provided BMP images. Replace -g with -s, -r, or -b to select sepia, reflection, or blur; view out.bmp in VS Code.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/filter/less
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/filter/less
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
