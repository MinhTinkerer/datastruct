#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list_node {
  struct list_node *next;
  struct list_node *prev;
  void             *item;
} list_node_t;

typedef struct list {
  list_node_t *first;
  list_node_t *last;
} list_t;

#define LIST_INITIALIZER {\
  .first = NULL,\
  .last  = NULL\
}

static inline void list_init(list_t *list) {
  list->first = NULL;
  list->last  = NULL;
}

static inline void* list_peek(list_t *list) {
  if (list->first == NULL) return NULL;
  return list->first->item;
}

static inline list_node_t* list_first(list_t *list) {
  return list->first;
}

static inline list_node_t* list_last(list_t *list) {
  return list->last;
}

static inline int list_isempty(list_t *list) {
  return list->first == NULL;
}

static inline int list_count(list_t* list) {
  if (list->first == NULL) return 0;
  int n = 1;
  for (list_node_t* node = list->first; node->next != NULL; node = node->next) n++;
  return n;
}

static inline list_node_t* list_next(list_node_t *node) {
  return node->next;
}

static inline list_node_t* list_prev(list_node_t *node) {
  return node->next;
}

static inline void* list_item(list_node_t *node) {
  return node->item;
}

typedef void (*list_dealloc_cb)(void*);

/* Push and pop are for LIFO stack-like behavior (use list_insert_after with list_last for queues) */
void  list_push(list_t *list, void *item);
void* list_pop(list_t *list);
void  list_insert_before(list_t *list, list_node_t *cur, void *item);
void  list_insert_after(list_t *list, list_node_t *cur, void *item);
void* list_split(list_t* list, list_node_t* node, list_t* left, list_t* right);
void  list_concat(list_t *list, list_t *left, list_t *right);
void* list_remove(list_t *list, list_node_t *cur);
void  list_clear(list_t *list, list_dealloc_cb dealloc);  /* MUST be called before discarding a list_t structure */

#define LIST_FOREACH(list, node) \
  for ((node)=list_first(list); node != NULL; (node)=list_next(node))

#endif /* LIST_H */

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
