
#include "hrtree_headers.h"

int existsInList(int n, vector<int>& List) {
  if (List.size() == 0)
    return -1;
  for (unsigned int i = 0; i < List.size(); i++)
    if (List[i] == n)
      return i;
  return -1;
}

void eraseElement(int n, vector<int>& List) {
  int index = existsInList(n, List);
  if (index != -1)  // if n does exist in L
    List.erase(List.begin() + index);
}


void mergeSets(map<int, int>& S1, map<int, int>& S2) {
  if (S2.size() == 0)
    return;
  for (map<int, int>::iterator ii = S2.begin(); ii != S2.end(); ++ii)
    S1[(*ii).first] = (*ii).first;
}

// -------------------------------------------------


#ifdef UNIX
void strupr(char* _msg)
{
  int dist = 'A' - 'a';
  char* c_ptr = _msg;

  while (*c_ptr)
  {
    if (*c_ptr >= 'a')
      *c_ptr += dist;
    c_ptr++;
  }
}
#endif

//void error(char* t, bool ex) {
//    fprintf(stderr, t);
//    if (ex)
//        exit(0);
//}

void error(string msg, bool ex) {
  cerr << msg;
  if (ex)
    exit(0);
}

float area(int dimension, float *mbr) {
  int i;
  float sum;

  sum = 1.0;
  for (i = 0; i < dimension; i++)
    sum *= mbr[2 * i + 1] - mbr[2 * i];

  return sum;
}

float margin(int dimension, float* mbr) {
  float* ml, *mu, *m_last, sum;

  sum = 0.0;
  m_last = mbr + 2 * dimension;
  ml = mbr;
  mu = ml + 1;
  while (mu < m_last) {
    sum += *mu - *ml;
    ml += 2;
    mu += 2;
  }

  return sum;
}

bool inside(float& p, float& lb, float& ub) {
  return (p >= lb && p <= ub);
}


