# Python regular expressions cheat sheet

A regular expression (regex) describes a text pattern. Python's built-in `re`
module can find matches, extract fields, replace text, and check input formats.
These examples target the Python 3.13 environment used by this workspace.

## Start here

```python
import re

text = "Room B has 24 seats"
match = re.search(r"[0-9]+", text)

if match is not None:
    print(match.group())   # 24 (a string)
    print(match.span())    # (11, 13): start included, end excluded
```

Read `r"[0-9]+"` as “one or more ASCII digits.” The `r` belongs to Python's
string syntax; it is not part of the regex pattern.

## Choose the operation

| Function | Use | Returns |
| --- | --- | --- |
| `re.search(pattern, text)` | Find the first match anywhere | Match object or `None` |
| `re.match(pattern, text)` | Match only at the beginning | Match object or `None` |
| `re.fullmatch(pattern, text)` | Require the entire string to match | Match object or `None` |
| `re.findall(pattern, text)` | Collect all non-overlapping matches | List; shape depends on capturing groups |
| `re.finditer(pattern, text)` | Iterate matches and positions | Iterator of match objects |
| `re.sub(pattern, replacement, text)` | Replace matches | New string |
| `re.split(pattern, text)` | Split at matching separators | List of strings |
| `re.compile(pattern)` | Create a reusable pattern object | Compiled pattern |

```python
import re

assert re.search(r"cat", "a cat naps") is not None
assert re.match(r"cat", "a cat naps") is None
assert re.match(r"cat", "catfish") is not None
assert re.fullmatch(r"cat", "catfish") is None
assert re.fullmatch(r"cat", "cat") is not None
```

Use `fullmatch` for whole-input format checks. A successful search for a number
inside a string does not mean the whole string is a number.

## Pattern building blocks

| Pattern | Meaning | Example |
| --- | --- | --- |
| `cat` | Literal text | Matches `cat` inside `catfish` |
| `.` | Any character except newline by default | `c.t` matches `cat` or `c7t` |
| `\.` | A literal dot | Matches the dot in `3.5` |
| `[abc]` | One character from this set | `a`, `b`, or `c` |
| `[a-z]` | One lowercase ASCII letter | `m` |
| `[A-Za-z]` | One ASCII letter | `M` or `m` |
| `[0-9]` | One ASCII digit | `7` |
| `[^0-9]` | One character that is not an ASCII digit | `x` or a newline |
| `\d` | Unicode decimal digit by default | ASCII digits and other decimal digit scripts |
| `\D` | Anything outside `\d` | `x` |
| `\w` | Unicode alphanumeric character or underscore | `A`, `7`, `_`, `é` |
| `\W` | Anything outside `\w` | `!` |
| `\s` | Whitespace | Space, tab, newline, and more |
| `\S` | Anything outside `\s` | `A` |
| `\b` | Word boundary, outside a character class | `r"\bcat\b"` excludes `catfish` |
| `^` | Start of string; also line starts with `re.MULTILINE` | `r"^Name:"` |
| `$` | End of string or before a final newline; also line ends with `re.MULTILINE` | `r"done$"` |
| `\A`, `\Z` | Strict start and end of the string in Python 3.13 | Unaffected by `re.MULTILINE` |

`\b` is defined using word/non-word characters, not human-language word parsing.
An underscore counts as a word character. Inside `[...]`, `\b` means backspace.
In a character class, a dot is literal: `[.]` matches a dot.

## Repetition

A quantifier applies to the preceding character, character class, or group.

| Pattern | Meaning |
| --- | --- |
| `a?` | Zero or one `a` |
| `a*` | Zero or more `a` characters |
| `a+` | One or more `a` characters |
| `a{3}` | Exactly three |
| `a{2,4}` | Between two and four |
| `a{2,}` | At least two |
| `(?:ab)+` | One or more repetitions of the whole `ab` group |

```python
import re

assert re.fullmatch(r"colou?r", "color") is not None
assert re.fullmatch(r"colou?r", "colour") is not None
assert re.fullmatch(r"[0-9]{4}", "2048") is not None
assert re.fullmatch(r"[0-9]{4}", "20489") is None
assert re.fullmatch(r"[0-9]*", "") is not None  # * permits an empty input
assert re.fullmatch(r"[0-9]+", "") is None     # + requires at least one
```

## Raw strings and escaping

```python
import re

assert re.search(r"\bcat\b", "a cat naps") is not None
assert re.fullmatch(r"3\.5", "3.5") is not None
assert re.fullmatch(r"3\.5", "3x5") is None
assert re.fullmatch(r"C:\\notes", "C:\\notes") is not None
```

Use raw strings for patterns so Python does not consume escapes intended for
regex. In an ordinary string, `"\b"` is a backspace character. Raw strings still
let the regex engine interpret escapes: `r"\n"` matches a newline, while
`r"\\n"` matches a literal backslash followed by `n`.

