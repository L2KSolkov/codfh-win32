/*
 * SectionInfo (the class name it registers with the class factory at
 * 0x30A9A6, with its MakeNew, sub_AFBC0, and its size, 0x20): a RenderWare
 * Studio behaviour that sets the three sections' memory settings (globals),
 * anchored at its vtables off_3D63C4 and off_3D63BC (CEventHandler part, at
 * +0x18), which its constructor (sub_AFC40) and destructor (sub_AFCF0)
 * install.
 */
#ifndef SECTIONINFO_H
#define SECTIONINFO_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class SectionInfo : public RWS::CAttributeHandler, public RWS::CEventHandler,
                    public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(SectionInfo);
    RWS_DECLARE_CLASSID(SectionInfo);

    SectionInfo(const RWS::CAttributePacket &attr);
    ~SectionInfo()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Resets the settings to their defaults.
    static void sub_AFD70();
    // The second section's flag, the first's sizes and the second's value.
    static RwInt32 sub_B0140();
    static RwUInt32 *sub_B0150();
    static RwReal sub_B0160();
};
typedef RwChar SectionInfo_size_check[sizeof(SectionInfo) == 0x20 ? 1 : -1];

// The settings, per section: a value (8, 8 and 4 by default; a second 10 is
// read as 8), a flag and four sizes.
extern RwReal flt_42918C;
extern RwReal flt_429190;
extern RwReal flt_429194;
extern RwInt32 dword_4B6820;
extern RwInt32 dword_4B6824;
extern RwInt32 dword_4B6828;
extern RwUInt32 dword_4B67F0[4];
extern RwUInt32 dword_4B6800[4];
extern RwUInt32 dword_4B6810[4];

#endif
