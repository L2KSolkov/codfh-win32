/*
 * The main render (unit_125490): the frame (sub_125F20) and the passes it
 * runs over the level's worlds, the world's lighting set-up and restore,
 * the character shadows projected on the collision triangles, the motion
 * blur, and the fog and far clip that fade between settings. The render
 * settings themselves are in types/RenderTrigger.h, which sets them.
 */
#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <xtl.h>

#include "rw/ostypes.h"
#include "rws/gftime.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baengine.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpworld.h"
#include "rw/rpmaterial.h"
#include "rw/baim3d.h"
#include "types/type_4E5D30.h"
#include "game/worldrender.h"

// The loading thread, held while the frame is drawn (the database's
// hThread; types/asynchload.h calls it dword_44BAD4).
extern RwUInt32 dword_44BAD4;

// The level's worlds: the main one (the database's world), two more drawn
// after it, the one the effects pass draws, and the lights added to each.
#ifdef CODFH_PLAIN
extern RpWorld *&world;
#else
extern RpWorld *world;
#endif
#ifdef CODFH_PLAIN
extern RpWorld *&dword_4E5C84;
#else
extern RpWorld *dword_4E5C84;
#endif
#ifdef CODFH_PLAIN
extern RpWorld *&dword_4E5C88;
#else
extern RpWorld *dword_4E5C88;
#endif
#ifdef CODFH_PLAIN
extern RpWorld *&dword_4E5C78;
#else
extern RpWorld *dword_4E5C78;
#endif
#ifdef CODFH_PLAIN
extern RpLight *&dword_4E5C7C;
#else
extern RpLight *dword_4E5C7C;
#endif

// Passes switched off (the debug toggles): the whole world, the level
// sections' opaque, animated and second worlds, the world render pass.
extern RwInt32 dword_4CF434;
extern RwInt32 dword_4CF438;
extern RwInt32 dword_4CF43C;
extern RwInt32 dword_4CF440;
extern RwInt32 dword_4CF444;

// The render states a pass saves (sub_126A30 and the others) and restores.
extern RwInt32 dword_4CF464;
extern RwInt32 dword_4CF484;
extern RwInt32 dword_4CF51C;
extern RwInt32 dword_4CF47C;
extern RwInt32 dword_4CF478;
extern RwInt32 dword_4CF510;
extern RwInt32 dword_4CF75C;

// The frame counters: frames this second and last second, the time the
// second began and now, and the frames drawn.
extern RwInt32 dword_4CF750;
extern RwInt32 dword_4CF480;
extern RwInt32 dword_4CF76C;
extern RwInt32 dword_4CF798;
extern RwInt32 dword_4CF7A0;
extern RwInt32 dword_4CF79C;

// The field of view the textures' filtering was last set for (sub_1254D0).
extern RwInt32 dword_4CF7C4;
// A far clip to fade to once the frame is drawn (sub_125F20).
extern RwReal flt_4CF7CC;
// Set when the frame ends in the game's own screen (sub_D8E80).
extern RwUInt8 byte_4CF7D0;

// The motion blur: its strength (0 to 255), how long it lasts and the time
// it falls over, and whether it is held.
extern RwInt32 dword_4CF48C;
extern RwReal dword_4CF774;
extern RwReal dword_4CF78C;
extern RwInt32 dword_4CF788;

// The fog and far clip fades (sub_128C80, sub_128CD0): the target, the time
// left and the step per second of each.
extern RwReal dword_4CF4D8;
extern RwReal dword_4CF514;
extern RwReal dword_4CF758;
extern RwReal dword_4CF4F8;
extern RwReal dword_4CF794;
extern RwReal dword_4CF470;

// The camera's position kept while the sky is drawn at a scale (sub_127530).
extern RwV3d dword_4CF5C0;

// The motion blur's strength floor, set whenever it is drawn (sub_1288D0).
extern RwReal dword_4F2B64;

// The shadows' textures by kind ("tankshadow", "charactershadow"), how far
// from the camera they are drawn (3000), how high over the ground (5), and
// the scale of the box their triangles are gathered in (1).
extern const RwChar *off_429BDC[10];
extern RwReal flt_429BD0;
extern RwReal flt_429BD4;
extern RwReal flt_429BD8;
// The up the gathered triangles must face.
extern RwV3d dword_429D90;
// A triangle's normal (sub_16E860: the triangle arg_0, arg_4, arg_8).
void sub_16E860(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C);

