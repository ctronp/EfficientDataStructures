#define T int
#include "../../src/vector.h"
#undef T

#include "../MCT/MCT.h"

START_TESTING(NULL) { printf("start testing Linked vectors\n"); }

TEST("create_delete", "create and delete a vector") {
  vector_int *l = new_vector_int();
  ASSERT(l != NULL);
  append_vector_int(l, 1);
  append_vector_int(l, 2);
  append_vector_int(l, 3);
  ASSERT_EQ_UNS(3, l->size)

  del_vector_int(l);
  free(l);
}

TEST("various_append", "test appending multiple times") {
  vector_int *l = new_vector_int();
  ASSERT_NE_PTR(NULL, l);
  for (int i = 0; i < 1000; i++) {
    append_vector_int(l, i);
  }

  for (int i = 999; i >= 0; i--) {
    ASSERT_EQ_INT(i, pop_vec_int(l))
  }

  del_vector_int(l);
  free(l);
}

TEST("2 vectors", "test appending and popping from 2 vectors") {
  vector_int *l1 = new_vector_int();
  vector_int *l2 = new_vector_int();
  ASSERT_NE_PTR(NULL, l1);
  ASSERT_NE_PTR(NULL, l2);
  for (int i = 0; i < 1000; i++) {
    append_vector_int(l1, i);
  }
  for (int i = 0; i < 1000; i++) {
    append_vector_int(l2, i);
  }

  for (int i = 999; i >= 0; i--) {
    ASSERT_EQ_INT(pop_vec_int(l2), pop_vec_int(l1))
  }

  del_vector_int(l1);
  del_vector_int(l2);
  free(l1);
  free(l2);
}

END_TESTING