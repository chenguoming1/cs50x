# Trivia

[Complete official specification](https://cs50.harvard.edu/x/psets/8/trivia/)
| [Problem Set 8 guide](../README.md)

Requirements and course commands checked on 25 October 2026. Read the full
specification for demonstrations, all edge cases, and permitted edits.

## Your task

Complete the trivia page with one multiple-choice question and one free-response question, each using an h3 heading. Provide at least three multiple-choice buttons with exactly one correct answer. Use JavaScript to show green and Correct! for a right answer, or red and Incorrect for a wrong answer. The free-response input also needs a confirmation button and equivalent feedback.

## Open and edit

In VS Code's container Bash terminal:

```bash
cd /workspaces/cs50x/pset8/trivia
code index.html styles.css
```

Save changes with Ctrl+S. Create a source file if it is not provided; existing
starter files and datasets are already downloaded.

## Run and check

```bash
http-server
```

In VS Code's **Ports** panel, open port **8080** in your browser.
Keep the server terminal running while testing. Use Ctrl+C to stop it before
typing other commands, or open a second terminal. Stop the previous problem's
server before starting another one on the same port.

Test every choice and both correct and incorrect typed answers in the browser. Check the browser console for errors. This assignment specifies manual browser testing, not a check50 command.

## Submit when ready

Run this from the problem folder after signing in and authorizing CS50 at
[submit.cs50.io](https://submit.cs50.io/):

```bash
submit50 cs50/problems/2026/x/trivia
```

Follow the authentication and file confirmation prompts yourself. Checking
does not submit your work.