// The screen quad sub_1288F0 sets up (four vertices).
extern RwIm2DVertex dword_4CF548[4];

// The shadows: a triangle buffer for each of the ten kinds (its vertices,
// how many triangles, its texture's raster), and the collision triangles
// under the current one (dword_4B25B8 of them, from 150).
struct type_4CF5D0
{
    RwIm3DVertex *unk_00;
    RwInt32 unk_04;
    RwRaster *unk_08;
};
extern type_4CF5D0 dword_4CF5D0[10];

// The level section order the world render pass follows, the global
// section (its world, unk_20, the database's dword_4E5CF8), and the fog's second setting.
extern RwInt32 dword_429BAC[4];
extern type_4E5D30 unk_4E5CD8;
extern RwInt32 dword_4CF490;

// What the frame calls (only their widths are known): the effects' passes
// and their end, the HUD's, and the clock (milliseconds).
void sub_19D080(RwCamera *arg_0);
void sub_17D3A0(RwCamera *arg_0);
void sub_15F390(RwCamera *arg_0);
void sub_187150(RwInt32 arg_0);
void sub_1A2D00();
namespace RWS
{
   namespace CameraHelper
   {
      void SetFieldOfView(RwReal fov, RwCamera *pCamera);
   }
}

// The lighting set-up for a pass (sub_126E30) and its restore (sub_127360),
// with their real types (game/worldrender.h declares them by width).
struct RpWorld;
struct RwCamera;
RwCamera *sub_126E30(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8, RwReal arg_C);
void sub_127360(RwCamera *arg_0, RpWorld *arg_4);

void sub_1254D0(RwCamera *arg_0);
void sub_1259C0(RwCamera *arg_0, RwInt32 arg_4);
RpMaterial *sub_125A10(RpMaterial *arg_0, void *arg_4);
void sub_125A50();
void sub_125E00();
void sub_125E40();
void sub_125E60(RwCamera *arg_0);
void sub_125ED0(RwCamera *arg_0, RwInt32 arg_4);
void sub_125F20(RwInt32 arg_0);
void sub_126750(RwCamera *arg_0);
void sub_126770();
void sub_1267D0(type_4E5D30 *arg_0, RwInt32 arg_4);
void sub_126850(RpWorld *arg_0, RwUInt32 arg_4, RwInt32 arg_8);
void sub_1268D0();
void sub_126930(type_4E5D30 *arg_0, RwInt32 arg_4);
void sub_1269B0(RpWorld *arg_0, RwUInt32 arg_4, RwInt32 arg_8);
RwCamera *sub_126A30(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8, RwReal arg_C,
                     RwInt32 arg_10);
void sub_126D00(RwCamera *arg_0, RpWorld *arg_4);
RwCamera *sub_127530(RwCamera *arg_0, RpWorld *arg_4);
void sub_127700(RwCamera *arg_0, RpWorld *arg_4);
RwCamera *sub_1277D0(RwCamera *arg_0, RpWorld *arg_4, RwUInt8 arg_8);
void sub_127910(RwCamera *arg_0, RpWorld *arg_4);
void sub_1279C0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C, RwReal arg_10,
                RwInt32 arg_14, RwInt32 arg_18);
void sub_1283E0(RwBBox *arg_0);
void sub_128770();
void sub_1287F0();
void sub_1288D0(RwCamera *arg_0, RwUInt32 arg_4);
void sub_1288F0(RwCamera *arg_0);
void sub_128B00(RwCamera *arg_0);
void sub_128C20(RwInt32 arg_0, RwReal arg_4, RwReal arg_8);
void sub_128C80(RwReal arg_0, RwReal arg_4);
void sub_128CD0(RwReal arg_0, RwReal arg_4);
void sub_128D30();
void sub_128DB0();
void sub_128E50(RpClump *arg_0, RwInt32 arg_4);
RpWorldSector *sub_1290A0(RpWorldSector *arg_0, void *arg_4);
void sub_1290F0(RwCamera *arg_0, RpWorld *arg_4, RwInt32 arg_8);
void sub_129140(RwCamera *arg_0, RpWorld *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                RwInt32 arg_10);
void sub_1291A0(RwInt32 arg_0, RwInt32 arg_4);
void sub_1291E0();

#endif
