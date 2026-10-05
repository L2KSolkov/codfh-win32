/*
 * CAnimBankInfo: a RenderWare Studio behaviour, named by the class name it
 * registers with the class factory ("CAnimBankInfo", string 0x3D5984,
 * passed with its MakeNew, sub_A02D0, by the initializer at 0x30A510). It
 * holds the animation heap's sizes and hands them to the animation banks
 * (sub_770F0, "ANIMATION HEAP SIZE ALLOCATION") once the system starts.
 * Vtables: off_3D599C (CAttributeHandler part) and off_3D5994
 * (CEventHandler part, at +0x18).
 *
 *   +0x20 unk_20  six sizes, 1 MB each by default
 *   +0x38 unk_38  six sizes, 1 MB each (the ones sub_770F0 gets)
 *   +0x50 unk_50  six sizes, 64 KB each
 */
#ifndef CANIMBANKINFO_H
#define CANIMBANKINFO_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class CAnimBankInfo : public RWS::CAttributeHandler, public RWS::CEventHandler,
                      public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CAnimBankInfo);
    RWS_DECLARE_CLASSID(CAnimBankInfo);

    CAnimBankInfo(const RWS::CAttributePacket &attr);
    ~CAnimBankInfo();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // arg_0 rounded up to a multiple of 4.
    RwUInt32 sub_A0530(RwUInt32 arg_0);
    // The sizes handed to the animation banks.
    RwUInt32 *sub_A0A20();

    RwUInt32 unk_20[6];
    RwUInt32 unk_38[6];
    RwUInt32 unk_50[6];
};
typedef RwChar CAnimBankInfo_size_check[sizeof(CAnimBankInfo) == 0x68 ? 1 : -1];

#endif
