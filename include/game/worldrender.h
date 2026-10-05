/*
 * The world render pass (unit_1227F0): the atomics in view, sorted by their
 * distance from the camera into three trees by their entity's render
 * priority, then drawn tree by tree with each atomic's lights set first.
 */
#ifndef GAME_WORLDRENDER_H
#define GAME_WORLDRENDER_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpworld.h"

// A node of the sort (0x10 bytes): the squared distance, the atomic and the
// nearer and farther subtrees (sub_128EB0 fills one; sub_129010 draws a
// subtree in order).
struct type_128EB0_04
{
    RwReal unk_00;
    RpAtomic *unk_04;
    type_128EB0_04 *unk_08;
    type_128EB0_04 *unk_0C;
};

struct type_128EB0;
extern type_128EB0 *dword_4CF7C0;

// The sort (0x1910 bytes, on sub_122DD0's stack): how many nodes are used,
// the nodes, and a tree for each render priority (type_3D3548's unk_29C).
// While it lives, dword_4CF7C0 points at it; its destructor, out of line at
// 0x122F30 for sub_122DD0's unwinding, clears it.
struct type_128EB0
{
    RwInt32 unk_00;
    type_128EB0_04 unk_04[400];
    type_128EB0_04 *unk_1904[3];

    type_128EB0()
    {
        RwInt32 var_4;

        unk_00 = 0;
        for (var_4 = 0; var_4 < 3; var_4++)
        {
            unk_1904[var_4] = 0;
        }
        dword_4CF7C0 = this;
    }
    ~type_128EB0()
    {
        dword_4CF7C0 = 0;
    }

    // Adds the atomic arg_0 at the squared distance arg_4, or draws it at
    // once when the nodes are used up.
    void sub_128EB0(RpAtomic *arg_0, RwReal arg_4);
    // Puts the node arg_4 in the subtree arg_0.
    void sub_128FA0(type_128EB0_04 *arg_0, type_128EB0_04 *arg_4);
    // Draws the subtree arg_0, nearest first.
    void sub_129010(type_128EB0_04 *arg_0);
};

// The sector walk's data (sub_122D90 builds it for sub_122D40): the camera,
// the second argument of sub_122DD0 and whether to skip the sectors the PVS
// hides.
struct type_122D90
{
    RwCamera *unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};

// Draws the atomics in the sector arg_0 through the sort (sub_1227F0), the
// atomics of the tie list from arg_0 to arg_4 (sub_122BC0).
void sub_1227F0(RpWorldSector *arg_0);
void sub_122BC0(RwLLLink *arg_0, RwLLLink *arg_4);
RpWorldSector *sub_122D40(RpWorldSector *arg_0, void *arg_4);
void sub_122D90(RwCamera *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_122DD0(RwCamera *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void sub_122F50();

// The world's lighting set-up (a later unit): whether it is ready, and the
// pass after the atomics.
struct RpWorld;
RwCamera *sub_126E30(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8, RwReal arg_C);
void sub_127360(RwCamera *arg_0, RpWorld *arg_4);

// Whether the PVS shows the sector arg_0 (RenderWare's PVS plugin,
// 0x2E7A60).
extern "C" RwBool RpPVSWorldSectorVisible(RpWorldSector *arg_0);

// The lights sub_122820 sets for each atomic: the ambient light, the four
// point lights with their default colours and frames, and the ambient
// colour to fall back on (.bss, a later unit's).
extern RpLight *light;
extern RpLight *result[4];
extern RwRGBAReal dword_4CF498[4];
extern RwMatrix dword_4CF650[4];
extern RwRGBAReal xmmword_4CF7AC;

// Counts sub_122820's calls for the entity sub_1745A0(0).
extern RwInt32 dword_4CEA68;

#endif
