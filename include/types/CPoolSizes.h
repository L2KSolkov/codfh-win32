/*
 * CPoolSizes (the class name it registers with the class factory at
 * 0x30AF76, with its MakeNew, sub_CA2C0, and its size, 0x44): a RenderWare
 * Studio behaviour that sizes the object pools, anchored at its vtables
 * off_3D6CF0 and off_3D6CE8 (CEventHandler part, at +0x18), which its
 * constructor (sub_CA340) and destructor (sub_CA490) install. On
 * iMsgStartSystem it passes its nine sizes (unk_20 on) to sub_D5320.
 */
#ifndef CPOOLSIZES_H
#define CPOOLSIZES_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CPoolSizes : public RWS::CAttributeHandler, public RWS::CEventHandler,
                   public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CPoolSizes);
    RWS_DECLARE_CLASSID(CPoolSizes);

    CPoolSizes(const RWS::CAttributePacket &attr);
    ~CPoolSizes();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    RwInt32 unk_20;             // command 0 (25)
    RwInt32 unk_24;             // command 1 (30)
    RwInt32 unk_28;             // command 2 (30)
    RwInt32 unk_2C;             // command 4 (5)
    RwInt32 unk_30;             // command 3 (0)
    RwInt32 unk_34;             // command 5 (1)
    RwUInt32 unk_38;            // command 7 (15, at most 33)
    RwInt32 unk_3C;             // command 6 (10)
    RwInt32 unk_40;             // command 8 (30)
};
typedef RwChar CPoolSizes_size_check[sizeof(CPoolSizes) == 0x44 ? 1 : -1];

// Sets the pools up from the nine sizes at arg_0 (CPoolSizes' unk_20 on).
void sub_D5320(RwInt32 *arg_0);

#endif
