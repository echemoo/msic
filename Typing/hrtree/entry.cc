
#include "hrtree_headers.h"

Entry::Entry() {
  son_ptr = NULL;
  bounces = NULL;
}

Entry::Entry(int _dimension, RTree* rt) {
  dimension = _dimension;
  my_tree = rt;
  bounces = new float[2 * dimension];
  son_ptr = NULL;
  son = 0;
  level = 0;
}

Entry::Entry(const Entry& e) {
  son = e.son;
  dimension = e.dimension;
  level = e.level;
  my_tree = e.my_tree;
  son_ptr = e.son_ptr;
  bounces = new float[2 * dimension];
  memcpy(bounces, e.bounces, 2 * dimension * sizeof(float));
}

Entry::~Entry() {
  if (bounces)
    delete[] bounces;
  if (son_ptr != NULL)
    delete son_ptr;
}

void Entry::del_son() {
  if (son_ptr != NULL) {
    delete son_ptr;
    son_ptr = NULL;
  }
}

Linkable* Entry::gen_Linkable() {
  Linkable *new_link = new Linkable(dimension);
  new_link -> son = son;
  for (int i = 0; i < 2 * dimension; i++)
    new_link -> bounces[i] = bounces[i];
  new_link -> level = level;

  return new_link;
}

int Entry::get_size() {
  return 2 * dimension * sizeof(float) + sizeof(int);
}

RTNode* Entry::get_son() {
  if (son_ptr == NULL)
    son_ptr = new RTNode(my_tree, son);

  return son_ptr;
}

void Entry::init_entry(int _dimension, RTree* _rt) {
  dimension = _dimension;
  my_tree = _rt;
  bounces = new float[2 * dimension];
  son_ptr = NULL;
  son = 0;
  level = 0;
}

void Entry::read_from_buffer(char* buffer) {
  int i;

  i = 2 * dimension * sizeof(float);
  memcpy(bounces, buffer, i);
  memcpy(&son, &buffer[i], sizeof(int));
  i += sizeof(int);
}

