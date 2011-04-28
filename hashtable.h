#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HASHTABLE_BITS    12
#define HASHTABLE_BUCKETS (1<<12)

typedef int   (*hashtable_hash_cb)(void *key);
typedef int   (*hashtable_cmp_cb)(void *key_a, void *key_b);
typedef void* (*hashtable_copy_cb)(void *key);

typedef struct hashtable {
  list_t            buckets[HASHTABLE_BUCKETS];
  hashtable_hash_cb hash;
  hashtable_cmp_cb  compare;
} hashtable_t;

typedef struct hashtable_item {
  void *key;
  void *value;
} hashtable_item_t;

/* a basic built-in callback for pointers */
int   hashtable_hash_voidp(void *key);
int   hashtable_cmp_voidp(void *key_a, void *key_b);
void* hashtable_copy_voidp(void *key);

void  hashtable_init(hashtable_t *table, hashtable_hash_cb hash, hashtable_cmp_cb compare);
void  hashtable_set(hashtable_t *table, void *key, void* value);
void* hashtable_get(hashtable_t *table, void *key);
void* hashtable_remove(hashtable_t *table, void *key);

#endif /* HASHTABLE_H */

/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
