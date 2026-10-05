/*
 * cNetLevelParams: a RenderWare Studio behaviour, named by the class name it
 * registers with the class factory ("cNetLevelParams", with its MakeNew,
 * sub_1B6FE0, and size 0xD8, docs/behaviours.md). A level's network
 * settings: per team (2 and 4) a count, two keys and five spawn keys. At the
 * system's start it looks each spawn key up (sub_15CB40) and starts its
 * settings (sub_15CAC0). The multiplayer manager keeps it at unk_280
 * (dword_4F8138 holds the last one built). Vtables: off_3E24B8
 * (CAttributeHandler part) and off_3E24B0 (CEventHandler part, at +0x18).
 */
#ifndef CNETLEVELPARAMS_H
#define CNETLEVELPARAMS_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/type_3DF8D8.h"

struct type_1B7910;

class cNetLevelParams : public RWS::CAttributeHandler, public RWS::CEventHandler,
                        public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(cNetLevelParams);
    RWS_DECLARE_CLASSID(cNetLevelParams);

    cNetLevelParams(const RWS::CAttributePacket &attr);
    ~cNetLevelParams();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Team arg_0's count (4, else 2), its two keys, the key of its spawn
    // arg_4, and that spawn's settings' index (the respawn, sub_1AED80).
    RwInt32 sub_1B78E0(RwInt32 arg_0);
    type_1B7910 *sub_1B7910(RwUInt32 arg_0);
    type_1B7910 *sub_1B7940(RwUInt32 arg_0);
    type_1B7910 *sub_1B7970(RwUInt32 arg_0, RwUInt32 arg_4);
    RwInt32 sub_1B79A0(RwUInt32 arg_0, RwInt32 arg_4);

    RwInt32 unk_20;             // commands 0 and 1: team 4's and team 2's
    RwInt32 unk_24;             // counts
    type_3DF8D8_04 unk_28;      // commands 2 to 5: the teams' keys
    type_3DF8D8_04 unk_30;
    type_3DF8D8_04 unk_38;
    type_3DF8D8_04 unk_40;
    type_3DF8D8_04 unk_48[5];   // commands 6 to 15: team 4's and team 2's
    type_3DF8D8_04 unk_70[5];   // spawn keys
    RwInt32 unk_98[5];          // their settings' indices (-1 for none)
    RwInt32 unk_AC[5];
    type_3DF8D8_04 unk_C0[2];   // commands 16 and 17
    RwInt32 unk_D0[2];
};
typedef RwChar cNetLevelParams_size_check[sizeof(cNetLevelParams) == 0xD8 ? 1 : -1];

// The last one built.
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern cNetLevelParams *&dword_4F8138;
#else
extern cNetLevelParams *dword_4F8138;
#endif

#endif
