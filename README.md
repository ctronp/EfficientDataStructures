# Efficient Data Structures

This repository includes simple and easy to use data structures, the objective of these is to reduce the number of system calls to request memory, similar to how C++ containers are made.

All structures are contained in the form of macros as single headers.

## Usage

Copy the header to the project in which it will be used. include previously assigning the macro with the name of the structure to use.

Example:

```C
#define T int
#include "include/generic_fifo.h"
#undef T

int main() {
  fifo_int *fifo = new_fifo_int();
  del_fifo_int(fifo);
  free(fifo);
  return 0;
}
```

After including the header, the functions and structures will be created, these with named in sanke_case.

## Unnecessary files

All files in the root folder are only used to test the correct functioning of the data structures, they are not required in any way for the use of these, and due to the license ([MIT](https://choosealicense.com/licenses/mit/)) you are allowed to delete and/or modify all files in this repository.