#include <stdio.h>
#include "mapserver.h"

int main(int argc, char** argv)
{
   int numbits = 100;
   int nSize = msGetBitArraySize(numbits);
   printf("msGetBitArraySize(100):%d\n" , nSize );
   printf("test for gcc.\n");
   return 0;
}
