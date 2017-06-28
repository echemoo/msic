/*
 * fork_test.c
 * version 4
 * Create on: 2016-10-11
 * Author: echemoo
 */
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t fpid;
  int count=0;
  printf("fork!");
  fpid = fork();
  if(fpid<0) printf("error in fork!");
  else if (fpid == 0){
    printf("i am the child process, my process id is %d\n", getpid());
    count++;
  }else {
    printf("i am the parent process, my process id is %d\n", getpid());
    count++;
  }
  printf("Total Result:%d\n", count);
  return 0;
}
