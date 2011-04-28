#include "list.h"

void  list_push(list_t *list, void *item) {
  list_node_t *node = malloc(sizeof(list_node_t));
  list_node_t *top  = list_first(list);
  if (top == NULL) {
    node->prev = NULL;
    node->next = NULL;
    node->item = item;

    list->first = node;
    list->last  = node;
  } else {
    node->prev = NULL;
    node->next = top;
    node->item = item;
    top->prev  = node;

    list->first = node;
  }
}

void* list_pop(list_t *list) {
  list_node_t *top  = list_first(list);
  if (top == NULL) { return NULL; }

  list_node_t *next = top->next;
  if (next == NULL) {
    list->first = NULL;
    list->last  = NULL;
  } else {
    next->prev  = NULL;
    list->first = next;
  }

  void *item = top->item;
  free(top);
  return item;
}

void  list_insert_before(list_t *list, list_node_t *cur, void *item) {
  if (cur == NULL) { list_push(list, item); return; }

  list_node_t *node = malloc(sizeof(list_node_t));
  list_node_t *prev = cur->prev;
  if (list->first == NULL || list->last == NULL) {
    node->prev  = NULL;
    node->next  = NULL;
    list->first = node;
    list->last  = node;
  } else if (prev == NULL) {
    node->prev = NULL;
    node->next = cur;
    node->item = item;
    cur->prev  = node;

    list->first = node;
  } else {
    node->prev = prev;
    node->next = cur;
    node->item = item;
    prev->next = node;
    cur->prev  = node;
  }
}
    
void  list_insert_after(list_t *list, list_node_t *cur, void *item) {
  if (cur == NULL) { list_push(list, item); return; }

  list_node_t *node = malloc(sizeof(list_node_t));
  list_node_t *next = cur->next;
  if (list->first == NULL || list->last == NULL) {
    node->prev  = NULL;
    node->next  = NULL;
    list->first = node;
    list->last  = node;
  } else if (next == NULL) {
    node->prev = cur;
    node->next = NULL;
    node->item = item;
    cur->next  = node;

    list->last = node;
  } else {
    node->prev = cur;
    node->next = next;
    node->item = item;
    next->prev = node;
    cur->next  = node;
  }
}

void* list_remove(list_t *list, list_node_t *cur) {
  if (cur->prev == NULL) {
    list->first = cur->next;
  } else {
    cur->prev->next = cur->next;
  }
  if (cur->next == NULL) {
    list->last = cur->prev;
  } else {
    cur->next->prev = cur->prev;
  }
  void *item = cur->item;
  free(cur);
  return item;
}

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
