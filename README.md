# NTlang Command Line Interpreter

## Introduction
The NTlang Command Line Interpreter is a versatile tool designed to interpret NTlang expressions for working with different number bases and bit widths. This interpreter is particularly useful for developers who need to perform number conversions and bit twiddling operations frequently.

## Building the Project
To build the interpreter, follow these steps:

1. Clone the repository:
    ```bash
    git clone [repository]
    ```
2. Navigate to the project directory:
    ```bash
    cd [project-directory]
    ```

3. Compile the source code:
    ```bash
    gcc -o ntlang main.c
    ```
## Running the Program
Run the interpreter from the command line by passing an expression, a number base, and a width. The output will be printed to stdout.

Examples:
```bash
./ntlang -e "1 + 1"
./ntlang -e "10" -b 16
./ntlang -e "10 + 1" -b 16 -w 16
```
## Command-Line Interface
The interpreter accepts the following command-line arguments:

* ```-e```: The NTlang expression to interpret.

* ```-b```: The number base for the output (valid inputs: 2, 10, 16).

* ```-w```: The bit width of the output (valid inputs: 4, 8, 16, 32).

* ```-u```: Print unsigned integers (only applicable for base 10).

```bash
Examples
$ ./ntlang -e "1 + 1"
2
$ ./ntlang -e "10" -b 16
0x0000000A
$ ./ntlang -e "10 + 1" -b 16 -w 16
0x000A
```

## Scanner and Parser
The scanner reads the command-line expression and creates a token data structure. The parser then generates an Abstract Syntax Tree (AST) from these tokens, representing valid NTlang programs.

## Bitwise Operations and Base Conversions
The interpreter supports various bitwise operations and base conversions as defined in the EBNF grammar provided.