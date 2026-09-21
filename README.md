# ft_printf

A personal implementation of the C standard `printf()` function,
developed as part of the 42 / 1337 Common Core.

> **Status:** Work in progress --- mandatory conversions are still being
> completed.

## Overview

The goal of `ft_printf` is to recreate the core behavior of `printf()`
while learning how variadic functions, format-string parsing, type
handling, number-base conversion, pointers, and modular C design work.

The current implementation is organized around a simple separation of
responsibilities:

``` text
ft_printf()
    │
    ▼
 parser
    │
    ├── %c ──► ft_putchar()
    ├── %s ──► ft_putstr()
    ├── %d ──► ft_putnbr()
    ├── %i ──► ft_putnbr()
    ├── %u ──► ft_putnbr_unsigned()
    ├── %x/%X ──► ft_put_hex()
    └── %p ──► ft_print_pointer()
```

The parser answers **"what conversion is this?"**, while the utility
functions answer **"how do I print it?"**.

## Current Features

### Implemented

  Conversion   Description                Status
  ------------ -------------------------- --------------------------------
  `%c`         Character                  ✅
  `%s`         String                     ✅
  `%p`         Pointer address            ✅
  `%d %i`      Signed decimal integer     ✅
  `%u`         Unsigned decimal integer   ✅
  `%x`         Lowercase hexadecimal      ✅
  `%X`         Uppercase hexadecimal      ✅
  `%%`         Literal `%`                ✅

### Not implemented yet

The project currently does not implement the bonus formatting system:

-   `-`
-   `0`
-   `.`
-   field width
-   `#`
-   `+`
-   space

These should be added only after the mandatory conversions are complete
and well tested.

## Project Structure

``` text
ft_printf/
├── Makefile
├── ft_printf.h
├── ft_printf.c
│
├── parser/
│   └── parsing.c
│
└── utils/
    ├── check_base.c
    ├── ft_print_pointer.c
    ├── ft_put_hex.c
    ├── ft_putchar.c
    ├── ft_putnbr.c
    ├── ft_putnbr_unsigned.c
    └── ft_putstr.c
```

### `ft_printf.c`

Entry point for the library.

It:

1.  receives the format string and variadic arguments;
2.  initializes `va_list`;
3.  delegates interpretation to `parser()`;
4.  closes the variadic argument list;
5.  returns the number of characters reported as printed.

### `parser/parsing.c`

Responsible for scanning the format string and dispatching conversions.

For example:

``` c
ft_printf("Hello %s: %d", name, age);
```

The parser identifies:

-   `%s` → retrieve a `char *`
-   `%d` → retrieve an `int`

The parser then sends the retrieved value to the appropriate printing
helper.

### `utils/`

Contains the actual output helpers:

-   `ft_putchar()` --- print one character
-   `ft_putstr()` --- print a string
-   `ft_putnbr()` --- print a signed integer
-   `ft_putnbr_unsigned()` --- print an unsigned integer
-   `ft_put_hex()` --- print an unsigned integer in hexadecimal
-   `ft_print_pointer()` --- print a pointer
-   `check_base()` --- select lowercase/uppercase hexadecimal digits

## Variadic Arguments

One of the main concepts of this project is the `<stdarg.h>` API:

``` c
va_list
va_start
va_arg
va_end
```

The parser uses the conversion specifier to determine the correct type
to retrieve:

``` c
va_arg(args, int)
va_arg(args, char *)
va_arg(args, unsigned int)
va_arg(args, void *)
```

The format string therefore acts like a small language that the parser
interprets.

## Number Conversion

### Decimal

`ft_putnbr()` recursively divides a number by `10`.

For example:

``` text
1234
│
├── 123
│   ├── 12
│   │   ├── 1
│   │   └── 2
│   └── 3
└── 4
```

The recursion reaches the most significant digit first and then prints
digits while returning from the recursive calls.

`INT_MIN` receives special handling because its positive magnitude
cannot be represented by a normal `int`.

### Unsigned Decimal

`ft_putnbr_unsigned()` uses the same recursive idea but works with
`unsigned int`.

This is important for `%u`, where the argument must be retrieved as:

``` c
va_arg(args, unsigned int)
```

### Hexadecimal

`ft_put_hex()` recursively divides by `16` and uses a supplied digit
table:

``` c
"0123456789abcdef"
```

or:

``` c
"0123456789ABCDEF"
```

This allows the same conversion function to support both `%x` and `%X`.

## Pointer Printing

`ft_print_pointer()` handles `%p`.

The current implementation:

1.  checks for `NULL`;
2.  prints `(nil)` for a null pointer;
3.  otherwise prints the `0x` prefix;
4.  converts the pointer value to hexadecimal.

## Building

The project uses a Makefile with:

``` bash
make
make clean
make fclean
make re
```

The compiler flags currently used are:

``` text
-Wall -Wextra -Werror
```

The library is built with `ar`.

> **Important:** the current Makefile names the library `ftprintf.a`.
> The 42/1337 project convention expects `libftprintf.a`, so this should
> be corrected before evaluation.

After correcting the name, a program can be linked with:

``` bash
cc main.c libftprintf.a
```

## Testing

A good `ft_printf` test should compare both:

1.  the printed output;
2.  the return value.

For example:

