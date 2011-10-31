#include "array.h"

#include <stdlib.h>
#include <assert.h>

/* start with 0x100 elements (not bytes) */
static const int array_initial_size = 0x100;
/* new size / old size = 3/2 */
static const int array_grow_mul = 3;
static const int array_grow_div = 2;

/* grow one increment w/ exponential scaling */
static void array_grow(array_t *array);
/* grow to at least 'size' w/ exponential scaling */
static void array_growto(array_t *array, int minsize, uint8_t clearbyte);
/* grow to exactly 'size' entries */
static void array_resize(array_t *array, int size);

/* ------------------------ */
void array_init(array_t *array, int item_size) {
  array->data      = malloc(array_initial_size * item_size);
  array->size      = array_initial_size;
  array->item_size = item_size;
  array->num_items = 0;
}

void array_clear(array_t *array) {
  free(array->data);
  array->data      = malloc(array_initial_size * array->item_size);
  array->size      = array_initial_size;
  array->num_items = 0;
}

void array_free(array_t *array) {
  free(array->data);
  array->size      = 0;
  array->item_size = 0;
  array->num_items = 0;
}

int array_push(array_t *array, void *item) {
  int i = array->num_items++;
  if (array->num_items > array->size) {
    array_grow(array);
    assert(i < array->size);
  }
  int bytes = array->item_size;
  memcpy(array->data + i * bytes, item, bytes);
  return i;
}

void array_set_expand(array_t *array, int i, void *item, uint8_t clearbyte) {
  if (i < array->num_items) {
    array_set(array, i, item);
    return;
  }
  array_growto(array, i+1, clearbyte);
  array->num_items = i + 1;
  array_set(array, i, item);
}

static void array_grow(array_t *array) {
  int size = array->size * array_grow_mul / array_grow_div;
  array_resize(array, size);
}

static void array_growto(array_t *array, int minsize, uint8_t clearbyte) {
  int oldsize = array->num_items;
  int size    = array->size;
  while (size < minsize) {
    size = size * array_grow_mul / array_grow_div;
  }
  array_resize(array, size);
  memset(array->data + oldsize * array->item_size, clearbyte, (minsize - oldsize) * array->item_size);
}

static void array_resize(array_t *array, int size) {
  array->data = realloc(array->data, size * array->item_size);
  array->size = size;
}
/* vim: set ts=2 sw=2 et */
