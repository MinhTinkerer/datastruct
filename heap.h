#ifndef HEAP_H
#define HEAP_H

#include "array.h"

/* a compare callback shoud return -1 for a<b, 0 for a=b, and 1 for a>b */
typedef int (*heap_cmp_cb)(void* a, void* b);

typedef struct heap {
  array_t     items;
  heap_cmp_cb compare;
} heap_t;

void  heap_init(heap_t *heap, heap_cmp_cb compare);
void  heap_insert(heap_t *heap, void *item);
void  heap_percolate_down(heap_t *heap, int index);
void  heap_percolate_up(heap_t *heap, int index);
void* heap_pop(heap_t *heap);
void* heap_peek(heap_t *heap);
int   heap_index(heap_t *heap, void *item);
static inline int heap_size(heap_t *heap) {
  return array_size(&heap->items);
}

#endif /* HEAP_H */

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
