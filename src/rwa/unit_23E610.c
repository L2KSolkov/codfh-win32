/*
 * codfh-match: RenderWare Audio's clock (sub_23E610: milliseconds elapsed into dword_5069F8)
 * and the allocation cursor callback (sub_23E680). Split from rwabase.c at an original object
 * boundary: in one unit VC7.0 emits RwaCoreUpdateStart, which calls the clock defined later,
 * and RwaCoreUpdate at the unit's end, where the image has them in place (docs/units.md; PLAN M7).
 */

#include "rwa.h"
#include "rwaint.h"

extern RwUInt32 dword_5069F8;

extern RwUInt32 dword_5069FC;

// match: _sub_23E610 @ 0x0023E610
// sp-match: _sub_23E610 @ 0x00150600
void
sub_23E610(void)
{
    RwUInt32    now = sub_244940();
    RwUInt32    frequency = sub_244960();
    RwUInt32    elapsed = now - dword_5069FC;

    if (now < dword_5069FC)
    {
        elapsed--;
    }

    dword_5069F8 += (RwInt32)((RwReal)elapsed / (RwReal)frequency * 1000.0f);
    dword_5069FC = now;
}
/* Allocation cursor callback: installed at 0x23E727, forwarded by
 * sub_23F9F0 to sub_243FF0; 0x244073-0x244082 uses its return as
 * allocated interface storage. EAX preserves the previous cursor. */
// match: _sub_23E680 @ 0x0023E680
// sp-match: _sub_23E680 @ 0x00150670
void *
sub_23E680(RwUInt32 amount, void *data)
{
    RwUInt8 **cursor = (RwUInt8 **)data;
    RwUInt8 *prior = *cursor;
    *cursor = prior + amount;
    return prior;
}
