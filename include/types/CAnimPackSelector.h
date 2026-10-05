/*
 * CAnimPackSelector: a RenderWare Studio behaviour, named by the class name
 * it registers with the class factory ("CAnimPackSelector", string
 * 0x3D59A4, passed with its MakeNew, sub_A0A50, by the initializer after
 * CAnimBankInfo's at 0x30A550). There is one (dword_4B67CC, set by its
 * constructor): two sets of six animation-pack names (keys) with their
 * text, and the pack to restart a group from ("SetRestartAnimGroup",
 * sub_A1130). Vtables: off_3D59C4 (CAttributeHandler part) and off_3D59BC
 * (CEventHandler part, at +0x18).
 */
#ifndef CANIMPACKSELECTOR_H
#define CANIMPACKSELECTOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/type_4B8EF0.h"
#include "types/type_72810.h"
#include "types/type_3DF8D8.h"

// A pack: its name's key and its text (sub_198900 fills the text).
struct CAnimPackSelector_pack
{
    type_3DF8D8_04 unk_00;
    RwChar unk_08[0x20];
};

class CAnimPackSelector : public RWS::CAttributeHandler, public RWS::CEventHandler,
                          public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CAnimPackSelector);
    RWS_DECLARE_CLASSID(CAnimPackSelector);

    CAnimPackSelector(const RWS::CAttributePacket &attr);
    ~CAnimPackSelector();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Clears both sets of packs.
    void sub_A0D40();
    // Sets the animation group arg_0 to restart from the key *arg_4
    // ("SetRestartAnimGroup").
    void sub_A1130(RwInt32 arg_0, type_3DF8D8_04 *arg_4);
    // The key group arg_0 restarts from, into *arg_4.
    void sub_A11A0(RwInt32 arg_0, type_3DF8D8_04 *arg_4);

    type_3DF8D8_04 unk_20;      // command 1's key
    CAnimPackSelector_pack unk_28[6];
    CAnimPackSelector_pack unk_118[6];
};
typedef RwChar CAnimPackSelector_size_check[sizeof(CAnimPackSelector) == 0x208 ? 1 : -1];

extern CAnimPackSelector *dword_4B67CC;
// The two messages it listens to: Id and dword_4B67C0 (rws/ceventhandler.h).
// What its HandleEvents calls between packs: sub_E9FB0 on dword_4B8EF0
// (with 4; types/type_4B8EF0.h) and sub_D9450; only the widths are known.
void sub_D9450();
// The callback sub_198900 calls for a pack's name (its text into arg_8).
struct type_3DFE94;
RwInt32 sub_195B70(type_3DFE94 *arg_0, RwInt32 arg_4, void *arg_8);

#endif
