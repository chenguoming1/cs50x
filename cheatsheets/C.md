# C cheat sheet for CS50

Use this reference while working on the C problem sets. Examples explain language
features; adapt them to your own programs.

## Compile, run, and debug

Run commands in the **VS Code container terminal**. Change to your program's
folder first.

```bash
make demo             # Compile demo.c into an executable named demo
./demo                # Run it
./demo first second   # Run with two command-line arguments
style50-cli demo.c    # Check formatting
debug50 ./demo        # Debug inside VS Code
valgrind ./demo       # Check for invalid memory accesses and memory leaks
```

Compile again after editing C source. Press **Ctrl+C** to interrupt a running
program. `demo.c` is source code; `demo` is the compiled executable.

The course's `make` command configures the CS50 library for you. A direct compiler
command, when you want to see the options explicitly, is:

```bash
clang -std=c11 -Wall -Wextra -Werror -g demo.c -o demo -lcs50 -lm
```

`-g` adds debugging information; `-lcs50` links CS50's library; `-lm` links the
math library. `-Werror` makes compiler warnings fail the build.

## Program structure

```c
#include <stdio.h>

int main(void)
{
    printf("C is running.\n");
    return 0;
}
```

- `#include` makes declarations from a header available.
- Statements usually end with `;`. Blocks use `{ ... }`.
- `main` is where execution starts. Returning `0` indicates success.
- `// comment` comments one line; `/* comment */` can span multiple lines.

## Headers to recognize

| Header | Common features |
| --- | --- |
| `<stdio.h>` | `printf`, `FILE`, `fopen`, `fclose`, `fread`, `fwrite` |
| `<cs50.h>` | `get_int`, `get_long`, `get_float`, `get_double`, `get_char`, `get_string`, `string` |
| `<stdbool.h>` | `bool`, `true`, `false` in the C11 examples here |
| `<stdlib.h>` | `malloc`, `calloc`, `realloc`, `free`, `strtol`, `EXIT_FAILURE` |
| `<string.h>` | `strlen`, `strcmp`, `strcpy`, `memcpy` |
| `<ctype.h>` | `isalpha`, `isdigit`, `isspace`, `tolower`, `toupper` |
| `<math.h>` | `round`, `sqrt`, `pow` |
| `<stdint.h>` | Fixed-width integers such as `uint8_t` and `int16_t` |
| `<limits.h>` | Integer limits such as `INT_MAX` |

## Variables and types

```c
int count = 10;
long population = 8000000000L;
float temperature = 24.5f;
double average = 12.75;
char initial = 'A';
bool ready = true;        // Include <stdbool.h>
const int LIMIT = 100;    // Cannot assign a new value to LIMIT
```

| Type | Meaning | Typical `printf` format |
| --- | --- | --- |
| `int` | Integer | `%i` or `%d` |
| `long` | Integer with at least as much range as `int` | `%ld` |
| `long long` | Integer with at least as much range as `long` | `%lld` |
| `float`, `double` | Floating-point number | `%f`, or `%.2f` for two decimals |
| `char` | One character | `%c` |
| `char *`, CS50 `string` | Pointer to characters forming a string | `%s` |
| `size_t` | Unsigned size or count, returned by `sizeof` and `strlen` | `%zu` |
| Pointer | Memory address | `%p`, with an argument cast to `(void *)` |

Type sizes depend on the platform. Use `sizeof(type)` or `sizeof variable` when
you need the actual size. Initialize local variables before reading their values.

Single quotes mean a character: `'A'`. Double quotes mean a string: `"A"`.

## Input and output

```c
#include <cs50.h>
#include <stdio.h>

// Inside main:
int quantity = get_int("Quantity: ");
double price = get_double("Price: ");
printf("Quantity: %i; price: %.2f\n", quantity, price);
```

| Escape sequence | Meaning |
| --- | --- |
| `\n` | Newline |
| `\t` | Tab |
| `\"` | Double quote inside a string |
| `\\` | Backslash |
| `\0` | Null character that terminates a C string |

Use `%%` in a `printf` format to print a percent sign.

## Operators and arithmetic

| Operators | Meaning |
| --- | --- |
| `+`, `-`, `*`, `/` | Arithmetic |
| `%` | Integer remainder |
| `=`, `+=`, `-=`, `*=`, `/=` | Assignment and update |
| `++`, `--` | Add or subtract one |
| `==`, `!=`, `<`, `<=`, `>`, `>=` | Comparisons |
| `&&`, `\|\|`, `!` | Logical AND, OR, NOT |
| `&`, `\|`, `^`, `~`, `<<`, `>>` | Bit operations; unary `&` also takes an address |

