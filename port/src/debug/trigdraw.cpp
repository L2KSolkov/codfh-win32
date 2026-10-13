// The Win32 port's debug tools (CODFH_DRAW_TRIGGERS, with the ImGui overlay;
// the plain build's research/trigdraw.cpp): draws every registered trigger's
// volume as Im3D lines after the world, so trigger placement can be seen in
// game. The shapes follow the containment tests the game
// actually uses (unit_144940 sub_144F20), not Trigger::sub_BDF70's random
// point:
//   0 sphere:   distance from the matrix position < unk_48 (sub_9ACE0);
//   1 cylinder: in the matrix's space, x*x + z*z < unk_48^2 and
//               -unk_4C < y < unk_4C (sub_92900);
//   2 box:      |x| < unk_48, |y| < unk_4C, |z| < unk_50 in the matrix's
//               space (sub_9ABE0): the metrics are half-extents.
// Triggers come from the handle table dword_4CFE30[0..dword_429D00]
// (sub_144C00 stores Trigger pointers there; freed handles are zeroed by
// sub_144C50).
// Each trigger's type is written at its centre in world space: camera-facing
// quads per character, textured from the debug text's RenderWare charset
// (charSet, unit_16BA60; single player never sets it up, so the labels
// make one of their own then), sized by the distance so they stay readable.
// With g_bTrigDrawCollision, the collision worlds are drawn too: the ones
// the collision queries test (RpCollisionWorldForAllIntersections in
// unit_0929A0 and unit_08E670), i.e. the global
// section's (unk_4E5CD8) and each live section slot's (dword_4E5D30[i],
// unk_28 while unk_00 is set), registered by sub_173CE0 with kind 2.

#ifdef CODFH_DRAW_TRIGGERS

#include <xtl.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "rw/baim3d.h"
#include "rw/baraster.h"
#include "rw/rtcharse.h"
#include "types/type_4D1DB8.h"
#include "types/type_44350.h"
#include "game/data.h"
#include "game/debugtext.h"
#include "rw/rpworld.h"
#include "types/type_4E5D30.h"
#include "game/padlib.h"
#include "game/worldmgr.h"
#include "types/type_4C00E8.h"
#include "types/type_F8350.h"
#include "types/AIData.h"
#include "types/type_3DAFC8.h"
#include "types/type_3D32F8.h"
#include <stddef.h>
#include "types/type_3DC9B0.h"
#include "types/type_15CCE0.h"
#include "types/type_154C0_F80.h"
#include "types/type_154C0_12F4.h"

#include "types/type_D48D0.h"
#include "types/type_1227C0.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_67620.h"
#include "types/type_3D2E7C.h"
#include "types/alfaobject.h"
#include "types/alfasched.h"
#include "types/type_3D96F0.h"
#include "types/type_92430.h"
#include "rw/rpmaterial.h"
#include "rw/batextur.h"
#include "trigcoll.h"
#include "trigsndproj.h"
#include "types/projectile.h"
#include "types/vec4.h"
#include "game/particles.h"
#include "types/type_3DF30.h"
#include "types/type_3CE6D0.h"
#include "game/data.h"
#include "types/type_3C540.h"
#include "rw/rphanim.h"
#include "rw/rplight.h"
#include "types/type_3D96F0.h"
#include "types/GimpTrigger.h"
#include "types/ShrimpTrigger.h"
#include "types/type_3DDB98.h"
#include "types/type_3DDE70.h"
#include "types/type_17CC40.h"
#include "types/SplinePath.h"

extern type_4C00E8 unk_4C00E8;

// A world sector as RenderWare 3.7.2 lays it out (include/rw/sdk/rpworld.h;
// the game reads boundingBox at +0x48 the same way, type_8F8C0), from the
// fields our rpworld.h leaves out.
struct TrigDrawSector
{
    RwInt32 nType;
    RpTriangle *pTriangles;
    RwV3d *pVertices;
    RwUInt8 aSkip[0x48 - 0x0C];
    RwBBox bbBounds;
    RwBBox bbTight;
    void *pMesh;
    void *pPipeline;
    RwUInt16 wMatListWindowBase;
    RwUInt16 wNumVertices;
    RwUInt16 wNumTriangles;
    RwUInt16 wPad;
};
typedef RwChar TrigDrawSector_check[sizeof(TrigDrawSector) == 0x88 ? 1 : -1];

extern type_4E5D30 dword_4E5D30[4];
extern type_4E5D30 unk_4E5CD8;

extern "C" volatile unsigned port_frame;

#define TRIGDRAW_COLLVERTS  3000

// The pad's Black and White in its analog buttons (the port's input header names neither;
// xpal_sys.cpp's XB_BLACK and XB_WHITE).
#ifndef XINPUT_GAMEPAD_BLACK
#define XINPUT_GAMEPAD_BLACK 4
#define XINPUT_GAMEPAD_WHITE 5
#endif

// (in the RenderWare tree, rtcharse.c, but not in its header here)
extern "C" RtCharset *RtCharsetGetDesc(RtCharset *charset, RtCharsetDesc *desc);
extern "C" RtCharset *RtCharsetCreate(const RwRGBA *foreGround, const RwRGBA *backGround);

// The labels' charset: the debug text's (charSet), or, when the game never
// made one (single player has no debug text), one of the labels' own, white
// on clear (the labels tint it), made the first time it is needed.
static RtCharset *TrigDrawCharset()
{
    static RtCharset *s_pOwn;
    static RwBool s_bTried;

    if (charSet != NULL)
        return charSet;
    if (!s_bTried)
    {
        RwRGBA fore = { 255, 255, 255, 255 };
        RwRGBA back = { 0, 0, 0, 0 };

        s_bTried = TRUE;
        s_pOwn = RtCharsetCreate(&fore, &back);
    }
    return s_pOwn;
}

#define TRIGDRAW_SEGMENTS   24
#define TRIGDRAW_MAXVERTS   (3 * TRIGDRAW_SEGMENTS * 2)
#define TRIGDRAW_MAXCHARS   48

// The trigger types by their kind (Trigger::vf_008 and its overrides); the
// kinds no class returns are printed as numbers. 0x1C is both
// StreamClumpTrigger and LevelClumpBankParamTrigger.
static const RwChar *const s_apszKindNames[0x28] =
{
    "Trigger", "PlayerTrigger", "RenderTrigger", 0,
    "SectionTrigger", "SoldierTrigger", "DogTrigger", "VehicleTrigger",
    "AnimatedBGTrigger", "ConfinedAreaTrigger", "SoundBankTrigger", "CustomTrigger",
    "StreamTrigger", "PlaySoundTrigger", "StreamVolume", "StopSoundStreamTrigger",
    "AnimPackTrigger", "SimpleMechanicTrigger", "ParticleTrigger", "ProjectileGeneratorTrigger",
    "DestructableObjectTrigger", 0, "MeshSwapDestructableObjectTrigger", "AddTaskTrigger",
    "PickupTrigger", "CCESSPoolTrigger", "VehicleEnterExitTrigger", "MountedWeaponTrigger",
    "StreamClump/LevelClumpBankParamTrigger", 0, "LevelScriptTrigger", "GimpTrigger",
    "LadderTrigger", "ShrimpTrigger", "PulseZoneTrigger", "GimpVehicleTrigger",
    "EndLevelTrigger", "cNetSpawnPoint", "FogTrigger", "PASTrigger"
};

static RwIm3DVertex s_aTextVerts[TRIGDRAW_MAXCHARS * 6];

// Switches, set from the debug tools' View list (trigtools.cpp): draw at all
// (off until asked for: the environment's CODFH_TRIGGERS=1 starts with it on,
// 2 with the collision too; CODFH_PATHNODES=1 the path nodes),
// the draw distance from the camera (0 = unlimited), and draw through
// walls (z test off).
RwBool g_bTrigDrawEnabled = FALSE;
RwReal g_fTrigDrawRange = 150.0f;
RwBool g_bTrigDrawSeeThrough = TRUE;
// The labels: on or off, and their height as a fraction of the distance.
RwBool g_bTrigDrawLabels = TRUE;
RwBool g_bTrigDrawNames = TRUE;        // the level's name for each trigger, above its type
// the gimps and shrimps (their section below)
RwBool g_bTrigDrawGimps = FALSE;
RwBool g_bTrigDrawShrimps = FALSE;
RwReal g_fTrigDrawGimpRange = 6000.0f;
RwInt32 g_nTrigDrawGimpsShown;
RwInt32 g_nTrigDrawShrimpsShown;
static void TrigDrawSpawnerLines(Trigger *pTrigger, const RwV3d *pvCentre, const RwMatrix *pCamLtm, RwUInt32 dwColour);
const RwChar *TrigDrawTriggerName(Trigger *pTrigger);   // (trignames.cpp)
const RwChar *TrigDrawKeyName(RwUInt32 a, RwUInt32 b);
RwReal g_fTrigDrawTextScale = 0.02f;
// The collision: on or off, how far from the camera a sector's box may be,
// and how far each triangle is pushed along its normal (against flicker).
RwBool g_bTrigDrawCollision = FALSE;
RwReal g_fTrigDrawCollisionRange = 30.0f;
RwReal g_fTrigDrawCollisionLift = 0.02f;
// Noclip for the local player (type_10F710::vf_044 skips its collision step
// and calls TrigDrawNoclipMove): on or off, and the speed in units per step
// unit (vf_044's argument).
RwBool g_bTrigDrawNoclip = FALSE;
RwReal g_fTrigDrawNoclipSpeed = 50.0f;

static RwIm3DVertex s_aCollVerts[TRIGDRAW_COLLVERTS];
static RwInt32 s_nCollVerts;
static RwV3d s_vCollCam;

// The collision material kinds (trigcoll.h), a material-to-kind cache emptied each frame (a
// level's materials are freed with it), and whether any kind is shown this frame.
TrigDrawCollKind g_aTrigDrawCollKinds[TRIGDRAW_COLLKINDS];
RwInt32 g_nTrigDrawCollKinds;
RwBool g_bTrigDrawCollByKind = FALSE;
RwInt32 g_nTrigDrawCollFill = 0;
RwReal g_fTrigDrawCollGrid = 32.0f;
// (the outlines' line buffer: two vertices an edge)
#define TRIGDRAW_COLLLINEVERTS 3000
static RwIm3DVertex s_aCollLineVerts[TRIGDRAW_COLLLINEVERTS];
static RwInt32 s_nCollLineVerts;
#define TRIGDRAW_COLLMATCACHE 512
static struct { void *pMaterial; RwInt32 nKind; } s_aCollMatCache[TRIGDRAW_COLLMATCACHE];
static RwBool s_bCollAnyShown;

static RwIm3DVertex s_aVerts[TRIGDRAW_MAXVERTS];
static RwInt32 s_nVerts;
static RwMatrix s_mLtm;     // an aligned copy of the trigger's matrix

static const RwUInt32 s_aKindColours[8] =
{
    0x00FF4040, 0x0040FF40, 0x004080FF, 0x00FF8000,
    0x0000FFFF, 0x00FF40FF, 0x00FFFFFF, 0x0080FF80
};

// Adds one line from (fX0,fY0,fZ0) to (fX1,fY1,fZ1), in trigger space, with
// the colour dwColour (0xAARRGGBB); drops it when the buffer is full.
static void TrigDrawAddLine(RwReal fX0, RwReal fY0, RwReal fZ0,
                            RwReal fX1, RwReal fY1, RwReal fZ1, RwUInt32 dwColour)
{
    RwIm3DVertex *pVert;

    if (s_nVerts + 2 > TRIGDRAW_MAXVERTS)
        return;
    pVert = &s_aVerts[s_nVerts];
    RwIm3DVertexSetPos(pVert, fX0, fY0, fZ0);
    pVert->color = dwColour;
    pVert++;
    RwIm3DVertexSetPos(pVert, fX1, fY1, fZ1);
    pVert->color = dwColour;
    s_nVerts += 2;
}

// Adds a circle of radius fRadius around the trigger-space axis nAxis
// (0 x, 1 y, 2 z), centred at height fOffset along that axis.
static void TrigDrawAddCircle(RwInt32 nAxis, RwReal fRadius, RwReal fOffset, RwUInt32 dwColour)
{
    RwInt32 i;
    RwReal fA0, fA1, fC0, fS0, fC1, fS1;

    for (i = 0; i < TRIGDRAW_SEGMENTS; i++)
    {
        fA0 = (RwReal)i * (6.2831853f / TRIGDRAW_SEGMENTS);
        fA1 = (RwReal)(i + 1) * (6.2831853f / TRIGDRAW_SEGMENTS);
        fC0 = (RwReal)cos(fA0) * fRadius;
        fS0 = (RwReal)sin(fA0) * fRadius;
        fC1 = (RwReal)cos(fA1) * fRadius;
        fS1 = (RwReal)sin(fA1) * fRadius;
        if (nAxis == 0)
            TrigDrawAddLine(fOffset, fC0, fS0, fOffset, fC1, fS1, dwColour);
        else if (nAxis == 1)
            TrigDrawAddLine(fC0, fOffset, fS0, fC1, fOffset, fS1, dwColour);
        else
            TrigDrawAddLine(fC0, fS0, fOffset, fC1, fS1, fOffset, dwColour);
    }
}

// Picks the trigger's line colour: grey when switched off (unk_24_0 clear,
// so its containment test always fails), yellow when its proximity checks
// are off (unk_24_3), magenta when it has been moved (unk_24_15), otherwise
// a colour by its kind (vf_008).
static RwUInt32 TrigDrawActColour(Trigger *pTrigger, RwUInt32 dwBase);   // (trigger activity, below)
static RwUInt32 TrigDrawColourBase(Trigger *pTrigger);

// (with its activity's flash over it)
static RwUInt32 TrigDrawColour(Trigger *pTrigger)
{
    return TrigDrawActColour(pTrigger, TrigDrawColourBase(pTrigger));
}

static RwUInt32 TrigDrawColourBase(Trigger *pTrigger)
{
    if (!pTrigger->unk_24_0)
        return 0x80808080;
    if (pTrigger->unk_24_3)
        return 0xC0FFFF00;
    if (pTrigger->unk_24_15)
        return 0xC0FF00FF;
    return 0xC0000000 | s_aKindColours[(RwUInt32)pTrigger->vf_008() & 7];
}

// Builds one trigger's outline in its own space by its shape (unk_46) and
// metrics (unk_48, unk_4C, unk_50) and draws it through its matrix.
static void TrigDrawOne(Trigger *pTrigger)
{
    RwReal fA = pTrigger->unk_48;
    RwReal fB = pTrigger->unk_4C;
    RwReal fC = pTrigger->unk_50;
    RwUInt32 dwColour = TrigDrawColour(pTrigger);
    RwInt32 i;
    RwReal fAngle, fX, fZ;

    s_nVerts = 0;
    switch (pTrigger->unk_46)
    {
    case 0:     // sphere: three great circles
        TrigDrawAddCircle(0, fA, 0.0f, dwColour);
        TrigDrawAddCircle(1, fA, 0.0f, dwColour);
        TrigDrawAddCircle(2, fA, 0.0f, dwColour);
        break;
    case 1:     // cylinder about y, from -height to +height
        TrigDrawAddCircle(1, fA, -fB, dwColour);
        TrigDrawAddCircle(1, fA, fB, dwColour);
        for (i = 0; i < 8; i++)
        {
            fAngle = (RwReal)i * (6.2831853f / 8);
            fX = (RwReal)cos(fAngle) * fA;
            fZ = (RwReal)sin(fAngle) * fA;
            TrigDrawAddLine(fX, -fB, fZ, fX, fB, fZ, dwColour);
        }
        break;
    case 2:     // box from half-extents
        TrigDrawAddLine(-fA, -fB, -fC, fA, -fB, -fC, dwColour);
        TrigDrawAddLine(-fA, fB, -fC, fA, fB, -fC, dwColour);
        TrigDrawAddLine(-fA, -fB, fC, fA, -fB, fC, dwColour);
        TrigDrawAddLine(-fA, fB, fC, fA, fB, fC, dwColour);
        TrigDrawAddLine(-fA, -fB, -fC, -fA, fB, -fC, dwColour);
        TrigDrawAddLine(fA, -fB, -fC, fA, fB, -fC, dwColour);
        TrigDrawAddLine(-fA, -fB, fC, -fA, fB, fC, dwColour);
        TrigDrawAddLine(fA, -fB, fC, fA, fB, fC, dwColour);
        TrigDrawAddLine(-fA, -fB, -fC, -fA, -fB, fC, dwColour);
        TrigDrawAddLine(fA, -fB, -fC, fA, -fB, fC, dwColour);
        TrigDrawAddLine(-fA, fB, -fC, -fA, fB, fC, dwColour);
        TrigDrawAddLine(fA, fB, -fC, fA, fB, fC, dwColour);
        break;
    default:
        return;
    }
    if (s_nVerts == 0)
        return;
    // (copied: Trigger's matrix is an unaligned RwMatrixTag at +0x60)
    s_mLtm = *(RwMatrix *)&pTrigger->unk_60_m;
    if (RwIm3DTransform(s_aVerts, s_nVerts, &s_mLtm, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA))
    {
        RwIm3DRenderPrimitive(rwPRIMTYPELINELIST);
        RwIm3DEnd();
    }
}

// The trigger's type as text: its class name by kind, or the kind's number.
const RwChar *TrigDrawKindName(Trigger *pTrigger)
{
    static RwChar s_szKind[24];
    RwInt32 nKind = pTrigger->vf_008();

    if (nKind >= 0 && nKind < 0x28 && s_apszKindNames[nKind])
        return s_apszKindNames[nKind];
    sprintf(s_szKind, "Trigger kind %d", nKind);
    return s_szKind;
}

// Writes pszText centred at *pvAt, facing the camera whose matrix is
// pCamLtm: a quad per character with the charset's glyph cell as its
// texture, tinted dwColour. The characters are g_fTrigDrawTextScale of the
// distance high; fLines moves the line up by that many lines.
static void TrigDrawText(const RwChar *pszText, const RwV3d *pvAt, const RwMatrix *pCamLtm, RwUInt32 dwColour,
                         RwReal fLines = 0.0f)
{
    RtCharsetDesc desc;
    RwInt32 nChars = (RwInt32)strlen(pszText);
    RwV3d vCentre, vRight, vUp, vCorner, vP0, vP1, vP2, vP3;
    RwReal fDist, fH, fW, fRasW, fRasH, fU0, fV0, fU1, fV1;
    RwInt32 i, nIndex, nRow, nCol, nVerts;
    RwIm3DVertex *pVert;

    RtCharset *pCharset = TrigDrawCharset();

    if (pCharset == NULL || RtCharsetGetDesc(pCharset, &desc) == NULL)
        return;
    if (nChars > TRIGDRAW_MAXCHARS)
        nChars = TRIGDRAW_MAXCHARS;
    vCentre = *pvAt;
    fDist = (RwReal)sqrt((vCentre.x - pCamLtm->pos.x) * (vCentre.x - pCamLtm->pos.x)
                         + (vCentre.y - pCamLtm->pos.y) * (vCentre.y - pCamLtm->pos.y)
                         + (vCentre.z - pCamLtm->pos.z) * (vCentre.z - pCamLtm->pos.z));
    fH = fDist * g_fTrigDrawTextScale;
    if (fH < 0.05f)
        fH = 0.05f;
    fW = fH * (RwReal)desc.width / (RwReal)desc.height;
    // (a RenderWare camera's right vector points to the screen's left)
    vRight.x = -pCamLtm->right.x;
    vRight.y = -pCamLtm->right.y;
    vRight.z = -pCamLtm->right.z;
    vUp = pCamLtm->up;
    vCentre.x += vUp.x * fH * 1.2f * fLines;
    vCentre.y += vUp.y * fH * 1.2f * fLines;
    vCentre.z += vUp.z * fH * 1.2f * fLines;
    // the top left corner of the first character, centring the line
    vCorner.x = vCentre.x - vRight.x * fW * nChars * 0.5f + vUp.x * fH * 0.5f;
    vCorner.y = vCentre.y - vRight.y * fW * nChars * 0.5f + vUp.y * fH * 0.5f;
    vCorner.z = vCentre.z - vRight.z * fW * nChars * 0.5f + vUp.z * fH * 0.5f;
    fRasW = (RwReal)RwRasterGetWidth(pCharset);
    fRasH = (RwReal)RwRasterGetHeight(pCharset);

    nVerts = 0;
    for (i = 0; i < nChars; i++)
    {
        if (pszText[i] == ' ')
            continue;
        nIndex = pszText[i] - ' ';
        nRow = nIndex / desc.tilewidth;
        nCol = nIndex - nRow * desc.tilewidth;
        // (the half texel offset RtCharset's own printing uses on D3D)
        fU0 = (RwReal)(nCol * desc.width_internal) / fRasW + 0.5f / fRasW;
        fV0 = (RwReal)(nRow * desc.height_internal) / fRasH + 0.5f / fRasH;
        fU1 = fU0 + (RwReal)desc.width / fRasW;
        fV1 = fV0 + (RwReal)desc.height / fRasH;
        vP0.x = vCorner.x + vRight.x * fW * i;
        vP0.y = vCorner.y + vRight.y * fW * i;
        vP0.z = vCorner.z + vRight.z * fW * i;
        vP1.x = vP0.x - vUp.x * fH;
        vP1.y = vP0.y - vUp.y * fH;
        vP1.z = vP0.z - vUp.z * fH;
        vP2.x = vP1.x + vRight.x * fW;
        vP2.y = vP1.y + vRight.y * fW;
        vP2.z = vP1.z + vRight.z * fW;
        vP3.x = vP0.x + vRight.x * fW;
        vP3.y = vP0.y + vRight.y * fW;
        vP3.z = vP0.z + vRight.z * fW;
        pVert = &s_aTextVerts[nVerts];
        // two triangles: P0 P1 P2 and P0 P2 P3
        RwIm3DVertexSetPos(&pVert[0], vP0.x, vP0.y, vP0.z);
        RwIm3DVertexSetU(&pVert[0], fU0);
        RwIm3DVertexSetV(&pVert[0], fV0);
        RwIm3DVertexSetPos(&pVert[1], vP1.x, vP1.y, vP1.z);
        RwIm3DVertexSetU(&pVert[1], fU0);
        RwIm3DVertexSetV(&pVert[1], fV1);
        RwIm3DVertexSetPos(&pVert[2], vP2.x, vP2.y, vP2.z);
        RwIm3DVertexSetU(&pVert[2], fU1);
        RwIm3DVertexSetV(&pVert[2], fV1);
        pVert[3] = pVert[0];
        pVert[4] = pVert[2];
        RwIm3DVertexSetPos(&pVert[5], vP3.x, vP3.y, vP3.z);
        RwIm3DVertexSetU(&pVert[5], fU1);
        RwIm3DVertexSetV(&pVert[5], fV0);
        pVert[0].color = pVert[1].color = pVert[2].color = dwColour;
        pVert[3].color = pVert[4].color = pVert[5].color = dwColour;
        nVerts += 6;
    }
    if (nVerts == 0)
        return;
    if (RwIm3DTransform(s_aTextVerts, nVerts, NULL, rwIM3D_VERTEXUV | rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA))
    {
        RwIm3DRenderPrimitive(rwPRIMTYPETRILIST);
        RwIm3DEnd();
    }
}

// Writes the trigger's type at its centre (the matrix's position), and the name the level
// gives it (trignames.cpp), when it has one, on the line above.
static void TrigDrawActLines(Trigger *pTrigger, const RwV3d *pvCentre, const RwMatrix *pCamLtm);

static void TrigDrawLabel(Trigger *pTrigger, const RwMatrix *pCamLtm, RwUInt32 dwColour)
{
    RwV3d vCentre;
    const RwChar *pszName = g_bTrigDrawNames ? TrigDrawTriggerName(pTrigger) : NULL;

    vCentre.x = pTrigger->unk_90;
    vCentre.y = pTrigger->unk_94;
    vCentre.z = pTrigger->unk_98;
    TrigDrawText(TrigDrawKindName(pTrigger), &vCentre, pCamLtm, dwColour);
    if (pszName != NULL)
        TrigDrawText(pszName, &vCentre, pCamLtm, dwColour, 1.0f);
    TrigDrawSpawnerLines(pTrigger, &vCentre, pCamLtm, dwColour);
    TrigDrawActLines(pTrigger, &vCentre, pCamLtm);
}

// ---- the path nodes ----

// The AI's path-node graph (unk_4C00E8, which sub_F8350 loads from the
// level's GodData: the cfh-web-suite's PATHFINDING.md): each node a marker
// (a cross and a post) coloured by its stored type, its links lines to the
// nodes they name (two 12-bit node IDs a link word, bits 24 and 25 their
// traversal flags: a link with a flag set, which the A* expansion skips, is
// red), and with labels the node's ID and type. Within the path range of
// the camera; a type filter keeps one type (and the links between its
// nodes). The graph is the level's: multiplayer maps have none.
RwBool g_bTrigDrawPathNodes = FALSE;
RwBool g_bTrigDrawPathLinks = TRUE;
RwBool g_bTrigDrawPathLabels = FALSE;
RwReal g_fTrigDrawPathRange = 3000.0f;
RwInt32 g_nTrigDrawPathType = -1;           // -1 all
RwInt32 g_nTrigDrawPathShown, g_nTrigDrawPathLinksShown;

#define TRIGDRAW_PATHVERTS  4000
static RwIm3DVertex s_aPathVerts[TRIGDRAW_PATHVERTS];
static RwInt32 s_nPathVerts;

// The stored types' names (the cfh-web-suite's node_types.py, AI_NODE_TYPES.md).
static const RwChar *const s_apszPathTypes[20] =
{
    "unidentified", "waypoint", "door control", "cover corner +X", "cover corner -X", "over-top cover A",
    "height waypoint 6", "door staging -X", "door staging +X", "over-top cover B", "height waypoint 10",
    "cover 100", "cover 200", "cover 188", "free combat", "facing marker 15", "facing marker 16",
    "mounted weapon", "alarm", "persistent cover"
};

const RwChar *TrigDrawPathTypeName(RwInt32 nType)
{
    return nType >= 0 && nType < 20 ? s_apszPathTypes[nType] : "?";
}

static const RwUInt32 s_adwPathColours[8] =
{
    0x0040FF40, 0x00FFFF40, 0x0040C0FF, 0x00FF8040, 0x00FF40FF, 0x0040FFFF, 0x00FFFFFF, 0x00C080FF
};

static RwUInt32 TrigDrawPathColour(RwInt32 nType)
{
    if (nType == 1)
        return 0xC060FF60;      // the waypoints, most of the graph
    return 0xE0000000 | s_adwPathColours[(RwUInt32)nType & 7];
}

static void TrigDrawPathFlush()
{
    if (s_nPathVerts == 0)
        return;
    if (RwIm3DTransform(s_aPathVerts, s_nPathVerts, NULL, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA))
    {
        RwIm3DRenderPrimitive(rwPRIMTYPELINELIST);
        RwIm3DEnd();
    }
    s_nPathVerts = 0;
}

static void TrigDrawPathLine(const RwV3d *pA, const RwV3d *pB, RwUInt32 dwColour)
{
    if (s_nPathVerts + 2 > TRIGDRAW_PATHVERTS)
        TrigDrawPathFlush();
    RwIm3DVertexSetPos(&s_aPathVerts[s_nPathVerts], pA->x, pA->y, pA->z);
    s_aPathVerts[s_nPathVerts].color = dwColour;
    RwIm3DVertexSetPos(&s_aPathVerts[s_nPathVerts + 1], pB->x, pB->y, pB->z);
    s_aPathVerts[s_nPathVerts + 1].color = dwColour;
    s_nPathVerts += 2;
}

// Node nId, or NULL (0 is the null node).
static type_F8350 *TrigDrawPathNode(RwInt32 nId)
{
    if (nId <= 0 || nId >= unk_4C00E8.unk_08 || unk_4C00E8.unk_2C == NULL)
        return NULL;
    return unk_4C00E8.unk_2C[nId];
}

// The node's link words: from +0x1C, or +0x2C with its orientation (flag bit 0).
static const RwUInt32 *TrigDrawPathLinks(type_F8350 *pNode)
{
    return (const RwUInt32 *)((const RwUInt8 *)pNode + (pNode->unk_00_0 ? 0x2C : 0x1C));
}

static RwBool TrigDrawPathNear(const RwV3d *pv, const RwV3d *pvCam)
{
    RwReal fDX = pv->x - pvCam->x, fDY = pv->y - pvCam->y, fDZ = pv->z - pvCam->z;

    return g_fTrigDrawPathRange <= 0.0f
        || fDX * fDX + fDY * fDY + fDZ * fDZ <= g_fTrigDrawPathRange * g_fTrigDrawPathRange;
}

// Whether node nTo links back to nFrom (a two-way link is drawn once).
static RwBool TrigDrawPathLinksTo(RwInt32 nFrom, RwInt32 nTo)
{
    type_F8350 *pNode = TrigDrawPathNode(nTo);
    const RwUInt32 *p;
    RwInt32 i;

    if (pNode == NULL)
        return FALSE;
    p = TrigDrawPathLinks(pNode);
    for (i = 0; i < 64; i++, p++)
    {
        RwInt32 nA = (RwInt32)(*p & 0xFFF), nB = (RwInt32)((*p >> 12) & 0xFFF);

        if (nA == 0)
            break;
        if (nA == nFrom || nB == nFrom)
            return TRUE;
        if (nB == 0)
            break;
    }
    return FALSE;
}

