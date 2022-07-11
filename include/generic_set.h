#include <stdlib.h>
#include <string.h>

// REQUIREMENTS:
// T is the type of the elements in the set.
// HASH_F is a function that takes a T and returns a size_t.

// OPTIONAL:
// HASH_SIZE is the size of the hash table. (default: 65537)
// SUFFIX is the suffix of the struct and functions. (default: HASH_F)

#define JOIN(x, y) x##y

// Errors:
// 1. HASH_SIZE is undefined.
// 2. HASH_F is undefined.
#if !defined(T) || !defined(HASH_F)
#error "T and HASH_F must be defined."
#endif

// default HASH_SIZE
#ifndef HASH_SIZE
#define HASH_SIZE 65537
#endif

// default SUFFIX
#ifndef SUFFIX
#define S HASH_F
#else
#define S SUFFIX
#endif

#define TS(S) JOIN(set_, S)

typedef struct {
  T *Values;
  size_t *sizes;
  size_t size;

} TS(S);

#define NEW_SET_(S) JOIN(new_set_, S)
TS(S) * NEW_SET_(S)() { return calloc(1, sizeof(TS(S))); }

#define INIT_SET_(S) JOIN(init_set, S)
void INIT_SET_(S)(TS(S) * set) { *set = (TS(S)){}; }


