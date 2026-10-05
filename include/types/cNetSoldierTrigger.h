/*
 * cNetSoldierTrigger: a RenderWare Studio behaviour, named by the class name
 * it registers with the class factory ("cNetSoldierTrigger", with its
 * MakeNew, sub_1C06E0, and size 0x1A0, docs/behaviours.md). A SoldierTrigger
 * for network games: its soldier is a remote player (sub_1BEBB0), while the
 * third animation pool has players free. The last one built is kept in
 * dword_4F8134. Vtables: off_3E32C8 and off_3E32C0 (its CEventHandler part,
 * at +0x18).
 */
#ifndef CNETSOLDIERTRIGGER_H
#define CNETSOLDIERTRIGGER_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "types/SoldierTrigger.h"

class cNetSoldierTrigger : public SoldierTrigger
{
public:
    RWS_MAKENEWCLASS(cNetSoldierTrigger);
    RWS_DECLARE_CLASSID(cNetSoldierTrigger);

    cNetSoldierTrigger(const RWS::CAttributePacket &attr);
    // No destructor of its own: the compiler's (sub_1C07C0) calls
    // SoldierTrigger's.

    // Its soldier: a remote player (sub_1BEBB0).
    virtual type_3D3548 *vf_020();
};
typedef RwChar cNetSoldierTrigger_size_check[sizeof(cNetSoldierTrigger) == 0x1A0 ? 1 : -1];

// The last one built.
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern cNetSoldierTrigger *&dword_4F8134;
#else
extern cNetSoldierTrigger *dword_4F8134;
#endif

#endif
