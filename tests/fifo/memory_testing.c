#define T int
#include "../../src/fifo.h"
#undef T

#include "../MCT/MCT.h"

START_TESTING(NULL) { printf("start testing FIFO\n"); }

TEST("create_delete", "create and delete a fifo") {
  fifo_int *f = new_fifo_int();
  ASSERT(f != NULL);
  append_fifo_int(f, 1);
  append_fifo_int(f, 2);
  append_fifo_int(f, 3);
  ASSERT_EQ_UNS(3, f->size)

  del_fifo_int(f);
  free(f);
}

TEST("various_append", "test appending multiple times") {
  fifo_int *l = new_fifo_int();
  ASSERT_NE_PTR(NULL, l);
  for (int i = 0; i < 1000; i++) {
    append_fifo_int(l, i);
  }

  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ_INT(i, pop_left_fifo_int(l))
  }

  del_fifo_int(l);
  free(l);
}

TEST("2 lists", "test appending and popping from 2 fifo") {
  fifo_int *l1 = new_fifo_int();
  fifo_int *l2 = new_fifo_int();
  ASSERT_NE_PTR(NULL, l1);
  ASSERT_NE_PTR(NULL, l2);
  for (int i = 0; i < 1000; i++) {
    append_fifo_int(l1, i);
  }
  for (int i = 0; i < 1000; i++) {
    append_fifo_int(l2, i);
  }

  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ_INT(pop_left_fifo_int(l2), pop_left_fifo_int(l1))
  }

  del_fifo_int(l1);
  del_fifo_int(l2);
  free(l1);
  free(l2);
}

TEST("with capacity", "test appending and popping from a fifo with capacity") {
  fifo_int *l1 = new_fifo_with_capacity_int(1000);
  fifo_int *l2 = new_fifo_with_capacity_int(1000);

  ASSERT_NE_PTR(NULL, l1)
  ASSERT_NE_PTR(NULL, l2)

  for (int i = 0; i < 1000; i++) {
    append_fifo_int(l1, i);
  }

  for (int i = 0; i < 1000; i++) {
    append_fifo_int(l2, i);
  }

  for (int i = 0; i < 1000; i++) {
    int t1 = pop_left_fifo_int(l1);
    ASSERT_EQ_INT(t1, pop_left_fifo_int(l2))
    ASSERT_EQ_INT(i, t1)
  }

  del_fifo_int(l1);
  del_fifo_int(l2);
  free(l1);
  free(l2);
}

TEST("init list", "test initializing a list") {
  fifo_int fifo, *f1 = &fifo;
  fifo_int *f2 = new_fifo_with_capacity_int(1000);

  ASSERT_NE_PTR(NULL, f1)
  ASSERT_NE_PTR(NULL, f2)

  init_fifo_int(f1);

  for (int i = 0; i < 1000; i++) {
    append_fifo_int(f1, i);
  }

  for (int i = 0; i < 1000; i++) {
    append_fifo_int(f2, i);
  }

  for (int i = 0; i < 1000; i++) {
    int t1 = pop_left_fifo_int(f1);
    ASSERT_EQ_INT(t1, pop_left_fifo_int(f2))
    ASSERT_EQ_INT(i, t1)
  }

  del_fifo_int(f1);
  del_fifo_int(f2);
  free(f2);
}

TEST("clean list", "test cleaning a list") {
  fifo_int *f1 = new_fifo_int();
  fifo_int *f2 = new_fifo_int();
  ASSERT_NE_PTR(NULL, f1);
  ASSERT_NE_PTR(NULL, f2);
  for (int i = 0; i < 1000; i++) {
    append_fifo_int(f1, i);
  }
  for (int i = 0; i < 1000; i++) {
    append_fifo_int(f2, i);
  }

  clean_fifo_int(f1);
  clean_fifo_int(f2);
  ASSERT_EQ_UNS(0, f1->size)
  ASSERT_EQ_UNS(0, f2->size)

  for (int i = 0; i < 1000; i++) {
    append_fifo_int(f1, i);
  }
  for (int i = 0; i < 1000; i++) {
    append_fifo_int(f2, i);
  }

  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ_INT(pop_left_fifo_int(f1), pop_left_fifo_int(f2))
  }

  del_fifo_int(f1);
  del_fifo_int(f2);
  free(f1);
  free(f2);
}

END_TESTING