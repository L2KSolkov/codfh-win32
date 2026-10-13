// The debug tools' sound and projectile views (trigdraw.cpp draws them, trigtools.cpp's View
// tabs set them and list what they found).

#ifndef TRIGSNDPROJ_H
#define TRIGSNDPROJ_H

#include "game/sectionslots.h"

// ---- sounds: the audio bridge's playing voices (port/src/audio/dsound_bridge.cpp) ----
struct PortAudioVoiceInfo
{
    const void *id;
    float x, y, z;              // where it plays, in the game's world (3D voices)
    int is3D, mode3D, looping, channels;   // mode3D: 0 in the world, 1 head-relative, 2 off
    float volumeDb, seconds, played, minDistance, maxDistance;
};
extern "C" int port_audio_voices(PortAudioVoiceInfo *out, int max, float *listener);

#define TRIGDRAW_SOUNDS 128
extern RwBool g_bTrigDrawSounds;        // a marker at each 3D voice
extern RwBool g_bTrigDrawSoundLabels;   // with its volume, length and distances
extern RwBool g_bTrigDrawSoundRanges;   // and its minimum distance, as a ring
extern RwReal g_fTrigDrawSoundRange;    // how far from the camera (0 unlimited)
extern PortAudioVoiceInfo g_aTrigDrawSoundList[TRIGDRAW_SOUNDS];   // the last frame's voices
extern RwInt32 g_nTrigDrawSoundList;
extern RwReal g_avTrigDrawListener[3];

// ---- projectiles: the nine pools (dword_4E19F8), their spawns, impacts and blasts ----
#define TRIGDRAW_PROJ_KINDS 9
extern RwBool g_bTrigDrawProjectiles;   // the live ones, their trails, and where they ended
extern RwBool g_bTrigDrawProjLabels;    // the impacts' surface ids, the blasts
extern RwBool g_bTrigDrawProjTrails;    // the trail each leaves (else only where it is)
extern RwReal g_fTrigDrawProjTrail;     // seconds a trail and an impact stay
extern RwInt32 g_anTrigDrawProjSpawned[TRIGDRAW_PROJ_KINDS];   // since the start, by kind
extern RwInt32 g_anTrigDrawProjLive[TRIGDRAW_PROJ_KINDS];      // the last frame's
extern RwInt32 g_nTrigDrawProjImpacts, g_nTrigDrawProjBlasts;
const RwChar *TrigDrawProjKindName(RwInt32 nKind);
void TrigDrawProjReset();
// The last events (newest first): bImpact, its kind, its surface (impacts), its age in seconds.
RwInt32 TrigDrawProjEvent(RwInt32 nIndex, RwBool *pbImpact, RwInt32 *pnKind, RwInt32 *pnSurface, RwReal *pfAge,
                          RwV3d *pv);

// ---- trigger activity: entries, exits and the messages each trigger sends ----
extern RwBool g_bTrigDrawActivity;      // flash each trigger volume as it fires, its messages listed
extern RwBool g_bTrigDrawActiveOnly;    // only draw the triggers that fired lately
extern RwReal g_fTrigDrawActivitySecs;  // how long a flash and its lines stay
// The last events across all triggers (newest first): the handle, the kind (0 an entity in,
// 1 out, 2 a message), the message's name (kind 2), its age in seconds.
RwBool TrigDrawActivityEvent(RwInt32 nIndex, RwInt32 *pnHandle, RwInt32 *pnKind, const RwChar **ppszName,
                             RwReal *pfAge);
void TrigDrawActivityClear();

// ---- splines: every SplinePath of the level (dword_4CFA18) ----
extern RwBool g_bTrigDrawSplines;
extern RwBool g_bTrigDrawSplineLabels;
extern RwReal g_fTrigDrawSplineRange;   // how far from the camera its nearest point may be (0 unlimited)
extern RwInt32 g_nTrigDrawSplinesShown, g_nTrigDrawSplinesAll;

