/*
 * type_4E6F20: the clock and 1-D noise the camera sway's noises read
 * (unit_176B30, unk_4E6F20, constructed by the initializer at 0x30BED0).
 * The noise is Ken Perlin's noise1 (the tables' size 0x100, the offset
 * 0x1000); its tables are set up on the first call while dword_42A040
 * (.data, 1) is set.
 */
#ifndef TYPE_4E6F20_H
#define TYPE_4E6F20_H

#include "rw/ostypes.h"

struct type_4E6F20
{
    RwReal (*unk_00)();         // the clock (sub_176B30)

    type_4E6F20();
    // Inline and empty: its exit function (0x30E970) does nothing.
    ~type_4E6F20()
    {
    }
    RwReal sub_176B80(RwReal arg_0);
    RwReal sub_176C40();
    void sub_176C50();
};
extern type_4E6F20 unk_4E6F20;

// The clock: the frame count (dword_4B87D8) in seconds.
RwReal sub_176B30();

// The noise's tables (.bss) and its set-up flag (.data).
extern RwReal dword_4E5F10[0x202];
extern RwInt32 dword_4E6718[0x202];
extern RwInt32 dword_42A040;

#endif
