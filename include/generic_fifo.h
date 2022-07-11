#include <stdlib.h>
#include <string.h>

#define JOIN(x, y) x##y
#define TF(TYPE) JOIN(fifo_, TYPE)

typedef struct {
  T *v1, *v2;
  size_t c1, c2;
  size_t start, size;
} TF(T);

#define NEW_FIFO_(T) JOIN(new_fifo_, T)
inline TF(T) * NEW_FIFO_(T)() {
  TF(T) *to_return = malloc(sizeof(TF(T)));
  *to_return = (TF(T)){.v1 = NULL, .v2 = NULL, .c1 = 0, .c2 = 0, .start = 0};
  return to_return;
}

#define INIT_FIFO_(T) JOIN(init_fifo_, T)
inline void INIT_FIFO_(T)(TF(T) * fifo) {
  *fifo = (TF(T)){.v1 = NULL, .v2 = NULL, .c1 = 0, .c2 = 0, .start = 0};
}

#define CLEAN_FIFO_(T) JOIN(clean_fifo_, T)
inline void CLEAN_FIFO_(T)(TF(T) * fifo) {
  fifo->start = 0;
  fifo->size = 0;
}

#define APPEND_FIFO_(T) JOIN(append_fifo_, T)
inline void APPEND_FIFO_(T)(TF(T) * fifo, T value) {
  if (!fifo->v1) {
    fifo->v1 = malloc(sizeof(T));
    fifo->v1[0] = value;
    fifo->c1 = 1;
    fifo->size = 1;
    return;
  }

  const size_t new_pos = fifo->start + fifo->size++;
  if (new_pos < fifo->c1) {
    fifo->v1[new_pos] = value;
    return;
  }

  if (!fifo->v2) {
    fifo->v2 = malloc(sizeof(T));
    fifo->v2[0] = value;
    fifo->c2 = 1;
    return;
  }

  const size_t pos_c2 = new_pos - fifo->c1;
  if (pos_c2 == fifo->c2) {
    fifo->c2 <<= 1;
    fifo->v2 = realloc(fifo->v2, fifo->c2 * sizeof(T));
  }
  fifo->v2[pos_c2] = value;
}

#define DEL_FIFO_(T) JOIN(del_fifo_, T)
inline void DEL_FIFO_(T)(TF(T) * fifo) {
  if (fifo->c1) {
    free(fifo->v1);
  }
  if (fifo->c2) {
    free(fifo->v2);
  }
}

#define POP_RIGHT_FIFO_(T) JOIN(pop_right_fifo_, T)
inline T POP_RIGHT_FIFO_(T)(TF(T) * fifo) {
  const size_t pos_c1 = fifo->start + --fifo->size;
  if (pos_c1 < fifo->c1) {
    return fifo->v1[pos_c1];
  }
  const size_t pos_c2 = pos_c1 - fifo->c1;
  return fifo->v2[pos_c2];
}

#define POP_LEFT_FIFO_(T) JOIN(pop_left_fifo_, T)
inline T POP_LEFT_FIFO_(T)(TF(T) * fifo) {
  const size_t pos_c1 = fifo->start++;
  fifo->size--;

  const T to_return = fifo->v1[pos_c1];

  if (pos_c1 + 1 == fifo->c1) {

    size_t const temp_c = fifo->c1;
    fifo->c1 = fifo->c2;
    fifo->c2 = temp_c;

    T *const temp_t = fifo->v1;
    fifo->v1 = fifo->v2;
    fifo->v2 = temp_t;

    fifo->start = 0;
  }

  return to_return;
}