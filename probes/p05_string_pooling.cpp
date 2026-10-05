// Probe 05: /GF. The "%d" literal must be a read-only pooled literal in
// .rdata (the original's lives at 0x003D51A4); without /GF VC7.1 puts literals
// in writable .data. Also a /GS 16-byte buffer, sprintf through the XDK's own
// <stdio.h>, and a thiscall with one stack argument (retn 4).
//
// match: sub_E0220 @ 0x000E0220

#include <stdio.h>

struct type_probe_E0220
{
    char unk_0000[0xC180];
    int unk_C180;

    void sub_E0220(int arg_0);
    void sub_E7380(int, char *);
    void sub_E3B50(int);
};

void type_probe_E0220::sub_E0220(int arg_0)
{
    char Buffer[16];

    if (unk_C180 != 0)
    {
        sprintf(Buffer, "%d", arg_0);
        sub_E7380(0x46, Buffer);
    }
    sub_E3B50(0x46);
}
