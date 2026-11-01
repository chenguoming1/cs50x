# Birthdays

[Complete official specification](https://cs50.harvard.edu/x/psets/9/birthdays/)
| [Problem Set 9 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete the Flask app to display stored names and birthdays in a table on GET requests and add a new entry from a name/month/day form on POST requests. Work in app.py and templates/index.html. Editing or deleting birthdays and additional features are optional.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset9/birthdays
code app.py templates/index.html
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
flask run --host=0.0.0.0
```

In VS Code's **Ports** panel, open port **5000** in your browser.
Keep the server terminal running while testing. Use Ctrl+C to stop it before
typing other commands, or open a second terminal. Stop the previous problem's
server before starting another one on the same port.

Check the initial table, submit a new birthday, and confirm it persists after refreshing. Test form behavior and check the server terminal for errors. The specification uses manual browser testing rather than check50.

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/birthdays
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
