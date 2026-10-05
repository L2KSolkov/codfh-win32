// Probe 02: /GS. The 0x1C-byte local holds an array, so the compiler loads
// __security_cookie into [ebp-4] and checks it through ecx before returning.
//
// match: sub_72990 @ 0x00072990

struct type_probe_72990_local
{
    int unk_00;
    int unk_04;
    char unk_08[0x14];
};

struct type_449B0C
{
    void sub_67970(type_probe_72990_local *);
};

extern type_449B0C dword_449B0C;

void sub_72990(int arg_0)
{
    type_probe_72990_local local;
    local.unk_04 = arg_0;
    dword_449B0C.sub_67970(&local);
}
