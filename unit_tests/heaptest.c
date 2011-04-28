#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

int compare(void *a, void *b) {
  int *c = a;
  int *d = b;
  return *c < *d ? -1 : *c > *d ? 1 : 0;
}

#define TEST_MAX 0x10000

int main() {
  heap_t heap;
  heap_init(&heap, &compare);

  int count = 0;
  int *value;
  srand(time(NULL));
  /* randomly insert and remove nodes */
  printf("Random insertion & removal test:\n");
  for (int i=0; i < TEST_MAX; i++) {
    if (rand() % 10 < 8) {
      printf("\r%d Ins. ", i);
      value  = malloc(sizeof(int));
      *value = rand();
      heap_insert(&heap, value);
      count++;
    } else {
      printf("\r%d Rem. ", i);
      value = heap_peek(&heap);
      if (heap_pop(&heap) != value) {
        fprintf(stderr, "Discrepancy between heap_peek() and heap_pop()!\n");
        return -1;
      }
      if (count > 0) {
        count--;
        if (value == NULL) {
          fprintf(stderr, "Unexpected NULL value!\n");
          return -1;
        }
        free(value);
      } else if (value != NULL) {
        fprintf(stderr, "Expected NULL value!\n");
        return -1;
      }
    }
  }
  /* remove all remaining nodes */
  int previous = INT_MIN;
  for (;;) {
    value = heap_pop(&heap);
    if (value == NULL) { break; }
    if (previous > *value) {
      fprintf(stderr, "Items out of order!\n");
      return -1;
    }
    previous = *value;
    free(value);
    count--;
  }
  if (count > 0) {
    fprintf(stderr, "We lost items!\n");
    return -1;
  } else if (count < 0) {
    fprintf(stderr, "We gained items!\n");
    return -1;
  }

  /* insert consecutive numbers into heap */
  printf("\n\nConsecutive number test:\n");
  for (int i=0; i < TEST_MAX; i++) {
    value  = malloc(sizeof(int));
    *value = i;
    heap_insert(&heap, value);
  }
  /* read consecutive numbers from heap */
  for (int i=0; i < TEST_MAX; i++) {
    value = heap_pop(&heap);
    printf("\r%d:%d ", i, *value);
    if (*value != i) {
      fprintf(stderr, "Consecutive number matching failed!\n");
      return -1;
    }
    free(value);
  }
  printf("\n\nTest successful! :D\n");
  return 0;
}
/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
