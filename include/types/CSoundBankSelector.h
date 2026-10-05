/*
 * CSoundBankSelector (the class name it registers with the class factory at
 * 0x30AAF9, with its MakeNew, sub_B9110, and its size, 0x1C0): a RenderWare
 * Studio behaviour that picks the sound banks a level loads, anchored at its
 * vtables off_3D6560 and off_3D6558 (CEventHandler part, at +0x18), which
 * its constructor (sub_B9190) and destructor (sub_B93B0) install. It loads
 * them on the message Id (sub_B9800) and requests its second set again on
 * dword_4B67C0.
 */
#ifndef CSOUNDBANKSELECTOR_H
#define CSOUNDBANKSELECTOR_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/soundbank.h"

class CSoundBankSelector : public RWS::CAttributeHandler, public RWS::CEventHandler,
                           public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CSoundBankSelector);
    RWS_DECLARE_CLASSID(CSoundBankSelector);

    CSoundBankSelector(const RWS::CAttributePacket &attr);
    ~CSoundBankSelector();

    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Reads its banks from the list arg_0 (command 0): a count, then per
    // bank its id, four skipped words, its slot (0x63: the second set) and
    // its name part; then three pairs for dword_4B1C20 when there were any.
    void sub_B95B0(const RwUInt32 *arg_0);
    // Loads its first set of banks (the slots not already holding them).
    void sub_B9800();

    type_825E0 unk_20[0x10];    // the first set (the first six used)
    type_825E0 unk_120[0xA];    // the second set (also in dword_4B1B60)
};
typedef RwChar CSoundBankSelector_size_check[sizeof(CSoundBankSelector) == 0x1C0 ? 1 : -1];

// Also called between packs by CAnimPackSelector (declared there too); only
// its name is known.
void sub_D9450();

#endif
