#define T int
#include "../../src/fifo.h"
#undef T

#include "../MCT/MCT.h"

START_TESTING(NULL) { printf("start testing Linked Lists\n"); }

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

TEST("2 lists", "test appending and popping from 2 lists") {
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

  for (int i = 0; i <1000 ; i++) {
    ASSERT_EQ_INT(pop_left_fifo_int(l2), pop_left_fifo_int(l1))
  }

  del_fifo_int(l1);
  del_fifo_int(l2);
  free(l1);
  free(l2);
}

TEST("with capacity", "test appending and popping from a list with capacity") {
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
//
//TEST("init list", "test initializing a list") {
//  list_int ll, *l1 = &ll;
//  list_int *l2 = new_list_with_capacity_int(1000);
//
//  ASSERT_NE_PTR(NULL, l1)
//  ASSERT_NE_PTR(NULL, l2)
//
//  init_list_int(l1);
//
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l1, i);
//  }
//
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l2, i);
//  }
//
//  for (int i = 999; i >= 0; i--) {
//    int t1 = pop_left_list_int(l1);
//    ASSERT_EQ_INT(t1, pop_left_list_int(l2))
//    ASSERT_EQ_INT(i, t1)
//  }
//
//  del_list_int(l1);
//  del_list_int(l2);
//  free(l2);
//}
//
//TEST("clean list", "test cleaning a list") {
//  list_int *l1 = new_list_int();
//  list_int *l2 = new_list_int();
//  ASSERT_NE_PTR(NULL, l1);
//  ASSERT_NE_PTR(NULL, l2);
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l1, i);
//  }
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l2, i);
//  }
//
//  clean_list_int(l1);
//  clean_list_int(l2);
//  ASSERT_EQ_UNS(0, l1->size)
//  ASSERT_EQ_UNS(0, l2->size)
//
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l1, i);
//  }
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l2, i);
//  }
//
//  for (int i = 0; i < 1000; i++) {
//    ASSERT_EQ_INT(pop_left_list_int(l1), pop_left_list_int(l2))
//  }
//
//  del_list_int(l1);
//  del_list_int(l2);
//  free(l1);
//  free(l2);
//}
//
//TEST("fit list", "test fitting a list") {
//  list_int *l1 = new_list_int();
//  list_int *l2 = new_list_int();
//  ASSERT_NE_PTR(NULL, l1);
//  ASSERT_NE_PTR(NULL, l2);
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l1, i);
//  }
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l2, i);
//  }
//
//  fit_list_int(l1);
//  fit_list_int(l2);
//  ASSERT_EQ_UNS(1000, l1->size)
//  ASSERT_EQ_UNS(1000, l2->size)
//  ASSERT_EQ_UNS(l1->lifo_free_capacity, 0)
//  ASSERT_EQ_UNS(l2->lifo_free_capacity, 0)
//
//  for (int i = 0; i < 1000; i++) {
//    ASSERT_EQ_INT(pop_left_list_int(l1), pop_left_list_int(l2))
//  }
//
//  fit_list_int(l1);
//  fit_list_int(l2);
//  ASSERT_EQ_UNS(0, l1->size)
//  ASSERT_EQ_UNS(0, l2->size)
//
//  del_list_int(l1);
//  del_list_int(l2);
//  free(l1);
//  free(l2);
//}
//
//TEST("pop with index", "test popping from a list with index") {
//  list_int *l1 = new_list_int();
//  list_int *l2 = new_list_int();
//  ASSERT_NE_PTR(NULL, l1);
//  ASSERT_NE_PTR(NULL, l2);
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l1, i);
//  }
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l2, i);
//  }
//
//  for (int i = 0; i < 1000; i++) {
//    ASSERT_EQ_INT(i, pop_with_index_int(l1, 999 - i))
//  }
//
//  for (int i = 0; i < 1000; i++) {
//    ASSERT_EQ_INT(999 - i, pop_with_index_int(l2, 0))
//  }
//
//  del_list_int(l1);
//  del_list_int(l2);
//  free(l1);
//  free(l2);
//}
//
//TEST("pop with pos", "test popping from a list with pos") {
//  list_int *l1 = new_list_int();
//  list_int *l2 = new_list_int();
//  ASSERT_NE_PTR(NULL, l1);
//  ASSERT_NE_PTR(NULL, l2);
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l1, i);
//  }
//  for (int i = 0; i < 1000; i++) {
//    append_left_list_int(l2, i);
//  }
//
//  for (int i = 0; i < 1000; i++) {
//    ASSERT_EQ_INT(999 - i, pop_with_pos_int(l1, 999 - i))
//  }
//
//  for (int i = 0; i < 1000; i++) {
//    ASSERT_EQ_INT(i, pop_with_pos_int(l2, i))
//  }
//
//  del_list_int(l1);
//  del_list_int(l2);
//  free(l1);
//  free(l2);
//}

END_TESTING