// Draws the graph near the camera at pvCam (with the camera's matrix for the labels).
static void TrigDrawPaths(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwInt32 nId, nCount = unk_4C00E8.unk_08, i, k;

    g_nTrigDrawPathShown = g_nTrigDrawPathLinksShown = 0;
    if (!unk_4C00E8.unk_64 || unk_4C00E8.unk_2C == NULL || nCount <= 1)
        return;
    if (nCount > 4096)
        nCount = 4096;
    s_nPathVerts = 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (nId = 1; nId < nCount; nId++)
    {
        type_F8350 *pNode = TrigDrawPathNode(nId);
        RwV3d vAt, vA, vB;
        RwUInt32 dwColour;
        const RwUInt32 *p;

        if (pNode == NULL || !TrigDrawPathNear(&pNode->unk_10, pvCam))
            continue;
        if (g_nTrigDrawPathType >= 0 && pNode->unk_04 != g_nTrigDrawPathType)
            continue;
        g_nTrigDrawPathShown++;
        vAt = pNode->unk_10;
        dwColour = TrigDrawPathColour(pNode->unk_04);
        // the marker: a cross at the node and a post up from it
        vA = vAt;
        vB = vAt;
        vA.x -= 25.0f;
        vB.x += 25.0f;
        TrigDrawPathLine(&vA, &vB, dwColour);
        vA = vAt;
        vB = vAt;
        vA.z -= 25.0f;
        vB.z += 25.0f;
        TrigDrawPathLine(&vA, &vB, dwColour);
        vB = vAt;
        vB.y += 60.0f;
        TrigDrawPathLine(&vAt, &vB, dwColour);
        if (!g_bTrigDrawPathLinks)
            continue;
        // the links: each two-way one once (from the lower ID), one-way ones always
        p = TrigDrawPathLinks(pNode);
        for (i = 0; i < 64; i++, p++)
        {
            for (k = 0; k < 2; k++)
            {
                RwInt32 nTo = (RwInt32)((*p >> (k * 12)) & 0xFFF);
                RwBool bBlocked = ((*p >> (24 + k)) & 1) != 0;
                type_F8350 *pTo;

                if (nTo == 0)
                    break;
                pTo = TrigDrawPathNode(nTo);
                if (pTo == NULL)
                    continue;
                if (g_nTrigDrawPathType >= 0 && pTo->unk_04 != g_nTrigDrawPathType)
                    continue;
                if (nTo < nId && TrigDrawPathLinksTo(nId, nTo) && TrigDrawPathNear(&pTo->unk_10, pvCam))
                    continue;
                vA = vAt;
                vA.y += 10.0f;
                vB = pTo->unk_10;
                vB.y += 10.0f;
                TrigDrawPathLine(&vA, &vB, bBlocked ? 0xE0FF3030 : 0x9080C0FF);
                g_nTrigDrawPathLinksShown++;
            }
            if (k < 2)
                break;
        }
    }
    TrigDrawPathFlush();
    // the labels: the node's ID and type, within a third of the range
    if (g_bTrigDrawPathLabels && TrigDrawCharset() != NULL)
    {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
        for (nId = 1; nId < nCount; nId++)
        {
            type_F8350 *pNode = TrigDrawPathNode(nId);
            RwV3d vAt, vD;
            RwChar szText[TRIGDRAW_MAXCHARS];

            if (pNode == NULL || (g_nTrigDrawPathType >= 0 && pNode->unk_04 != g_nTrigDrawPathType))
                continue;
            vD.x = pNode->unk_10.x - pvCam->x;
            vD.y = pNode->unk_10.y - pvCam->y;
            vD.z = pNode->unk_10.z - pvCam->z;
            if (vD.x * vD.x + vD.y * vD.y + vD.z * vD.z > g_fTrigDrawPathRange * g_fTrigDrawPathRange / 9.0f)
                continue;
            vAt = pNode->unk_10;
            vAt.y += 80.0f;
            _snprintf(szText, sizeof(szText) - 1, "%d %s", nId, TrigDrawPathTypeName(pNode->unk_04));
            szText[sizeof(szText) - 1] = 0;
            TrigDrawText(szText, &vAt, pCamLtm, 0xFF000000 | TrigDrawPathColour(pNode->unk_04));
        }
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    }
}

// ---- the AI ----

// What each AI is doing, over its head and as lines: its AI object's
// (AIData, the entity's vf_120) state code (unk_578) and alert (unk_520),
// its hit points, the entity it tracks (unk_1374: a red line), its target
// point (unk_4F0: orange), where it aims (a soldier's aim object's world
// point, from its aim blend's origin, as type_3DAFC8::vf_244 takes them: yellow), the path it follows (unk_8AC's nodes
// in the path-node graph: cyan) and its current node (unk_F60: green); and
// the game's own words for what it is thinking: the last lines its AI code
// logged about it (the entity-tagged sub_19A750, as the A* scheduler's "AStar
// search registered. Type: eASST_...") and the script messages it raised
// (sub_6B5F0: "FoundTarget", "AStar_ArrivedATDestination", "AIAction_..."),
// with their age. Also: the task its object runs (its script, function and
// line, when the scripts keep lines), its behaviour script's state, the
// path's A* request (its kind, the path's own request parameter; whether
// found, its length, the start and goal nodes by ID and type; the goal a
// magenta cross) and its current and next nodes. The search's eASST type is
// in the notes, from the scheduler's own log. A note repeated is one line
// with its count. Within the AI range of the camera; players left out.
RwBool g_bTrigDrawAi = FALSE;
RwBool g_bTrigDrawAiText = TRUE;
RwBool g_bTrigDrawAiLines = TRUE;
RwBool g_bTrigDrawAiPath = TRUE;
// Its cover: the cover search radius (unk_F6C, a circle), the cover nodes its
// two node searches found (unk_F80, unk_10C4: small posts, grey once tried),
// the node found (unk_F54), next (unk_F5C) and left (unk_F58), its vehicle
// cover point (unk_4F4) and its five cover records' points (unk_12F4 on).
RwBool g_bTrigDrawAiCover = FALSE;
// Its perception and fighting: where it last saw the entity it tracks
// (unk_1380, a white cross), how long it has tracked it (unk_1378), what it
// hears (the classes, kinds and sides, unk_538 to unk_540), whether it may
// lose sight of its target (unk_52C), its AI control (unk_51C), the nearest
// blocker to a player target (unk_139C), the shots left in its burst
// (unk_498), its timers in and out of its fighting states (unk_550,
// unk_554), and its weapon (a soldier's unk_3E0: type, the soldiers' own
// numbering, not the player's weapons'; ammunition, time to its next shot,
// the point it aims its weapon at).
RwBool g_bTrigDrawAiCombat = FALSE;
RwReal g_fTrigDrawAiRange = 3000.0f;
RwInt32 g_nTrigDrawAiShown;

#define TRIGDRAW_AI_ENTITIES    96
#define TRIGDRAW_AI_NOTES       4
#define TRIGDRAW_AI_NOTE        72

struct TrigDrawAiNotes
{
    const void *pEntity;
    RwUInt32 dwLast;                    // the frame of its newest note
    RwInt32 nNext;
    RwUInt32 adwFrame[TRIGDRAW_AI_NOTES];
    RwInt32 anRepeats[TRIGDRAW_AI_NOTES];   // the same note again (1 once)
    RwChar aszText[TRIGDRAW_AI_NOTES][TRIGDRAW_AI_NOTE];
};
static TrigDrawAiNotes s_aAiNotes[TRIGDRAW_AI_ENTITIES];
extern RwBool g_bTrigLiveDebug;          // (a live viewer takes the debug feed: the notes are kept)
static volatile LONG s_nAiNotesLock;

static void TrigDrawNoteKeep(TrigDrawAiNotes *pAll, RwInt32 nAll, const void *pKey, const RwChar *pszText);

// Keeps a note about the entity pEntity (its newest four), for its label.
void TrigDrawAiNote(const void *pEntity, const RwChar *pszText)
{
    RwChar szShort[TRIGDRAW_AI_NOTE];
    const RwChar *p;

    if ((!g_bTrigDrawAi && !g_bTrigDrawGimps && !g_bTrigLiveDebug) || pEntity == NULL || pszText == NULL)
        return;
    // (the A* scheduler's lines, shortened to the search type the game names: "A* eASST_...")
    static const RwChar s_szRegistered[] = "AStar search registered. Type: ";
    static const RwChar s_szUnregistering[] = "Unregistering A* search for object. Type: ";
    if (strncmp(pszText, s_szRegistered, sizeof(s_szRegistered) - 1) == 0 ||
        strncmp(pszText, s_szUnregistering, sizeof(s_szUnregistering) - 1) == 0)
    {
        RwBool bDone = pszText[0] == 'U';

        p = strstr(pszText, "Type: ") + 6;
        _snprintf(szShort, sizeof(szShort) - 1, "A* %s%s", bDone ? "done " : "", p);
        szShort[sizeof(szShort) - 1] = 0;
        if (strchr(szShort, ','))
            *strchr(szShort, ',') = 0;
        pszText = szShort;
    }
    TrigDrawNoteKeep(s_aAiNotes, TRIGDRAW_AI_ENTITIES, pEntity, pszText);
}

// Keeps the note pszText under pKey in pAll (nAll keys, the oldest
// replaced): its newest four, a repeat counted on the newest.
static void TrigDrawNoteKeep(TrigDrawAiNotes *pAll, RwInt32 nAll, const void *pKey, const RwChar *pszText)
{
    TrigDrawAiNotes *pNotes = NULL;
    RwInt32 i, nOldest = 0;

    while (InterlockedExchange(&s_nAiNotesLock, 1))
        ;
    for (i = 0; i < nAll; i++)
    {
        if (pAll[i].pEntity == pKey)
        {
            pNotes = &pAll[i];
            break;
        }
        if (pAll[i].dwLast < pAll[nOldest].dwLast)
            nOldest = i;
    }
    if (pNotes == NULL)
    {
        pNotes = &pAll[nOldest];
        memset(pNotes, 0, sizeof(*pNotes));
        pNotes->pEntity = pKey;
    }
    pNotes->dwLast = port_frame ? port_frame : 1;
    {
        RwInt32 nNewest = (pNotes->nNext + TRIGDRAW_AI_NOTES - 1) % TRIGDRAW_AI_NOTES;

        if (pNotes->adwFrame[nNewest] && strncmp(pNotes->aszText[nNewest], pszText, TRIGDRAW_AI_NOTE - 1) == 0)
        {
            pNotes->adwFrame[nNewest] = pNotes->dwLast;
            pNotes->anRepeats[nNewest]++;
            InterlockedExchange(&s_nAiNotesLock, 0);
            return;
        }
    }
    pNotes->anRepeats[pNotes->nNext] = 1;
    pNotes->adwFrame[pNotes->nNext] = pNotes->dwLast;
    strncpy(pNotes->aszText[pNotes->nNext], pszText, TRIGDRAW_AI_NOTE - 1);
    pNotes->aszText[pNotes->nNext][TRIGDRAW_AI_NOTE - 1] = 0;
    pNotes->nNext = (pNotes->nNext + 1) % TRIGDRAW_AI_NOTES;
    InterlockedExchange(&s_nAiNotesLock, 0);
}

// A script message (sub_6B5F0) sent to the script object pScript: noted for
// the entity the object belongs to.
void TrigDrawAiMessage(const RwChar *pszName, type_67620 *pScript)
{
    const void *pEntity = NULL;

    if ((!g_bTrigDrawAi && !g_bTrigDrawGimps && !g_bTrigLiveDebug) || pScript == NULL || pszName == NULL)
        return;
    __try
    {
        type_3D2E7C *pObject = pScript->vf_024();

        if (pObject)
            pEntity = pObject->sub_71300();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pEntity = NULL;
    }
    if (pEntity)
    {
        RwChar sz[TRIGDRAW_AI_NOTE];

        _snprintf(sz, sizeof(sz) - 1, "> %s", pszName);
        sz[sizeof(sz) - 1] = 0;
        TrigDrawAiNote(pEntity, sz);
    }
}

// One AI's state, read guarded (an entity can go while it is read).
struct TrigDrawAiState
{
    RwV3d vPos, vTarget, vPoint, vAim, vAimFrom, vNode;
    RwBool bTarget, bPoint, bAim, bNode;
    RwInt32 nState, nAlert, nHp, nTargetSlot;
    RwInt32 nPath;
    RwV3d avPath[32];
    // its object's task (type_3D2E7C::sub_71090, a type_3D2E20): its script, function, place and
    // whether it waits
    RwBool bTask;
    RwInt32 nTaskScript, nTaskFunction, nTaskLine, nTaskWaits;
    RwChar szTaskFile[40];
    // its behaviour script (the state machine whose owner is its object): place and state
    RwBool bMachine;
    RwInt32 nMachineLine, nMachineState;
    RwChar szMachineFile[40];
    // the path it follows (unk_8AC): its A* request's kind, result, length, start and goal
    // nodes, the waypoints left, the goal point
    RwBool bPathSearch;
    RwInt32 nSearchKind, nSearchResult, nSearchLength, nStartNode, nGoalNode, nGoalType, nLeft;
    RwV3d vGoal;
    RwBool bGoal;
    // its nodes: the current (unk_F60) and the one found next (unk_F5C)
    RwInt32 nNodeId, nNodeType, nNextId, nNextType;
    // its cover
    RwReal fCoverRadius;
    RwInt32 nCandidates, nTried;
    RwV3d avCandidate[35];
    RwBool abTried[35];
    RwV3d avCoverNode[3];               // found, next, left
    RwBool abCoverNode[3];
    RwV3d avCoverPoint[6];              // the vehicle cover point, the five records
    RwInt32 nCoverPoints;
    // its perception and fighting
    RwBool bSeen;
    RwV3d vSeen;
    RwReal fTracked, fBlocker, fIn, fOut;
    RwInt32 nHearClasses, nHearKinds, nHearSides, nLosLoss, nControl, nShots;
    RwBool bWeapon;
    RwInt32 nWeaponType, nAmmo, nInfinite, nNoTarget, nAimsWeapon;
    RwReal fNextShot;
    RwV3d vWeaponAim;
};

// The live state machines' owners and machines (the m_stateMachineObjectPool's
// elements not on its free list, walked as trigtools.cpp's Scripts tab does),
// gathered once a frame for the AI's behaviour scripts.
extern type_16C2A0 dword_449A30;
static RwUInt32 s_adwMachineOwner[1100];
static type_3D2DB8 *s_apMachine[1100];
static RwInt32 s_nMachines;

static void TrigDrawAiMachines()
{
    static RwUInt8 s_abFree[1100];

    s_nMachines = 0;
    __try
    {
        type_16C2A0 *pPool = &dword_449A30;
        RwUInt8 *p = pPool->unk_08, *pBase = (RwUInt8 *)pPool->unk_04;
        RwInt32 nStride = pPool->unk_10, nCount = pPool->unk_0C;
        RwInt32 nNext = nStride - ((pPool->unk_00 & 2) ? 4 : 0);
        RwInt32 i, nIndex;

        if (pBase == NULL || nStride <= 0 || nCount <= 0 || nCount > 1100)
            return;
        memset(s_abFree, 0, nCount);
        for (i = 0; p != NULL && i < nCount; i++)
        {
            nIndex = (RwInt32)(p - pBase) / nStride;
            if (nIndex < 0 || nIndex >= nCount)
                break;
            s_abFree[nIndex] = 1;
            p = *(RwUInt8 **)(p + nNext);
        }
        for (i = 0; i < nCount; i++)
        {
            if (s_abFree[i])
                continue;
            s_apMachine[s_nMachines] = (type_3D2DB8 *)(pBase + i * nStride);
            s_adwMachineOwner[s_nMachines] = s_apMachine[s_nMachines]->unk_7C;
            s_nMachines++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        s_nMachines = 0;
    }
}

// A script's file: its name when the word points at text, else its number.
static void TrigDrawAiFile(RwUInt32 dwFile, RwChar *psz, RwInt32 nMax)
{
    RwInt32 i;

    if (dwFile <= 0x10000)
    {
        _snprintf(psz, nMax - 1, "%d", (RwInt32)dwFile);
        psz[nMax - 1] = 0;
        return;
    }
    for (i = 0; i < nMax - 1; i++)
    {
        RwChar c = ((const RwChar *)dwFile)[i];

        if (c == 0)
            break;
        psz[i] = (RwUInt8)c < 0x20 || (RwUInt8)c > 0x7E ? '.' : c;
    }
    psz[i] = 0;
}

// The ID of the node pNode in the graph, 0 for none.
static RwInt32 TrigDrawPathNodeId(type_F8350 *pNode)
{
    RwInt32 i;

    if (pNode == NULL || unk_4C00E8.unk_2C == NULL)
        return 0;
    for (i = 1; i < unk_4C00E8.unk_08 && i < 4096; i++)
        if (unk_4C00E8.unk_2C[i] == pNode)
            return i;
    return 0;
}

static RwBool TrigDrawAiRead(type_3D3548 *pEntity, RwUInt32 dwBits, TrigDrawAiState *pState)
{
    __try
    {
        AIData *pAi = pEntity->vf_120();
        RwFrame *pFrame = pEntity->unk_338.unk_08;
        type_3D3548 *pTarget;
        type_F8350 *pNode;
        RwInt32 i, n;

        if (pAi == NULL || pFrame == NULL)
            return FALSE;
        pState->vPos = RwFrameGetMatrix(pFrame)->pos;
        pState->nState = pAi->get_unk_578();
        pState->nAlert = pAi->get_unk_520();
        pState->nHp = pEntity->vf_174();
        pTarget = pAi->unk_1374.sub_D4910();
        pState->bTarget = FALSE;
        pState->nTargetSlot = -1;
        if (pTarget && pTarget->unk_338.unk_08)
        {
            pState->vTarget = RwFrameGetMatrix(pTarget->unk_338.unk_08)->pos;
            pState->bTarget = TRUE;
            for (i = 0; i < 768; i++)
                if (dword_4B6A00[i].unk_04 == pTarget)
                {
                    pState->nTargetSlot = i;
                    break;
                }
        }
        pState->bPoint = pAi->unk_4F0 != NULL;
        if (pState->bPoint)
            pState->vPoint = *pAi->unk_4F0;
        // (a soldier's aim, as type_3DAFC8::vf_244 finds it before turning it into its five-way
        // blend's local point: the world point its aim object (unk_3E0) or, mounted, its
        // vehicle gives, from the blend's origin, unk_1D64 in its frame)
        pState->bAim = FALSE;
        if (dwBits & 0x20)
        {
            type_3DAFC8 *pSoldier = (type_3DAFC8 *)pEntity;

            if (pSoldier->get_unk_61C())
            {
                type_3DC9B0 *pVehicle = (type_3DC9B0 *)pSoldier->unk_618.sub_D4910();

                if (pVehicle)
                {
                    pVehicle->sub_16A580(&pState->vAim);
                    pState->bAim = TRUE;
                }
            }
            else
            {
                pSoldier->unk_3E0.sub_15E9E0(&pState->vAim);
                pState->bAim = TRUE;
            }
            if (pState->bAim)
                RwV3dTransformPoints(&pState->vAimFrom, &pSoldier->unk_1D64, 1, RwFrameGetLTM(pFrame));
        }
        pNode = pAi->get_unk_F60();
        pState->bNode = pNode != NULL;
        if (pNode)
            pState->vNode = pNode->unk_10;
        pState->nNodeId = TrigDrawPathNodeId(pNode);
        pState->nNodeType = pNode ? pNode->unk_04 : -1;
        pState->nNextId = TrigDrawPathNodeId(pAi->unk_F5C);
        pState->nNextType = pAi->unk_F5C ? pAi->unk_F5C->unk_04 : -1;
        // the task its object runs, and its behaviour script (by its object's handle)
        pState->bTask = FALSE;
        pState->bMachine = FALSE;
        {
            type_3D2E7C *pObject = pEntity->vf_098();

            if (pObject)
            {
                type_3D2E20 *pTask = (type_3D2E20 *)pObject->sub_71090();
                RwUInt32 dwHandle = pObject->get_unk_04();

                if (pTask)
                {
                    pState->bTask = TRUE;
                    pState->nTaskScript = pTask->unk_64;
                    pState->nTaskFunction = pTask->unk_108;
                    pState->nTaskLine = pTask->unk_08;
                    pState->nTaskWaits = pTask->unk_10C;
                    TrigDrawAiFile((RwUInt32)pTask->unk_0C, pState->szTaskFile, sizeof(pState->szTaskFile));
                }
                for (i = 0; i < s_nMachines; i++)
                    if (s_adwMachineOwner[i] == dwHandle)
                    {
                        pState->bMachine = TRUE;
                        pState->nMachineLine = s_apMachine[i]->unk_08;
                        pState->nMachineState = s_apMachine[i]->unk_90;
                        TrigDrawAiFile((RwUInt32)s_apMachine[i]->unk_0C, pState->szMachineFile,
                                       sizeof(pState->szMachineFile));
                        break;
                    }
            }
        }
        // its cover
        {
            type_154C0_12F4 *apRecord[5];
            type_F8350 *apNode[3];

            pState->fCoverRadius = pAi->unk_F6C;
            pState->nCandidates = pState->nTried = 0;
            for (i = 0; i < 35; i++)
            {
                const type_154C0_F80 *r = i < 25 ? &pAi->unk_F80[i] : &pAi->unk_10C4[i - 25];
                type_F8350 *pCand = TrigDrawPathNode(r->unk_00);

                if (pCand == NULL)
                    continue;
                pState->avCandidate[pState->nCandidates] = pCand->unk_10;
                pState->abTried[pState->nCandidates] = r->unk_02 != 0;
                pState->nTried += r->unk_02 != 0;
                pState->nCandidates++;
            }
            apNode[0] = pAi->unk_F54;
            apNode[1] = pAi->unk_F5C;
            apNode[2] = pAi->unk_F58;
            for (i = 0; i < 3; i++)
            {
                pState->abCoverNode[i] = apNode[i] != NULL;
                if (apNode[i])
                    pState->avCoverNode[i] = apNode[i]->unk_10;
            }
            pState->nCoverPoints = 0;
            if (pAi->unk_4F4.x != 0.0f || pAi->unk_4F4.y != 0.0f || pAi->unk_4F4.z != 0.0f)
                pState->avCoverPoint[pState->nCoverPoints++] = pAi->unk_4F4;
            apRecord[0] = &pAi->unk_12F4;
            apRecord[1] = &pAi->unk_130C;
            apRecord[2] = &pAi->unk_1324;
            apRecord[3] = &pAi->unk_133C;
            apRecord[4] = &pAi->unk_1354;
            for (i = 0; i < 5; i++)
                if (apRecord[i]->unk_0C.x != 0.0f || apRecord[i]->unk_0C.y != 0.0f || apRecord[i]->unk_0C.z != 0.0f)
                    pState->avCoverPoint[pState->nCoverPoints++] = apRecord[i]->unk_0C;
        }
        // its perception and fighting
        pState->bSeen = pState->bTarget &&
                        (pAi->unk_1380.x != 0.0f || pAi->unk_1380.y != 0.0f || pAi->unk_1380.z != 0.0f);
        pState->vSeen = pAi->unk_1380;
        pState->fTracked = pAi->unk_1378;
        pState->fBlocker = pAi->unk_139C;
        pState->fIn = pAi->unk_550;
        pState->fOut = pAi->unk_554;
        pState->nHearClasses = pAi->unk_538;
        pState->nHearKinds = pAi->unk_53C;
        pState->nHearSides = pAi->unk_540;
        pState->nLosLoss = pAi->unk_52C;
        pState->nControl = pAi->unk_51C;
        pState->nShots = pAi->unk_498;
        pState->bWeapon = (dwBits & 0x20) != 0;
        if (pState->bWeapon)
        {
            type_15CCE0 *pWeapon = &((type_3DAFC8 *)pEntity)->unk_3E0;

            pState->nWeaponType = pWeapon->unk_04;
            pState->nAmmo = pWeapon->unk_1C;
            pState->nInfinite = pWeapon->unk_20;
            pState->fNextShot = pWeapon->unk_88;
            pState->nNoTarget = pWeapon->unk_A0;
            pState->nAimsWeapon = pWeapon->unk_CC;
            pState->vWeaponAim = pWeapon->unk_D0;
        }
        // the path it follows: its A* request and goal
        // (shown once found, or with a goal node asked for)
        pState->bPathSearch = pAi->unk_8AC.unk_64.unk_28 == 1 || pAi->unk_8AC.unk_64.unk_40 != 0;
        pState->nSearchKind = pAi->unk_8AC.unk_64.unk_1C;
        pState->nSearchResult = pAi->unk_8AC.unk_64.unk_28;
        pState->nSearchLength = pAi->unk_8AC.unk_64.unk_2C;
        pState->nStartNode = pAi->unk_8AC.unk_64.unk_38;
        pState->nGoalNode = pAi->unk_8AC.unk_64.unk_40;
        pState->nGoalType = TrigDrawPathNode(pState->nGoalNode) ? TrigDrawPathNode(pState->nGoalNode)->unk_04 : -1;
        pState->nLeft = pAi->unk_8AC.unk_04;
        pState->bGoal = pState->nLeft > 0;
        if (pState->bGoal)
            pState->vGoal = pAi->unk_8AC.unk_20;
        // the path it follows: its nodes' places, in the order the path keeps them
        pState->nPath = 0;
        n = pAi->unk_8AC.unk_64.unk_2C;
        if (n > 0 && unk_4C00E8.unk_64 && unk_4C00E8.unk_2C)
        {
            for (i = 0; i < n && i < 100 && pState->nPath < 32; i++)
            {
                type_F8350 *pPathNode = TrigDrawPathNode(pAi->unk_8AC.unk_B0[i]);

                if (pPathNode)
                    pState->avPath[pState->nPath++] = pPathNode->unk_10;
            }
        }
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// Draws every AI near the camera at pvCam.
// Adds the notes kept under pKey in pAll to aszLines from line nLines,
// newest first, with their age in seconds; the lines then.
static RwInt32 TrigDrawNoteLines(TrigDrawAiNotes *pAll, RwInt32 nAll, const void *pKey,
                                 RwChar (*aszLines)[TRIGDRAW_AI_NOTE + 16], RwInt32 nLines)
{
    TrigDrawAiNotes *pNotes = NULL;
    RwInt32 j;

    for (j = 0; j < nAll; j++)
        if (pAll[j].pEntity == pKey)
        {
            pNotes = &pAll[j];
            break;
        }
    for (j = 0; pNotes && j < TRIGDRAW_AI_NOTES; j++)
    {
        RwInt32 n = (pNotes->nNext + TRIGDRAW_AI_NOTES - 1 - j) % TRIGDRAW_AI_NOTES;

        if (!pNotes->adwFrame[n])
            continue;
        if (pNotes->anRepeats[n] > 1)
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE + 15, "%.0fs %s (x%d)",
                      (RwReal)(port_frame - pNotes->adwFrame[n]) / 60.0f, pNotes->aszText[n], pNotes->anRepeats[n]);
        else
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE + 15, "%.0fs %s",
                      (RwReal)(port_frame - pNotes->adwFrame[n]) / 60.0f, pNotes->aszText[n]);
    }
    return nLines;
}

// The label's lines, stacked up the screen from pvAt (the first on top):
// white, the last nNotes orange.
static void TrigDrawLines(RwChar (*aszLines)[TRIGDRAW_AI_NOTE + 16], RwInt32 nLines, RwInt32 nNotes,
                          const RwV3d *pvAt, RwReal fDist, const RwMatrix *pCamLtm)
{
    RwReal fStep = fDist * g_fTrigDrawTextScale * 1.2f;
    RwInt32 j;

    if (fStep < 0.06f)
        fStep = 0.06f;
    for (j = 0; j < nLines; j++)
    {
        RwV3d vAt;

        aszLines[j][TRIGDRAW_AI_NOTE + 15] = 0;
        vAt.x = pvAt->x + pCamLtm->up.x * fStep * (RwReal)(nLines - j);
        vAt.y = pvAt->y + pCamLtm->up.y * fStep * (RwReal)(nLines - j);
        vAt.z = pvAt->z + pCamLtm->up.z * fStep * (RwReal)(nLines - j);
        TrigDrawText(aszLines[j], &vAt, pCamLtm, j < nLines - nNotes ? 0xFFFFFFFF : 0xFFFFD080);
    }
}

static void TrigDrawAi(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    static TrigDrawAiState s_state;
    RwInt32 i, k;

    g_nTrigDrawAiShown = 0;
    s_nPathVerts = 0;
    TrigDrawAiMachines();
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < 768; i++)
    {
        type_3D3548 *pEntity = dword_4B6A00[i].unk_04;
        RwUInt32 dwBits;
        RwV3d vHead, vD, vEye;
        TrigDrawAiState *s = &s_state;

        if (pEntity == NULL)
            continue;
        dwBits = pEntity->unk_2C;
        if (dwBits & 0x10)
            continue;               // (players)
        if (!TrigDrawAiRead(pEntity, dwBits, s))
            continue;
        vD.x = s->vPos.x - pvCam->x;
        vD.y = s->vPos.y - pvCam->y;
        vD.z = s->vPos.z - pvCam->z;
        if (g_fTrigDrawAiRange > 0.0f && vD.x * vD.x + vD.y * vD.y + vD.z * vD.z > g_fTrigDrawAiRange * g_fTrigDrawAiRange)
            continue;
        g_nTrigDrawAiShown++;
        vEye = s->vPos;
        vEye.y += 160.0f;
        if (g_bTrigDrawAiLines)
        {
            if (s->bTarget)
                TrigDrawPathLine(&vEye, &s->vTarget, 0xE0FF3030);
            if (s->bPoint)
                TrigDrawPathLine(&vEye, &s->vPoint, 0xE0FF9020);
            if (s->bAim)
                TrigDrawPathLine(&s->vAimFrom, &s->vAim, 0xE0FFFF40);
            if (s->bNode)
                TrigDrawPathLine(&s->vPos, &s->vNode, 0xE040FF40);
        }
        if (g_bTrigDrawAiCover)
        {
            // the search radius (a circle at its feet), the candidates, its nodes, its cover points
            if (s->fCoverRadius > 0.0f)
                for (k = 0; k < 32; k++)
                {
                    RwReal a0 = (RwReal)k * (6.2831853f / 32), a1 = (RwReal)(k + 1) * (6.2831853f / 32);
                    RwV3d vA = s->vPos, vB = s->vPos;

                    vA.x += (RwReal)cos(a0) * s->fCoverRadius;
                    vA.z += (RwReal)sin(a0) * s->fCoverRadius;
                    vB.x += (RwReal)cos(a1) * s->fCoverRadius;
                    vB.z += (RwReal)sin(a1) * s->fCoverRadius;
                    vA.y += 5.0f;
                    vB.y += 5.0f;
                    TrigDrawPathLine(&vA, &vB, 0x6040C0C0);
                }
            for (k = 0; k < s->nCandidates; k++)
            {
                RwV3d vTop = s->avCandidate[k];

                vTop.y += 100.0f;
                TrigDrawPathLine(&s->avCandidate[k], &vTop, s->abTried[k] ? 0x80808080 : 0xC040FFC0);
            }
            {
                static const RwUInt32 s_adwNode[3] = { 0xE0FFFFFF, 0xE040FF40, 0xC0FF8080 };

                for (k = 0; k < 3; k++)
                    if (s->abCoverNode[k])
                    {
                        RwV3d vTop = s->avCoverNode[k];

                        vTop.y += 150.0f;
                        TrigDrawPathLine(&s->avCoverNode[k], &vTop, s_adwNode[k]);
                        TrigDrawPathLine(&s->vPos, &s->avCoverNode[k], s_adwNode[k] & 0x60FFFFFF);
                    }
            }
            for (k = 0; k < s->nCoverPoints; k++)
            {
                RwV3d vA = s->avCoverPoint[k], vB = s->avCoverPoint[k];

                vA.x -= 30.0f;
                vB.x += 30.0f;
                vA.y += 30.0f;
                vB.y += 30.0f;
                TrigDrawPathLine(&vA, &vB, 0xE0FFC040);
            }
        }
        if (g_bTrigDrawAiCombat)
        {
            if (s->bSeen)
            {
                RwV3d vA = s->vSeen, vB = s->vSeen;

                vA.x -= 40.0f;
                vB.x += 40.0f;
                TrigDrawPathLine(&vA, &vB, 0xFFFFFFFF);
                vA = s->vSeen;
                vB = s->vSeen;
                vA.z -= 40.0f;
                vB.z += 40.0f;
                TrigDrawPathLine(&vA, &vB, 0xFFFFFFFF);
            }
            if (s->bWeapon && s->nAimsWeapon)
                TrigDrawPathLine(&vEye, &s->vWeaponAim, 0xC0FF80FF);
        }
        if (g_bTrigDrawAiPath && s->bGoal)
        {
            RwV3d vA = s->vGoal, vB = s->vGoal;

            TrigDrawPathLine(&s->vPos, &s->vGoal, 0x90FF40FF);
            vA.x -= 40.0f;
            vB.x += 40.0f;
            TrigDrawPathLine(&vA, &vB, 0xE0FF40FF);
            vA = s->vGoal;
            vB = s->vGoal;
            vA.z -= 40.0f;
            vB.z += 40.0f;
            TrigDrawPathLine(&vA, &vB, 0xE0FF40FF);
        }
        if (g_bTrigDrawAiPath && s->nPath > 0)
        {
            TrigDrawPathLine(&s->vPos, &s->avPath[0], 0xC040E0FF);
            for (k = 1; k < s->nPath; k++)
                TrigDrawPathLine(&s->avPath[k - 1], &s->avPath[k], 0xC040E0FF);
        }
        if (!g_bTrigDrawAiText || TrigDrawCharset() == NULL)
            continue;
        TrigDrawPathFlush();
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
        {
            RwChar aszLines[12 + TRIGDRAW_AI_NOTES][TRIGDRAW_AI_NOTE + 16];
            RwInt32 nLines = 0, j;
            RwReal fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z), fStep;

            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "#%d %s hp %d", i,
                      (dwBits & 0x20) ? "soldier" : "ai", s->nHp);
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "state %d%s", s->nState, s->nAlert ? ", alerted" : "");
            if (s->bTarget)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "target #%d", s->nTargetSlot);
            if (s->bTask)
            {
                RwChar szAt[56] = "";

                if (s->nTaskLine >= 0)
                    _snprintf(szAt, sizeof(szAt) - 1, ", %s:%d", s->szTaskFile, s->nTaskLine);
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "task: script %d fn %d%s%s", s->nTaskScript,
                          s->nTaskFunction, szAt, s->nTaskWaits ? ", waiting" : "");
            }
            else
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "no task");
            if (s->bMachine)
            {
                if (s->nMachineLine >= 0)
                    _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "script: %s:%d, state %d", s->szMachineFile,
                              s->nMachineLine, s->nMachineState);
                else
                    _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "script: state %d", s->nMachineState);
            }
            if (s->bPathSearch)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "path: kind %d %s, %d nodes, #%d to #%d %s%s",
                          s->nSearchKind, s->nSearchResult > 0 ? "found" : "not found", s->nSearchLength, s->nStartNode,
                          s->nGoalNode, TrigDrawPathTypeName(s->nGoalType), s->bGoal ? "" : " (done)");
            if (g_bTrigDrawAiCover)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "cover: radius %.0f, %d nodes found (%d tried)%s",
                          s->fCoverRadius, s->nCandidates, s->nTried, s->nCoverPoints ? ", cover points" : "");
            if (g_bTrigDrawAiCombat)
            {
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "tracked %.1fs%s, hears %X/%X/%d%s%s",
                          s->fTracked / 60.0f, s->bSeen ? ", chase point (x)" : "", s->nHearClasses, s->nHearKinds,
                          s->nHearSides, s->nLosLoss ? ", may lose sight" : "", s->nControl ? "" : ", no AI control");
            {
                RwChar szBlocker[32] = "";

                if (s->fBlocker > 0.0f && s->fBlocker < 1e30f)
                    _snprintf(szBlocker, sizeof(szBlocker) - 1, ", line of fire blocked at %.0f%%", s->fBlocker * 100.0f);
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "idle/pursuing %.1fs, engaging %.1fs, burst %d left%s",
                          s->fIn / 60.0f, s->fOut / 60.0f, s->nShots, szBlocker);
            }
                if (s->bWeapon)
                    _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "weapon type %d: ammo %d%s, next shot %.2f",
                              s->nWeaponType, s->nAmmo, s->nInfinite ? " (infinite)" : "", s->fNextShot);
            }
            if (s->nNodeId || s->nNextId)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "node: at #%d %s, next #%d %s", s->nNodeId,
                          s->nNodeId ? TrigDrawPathTypeName(s->nNodeType) : "-", s->nNextId,
                          s->nNextId ? TrigDrawPathTypeName(s->nNextType) : "-");
            // the notes, newest first, with their age in seconds
            RwInt32 nNotes = nLines;
            nLines = TrigDrawNoteLines(s_aAiNotes, TRIGDRAW_AI_ENTITIES, pEntity, aszLines, nLines);
            nNotes = nLines - nNotes;
            fStep = fDist * g_fTrigDrawTextScale * 1.2f;
            if (fStep < 0.06f)
                fStep = 0.06f;
            for (j = 0; j < nLines; j++)
            {
                RwV3d vAt;

                aszLines[j][TRIGDRAW_AI_NOTE + 15] = 0;
                // (stacked up the screen from over its head, the first line on top)
                vAt.x = vEye.x + pCamLtm->up.x * fStep * (RwReal)(nLines - j);
                vAt.y = vEye.y + 40.0f + pCamLtm->up.y * fStep * (RwReal)(nLines - j);
                vAt.z = vEye.z + pCamLtm->up.z * fStep * (RwReal)(nLines - j);
                TrigDrawText(aszLines[j], &vAt, pCamLtm, j < nLines - nNotes ? 0xFFFFFFFF : 0xFFFFD080);
            }
        }
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    }
    TrigDrawPathFlush();
}

