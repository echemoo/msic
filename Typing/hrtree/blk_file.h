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
    void get_bytes(char* bytes, int num){fread(bytes, num, 1, fp);}
    void fwrite_number(int num);
    int fread_number();
    void seek_block(int bnum){fseek(fp, (bnum-act_block) * blocklength, SEEK_CUR);}
    void read_header(char* header);
    void set_header(char* header);
    bool read_block(Block b, int i);
    bool write_block(Block b, int i);
    int append_block(Block b);
    bool delete_last_blocks(int num);
    bool file_new(){return new_flag;}
    int get_blocklength(){return blocklength;}
    int get_num_of_blocks(){return number;}
};



#endif // __BLK_FILE
