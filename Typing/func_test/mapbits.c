#include "mapserver.h"
#include <limits.h>

size_t msGetBitArraySize(int numbits)
{
  return((numbits + MS_ARRAY_BIT - 1) / MS_ARRAY_BIT);
}

ms_bitarray msAllocBitArray(int numbits)
{
  ms_bitarray array = calloc((numbits + MS_ARRAY_BIT - 1) / MS_ARRAY_BIT, MS_ARRAY_BIT);

  return(array);
}

int msGetBit(ms_const_bitarray array, int index)
{
  array += index / MS_ARRAY_BIT;
  return (*array & (1 << (index % MS_ARRAY_BIT))) != 0;    /* 0 or 1 */
}

int msGetNextBit(ms_const_bitarray array, int i, int size)
{

  register ms_uint32 b;

  while(i < size) {
    b = *(array + (i/MS_ARRAY_BIT));
    if( b && (b >> (i % MS_ARRAY_BIT)) ) {
      /* There is something in this byte */
      /* And it is not to the right of us */
      if( b & ( 1 << (i % MS_ARRAY_BIT)) ) {
        /* There is something at this bit! */
        return i;
      } else {
        i++;
      }
    } else {
      /* Nothing in this byte, move to start of next byte */
      i += MS_ARRAY_BIT - (i % MS_ARRAY_BIT);
    }
  }

  /* Got to the last byte with no hits! */
  return -1;
}

void msSetBit(ms_bitarray array, int index, int value)
{
  array += index / MS_ARRAY_BIT;
  if (value)
    *array |= 1 << (index % MS_ARRAY_BIT);           /* set bit */
  else
    *array &= ~(1 << (index % MS_ARRAY_BIT));        /* clear bit */
}

void msSetAllBits(ms_bitarray array, int numbits, int value)
{
  if (value)
    memset(array, 0xff, ((numbits + 7) / 8) ); /* set bit */
  else
    memset(array, 0x0,  ((numbits + 7) / 8) ); /* clear bit */
}

void msFlipBit(ms_bitarray array, int index)
{
  array += index / MS_ARRAY_BIT;
  *array ^= 1 << (index % MS_ARRAY_BIT);                   /* flip bit */
}
