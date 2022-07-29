

#include <stdlib.h>
#include <string.h>

#define NONE (((size_t)(0)) - 1)

#define JOIN(x, y) x##y
#define TDL(T) JOIN(d_list_, T)
#define TDLN(T) JOIN(d_list_node_, T)

typedef struct {
  T value;
  size_t prev;
  size_t next;
} TDLN(T);

typedef struct {
  TDLN(T) * values;
  size_t first;
  size_t last;
  size_t *lifo_free;
  size_t lifo_free_size;
  size_t lifo_free_capacity;
  size_t size;
  size_t capacity;
} TDL(T);

#define NEW_D_LIST_(T) JOIN(new_d_list_, T)

TDL(T) * NEW_D_LIST_(T)() {
  TDL(T) *const to_return = malloc(sizeof(TDL(T)));
  *to_return = (TDL(T)){.values = NULL,
                        .first = NONE,
                        .last = NONE,
                        .lifo_free = NULL,
                        .lifo_free_size = 0,
                        .lifo_free_capacity = 0,
                        .size = 0,
                        .capacity = 0};
  return to_return;
}

#define NEW_D_LIST_WITH_CAPACITY_(T) JOIN(new_d_list_with_capacity_, T)

TDL(T) * NEW_D_LIST_WITH_CAPACITY_(T)(size_t capacity) {
  TDL(T) *to_return = malloc(sizeof(TDL(T)));
  *to_return = (TDL(T)){.values = malloc(sizeof(TDLN(T)) * capacity),
                        .first = NONE,
                        .last = NONE,
                        .lifo_free = NULL,
                        .lifo_free_size = 0,
                        .lifo_free_capacity = 0,
                        .size = 0,
                        .capacity = capacity};
  return to_return;
}

#define INIT_D_LIST_(T) JOIN(init_d_list, T)

void INIT_D_LIST_(T)(TDL(T) * list) {
  *list = (TDL(T)){.values = NULL,
                   .first = NONE,
                   .last = NONE,
                   .lifo_free = NULL,
                   .lifo_free_size = 0,
                   .lifo_free_capacity = 0,
                   .size = 0,
                   .capacity = 0};
}

#define DEL_D_LIST_(T) JOIN(del_d_list_, T)

void DEL_D_LIST_(T)(TDL(T) * list) {
  if (list->capacity) {
    free(list->values);
  }
  if (list->lifo_free_capacity) {
    free(list->lifo_free);
  }
}

#define APPEND_LEFT_D_LIST_(T) JOIN(append_left_d_list_, T)

void APPEND_LEFT_D_LIST_(T)(TDL(T) *const list, T value) {
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TDLN(T)));
    list->first = 0;
    list->last = 0;
    list->values[0] = (TDLN(T)){.value = value, .prev = NONE, .next = NONE};
    return;
  }

  size_t pos;
  if (list->lifo_free_size) {
    pos = --list->lifo_free_size;
    list->size++;
  } else if (list->size == list->capacity) {
    pos = list->size++;
    list->capacity <<= 1;
    list->values = realloc(list->values, sizeof(TDLN(T)) * list->capacity);
  } else {
    pos = list->size++;
  }

  list->values[pos] = (TDLN(T)){
      .value = value,
      .prev = NONE,
      .next = list->first,
  };
  list->first = pos;

  if (list->last == NONE) {
    list->last = pos;
  }
}

#define APPEND_RIGHT_D_LIST_(T) JOIN(append_right_d_list_, T)

void APPEND_RIGHT_D_LIST_(T)(TDL(T) * list, T value) {
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TDLN(T)));
    list->first = 0;
    list->last = 0;
    list->values[0] = (TDLN(T)){.value = value, .prev = NONE, .next = NONE};
    return;
  }

  size_t pos;
  if (list->lifo_free_size) {
    pos = --list->lifo_free_size;
    list->size++;
  } else if (list->size == list->capacity) {
    pos = list->size++;
    list->capacity <<= 1;
    list->values = realloc(list->values, sizeof(TDLN(T)) * list->capacity);
  } else {
    pos = list->size++;
  }

  list->values[pos] = (TDLN(T)){
      .value = value,
      .prev = list->last,
      .next = NONE,
  };
  list->last = pos;

  if (list->first == NONE) {
    list->first = pos;
  }
}

#define CLEAN_D_LIST_(T) JOIN(clean_d_list_, T)

void CLEAN_D_LIST_(T)(TDL(T) * list) {
  list->size = 0;
  list->lifo_free_size = 0;
}

#define FIT_D_LIST_(T) JOIN(fit_d_list_, T)

void FIT_D_LIST_(T)(TDL(T) * list) {
  // O(n) complexity, so only lifo_free will be fit (O(1))
  list->lifo_free_capacity = list->lifo_free_size;
  list->lifo_free =
      realloc(list->lifo_free, sizeof(TDLN(T) *) * list->lifo_free_size);
}

#define POP_LEFT_D_LIST_(T) JOIN(pop_left_d_list_, T)

T POP_LEFT_D_LIST_(T)(TDL(T) * list) {
  const size_t pos = list->first;
  const T value = list->values[pos].value;

  list->first = list->values[pos].next;
  if (list->first == NONE) {
    list->last = NONE;
    list->size = 0;
    list->lifo_free_size = 0;
    return value;
  }

  const size_t first_pos = list->first;
  list->values[first_pos].prev = NONE;

  if (list->lifo_free_size == list->lifo_free_capacity) {
    list->lifo_free_capacity <<= 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  }
  list->lifo_free[list->lifo_free_size++] = pos;
  return value;
}

#define POP_RIGHT_D_LIST_(T) JOIN(pop_right_d_list_, T)

T POP_RIGHT_D_LIST_(T)(TDL(T) * list) {
  const size_t pos = list->last;
  const T value = list->values[pos].value;

  list->last = list->values[pos].prev;
  if (list->last == NONE) {
    list->first = NONE;
    list->size = 0;
    list->lifo_free_size = 0;
    return value;
  }

  const size_t last_pos = list->last;
  list->values[last_pos].next = NONE;

  if (list->lifo_free_size == list->lifo_free_capacity) {
    list->lifo_free_capacity <<= 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  }
  list->lifo_free[list->lifo_free_size++] = pos;
  return value;
}