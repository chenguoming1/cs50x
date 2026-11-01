# C pointers cheat sheet

A pointer holds an address. Dereferencing a pointer accesses the object at that
address. Start with these three expressions:

| Expression | Read it as |
| --- | --- |
| `number` | The value stored in `number` |
| `&number` | The address of `number` |
| `*p` | The object at the address stored in `p` |

## 1. Address versus value

```c
int number = 42;
int *p = &number;

printf("%i\n", number);      // 42
printf("%p\n", (void *) p);  // Address of number; varies between runs
printf("%i\n", *p);          // 42

*p = 99;
printf("%i\n", number);      // 99
```

Include `<stdio.h>` for `printf`.

```text
p                          number
+------------------+       +--------+
| &number          | ----> | 42     |
+------------------+       +--------+
```

`p` and `number` are separate variables. Changing `*p` changes `number`.
Changing `p` changes which object the pointer refers to.

## 2. Declaring pointers

```c
int *p;           // Pointer to int; not initialized yet
char *text;       // Pointer to char
double *price;    // Pointer to double
int **pp;         // Pointer to a pointer to int

int *a, *b;       // Both are pointers
int *c, d;        // c is a pointer; d is an int
```

The `*` in a declaration helps specify a type. The `*` in an expression such as
`*p = 10` dereferences a pointer.

Prefer one declaration per line while learning:

```c
int *p = NULL;
int *q = NULL;
```

`NULL` is available from headers including `<stddef.h>`, `<stdio.h>`, and
`<stdlib.h>`. Assign a valid address before dereferencing either pointer.

## 3. Copying pointers creates aliases

```c
int number = 5;
int *p = &number;
int *q = p;

*q = 12;
printf("%i\n", *p);  // 12
```

Both pointers refer to the same integer. `q = p` copies an address; it does not
create a separate copy of the pointed-to object.

```text
p ----+
      +----> number: 12
q ----+
```

## 4. Pointers and functions

C passes function arguments **by value**, including pointer arguments. A function
receives a copy of the address, through which it can change the caller's object.

```c
void set_value(int *destination)
{
    *destination = 25;
}

// Inside main:
int number = 0;
set_value(&number);
printf("%i\n", number);  // 25
```

The caller must supply a valid pointer to an integer it may modify. Put the
function definition or a prototype before the call.

To exchange two caller-owned values:

```c
void swap(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

// Inside main:
int left = 3;
int right = 8;
swap(&left, &right);
// left is 8; right is 3
```

Assigning a different address to the function's pointer parameter changes only
that local copy. To change the caller's pointer itself, pass its address.

## 5. Pointer to pointer: `int **`

```c
void point_to(int **destination, int *target)
{
    *destination = target;
}

// Inside main:
int number = 7;
int *p = NULL;
point_to(&p, &number);
printf("%i\n", *p);  // 7
```

| Expression in the function | Type | Meaning |
| --- | --- | --- |
| `destination` | `int **` | Address of the caller's pointer |
| `*destination` | `int *` | The caller's pointer |
| `**destination` | `int` | The integer that pointer refers to, if valid |

Do not evaluate `**destination` before the inner pointer refers to a valid `int`.

## 6. Arrays and pointer arithmetic

```c
int values[] = {10, 20, 30};
int *p = values;

printf("%i\n", p[0]);      // 10
printf("%i\n", *(p + 1));  // 20
printf("%i\n", values[2]); // 30
```

In most expressions, an array converts to a pointer to its first element:
`values` becomes `&values[0]`.

- `p[i]` means `*(p + i)`.
- `p + 1` advances by **one element**, not necessarily one byte.
- For an array of `n` elements, dereference only indexes `0` through `n - 1`.
- You may form a pointer one past the array, such as `values + 3` here, but must
  not dereference it. Pointer arithmetic must stay within that array or one past.
- Subtract two pointers only when they refer into the same array or one past it.

### An array is not a pointer variable

```c
int values[3] = {10, 20, 30};
int *p = values;

size_t array_bytes = sizeof values; // Storage for three ints
size_t pointer_bytes = sizeof p;    // Storage for one pointer
size_t length = sizeof values / sizeof values[0]; // 3
```

Do not assume these sizes are the same on every platform. The length formula
works for an actual array, not a pointer or an array parameter.

```c
void inspect(int values[], size_t length);
// In this parameter list, int values[] is adjusted to int *values.
```

`&values` for the actual array has a different type: a pointer to the whole
array, `int (*)[3]`. A two-dimensional array is not interchangeable with `int **`.

### Passing an array to `int *`, and a pointer to `int []`

Both directions work. In a function parameter list, `int items[]` is adjusted
to `int *items`. With `const`, both forms provide read-only access through that
parameter. The caller must provide enough elements for the count it passes.

This complete example shows both styles:

