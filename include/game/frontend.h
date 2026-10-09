/*
 * The front end (sub_DA290: "GameFrontEnd Initialization begin...."): a
 * world and camera of its own for the shell's screens (sub_1A2E40), then
 * torn down.
 */
#ifndef GAME_FRONTEND_H
#define GAME_FRONTEND_H

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/batextur.h"
#include "types/type_DA580.h"
#include "types/type_DA0A0.h"
#include "types/type_8A980.h"
#include "game/ingamemenu.h"
#include "game/kujufont.h"

void sub_DA290();
// The front end's world (sub_1331E0 makes it; sub_16E5C0 tells whether it
// is empty at shut-down).
RpWorld *sub_1331E0();
bool sub_16E5C0(RpWorld *arg_0, RwInt32 arg_4, RwInt32 arg_8);
// Runs the shell's screens on the camera arg_0.
void sub_1A2E40(RwCamera *arg_0);
// The level file's texture dictionary (0 when it has none).
RwTexDictionary *sub_1A2D90(const RwChar *arg_0);
// The shell's hooks while it runs (dword_504378: begin, vf_08, and end,
// vf_0C): an interface of four pure methods (off_3E83F4), and the shell's
// own (off_3E83E4, whose methods are empty but for vf_04, 0x203E10). Only
// the widths are known.
struct type_3E83F4
{
    virtual void vf_00() = 0;
    // Plays the front end's sound arg_0 (0x203E10, a switch of four; kujuUI's
    // event mapper plays 3 for a press).
    virtual void vf_04(RwInt32 arg_0) = 0;
    virtual void vf_08() = 0;
    virtual void vf_0C() = 0;
};
extern type_3E83F4 *dword_504378;
struct type_3E83E4 : type_3E83F4
{
    type_8A980 unk_04;          // the front end's sound player (its voices
                                // let go when the shell ends)
    RwUInt8 unk_88[0x28];

    type_3E83E4();
    ~type_3E83E4();
    virtual void vf_00();
    virtual void vf_04(RwInt32 arg_0);
    virtual void vf_08();
    virtual void vf_0C();
};
// The shell on the camera arg_0 (unit_200960; 0x2C bytes): its in-game
// menus' manager (unk_04), which its constructor points at the in-game menu
// 13 once the menus are loaded (sub_204100, then sub_204700 until
// sub_204750) and sub_200AE0 runs, and five items it deletes when it goes
// (unk_14, never filled here; their type is not known).
struct type_200960
{
    RwCamera *unk_00;
    InGameMenuManager unk_04;
    type_1E61A0<void *, 5> unk_14;

    type_200960(RwCamera *arg_0);
    ~type_200960();
    void sub_200AE0();
};
// The camera the shell runs on (sub_1A2E40).
#ifdef CODFH_PLAIN
extern RwCamera *&dword_4F7E98;
#else
extern RwCamera *dword_4F7E98;
#endif
namespace kujuUI
{
struct type_3E7D08;
}
// The one Live options page (game/livemenu.h's type_209E00, dword_504578),
// built on first use (the in-game menus' loop takes it off the pad's widget
// stack).
kujuUI::type_3E7D08 *sub_20A540();
extern RwInt32 dword_4B889C;
extern RwInt32 dword_4F39DC;
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4F30B8;
#else
extern RwInt32 dword_4F30B8;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B9E54;
#else
extern RwInt32 dword_4B9E54;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B9E48;
#else
extern RwInt32 dword_4B9E48;
#endif
extern bool byte_4B88B8;
// The memory card the shell saves to.
extern type_D9CF0 unk_4B8744;
// Sets byte_4B8920 and clears dword_4B8924 (sub_DA570).
void sub_DA550(bool arg_0);
void sub_DA570();
extern bool byte_4B8920;
#ifdef CODFH_SP // single player times the front end's idleness in it (SP 0xA61DC)
extern RwReal dword_4B8924;
#else
extern RwInt32 dword_4B8924;
#endif

#endif
