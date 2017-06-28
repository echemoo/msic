/******************************************************************************
 * Name:    dweight.c
 * Porpuse: Computes the dimensional weight of a 12" x 10" x 8" box 
 * Author:  echemoo
 *****************************************************************************/

#include <stdio.h>

int main(void)
{
  int height, length, width, volume, weight;

  height = 8;
  length = 12;
  width = 10;
  volume = height * length * width;
  weight = (volume + 165) / 166;

  printf("Diemensions: %dx%dx%d\n", length , width, height);
  printf("Volum (cubic inches): %d\n", volume);
  printf("Diemensions weight (pounds): %d\n", weight);

  return 0;
}
