/*
 * The particle systems (src/recovered/unit_0F2880.cpp): the definitions
 * file (dword_4BFD28: a count, then 0x2C-byte records naming each
 * definition, found by name or by id through the hash dword_4BFD64), its
 * texture dictionary (dict) and meshes (dword_4BC8B8), the two pools the
 * systems (types/type_F2FF0.h) are built in (dword_4BFD44, and dword_4BFD98
 * for the ones that must not fail), the live list (dword_4BFD34), and the
 * tree the sprite systems are sorted in by depth to draw (dword_4BCE48's
 * nodes).
 */
#ifndef GAME_PARTICLES_H
#define GAME_PARTICLES_H

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/bastream.h"
#include "rw/batextur.h"
#include "rw/baengine.h"
#include "rw/rpatomic.h"
#include "types/alfahash.h"
#include "types/type_F3130.h"
#include "types/type_F2FF0.h"

// A definition's record in the file: its name, its definition's offset in
// the file and its id.
struct type_4BFD28_rec
{
    RwChar unk_00[0x24];
    RwInt32 unk_24;
    RwInt32 unk_28;
};

// The file: the records' count, then the records.
struct type_4BFD28
{
    RwInt32 unk_00;
    type_4BFD28_rec unk_04[1];
};

// A mesh: its name ("<name>_rx1") and clump, and the clump's atomic.
struct type_4BC8B8
{
    RwChar unk_00[0x14];
    RpClump *unk_14;
    RpAtomic *unk_18;
};

// A node of the depth tree (from dword_4BCE44's free list): nearer and
// farther subtrees (the first is also the free list's link), the depth
// and the system.
struct type_F3830
{
    type_F3830 *unk_00;
    type_F3830 *unk_04;
    RwReal unk_08;
    type_F2FF0 *unk_0C;
};

extern type_4BC8B8 dword_4BC8B8[50];
// The tree's peak and current node counts, its root and free list, and its
// nodes.
extern RwInt32 dword_4BCE30;
extern type_F3830 *dword_4BCE34;
extern RwInt32 dword_4BCE38;
extern type_F3830 *dword_4BCE44;
extern type_F3830 dword_4BCE48[0x2BC];
// The systems in the second pool, and their peak.
extern RwInt32 dword_4BCE3C;
extern RwInt32 dword_4BCE40;
extern type_4BFD28 *dword_4BFD28;
extern RwTexDictionary *dict;
// The systems counted (flag 0x20), the live list, whether the file and
// dictionary are both in, the meshes' count and whether drawing is off.
extern RwInt32 dword_4BFD30;
extern type_F2FF0 *dword_4BFD34;
extern RwInt32 dword_4BFD38;
extern RwInt32 dword_4BFD3C;
extern RwInt32 dword_4BFD40;
extern type_16C2A0 dword_4BFD44;
extern alfahash dword_4BFD64;
extern type_16C2A0 dword_4BFD98;
// The most systems updated at once, the camera of the update, the
// particles in mesh systems and the systems built.
extern RwInt32 dword_4BFDB8;
extern RwCamera *dword_4BFDBC;
extern RwInt32 dword_4BFDC0;
extern RwInt32 dword_4BFDC4;

// The world manager's directional lights (sub_171DC0 creates them: the
// first, the database's "camera", and three more at dword_4E5C98[1] to [3];
// a level's own directional light takes [0], sub_173800) and the level's
// ambient light (the database's "clump"; the database's names).
#ifdef CODFH_PLAIN
extern RpLight * (&dword_4E5C98)[4];
#else
extern RpLight *dword_4E5C98[4];
#endif
#ifdef CODFH_PLAIN
extern RpLight *&camera;
#else
extern RpLight *camera;
#endif
#ifdef CODFH_PLAIN
extern RpLight *&clump;
#else
extern RpLight *clump;
#endif

// The directional light arg_0 (the first without one); an inline with no
// address, named for what it returns. Evidence: the draw (sub_F34C0)
// indexes with a constant 0 that is still loaded (xor eax, eax; shl eax, 2)
// and keeps the choice in a temporary.
inline RpLight *get_light(RwInt32 arg_0)
{
    return !dword_4E5C98[arg_0] ? camera : dword_4E5C98[arg_0];
}

// Set-up, shutdown and restart (sub_F2A00 clears the systems, and with
// arg_0 the decals, file and dictionary too).
void sub_F2920();
void sub_F29F0();
void sub_F2A30();
// Takes the definitions file arg_0, and reads the meshes from the stream
// arg_0; the mesh named arg_0; the file's and dictionary's release; takes
// the dictionary arg_0.
void sub_F2B00(type_4BFD28 *arg_0);
void sub_F2C30(RwStream *arg_0);
RpAtomic *sub_F2D80(const RwChar *arg_0);
void sub_F2E10();
void sub_F2E90();
RwTexture *sub_F2EC0(RwTexture *arg_0, void *arg_4);
void sub_F2EE0(RwTexDictionary *arg_0);
// Links arg_0 to and unlinks it from the live list.
void sub_F2F40(type_F2FF0 *arg_0);
void sub_F2F80(type_F2FF0 *arg_0);
// Starts the definition named arg_0 ("<name>.spp") at the matrix arg_4.
type_F2FF0 *sub_F3070(const RwChar *arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C, bool arg_10,
                      bool arg_14);
// Destroys all systems; updates them; draws the pass arg_4 (arg_0: the
// sprite pass, sorted by depth).
void sub_F33C0();
void sub_F3410();
void sub_F34C0(RwInt32 arg_0, RwUInt32 arg_4);
// The depth tree: reset, node alloc and free, insert and draw (arg_4: far
// to near).
void sub_F37B0();
type_F3830 *sub_F3830();
void sub_F3880(type_F3830 *arg_0);
void sub_F38B0(type_F3830 *arg_0);
void sub_F3930(type_F3830 *arg_0, bool arg_4);
// The clock (RWS::Time::GetTime's milliseconds).
RwUInt32 sub_F39D0();

// The particles' state and the pool clock (game code outside the unit).
void sub_19E500();
void sub_19E930();
void sub_19E940(type_F2FF0_60 *arg_0);
void sub_19EA10();
void sub_19EB20(RwCamera *arg_0);
void sub_19EB90();
type_F2FF0_60 *sub_19EC70(type_F2FF0_60 *arg_0, RwMatrix *arg_4, type_F3130 *arg_8, bool arg_C);
void sub_19F740(type_F2FF0_60 *arg_0, type_F2FF0 *arg_4, type_F3130 *arg_8, RwUInt32 arg_C);
// A mesh system's update and draw (still binary).
RwInt32 sub_EF040(type_F2FF0 *arg_0, RwReal arg_4);
void sub_EFB70(type_F2FF0 *arg_0);
// The clump atomic callback that stores its atomic at *arg_4.

#endif
