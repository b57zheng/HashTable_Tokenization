
---

#  HashTable Tokenizer

## Overview
The HashTable Tokenizer is a C++ implemented hash table designed for efficient tokenization. This project provides a solution to convert text into numeric tokens and vice versa, facilitating the intermediate processing of large language modele. The implementation uses a custom hash function with separate chaining to resolve collisions, optimized for quick retrieval and insertion of token-word pairs.

## Features
- **Custom Hashing**: Implements a unique hashing function for distributing words efficiently across the hash table.
- **Separate Chaining**: Utilizes separate chaining to handle collisions, ensuring fast access even with hash conflicts.
- **No STL Libraries**: Developed without the use of Standard Template Library (STL) to meet project constraints.
- **Efficient Tokenization**: Supports operations to tokenize text to numeric tokens and retrieve text from tokens.
- **Memory Management**: Careful handling of memory allocation and deallocation to prevent leaks and ensure optimal performance.

## Getting Started

### Prerequisites
Ensure you have a C++ compiler installed on your system (GCC recommended). This project does not require any external libraries.

### Compilation
To compile the project, navigate to the project directory and use the provided Makefile:
```bash
make
```

### Running
After compilation, you can run the program using:
```bash
./a.out < input_file
```
Where `input_file` is a file containing a sequence of commands as described in the "Commands" section.

### Commands
This project accepts the following commands:
- `M m`: Initializes a new hash table with size `m`.
- `INSERT word`: Inserts a word into the tokenizer.
- `READ filename`: Reads words from a specified file.
- `TOKENIZE word`: Returns the token associated with the word.
- `RETRIEVE t`: Retrieves the word associated with token `t`.
- `STOK string_of_words`: Tokenizes a string of words.
- `TOKS string_of_tokens`: Turns a string of tokens back into words.
- `PRINT k`: Prints the keys stored at position `k` in the hash table.

### Input/Output
The input files should end with the string "EXIT", which will terminate the program. The output for each command is either a success or failure message, a token, a word, or a series of tokens or words depending on the command.

## Documentation
For a detailed explanation of the program's design and implementation, refer to the design document included in the repository.

## Testing
To test the project with Valgrind for memory leaks:
```bash
valgrind ./a.out < test01.in
```
Replace `test01.in` with your test input file.

---
