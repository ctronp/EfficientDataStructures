#include <stdlib.h>
#include <string.h>

#define JOIN(x, y) x##y
#define TL(T) JOIN(list_, T)
#define TLN(T) JOIN(list_node_, T)
#define TLNS(T) JOIN(list_node_struct_, T)

typedef struct TLNS(T) {
  T value;
  struct TLNS(T) * next;
} TLN(T);

typedef struct {
  struct TLNS(T) * values;
  TLN(T) * first;
  TLN(T) * last;
  size_t *lifo_free;
  size_t lifo_free_size;
  size_t lifo_free_capacity;
  size_t size;
  size_t capacity;
} TL(T);

#define NEW_LIST_(T) JOIN(new_list_, T)
inline TL(T) * NEW_LIST_(T)() { return calloc(1, sizeof(TL(T))); }

#define NEW_LIST_WITH_CAPACITY_(T) JOIN(new_list_with_capacity_, T)
inline TL(T) * NEW_LIST_WITH_CAPACITY_(T)(size_t capacity) {
  TL(T) *to_return = malloc(sizeof(TL(T)));
  to_return->values = malloc(sizeof(T) * capacity);
  to_return->size = 0;
  to_return->capacity = capacity;
  to_return->first = 0;
  to_return->last = 0;
  return to_return;
}

#define INIT_LIST_(T) JOIN(init_list, T)
inline void INIT_LIST_(T)(TL(T) * list) { *list = (TL(T)){}; }

#define DEL_LIST_(T) JOIN(del_list_, T)
inline void DEL_LIST_(T)(TL(T) * list) {
  if (list->capacity) {
    free(list->values);
  }
  if (list->lifo_free_capacity) {
    free(list->lifo_free);
  }
}

#define APPEND_LEFT_LIST_(T) JOIN(append_left_list_, T)
inline void APPEND_LEFT_LIST_(T)(TL(T) * list, T value) {
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TLN(T)));
    list->first = list->values;
    list->last = list->values;
    list->values[0] = (TLN(T)){.value = value, .next = NULL};
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
  list->values[pos].next = list->first;
}

#define APPEND_RIGHT_LIST_(T) JOIN(append_right_list_, T)
inline void APPEND_RIGHT_LIST_(T)(TL(T) * list, T value) {
  if (!list->capacity) {
    list->capacity = 1;
    list->size = 1;
    list->values = malloc(sizeof(TLN(T)));
    list->first = list->values;
    list->last = list->values;
    list->values[0] = (TLN(T)){.value = value, .next = NULL};
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
  list->values[pos].next = NULL;
  list->last->next = &list->values[pos];
}

#define CLEAN_LIST_(T) JOIN(clean_list_, T)
inline void CLEAN_LIST_(T)(TL(T) * list) {
  list->size = 0;
  list->lifo_free_size = 0;
}

#define FIT_LIST_(T) JOIN(fit_list_, T)
inline void FIT_LIST_(T)(TL(T) * list) {
  // O(n) complexity, so only lifo_free will be fit (O(1))
  list->lifo_free_capacity = list->lifo_free_size;
  list->lifo_free =
      realloc(list->lifo_free, sizeof(TLN(T) *) * list->lifo_free_size);
}

#define POP_LEFT_LIST_(T) JOIN(pop_left_list_, T)
inline T POP_LEFT_LIST_(T)(TL(T) * list) {
  const T value = list->first->value;
  const size_t pos = list->first - list->values;
  list->first = list->first->next;
  if (list->lifo_free_size == list->lifo_free_capacity) {
    list->lifo_free_capacity <<= 1;
    list->lifo_free =
        realloc(list->lifo_free, sizeof(size_t) * list->lifo_free_capacity);
  }
  list->lifo_free[list->lifo_free_size++] = pos;
  return value;
}