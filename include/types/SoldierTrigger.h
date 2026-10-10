/*
 * SoldierTrigger (the class name it registers with the class factory at
 * 0x30AAC9, with its MakeNew, sub_B7AA0, and its size, 0x1A0): the soldier
 * spawner, a trigger of kind 5 derived from Trigger, anchored at its
 * vtables off_3D6510 and off_3D6508 (+0x18), which its constructor
 * (sub_B7B20) and destructor (sub_B7F50) install. Its constant functions
 * (0xA17A0 to 0xA17F0) are placed after AnimTestTrigger's constructor, the
 * first object to use them, and are recovered there.
 */
#ifndef SOLDIERTRIGGER_H
#define SOLDIERTRIGGER_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/type_D48D0.h"

struct type_3D2E7C;

// A soldier's definition, the object of kind 4 sub_198800 finds by its name:
// sub_1917A0 and sub_1917F0 give its model's objects (warning when the clump
// cannot be found); unk_44 is its weapon class.
// A model object (what a soldier's definition's sub_1917A0, sub_1917F0 and
// sub_191840 give), named after its method sub_1908A0: its key arg_0 (0 to
// 3; 0 for others).
struct type_1908A0 : type_3DF8D8
{
    RwUInt8 unk_20[0x34];
    RwInt32 unk_54;             // its render part state (sub_16E080)

    type_3DF8D8_04 *sub_1908A0(RwInt32 arg_0);
    // An inline accessor for unk_54, with no address and so no database
    // name; named for its field. Evidence: the soldier's set-up
    // (type_3DAFC8::sub_135430) copies it through a local of the inline's
    // after a copy of the call result it is read from.
    RwInt32 get_unk_54()
    {
        RwInt32 r = unk_54;
        return r;
    }
};

// A model record in a soldier's definition (at +0x10 and +0x28), named after
// its place: its model's key and its render part state.
struct type_1917A0_10
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;      // the model object's key (sub_18F830)
    RwInt32 unk_0C;             // its render part state (sub_16E080)
};

struct type_1917A0 : type_3DF8D8
{
    type_3DF8D8_04 unk_20;
    type_1917A0_10 unk_28;      // its head (the body's record is at +0x10,
                                // over the base's fields)
    RwUInt8 unk_38[0xC];
    RwInt32 unk_44;

    // The clump of the record arg_0's model object, or 0 (the set-up passes
    // its body's and head's records); only the widths are known.
    RpClump *sub_18F830(type_1917A0_10 *arg_0);
    // An inline accessor for the head record's render part state, with no
    // address and so no database name; named for its offset. Evidence: the
    // soldier's set-up copies it through a local of the inline's.
    RwInt32 get_unk_34()
    {
        RwInt32 r = unk_28.unk_0C;
        return r;
    }

    type_1908A0 *sub_1917A0();
    type_1908A0 *sub_1917F0();
    // unk_44 with no result local: an inline with no address and so no
    // database name, named for its field. Evidence: the gimp's set-up
    // switches on it through a temporary that first copies an uninitialised
    // slot (the inline's return slot).
    RwInt32 get_unk_44()
    {
        return unk_44;
    }
    // A third model object, or 0 (type_3DAFC8::vf_058).
    type_1908A0 *sub_191840();
};

class SoldierTrigger : public Trigger
{
public:
    RWS_MAKENEWCLASS(SoldierTrigger);
    RWS_DECLARE_CLASSID(SoldierTrigger);

    SoldierTrigger(const RWS::CAttributePacket &attr);
    ~SoldierTrigger();

    virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    virtual void HandleEvents(RWS::CMsg &pMsg);
    // Its kind (5), the most soldiers it may spawn (unk_15C), its key
    // (&unk_D0) and its CCESS slot (unk_164).
    // Inline: the constructor's vtable emits them after it, before ??_G (the image's order).
    virtual RwInt32 vf_008()
    {
        return 5;
    }
    virtual RwInt32 vf_00C()
    {
        return unk_15C;
    }
    virtual type_3DF8D8_04 * vf_01C()
    {
        return &unk_D0;
    }
    virtual RwInt32 vf_024()
    {
        return unk_164;
    }
    // Adds arg_4 to (arg_0 set) or sets (arg_0 0) the number it may spawn,
    // unk_15C (0x7FFFFFFF: no limit).
    virtual void vf_010(RwInt32 arg_0, RwInt32 arg_4);
    // unk_100 (folded, /OPT:ICF, into another class's accessor, sub_1C9090).
    virtual RwInt32 vf_014();
    // Its CCESS tracker's kind, by its soldier's weapon class: 1, 2 or 4.
    virtual RwInt32 vf_018();
    // Its soldier (sub_134B40), when its definition is known and the third
    // animation pool has players free or its unk_24_18 is set.
    virtual type_3D3548 *vf_020();

    // Posts the messages of its block (unk_198) to arg_0, up to the first
    // unused one (as DogTrigger's sub_A48B0).
    void sub_B8F80(type_3D2E7C *arg_0);

    RwUInt8 unk_C0[0x6];        // the last two set; command 25's value at +2
    RwInt16 unk_C6[0x5];        // -1; commands 26 to 28 set the first three
    type_3DF8D8_04 unk_D0;      // command 0, a name of the kind 0x2E
    type_3DF8D8_04 unk_D8;      // command 3: its definition's name (kind 4)
    type_3DF8D8_04 unk_E0;      // command 7, of the kind 0xA
    type_3DF8D8_04 unk_E8;      // command 8 when set, of the kind 0xC
    type_3DF8D8_04 unk_F0;      // command 37
    type_3DF8D8_04 unk_F8;      // command 15, when set
    RwInt32 unk_100;            // command 12
    RwReal unk_104;             // commands 16 and 17: the cosines of half
    RwReal unk_108;             // their angles (in degrees)
    RwReal unk_10C;             // commands 18, 19 and 21, times 100
    RwReal unk_110;
    RwReal unk_114;             // command 20
    RwReal unk_118;
    RwInt32 unk_11C;            // command 14
    type_3DF8D8_04 unk_120;     // commands 38 and 39: its weapons' names,
    type_3DF8D8_04 unk_128;     // and their NPC weapon settings (sub_15CB40)
    RwInt32 unk_130;
    RwInt32 unk_134;
    RwInt32 unk_138;            // commands 40 and 41 (1 by default)
    RwInt32 unk_13C;
    RwInt32 unk_140;            // command 22 (100 by default)
    RwReal unk_144;             // commands 23 and 24, halved
    RwReal unk_148;
    RwInt32 unk_14C;            // command 42 (-1 for 0x6B and from 0x6E on)
    RwInt32 unk_150;            // command 43
    RwReal unk_154;             // command 44
    RwInt32 unk_158;            // command 13: the number it may spawn, and
    RwInt32 unk_15C;            // its cap now (spawning leaves it; 0x7FFFFFFF: no limit)
    RwInt32 unk_160;            // command 6
    RwInt32 unk_164;            // command 11
    RwInt32 unk_168;            // command 9
    RwInt32 unk_16C;            // commands 4 and 5
    RwInt32 unk_170;
    RwChar unk_174[0x20];       // command 1: a name (at most 31 characters)
    type_D48D0 unk_194;         // an entity (a handle; nothing reads it)
    RwUInt8 *unk_198;           // command 10: its messages' block
                                // (sub_BD490)
    RwUInt8 unk_19C[0x4];
};
typedef RwChar SoldierTrigger_size_check[sizeof(SoldierTrigger) == 0x1A0 ? 1 : -1];

#endif