// ---- the gimps and shrimps ----

// Gimps: GimpTrigger's scripted extras (type_3DDB98, entity kind 0x200000), with no AI of
// their own: each gets a label over its head (its health, attitude, the ride it is on, its
// head shot, its place along its spline and the state of each of its scripts, by name for
// the shared GimpEntityObjClass and GimpAnim) and a line to its point on the spline.
// Shrimps: each ShrimpTrigger's swimmers (type_17CC40's list of type_17CA70_node), drawn as
// its spline path and a marker per shrimp. The two spawners' labels (TrigDrawLabel) add
// their spawn counts.

// The shared gimp scripts' states, by index (their names in the debug-built levels).
static const RwChar *s_apszGimpEntityStates[] = {
    "Main", "FlyingExplosionReaction", "Start", "ScriptedScene", "TankCrewCommanderLookAround",
    "HitDeathReaction", "WaitForFadeOut", "WaitForFadeToBegin", "WaitForDeathAnim", "DestroyedExit", "Exit",
};
static const RwChar *s_apszGimpAnimStates[] = {
    "Main", "DoNothingEverAgain", "Start", "ScriptedScene", "DoNothing", "AlertStand", "Idle", "StartIdle",
    "ExplosionReaction", "WaitForWallOrGroundHit", "HitTheWall", "LandedOnGround", "Run", "ExplosionDive",
    "TankCrewCommanderLookAround", "RunLoop",
};

struct TrigDrawGimpState
{
    RwV3d vPos, vPoint;
    RwInt32 nHp, nHpMax, nAttitude, nHeadShot;
    RwReal fAlong, fEnd, fSpeed, fPathLength;
    RwBool bRiding, bSpline;
    RwInt32 nMachines;
    RwChar aszMachine[3][48];
    // its names (its trigger's binding, definition and scripts, its spline path's), "" for none
    RwChar szName[48], szDef[48], szPath[48], szScripts[2][48];
    RwChar szHat[8];
    RwInt32 nTrigger;           // its GimpTrigger's index in dword_4CFE30, -1 for none found
    RwUInt32 dwFlags;           // unk_760: 1 at its own speed (else its animation's), 2 along
                                // its spline, 4 to its point
    RwInt32 nGround;            // unk_764: 1 kept on the ground, 0 when its entity says, else
                                // at its path's height
    RwInt32 nEndMode;           // its path's end: 2 turns back, 1 wraps, 0 stops
};

// Each gimp's GimpTrigger, once a frame: the trigger whose binding (unk_D8, the name the
// scripts find the gimp by; flag 2, the entity's id at unk_24_id) holds it.
struct TrigDrawGimpOwner
{
    type_3D3548 *pGimp;
    RwInt32 nTrigger;
};
static TrigDrawGimpOwner s_aGimpOwner[256];
static RwInt32 s_nGimpOwners;
static unsigned s_uGimpOwnersFrame = 0xFFFFFFFF;

static GimpTrigger *TrigDrawGimpTrigger(type_3D3548 *pGimp, RwInt32 *pnIndex)
{
    RwInt32 i;

    if (s_uGimpOwnersFrame != port_frame)
    {
        s_uGimpOwnersFrame = port_frame;
        s_nGimpOwners = 0;
        for (i = 0; i <= dword_429D00 && i < 2000 && s_nGimpOwners < 256; i++)
        {
            Trigger *pTrigger = (Trigger *)dword_4CFE30[i];

            if (pTrigger == NULL || pTrigger->vf_008() != 0x1F)
                continue;
            __try
            {
                GimpTrigger *pGimps = (GimpTrigger *)pTrigger;
                type_3DF8D8 *pObj;
                type_3D3548 *pEntity;

                if (!pGimps->unk_D8.unk_00)
                    continue;
                pObj = sub_198800(&pGimps->unk_D8);
                if (pObj == NULL || pObj->vf_008() != 0x2E || !(pObj->unk_10 & 2))
                    continue;
                pEntity = ((type_D48D0 *)&((type_3DFEEC *)pObj)->unk_24_id)->sub_D4910();
                if (pEntity == NULL)
                    continue;
                s_aGimpOwner[s_nGimpOwners].pGimp = pEntity;
                s_aGimpOwner[s_nGimpOwners].nTrigger = i;
                s_nGimpOwners++;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
    }
    for (i = 0; i < s_nGimpOwners; i++)
        if (s_aGimpOwner[i].pGimp == pGimp)
        {
            if (pnIndex)
                *pnIndex = s_aGimpOwner[i].nTrigger;
            return (GimpTrigger *)dword_4CFE30[s_aGimpOwner[i].nTrigger];
        }
    if (pnIndex)
        *pnIndex = -1;
    return NULL;
}

// A key's name into psz ("" for none).
static void TrigDrawKeyText(const type_3DF8D8_04 *pKey, RwChar *psz, RwInt32 nMax)
{
    const RwChar *pszName = pKey ? TrigDrawKeyName(pKey->unk_00, pKey->unk_04) : NULL;

    psz[0] = 0;
    if (pszName)
    {
        strncpy(psz, pszName, nMax - 1);
        psz[nMax - 1] = 0;
    }
}

// A tag's characters, high byte first, while printable ("HAT" is a gimp with no hat).
static void TrigDrawTagText(RwUInt32 dwTag, RwChar *psz)
{
    RwInt32 i, n = 0;

    for (i = 3; i >= 0; i--)
    {
        RwUInt8 c = (RwUInt8)(dwTag >> (i * 8));

        if (c < 0x21 || c > 0x7E)
            break;
        psz[n++] = (RwChar)c;
    }
    psz[n] = 0;
}

// Its path's end mode, as text.
static const RwChar *TrigDrawEndMode(RwInt32 nMode)
{
    return nMode == 2 ? "turns back" : nMode == 1 ? "wraps" : "stops";
}

// One machine's state as text: the gimp scripts' state names by their state counts.
static void TrigDrawMachineState(type_3D2DB8 *pMachine, RwChar *psz, RwInt32 nMax)
{
    RwInt32 nState = -1, nStates = 0;
    type_3D2DB8_6C *pState = pMachine->unk_6C;
    type_3D2E7C *pObject = pMachine->vf_024();

    if (pState)
        nState = pState->unk_10;
    if (pObject && pObject->unk_08)
        nStates = pObject->unk_08->unk_0C;
    if (nStates == 11 && nState >= 0 && nState < 11)
        _snprintf(psz, nMax - 1, "GimpEntity: %s", s_apszGimpEntityStates[nState]);
    else if (nStates == 16 && nState >= 0 && nState < 16)
        _snprintf(psz, nMax - 1, "GimpAnim: %s", s_apszGimpAnimStates[nState]);
    else
        _snprintf(psz, nMax - 1, "script (%d states): state %d", nStates, nState);
    psz[nMax - 1] = 0;
}

static RwBool TrigDrawGimpRead(type_3DDB98 *pGimp, TrigDrawGimpState *s)
{
    __try
    {
        RwFrame *pFrame = pGimp->unk_338.unk_08;
        type_3D2E7C *pObject;
        RwInt32 i;

        if (pFrame == NULL)
            return FALSE;
        s->vPos = RwFrameGetMatrix(pFrame)->pos;
        s->nHp = pGimp->unk_740;
        s->nHpMax = pGimp->unk_744;
        s->nAttitude = pGimp->unk_75C;
        s->nHeadShot = pGimp->unk_695;
        s->fAlong = pGimp->unk_6E4;
        s->fEnd = pGimp->unk_738;
        s->fSpeed = pGimp->unk_768;
        s->vPoint = pGimp->unk_76C;
        s->bSpline = s->fEnd > 0.0f && pGimp->unk_734 != NULL;
        s->bRiding = pGimp->unk_3D8.sub_D4910() != NULL;
        s->dwFlags = pGimp->unk_760;
        s->nGround = pGimp->unk_764;
        TrigDrawTagText(pGimp->unk_69C, s->szHat);
        s->szPath[0] = 0;
        s->fPathLength = 0.0f;
        s->nEndMode = 0;
        if (pGimp->unk_734)
        {
            TrigDrawKeyText(&pGimp->unk_734->unk_2C, s->szPath, sizeof(s->szPath));
            s->fPathLength = pGimp->unk_734->unk_24;
            s->nEndMode = pGimp->unk_734->unk_1C_0;
        }
        {
            GimpTrigger *pGimps = TrigDrawGimpTrigger(pGimp, &s->nTrigger);

            s->szName[0] = s->szDef[0] = s->szScripts[0][0] = s->szScripts[1][0] = 0;
            if (pGimps)
            {
                TrigDrawKeyText(&pGimps->unk_D8, s->szName, sizeof(s->szName));
                TrigDrawKeyText(&pGimps->unk_C0, s->szDef, sizeof(s->szDef));
                TrigDrawKeyText(&pGimps->unk_C8, s->szScripts[0], sizeof(s->szScripts[0]));
                if (pGimps->unk_D0.unk_00)
                    TrigDrawKeyText(&pGimps->unk_D0, s->szScripts[1], sizeof(s->szScripts[1]));
            }
        }
        s->nMachines = 0;
        pObject = pGimp->vf_098();
        if (pObject)
        {
            RwUInt32 dwHandle = pObject->get_unk_04();

            for (i = 0; i < s_nMachines && s->nMachines < 3; i++)
                if (s_adwMachineOwner[i] == dwHandle)
                    TrigDrawMachineState(s_apMachine[i], s->aszMachine[s->nMachines++], 48);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
    return TRUE;
}

// A cross at *pv, the size of fSize, with a post up from it.
static void TrigDrawMarker(const RwV3d *pv, RwReal fSize, RwUInt32 dwColour)
{
    RwV3d vA = *pv, vB = *pv;

    vA.x -= fSize;
    vB.x += fSize;
    TrigDrawPathLine(&vA, &vB, dwColour);
    vA = *pv;
    vB = *pv;
    vA.z -= fSize;
    vB.z += fSize;
    TrigDrawPathLine(&vA, &vB, dwColour);
    vA = *pv;
    vB = *pv;
    vB.y += fSize * 2.0f;
    TrigDrawPathLine(&vA, &vB, dwColour);
}

static void TrigDrawGimps(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwInt32 i, j;

    g_nTrigDrawGimpsShown = 0;
    TrigDrawAiMachines();
    for (i = 0; i < 768; i++)
    {
        type_3D3548 *pEntity = dword_4B6A00[i].unk_04;
        TrigDrawGimpState s;
        RwV3d vD, vHead;
        RwReal fDist, fStep;
        RwChar aszLines[12 + TRIGDRAW_AI_NOTES][TRIGDRAW_AI_NOTE + 16];
        RwInt32 nLines = 0, nNotes;

        if (pEntity == NULL || (pEntity->unk_2C & 0x3FFFFF0) != 0x200000)
            continue;
        if (!TrigDrawGimpRead((type_3DDB98 *)pEntity, &s))
            continue;
        vD.x = s.vPos.x - pvCam->x;
        vD.y = s.vPos.y - pvCam->y;
        vD.z = s.vPos.z - pvCam->z;
        fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z);
        if (g_fTrigDrawGimpRange > 0.0f && fDist > g_fTrigDrawGimpRange)
            continue;
        g_nTrigDrawGimpsShown++;
        vHead = s.vPos;
        vHead.y += 160.0f;
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
        if (s.bSpline)
        {
            TrigDrawPathLine(&s.vPos, &s.vPoint, 0xC0FFA040);
            TrigDrawMarker(&s.vPoint, 25.0f, 0xE0FFA040);
        }
        TrigDrawPathFlush();
        if (TrigDrawCharset() == NULL)
            continue;
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
        _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "#%d gimp %s hp %d/%d, attitude %d%s%s", i,
                  s.szName[0] ? s.szName : "", s.nHp, s.nHpMax, s.nAttitude, s.bRiding ? ", riding" : "",
                  s.nHeadShot == 2 ? ", head shot" : "");
        if (s.szDef[0] || s.szHat[0])
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "%s%s%s%s", s.szDef[0] ? "def " : "", s.szDef,
                      s.szHat[0] && strcmp(s.szHat, "HAT") ? (s.szDef[0] ? ", hat " : "hat ") : "",
                      s.szHat[0] && strcmp(s.szHat, "HAT") ? s.szHat : "");
        if (s.bSpline)
        {
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "spline %s: %.0f of %.0f (length %.0f, %s), speed %.2f",
                      s.szPath[0] ? s.szPath : "?", s.fAlong, s.fEnd, s.fPathLength, TrigDrawEndMode(s.nEndMode),
                      s.fSpeed);
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "%s, %s, %s",
                      (s.dwFlags & 2) ? "going along its spline" : (s.dwFlags & 4) ? "going to its point" : "held",
                      (s.dwFlags & 1) ? "at its own speed" : "at its animation's speed",
                      s.nGround == 1 ? "on the ground" : s.nGround == 0 ? "on the ground if flagged" : "at the path's height");
        }
        if (s.szScripts[0][0] || s.szScripts[1][0])
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "scripts %s%s%s", s.szScripts[0],
                      s.szScripts[1][0] ? ", " : "", s.szScripts[1]);
        for (j = 0; j < s.nMachines; j++)
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "%s", s.aszMachine[j]);
        nNotes = nLines;
        nLines = TrigDrawNoteLines(s_aAiNotes, TRIGDRAW_AI_ENTITIES, pEntity, aszLines, nLines);
        nNotes = nLines - nNotes;
        fStep = fDist * g_fTrigDrawTextScale * 1.2f;
        if (fStep < 0.06f)
            fStep = 0.06f;
        for (j = 0; j < nLines; j++)
        {
            RwV3d vAt;

            aszLines[j][TRIGDRAW_AI_NOTE + 15] = 0;
            vAt.x = vHead.x + pCamLtm->up.x * fStep * (RwReal)(nLines - j);
            vAt.y = vHead.y + 40.0f + pCamLtm->up.y * fStep * (RwReal)(nLines - j);
            vAt.z = vHead.z + pCamLtm->up.z * fStep * (RwReal)(nLines - j);
            TrigDrawText(aszLines[j], &vAt, pCamLtm, j < nLines - nNotes ? 0xFFFFE0A0 : 0xFFFFD080);
        }
    }
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
}

