#include <stdlib.h>
#include <string.h>

#define JOIN(x, y) x##y
#define TV(T) JOIN(vector_, T)

typedef struct {
  T *values;
  size_t size;
  size_t capacity;
} TV(T);

#define NEW_VECTOR_(T) JOIN(new_vector_, T)
inline TV(T) * NEW_VECTOR_(T)() { return calloc(1, sizeof(TV(T))); }

#define NEW_VECTOR_WITH_CAPACITY_(T) JOIN(new_vector_with_capacity_, T)
inline TV(T) * NEW_VECTOR_WITH_CAPACITY_(T)(size_t capacity) {
  TV(T) *const to_return = malloc(sizeof(TV(T)));
  *to_return = (TV(T)){.values = malloc(sizeof(T) * capacity),
                       to_return->size = 0,
                       to_return->capacity = capacity};
  return to_return;
}

#define INIT_VECTOR_(T) JOIN(init_vector_, T)
inline void INIT_VECTOR_(T)(TV(T) * vec) { *vec = (TV(T)){}; }

#define DEL_VECTOR_(T) JOIN(del_vector_, T)
inline void DEL_VECTOR_(T)(TV(T) * vec) {
  if (vec->capacity)
    free(vec->values);
}

#define APPEND_VECTOR_(T) JOIN(append_vector_, T)
inline void APPEND_VECTOR_(T)(TV(T) * vec, T value) {
  if (vec->capacity == 0) {
    vec->capacity = 1;
    vec->size = 1;
    vec->values = malloc(sizeof(T));
    vec->values[0] = value;
    return;
  }
  if (vec->capacity == vec->size) {
    vec->capacity <<= 1;
    vec->values = realloc(vec->values, vec->capacity * sizeof(T));
  }
  vec->values[vec->size++] = value;
}

#define CONCAT_VEC_(T) JOIN(concat_vec_, T)
inline void CONCAT_VEC_(T)(TV(T) * des, TV(T) const *orig) {
  if (orig->size == 0)
    return;

  const size_t start_des_cap = des->capacity;
  while (des->capacity < des->size + orig->size) {
    des->capacity <<= 1;
  }
  if (start_des_cap != des->capacity) {
    des->values = realloc(des->values, des->capacity * sizeof(T));
  }
  memcpy(&des->values[des->size], orig->values, orig->size * sizeof(T));
  des->size += orig->size;
}

#define CLEAN_VEC_(T) JOIN(clean_vec_, T)
inline void CLEAN_VEC_(T)(TV(T) * vec) { vec->size = 0; }

#define FIT_VEC_(T) JOIN(fit_vec_, T)
inline void FIT_VEC_(T)(TV(T) * vec) {
  if (vec->size != vec->capacity) {
    vec->capacity = vec->size;
    vec->values = realloc(vec->values, vec->capacity * sizeof(T));
  }
}

#define POP_VEC_(T) JOIN(pop_vec_, T)
inline T POP_VEC_(T)(TV(T) * vec) { return vec->values[--vec->size]; }