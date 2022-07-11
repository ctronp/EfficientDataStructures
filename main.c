#define T int
#include "include/generic_vector.h"
#undef T

#define T unsigned
#include "include/generic_vector.h"
#undef T

#define T int
#include "include/generic_fifo.h"
#undef T

#define T unsigned
#include "include/generic_fifo.h"
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