// The shrimp triggers' paths and their shrimps (kind 0x21 triggers).
static void TrigDrawShrimps(const RwV3d *pvCam)
{
    RwInt32 i, k;

    g_nTrigDrawShrimpsShown = 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i <= dword_429D00 && i < 2000; i++)
    {
        Trigger *pTrigger = (Trigger *)dword_4CFE30[i];

        if (pTrigger == NULL || pTrigger->vf_008() != 0x21)
            continue;
        __try
        {
            ShrimpTrigger *pShrimps = (ShrimpTrigger *)pTrigger;
            SplinePath *pPath = pShrimps->unk_EC.unk_0C;
            type_17CA70_node *pNode;
            RwV3d vA, vB;

            if (pPath == NULL)
                continue;
            if (g_fTrigDrawGimpRange > 0.0f)
            {
                RwReal dx = pTrigger->unk_90 - pvCam->x, dz = pTrigger->unk_98 - pvCam->z;

                if (dx * dx + dz * dz > g_fTrigDrawGimpRange * g_fTrigDrawGimpRange * 4.0f)
                    continue;
            }
            // its path, with a tick at its start
            pPath->sub_BA990(0.0f, &vA, NULL);
            vB = vA;
            vB.y += 80.0f;
            TrigDrawPathLine(&vA, &vB, 0xE040FFFF);
            for (k = 1; k <= 48; k++)
            {
                pPath->sub_BA990((RwReal)k / 48.0f, &vB, NULL);
                TrigDrawPathLine(&vA, &vB, 0x9040C0FF);
                vA = vB;
            }
            // each shrimp
            for (pNode = pShrimps->unk_EC.unk_14, k = 0; pNode != NULL && k < 256; pNode = pNode->unk_0C, k++)
            {
                pPath->sub_BA990(pNode->unk_00, &vA, NULL);
                TrigDrawMarker(&vA, 20.0f, pNode->unk_04 >= 0.0f ? 0xFF60FFFF : 0xFFFF60FF);
                g_nTrigDrawShrimpsShown++;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    TrigDrawPathFlush();
}

// The spawn counts under a GimpTrigger's or ShrimpTrigger's label, for TrigDrawLabel: lines
// written below the type at *pvCentre.
static void TrigDrawSpawnerLines(Trigger *pTrigger, const RwV3d *pvCentre, const RwMatrix *pCamLtm, RwUInt32 dwColour)
{
    RwChar sz[96], szLimit[24];
    RwInt32 nKind = pTrigger->vf_008();

    if (nKind == 0x1F && g_bTrigDrawGimps)
    {
        GimpTrigger *pGimps = (GimpTrigger *)pTrigger;

        if (pGimps->unk_148 == 0x7FFFFFFF)
            strcpy(szLimit, "no limit");
        else
            _snprintf(szLimit, sizeof(szLimit) - 1, "%d left of %d", pGimps->unk_14C, pGimps->unk_148);
        szLimit[sizeof(szLimit) - 1] = 0;
        _snprintf(sz, sizeof(sz) - 1, "spawns %s%s, health %.0f", szLimit, pGimps->unk_140 ? ", live once" : "",
                  pGimps->unk_120_r);
        sz[sizeof(sz) - 1] = 0;
        TrigDrawText(sz, pvCentre, pCamLtm, dwColour, -1.0f);
        {
            RwChar szName[48], szDef[48], szWeapon[48], szScript[48];

            TrigDrawKeyText(&pGimps->unk_D8, szName, sizeof(szName));
            TrigDrawKeyText(&pGimps->unk_C0, szDef, sizeof(szDef));
            TrigDrawKeyText(&pGimps->unk_E8, szWeapon, sizeof(szWeapon));
            TrigDrawKeyText(&pGimps->unk_C8, szScript, sizeof(szScript));
            _snprintf(sz, sizeof(sz) - 1, "gimp %s, def %s%s%s", szName[0] ? szName : "-", szDef[0] ? szDef : "-",
                      szWeapon[0] ? ", weapon " : "", szWeapon);
            sz[sizeof(sz) - 1] = 0;
            TrigDrawText(sz, pvCentre, pCamLtm, dwColour, -2.0f);
            if (szScript[0])
            {
                _snprintf(sz, sizeof(sz) - 1, "script %s", szScript);
                sz[sizeof(sz) - 1] = 0;
                TrigDrawText(sz, pvCentre, pCamLtm, dwColour, -3.0f);
            }
        }
    }
    else if (nKind == 0x21 && g_bTrigDrawShrimps)
    {
        ShrimpTrigger *pShrimps = (ShrimpTrigger *)pTrigger;
        type_17CA70_node *pNode;
        RwInt32 nAlive = 0;

        RwInt32 nForward = 0;

        for (pNode = pShrimps->unk_EC.unk_14; pNode != NULL && nAlive < 256; pNode = pNode->unk_0C)
        {
            nAlive++;
            nForward += pNode->unk_04 >= 0.0f;
        }
        if (pShrimps->unk_E0 == 0x7FFFFFFF)
            strcpy(szLimit, "no limit");
        else
            _snprintf(szLimit, sizeof(szLimit) - 1, "%d left of %d", pShrimps->unk_E4, pShrimps->unk_E0);
        szLimit[sizeof(szLimit) - 1] = 0;
        _snprintf(sz, sizeof(sz) - 1, "%d shrimps (%d forward, %d back), spawns %s, chance %.0f%%, speed %.3f",
                  nAlive, nForward, nAlive - nForward, szLimit, pShrimps->unk_DC, pShrimps->unk_D0_r);
        sz[sizeof(sz) - 1] = 0;
        TrigDrawText(sz, pvCentre, pCamLtm, dwColour, -1.0f);
        {
            RwChar szModel[48], szPath[48];
            SplinePath *pPath = pShrimps->unk_EC.unk_0C;

            TrigDrawKeyText(&pShrimps->unk_C0, szModel, sizeof(szModel));
            szPath[0] = 0;
            if (pPath)
                TrigDrawKeyText(&pPath->unk_2C, szPath, sizeof(szPath));
            if (pPath)
                _snprintf(sz, sizeof(sz) - 1, "model %s, path %s (length %.0f, %s)", szModel[0] ? szModel : "-",
                          szPath[0] ? szPath : "-", pPath->unk_24, TrigDrawEndMode(pPath->unk_1C_0));
            else
                _snprintf(sz, sizeof(sz) - 1, "model %s, no path yet", szModel[0] ? szModel : "-");
            sz[sizeof(sz) - 1] = 0;
            TrigDrawText(sz, pvCentre, pCamLtm, dwColour, -2.0f);
        }
    }
}

// ---- the projectile generators ----

// Each live projectile generator (type_1227C0, the list dword_4CE8F8): its
// muzzle (its matrix, unk_70: a cross and its facing; orange fires bullets,
// red lobs shells), the line to its target by its kind (unk_38: red the
// nearest entity, orange a set one, yellow a point, blue its path), where
// it aims (unk_B0, a yellow cross; the last, unk_BC, dimmer) with its spread
// (unk_60) as a circle there, its turret's facing (unk_12C: cyan, magenta
// while it turns), and a grey line to its trigger; over it its state, its
// stage, burst and timers, then its notes (its shots, bursts, stages and
// starts, seen frame to frame).
RwBool g_bTrigDrawPg = FALSE;
RwBool g_bTrigDrawPgText = TRUE;
RwReal g_fTrigDrawPgRange = 0.0f;
RwInt32 g_nTrigDrawPgShown;

#define TRIGDRAW_PG_NOTED 64
static TrigDrawAiNotes s_aPgNotes[TRIGDRAW_PG_NOTED];

// A generator as last seen, for its notes.
struct TrigDrawPgSeen
{
    const void *pGen;
    RwInt32 nState, nStage, nShots, nStageShots;
};
static TrigDrawPgSeen s_aPgSeen[TRIGDRAW_PG_NOTED];

struct TrigDrawPgState
{
    RwInt32 nId, nKind, nState, nForced, nTurning, nStagesOn, nStage, nTargetKind, nStageShots, nShots, nBursts,
        nLos, nReplays;
    RwReal fNext, fSpread, fHeight, fPathAt, fPathSpeed, fWait, fWaitLeft, fReplay, fSpeed;
    RwV3d vPos, vAt, vAim, vLastAim, vTarget, vFacing, vTrigger;
    RwBool bTarget, bTrigger;
};

static RwBool TrigDrawEntityPos(type_D48D0 *pHandle, RwV3d *pv)
{
    type_3D3548 *pEntity = pHandle->sub_D4910();

    if (pEntity == NULL || pEntity->unk_338.unk_08 == NULL)
        return FALSE;
    *pv = RwFrameGetMatrix(pEntity->unk_338.unk_08)->pos;
    return TRUE;
}

static RwBool TrigDrawPgRead(type_1227C0 *pGen, TrigDrawPgState *p)
{
    __try
    {
        ProjectileGeneratorTrigger *pTrigger = pGen->unk_18.unk_08_pg;

        p->nId = pGen->unk_104;
        p->nKind = pGen->vf_01C() != NULL ? 1 : 0;
        p->nState = pGen->unk_14;
        p->nForced = pGen->unk_28;
        p->nTurning = pGen->unk_2C == 0;
        p->nStagesOn = pGen->unk_30;
        p->nStage = pGen->unk_34;
        p->nTargetKind = pGen->unk_38;
        p->nStageShots = pGen->unk_3C;
        p->nShots = pGen->unk_40;
        p->fNext = pGen->unk_44;
        p->nBursts = pGen->unk_50;
        p->fSpread = pGen->unk_60_r;
        p->fHeight = pGen->unk_C8;
        p->fPathAt = pGen->unk_CC;
        p->fPathSpeed = pGen->unk_D0;
        p->nLos = p->nKind == 0 ? ((type_11DB10 *)pGen)->unk_20C : -1;
        p->fWait = pGen->unk_138;
        p->fWaitLeft = pGen->unk_13C;
        p->nReplays = pGen->unk_140;
        p->fReplay = pGen->unk_144;
        p->vPos = pGen->unk_70.pos;
        p->vAt = pGen->unk_70.at;
        p->vAim = pGen->unk_B0;
        p->vLastAim = pGen->unk_BC;
        p->vFacing = pGen->unk_12C;
        p->bTarget = FALSE;
        if (p->nTargetKind == 2)
        {
            p->vTarget = pGen->unk_54;
            p->bTarget = TRUE;
        }
        else if (p->nTargetKind <= 1)
            p->bTarget = TrigDrawEntityPos(&pGen->unk_24, &p->vTarget);
        p->bTrigger = pTrigger != NULL;
        p->fSpeed = 0.0f;
        if (pTrigger)
        {
            p->vTrigger.x = pTrigger->unk_90;
            p->vTrigger.y = pTrigger->unk_94;
            p->vTrigger.z = pTrigger->unk_98;
            p->fSpeed = pTrigger->unk_158_r;
        }
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// Its notes: what changed since the last frame.
static void TrigDrawPgNotes(const void *pGen, const TrigDrawPgState *p)
{
    TrigDrawPgSeen *pSeen = NULL;
    RwInt32 i;
    RwChar sz[TRIGDRAW_AI_NOTE];

    for (i = 0; i < TRIGDRAW_PG_NOTED; i++)
        if (s_aPgSeen[i].pGen == pGen)
        {
            pSeen = &s_aPgSeen[i];
            break;
        }
    if (pSeen == NULL)
    {
        for (i = 0; i < TRIGDRAW_PG_NOTED && s_aPgSeen[i].pGen != NULL; i++)
            ;
        if (i == TRIGDRAW_PG_NOTED)
            return;
        pSeen = &s_aPgSeen[i];
        pSeen->pGen = pGen;
        pSeen->nState = p->nState;
        pSeen->nStage = p->nStage;
        pSeen->nShots = p->nShots;
        pSeen->nStageShots = p->nStageShots;
        return;
    }
    if (p->nState != pSeen->nState)
        TrigDrawNoteKeep(s_aPgNotes, TRIGDRAW_PG_NOTED, pGen,
                         p->nState == 0 ? "stopped" : pSeen->nState == 0 ? "started" : "firing");
    if (p->nShots < pSeen->nShots)
        TrigDrawNoteKeep(s_aPgNotes, TRIGDRAW_PG_NOTED, pGen, "shot");
    else if (p->nShots > pSeen->nShots)
    {
        _snprintf(sz, sizeof(sz) - 1, "burst of %d", p->nShots);
        sz[sizeof(sz) - 1] = 0;
        TrigDrawNoteKeep(s_aPgNotes, TRIGDRAW_PG_NOTED, pGen, sz);
    }
    if (p->nStage != pSeen->nStage)
    {
        _snprintf(sz, sizeof(sz) - 1, p->nStage >= 3 ? "stages over" : "stage %d", p->nStage);
        sz[sizeof(sz) - 1] = 0;
        TrigDrawNoteKeep(s_aPgNotes, TRIGDRAW_PG_NOTED, pGen, sz);
    }
    pSeen->nState = p->nState;
    pSeen->nStage = p->nStage;
    pSeen->nShots = p->nShots;
    pSeen->nStageShots = p->nStageShots;
}

static void TrigDrawCross(const RwV3d *pv, RwReal f, RwUInt32 dwColour)
{
    RwV3d vA = *pv, vB = *pv;

    vA.x -= f;
    vB.x += f;
    TrigDrawPathLine(&vA, &vB, dwColour);
    vA = *pv;
    vB = *pv;
    vA.y -= f;
    vB.y += f;
    TrigDrawPathLine(&vA, &vB, dwColour);
    vA = *pv;
    vB = *pv;
    vA.z -= f;
    vB.z += f;
    TrigDrawPathLine(&vA, &vB, dwColour);
}

static void TrigDrawPg(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    static const RwChar *const s_apszTarget[4] = {"the nearest entity", "an entity", "a point", "its path"};
    static const RwUInt32 s_adwTarget[4] = {0xE0FF4040, 0xE0FF9040, 0xE0FFFF40, 0xE040A0FF};
    static TrigDrawPgState s_state;
    type_1227C0 *pGen;
    RwInt32 n = 0, k;

    g_nTrigDrawPgShown = 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (pGen = dword_4CE8F8; pGen != NULL && n < 512; n++)
    {
        TrigDrawPgState *p = &s_state;
        type_1227C0 *pNext;
        RwV3d vD, vEnd;
        RwReal fDist;
        RwUInt32 dwKind;

        if (!TrigDrawPgRead(pGen, p))
            break;
        pNext = pGen->unk_100;
        TrigDrawPgNotes(pGen, p);
        vD.x = p->vPos.x - pvCam->x;
        vD.y = p->vPos.y - pvCam->y;
        vD.z = p->vPos.z - pvCam->z;
        fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z);
        if (g_fTrigDrawPgRange > 0.0f && fDist > g_fTrigDrawPgRange)
        {
            pGen = pNext;
            continue;
        }
        g_nTrigDrawPgShown++;
        dwKind = p->nKind ? 0xFFFF3030 : 0xFFFF9020;
        // the muzzle and its facing
        TrigDrawCross(&p->vPos, 30.0f, dwKind);
        vEnd.x = p->vPos.x + p->vAt.x * 120.0f;
        vEnd.y = p->vPos.y + p->vAt.y * 120.0f;
        vEnd.z = p->vPos.z + p->vAt.z * 120.0f;
        TrigDrawPathLine(&p->vPos, &vEnd, dwKind);
        // the turret's facing
        if (p->vFacing.x != 0.0f || p->vFacing.y != 0.0f || p->vFacing.z != 0.0f)
        {
            vEnd.x = p->vPos.x + p->vFacing.x * 200.0f;
            vEnd.y = p->vPos.y + p->vFacing.y * 200.0f;
            vEnd.z = p->vPos.z + p->vFacing.z * 200.0f;
            TrigDrawPathLine(&p->vPos, &vEnd, p->nTurning ? 0xE0FF40FF : 0xE040FFFF);
        }
        // its target
        if (p->bTarget && p->nTargetKind >= 0 && p->nTargetKind < 4)
            TrigDrawPathLine(&p->vPos, &p->vTarget, s_adwTarget[p->nTargetKind]);
        // where it aims, and its spread there
        if (p->vAim.x != 0.0f || p->vAim.y != 0.0f || p->vAim.z != 0.0f)
        {
            TrigDrawPathLine(&p->vPos, &p->vAim, 0x80FFFF60);
            TrigDrawCross(&p->vAim, 40.0f, 0xFFFFFF40);
            if (p->fSpread > 0.0f && p->fSpread < 5000.0f)
                for (k = 0; k < 24; k++)
                {
                    RwReal a0 = (RwReal)k * (6.2831853f / 24), a1 = (RwReal)(k + 1) * (6.2831853f / 24);
                    RwV3d vA = p->vAim, vB = p->vAim;

                    vA.x += (RwReal)cos(a0) * p->fSpread;
                    vA.z += (RwReal)sin(a0) * p->fSpread;
                    vB.x += (RwReal)cos(a1) * p->fSpread;
                    vB.z += (RwReal)sin(a1) * p->fSpread;
                    TrigDrawPathLine(&vA, &vB, 0xA0FFFF40);
                }
        }
        if (p->vLastAim.x != 0.0f || p->vLastAim.y != 0.0f || p->vLastAim.z != 0.0f)
            TrigDrawCross(&p->vLastAim, 25.0f, 0x80A0A040);
        if (p->bTrigger)
            TrigDrawPathLine(&p->vPos, &p->vTrigger, 0x60C0C0C0);

        if (g_bTrigDrawPgText && TrigDrawCharset() != NULL)
        {
            RwChar aszLines[8 + TRIGDRAW_AI_NOTES][TRIGDRAW_AI_NOTE + 16];
            RwInt32 nLines = 0, nNotes;
            RwV3d vAt = p->vPos;

            TrigDrawPathFlush();
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "generator %d (%s): %s%s", p->nId & 0xFFFF,
                      p->nKind ? "shells" : "bullets",
                      p->nState == 1 ? "firing" : p->nState == 2 ? "updated" : p->nState == 0 ? "stopped" : "?",
                      p->nForced ? ", forced" : "");
            if (p->nTargetKind == 3)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "target: its path at %.2f (speed %g)", p->fPathAt,
                          p->fPathSpeed);
            else
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "target: %s%s, spread %g, height %g",
                          p->nTargetKind >= 0 && p->nTargetKind < 4 ? s_apszTarget[p->nTargetKind] : "?",
                          p->bTarget || p->nTargetKind == 2 ? "" : " (none now)", p->fSpread, p->fHeight);
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "burst: %d left, next in %.1fs, %d shots to the long pause",
                      p->nShots, p->fNext / 60.0f, p->nBursts);
            if (p->nStagesOn)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE,
                          p->nStage >= 3 ? "stages: over" : "stage %d: %d bursts left", p->nStage, p->nStageShots);
            if (p->nTurning || p->fWaitLeft > 0.0f)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "%s%sholding its aim %.1f of %.1fs",
                          p->nTurning ? "turret not on target" : "", p->nTurning ? ", " : "", p->fWaitLeft / 60.0f,
                          p->fWait / 60.0f);
            _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "%sprojectile speed %g",
                      p->nLos < 0 ? "" : p->nLos ? "line of sight check on, " : "line of sight check off, ", p->fSpeed);
            if (p->nReplays && p->fReplay > 0.0f)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "hit: paused %.1fs more", p->fReplay / 60.0f);
            nNotes = nLines;
            nLines = TrigDrawNoteLines(s_aPgNotes, TRIGDRAW_PG_NOTED, pGen, aszLines, nLines);
            nNotes = nLines - nNotes;
            vAt.y += 40.0f;
            TrigDrawLines(aszLines, nLines, nNotes, &vAt, fDist, pCamLtm);
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
        }
        pGen = pNext;
    }
    TrigDrawPathFlush();
}

// Draws and empties the collision triangle buffer.
static void TrigDrawCollisionFlush()
{
    if (s_nCollVerts == 0)
        return;
    if (RwIm3DTransform(s_aCollVerts, s_nCollVerts, NULL, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA))
    {
        RwIm3DRenderPrimitive(rwPRIMTYPETRILIST);
        RwIm3DEnd();
    }
    s_nCollVerts = 0;
}

// Draws and empties the collision outline buffer.
static void TrigDrawCollisionLineFlush()
{
    if (s_nCollLineVerts == 0)
        return;
    if (RwIm3DTransform(s_aCollLineVerts, s_nCollLineVerts, NULL, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA))
    {
        RwIm3DRenderPrimitive(rwPRIMTYPELINELIST);
        RwIm3DEnd();
    }
    s_nCollLineVerts = 0;
}

// A line into the outline buffer, lifted along vN by fLift.
static void TrigDrawCollLine(const RwV3d *pP, const RwV3d *pQ, const RwV3d *pvN, RwReal fLift, RwUInt32 dwColour)
{
    RwIm3DVertex *pVert;

    if (s_nCollLineVerts + 2 > TRIGDRAW_COLLLINEVERTS)
        TrigDrawCollisionLineFlush();
    pVert = &s_aCollLineVerts[s_nCollLineVerts];
    RwIm3DVertexSetPos(&pVert[0], pP->x + pvN->x * fLift, pP->y + pvN->y * fLift, pP->z + pvN->z * fLift);
    RwIm3DVertexSetPos(&pVert[1], pQ->x + pvN->x * fLift, pQ->y + pvN->y * fLift, pQ->z + pvN->z * fLift);
    pVert[0].color = pVert[1].color = dwColour;
    s_nCollLineVerts += 2;
}

static RwReal TrigDrawAxis(const RwV3d *pv, RwInt32 nAxis)
{
    return nAxis == 0 ? pv->x : nAxis == 1 ? pv->y : pv->z;
}

// The grid lines across a triangle: where it crosses the planes every fSpacing units along
// the two axes its normal is least along (a floor's x and z, a wall's y and the other), at
// most 48 a direction.
static void TrigDrawCollGrid(const RwV3d *pA, const RwV3d *pB, const RwV3d *pC, const RwV3d *pvN,
                             RwReal fSpacing, RwReal fLift, RwUInt32 dwColour)
{
    const RwV3d *apV[3] = { pA, pB, pC };
    RwReal fAx = (RwReal)fabs(pvN->x), fAy = (RwReal)fabs(pvN->y), fAz = (RwReal)fabs(pvN->z);
    RwInt32 nMain = fAy >= fAx && fAy >= fAz ? 1 : fAx >= fAz ? 0 : 2;
    RwInt32 nAxis, e;

    for (nAxis = 0; nAxis < 3; nAxis++)
    {
        RwReal fA, fB, fC, fLo, fHi, t;
        RwInt32 n;

        if (nAxis == nMain)
            continue;
        fA = TrigDrawAxis(pA, nAxis);
        fB = TrigDrawAxis(pB, nAxis);
        fC = TrigDrawAxis(pC, nAxis);
        fLo = fA < fB ? (fA < fC ? fA : fC) : (fB < fC ? fB : fC);
        fHi = fA > fB ? (fA > fC ? fA : fC) : (fB > fC ? fB : fC);
        t = (RwReal)ceil(fLo / fSpacing) * fSpacing;
        for (n = 0; t < fHi && n < 48; t += fSpacing, n++)
        {
            RwV3d avHit[2];
            RwInt32 nHits = 0;

            // (the two edges the plane crosses)
            for (e = 0; e < 3 && nHits < 2; e++)
            {
                const RwV3d *pP = apV[e], *pQ = apV[(e + 1) % 3];
                RwReal p = TrigDrawAxis(pP, nAxis), q = TrigDrawAxis(pQ, nAxis);

                if ((p <= t && q > t) || (q <= t && p > t))
                {
                    RwReal f = (t - p) / (q - p);

                    avHit[nHits].x = pP->x + (pQ->x - pP->x) * f;
                    avHit[nHits].y = pP->y + (pQ->y - pP->y) * f;
                    avHit[nHits].z = pP->z + (pQ->z - pP->z) * f;
                    nHits++;
                }
            }
            if (nHits == 2)
                TrigDrawCollLine(&avHit[0], &avHit[1], pvN, fLift, dwColour);
        }
    }
}

// A kind's own colour: a hue from a hash (FNV-1a) of its tag and texture name,
// full and bright, so a kind keeps its colour across levels and a forget.
static RwUInt32 TrigDrawCollKindHue(RwUInt32 dwTag, const RwChar *pszTexture)
{
    RwUInt32 h = 2166136261u;
    RwReal fHue, f, r, g, b;
    RwInt32 i, nSector;

    for (i = 0; i < 4; i++)
        h = (h ^ ((dwTag >> (i * 8)) & 0xFF)) * 16777619u;
    for (i = 0; pszTexture[i]; i++)
        h = (h ^ (RwUInt8)pszTexture[i]) * 16777619u;
    fHue = (RwReal)((h >> 8) % 360u) / 60.0f;
    nSector = (RwInt32)fHue;
    f = fHue - nSector;
    // (the HSV hue at full saturation, value 1)
    switch (nSector % 6)
    {
    case 0: r = 1.0f; g = f; b = 0.0f; break;
    case 1: r = 1.0f - f; g = 1.0f; b = 0.0f; break;
    case 2: r = 0.0f; g = 1.0f; b = f; break;
    case 3: r = 0.0f; g = 1.0f - f; b = 1.0f; break;
    case 4: r = f; g = 0.0f; b = 1.0f; break;
    default: r = 1.0f; g = 0.0f; b = 1.0f - f; break;
    }
    // (a little white mixed in: the darker hues read better on the dark levels)
    r = 0.25f + 0.75f * r;
    g = 0.25f + 0.75f * g;
    b = 0.25f + 0.75f * b;
    return 0xFF000000 | ((RwUInt32)(r * 255.0f) << 16) | ((RwUInt32)(g * 255.0f) << 8) | (RwUInt32)(b * 255.0f);
}

void TrigDrawCollKindsClear()
{
    g_nTrigDrawCollKinds = 0;
    memset(s_aCollMatCache, 0, sizeof(s_aCollMatCache));
}

const RwChar *TrigDrawCollFlagsText(RwUInt32 dwFlags, RwChar *pszOut, RwInt32 nOut)
{
    static const struct { RwUInt32 dwBit; const RwChar *pszName; } s_aBits[] =
    {
        { 0x10000, "player" }, { 0x20000, "soldiers" }, { 0x40000, "vehicles" },
        { 0x80000, "projectiles" }, { 0x100000, "projectiles 2" }, { 0x400000, "AI sight" },
        { 0x800000, "other vehicles" },
    };
    RwUInt32 dwRest = dwFlags & 0xFFFF0000;
    RwInt32 n = 0, i;

    pszOut[0] = 0;
    if (!dwRest)
        return "solid to all";
    for (i = 0; i < (RwInt32)(sizeof(s_aBits) / sizeof(s_aBits[0])); i++)
    {
        if (dwRest & s_aBits[i].dwBit)
        {
            n += _snprintf(pszOut + n, nOut - n, "%s%s", n ? ", " : "skipped by ", s_aBits[i].pszName);
            dwRest &= ~s_aBits[i].dwBit;
            if (n >= nOut - 1)
                break;
        }
    }
    if (dwRest && n < nOut - 1)
        _snprintf(pszOut + n, nOut - n, "%s0x%X", n ? ", " : "", dwRest);
    pszOut[nOut - 1] = 0;
    return pszOut;
}

// The kind of the collision material pMaterial (a new one added while there is room; -1 for
// none or a full table).
static RwInt32 TrigDrawCollKindOf(void *pMaterial)
{
    RwUInt32 nSlot = (RwUInt32)(((RwUInt32)pMaterial >> 4) % TRIGDRAW_COLLMATCACHE);
    RpMaterial *pMat = (RpMaterial *)pMaterial;
    RwUInt32 dwTag, dwRgba;
    const RwChar *pszTex;
    RwInt32 i;

    if (pMaterial == NULL)
        return -1;
    if (s_aCollMatCache[nSlot].pMaterial == pMaterial)
        return s_aCollMatCache[nSlot].nKind;
    dwTag = sub_FC000(pMaterial)->unk_04;
    dwRgba = ((RwUInt32)pMat->color.red << 24) | ((RwUInt32)pMat->color.green << 16)
           | ((RwUInt32)pMat->color.blue << 8) | pMat->color.alpha;
    pszTex = pMat->texture ? pMat->texture->name : "";
    for (i = 0; i < g_nTrigDrawCollKinds; i++)
    {
        if (g_aTrigDrawCollKinds[i].dwTag == dwTag && g_aTrigDrawCollKinds[i].dwRgba == dwRgba
            && (g_aTrigDrawCollKinds[i].szTexture[0] != 0) == (pszTex[0] != 0)
            && (pszTex[0] == 0 || !strncmp(g_aTrigDrawCollKinds[i].szTexture, pszTex, 31)))
            break;
    }
    if (i == g_nTrigDrawCollKinds)
    {
        if (i >= TRIGDRAW_COLLKINDS)
            i = -1;
        else
        {
            TrigDrawCollKind *k = &g_aTrigDrawCollKinds[g_nTrigDrawCollKinds++];

            memset(k, 0, sizeof(*k));
            k->dwTag = dwTag;
            k->dwRgba = dwRgba;
            k->dwDraw = TrigDrawCollKindHue(dwTag, pszTex);
            strncpy(k->szTexture, pszTex, sizeof(k->szTexture) - 1);
        }
    }
    if (i >= 0)
        g_aTrigDrawCollKinds[i].nMaterials++;
    s_aCollMatCache[nSlot].pMaterial = pMaterial;
    s_aCollMatCache[nSlot].nKind = i;
    return i;
}

// A kind's drawing colour, see-through (g_bTrigDrawCollByKind); grey for none.
static RwUInt32 TrigDrawCollKindColour(RwInt32 nKind)
{
    return nKind < 0 ? 0x60808080 : (g_aTrigDrawCollKinds[nKind].dwDraw & 0x00FFFFFF) | 0x70000000;
}

// A world sector callback: when the sector's box is within
// g_fTrigDrawCollisionRange of the camera, adds each of its triangles,
// lifted along its normal and coloured by its facing (green floors, blue
// walls, red ceilings), drawing whenever the buffer fills.
static RpWorldSector *TrigDrawCollisionSector(RpWorldSector *pSector, void *pData)
{
    TrigDrawSector *pSec = (TrigDrawSector *)pSector;
    RwReal fDX, fDY, fDZ, fLen;
    RwV3d vA, vB, vC, vE1, vE2, vN;
    RwUInt32 dwColour;
    RwInt32 i, k;
    RwIm3DVertex *pVert;

    // the camera's distance from the box, per axis
    fDX = s_vCollCam.x < pSec->bbTight.inf.x ? pSec->bbTight.inf.x - s_vCollCam.x
        : s_vCollCam.x > pSec->bbTight.sup.x ? s_vCollCam.x - pSec->bbTight.sup.x : 0.0f;
    fDY = s_vCollCam.y < pSec->bbTight.inf.y ? pSec->bbTight.inf.y - s_vCollCam.y
        : s_vCollCam.y > pSec->bbTight.sup.y ? s_vCollCam.y - pSec->bbTight.sup.y : 0.0f;
    fDZ = s_vCollCam.z < pSec->bbTight.inf.z ? pSec->bbTight.inf.z - s_vCollCam.z
        : s_vCollCam.z > pSec->bbTight.sup.z ? s_vCollCam.z - pSec->bbTight.sup.z : 0.0f;
    if (fDX * fDX + fDY * fDY + fDZ * fDZ > g_fTrigDrawCollisionRange * g_fTrigDrawCollisionRange)
        return pSector;
    if (pSec->pTriangles == NULL || pSec->pVertices == NULL)
        return pSector;

    for (i = 0; i < pSec->wNumTriangles; i++)
    {
        // (its material's kind: the world's material list, as the game's queries index it)
        type_96E30 *pWorld = (type_96E30 *)pData;
        RwInt32 nKind = pWorld && pWorld->unk_10 ? TrigDrawCollKindOf(pWorld->unk_10[pSec->pTriangles[i].matIndex]) : -1;

        if (nKind >= 0)
            g_aTrigDrawCollKinds[nKind].nTriangles++;
        if (s_bCollAnyShown && (nKind < 0 || !g_aTrigDrawCollKinds[nKind].bShow))
            continue;
        vA = pSec->pVertices[pSec->pTriangles[i].vertIndex[0]];
        vB = pSec->pVertices[pSec->pTriangles[i].vertIndex[1]];
        vC = pSec->pVertices[pSec->pTriangles[i].vertIndex[2]];
        vE1.x = vB.x - vA.x; vE1.y = vB.y - vA.y; vE1.z = vB.z - vA.z;
        vE2.x = vC.x - vA.x; vE2.y = vC.y - vA.y; vE2.z = vC.z - vA.z;
        vN.x = vE1.y * vE2.z - vE1.z * vE2.y;
        vN.y = vE1.z * vE2.x - vE1.x * vE2.z;
        vN.z = vE1.x * vE2.y - vE1.y * vE2.x;
        fLen = (RwReal)sqrt(vN.x * vN.x + vN.y * vN.y + vN.z * vN.z);
        if (fLen < 1e-6f)
            continue;
        vN.x /= fLen; vN.y /= fLen; vN.z /= fLen;
        // (y is up in this game's worlds)
        if (vN.y > 0.7f)
            dwColour = 0x6040FF40;
        else if (vN.y < -0.7f)
            dwColour = 0x60FF4040;
        else
            dwColour = 0x604080FF;
        if (g_bTrigDrawCollByKind)
            dwColour = TrigDrawCollKindColour(nKind);
        // (filled: the triangle, see-through)
        if (g_nTrigDrawCollFill != 1)
        {
            if (s_nCollVerts + 3 > TRIGDRAW_COLLVERTS)
                TrigDrawCollisionFlush();
            pVert = &s_aCollVerts[s_nCollVerts];
            for (k = 0; k < 3; k++)
            {
                const RwV3d *pv = k == 0 ? &vA : k == 1 ? &vB : &vC;
                RwIm3DVertexSetPos(&pVert[k], pv->x + vN.x * g_fTrigDrawCollisionLift,
                                   pv->y + vN.y * g_fTrigDrawCollisionLift,
                                   pv->z + vN.z * g_fTrigDrawCollisionLift);
                pVert[k].color = dwColour;
            }
            s_nCollVerts += 3;
        }
        // (outlines: its three edges, in the colour made opaque, and the grid lines across it a
        // little fainter; lifted a little more so they sit on the fill)
        if (g_nTrigDrawCollFill != 0)
        {
            RwReal fLift = g_fTrigDrawCollisionLift * 2.0f;
            RwUInt32 dwLine = dwColour | 0xFF000000;

            TrigDrawCollLine(&vA, &vB, &vN, fLift, dwLine);
            TrigDrawCollLine(&vB, &vC, &vN, fLift, dwLine);
            TrigDrawCollLine(&vC, &vA, &vN, fLift, dwLine);
            if (g_fTrigDrawCollGrid > 0.5f)
                TrigDrawCollGrid(&vA, &vB, &vC, &vN, g_fTrigDrawCollGrid, fLift, (dwColour & 0x00FFFFFF) | 0xB0000000);
        }
    }
    return pSector;
}

// Draws the collision worlds near the camera at pvCam: the global section's
// and every live section slot's (as the collision queries walk them).
static void TrigDrawCollision(const RwV3d *pvCam)
{
    RwInt32 i;

    s_vCollCam = *pvCam;
    s_nCollVerts = 0;
    s_nCollLineVerts = 0;
    // (this frame's counts and material cache; whether any kind is shown)
    memset(s_aCollMatCache, 0, sizeof(s_aCollMatCache));
    s_bCollAnyShown = FALSE;
    for (i = 0; i < g_nTrigDrawCollKinds; i++)
    {
        g_aTrigDrawCollKinds[i].nTriangles = 0;
        g_aTrigDrawCollKinds[i].nMaterials = 0;
        if (g_aTrigDrawCollKinds[i].bShow)
            s_bCollAnyShown = TRUE;
    }
    if (unk_4E5CD8.get_unk_28())
        RpWorldForAllWorldSectors(unk_4E5CD8.get_unk_28(), TrigDrawCollisionSector, unk_4E5CD8.get_unk_28());
    for (i = 0; i < 4; i++)
    {
        if (dword_4E5D30[i].get_unk_00() && dword_4E5D30[i].get_unk_28())
            RpWorldForAllWorldSectors(dword_4E5D30[i].get_unk_28(), TrigDrawCollisionSector,
                                      dword_4E5D30[i].get_unk_28());
    }
    TrigDrawCollisionFlush();
    TrigDrawCollisionLineFlush();
}

// A stick axis as -1..1, with the game's dead zone (flt_42C77C) of 0.25 of
// the range when it is unset.
static RwReal TrigDrawStick(SHORT sValue)
{
    RwReal fValue = (RwReal)sValue / 32767.0f;
    RwReal fDead = flt_42C77C > 0.0f && flt_42C77C < 1.0f ? flt_42C77C : 0.25f;

    if (fValue > -fDead && fValue < fDead)
        return 0.0f;
    return fValue > 1.0f ? 1.0f : fValue < -1.0f ? -1.0f : fValue;
}

