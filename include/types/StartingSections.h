/*
 * StartingSections (the class name it registers with the class factory at
 * 0x30AA06, with its MakeNew, sub_B0410, and its size, 0x20): a RenderWare
 * Studio behaviour that sets the sections the game starts with (globals),
 * anchored at its vtables off_3D6430 and off_3D6428 (CEventHandler part, at
 * +0x18), which its constructor (sub_B0490) and destructor (sub_B0540)
 * install.
 */
#ifndef STARTINGSECTIONS_H
#define STARTINGSECTIONS_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class StartingSections : public RWS::CAttributeHandler, public RWS::CEventHandler,
                         public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(StartingSections);
    RWS_DECLARE_CLASSID(StartingSections);

    StartingSections(const RWS::CAttributePacket &attr);
    ~StartingSections()
    {
    }

    // Empty: folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Resets the settings to their defaults (0, and sections 1 to 4).
    static void sub_B05C0();
};
typedef RwChar StartingSections_size_check[sizeof(StartingSections) == 0x20 ? 1 : -1];

// The starting sections: a value (command 0) and two sets of four
// (commands 1, 3, 5, 7 and 2, 4, 6, 8).
extern RwInt32 dword_4B6850;
extern RwInt32 dword_4B6840[4];
extern RwInt32 dword_4B6830[4];

#endif