``` c
int ft_ret;
int printf_ret;

ft_ret = ft_printf("Number: %d\n", 42);
printf_ret = printf("Number: %d\n", 42);
```

The two return values should match for supported, defined inputs.

### Important test cases

#### Characters

``` c
ft_printf("%c\n", 'A');
```

#### Strings

``` c
ft_printf("%s\n", "Hello");
ft_printf("%s\n", "");
```

Also test the chosen behavior for:

``` c
ft_printf("%s\n", (char *)NULL);
```

#### Signed integers

``` c
ft_printf("%d\n", 0);
ft_printf("%d\n", 42);
ft_printf("%d\n", -42);
ft_printf("%d\n", INT_MAX);
ft_printf("%d\n", INT_MIN);
```

#### Unsigned integers

``` c
ft_printf("%u\n", 0u);
ft_printf("%u\n", UINT_MAX);
```

#### Hexadecimal

``` c
ft_printf("%x\n", 0u);
ft_printf("%x\n", 255u);
ft_printf("%X\n", 255u);
ft_printf("%x\n", UINT_MAX);
```

#### Pointers

``` c
int value = 42;

ft_printf("%p\n", &value);
ft_printf("%p\n", NULL);
```

#### Literal percent

``` c
ft_printf("100%%\n");
```

#### Return values

Every conversion should be checked against the return value of the
system `printf()` for the same defined input.

## Current Review Notes

The current code already has a good modular foundation, but before
considering the mandatory part complete, the following items should be
addressed:

### 1. `%i` is missing

The parser currently handles `%d` but not `%i`.

The mandatory set includes both `%d` and `%i`, even though both print
signed decimal integers.

The parser should dispatch `%i` to the same integer-printing logic as
`%d`.

### 2. Library name

The Makefile currently creates:

``` text
ftprintf.a
```

The expected project library name is:

``` text
libftprintf.a
```

### 3. `ft_putstr()` return type

The current header declares:

``` c
size_t ft_putstr(char *s);
```

while the main character-count accumulator is an `int`.

For a `printf`-style interface, keeping the helper return type as `int`
makes the character-counting contract simpler and avoids signed/unsigned
conversions.

### 4. `ft_putchar()` argument type

The current helper accepts:

``` c
int ft_putchar(char c);
```

while `%c` retrieves an `int` through `va_arg()`.

A cleaner interface is to let the helper receive an `int` and
convert/write the character internally. This also avoids
narrowing-conversion warnings under stricter compiler settings.

### 5. `%p` implementation

The current pointer implementation uses `unsigned long` for the
hexadecimal representation.

This works on the target 64-bit Linux environment, but the
representation is technically more portable when an integer type
explicitly intended to hold converted pointer values is used.

### 6. Parser organization

The parser is currently correct in spirit and already has a useful
architecture:

``` text
format string
      ↓
    parser
      ↓
conversion detection
      ↓
   va_arg()
      ↓
utility printer
```

As the bonus part is added, avoid turning the parser into a huge chain
of nested `if/else` statements. A small conversion-dispatch layer will
make flags, width, and precision much easier to add later.

### 7. Error/edge-case policy

Invalid conversions and malformed format strings are outside the normal
mandatory conversion set. They should not be allowed to silently
influence argument consumption.

The important requirement is that every supported conversion consumes
exactly the correct variadic argument type.

## Mandatory Completion Checklist

-   [x] `%c`
-   [x] `%s`
-   [x] `%p`
-   [x] `%d`
-   [x] `%i`
-   [x] `%u`
-   [x] `%x`
-   [x] `%X`
-   [x] `%%`
-   [x] Correct library name: `libftprintf.a`
-   [x] Full mandatory test suite
-   [ ] Norminette clean
-   [ ] Memory/UB checks
-   [ ] Return-value comparison against `printf`

## Bonus Roadmap

After the mandatory part is stable:

1.  Parse flags.
2.  Parse field width.
3.  Parse precision.
4.  Define a conversion-state structure.
5.  Implement `-` and `0`.
6.  Implement precision for numeric/string conversions.
7.  Implement `#`.
8.  Implement `+`.
9.  Implement space.
10. Test combinations such as:

``` text
%10d
%-10d
%010d
%.5d
%+d
% d
%#x
%#X
%-#10x
%+010d
```

Do not start the bonus until the mandatory conversion layer is reliable.

## What This Project Teaches

This implementation is intended to strengthen:

-   variadic functions
-   `va_list` / `va_arg`
-   format-string parsing
-   function decomposition
-   recursion
-   decimal and hexadecimal conversion
-   signed vs unsigned integers
-   pointer representation
-   return-value accounting
-   static library creation
-   Makefiles
-   C API design
-   edge-case testing

## Useful Commands

Build:

``` bash
make
```

Clean object files:

``` bash
make clean
```

Remove everything generated by the build:

``` bash
make fclean
```

Rebuild:

``` bash
make re
```

Compile a test program:

``` bash
cc -Wall -Wextra -Werror main.c libftprintf.a
```

Run:

``` bash
./a.out
```

## Project Context

**School:** 1337 Coding School\
**Curriculum:** 42 / 1337 Common Core\
**Language:** C\
**Project:** ft_printf

This repository is a learning project focused on understanding how
formatted output can be built from scratch rather than relying on the
standard `printf()` implementation.
