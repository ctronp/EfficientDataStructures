#define T int
#include "../src/generic_vector.h"
#undef T

#include <stdio.h>

int main() {
  vector_int *vec = new_vector_int();

  del_vector_int(vec);
  free(vec);
}