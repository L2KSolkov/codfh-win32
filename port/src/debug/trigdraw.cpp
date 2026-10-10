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
#include "types/type_3DC9B0.h"
#include "types/type_15CCE0.h"
#include "types/type_D48D0.h"
#include "types/type_67620.h"
#include "types/type_3D2E7C.h"
#include "types/alfaobject.h"
#include "types/alfasched.h"

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

// Switches, set from the overlay's Drawing tab (trigtools.cpp): draw at all
// (off until asked for: the environment's CODFH_TRIGGERS=1 starts with it on,
// 2 with the collision too; CODFH_PATHNODES=1 the path nodes),
// the draw distance from the camera (0 = unlimited), and draw through
// walls (z test off).
RwBool g_bTrigDrawEnabled = FALSE;
RwReal g_fTrigDrawRange = 150.0f;
RwBool g_bTrigDrawSeeThrough = TRUE;
// The labels: on or off, and their height as a fraction of the distance.
RwBool g_bTrigDrawLabels = TRUE;
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
static RwUInt32 TrigDrawColour(Trigger *pTrigger)
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
// distance high.
static void TrigDrawText(const RwChar *pszText, const RwV3d *pvAt, const RwMatrix *pCamLtm, RwUInt32 dwColour)
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

// Writes the trigger's type at its centre (the matrix's position).
static void TrigDrawLabel(Trigger *pTrigger, const RwMatrix *pCamLtm, RwUInt32 dwColour)
{
    RwV3d vCentre;

    vCentre.x = pTrigger->unk_90;
    vCentre.y = pTrigger->unk_94;
    vCentre.z = pTrigger->unk_98;
    TrigDrawText(TrigDrawKindName(pTrigger), &vCentre, pCamLtm, dwColour);
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
static volatile LONG s_nAiNotesLock;

// Keeps a note about the entity pEntity (its newest four), for its label.
void TrigDrawAiNote(const void *pEntity, const RwChar *pszText)
{
    TrigDrawAiNotes *pNotes = NULL;
    RwInt32 i, nOldest = 0;

    RwChar szShort[TRIGDRAW_AI_NOTE];
    const RwChar *p;

    if (!g_bTrigDrawAi || pEntity == NULL || pszText == NULL)
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
    while (InterlockedExchange(&s_nAiNotesLock, 1))
        ;
    for (i = 0; i < TRIGDRAW_AI_ENTITIES; i++)
    {
        if (s_aAiNotes[i].pEntity == pEntity)
        {
            pNotes = &s_aAiNotes[i];
            break;
        }
        if (s_aAiNotes[i].dwLast < s_aAiNotes[nOldest].dwLast)
            nOldest = i;
    }
    if (pNotes == NULL)
    {
        pNotes = &s_aAiNotes[nOldest];
        memset(pNotes, 0, sizeof(*pNotes));
        pNotes->pEntity = pEntity;
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

    if (!g_bTrigDrawAi || pScript == NULL || pszName == NULL)
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
            RwChar aszLines[7 + TRIGDRAW_AI_NOTES][TRIGDRAW_AI_NOTE + 16];
            RwInt32 nLines = 0, j;
            RwReal fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z), fStep;
            TrigDrawAiNotes *pNotes = NULL;

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
            if (s->nNodeId || s->nNextId)
                _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE, "node: at #%d %s, next #%d %s", s->nNodeId,
                          s->nNodeId ? TrigDrawPathTypeName(s->nNodeType) : "-", s->nNextId,
                          s->nNextId ? TrigDrawPathTypeName(s->nNextType) : "-");
            for (j = 0; j < TRIGDRAW_AI_ENTITIES; j++)
                if (s_aAiNotes[j].pEntity == pEntity)
                {
                    pNotes = &s_aAiNotes[j];
                    break;
                }
            // the notes, newest first, with their age in seconds
            RwInt32 nNotes = nLines;
            for (j = 0; pNotes && j < TRIGDRAW_AI_NOTES; j++)
            {
                RwInt32 n = (pNotes->nNext + TRIGDRAW_AI_NOTES - 1 - j) % TRIGDRAW_AI_NOTES;

                if (!pNotes->adwFrame[n])
                    continue;
                if (pNotes->anRepeats[n] > 1)
                    _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE + 15, "%.0fs %s (x%d)",
                              (RwReal)(port_frame - pNotes->adwFrame[n]) / 60.0f, pNotes->aszText[n],
                              pNotes->anRepeats[n]);
                else
                    _snprintf(aszLines[nLines++], TRIGDRAW_AI_NOTE + 15, "%.0fs %s",
                              (RwReal)(port_frame - pNotes->adwFrame[n]) / 60.0f, pNotes->aszText[n]);
            }
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
    return pSector;
}

// Draws the collision worlds near the camera at pvCam: the global section's
// and every live section slot's (as the collision queries walk them).
static void TrigDrawCollision(const RwV3d *pvCam)
{
    RwInt32 i;

    s_vCollCam = *pvCam;
    s_nCollVerts = 0;
    if (unk_4E5CD8.get_unk_28())
        RpWorldForAllWorldSectors(unk_4E5CD8.get_unk_28(), TrigDrawCollisionSector, NULL);
    for (i = 0; i < 4; i++)
    {
        if (dword_4E5D30[i].get_unk_00() && dword_4E5D30[i].get_unk_28())
            RpWorldForAllWorldSectors(dword_4E5D30[i].get_unk_28(), TrigDrawCollisionSector, NULL);
    }
    TrigDrawCollisionFlush();
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

// The free camera (the Drawing tab's switch): the world is drawn from its own
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
        // (CODFH_AI=1: the AI's state and notes)
        if (GetEnvironmentVariableA("CODFH_AI", NULL, 0))
            g_bTrigDrawAi = TRUE;
        // (CODFH_PATHNODES=1: the path nodes, with their labels)
        if (GetEnvironmentVariableA("CODFH_PATHNODES", NULL, 0))
            g_bTrigDrawPathNodes = g_bTrigDrawPathLabels = TRUE;
    }
    if ((!g_bTrigDrawEnabled && !g_bTrigDrawPathNodes && !g_bTrigDrawAi) || pCamera == NULL)
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
    if (!g_bTrigDrawEnabled)
        i = dword_429D00 + 1;
    else
        i = 0;

    for (; i <= dword_429D00 && i < 2000; i++)
    {
        pTrigger = (Trigger *)dword_4CFE30[i];
        if (pTrigger != NULL && TrigDrawInRange(pTrigger, &vCam))
            TrigDrawOne(pTrigger);
    }
    if (g_bTrigDrawEnabled && g_bTrigDrawLabels && TrigDrawCharset() != NULL)
    {
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)TrigDrawCharset());
        for (i = 0; i <= dword_429D00 && i < 2000; i++)
        {
            pTrigger = (Trigger *)dword_4CFE30[i];
            if (pTrigger != NULL && TrigDrawInRange(pTrigger, &vCam))
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

#endif // CODFH_DRAW_TRIGGERS
