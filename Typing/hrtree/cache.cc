
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

Cache::~Cache() {
  delete[] cache_cont;
  delete[] fuf_cont;
  delete[] LRU_indicator;
  delete[] cache_tree;
  delete[] dirty_indicator;

  for (int i = 0; i < cachesize; i++)
    delete[] cache[i];
  delete[] cache;
}

int Cache::next() {
  int ret_val, tmp;

  if (cachesize == 0) return -1;
  else {
    if (fuf_cont[ptr] == free) {
      ret_val = ptr++;
      ptr = ptr % cachesize;
      return ret_val;
    }
    else {
      tmp = (ptr + 1) % cachesize;
      while (tmp != ptr && fuf_cont[tmp] != free)
        tmp = (tmp + 1) % cachesize;

      if (ptr == tmp) {
        int lru_index = 0;
        for (int i = 0; i < cachesize; i++)
          if (LRU_indicator[i] > LRU_indicator[lru_index])
            lru_index = i;

        ptr = lru_index;
        if (dirty_indicator[ptr])
          cache_tree[ptr] -> file -> write_block(cache[ptr], cache_cont[ptr] - 1);
        fuf_cont[ptr] = free;
        dirty_indicator[ptr] = false;
        ret_val = ptr++;
        ptr = ptr % cachesize;

        return ret_val;
      }
      else
        return tmp;
    }
  }
}

int Cache::in_cache(int index, Cacheable *rt) {
  int i;
  int ret_val = -1;
  for (i = 0; i < cachesize; i++)
    if ((cache_cont[i] == index) && (cache_tree[i] == rt) && (fuf_cont[i] != free)) {
      LRU_indicator[i] = 0;
      ret_val = i;
    }
    else if (fuf_cont[i] != free)
      LRU_indicator[i]++;
  return ret_val;
}

