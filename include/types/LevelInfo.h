/*
 * LevelInfo (the class name it registers with the class factory at
 * 0x30ADF6, with its MakeNew, sub_C5A60, and its size, 0x20): a RenderWare
 * Studio behaviour that sets the level's five settings (dword_4B686C to
 * dword_4B687C) from its commands, anchored at its vtables off_3D6B00 and
 * off_3D6AF8 (CEventHandler part, at +0x18), which its constructor
 * (sub_C5AE0) and destructor (sub_C5B90) install.
 */
#ifndef LEVELINFO_H
#define LEVELINFO_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"

class LevelInfo : public RWS::CAttributeHandler, public RWS::CEventHandler,
                  public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(LevelInfo);
    RWS_DECLARE_CLASSID(LevelInfo);

    LevelInfo(const RWS::CAttributePacket &attr);
    ~LevelInfo();

    // Empty, folded (/OPT:ICF) into sub_15FB30.
    virtual void HandleEvents(RWS::CMsg &pMsg)
    {
    }
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);

    // Clears the level's settings.
    static void sub_C5C10();
};
typedef RwChar LevelInfo_size_check[sizeof(LevelInfo) == 0x20 ? 1 : -1];

// The level's settings, LevelInfo's commands 0 to 4.
#ifdef CODFH_SP // reals in single player: SP 0x966E0 clears them with immediate stores
extern RwReal dword_4B686C;
extern RwReal dword_4B6870;
extern RwReal dword_4B6874;
extern RwReal dword_4B6878;
extern RwReal dword_4B687C;
#else
extern RwInt32 dword_4B686C;
extern RwInt32 dword_4B6870;
extern RwInt32 dword_4B6874;
extern RwInt32 dword_4B6878;
extern RwInt32 dword_4B687C;
#endif

#endif
