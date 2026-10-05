/*
 * CShellBehaviorClass (the class name it registers with the class factory at
 * 0x30AA36, with its MakeNew, sub_B07D0, and its size, 0x20): a RenderWare
 * Studio behaviour that sets the front end's (shell's) settings, anchored at
 * its vtables off_3D6460 and off_3D6458 (CEventHandler part, at +0x18), which
 * its constructor (sub_B0850) and destructor (sub_B0900) install. Its
 * HandleAttributes (sub_B0980, 242 commands) sets the HUD's and the front
 * end's settings (type_DC400.h) and the difficulty and damage multipliers.
 */
#ifndef CSHELLBEHAVIORCLASS_H
#define CSHELLBEHAVIORCLASS_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CShellBehaviorClass : public RWS::CAttributeHandler, public RWS::CEventHandler,
                            public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CShellBehaviorClass);
    RWS_DECLARE_CLASSID(CShellBehaviorClass);

    CShellBehaviorClass(const RWS::CAttributePacket &attr);
    ~CShellBehaviorClass()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};
typedef RwChar CShellBehaviorClass_size_check[sizeof(CShellBehaviorClass) == 0x20 ? 1 : -1];

#endif
