#ifndef __BLK_FILE
#define __BLK_FILE

//header files
#include <stdio.h>
#include "gendef.h"

class BlockFile
{
  public:
    FILE* fp;           // os file pointer
    char* filename;
    int blocklength;    // length of a block
    int act_block;      // block # of fp's position (fp can stay at block boundaries)
    int number;         // total # of blocks
    bool new_flag;      // specifies if this is a new file

    BlockFile(const char* name, int b_length);
    ~BlockFile();

    void put_bytes(char* bytes, int num){fwrite(bytes, num, 1, fp);}
};

#endif // __BLK_FILE
