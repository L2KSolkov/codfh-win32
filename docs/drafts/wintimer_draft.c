/*
 * codfh-match: RAD's millisecond timer (the library's wintimer.obj): the
 * performance counter scaled to milliseconds, kept in step with
 * GetTickCount.
 */
#include "bink.h"
#include "binkint.h"

// match: _RADTimerRead@0 @ 0x00344990
RADEXPFUNC U32 RADEXPLINK RADTimerRead(void)
{
#pragma data_seg("BINKDATA")
  static S32 noprof = 1;
  static S32 radadj = 0;
#pragma data_seg()
  static U32 lastrad;
  static S64 qpfirst;
  static S64 qpfreq;
  static U32 lasttime;
  S64 now;
  U32 time;
  U32 rad;
  S32 diff;

  if (noprof)
  {
    noprof = 0;
    if (QueryPerformanceFrequency(&qpfreq))
    {
      QueryPerformanceCounter(&qpfirst);
      lastrad = 0;
      lasttime = GetTickCount();
      return 0;
    }
    qpfreq = 0;
    return GetTickCount();
  }

  if (qpfreq == 0)
    return GetTickCount();

  QueryPerformanceCounter(&now);
  time = GetTickCount();
  rad = (U32)((U64)((now - qpfirst) * 1000) / (U64)qpfreq) + radadj;

  diff = (time - lasttime) - (rad - lastrad);
  if (abs(diff) > 200)
  {
    radadj += diff;
    rad += diff;
  }

  if ((rad - lastrad) > 0xc0000000)
    return lastrad;

  lasttime = time;
  lastrad = rad;
  return rad;
}
