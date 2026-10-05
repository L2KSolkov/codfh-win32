/*
 * codfh-match: RenderWare Audio's timer (rwatimer.h in the library's PS2
 * header): the time stamp counter's frequency, the timer start and the
 * ticks since it, with the 32-bit wrap. The counter reads (0x244930,
 * 0x244940) are the original's inline assembly (rdtsc).
 */
#include "rwa.h"
#include "rwaint.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00507178
RwUInt64 qword_507178;
// End of its data definitions.


extern RwUInt32 sub_244980(void);

/* The counter at the timer start (.bss). */
extern RwUInt64 qword_507178;

// match: _sub_244930 @ 0x00244930
void
sub_244930(void)
{
    // begin original __asm (rdtsc into the start count: the image's code)
    __asm
    {
        rdtsc
        lea ebx, qword_507178
        mov [ebx], eax
        mov [ebx + 4], edx
    }
    // end original __asm
}

// match: _sub_244940 @ 0x00244940
RwUInt32
sub_244940(void)
{
    RwUInt64 now;

    // begin original __asm (rdtsc into a local: the image's code)
    __asm
    {
        rdtsc
        lea ebx, now
        mov [ebx], eax
        mov [ebx + 4], edx
    }
    // end original __asm
    return (RwUInt32)now;
}

// match: _sub_244960 @ 0x00244960
RwUInt32
sub_244960(void)
{
    return 733333333;
}

// match: _sub_244970 @ 0x00244970
RwBool
sub_244970(void)
{
    sub_244930();

    return TRUE;
}

// match: _sub_2449B0 @ 0x002449B0
RwUInt32
sub_2449B0(void)
{
    return sub_244980();
}

/* The UInt64 start is masked before comparison and arithmetic, as also
 * seen in Studio's rwad.dll RwaTimerStop at 0x1007E4B1. */
// match: _sub_244980 @ 0x00244980
RwUInt32
sub_244980(void)
{
    RwUInt32 elapsed = sub_244940();

    if (elapsed < (qword_507178 & 0xFFFFFFFF))
    {
        elapsed += 0xFFFFFFFF - (qword_507178 & 0xFFFFFFFF);
    }
    else
    {
        elapsed -= qword_507178 & 0xFFFFFFFF;
    }
    return elapsed;
}
