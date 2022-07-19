#define T int
#include "../../src/ll.h"
#undef T

#include "../MCT/MCT.h"

START_TESTING(NULL) { printf("start testing Linked Lists\n"); }

TEST("create_delete", "create and delete a list") {
  list_int *l = new_list_int();
  ASSERT(l != NULL);
  append_left_list_int(l, 1);
  append_left_list_int(l, 2);
  append_left_list_int(l, 3);
  ASSERT_EQ_UNS(3, l->size)

  del_list_int(l);
  free(l);
}

END_TESTING