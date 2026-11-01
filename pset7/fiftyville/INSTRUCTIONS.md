# Fiftyville

[Complete official specification](https://cs50.harvard.edu/x/psets/7/fiftyville/)
| [Problem Set 7 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Investigate the stolen duck using only the supplied town database. Identify the thief, escape destination, and accomplice. Record every investigative query in log.sql with a preceding SQL comment explaining its purpose. Fill the existing lines in answers.txt without changing their labels or adding lines.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset7/fiftyville
code log.sql answers.txt
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
sqlite3 fiftyville.db '.schema'
sqlite3 fiftyville.db
```

These commands run in Bash. At the `sqlite>` prompt, use `.tables` and
`.schema` to inspect the database; type `.quit` to return to Bash. End SQL
statements with `;`. Keep the supplied database unchanged.

Start from the incident details in the specification and inspect the database schema. Keep your investigation log as you work; submit both log.sql and answers.txt.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/fiftyville
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/fiftyville
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
