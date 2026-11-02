# Python strings and collections

Companion to the [Python basics cheat sheet](PYTHON.md). Use this for choosing
containers, working with text, and reading records from files.

## Choose a type

| Type | Example | Use for | Mutable? |
| --- | --- | --- | --- |
| `str` | `"hello"` | Text | No |
| `list` | `[4, 7, 4]` | Ordered sequence you can change | Yes |
| `tuple` | `(10, 20)` | Fixed group of values | No |
| `dict` | `{"name": "Mina", "age": 22}` | Key → value lookup | Yes |
| `set` | `{"red", "blue"}` | Unique values and membership | Yes |

Lists and tuples allow duplicates. Dictionaries preserve insertion order;
sets do not provide a defined iteration order. Dictionary keys and set elements
must be hashable: strings and integers work, lists and dictionaries do not.

## Strings: indexing and slicing

```python
text = "python"

print(len(text))           # 6
print(text[0])             # p
print(text[-1])            # n
print(text[1:4])           # yth
print(text[:2])            # py
print(text[2:])            # thon
print(text[::2])           # pto
print(text[::-1])          # nohtyp
```

Slices use `[start:stop:step]`; `stop` is excluded. Out-of-range slice bounds
are clipped, but a single out-of-range index raises `IndexError`. The same
indexing and slicing syntax works for lists and tuples.

Python has no separate `char` type: `text[0]` is a one-character string. String
indices count Unicode code points, which may differ from visible characters.

## String operations

```python
text = "  Red apple  "

print(text.strip())                  # Red apple
print(text.lower())                  #   red apple  (spaces retained)
print(text.upper())                  #   RED APPLE  (spaces retained)
print(text.replace("apple", "pear"))  #   Red pear
print("apple" in text)               # True
print(text.strip().startswith("Red"))  # True
print(text.strip().endswith("apple"))  # True
print(text.find("apple"))            # 6; -1 if absent
print("ha-ha".count("ha"))            # 2
print("go" * 3)                      # gogogo
```

Strings cannot be modified in place. Methods return results, so assign the
result when you want to keep it: `text = text.strip()`.

```python
words = "one   two\nthree".split()    # Splits runs of whitespace
print(words)                        # ['one', 'two', 'three']
print(" | ".join(words))             # one | two | three
print("a,,b".split(","))              # ['a', '', 'b']

print("Hello".isalpha())             # True
print("42".isdigit())                # True
print(" \t".isspace())               # True
```

`split()` and `split(" ")` differ: the latter splits only literal spaces and
can retain empty fields. `join` requires strings. `count` counts non-overlapping
matches, and does not measure the longest consecutive run.

Character tests support Unicode. `isdigit()` is not a general replacement for
`try: int(text)`: signed integers fail `isdigit`, and some Unicode digit
characters accepted by `isdigit` cannot be converted by `int`.

## Lists

```python
scores = [12, 18, 15]
scores.append(20)          # [12, 18, 15, 20]
scores.extend([10, 14])    # Adds each item
scores[0] = 13             # Replace one item
last = scores.pop()        # Removes and returns 14
scores.remove(18)          # Removes the first matching value

print(scores)             # [13, 15, 20, 10]
print(len(scores))        # 4
print(sum(scores))        # 58
print(min(scores))        # 10
print(max(scores))        # 20
print(15 in scores)       # True
```

`remove(value)` raises `ValueError` if the value is missing; `pop()` on an empty
list raises `IndexError`. `min` and `max` need a nonempty collection unless you
provide a suitable `default`.

```python
scores = [12, 18, 15]
ordered = sorted(scores)  # New list: [12, 15, 18]
print(scores)             # Original unchanged: [12, 18, 15]
scores.sort(reverse=True) # Changes original to [18, 15, 12]
```

Do not write `scores = scores.sort()`: `sort` returns `None`. The same caution
applies to `append`, `extend`, and other methods that only modify the list.

## Looping over collections

```python
names = ["Mina", "Leo", "An"]

for name in names:
    print(name)

for index, name in enumerate(names):
    print(index, name)                 # Index starts at 0

for position, name in enumerate(names, start=1):
    print(position, name)              # Display positions starting at 1

scores = [17, 19, 16]
for name, score in zip(names, scores):
    print(name, score)
```

`zip` normally stops at the shortest input. `zip(a, b, strict=True)` raises
`ValueError` during iteration when the lengths differ.

Prefer iterating directly when you need values; use `enumerate` when you also
need indices. Avoid adding/removing items from a collection while iterating
over it; build a new result instead.

## Comprehensions

```python
numbers = [1, 2, 3, 4]
squares = [number ** 2 for number in numbers]       # [1, 4, 9, 16]
evens = [number for number in numbers if number % 2 == 0]  # [2, 4]
labels = {number: str(number) for number in numbers}
```

