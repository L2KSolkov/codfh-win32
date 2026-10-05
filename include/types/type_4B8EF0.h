/*
 * type_4B8EF0: the shell manager ("Restart: shellManager.Restart()"), one
 * object at dword_4B8EF0 (built by its dynamic initializer at 0x30B500):
 * the front end's settings (CShellLevelBehaviorClass's HandleAttributes,
 * sub_B7060, sets them), the HUD it owns (unk_2A0, built when its flag 4 is
 * set), its camera, the loading screen and its progress bar (sub_E9FB0),
 * and the shell's fonts' path. Its data and the 54 keys the level's
 * objects name are in its base type_E8F90, whose implicit constructor
 * (sub_E8F90) its own (sub_E8F40) calls.
 */
#ifndef TYPE_4B8EF0_H
#define TYPE_4B8EF0_H

#include "rw/batypes.h"
#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/batextur.h"
#include "types/type_3DF8D8.h"

struct type_DC400;

// The shell manager's data. Named for its implicit constructor (sub_E8F90),
// which constructs the keys one by one, each through a `this` temporary
// (type_3DF8D8_04's inline constructor).
struct type_E8F90
{
    RwReal unk_00;              // CShellLevelBehaviorClass's command 0: the
                                // level's north in degrees (the HUD's radar,
                                // type_DC400::sub_E4030, turns by it)
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwUInt8 unk_0C[0x10];
    RwInt32 unk_1C;
    RwInt32 unk_20;
    RwInt32 unk_24;             // commands 3 and 4
    RwInt32 unk_28;
    RwReal unk_2C;              // command 2, times 1000
    RwUInt8 unk_30[0x8];
    RwRGBA unk_38;              // command 5: a colour
    RwUInt8 unk_3C[0x4];
    RwReal unk_40;              // 5 at set-up
    RwUInt8 unk_44[0x20];
    RwInt32 unk_64;
    RwInt32 unk_68;
    RwUInt8 unk_6C[0x48];
    type_3DF8D8_04 unk_B4;
    type_3DF8D8_04 unk_BC;
    type_3DF8D8_04 unk_C4;
    type_3DF8D8_04 unk_CC;
    type_3DF8D8_04 unk_D4;
    type_3DF8D8_04 unk_DC;
    type_3DF8D8_04 unk_E4;
    type_3DF8D8_04 unk_EC;
    type_3DF8D8_04 unk_F4;
    type_3DF8D8_04 unk_FC;
    type_3DF8D8_04 unk_104;
    type_3DF8D8_04 unk_10C;
    type_3DF8D8_04 unk_114;
    type_3DF8D8_04 unk_11C;
    type_3DF8D8_04 unk_124;
    type_3DF8D8_04 unk_12C;
    type_3DF8D8_04 unk_134;
    type_3DF8D8_04 unk_13C;
    type_3DF8D8_04 unk_144;
    type_3DF8D8_04 unk_14C;
    type_3DF8D8_04 unk_154;
    type_3DF8D8_04 unk_15C;
    type_3DF8D8_04 unk_164;
    type_3DF8D8_04 unk_16C;
    type_3DF8D8_04 unk_174;
    type_3DF8D8_04 unk_17C;
    type_3DF8D8_04 unk_184;
    type_3DF8D8_04 unk_18C;
    type_3DF8D8_04 unk_194;
    type_3DF8D8_04 unk_19C;
    type_3DF8D8_04 unk_1A4;
    type_3DF8D8_04 unk_1AC;
    type_3DF8D8_04 unk_1B4;
    type_3DF8D8_04 unk_1BC;
    type_3DF8D8_04 unk_1C4;
    type_3DF8D8_04 unk_1CC;
    type_3DF8D8_04 unk_1D4;
    type_3DF8D8_04 unk_1DC;
    type_3DF8D8_04 unk_1E4;
    type_3DF8D8_04 unk_1EC;
    type_3DF8D8_04 unk_1F4;
    type_3DF8D8_04 unk_1FC;
    type_3DF8D8_04 unk_204;
    type_3DF8D8_04 unk_20C;
    type_3DF8D8_04 unk_214;
    type_3DF8D8_04 unk_21C;
    type_3DF8D8_04 unk_224;
    type_3DF8D8_04 unk_22C;
    type_3DF8D8_04 unk_234;
    type_3DF8D8_04 unk_23C;
    type_3DF8D8_04 unk_244;
    type_3DF8D8_04 unk_24C;
    type_3DF8D8_04 unk_254;
    type_3DF8D8_04 unk_25C;
    RwInt32 unk_264;
    RwUInt8 unk_268[0x14];
    RwInt32 unk_27C;
    RwInt32 unk_280;
    RwUInt8 unk_284[0x18];
    RwInt32 unk_29C;
    type_DC400 *unk_2A0;        // the HUD (flag 4)
    RwUInt32 unk_2A4;           // flags: 4 builds the HUD
    RwCamera *unk_2A8;          // its camera
    RwChar unk_2AC[0x80];       // the shell's fonts' path
    RwReal unk_32C;             // the loading bar's progress, 0 to 1
};

