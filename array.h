#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <assert.h>

typedef struct array {
  void      **items;
  int         size;
  int         n;
} array_t;

void  array_init(array_t *array);
int   array_push(array_t *array, void *item);

static inline void* array_pop(array_t *array) {
  if (array->n <= 0) { return NULL; }
  return array->items[--array->n];
}

static inline void* array_get(array_t *array, int i) {
  return i < array->n ? array->items[i] : NULL;
}

static inline void  array_set(array_t *array, int i, void *item) {
  assert(i < array->n);
  array->items[i] = item;
}

static inline void  array_swap(array_t *array, int i, int j) {
  assert(i < array->n && j < array->n);
  void* temp      = array->items[i];
  array->items[i] = array->items[j];
  array->items[j] = temp;
}

static inline int   array_size(array_t *array) {
  return array->n;
}

#endif /* ARRAY_H */

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
