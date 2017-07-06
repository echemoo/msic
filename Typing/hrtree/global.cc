
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

