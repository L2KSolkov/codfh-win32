/*
 * WorldLight (the class name it registers with the class factory at
 * 0x30ADC9, with its MakeNew, sub_C5380, and its size, 0xE0): a trigger of
 * kind 3 derived from Trigger that owns a RenderWare light, anchored at its
 * vtables off_3D6AB8 and off_3D6AB0 (+0x18), which its constructor
 * (sub_C5400) and destructor (sub_C5570) install.
 */
#ifndef WORLDLIGHT_H
#define WORLDLIGHT_H

#include "rws/lighthelper.h"
#include "rw/ostypes.h"
#include "rw/rplight.h"
#include "types/type_129_base.h"
#include "types/type_44350.h"

class WorldLight : public Trigger
{
public:
    RWS_MAKENEWCLASS(WorldLight);
    RWS_DECLARE_CLASSID(WorldLight);

    WorldLight(const RWS::CAttributePacket &attr);
    ~WorldLight();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // Folded (/OPT:ICF) into CCESSPoolTrigger's (sub_A2BF0): it passes its
    // events to Trigger's.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (3).
    virtual RwInt32 vf_008();

    // Gives its light its colour, radius, cone angle and flags (the ambient
    // colour, dword_4E5C60, too for an ambient light), then sub_1739C0.
    void sub_C58F0();

    RwInt32 unk_C0;             // command 0: its light's type (RpLightType)
    RwReal unk_C4;              // command 1: its cone angle, in radians (pi/4)
    RwReal unk_C8;              // command 2: its radius (1000)
    RwInt32 unk_CC;             // command 3: its flags (RpLightFlag; 3)
    RwUInt32 unk_D0;            // command 4: its colour, 0xAARRGGBB (white)
    type_129BD0 unk_D4;         // its light
};
typedef RwChar WorldLight_size_check[sizeof(WorldLight) == 0xE0 ? 1 : -1];

// The ambient colour (an ambient WorldLight's).
#ifdef CODFH_PLAIN
extern RwRGBAReal &unk_4E5C60;
#else
extern RwRGBAReal unk_4E5C60;
#endif

// Adds the light arg_0 to the scene (an ambient one as the ambient light).
RwInt32 sub_173800(RpLight *arg_0);
// Updates the scene's lights.
void sub_1739C0();

#endif
