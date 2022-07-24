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

TEST("various_append", "test appending multiple times") {
  list_int *l = new_list_int();
  ASSERT_NE_PTR(NULL, l);
  for (int i = 0; i < 1000; i++) {
    append_left_list_int(l, i);
  }

  for (int i = 999; i >= 0; i--) {
    ASSERT_EQ_INT(i, pop_left_list_int(l))
  }

  del_list_int(l);
  free(l);
}

TEST("2 lists", "test appending and popping from 2 lists") {
  list_int *l1 = new_list_int();
  list_int *l2 = new_list_int();
  ASSERT_NE_PTR(NULL, l1);
  ASSERT_NE_PTR(NULL, l2);
  for (int i = 0; i < 1000; i++) {
    append_left_list_int(l1, i);
  }
  for (int i = 0; i < 1000; i++) {
    append_left_list_int(l2, i);
  }

  for (int i = 999; i >= 0; i--) {
    ASSERT_EQ_INT(pop_left_list_int(l2), pop_left_list_int(l1))
  }

  del_list_int(l1);
  del_list_int(l2);
  free(l1);
  free(l2);
}

END_TESTING