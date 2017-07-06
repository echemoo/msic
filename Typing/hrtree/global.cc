
#include "hrtree_headers.h"

int existsInList(int n, vector<int>& List) {
  if (List.size() == 0)
    return -1;
  for (unsigned int i = 0; i < List.size(); i++)
    if (List[i] == n)
      return i;
  return -1;
}

