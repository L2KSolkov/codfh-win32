/*
 * PulseZoneTrigger (the class name it registers with the class factory at
 * 0x30B039, with its MakeNew, sub_CB430, and its size, 0xF0): a trigger of
 * kind 0x22 derived from Trigger that owns a pulse zone (a type_17DB90, as
 * the scripts see it through type_4CFE30), anchored at its vtables
 * off_3D6DE8 and off_3D6DE0 (+0x18), which its constructor (sub_CB4B0) and
 * destructor (sub_CB5E0) install.
 */
#ifndef PULSEZONETRIGGER_H
#define PULSEZONETRIGGER_H

#include "rw/ostypes.h"
#include "game/data.h"
#include "types/type_44350.h"
#include "types/type_17DB90.h"
#include "types/alfasched.h"

class PulseZoneTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(PulseZoneTrigger);
    RWS_DECLARE_CLASSID(PulseZoneTrigger);

    PulseZoneTrigger(const RWS::CAttributePacket &attr);
    ~PulseZoneTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    // On dword_4B67B0 and dword_4B8750 it makes its zone (sub_17E3A0) and,
    // with unk_E0 set, starts it with its particle system.
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (0x22), folded (/OPT:ICF) into sub_193FA0.
    virtual RwInt32 vf_008();

    // Pass arg_0 on to its zone (type_17DB90's sub_17D940 and sub_17DA20),
    // when it has one.
    void sub_CB960(RwInt32 arg_0);
    void sub_CB990(RwInt32 arg_0);

    RwInt32 unk_C0;             // command 1
    RwInt32 unk_C4;             // command 0
    RwInt32 unk_C8;             // command 2 (-1)
    RwReal unk_CC;              // command 3, times 60 (60)
    RwInt32 unk_D0;             // command 4
    RwInt32 unk_D4;             // command 5
    type_17DB90 *unk_D8;        // its zone
    RwInt32 unk_DC;             // command 7: its particle system, by name
    RwInt32 unk_E0;             // command 6: set to start it at once
    RwUInt8 unk_E4[0xC];
};
typedef RwChar PulseZoneTrigger_size_check[sizeof(PulseZoneTrigger) == 0xF0 ? 1 : -1];

// A zone's handle, returned by value: its slot in dword_4E7268 and a serial
// (dword_4E7370 when it was made), so a stale handle finds nothing.
struct type_17E3A0
{
    union
    {
        RwUInt32 unk_00;
        struct
        {
            RwUInt16 unk_00_w;  // its slot (1 to 32)
            RwUInt16 unk_02_w;  // its serial
        };
    };
};
// A slot of the zones' handle table: the handle it was given and its zone.
struct type_4E7268
{
    type_17E3A0 unk_00;
    type_17DB90 *unk_04;
};
// The zones' handle table (slot 0 unused), the next serial, the zones (linked
// through unk_50) and their pool ("m_freePulseZoneList", 32 of 0xD0 bytes).
extern type_4E7268 dword_4E7268[33];
extern RwInt32 dword_4E7370;
extern type_17DB90 *dword_4E7374;
extern type_16C2A0 dword_4E7378;
// Drops the zone arg_0: out of the list, its handle freed, back to the pool.
void sub_17E470(type_17DB90 *arg_0);
// Drops every zone.
void sub_17E510();
// A handle for the zone arg_0 (a type_17E3A0's value; unset when the table
// is full).
RwInt32 sub_17E560(type_17DB90 *arg_0);
// Frees the handle arg_0's slot.
void sub_17E620(type_17E3A0 arg_0);
inline type_17E3A0 type_17DB90::get_unk_B0()
{
    return *(type_17E3A0 *)&unk_B0;
}
// Makes a zone for the trigger arg_0; its handle.
type_17E3A0 sub_17E3A0(Trigger *arg_0);
// The zone with the handle arg_0 (0 when stale).
type_17DB90 *sub_17E650(type_17E3A0 arg_0);

#endif
