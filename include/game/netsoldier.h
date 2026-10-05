/*
 * The multiplayer manager's remote players (game/gameloop.h, type_4F7EB8's
 * unk_1F0): soldiers with a network part.
 */
#ifndef GAME_NETSOLDIER_H
#define GAME_NETSOLDIER_H

#include "rw/ostypes.h"
#include "types/type_3DAFC8.h"
#include "types/type_3D32F8.h"
#include "game/gameloop.h"
#include "game/netplayer.h"

// A remote player: a soldier (type_3DAFC8, 0x2170 bytes) with its network
// part as a second base at +0x2170 (what shows a network player,
// game/netplayer.h) and the sections it holds at +0x21AC (sub_1AF850).
// Evidence for the base: the state change (sub_1ABC00) converts to it with
// the compiler's null check and calls its virtuals through the soldier's
// pointer.
class SoldierTrigger;
struct type_4F7EB8_1F0 : type_3DAFC8, type_4F6B00_120
{
    // Built in entity memory for its trigger (sub_1BEBB0; 0x21D0 bytes).
    type_4F7EB8_1F0(SoldierTrigger *arg_0);
    // Tells the manager (sub_15FB30, empty) before the soldier goes.
    ~type_4F7EB8_1F0();
    // The placement pair it is built in entity memory with, and its plain
    // operator delete (all folded).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // Overrides of the soldier's slots.
    virtual void vf_038(RwReal arg_0);
    virtual void vf_054(RwInt32 arg_0);
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    // An explosion: none (the manager deals them). Returns 0: folded
    // (/OPT:ICF) into sub_32260.
    virtual RwInt32 vf_068(struct type_758F0 *arg_0)
    {
        return 0;
    }
    virtual RwV3d *vf_244(RwV3d *arg_0);
    // The soldier's vf_05C again, as its network part's +0x02C needs an
    // overrider of its own: identical, so folded (/OPT:ICF) with it at
    // 0x1C06A0, which the part's thunk (sub_1C06D0) reaches.
    virtual void vf_05C()
    {
        unk_35C[0].sub_D48D0(0);
        unk_364[0] = -1;
    }

    // The network part's slots: the remote player's state; shown and
    // hidden; told its id and session; its bullet and grenade hits (with a
    // death); its lean; a death's values.
    virtual void pvf_000(type_1F8560_v *arg_0, type_4F6B00_F4 *arg_4, type_1F8560_v *arg_8, RwInt32 *arg_C,
                         RwInt32 *arg_10, RwInt32 *arg_14, RwUInt32 *arg_18, RwUInt16 *arg_1C);
    virtual void pvf_004();
    virtual void pvf_008();
    virtual void pvf_00C(RwInt32 arg_0);
    virtual void pvf_010(type_4F8058 *arg_0);
    virtual void pvf_014(type_75600 *arg_0);
    virtual void pvf_018(type_75600 *arg_0);
    virtual void pvf_01C(struct type_4AE70 *arg_0);
    virtual void pvf_020(struct type_4AE70 *arg_0);
    virtual void pvf_024();
    virtual void pvf_028(RwV3d *arg_0, RwInt32 arg_4);

    // Tells its network player its hit-death values (sub_73D90, empty).
    void sub_1BFFD0();
    // Its performance from the remote player's state (the facing, velocity,
    // lean, stance and flags).
    void sub_1BF5E0(type_4F6B00_F4 *arg_0, type_1F8560_v *arg_4, RwInt32 *arg_8, RwInt32 *arg_C, RwUInt32 *arg_10);
    // Its bullet and grenade hits.
    void sub_1C0020(type_75600 *arg_0);
    void sub_1C0200(struct type_4AE70 *arg_0);

    type_4F8058 *unk_2174;      // the session (pvf_010)
    RwInt32 unk_2178;           // its network player's id (-1; pvf_00C)
    RwInt32 unk_217C;           // set while a hit waits to be sent
    RwReal unk_2180;            // the time to the next send (0.2)
    type_3DA434 unk_2184;       // the damage message
    type_3E0F6C unk_2194;       // the hit message
    RwReal unk_21A4;            // its lean, in degrees (vf_244)
    RwInt32 unk_21A8;           // set while hidden (pvf_008)
    type_1AFAF0 unk_21AC;
    RwInt32 unk_21BC;
    RwInt32 unk_21C0;           // set by pvf_024
    RwUInt8 unk_21C4[6];
    RwUInt8 unk_21CA[6];
};
typedef RwChar type_4F7EB8_1F0_size_check[sizeof(type_4F7EB8_1F0) == 0x21D0 ? 1 : -1];

// Built in entity memory for the trigger arg_0, or a warning that there is
// no entity memory for it.
type_4F7EB8_1F0 *sub_1BEBB0(type_712B0 *arg_0);
// The remote players' performance settings (sub_1BF5E0): the run's rates
// by posture and stance (four rows of five), the debug override's switch,
// case and default values, and the animation state kept for the debug
// display.
extern RwReal flt_42CB40[4][5];
extern RwReal flt_42CB90;            // the side-step's turn per unit (.data)
extern RwUInt8 byte_42CB94[2];
extern RwInt32 dword_4FBC3C;
extern RwUInt8 byte_4FBC40;
extern RwInt32 dword_4FBC44;
extern RwInt32 dword_4FBC30;
extern RwInt32 dword_4FBC34;
extern struct type_7C8D0 *dword_4FBC38;
// The axes the remote player's frame and aim turn about (y and x; .rdata,
// pvf_000).
extern const RwV3d stru_3E2FC4;
extern const RwV3d stru_3E2FB8;

typedef RwChar type_4F7EB8_1F0_base_check[sizeof(type_3DAFC8) + 4 == 0x2174 ? 1 : -1];

#endif