// Noclip: moves *pvPos freely for one collision step of fStep units, along
// the main camera's view (dword_4E5C74) by the first connected controller's
// left stick, up while Black is held and down while White is (the
// controller's raw XInput state, dword_4F4638). Looking stays the game's.
void TrigDrawNoclipMove(RwV3d *pvPos, RwReal fStep)
{
    type_4F4638 *pPad = NULL;
    RwCamera *pCamera = (RwCamera *)dword_4E5C74;
    RwMatrix *pLtm;
    RwReal fFwd, fSide, fUp, fDist;
    RwInt32 i;

    for (i = 0; i < 4; i++)
    {
        if (dword_4F4638[i].unk_48)
        {
            pPad = &dword_4F4638[i];
            break;
        }
    }
    if (pPad == NULL || pCamera == NULL)
        return;
    pLtm = RwFrameGetLTM(RwCameraGetFrame(pCamera));
    fFwd = TrigDrawStick(pPad->unk_00.Gamepad.sThumbLY);
    fSide = TrigDrawStick(pPad->unk_00.Gamepad.sThumbLX);
    fUp = 0.0f;
    if (pPad->unk_00.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_BLACK] > 30)
        fUp += 1.0f;
    if (pPad->unk_00.Gamepad.bAnalogButtons[XINPUT_GAMEPAD_WHITE] > 30)
        fUp -= 1.0f;
    fDist = g_fTrigDrawNoclipSpeed * fStep;
    // (a RenderWare camera's right vector points to the screen's left)
    pvPos->x += (pLtm->at.x * fFwd - pLtm->right.x * fSide) * fDist;
    pvPos->y += (pLtm->at.y * fFwd - pLtm->right.y * fSide + fUp) * fDist;
    pvPos->z += (pLtm->at.z * fFwd - pLtm->right.z * fSide) * fDist;
}

// ---- the free camera ----

// The free camera (View, Camera's switch): the world is drawn from its own
// place and look instead of the game's camera, which is put back after the
// frame (TrigDrawFreeCamBegin, TrigDrawFreeCamEnd, from sub_125F20), so the
// game's logic, aiming and sound go on from the player; while it is on, pad
// 0 (the keyboard and mouse with it) is the camera's, not the game's
// (port_freecam_input, from the port's XInputGetState; start and back stay
// the game's), outside the menus. The left stick (WASD) moves along the look,
// the right stick (the mouse) looks, Black and White (Q, E) go up and down,
// the right trigger is four times the speed, the left a quarter.
RwBool g_bTrigDrawFreeCam = FALSE;
RwReal g_fTrigDrawFreeCamSpeed = 1000.0f;   // units a second (noclip's default is about 3000)
RwReal g_fTrigDrawFreeCamLook = 2.5f;       // radians a second at full deflection

static RwBool s_bFreeCamLive;               // its place set from the game's camera
static RwV3d s_vFreeCamPos;
static RwReal s_fFreeCamYaw, s_fFreeCamPitch;
static XINPUT_GAMEPAD s_FreeCamPad;         // the pad as the camera last took it
static RwMatrix s_mFreeCamSaved;            // the game's camera, put back after the frame
static RwBool s_bFreeCamSaved;
static LARGE_INTEGER s_liFreeCamLast;

extern "C" int port_in_menus(void);

// Takes pad 0's state for the free camera while it is on in a level: TRUE
// when it did (the game then gets a neutral pad).
extern "C" int port_freecam_input(XINPUT_GAMEPAD *pPad)
{
    static RwInt32 s_nStart = -1;

    // (CODFH_FREECAM=1 starts with it on)
    if (s_nStart < 0)
    {
        s_nStart = GetEnvironmentVariableA("CODFH_FREECAM", NULL, 0) ? 1 : 0;
        if (s_nStart)
            g_bTrigDrawFreeCam = TRUE;
    }
    if (!g_bTrigDrawFreeCam || dword_4E5C74 == NULL || port_in_menus())
        return FALSE;
    s_FreeCamPad = *pPad;
    return TRUE;
}

RwBool TrigDrawFreeCamActive()
{
    return g_bTrigDrawFreeCam && dword_4E5C74 != NULL;
}

// A stick axis as -1..1 with a dead zone of 0.2.
static RwReal TrigDrawFreeCamAxis(SHORT sValue)
{
    RwReal f = (RwReal)sValue / 32767.0f;

    if (f > -0.2f && f < 0.2f)
        return 0.0f;
    return f > 1.0f ? 1.0f : f < -1.0f ? -1.0f : f;
}

// Before the world is drawn: moves the free camera by the pad over the time
// since the last frame and puts the camera pCamera's frame there (the game's
// own matrix kept for TrigDrawFreeCamEnd).
void TrigDrawFreeCamBegin(RwCamera *pCamera)
{
    RwFrame *pFrame;
    RwMatrix *pLtm, mWorld, mInv;
    RwV3d vAt, vRight, vUp;
    RwReal fDt, fFwd, fSide, fRise, fSpeed, fCos;
    LARGE_INTEGER liNow, liFreq;

    s_bFreeCamSaved = FALSE;
    if (!g_bTrigDrawFreeCam || pCamera == NULL)
    {
        s_bFreeCamLive = FALSE;
        return;
    }
    pFrame = RwCameraGetFrame(pCamera);
    pLtm = RwFrameGetLTM(pFrame);
    QueryPerformanceCounter(&liNow);
    QueryPerformanceFrequency(&liFreq);
    if (!s_bFreeCamLive)
    {
        // (from where the game's camera is, looking its way)
        s_vFreeCamPos = pLtm->pos;
        s_fFreeCamYaw = (RwReal)atan2(pLtm->at.x, pLtm->at.z);
        s_fFreeCamPitch = (RwReal)asin(pLtm->at.y > 1.0f ? 1.0f : pLtm->at.y < -1.0f ? -1.0f : pLtm->at.y);
        memset(&s_FreeCamPad, 0, sizeof(s_FreeCamPad));
        s_liFreeCamLast = liNow;
        s_bFreeCamLive = TRUE;
    }
    fDt = (RwReal)((RwReal)(liNow.QuadPart - s_liFreeCamLast.QuadPart) / (RwReal)liFreq.QuadPart);
    s_liFreeCamLast = liNow;
    if (fDt > 0.1f)
        fDt = 0.1f;

    // the look: the right stick turns right (the yaw falls) and up
    s_fFreeCamYaw -= TrigDrawFreeCamAxis(s_FreeCamPad.sThumbRX) * g_fTrigDrawFreeCamLook * fDt;
    s_fFreeCamPitch += TrigDrawFreeCamAxis(s_FreeCamPad.sThumbRY) * g_fTrigDrawFreeCamLook * fDt;
    if (s_fFreeCamPitch > 1.55f)
        s_fFreeCamPitch = 1.55f;
    if (s_fFreeCamPitch < -1.55f)
        s_fFreeCamPitch = -1.55f;
    fCos = (RwReal)cos(s_fFreeCamPitch);
    vAt.x = fCos * (RwReal)sin(s_fFreeCamYaw);
    vAt.y = (RwReal)sin(s_fFreeCamPitch);
    vAt.z = fCos * (RwReal)cos(s_fFreeCamYaw);
    // (y is up; a RenderWare camera's right vector points to the screen's left: up x at)
    vRight.x = vAt.z;
    vRight.y = 0.0f;
    vRight.z = -vAt.x;
    fCos = (RwReal)sqrt(vRight.x * vRight.x + vRight.z * vRight.z);
    if (fCos < 1e-5f)
        fCos = 1e-5f;
    vRight.x /= fCos;
    vRight.z /= fCos;
    // (at x right)
    vUp.x = vAt.y * vRight.z - vAt.z * vRight.y;
    vUp.y = vAt.z * vRight.x - vAt.x * vRight.z;
    vUp.z = vAt.x * vRight.y - vAt.y * vRight.x;

    // the move: along the look, sideways (to the screen's right is -right), up and down
    fFwd = TrigDrawFreeCamAxis(s_FreeCamPad.sThumbLY);
    fSide = TrigDrawFreeCamAxis(s_FreeCamPad.sThumbLX);
    fRise = (s_FreeCamPad.bAnalogButtons[XINPUT_GAMEPAD_BLACK] > 30 ? 1.0f : 0.0f)
          - (s_FreeCamPad.bAnalogButtons[XINPUT_GAMEPAD_WHITE] > 30 ? 1.0f : 0.0f);
    fSpeed = g_fTrigDrawFreeCamSpeed * fDt;
    if (s_FreeCamPad.bAnalogButtons[7] > 30)
        fSpeed *= 4.0f;
    if (s_FreeCamPad.bAnalogButtons[6] > 30)
        fSpeed *= 0.25f;
    s_vFreeCamPos.x += (vAt.x * fFwd - vRight.x * fSide) * fSpeed;
    s_vFreeCamPos.y += (vAt.y * fFwd + fRise) * fSpeed;
    s_vFreeCamPos.z += (vAt.z * fFwd - vRight.z * fSide) * fSpeed;

    // the camera's frame there: its modelling matrix, relative to its parent's when it has one
    memset(&mWorld, 0, sizeof(mWorld));
    mWorld.right = vRight;
    mWorld.up = vUp;
    mWorld.at = vAt;
    mWorld.pos = s_vFreeCamPos;
    mWorld.flags = 3;
    s_mFreeCamSaved = pFrame->modelling;
    s_bFreeCamSaved = TRUE;
    if (RwFrameGetParent(pFrame))
    {
        RwMatrixInvert(&mInv, RwFrameGetLTM(RwFrameGetParent(pFrame)));
        RwMatrixMultiply(&pFrame->modelling, &mWorld, &mInv);
    }
    else
        pFrame->modelling = mWorld;
    RwFrameUpdateObjects(pFrame);
}

// After the frame: the game's camera back as the game left it.
void TrigDrawFreeCamEnd(RwCamera *pCamera)
{
    RwFrame *pFrame;

    if (!s_bFreeCamSaved || pCamera == NULL)
        return;
    pFrame = RwCameraGetFrame(pCamera);
    pFrame->modelling = s_mFreeCamSaved;
    RwFrameUpdateObjects(pFrame);
    s_bFreeCamSaved = FALSE;
}

// Whether the trigger is within g_fTrigDrawRange of the camera at pvCam
// (always when the range is 0).
static RwBool TrigDrawInRange(Trigger *pTrigger, const RwV3d *pvCam)
{
    RwReal fDX, fDY, fDZ, fReach;

    if (g_fTrigDrawRange <= 0.0f)
        return TRUE;
    fDX = pTrigger->unk_90 - pvCam->x;
    fDY = pTrigger->unk_94 - pvCam->y;
    fDZ = pTrigger->unk_98 - pvCam->z;
    fReach = g_fTrigDrawRange + pTrigger->unk_48 + pTrigger->unk_4C + pTrigger->unk_50;
    return fDX * fDX + fDY * fDY + fDZ * fDZ <= fReach * fReach;
}

// Draws every registered trigger within g_fTrigDrawRange of the camera
// pCamera, outlines first and then their labels; called once a frame after
// the world (sub_125F20). Saves and restores the render states it changes.
// Points the free camera at pv from a little way off (Level, Generators).
void TrigDrawFreeCamLookAt(const RwV3d *pv)
{
    RwV3d vFrom, vD;
    RwReal fLen;

    vFrom.x = pv->x - 500.0f;
    vFrom.y = pv->y + 350.0f;
    vFrom.z = pv->z - 500.0f;
    vD.x = pv->x - vFrom.x;
    vD.y = pv->y - vFrom.y;
    vD.z = pv->z - vFrom.z;
    fLen = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z);
    s_vFreeCamPos = vFrom;
    s_fFreeCamYaw = (RwReal)atan2(vD.x, vD.z);
    s_fFreeCamPitch = (RwReal)asin(vD.y / fLen);
    memset(&s_FreeCamPad, 0, sizeof(s_FreeCamPad));
    QueryPerformanceCounter(&s_liFreeCamLast);
    s_bFreeCamLive = TRUE;
    g_bTrigDrawFreeCam = TRUE;
}

// The free camera's place, for the live link (trigweb.cpp): TRUE while it is on.
RwBool TrigDrawFreeCamGet(RwV3d *pv, RwReal *pfYaw, RwReal *pfPitch)
{
    if (!g_bTrigDrawFreeCam || !s_bFreeCamLive)
        return FALSE;
    *pv = s_vFreeCamPos;
    *pfYaw = s_fFreeCamYaw;
    *pfPitch = s_fFreeCamPitch;
    return TRUE;
}

// Puts the free camera at pv, looking along fYaw and fPitch (the viewer's own view).
void TrigDrawFreeCamSet(const RwV3d *pv, RwReal fYaw, RwReal fPitch)
{
    s_vFreeCamPos = *pv;
    s_fFreeCamYaw = fYaw;
    s_fFreeCamPitch = fPitch > 1.55f ? 1.55f : fPitch < -1.55f ? -1.55f : fPitch;
    memset(&s_FreeCamPad, 0, sizeof(s_FreeCamPad));
    QueryPerformanceCounter(&s_liFreeCamLast);
    s_bFreeCamLive = TRUE;
    g_bTrigDrawFreeCam = TRUE;
}

// A trigger kind's class name (the labels' table), or NULL.
const RwChar *TrigDrawKindName(RwInt32 nKind)
{
    return nKind >= 0 && nKind < 0x28 ? s_apszKindNames[nKind] : NULL;
}

static RwReal TrigDrawDist2(const RwV3d *pA, const RwV3d *pB)
{
    RwReal dx = pA->x - pB->x, dy = pA->y - pB->y, dz = pA->z - pB->z;
    return dx * dx + dy * dy + dz * dz;
}

// ---- the world line tests ----

RwBool g_bTrigDrawRays = FALSE;
RwBool g_bTrigDrawRayMisses = FALSE;
RwReal g_fTrigDrawRaySecs = 0.5f;
RwBool g_abTrigDrawRayKinds[6] = { TRUE, TRUE, FALSE, TRUE, TRUE, FALSE };
RwInt32 g_anTrigDrawRayCount[6];

#define TRIGDRAW_RAYS 2048

// A test: its line, whether it hit and where, its mask, its kind, the caller, when.
struct TrigDrawRay
{
    RwV3d vStart, vEnd, vHit;
    RwUInt32 dwMask, dwTick, dwFrame;
    const void *pCaller;
    RwInt32 nKind, bHit, nSurface;
};
static TrigDrawRay s_aRays[TRIGDRAW_RAYS];
static RwInt32 s_nRayNext;
static RwInt32 s_anRayThisSecond[6];
static RwUInt32 s_dwRaySecond;

const RwChar *TrigDrawRayKindName(RwInt32 nKind)
{
    static const RwChar *const s_apsz[6] = { "bullets and grenades (0x180000)", "AI sight (0x420000)",
                                             "AI paths (0x10000, 0x20000)", "aim (0x590000)",
                                             "vehicles (0x40000, 0x840000)", "other masks" };
    return nKind >= 0 && nKind < 6 ? s_apsz[nKind] : "?";
}

static RwInt32 TrigDrawRayKind(RwUInt32 dwMask)
{
    switch (dwMask)
    {
    case 0x180000: return 0;
    case 0x420000: return 1;
    case 0x10000: case 0x20000: case 0x30000: return 2;
    case 0x590000: return 3;
    case 0x40000: case 0x840000: return 4;
    }
    return 5;
}

static const RwUInt32 s_adwRayKind[6] = { 0xFFFFD040, 0xFF40C0FF, 0xFF80FF80, 0xFFFF60FF, 0xFFFF9040, 0xFFC0C0C0 };

// (from sub_91F40's end: one call a collision world, so a test over the four section worlds comes
// four times; the same line from the same caller in one frame is one test, its nearest hit kept)
void TrigDrawLineTest(const RwV3d *pvStart, const RwV3d *pvEnd, RwInt32 bHit, RwReal fT, RwUInt32 dwMask,
                      RwInt32 nSurface, const void *pCaller)
{
    TrigDrawRay *r;
    RwInt32 nKind = TrigDrawRayKind(dwMask), i;
    RwUInt32 dwNow;

    if (!g_bTrigDrawRays)
        return;
    dwNow = GetTickCount();
    if (dwNow - s_dwRaySecond >= 1000)
    {
        memcpy(g_anTrigDrawRayCount, s_anRayThisSecond, sizeof(g_anTrigDrawRayCount));
        memset(s_anRayThisSecond, 0, sizeof(s_anRayThisSecond));
        s_dwRaySecond = dwNow;
    }
    for (i = 1; i <= 4; i++)
    {
        TrigDrawRay *q = &s_aRays[(s_nRayNext + TRIGDRAW_RAYS - i) % TRIGDRAW_RAYS];

        if (q->dwFrame == port_frame && q->pCaller == pCaller && q->vStart.x == pvStart->x && q->vStart.y == pvStart->y
            && q->vStart.z == pvStart->z && q->vEnd.x == pvEnd->x && q->vEnd.y == pvEnd->y && q->vEnd.z == pvEnd->z)
        {
            if (bHit && (!q->bHit || (fT < 1.0f && TrigDrawDist2(pvStart, &q->vHit) >
                                                       (fT * fT) * TrigDrawDist2(pvStart, pvEnd))))
            {
                q->bHit = 1;
                q->vHit.x = pvStart->x + (pvEnd->x - pvStart->x) * fT;
                q->vHit.y = pvStart->y + (pvEnd->y - pvStart->y) * fT;
                q->vHit.z = pvStart->z + (pvEnd->z - pvStart->z) * fT;
                q->nSurface = nSurface;
            }
            return;
        }
    }
    s_anRayThisSecond[nKind]++;
    r = &s_aRays[s_nRayNext];
    s_nRayNext = (s_nRayNext + 1) % TRIGDRAW_RAYS;
    r->vStart = *pvStart;
    r->vEnd = *pvEnd;
    r->bHit = bHit;
    r->nSurface = nSurface;
    if (bHit)
    {
        r->vHit.x = pvStart->x + (pvEnd->x - pvStart->x) * fT;
        r->vHit.y = pvStart->y + (pvEnd->y - pvStart->y) * fT;
        r->vHit.z = pvStart->z + (pvEnd->z - pvStart->z) * fT;
    }
    r->dwMask = dwMask;
    r->nKind = nKind;
    r->pCaller = pCaller;
    r->dwTick = dwNow ? dwNow : 1;
    r->dwFrame = port_frame;
}

// The recent tests: a hit drawn to where it hit in its kind's colour, with a cross there (red),
// the rest of its line faint; a miss (when shown) faint in its colour; all fading.
static void TrigDrawRays()
{
    RwUInt32 dwNow = GetTickCount(), dwKeep = (RwUInt32)(g_fTrigDrawRaySecs * 1000.0f);
    RwInt32 i;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < TRIGDRAW_RAYS; i++)
    {
        const TrigDrawRay *r = &s_aRays[i];
        RwUInt32 dwAge, dwColour, dwAlpha;

        if (!r->dwTick || !g_abTrigDrawRayKinds[r->nKind])
            continue;
        dwAge = dwNow - r->dwTick;
        if (dwAge > dwKeep)
            continue;
        dwAlpha = (RwUInt32)(255.0f * (1.0f - (RwReal)dwAge / (dwKeep ? dwKeep : 1)));
        dwColour = (s_adwRayKind[r->nKind] & 0x00FFFFFF) | (dwAlpha << 24);
        if (r->bHit)
        {
            TrigDrawPathLine(&r->vStart, &r->vHit, dwColour);
            TrigDrawPathLine(&r->vHit, &r->vEnd, (dwColour & 0x00FFFFFF) | ((dwAlpha / 5) << 24));
            TrigDrawCross(&r->vHit, 6.0f, 0x00FF3030 | (dwAlpha << 24));
        }
        else if (g_bTrigDrawRayMisses)
            TrigDrawPathLine(&r->vStart, &r->vEnd, (dwColour & 0x00FFFFFF) | ((dwAlpha / 3) << 24));
    }
    TrigDrawPathFlush();
}

// ---- bullet hits and the bone boxes ----

RwBool g_bTrigDrawHits = FALSE;
RwBool g_bTrigDrawHitBoxes = FALSE;
RwReal g_fTrigDrawHitSecs = 2.0f;
RwReal g_fTrigDrawHitBoxRange = 1500.0f;
RwInt32 g_nTrigDrawHitBoxesShown;

#define TRIGDRAW_HITS 64

struct TrigDrawHit
{
    const void *pEntity;
    RwV3d v;
    RwReal fDamage, fDealt;     // the bullet's, and what the soldier lost (sub_13C490; -1 unknown)
    RwInt32 nPart;
    RwUInt32 dwTick, dwFrame;
};
static TrigDrawHit s_aHits[TRIGDRAW_HITS];
static RwInt32 s_nHitNext;

// (from the projectiles' steps, just before the entity's vf_064)
void TrigDrawBulletHit(void *pEntity, const RwV3d *pv, RwInt32 nPart, RwReal fDamage)
{
    TrigDrawHit *h;

    if (pv == NULL)
        return;
    h = &s_aHits[s_nHitNext];
    s_nHitNext = (s_nHitNext + 1) % TRIGDRAW_HITS;
    h->pEntity = pEntity;
    h->v = *pv;
    h->nPart = nPart;
    h->fDamage = fDamage;
    h->fDealt = -1.0f;
    h->dwTick = GetTickCount();
    h->dwFrame = port_frame;
}

// (from the soldiers' sub_13C490: the hit points it takes, put on this frame's hit on it)
void TrigDrawDamageTaken(void *pEntity, RwReal fAmount)
{
    RwInt32 i;

    for (i = 1; i <= TRIGDRAW_HITS; i++)
    {
        TrigDrawHit *h = &s_aHits[(s_nHitNext + TRIGDRAW_HITS - i) % TRIGDRAW_HITS];

        if (h->dwFrame != port_frame)
            break;
        if (h->pEntity == pEntity && h->fDealt < 0.0f)
        {
            h->fDealt = fAmount;
            return;
        }
    }
}

static const RwChar *TrigDrawPartName(RwInt32 nPart)
{
    // (the parts the bone boxes return, dword_428E80: 0 the head; the rest by their order)
    static const RwChar *const s_apsz[9] = { "head", "chest", "pelvis", "arm", "arm", "forearm", "leg", "leg", "shin" };
    return nPart >= 0 && nPart < 9 ? s_apsz[nPart] : "body";
}

// A box's twelve edges, its corners the two given.
static void TrigDrawBox(const RwV3d *pMin, const RwV3d *pMax, RwUInt32 dwColour)
{
    RwV3d c[8];
    RwInt32 i;
    static const RwInt32 s_aEdges[12][2] = { {0,1},{1,3},{3,2},{2,0},{4,5},{5,7},{7,6},{6,4},{0,4},{1,5},{2,6},{3,7} };

    for (i = 0; i < 8; i++)
    {
        c[i].x = (i & 1) ? pMax->x : pMin->x;
        c[i].y = (i & 2) ? pMax->y : pMin->y;
        c[i].z = (i & 4) ? pMax->z : pMin->z;
    }
    for (i = 0; i < 12; i++)
        TrigDrawPathLine(&c[s_aEdges[i][0]], &c[s_aEdges[i][1]], dwColour);
}

