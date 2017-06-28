/*
  Copyright (c) <2007-2012> <Barbara Philippot - Olivier Courtin>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/


#ifndef OWS_STRUCT_H
#define OWS_STRUCT_H

#include <stdio.h>    /* FILE prototype */


/* ========= Structures ========= */

enum Bool {
  false,
  true
};

typedef enum Bool bool;

#define BUFFER_SIZE_INIT   256

typedef struct Buffer {
  size_t use;     /** size used for data */
  size_t size;    /** memory available */
  size_t realloc;   /** size to next realloc */
  char * buf;     /** data */
} buffer;


typedef struct List_node {
  buffer * value;
  struct List_node * next;
  struct List_node * prev;
} list_node;

typedef struct List {
  list_node * first;
  list_node * last;
  unsigned int size;
} list;


typedef struct Mlist_node {
  list * value;
  struct Mlist_node * next;
  struct Mlist_node * prev;
} mlist_node;

typedef struct Mlist {
  mlist_node * first;
  mlist_node * last;
  unsigned int size;
} mlist;


typedef struct Alist_node {
  buffer * key;
  list * value;
  struct Alist_node * next;
} alist_node;

typedef struct Alist {
  alist_node * first;
  alist_node * last;
} alist;


typedef struct Array_node {
  buffer * key;
  buffer * value;
  struct Array_node * next;
} array_node;

typedef struct Array {
  array_node * first;
  array_node * last;
} array;


/* ========= OWS Common ========= */

//}

#endif /* OWS_STRUCT_H */
