#define T int
#include "../../src/ll.h"
#undef T


int main() {
  list_int *list = new_list_int();

  del_list_int(list);
  free(list);
}