// if possible prefer vector (stack) or fifo
// they have less overhead.
//
// if you need to remove from both ends prefer Doubly Linked List

#include <stdlib.h>
#include <string.h>

#define NONE (((size_t)(0)) - 1)

#define JOIN(x, y) x##y
#define TL(T) JOIN(list_, T)
#define TLN(T) JOIN(list_node_, T)
#define TLNS(T) JOIN(list_node_struct_, T)

typedef struct TLNS(T) {
  T value;
  size_t next;
} TLN(T);

typedef struct {
  struct TLNS(T) * values;
  size_t first;
  size_t *lifo_free;
  size_t lifo_free_size;
  size_t lifo_free_capacity;
  size_t size;
  size_t capacity;
} TL(T);

#define NEW_LIST_(T) JOIN(new_list_, T)
TL(T) * NEW_LIST_(T)() {
  TL(T) *const to_return = malloc(sizeof(TL(T)));
  *to_return = (TL(T)){.values = NULL,
                       .first = NONE,
                       .lifo_free = NULL,
                       .lifo_free_size = 0,
                       .lifo_free_capacity = 0,
                       .size = 0,
                       .capacity = 0};
  return to_return;
}

#define NEW_LIST_WITH_CAPACITY_(T) JOIN(new_list_with_capacity_, T)
TL(T) * NEW_LIST_WITH_CAPACITY_(T)(size_t capacity) {
  TL(T) *const to_return = malloc(sizeof(TL(T)));
  *to_return = (TL(T)){.values = malloc(sizeof(TLN(T)) * capacity),
                       .first = NONE,
                       .lifo_free = NULL,
                       .lifo_free_size = 0,
                       .lifo_free_capacity = 0,
                       .size = 0,
                       .capacity = capacity};
  return to_return;
}

#define INIT_LIST_(T) JOIN(init_list, T)
void INIT_LIST_(T)(TL(T) *const list) {
  *list = (TL(T)){.values = NULL,
                  .first = NONE,
                  .lifo_free = NULL,
                  .lifo_free_size = 0,
                  .lifo_free_capacity = 0,
                  .size = 0,
                  .capacity = 0};
}

#define DEL_LIST_(T) JOIN(del_list_, T)
void DEL_LIST_(T)(TL(T) * list) {
  if (list->capacity) {
    free(list->values);
  }
  if (list->lifo_free_capacity) {
    free(list->lifo_free);
  }
}

#define APPEND_LEFT_LIST_(T) JOIN(append_left_list_, T)
void APPEND_LEFT_LIST_(T)(TL(T) * list, T value) {
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TLN(T)));
    list->first = 0;
    list->values[0] = (TLN(T)){.value = value, .next = NONE};
    return;
  }

  size_t pos;
  if (list->lifo_free_size) {
    pos = --list->lifo_free_size;
    list->size++;
  } else if (list->size == list->capacity) {
    pos = list->size++;
    list->capacity <<= 1;
    list->values = realloc(list->values, sizeof(TLN(T)) * list->capacity);
  } else {
    pos = list->size++;
  }

  list->values[pos].value = value;
  list->values[pos].next = list->first;
  list->first = pos;
}

#define CLEAN_LIST_(T) JOIN(clean_list_, T)
void CLEAN_LIST_(T)(TL(T) * list) {
  list->size = 0;
  list->lifo_free_size = 0;
}

#define FIT_LIST_(T) JOIN(fit_list_, T)
void FIT_LIST_(T)(TL(T) * list) {
  // O(n) complexity, so only lifo_free will be fit (O(1))
  list->lifo_free_capacity = list->lifo_free_size;
  list->lifo_free =
      realloc(list->lifo_free, sizeof(TLN(T) *) * list->lifo_free_size);
}

#define POP_LEFT_LIST_(T) JOIN(pop_left_list_, T)
T POP_LEFT_LIST_(T)(TL(T) * list) {
  const size_t first_pos = list->first;
  list->first = list->values[first_pos].next;
  list->size--;

  if (list->lifo_free_capacity == 0) {
    list->lifo_free_capacity = 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  } else if (list->lifo_free_size == list->lifo_free_capacity) {
    list->lifo_free_capacity <<= 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  }
  list->lifo_free[list->lifo_free_size++] = first_pos;

  return list->values[first_pos].value;
}