// The debug tools' sound and projectile views (trigdraw.cpp draws them, trigtools.cpp's View
// tabs set them and list what they found).

#ifndef TRIGSNDPROJ_H
#define TRIGSNDPROJ_H

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
};
#define TRIGDRAW_LIGHTS 128
extern TrigDrawLightInfo g_aTrigDrawLightList[TRIGDRAW_LIGHTS];
extern RwInt32 g_nTrigDrawLightList;

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
