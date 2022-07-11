#define T int
#include "include/generic_vector.h"
#undef T

#define T unsigned
#include "include/generic_vector.h"
#undef T

#define T int
#include "include/generic_ll.h"
#undef T

#define T unsigned
#include "include/generic_ll.h"
#undef T

#define T int
#include "include/generic_fifo.h"
#undef T

#define T unsigned
#include "include/generic_fifo.h"
#undef T

size_t test_hash(int i) { return (size_t)i; }

#define T int
#define HASH_F test_hash
#include "include/generic_set.h"
#undef T
#undef HASH_F

size_t test_hash2(int i) { return (size_t)i; }

#define T unsigned
#define HASH_F test_hash2
#include "include/generic_set.h"
#undef T



#include <stdio.h>

#define REP(var, init, end)                                                    \
  for (int(var) = (int)(init); (var) != (end); (var)++)

int main() {
  fifo_int *fifo = new_fifo_int();
  del_fifo_int(fifo);
  free(fifo);
  return 0;
}
