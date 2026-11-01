# Filter: more comfortable

[Complete official specification](https://cs50.harvard.edu/x/psets/4/filter/more/)
| [Problem Set 4 guide](../../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Implement grayscale, horizontal reflection, box blur, and Sobel edge detection in helpers.c. Change only that file and keep all function signatures. Use the supplied Makefile to build the filter program.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset4/filter/more
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

Test all four filters on the provided BMP images. Replace -g with -r, -b, or -e to select reflection, blur, or edges; view out.bmp in VS Code.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/filter/more
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/filter/more
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
