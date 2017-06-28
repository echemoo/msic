/*
 * fork_test.c
 * version 3
 * Create on: 2016-10-11
 * Author: echemoo
 */
#include <unistd.h>
#include <stdio.h>

int main() {
  int i=0;
  for(i=0; i<3; i++){
    pid_t fpid = fork();
    if(fpid==0) printf("son\n");
    else printf("parant\n");
  }
  return 0;
}
