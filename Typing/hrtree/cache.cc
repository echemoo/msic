
#include "hrtree_headers.h"

Cache::Cache(int csize, int blength) {
  int i;

  ptr = 0;
  blocklength = blength;

  if (csize >= 0) cachesize = csize;
  else error("Cache size cannot be negative\n", TRUE);

  cache_cont = new int[cachesize];
  cache_tree = new Cacheable*[cachesize];
  fuf_cont = new uses[cachesize];
  LRU_indicator = new int[cachesize];
  dirty_indicator = new bool[cachesize];

  for (i = 0; i < cachesize; i++) {
    cache_cont[i] = 0;
    cache_tree[i] = NULL;
    fuf_cont[i] = free;
    LRU_indicator[i] = 0;
    dirty_indicator[i] = false;
  }

  cache = new char*[cachesize];
  for (i = 0; i < cachesize; i++)
    cache[i] = new char[blocklength];

  page_faults = 0;
}

