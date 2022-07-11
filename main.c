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

//  printf("tamanno=%zu\n", fifo->size);
//  printf("capacidad=%zu\n", fifo->c1 + fifo->c2);
//
//  REP(i, 0, 10) { append_fifo_int(fifo, i); }
//
//  printf("tamanno=%zu\n", fifo->size);
//  printf("capacidad=%zu\n", fifo->c1 + fifo->c2);
//
//  REP(i, 0, 10) { printf("value %d: %d\n", i, pop_left_fifo_int(fifo)); }
//
//  REP(i, 0, 10) { append_fifo_int(fifo, i); }
//
//  printf("tamanno=%zu\n", fifo->size);
//  printf("capacidad=%zu\n", fifo->c1 + fifo->c2);
//
//  REP(i, 0, 10) { printf("value %d: %d\n", i, pop_right_fifo_int(fifo)); }
//
//  del_fifo_int(fifo);
//  free(fifo);
//  return 0;
//}
