# Volume

[Complete official specification](https://cs50.harvard.edu/x/psets/4/volume/)
| [Problem Set 4 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete volume.c so it accepts input and output WAV paths and a scaling factor. Preserve the 44-byte WAV header, scale each signed 16-bit sample, and write the result. Follow the starter program's argument and file-handling behavior, and avoid memory leaks.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset4/volume
code volume.c
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
make volume
./volume input.wav output.wav 2.0
style50-cli volume.c
```

Run with factors 2.0 and 0.5. Open the input and output audio files from VS Code to compare them.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/volume
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/volume
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