```c
#include <stddef.h>
#include <stdio.h>

void print_pointer(const int *items, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%i%s", *(items + i), i + 1 == count ? "\n" : " ");
    }
}

void print_array(const int items[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%i%s", items[i], i + 1 == count ? "\n" : " ");
    }
}

int main(void)
{
    int numbers[] = {10, 20, 30};
    size_t count = sizeof numbers / sizeof numbers[0];
    int *p = numbers;

    print_pointer(numbers, count); // Array argument -> pointer parameter
    print_array(p, count);         // Pointer argument -> array-style parameter

    return 0;
}
```

Both calls print `10 20 30`. You can also call `print_pointer(p, count)` or
`print_array(numbers, count)`.

Inside **either** function, `items[i]` and `*(items + i)` mean the same thing.
The array is not copied, and its length is not automatically passed. Writing
`int items[3]` as a function parameter also adjusts to a pointer; that spelling
alone does not check that the caller supplies three elements.

### A pointer to one element can be passed too

```c
int numbers[] = {10, 20, 30};
int *p = &numbers[1];

print_array(p, 2);            // Prints 20 30
print_pointer(&numbers[1], 2); // Same starting point and count
```

These calls start at the second element. Only two elements remain available;
passing a count of three would make the functions read past the array.
For a pointer to a standalone `int`, the available element count is one.

### Passing `p` versus passing `*p`

For `int *p`, `p` has type `int *`, while `*p` has type `int`.

```c
void show_number(int value)
{
    printf("%i\n", value);
}

void change_number(int *destination)
{
    *destination = 50;
}

// Inside main:
int numbers[] = {10, 20, 30};
int *p = numbers;

show_number(*p);           // Pass the first integer's value: 10
show_number(numbers[0]);   // Same value
change_number(p);          // Pass an address; numbers[0] becomes 50
change_number(&numbers[0]); // Same address
```

| Argument | Type in this example | Suitable parameter |
| --- | --- | --- |
| `numbers` | Converts from an array to `int *` | `int *items` or `int items[]` |
| `p` | `int *` | `int *items` or `int items[]` |
| `&numbers[0]` | `int *` | Pointer to the first element |
| `*p` | `int` | `int value` |
| `numbers[0]` | `int` | `int value` |
| `&p` | `int **` | Pointer-to-pointer parameter |
| `&numbers` | `int (*)[3]` | Pointer to a whole three-element array |

Use an address when the function expects a pointer. Dereference a valid pointer
when the function expects the pointed-to value.

### Passing a pointer to the whole array

A pointer to an element and a pointer to an entire array have different types:

```c
void change_last(int (*items)[3])
{
    (*items)[2] = 99;
}

// Inside main:
int numbers[3] = {10, 20, 30};
int (*whole)[3] = &numbers;

change_last(&numbers); // Pass the address of the whole array
change_last(whole);    // Pass a pointer variable of that same type
// numbers is now {10, 20, 99}
```

`int (*items)[3]` means “pointer to an array of three ints.” The parentheses
matter: `int *items[3]` would declare an array of three pointers.

For a whole-array pointer, `(*items)[i]` accesses an element. Advancing `items`
by one steps over a whole three-int array. Do not pass an ordinary `int *` to
`change_last`; its parameter requires `int (*)[3]`.

### Assigning a pointer is not assigning an array

```c
int numbers[] = {10, 20, 30};
int *p = numbers; // Valid: store the first element's address in p
p = &numbers[1]; // Valid: redirect p to another element

// numbers = p;  // Invalid: an array cannot be assigned a new address
```

To change an array's contents, assign its elements or copy values into its
existing storage. Passing an `int *` to an array-style parameter does not turn
the pointer variable into an array object.

## 7. Strings are character sequences ending in `\0`

```c
char word[] = "cat";
char *p = word;

printf("%s\n", p);          // cat: print characters until '\0'
printf("%c\n", *p);         // c: print the first character
printf("%p\n", (void *) p); // Print the address

p[0] = 'b';
printf("%s\n", word);       // bat
```

`word` has four characters of storage: `'c'`, `'a'`, `'t'`, and `'\0'`.

```c
const char *label = "cat"; // Literal automatically includes a final '\0'
// Do not modify the literal.

char editable[] = "cat";  // An array containing a writable copy
editable[0] = 'b';
```

The compiler stores `"cat"` as `'c'`, `'a'`, `'t'`, `'\0'`; you do not need to
write the terminator yourself. `label` points to its first character.

- CS50's `string` is an alias for `char *`.
- `strcmp(first, second) == 0` checks equal string contents; `first == second`
  compares addresses when both expressions are pointers.
- `strlen(text)` counts characters before `\0`; it excludes the terminator.
- For `n` characters plus a terminator, reserve at least `n + 1` bytes.
- Copying a `char *` copies an address, not the text.
- A `char *` does not tell you who owns its storage. Follow the relevant
  library's ownership rules before freeing it.

## 8. Allocate, use, free

