// Probe 01: an empty __thiscall member with three stack arguments.
// The original spills ecx to the frame and returns with retn 0Ch.
//
// match: sub_73D80 @ 0x00073D80

struct type_probe_73D80
{
    void sub_73D80(int, int, int);
};

void type_probe_73D80::sub_73D80(int, int, int)
{
}