// The soldiers' (and gimps') bone boxes in view, as the bullets test them against the player
// (sub_8D660: kind 0, the others 0.75 of their size): each bone's box through its matrix to a
// box in the world (sub_8C410); the head's red. Off screen the game tests one box from the
// entity's width and height; that one is drawn grey.
static void TrigDrawHitBoxesAll(const RwV3d *pvCam)
{
    RwInt32 i, k;

    g_nTrigDrawHitBoxesShown = 0;
    for (i = 0; i < 0x300; i++)
    {
        type_3D3548 *pEntity = dword_4B6A00[i].unk_04;

        if (pEntity == NULL)
            continue;
        __try
        {
            RwMatrix *pLtm;
            RpHAnimHierarchy *pH;
            RwMatrix *aBones;
            RwReal dx, dy, dz;

            if (pEntity->unk_58 != 1 || !pEntity->unk_88_1 || pEntity->unk_284 == NULL)
                continue;
            pH = pEntity->unk_284->unk_18;
            if (pH == NULL)
                continue;
            aBones = RpHAnimHierarchyGetMatrixArray(pH);
            if (aBones == NULL)
                continue;
            pLtm = &aBones[0];
            dx = pLtm->pos.x - pvCam->x;
            dy = pLtm->pos.y - pvCam->y;
            dz = pLtm->pos.z - pvCam->z;
            if (g_fTrigDrawHitBoxRange > 0.0f && dx * dx + dy * dy + dz * dz > g_fTrigDrawHitBoxRange * g_fTrigDrawHitBoxRange)
                continue;
            g_nTrigDrawHitBoxesShown++;
            if (!pEntity->unk_28_13)
                continue;
            for (k = 0; k < 13; k++)
            {
                // (the table's boxes in order, as the game's loop steps through them)
                const type_4B21D0_60 *pBox = &dword_4B21D0.unk_60[0] + k;
                __declspec(align(16)) type_8C410 box, world;
                type_8BFA0 m;
                RwReal fScale = k == 0 ? 1.0f : 0.75f;
                RwV3d vMin, vMax;
                RwInt32 nBone = (RwInt32)pBox->unk_0C;

                if (nBone < 0 || nBone > 255)
                    continue;
                m = *(type_8BFA0 *)&aBones[nBone];
                m.unk_00[0].unk_0C = 0.0f;
                m.unk_00[1].unk_0C = 0.0f;
                m.unk_00[2].unk_0C = 0.0f;
                m.unk_00[3].unk_0C = 1.0f;
                box.unk_00.unk_00 = fScale * pBox->unk_00;
                box.unk_00.unk_04 = fScale * pBox->unk_04;
                box.unk_00.unk_08 = fScale * pBox->unk_08;
                box.unk_10.unk_00 = fScale * pBox->unk_10;
                box.unk_10.unk_04 = fScale * pBox->unk_14;
                box.unk_10.unk_08 = fScale * pBox->unk_18;
                world = sub_8C410((RwMatrix *)&m, &box.unk_00);
                vMin.x = world.unk_00.unk_00;
                vMin.y = world.unk_00.unk_04;
                vMin.z = world.unk_00.unk_08;
                vMax.x = world.unk_10.unk_00;
                vMax.y = world.unk_10.unk_04;
                vMax.z = world.unk_10.unk_08;
                TrigDrawBox(&vMin, &vMax, dword_428E80[k].unk_10 == 0 ? 0xC0FF4040 : 0x9040FF80);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
}

// The recent hits: a cross where the bullet hit, its damage (what the soldier lost when known,
// else the bullet's) and its part, rising as it fades; a head shot red.
static void TrigDrawHits(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwUInt32 dwNow = GetTickCount(), dwKeep = (RwUInt32)(g_fTrigDrawHitSecs * 1000.0f);
    RwInt32 i;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < TRIGDRAW_HITS; i++)
    {
        const TrigDrawHit *h = &s_aHits[i];
        RwUInt32 dwAge;

        if (!h->dwTick)
            continue;
        dwAge = dwNow - h->dwTick;
        if (dwAge > dwKeep)
            continue;
        TrigDrawCross(&h->v, 5.0f, h->nPart == 0 ? 0xFFFF3030 : 0xFFFFD040);
    }
    TrigDrawPathFlush();
    if (TrigDrawCharset() == NULL)
        return;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
    for (i = 0; i < TRIGDRAW_HITS; i++)
    {
        const TrigDrawHit *h = &s_aHits[i];
        RwUInt32 dwAge;
        RwChar sz[48];
        RwV3d vAt;
        RwReal f;

        if (!h->dwTick)
            continue;
        dwAge = dwNow - h->dwTick;
        if (dwAge > dwKeep)
            continue;
        f = (RwReal)dwAge / (dwKeep ? dwKeep : 1);
        vAt = h->v;
        vAt.y += 10.0f + 30.0f * f;
        if (h->fDealt >= 0.0f)
            _snprintf(sz, sizeof(sz), "-%.0f %s", h->fDealt, TrigDrawPartName(h->nPart));
        else
            _snprintf(sz, sizeof(sz), "%.0f %s", h->fDamage, h->nPart >= 0 ? TrigDrawPartName(h->nPart) : "");
        sz[sizeof(sz) - 1] = 0;
        TrigDrawText(sz, &vAt, pCamLtm, ((RwUInt32)(255.0f * (1.0f - f)) << 24) | (h->nPart == 0 ? 0xFF4040 : 0xFFE060));
    }
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
}

// ---- the lights ----

RwBool g_bTrigDrawLights = FALSE;
RwBool g_bTrigDrawLightLabels = TRUE;
RwBool g_bTrigDrawLightRadii = TRUE;
RwReal g_fTrigDrawLightRange = 6000.0f;
TrigDrawLightInfo g_aTrigDrawLightList[TRIGDRAW_LIGHTS];
RwInt32 g_nTrigDrawLightList;
// (render.h's dword_4E5C7C: the level's light list; particles.h's dword_4E5C98, the directional
// slots, clump the ambient and camera the fallback directional)

static void TrigDrawLightAdd(RpLight *pLight, RwInt32 nSource)
{
    TrigDrawLightInfo *o;
    RwFrame *pFrame;
    RwInt32 i;

    if (pLight == NULL || g_nTrigDrawLightList >= TRIGDRAW_LIGHTS)
        return;
    for (i = 0; i < g_nTrigDrawLightList; i++)
        if (g_aTrigDrawLightList[i].id == pLight)
            return;
    o = &g_aTrigDrawLightList[g_nTrigDrawLightList];
    memset(o, 0, sizeof(*o));
    o->id = pLight;
    o->nType = pLight->object.subType;
    o->nFlags = pLight->object.flags;
    o->fRadius = pLight->radius;
    o->colour = pLight->color;
    o->fCone = *(const RwReal *)((const RwUInt8 *)pLight + 0x28);   // (minusCosAngle)
    o->nSource = nSource;
    pFrame = RpLightGetFrame(pLight);
    if (pFrame)
    {
        RwMatrix *m = RwFrameGetLTM(pFrame);

        o->vPos = m->pos;
        o->vAt = m->at;
    }
    g_nTrigDrawLightList++;
}

// The lights: the level's list (its own, sub_173800), the ambient, the directional slots and the
// fallback directional; each point or spot a cross in its colour with its radius as three rings
// (a spot its cone's axis too), the directionals arrows in front of the camera.
static void TrigDrawLights(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RpLight *pLight;
    RwInt32 i, n;

    g_nTrigDrawLightList = 0;
    __try
    {
        for (pLight = dword_4E5C7C, n = 0; pLight != NULL && n < 512; n++)
        {
            TrigDrawLightAdd(pLight, 0);
            pLight = (RpLight *)((type_3D96FC *)sub_FBDD0(pLight))->unk_1C;
        }
        TrigDrawLightAdd(clump, 1);
        for (i = 0; i < 4; i++)
            TrigDrawLightAdd(dword_4E5C98[i], 2);
        TrigDrawLightAdd(camera, 3);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < g_nTrigDrawLightList; i++)
    {
        const TrigDrawLightInfo *l = &g_aTrigDrawLightList[i];
        RwUInt32 r = (RwUInt32)(l->colour.red > 1.0f ? 255 : l->colour.red < 0.0f ? 0 : l->colour.red * 255.0f);
        RwUInt32 g = (RwUInt32)(l->colour.green > 1.0f ? 255 : l->colour.green < 0.0f ? 0 : l->colour.green * 255.0f);
        RwUInt32 b = (RwUInt32)(l->colour.blue > 1.0f ? 255 : l->colour.blue < 0.0f ? 0 : l->colour.blue * 255.0f);
        RwUInt32 dwColour = 0xFF000000 | (r << 16) | (g << 8) | b;
        RwV3d vAt;

        // (a dark light still shows)
        if (r + g + b < 60)
            dwColour = 0xFF505050;
        if (l->nType >= 0x80)
        {
            RwReal dx = l->vPos.x - pvCam->x, dy = l->vPos.y - pvCam->y, dz = l->vPos.z - pvCam->z;

            if (g_fTrigDrawLightRange > 0.0f && dx * dx + dy * dy + dz * dz > g_fTrigDrawLightRange * g_fTrigDrawLightRange)
                continue;
            TrigDrawCross(&l->vPos, 20.0f, dwColour);
            if (g_bTrigDrawLightRadii && l->fRadius > 0.0f && l->fRadius < 20000.0f)
            {
                RwInt32 k;

                for (k = 0; k < 24; k++)
                {
                    RwReal a0 = k * 6.2831853f / 24.0f, a1 = (k + 1) * 6.2831853f / 24.0f;
                    RwReal c0 = (RwReal)cos(a0) * l->fRadius, s0 = (RwReal)sin(a0) * l->fRadius;
                    RwReal c1 = (RwReal)cos(a1) * l->fRadius, s1 = (RwReal)sin(a1) * l->fRadius;
                    RwV3d pA = l->vPos, pB = l->vPos;
                    RwUInt32 dwRing = (dwColour & 0x00FFFFFF) | 0x70000000;

                    pA.x += c0; pA.z += s0; pB.x += c1; pB.z += s1;
                    TrigDrawPathLine(&pA, &pB, dwRing);
                    pA = l->vPos; pB = l->vPos;
                    pA.x += c0; pA.y += s0; pB.x += c1; pB.y += s1;
                    TrigDrawPathLine(&pA, &pB, dwRing);
                    pA = l->vPos; pB = l->vPos;
                    pA.y += c0; pA.z += s0; pB.y += c1; pB.z += s1;
                    TrigDrawPathLine(&pA, &pB, dwRing);
                }
            }
            if (l->nType > 0x80)
            {
                vAt = l->vPos;
                vAt.x += l->vAt.x * (l->fRadius > 0.0f ? l->fRadius : 200.0f);
                vAt.y += l->vAt.y * (l->fRadius > 0.0f ? l->fRadius : 200.0f);
                vAt.z += l->vAt.z * (l->fRadius > 0.0f ? l->fRadius : 200.0f);
                TrigDrawPathLine(&l->vPos, &vAt, dwColour);
            }
        }
        else if (l->nType == 1)
        {
            // (an arrow along its direction, 300 in front of the camera, spread out by slot)
            RwV3d vBase = *pvCam, vTip;

            vBase.x += pCamLtm->at.x * 300.0f + pCamLtm->right.x * (i * 25.0f - 50.0f);
            vBase.y += pCamLtm->at.y * 300.0f + 60.0f;
            vBase.z += pCamLtm->at.z * 300.0f + pCamLtm->right.z * (i * 25.0f - 50.0f);
            vTip = vBase;
            vTip.x += l->vAt.x * 40.0f;
            vTip.y += l->vAt.y * 40.0f;
            vTip.z += l->vAt.z * 40.0f;
            TrigDrawPathLine(&vBase, &vTip, dwColour);
            TrigDrawCross(&vTip, 3.0f, dwColour);
        }
    }
    TrigDrawPathFlush();
    if (g_bTrigDrawLightLabels && TrigDrawCharset() != NULL)
    {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
        for (i = 0; i < g_nTrigDrawLightList; i++)
        {
            const TrigDrawLightInfo *l = &g_aTrigDrawLightList[i];
            RwChar sz[96];
            RwV3d vAt = l->vPos;
            RwReal dx = l->vPos.x - pvCam->x, dy = l->vPos.y - pvCam->y, dz = l->vPos.z - pvCam->z;

            if (l->nType < 0x80)
                continue;
            if (g_fTrigDrawLightRange > 0.0f && dx * dx + dy * dy + dz * dz > g_fTrigDrawLightRange * g_fTrigDrawLightRange)
                continue;
            _snprintf(sz, sizeof(sz), "%s light, radius %.0f, %.2f %.2f %.2f", l->nType == 0x80 ? "point" : "spot",
                      l->fRadius, l->colour.red, l->colour.green, l->colour.blue);
            sz[sizeof(sz) - 1] = 0;
            vAt.y += 25.0f;
            TrigDrawText(sz, &vAt, pCamLtm, 0xFFFFFFFF);
        }
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    }
}

// ---- the lighting zones ----

RwBool g_bTrigDrawZones = FALSE;
RwBool g_bTrigDrawZoneEntities = TRUE;
RwBool g_bTrigDrawZoneLabels = TRUE;
RwReal g_fTrigDrawZoneRange = 4000.0f;
RwInt32 g_nTrigDrawZonesAll, g_nTrigDrawZonesShown;

// A colour per zone index (a hue each; the default zone white, none grey).
static RwUInt32 TrigDrawZoneColour(RwInt32 nZone)
{
    static const RwUInt32 s_adw[12] =
    {
        0xFF5AC8FA, 0xFFFF9F43, 0xFF7CE07C, 0xFFFF6B9D, 0xFFC490FF, 0xFFFFE066,
        0xFF4ADEDE, 0xFFFF7A5C, 0xFF9AD24A, 0xFF7A9CFF, 0xFFE07CE0, 0xFFB0B0FF,
    };
    if (nZone == -2)
        return 0xFFFFFFFF;
    if (nZone < 0)
        return 0xFF707070;
    return s_adw[nZone % 12];
}

// The index of a zone in the table (-2 the default zone, -1 none or unknown).
static RwInt32 TrigDrawZoneIndex(const type_8F3E0 *pZone)
{
    RwInt32 i;

    if (pZone == NULL)
        return -1;
    if (pZone == &dword_4E5BE0)
        return -2;
    for (i = 0; i < dword_4B2550.unk_00 && i < 256; i++)
        if (dword_4B2550.get_zone(i) == pZone)
            return i;
    return -1;
}

// The zones' boxes (each a bound: a zone may also be cut by planes) in their colours, labelled
// with their index and ambient; each entity's mark in its zone's colour (a line to the zone it
// is fading out of while it does).
static void TrigDrawZones(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwInt32 i;

    g_nTrigDrawZonesAll = 0;
    g_nTrigDrawZonesShown = 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    __try
    {
        g_nTrigDrawZonesAll = dword_4B2550.unk_08 ? dword_4B2550.unk_00 : 0;
        for (i = 0; i < g_nTrigDrawZonesAll && i < 256; i++)
        {
            type_8F3E0 *z = dword_4B2550.get_zone(i);
            RwV3d vMin, vMax, vMid;

            if (z == NULL)
                continue;
            vMin.x = z->unk_00[0].unk_00;
            vMin.y = z->unk_00[0].unk_04;
            vMin.z = z->unk_00[0].unk_08;
            vMax.x = z->unk_00[1].unk_00;
            vMax.y = z->unk_00[1].unk_04;
            vMax.z = z->unk_00[1].unk_08;
            vMid.x = (vMin.x + vMax.x) * 0.5f;
            vMid.y = (vMin.y + vMax.y) * 0.5f;
            vMid.z = (vMin.z + vMax.z) * 0.5f;
            if (g_fTrigDrawZoneRange > 0.0f)
            {
                // (the camera's distance from the box)
                RwReal dx = pvCam->x < vMin.x ? vMin.x - pvCam->x : pvCam->x > vMax.x ? pvCam->x - vMax.x : 0.0f;
                RwReal dy = pvCam->y < vMin.y ? vMin.y - pvCam->y : pvCam->y > vMax.y ? pvCam->y - vMax.y : 0.0f;
                RwReal dz = pvCam->z < vMin.z ? vMin.z - pvCam->z : pvCam->z > vMax.z ? pvCam->z - vMax.z : 0.0f;

                if (dx * dx + dy * dy + dz * dz > g_fTrigDrawZoneRange * g_fTrigDrawZoneRange)
                    continue;
            }
            g_nTrigDrawZonesShown++;
            TrigDrawBox(&vMin, &vMax, (TrigDrawZoneColour(i) & 0x00FFFFFF) | 0xA0000000);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    if (g_bTrigDrawZoneEntities)
    {
        for (i = 0; i < 0x300; i++)
        {
            type_3D3548 *pEntity = dword_4B6A00[i].unk_04;

            if (pEntity == NULL)
                continue;
            __try
            {
                RwV3d vPos, vTop;
                RwInt32 nZone;

                if (pEntity->unk_338.unk_08 == NULL)
                    continue;
                vPos = RwFrameGetMatrix(pEntity->unk_338.unk_08)->pos;
                if (g_fTrigDrawZoneRange > 0.0f && TrigDrawDist2(&vPos, pvCam) > g_fTrigDrawZoneRange * g_fTrigDrawZoneRange)
                    continue;
                nZone = TrigDrawZoneIndex(pEntity->unk_90.unk_00);
                vTop = vPos;
                vTop.y += 90.0f;
                TrigDrawPathLine(&vPos, &vTop, TrigDrawZoneColour(nZone));
                TrigDrawCross(&vTop, 6.0f, TrigDrawZoneColour(nZone));
                if (pEntity->unk_90.unk_08 && pEntity->unk_90.unk_0C > 0.0f)
                {
                    // (fading out of its last zone: a line toward that zone's centre)
                    const type_8F3E0 *zOld = pEntity->unk_90.unk_08;
                    RwV3d vOld;

                    if (zOld != &dword_4E5BE0)
                    {
                        vOld.x = (zOld->unk_00[0].unk_00 + zOld->unk_00[1].unk_00) * 0.5f;
                        vOld.y = (zOld->unk_00[0].unk_04 + zOld->unk_00[1].unk_04) * 0.5f;
                        vOld.z = (zOld->unk_00[0].unk_08 + zOld->unk_00[1].unk_08) * 0.5f;
                        TrigDrawPathLine(&vTop, &vOld, (TrigDrawZoneColour(TrigDrawZoneIndex(zOld)) & 0x00FFFFFF) | 0x60000000);
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
    }
    TrigDrawPathFlush();
    if (!g_bTrigDrawZoneLabels || TrigDrawCharset() == NULL)
        return;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
    __try
    {
        for (i = 0; i < g_nTrigDrawZonesAll && i < 256; i++)
        {
            type_8F3E0 *z = dword_4B2550.get_zone(i);
            RwV3d vAt;
            RwChar sz[80];

            if (z == NULL)
                continue;
            vAt.x = (z->unk_00[0].unk_00 + z->unk_00[1].unk_00) * 0.5f;
            vAt.y = z->unk_00[1].unk_04;
            vAt.z = (z->unk_00[0].unk_08 + z->unk_00[1].unk_08) * 0.5f;
            if (g_fTrigDrawZoneRange > 0.0f && TrigDrawDist2(&vAt, pvCam) > g_fTrigDrawZoneRange * g_fTrigDrawZoneRange)
                continue;
            _snprintf(sz, sizeof(sz), "zone %d: ambient %.2f %.2f %.2f%s", i, z->unk_30.unk_00, z->unk_30.unk_04,
                      z->unk_30.unk_08, ((z->unk_8C >> 16) & 0xFF) ? ", cut by planes" : "");
            sz[sizeof(sz) - 1] = 0;
            TrigDrawText(sz, &vAt, pCamLtm, TrigDrawZoneColour(i));
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
}

// ---- the squads ----

RwBool g_bTrigDrawSquads = FALSE;
RwBool g_bTrigDrawSquadLabels = TRUE;
RwInt32 g_nTrigDrawSquads;

const RwChar *TrigDrawManeuverName(RwInt32 nKind)
{
    // (by the maneuver classes sub_3CE20 builds, types/type_3CE6D0.h and the kinds' headers)
    static const RwChar *const s_apsz[7] =
    {
        "run members", "pair at a spot", "(none)", "flag 0x80 members", "flag 0x40000 members",
        "fire and movement", "alert stand",
    };
    return nKind >= 0 && nKind < 7 ? s_apsz[nKind] : "?";
}

// Every squad: a line from each member to its leader (or, with none set, its first member) in
// the squad's colour, a ring on the leader; labelled with its id, its side, its members, the
// targets it sees and its maneuvers (the ones besides the four every squad starts with first).
static void TrigDrawSquads(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    type_3DF30 *pSquad;
    RwInt32 n = 0;

    g_nTrigDrawSquads = 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (pSquad = dword_4395F0; pSquad != NULL && n < 64; n++)
    {
        type_3DF30 *pNext = NULL;

        __try
        {
            type_3D3548 *pLeader, *pMember;
            RwV3d vLeader, vAt;
            RwUInt32 dwColour = TrigDrawZoneColour(pSquad->unk_2B4 * 5 + 3);
            RwInt32 nMembers = 0, k;
            RwChar sz[160];
            type_3CE6D0 *pMan;

            pNext = pSquad->unk_2AC;
            g_nTrigDrawSquads++;
            pLeader = pSquad->unk_2BC.sub_D4910();
            if (pLeader == NULL)
                pLeader = pSquad->unk_00;
            if (pLeader == NULL || pLeader->unk_338.unk_08 == NULL)
            {
                pSquad = pNext;
                continue;
            }
            vLeader = RwFrameGetMatrix(pLeader->unk_338.unk_08)->pos;
            vLeader.y += 70.0f;
            for (pMember = pSquad->unk_00, k = 0; pMember != NULL && k < 64; k++)
            {
                RwV3d v;

                nMembers++;
                if (pMember != pLeader && pMember->unk_338.unk_08 != NULL)
                {
                    v = RwFrameGetMatrix(pMember->unk_338.unk_08)->pos;
                    v.y += 70.0f;
                    TrigDrawPathLine(&v, &vLeader, dwColour);
                    TrigDrawCross(&v, 6.0f, dwColour);
                }
                pMember = pMember->vf_118();
            }
            // (the leader's ring: two crossed circles)
            for (k = 0; k < 16; k++)
            {
                RwReal a0 = k * 6.2831853f / 16.0f, a1 = (k + 1) * 6.2831853f / 16.0f;
                RwV3d pA = vLeader, pB = vLeader;

                pA.x += (RwReal)cos(a0) * 25.0f;
                pA.z += (RwReal)sin(a0) * 25.0f;
                pB.x += (RwReal)cos(a1) * 25.0f;
                pB.z += (RwReal)sin(a1) * 25.0f;
                TrigDrawPathLine(&pA, &pB, dwColour);
            }
            if (g_bTrigDrawSquadLabels && TrigDrawCharset() != NULL && TrigDrawDist2(&vLeader, pvCam) < 6000.0f * 6000.0f)
            {
                RwInt32 nLen;

                nLen = _snprintf(sz, sizeof(sz), "squad %d (side %d): %d member%s, %d target%s seen%s", pSquad->unk_2B4,
                                 pSquad->unk_2B0, nMembers, nMembers == 1 ? "" : "s", pSquad->unk_04.unk_04,
                                 pSquad->unk_04.unk_04 == 1 ? "" : "s",
                                 pSquad->unk_2BC.sub_D4910() ? "" : " (no leader set)");
                vAt = vLeader;
                vAt.y += 25.0f;
                TrigDrawPathFlush();
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
                sz[sizeof(sz) - 1] = 0;
                TrigDrawText(sz, &vAt, pCamLtm, dwColour);
                // (its maneuvers, by priority)
                nLen = _snprintf(sz, sizeof(sz), "maneuvers:");
                for (pMan = sub_3D3E0(pSquad->unk_2A8), k = 0; pMan != NULL && k < 8 && nLen > 0 && nLen < (RwInt32)sizeof(sz) - 24; k++)
                {
                    nLen += _snprintf(sz + nLen, sizeof(sz) - nLen, " %s,", TrigDrawManeuverName(pMan->vf_030()));
                    pMan = sub_3D3E0(pMan->unk_14);
                }
                if (nLen > 0 && sz[nLen - 1] == ',')
                    sz[nLen - 1] = 0;
                sz[sizeof(sz) - 1] = 0;
                TrigDrawText(sz, &vAt, pCamLtm, dwColour, -1.0f);
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        pSquad = pNext;
    }
    TrigDrawPathFlush();
}

// ---- the AI's hearing ----

RwBool g_bTrigDrawHearing = FALSE;
RwBool g_bTrigDrawHearRadii = FALSE;
RwBool g_bTrigDrawHearLabels = TRUE;
RwReal g_fTrigDrawHearSecs = 1.5f;
RwInt32 g_nTrigDrawHearNoises, g_nTrigDrawHeardCount;

#define TRIGDRAW_NOISES 96
#define TRIGDRAW_HEARD 128

struct TrigDrawNoise
{
    RwV3d v;
    RwReal fRange;
    RwInt32 nKind, nClass, bLasting;
    RwUInt32 dwTick;
};
static TrigDrawNoise s_aNoises[TRIGDRAW_NOISES];
static RwInt32 s_nNoiseNext;

struct TrigDrawHeard
{
    const void *pHearer;
    RwV3d vFrom;
    RwInt32 nKind;
    RwUInt32 dwTick;
};
static TrigDrawHeard s_aHeard[TRIGDRAW_HEARD];
static RwInt32 s_nHeardNext;
static RwInt32 s_nNoisesThisSecond, s_nHeardThisSecond;
static RwUInt32 s_dwHearSecond;

const RwChar *TrigDrawNoiseKindName(RwInt32 nKind)
{
    // (the kinds the game's sounds are played with: the soldiers hear 0x57 unless a script says
    // otherwise)
    switch (nKind)
    {
    case 0: return "script or blast";
    case 1: return "player";
    case 2: return "soldier";
    case 4: return "vehicle";
    case 8: return "effect";
    case 0x10: return "generator";
    case 0x20: return "ambience";
    case 0x40: return "impact";
    }
    return "?";
}

static void TrigDrawHearTick()
{
    RwUInt32 dwNow = GetTickCount();

    if (dwNow - s_dwHearSecond >= 1000)
    {
        g_nTrigDrawHearNoises = s_nNoisesThisSecond;
        g_nTrigDrawHeardCount = s_nHeardThisSecond;
        s_nNoisesThisSecond = s_nHeardThisSecond = 0;
        s_dwHearSecond = dwNow;
    }
}

// (from sub_3C4B0 and sub_3C540: a sound the AI can hear, its position copied (it may be a
// caller's local, or none for ambience))
void TrigDrawNoiseMade(const RwV3d *pv, RwInt32 nKind, RwInt32 nClass, RwReal fRange, RwInt32 bLasting)
{
    TrigDrawNoise *n;

    if (!g_bTrigDrawHearing || pv == NULL)
        return;
    TrigDrawHearTick();
    s_nNoisesThisSecond++;
    n = &s_aNoises[s_nNoiseNext];
    s_nNoiseNext = (s_nNoiseNext + 1) % TRIGDRAW_NOISES;
    n->v = *pv;
    n->fRange = fRange;
    n->nKind = nKind;
    n->nClass = nClass;
    n->bLasting = bLasting;
    n->dwTick = GetTickCount();
}

// (from sub_3C7D0, as it sends the soldier "AIAction_HearSound"; a lasting sound comes every
// frame, so the same hearer and place only refreshes its line)
void TrigDrawNoiseHeard(const void *pHearer, const RwV3d *pvFrom, RwInt32 nKind)
{
    TrigDrawHeard *h;
    RwInt32 i;
    RwUInt32 dwNow;

    if (!g_bTrigDrawHearing || pvFrom == NULL)
        return;
    TrigDrawHearTick();
    dwNow = GetTickCount();
    for (i = 0; i < TRIGDRAW_HEARD; i++)
        if (s_aHeard[i].pHearer == pHearer && s_aHeard[i].dwTick && s_aHeard[i].vFrom.x == pvFrom->x
            && s_aHeard[i].vFrom.y == pvFrom->y && s_aHeard[i].vFrom.z == pvFrom->z)
        {
            s_aHeard[i].dwTick = dwNow;
            return;
        }
    s_nHeardThisSecond++;
    h = &s_aHeard[s_nHeardNext];
    s_nHeardNext = (s_nHeardNext + 1) % TRIGDRAW_HEARD;
    h->pHearer = pHearer;
    h->vFrom = *pvFrom;
    h->nKind = nKind;
    h->dwTick = dwNow;
}

// A flat ring.
static void TrigDrawFlatRing(const RwV3d *pv, RwReal fR, RwUInt32 dwColour, RwInt32 nSteps)
{
    RwInt32 k;

    for (k = 0; k < nSteps; k++)
    {
        RwReal a0 = k * 6.2831853f / nSteps, a1 = (k + 1) * 6.2831853f / nSteps;
        RwV3d pA = *pv, pB = *pv;

        pA.x += (RwReal)cos(a0) * fR;
        pA.z += (RwReal)sin(a0) * fR;
        pB.x += (RwReal)cos(a1) * fR;
        pB.z += (RwReal)sin(a1) * fR;
        TrigDrawPathLine(&pA, &pB, dwColour);
    }
}

// The sounds (a cross, and a ring of their range: a soldier hears one within the square root of
// its range and its own radius squared), the lines to the soldiers that heard them (green), and
// with the radii each listener's own hearing ring.
static void TrigDrawHearing(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwUInt32 dwNow = GetTickCount(), dwKeep = (RwUInt32)(g_fTrigDrawHearSecs * 1000.0f);
    RwInt32 i;

    TrigDrawHearTick();
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < TRIGDRAW_NOISES; i++)
    {
        const TrigDrawNoise *n = &s_aNoises[i];
        RwUInt32 dwAge, dwAlpha, dwColour;

        if (!n->dwTick || (dwAge = dwNow - n->dwTick) > dwKeep)
            continue;
        dwAlpha = (RwUInt32)(255.0f * (1.0f - (RwReal)dwAge / (dwKeep ? dwKeep : 1)));
        dwColour = (n->nKind == 1 ? 0x0060C0FF : n->nKind == 2 ? 0x00FF6060 : 0x00FFC040) | (dwAlpha << 24);
        TrigDrawCross(&n->v, 10.0f, dwColour);
        if (n->fRange > 0.0f && n->fRange < 50000.0f)
            TrigDrawFlatRing(&n->v, n->fRange, (dwColour & 0x00FFFFFF) | ((dwAlpha / 2) << 24), 32);
    }
    for (i = 0; i < TRIGDRAW_HEARD; i++)
    {
        const TrigDrawHeard *h = &s_aHeard[i];
        RwUInt32 dwAge, dwAlpha;

        if (!h->dwTick || (dwAge = dwNow - h->dwTick) > dwKeep)
            continue;
        dwAlpha = (RwUInt32)(255.0f * (1.0f - (RwReal)dwAge / (dwKeep ? dwKeep : 1)));
        __try
        {
            const type_3D3548 *pHearer = (const type_3D3548 *)h->pHearer;
            RwV3d v;

            if (pHearer->unk_338.unk_08 == NULL)
                continue;
            v = RwFrameGetMatrix(pHearer->unk_338.unk_08)->pos;
            v.y += 160.0f;
            TrigDrawPathLine(&h->vFrom, &v, 0x0040FF60 | (dwAlpha << 24));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    if (g_bTrigDrawHearRadii)
    {
        type_3C720 *pListener;
        RwInt32 n = 0;

        __try
        {
            for (pListener = dword_43925C; pListener != NULL && n < 64; pListener = pListener->unk_08, n++)
            {
                type_3D3548 *pEntity = pListener->unk_00;
                RwV3d v;
                RwReal fR;

                if (pEntity == NULL || pEntity->unk_338.unk_08 == NULL)
                    continue;
                v = RwFrameGetMatrix(pEntity->unk_338.unk_08)->pos;
                if (TrigDrawDist2(&v, pvCam) > 8000.0f * 8000.0f)
                    continue;
                fR = pEntity->vf_130();
                if (fR > 0.0f && fR < 50000.0f)
                    TrigDrawFlatRing(&v, fR, 0x7040FF60, 32);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    TrigDrawPathFlush();
    if (!g_bTrigDrawHearLabels || TrigDrawCharset() == NULL)
        return;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
    for (i = 0; i < TRIGDRAW_NOISES; i++)
    {
        const TrigDrawNoise *n = &s_aNoises[i];
        RwUInt32 dwAge;
        RwChar sz[64];
        RwV3d vAt;

        if (!n->dwTick || (dwAge = dwNow - n->dwTick) > dwKeep)
            continue;
        if (TrigDrawDist2(&n->v, pvCam) > 5000.0f * 5000.0f)
            continue;
        _snprintf(sz, sizeof(sz), "%s sound, range %.0f%s", TrigDrawNoiseKindName(n->nKind), n->fRange,
                  n->bLasting ? ", lasting" : "");
        sz[sizeof(sz) - 1] = 0;
        vAt = n->v;
        vAt.y += 20.0f;
        TrigDrawText(sz, &vAt, pCamLtm, 0xFFFFE080);
    }
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
}

// ---- trigger activity ----

RwBool g_bTrigDrawActivity = FALSE;   // (off: nothing recorded until it is turned on)
RwBool g_bTrigDrawActiveOnly = FALSE;
RwReal g_fTrigDrawActivitySecs = 2.0f;

#define TRIGDRAW_ACT_EVENTS 128
#define TRIGDRAW_ACT_NAME   40

// The events, a ring: the handle, the kind, the message's name, when.
struct TrigDrawActEvent
{
    RwInt32 nHandle, nKind;
    RwUInt32 dwTick;
    RwChar szName[TRIGDRAW_ACT_NAME];
};
static TrigDrawActEvent s_aActEvents[TRIGDRAW_ACT_EVENTS];
static RwInt32 s_nActNext;
// (each handle's last event, for the flash: the tick and the kind)
static RwUInt32 s_adwActTick[2000];
static RwUInt8 s_abActKind[2000];

// (from sub_6B680 and sub_6B5F0 for a message a trigger sends, from sub_145060 and sub_145640
// for an entity going in and out; pTrigger checked against the trigger table)
void TrigDrawTriggerEvent(void *pTrigger, RwInt32 nKind, const RwChar *pszName)
{
    TrigDrawActEvent *e;
    RwInt32 h;

    if (pTrigger == NULL || !g_bTrigDrawActivity)
        return;
    __try
    {
        h = ((Trigger *)pTrigger)->unk_3C;
        if (h < 0 || h >= 2000 || dword_4CFE30[h] != pTrigger)
            return;
        e = &s_aActEvents[s_nActNext];
        s_nActNext = (s_nActNext + 1) % TRIGDRAW_ACT_EVENTS;
        e->nHandle = h;
        e->nKind = nKind;
        e->dwTick = GetTickCount();
        e->szName[0] = 0;
        if (pszName)
        {
            strncpy(e->szName, pszName, TRIGDRAW_ACT_NAME - 1);
            e->szName[TRIGDRAW_ACT_NAME - 1] = 0;
        }
        s_adwActTick[h] = e->dwTick ? e->dwTick : 1;
        s_abActKind[h] = (RwUInt8)nKind;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

RwBool TrigDrawActivityEvent(RwInt32 nIndex, RwInt32 *pnHandle, RwInt32 *pnKind, const RwChar **ppszName,
                             RwReal *pfAge)
{
    const TrigDrawActEvent *e;

    if (nIndex < 0 || nIndex >= TRIGDRAW_ACT_EVENTS)
        return FALSE;
    e = &s_aActEvents[(s_nActNext + TRIGDRAW_ACT_EVENTS - 1 - nIndex) % TRIGDRAW_ACT_EVENTS];
    if (e->dwTick == 0)
        return FALSE;
    *pnHandle = e->nHandle;
    *pnKind = e->nKind;
    *ppszName = e->szName;
    *pfAge = (GetTickCount() - e->dwTick) / 1000.0f;
    return TRUE;
}

void TrigDrawActivityClear()
{
    memset(s_aActEvents, 0, sizeof(s_aActEvents));
    memset(s_adwActTick, 0, sizeof(s_adwActTick));
    s_nActNext = 0;
}

// How far into its flash a trigger is (1 just fired, 0 none), and its kind's colour.
static RwReal TrigDrawActLevel(RwInt32 h, RwUInt32 *pdwColour)
{
    RwUInt32 dwKeep = (RwUInt32)(g_fTrigDrawActivitySecs * 1000.0f), dwAge;

    if (h < 0 || h >= 2000 || !s_adwActTick[h] || !dwKeep)
        return 0.0f;
    dwAge = GetTickCount() - s_adwActTick[h];
    if (dwAge >= dwKeep)
        return 0.0f;
    if (pdwColour)
        *pdwColour = s_abActKind[h] == 0 ? 0x0040FF40 : s_abActKind[h] == 1 ? 0x00FF4040 : 0x00FFFFFF;
    return 1.0f - (RwReal)dwAge / dwKeep;
}

// A trigger's colour with its flash over it.
static RwUInt32 TrigDrawActColour(Trigger *pTrigger, RwUInt32 dwBase)
{
    RwUInt32 dwFlash, r, g, b, a;
    RwReal f;

    if (!g_bTrigDrawActivity)
        return dwBase;
    f = TrigDrawActLevel(pTrigger->unk_3C, &dwFlash);
    if (f <= 0.0f)
        return dwBase;
    r = (RwUInt32)(((dwBase >> 16) & 0xFF) * (1.0f - f) + ((dwFlash >> 16) & 0xFF) * f);
    g = (RwUInt32)(((dwBase >> 8) & 0xFF) * (1.0f - f) + ((dwFlash >> 8) & 0xFF) * f);
    b = (RwUInt32)((dwBase & 0xFF) * (1.0f - f) + (dwFlash & 0xFF) * f);
    a = 0xFF;
    return (a << 24) | (r << 16) | (g << 8) | b;
}

// Whether a trigger is drawn when only the active ones are.
static RwBool TrigDrawActShown(Trigger *pTrigger)
{
    return !g_bTrigDrawActiveOnly || TrigDrawActLevel(pTrigger->unk_3C, NULL) > 0.0f;
}

// Its recent messages under its label ("> name 0.4s").
static void TrigDrawActLines(Trigger *pTrigger, const RwV3d *pvCentre, const RwMatrix *pCamLtm)
{
    RwUInt32 dwKeep = (RwUInt32)(g_fTrigDrawActivitySecs * 1000.0f), dwNow = GetTickCount();
    RwInt32 i, n = 0;

    if (!g_bTrigDrawActivity)
        return;
    for (i = 0; i < TRIGDRAW_ACT_EVENTS && n < 4; i++)
    {
        const TrigDrawActEvent *e = &s_aActEvents[(s_nActNext + TRIGDRAW_ACT_EVENTS - 1 - i) % TRIGDRAW_ACT_EVENTS];
        RwChar sz[TRIGDRAW_ACT_NAME + 24];

        if (e->dwTick == 0 || dwNow - e->dwTick > dwKeep)
            break;
        if (e->nHandle != pTrigger->unk_3C)
            continue;
        if (e->nKind == 2)
            _snprintf(sz, sizeof(sz), "> %s %.1fs", e->szName, (dwNow - e->dwTick) / 1000.0f);
        else
            _snprintf(sz, sizeof(sz), "%s %.1fs", e->nKind == 0 ? "entered" : "left", (dwNow - e->dwTick) / 1000.0f);
        sz[sizeof(sz) - 1] = 0;
        n++;
        TrigDrawText(sz, pvCentre, pCamLtm, e->nKind == 0 ? 0xFF60FF60 : e->nKind == 1 ? 0xFFFF7060 : 0xFFFFFFFF,
                     -(RwReal)n);
    }
}

// ---- splines ----

RwBool g_bTrigDrawSplines = FALSE;
RwBool g_bTrigDrawSplineLabels = TRUE;
RwReal g_fTrigDrawSplineRange = 6000.0f;
RwInt32 g_nTrigDrawSplinesShown, g_nTrigDrawSplinesAll;
extern SplinePath *dword_4CFA18[0x100];
extern RwUInt32 dword_4CFE1C;

#define TRIGDRAW_SPLINE_STEPS 64

// Every SplinePath in the level's table (its constructor adds it, the level's start clears
// it): its curve evaluated at 65 points (sub_BA990), drawn in a colour of its own, a post at
// its start and a cross at its end; labelled with its name, its index and its length.
static void TrigDrawSplines(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwInt32 i, k, n = (RwInt32)(dword_4CFE1C < 0x100 ? dword_4CFE1C : 0x100);

    g_nTrigDrawSplinesShown = 0;
    g_nTrigDrawSplinesAll = 0;
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < n; i++)
    {
        SplinePath *pPath = dword_4CFA18[i];
        RwV3d av[TRIGDRAW_SPLINE_STEPS + 1];
        RwReal fNear = 1e30f;
        RwUInt32 dwColour, h;
        RwChar szName[64];

        if (pPath == NULL)
            continue;
        __try
        {
            if (pPath->unk_28 == NULL)
                continue;
            g_nTrigDrawSplinesAll++;
            for (k = 0; k <= TRIGDRAW_SPLINE_STEPS; k++)
            {
                RwReal dx, dy, dz, d;

                pPath->sub_BA990((RwReal)k / TRIGDRAW_SPLINE_STEPS, &av[k], NULL);
                dx = av[k].x - pvCam->x;
                dy = av[k].y - pvCam->y;
                dz = av[k].z - pvCam->z;
                d = dx * dx + dy * dy + dz * dz;
                if (d < fNear)
                    fNear = d;
            }
            if (g_fTrigDrawSplineRange > 0.0f && fNear > g_fTrigDrawSplineRange * g_fTrigDrawSplineRange)
                continue;
            g_nTrigDrawSplinesShown++;
            // (a colour from its name key)
            h = (pPath->unk_2C.unk_00 * 2654435761u) ^ (pPath->unk_2C.unk_04 * 40503u) ^ (RwUInt32)i;
            dwColour = 0xE0000000 | (0x40 + (h & 0xBF)) << 16 | (0x40 + ((h >> 8) & 0xBF)) << 8 | (0x40 + ((h >> 16) & 0xBF));
            for (k = 1; k <= TRIGDRAW_SPLINE_STEPS; k++)
                TrigDrawPathLine(&av[k - 1], &av[k], dwColour);
            {
                RwV3d vPost = av[0];

                vPost.y += 60.0f;
                TrigDrawPathLine(&av[0], &vPost, dwColour);
                TrigDrawCross(&av[TRIGDRAW_SPLINE_STEPS], 15.0f, dwColour);
            }
            if (g_bTrigDrawSplineLabels && TrigDrawCharset() != NULL)
            {
                RwChar sz[96];
                RwV3d vAt = av[0];

                TrigDrawKeyText(&pPath->unk_2C, szName, sizeof(szName));
                _snprintf(sz, sizeof(sz), "spline %d %s (%.0f long%s)", i, szName, pPath->unk_24,
                          pPath->unk_1C_0 == 1 ? ", wraps" : pPath->unk_1C_0 == 2 ? ", turns back" : "");
                sz[sizeof(sz) - 1] = 0;
                vAt.y += 70.0f;
                TrigDrawPathFlush();
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
                TrigDrawText(sz, &vAt, pCamLtm, dwColour | 0xFF000000);
                RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    TrigDrawPathFlush();
}

// ---- the sounds ----

RwBool g_bTrigDrawSounds = FALSE;
RwBool g_bTrigDrawSoundLabels = TRUE;
RwBool g_bTrigDrawSoundRanges = FALSE;
RwReal g_fTrigDrawSoundRange = 6000.0f;
PortAudioVoiceInfo g_aTrigDrawSoundList[TRIGDRAW_SOUNDS];
RwInt32 g_nTrigDrawSoundList;
RwReal g_avTrigDrawListener[3];

// A ring of radius fR around pv, flat (for a voice's minimum distance).
static void TrigDrawRing(const RwV3d *pv, RwReal fR, RwUInt32 dwColour)
{
    RwInt32 i;

    for (i = 0; i < 24; i++)
    {
        RwReal a0 = i * 6.2831853f / 24.0f, a1 = (i + 1) * 6.2831853f / 24.0f;
        RwV3d vA = *pv, vB = *pv;

        vA.x += (RwReal)cos(a0) * fR;
        vA.z += (RwReal)sin(a0) * fR;
        vB.x += (RwReal)cos(a1) * fR;
        vB.z += (RwReal)sin(a1) * fR;
        TrigDrawPathLine(&vA, &vB, dwColour);
    }
}

// The audio bridge's playing voices: the snapshot for the Sounds tab's list (every frame the
// view is on), and over each 3D voice in the world a cross coloured by its volume (green loud,
// red quiet), with its lines.
static void TrigDrawSounds(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwInt32 i;

    g_nTrigDrawSoundList = port_audio_voices(g_aTrigDrawSoundList, TRIGDRAW_SOUNDS, g_avTrigDrawListener);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < g_nTrigDrawSoundList; i++)
    {
        const PortAudioVoiceInfo *v = &g_aTrigDrawSoundList[i];
        RwV3d vPos, vD;
        RwReal fDist, fLoud;
        RwUInt32 dwColour, r, g;

        if (!v->is3D || v->mode3D != 0)
            continue;
        vPos.x = v->x;
        vPos.y = v->y;
        vPos.z = v->z;
        vD.x = vPos.x - pvCam->x;
        vD.y = vPos.y - pvCam->y;
        vD.z = vPos.z - pvCam->z;
        fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z);
        if (g_fTrigDrawSoundRange > 0.0f && fDist > g_fTrigDrawSoundRange)
            continue;
        // (0 dB green, -40 dB and below red)
        fLoud = 1.0f + v->volumeDb / 40.0f;
        fLoud = fLoud < 0.0f ? 0.0f : fLoud > 1.0f ? 1.0f : fLoud;
        r = (RwUInt32)(255.0f * (1.0f - fLoud));
        g = (RwUInt32)(255.0f * fLoud);
        dwColour = 0xFF000000 | (r << 16) | (g << 8) | 0x40;
        TrigDrawCross(&vPos, 20.0f, dwColour);
        if (g_bTrigDrawSoundRanges && v->minDistance > 0.0f && v->minDistance < 5000.0f)
            TrigDrawRing(&vPos, v->minDistance, (dwColour & 0x00FFFFFF) | 0x80000000);
        if (g_bTrigDrawSoundLabels && TrigDrawCharset() != NULL)
        {
            RwChar aszLines[2][TRIGDRAW_AI_NOTE + 16];
            RwV3d vAt = vPos;

            TrigDrawPathFlush();
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
            _snprintf(aszLines[0], TRIGDRAW_AI_NOTE, "sound %.1f dB, %s%.1f s (%.0f%%)", v->volumeDb,
                      v->looping ? "looping, " : "", v->seconds, v->played * 100.0f);
            _snprintf(aszLines[1], TRIGDRAW_AI_NOTE, "%.0f away; min %.0f, max %.0f", fDist, v->minDistance,
                      v->maxDistance > 1e8f ? 0.0f : v->maxDistance);
            aszLines[0][TRIGDRAW_AI_NOTE - 1] = aszLines[1][TRIGDRAW_AI_NOTE - 1] = 0;
            vAt.y += 25.0f;
            TrigDrawLines(aszLines, 2, 0, &vAt, fDist, pCamLtm);
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
        }
    }
    TrigDrawPathFlush();
}

// ---- the projectiles ----

RwBool g_bTrigDrawProjectiles = FALSE;
RwBool g_bTrigDrawProjLabels = TRUE;
RwBool g_bTrigDrawProjTrails = TRUE;
RwReal g_fTrigDrawProjTrail = 3.0f;
RwInt32 g_anTrigDrawProjSpawned[TRIGDRAW_PROJ_KINDS];
RwInt32 g_anTrigDrawProjLive[TRIGDRAW_PROJ_KINDS];
RwInt32 g_nTrigDrawProjImpacts, g_nTrigDrawProjBlasts;

#define TRIGDRAW_PROJ_TRACKED 192
#define TRIGDRAW_PROJ_POINTS 32
#define TRIGDRAW_PROJ_EVENTS 64

// A projectile followed: its points (one a frame it moved), when it was last seen live.
struct TrigDrawProjTrack
{
    const void *pProjectile;
    RwInt32 nKind;
    RwV3d av[TRIGDRAW_PROJ_POINTS];
    RwInt32 n;
    RwUInt32 dwSeen;
    RwBool bLive;
};
static TrigDrawProjTrack s_aProjTracks[TRIGDRAW_PROJ_TRACKED];

// Where one ended: an impact (its surface) or a blast.
struct TrigDrawProjHit
{
    RwV3d v;
    RwUInt32 dwTick;
    const void *pProjectile;
    RwUInt32 dwFrame;
    RwInt32 nKind, nSurface;
    RwBool bImpact;
};
static TrigDrawProjHit s_aProjHits[TRIGDRAW_PROJ_EVENTS];
static RwInt32 s_nProjHitNext;

const RwChar *TrigDrawProjKindName(RwInt32 nKind)
{
    // (by the classes the factory builds for each pool, types/projectile.h)
    static const RwChar *const s_apsz[TRIGDRAW_PROJ_KINDS] =
    {
        "0 (base)", "1 (base)", "2 (type_3DC8B8)", "3 (with a model)", "4 (type_3DC858)", "5 (type_3DC8B8)",
        "6 (type_3DC8B8)", "7 (type_3DC738)", "8 (type_3DC6D8, a model)",
    };
    return nKind >= 0 && nKind < TRIGDRAW_PROJ_KINDS ? s_apsz[nKind] : "?";
}

static const RwUInt32 s_adwProjKind[TRIGDRAW_PROJ_KINDS] =
{
    0xFFFFFF60, 0xFFFFD040, 0xFF60FF60, 0xFFFF6060, 0xFF60C0FF, 0xFF40FFC0, 0xFFC080FF, 0xFFFF9030, 0xFFFF60C0,
};

// The kind of a projectile: the pool whose live list holds it (-1 none).
static RwInt32 TrigDrawProjKindOf(const void *pProjectile)
{
    RwInt32 k, n;

    for (k = 0; k < TRIGDRAW_PROJ_KINDS; k++)
    {
        const type_3DC7F8 *p;

        for (p = dword_4E19F8[k].unk_24, n = 0; p != NULL && n < 4096; p = p->unk_40, n++)
            if (p == pProjectile)
                return k;
    }
    return -1;
}

void TrigDrawProjectileSpawned(RwInt32 nKind, void *pProjectile)
{
    RwInt32 i;

    if (nKind >= 0 && nKind < TRIGDRAW_PROJ_KINDS)
        g_anTrigDrawProjSpawned[nKind]++;
    // (a new one where an old one was: its trail starts again)
    for (i = 0; i < TRIGDRAW_PROJ_TRACKED; i++)
        if (s_aProjTracks[i].pProjectile == pProjectile)
            s_aProjTracks[i].pProjectile = NULL;
}

static void TrigDrawProjEnd(void *pProjectile, const RwV3d *pv, RwInt32 nSurface, RwBool bImpact)
{
    TrigDrawProjHit *h;
    RwInt32 i;

    // (one a frame per projectile: a derived impact calls its base's)
    for (i = 0; i < TRIGDRAW_PROJ_EVENTS; i++)
        if (s_aProjHits[i].pProjectile == pProjectile && s_aProjHits[i].dwFrame == port_frame
            && s_aProjHits[i].bImpact == bImpact)
            return;
    if (bImpact)
        g_nTrigDrawProjImpacts++;
    else
        g_nTrigDrawProjBlasts++;
    h = &s_aProjHits[s_nProjHitNext];
    s_nProjHitNext = (s_nProjHitNext + 1) % TRIGDRAW_PROJ_EVENTS;
    h->v = *pv;
    h->dwTick = GetTickCount();
    h->dwFrame = port_frame;
    h->pProjectile = pProjectile;
    h->nKind = TrigDrawProjKindOf(pProjectile);
    h->nSurface = nSurface;
    h->bImpact = bImpact;
}

void TrigDrawProjectileImpact(void *pProjectile, RwInt32 nSurface, const RwV3d *pv, void *pEntity)
{
    (void)pEntity;
    if (pv)
        TrigDrawProjEnd(pProjectile, pv, nSurface, TRUE);
}

void TrigDrawProjectileBlast(void *pProjectile, const RwV3d *pv)
{
    if (pv)
        TrigDrawProjEnd(pProjectile, pv, -1, FALSE);
}

void TrigDrawProjReset()
{
    memset(g_anTrigDrawProjSpawned, 0, sizeof(g_anTrigDrawProjSpawned));
    g_nTrigDrawProjImpacts = g_nTrigDrawProjBlasts = 0;
    memset(s_aProjHits, 0, sizeof(s_aProjHits));
    memset(s_aProjTracks, 0, sizeof(s_aProjTracks));
}

RwInt32 TrigDrawProjEvent(RwInt32 nIndex, RwBool *pbImpact, RwInt32 *pnKind, RwInt32 *pnSurface, RwReal *pfAge,
                          RwV3d *pv)
{
    const TrigDrawProjHit *h;

    if (nIndex < 0 || nIndex >= TRIGDRAW_PROJ_EVENTS)
        return FALSE;
    h = &s_aProjHits[(s_nProjHitNext + TRIGDRAW_PROJ_EVENTS - 1 - nIndex) % TRIGDRAW_PROJ_EVENTS];
    if (h->dwTick == 0)
        return FALSE;
    *pbImpact = h->bImpact;
    *pnKind = h->nKind;
    *pnSurface = h->nSurface;
    *pfAge = (GetTickCount() - h->dwTick) / 1000.0f;
    *pv = h->v;
    return TRUE;
}

// The live projectiles (a cross each, in its kind's colour, and the trail it left), the ones
// gone a while (their trail fading), and where they hit (orange crosses, their surface id) or
// blew up (red).
static void TrigDrawProjectiles(const RwV3d *pvCam, const RwMatrix *pCamLtm)
{
    RwUInt32 dwNow = GetTickCount(), dwKeep = (RwUInt32)(g_fTrigDrawProjTrail * 1000.0f);
    RwInt32 i, k, n;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    for (i = 0; i < TRIGDRAW_PROJ_TRACKED; i++)
        s_aProjTracks[i].bLive = FALSE;
    for (k = 0; k < TRIGDRAW_PROJ_KINDS; k++)
    {
        const type_3DC7F8 *p;

        g_anTrigDrawProjLive[k] = 0;
        for (p = dword_4E19F8[k].unk_24, n = 0; p != NULL && n < 4096; p = p->unk_40, n++)
        {
            TrigDrawProjTrack *t = NULL, *pFree = NULL;

            g_anTrigDrawProjLive[k]++;
            for (i = 0; i < TRIGDRAW_PROJ_TRACKED; i++)
            {
                if (s_aProjTracks[i].pProjectile == p)
                {
                    t = &s_aProjTracks[i];
                    break;
                }
                if (pFree == NULL && (s_aProjTracks[i].pProjectile == NULL || dwNow - s_aProjTracks[i].dwSeen > dwKeep))
                    pFree = &s_aProjTracks[i];
            }
            if (t == NULL && pFree != NULL)
            {
                t = pFree;
                memset(t, 0, sizeof(*t));
                t->pProjectile = p;
                t->nKind = k;
            }
            if (t == NULL)
                continue;
            t->bLive = TRUE;
            t->dwSeen = dwNow;
            if (t->n == 0 || (t->av[t->n - 1].x - p->unk_04.x) * (t->av[t->n - 1].x - p->unk_04.x)
                                 + (t->av[t->n - 1].y - p->unk_04.y) * (t->av[t->n - 1].y - p->unk_04.y)
                                 + (t->av[t->n - 1].z - p->unk_04.z) * (t->av[t->n - 1].z - p->unk_04.z) > 1.0f)
            {
                if (t->n == TRIGDRAW_PROJ_POINTS)
                {
                    memmove(&t->av[0], &t->av[1], sizeof(RwV3d) * (TRIGDRAW_PROJ_POINTS - 1));
                    t->n--;
                }
                t->av[t->n++] = p->unk_04;
            }
        }
    }
    for (i = 0; i < TRIGDRAW_PROJ_TRACKED; i++)
    {
        TrigDrawProjTrack *t = &s_aProjTracks[i];
        RwUInt32 dwColour;

        if (t->pProjectile == NULL || t->n == 0)
            continue;
        if (!t->bLive && dwNow - t->dwSeen > dwKeep)
        {
            t->pProjectile = NULL;
            continue;
        }
        dwColour = s_adwProjKind[t->nKind];
        if (!t->bLive)
        {
            RwReal fLeft = 1.0f - (RwReal)(dwNow - t->dwSeen) / (dwKeep ? dwKeep : 1);

            dwColour = (dwColour & 0x00FFFFFF) | ((RwUInt32)(fLeft * 200.0f) << 24);
        }
        if (g_bTrigDrawProjTrails)
            for (k = 1; k < t->n; k++)
                TrigDrawPathLine(&t->av[k - 1], &t->av[k], dwColour);
        if (t->bLive)
            TrigDrawCross(&t->av[t->n - 1], 8.0f, dwColour);
    }
    for (i = 0; i < TRIGDRAW_PROJ_EVENTS; i++)
    {
        const TrigDrawProjHit *h = &s_aProjHits[i];
        RwV3d vD;
        RwReal fDist;

        if (h->dwTick == 0 || dwNow - h->dwTick > dwKeep)
            continue;
        TrigDrawCross(&h->v, h->bImpact ? 14.0f : 40.0f, h->bImpact ? 0xFFFF9020 : 0xFFFF3030);
        if (!g_bTrigDrawProjLabels || TrigDrawCharset() == NULL)
            continue;
        vD.x = h->v.x - pvCam->x;
        vD.y = h->v.y - pvCam->y;
        vD.z = h->v.z - pvCam->z;
        fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z);
        {
            RwChar aszLines[1][TRIGDRAW_AI_NOTE + 16];
            RwV3d vAt = h->v;

            TrigDrawPathFlush();
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
            if (h->bImpact)
                _snprintf(aszLines[0], TRIGDRAW_AI_NOTE, "hit surface %d (kind %d)", h->nSurface, h->nKind);
            else
                _snprintf(aszLines[0], TRIGDRAW_AI_NOTE, "blast (kind %d)", h->nKind);
            aszLines[0][TRIGDRAW_AI_NOTE - 1] = 0;
            vAt.y += 15.0f;
            TrigDrawLines(aszLines, 1, 0, &vAt, fDist, pCamLtm);
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
        }
    }
    TrigDrawPathFlush();
}

void TrigDrawAll(RwCamera *pCamera)
{
    void *pRaster;
    RwInt32 nZTest, nZWrite, nAlpha, nSrc, nDest, nCull;
    RwV3d vCam;
    RwMatrix *pCamLtm;
    Trigger *pTrigger;
    RwInt32 i;

    static RwInt32 s_nStart = -1;

    if (s_nStart < 0)
    {
        RwChar szValue[8];

        s_nStart = GetEnvironmentVariableA("CODFH_TRIGGERS", szValue, sizeof(szValue)) ? atoi(szValue) : 0;
        if (s_nStart >= 1)
            g_bTrigDrawEnabled = TRUE;
        if (s_nStart >= 2)
            g_bTrigDrawCollision = TRUE;
        // (CODFH_AI=1: the AI's state and notes; 2 with its cover and fighting)
        if (GetEnvironmentVariableA("CODFH_AI", szValue, sizeof(szValue)))
        {
            g_bTrigDrawAi = TRUE;
            if (atoi(szValue) >= 2)
                g_bTrigDrawAiCover = g_bTrigDrawAiCombat = TRUE;
        }
        // (CODFH_PG=1: the projectile generators)
        if (GetEnvironmentVariableA("CODFH_PG", NULL, 0))
            g_bTrigDrawPg = TRUE;
        // (CODFH_PATHNODES=1: the path nodes, with their labels)
        if (GetEnvironmentVariableA("CODFH_PATHNODES", NULL, 0))
            g_bTrigDrawPathNodes = g_bTrigDrawPathLabels = TRUE;
        // (CODFH_GIMPS=1, CODFH_SHRIMPS=1: the gimps, the shrimps)
        if (GetEnvironmentVariableA("CODFH_GIMPS", NULL, 0))
            g_bTrigDrawGimps = TRUE;
        if (GetEnvironmentVariableA("CODFH_SHRIMPS", NULL, 0))
            g_bTrigDrawShrimps = TRUE;
        // (CODFH_SOUNDS=1, CODFH_PROJECTILES=1: the sounds playing, the projectiles)
        if (GetEnvironmentVariableA("CODFH_SOUNDS", NULL, 0))
            g_bTrigDrawSounds = TRUE;
        if (GetEnvironmentVariableA("CODFH_PROJECTILES", NULL, 0))
            g_bTrigDrawProjectiles = TRUE;
        // (CODFH_RAYS=1, CODFH_HITS=1 (with the bone boxes), CODFH_LIGHTS=1, CODFH_SPLINES=1)
        if (GetEnvironmentVariableA("CODFH_RAYS", NULL, 0))
            g_bTrigDrawRays = TRUE;
        if (GetEnvironmentVariableA("CODFH_HITS", NULL, 0))
            g_bTrigDrawHits = g_bTrigDrawHitBoxes = TRUE;
        if (GetEnvironmentVariableA("CODFH_LIGHTS", NULL, 0))
            g_bTrigDrawLights = TRUE;
        if (GetEnvironmentVariableA("CODFH_SPLINES", NULL, 0))
            g_bTrigDrawSplines = TRUE;
        // (CODFH_ZONES=1, CODFH_SQUADS=1)
        if (GetEnvironmentVariableA("CODFH_ZONES", NULL, 0))
            g_bTrigDrawZones = TRUE;
        if (GetEnvironmentVariableA("CODFH_SQUADS", NULL, 0))
            g_bTrigDrawSquads = TRUE;
        if (GetEnvironmentVariableA("CODFH_HEARING", NULL, 0))
            g_bTrigDrawHearing = g_bTrigDrawHearRadii = TRUE;
    }
    if ((!g_bTrigDrawEnabled && !g_bTrigDrawCollision && !g_bTrigDrawPathNodes && !g_bTrigDrawAi && !g_bTrigDrawPg &&
         !g_bTrigDrawGimps && !g_bTrigDrawShrimps && !g_bTrigDrawSounds && !g_bTrigDrawProjectiles &&
         !g_bTrigDrawSplines && !g_bTrigDrawRays && !g_bTrigDrawHits && !g_bTrigDrawHitBoxes && !g_bTrigDrawLights &&
         !g_bTrigDrawZones && !g_bTrigDrawSquads && !g_bTrigDrawHearing) ||
        pCamera == NULL)
        return;
    pCamLtm = RwFrameGetLTM(RwCameraGetFrame(pCamera));
    vCam = pCamLtm->pos;

    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, (void *)&pRaster);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, (void *)&nZTest);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, (void *)&nZWrite);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)&nAlpha);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, (void *)&nSrc);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, (void *)&nDest);
    RwRenderStateGet(rwRENDERSTATECULLMODE, (void *)&nCull);

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)NULL);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);

    // the collision, depth-tested so walls hide what is behind them
    if (g_bTrigDrawCollision)
    {
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)TRUE);
        TrigDrawCollision(&vCam);
    }
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)(g_bTrigDrawSeeThrough ? FALSE : TRUE));
    if (g_bTrigDrawPathNodes)
        TrigDrawPaths(&vCam, pCamLtm);
    if (g_bTrigDrawAi)
        TrigDrawAi(&vCam, pCamLtm);
    if (g_bTrigDrawPg)
        TrigDrawPg(&vCam, pCamLtm);
    if (g_bTrigDrawGimps)
        TrigDrawGimps(&vCam, pCamLtm);
    if (g_bTrigDrawShrimps)
        TrigDrawShrimps(&vCam);
    if (g_bTrigDrawSplines)
        TrigDrawSplines(&vCam, pCamLtm);
    if (g_bTrigDrawRays)
        TrigDrawRays();
    if (g_bTrigDrawHitBoxes)
        TrigDrawHitBoxesAll(&vCam);
    if (g_bTrigDrawHits)
        TrigDrawHits(&vCam, pCamLtm);
    if (g_bTrigDrawLights)
        TrigDrawLights(&vCam, pCamLtm);
    if (g_bTrigDrawZones)
        TrigDrawZones(&vCam, pCamLtm);
    if (g_bTrigDrawSquads)
        TrigDrawSquads(&vCam, pCamLtm);
    if (g_bTrigDrawHearing)
        TrigDrawHearing(&vCam, pCamLtm);
    if (g_bTrigDrawSounds)
        TrigDrawSounds(&vCam, pCamLtm);
    if (g_bTrigDrawProjectiles)
        TrigDrawProjectiles(&vCam, pCamLtm);
    if (!g_bTrigDrawEnabled)
        i = dword_429D00 + 1;
    else
        i = 0;

    for (; i <= dword_429D00 && i < 2000; i++)
    {
        pTrigger = (Trigger *)dword_4CFE30[i];
        if (pTrigger != NULL && TrigDrawInRange(pTrigger, &vCam) && TrigDrawActShown(pTrigger))
            TrigDrawOne(pTrigger);
    }
    if (g_bTrigDrawEnabled && g_bTrigDrawLabels && TrigDrawCharset() != NULL)
    {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
        for (i = 0; i <= dword_429D00 && i < 2000; i++)
        {
            pTrigger = (Trigger *)dword_4CFE30[i];
            if (pTrigger != NULL && TrigDrawInRange(pTrigger, &vCam) && TrigDrawActShown(pTrigger))
                TrigDrawLabel(pTrigger, pCamLtm, 0xFF000000 | TrigDrawColour(pTrigger));
        }
    }

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, pRaster);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)nZTest);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)nZWrite);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)nAlpha);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)nSrc);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)nDest);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)nCull);
}