When inserting literal text into a pattern, escape its regex punctuation:

```python
import re

label = "total (USD)"
pattern = re.escape(label) + r":\s*([0-9]+)"
match = re.search(pattern, "total (USD): 42")
assert match is not None
print(match.group(1))      # 42
```

`re.escape` is for literal text inside a pattern, not for replacement strings.

## Groups and alternatives

- `(pattern)` captures the matched part.
- `(?:pattern)` groups without capturing.
- `(?P<name>pattern)` gives a capture a name.
- `A|B` matches either alternative, trying the left one first.

```python
import re

pattern = r"(?P<item>[A-Za-z]+):\s*(?P<count>[0-9]+)"
match = re.fullmatch(pattern, "Pencils: 12")
assert match is not None

print(match.group(0))      # Pencils: 12 (the whole match)
print(match.group(1))      # Pencils
print(match.group("count"))  # 12
print(match.groups())      # ('Pencils', '12')
print(match.groupdict())   # {'item': 'Pencils', 'count': '12'}
count = int(match.group("count"))
```

Captures are strings; convert them when needed. An optional group that did not
participate is `None` when accessed through a match object.

```python
import re

assert re.fullmatch(r"(?:yes|no)", "yes") is not None
assert re.fullmatch(r"(?:yes|no)", "maybe") is None
match = re.search(r"cat|catfish", "catfish")
assert match is not None
print(match.group())       # cat: alternatives are not automatically longest-first
```

Group alternatives when adding boundaries or other constraints:
`r"\b(?:cat|dog)\b"` applies both word boundaries to either animal.

## All matches: findall versus finditer

```python
import re

text = "A12 B34"
assert re.findall(r"[A-Z][0-9]+", text) == ["A12", "B34"]
assert re.findall(r"[A-Z]([0-9]+)", text) == ["12", "34"]
assert re.findall(r"([A-Z])([0-9]+)", text) == [("A", "12"), ("B", "34")]

for match in re.finditer(r"[A-Z][0-9]+", text):
    print(match.group(), match.span())
# A12 (0, 3)
# B34 (4, 7)
```

With no captures, `findall` returns whole-match strings. With one capture, it
returns that group's strings. With multiple captures, it returns tuples. Use
non-capturing groups when grouping should not change the result's shape.

Matches normally do not overlap. For example, `re.findall(r"ana", "banana")`
returns only one match.

## Greedy and lazy matching

Quantifiers such as `*` and `+` are greedy: they try longer matches first while
allowing the rest of the pattern to match. Add `?` to try shorter matches first.

```python
import re

text = "[red] [blue]"
assert re.findall(r"\[.*\]", text) == ["[red] [blue]"]
assert re.findall(r"\[.*?\]", text) == ["[red]", "[blue]"]
assert re.findall(r"\[[^\]]*\]", text) == ["[red]", "[blue]"]
```

The last pattern explicitly excludes a closing bracket from the contents. None
of these examples handles arbitrary nested brackets. Lazy does not mean faster
or that the rest of the pattern stops mattering.

## Replacing and splitting

```python
import re

text = "red   blue\tgreen"
assert re.sub(r"\s+", " ", text) == "red blue green"
assert re.sub(r"[0-9]+", "#", "A12 B34", count=1) == "A# B34"
assert re.split(r"[,;]\s*", "red, blue;green") == ["red", "blue", "green"]
assert re.split(r"([,;])", "red,blue;green") == ["red", ",", "blue", ";", "green"]
```

`sub` returns a new string. `split` includes separators if the separator pattern
captures them, and leading/trailing separators can produce empty strings.

Replacement strings can reference captured groups:

```python
import re

result = re.sub(r"([A-Za-z]+),\s*([A-Za-z]+)", r"\g<2> \g<1>", "Lee, Mina")
assert result == "Mina Lee"

result = re.sub(r"[0-9]+", lambda match: str(int(match.group()) * 2), "3 boxes, 4 bags")
assert result == "6 boxes, 8 bags"
```

Use `\g<name>` for named groups in replacement text. `\g<1>0` means group 1
followed by a literal zero; `\10` means group 10. For arbitrary literal
replacement text containing backslashes, a function avoids replacement escapes:

```python
import re

replacement = r"C:\notes"
result = re.sub(r"PLACEHOLDER", lambda match: replacement, "File: PLACEHOLDER")
assert result == r"File: C:\notes"
```

## Flags

| Flag | Effect |
| --- | --- |
| `re.IGNORECASE` / `re.I` | Match without case sensitivity |
| `re.MULTILINE` / `re.M` | Let `^` and `$` match line boundaries |
| `re.DOTALL` / `re.S` | Let `.` match newlines too |
| `re.ASCII` / `re.A` | Use ASCII definitions for shorthand classes and word boundaries |
| `re.VERBOSE` / `re.X` | Allow explanatory whitespace and comments in the pattern |

