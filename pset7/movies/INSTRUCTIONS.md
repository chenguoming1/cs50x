# Movies

[Complete official specification](https://cs50.harvard.edu/x/psets/7/movies/)
| [Problem Set 7 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Write the thirteen queries described in the specification in 1.sql through 13.sql. Use one query per file, returning only the requested data. Do not hard-code movie or person IDs. Check ordering, duplicate handling, and distinctions between people with the same name.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset7/movies
code 1.sql
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
sqlite3 movies.db '.schema'
sqlite3 movies.db < 1.sql
```

These commands run in Bash. At the `sqlite>` prompt, use `.tables` and
`.schema` to inspect the database; type `.quit` to return to Bash. End SQL
statements with `;`. Keep the supplied database unchanged.

Use the expected row counts and column requirements on the official page to check each query. The supplied database is a snapshot; live IMDb ratings may differ.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/movies
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/movies
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
