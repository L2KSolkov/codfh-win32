// Frees its data and entries (the data's check comes twice: once more after
// the entries).
// match: ??1type_ECDA0@@QAE@XZ @ 0x000EC6D0
type_ECDA0::~type_ECDA0()
{
    if (unk_08)
    {
        dword_520218(unk_08);
        unk_08 = 0;
    }
    if (unk_04)
    {
        dword_520218(unk_04);
        unk_04 = 0;
        unk_00 = 0;
    }
    if (unk_08)
    {
        dword_520218(unk_08);
        unk_08 = 0;
    }
}

