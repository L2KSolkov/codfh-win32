// match: ?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z @ 0x001FB5A0
// match: __ehhandler$?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z-0x10 @ 0x00304B70
// match: __ehhandler$?sub_1FB5A0@type_1FB520@@QAE_NABU1@@Z @ 0x00304B80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_1FB520::sub_1FB5A0(const type_1FB520 &arg_0)
{
    if (unk_40 && arg_0.unk_40)
    {
        switch (dword_5043AC)
        {
        case 0:
        {
            type_1A5EA0 q48(unk_40->unk_10);
            type_1A5EA0 stk_2C(arg_0.unk_40->unk_10);

            return q48 < stk_2C;
        }
        case 1:
            return unk_40->unk_28 < arg_0.unk_40->unk_28;
        case 2:
            return unk_40->unk_29 < arg_0.unk_40->unk_29;
        case 3:
            return unk_40->unk_2B < arg_0.unk_40->unk_2B;
        }
    }
    return unk_40 == 0;
}

// The library's string constructor from a C string, out of line here.
// match: ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@PBD@Z @ 0x001C5700

