#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

typedef struct array {
  uint8_t *data;
  int      size;
  int      item_size;
  int      num_items;
} array_t;

void  array_init(array_t *array, int size);
void  array_clear(array_t *array);
void  array_free(array_t *array);
int   array_push(array_t *array, void *item);

static inline int array_pop(array_t *array, void* item) {
  if (array->num_items <= 0) return -1;
  int bytes = array->item_size;
  memcpy(item, array->data + (--array->num_items) * bytes, bytes);
  return 0;
}

static inline void array_get(array_t *array, int i, void* item) {
  assert(i < array->num_items);
  int bytes = array->item_size;
  memcpy(item, array->data + i * bytes, bytes);
}

static inline void  array_set(array_t *array, int i, void *item) {
  assert(i < array->num_items);
  int bytes = array->item_size;
  memcpy(array->data + i * bytes, item, bytes);
}
void array_set_expand(array_t *array, int i, void *item, uint8_t clearbyte);

static inline void* array_data(array_t *array) {
  return array->data;
}

static inline int array_bytes(array_t *array) {
  return array->num_items * array->item_size;
}

static inline int array_size(array_t *array) {
  return array->num_items;
}

#endif /* ARRAY_H */

/* vim: set ts=2 sw=2 et */
