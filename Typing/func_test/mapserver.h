#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#include <stdint.h>

//#define MS_DLL_EXPORT     __declspec(dllexport)
#define MS_DLL_EXPORT 

#if ULONG_MAX == 0xffffffff
typedef long            ms_int32;
typedef unsigned long   ms_uint32;
#elif UINT_MAX == 0xffffffff
typedef int             ms_int32;
typedef unsigned int    ms_uint32;
#else
typedef int32_t         ms_int32;
typedef uint32_t        ms_uint32;
#endif

typedef ms_uint32 *     ms_bitarray;
typedef const ms_uint32 *ms_const_bitarray;


  /* mapbits.c - bit array handling functions and macros */

#define MS_ARRAY_BIT 32

#define MS_GET_BIT(array,i) (array[i>>5] & (1 <<(i & 0x3f)))
#define MS_SET_BIT(array,i) {array[i>>5] |= (1 <<(i & 0x3f));}
#define MS_CLR_BIT(array,i) {array[i>>5] &= (~(1 <<(i & 0x3f)));}

MS_DLL_EXPORT size_t msGetBitArraySize(int numbits); /* in mapbits.c */
MS_DLL_EXPORT ms_bitarray msAllocBitArray(int numbits);
MS_DLL_EXPORT int msGetBit(ms_const_bitarray array, int index);
MS_DLL_EXPORT void msSetBit(ms_bitarray array, int index, int value);
MS_DLL_EXPORT void msSetAllBits(ms_bitarray array, int index, int value);
MS_DLL_EXPORT void msFlipBit(ms_bitarray array, int index);
MS_DLL_EXPORT int msGetNextBit(ms_const_bitarray array, int index, int size);
