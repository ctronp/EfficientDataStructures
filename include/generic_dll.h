

#include <stdlib.h>
#include <string.h>

#define JOIN(x, y) x##y
#define TDL(T) JOIN(d_list_, T)
#define TDLN(T) JOIN(d_list_node_, T)
#define TDLNS(T) JOIN(d_list_node_struct_, T)

typedef struct TDLNS(T) {
  T value;
  struct TDLNS(T) * prev;
  struct TDLNS(T) * next;
} TDLN(T);

typedef struct {
  struct TDLNS(T) * values;
  struct TDLNS(T) * first;
  struct TDLNS(T) * last;
  size_t *lifo_free;
  size_t lifo_free_size;
  size_t lifo_free_capacity;
  size_t size;
  size_t capacity;
} TDL(T);

#define NEW_D_LIST_(T) JOIN(new_d_list_, T)
inline TDL(T) * NEW_D_LIST_(T)() { return calloc(1, sizeof(TDL(T))); }

#define NEW_D_LIST_WITH_CAPACITY_(T) JOIN(new_d_list_with_capacity_, T)
inline TDL(T) * NEW_D_LIST_WITH_CAPACITY_(T)(size_t capacity) {
  TDL(T) *to_return = malloc(sizeof(TL(T)));
  to_return->values = malloc(sizeof(TDL(T)) * capacity);
  to_return->size = 0;
  to_return->capacity = capacity;
  to_return->first = 0;
  to_return->last = 0;
  return to_return;
}

#define INIT_D_LIST_(T) JOIN(init_d_list, T)
inline void INIT_D_LIST_(T)(TDL(T) * list) { *list = (TDL(T)){}; }

#define DEL_D_LIST_(T) JOIN(del_d_list_, T)
inline void DEL_D_LIST_(T)(TDL(T) * list) {
  if (list->capacity) {
    free(list->values);
  }
  if (list->lifo_free_capacity) {
    free(list->lifo_free);
  }
}

#define APPEND_LEFT_D_LIST_(T) JOIN(append_left_d_list_, T)
inline void APPEND_LEFT_D_LIST_(T)(TDL(T) * list, T value) {
  // TODO
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TDLN(T)));
    list->first = list->values;
    list->last = list->values;
    list->values[0] = (TDLN(T)){.value = value, .prev = NULL, .next = NULL};
  }

  size_t pos;
  if (list->lifo_free_size) {
    pos = --list->lifo_free_size;
    list->size++;
    list->values[pos].value = value;
  } else if (list->size == list->capacity) {
    pos = list->size++;
    list->capacity <<= 1;
    list->values = realloc(list->values, sizeof(TDLN(T)) * list->capacity);
    list->values[pos].value = value;
  } else {
    pos = list->size++;
    list->values[pos].value = value;
  }

  TDLN(T) *const loc = &list->values[pos];

  loc->prev = NULL;
  loc->next = list->first;
  list->first->prev = loc;
  list->first = loc;
}

#define APPEND_RIGHT_D_LIST_(T) JOIN(append_right_d_list_, T)
inline void APPEND_RIGHT_D_LIST_(T)(TDL(T) * list, T value) {
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TLN(T)));
    list->first = list->values;
    list->last = list->values;
    list->values[0] = (TDLN(T)){.value = value, .prev = NULL, .next = NULL};
  }

  size_t pos;
  if (list->lifo_free_size) {
    pos = --list->lifo_free_size;
    list->size++;
    list->values[pos].value = value;
  } else if (list->size == list->capacity) {
    pos = list->size++;
    list->capacity <<= 1;
    list->values = realloc(list->values, sizeof(TLN(T)) * list->capacity);
    list->values[pos].value = value;
  } else {
    pos = list->size++;
    list->values[pos].value = value;
  }

  TDLN(T) *const loc = &list->values[pos];

  loc->prev = list->last;
  loc->next = NULL;
  list->last->next = loc;
  list->last = loc;
}

#define CLEAN_D_LIST_(T) JOIN(clean_d_list_, T)
inline void CLEAN_D_LIST_(T)(TDL(T) * list) {
  list->size = 0;
  list->lifo_free_size = 0;
}

#define FIT_D_LIST_(T) JOIN(fit_d_list_, T)
inline void FIT_D_LIST_(T)(TDL(T) * list) {
  // O(n) complexity, so only lifo_free will be fit (O(1))
  list->lifo_free_capacity = list->lifo_free_size;
  list->lifo_free =
      realloc(list->lifo_free, sizeof(TLN(T) *) * list->lifo_free_size);
}

#define POP_LEFT_D_LIST_(T) JOIN(pop_left_d_list_, T)
inline T POP_LEFT_D_LIST_(T)(TDL(T) * list) {
  const T value = list->first->value;
  const size_t pos = list->first - list->values;
  list->first = list->first->next;
  list->first->prev = NULL;
  if (list->lifo_free_size == list->lifo_free_capacity) {
    list->lifo_free_capacity <<= 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  }
  list->lifo_free[list->lifo_free_size++] = pos;
  return value;
}

#define POP_RIGHT_D_LIST_(T) JOIN(pop_right_d_list_, T)
inline T POP_RIGHT_D_LIST_(T)(TDL(T) * list) {
  const T value = list->last->value;
  const size_t pos = list->last - list->values;
  list->last = list->last->prev;
  list->last->next = NULL;
  if (list->lifo_free_size == list->lifo_free_capacity) {
    list->lifo_free_capacity <<= 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  }
  list->lifo_free[list->lifo_free_size++] = pos;
  return value;
}