// ---- the world line tests (sub_91F40): the bullets', the AI's sight, the paths, the aim ----
extern RwBool g_bTrigDrawRays;
extern RwBool g_bTrigDrawRayMisses;     // the misses too (else only the hits)
extern RwReal g_fTrigDrawRaySecs;       // how long a ray stays
extern RwBool g_abTrigDrawRayKinds[6];  // by the mask: bullets, sight, paths, aim, vehicles, other
extern RwInt32 g_anTrigDrawRayCount[6]; // tests a second, by kind
const RwChar *TrigDrawRayKindName(RwInt32 nKind);

// ---- bullet hits on entities: the damage, the part; the soldiers' bone boxes ----
extern RwBool g_bTrigDrawHits;          // a number where each bullet hit, its damage and part
extern RwBool g_bTrigDrawHitBoxes;      // the bone boxes the bullets test on soldiers in view
extern RwReal g_fTrigDrawHitSecs;
extern RwReal g_fTrigDrawHitBoxRange;
extern RwInt32 g_nTrigDrawHitBoxesShown;

// ---- the level's lights (the world manager's list, the ambient and the directionals) ----
extern RwBool g_bTrigDrawLights;
extern RwBool g_bTrigDrawLightLabels;
extern RwBool g_bTrigDrawLightRadii;
extern RwReal g_fTrigDrawLightRange;
struct TrigDrawLightInfo
{
    const void *id;
    RwInt32 nType;              // 1 directional, 2 ambient, 0x80 point, 0x81 spot, 0x82 soft spot
    RwV3d vPos, vAt;
    RwReal fRadius, fCone;      // fCone: the cone's cosine (spots)
    RwRGBAReal colour;
    RwInt32 nFlags;             // 1 lights atomics, 2 lights the world
    RwInt32 nSource;            // 0 the level's list, 1 the ambient, 2 a directional slot, 3 the fallback
    // (the game's light extension, plugin 0x42B3: the section slot it is placed in (0xFFFF none,
    // 0x7FFF the global section), that section's id, and the entity that owns it)
    RwBool bExt;
    RwInt32 nSlot, nSectionId;
    const void *pOwner;
    RwUInt32 dwOwnerBits;       // the owner's unk_2C kind bits
};
#define TRIGDRAW_LIGHTS 128
extern TrigDrawLightInfo g_aTrigDrawLightList[TRIGDRAW_LIGHTS];
extern RwInt32 g_nTrigDrawLightList;
extern RwBool g_bTrigDrawLightCones;    // a spot's cone
// (the entities' zone light rigs: what actually lights a model. The world render recolours the
// shared ambient and four view lights for each model it draws (sub_1227F0) from the model's
// entity's zones (type_8E670::sub_8E870): an ambient colour and up to four directional lights)
extern RwBool g_bTrigDrawLightRigs;
struct TrigDrawLightRig
{
    const void *pEntity;
    RwUInt32 dwBits;            // its unk_2C kind bits
    RwV3d vPos;
    RwInt32 nLights;            // the directionals (0..4)
    RwRGBAReal ambient;
    RwV3d avDir[4];             // the direction each shines along
    RwRGBAReal aColour[4];
};
#define TRIGDRAW_LIGHT_RIGS 64
extern TrigDrawLightRig g_aTrigDrawLightRigs[TRIGDRAW_LIGHT_RIGS];
extern RwInt32 g_nTrigDrawLightRigs;
extern RwInt32 g_nTrigDrawLightRigsUnlit;   // in range but zone lighting off (unk_28_17 clear)

