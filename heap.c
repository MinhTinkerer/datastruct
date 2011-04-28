#include "heap.h"

#include "array.h"

static inline int heap_parent(int i) {
  if (i == 0) { return -1; }
  return (i + 1) / 2 - 1;
}

static inline int heap_left(int i) {
  return (i + 1) * 2 - 1;
}

static inline int heap_right(int i) {
  return (i + 1) * 2;
}

void  heap_init(heap_t *heap, heap_cmp_cb compare) {
  array_init(&heap->items);
  heap->compare = compare;
}

void  heap_insert(heap_t *heap, void *item) {
  int i = array_push(&heap->items, item);
  heap_percolate_up(heap, i);
}

void  heap_percolate_down(heap_t *heap, int index) {
  void *left, *right, *cur;
  int  l, r, c;

  c = index;
  for (;;) {
    l = heap_left(c);
    r = heap_right(c);

    left  = array_get(&heap->items, l);
    right = array_get(&heap->items, r);
    cur   = array_get(&heap->items, c);

    if (left != NULL && right != NULL) {
      if (heap->compare(left, right) < 0) {
        goto left;
      } else {
        goto right;
      }
    } else if (left != NULL) {
      goto left;
    } else if (right != NULL) {
      goto right;
    } else {
      return;
    }

    left:
      if (heap->compare(left, cur) < 0) {
        array_swap(&heap->items, c, l);
        c = l;
      } else {
        return;
      }
      continue;
    right:
      if (heap->compare(right, cur) < 0) {
        array_swap(&heap->items, c, r);
        c = r;
      } else {
        return;
      }
      continue;
  }
}

void  heap_percolate_up(heap_t *heap, int index) {
  int i = index;
  int p;
  for (;;) {
    p = heap_parent(i);
    if (p < 0) { return; }
    if (heap->compare(array_get(&heap->items, i), array_get(&heap->items, p)) < 0) {
      array_swap(&heap->items, i, p);
      i = p;
    } else {
      return;
    }
  }
}

void* heap_pop(heap_t *heap) {
  int n = array_size(&heap->items);
  if (n == 0) { return NULL; }
  if (n == 1) { return array_pop(&heap->items); }

  array_swap(&heap->items, 0, n-1);
  void *result = array_pop(&heap->items);
  heap_percolate_down(heap, 0);
  return result;
}

void* heap_peek(heap_t *heap) {
  return array_get(&heap->items, 0);
}

/* FIXME: this implementation is slow (linear instead of logarithmic or constant time)
          replace brute-force search with a hash table implementation later */
int heap_index(heap_t *heap, void *item) {
  for (int i=0; i < array_size(&heap->items); i++) {
    if (array_get(&heap->items, i) == item) {
      return i;
    }
  }
  return -1;
}

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
