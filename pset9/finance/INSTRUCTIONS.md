# C$50 Finance

[Complete official specification](https://cs50.harvard.edu/x/psets/9/finance/)
| [Problem Set 9 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete registration, stock quotes, purchases, portfolio display, sales, and transaction history. Add at least one personal feature of the scope described in the specification. Store password hashes, maintain each user's cash and holdings, record transactions, and reject invalid or unaffordable operations. Consult the route-by-route requirements for exact form field names and behavior.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset9/finance
code app.py templates/layout.html
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
pip install -r requirements.txt
flask run --host=0.0.0.0
```

In VS Code's **Ports** panel, open port **5000** in your browser.
Keep the server terminal running while testing. Use Ctrl+C to stop it before
typing other commands, or open a second terminal. Stop the previous problem's
server before starting another one on the same port.

Test registration and login, valid and invalid symbols, share counts, insufficient cash or shares, portfolio totals, history, and your personal feature. Quote lookup needs internet access. Start with the supplied helpers and requirements; the course app does not require a separate API-key setup.

After manual testing, run the official checks locally:

```bash
check50 --local cs50/problems/2026/x/finance
```

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/finance
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