// ---- the models' mount points (the clump data plugin 0x4210's tagged matrices, chunk 0x4211) ----
extern RwBool g_bTrigDrawMounts;
extern RwBool g_bTrigDrawMountLabels;
extern RwBool g_bTrigDrawMountAxes;     // each point's axes (x red, y green, z blue), else a cross
extern RwReal g_fTrigDrawMountRange;
extern RwReal g_fTrigDrawMountSize;
extern RwChar g_szTrigDrawMountFilter[32];  // only tags containing this (any case); empty: all
struct TrigDrawMountInfo
{
    const void *pClump;
    const void *pOwner;         // the clump's entity (its extension, plugin 0x42B1), or 0
    RwUInt32 dwOwnerBits;
    RwUInt32 dwTag;             // four characters, high byte first ('FIRE')
    RwInt32 nBone;              // the hierarchy node it hangs on (0: the clump's frame)
    RwV3d vPos;
};
// ---- the models (the game's RenderWare extensions, plugins 0x42B0 atomic and 0x42B1 clump):
// what each model is, where the world manager placed it, what skips it, the inspector, the
// skeletons and the model cache ----
extern RwBool g_bTrigDrawModels;
extern RwInt32 g_nTrigDrawModelMode;    // 1 by section, 2 the collision skip flags, 3 by owner
extern RwBool g_bTrigDrawModelLabels;
extern RwReal g_fTrigDrawModelRange;
extern RwInt32 g_nTrigDrawModels;       // the models (clumps) found this frame
extern RwInt32 g_anTrigDrawModelsBySlot[SECTION_SLOTS + 2];   // the slots', then global, then none
extern RwInt32 g_nTrigDrawModelsSkipLines, g_nTrigDrawModelsSkipShots;  // atomics with bit 3, bit 4
// (the inspector: the model nearest the camera's line of sight)
extern RwBool g_bTrigDrawInspect;
extern RwBool g_bTrigDrawInspectFreeze;
struct TrigDrawModelInfo
{
    const void *pClump;
    const void *pAtomic;            // the atomic the line of sight hit
    const void *pOwner;
    RwUInt32 dwOwnerBits;
    RwV3d vCentre;
    RwReal fRadius;
    RwUInt32 dwClumpFlags, dwAtomicFlags;   // the extensions' flag bytes
    RwInt32 nClumpSlot, nClumpSection;      // where the clump is placed
    RwInt32 nAtomicSlot, nAtomicSection;
    RwInt32 nClumpHolders, nAtomicHolders;  // the holder lists' lengths (who points at it)
    RwInt32 nCacheKey;                      // the clump's model cache file key (0 none)
    RwInt32 nAtomics, nMounts, nBones, nKeepBones;
    RwUInt32 dwPartMask;                    // the atomic's unk_10
    RwBool bValid;
};
extern TrigDrawModelInfo g_TrigDrawInspected;
// (the skeletons: each bone as the animation has it, and where its rest offset (chunk 0x4212)
// would put it under its animated parent)
extern RwBool g_bTrigDrawSkeletons;
extern RwBool g_bTrigDrawSkeletonRest;
extern RwReal g_fTrigDrawSkeletonRange;
extern RwInt32 g_nTrigDrawSkeletons;
// (the model cache: dword_4F26D4's file records, refreshed while the view is open)
struct TrigDrawCacheInfo
{
    RwInt32 nFile, nValue;
    const void *pClump;
    RwInt32 nHolders, nUsers, nAtomics, nMounts;
};
#define TRIGDRAW_CACHE 320
extern TrigDrawCacheInfo g_aTrigDrawCache[TRIGDRAW_CACHE];
extern RwInt32 g_nTrigDrawCache;
void TrigDrawCacheRefresh();
// (the collision coloured by surface id: the material extension's low word)
extern RwBool g_bTrigDrawCollBySurface;
RwUInt32 TrigDrawSurfaceColour(RwInt32 nSurface);

// ---- the random numbers (trigrng.cpp): RpRandom (0) and rand() (1), counted while recording ----
extern RwBool g_bTrigRngRecord;
extern RwBool g_bTrigRngSeedOnRestart;  // reseed both at every restart (level, checkpoint, death)
extern RwUInt32 g_dwTrigRngSeed;
extern RwUInt32 g_anTrigRngTotal[2];
extern RwUInt32 g_anTrigRngLastFrame[2];
extern RwReal g_afTrigRngPerSecond[2];
extern RwUInt32 g_anTrigRngSinceRestart[2];
extern RwInt32 g_nTrigRngRestarts;
struct TrigRngCaller
{
    const void *pAddr;
    RwInt32 nGen;
    RwUInt32 nCount, nThisFrame, nLastFrame;
    RwBool bNamed, bLogged;
    RwChar szName[96];
};
#define TRIGRNG_CALLERS 256
extern TrigRngCaller g_aTrigRngCallers[TRIGRNG_CALLERS];
extern RwInt32 g_nTrigRngCallers;
struct TrigRngCall
{
    RwInt32 nGen;
    const void *pAddr;
    RwUInt32 dwValue;
    RwUInt32 dwFrame;
};
#define TRIGRNG_LOG 256
extern TrigRngCall g_aTrigRngLog[TRIGRNG_LOG];
extern RwInt32 g_nTrigRngLogNext;
extern RwUInt32 g_nTrigRngLogTotal;
extern "C" void PortRngNote(RwInt32 nGen, const void *pCaller, RwUInt32 dwValue);
void TrigRngReset();
void TrigRngSeedNow(RwUInt32 dwSeed);
RwUInt32 TrigRngStateHash(RwInt32 nGen);
const RwChar *TrigRngCallerName(TrigRngCaller *p);
void TrigRngFrame();

