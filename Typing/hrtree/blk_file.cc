
#include "hrtree_headers.h"

void BlockFile::fwrite_number(int value){
  put_bytes((char*) &value, sizeof(int));
}

int BlockFile::fread_number(){
  char ca[sizeof(int)];
  get_bytes(ca, sizeof(int));
  return *((int*)ca);
}

BlockFile::BlockFile(const char* name, int b_length){
  char* buffer;
  int l;

  filename = new char[strlen(name) + 1];
  strcpy(filename, name);
  blocklength = b_length;

  number = 0;       // number is the # of blocks stored in a file

  if((fp=fopen(name,"rb+")) != 0){
    new_flag = FALSE;
    blocklength = fread_number();
    number = fread_number();
  }
  else{
    if (blocklength < BFHEAD_LENGTH)
      error("BlockFile::BlockFile: Blocks zu kurz\n", TRUE);

    fp = fopen(filename, "wb+");
    if (fp == NULL)
      error("BlockFile::new_file: Schreibfehler", TRUE);

    new_flag = TRUE;
    fwrite_number(blocklength);
    fwrite_number(0);       // write # of blocks in the file

    buffer = new char[(l=blocklength-(int)ftell(fp))];
    memset(buffer, 0, sizeof(buffer));
    put_bytes(buffer, l);   // fill in the rest of block with 0

    delete[] buffer;
  }

  fseek(fp, 0, SEEK_SET);
  act_block=0;
}

BlockFile::~BlockFile(){
  delete[] filename;
  fclose(fp);
}

void BlockFile::read_header(char* buffer){
  fseek(fp, BFHEAD_LENGTH, SEEK_SET);
  get_bytes(buffer, blocklength - BFHEAD_LENGTH);

  if (number < 1){
    fseek(fp, 0, SEEK_SET);
    act_block = 0;
  }
  else
    act_block = 1;
}

void BlockFile::set_header(char* header){
  fseek(fp, BFHEAD_LENGTH, SEEK_SET);
  put_bytes(header, blocklength - BFHEAD_LENGTH);
  if (number < 1){
    fseek(fp, 0, SEEK_SET);
    act_block = 0;
  }
  else
    act_block = 1;
}


