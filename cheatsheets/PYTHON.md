# Python cheat sheet for CS50

Use this while working on Problem Set 6. Examples demonstrate language features
and use Python 3.13, which is installed in this workspace's container.

For more examples, see [strings and collections](PYTHON-COLLECTIONS.md).

## Run, check, and submit

Run these in the **VS Code container terminal**, from your program's folder:

```bash
python demo.py              # Run a file; no make step
python demo.py first second # Supply command-line arguments
python                     # Open the interactive Python prompt (>>>).
python -m pdb demo.py       # Run with Python's terminal debugger
style50-cli demo.py         # Check formatting
```

At `>>>`, use `exit()` to return to the shell. Press **Ctrl+C** to interrupt a
running program. Save the file before running it again.

For the Hello exercise specifically:

```bash
cd /workspaces/cs50x/pset6/hello
python hello.py
check50 --local cs50/problems/2026/x/sentimental/hello
check50 cs50/problems/2026/x/sentimental/hello
submit50 cs50/problems/2026/x/sentimental/hello
```

`check50 --local` runs checks locally; `check50` runs remote checks. Only
`submit50` submits. Use each problem's `INSTRUCTIONS.md` for its exact identifier.

## C to Python at a glance

| C | Python | Note |
| --- | --- | --- |
| `int count = 0;` | `count = 0` | No type declaration required |
| `true`, `false` | `True`, `False` | Capital letters matter |
| `NULL` | `None` | Python's missing-value marker; not a pointer |
| `printf("%i\n", count);` | `print(count)` | Newline included by default |
| `strlen(text)` | `len(text)` | Number of characters in a string |
| `strcmp(a, b) == 0` | `a == b` | Compare string contents directly |
| `&&`, `\|\|`, `!` | `and`, `or`, `not` | Logical operators |
| `else if` | `elif` | Ends with a colon |
| `i++` | `i += 1` | Python has no increment operator |
| `for (int i = 0; i < n; i++)` | `for i in range(n):` | Stop value is excluded |
| `{ ... }` block | Indented block | Use four spaces per level |
| `// comment` | `# comment` | `//` means floor division in Python |
| `malloc` / `free` | Automatic memory management | Objects can still be shared by references |

## Program structure

```python
def main():
    temperature = 24
    print(f"Temperature: {temperature} C")


if __name__ == "__main__":
    main()
```

Python executes top-level statements in order. The final condition calls `main`
when this file is run directly, but not when another file imports it. Define your
functions before the call to `main`. Small programs can also use top-level code.

- End `def`, `if`, `elif`, `else`, `for`, and `while` headers with `:`.
- Indentation determines which statements belong to a block.
- No semicolons are needed. Use `#` for comments.
- Function calls need parentheses: `main()` calls; `main` refers to the function.

## Variables and basic types

```python
count = 12                  # int
price = 4.75                # float
title = "Notebook"          # str
available = True            # bool
result = None               # No value yet
LIMIT = 100                 # Uppercase is a convention, not enforcement

print(type(count))          # <class 'int'>
```

Python integers can grow beyond C's fixed-width integer limits, subject to
available memory. Strings are immutable; lists and dictionaries are mutable.

```python
int("42")                  # 42
float("3.5")               # 3.5
str(42)                    # "42"
int(3.9)                   # 3: truncates toward zero
bool("")                   # False
bool("False")              # True: this is a nonempty string!
```

`int("3.5")` raises `ValueError`. Conversion is not input validation by itself.

## Input and output

```python
label = input("Label: ")    # Always returns a string
print("You entered", label)
print(f"Label: {label}")    # f-string inserts expressions inside braces

price = 4.5
print(f"Price: ${price:.2f}")  # Price: $4.50
print("A", "B", sep="-")     # A-B
print("Loading", end="...")  # No trailing newline here
print("done")
```

CS50 input helpers are also available:

```python
from cs50 import get_float, get_int, get_string

quantity = get_int("Quantity: ")
weight = get_float("Weight: ")
description = get_string("Description: ")
```

The numeric helpers retry when input cannot be parsed as the requested type.
You still need to enforce your program's allowed range.

## Arithmetic

| Expression | Result | Meaning |
| --- | --- | --- |
| `7 + 2` | `9` | Addition |
| `7 - 2` | `5` | Subtraction |
| `7 * 2` | `14` | Multiplication |
| `7 / 2` | `3.5` | True division |
| `7 // 2` | `3` | Floor division |
| `-7 // 2` | `-4` | Rounds down, unlike C integer truncation |
| `7 % 2` | `1` | Remainder |
| `2 ** 3` | `8` | Exponentiation |
| `abs(-7)` | `7` | Absolute value |

`^` is bitwise XOR, not exponentiation. Use parentheses to make grouping clear.

```python
count = 10
count += 1
count -= 2
count *= 3
count /= 2                 # Result becomes a float
```

Floating-point arithmetic can be approximate: `0.1 + 0.2 == 0.3` is false.
`round` uses ties-to-even for exact halfway cases: `round(2.5)` is `2`, while
`round(3.5)` is `4`. This differs from C's `round` for halfway cases.
Formatting with `:.2f` changes displayed text, not the stored number.

