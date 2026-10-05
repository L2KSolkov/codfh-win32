/*
 * CGlobalSounds (the class name it registers with the class factory at
 * 0x30AF46, with its MakeNew, sub_C7CE0, and its size, 0x20): a RenderWare
 * Studio behaviour that sets the sound system's global settings (sound keys,
 * voice counts, volumes and rates) from its commands, anchored at its
 * vtables off_3D6CD4 and off_3D6CCC (CEventHandler part, at +0x18), which
 * its constructor (sub_C7D60) and destructor (sub_C7EA0) install.
 */
#ifndef CGLOBALSOUNDS_H
#define CGLOBALSOUNDS_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/ceventhandler.h"
#include "rws/linearallocationpolicy.h"
#include "types/type_3DF8D8.h"

class CGlobalSounds : public RWS::CAttributeHandler, public RWS::CEventHandler,
                      public RWS::LinearAllocationPolicy
{
public:
    RWS_MAKENEWCLASS(CGlobalSounds);
    RWS_DECLARE_CLASSID(CGlobalSounds);

    CGlobalSounds(const RWS::CAttributePacket &attr);
    ~CGlobalSounds();

    // On Id (once) and dword_4B67C0 it applies the settings (sub_83B20).
    virtual void HandleEvents(RWS::CMsg &pMsg);
    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
};
typedef RwChar CGlobalSounds_size_check[sizeof(CGlobalSounds) == 0x20 ? 1 : -1];

// The settings CGlobalSounds' commands set: sound keys, counts and rates.
// flt_44D490, flt_44E814 and dword_4B1F24 each begin three by stance, the
// player's footsteps' intervals, volumes and keys (type_10F710::sub_10C370
// indexes them).
extern RwReal flt_44D490;
extern RwReal flt_44D494;
extern RwReal flt_44D498;
extern RwInt32 dword_44D4D4;
extern RwReal flt_44E814;
extern RwReal flt_44E818;
extern RwReal flt_44E81C;
extern RwInt32 dword_44E83C;
extern type_3DF8D8_04 dword_4AEFEC;
extern type_3DF8D8_04 dword_4AEFF8;
extern type_3DF8D8_04 dword_4AF000;
extern type_3DF8D8_04 dword_4AF008;
extern type_3DF8D8_04 dword_4AF010;
extern type_3DF8D8_04 dword_4AF018;
extern type_3DF8D8_04 dword_4AF020;
extern type_3DF8D8_04 dword_4AF028;
extern type_3DF8D8_04 dword_4AF030;
extern type_3DF8D8_04 dword_4B1A18;
extern type_3DF8D8_04 dword_4B1B10;
extern type_3DF8D8_04 dword_4B1B18;
extern type_3DF8D8_04 dword_4B1B20;
extern type_3DF8D8_04 dword_4B1B28;
extern type_3DF8D8_04 dword_4B1B30;
extern type_3DF8D8_04 dword_4B1B38;
extern type_3DF8D8_04 dword_4B1B40;
extern type_3DF8D8_04 dword_4B1B48;
extern type_3DF8D8_04 dword_4B1B50;
extern type_3DF8D8_04 dword_4B1B58;
extern type_3DF8D8_04 dword_4B1C00;
extern type_3DF8D8_04 dword_4B1C10;
extern type_3DF8D8_04 dword_4B1C18;
extern type_3DF8D8_04 dword_4B1C38;
extern type_3DF8D8_04 dword_4B1C40;
extern type_3DF8D8_04 dword_4B1C48;
extern type_3DF8D8_04 dword_4B1C50;
extern type_3DF8D8_04 dword_4B1C58;
extern type_3DF8D8_04 dword_4B1C60[3];   // three, by stance (unit_155470 indexes it; the initializer builds three)
struct type_3DF8D8_04_data;
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B1C68;
#else
extern type_3DF8D8_04_data dword_4B1C68;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B1C70;
#else
extern type_3DF8D8_04_data dword_4B1C70;
#endif
extern type_3DF8D8_04 dword_4B1C78;
extern type_3DF8D8_04 dword_4B1C80;
extern type_3DF8D8_04 dword_4B1C88;
extern type_3DF8D8_04 dword_4B1C90;
extern type_3DF8D8_04 dword_4B1C98;
extern type_3DF8D8_04 dword_4B1E80;
extern type_3DF8D8_04 dword_4B1E88;
extern type_3DF8D8_04 dword_4B1E90;
extern type_3DF8D8_04 dword_4B1F1C;
extern type_3DF8D8_04 dword_4B1F24[3];   // three, by stance (the initializer builds three)
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B1F2C;
#else
extern type_3DF8D8_04_data dword_4B1F2C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &dword_4B1F34;
#else
extern type_3DF8D8_04_data dword_4B1F34;
#endif
extern type_3DF8D8_04 dword_4B1F3C;
extern type_3DF8D8_04 dword_4B1F44;
extern type_3DF8D8_04 dword_4B1F4C;

#endif
