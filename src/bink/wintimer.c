/*
 * codfh-match: RAD's millisecond timer (the library's wintimer.obj): the
 * performance counter scaled to milliseconds, kept in step with
 * GetTickCount.
 */
#include "bink.h"
#include "binkint.h"

// RAD puts all of Bink's code in its BINK section (the image's 0x341480-0x34E01C).
#pragma code_seg("BINK")

// Its data definitions (PLAN M5), in the image's address order.
// 0x00508230
U32 wintimer_lastrad;
// 0x00508238
S64 wintimer_qpfirst;
// 0x00508240
S64 wintimer_qpfreq;
// 0x00508248
U32 wintimer_lasttime;
// End of its data definitions.


/* The timer's function statics, named through their image aliases. */
/* The two initialized ones are in BINKDATA (the image's 0x52F268, after the logo movie). */
#pragma data_seg("BINKDATA")
// match: _wintimer_noprof @ 0x0052F268
S32 wintimer_noprof = 1;
// match: _wintimer_radadj @ 0x0052F26C
S32 wintimer_radadj = 0;
#pragma data_seg()
extern U32 wintimer_lastrad;
extern U32 wintimer_lasttime;
extern S64 wintimer_qpfirst;
extern S64 wintimer_qpfreq;

// match: _RADTimerRead@0 @ 0x00344990
RADEXPFUNC U32 RADEXPLINK RADTimerRead(void)
{
  S64 now;
  U32 time;
  U32 rad;
  S32 diff;

  if (wintimer_noprof)
  {
    wintimer_noprof = 0;
    if (QueryPerformanceFrequency(&wintimer_qpfreq))
    {
      QueryPerformanceCounter(&wintimer_qpfirst);
      wintimer_lastrad = 0;
      wintimer_lasttime = GetTickCount();
      return 0;
    }
    wintimer_qpfreq = 0;
    return GetTickCount();
  }

  if (wintimer_qpfreq == 0)
    return GetTickCount();

  QueryPerformanceCounter(&now);
  time = GetTickCount();
  rad = (U32)((U64)((now - wintimer_qpfirst) * 1000) / (U64)wintimer_qpfreq) + wintimer_radadj;

  diff = time - wintimer_lasttime;
  {
    U32 elapsed = rad - wintimer_lastrad;

    if (abs(diff - elapsed) > 200)
    {
      diff -= elapsed;
      wintimer_radadj += diff;
      rad += diff;
    }
  }

  if ((rad - wintimer_lastrad) > 0xc0000000)
    return wintimer_lastrad;

  wintimer_lasttime = time;
  wintimer_lastrad = rad;
  return rad;
}
