/*
 * CShellLevelBehaviorClass (the class name it registers with the class
 * factory at 0x30AA66, with its MakeNew, sub_B6EB0, and its size, 0x20): a
 * RenderWare Studio behaviour that sets a level's front-end (shell)
 * settings, anchored at its vtables off_3D649C and off_3D6494 (CEventHandler
 * part, at +0x18), which its constructor (sub_B6F30) and destructor
 * (sub_B6FE0) install.
 */
#ifndef CSHELLLEVELBEHAVIORCLASS_H
#define CSHELLLEVELBEHAVIORCLASS_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/type_44350.h"

class CShellLevelBehaviorClass : public RWS::CAttributeHandler, public RWS::CEventHandler,
                                 public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CShellLevelBehaviorClass);
    RWS_DECLARE_CLASSID(CShellLevelBehaviorClass);

    CShellLevelBehaviorClass(const RWS::CAttributePacket &attr);
    ~CShellLevelBehaviorClass()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};
typedef RwChar CShellLevelBehaviorClass_size_check[sizeof(CShellLevelBehaviorClass) == 0x20 ? 1 : -1];

// A level setting (command 8).
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B918C;
#else
extern RwInt32 dword_4B918C;
#endif
// Take the names (keys) commands 6 and 7 give (registered with the kind
// 0x3B); only the widths are known.
void sub_E8DB0(Trigger_key *arg_0);
void sub_E8E30(Trigger_key *arg_0);

#endif
