// The debug tools' collision material kinds (trigdraw.cpp keeps them, trigtools.cpp's Drawing
// tab lists them): each kind of material the collision triangles near the camera use, by its
// game tag (the material plugin 0x7A7's word, sub_FC000: the surface id in the low 16 bits,
// 0xFFFF none, the query flags in the high 16), its texture and its colour. With any kind's
// bShow set, only the shown kinds are drawn: the invisible blockers (untextured, or flagged to
// be skipped by some queries) on their own.

#ifndef TRIGCOLL_H
#define TRIGCOLL_H

#define TRIGDRAW_COLLKINDS 128

struct TrigDrawCollKind
{
    RwUInt32 dwTag;         // the material's game tag (surface id | flags << 16)
    RwUInt32 dwRgba;        // its colour, 0xRRGGBBAA
    RwChar szTexture[32];   // its texture's name ("" untextured)
    RwInt32 nTriangles;     // the triangles drawn of it in the last frame (all kinds counted)
    RwInt32 nMaterials;     // the materials seen of it
    RwBool bShow;           // drawn while any kind is shown
    RwUInt32 dwDraw;        // its colour when coloured by kind (0xAARRGGBB, from its tag and texture)
};

extern TrigDrawCollKind g_aTrigDrawCollKinds[TRIGDRAW_COLLKINDS];
extern RwInt32 g_nTrigDrawCollKinds;
extern RwBool g_bTrigDrawCollByKind;    // colour the triangles by their kind, not their facing
extern RwInt32 g_nTrigDrawCollFill;     // 0 filled, 1 outlines (the edges alone), 2 both
extern RwReal g_fTrigDrawCollGrid;      // outlines: grid lines across each triangle this far apart (0 none)
// What the query flags are known to exclude (docs: the web suite's COLLISION_MATERIALS.md):
// 0x10000 the player's body, 0x20000 the soldiers' and gimps' bodies (and the AI's sight),
// 0x40000 the vehicles, 0x80000 and 0x100000 the projectiles' line tests, 0x400000 the AI's
// sight tests, 0x800000 the other (non-player) vehicles.
const RwChar *TrigDrawCollFlagsText(RwUInt32 dwFlags, RwChar *pszOut, RwInt32 nOut);
void TrigDrawCollKindsClear();

#endif
