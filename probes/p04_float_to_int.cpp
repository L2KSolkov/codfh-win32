// Probe 04: float-to-int conversion. The original loads the int with fild,
// multiplies by the float and converts through __ftol2 — never cvttss2si.
//
// match: sub_FD980 @ 0x000FD980

struct type_probe_FD980
{
    char unk_0000[0x19DC];
    float unk_19DC;
    int unk_19E0;

    int sub_FD980();
};

int type_probe_FD980::sub_FD980()
{
    return (int)(unk_19E0 * unk_19DC);
}