Read a list comprehension as “produce this expression for each item, optionally
keeping only items that pass this condition.” Use a normal loop when the logic
needs several steps or would be difficult to read.

## Dictionaries

```python
person = {"name": "Mina", "age": 22}
print(person["name"])                 # Mina
person["age"] = 23                    # Update
person["city"] = "Singapore"          # Add
print(person.get("nickname", "—"))    # Default if key is absent
print("name" in person)               # Checks keys, not values

for key, value in person.items():
    print(key, value)

del person["city"]
```

`person["missing"]` raises `KeyError`; `person.get("missing")` returns `None`.
`get(key, default)` does not insert a missing key. Use `.keys()`, `.values()`, or
`.items()` to iterate keys, values, or pairs.

Example of accumulating counts:

```python
colors = ["red", "blue", "red"]
counts = {}
for color in colors:
    counts[color] = counts.get(color, 0) + 1

print(counts)                         # {'red': 2, 'blue': 1}
```

## Sets and tuples

```python
seen = set()                         # {} creates an empty dict, not a set
seen.add("red")
seen.add("red")
seen.add("blue")
print(len(seen))                     # 2
seen.discard("green")                # Does nothing if absent

a = {1, 2, 3}
b = {3, 4}
print(a & b)                         # Intersection: {3}
print(sorted(a | b))                 # Union, sorted: [1, 2, 3, 4]
print(sorted(a - b))                 # Difference, sorted: [1, 2]

point = (10, 20)
x, y = point                        # Unpack two values
single = (10,)                       # Comma makes a one-item tuple
```

A tuple cannot have its elements reassigned, but it can contain a mutable object
such as a list. A tuple is hashable only if all its elements are hashable.

## References, copies, and mutation

```python
original = [1, 2]
alias = original
alias.append(3)
print(original)                      # [1, 2, 3]: same list

separate = original.copy()
separate.append(4)
print(original)                      # Still [1, 2, 3]
```

`=` binds a name to an object; it does not copy the object. `.copy()` and list
slicing make shallow copies, so nested objects can still be shared.

```python
rows = [[0] * 3 for _ in range(2)]    # Two separate lists
rows[0][0] = 1
print(rows)                          # [[1, 0, 0], [0, 0, 0]]
```

Avoid `rows = [[0] * 3] * 2` when rows must be independent: it repeats references
to the same inner list. Use `copy.deepcopy` when you need a recursive copy of
nested mutable data.

Default arguments are evaluated once, when a function is defined. Avoid mutable
defaults such as `def add_item(item, items=[])`. Use `None` and create a new list
inside the function when no list is supplied.

## Text files

Create `notes.txt` containing a few lines before running this example:

```python
with open("notes.txt", encoding="utf-8") as file:
    for line in file:
        print(line.rstrip("\n"))
```

`with` closes the file even when the block raises an error. Paths are relative
to the terminal's working directory, not automatically the script's directory.
`file.read()` reads the remaining contents as one string. Iterating line by line
avoids loading the entire file at once.

```python
with open("notes-output.txt", "w", encoding="utf-8") as file:
    file.write("First line\n")
```

`"r"` reads; `"w"` creates or overwrites; `"a"` creates or appends. `write` does
not add a newline. `strip()` removes surrounding whitespace, so use it only
when discarding that whitespace is intended.

## CSV records

Example `people.csv`:

```csv
name,score
Mina,17
Leo,19
```

```python
import csv

with open("people.csv", newline="", encoding="utf-8") as file:
    reader = csv.DictReader(file)
    for row in reader:
        name = row["name"]
        score = int(row["score"])
        print(f"{name}: {score}")
```

`DictReader` normally uses the first row as field names. Fields are strings, so
convert numeric values explicitly. Use `csv.reader(file)` when you want each
row as a list instead. Use `newline=""` when opening CSV files, and use the
CSV parser rather than `split(",")` so quoted commas are handled correctly.
These conventions follow the [Python CSV documentation](https://docs.python.org/3.13/library/csv.html).

## Quick reminders

| Need | Expression |
| --- | --- |
| Length | `len(values)` |
| Membership | `value in values` |
| Last item | `values[-1]` (requires a nonempty sequence) |
| Copy a list | `values.copy()` |
| Sort without modifying original | `sorted(values)` |
| Reverse iteration | `reversed(values)` |
| All conditions true | `all(conditions)`; true for an empty iterable |
| At least one true | `any(conditions)`; false for an empty iterable |
| Unique values | `set(values)` (elements must be hashable) |
| Dictionary fallback | `mapping.get(key, default)` |
| Join strings | `separator.join(parts)` |

See also the [Python data structures tutorial](https://docs.python.org/3.13/tutorial/datastructures.html),
[Python basics](PYTHON.md), [regular expressions](PYTHON-REGEX.md), and
[all cheat sheets](README.md).
