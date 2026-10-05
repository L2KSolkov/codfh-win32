/*
 * CDebugScript: a RenderWare Studio behaviour, named by the class name it
 * registers with the class factory ("CDebugScript", string 0x3CE958, passed
 * to RWS::CClassFactory::CRegistrar at 0x309910 with its MakeNew, sub_42F40,
 * and its size, 0x24). Its commands set the message system's debug settings
 * (dword_44928C and on, read by sub_67B10, sub_6A970 and sub_6B060).
 * Vtables: off_3CE970 (CAttributeHandler part) and off_3CE968 (CEventHandler
 * part, at +0x18); its HandleEvents is empty (sub_15FB30, folded).
 *
 *   +0x20 unk_20  command 11's value
 */
#ifndef CDEBUGSCRIPT_H
#define CDEBUGSCRIPT_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CDebugScript : public RWS::CAttributeHandler, public RWS::CEventHandler,
                     public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CDebugScript);
    RWS_DECLARE_CLASSID(CDebugScript);

    CDebugScript(const RWS::CAttributePacket &attr);
    ~CDebugScript();

    virtual void HandleEvents(RWS::CMsg &pMsg)
    {
    }
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;
};
typedef RwChar CDebugScript_size_check[sizeof(CDebugScript) == 0x24 ? 1 : -1];

#endif