```c
int whole = 5 / 2;           // 2: both operands are integers
double precise = 5.0 / 2;    // 2.5
double ratio = (double) 5 / 2;
int remainder = 7 % 3;       // 1
```

Casting the result of integer division is too late: `(double) (5 / 2)` is `2.0`.
Signed integer overflow is undefined behavior. Floating-point arithmetic can
have rounding error; a value such as `0.1` is not necessarily stored exactly.

## Conditions

```c
if (count > 10)
{
    printf("Large\n");
}
else if (count == 10)
{
    printf("Exactly ten\n");
}
else
{
    printf("Small\n");
}
```

`=` assigns; `==` compares. Zero is false; nonzero values are true.
`&&` and `||` short-circuit: the right side is evaluated only when needed.

```c
switch (initial)
{
    case 'A':
        printf("Option A\n");
        break;
    default:
        printf("Other option\n");
        break;
}
```

Without `break`, execution can continue into the next case.

## Loops

```c
for (int i = 0; i < 3; i++)
{
    printf("%i\n", i);  // 0, 1, 2
}

int remaining = 3;
while (remaining > 0)
{
    remaining--;
}

int choice;
do
{
    choice = get_int("Choose a positive number: ");
}
while (choice <= 0);
```

- `for`: useful when tracking an index or counter.
- `while`: checks the condition before the body; can run zero times.
- `do ... while`: checks afterward; runs at least once. Its final `;` is required.
- `break`: leaves the innermost loop.
- `continue`: skips to the next iteration of the innermost loop.

## Functions and scope

```c
int add(int a, int b);  // Declaration / prototype

int main(void)
{
    int total = add(2, 3);
    printf("%i\n", total);
    return 0;
}

int add(int a, int b)   // Definition
{
    return a + b;
}
```

Declare a function before calling it. `void` as the return type means the
function returns no value; `(void)` means it takes no arguments.

Variables declared inside a block are accessible within that block and nested
blocks. Function arguments are passed **by value**: the parameter receives a
copy. A copied pointer can still access and modify the object it points to.

A recursive function calls itself. Give it a base case and ensure each recursive
call makes progress toward that case.

## Arrays

```c
int scores[] = {12, 18, 24};
size_t length = sizeof scores / sizeof scores[0];

for (size_t i = 0; i < length; i++)
{
    printf("%i\n", scores[i]);
}

int grid[2][3] = {{1, 2, 3}, {4, 5, 6}};
printf("%i\n", grid[1][2]);  // 6
```

An array of length `n` has indexes `0` through `n - 1`. C does not automatically
check bounds. The `sizeof array / sizeof array[0]` formula works for an actual
array in scope; an array parameter in a function is adjusted to a pointer, so
pass its length separately.

## Strings

```c
#include <string.h>

char word[] = "cat";              // Four bytes: c, a, t, '\0'
word[0] = 'b';                    // word is now "bat"
size_t letters = strlen(word);    // 3, excluding the terminator

if (strcmp(word, "bat") == 0)
{
    printf("Same text\n");
}
```

- CS50's `string` is an alias for `char *`; it is not a built-in C type.
- Strings end at `\0`. Allocating for `n` characters needs at least `n + 1` bytes.
- `strcmp(a, b)` returns zero when the strings have equal contents. A negative
  or positive result indicates their lexicographic order; it need not be -1 or 1.
- `a == b` compares pointers when `a` and `b` are pointers, not string contents.
- `strcpy(destination, source)` requires enough space in the destination,
  including the terminator. Check capacity before copying.
- `const char *label = "example";` points at a string literal. Do not modify
  the literal.
- For `<ctype.h>` functions, pass `EOF` or a value representable as
  `unsigned char`, such as `isalpha((unsigned char) word[i])`.

## Pointers

For a deeper reference with diagrams and examples, see the dedicated
[pointer cheat sheet](POINTERS.md).

```c
int value = 7;
int *address = &value;

printf("%i\n", *address);          // Read the pointed-to int: 7
*address = 9;                      // Change value through the pointer
printf("%p\n", (void *) address);  // Print an address
```