This complete program owns a dynamically allocated array:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t count = 3;
    int *values = malloc(count * sizeof *values);
    if (values == NULL)
    {
        return 1;
    }

    for (size_t i = 0; i < count; i++)
    {
        values[i] = (int) i;
    }

    printf("%i\n", values[2]); // 2
    free(values);
    values = NULL;
    return 0;
}
```

| Operation | Effect |
| --- | --- |
| `malloc(bytes)` | Allocate uninitialized storage |
| `calloc(count, size)` | Allocate storage with all bytes set to zero |
| `free(p)` | Release the allocation pointed to by `p` |
| `free(NULL)` | Valid; does nothing |

`sizeof *values` asks for the size of one `int`. For this ordinary non-VLA type,
it does not read the pointed-to integer. `sizeof values` would give the size of
the pointer, which is usually the wrong quantity for allocating array elements.

For potentially large counts, check that the size multiplication cannot overflow.
Check allocation results, initialize storage before reading it, and free each
owned allocation exactly once. Pass the allocation's start pointer to `free`,
not a pointer advanced into its middle.

### Resizing with `realloc`

```c
// values is an existing malloc/calloc/realloc allocation.
// new_count is positive, and its size calculation has been checked.
int *grown = realloc(values, new_count * sizeof *values);
if (grown == NULL)
{
    // Resizing failed; values still refers to the original allocation.
    // Handle the failure without losing that allocation.
}
else
{
    values = grown;
}
```

A successful resize may move the allocation. Do not keep using old aliases or
pointers into the previous allocation. Added storage is uninitialized.

## 9. Lifetime and ownership

```c
int number = 5;
int *p = &number;
// Do not free(p): number is a local variable, not a malloc allocation.
```

A local variable normally lives until its block ends. Returning its address
would leave the caller with an invalid pointer after the function returns:

```c
// Incorrect example: do not use this function.
int *bad_address(void)
{
    int temporary = 5;
    return &temporary;
}
```

Dynamically allocated storage lives until it is freed, even if the function that
allocated it has returned. Decide which part of your program owns and releases it.

Setting one pointer to `NULL` does not update its aliases:

```c
int *p = malloc(sizeof *p);
if (p == NULL)
{
    return 1; // Example assumes an int-returning function
}
int *q = p;
free(p);
p = NULL;
// q is now dangling. Do not dereference or free q.
```

Checking `p != NULL` only rules out a null pointer. It does not establish that
the pointed-to object is still alive, in bounds, initialized, or writable.

## 10. Pointers to structs

```c
typedef struct node
{
    int value;
    struct node *next;
} node;

node item = {.value = 10, .next = NULL};
node *p = &item;

printf("%i\n", item.value);
printf("%i\n", p->value);    // Same as (*p).value
p->value = 20;
```

| Expression | Use when |
| --- | --- |
| `item.value` | `item` is a struct object |
| `p->value` | `p` is a pointer to a valid struct object |
| `p->next` | Read or update the next-node pointer |
| `p->next->value` | Access the next node, only if that node exists |

## 11. Read declarations with `const`

```c
int first = 1;
int second = 2;

const int *a = &first;       // Cannot modify first through a; can redirect a
int *const b = &first;       // Can modify first through b; cannot redirect b
const int *const c = &first; // Neither modification through c nor redirection

a = &second; // Valid
*b = 3;      // Valid
```

`const int *` and `int const *` mean the same thing. Adding `const` to an access
path does not make every other alias to the underlying object const.

## 12. Precedence traps

| Expression | Meaning |
| --- | --- |
| `*p++` | `*(p++)`: use the old pointed-to object, then advance `p` |
| `(*p)++` | Increment the pointed-to value |
| `*++p` | Advance `p`, then access the new pointed-to object |
| `p->value` | `(*p).value` |
| `*p = 0` | Store zero in the pointed-to object |
| `p = NULL` | Change the pointer itself to a null pointer |

Use parentheses when they make the operation clearer. Any pointer movement and
dereference must still obey the array-boundary and lifetime rules.

## 13. Debugging checklist

Before dereferencing a pointer, ask:

1. Was this pointer initialized?
2. Does it refer to an object that is still alive?
3. Is the access within that object's bounds?
4. Is the pointed-to type appropriate for the object?
5. If reading, has the value been initialized?
6. If writing, is the object writable?

| Problem | Common cause |
| --- | --- |
| Segmentation fault | Null/dangling pointer or an out-of-bounds access |
| Value changes unexpectedly | Two pointers alias the same object |
| Caller pointer did not change | Reassigned a pointer parameter instead of using a pointer to pointer |
| Invalid free | Freed a local object, literal, interior pointer, or already-freed allocation |
| Memory leak | Lost the last owning pointer before freeing its allocation |
| Wrong allocation size | Used `sizeof pointer` instead of `sizeof *pointer` |
| String contains garbage | Missing terminator, insufficient storage, or uninitialized bytes |

For a program saved as `pointer_demo.c`, run in the container terminal:

```bash
make pointer_demo
./pointer_demo
debug50 ./pointer_demo
valgrind ./pointer_demo
```

In the debugger, inspect the pointer and the pointed-to value separately. Address
values can change between runs, so focus on which objects they refer to.

[General C cheat sheet](C.md) | [All cheat sheets](README.md)
