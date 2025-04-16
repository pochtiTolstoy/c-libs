# C Utilities Collection

A repository containing modular C implementations of common utilities and data structures, each with unit tests and code coverage reporting.

## Included Programs

1. **decimal**  
   - High-precision decimal arithmetic library.
2. **grep**  
   - Custom implementation of text pattern searching (subset of GNU grep functionality).
3. **cat**  
   - File concatenation and display utility.
4. **string**  
   - Safe string manipulation library with bounds checking.
5. **matrix**  
   - Matrix operations library (addition, multiplication, transposition).
6. **avl-tree**  
   - Self-balancing binary search tree implementation

## Prerequisites

- GCC (GNU Compiler Collection)
- GNU Make
- gcov/lcov (for coverage reporting)
- Check (unit testing framework)

## Building

```bash
# Build program
make all

# Run unit tests
make tests

# Clean build artifacts
make clean
