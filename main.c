#define T int
#include "src/generic_vector.h"
#undef T

#define T unsigned
#include "src/generic_vector.h"
#undef T

#define T int
#include "src/generic_ll.h"
#undef T

#define T unsigned
#include "src/generic_ll.h"
#undef T

#define T int
#include "src/generic_dll.h"
#undef T

#define T unsigned
#include "src/generic_dll.h"
#undef T

#define T int
#include "src/generic_fifo.h"
#undef T

#define T unsigned
#include "src/generic_fifo.h"
#undef T

size_t test_hash(int i) { return (size_t)i; }

#define T int
#define HASH_F test_hash
#include "src/generic_set.h"
#undef T
#undef HASH_F

size_t test_hash2(int i) { return (size_t)i; }

#define T unsigned
#define HASH_F test_hash2
#include "src/generic_set.h"
#undef T

#include <stdio.h>

int main() {
  fifo_int *fifo = new_fifo_int();
  del_fifo_int(fifo);
  free(fifo);
  return 0;
}