// ---- the frame timing (trigrng.cpp): what depends on the frame rate ----
extern RwBool g_bTrigFrameSample;     // measuring at all
struct TrigFrameSample
{
    RwReal fDelta;              // deltaTime: the frame's game time, in 60ths of a second (capped at 5)
    RwReal fRaw;                // flt_429288: before the cap
    RwReal fRealMs;             // its real time
    RwReal fSpeedGame, fSpeedReal;  // the player's horizontal speed, a game second and a real one
    RwUInt32 anRng[2];          // the random numbers drawn in it
};
#define TRIGFRAME_SAMPLES 240
extern TrigFrameSample g_aTrigFrameSamples[TRIGFRAME_SAMPLES];
extern RwInt32 g_nTrigFrameNext, g_nTrigFrameCount;
extern RwReal g_fTrigFrameGameOverReal;     // game seconds a real second, the last second
extern RwReal g_fTrigFrameFps;
extern RwInt32 g_nTrigFrameCapped;          // of the samples, frames longer than the cap
struct TrigFrameNote
{
    RwInt32 nMaxFps;
    RwReal fFps, fGameOverReal, fSpeedGame, fSpeedReal;
    RwReal afRngPerGameSecond[2];
    RwInt32 nCapped;
};
#define TRIGFRAME_NOTES 16
extern TrigFrameNote g_aTrigFrameNotes[TRIGFRAME_NOTES];
extern RwInt32 g_nTrigFrameNotes;
void TrigFrameNoteNow();
extern "C" int port_get_max_fps(void);
extern "C" void port_set_max_fps(int fps);

#define TRIGDRAW_MOUNTS 512
extern TrigDrawMountInfo g_aTrigDrawMountList[TRIGDRAW_MOUNTS];
extern RwInt32 g_nTrigDrawMountList;    // the points listed (in range, matching the filter)
extern RwInt32 g_nTrigDrawMountClumps;  // the clumps with mount points found
const RwChar *TrigDrawMountMeaning(RwUInt32 dwTag);

// ---- the lighting zones (dword_4B2550) and the entity each is in (type_3D3548::unk_90) ----
extern RwBool g_bTrigDrawZones;         // the zones' boxes
extern RwBool g_bTrigDrawZoneEntities;  // a mark on each entity in its zone's colour
extern RwBool g_bTrigDrawZoneLabels;
extern RwReal g_fTrigDrawZoneRange;
extern RwInt32 g_nTrigDrawZonesAll, g_nTrigDrawZonesShown;

// ---- the AI squads (dword_4395F0): members to their leader, the maneuvers ----
extern RwBool g_bTrigDrawSquads;
extern RwBool g_bTrigDrawSquadLabels;
extern RwInt32 g_nTrigDrawSquads;
const RwChar *TrigDrawManeuverName(RwInt32 nKind);

// ---- the AI's hearing (unit_03C1D0): the sounds made, the soldiers that heard them ----
extern RwBool g_bTrigDrawHearing;       // a ring at each sound (its range), lines to who heard it
extern RwBool g_bTrigDrawHearRadii;     // each listening soldier's own hearing radius
extern RwBool g_bTrigDrawHearLabels;
extern RwReal g_fTrigDrawHearSecs;
extern RwInt32 g_nTrigDrawHearNoises, g_nTrigDrawHeardCount;   // a second
const RwChar *TrigDrawNoiseKindName(RwInt32 nKind);

#endif
