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
// 2 with the collision too),
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

// Writes the trigger's type at its centre (the matrix's position), facing
// the camera whose matrix is pCamLtm: a quad per character with the
// charset's glyph cell as its texture, tinted dwColour. The characters are
// g_fTrigDrawTextScale of the distance high.
static void TrigDrawLabel(Trigger *pTrigger, const RwMatrix *pCamLtm, RwUInt32 dwColour)
{
    RtCharsetDesc desc;
    const RwChar *pszText = TrigDrawKindName(pTrigger);
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
    vCentre.x = pTrigger->unk_90;
    vCentre.y = pTrigger->unk_94;
    vCentre.z = pTrigger->unk_98;
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
    }
    if (!g_bTrigDrawEnabled || pCamera == NULL)
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

    for (i = 0; i <= dword_429D00 && i < 2000; i++)
    {
        pTrigger = (Trigger *)dword_4CFE30[i];
        if (pTrigger != NULL && TrigDrawInRange(pTrigger, &vCam))
            TrigDrawOne(pTrigger);
    }
    if (g_bTrigDrawLabels && TrigDrawCharset() != NULL)
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
