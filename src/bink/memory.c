/*
 * codfh-match: RAD's memory hooks (the library's memory.obj, in .text):
 * allocations aligned to 32 bytes, through the user's functions when set,
 * each block remembering how to free itself.
 */
#include "bink.h"
#include "binkint.h"

static void PTR4 *(RADLINK *usermalloc)(U32 bytes);
static void (RADLINK *userfree)(void PTR4 *ptr);

void *malloc(size_t size);
void free(void *ptr);

// match: _radmalloc@4 @ 0x00258C90
// sp-match: _radmalloc@4 @ 0x00174B00
RADEXPFUNC void PTR4 *RADEXPLINK radmalloc(U32 numbytes)
{
  U8 *p;
  U8 type;
  U8 ofs;

  if ((numbytes == 0) || (numbytes == 0xffffffff))
    return 0;

  if (usermalloc)
  {
    p = (U8 *)usermalloc(numbytes + 64);
    if (p)
    {
      if (p == (U8 *)-1)
        return 0;
      type = 3;
      goto aligned;
    }
  }

  p = (U8 *)malloc(numbytes + 64);
  if (p == 0)
    return 0;
  type = 0;

 aligned:
  ofs = (U8)(64 - ((U8)(U32)p & 31));
  p += ofs;
  p[-1] = ofs;
  p[-2] = type;
  if (type == 3)
    ((void **)p)[-2] = (void *)userfree;
  return p;
}

// match: _radfree@4 @ 0x00258D00
// sp-match: _radfree@4 @ 0x00174B70
RADEXPFUNC void RADEXPLINK radfree(void PTR4 *ptr)
{
  if (ptr)
  {
    if (((U8 *)ptr)[-2] == 3)
      ((void (RADLINK *)(void PTR4 *))((void **)ptr)[-2])((U8 *)ptr - ((U8 *)ptr)[-1]);
    else
      free((U8 *)ptr - ((U8 *)ptr)[-1]);
  }
}
