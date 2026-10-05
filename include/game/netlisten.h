/*
 * The network game's listeners (types/type_DC400.h, cNetGame's unk_A0 to
 * unk_A8): their own header so the multiplayer manager (game/gameloop.h),
 * the third, can derive from it.
 */
#ifndef GAME_NETLISTEN_H
#define GAME_NETLISTEN_H

#include "rw/ostypes.h"

// The network game's listeners: told of a peer (slot 0, six arguments,
// the last two 1 for joining and 0 for leaving) and of a message (five
// arguments). Only the widths are known. Their own methods are empty and
// inline (the vtables off_3E66D0 and off_3E66B8 hold them: 0xF7B90 and
// 0x1DE440, folded by /OPT:ICF).
struct type_4F8054_A0
{
    virtual void vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                        RwInt32 arg_14)
    {
    }
};
struct type_4F8054_A4
{
    virtual void vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
    {
    }
};
// The network game's third listener, which the multiplayer manager is: told
// of a peer joining and leaving, and when joining fails. Its own methods
// are empty and inline (their instances folded by /OPT:ICF into sub_15FB30
// and pDtor, 0x1E41C0); its vtable is off_3E13F4, which its inline
// constructor installs.
struct type_4F8054_A8
{
    // Peer arg_0 has joined (the server's join step).
    virtual void vf_000(RwInt32 arg_0)
    {
    }
    // Peer arg_0 has left (the players' sub_1CFC20).
    virtual void vf_004(RwInt32 arg_0)
    {
    }
    virtual void vf_008()
    {
    }
};

#endif
