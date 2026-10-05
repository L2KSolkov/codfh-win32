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
  amount += (((pushtot >> 5) - (amount >> 5) + 1) & 31) << 5;
  pushtot += amount;
  pushamt[pushcur] = amount;
  pushptr[pushcur] = (void PTR4 * PTR4 *)ptr;
  ++pushcur;
}

