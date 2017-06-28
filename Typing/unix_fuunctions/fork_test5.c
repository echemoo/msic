/*
 * fork_test.c
 * version 3
 * Create on: 2016-10-11
 * Author: echemoo
 */
#include <unistd.h>
#include <stdio.h>

int main() {
  fork();
  fork() && fork() || fork();
  fork();
  printf("+\n");
  return 0;
}