// ---- the live link's debug feed (trigweb.cpp, the web suite's level viewer) ----
// What the View list's AI, projectile generator and path node drawing reads, as JSON for the
// viewer to draw with labels: every AI's whole state (TrigDrawAiRead) with its notes, every
// projectile generator's (TrigDrawPgRead) with its notes, and the path node graph (all of it
// once, then the nodes whose flags or blocked links changed). While a viewer takes the feed,
// the notes are kept as when the overlay draws the AI (g_bTrigLiveDebug).
RwBool g_bTrigLiveDebug = FALSE;

struct TrigLiveJson
{
    RwChar *psz;
    RwInt32 n, nMax;
};

static void LiveJ(TrigLiveJson *j, const RwChar *pszFormat, ...)
{
    va_list va;
    RwInt32 n;

    if (j->n >= j->nMax - 1)
        return;
    va_start(va, pszFormat);
    n = _vsnprintf(j->psz + j->n, j->nMax - 1 - j->n, pszFormat, va);
    va_end(va);
    if (n < 0)
        j->n = j->nMax - 1;
    else
        j->n += n;
    j->psz[j->n] = 0;
}

static void LiveJV(TrigLiveJson *j, const RwChar *pszKey, const RwV3d *pv)
{
    LiveJ(j, ",\"%s\":[%.1f,%.1f,%.1f]", pszKey, pv->x, pv->y, pv->z);
}

