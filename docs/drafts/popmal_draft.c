/*
 * codfh-match: RAD's grouped allocations (the library's popmal.obj, in
 * .text): pushmalloc queues pointers to fill with sizes, popmalloc makes
 * one allocation for all of them, staggering each block's start by its
 * running total so the blocks fall on different cache lines.
 */
#include "bink.h"
#include "binkint.h"

static U32 amt[32];
static void *ptrs[32];
static U32 pushtot;
static U32 pushcur;
static void **pushptr = ptrs;
static U32 *pushamt = amt;
static U32 cursize = 32;

// match: _pushmalloc@8 @ 0x00258B20
RADEXPFUNC void RADEXPLINK pushmalloc(void PTR4 *ptr, U32 amount)
{
  if (cursize == pushcur)
  {
    void **np = (void **)radmalloc(cursize * 16);
    U32 *na;

    memcpy(np, pushptr, cursize * 4);
    na = (U32 *)(np + cursize * 2);
    memcpy(na, pushamt, cursize * 4);
    cursize *= 2;
    if (cursize != 64)
      radfree(pushptr);
    pushamt = na;
    pushptr = np;
  }

  amount = (amount + 31) & ~31;
  {
    U32 c = ((pushtot >> 5) - (amount >> 5) + 1) & 31;

    amount += c << 5;
  }
  pushtot += amount;
  pushamt[pushcur] = amount;
  pushptr[pushcur] = ptr;
  pushcur++;
}

// match: _popmalloctotal@0 @ 0x00258C00
RADEXPFUNC U32 RADEXPLINK popmalloctotal(void)
{
  return pushtot;
}

// match: _popmalloc@4 @ 0x00258C10
RADEXPFUNC void PTR4 *RADEXPLINK popmalloc(U32 amount)
{
  U8 *p;

  amount = (amount + 31) & ~31;
  p = (U8 *)radmalloc(pushtot + amount);
  pushtot = 0;
  if (p)
  {
    U8 *cur = p + amount;
    U32 i;

    for (i = 0; i < pushcur; i++)
    {
      *(void **)pushptr[i] = cur;
      cur += pushamt[i];
    }
  }
  pushcur = 0;
  return p;
}
