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


The program can be linked with:

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
