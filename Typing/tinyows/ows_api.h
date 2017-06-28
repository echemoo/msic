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


void array_add (array * a, buffer * key, buffer * value);
void array_flush (const array * a, FILE * output);
void array_free (array * a);
buffer *array_get (const array * a, const char *key);
buffer *array_get_key(const array * a, const char *value);
array *array_init ();
bool array_is_key (const array * a, const char *key);
bool array_is_value (const array * a, const char *value);
alist *alist_init();
void alist_free(alist * al);
void alist_add(alist * al, buffer * key, buffer * value);
bool alist_is_key(const alist * al, const char *key);
list *alist_get(const alist * al, const char *key);
void alist_flush(const alist * al, FILE * output);
void buffer_add (buffer * buf, char c);
void buffer_add_double (buffer * buf, double f);
void buffer_add_head (buffer * buf, char c);
void buffer_add_head_str (buffer * buf, char *str);
void buffer_add_int (buffer * buf, int i);
void buffer_add_str (buffer * buf, const char *str);
void buffer_add_nstr (buffer * buf, const char *str, size_t n);
buffer *buffer_from_str(const char *str);
bool buffer_cmp (const buffer * buf, const char *str);
bool buffer_ncmp(const buffer * buf, const char *str, size_t n);
bool buffer_case_cmp (const buffer * buf, const char *str);
void buffer_copy (buffer * dest, const buffer * src);
buffer *buffer_clone(buffer * buf);
void buffer_empty (buffer * buf);
void buffer_flush (buffer * buf, FILE * output);
void buffer_free (buffer * buf);
buffer *buffer_ftoa (double f);
buffer *buffer_init ();
buffer *buffer_itoa (int i);
void buffer_pop (buffer * buf, size_t len);
buffer *buffer_replace (buffer * buf, char *before, char *after);
void buffer_shift (buffer * buf, size_t len);
long int buffer_chr(const buffer * buf, char c);
long int buffer_rchr(const buffer * buf, char c);
buffer *buffer_encode_xml_entities_str(const char *str);
buffer *buffer_encode_json_str(const char *str);
buffer *cgi_add_xml_into_buffer (buffer * element, xmlNodePtr n);
char *cgi_getback_query (ows * o);
bool cgi_method_get ();
bool cgi_method_post ();
array *cgi_parse_kvp (ows * o, char *query);
array *cgi_parse_xml (ows * o, char *query);
bool check_regexp (const char *str_request, const char *str_regex);
buffer *fe_comparison_op (ows * o, buffer * typename, filter_encoding * fe, xmlNodePtr n);
buffer *fe_envelope (ows * o, buffer * typename, filter_encoding * fe, buffer *envelope, xmlNodePtr n);
void fe_error (ows * o, filter_encoding * fe);
buffer *fe_expression (ows * o, buffer * typename, filter_encoding * fe, buffer * sql, xmlNodePtr n);
buffer *fe_feature_id (ows * o, buffer * typename, filter_encoding * fe, xmlNodePtr n);
filter_encoding *fe_filter (ows * o, filter_encoding * fe, buffer * typename, buffer * xmlchar);
void fe_filter_capabilities_100 ()