```python
import re

assert re.fullmatch(r"hello", "HELLO", flags=re.I) is not None
assert re.findall(r"^name", "Name: Mina\nname: Leo", flags=re.I | re.M) == ["Name", "name"]
assert re.fullmatch(r"a.b", "a\nb") is None
assert re.fullmatch(r"a.b", "a\nb", flags=re.S) is not None
assert re.fullmatch(r"\d+", "٣") is not None
assert re.fullmatch(r"\d+", "٣", flags=re.A) is None
```

`MULTILINE` does not make `.` match newlines, and does not make `re.match` search
every line. Use `search`/`finditer` with anchors for line-oriented searches.

## Compile and explain a pattern

```python
import re

item_code = re.compile(r"""
    [A-Z]{2}       # Two uppercase ASCII letters
    -              # Literal hyphen
    [0-9]{3}       # Three ASCII digits
""", flags=re.X)

assert item_code.fullmatch("AB-204") is not None
assert item_code.fullmatch("A-204") is None
assert item_code.findall("AB-204 CD-305") == ["AB-204", "CD-305"]
```

A compiled pattern offers methods such as `.search`, `.fullmatch`, and `.sub`.
Compilation is useful for naming and reusing a pattern; module-level functions
already cache recently used patterns.

With `VERBOSE`, literal spaces and `#` outside character classes need escaping
or a character class, such as `[ ]` and `[#]`.

## Lookarounds and backreferences

Lookarounds test surrounding text without including that surrounding text in
the match:

| Pattern | Meaning |
| --- | --- |
| `X(?=Y)` | Match `X` only when followed by `Y` |
| `X(?!Y)` | Match `X` only when not followed by `Y` |
| `(?<=Y)X` | Match `X` only when preceded by `Y` |
| `(?<!Y)X` | Match `X` only when not preceded by `Y` |

```python
import re

assert re.findall(r"[0-9]+(?=kg\b)", "5kg 8lb") == ["5"]
assert re.findall(r"(?<=USD )[0-9]+", "USD 25 EUR 40") == ["25"]
assert re.findall(r"\bcat\b(?!!)", "cat! cat?") == ["cat"]
```

Python's built-in `re` requires fixed-width lookbehind: `(?<=USD )` is valid,
but `(?<=USD\s+)` is not. Capture surrounding text when a lookbehind cannot
express what you need clearly.

A backreference matches the same text that a group captured earlier:

```python
import re

pattern = r"\b(?P<word>[A-Za-z]+)\s+(?P=word)\b"
match = re.search(pattern, "This is is repeated")
assert match is not None
assert match.group() == "is is"
assert match.group("word") == "is"
```

Named backreferences in a pattern use `(?P=name)`; replacements use `\g<name>`.
A numbered pattern backreference such as `r"([a-z])\1"` matches doubled letters.

## Small format checks

Use these patterns with `re.fullmatch(pattern, text)`:

| Format | Pattern | Accepted example |
| --- | --- | --- |
| Signed ASCII integer | `r"[+-]?[0-9]+"` | `-42` |
| Decimal with required integer part | `r"[+-]?[0-9]+(?:\.[0-9]+)?"` | `12.50` |
| Simple ASCII username, 3–16 characters | `r"[A-Za-z][A-Za-z0-9_]{2,15}"` | `Mina_7` |
| Six-digit hex color | `r"#[0-9A-Fa-f]{6}"` | `#12AbEF` |
| Date-shaped text | `r"[0-9]{4}-[0-9]{2}-[0-9]{2}"` | `2026-11-02` |

These define specific text formats. The decimal example excludes `.5`, `5.`, and
scientific notation. The date pattern also accepts impossible dates such as
`2026-99-99`; use `datetime.date.fromisoformat` for calendar validation.

## Common mistakes

| Symptom | Check |
| --- | --- |
| `AttributeError` when calling `.group()` | Did the search return `None`? |
| Pattern unexpectedly matches any character | Escape literal dots: `r"\."` |
| Word boundaries fail | Use a raw string: `r"\bword\b"` |
| Empty input is accepted | `*` and `?` can match zero characters; consider `+` |
| Extra text is accepted | Use `fullmatch` for whole-input validation |
| Results contain tuples or only part of the text | Check capturing groups in `findall` |
| Match crosses several delimiters | Use a narrower character class or lazy repetition |
| Whitespace disappears from a verbose pattern | Escape intended spaces or use `[ ]` |
| A pattern takes too long on almost-matching text | Simplify ambiguous nested repetitions such as `(a+)+` |

Prefer plain string tools when the task is literal: `in`, `.startswith`,
`.endswith`, `.replace`, and `.split` are often clearer. Use parsers such as
`csv` and `json` for structured data rather than building a large regex.

## Further reading

- [Python 3.13 `re` reference](https://docs.python.org/3.13/library/re.html)
- [Python basics](PYTHON.md)
- [Strings and collections](PYTHON-COLLECTIONS.md)
- [All cheat sheets](README.md)
