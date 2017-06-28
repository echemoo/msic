/*
 * fork_test.c
 * version 2
 * Create on: 2016-10-11
 * Author: echemoo
 */
#include <unistd.h>
#include <stdio.h>

int main() {
  int i=0;
  printf("i\tson/pa\tppid\tpid\tfpid\n");
  for(i=0; i<2;i++){
    pid_t fpid = fork();
    if(fpid < 0) printf("error!\n");
    else if(fpid == 0){
      printf("%d\tchild\t%4d\t%4d\t%4d\n", i, getppid(), getpid(), fpid);
    }else printf("%d\tparant\t%4d\t%4d\t%4d\n", i, getppid(), getpid(), fpid);
  }
  return 0;
}
