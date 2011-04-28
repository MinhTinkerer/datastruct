#include "array.h"

#include <stdlib.h>
#include <assert.h>

/* start with 0x1000 elements (not bytes) */
static const int array_initial_size = 0x1000;
/* new size / old size = 3 / 2 */
static const int array_grow_mul     = 3;
static const int array_grow_div     = 2;

static void array_grow(array_t *array) {
  array->size  = array->size * array_grow_mul / array_grow_div;
  array->items = realloc(array->items, array->size * sizeof(void*));
}

void  array_init(array_t *array) {
  array->items   = malloc(array_initial_size * sizeof(void*));
  array->size    = array_initial_size;
  array->n       = 0;
}

int   array_push(array_t *array, void *item) {
  int i = array->n++;
  if (array->n > array->size) {
    array_grow(array);
    assert(i < array->size);
  }
  array->items[i] = item;
  return i;
}

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