static void LiveJText(TrigLiveJson *j, const RwChar *pszIn)
{
    LiveJ(j, "\"");
    for (; *pszIn && j->n < j->nMax - 8; pszIn++)
    {
        RwUInt8 c = (RwUInt8)*pszIn;

        if (c == '"' || c == '\\')
            LiveJ(j, "\\%c", c);
        else if (c < 0x20 || c > 0x7E)
            LiveJ(j, " ");
        else
            LiveJ(j, "%c", c);
    }
    LiveJ(j, "\"");
}

// The notes kept under pKey, newest first: [age in seconds, repeats, text].
static void LiveJNotes(TrigLiveJson *j, TrigDrawAiNotes *pAll, RwInt32 nAll, const void *pKey)
{
    TrigDrawAiNotes *pNotes = NULL;
    RwInt32 i, k, nShown = 0;

    for (i = 0; i < nAll; i++)
        if (pAll[i].pEntity == pKey)
        {
            pNotes = &pAll[i];
            break;
        }
    LiveJ(j, ",\"notes\":[");
    for (k = 0; pNotes && k < TRIGDRAW_AI_NOTES; k++)
    {
        RwInt32 n = (pNotes->nNext + TRIGDRAW_AI_NOTES - 1 - k) % TRIGDRAW_AI_NOTES;

        if (!pNotes->adwFrame[n])
            continue;
        LiveJ(j, "%s[%.1f,%d,", nShown++ ? "," : "", (RwReal)(port_frame - pNotes->adwFrame[n]) / 60.0f, pNotes->anRepeats[n]);
        LiveJText(j, pNotes->aszText[n]);
        LiveJ(j, "]");
    }
    LiveJ(j, "]");
}

// Every AI: {"t":"ai","frame":n,"list":[...]}.
RwBool TrigDrawLiveAiJson(RwChar *psz, RwInt32 nMax)
{
    static TrigDrawAiState s_state;
    TrigLiveJson j = { psz, 0, nMax };
    RwInt32 i, k, nShown = 0;

    LiveJ(&j, "{\"t\":\"ai\",\"frame\":%u,\"list\":[", port_frame);
    TrigDrawAiMachines();
    for (i = 0; i < 768 && j.n < nMax - 4096; i++)
    {
        type_3D3548 *pEntity = dword_4B6A00[i].unk_04;
        TrigDrawAiState *s = &s_state;
        RwUInt32 dwBits;

        if (pEntity == NULL)
            continue;
        dwBits = pEntity->unk_2C;
        if ((dwBits & 0x10) || !TrigDrawAiRead(pEntity, dwBits, s))
            continue;
        LiveJ(&j, "%s{\"slot\":%d,\"soldier\":%d,\"hp\":%d,\"state\":%d,\"alert\":%d,\"bits\":%u", nShown++ ? "," : "", i,
              (dwBits & 0x20) ? 1 : 0, s->nHp, s->nState, s->nAlert, dwBits);
        LiveJV(&j, "pos", &s->vPos);
        if (s->bTarget)
        {
            LiveJ(&j, ",\"target\":%d", s->nTargetSlot);
            LiveJV(&j, "targetPos", &s->vTarget);
        }
        if (s->bPoint)
            LiveJV(&j, "point", &s->vPoint);
        if (s->bAim)
        {
            LiveJV(&j, "aimFrom", &s->vAimFrom);
            LiveJV(&j, "aim", &s->vAim);
        }
        LiveJ(&j, ",\"node\":%d,\"nodeType\":%d,\"next\":%d,\"nextType\":%d", s->nNodeId, s->nNodeType, s->nNextId, s->nNextType);
        if (s->bNode)
            LiveJV(&j, "nodePos", &s->vNode);
        if (s->bTask)
        {
            LiveJ(&j, ",\"task\":{\"script\":%d,\"function\":%d,\"line\":%d,\"waits\":%d,\"file\":", s->nTaskScript,
                  s->nTaskFunction, s->nTaskLine, s->nTaskWaits);
            LiveJText(&j, s->szTaskFile);
            LiveJ(&j, "}");
        }
        if (s->bMachine)
        {
            LiveJ(&j, ",\"machine\":{\"line\":%d,\"state\":%d,\"file\":", s->nMachineLine, s->nMachineState);
            LiveJText(&j, s->szMachineFile);
            LiveJ(&j, "}");
        }
        if (s->bPathSearch)
            LiveJ(&j, ",\"search\":{\"kind\":%d,\"result\":%d,\"length\":%d,\"start\":%d,\"goal\":%d,\"goalType\":%d,\"left\":%d}",
                  s->nSearchKind, s->nSearchResult, s->nSearchLength, s->nStartNode, s->nGoalNode, s->nGoalType, s->nLeft);
        if (s->bGoal)
            LiveJV(&j, "goal", &s->vGoal);
        if (s->nPath > 0)
        {
            LiveJ(&j, ",\"path\":[");
            for (k = 0; k < s->nPath; k++)
                LiveJ(&j, "%s[%.1f,%.1f,%.1f]", k ? "," : "", s->avPath[k].x, s->avPath[k].y, s->avPath[k].z);
            LiveJ(&j, "]");
        }
        LiveJ(&j, ",\"cover\":{\"radius\":%.1f,\"found\":%d,\"tried\":%d,\"candidates\":[", s->fCoverRadius, s->nCandidates, s->nTried);
        for (k = 0; k < s->nCandidates; k++)
            LiveJ(&j, "%s[%.1f,%.1f,%.1f,%d]", k ? "," : "", s->avCandidate[k].x, s->avCandidate[k].y, s->avCandidate[k].z,
                  s->abTried[k] ? 1 : 0);
        LiveJ(&j, "],\"nodes\":[");
        for (k = 0; k < 3; k++)
            if (s->abCoverNode[k])
                LiveJ(&j, "%s[%.1f,%.1f,%.1f,%d]", k ? "," : "", s->avCoverNode[k].x, s->avCoverNode[k].y, s->avCoverNode[k].z, k);
            else
                LiveJ(&j, "%snull", k ? "," : "");
        LiveJ(&j, "],\"points\":[");
        for (k = 0; k < s->nCoverPoints; k++)
            LiveJ(&j, "%s[%.1f,%.1f,%.1f]", k ? "," : "", s->avCoverPoint[k].x, s->avCoverPoint[k].y, s->avCoverPoint[k].z);
        LiveJ(&j, "]},\"combat\":{\"tracked\":%.2f,\"blocker\":%.1f,\"fighting\":%.2f,\"notFighting\":%.2f,\"hearClasses\":%d,"
                  "\"hearKinds\":%d,\"hearSides\":%d,\"mayLoseSight\":%d,\"control\":%d,\"burstLeft\":%d",
              s->fTracked / 60.0f, s->fBlocker < 1e30f ? s->fBlocker : -1.0f, s->fIn / 60.0f, s->fOut / 60.0f, s->nHearClasses,
              s->nHearKinds, s->nHearSides, s->nLosLoss, s->nControl, s->nShots);
        if (s->bSeen)
            LiveJV(&j, "seen", &s->vSeen);
        LiveJ(&j, "}");
        if (s->bWeapon)
        {
            LiveJ(&j, ",\"weapon\":{\"type\":%d,\"ammo\":%d,\"infinite\":%d,\"nextShot\":%.2f,\"noTarget\":%d,\"aims\":%d",
                  s->nWeaponType, s->nAmmo, s->nInfinite, s->fNextShot, s->nNoTarget, s->nAimsWeapon);
            if (s->nAimsWeapon)
                LiveJV(&j, "aim", &s->vWeaponAim);
            LiveJ(&j, "}");
        }
        while (InterlockedExchange(&s_nAiNotesLock, 1))
            ;
        LiveJNotes(&j, s_aAiNotes, TRIGDRAW_AI_ENTITIES, pEntity);
        InterlockedExchange(&s_nAiNotesLock, 0);
        LiveJ(&j, "}");
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

// Every projectile generator: {"t":"pg","frame":n,"list":[...]}.
RwBool TrigDrawLivePgJson(RwChar *psz, RwInt32 nMax)
{
    static TrigDrawPgState s_state;
    TrigLiveJson j = { psz, 0, nMax };
    type_1227C0 *pGen;
    RwInt32 n = 0;

    LiveJ(&j, "{\"t\":\"pg\",\"frame\":%u,\"list\":[", port_frame);
    for (pGen = dword_4CE8F8; pGen != NULL && n < 512 && j.n < nMax - 2048; n++)
    {
        TrigDrawPgState *p = &s_state;
        type_1227C0 *pNext;

        if (!TrigDrawPgRead(pGen, p))
            break;
        pNext = pGen->unk_100;
        // (the overlay notes them when it draws them)
        if (!g_bTrigDrawPg)
            TrigDrawPgNotes(pGen, p);
        LiveJ(&j, "%s{\"id\":%d,\"shells\":%d,\"state\":%d,\"forced\":%d,\"turning\":%d,\"stagesOn\":%d,\"stage\":%d,\"targetKind\":%d,"
                  "\"stageShots\":%d,\"shots\":%d,\"bursts\":%d,\"los\":%d,\"replays\":%d,\"next\":%.2f,\"spread\":%.1f,\"height\":%.1f,"
                  "\"pathAt\":%.2f,\"pathSpeed\":%.2f,\"wait\":%.2f,\"waitLeft\":%.2f,\"replay\":%.2f,\"speed\":%.1f",
              n ? "," : "", p->nId, p->nKind, p->nState, p->nForced, p->nTurning, p->nStagesOn, p->nStage, p->nTargetKind,
              p->nStageShots, p->nShots, p->nBursts, p->nLos, p->nReplays, p->fNext, p->fSpread, p->fHeight, p->fPathAt,
              p->fPathSpeed, p->fWait, p->fWaitLeft, p->fReplay, p->fSpeed);
        LiveJV(&j, "pos", &p->vPos);
        LiveJV(&j, "at", &p->vAt);
        LiveJV(&j, "aim", &p->vAim);
        LiveJV(&j, "lastAim", &p->vLastAim);
        LiveJV(&j, "facing", &p->vFacing);
        if (p->bTarget)
            LiveJV(&j, "target", &p->vTarget);
        if (p->bTrigger)
            LiveJV(&j, "trigger", &p->vTrigger);
        LiveJNotes(&j, s_aPgNotes, TRIGDRAW_PG_NOTED, pGen);
        LiveJ(&j, "}");
        pGen = pNext;
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

// The gimps and their spawners: {"t":"gimps","frame":n,"list":[...],"spawners":[...]}, each
// gimp as its label draws it (TrigDrawGimpRead) with its notes, each GimpTrigger with its
// spawn counts.
RwBool TrigDrawLiveGimpsJson(RwChar *psz, RwInt32 nMax)
{
    static TrigDrawGimpState s_state;
    TrigLiveJson j = { psz, 0, nMax };
    RwInt32 i, k, nShown = 0, nMark;

    LiveJ(&j, "{\"t\":\"gimps\",\"frame\":%u,\"list\":[", port_frame);
    TrigDrawAiMachines();
    for (i = 0; i < 768 && j.n < nMax - 2048; i++)
    {
        type_3D3548 *pEntity = dword_4B6A00[i].unk_04;
        TrigDrawGimpState *s = &s_state;

        if (pEntity == NULL || (pEntity->unk_2C & 0x3FFFFF0) != 0x200000)
            continue;
        if (!TrigDrawGimpRead((type_3DDB98 *)pEntity, s))
            continue;
        LiveJ(&j, "%s{\"slot\":%d,\"hp\":%d,\"hpMax\":%d,\"attitude\":%d,\"riding\":%d,\"headShot\":%d,\"trigger\":%d,"
                  "\"flags\":%u,\"ground\":%d", nShown++ ? "," : "", i, s->nHp, s->nHpMax, s->nAttitude, s->bRiding ? 1 : 0,
              s->nHeadShot, s->nTrigger, s->dwFlags, s->nGround);
        LiveJV(&j, "pos", &s->vPos);
        LiveJ(&j, ",\"name\":");
        LiveJText(&j, s->szName);
        LiveJ(&j, ",\"def\":");
        LiveJText(&j, s->szDef);
        LiveJ(&j, ",\"hat\":");
        LiveJText(&j, s->szHat);
        LiveJ(&j, ",\"scriptNames\":[");
        LiveJText(&j, s->szScripts[0]);
        LiveJ(&j, ",");
        LiveJText(&j, s->szScripts[1]);
        LiveJ(&j, "]");
        if (s->bSpline)
        {
            LiveJ(&j, ",\"spline\":{\"along\":%.1f,\"end\":%.1f,\"speed\":%.2f,\"length\":%.1f,\"endMode\":%d,\"name\":",
                  s->fAlong, s->fEnd, s->fSpeed, s->fPathLength, s->nEndMode);
            LiveJText(&j, s->szPath);
            LiveJV(&j, "point", &s->vPoint);
            LiveJ(&j, "}");
        }
        LiveJ(&j, ",\"scripts\":[");
        for (k = 0; k < s->nMachines; k++)
        {
            if (k)
                LiveJ(&j, ",");
            LiveJText(&j, s->aszMachine[k]);
        }
        LiveJ(&j, "]");
        LiveJNotes(&j, s_aAiNotes, TRIGDRAW_AI_ENTITIES, pEntity);
        LiveJ(&j, "}");
    }
    LiveJ(&j, "],\"spawners\":[");
    nShown = 0;
    for (i = 0; i <= dword_429D00 && i < 2000 && j.n < nMax - 1024; i++)
    {
        Trigger *pTrigger = (Trigger *)dword_4CFE30[i];
        const RwChar *pszName;

        if (pTrigger == NULL || pTrigger->vf_008() != 0x1F)
            continue;
        nMark = j.n;
        __try
        {
            GimpTrigger *pGimps = (GimpTrigger *)pTrigger;

            LiveJ(&j, "%s{\"trigger\":%d,\"left\":%d,\"limit\":%d,\"liveOnce\":%d,\"health\":%.0f,\"pos\":[%.1f,%.1f,%.1f]",
                  nShown++ ? "," : "", i, pGimps->unk_14C, pGimps->unk_148 == 0x7FFFFFFF ? -1 : pGimps->unk_148,
                  pGimps->unk_140 ? 1 : 0, pGimps->unk_120_r, pTrigger->unk_90, pTrigger->unk_94, pTrigger->unk_98);
            pszName = TrigDrawTriggerName(pTrigger);
            if (pszName)
            {
                LiveJ(&j, ",\"name\":");
                LiveJText(&j, pszName);
            }
            {
                RwChar sz[48];

                TrigDrawKeyText(&pGimps->unk_D8, sz, sizeof(sz));
                LiveJ(&j, ",\"gimp\":");
                LiveJText(&j, sz);
                TrigDrawKeyText(&pGimps->unk_C0, sz, sizeof(sz));
                LiveJ(&j, ",\"def\":");
                LiveJText(&j, sz);
                TrigDrawKeyText(&pGimps->unk_E8, sz, sizeof(sz));
                LiveJ(&j, ",\"weapon\":");
                LiveJText(&j, sz);
                TrigDrawKeyText(&pGimps->unk_C8, sz, sizeof(sz));
                LiveJ(&j, ",\"script\":");
                LiveJText(&j, sz);
            }
            LiveJ(&j, "}");
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            j.n = nMark;
            psz[j.n] = 0;
            if (j.n && psz[j.n - 1] == '[')
                nShown = 0;
        }
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

// The shrimp triggers: {"t":"shrimps","frame":n,"list":[...]}, each with its counts, its path
// (49 points along its spline) and its shrimps ([x,y,z,forward]).
RwBool TrigDrawLiveShrimpsJson(RwChar *psz, RwInt32 nMax)
{
    TrigLiveJson j = { psz, 0, nMax };
    RwInt32 i, k, nShown = 0, nMark;

    LiveJ(&j, "{\"t\":\"shrimps\",\"frame\":%u,\"list\":[", port_frame);
    for (i = 0; i <= dword_429D00 && i < 2000 && j.n < nMax - 8192; i++)
    {
        Trigger *pTrigger = (Trigger *)dword_4CFE30[i];
        const RwChar *pszName;

        if (pTrigger == NULL || pTrigger->vf_008() != 0x21)
            continue;
        nMark = j.n;
        __try
        {
            ShrimpTrigger *pShrimps = (ShrimpTrigger *)pTrigger;
            SplinePath *pPath = pShrimps->unk_EC.unk_0C;
            type_17CA70_node *pNode;
            RwInt32 nAlive = 0;
            RwV3d v;

            for (pNode = pShrimps->unk_EC.unk_14; pNode != NULL && nAlive < 256; pNode = pNode->unk_0C)
                nAlive++;
            LiveJ(&j, "%s{\"trigger\":%d,\"alive\":%d,\"left\":%d,\"limit\":%d,\"chance\":%.0f,\"speed\":%.3f,\"pos\":[%.1f,%.1f,%.1f]",
                  nShown++ ? "," : "", i, nAlive, pShrimps->unk_E4, pShrimps->unk_E0 == 0x7FFFFFFF ? -1 : pShrimps->unk_E0,
                  pShrimps->unk_DC, pShrimps->unk_D0_r, pTrigger->unk_90, pTrigger->unk_94, pTrigger->unk_98);
            pszName = TrigDrawTriggerName(pTrigger);
            if (pszName)
            {
                LiveJ(&j, ",\"name\":");
                LiveJText(&j, pszName);
            }
            {
                RwChar sz[48];

                TrigDrawKeyText(&pShrimps->unk_C0, sz, sizeof(sz));
                LiveJ(&j, ",\"model\":");
                LiveJText(&j, sz);
                if (pPath)
                {
                    TrigDrawKeyText(&pPath->unk_2C, sz, sizeof(sz));
                    LiveJ(&j, ",\"pathName\":");
                    LiveJText(&j, sz);
                    LiveJ(&j, ",\"length\":%.1f,\"endMode\":%d", pPath->unk_24, (RwInt32)pPath->unk_1C_0);
                }
            }
            if (pPath)
            {
                LiveJ(&j, ",\"path\":[");
                for (k = 0; k <= 48; k++)
                {
                    pPath->sub_BA990((RwReal)k / 48.0f, &v, NULL);
                    LiveJ(&j, "%s[%.1f,%.1f,%.1f]", k ? "," : "", v.x, v.y, v.z);
                }
                LiveJ(&j, "],\"shrimps\":[");
                for (pNode = pShrimps->unk_EC.unk_14, k = 0; pNode != NULL && k < 256; pNode = pNode->unk_0C, k++)
                {
                    pPath->sub_BA990(pNode->unk_00, &v, NULL);
                    LiveJ(&j, "%s[%.1f,%.1f,%.1f,%d]", k ? "," : "", v.x, v.y, v.z, pNode->unk_04 >= 0.0f ? 1 : 0);
                }
                LiveJ(&j, "]");
            }
            LiveJ(&j, "}");
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            // (a half-written entry: dropped)
            j.n = nMark;
            psz[j.n] = 0;
            if (j.n && psz[j.n - 1] == '[')
                nShown = 0;
        }
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

// The path node graph: bFull every node, {"id","type","flags","pos","links":[[to,blocked],...]},
// else only the nodes whose flags or links' blocked bits changed since the last call.
static RwUInt32 s_adwLiveNodeHash[4096];

RwBool TrigDrawLiveNodesJson(RwChar *psz, RwInt32 nMax, RwBool bFull)
{
    TrigLiveJson j = { psz, 0, nMax };
    RwInt32 nId, nCount, nShown = 0, i, k;

    LiveJ(&j, "{\"t\":\"nodes\",\"frame\":%u,\"full\":%d,\"list\":[", port_frame, bFull ? 1 : 0);
    __try
    {
        nCount = unk_4C00E8.unk_64 && unk_4C00E8.unk_2C ? unk_4C00E8.unk_08 : 0;
        if (nCount > 4096)
            nCount = 4096;
        for (nId = 1; nId < nCount && j.n < nMax - 2048; nId++)
        {
            type_F8350 *pNode = TrigDrawPathNode(nId);
            const RwUInt32 *p;
            RwUInt32 dwHash;

            if (pNode == NULL)
                continue;
            // (the flags and the links' blocked bits, folded, to tell a change)
            dwHash = pNode->unk_00 * 2654435761u;
            p = TrigDrawPathLinks(pNode);
            for (i = 0; i < 64 && (p[i] & 0xFFF); i++)
                dwHash = (dwHash ^ (p[i] >> 24)) * 16777619u + (RwUInt32)i;
            if (!bFull && dwHash == s_adwLiveNodeHash[nId])
                continue;
            s_adwLiveNodeHash[nId] = dwHash;
            LiveJ(&j, "%s{\"id\":%d,\"type\":%d,\"flags\":%u", nShown++ ? "," : "", nId, pNode->unk_04, pNode->unk_00);
            LiveJV(&j, "pos", &pNode->unk_10);
            LiveJ(&j, ",\"links\":[");
            for (i = 0, k = 0; i < 64; i++)
            {
                RwInt32 h, nTo;

                for (h = 0; h < 2; h++)
                {
                    nTo = (RwInt32)((p[i] >> (h * 12)) & 0xFFF);
                    if (nTo == 0)
                        break;
                    LiveJ(&j, "%s[%d,%d]", k++ ? "," : "", nTo, (RwInt32)((p[i] >> (24 + h)) & 1));
                }
                if (h < 2)
                    break;
            }
            LiveJ(&j, "]}");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

// The full AI view (the level viewer's): every field of one AI's AIData and of its entity's
// classes (type_3D3548, and a soldier's type_3D32F8 and type_3DAFC8), from the tables
// tools/gen_aifields.py makes from the headers. The tables go once, as {"t":"aifields"}: each
// class's name, size and rows [path, offset, kind, count, size, comment, bits/values or type,
// readable name]; the
// values as the memory itself, {"t":"aifull"}: each class's block as hex, for the page to
// decode by the table.
enum { AF_INT, AF_UINT, AF_REAL, AF_INTREAL, AF_I16, AF_U16, AF_I8, AF_U8, AF_V3D, AF_V2D, AF_RGBA, AF_MATRIX, AF_HANDLE,
       AF_KEY, AF_PTR, AF_GROUP, AF_RAW };
static const RwChar *const s_apszAiKinds[] = { "int", "uint", "real", "intreal", "i16", "u16", "i8", "u8", "v3d", "v2d",
                                               "rgba", "matrix", "handle", "key", "ptr", "group", "raw" };

struct AiField
{
    const RwChar *pszPath;
    RwUInt32 dwOffset;
    RwUInt16 nKind;
    RwUInt16 nCount;
    RwUInt32 dwSize;
    const RwChar *pszDesc;
    const RwChar *pszExtra;     // the bits or values (AF_UINT, AF_INT), or the type (AF_GROUP, AF_RAW)
    const RwChar *pszLabel;     // the traced readable name (tools/aifields_desc.json), or ""
};

struct AiFieldClass
{
    const RwChar *pszName;
    const AiField *pFields;
    RwInt32 nFields;
    RwUInt32 dwSize;
};

#include "aifields.inc"

RwBool TrigDrawLiveAiFieldsJson(RwChar *psz, RwInt32 nMax)
{
    TrigLiveJson j = { psz, 0, nMax };
    RwInt32 c, i;

    LiveJ(&j, "{\"t\":\"aifields\",\"classes\":[");
    for (c = 0; c < (RwInt32)(sizeof(s_aAiFieldClasses) / sizeof(s_aAiFieldClasses[0])); c++)
    {
        const AiFieldClass *pClass = &s_aAiFieldClasses[c];

        LiveJ(&j, "%s{\"name\":\"%s\",\"size\":%u,\"fields\":[", c ? "," : "", pClass->pszName, pClass->dwSize);
        for (i = 0; i < pClass->nFields; i++)
        {
            const AiField *f = &pClass->pFields[i];

            LiveJ(&j, "%s[", i ? "," : "");
            LiveJText(&j, f->pszPath);
            LiveJ(&j, ",%u,\"%s\",%u,%u,", f->dwOffset, s_apszAiKinds[f->nKind], f->nCount, f->dwSize);
            LiveJText(&j, f->pszDesc);
            LiveJ(&j, ",");
            LiveJText(&j, f->pszExtra);
            LiveJ(&j, ",");
            LiveJText(&j, f->pszLabel);
            LiveJ(&j, "]");
        }
        LiveJ(&j, "]}");
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

// Copies n bytes from p, word by word where a page faults (those words 0xCDCDCDCD); FALSE when
// none of it could be read.
static RwBool LiveCopy(RwUInt8 *pOut, const RwUInt8 *p, RwUInt32 n)
{
    RwUInt32 i, nRead = 0;

    __try
    {
        memcpy(pOut, p, n);
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    for (i = 0; i + 4 <= n; i += 4)
    {
        __try
        {
            *(RwUInt32 *)(pOut + i) = *(const RwUInt32 *)(p + i);
            nRead++;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            *(RwUInt32 *)(pOut + i) = 0xCDCDCDCD;
        }
    }
    return nRead > 0;
}

static void LiveJHex(TrigLiveJson *j, const RwUInt8 *p, RwUInt32 n)
{
    static const RwChar s_szHex[] = "0123456789abcdef";
    RwUInt32 i;

    if (j->n + (RwInt32)n * 2 + 8 >= j->nMax)
        return;
    j->psz[j->n++] = '"';
    for (i = 0; i < n; i++)
    {
        j->psz[j->n++] = s_szHex[p[i] >> 4];
        j->psz[j->n++] = s_szHex[p[i] & 15];
    }
    j->psz[j->n++] = '"';
    j->psz[j->n] = 0;
}

// The AI in entity slot nSlot: its blocks, by class (an AIData, then the entity's classes it is).
RwBool TrigDrawLiveAiFullJson(RwChar *psz, RwInt32 nMax, RwInt32 nSlot)
{
    static RwUInt8 s_ab[0x4000];
    TrigLiveJson j = { psz, 0, nMax };
    type_3D3548 *pEntity = nSlot >= 0 && nSlot < 768 ? dword_4B6A00[nSlot].unk_04 : NULL;
    AIData *pAi = NULL;
    RwUInt32 dwBits = 0;
    RwInt32 c;

    LiveJ(&j, "{\"t\":\"aifull\",\"frame\":%u,\"slot\":%d", port_frame, nSlot);
    if (pEntity)
        __try
        {
            dwBits = pEntity->unk_2C;
            pAi = pEntity->vf_120();
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            pEntity = NULL;
        }
    if (pEntity == NULL)
    {
        LiveJ(&j, ",\"gone\":1}");
        return TRUE;
    }
    LiveJ(&j, ",\"soldier\":%d,\"entity\":\"%08X\",\"ai\":\"%08X\",\"classes\":[", (dwBits & 0x20) ? 1 : 0, (RwUInt32)pEntity,
          (RwUInt32)pAi);
    for (c = 0; c < (RwInt32)(sizeof(s_aAiFieldClasses) / sizeof(s_aAiFieldClasses[0])); c++)
    {
        const AiFieldClass *pClass = &s_aAiFieldClasses[c];
        const RwUInt8 *pBase;

        // (AIData from the AI object; the entity's classes from the entity, a soldier's only for a soldier)
        if (c == 0)
            pBase = (const RwUInt8 *)pAi;
        else if (c == 1 || (dwBits & 0x20))
            pBase = (const RwUInt8 *)pEntity;
        else
            continue;
        if (pBase == NULL || pClass->dwSize > sizeof(s_ab) || !LiveCopy(s_ab, pBase, pClass->dwSize))
            continue;
        LiveJ(&j, "%s{\"name\":\"%s\",\"addr\":\"%08X\",\"bytes\":", c ? "," : "", pClass->pszName, (RwUInt32)pBase);
        LiveJHex(&j, s_ab, pClass->dwSize);
        LiveJ(&j, "}");
    }
    LiveJ(&j, "]}");
    return j.n < nMax - 1;
}

#endif // CODFH_DRAW_TRIGGERS