## Conditions

```python
temperature = 24

if temperature < 18:
    print("Cool")
elif temperature <= 28:
    print("Comfortable")
else:
    print("Warm")

if 18 <= temperature <= 28:
    print("Inside the range")
```

| Operator | Meaning |
| --- | --- |
| `==`, `!=` | Equal, unequal |
| `<`, `<=`, `>`, `>=` | Ordered comparisons |
| `and`, `or`, `not` | Logical operations; `and` and `or` short-circuit |
| `in`, `not in` | Membership |
| `is`, `is not` | Object identity; commonly `value is None` |

Use `==` for matching values. Do not use `is` to compare string or number values.
`and` and `or` return one of their operands, so their result need not be a Boolean.

`False`, `None`, numeric zero, and empty strings/collections are false in a
condition. Nonempty strings such as `"0"` and `"False"` are true.

## Loops

```python
for i in range(3):
    print(i)               # 0, 1, 2 on separate lines

for i in range(2, 7, 2):
    print(i)               # 2, 4, 6

for i in range(3, 0, -1):
    print(i)               # 3, 2, 1

for character in "cat":
    print(character)       # c, a, t
```

`range(start, stop, step)` excludes `stop`. Its step cannot be zero.

```python
remaining = 3
while remaining > 0:
    print(remaining)
    remaining -= 1
```

- `break` exits the innermost loop.
- `continue` skips to the next iteration.
- `return` exits the entire function.
- `pass` does nothing; it can temporarily fill an otherwise empty block.

Python has no `do ... while`. A validation loop can use `while True`:

```python
from cs50 import get_int

while True:
    quantity = get_int("Quantity (1–20): ")
    if 1 <= quantity <= 20:
        break
```

## Functions and scope

```python
def rectangle_area(width, height):
    return width * height


area = rectangle_area(4, 3)
print(area)                # 12
```

`return` sends a value to the caller. `print` displays something. A function
without an explicit return value returns `None`.

```python
def format_label(text, prefix="Item"):
    return f"{prefix}: {text}"


print(format_label("Book"))
print(format_label("Book", prefix="Selected"))
```

Assigning a name inside a function normally makes it local to that function.
Prefer passing values in and returning results instead of changing globals.
Python `if` and `for` blocks do not create a separate local scope.

Type hints are optional and do not enforce types at runtime:

```python
def double(number: int) -> int:
    return number * 2
```

## Imports and command-line arguments

```python
import math
from pathlib import Path

print(math.sqrt(81))
print(Path("notes.txt").suffix)  # .txt
```

Avoid filenames such as `csv.py`, `math.py`, or `cs50.py`: they can hide the
module you intended to import. Similarly, avoid variable names like `list` or
`str` when you still need those built-in functions.

Save this example as `demo.py`, then run `python demo.py notes.txt`:

```python
import sys

if len(sys.argv) != 2:
    sys.exit("Usage: python demo.py filename")

filename = sys.argv[1]
print(f"Selected file: {filename}")
```

`sys.argv[0]` is the script name. All arguments are strings. `sys.exit("message")`
prints an error and exits unsuccessfully; `sys.exit(0)` indicates success.

## Exceptions and debugging

```python
try:
    quantity = int(input("Quantity: "))
except ValueError:
    print("Enter a whole number")
else:
    print(f"Accepted: {quantity}")
```

Catch the error you expect. A broad `except:` can hide bugs and catch interrupts.
Read the last line of a traceback first, then locate the relevant file and line.

| Error | Usual cause |
| --- | --- |
| `SyntaxError` | Missing colon, quote, bracket, or invalid syntax |
| `IndentationError` / `TabError` | Incorrect indentation or mixed tabs/spaces |
| `NameError` | Name not defined, misspelled, or unavailable in this scope |
| `TypeError` | Wrong kind of value, such as `"4" + 2` |
| `ValueError` | Right type but invalid value, such as `int("cat")` |
| `IndexError` | List/string index out of range |
| `KeyError` | Dictionary key does not exist |
| `AttributeError` | Object has no requested method/attribute |
| `FileNotFoundError` | Wrong filename or working directory |
| `ModuleNotFoundError` | Module unavailable in the current Python environment |

Useful temporary debugging tools:

```python
value = "  text\n"
print(repr(value))         # Shows whitespace and escape sequences
print(type(value))
assert len(value) > 0      # Raises AssertionError if false
```

`assert` is useful for development checks, not required user-input validation:
Python's optimized mode can disable it. Put `breakpoint()` in your program to
pause in the debugger; use `n` for next, `s` to step into, `p expression` to
inspect, `c` to continue, and `q` to quit. Remove debugging output before checks
that require exact output.

## Further reading

- [Python 3.13 tutorial: introduction](https://docs.python.org/3.13/tutorial/introduction.html)
- [Strings and collections cheat sheet](PYTHON-COLLECTIONS.md)
- [Regular expressions cheat sheet](PYTHON-REGEX.md)
- [Problem Set 6 workspace guide](../pset6/README.md)
- [All cheat sheets](README.md)
