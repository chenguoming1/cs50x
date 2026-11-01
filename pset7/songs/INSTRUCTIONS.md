# Songs

[Complete official specification](https://cs50.harvard.edu/x/psets/7/songs/)
| [Problem Set 7 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Write the eight SQL queries requested by the specification in 1.sql through 8.sql. Each file should contain one query returning only the requested columns and rows. Do not hard-code song or artist IDs. Complete answers.txt with your audio-aura interpretation and its limitations, as requested in the Spotify Wrapped section.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset7/songs
code 1.sql answers.txt
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
sqlite3 songs.db '.schema'
sqlite3 songs.db < 1.sql
```

These commands run in Bash. At the `sqlite>` prompt, use `.tables` and
`.schema` to inspect the database; type `.quit` to return to Bash. End SQL
statements with `;`. Keep the supplied database unchanged.

Compare columns, sort order, and results against each numbered requirement. Submit answers.txt as well as the eight SQL files.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/songs
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/songs
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
