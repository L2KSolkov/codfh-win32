/*
 * cXboxLiveNetGame: cNetGame's Xbox side (0x18C bytes, its vtable
 * off_3E4FC0), named by its trace ("cXboxLiveNetGame::stateServerTakeUp
 * ..."); formerly type_1D5190. The multiplayer manager's set-up
 * (sub_1A9580) builds it. It runs the session through the network system
 * (sub_1D8810, game/voice.h): the host's session over Xbox Live or the
 * system link, the join with the server's address and keys, the peers'
 * user ids, and the link's watch.
 */
#ifndef CXBOXLIVENETGAME_H
#define CXBOXLIVENETGAME_H

#include <xtl.h>
#include <xonline.h>

#include "rw/ostypes.h"
#include "types/type_1CCA10.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_DC400.h"

// The join's server as the Xbox side keeps it (0x74 bytes): the common part
// and the server's address and session keys.
struct cXboxLiveNetGame_114 : type_1CC3C0
{
    type_1CCA10 unk_30;
    RwUInt8 unk_34[4];
    XNADDR unk_38;
    XNKID unk_5C;
    XNKEY unk_64;
};

struct cXboxLiveNetGame : type_4F8054
{
    RwInt32 unk_D0;             // set while a join's search runs (vf_070)
    XNADDR unk_D4;              // the server's address, id and key (vf_060)
    XNKID unk_F8;
    XNKEY unk_100;
    RwInt32 unk_110;
    cXboxLiveNetGame_114 unk_114;
    RwInt32 unk_188;            // set: vf_050 reports the link (unk_CC)

    cXboxLiveNetGame();
    virtual ~cXboxLiveNetGame();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C(const type_1CCA10 &arg_0);
    virtual const RwChar *vf_010();
    // Inline, their bodies shared with other classes' (/OPT:ICF).
    virtual RwInt32 vf_014(RwInt32 arg_0)
    {
        return 1;
    }
    virtual RwInt32 vf_018(RwInt32 arg_0)
    {
        return 1;
    }
    virtual RwInt32 vf_01C(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    virtual RwInt32 vf_020(RwInt32 arg_0, RwInt32 arg_4)
    {
        return 1;
    }
    virtual RwInt32 vf_024(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    virtual RwInt32 vf_028(RwInt32 arg_0)
    {
        return 0;
    }
    virtual void vf_02C(RwInt32 arg_0, RwInt32 arg_4)
    {
    }
    virtual void vf_030(RwInt32 arg_0)
    {
    }
    virtual void vf_034(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
    {
    }
    virtual void vf_038(RwInt32 arg_0, RwUInt8 *arg_4, RwInt32 arg_8);
    virtual RwInt32 vf_03C()
    {
        return 0;
    }
    virtual RwInt32 vf_040(RwInt32 arg_0)
    {
        return 0;
    }
    virtual void vf_044(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    virtual RwInt32 vf_048(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_04C(const type_1DDE20_mask &arg_0);
    virtual RwInt32 vf_050();
    virtual void vf_054(RwInt32 arg_0);
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual void vf_058(RwInt32 arg_0)
    {
        unk_188 = arg_0;
    }
    virtual void vf_05C(const type_1CC1F0 *arg_0);
    virtual void vf_060(const type_1CC1F0 *arg_0, const type_1CC3C0 *arg_4, RwInt32 arg_8);
    virtual void vf_068(RwInt32 arg_0);
    virtual void vf_070(const type_1CC1F0 *arg_0, const type_4F8054_4C *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    virtual RwInt32 vf_074();
    virtual RwInt32 vf_078(RwInt32 arg_0);
    virtual void vf_07C();
    virtual void vf_080(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_084(RwInt32 arg_0, RwInt32 arg_4);

    // The host's session being made (named by its trace) and the join's
    // state (sub_1D55A0), each step at the time arg_0; the other states'
    // steps are empty and out of line, folded (/OPT:ICF) into sub_15FB30.
    void stateServerTakeUp(const type_1CCA10 &arg_0);
    void sub_1D55A0(const type_1CCA10 &arg_0);
    void sub_15FB30(const type_1CCA10 &arg_0);
};
typedef RwChar cXboxLiveNetGame_size_check[sizeof(cXboxLiveNetGame) == 0x18C ? 1 : -1];
typedef RwChar cXboxLiveNetGame_114_size_check[sizeof(cXboxLiveNetGame_114) == 0x74 ? 1 : -1];

#endif
