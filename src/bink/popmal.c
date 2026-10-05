/*
 * codfh-match: RAD's pushed allocations (the library's popmal.obj, in
 * .text): callers push (pointer variable, size) pairs, and one popmalloc
 * allocates them all in a single 32-byte aligned block and fills in the
 * pointers.
 */
#include "bink.h"
#include "binkint.h"

static U32 amt[32];
static void PTR4 * PTR4 *ptrs[32];
static U32 pushtot;
static U32 pushcur;

static void PTR4 * PTR4 * PTR4 *pushptr = ptrs;
static U32 PTR4 *pushamt = amt;
static U32 cursize = 32;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _pushptr @ 0x0043117C
// match: _pushamt @ 0x00431180
// match: _cursize @ 0x00431184

// match: _pushmalloc@8 @ 0x00258B20

RADEXPFUNC void RADEXPLINK pushmalloc(void PTR4 *ptr, U32 amount)
{
  if (cursize == pushcur)
  {
    void PTR4 * PTR4 * PTR4 *np = (void PTR4 * PTR4 * PTR4 *)radmalloc(cursize * 16);
    U32 PTR4 *na;

    memcpy(np, pushptr, cursize * 4);
    na = (U32 PTR4 *)(np + cursize * 2);
    memcpy(na, pushamt, cursize * 4);
    cursize *= 2;
    if (cursize != 64)
      radfree(pushptr);
    pushamt = na;
    pushptr = np;
  }

  amount = (amount + 31) & ~31;
  amount += ((((pushtot / 32) & 31) -
              ((amount / 32) & 31) + 1) & 31) * 32;
  pushtot += amount;
  pushamt[pushcur] = amount;
  pushptr[pushcur] = (void PTR4 * PTR4 *)ptr;
  ++pushcur;
}

// match: _popmalloctotal@0 @ 0x00258C00
RADEXPFUNC U32 RADEXPLINK popmalloctotal(void)
{
  return pushtot;
}

// match: _popmalloc@4 @ 0x00258C10
RADEXPFUNC void PTR4 *RADEXPLINK popmalloc(U32 amount)
{
  U8 PTR4 *p;

  amount = (amount + 31) & ~31;
  p = (U8 PTR4 *)radmalloc(pushtot + amount);
  pushtot = 0;
  if (p)
  {
    U8 PTR4 *cur = p + amount;
    U32 i;

    for (i = 0; i < pushcur; i++)
    {
      *pushptr[i] = cur;
      cur += pushamt[i];
    }
  }
  pushcur = 0;

  return p;
}
