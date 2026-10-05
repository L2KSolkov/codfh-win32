/*
 * cNetStaticCamTrigger: a RenderWare Studio behaviour, named by the class
 * name it registers with the class factory ("cNetStaticCamTrigger", with its
 * MakeNew, sub_1C2120, and size 0xD0, docs/behaviours.md). A Trigger that,
 * at the game's start, becomes the multiplayer manager's static camera
 * (unk_4F7EB8.unk_234, game/gameloop.h: its matrix is where the second
 * player's view goes, its four commands the starting level sections).
 * Vtables: off_3E33FC and off_3E33F4 (its CEventHandler part, at +0x18).
 */
#ifndef CNETSTATICCAMTRIGGER_H
#define CNETSTATICCAMTRIGGER_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "types/type_44350.h"

class cNetStaticCamTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(cNetStaticCamTrigger);
    RWS_DECLARE_CLASSID(cNetStaticCamTrigger);

    cNetStaticCamTrigger(const RWS::CAttributePacket &attr);
    ~cNetStaticCamTrigger();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_C0[4];          // commands 0 to 3: the starting level
                                // sections (type_1AFAF0)
};
typedef RwChar cNetStaticCamTrigger_size_check[sizeof(cNetStaticCamTrigger) == 0xD0 ? 1 : -1];

#endif