typedef RwChar type_E8F90_size_check[sizeof(type_E8F90) == 0x330 ? 1 : -1];

struct type_4B8EF0 : type_E8F90
{
    type_4B8EF0();
    ~type_4B8EF0();

    // An inline reset of five fields, with no address and so no database
    // name; named for its first field. Evidence: the set-up (sub_E9790)
    // stores the same five fields twice in a row.
    void reset_unk_264()
    {
        unk_264 = 0;
        unk_40 = 5.0f;
        unk_68 = 0;
        unk_64 = 0;
        unk_29C = 0;
    }

    // Steps the loading bar by the step arg_0 (1 to 20; each its own
    // share) and draws it, unless the level is loading (dword_4B8710).
    void sub_E9FB0(RwInt32 arg_0);
    // Its set-up (sub_D6820, with the module flags arg_0 and the camera
    // arg_4, dword_4E5CBC): the Rt2d device, the fonts' path, the text
    // manager and, with flag 4, the HUD.
    void sub_E9790(RwInt32 arg_0, RwInt32 arg_4);
    // Its restart ("Restart: shellManager.Restart()", sub_D6A50).
    void sub_E99A0();
    // Its shutdown (sub_D7040): the text manager, then its flags, the HUD
    // last.
    void sub_E99E0();
    // Called as the level starts (sub_D7570): the fonts' path, and with the
    // HUD its textures, the console font and the text manager.
    void sub_E9C20();
    // Sets its flags.
    void sub_E9C80(RwUInt32 arg_0);
    // Draws the text arg_0 at *arg_4 (the memory card message, sub_D8E80)
    // on its camera (sub_EBAE0); the rest only known by width.
    void sub_E9BE0(const RwChar *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwReal arg_C, RwReal arg_10,
                   RwReal arg_14);
    // Its set-up (sub_D8B90): draws the level's loading screen for the
    // game type and the language's loading banner, twice.
    void sub_E9CA0();
    // Its update, arg_0 the frame's time (sub_D7880): the HUD, then the
    // text manager while the HUD is not paused; returns 1.
    RwInt32 sub_E9AD0(RwReal arg_0);
    // Its render (sub_125F20): the HUD, then the text manager.
    void sub_E9B50();
    // An empty method sub_D7570 calls, folded by /OPT:ICF into pDtor
    // (0x1E41C0), whose database name it takes.
    void pDtor();
};
extern type_4B8EF0 dword_4B8EF0;

// The game's operator new with a memory type (0x12F0E0; the shell manager
// allocates its HUD with type 4).
void *operator new(size_t arg_0, RwUInt32 arg_4);
// The languages' loading texts' and banners' texture names, by sub_19B0A0.
extern const RwChar *off_429408[];
extern const RwChar *off_429458[];
// The database's name for a callback folded by /OPT:ICF that keeps the
// first object it is given in *arg_4 and stops (0x16E1F0); the shell's
// loading screen takes a dictionary's first texture with it.
RwTexture *Clump_CaptureFirstAtomic(RwTexture *arg_0, void *arg_4);

// The loading bar (sub_E9FB0): its full width (flt_429448), height, and
// position on a 512 by 448 screen, and its colour's red, green, alpha
// (byte_429444 to byte_429446) and blue (byte_4B8EE8).
extern RwReal flt_429448;
extern RwReal flt_42944C;
extern RwReal flt_429450;
extern RwReal flt_429454;
extern RwUInt8 byte_429444;
extern RwUInt8 byte_429445;
extern RwUInt8 byte_429446;
extern RwUInt8 byte_4B8EE8;

// Draws the raster arg_0 at alpha arg_4 over the screen (arg_C, arg_10) to
// (arg_14, arg_18) of 512 by 448 (all of it when arg_C equals arg_14) on
// the camera arg_8.
void sub_EA640(RwRaster *arg_0, RwUInt8 arg_4, RwCamera *arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
               RwReal arg_18);
// Reads the texture dictionary arg_0 (a level path); 0 when it cannot.
RwTexDictionary *sub_EA9C0(const RwChar *arg_0);
// Draws the language's loading banner on the camera arg_0, twice.
void sub_EA560(RwCamera *arg_0);

#endif