| Expression | Meaning |
| --- | --- |
| `int *p` | Declare a pointer to an `int` |
| `&value` | Address of `value` |
| `*p` | Object pointed to by `p` |
| `NULL` | Null pointer constant |
| `p[i]` | Equivalent to `*(p + i)` for valid array access |

Only dereference pointers that refer to valid, accessible objects. A pointer to
a local variable becomes invalid after that variable's lifetime ends.

## Dynamic memory

```c
#include <stdlib.h>

// Inside a function:
size_t count = 10;
int *values = malloc(count * sizeof *values);
if (values == NULL)
{
    return 1;  // This example assumes a function returning int
}

for (size_t i = 0; i < count; i++)
{
    values[i] = 0;
}

free(values);
values = NULL;
```

- `malloc(bytes)` allocates uninitialized storage. Check for allocation failure.
- `calloc(count, size)` allocates storage with all bytes initialized to zero.
- `free(pointer)` releases dynamically allocated storage. Release each allocation
  once, when it is no longer needed; do not use it afterward.
- Do not `free` a stack array, string literal, or other non-owned allocation.
- Before allocating from a potentially large count, ensure `count * element_size`
  cannot overflow `size_t`.
- With `realloc`, use a temporary pointer so failure does not lose the original
  allocation. A successful reallocation may move the storage.

## Structs and linked nodes

```c
typedef struct
{
    int id;
    double score;
} record;

record item = {.id = 42, .score = 8.5};
record *pointer = &item;

printf("%i\n", item.id);
printf("%.1f\n", pointer->score);  // Equivalent to (*pointer).score

typedef struct node
{
    int value;
    struct node *next;
} node;
```

Use `object.member` for a struct object and `pointer->member` for a pointer to
a struct. `typedef` creates a type alias. A linked node stores a pointer to the
next node; a null next pointer commonly marks the end of a list.

## Command-line arguments

```c
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./demo argument\n");
        return 1;
    }

    printf("Argument: %s\n", argv[1]);
    return 0;
}
```

For `./demo apple`, `argc` is 2, `argv[0]` is the program name, and `argv[1]`
is `"apple"`. Check `argc` before accessing the argument you expect. Arguments
start as strings; converting them to numbers and validating them are separate
steps. `strtol` provides an end pointer and error reporting for robust conversion.

## File I/O

```c
// Inside main, with <stdio.h> included:
FILE *file = fopen("notes.txt", "r");
if (file == NULL)
{
    perror("notes.txt");
    return 1;
}

int ch;
while ((ch = fgetc(file)) != EOF)
{
    putchar(ch);
}

fclose(file);
```

Store `fgetc`'s result in an `int` so it can represent both character values and
the special `EOF` value. A loop ending at `EOF` can mean end of file or an error;
use `ferror(file)` to distinguish them before closing when needed.

| Operation | Purpose |
| --- | --- |
| `fopen(path, "r")` | Open an existing text file for reading |
| `fopen(path, "w")` | Create a text file or truncate its existing contents |
| `fopen(path, "a")` | Open a text file for appending |
| `"rb"`, `"wb"` | Binary reading / writing modes |
| `fgets(buffer, capacity, file)` | Read a bounded line; may retain its newline |
| `fprintf(file, format, ...)` | Write formatted text |
| `fread(buffer, size, count, file)` | Read up to `count` objects; return objects read |
| `fwrite(buffer, size, count, file)` | Write objects; return objects written |
| `fseek(file, offset, origin)` | Change the file position |
| `fclose(file)` | Close the stream and release its resources |

Check file-operation return values. A short read or write needs interpretation;
the requested number of objects is not guaranteed to be transferred.

## Common mistakes

| Symptom | Check |
| --- | --- |
| Compiler error near the next line | Missing `;`, quote, or closing brace earlier |
| Code after an `if` runs unexpectedly | Accidental `;` immediately after `if (...)` |
| Wrong result for an average | Integer division before conversion to floating point |
| Strings look equal but comparison fails | Pointer comparison instead of `strcmp` |
| Segmentation fault | Invalid pointer, null dereference, or out-of-bounds access |
| Unpredictable value | Uninitialized variable or invalid memory access |
| Memory leak | Allocation that was never released |
| Double-free / invalid-free error | Releasing the same allocation twice or freeing non-owned memory |
| Old behavior after editing | Executable was not recompiled |
| Infinite loop | Condition never changes, wrong update, or missing base case |

For unfamiliar library functions, consult the [CS50 manual](https://manual.cs50.io/).

[Back to the workspace guide](../README.md)
