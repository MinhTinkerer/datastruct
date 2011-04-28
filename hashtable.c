#include "hashtable.h"

#include "list.h"

static const uint32_t hashtable_hash_frac = 3037000499;

int hashtable_hash_voidp(void *key) {
  /* this doesn't look safe for 64-bit systems at first due to the cast from void* to uint32_t,
   * but I'm fairly certain it should work perfectly fine for hashing on all systems */
  uint32_t value = (uint32_t)*((void**)key);
  return (value * hashtable_hash_frac) >> (32 - HASHTABLE_BITS);
}

int hashtable_cmp_voidp(void *key_a, void *key_b) {
  void *a = *((void**)key_a);
  void *b = *((void**)key_b);
  return a > b ? 1 : a < b ? -1 : 0;
}

void* hashtable_copy_voidp(void *key) {
  void **result = malloc(sizeof(void*));
  *result = *((void**)key);
  return result;
}

void  hashtable_init(hashtable_t *table, hashtable_hash_cb hash, hashtable_cmp_cb compare) {
  for (int i = 0; i < HASHTABLE_BUCKETS; i++) {
    list_init(&table->buckets[i]);
  }
  table->hash    = hash;
  table->compare = compare;
}

void  hashtable_set(hashtable_t *table, void *key, void* value) {
  int     i      = table->hash(key) % HASHTABLE_BUCKETS;
  list_t *bucket = &table->buckets[i];
  /* INCOMPLETE: find and modify _existing_ buckets */
  hashtable_item_t *item = malloc(sizeof(hashtable_item_t));
  item->key      = key;
  item->value    = value;
  list_push(bucket, item);
}

void* hashtable_get(hashtable_t *table, void *key) {
  int     i      = table->hash(key) % HASHTABLE_BUCKETS;
  list_t *bucket = &table->buckets[i];
  for (list_node_t *node = list_first(bucket); node != NULL; node = list_next(node)) {
    hashtable_item_t *item = list_item(node);
    if (table->compare(item->key, key) == 0) {
      return item->value;
    }
  }
  return NULL;
}   

void* hashtable_remove(hashtable_t *table, void *key) {


/* vim: set ts=2 sts=2 sw=2 et ft=c tw=120: */
