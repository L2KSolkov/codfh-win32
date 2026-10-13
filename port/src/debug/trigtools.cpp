// The Win32 port's game debug tools (CODFH_DRAW_TRIGGERS, with the ImGui
// overlay): the plain build's research web pages (research/trigweb.cpp in
// C:\codfh-patches\plain-build\draw-triggers.patch) as tabs of an overlay
// window, live state read straight from memory and the pages' actions, in five groups of tabs
// (the last action's result above them):
//   View     every overlay in one list, by topic, its switch beside its name and its page beside
//            the list: World (triggers with their activity, collision and its material kinds,
//            splines, lighting zones, lights, sounds), AI (the soldiers' state, path nodes, squads,
//            hearing, gimps), Combat (the world line tests, hits and bone boxes, projectiles,
//            generators), Camera (noclip, the free camera)
//   Player   Player       the local player (sub_1745A0(0), a type_10F710)
//            Inventory    health, the inventory and the 39 weapons, with gives
//            Weapons      the weapon settings (dword_4C19C0), edited in place
//            Cheats       the developers' switches (the AI ignores me, god mode, next level, no
//                         AI spawns, tank reset), freeze all AI, unlimited ammo, game speed,
//                         cheat flags
//   Level    Entities     the entity table (dword_4B6A00): teleport, kill, hp
//            Triggers     List: the handle table, nearest first: teleport, spawn soldiers;
//                         Selected: every field of any trigger (triggerfields.inc), editable
//            Generators   List: the projectile generators, nearest first: their state and
//                         target, the scripts' PG_ actions, teleport, a free camera look;
//                         Selected: every field of one and its trigger, editable
//            Objectives   the checkpoint and global script registers, the objectives
//            Sections     the section slots, and a section load into one
//   Scripts  Scripts      the live state machines, performances and tasks by name; a
//                         picked one's code and (a state machine's) variables, editable
//            Script log   the scripts' prints and failed checks, the script debugger's
//                         reports (CDebugScript's settings) and the debug switches
//            VM           the level-script VM's registers, code and stacks, as the last
//                         script to run halted (the overlay draws between runs)
//   Engine   Level and render  frame step, FOV zoom, far clip, zones...
//            Audio        the level's mutes and sound warnings
//            Tunables     the tuning values no code changes (AI, pathing, vehicles, player...)
//            Shell        the shell manager's settings (the level's and the front end's)
//            HUD          the HUD's items (151, single player's 101), shown or hidden
//            Loading      the loading queue (AsynchLoadingQueue)
//            Memory       the section arenas and the script pools
//            Links        the web suite's live link, the game's own debug menu
// (Not the patch's /map and /levels: the second loads a single-player level
// into the multiplayer build, which its other hooks are for.)
// The overlay draws from the device's Present, on the game's thread, after
// the frame; what changes the game (a section load, a give, a teleport, a
// spawn) is handed to the main loop (TrigWebTick, from sub_D7880) as the
// pages did. Reads stay guarded (__try): a "?" for what is not there. The
// structures are read by their fields (the headers lay them out for single
// player too, under CODFH_SP), the tables by the sizes both builds share.

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
#include "types/type_44350.h"
#include "types/scriptvm.h"
#include "types/alfaobject.h"
#include <dbghelp.h>
#include "types/alfatimer.h"
#include "types/alfamessman.h"
#include "types/type_42AF0.h"
#include "types/type_10F710.h"
#include "game/functions.h"
#include "game/worldmgr.h"
#include "types/type_4E5D30.h"
#include "types/SectionInfo.h"
#include "types/alfasched.h"
#include "types/type_4C19C0.h"
#include "types/type_DC400.h"
#include "game/objectives.h"
#include "types/alfaobjman.h"
#include "types/PlayerTrigger.h"
#include "types/SoldierTrigger.h"
#ifndef CODFH_SP
#include "types/cNetSoldierTrigger.h"
#include "game/parsedfile.h"
#include "game/uiglue.h"
#include "game/liveservice.h"
#include "game/ingamepages.h"
#include "game/ingamescreens.h"
#include "types/type_141C10.h"
#include "types/type_3DAFC8.h"
#include "types/type_4B83A0.h"
#include "types/type_4B85F8.h"
#include "types/type_4D53F8.h"
#include "game/netmsg.h"
#include "types/type_15CCE0.h"
#endif
#include "types/type_4B8EF0.h"
#include "types/VehicleTrigger.h"
#include "types/type_495F0.h"
#include "game/weaponbank.h"
#include "game/debugmenu.h"
#include "rw/rpworld.h"
#include "rw/rpcollis.h"
#include <stddef.h>
#include "types/type_4D1DB8.h"
#include "game/data.h"
#include "types/type_4C00E8.h"
#include "types/cNetLevelParams.h"
#include "rws/debugswitches.h"
#include "rws/camerahelper.h"
#include "game/cheats.h"
#include "game/gameloop.h"
#include "game/savestate.h"
#include "types/AIData.h"
#include "types/type_3C540.h"
#include "types/type_3DBC78_450.h"
#include "types/type_1227C0.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_3D2E7C.h"
#include "game/godassetmanager.h"
#include "types/type_72810.h"
#include "types/type_3DF8D8.h"

#include "../../third_party/imgui/imgui.h"

// The VM's stack pointer and its current script object (unit_067B10; not
// in scriptvm.h).
extern RwInt32 *dword_449318;
extern type_67620 *dword_449328;
// The call opcode (unit_067B10), to find its slot in the opcode table.
void sub_69330();
// trigdraw.cpp's switches.
extern RwBool g_bTrigDrawEnabled;
extern RwBool g_bTrigDrawCollision;
extern RwBool g_bTrigDrawNoclip;
extern RwReal g_fTrigDrawNoclipSpeed;
extern RwBool g_bTrigDrawSeeThrough;
extern RwBool g_bTrigDrawLabels;
extern RwBool g_bTrigDrawNames;
extern RwReal g_fTrigDrawRange;
extern RwReal g_fTrigDrawTextScale;
extern RwReal g_fTrigDrawCollisionRange;
extern RwReal g_fTrigDrawCollisionLift;
#include "trigcoll.h"
#include "trigsndproj.h"
#include "types/animbank.h"
#include "types/vec4.h"
#include "rw/rprandom.h"
#include <float.h>
#include <stdlib.h>
extern RwBool g_bTrigDrawFreeCam;
// (trigweb.cpp: the level viewer's live link)
extern RwBool g_bTrigLive;
extern RwInt32 g_nTrigLivePort;
extern RwInt32 g_nTrigLiveClients;
void TrigLiveTick();
void TrigLiveLog(const RwChar *pszLine);
extern RwBool g_bTrigDrawAi;
extern RwBool g_bTrigDrawAiText;
extern RwBool g_bTrigDrawAiLines;
extern RwBool g_bTrigDrawAiPath;
extern RwBool g_bTrigDrawAiCover;
extern RwBool g_bTrigDrawAiCombat;
extern RwBool g_bTrigDrawPg;
extern RwBool g_bTrigDrawGimps, g_bTrigDrawShrimps;
extern RwReal g_fTrigDrawGimpRange;
extern RwInt32 g_nTrigDrawGimpsShown, g_nTrigDrawShrimpsShown;
extern RwBool g_bTrigDrawPgText;
extern RwReal g_fTrigDrawPgRange;
extern RwInt32 g_nTrigDrawPgShown;
void TrigDrawFreeCamLookAt(const RwV3d *pv);
extern RwReal g_fTrigDrawAiRange;
extern RwInt32 g_nTrigDrawAiShown;
extern RwBool g_bTrigDrawPathNodes;
extern RwBool g_bTrigDrawPathLinks;
extern RwBool g_bTrigDrawPathLabels;
extern RwReal g_fTrigDrawPathRange;
extern RwInt32 g_nTrigDrawPathType;
extern RwInt32 g_nTrigDrawPathShown, g_nTrigDrawPathLinksShown;
const RwChar *TrigDrawPathTypeName(RwInt32 nType);
extern RwReal g_fTrigDrawFreeCamSpeed;
extern RwReal g_fTrigDrawFreeCamLook;
const RwChar *TrigDrawKindName(Trigger *pTrigger);
const RwChar *TrigDrawTriggerName(Trigger *pTrigger);   // (trignames.cpp)
// The section slots, the global section, and the starting sections
// (unit_171DC0, unit_0B0410).
#include "game/sectionslots.h"
extern type_4E5D30 dword_4E5D30[SECTION_SLOTS];
extern type_4E5D30 unk_4E5CD8;
extern RwInt32 dword_4B6830[4];
extern RwInt32 dword_4B6840[4];
extern RwInt32 dword_4B6850;
RwInt32 sub_174640(RwUInt16 arg_0);
// The loading queue (types/asynchload.h, which brings the kernel's own
// headers in against xtl.h): queue a job, whether one is queued, whether a
// section's is, and cancel the sections' loads not kept.
void sub_81EB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
RwInt32 sub_81FB0(RwInt32 arg_0, const RwChar *arg_4, RwInt32 arg_8);
RwInt32 sub_82020(RwInt32 arg_0, RwInt32 arg_4);
void sub_82070(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
// The weapons' English names (unit_0FD730), by index 0 to 38.
extern const RwChar *off_429768[39];
// The script pools (unit_071360, sub_713E0 sets them up).
extern type_16C2A0 dword_449A50;
extern type_16C2A0 dword_449A30;
extern type_16C2A0 dword_4499F0;
extern type_16C2A0 dword_4499D0;
extern type_16C2A0 dword_449A10;
extern type_16C2A0 dword_4499B0;
extern type_16C2A0 dword_449950[3];

// An action asked for in a tab, for the main thread (TrigWebTick): its kind
// and arguments, set while pending; and what came of the last one.
enum
{
    REQ_SECTION = 1,    // a: the section, b: the slot
    REQ_TELEPORT,       // f: the position
    REQ_HEAL,           // f[0]: the health percentage
    REQ_GIVE,           // a: the inventory kind, b: how many
    REQ_AMMO,           // a: the weapon index, b: the rounds in reserve
    REQ_SETHP,          // a: the entity table slot, b: the hit points
    REQ_GIVEWEAPON,     // a: the weapon, b: 1 into the other slot (else the
                        // hand's) | 2 keep it across checkpoint restarts
    REQ_SPAWNSOLDIER,   // a: the soldier trigger's handle (-1 the nearest
                        // that can spawn), f: where
    REQ_PG              // a: the projectile generator's id, b: what (PG_*)
};

// What a REQ_PG does to its generator, as the scripts' "PG_" commands do.
enum
{
    PG_START,           // "PG_ManipulateProjectileGenerator" 2
    PG_STOP,            // and 1
    PG_FIRE,            // "PG_ForcedFire"
    PG_TARGETME,        // "PG_TargetPoint" at the player, its spread kept
    PG_TARGETDEFAULT,   // "PG_TargetDefault"
    PG_LOSON,           // "PG_EnableLOSCheck"
    PG_LOSOFF,
    PG_STAGESON,        // "PG_EnableFiringStages"
    PG_STAGESOFF
};

// A weapon give in progress (TickGive, each frame): the weapon, its slot
// (0 the hand's, 1 the other), whether to keep it, and the frames waited for
// its bank.
static RwInt32 s_nGiveWeapon = -1;
static RwInt32 s_nGiveSlot;
static RwBool s_bGiveKeep;
static RwInt32 s_nGiveFrames;
#define TRIGWEB_GIVE_TIMEOUT 900
static RwInt32 s_nReqKind;
static RwInt32 s_nReqA, s_nReqB;
static RwReal s_afReq[3];
static RwBool s_bReqPending;
static RwChar s_szReqResult[160] = "none yet";

// Guarded reads: the value, or FALSE when the address faults.
static RwBool ReadU32(const void *pAddress, RwUInt32 *pdwOut)
{
    __try
    {
        *pdwOut = *(const RwUInt32 *)pAddress;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

static RwBool ReadF32(const void *pAddress, RwReal *pfOut)
{
    __try
    {
        *pfOut = *(const RwReal *)pAddress;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// A zero-terminated string of up to nMax characters into pszOut (printable
// characters only); "?" when it faults.
static void ReadText(const RwChar *pszText, RwChar *pszOut, RwInt32 nMax)
{
    RwInt32 i, n = 0;
    RwChar c;

    __try
    {
        for (i = 0; i < nMax && pszText[i]; i++)
        {
            c = pszText[i];
            if ((RwUInt8)c < 0x20 || (RwUInt8)c > 0x7E)
                c = '.';
            pszOut[n++] = c;
        }
        pszOut[n] = 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        strcpy(pszOut, "?");
    }
}

// ---- the tabs' rows: a name and a value, two columns ----

static RwBool BeginRows(const RwChar *pszId)
{
    if (!ImGui::BeginTable(pszId, 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return FALSE;
    return TRUE;
}

static void Row(const RwChar *pszName, const RwChar *pszFormat, ...)
{
    RwChar sz[256];
    va_list args;

    va_start(args, pszFormat);
    _vsnprintf(sz, sizeof(sz) - 1, pszFormat, args);
    va_end(args);
    sz[sizeof(sz) - 1] = 0;
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("%s", pszName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(sz);
}

static void RowU32(const RwChar *pszName, const void *pAddress, RwBool bHex)
{
    RwUInt32 dw;

    if (!ReadU32(pAddress, &dw))
        Row(pszName, "?");
    else if (bHex)
        Row(pszName, "0x%08X", dw);
    else
        Row(pszName, "%d", (RwInt32)dw);
}

static void RowF32(const RwChar *pszName, const void *pAddress)
{
    RwReal f;

    if (ReadF32(pAddress, &f))
        Row(pszName, "%.3f", f);
    else
        Row(pszName, "?");
}

static void RowV3d(const RwChar *pszName, const RwV3d *pv)
{
    RwReal x, y, z;

    if (ReadF32(&pv->x, &x) && ReadF32(&pv->y, &y) && ReadF32(&pv->z, &z))
        Row(pszName, "%.2f, %.2f, %.2f", x, y, z);
    else
        Row(pszName, "?");
}

// Hands an action to the main thread (TrigWebTick); its result shows on
// the result line once done.
static void Request(RwInt32 nKind, RwInt32 nA, RwInt32 nB, RwReal f0, RwReal f1, RwReal f2)
{
    if (s_bReqPending)
    {
        strcpy(s_szReqResult, "busy: the last action is still pending");
        return;
    }
    s_nReqKind = nKind;
    s_nReqA = nA;
    s_nReqB = nB;
    s_afReq[0] = f0;
    s_afReq[1] = f1;
    s_afReq[2] = f2;
    s_bReqPending = TRUE;
}

// The last action's result, as a line in a tab.
static void ResultLine()
{
    ImGui::TextDisabled("last action:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.4f, 1.0f), "%s%s", s_szReqResult, s_bReqPending ? " (pending)" : "");
}

// The local player's frame position, or FALSE.
static RwBool PlayerPosition(type_10F710 *pPlayer, RwV3d *pvOut)
{
    __try
    {
        RwFrame *pFrame = pPlayer->unk_338.unk_08;

        if (pFrame == NULL)
            return FALSE;
        *pvOut = RwFrameGetMatrix(pFrame)->pos;
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// The name of the script command at index nIndex of Base, or "?".
static void CommandName(RwInt32 nIndex, RwChar *pszOut)
{
    RwUInt32 dwBase, dwName, dwCount;

    strcpy(pszOut, "?");
    if (!ReadU32(&Base, &dwBase) || !ReadU32(&NumOfElements, &dwCount) || dwBase == 0)
        return;
    if (nIndex < 0 || nIndex >= (RwInt32)dwCount)
        return;
    if (!ReadU32(&((type_44350 *)dwBase)[nIndex].unk_00, &dwName) || dwName == 0)
        return;
    ReadText((const RwChar *)dwName, pszOut, 60);
}

// The call opcode's slot in the opcode table, -1 when not found.
static RwInt32 CallOpcode()
{
    RwInt32 i;

    for (i = 0; i < 49; i++)
    {
        if (dword_4491C0[i] == sub_69330)
            return i;
    }
    return -1;
}

// ---- the actions (the main thread's) ----

// Whether the slot holds a section: live or loading.
static RwBool SlotUsed(type_4E5D30 *pSlot)
{
    return pSlot->get_unk_00() || pSlot->get_unk_04();
}

// Loads the section wSection into the slot nSlot the way a SectionTrigger
// the player enters does (sub_145060, kind 4), keeping the other slots'
// sections: unloads the slot (unless its section is still queued), labels
// it with the new section, cancels the queued loads of sections not kept,
// and queues the load unless the section is loaded, loading or queued.
// On the main thread only (TrigWebTick).
static void LoadSection(RwUInt16 wSection, RwInt32 nSlot)
{
    type_4E5D30 *pSlot;
    RwInt32 aKeep[3] = { 0xFFFF, 0xFFFF, 0xFFFF };
    RwInt32 i, nKeep = 0;
    RwBool bHave = FALSE;
    RwUInt16 wOld;

    for (i = 0; i < 4; i++)
    {
        pSlot = &dword_4E5D30[i];
        if (!SlotUsed(pSlot))
            continue;
        if (pSlot->unk_08 == wSection)
            bHave = TRUE;
        else if (i != nSlot && nKeep < 3)
            aKeep[nKeep++] = pSlot->unk_08;
    }
    if (bHave || sub_174640(wSection))
    {
        sprintf(s_szReqResult, "section %d is already loaded or loading", wSection);
        return;
    }
    pSlot = &dword_4E5D30[nSlot];
    if (SlotUsed(pSlot))
    {
        wOld = pSlot->unk_08;
        if (sub_82020(0, wOld))
        {
            sprintf(s_szReqResult, "slot %d's section %d is still queued; try again", nSlot, wOld);
            return;
        }
        sub_174030((RwUInt16)nSlot, 0);
        pSlot->set_unk_08(wSection);
        if (SectionInfo::sub_B0140())
            pSlot->unk_04 = 1;
        sprintf(s_szReqResult, "unloaded section %d from slot %d; ", wOld, nSlot);
    }
    else
        s_szReqResult[0] = 0;
    sub_82070(aKeep[0], aKeep[1], aKeep[2], wSection);
    if (!sub_81FB0(0, "", wSection))
    {
        sub_81EB0(0, "", wSection);
        sprintf(s_szReqResult + strlen(s_szReqResult), "queued section %d", wSection);
    }
    else
        sprintf(s_szReqResult + strlen(s_szReqResult), "section %d was already queued", wSection);
}

// Moves the local player to pv: its frame, its last and target places, and
// no fall to count (as noclip does in type_10F710::vf_044).
static void Teleport(type_10F710 *pPlayer, const RwV3d *pv)
{
    RwFrame *pFrame = pPlayer->unk_338.unk_08;

    if (pFrame == NULL)
    {
        strcpy(s_szReqResult, "the player has no frame");
        return;
    }
    // (placed as the scripts' teleports place an entity, "TeleportToNamedObject": its vf_0C0,
    // which keeps its every position, not only its frame's; then its fall forgotten)
    pPlayer->vf_0C0((RwV3d *)pv);
    pPlayer->unk_440 = *pv;
    pPlayer->unk_510 = -1000000.0f;
    pPlayer->unk_518 = 0.0f;
    sprintf(s_szReqResult, "teleported to %.2f, %.2f, %.2f", pv->x, pv->y, pv->z);
}

// The nearest hit along the line GroundBelow casts (its fraction).
static RpCollisionTriangle *GroundHit(RpIntersection *pIs, RpWorldSector *pSector, RpCollisionTriangle *pTri,
                                      RwReal fDist, void *pData)
{
    if (fDist < *(RwReal *)pData)
        *(RwReal *)pData = fDist;
    return pTri;
}

// Moves *pv down onto the collision floor below it (from 1 m above, up to
// 200 m down), through the global section's world and each live section
// slot's; FALSE, leaving it, when there is none. Soldiers do not fall: they
// stand where they are put and walk by navigation, so one in the air stays.
static RwBool GroundBelow(RwV3d *pv)
{
    RpIntersection is;
    RwReal fHit = 2.0f;
    RpWorld *pWorld;
    RwInt32 i;

    is.type = rpINTERSECTLINE;
    is.t.line.start = *pv;
    is.t.line.start.y += 1.0f;
    is.t.line.end = *pv;
    is.t.line.end.y -= 200.0f;
    for (i = 0; i <= 4; i++)
    {
        pWorld = i < 4 ? (dword_4E5D30[i].get_unk_00() ? dword_4E5D30[i].get_unk_28() : NULL) : unk_4E5CD8.get_unk_28();
        if (pWorld)
            RpCollisionWorldForAllIntersections(pWorld, &is, GroundHit, &fHit);
    }
    if (fHit > 1.0f)
        return FALSE;
    pv->y = is.t.line.start.y + (is.t.line.end.y - is.t.line.start.y) * fHit;
    return TRUE;
}

// Whether the line from *pA to *pB meets no collision (the global section's world and each live
// section slot's, as GroundBelow tests).
static RwBool LineClear(const RwV3d *pA, const RwV3d *pB)
{
    RpIntersection is;
    RwReal fHit = 2.0f;
    RpWorld *pWorld;
    RwInt32 i;

    is.type = rpINTERSECTLINE;
    is.t.line.start = *pA;
    is.t.line.end = *pB;
    for (i = 0; i <= 4; i++)
    {
        pWorld = i < 4 ? (dword_4E5D30[i].get_unk_00() ? dword_4E5D30[i].get_unk_28() : NULL) : unk_4E5CD8.get_unk_28();
        if (pWorld)
            RpCollisionWorldForAllIntersections(pWorld, &is, GroundHit, &fHit);
    }
    return fHit > 1.0f;
}

// Spawns the soldier of the soldier trigger pTrigger (kind 5) at *pv: its
// place (unk_90) and matrix are moved there for the spawn and put back, and
// its free-spawn flag (unk_24_18: no starting cover point needed, entity
// memory past the soldier pool's room) set for it. Its spawn (vf_020) needs
// the trigger's soldier definition loaded, so a trigger of this map. Returns
// the soldier, or NULL. In multiplayer, the map's cNetSoldierTrigger (dword_4F8134) spawns a
// remote player's soldier, a body only the network moves (sub_1BEBB0): it is spawned as single
// player spawns a soldier instead (SpawnAiSoldierMp), a soldier with its AI and class script,
// in the multiplayer character.
extern "C" void plog(const char *fmt, ...);

// (a faulting spawn's exception: its code, address, the address it touched, and the return
// addresses up the frame pointers, kept by the filter for the result line)
static void MsgCodeName(void *p, RwChar *psz, RwInt32 nMax);
static struct
{
    RwUInt32 dwCode;
    void *pAt;
    RwUInt32 dwTouched;
    void *apUp[6];
    RwInt32 nUp;
} s_spawnFault;

static int SpawnFaultFilter(EXCEPTION_POINTERS *pEx)
{
    RwUInt32 *pFrame = (RwUInt32 *)(size_t)pEx->ContextRecord->Ebp;

    s_spawnFault.dwCode = pEx->ExceptionRecord->ExceptionCode;
    s_spawnFault.pAt = pEx->ExceptionRecord->ExceptionAddress;
    s_spawnFault.dwTouched = pEx->ExceptionRecord->NumberParameters >= 2
                                 ? (RwUInt32)pEx->ExceptionRecord->ExceptionInformation[1] : 0;
    s_spawnFault.nUp = 0;
    while (pFrame && s_spawnFault.nUp < 6 && !IsBadReadPtr(pFrame, 8))
    {
        s_spawnFault.apUp[s_spawnFault.nUp++] = (void *)(size_t)pFrame[1];
        if ((RwUInt32 *)(size_t)pFrame[0] <= pFrame)
            break;
        pFrame = (RwUInt32 *)(size_t)pFrame[0];
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

static void SpawnFaultText()
{
    RwChar sz[96];
    RwInt32 i, n;

    MsgCodeName(s_spawnFault.pAt, sz, sizeof(sz));
    n = _snprintf(s_szReqResult, sizeof(s_szReqResult), "the spawn faulted: %08X at %s (touching %08X); from",
                  s_spawnFault.dwCode, sz, s_spawnFault.dwTouched);
    for (i = 0; i < s_spawnFault.nUp && n > 0 && n < (RwInt32)sizeof(s_szReqResult) - 2; i++)
    {
        MsgCodeName(s_spawnFault.apUp[i], sz, sizeof(sz));
        n += _snprintf(s_szReqResult + n, sizeof(s_szReqResult) - n, " %s", sz);
    }
    s_szReqResult[sizeof(s_szReqResult) - 1] = 0;
    plog("spawn: %s", s_szReqResult);
}

#ifndef CODFH_SP
// A single player soldier in multiplayer: SoldierTrigger::vf_020 and sub_134B40 as they are,
// but its entity memory from pool 6 (0x2240 bytes, the remote players' soldiers'). Multiplayer
// never makes one of these (0x2170 bytes): its entity allocator (sub_D56D0) only looks in pools
// 1 to 5 (at most 0x9B0) for one, then, asked to make room, faults ranking the entities. The
// entity notes its pool (unk_20, from dword_429264) for its release.
static type_3DF8D8 *ForeignRead(const RwChar *pszLevel, type_3DF8D8_04 *pKey, RwInt32 nKind);

// The AI soldiers spawned in multiplayer (TrigIsAiSoldier: their weapons aim as single player's do,
// src/recovered/unit_15CCE0.cpp's fire); a slot freed is reused.
#define TRIG_AI_SOLDIERS 64
static const void *s_apAiSoldiers[TRIG_AI_SOLDIERS];

bool TrigIsAiSoldier(const void *pEntity)
{
    RwInt32 i;

    if (pEntity == NULL)
        return false;
    for (i = 0; i < TRIG_AI_SOLDIERS; i++)
        if (s_apAiSoldiers[i] == pEntity)
            return true;
    return false;
}

// A bullet hit on the local player (its vf_064, which deals none: the network's hit messages
// do, sub_1ACAB0): from an AI soldier, dealt as those do (pvf_03C); killed, the player dies.
RwInt32 TrigAiHitPlayer(type_17DBD0_player *pPlayer, type_75600 *pHit)
{
    if (pHit == NULL || !TrigIsAiSoldier(pHit->unk_0C) || (void *)pPlayer != (void *)unk_4F7EB8.unk_1A4)
        return 0;
    if (pPlayer->pvf_03C(pHit))
    {
        type_3DA434 msg;

        // (the kill as the network's bullet kills take it, sub_1ACBA0: sent, shown and scored; as
        // the player's own, there being no peer that fired)
        msg.unk_04 = 0;
        msg.unk_08 = (RwUInt8)pHit->unk_24;
        msg.unk_0C = pHit->unk_2C;
        sub_1ACBA0(unk_4F7EB8.sub_1AEC70(), &msg);
        plog("aihit: an AI soldier's bullet killed the local player");
        return 1;
    }
    plog("aihit: an AI soldier's bullet hit the local player: health %.2f", pPlayer->unk_19DC);
    return 0;
}

static void TrigAddAiSoldier(const void *pEntity)
{
    RwInt32 i, k;

    // (a slot whose entity is gone from the entity table is free)
    for (i = 0; i < TRIG_AI_SOLDIERS; i++)
    {
        if (s_apAiSoldiers[i] == NULL)
            break;
        for (k = 0; k < 0x300; k++)
            if (dword_4B6A00[k].unk_04 == s_apAiSoldiers[i])
                break;
        if (k == 0x300)
            break;
    }
    if (i < TRIG_AI_SOLDIERS)
        s_apAiSoldiers[i] = pEntity;
}

// An NPC weapon type for an AI soldier in multiplayer: the first whose model is read
// (sub_15D010 clones its definition's model, kind 26, and gives up without one, and the
// weapon's take-up, sub_15D3E0, then faults on no clump; one with unk_74 set needs unk_58's
// object too), or -1; *pnAll the NPC weapons the level has.
static RwInt32 PickNpcWeapon(RwInt32 *pnAll)
{
    RwInt32 k, nWeapon = -1;

    *pnAll = 0;
    for (k = 0; k < 128; k++)
    {
        type_3DF8D8 *pDef;

        if (!dword_4D53F8[k].unk_48.unk_00 && !dword_4D53F8[k].unk_48.unk_04)
            continue;
        (*pnAll)++;
        __try
        {
            pDef = sub_198800(&dword_4D53F8[k].unk_48);
            if (pDef == NULL || pDef->vf_008() != 26 || !definition_model(pDef))
                continue;
            if (dword_4D53F8[k].unk_74 && sub_198800(&dword_4D53F8[k].unk_58) == NULL)
                continue;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            continue;
        }
        if (nWeapon < 0)
            nWeapon = k;
    }
    return nWeapon;
}

// (nonzero: the side SpawnAiSoldierMp gives the soldier, the bots')
static RwUInt32 s_dwSpawnSide;

static type_3D3548 *SpawnAiSoldierMp(SoldierTrigger *pTrigger)
{
    type_3DF8D8 *pDef = sub_198800(&pTrigger->unk_D8);
    type_1917A0 *pChar;
    type_3DAFC8 *pSoldier;
    void *p;

    if (pDef == NULL || pDef->vf_008() != 4)
    {
        strcpy(s_szReqResult, "the trigger's soldier definition is not loaded");
        return NULL;
    }
    pChar = (type_1917A0 *)pDef;
    if (!pChar->sub_1917A0() || !pChar->sub_1917F0())
    {
        strcpy(s_szReqResult, "the trigger's soldier definition has no body or head");
        return NULL;
    }
    if (dword_4B83A0[6].unk_00 < 0x2170 || (p = dword_4B83A0[6].sub_D65C0()) == NULL)
    {
        strcpy(s_szReqResult, "no entity memory left in the soldiers' pool (6)");
        return NULL;
    }
    // (its weapon: the trigger's weapon type, unk_130, an index into the NPC weapons
    // (dword_4D53F8, by the weapon's key; SoldierTrigger's command 38). The network player's
    // trigger has none (players take a loadout): CODFH_SPAWNAI_WEAPON's index, else the first
    // NPC weapon this level has, for the soldier's making only)
    RwInt32 nOldWeapon = pTrigger->unk_130, nWeapon = -1, nWeapons = 0;
    RwChar szWeapon[16];

    nWeapon = PickNpcWeapon(&nWeapons);
    if (GetEnvironmentVariableA("CODFH_SPAWNAI_WEAPON", szWeapon, sizeof(szWeapon)))
        nWeapon = atoi(szWeapon);
    plog("spawn: %d NPC weapons in this level; the soldier gets weapon type %d (the trigger's %d; -1: none with its "
         "model read)", nWeapons, nWeapon, nOldWeapon);
    if (!valid_weapon_type(nOldWeapon) && valid_weapon_type(nWeapon))
        pTrigger->unk_130 = nWeapon;
    // (its brain single player's: the soldier class every single player soldier trigger names
    // (command 7: F19B8E76,A9A821C0), read from L_1_1_B's god data when this level lacks it
    // (ForeignRead, CODFH_SPAWNAI_LEVEL), made the trigger's class (unk_E0) for the soldier's
    // making, so its set-up starts it (sub_70E10) and registers it with the vision, distance and
    // other schedulers, as a single player soldier's is; started after, those keep the class it
    // replaced)
    type_3DF8D8_04 oldClass = pTrigger->unk_E0;
    {
        type_3DF8D8_04 key;
        RwChar szLevel[32];

        key.unk_00 = (RwInt32)0xF19B8E76; // not an address: a god key
        key.unk_04 = (RwInt32)0xA9A821C0; // not an address: a god key
        if (!GetEnvironmentVariableA("CODFH_SPAWNAI_LEVEL", szLevel, sizeof(szLevel)))
            strcpy(szLevel, "L_1_1_B");
        if (ForeignRead(szLevel, &key, 0xA))
            pTrigger->unk_E0 = key;
        else
            plog("spawn: single player's soldier class is not there; the soldier keeps the network player's");
    }
    dword_429264 = 6;
    pSoldier = new (p) type_3DAFC8(pTrigger);
    pTrigger->unk_130 = nOldWeapon;
    pTrigger->unk_E0 = oldClass;
    TrigAddAiSoldier(pSoldier);
    if (pSoldier->unk_28 & 0x400000) // not an address: entity flag
    {
        sub_D5A60(pSoldier, 0);
        strcpy(s_szReqResult, "the soldier removed itself as it was made");
        return NULL;
    }
    // (its side the other one to the local player's: a bullet harms only an entity of another
    // side than the bullet's, its shooter's, unless friendly fire is on (sub_15F1B0's
    // get_unk_2C_side test); the network player's trigger may give the soldier the player's own)
    {
        type_3D3548 *pPlayer = sub_1745A0(0);
        RwUInt32 dwMine = pPlayer ? (pPlayer->unk_2C & 7) : 1;
        RwUInt32 dwTheirs = s_dwSpawnSide ? s_dwSpawnSide : dwMine == 2 ? 1 : 2;

        pSoldier->unk_2C = (pSoldier->unk_2C & ~7u) | dwTheirs;
        plog("spawn: the player's side %u; the soldier's %u", dwMine, dwTheirs);
    }
    return pSoldier;
}
#endif

static type_3D3548 *SpawnSoldierAt(Trigger *pTrigger, const RwV3d *pv)
{
    RwV3d vPlace, vMatrix;
    RwUInt32 bFree;
    type_3D3548 *pSoldier = NULL;

    vPlace.x = pTrigger->unk_90;
    vPlace.y = pTrigger->unk_94;
    vPlace.z = pTrigger->unk_98;
    vMatrix = pTrigger->unk_60_m.pos;
    bFree = pTrigger->unk_24_18;
    pTrigger->unk_90 = pv->x;
    pTrigger->unk_94 = pv->y;
    pTrigger->unk_98 = pv->z;
    pTrigger->unk_60_m.pos = *pv;
    pTrigger->unk_24_18 = 1;
    __try
    {
#ifndef CODFH_SP
        if ((void *)pTrigger == (void *)dword_4F8134)
            pSoldier = SpawnAiSoldierMp((SoldierTrigger *)pTrigger);
        else
#endif
            pSoldier = pTrigger->vf_020();
    }
    __except (SpawnFaultFilter(GetExceptionInformation()))
    {
        pSoldier = NULL;
        SpawnFaultText();
    }
    pTrigger->unk_90 = vPlace.x;
    pTrigger->unk_94 = vPlace.y;
    pTrigger->unk_98 = vPlace.z;
    pTrigger->unk_60_m.pos = vMatrix;
    pTrigger->unk_24_18 = bFree;
    return pSoldier;
}

// "Spawn a soldier": trigger handle n, or with n -1 each soldier trigger in
// turn, nearest the place first, until one spawns.
static void SpawnSoldier(RwInt32 n, const RwV3d *pv)
{
    RwInt32 i, nLast = dword_429D00, nBest;
    RwReal fBest, fDist;
    Trigger *pTrigger;
    type_3D3548 *pSoldier = NULL;
    static RwUInt8 s_abTried[2000];

    s_szReqResult[0] = 0;
    if (nLast >= 2000)
        nLast = 1999;
    if (n >= 0)
    {
        pTrigger = n < 2000 ? (Trigger *)dword_4CFE30[n] : NULL;
        if (pTrigger == NULL || pTrigger->vf_008() != 5)
        {
            sprintf(s_szReqResult, "trigger %d is not a soldier trigger", n);
            return;
        }
        pSoldier = SpawnSoldierAt(pTrigger, pv);
    }
    else
    {
        memset(s_abTried, 0, sizeof(s_abTried));
        for (;;)
        {
            nBest = -1;
            fBest = 1e30f;
            for (i = 0; i <= nLast; i++)
            {
                pTrigger = (Trigger *)dword_4CFE30[i];
                if (pTrigger == NULL || s_abTried[i] || pTrigger->vf_008() != 5)
                    continue;
                fDist = (pTrigger->unk_90 - pv->x) * (pTrigger->unk_90 - pv->x)
                        + (pTrigger->unk_98 - pv->z) * (pTrigger->unk_98 - pv->z);
                if (fDist < fBest)
                {
                    fBest = fDist;
                    nBest = i;
                }
            }
            if (nBest < 0)
                break;
            s_abTried[nBest] = 1;
            pSoldier = SpawnSoldierAt((Trigger *)dword_4CFE30[nBest], pv);
            if (pSoldier)
            {
                n = nBest;
                break;
            }
        }
    }
    if (pSoldier)
    {
        RwUInt32 dwBits = 0;
        RwBool bAi = FALSE;

        __try
        {
            dwBits = pSoldier->unk_2C;
            bAi = pSoldier->vf_120() != NULL;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        sprintf(s_szReqResult, "spawned a soldier from trigger %d at %.1f, %.1f, %.1f (%s, %s)", n, pv->x, pv->y, pv->z,
                bAi ? "with its AI" : "no AI", (dwBits & 2) ? "enemy" : (dwBits & 1) ? "ally" : "no side");
    }
    else if (!s_szReqResult[0])
        strcpy(s_szReqResult, n >= 0 ? "no soldier: its definition is not loaded, or no entity memory"
                                     : "no soldier trigger on this map could spawn one");
}

// The player's own trigger (a PlayerTrigger, kind 1, as player set-up finds
// it: sub_10D8A0), or NULL.
static PlayerTrigger *OwnPlayerTrigger(type_10F710 *pPlayer)
{
    Trigger *pTrigger = (Trigger *)pPlayer->unk_344.unk_08;

    if (pTrigger == NULL || pTrigger->vf_008() != 1)
        return NULL;
    return (PlayerTrigger *)pTrigger;
}

// Whether weapon w has a handheld model once its bank is loaded: its
// definition (kind 5, sub_198800 of its settings' key) and the model that
// definition names (sub_18F800), as the copy's vf_008 finds them before it
// clones the model. Mounted and vehicle weapons can lack one; giving such a
// weapon clones NULL (RpClumpClone in sub_10E9D0).
static RwBool HasHandheldModel(RwInt32 w)
{
    __try
    {
        type_495F0 *pDef = (type_495F0 *)sub_198800(&dword_4C19C0[w].unk_00);

        if (pDef == NULL || pDef->vf_008() != 5)
            return FALSE;
        return pDef->sub_18F800(&pDef->unk_20) != 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// Whether weapon w is a throwable or a mine, which the inventory gives.
static RwBool IsThrowable(RwInt32 w)
{
    return w == 19 || w == 20 || w == 21 || w == 22 || w == 31 || w == 33 || w == 34 || w == 38;
}

// The inventory kind of throwable w, as the player's checkpoint restore
// maps them (unit_0FD730's loadout switch); -1 for the others.
static RwInt32 InventoryKind(RwInt32 w)
{
    switch (w)
    {
    case 21:
        return 2;
    case 33:
        return 7;
    case 31:
        return 5;
    case 20:
        return 8;
    case 22:
        return 9;
    case 19:
        return 10;
    case 34:
        return 11;
    case 38:
        return 12;
    }
    return -1;
}

// A bank slot to stream a weapon into, -1 for none: one no model in use
// comes from. The player's own choice (sub_10E930) spares only the two held
// weapons' slots; a given grenade in hand, or one whose model is attached,
// is in neither, and streaming over its slot frees the model it is drawing
// with (a crash in RpGeometryDestroy's resource free).
static RwInt32 FreeBankSlot(type_10F710 *pPlayer)
{
    RwBool abUsed[3] = { FALSE, FALSE, FALSE };
    RwInt32 i, nSlot;

    for (i = 0; i < 39; i++)
    {
        if (pPlayer->unk_1A48[i] == NULL)
            continue;
        if (i != pPlayer->unk_1AE4 && i != pPlayer->unk_1B30[0] && i != pPlayer->unk_1B30[1]
            && !pPlayer->unk_1A48[i]->get_unk_41E())
            continue;
        nSlot = sub_16F860(dword_4C19C0[i].unk_24);
        if (nSlot >= 0 && nSlot < 3)
            abUsed[nSlot] = TRUE;
    }
    for (i = 0; i < 3; i++)
    {
        if (!abUsed[i])
            return i;
    }
    return -1;
}

// Gives 5 of throwable w and selects it: grenades and mines are inventory
// items ("GivePlayerInventoryItem"), thrown through their weapon copy.
static void GiveThrowable(type_10F710 *pPlayer, RwInt32 w)
{
    RwInt32 nKind = InventoryKind(w);

    sprintf(s_szReqResult, "gave 5 %s (inventory kind %d, now %d)", off_429768[w], nKind,
            pPlayer->unk_21B4.sub_116080(nKind, 5));
    pPlayer->unk_21B4.sub_115980(nKind);
    // (the throw, type_3DA5A0::vf_018, refuses while its copy has no rounds
    // in reserve and its settings have a most; the inventory count is apart)
    if (pPlayer->unk_1A48[w] && pPlayer->unk_1A48[w]->unk_418 <= 0)
        pPlayer->unk_1A48[w]->unk_418 = dword_4C19C0[w].unk_CC > 0 ? dword_4C19C0[w].unk_CC : 1;
}

// Starts giving weapon w the way the scripts do ("RequestToStreamPlayerWeapon",
// "IsPlayerWeaponStreamed", "SetPlayerWeapon"): its bank first when it is
// not loaded, into the slot neither held weapon uses (sub_10E930), so no
// held weapon loses its model; TickGive gives it once loaded.
static void StartGive(type_10F710 *pPlayer, RwInt32 w, RwInt32 nSlot, RwBool bKeep)
{
    if (w < 0 || w >= 39)
    {
        strcpy(s_szReqResult, "no such weapon");
        return;
    }
    if (dword_4C19C0[w].unk_24 == -1)
    {
        sprintf(s_szReqResult, "%s has no weapon bank assigned (the level has not started?)", off_429768[w]);
        return;
    }
    if ((w >= 23 && w <= 30) || w == 35 || w == 36)
    {
        // (the mounted guns' banks are stubs with no model, and the tank guns'
        // copies, type_3DA558, update as part of a vehicle: given to the player
        // on foot, vf_018 writes through a NULL vehicle in sub_8F140)
        sprintf(s_szReqResult, "refused %s: a mounted or vehicle weapon, which only works from its mount",
                off_429768[w]);
        return;
    }
    if (IsThrowable(w) && pPlayer->unk_1A48[w] && pPlayer->unk_1A48[w]->get_unk_41E())
    {
        // (its model is on the player already: only the count)
        GiveThrowable(pPlayer, w);
        return;
    }
    if (s_nGiveWeapon != -1)
    {
        sprintf(s_szReqResult, "already giving %s", off_429768[s_nGiveWeapon]);
        return;
    }
    s_nGiveWeapon = w;
    s_nGiveSlot = nSlot;
    s_bGiveKeep = bKeep;
    s_nGiveFrames = 0;
    if (!pPlayer->sub_10E8C0(w))
    {
        RwInt32 nFree = FreeBankSlot(pPlayer);

        if (nFree < 0)
        {
            sprintf(s_szReqResult, "refused %s: all three bank slots hold a model in use (the held weapons, the "
                    "one in hand or a grenade); drop one first", off_429768[w]);
            s_nGiveWeapon = -1;
            return;
        }
        pPlayer->unk_2134 = nFree;
        pPlayer->unk_2138 = 1;
        pPlayer->sub_10DA70(w);
        sprintf(s_szReqResult, "streaming %s (wbank_%02d.bin) into bank slot %d...", off_429768[w],
                dword_4C19C0[w].unk_24, pPlayer->unk_2134);
    }
    else
        sprintf(s_szReqResult, "%s's bank is loaded; giving", off_429768[w]);
}

// Each frame: once the weapon being given has its bank, gives it (with
// selecting) into its slot with a full clip and reserve, and records it in
// the player's trigger when kept; gives up after TRIGWEB_GIVE_TIMEOUT frames.
static void TickGive()
{
    type_10F710 *pPlayer;
    type_4C19C0 *pSettings;
    PlayerTrigger *pTrigger;
    RwInt32 w = s_nGiveWeapon, i;

    if (w == -1)
        return;
    pPlayer = (type_10F710 *)sub_1745A0(0);
    if (pPlayer == NULL)
    {
        strcpy(s_szReqResult, "give cancelled: no local player");
        s_nGiveWeapon = -1;
        return;
    }
    if (!pPlayer->sub_10E8C0(w))
    {
        if (++s_nGiveFrames > TRIGWEB_GIVE_TIMEOUT)
        {
            sprintf(s_szReqResult, "gave up on %s: its bank did not load", off_429768[w]);
            s_nGiveWeapon = -1;
        }
        return;
    }
    // (with its bank loaded, the model must resolve, or the give clones NULL)
    if (!HasHandheldModel(w))
    {
        sprintf(s_szReqResult, "refused %s: its bank is loaded but it has no handheld model "
                "(a mounted or vehicle weapon?)", off_429768[w]);
        s_nGiveWeapon = -1;
        return;
    }
    if (IsThrowable(w))
    {
        // (as the player's step readies a weapon it streamed: the model
        // onto its copy, which lets it be thrown, and the bank slot kept)
        if (pPlayer->unk_1A48[w] == NULL)
        {
            sprintf(s_szReqResult, "refused %s: the player has no copy of it", off_429768[w]);
            s_nGiveWeapon = -1;
            return;
        }
        if (!pPlayer->unk_1A48[w]->get_unk_41E())
        {
            pPlayer->unk_1A48[w]->vf_008(pPlayer, pPlayer->unk_1A3C.get_unk_08(), w);
            set_bank_state(pPlayer->unk_2134, 1, 1);
        }
        GiveThrowable(pPlayer, w);
        s_nGiveWeapon = -1;
        return;
    }
    // ("SetPlayerWeapon": slot 0 the hand's, 1 the other; selected)
    pPlayer->sub_10E9D0(w, 1, s_nGiveSlot);
    pSettings = &dword_4C19C0[w];
    if (pPlayer->unk_1A48[w])
    {
        pPlayer->unk_1A48[w]->unk_414 = pSettings->unk_C8;
        pPlayer->unk_1A48[w]->unk_418 = pSettings->unk_CC;
    }
    sprintf(s_szReqResult, "gave %s (after %d frames)", off_429768[w], s_nGiveFrames);
    if (s_bGiveKeep && (pTrigger = OwnPlayerTrigger(pPlayer)) != NULL)
    {
        // (what a checkpoint restart rebuilds the loadout from: its two
        // weapons, the ones it has, their rounds)
        for (i = 0; i < 2; i++)
            pTrigger->unk_108[i] = pPlayer->unk_1B30[i];
        pTrigger->unk_114[w] = 1;
        pTrigger->unk_384[w] = pSettings->unk_CC;
        strcat(s_szReqResult, "; kept in the player's trigger");
    }
    s_nGiveWeapon = -1;
}

// ---- Cheats ----

// The developers' switches left in the game with nothing that sets them
// (each only zeroed at a reset), and the debug menu's: kept on each frame
// here, as the resets would clear them.
//   byte_4C1940  the AI's target filter (sub_3DE00) refuses players: the AI
//                ignores you (zeroed at the player's reset)
//   byte_4F28F8  the player's bullet and explosion damage (vf_064, vf_068)
//                takes no health ("Invulnerability"; zeroed at set-up)
//   dword_4C19AC the player's weapons spend no rounds (the debug menu's
//                "Unlimited Ammo"; zeroed at the player's reset)
static RwBool s_bCheatIgnoreMe, s_bCheatGod, s_bCheatAmmo, s_bCheatFreezeAi;

// The AI control (AIData::unk_51C, "SetAIControl") of the AIs frozen, to
// put back: the AI data and its value.
struct CheatFrozen
{
    AIData *pAi;
    RwInt32 nControl;
};
static CheatFrozen s_aCheatFrozen[768];
static RwInt32 s_nCheatFrozen;

static void CheatFreezeTick()
{
    RwInt32 i, j;

    if (!s_bCheatFreezeAi)
    {
        // thaw: each frozen AI gets its control back, if it still has the 0 we gave it
        for (j = 0; j < s_nCheatFrozen; j++)
            __try
            {
                if (s_aCheatFrozen[j].pAi->unk_51C == 0)
                    s_aCheatFrozen[j].pAi->unk_51C = s_aCheatFrozen[j].nControl;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        s_nCheatFrozen = 0;
        return;
    }
    for (i = 0; i < 768; i++)
    {
        type_3D3548 *pEntity = dword_4B6A00[i].unk_04;
        AIData *pAi;

        if (pEntity == NULL || (pEntity->unk_2C & 0x10))
            continue;               // (players)
        __try
        {
            pAi = pEntity->vf_120();
            if (pAi == NULL || pAi->unk_51C == 0)
                continue;
            for (j = 0; j < s_nCheatFrozen && s_aCheatFrozen[j].pAi != pAi; j++)
                ;
            if (j == s_nCheatFrozen && s_nCheatFrozen < 768)
            {
                s_aCheatFrozen[s_nCheatFrozen].pAi = pAi;
                s_aCheatFrozen[s_nCheatFrozen].nControl = pAi->unk_51C;
                s_nCheatFrozen++;
            }
            pAi->unk_51C = 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
}

static void CheatTick()
{
    static RwInt32 s_nGodStart = -1;

    // (CODFH_GOD=1: god mode from the start)
    if (s_nGodStart < 0)
    {
        s_nGodStart = 0;
        if (GetEnvironmentVariableA("CODFH_GOD", NULL, 0))
            s_bCheatGod = TRUE;
    }
    if (s_bCheatIgnoreMe)
        byte_4C1940 = 1;
    if (s_bCheatGod)
    {
        type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);

        byte_4F28F8 = 1;
        // (falls too: the game's god mode spares only bullets and explosions; a fall kills
        // through its height, unk_510, and its time in the air, unk_518, type_10F710::vf_044)
        if (pPlayer)
        {
            __try
            {
                pPlayer->unk_510 = -1000000.0f;
                pPlayer->unk_518 = 0.0f;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
    }
    if (s_bCheatAmmo)
        dword_4C19AC = 1;
    if (s_bCheatFreezeAi || s_nCheatFrozen)
        CheatFreezeTick();
}

// Called each frame on the main thread (sub_D7880): carries out the pending
// action from a tab, and a weapon give in progress.
#ifdef CODFH_ALL_SECTIONS
static void AllSectionsTick();      // (below, with the Sections tab)
#endif

static void WaitsLogTick();
static void TrigMsgTick();
static void SpawnAiTestTick();
static void AutoSpawnTick();
static void PathsTick();
static void BotsTick();
static void LogSoldierTriggersTick();

void TrigWebTick()
{
    type_10F710 *pPlayer;
    RwV3d v;

    CheatTick();
    TickGive();
    TrigLiveTick();
    TrigRngFrame();
    WaitsLogTick();
    TrigMsgTick();
    PathsTick();
#ifndef CODFH_SP
    BotsTick();
#endif
    SpawnAiTestTick();
    AutoSpawnTick();
    LogSoldierTriggersTick();
#ifdef CODFH_ALL_SECTIONS
    AllSectionsTick();
#endif
    if (!s_bReqPending)
        return;
    pPlayer = (type_10F710 *)sub_1745A0(0);
    switch (s_nReqKind)
    {
    case REQ_SECTION:
        if (s_nReqA >= 0 && s_nReqA < 0xFFFF && s_nReqB >= 0 && s_nReqB < 4)
            LoadSection((RwUInt16)s_nReqA, s_nReqB);
        else
            sprintf(s_szReqResult, "bad section request (section %d, slot %d)", s_nReqA, s_nReqB);
        break;
    case REQ_TELEPORT:
        if (pPlayer == NULL)
        {
            strcpy(s_szReqResult, "no local player");
            break;
        }
        v.x = s_afReq[0];
        v.y = s_afReq[1];
        v.z = s_afReq[2];
        Teleport(pPlayer, &v);
        break;
    case REQ_HEAL:
        if (pPlayer == NULL)
        {
            strcpy(s_szReqResult, "no local player");
            break;
        }
        // (the player's "SetPlayerHealthPercentage")
        pPlayer->vf_23C(s_afReq[0]);
        sprintf(s_szReqResult, "health set to %.0f%%", s_afReq[0]);
        break;
    case REQ_GIVE:
        if (pPlayer == NULL || s_nReqA < 1 || s_nReqA > 12)
        {
            strcpy(s_szReqResult, "no local player, or a kind outside 1 to 12");
            break;
        }
        // (as "GivePlayerInventoryItem": adds, then selects)
        sprintf(s_szReqResult, "kind %d now %d", s_nReqA, pPlayer->unk_21B4.sub_116080(s_nReqA, s_nReqB));
        pPlayer->unk_21B4.sub_115980(s_nReqA);
        break;
    case REQ_AMMO:
        if (pPlayer == NULL || s_nReqA < 0 || s_nReqA >= 39 || pPlayer->unk_1A48[s_nReqA] == NULL)
        {
            strcpy(s_szReqResult, "no local player, or no such weapon");
            break;
        }
        pPlayer->unk_1A48[s_nReqA]->unk_418 = s_nReqB;
        sprintf(s_szReqResult, "weapon %d: %d rounds in reserve", s_nReqA, s_nReqB);
        break;
    case REQ_GIVEWEAPON:
        if (pPlayer == NULL)
        {
            strcpy(s_szReqResult, "no local player");
            break;
        }
        StartGive(pPlayer, s_nReqA, s_nReqB & 1, (s_nReqB & 2) != 0);
        break;
    case REQ_SPAWNSOLDIER:
        if (pPlayer == NULL || !PlayerPosition(pPlayer, &v))
        {
            strcpy(s_szReqResult, "no local player");
            break;
        }
        // (4 m ahead of the camera, level, at the player's height)
        if (dword_4E5C74)
        {
            RwMatrix *pLtm = RwFrameGetLTM(RwCameraGetFrame((RwCamera *)dword_4E5C74));
            RwReal fLen = (RwReal)sqrt(pLtm->at.x * pLtm->at.x + pLtm->at.z * pLtm->at.z);

            if (fLen > 0.01f)
            {
                v.x += pLtm->at.x / fLen * 4.0f;
                v.z += pLtm->at.z / fLen * 4.0f;
            }
        }
        if (!GroundBelow(&v))
        {
            strcpy(s_szReqResult, "no floor below the spot ahead of the player");
            break;
        }
        SpawnSoldier(s_nReqA, &v);
        break;
    case REQ_SETHP:
    {
        type_3D3548 *pEntity = s_nReqA >= 0 && s_nReqA < 768 ? dword_4B6A00[s_nReqA].unk_04 : NULL;

        if (pEntity == NULL)
        {
            strcpy(s_szReqResult, "no entity in that slot");
            break;
        }
        // (the entity's own setter: 0 or less starts its death)
        pEntity->vf_178(s_nReqB);
        sprintf(s_szReqResult, "entity %d: hit points set to %d", s_nReqA, s_nReqB);
        break;
    }
    case REQ_PG:
    {
        type_1227C0 *pGen = sub_1227C0(s_nReqA);
        static const RwChar *const s_apszDone[9] = {"started", "stopped", "fired", "targets you",
                                                    "back on its default target", "line of sight check on",
                                                    "line of sight check off", "firing stages on",
                                                    "firing stages off"};

        if (pGen == NULL)
        {
            sprintf(s_szReqResult, "no projectile generator %d now", s_nReqA & 0xFFFF);
            break;
        }
        switch (s_nReqB)
        {
        case PG_START:
            pGen->sub_121D20(1);
            break;
        case PG_STOP:
            pGen->sub_121D20(0);
            break;
        case PG_FIRE:
            pGen->sub_120150();
            break;
        case PG_TARGETME:
            if (pPlayer == NULL || !PlayerPosition(pPlayer, &v))
            {
                strcpy(s_szReqResult, "no local player");
                s_bReqPending = FALSE;
                return;
            }
            pGen->sub_1218A0(&v, pGen->unk_60);
            break;
        case PG_TARGETDEFAULT:
            pGen->sub_121870();
            break;
        case PG_LOSON:
        case PG_LOSOFF:
            pGen->vf_014(s_nReqB == PG_LOSON);
            break;
        case PG_STAGESON:
        case PG_STAGESOFF:
            pGen->sub_121A30(s_nReqB == PG_STAGESON);
            break;
        default:
            strcpy(s_szReqResult, "unknown generator action");
            s_bReqPending = FALSE;
            return;
        }
        sprintf(s_szReqResult, "generator %d %s", s_nReqA & 0xFFFF, s_apszDone[s_nReqB]);
        break;
    }
    default:
        strcpy(s_szReqResult, "unknown action");
    }
    s_bReqPending = FALSE;
}

// ---- Drawing ----

// Set to open or close the game's debug menu (unk_4E73A8): its update
// (sub_183840) toggles it on the main thread.
RwInt32 g_nTrigWebDebugMenuToggle;

static void Check(const RwChar *pszLabel, RwBool *pb)
{
    bool b = *pb != 0;

    if (ImGui::Checkbox(pszLabel, &b))
        *pb = b;
}

// The cheat flags (dword_4B8888's word, game/cheats.h), by bit.
static const RwChar *const s_apszCheatBits[7] =
{
    "soldiers' second animation at double speed",
    "projectiles bounce (bit 1)",
    "bullets kill with a head shot, and do nothing otherwise",
    "projectiles bounce (bit 3)",
    "soldiers shrink with their hit points",
    "bullets kill",
    "soldiers drawn smaller, at random",
};

static void CheckSet(const RwChar *pszLabel, RwBool *pb, RwBool bOff, void (*pfnOff)())
{
    bool b = *pb != 0;

    if (ImGui::Checkbox(pszLabel, &b))
    {
        *pb = b;
        if (!b && pfnOff)
            pfnOff();
    }
}

static void CheatIgnoreOff()
{
    byte_4C1940 = 0;
}

static void CheatGodOff()
{
    byte_4F28F8 = 0;
}

static void CheatAmmoOff()
{
    dword_4C19AC = 0;
}

static void CheatsLevelRender();
static void CheatsAudio();

static void TabCheats()
{
    RwInt32 i;

    ImGui::SeparatorText("The developers' switches (nothing in the game sets them)");
    CheckSet("the AI ignores me (byte_4C1940: their target filter refuses players)", &s_bCheatIgnoreMe, FALSE,
             CheatIgnoreOff);
    CheckSet("god mode (byte_4F28F8: bullets and explosions take no health; the port adds falls)", &s_bCheatGod, FALSE, CheatGodOff);
    {
        bool b = RWS::DebugSwitches::GetSwitch(0x15);

        if (ImGui::Checkbox("no AI spawns (debug switch 0x15: the scripts' CreateSoldier and CreateTank)", &b))
            RWS::DebugSwitches::SetSwitch(0x15, b);
    }
    if (ImGui::Button("skip to the next level (byte_4C1941)"))
    {
        byte_4C1941 = 1;
        strcpy(s_szReqResult, "the main loop goes to the next level");
    }
    ImGui::SameLine();
    if (ImGui::Button("reset the tanks (dword_4D50F8)"))
    {
        dword_4D50F8 = 2;
        strcpy(s_szReqResult, "tanks put back over their triggers, their motion cleared");
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(each tank 100 above its trigger, stopped)");

    ImGui::SeparatorText("The AI");
    CheckSet("freeze all AI (clears each AI's AI control, SetAIControl; put back when off)", &s_bCheatFreezeAi,
             FALSE, NULL);
    ImGui::SameLine();
    ImGui::TextDisabled("%d frozen", s_nCheatFrozen);
    ImGui::TextDisabled("(AI control off makes their checks pass over them; scripted moves may still play)");

    ImGui::SeparatorText("The debug menu's");
    CheckSet("unlimited ammunition (dword_4C19AC)", &s_bCheatAmmo, FALSE, CheatAmmoOff);
    ImGui::SetNextItemWidth(240.0f);
    ImGui::SliderFloat("game speed (flt_429298)", &flt_429298, 0.05f, 4.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
    ImGui::SameLine();
    if (ImGui::SmallButton("1"))
        flt_429298 = 1.0f;

    ImGui::SeparatorText("Cheat flags (dword_4B8888)");
    if (dword_4B8888 == NULL)
        ImGui::TextDisabled("Not set up yet (a level sets the pointer).");
    else
    {
        RwUInt32 *pdw = (RwUInt32 *)dword_4B8888;
        RwUInt32 dw;

        if (!ReadU32(pdw, &dw))
            ImGui::Text("0x%08X can't be read.", (RwUInt32)pdw);
        else
        {
            for (i = 0; i < 7; i++)
            {
                bool b = ((dw >> i) & 1) != 0;

                if (ImGui::Checkbox(s_apszCheatBits[i], &b))
                {
                    dw = b ? dw | (1u << i) : dw & ~(1u << i);
                    *pdw = dw;
                }
            }
            ImGui::TextDisabled("at 0x%08X (single player: the save's cheats; they stay as set)", (RwUInt32)pdw);
        }
    }
}

// The collision's material kinds near the camera (trigcoll.h): tick kinds to draw only those,
// as the invisible blockers (untextured, or flagged).
static void CollisionKinds()
{
    RwInt32 i, nShown = 0;

    if (!ImGui::TreeNode("collision kinds (draw only the ticked ones)"))
        return;
    if (!g_bTrigDrawCollision)
        ImGui::TextDisabled("(drawing the collision fills this table)");
    for (i = 0; i < g_nTrigDrawCollKinds; i++)
        nShown += g_aTrigDrawCollKinds[i].bShow ? 1 : 0;
    ImGui::Text("%d kinds, %d ticked: %s", g_nTrigDrawCollKinds, nShown,
                nShown ? "only the ticked kinds are drawn" : "every kind is drawn");
    if (ImGui::SmallButton("untick all"))
        for (i = 0; i < g_nTrigDrawCollKinds; i++)
            g_aTrigDrawCollKinds[i].bShow = FALSE;
    ImGui::SameLine();
    if (ImGui::SmallButton("tick the untextured"))
        for (i = 0; i < g_nTrigDrawCollKinds; i++)
            g_aTrigDrawCollKinds[i].bShow = g_aTrigDrawCollKinds[i].szTexture[0] == 0;
    ImGui::SameLine();
    if (ImGui::SmallButton("tick the flagged"))
        for (i = 0; i < g_nTrigDrawCollKinds; i++)
            g_aTrigDrawCollKinds[i].bShow = (g_aTrigDrawCollKinds[i].dwTag & 0xFFFF0000) != 0;
    ImGui::SameLine();
    if (ImGui::SmallButton("forget the kinds"))
        TrigDrawCollKindsClear();
    Check("colour by kind (not by facing)", &g_bTrigDrawCollByKind);
    ImGui::SameLine();
    {
        static const char *const s_apszFill[] = { "filled", "outlines", "filled and outlined" };

        ImGui::SetNextItemWidth(170.0f);
        ImGui::Combo("drawn as", &g_nTrigDrawCollFill, s_apszFill, 3);
    }
    if (g_nTrigDrawCollFill != 0)
    {
        ImGui::SetNextItemWidth(240.0f);
        ImGui::SliderFloat("outline grid every (units, 0 edges only)", &g_fTrigDrawCollGrid, 0.0f, 512.0f, "%.0f",
                           ImGuiSliderFlags_Logarithmic);
    }
    if (ImGui::BeginTable("collkinds", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY
                                              | ImGuiTableFlags_Resizable | ImGuiTableFlags_Sortable,
                          ImVec2(0.0f, 260.0f)))
    {
        static RwInt32 s_aOrder[TRIGDRAW_COLLKINDS];
        static RwInt32 s_nSortColumn = 4;
        static RwBool s_bSortDown = TRUE;
        RwInt32 n = g_nTrigDrawCollKinds, a, b;

        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("draw", ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("flags");
        ImGui::TableSetupColumn("surface");
        ImGui::TableSetupColumn("texture");
        ImGui::TableSetupColumn("triangles", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_PreferSortDescending);
        ImGui::TableSetupColumn("material colour");
        ImGui::TableSetupColumn("what the flags do", ImGuiTableColumnFlags_NoSort);
        ImGui::TableHeadersRow();
        if (ImGuiTableSortSpecs *pSort = ImGui::TableGetSortSpecs())
        {
            if (pSort->SpecsCount > 0)
            {
                s_nSortColumn = pSort->Specs[0].ColumnIndex;
                s_bSortDown = pSort->Specs[0].SortDirection == ImGuiSortDirection_Descending;
            }
        }
        for (a = 0; a < n; a++)
            s_aOrder[a] = a;
        // (a small insertion sort by the chosen column)
        for (a = 1; a < n; a++)
        {
            RwInt32 v = s_aOrder[a];

            for (b = a; b > 0; b--)
            {
                const TrigDrawCollKind *x = &g_aTrigDrawCollKinds[s_aOrder[b - 1]], *y = &g_aTrigDrawCollKinds[v];
                RwInt32 c = s_nSortColumn == 1 ? (RwInt32)(x->dwTag >> 16) - (RwInt32)(y->dwTag >> 16)
                          : s_nSortColumn == 2 ? (RwInt32)(x->dwTag & 0xFFFF) - (RwInt32)(y->dwTag & 0xFFFF)
                          : s_nSortColumn == 3 ? strcmp(x->szTexture, y->szTexture)
                          : s_nSortColumn == 5 ? (x->dwRgba > y->dwRgba) - (x->dwRgba < y->dwRgba)
                          : x->nTriangles - y->nTriangles;
                if (s_bSortDown ? c >= 0 : c <= 0)
                    break;
                s_aOrder[b] = s_aOrder[b - 1];
            }
            s_aOrder[b] = v;
        }
        for (a = 0; a < n; a++)
        {
            TrigDrawCollKind *k = &g_aTrigDrawCollKinds[s_aOrder[a]];
            RwChar szWhat[128];
            RwUInt32 dwSurface = k->dwTag & 0xFFFF;

            ImGui::PushID(s_aOrder[a]);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            Check("##draw", &k->bShow);
            ImGui::SameLine();
            // (its colour when coloured by kind)
            ImGui::ColorButton("##kind", ImVec4(((k->dwDraw >> 16) & 0xFF) / 255.0f, ((k->dwDraw >> 8) & 0xFF) / 255.0f,
                                                (k->dwDraw & 0xFF) / 255.0f, 1.0f),
                               ImGuiColorEditFlags_NoTooltip, ImVec2(14.0f, 14.0f));
            ImGui::TableNextColumn();
            ImGui::Text("0x%04X", k->dwTag >> 16);
            ImGui::TableNextColumn();
            if (dwSurface == 0xFFFF)
                ImGui::TextDisabled("none");
            else
                ImGui::Text("%u", dwSurface);
            ImGui::TableNextColumn();
            if (k->szTexture[0])
                ImGui::TextUnformatted(k->szTexture);
            else
                ImGui::TextDisabled("(untextured)");
            ImGui::TableNextColumn();
            if (k->nTriangles)
                ImGui::Text("%d", k->nTriangles);
            else
                ImGui::TextDisabled("not near");
            ImGui::TableNextColumn();
            ImGui::ColorButton("##c", ImVec4((k->dwRgba >> 24) / 255.0f, ((k->dwRgba >> 16) & 0xFF) / 255.0f,
                                             ((k->dwRgba >> 8) & 0xFF) / 255.0f, (k->dwRgba & 0xFF) / 255.0f),
                               ImGuiColorEditFlags_NoTooltip, ImVec2(14.0f, 14.0f));
            ImGui::SameLine();
            ImGui::Text("%08X", k->dwRgba);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(TrigDrawCollFlagsText(k->dwTag, szWhat, sizeof(szWhat)));
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    ImGui::TreePop();
}

static void ViewTriggers()
{
    Check("draw the trigger volumes", &g_bTrigDrawEnabled);
    Check("through walls", &g_bTrigDrawSeeThrough);
    ImGui::SameLine();
    Check("labels (each trigger's type)", &g_bTrigDrawLabels);
    Check("names (the level's name for a trigger, above its type)", &g_bTrigDrawNames);
    ImGui::SliderFloat("trigger draw distance (0 unlimited)", &g_fTrigDrawRange, 0.0f, 1000.0f, "%.0f");
    ImGui::SliderFloat("label height (of the distance)", &g_fTrigDrawTextScale, 0.005f, 0.1f, "%.3f");
    ImGui::SeparatorText("Activity");
    Check("record and flash as they fire (green in, red out, white a message)", &g_bTrigDrawActivity);
    ImGui::SameLine();
    Check("only the ones that fired lately", &g_bTrigDrawActiveOnly);
    ImGui::SliderFloat("flash and messages stay (seconds)", &g_fTrigDrawActivitySecs, 0.5f, 20.0f, "%.1f");
    if (ImGui::TreeNode("the last events"))
    {
        RwInt32 i, nHandle, nKind;
        const RwChar *pszName;
        RwReal fAge;

        if (ImGui::SmallButton("clear##act"))
            TrigDrawActivityClear();
        for (i = 0; i < 40 && TrigDrawActivityEvent(i, &nHandle, &nKind, &pszName, &fAge); i++)
        {
            Trigger *pTrigger = (Trigger *)dword_4CFE30[nHandle];
            const RwChar *pszTrig = pTrigger ? TrigDrawTriggerName(pTrigger) : NULL;

            ImGui::Text("%5.1fs  %d %s: %s%s", fAge, nHandle, pszTrig ? pszTrig : (pTrigger ? TrigDrawKindName(pTrigger) : "?"),
                        nKind == 0 ? "entered" : nKind == 1 ? "left" : "sent ", nKind == 2 ? pszName : "");
        }
        ImGui::TreePop();
    }
}

static void EntityKind(RwUInt32 dwBits, RwChar *psz);

// ---- Speedrun: the random numbers, the frame timing ----

// The random numbers: who draws them, how many, the generators' state, and seeding.
static void ViewRng()
{
    static const RwChar *const s_apszGen[2] = { "RpRandom", "rand()" };
    static RwInt32 s_nSort;     // 0 by count, 1 by last frame
    static RwBool s_bOnlyPerFrame;
    RwInt32 i, k;

    Check("record the calls", &g_bTrigRngRecord);
    ImGui::SameLine();
    if (ImGui::Button("clear"))
        TrigRngReset();
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(the game never seeds its generators: RenderWare's RpRandom starts from 0x9A319039 when the "
                        "engine opens, rand() from 1. So what a run gets depends only on how many numbers were drawn "
                        "before; anything that draws every frame makes the frame rate change the outcome)");
    ImGui::PopTextWrapPos();
    if (ImGui::BeginTable("rngstate", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableSetupColumn("generator");
        ImGui::TableSetupColumn("state fingerprint");
        ImGui::TableSetupColumn("calls");
        ImGui::TableSetupColumn("since the restart");
        ImGui::TableSetupColumn("last frame");
        ImGui::TableSetupColumn("a second");
        ImGui::TableHeadersRow();
        for (k = 0; k < 2; k++)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(s_apszGen[k]);
            ImGui::TableNextColumn();
            ImGui::Text("%08X", TrigRngStateHash(k));
            ImGui::TableNextColumn();
            ImGui::Text("%u", g_anTrigRngTotal[k]);
            ImGui::TableNextColumn();
            ImGui::Text("%u", g_anTrigRngSinceRestart[k]);
            ImGui::TableNextColumn();
            ImGui::Text("%u", g_anTrigRngLastFrame[k]);
            ImGui::TableNextColumn();
            ImGui::Text("%.0f", g_afTrigRngPerSecond[k]);
        }
        ImGui::EndTable();
    }
    ImGui::TextDisabled("(the fingerprint changes with every number drawn; two runs with the same fingerprint at the "
                        "same point get the same numbers from there. %d restarts seen)", g_nTrigRngRestarts);

    ImGui::SeparatorText("Seeding");
    {
        static RwChar s_szSeed[16] = "12345";

        ImGui::SetNextItemWidth(140.0f);
        if (ImGui::InputText("seed (decimal, or 0x hex)", s_szSeed, sizeof(s_szSeed)))
            g_dwTrigRngSeed = (RwUInt32)strtoul(s_szSeed, NULL, 0);
        if (ImGui::Button("seed both now"))
            TrigRngSeedNow(g_dwTrigRngSeed);
        ImGui::SameLine();
        if (ImGui::Button("back to the game's own seeds"))
        {
            RwBool bRecord = g_bTrigRngRecord;

            g_bTrigRngRecord = FALSE;
            RpRandomSeed(0x9A319039u);
            srand(1);
            g_bTrigRngRecord = bRecord;
        }
        Check("reseed both at every restart (a level's start, a checkpoint, a death)", &g_bTrigRngSeedOnRestart);
        ImGui::PushTextWrapPos(0.0f);
        ImGui::TextDisabled("(for practice: every attempt from a checkpoint then starts from the same numbers, so the "
                            "same inputs give the same enemies, spreads and effects, as far as the frame timing is the "
                            "same too. Not for timed runs: the game itself never reseeds)");
        ImGui::PopTextWrapPos();
    }

    if (!g_bTrigRngRecord)
        return;
    ImGui::SeparatorText("Who draws them");
    ImGui::RadioButton("by calls", &s_nSort, 0);
    ImGui::SameLine();
    ImGui::RadioButton("by the last frame", &s_nSort, 1);
    ImGui::SameLine();
    Check("only those drawing every frame", &s_bOnlyPerFrame);
    {
        RwInt32 aOrder[TRIGRNG_CALLERS];
        RwInt32 n = 0;

        for (i = 0; i < g_nTrigRngCallers; i++)
            if (!s_bOnlyPerFrame || g_aTrigRngCallers[i].nLastFrame > 0)
                aOrder[n++] = i;
        // (a small insertion sort: at most 256)
        for (i = 1; i < n; i++)
        {
            RwInt32 v = aOrder[i], j = i - 1;
            RwUInt32 fv = s_nSort ? g_aTrigRngCallers[v].nLastFrame : g_aTrigRngCallers[v].nCount;

            while (j >= 0 && (s_nSort ? g_aTrigRngCallers[aOrder[j]].nLastFrame : g_aTrigRngCallers[aOrder[j]].nCount) < fv)
            {
                aOrder[j + 1] = aOrder[j];
                j--;
            }
            aOrder[j + 1] = v;
        }
        if (ImGui::BeginTable("rngcallers", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                              ImVec2(0.0f, 240.0f)))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("caller (the image's address in its name)");
            ImGui::TableSetupColumn("generator");
            ImGui::TableSetupColumn("calls");
            ImGui::TableSetupColumn("last frame");
            ImGui::TableHeadersRow();
            for (i = 0; i < n; i++)
            {
                TrigRngCaller *p = &g_aTrigRngCallers[aOrder[i]];

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::TextUnformatted(TrigRngCallerName(p));
                ImGui::TableNextColumn();
                ImGui::TextUnformatted(s_apszGen[p->nGen & 1]);
                ImGui::TableNextColumn();
                ImGui::Text("%u", p->nCount);
                ImGui::TableNextColumn();
                if (p->nLastFrame)
                    ImGui::Text("%u", p->nLastFrame);
                else
                    ImGui::TextDisabled("0");
            }
            ImGui::EndTable();
        }
    }
    if (ImGui::CollapsingHeader("the last calls"))
    {
        if (ImGui::BeginTable("rnglog", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                              ImVec2(0.0f, 220.0f)))
        {
            RwInt32 nShown = g_nTrigRngLogTotal < TRIGRNG_LOG ? (RwInt32)g_nTrigRngLogTotal : TRIGRNG_LOG;

            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("frame");
            ImGui::TableSetupColumn("generator");
            ImGui::TableSetupColumn("value");
            ImGui::TableSetupColumn("caller");
            ImGui::TableHeadersRow();
            for (i = 1; i <= nShown; i++)
            {
                const TrigRngCall *c = &g_aTrigRngLog[(g_nTrigRngLogNext + TRIGRNG_LOG - i) % TRIGRNG_LOG];
                TrigRngCaller *pName = NULL;

                for (k = 0; k < g_nTrigRngCallers; k++)
                    if (g_aTrigRngCallers[k].pAddr == c->pAddr && g_aTrigRngCallers[k].nGen == c->nGen)
                    {
                        pName = &g_aTrigRngCallers[k];
                        break;
                    }
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%u", c->dwFrame);
                ImGui::TableNextColumn();
                ImGui::TextUnformatted(s_apszGen[c->nGen & 1]);
                ImGui::TableNextColumn();
                ImGui::Text("%u", c->dwValue);
                ImGui::TableNextColumn();
                if (pName)
                    ImGui::TextUnformatted(TrigRngCallerName(pName));
                else
                    ImGui::Text("%p", c->pAddr);
            }
            ImGui::EndTable();
        }
    }
}

// The frame timing: game time against real time, the cap, the player's speed by each clock,
// the random numbers a frame; the frame cap set live and a table to compare frame rates.
static void ViewFrameRate()
{
    static float s_afPlot[TRIGFRAME_SAMPLES];
    RwInt32 nCap = port_get_max_fps(), i;

    Check("sample the frames", &g_bTrigFrameSample);
    if (!g_bTrigFrameSample)
    {
        ImGui::TextDisabled("(off: nothing is measured)");
        return;
    }
    ImGui::Text("%.1f fps; game time runs at %.3f of real time; %d of the last %d frames hit the cap", g_fTrigFrameFps,
                g_fTrigFrameGameOverReal, g_nTrigFrameCapped, g_nTrigFrameCount);
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(the game times a frame in 60ths of a second (deltaTime) and caps it at 5: below 12 fps the "
                        "game itself slows down. Movement that scales by deltaTime keeps the same speed a game second "
                        "at any frame rate; anything done once a frame, random numbers included, happens more often "
                        "at a higher one)");
    ImGui::PopTextWrapPos();

    ImGui::SeparatorText("Frame cap");
    {
        static const RwInt32 s_anCaps[6] = { 20, 30, 60, 120, 144, 0 };

        ImGui::Text("now: %s", nCap > 0 ? "" : "uncapped");
        if (nCap > 0)
        {
            ImGui::SameLine(0.0f, 0.0f);
            ImGui::Text("%d", nCap);
        }
        for (i = 0; i < 6; i++)
        {
            RwChar sz[16];

            if (i)
                ImGui::SameLine();
            if (s_anCaps[i])
                sprintf(sz, "%d##cap", s_anCaps[i]);
            else
                strcpy(sz, "uncapped##cap");
            if (ImGui::Button(sz))
                port_set_max_fps(s_anCaps[i]);
        }
        {
            int n = nCap;

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderInt("cap (0 uncapped)", &n, 0, 300))
                port_set_max_fps(n);
        }
        ImGui::TextDisabled("(for this session only; [video] max_fps in codfh.ini keeps one. With vsync on, the "
                            "display paces frames when it is no faster than the cap)");
    }

    ImGui::SeparatorText("The last frames");
    for (i = 0; i < g_nTrigFrameCount; i++)
        s_afPlot[i] = g_aTrigFrameSamples[(g_nTrigFrameNext + TRIGFRAME_SAMPLES - g_nTrigFrameCount + i) % TRIGFRAME_SAMPLES].fRealMs;
    ImGui::PlotLines("real ms", s_afPlot, g_nTrigFrameCount, 0, NULL, 0.0f, 100.0f, ImVec2(0.0f, 50.0f));
    for (i = 0; i < g_nTrigFrameCount; i++)
        s_afPlot[i] = g_aTrigFrameSamples[(g_nTrigFrameNext + TRIGFRAME_SAMPLES - g_nTrigFrameCount + i) % TRIGFRAME_SAMPLES].fRaw;
    ImGui::PlotLines("deltaTime before the cap", s_afPlot, g_nTrigFrameCount, 0, NULL, 0.0f, 6.0f, ImVec2(0.0f, 50.0f));
    for (i = 0; i < g_nTrigFrameCount; i++)
        s_afPlot[i] = g_aTrigFrameSamples[(g_nTrigFrameNext + TRIGFRAME_SAMPLES - g_nTrigFrameCount + i) % TRIGFRAME_SAMPLES].fSpeedGame;
    ImGui::PlotLines("speed a game second", s_afPlot, g_nTrigFrameCount, 0, NULL, 0.0f, FLT_MAX, ImVec2(0.0f, 50.0f));
    for (i = 0; i < g_nTrigFrameCount; i++)
        s_afPlot[i] = g_aTrigFrameSamples[(g_nTrigFrameNext + TRIGFRAME_SAMPLES - g_nTrigFrameCount + i) % TRIGFRAME_SAMPLES].fSpeedReal;
    ImGui::PlotLines("speed a real second", s_afPlot, g_nTrigFrameCount, 0, NULL, 0.0f, FLT_MAX, ImVec2(0.0f, 50.0f));
    if (g_bTrigRngRecord)
    {
        for (i = 0; i < g_nTrigFrameCount; i++)
        {
            const TrigFrameSample *f =
                &g_aTrigFrameSamples[(g_nTrigFrameNext + TRIGFRAME_SAMPLES - g_nTrigFrameCount + i) % TRIGFRAME_SAMPLES];

            s_afPlot[i] = (float)(f->anRng[0] + f->anRng[1]);
        }
        ImGui::PlotLines("random numbers a frame", s_afPlot, g_nTrigFrameCount, 0, NULL, 0.0f, FLT_MAX, ImVec2(0.0f, 50.0f));
    }
    else
        ImGui::TextDisabled("(turn on recording in the RNG view to plot the random numbers a frame)");

    ImGui::SeparatorText("Compare frame rates");
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(set a cap, do the same thing for a few seconds (run in a straight line, stand still in a "
                        "fight), then note it; repeat at another cap. Equal speed a game second and equal random numbers "
                        "a game second at every cap: the frame rate changes nothing there)");
    ImGui::PopTextWrapPos();
    if (ImGui::Button("note the last 240 frames"))
        TrigFrameNoteNow();
    ImGui::SameLine();
    if (ImGui::Button("clear the notes"))
        g_nTrigFrameNotes = 0;
    if (g_nTrigFrameNotes > 0 &&
        ImGui::BeginTable("framenotes", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit))
    {
        ImGui::TableSetupColumn("cap");
        ImGui::TableSetupColumn("fps");
        ImGui::TableSetupColumn("game/real");
        ImGui::TableSetupColumn("capped frames");
        ImGui::TableSetupColumn("speed/game s");
        ImGui::TableSetupColumn("speed/real s");
        ImGui::TableSetupColumn("RpRandom/game s");
        ImGui::TableSetupColumn("rand()/game s");
        ImGui::TableHeadersRow();
        for (i = 0; i < g_nTrigFrameNotes; i++)
        {
            const TrigFrameNote *n = &g_aTrigFrameNotes[i];

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (n->nMaxFps > 0)
                ImGui::Text("%d", n->nMaxFps);
            else
                ImGui::TextUnformatted("none");
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", n->fFps);
            ImGui::TableNextColumn();
            ImGui::Text("%.3f", n->fGameOverReal);
            ImGui::TableNextColumn();
            ImGui::Text("%d", n->nCapped);
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", n->fSpeedGame);
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", n->fSpeedReal);
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", n->afRngPerGameSecond[0]);
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", n->afRngPerGameSecond[1]);
        }
        ImGui::EndTable();
    }
}

// The collision's surfaces: the surface ids (the material extension's low word) of the kinds
// seen this frame, their triangles summed, each in its drawing colour.
static void CollisionSurfaces()
{
    struct Surface { RwInt32 nId, nTriangles, nKinds; };
    static Surface s_a[TRIGDRAW_COLLKINDS];
    RwInt32 n = 0, i, k;

    Check("colour by surface id", &g_bTrigDrawCollBySurface);
    ImGui::SameLine();
    ImGui::TextDisabled("(what footsteps, landings and impact effects look up; magenta: untagged)");
    for (i = 0; i < g_nTrigDrawCollKinds; i++)
    {
        RwInt32 nId = (RwInt32)(g_aTrigDrawCollKinds[i].dwTag & 0xFFFF);

        for (k = 0; k < n; k++)
            if (s_a[k].nId == nId)
                break;
        if (k == n)
        {
            if (n >= TRIGDRAW_COLLKINDS)
                continue;
            s_a[n].nId = nId;
            s_a[n].nTriangles = 0;
            s_a[n].nKinds = 0;
            n++;
        }
        s_a[k].nTriangles += g_aTrigDrawCollKinds[i].nTriangles;
        s_a[k].nKinds++;
    }
    if (!g_bTrigDrawCollBySurface || n == 0)
        return;
    if (ImGui::BeginTable("surfaces", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 180.0f)))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("surface id");
        ImGui::TableSetupColumn("triangles drawn");
        ImGui::TableSetupColumn("material kinds");
        ImGui::TableHeadersRow();
        for (i = 0; i < n; i++)
        {
            RwUInt32 dw = TrigDrawSurfaceColour(s_a[i].nId);

            ImGui::PushID(i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::ColorButton("##sc", ImVec4(((dw >> 16) & 0xFF) / 255.0f, ((dw >> 8) & 0xFF) / 255.0f,
                                              (dw & 0xFF) / 255.0f, 1.0f),
                               ImGuiColorEditFlags_NoTooltip, ImVec2(14.0f, 14.0f));
            ImGui::SameLine();
            if (s_a[i].nId == 0xFFFF)
                ImGui::TextUnformatted("untagged");
            else
                ImGui::Text("%d", s_a[i].nId);
            ImGui::TableNextColumn();
            ImGui::Text("%d", s_a[i].nTriangles);
            ImGui::TableNextColumn();
            ImGui::Text("%d", s_a[i].nKinds);
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
}

// The models: what each is and where it went (the game's atomic and clump extensions).
static void ViewModels()
{
    static const RwChar *const s_apszModes[3] = { "by section", "the collision skip flags", "by owner" };
    RwInt32 i;

    Check("draw the models", &g_bTrigDrawModels);
    ImGui::SameLine();
    Check("labels##models", &g_bTrigDrawModelLabels);
    for (i = 0; i < 3; i++)
    {
        if (i)
            ImGui::SameLine();
        ImGui::RadioButton(s_apszModes[i], &g_nTrigDrawModelMode, i + 1);
    }
    ImGui::SliderFloat("model draw distance (0 unlimited)", &g_fTrigDrawModelRange, 0.0f, 50000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    ImGui::PushTextWrapPos(0.0f);
    if (g_nTrigDrawModelMode == 1)
        ImGui::TextDisabled("(a ring under each model in its section slot's colour, from the clump's extension: where "
                            "the world manager placed it (sub_173080). White the global section, grey not placed)");
    else if (g_nTrigDrawModelMode == 2)
        ImGui::TextDisabled("(each atomic with a skip flag: orange bit 3, the line and sphere queries pass through it; "
                            "purple bit 4, the projectiles do; red both. Nothing in the recovered code sets them, so "
                            "any shown here were set by data)");
    else
        ImGui::TextDisabled("(a ring under each model in its owner's colour: green the player, blue soldiers, red "
                            "enemies, yellow pickups, white other entities, grey no owner)");
    ImGui::PopTextWrapPos();
    if (g_bTrigDrawModels || g_bTrigDrawInspect)
    {
        ImGui::Text("%d models; atomics skipping lines %d, skipping projectiles %d", g_nTrigDrawModels,
                    g_nTrigDrawModelsSkipLines, g_nTrigDrawModelsSkipShots);
        if (ImGui::BeginTable("modelslots", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit))
        {
            ImGui::TableSetupColumn("placed in");
            ImGui::TableSetupColumn("models");
            ImGui::TableHeadersRow();
            for (i = 0; i < SECTION_SLOTS + 2; i++)
            {
                RwInt32 nSection = i < SECTION_SLOTS ? (RwInt32)dword_4E5D30[i].unk_08 : 0;

                if (g_anTrigDrawModelsBySlot[i] == 0)
                    continue;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (i < SECTION_SLOTS)
                    ImGui::Text("slot %d (S_%d)", i, nSection);
                else
                    ImGui::TextUnformatted(i == SECTION_SLOTS ? "the global section" : "not placed");
                ImGui::TableNextColumn();
                ImGui::Text("%d", g_anTrigDrawModelsBySlot[i]);
            }
            ImGui::EndTable();
        }
    }

    ImGui::SeparatorText("Inspector");
    Check("inspect the model in the line of sight", &g_bTrigDrawInspect);
    ImGui::SameLine();
    Check("freeze", &g_bTrigDrawInspectFreeze);
    if (g_bTrigDrawInspect)
    {
        const TrigDrawModelInfo *o = &g_TrigDrawInspected;

        if (!o->bValid)
            ImGui::TextDisabled("(no model in the line of sight)");
        else if (ImGui::BeginTable("inspect", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit))
        {
            RwChar sz[128];

#define INSPECT_ROW(name, ...) do { ImGui::TableNextRow(); ImGui::TableNextColumn(); ImGui::TextUnformatted(name); \
                                    ImGui::TableNextColumn(); ImGui::Text(__VA_ARGS__); } while (0)
            INSPECT_ROW("clump, atomic", "%p, %p", o->pClump, o->pAtomic);
            if (o->pOwner)
            {
                EntityKind(o->dwOwnerBits, sz);
                INSPECT_ROW("owner", "%p %s", o->pOwner, sz);
            }
            else
                INSPECT_ROW("owner", "none (a world prop or a model no entity holds)");
            INSPECT_ROW("clump flags", "0x%02X%s%s%s", o->dwClumpFlags, (o->dwClumpFlags & 1) ? " opaque" : "",
                        (o->dwClumpFlags & 2) ? " alpha" : "", (o->dwClumpFlags & 4) ? " collision" : "");
            INSPECT_ROW("atomic flags", "0x%02X%s%s%s%s%s", o->dwAtomicFlags, (o->dwAtomicFlags & 1) ? " opaque" : "",
                        (o->dwAtomicFlags & 2) ? " alpha" : "", (o->dwAtomicFlags & 4) ? " collision" : "",
                        (o->dwAtomicFlags & 8) ? " skips-lines" : "", (o->dwAtomicFlags & 0x10) ? " skips-shots" : "");
            if (o->nClumpSlot == 0xFFFF)
                INSPECT_ROW("clump placed", "not placed");
            else if (o->nClumpSlot == 0x7FFF)
                INSPECT_ROW("clump placed", "the global section");
            else
                INSPECT_ROW("clump placed", "slot %d (S_%d)", o->nClumpSlot, o->nClumpSection);
            if (o->nAtomicSlot == 0xFFFF)
                INSPECT_ROW("atomic placed", "not placed");
            else if (o->nAtomicSlot == 0x7FFF)
                INSPECT_ROW("atomic placed", "the global section");
            else
                INSPECT_ROW("atomic placed", "slot %d (S_%d)", o->nAtomicSlot, o->nAtomicSection);
            INSPECT_ROW("holders (clump, atomic)", "%d, %d", o->nClumpHolders, o->nAtomicHolders);
            if (o->nCacheKey)
                INSPECT_ROW("model cache key", "0x%08X", (RwUInt32)o->nCacheKey);
            else
                INSPECT_ROW("model cache key", "none (a clone, or not from a model file)");
            INSPECT_ROW("atomics, bones", "%d, %d", o->nAtomics, o->nBones);
            INSPECT_ROW("mount points, kept-bone list", "%d, %d", o->nMounts, o->nKeepBones);
            INSPECT_ROW("atomic part mask (unk_10)", "0x%08X", o->dwPartMask);
            INSPECT_ROW("bounding sphere", "%.0f, %.0f, %.0f r %.1f", o->vCentre.x, o->vCentre.y, o->vCentre.z,
                        o->fRadius);
#undef INSPECT_ROW
            ImGui::EndTable();
        }
    }

    ImGui::SeparatorText("Model cache");
    if (ImGui::CollapsingHeader("the loaded models' file records (dword_4F26D4)"))
    {
        TrigDrawCacheRefresh();
        ImGui::Text("%d records%s", g_nTrigDrawCache, g_nTrigDrawCache >= TRIGDRAW_CACHE ? " (the list is full)" : "");
        ImGui::PushTextWrapPos(0.0f);
        ImGui::TextDisabled("(the GodAsset manager keeps the clump read for each model file, keyed by the file, and "
                            "hands it out again; holders are who points at it, users the entities drawing that very "
                            "clump. Most entities draw clones, so their own clumps are not here)");
        ImGui::PopTextWrapPos();
        if (ImGui::BeginTable("modelcache", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY |
                                               ImGuiTableFlags_Sortable, ImVec2(0.0f, 260.0f)))
        {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("file key");
            ImGui::TableSetupColumn("value");
            ImGui::TableSetupColumn("clump");
            ImGui::TableSetupColumn("holders");
            ImGui::TableSetupColumn("users");
            ImGui::TableSetupColumn("atomics");
            ImGui::TableSetupColumn("mounts");
            ImGui::TableHeadersRow();
            for (i = 0; i < g_nTrigDrawCache; i++)
            {
                const TrigDrawCacheInfo *c = &g_aTrigDrawCache[i];

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("0x%08X", (RwUInt32)c->nFile);
                ImGui::TableNextColumn();
                ImGui::Text("%d", c->nValue);
                ImGui::TableNextColumn();
                ImGui::Text("%p", c->pClump);
                ImGui::TableNextColumn();
                ImGui::Text("%d", c->nHolders);
                ImGui::TableNextColumn();
                ImGui::Text("%d", c->nUsers);
                ImGui::TableNextColumn();
                ImGui::Text("%d", c->nAtomics);
                ImGui::TableNextColumn();
                ImGui::Text("%d", c->nMounts);
            }
            ImGui::EndTable();
        }
    }
}

// The skeletons and their rest offsets.
static void ViewSkeletons()
{
    Check("draw the skeletons", &g_bTrigDrawSkeletons);
    ImGui::SameLine();
    Check("rest offsets", &g_bTrigDrawSkeletonRest);
    ImGui::SliderFloat("skeleton draw distance (0 unlimited)", &g_fTrigDrawSkeletonRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawSkeletons)
        ImGui::Text("%d skeletons drawn", g_nTrigDrawSkeletons);
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(each bone a cyan line from its parent, as the animation poses it. With the rest offsets "
                        "(the .sdf's chunk 0x4212, each bone's bind translation): a small white cross where the rest "
                        "offset puts the bone under its posed parent and the bone is there, as the game's own "
                        "animation scheme (0x1142) always does; orange with a line to the bone where its animation "
                        "gives the bone a translation of its own, as standard keyframes can)");
    ImGui::PopTextWrapPos();
}

// The zone editor: the zone the player is in, or any by its index; its ambient and its two
// lights, changed in place (the level's own data, back to how it loaded with restore).
static void ZoneEditor()
{
    struct Saved { type_8F3E0 *pZone; type_8BEC0 a[5]; };
    static Saved s_aSaved[64];
    static RwInt32 s_nSaved;
    static RwInt32 s_nPick = -1;    // -1 the player's
    type_8F3E0 *pZone = NULL;
    RwInt32 nAll = dword_4B2550.unk_08 ? dword_4B2550.unk_00 : 0, i, nIndex = -1;
    type_3D3548 *pPlayer = (type_3D3548 *)sub_1745A0(0);
    Saved *pSaved = NULL;
    static const void *s_pTable;

    if (s_pTable != (const void *)dword_4B2550.unk_08)
    {
        s_pTable = (const void *)dword_4B2550.unk_08;
        s_nSaved = 0;
    }
    ImGui::SeparatorText("Edit a zone");
    if (nAll <= 0)
    {
        ImGui::TextDisabled("(this level has no zones)");
        return;
    }
    ImGui::RadioButton("the player's zone", &s_nPick, -1);
    ImGui::SameLine();
    if (ImGui::RadioButton("by index", s_nPick >= 0) && s_nPick < 0)
        s_nPick = 0;
    if (s_nPick >= 0)
    {
        ImGui::SameLine();
        ImGui::SetNextItemWidth(160.0f);
        ImGui::SliderInt("zone##edit", &s_nPick, 0, nAll - 1);
        pZone = dword_4B2550.get_zone(s_nPick);
        nIndex = s_nPick;
    }
    else if (pPlayer)
    {
        __try
        {
            pZone = pPlayer->unk_90.unk_00;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            pZone = NULL;
        }
        for (i = 0; i < nAll && pZone; i++)
            if (dword_4B2550.get_zone(i) == pZone)
            {
                nIndex = i;
                break;
            }
    }
    if (pZone == NULL)
    {
        ImGui::TextDisabled("(the player is in no zone)");
        return;
    }
    // (its values as the level loaded them, kept the first time it is shown)
    for (i = 0; i < s_nSaved; i++)
        if (s_aSaved[i].pZone == pZone)
            pSaved = &s_aSaved[i];
    if (pSaved == NULL && s_nSaved < 64)
    {
        pSaved = &s_aSaved[s_nSaved++];
        pSaved->pZone = pZone;
        pSaved->a[0] = pZone->unk_30;
        pSaved->a[1] = pZone->unk_40;
        pSaved->a[2] = pZone->unk_50;
        pSaved->a[3] = pZone->unk_60;
        pSaved->a[4] = pZone->unk_70;
    }
    ImGui::Text("zone %d", nIndex);
    ImGui::ColorEdit4("ambient##ze", &pZone->unk_30.unk_00, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR);
    ImGui::DragFloat3("light 1 direction (all zero: none)##ze", &pZone->unk_40.unk_00, 0.01f, -1.0f, 1.0f, "%.2f");
    ImGui::ColorEdit4("light 1 colour##ze", &pZone->unk_50.unk_00, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR);
    ImGui::DragFloat3("light 2 direction (all zero: none)##ze", &pZone->unk_60.unk_00, 0.01f, -1.0f, 1.0f, "%.2f");
    ImGui::ColorEdit4("light 2 colour##ze", &pZone->unk_70.unk_00, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR);
    if (pSaved && ImGui::Button("restore this zone"))
    {
        pZone->unk_30 = pSaved->a[0];
        pZone->unk_40 = pSaved->a[1];
        pZone->unk_50 = pSaved->a[2];
        pZone->unk_60 = pSaved->a[3];
        pZone->unk_70 = pSaved->a[4];
    }
    ImGui::SameLine();
    if (ImGui::Button("restore all edited zones"))
    {
        for (i = 0; i < s_nSaved; i++)
        {
            s_aSaved[i].pZone->unk_30 = s_aSaved[i].a[0];
            s_aSaved[i].pZone->unk_40 = s_aSaved[i].a[1];
            s_aSaved[i].pZone->unk_50 = s_aSaved[i].a[2];
            s_aSaved[i].pZone->unk_60 = s_aSaved[i].a[3];
            s_aSaved[i].pZone->unk_70 = s_aSaved[i].a[4];
        }
    }
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(the models in the zone change at once: their light rigs are built from these each frame. "
                        "Edits last until the level unloads; a new level forgets them)");
    ImGui::PopTextWrapPos();
}

static void ViewCollision()
{
    Check("draw the collision worlds", &g_bTrigDrawCollision);
    ImGui::SliderFloat("collision draw distance", &g_fTrigDrawCollisionRange, 5.0f, 200.0f, "%.0f");
    ImGui::SliderFloat("collision lift along the normal", &g_fTrigDrawCollisionLift, 0.0f, 0.5f, "%.3f");
    CollisionKinds();
    CollisionSurfaces();
}

// The AI: its path nodes, then the soldiers' state.
static void ViewAi()
{
    ImGui::SeparatorText("Path nodes");
    Check("draw the AI's path nodes", &g_bTrigDrawPathNodes);
    ImGui::SameLine();
    Check("their links", &g_bTrigDrawPathLinks);
    ImGui::SameLine();
    Check("their IDs and types", &g_bTrigDrawPathLabels);
    ImGui::SliderFloat("path node draw distance (0 unlimited)", &g_fTrigDrawPathRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    {
        RwChar szType[48];
        RwInt32 t;

        if (g_nTrigDrawPathType < 0)
            strcpy(szType, "all types");
        else
            sprintf(szType, "%d %s", g_nTrigDrawPathType, TrigDrawPathTypeName(g_nTrigDrawPathType));
        if (ImGui::BeginCombo("path node type", szType))
        {
            if (ImGui::Selectable("all types", g_nTrigDrawPathType < 0))
                g_nTrigDrawPathType = -1;
            for (t = 0; t < 20; t++)
            {
                sprintf(szType, "%d %s", t, TrigDrawPathTypeName(t));
                if (ImGui::Selectable(szType, g_nTrigDrawPathType == t))
                    g_nTrigDrawPathType = t;
            }
            ImGui::EndCombo();
        }
    }
    if (g_bTrigDrawPathNodes)
    {
        if (unk_4C00E8.unk_64 && unk_4C00E8.unk_08 > 1)
            ImGui::TextDisabled("(%d nodes in the level's graph, grid %d x %d of %d; drawn: %d nodes, %d links; red "
                                "links are ones the A* skips)", unk_4C00E8.unk_08 - 1, unk_4C00E8.unk_24,
                                unk_4C00E8.unk_28, unk_4C00E8.unk_04, g_nTrigDrawPathShown, g_nTrigDrawPathLinksShown);
        else
            ImGui::TextDisabled("(no path graph loaded: multiplayer maps have none)");
    }
    ImGui::SeparatorText("The soldiers");
    Check("draw the AI's state", &g_bTrigDrawAi);
    ImGui::SameLine();
    Check("text", &g_bTrigDrawAiText);
    ImGui::SameLine();
    Check("target, point, aim, node", &g_bTrigDrawAiLines);
    ImGui::SameLine();
    Check("path", &g_bTrigDrawAiPath);
    Check("cover (radius, nodes found, cover points)", &g_bTrigDrawAiCover);
    ImGui::SameLine();
    Check("perception and combat", &g_bTrigDrawAiCombat);
    ImGui::SliderFloat("AI draw distance (0 unlimited)", &g_fTrigDrawAiRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawAi)
        ImGui::TextDisabled("(%d drawn: over each, its slot, hit points, AI state code (unk_578), alert and target, "
                            "then the last lines the game logged about it and the script messages it raised (> ...), "
                            "with their age; lines: red the tracked entity, orange the target point, yellow where it "
                            "aims, green its current node, cyan its path)", g_nTrigDrawAiShown);
}

static void ViewGenerators()
{
    Check("draw the projectile generators", &g_bTrigDrawPg);
    ImGui::SameLine();
    Check("their state##pg", &g_bTrigDrawPgText);
    ImGui::SliderFloat("generator draw distance (0 unlimited)", &g_fTrigDrawPgRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawPg)
        ImGui::TextDisabled("(%d drawn: the muzzle, orange bullets, red shells; to the target, red the nearest "
                            "entity, orange a set one, yellow a point, blue its path; the yellow cross where it aims "
                            "with its spread; cyan its turret's facing, magenta while it turns; grey to its "
                            "trigger)", g_nTrigDrawPgShown);
    ImGui::TextDisabled("(Level, Generators: the list, and each one's settings)");
}

static void ViewGimps()
{
    Check("draw the gimps", &g_bTrigDrawGimps);
    ImGui::SameLine();
    Check("the shrimps", &g_bTrigDrawShrimps);
    ImGui::SliderFloat("gimp draw distance (0 unlimited)", &g_fTrigDrawGimpRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawGimps)
        ImGui::TextDisabled("(%d gimps drawn: over each, its slot, health, attitude, its ride and head shot, its place "
                            "along its spline and each of its scripts' states, then the messages it got; orange to its "
                            "point on the spline; a GimpTrigger's label adds its spawns left and the gimp's health)",
                            g_nTrigDrawGimpsShown);
    if (g_bTrigDrawShrimps)
        ImGui::TextDisabled("(%d shrimps drawn: each shrimp trigger's path in blue from its tick, a cross per shrimp, "
                            "cyan going forward, magenta back; its label adds the count, spawns left, chance and speed)",
                            g_nTrigDrawShrimpsShown);
}

// The sounds playing: their markers in the world, and the list of every voice (the 2D ones,
// the music and the HUD's, too).
static void ViewSounds()
{
    RwInt32 i, n3D = 0;

    Check("draw the 3D sounds", &g_bTrigDrawSounds);
    ImGui::SameLine();
    Check("their lines##snd", &g_bTrigDrawSoundLabels);
    ImGui::SameLine();
    Check("minimum distance rings", &g_bTrigDrawSoundRanges);
    ImGui::SliderFloat("sound draw distance (0 unlimited)", &g_fTrigDrawSoundRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (!g_bTrigDrawSounds)
    {
        ImGui::TextDisabled("(drawing them fills the list below)");
        return;
    }
    for (i = 0; i < g_nTrigDrawSoundList; i++)
        n3D += g_aTrigDrawSoundList[i].is3D && g_aTrigDrawSoundList[i].mode3D == 0 ? 1 : 0;
    ImGui::Text("%d playing, %d in the world; the listener at %.0f, %.0f, %.0f", g_nTrigDrawSoundList, n3D,
                g_avTrigDrawListener[0], g_avTrigDrawListener[1], g_avTrigDrawListener[2]);
    ImGui::TextDisabled("(crosses green loud to red quiet; the bridge knows each voice, not which game sound it is: "
                        "-verbose logs the scripts' sound keys)");
    if (ImGui::BeginTable("sounds", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 300.0f)))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("where");
        ImGui::TableSetupColumn("volume");
        ImGui::TableSetupColumn("length");
        ImGui::TableSetupColumn("distance");
        ImGui::TableSetupColumn("min / max");
        ImGui::TableSetupColumn("channels");
        ImGui::TableHeadersRow();
        for (i = 0; i < g_nTrigDrawSoundList; i++)
        {
            const PortAudioVoiceInfo *v = &g_aTrigDrawSoundList[i];
            RwReal dx = v->x - g_avTrigDrawListener[0], dy = v->y - g_avTrigDrawListener[1],
                   dz = v->z - g_avTrigDrawListener[2];

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (v->is3D && v->mode3D == 0)
                ImGui::Text("%.0f, %.0f, %.0f", v->x, v->y, v->z);
            else
                ImGui::TextDisabled(v->is3D && v->mode3D == 1 ? "head-relative" : "2D");
            ImGui::TableNextColumn();
            ImGui::Text("%.1f dB", v->volumeDb);
            ImGui::TableNextColumn();
            ImGui::Text("%.1f s%s (%.0f%%)", v->seconds, v->looping ? " looping" : "", v->played * 100.0f);
            ImGui::TableNextColumn();
            if (v->is3D && v->mode3D == 0)
                ImGui::Text("%.0f", (RwReal)sqrt(dx * dx + dy * dy + dz * dz));
            else
                ImGui::TextDisabled("-");
            ImGui::TableNextColumn();
            if (v->is3D)
                ImGui::Text("%.0f / %.0f", v->minDistance, v->maxDistance > 1e8f ? 0.0f : v->maxDistance);
            else
                ImGui::TextDisabled("-");
            ImGui::TableNextColumn();
            ImGui::Text("%d", v->channels);
        }
        ImGui::EndTable();
    }
}

// The projectiles: the live ones and their trails, where they hit, and what each pool made.
static void ViewProjectiles()
{
    RwInt32 i;
    RwBool bImpact;
    RwInt32 nKind, nSurface;
    RwReal fAge;
    RwV3d v;

    Check("draw the projectiles", &g_bTrigDrawProjectiles);
    ImGui::SameLine();
    Check("trails", &g_bTrigDrawProjTrails);
    ImGui::SameLine();
    Check("label the hits", &g_bTrigDrawProjLabels);
    ImGui::SliderFloat("trails and hits stay (seconds)", &g_fTrigDrawProjTrail, 0.5f, 30.0f, "%.1f");
    ImGui::TextDisabled("(a cross on each one in flight in its kind's colour, the trail behind it; an orange cross "
                        "where one hit, with the surface id; red where one blew up. The counts run whether it is "
                        "drawn or not)");
    if (ImGui::SmallButton("reset the counts"))
        TrigDrawProjReset();
    ImGui::SameLine();
    ImGui::Text("%d hits, %d blasts", g_nTrigDrawProjImpacts, g_nTrigDrawProjBlasts);
    if (ImGui::BeginTable("projpools", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("pool (kind)");
        ImGui::TableSetupColumn("made");
        ImGui::TableSetupColumn("in flight");
        ImGui::TableHeadersRow();
        for (i = 0; i < TRIGDRAW_PROJ_KINDS; i++)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(TrigDrawProjKindName(i));
            ImGui::TableNextColumn();
            ImGui::Text("%d", g_anTrigDrawProjSpawned[i]);
            ImGui::TableNextColumn();
            if (g_bTrigDrawProjectiles)
                ImGui::Text("%d", g_anTrigDrawProjLive[i]);
            else
                ImGui::TextDisabled("(drawn only)");
        }
        ImGui::EndTable();
    }
    if (ImGui::TreeNode("the last hits and blasts"))
    {
        for (i = 0; i < 20 && TrigDrawProjEvent(i, &bImpact, &nKind, &nSurface, &fAge, &v); i++)
        {
            if (bImpact)
                ImGui::Text("%.1f s ago: kind %d hit surface %d at %.0f, %.0f, %.0f", fAge, nKind, nSurface, v.x, v.y,
                            v.z);
            else
                ImGui::Text("%.1f s ago: kind %d blew up at %.0f, %.0f, %.0f", fAge, nKind, v.x, v.y, v.z);
        }
        ImGui::TreePop();
    }
}

// The world line tests the game makes, by their kind (the surface mask they pass).
static void ViewRays()
{
    RwInt32 i;

    Check("draw the line tests", &g_bTrigDrawRays);
    ImGui::SameLine();
    Check("the misses too", &g_bTrigDrawRayMisses);
    ImGui::SliderFloat("they stay (seconds)##rays", &g_fTrigDrawRaySecs, 0.05f, 5.0f, "%.2f");
    ImGui::TextDisabled("(sub_91F40, the world's line test: a hit drawn to where it hit, red cross there, the rest of "
                        "the line faint; the AI's and the bullets' tests against entities are not world tests)");
    for (i = 0; i < 6; i++)
    {
        ImGui::PushID(i);
        Check(TrigDrawRayKindName(i), &g_abTrigDrawRayKinds[i]);
        ImGui::SameLine(330.0f);
        if (g_bTrigDrawRays)
            ImGui::Text("%d a second", g_anTrigDrawRayCount[i]);
        ImGui::PopID();
    }
}

// The bullets' hits on entities, and the bone boxes they test on soldiers.
static void ViewHits()
{
    Check("show the hits (damage and part where each bullet hit)", &g_bTrigDrawHits);
    ImGui::SliderFloat("they stay (seconds)##hits", &g_fTrigDrawHitSecs, 0.5f, 10.0f, "%.1f");
    Check("draw the soldiers' bone boxes", &g_bTrigDrawHitBoxes);
    ImGui::SliderFloat("bone box distance (0 unlimited)", &g_fTrigDrawHitBoxRange, 0.0f, 10000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawHitBoxes)
        ImGui::Text("%d soldiers in range", g_nTrigDrawHitBoxesShown);
    ImGui::TextDisabled("(the 13 boxes per soldier the player's bullets are tested against (sub_8D660), the head red; "
                        "only while the soldier is in view: off screen the game tests one box from its size. A hit's "
                        "number is what the soldier lost when known (sub_13C490), else the bullet's damage)");
}

// The level's lights.
static void EntityKind(RwUInt32 dwBits, RwChar *psz);

static void ViewLights()
{
    RwInt32 i;

    Check("draw the lights", &g_bTrigDrawLights);
    ImGui::SameLine();
    Check("their lines##lights", &g_bTrigDrawLightLabels);
    ImGui::SameLine();
    Check("radii", &g_bTrigDrawLightRadii);
    ImGui::SameLine();
    Check("spot cones", &g_bTrigDrawLightCones);
    ImGui::SameLine();
    Check("entities' light rigs", &g_bTrigDrawLightRigs);
    ImGui::SliderFloat("light draw distance (0 unlimited)", &g_fTrigDrawLightRange, 0.0f, 50000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(RenderWare lights: the level's list, which only WorldLight entities add to (sub_173800), "
                        "the ambient and the four view-light slots, the directionals as arrows in front of the "
                        "camera. The level geometry is prelit and uses none of them. The models are lit by their "
                        "entity's light rig instead: the world render recolours the shared ambient and view lights "
                        "for each model from its entity's zones (sub_1227F0), so the slots below only show what the "
                        "last model drawn left in them. The rigs are drawn at each entity: a cross in the ambient "
                        "colour, each directional a line shining in)");
    ImGui::PopTextWrapPos();
    if (!g_bTrigDrawLights)
        return;
    if (ImGui::BeginTable("lights", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 260.0f)))
    {
        static const RwChar *const s_apszSource[4] = { "the level's", "the ambient", "a directional slot", "the fallback" };

        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("type");
        ImGui::TableSetupColumn("from");
        ImGui::TableSetupColumn("where");
        ImGui::TableSetupColumn("radius");
        ImGui::TableSetupColumn("colour");
        ImGui::TableSetupColumn("lights");
        ImGui::TableSetupColumn("section");
        ImGui::TableSetupColumn("owner");
        ImGui::TableHeadersRow();
        for (i = 0; i < g_nTrigDrawLightList; i++)
        {
            const TrigDrawLightInfo *l = &g_aTrigDrawLightList[i];

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(l->nType == 1 ? "directional" : l->nType == 2 ? "ambient" : l->nType == 0x80 ? "point"
                                   : l->nType == 0x81 ? "spot" : l->nType == 0x82 ? "soft spot" : "?");
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(s_apszSource[l->nSource & 3]);
            ImGui::TableNextColumn();
            if (l->nType >= 0x80)
                ImGui::Text("%.0f, %.0f, %.0f", l->vPos.x, l->vPos.y, l->vPos.z);
            else if (l->nType == 1)
                ImGui::Text("towards %.2f, %.2f, %.2f", l->vAt.x, l->vAt.y, l->vAt.z);
            else
                ImGui::TextDisabled("-");
            ImGui::TableNextColumn();
            if (l->nType >= 0x80)
                ImGui::Text("%.0f", l->fRadius);
            else
                ImGui::TextDisabled("-");
            ImGui::TableNextColumn();
            ImGui::ColorButton("##lc", ImVec4(l->colour.red, l->colour.green, l->colour.blue, 1.0f),
                               ImGuiColorEditFlags_NoTooltip, ImVec2(14.0f, 14.0f));
            ImGui::SameLine();
            ImGui::Text("%.2f %.2f %.2f", l->colour.red, l->colour.green, l->colour.blue);
            // (RenderWare's flags: rpLIGHTLIGHTATOMICS 1, rpLIGHTLIGHTWORLD 2)
            ImGui::TableNextColumn();
            if ((l->nFlags & 3) == 3)
                ImGui::TextUnformatted("models, world");
            else if (l->nFlags & 1)
                ImGui::TextUnformatted("models");
            else if (l->nFlags & 2)
                ImGui::TextUnformatted("world");
            else
                ImGui::TextDisabled("nothing");
            // (its extension's placement: the slot and that section's id)
            ImGui::TableNextColumn();
            if (!l->bExt || l->nSlot == 0xFFFF)
                ImGui::TextDisabled("-");
            else if (l->nSlot == 0x7FFF)
                ImGui::TextUnformatted("global");
            else
                ImGui::Text("slot %d (S_%d)", l->nSlot, l->nSectionId);
            ImGui::TableNextColumn();
            if (l->pOwner)
            {
                RwChar szKind[96];

                EntityKind(l->dwOwnerBits, szKind);
                ImGui::Text("%p %s", l->pOwner, szKind);
            }
            else
                ImGui::TextDisabled("-");
        }
        ImGui::EndTable();
    }
    if (!g_bTrigDrawLightRigs)
        return;
    ImGui::Text("%d entities' light rigs in range; %d more with zone lighting off", g_nTrigDrawLightRigs,
                g_nTrigDrawLightRigsUnlit);
    if (ImGui::BeginTable("lightrigs", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 220.0f)))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("entity");
        ImGui::TableSetupColumn("ambient");
        ImGui::TableSetupColumn("directionals (shining along)");
        ImGui::TableHeadersRow();
        for (i = 0; i < g_nTrigDrawLightRigs; i++)
        {
            const TrigDrawLightRig *o = &g_aTrigDrawLightRigs[i];
            RwChar szKind[96];
            RwInt32 k;

            ImGui::PushID(i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            EntityKind(o->dwBits, szKind);
            ImGui::Text("%p %s", o->pEntity, szKind);
            ImGui::TableNextColumn();
            ImGui::ColorButton("##ra", ImVec4(o->ambient.red, o->ambient.green, o->ambient.blue, 1.0f),
                               ImGuiColorEditFlags_NoTooltip, ImVec2(14.0f, 14.0f));
            ImGui::SameLine();
            ImGui::Text("%.2f %.2f %.2f", o->ambient.red, o->ambient.green, o->ambient.blue);
            ImGui::TableNextColumn();
            if (o->nLights == 0)
                ImGui::TextDisabled("none");
            for (k = 0; k < o->nLights; k++)
            {
                ImGui::PushID(k);
                if (k)
                    ImGui::SameLine();
                ImGui::ColorButton("##rl", ImVec4(o->aColour[k].red, o->aColour[k].green, o->aColour[k].blue, 1.0f),
                                   ImGuiColorEditFlags_NoTooltip, ImVec2(14.0f, 14.0f));
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("colour %.2f %.2f %.2f\nalong %.2f, %.2f, %.2f", o->aColour[k].red,
                                      o->aColour[k].green, o->aColour[k].blue, o->avDir[k].x, o->avDir[k].y,
                                      o->avDir[k].z);
                ImGui::PopID();
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
}

// The models' mount points.
static void ViewMounts()
{
    RwInt32 i;

    Check("draw the mount points", &g_bTrigDrawMounts);
    ImGui::SameLine();
    Check("tags##mounts", &g_bTrigDrawMountLabels);
    ImGui::SameLine();
    Check("axes (else a cross)", &g_bTrigDrawMountAxes);
    ImGui::SliderFloat("mount draw distance (0 unlimited)", &g_fTrigDrawMountRange, 0.0f, 20000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    ImGui::SliderFloat("axis length##mounts", &g_fTrigDrawMountSize, 1.0f, 100.0f, "%.0f", ImGuiSliderFlags_Logarithmic);
    ImGui::InputText("only tags containing", g_szTrigDrawMountFilter, sizeof(g_szTrigDrawMountFilter));
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(the named points the .sdf models carry (the clump data plugin 0x4210, chunk 0x4211): "
                        "each a tag, the bone it hangs on and an offset, placed as the game places them. x red, "
                        "y green, z blue; a tag the code is not known to use is drawn orange)");
    ImGui::PopTextWrapPos();
    if (!g_bTrigDrawMounts)
        return;
    ImGui::Text("%d models with mount points; %d points listed%s", g_nTrigDrawMountClumps, g_nTrigDrawMountList,
                g_nTrigDrawMountList >= TRIGDRAW_MOUNTS ? " (the list is full)" : "");
    if (ImGui::BeginTable("mounts", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 300.0f)))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("tag");
        ImGui::TableSetupColumn("bone");
        ImGui::TableSetupColumn("where");
        ImGui::TableSetupColumn("model's owner");
        ImGui::TableSetupColumn("what it is for");
        ImGui::TableHeadersRow();
        for (i = 0; i < g_nTrigDrawMountList; i++)
        {
            const TrigDrawMountInfo *o = &g_aTrigDrawMountList[i];
            const RwChar *pszMeaning = TrigDrawMountMeaning(o->dwTag);
            RwUInt32 dwTag = o->dwTag;
            RwChar szTag[8];
            RwInt32 n = 0, k;

            // (high byte first, leading zero bytes skipped)
            while (dwTag != 0 && (dwTag & 0xFF000000) == 0)
                dwTag <<= 8;
            for (k = 3; k >= 0; k--)
            {
                RwUInt8 c = (RwUInt8)(dwTag >> (k * 8));

                if (c < 0x21 || c > 0x7E)
                    break;
                szTag[n++] = (RwChar)c;
            }
            szTag[n] = 0;
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", szTag);
            ImGui::TableNextColumn();
            if (o->nBone)
                ImGui::Text("%d", o->nBone);
            else
                ImGui::TextDisabled("clump");
            ImGui::TableNextColumn();
            ImGui::Text("%.0f, %.0f, %.0f", o->vPos.x, o->vPos.y, o->vPos.z);
            ImGui::TableNextColumn();
            if (o->pOwner)
            {
                RwChar szKind[96];

                EntityKind(o->dwOwnerBits, szKind);
                ImGui::Text("%s", szKind);
            }
            else
                ImGui::TextDisabled("-");
            ImGui::TableNextColumn();
            if (pszMeaning)
                ImGui::TextUnformatted(pszMeaning);
            else
                ImGui::TextDisabled("not known");
        }
        ImGui::EndTable();
    }
}

// The AI's hearing.
static void ViewHearing()
{
    Check("draw the sounds the AI can hear", &g_bTrigDrawHearing);
    ImGui::SameLine();
    Check("listeners' radii", &g_bTrigDrawHearRadii);
    ImGui::SameLine();
    Check("labels##hear", &g_bTrigDrawHearLabels);
    ImGui::SliderFloat("they stay (seconds)##hear", &g_fTrigDrawHearSecs, 0.2f, 10.0f, "%.1f");
    if (g_bTrigDrawHearing)
        ImGui::Text("%d sounds a second, %d heard a second", g_nTrigDrawHearNoises, g_nTrigDrawHeardCount);
    ImGui::TextDisabled("(each sound a cross with a ring of its range, blue the player's, red a soldier's; a green line "
                        "to each soldier that heard it (\"AIAction_HearSound\"). A soldier hears a sound within the "
                        "square root of the sound's range squared plus its own radius squared, only of the kinds and "
                        "sides it listens for, and only in some of its states)");
}

// The lighting zones and the entity in each.
static void ViewZones()
{
    Check("draw the zones", &g_bTrigDrawZones);
    ImGui::SameLine();
    Check("entities' zones", &g_bTrigDrawZoneEntities);
    ImGui::SameLine();
    Check("labels##zones", &g_bTrigDrawZoneLabels);
    ImGui::SliderFloat("zone draw distance (0 unlimited)", &g_fTrigDrawZoneRange, 0.0f, 50000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawZones)
        ImGui::Text("%d of the level's %d zones drawn", g_nTrigDrawZonesShown, g_nTrigDrawZonesAll);
    ImGui::TextDisabled("(the lighting zones, dword_4B2550: each entity is lit by the smallest zone holding it, its "
                        "ambient and up to two lights, cross-fading as it moves; a post on each entity in its zone's "
                        "colour, white the default zone, grey none. Only lighting reads them; Engine, Level and render "
                        "has the switches that turn them off)");
    ZoneEditor();
}

// The AI squads.
static void ViewSquads()
{
    Check("draw the squads", &g_bTrigDrawSquads);
    ImGui::SameLine();
    Check("labels##squads", &g_bTrigDrawSquadLabels);
    if (g_bTrigDrawSquads)
        ImGui::Text("%d squads", g_nTrigDrawSquads);
    ImGui::TextDisabled("(a line from each member to its leader (\"SetSquadLeader\"; its first member when none is "
                        "set), a ring on the leader; its id, side, members, the targets it sees and its maneuvers: "
                        "every squad starts with run members, alert stand and the two flagged ones, scripts add pair "
                        "at a spot and fire and movement)");
}

// The splines: every SplinePath the level made, its curve, name and length.
static void ViewSplines()
{
    Check("draw the splines", &g_bTrigDrawSplines);
    ImGui::SameLine();
    Check("their names##spl", &g_bTrigDrawSplineLabels);
    ImGui::SliderFloat("spline draw distance (0 unlimited)", &g_fTrigDrawSplineRange, 0.0f, 50000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    if (g_bTrigDrawSplines)
        ImGui::Text("%d of the level's %d splines drawn", g_nTrigDrawSplinesShown, g_nTrigDrawSplinesAll);
    ImGui::TextDisabled("(the paths gimps, vehicles, the camera, shrimps and moving props follow: a post at each "
                        "start, a cross at each end, a colour each)");
}

// Moving about: noclip for the player, the free camera.
static void ViewCamera()
{
    ImGui::SeparatorText("Noclip");
    Check("noclip for the local player", &g_bTrigDrawNoclip);
    ImGui::SliderFloat("noclip speed", &g_fTrigDrawNoclipSpeed, 1.0f, 500.0f, "%.0f");
    ImGui::TextDisabled("(noclip: the left stick moves along the view, Black up, White down)");
    ImGui::SeparatorText("Free camera");
    Check("free camera", &g_bTrigDrawFreeCam);
    ImGui::SliderFloat("free camera speed (units a second)", &g_fTrigDrawFreeCamSpeed, 50.0f, 10000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    ImGui::SliderFloat("free camera look (radians a second)", &g_fTrigDrawFreeCamLook, 0.5f, 6.0f, "%.1f");
    ImGui::TextDisabled("(free camera: the pad is the camera's, not the player's; the left stick (WASD) moves, the "
                        "right (the mouse) looks, Black/White (Q/E) up and down, the right trigger faster, the left "
                        "slower; start and back stay the game's)");
}

// The web suite's live link, and the game's own debug menu.
static void EngineLinks()
{
    ImGui::SeparatorText("The web suite's live link");
    Check("live link for the level viewer", &g_bTrigLive);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(90.0f);
    if (!g_bTrigLive)
        ImGui::InputInt("port##live", &g_nTrigLivePort, 0, 0);
    else
        ImGui::Text("ws://127.0.0.1:%d, %d viewer%s", g_nTrigLivePort, g_nTrigLiveClients,
                    g_nTrigLiveClients == 1 ? "" : "s");
    ImGui::TextDisabled("(the viewer's Live game panel connects to it; CODFH_LIVE=1 starts with it on; only this "
                        "machine can connect, and only a page served from it may command the game)");
    ImGui::SeparatorText("The game's own debug menu");
    ImGui::Text("The game's debug menu: %s", unk_4E73A8.unk_14 ? "open" : "closed");
    ImGui::SameLine();
    if (ImGui::Button(unk_4E73A8.unk_14 ? "close it" : "open it"))
        g_nTrigWebDebugMenuToggle = 1;
    ImGui::TextWrapped("In game: D-pad up/down selects, left/right changes a value, A enters a group, White goes "
                       "back. It holds Renderer Switching (disable world parts, clones, particles, sky; light "
                       "scales), Game Speed, Unlimited Ammo and the debug switches, and Performance Statistics.");
}

// ---- Player ----

static void TabPlayer()
{
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vPos;

    if (pPlayer == NULL)
    {
        ImGui::Text("No local player (sub_1745A0(0) is NULL).");
        return;
    }
    if (!BeginRows("player"))
        return;
    Row("entity", "0x%08X", (RwUInt32)pPlayer);
    if (PlayerPosition(pPlayer, &vPos))
        Row("position (frame)", "%.2f, %.2f, %.2f", vPos.x, vPos.y, vPos.z);
    else
        Row("position (frame)", "?");
    RowV3d("last placed (unk_434)", &pPlayer->unk_434);
    RowV3d("step from (unk_440)", &pPlayer->unk_440);
    RowF32("health fraction (unk_19DC)", &pPlayer->unk_19DC);
    RowU32("movement state (unk_19D0)", &pPlayer->unk_19D0, FALSE);
    RowF32("look pitch, degrees (unk_530)", &pPlayer->unk_530);
    RowF32("field of view (unk_534)", &pPlayer->unk_534);
    RowF32("eye height (unk_524)", &pPlayer->unk_524);
    RowF32("fall's highest point (unk_510)", &pPlayer->unk_510);
    RowF32("time falling (unk_518)", &pPlayer->unk_518);
    RowU32("landings (unk_514)", &pPlayer->unk_514, FALSE);
    RowF32("jump wait (unk_428)", &pPlayer->unk_428);
    RowU32("player index (unk_3DC)", &pPlayer->unk_3DC, FALSE);
    RowU32("pad (unk_3D8)", &pPlayer->unk_3D8, FALSE);
    RowV3d("aim point (unk_474)", &pPlayer->unk_474);
    ImGui::EndTable();
}

// ---- Inventory ----

static void TabInventory()
{
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwUInt32 dwWeapon, dwHand, dwSel;
    RwInt32 i;

    if (pPlayer == NULL)
    {
        ImGui::Text("No local player.");
        return;
    }
    {
        RwReal f = 0.0f;

        ReadF32(&pPlayer->unk_19DC, &f);
        ImGui::Text("health fraction (unk_19DC): %.3f", f);
    }
    if (ImGui::Button("heal to 100%"))
        Request(REQ_HEAL, 0, 0, 100.0f, 0.0f, 0.0f);
    ImGui::SameLine();
    if (ImGui::Button("set 50%"))
        Request(REQ_HEAL, 0, 0, 50.0f, 0.0f, 0.0f);
    ImGui::SameLine();
    if (ImGui::Button("set 10%"))
        Request(REQ_HEAL, 0, 0, 10.0f, 0.0f, 0.0f);

    // the inventory: a count per kind 1 to 12 (1 the health packs)
    if (ImGui::CollapsingHeader("Inventory (unk_21B4)", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (!ReadU32(&pPlayer->unk_21B4.unk_34, &dwSel))
            dwSel = 0;
        if (ImGui::BeginTable("inv", 3, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        {
            for (i = 1; i <= 12; i++)
            {
                RwUInt32 dw;

                if (!ReadU32(&pPlayer->unk_21B4.unk_00[i], &dw))
                    continue;
                ImGui::PushID(i);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d%s%s", i, i == 1 ? " (health packs)" : "", (RwInt32)dwSel == i ? " < selected" : "");
                ImGui::TableNextColumn();
                ImGui::Text("%d", (RwInt32)dw);
                ImGui::TableNextColumn();
                if (ImGui::SmallButton("+1"))
                    Request(REQ_GIVE, i, 1, 0.0f, 0.0f, 0.0f);
                ImGui::SameLine();
                if (ImGui::SmallButton("+10"))
                    Request(REQ_GIVE, i, 10, 0.0f, 0.0f, 0.0f);
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }

    // the weapons: the player keeps a copy of each of the 39 (unk_1A48), holds
    // two (unk_1B30), one in hand (unk_1AE4); a weapon's model needs its bank
    if (!ImGui::CollapsingHeader("Weapons", ImGuiTreeNodeFlags_DefaultOpen))
        return;
    if (!ReadU32(&pPlayer->unk_1AE4, &dwHand))
        dwHand = (RwUInt32)-1;
    {
        RwUInt32 dwHeld0 = (RwUInt32)-1, dwHeld1 = (RwUInt32)-1;

        ReadU32(&pPlayer->unk_1B30[0], &dwHeld0);
        ReadU32(&pPlayer->unk_1B30[1], &dwHeld1);
        ImGui::Text("Held: %s and %s; in hand: %s.%s",
                    (RwInt32)dwHeld0 >= 0 && dwHeld0 < 39 ? off_429768[dwHeld0] : "none",
                    (RwInt32)dwHeld1 >= 0 && dwHeld1 < 39 ? off_429768[dwHeld1] : "none",
                    (RwInt32)dwHand >= 0 && dwHand < 39 ? off_429768[dwHand] : "none",
                    s_nGiveWeapon != -1 ? " A give is in progress." : "");
        ImGui::TextWrapped("Giving streams the weapon's bank first when needed (into the bank slot neither held "
                           "weapon uses), then gives it the way \"SetPlayerWeapon\" does and fills its clip and "
                           "reserve. Grenades and mines go to the inventory. \"keep\" also records it in the "
                           "player's trigger, so a checkpoint restart keeps it.");
        if (!ImGui::BeginTable("weapons", 7, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
            return;
        ImGui::TableSetupColumn("#");
        ImGui::TableSetupColumn("weapon");
        ImGui::TableSetupColumn("held");
        ImGui::TableSetupColumn("bank");
        ImGui::TableSetupColumn("loaded");
        ImGui::TableSetupColumn("reserve");
        ImGui::TableSetupColumn("give");
        ImGui::TableHeadersRow();
        for (i = 0; i < 39; i++)
        {
            RwUInt32 dwLoaded = 0, dwReserve = 0, dwBank = (RwUInt32)-1;
            RwInt32 nStreamed = 0;
            const RwChar *pszHeld = "";

            if (!ReadU32(&pPlayer->unk_1A48[i], &dwWeapon) || dwWeapon == 0)
                continue;
            ReadU32(&((type_10F710_1A48 *)dwWeapon)->unk_414, &dwLoaded);
            ReadU32(&((type_10F710_1A48 *)dwWeapon)->unk_418, &dwReserve);
            ReadU32(&dword_4C19C0[i].unk_24, &dwBank);
            __try
            {
                nStreamed = pPlayer->sub_10E8C0(i);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            if ((RwInt32)dwHand == i)
                pszHeld = "in hand";
            else if ((RwInt32)dwHeld0 == i || (RwInt32)dwHeld1 == i)
                pszHeld = "held";
            ImGui::PushID(i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%d", i);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(off_429768[i]);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(pszHeld);
            ImGui::TableNextColumn();
            if ((RwInt32)dwBank >= 0)
                ImGui::Text("wbank_%02d %s", (RwInt32)dwBank, nStreamed ? "(loaded)" : "");
            else
                ImGui::Text("-");
            ImGui::TableNextColumn();
            ImGui::Text("%d", (RwInt32)dwLoaded);
            ImGui::TableNextColumn();
            ImGui::Text("%d", (RwInt32)dwReserve);
            ImGui::TableNextColumn();
            if (ImGui::SmallButton("hand"))
                Request(REQ_GIVEWEAPON, i, 0, 0.0f, 0.0f, 0.0f);
            ImGui::SameLine();
            if (ImGui::SmallButton("other"))
                Request(REQ_GIVEWEAPON, i, 1, 0.0f, 0.0f, 0.0f);
            ImGui::SameLine();
            if (ImGui::SmallButton("hand+keep"))
                Request(REQ_GIVEWEAPON, i, 2, 0.0f, 0.0f, 0.0f);
            ImGui::SameLine();
            if (ImGui::SmallButton("reserve 999"))
                Request(REQ_AMMO, i, 999, 0.0f, 0.0f, 0.0f);
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
}

// ---- Weapons ----

// The weapon settings fields the behaviours set (weaponfields.inc, written by
// the plain build's research/gen_weaponfields.py from their HandleAttributes).
enum { WF_INT, WF_REAL, WF_BOOL, WF_V3D, WF_BYTE };

struct WeaponField
{
    const RwChar *pszBehaviour;
    RwInt32 nCommand;
    const RwChar *pszField;
    RwUInt32 dwOffset;
    RwInt32 nKind;
    const RwChar *pszHow;
    const RwChar *pszDesc;
};

static const WeaponField s_aWeaponFields[] =
{
#include "weaponfields.inc"
};

// An 8-byte name key (type_3DF8D8_04) at p as hex, into psz ("?" when it
// faults).
static void KeyText(const void *p, RwChar *psz)
{
    RwUInt32 dw0, dw1;

    if (ReadU32(p, &dw0) && ReadU32((const RwUInt8 *)p + 4, &dw1))
        sprintf(psz, "%08X:%08X", dw0, dw1);
    else
        strcpy(psz, "?");
}

// Weapon w's model chain, as the copy's vf_008 walks it: its definition
// (sub_198800 of its settings' key; kind 5), the model key the definition
// names (unk_20) and whether that model resolves (sub_18F800); each guarded.
static void WeaponModelChain(RwInt32 w, RwChar *pszDef, RwChar *pszModelKey, RwChar *pszModel)
{
    type_495F0 *pDef = NULL;
    RwInt32 nKind = -1;

    strcpy(pszDef, "?");
    strcpy(pszModelKey, "-");
    strcpy(pszModel, "-");
    __try
    {
        pDef = (type_495F0 *)sub_198800(&dword_4C19C0[w].unk_00);
        if (pDef == NULL)
        {
            strcpy(pszDef, "not registered");
            return;
        }
        nKind = pDef->vf_008();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        strcpy(pszDef, "faulted");
        return;
    }
    sprintf(pszDef, "0x%08X kind %d", (RwUInt32)pDef, nKind);
    if (nKind != 5)
        return;
    KeyText(&pDef->unk_20.unk_04, pszModelKey);
    __try
    {
        RwInt32 nModel = pDef->sub_18F800(&pDef->unk_20);

        if (nModel)
            sprintf(pszModel, "yes (0x%08X)", nModel);
        else
            strcpy(pszModel, "no");
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        strcpy(pszModel, "faulted");
    }
}

// Whether weapon w's definition names a projectile object (type_495F0's
// unk_38, what a throw or shot spawns) that resolves on this map.
static const RwChar *WeaponProjectile(RwInt32 w)
{
    __try
    {
        type_495F0 *pDef = (type_495F0 *)sub_198800(&dword_4C19C0[w].unk_00);

        if (pDef == NULL || pDef->vf_008() != 5)
            return "-";
        if (pDef->unk_38.unk_04.unk_00 == 0 && pDef->unk_38.unk_04.unk_04 == 0)
            return "none named";
        return sub_198800(&pDef->unk_38.unk_04) ? "yes" : "not loaded";
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return "faulted";
    }
}

// The weapons' model diagnostic: each weapon's settings key, definition,
// model key, whether the model resolves, its bank and the bank slot holding
// it; then the three bank slots and their keys.
static void WeaponDiagnostic()
{
    RwInt32 i, j;
    RwChar szKey[24], szDef[48], szModelKey[24], szModel[32];

    ImGui::TextWrapped("The chain the weapon copy follows to its model (vf_008): the settings' key, the "
                       "definition (must be kind 5), the model key it names, the model, which resolves only while "
                       "its bank is in a slot. The mounted and coaxial guns' banks (4, 16, 27, 30, 32, 33, 34, 37) "
                       "are 480-byte stubs with no model.");
    if (ImGui::BeginTable("diag", 10, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        static const RwChar *const s_apszCols[10] = {"#", "weapon", "settings key", "definition", "model key",
                                                     "model resolves", "bank", "bank slot", "fire animation",
                                                     "projectile"};
        for (i = 0; i < 10; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
        for (i = 0; i < 39; i++)
        {
            RwUInt32 dwBank = (RwUInt32)-1;
            RwInt32 nSlot = -1;

            KeyText(&dword_4C19C0[i].unk_00, szKey);
            WeaponModelChain(i, szDef, szModelKey, szModel);
            ReadU32(&dword_4C19C0[i].unk_24, &dwBank);
            __try
            {
                nSlot = sub_16F860((RwInt32)dwBank);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%d", i);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(off_429768[i]);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(szKey);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(szDef);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(szModelKey);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(szModel);
            ImGui::TableNextColumn();
            ImGui::Text("%d", (RwInt32)dwBank);
            ImGui::TableNextColumn();
            ImGui::Text("%d", nSlot);
            ImGui::TableNextColumn();
            ImGui::Text("%08X%s", (RwUInt32)dword_4C19C0[i].unk_2C,
                        dword_4C19C0[i].unk_2C == 0 ? " (none)"
                        : (RwUInt32)dword_4C19C0[i].unk_2C == 0x811C9DC5 ? " (empty name)" : "");
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(WeaponProjectile(i));
        }
        ImGui::EndTable();
    }
    ImGui::Text("Weapon bank slots (unit_16F2C0)");
    if (!ImGui::BeginTable("banks", 6, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    ImGui::TableSetupColumn("slot");
    ImGui::TableSetupColumn("loaded bank");
    ImGui::TableSetupColumn("requested");
    ImGui::TableSetupColumn("level's");
    ImGui::TableSetupColumn("state");
    ImGui::TableSetupColumn("keys (the clumps it holds; * a weapon's model key)");
    ImGui::TableHeadersRow();
    for (i = 0; i < 3; i++)
    {
        RwUInt32 dwLoaded = (RwUInt32)-1, dwWanted = (RwUInt32)-1, dwLevel = (RwUInt32)-1, dwState = 0;

        ReadU32(&dword_4E54D0[i], &dwLoaded);
        ReadU32(&dword_4E54DC[i], &dwWanted);
        ReadU32(&dword_4E54E8[i], &dwLevel);
        ReadU32(&dword_4E5518[i], &dwState);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", i);
        ImGui::TableNextColumn();
        ImGui::Text("%d", (RwInt32)dwLoaded);
        ImGui::TableNextColumn();
        ImGui::Text("%d", (RwInt32)dwWanted);
        ImGui::TableNextColumn();
        ImGui::Text("%d", (RwInt32)dwLevel);
        ImGui::TableNextColumn();
        ImGui::Text("count %d, loading %d", (RwInt32)(dwState >> 16), (RwInt32)(dwState & 0xFFFF));
        ImGui::TableNextColumn();
        for (j = 0; j < 8; j++)
        {
            RwUInt32 dw0 = 0, dw1 = 0;
            RwInt32 w;
            const RwChar *pszOwner = "";

            ReadU32(&dword_4E5528[i][j].unk_00, &dw0);
            ReadU32((RwUInt8 *)&dword_4E5528[i][j].unk_00 + 4, &dw1);
            if (dw0 == 0 && dw1 == 0)
                continue;
            // (whose model key it is, if any weapon's)
            for (w = 0; w < 39; w++)
            {
                RwChar szDummy[48], szMk[24], szM[32];
                RwChar szThis[24];

                WeaponModelChain(w, szDummy, szMk, szM);
                sprintf(szThis, "%08X:%08X", dw0, dw1);
                if (strcmp(szMk, szThis) == 0)
                {
                    pszOwner = off_429768[w];
                    break;
                }
            }
            ImGui::Text("%08X:%08X%s%s", dw0, dw1, pszOwner[0] ? " * " : "", pszOwner);
        }
    }
    ImGui::EndTable();
}

// One field's row: its command, name, value (edited in place: the settings
// are plain data the weapons read as they need it), how it is stored and its
// description.
static void WeaponFieldRow(RwUInt8 *pSettings, const WeaponField *pField)
{
    RwUInt8 *p = pSettings + pField->dwOffset;
    RwUInt32 dw;
    RwReal f;

    switch (pField->nKind)
    {
    case WF_INT:
    case WF_BOOL:
    case WF_BYTE:
        if (!ReadU32(p, &dw))
            return;
        break;
    case WF_REAL:
        if (!ReadF32(p, &f))
            return;
        break;
    case WF_V3D:
        if (!ReadF32(p, &f) || !ReadF32(p + 8, &f))
            return;
        break;
    default:
        return;
    }
    ImGui::PushID(pField->pszField);
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%d", pField->nCommand);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(pField->pszField);
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(220);
    switch (pField->nKind)
    {
    case WF_INT:
        if (ImGui::InputInt("##v", (int *)p, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue))
            sprintf(s_szReqResult, "%s (command %d) set", pField->pszField, pField->nCommand);
        break;
    case WF_REAL:
        if (ImGui::InputFloat("##v", (float *)p, 0.0f, 0.0f, "%g", ImGuiInputTextFlags_EnterReturnsTrue))
            sprintf(s_szReqResult, "%s (command %d) set", pField->pszField, pField->nCommand);
        break;
    case WF_BOOL:
        if (ImGui::Checkbox("##v", (bool *)p))
            sprintf(s_szReqResult, "%s (command %d) set", pField->pszField, pField->nCommand);
        break;
    case WF_V3D:
        if (ImGui::InputFloat3("##v", (float *)p, "%g", ImGuiInputTextFlags_EnterReturnsTrue))
            sprintf(s_szReqResult, "%s (command %d) set", pField->pszField, pField->nCommand);
        break;
    case WF_BYTE:
        if (ImGui::InputScalar("##v", ImGuiDataType_U8, p, NULL, NULL, "%u", ImGuiInputTextFlags_EnterReturnsTrue))
            sprintf(s_szReqResult, "%s (command %d) set", pField->pszField, pField->nCommand);
        break;
    }
    ImGui::TableNextColumn();
    ImGui::TextDisabled("%s%s%s", pField->pszHow, pField->pszDesc[0] ? "; " : "", pField->pszDesc);
    ImGui::PopID();
}

static void TabWeapons()
{
    static RwInt32 s_nWeapon = -1;
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwUInt32 dwHand = (RwUInt32)-1, dwHeld0 = (RwUInt32)-1, dwHeld1 = (RwUInt32)-1;
    const RwChar *pszBehaviour = "";
    RwInt32 i;
    RwChar szItem[64];

    if (pPlayer)
    {
        if (!ReadU32(&pPlayer->unk_1AE4, &dwHand))
            dwHand = (RwUInt32)-1;
        ReadU32(&pPlayer->unk_1B30[0], &dwHeld0);
        ReadU32(&pPlayer->unk_1B30[1], &dwHeld1);
    }
    if (s_nWeapon < 0 || s_nWeapon >= 39)
        s_nWeapon = (RwInt32)dwHand >= 0 && (RwInt32)dwHand < 39 ? (RwInt32)dwHand : 0;
    // the active weapon: the one in hand (unk_1AE4), its copy's rounds
    if ((RwInt32)dwHand >= 0 && (RwInt32)dwHand < 39)
    {
        RwUInt32 dwCopy = 0, dwLoaded = 0, dwReserve = 0;

        ReadU32(&pPlayer->unk_1A48[dwHand], &dwCopy);
        if (dwCopy)
        {
            ReadU32(&((type_10F710_1A48 *)dwCopy)->unk_414, &dwLoaded);
            ReadU32(&((type_10F710_1A48 *)dwCopy)->unk_418, &dwReserve);
        }
        ImGui::Text("Active weapon: settings %d, %s (%d loaded, %d in reserve)", dwHand, off_429768[dwHand],
                    (RwInt32)dwLoaded, (RwInt32)dwReserve);
        ImGui::SameLine();
        if (ImGui::SmallButton("show it"))
            s_nWeapon = (RwInt32)dwHand;
    }
    else
        ImGui::Text("Active weapon: none%s", pPlayer ? "" : " (no local player)");
    // the 39 settings: each one's clip and reserve, which the player has
    sprintf(szItem, "%d %s", s_nWeapon, off_429768[s_nWeapon]);
    if (ImGui::BeginCombo("settings", szItem))
    {
        for (i = 0; i < 39; i++)
        {
            RwUInt32 dwClip = 0, dwMost = 0;

            ReadU32(&dword_4C19C0[i].unk_C8, &dwClip);
            ReadU32(&dword_4C19C0[i].unk_CC, &dwMost);
            sprintf(szItem, "%d %s (%d/%d)%s", i, off_429768[i], (RwInt32)dwClip, (RwInt32)dwMost,
                    (RwInt32)dwHand == i ? " <hand" : ((RwInt32)dwHeld0 == i || (RwInt32)dwHeld1 == i) ? " *" : "");
            if (ImGui::Selectable(szItem, i == s_nWeapon))
                s_nWeapon = i;
        }
        ImGui::EndCombo();
    }
    ImGui::TextDisabled("(clip/most in reserve); * held, <hand in hand. Edits change dword_4C19C0[%d] at once (Enter "
                        "to set a number); what the player's copy took when given stays until it is given again.",
                        s_nWeapon);
    if (ImGui::CollapsingHeader("Settings", ImGuiTreeNodeFlags_DefaultOpen) &&
        ImGui::BeginTable("fields", 4, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("cmd");
        ImGui::TableSetupColumn("field");
        ImGui::TableSetupColumn("value");
        ImGui::TableSetupColumn("stored as; description");
        ImGui::TableHeadersRow();
        for (i = 0; i < (RwInt32)(sizeof(s_aWeaponFields) / sizeof(s_aWeaponFields[0])); i++)
        {
            if (strcmp(pszBehaviour, s_aWeaponFields[i].pszBehaviour) != 0)
            {
                pszBehaviour = s_aWeaponFields[i].pszBehaviour;
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::TableNextColumn();
                ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.4f, 1.0f), "%s", pszBehaviour);
            }
            WeaponFieldRow((RwUInt8 *)&dword_4C19C0[s_nWeapon], &s_aWeaponFields[i]);
        }
        ImGui::EndTable();
    }
    if (ImGui::CollapsingHeader("Model diagnostic"))
        WeaponDiagnostic();
}

// ---- Triggers ----

static RwInt32 s_anTrigOrder[2000];
static RwReal s_afTrigDist[2000];

static int __cdecl TrigByDistance(const void *pA, const void *pB)
{
    RwReal fA = s_afTrigDist[*(const RwInt32 *)pA], fB = s_afTrigDist[*(const RwInt32 *)pB];

    return fA < fB ? -1 : fA > fB ? 1 : 0;
}

// The trigger's row: its type, shape, place, flags, distance and its actions.
// The trigger Level, Triggers, Selected edits (a handle; -1 none), set from here.
static RwInt32 s_nTrigEdit = -1;

static void TrigRow(RwInt32 nHandle, Trigger *pTrigger, RwReal fDist)
{
    RwChar szShape[64], szFlags[48];
    const RwChar *pszKind;
    RwV3d vAt;
    RwBool bSoldier, bEditable;

    __try
    {
        pszKind = TrigDrawKindName(pTrigger);
        switch (pTrigger->unk_46)
        {
        case 0:
            sprintf(szShape, "sphere r %.1f", pTrigger->unk_48);
            break;
        case 1:
            sprintf(szShape, "cylinder r %.1f h +-%.1f", pTrigger->unk_48, pTrigger->unk_4C);
            break;
        case 2:
            sprintf(szShape, "box %.1f x %.1f x %.1f", pTrigger->unk_48 * 2, pTrigger->unk_4C * 2,
                    pTrigger->unk_50 * 2);
            break;
        default:
            sprintf(szShape, "shape %d", pTrigger->unk_46);
        }
        sprintf(szFlags, "%s%s%s", pTrigger->unk_24_0 ? "on" : "off", pTrigger->unk_24_3 ? ", proximity off" : "",
                pTrigger->unk_24_15 ? ", moved" : "");
        vAt.x = pTrigger->unk_90;
        vAt.y = pTrigger->unk_94;
        vAt.z = pTrigger->unk_98;
        bSoldier = pTrigger->vf_008() == 5;
        bEditable = TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return;
    }
    ImGui::PushID(nHandle);
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%d", nHandle);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(pszKind);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(szShape);
    ImGui::TableNextColumn();
    ImGui::Text("%.1f, %.1f, %.1f", vAt.x, vAt.y, vAt.z);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(szFlags);
    ImGui::TableNextColumn();
    ImGui::Text("%.1f", fDist);
    ImGui::TableNextColumn();
    if (ImGui::SmallButton("teleport"))
        Request(REQ_TELEPORT, 0, 0, vAt.x, vAt.y, vAt.z);
    if (bEditable)
    {
        ImGui::SameLine();
        if (ImGui::SmallButton(s_nTrigEdit == nHandle ? "editing" : "edit"))
            s_nTrigEdit = nHandle;
    }
    if (bSoldier)
    {
        ImGui::SameLine();
        if (ImGui::SmallButton("spawn its soldier ahead of me"))
            Request(REQ_SPAWNSOLDIER, nHandle, 0, 0.0f, 0.0f, 0.0f);
    }
    ImGui::PopID();
}

// ---- Generators ----

// The live projectile generators (type_1227C0, the list dword_4CE8F8),
// nearest first: their state and target, with the scripts' "PG_" actions
// (REQ_PG), a teleport and a look with the free camera; the picked one's
// trigger settings (ProjectileGeneratorTrigger) below.
struct TrigWebPg
{
    type_1227C0 *pGen;
    RwInt32 nId, nKind, nState, nTarget, nShots, nStage, nStagesOn, nLos, nForced;
    RwReal fNext, fDist;
    RwV3d vPos, vTrigger;
    ProjectileGeneratorTrigger *pTrigger;
};
static TrigWebPg s_aPg[256];
static RwInt32 s_nPgSel = -1;

static int PgByDistance(const void *pA, const void *pB)
{
    RwReal f = ((const TrigWebPg *)pA)->fDist - ((const TrigWebPg *)pB)->fDist;

    return f < 0.0f ? -1 : f > 0.0f ? 1 : 0;
}

static RwInt32 PgList(const RwV3d *pvFrom)
{
    RwInt32 n = 0;

    __try
    {
        type_1227C0 *pGen;

        for (pGen = dword_4CE8F8; pGen != NULL && n < 256; pGen = pGen->unk_100)
        {
            TrigWebPg *p = &s_aPg[n];
            RwV3d vD;

            p->pGen = pGen;
            p->nId = pGen->unk_104;
            p->nKind = pGen->vf_01C() != NULL;
            p->nState = pGen->unk_14;
            p->nTarget = pGen->unk_38;
            p->nShots = pGen->unk_40;
            p->nStage = pGen->unk_34;
            p->nStagesOn = pGen->unk_30;
            p->nLos = p->nKind == 0 ? ((type_11DB10 *)pGen)->unk_20C : -1;
            p->nForced = pGen->unk_28;
            p->fNext = pGen->unk_44;
            p->vPos = pGen->unk_70.pos;
            p->pTrigger = pGen->unk_18.unk_08_pg;
            p->vTrigger = p->vPos;
            if (p->pTrigger)
            {
                p->vTrigger.x = p->pTrigger->unk_90;
                p->vTrigger.y = p->pTrigger->unk_94;
                p->vTrigger.z = p->pTrigger->unk_98;
            }
            vD.x = p->vPos.x - pvFrom->x;
            vD.y = p->vPos.y - pvFrom->y;
            vD.z = p->vPos.z - pvFrom->z;
            p->fDist = (RwReal)sqrt(vD.x * vD.x + vD.y * vD.y + vD.z * vD.z);
            n++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    qsort(s_aPg, n, sizeof(TrigWebPg), PgByDistance);
    return n;
}

static void PgSettings(ProjectileGeneratorTrigger *pT)
{
    if (pT == NULL || !BeginRows("pgset"))
        return;
    __try
    {
        Row("trigger", "0x%08X at %.1f, %.1f, %.1f", (RwUInt32)pT, pT->unk_90, pT->unk_94, pT->unk_98);
        Row("projectile speed (unk_158)", "%g", pT->unk_158_r);
        Row("time between shots (unk_128)", "%g", pT->unk_128_r);
        Row("bursts before a pause (unk_108, unk_10C)", "%u to %u", pT->unk_108, pT->unk_10C);
        Row("pause after a burst (unk_114)", "%g", pT->unk_114_r);
        Row("pause between bursts (unk_120, unk_124)", "%g to %g", pT->unk_120_r, pT->unk_124_r);
        Row("stage shot counts (unk_164, unk_168)", "%u, %u", pT->unk_164, pT->unk_168);
        Row("chance not flagged 2 (unk_104)", "%u%%", pT->unk_104);
        Row("path speed (unk_FC)", "%g", pT->unk_FC_r);
        Row("sound replay delay (unk_220)", "%u to %u", pT->unk_220 & 0xFFFF, pT->unk_220 >> 16);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Row("trigger", "?");
    }
    ImGui::EndTable();
}

static void TabGenerators()
{
    static const RwChar *const s_apszTarget[4] = {"nearest", "entity", "point", "path"};
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vFrom = {0.0f, 0.0f, 0.0f};
    RwInt32 n, i;

    if (pPlayer == NULL || !PlayerPosition(pPlayer, &vFrom))
        vFrom.x = vFrom.y = vFrom.z = 0.0f;
    n = PgList(&vFrom);
    Check("draw them##pgtab", &g_bTrigDrawPg);
    ImGui::SameLine();
    ImGui::TextDisabled("%d live, nearest first; the actions are the scripts' PG_ commands", n);
    if (!ImGui::BeginTable("pgs", 8, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                           ImVec2(0.0f, 320.0f)))
        return;
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableSetupColumn("id");
    ImGui::TableSetupColumn("kind");
    ImGui::TableSetupColumn("state");
    ImGui::TableSetupColumn("target");
    ImGui::TableSetupColumn("burst");
    ImGui::TableSetupColumn("distance");
    ImGui::TableSetupColumn("go");
    ImGui::TableSetupColumn("actions");
    ImGui::TableHeadersRow();
    for (i = 0; i < n; i++)
    {
        TrigWebPg *p = &s_aPg[i];
        RwChar szId[16];

        ImGui::PushID(p->nId);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        sprintf(szId, "%d", p->nId & 0xFFFF);
        if (ImGui::Selectable(szId, s_nPgSel == p->nId))
            s_nPgSel = s_nPgSel == p->nId ? -1 : p->nId;
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(p->nKind ? "shells" : "bullets");
        ImGui::TableNextColumn();
        ImGui::Text("%s%s", p->nState == 1 ? "firing" : p->nState == 2 ? "updated" : p->nState == 0 ? "stopped" : "?",
                    p->nForced ? ", forced" : "");
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(p->nTarget >= 0 && p->nTarget < 4 ? s_apszTarget[p->nTarget] : "?");
        ImGui::TableNextColumn();
        ImGui::Text("%d, next %.1fs", p->nShots, p->fNext / 60.0f);
        ImGui::TableNextColumn();
        ImGui::Text("%.0f", p->fDist);
        ImGui::TableNextColumn();
        if (ImGui::SmallButton("teleport"))
            Request(REQ_TELEPORT, 0, 0, p->vTrigger.x, p->vTrigger.y, p->vTrigger.z);
        ImGui::SameLine();
        if (ImGui::SmallButton("look"))
            TrigDrawFreeCamLookAt(&p->vPos);
        ImGui::TableNextColumn();
        if (ImGui::SmallButton(p->nState ? "stop" : "start"))
            Request(REQ_PG, p->nId, p->nState ? PG_STOP : PG_START, 0.0f, 0.0f, 0.0f);
        ImGui::SameLine();
        if (ImGui::SmallButton("fire"))
            Request(REQ_PG, p->nId, PG_FIRE, 0.0f, 0.0f, 0.0f);
        ImGui::SameLine();
        if (ImGui::SmallButton("target me"))
            Request(REQ_PG, p->nId, PG_TARGETME, 0.0f, 0.0f, 0.0f);
        ImGui::SameLine();
        if (ImGui::SmallButton("default"))
            Request(REQ_PG, p->nId, PG_TARGETDEFAULT, 0.0f, 0.0f, 0.0f);
        if (p->nLos >= 0)
        {
            ImGui::SameLine();
            if (ImGui::SmallButton(p->nLos ? "LOS off" : "LOS on"))
                Request(REQ_PG, p->nId, p->nLos ? PG_LOSOFF : PG_LOSON, 0.0f, 0.0f, 0.0f);
        }
        ImGui::SameLine();
        if (ImGui::SmallButton(p->nStagesOn ? "stages off" : "stages on"))
            Request(REQ_PG, p->nId, p->nStagesOn ? PG_STAGESOFF : PG_STAGESON, 0.0f, 0.0f, 0.0f);
        ImGui::PopID();
    }
    ImGui::EndTable();
    for (i = 0; i < n; i++)
        if (s_aPg[i].nId == s_nPgSel)
        {
            ImGui::SeparatorText("Its trigger's settings");
            PgSettings(s_aPg[i].pTrigger);
            break;
        }
    if (s_nPgSel != -1 && i == n)
        ImGui::TextDisabled("(the picked generator is gone)");
}

// ---- Generator ----

// Every field of a projectile generator (type_1227C0, and its kind's own) and
// of the trigger it was set up from (ProjectileGeneratorTrigger), editable:
// Enter sets a value. What each does is from tracing the generator's code
// (unit_11EE20, unit_11DB10, unit_11E440) and the projectiles' (unit_15F1B0,
// unit_161C50); times are frames. The trigger's rows give the attribute command that sets each
// (HandleAttributes, unit_0AD1B0) and how it stores it.
enum
{
    PF_INT,         // an integer (its bits as a real beside it)
    PF_REAL,        // a real (its bits as an integer beside it)
    PF_INTREAL,     // either: an integer the game may read as a real
    PF_HEX,         // a word in hex
    PF_HEX16,       // a half word in hex
    PF_I16,         // a signed half word
    PF_BYTE,        // a byte
    PF_TEXT,        // a string (nSize characters, 32 when 0)
    PF_V2D,         // a 2D vector
    PF_RGBA,        // an RwRGBA
    PF_V3D,         // a vector
    PF_KEY,         // two words: an object's key
    PF_RO           // a pointer or id, shown only
};

struct PgField
{
    const RwChar *pszName;
    RwUInt32 dwOffset;
    RwInt32 nKind;
    RwInt32 nCommand;
    const RwChar *pszDesc;
    RwInt32 nSize;              // PF_TEXT's buffer (0: 32)
};

static const PgField s_aPgGenFields[] =
{
    { "unk_10", offsetof(type_1227C0, unk_10), PF_RO, -1, "the looping fire sound (its emitter handle)" },
    { "unk_14", offsetof(type_1227C0, unk_14), PF_INT, -1, "run state: 0 stopped, 1 just started, 2 running" },
    { "unk_24", offsetof(type_1227C0, unk_24), PF_INT, -1, "the target entity (an entity id)" },
    { "unk_28", offsetof(type_1227C0, unk_28), PF_INT, -1, "a forced shot is due (\"PG_ForcedFire\"); cleared after" },
    { "unk_2C", offsetof(type_1227C0, unk_2C), PF_INT, -1, "the turret is on target; bullets fire only then" },
    { "unk_30", offsetof(type_1227C0, unk_30), PF_INT, -1, "firing stages on (\"PG_EnableFiringStages\")" },
    { "unk_34", offsetof(type_1227C0, unk_34), PF_INT, -1, "firing stage 0 to 2; 3: aim straight at it with an angle spread" },
    { "unk_38", offsetof(type_1227C0, unk_38), PF_INT, -1, "target mode: 0 picked, 1 an entity, 2 a point, 3 its path" },
    { "unk_3C", offsetof(type_1227C0, unk_3C), PF_INT, -1, "bursts left in the stage" },
    { "unk_40", offsetof(type_1227C0, unk_40), PF_INT, -1, "shots left in the burst" },
    { "unk_44", offsetof(type_1227C0, unk_44), PF_REAL, -1, "frames to the next shot (or pause)" },
    { "unk_48", offsetof(type_1227C0, unk_48), PF_INT, -1, "start a new aim walk on the next stage shot" },
    { "unk_4C", offsetof(type_1227C0, unk_4C), PF_REAL, -1, "the turret's turn blend per update (default 0.15)" },
    { "unk_50", offsetof(type_1227C0, unk_50), PF_INT, -1, "shots left before the long pause" },
    { "unk_54", offsetof(type_1227C0, unk_54), PF_V3D, -1, "the target point (the entity's centre, or the script's point)" },
    { "unk_60", offsetof(type_1227C0, unk_60_r), PF_REAL, -1, "scatter radius around a point target (world units)" },
    { "unk_70.right", offsetof(type_1227C0, unk_70) + offsetof(RwMatrixTag, right), PF_V3D, -1, "its matrix: right" },
    { "unk_70.up", offsetof(type_1227C0, unk_70) + offsetof(RwMatrixTag, up), PF_V3D, -1, "its matrix: up" },
    { "unk_70.at", offsetof(type_1227C0, unk_70) + offsetof(RwMatrixTag, at), PF_V3D, -1, "its matrix: at (where it fires; the arc tests)" },
    { "unk_70.pos", offsetof(type_1227C0, unk_70) + offsetof(RwMatrixTag, pos), PF_V3D, -1, "its matrix: position (the muzzle)" },
    { "unk_B0", offsetof(type_1227C0, unk_B0), PF_V3D, -1, "the current aim point" },
    { "unk_BC", offsetof(type_1227C0, unk_BC), PF_V3D, -1, "the previous aim point (sets the aim walk's direction)" },
    { "unk_C8", offsetof(type_1227C0, unk_C8), PF_REAL, -1, "vertical aim offset (minus the target's height)" },
    { "unk_CC", offsetof(type_1227C0, unk_CC), PF_REAL, -1, "its place along its path, 0 to 1" },
    { "unk_D0", offsetof(type_1227C0, unk_D0), PF_REAL, -1, "path step per shot (its sign flips at the ends)" },
    { "unk_D4", offsetof(type_1227C0, unk_D4), PF_INT, -1, "firing-arc check on (always 1)" },
    { "unk_D8", offsetof(type_1227C0, unk_D8), PF_INT, -1, "passed on as the projectile's unk_48 (always 0)" },
    { "unk_DC", offsetof(type_1227C0, unk_DC), PF_RO, -1, "its path (a SplinePath)" },
    { "unk_E0", offsetof(type_1227C0, unk_E0), PF_INT, -1, "its parent entity (an entity id)" },
    { "unk_E4", offsetof(type_1227C0, unk_E4), PF_INT, -1, "its attach point: the parent's 'PGN0'+n tag" },
    { "unk_E8", offsetof(type_1227C0, unk_E8), PF_INT, -1, "its turret (an entity id)" },
    { "unk_EC", offsetof(type_1227C0, unk_EC), PF_INT, -1, "its barrel (an entity id)" },
    { "unk_F0", offsetof(type_1227C0, unk_F0), PF_INT, -1, "follows its parent: 0 no, 1 its frame, 2 the tag" },
    { "unk_F4", offsetof(type_1227C0, unk_F4), PF_INT, -1, "fires from the turret's 'FIRE' tag (2) or frame" },
    { "unk_F8", offsetof(type_1227C0, unk_F8), PF_INT, -1, "the barrel sits on the turret's 'OPR0' tag (2) or frame" },
    { "unk_FC", offsetof(type_1227C0, unk_FC), PF_INT, -1, "the turret's 'ATMT' tag offset (2)" },
    { "unk_104", offsetof(type_1227C0, unk_104), PF_RO, -1, "its id (index and serial)" },
    { "unk_12C", offsetof(type_1227C0, unk_12C), PF_V3D, -1, "the turret's current facing (bullets)" },
    { "unk_138", offsetof(type_1227C0, unk_138), PF_REAL, -1, "frames the turret holds its aim once the target leaves its arc (default 300)" },
    { "unk_13C", offsetof(type_1227C0, unk_13C), PF_REAL, -1, "frames left of that hold" },
    { "unk_140", offsetof(type_1227C0, unk_140), PF_INT, -1, "pause when its turret or barrel is hit: on" },
    { "unk_144", offsetof(type_1227C0, unk_144), PF_REAL, -1, "frames left of that pause (bullets hold fire)" },
    { "unk_148", offsetof(type_1227C0, unk_148), PF_HEX, -1, "that pause's range in frames (low word min, high max)" },
    { "unk_14C", offsetof(type_1227C0, unk_14C), PF_HEX, -1, "the turret's hit points (high word) and the barrel's (low), last seen" },
};

static const PgField s_aPgTrigFields[] =
{
    { "unk_C0", offsetof(ProjectileGeneratorTrigger, unk_C0), PF_KEY, 2, "the parent entity it rides on" },
    { "unk_C8", offsetof(ProjectileGeneratorTrigger, unk_C8), PF_INT, 3, "the parent's attach tag: 'PGN0'+n" },
    { "unk_CC", offsetof(ProjectileGeneratorTrigger, unk_CC), PF_KEY, 4, "the turret entity (turned to the target; its FIRE tag is the muzzle)" },
    { "unk_D4", offsetof(ProjectileGeneratorTrigger, unk_D4), PF_KEY, 6, "the barrel entity (kept on the turret's OPR0 tag)" },
    { "unk_DC", offsetof(ProjectileGeneratorTrigger, unk_DC), PF_INT, 0, "its side: skipped when picking a target (0 is stored as 2)" },
    { "unk_E0", offsetof(ProjectileGeneratorTrigger, unk_E0), PF_INT, 1, "the generator kind: 0 bullets, 1 lobbed shells" },
    { "unk_E4", offsetof(ProjectileGeneratorTrigger, unk_E4), PF_INT, 10, "target choice: 0 the player, 1 the nearest enemy, 2 straight ahead" },
    { "unk_E8", offsetof(ProjectileGeneratorTrigger, unk_E8), PF_KEY, 13, "a spline path to fire along (target mode 3)" },
    { "unk_F0", offsetof(ProjectileGeneratorTrigger, unk_F0), PF_KEY, 11, "a named target point" },
#ifdef CODFH_SP
    { "unk_F8", offsetof(ProjectileGeneratorTrigger, unk_F8), PF_REAL, 12, "scatter radius around a point target" },
#else
    { "unk_F8", offsetof(ProjectileGeneratorTrigger, unk_F8), PF_INTREAL, 12, "scatter radius around a point target" },
#endif
    { "unk_FC", offsetof(ProjectileGeneratorTrigger, unk_FC_r), PF_REAL, 14, "speed along the path, per shot" },
    { "unk_100", offsetof(ProjectileGeneratorTrigger, unk_100), PF_INT, 15, "shots before the long pause" },
    { "unk_104", offsetof(ProjectileGeneratorTrigger, unk_104), PF_INT, 25, "chance (%) a projectile collides with the world (default 100)" },
    { "unk_108", offsetof(ProjectileGeneratorTrigger, unk_108), PF_INT, 47, "shots per burst: from" },
    { "unk_10C", offsetof(ProjectileGeneratorTrigger, unk_10C), PF_INT, 48, "... to" },
    { "unk_110", offsetof(ProjectileGeneratorTrigger, unk_110), PF_INT, 5, "take its firing matrix from the turret on start (default 1)" },
    { "unk_114", offsetof(ProjectileGeneratorTrigger, unk_114_r), PF_REAL, 16, "the long pause, frames" },
    { "unk_118", offsetof(ProjectileGeneratorTrigger, unk_118), PF_REAL, 82, "turret turn blend per update (default 0.15)" },
    { "unk_11C", offsetof(ProjectileGeneratorTrigger, unk_11C), PF_REAL, 83, "frames the turret holds its aim after losing the target (attr x60, default 5 s)" },
    { "unk_120", offsetof(ProjectileGeneratorTrigger, unk_120_r), PF_REAL, 49, "pause between bursts, frames: from" },
    { "unk_124", offsetof(ProjectileGeneratorTrigger, unk_124_r), PF_REAL, 50, "... to" },
    { "unk_128", offsetof(ProjectileGeneratorTrigger, unk_128_r), PF_REAL, 17, "frames between shots" },
    { "unk_12C", offsetof(ProjectileGeneratorTrigger, unk_12C), PF_REAL, 54, "random yaw spread, half angle (scaled by difficulty)" },
    { "unk_130", offsetof(ProjectileGeneratorTrigger, unk_130), PF_REAL, 55, "random pitch spread, half angle (scaled by difficulty)" },
    { "unk_134", offsetof(ProjectileGeneratorTrigger, unk_134), PF_REAL, 56, "horizontal firing arc (the cosine of half its degrees)" },
    { "unk_138", offsetof(ProjectileGeneratorTrigger, unk_138), PF_REAL, 57, "vertical firing arc (the cosine of half its degrees)" },
    { "unk_13C", offsetof(ProjectileGeneratorTrigger, unk_13C), PF_INT, 21, "built-in fire sound 0, 1 or 2 when no sound is set" },
    { "unk_140", offsetof(ProjectileGeneratorTrigger, unk_140), PF_KEY, 19, "the firing (loop) sound" },
    { "unk_148", offsetof(ProjectileGeneratorTrigger, unk_148), PF_KEY, 20, "the sound when firing stops" },
    { "unk_150", offsetof(ProjectileGeneratorTrigger, unk_150), PF_INT, 18, "the stop sound is on" },
    { "unk_154", offsetof(ProjectileGeneratorTrigger, unk_154), PF_INTREAL, 23, "projectile damage (also the blast damage)" },
    { "unk_158", offsetof(ProjectileGeneratorTrigger, unk_158_r), PF_REAL, 24, "projectile launch speed" },
    { "unk_15C", offsetof(ProjectileGeneratorTrigger, unk_15C), PF_REAL, 90, "artillery: the distance picking the near or far incoming sound (x100)" },
    { "unk_160", offsetof(ProjectileGeneratorTrigger, unk_160), PF_REAL, 72, "stage 0: the first shot's miss distance (x100)" },
    { "unk_164", offsetof(ProjectileGeneratorTrigger, unk_164), PF_INT, 73, "stage 0 length in bursts: from" },
    { "unk_168", offsetof(ProjectileGeneratorTrigger, unk_168), PF_INT, 74, "... to" },
    { "unk_16C", offsetof(ProjectileGeneratorTrigger, unk_16C), PF_REAL, 75, "stage 1 miss distance (x100)" },
    { "unk_170", offsetof(ProjectileGeneratorTrigger, unk_170), PF_INT, 76, "stage 1 length in bursts: from" },
    { "unk_174", offsetof(ProjectileGeneratorTrigger, unk_174), PF_INT, 77, "... to" },
    { "unk_178", offsetof(ProjectileGeneratorTrigger, unk_178), PF_REAL, 78, "stage 2 miss distance (x100)" },
    { "unk_17C", offsetof(ProjectileGeneratorTrigger, unk_17C), PF_INT, 79, "stage 2 length in bursts: from" },
    { "unk_180", offsetof(ProjectileGeneratorTrigger, unk_180), PF_INT, 80, "... to" },
    { "unk_184", offsetof(ProjectileGeneratorTrigger, unk_184), PF_REAL, 51, "aim walk step per later shot: from (x100)" },
    { "unk_188", offsetof(ProjectileGeneratorTrigger, unk_188), PF_REAL, 52, "... to (x100)" },
    { "unk_18C", offsetof(ProjectileGeneratorTrigger, unk_18C), PF_REAL, 53, "aim walk random turn about vertical, half range" },
    { "unk_190", offsetof(ProjectileGeneratorTrigger, unk_190), PF_INT, 58, "shells explode on impact" },
    { "unk_194", offsetof(ProjectileGeneratorTrigger, unk_194), PF_REAL, 59, "blast radius (x100)" },
    { "unk_198", offsetof(ProjectileGeneratorTrigger, unk_198), PF_REAL, 60, "fuse time, frames: a nearby blast sets it off (x60)" },
    { "unk_19C", offsetof(ProjectileGeneratorTrigger, unk_19C), PF_INT, -1, "(nothing reads it)" },
    { "unk_1A0", offsetof(ProjectileGeneratorTrigger, unk_1A0), PF_REAL, 62, "blast range, posture class 1 (x100)" },
    { "unk_1A4", offsetof(ProjectileGeneratorTrigger, unk_1A4), PF_REAL, 64, "blast range, posture class 2 (x100)" },
    { "unk_1A8", offsetof(ProjectileGeneratorTrigger, unk_1A8), PF_INTREAL, 63, "maximum blast damage, posture class 1" },
    { "unk_1AC", offsetof(ProjectileGeneratorTrigger, unk_1AC), PF_INTREAL, 65, "maximum blast damage, posture class 2" },
    { "unk_1B0", offsetof(ProjectileGeneratorTrigger, unk_1B0), PF_REAL, 61, "inner radius of full damage (x100)" },
    { "unk_1B4", offsetof(ProjectileGeneratorTrigger, unk_1B4), PF_REAL, 66, "the player's camera shake radius (x100)" },
    { "unk_1B8", offsetof(ProjectileGeneratorTrigger, unk_1B8), PF_INTREAL, 67, "camera shake strength" },
    { "unk_1BC", offsetof(ProjectileGeneratorTrigger, unk_1BC), PF_INT, 68, "(never copied: the game copies unk_1C8 where this likely belongs)" },
    { "unk_1C0", offsetof(ProjectileGeneratorTrigger, unk_1C0), PF_INTREAL, 69, "camera shake fade per frame" },
    { "unk_1C4", offsetof(ProjectileGeneratorTrigger, unk_1C4), PF_REAL, 70, "the player's shock radius (x100)" },
    { "unk_1C8", offsetof(ProjectileGeneratorTrigger, unk_1C8), PF_INTREAL, 71, "shock strength (also copied as the shake duration)" },
    { "unk_1CC", offsetof(ProjectileGeneratorTrigger, unk_1CC), PF_INT, 22, "projectile type: 0 bullet, 1 model shell, 3 artillery" },
    { "unk_1D0", offsetof(ProjectileGeneratorTrigger, unk_1D0), PF_KEY, 22, "the projectile's mesh" },
    { "unk_1D8", offsetof(ProjectileGeneratorTrigger, unk_1D8), PF_INT, 28, "muzzle particle system 1" },
    { "unk_1DC", offsetof(ProjectileGeneratorTrigger, unk_1DC), PF_INT, 31, "muzzle particle system 2" },
    { "unk_1E0", offsetof(ProjectileGeneratorTrigger, unk_1E0), PF_INT, 34, "muzzle particle system 3" },
    { "unk_1E4", offsetof(ProjectileGeneratorTrigger, unk_1E4), PF_INT, 26, "muzzle particles on (all; and system 1)" },
    { "unk_1E8", offsetof(ProjectileGeneratorTrigger, unk_1E8), PF_INT, 29, "muzzle particle 2 on" },
    { "unk_1EC", offsetof(ProjectileGeneratorTrigger, unk_1EC), PF_INT, 32, "muzzle particle 3 on" },
    { "unk_1F0", offsetof(ProjectileGeneratorTrigger, unk_1F0), PF_INT, 27, "muzzle particle 1 follows the generator (default 1)" },
    { "unk_1F4", offsetof(ProjectileGeneratorTrigger, unk_1F4), PF_INT, 30, "muzzle particle 2 follows (default 1)" },
    { "unk_1F8", offsetof(ProjectileGeneratorTrigger, unk_1F8), PF_INT, 33, "muzzle particle 3 follows (default 1)" },
    { "unk_1FC", offsetof(ProjectileGeneratorTrigger, unk_1FC), PF_INT, 81, "bullets: line-of-sight check on" },
    { "unk_200", offsetof(ProjectileGeneratorTrigger, unk_200), PF_INT, 84, "shells: the high lob arc (default 1)" },
    { "unk_204", offsetof(ProjectileGeneratorTrigger, unk_204), PF_REAL, 85, "shell gravity (the attribute negated; default 1)" },
    { "unk_208", offsetof(ProjectileGeneratorTrigger, unk_208), PF_INTREAL, 87, "shells: how fast the fall speeds up" },
    { "unk_20C", offsetof(ProjectileGeneratorTrigger, unk_20C), PF_INTREAL, 88, "shells: frames before the fall speeds up" },
    { "unk_210", offsetof(ProjectileGeneratorTrigger, unk_210), PF_INT, 86, "shells: the faster fall is on" },
    { "unk_214", offsetof(ProjectileGeneratorTrigger, unk_214), PF_REAL, 89, "shell lifetime, seconds (default 15)" },
    { "unk_218", offsetof(ProjectileGeneratorTrigger, unk_218), PF_INT, 98, "(nothing reads it)" },
    { "unk_21C", offsetof(ProjectileGeneratorTrigger, unk_21C), PF_INT, 7, "pause firing when its turret or barrel is hit" },
    { "unk_220", offsetof(ProjectileGeneratorTrigger, unk_220), PF_HEX, 8, "that pause's range in frames (commands 8 and 9: low, high words)" },
    { "unk_228.unk_00", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_00), PF_HEX, 91, "the projectiles' colour (0xAARRGGBB)" },
    { "unk_228.unk_04", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_04), PF_HEX, 92, "the other colour, blended at random (0: the first)" },
    { "unk_228.unk_08", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_08), PF_INTREAL, 93, "the tracer's width" },
    { "unk_228.unk_0C", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_0C), PF_INTREAL, 94, "the tracer's height" },
    { "unk_228.unk_10", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_10), PF_INTREAL, 95, "the shortest life (tracer length)" },
    { "unk_228.unk_14", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_14), PF_INTREAL, 96, "random extra life" },
    { "unk_228.unk_18", offsetof(ProjectileGeneratorTrigger, unk_228) + offsetof(type_429E54, unk_18), PF_INTREAL, 97, "the tracer's fade distance" },
    { "unk_244", offsetof(ProjectileGeneratorTrigger, unk_244), PF_INT, 35, "trail particle effect 1 on" },
    { "unk_248", offsetof(ProjectileGeneratorTrigger, unk_248), PF_INT, 36, "trail effect 1: its particle system" },
    { "unk_24C", offsetof(ProjectileGeneratorTrigger, unk_24C), PF_INT, 37, "trail effect 1: count" },
    { "unk_250", offsetof(ProjectileGeneratorTrigger, unk_250), PF_REAL, 38, "trail effect 1: duration (x60)" },
    { "unk_254", offsetof(ProjectileGeneratorTrigger, unk_254), PF_INT, 39, "trail effect 1: a value (its +0x2C)" },
    { "unk_258", offsetof(ProjectileGeneratorTrigger, unk_258), PF_INT, 40, "trail effect 1: the node it follows" },
    { "unk_25C", offsetof(ProjectileGeneratorTrigger, unk_25C), PF_INT, 41, "trail particle effect 2 on" },
    { "unk_260", offsetof(ProjectileGeneratorTrigger, unk_260), PF_INT, 42, "trail effect 2: its particle system" },
    { "unk_264", offsetof(ProjectileGeneratorTrigger, unk_264), PF_INT, 43, "trail effect 2: count" },
    { "unk_268", offsetof(ProjectileGeneratorTrigger, unk_268), PF_REAL, 44, "trail effect 2: duration (x60)" },
    { "unk_26C", offsetof(ProjectileGeneratorTrigger, unk_26C), PF_INT, 45, "trail effect 2: a value (its +0x2C)" },
    { "unk_270", offsetof(ProjectileGeneratorTrigger, unk_270), PF_INT, 46, "trail effect 2: the node it follows" },
};

// The kinds' own: the bullets' (type_11DB10) and the shells' (type_11E440),
// mostly their projectile settings, copied from the trigger on set-up.
static const PgField s_aPgBulletFields[] =
{
    { "unk_150.unk_04", offsetof(type_11DB10, unk_150) + offsetof(type_10F710_1A48_29C, unk_04), PF_INTREAL, -1, "a plain bullet's damage (trigger unk_154)" },
    { "unk_188.unk_04", offsetof(type_11DB10, unk_188) + offsetof(type_67260, unk_04), PF_INTREAL, -1, "a model projectile's damage" },
    { "unk_188.unk_38", offsetof(type_11DB10, unk_188) + offsetof(type_67260, unk_38), PF_HEX, -1, "the projectile's model (the trigger's mesh)" },
    { "unk_188.unk_40", offsetof(type_11DB10, unk_188) + offsetof(type_67260, unk_40), PF_INTREAL, -1, "gravity (0 here)" },
    { "unk_188.unk_4C", offsetof(type_11DB10, unk_188) + offsetof(type_67260, unk_4C), PF_INTREAL, -1, "blast radius (world units)" },
    { "unk_1D8", offsetof(type_11DB10, unk_1D8), PF_REAL, -1, "fuse time, frames (set off by a nearby blast)" },
    { "unk_1DC", offsetof(type_11DB10, unk_1DC), PF_INTREAL, -1, "blast damage" },
    { "unk_1E0", offsetof(type_11DB10, unk_1E0), PF_REAL, -1, "blast range, posture class 1" },
    { "unk_1E4", offsetof(type_11DB10, unk_1E4), PF_REAL, -1, "blast range, posture class 2" },
    { "unk_1E8", offsetof(type_11DB10, unk_1E8), PF_INTREAL, -1, "maximum blast damage, posture class 1" },
    { "unk_1EC", offsetof(type_11DB10, unk_1EC), PF_INTREAL, -1, "maximum blast damage, posture class 2" },
    { "unk_1F0", offsetof(type_11DB10, unk_1F0), PF_REAL, -1, "inner radius of full damage" },
    { "unk_1F4", offsetof(type_11DB10, unk_1F4), PF_REAL, -1, "the player's camera shake radius" },
    { "unk_1F8", offsetof(type_11DB10, unk_1F8), PF_INTREAL, -1, "camera shake strength" },
    { "unk_1FC", offsetof(type_11DB10, unk_1FC), PF_INTREAL, -1, "camera shake duration (the game copies the shock strength here)" },
    { "unk_200", offsetof(type_11DB10, unk_200), PF_INTREAL, -1, "camera shake fade per frame" },
    { "unk_204", offsetof(type_11DB10, unk_204), PF_REAL, -1, "the player's shock radius" },
    { "unk_208", offsetof(type_11DB10, unk_208), PF_INTREAL, -1, "shock strength" },
    { "unk_20C", offsetof(type_11DB10, unk_20C), PF_INT, -1, "line-of-sight check on (\"PG_EnableLOSCheck\")" },
};

static const PgField s_aPgShellFields[] =
{
    { "unk_150.unk_00", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_00), PF_HEX16, -1, "projectile table: 7 no model, 8 with a model" },
    { "unk_150.unk_04", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_04), PF_INTREAL, -1, "damage" },
    { "unk_150.unk_38", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_38), PF_HEX, -1, "its model (table 8)" },
    { "unk_150.unk_40", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_40), PF_INTREAL, -1, "gravity (the lob solve uses it too)" },
    { "unk_150.unk_4C", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_4C), PF_INTREAL, -1, "blast radius (world units)" },
    { "unk_150.unk_50", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_50), PF_REAL, -1, "fuse time, frames" },
    { "unk_150.unk_54", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_54), PF_INTREAL, -1, "blast damage" },
    { "unk_150.unk_58", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_58), PF_REAL, -1, "blast range, posture class 1" },
    { "unk_150.unk_5C", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_5C), PF_REAL, -1, "blast range, posture class 2" },
    { "unk_150.unk_60", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_60), PF_INTREAL, -1, "maximum blast damage, posture class 1" },
    { "unk_150.unk_64", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_64), PF_INTREAL, -1, "maximum blast damage, posture class 2" },
    { "unk_150.unk_68", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_68), PF_REAL, -1, "inner radius of full damage" },
    { "unk_150.unk_6C", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_6C), PF_REAL, -1, "the player's camera shake radius" },
    { "unk_150.unk_70", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_70), PF_INTREAL, -1, "camera shake strength" },
    { "unk_150.unk_74", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_74), PF_INTREAL, -1, "camera shake duration (the game copies the shock strength here)" },
    { "unk_150.unk_78", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_78), PF_INTREAL, -1, "camera shake fade per frame" },
    { "unk_150.unk_7C", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_7C), PF_REAL, -1, "the player's shock radius" },
    { "unk_150.unk_80", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_80), PF_INTREAL, -1, "shock strength" },
    { "unk_150.unk_84", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_84), PF_INT, -1, "explodes on impact" },
    { "unk_150.unk_88", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_88), PF_INTREAL, -1, "how fast the fall speeds up" },
    { "unk_150.unk_8C", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_8C), PF_INTREAL, -1, "frames before the fall speeds up" },
    { "unk_150.unk_90", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_90), PF_INT, -1, "the faster fall is on" },
    { "unk_150.unk_94", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_94), PF_REAL, -1, "lifetime in seconds (default 15)" },
    { "unk_150.unk_98", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_98), PF_REAL, -1, "predicted flight time, frames" },
    { "unk_150.unk_9C", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_9C), PF_REAL, -1, "distance picking the near or far incoming sound" },
    { "unk_150.unk_A0", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_A0), PF_REAL, -1, "frames until the incoming sound (flight time - 180)" },
    { "unk_150.unk_A4", offsetof(type_11E440, unk_150) + offsetof(type_11E4A0, unk_A4), PF_V3D, -1, "the impact point (the incoming sound is placed there)" },
};

static RwChar s_szPgFieldFilter[32];
static RwBool ReportHas(const RwChar *psz, const RwChar *pszPart);

static void PgFieldRow(RwUInt8 *pBase, const PgField *pField, RwBool bCommands)
{
    RwUInt8 *p = pBase + pField->dwOffset;
    RwUInt32 dw, dw2;

    if (s_szPgFieldFilter[0] && !ReportHas(pField->pszName, s_szPgFieldFilter)
        && !ReportHas(pField->pszDesc, s_szPgFieldFilter))
        return;
    if (!ReadU32(p, &dw) || ((pField->nKind == PF_V3D || pField->nKind == PF_KEY || pField->nKind == PF_V2D)
                             && !ReadU32(p + 4, &dw2)))
        return;
    ImGui::PushID(pField->pszName);
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(pField->pszName);
    if (bCommands)
    {
        ImGui::TableNextColumn();
        if (pField->nCommand >= 0)
            ImGui::Text("%d", pField->nCommand);
    }
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(230.0f);
    switch (pField->nKind)
    {
    case PF_INT:
    case PF_INTREAL:
        ImGui::InputInt("##v", (int *)p, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_REAL:
        ImGui::InputFloat("##v", (float *)p, 0.0f, 0.0f, "%g", ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_HEX:
        ImGui::InputScalar("##v", ImGuiDataType_U32, p, NULL, NULL, "%08X",
                           ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsHexadecimal);
        break;
    case PF_HEX16:
        ImGui::InputScalar("##v", ImGuiDataType_U16, p, NULL, NULL, "%04X",
                           ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsHexadecimal);
        break;
    case PF_I16:
        ImGui::InputScalar("##v", ImGuiDataType_S16, p, NULL, NULL, "%d", ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_BYTE:
        ImGui::InputScalar("##v", ImGuiDataType_U8, p, NULL, NULL, "%u", ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_TEXT:
        ImGui::InputText("##v", (char *)p, pField->nSize > 0 ? pField->nSize : 32,
                         ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_V2D:
        ImGui::InputFloat2("##v", (float *)p, "%g", ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_RGBA:
    {
        RwRGBA *pc = (RwRGBA *)p;
        float af[4] = {pc->red / 255.0f, pc->green / 255.0f, pc->blue / 255.0f, pc->alpha / 255.0f};

        if (ImGui::ColorEdit4("##v", af, ImGuiColorEditFlags_AlphaBar))
        {
            pc->red = (RwUInt8)(af[0] * 255.0f + 0.5f);
            pc->green = (RwUInt8)(af[1] * 255.0f + 0.5f);
            pc->blue = (RwUInt8)(af[2] * 255.0f + 0.5f);
            pc->alpha = (RwUInt8)(af[3] * 255.0f + 0.5f);
        }
        break;
    }
    case PF_V3D:
        ImGui::InputFloat3("##v", (float *)p, "%g", ImGuiInputTextFlags_EnterReturnsTrue);
        break;
    case PF_KEY:
        ImGui::InputScalarN("##v", ImGuiDataType_U32, p, 2, NULL, NULL, "%08X",
                            ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsHexadecimal);
        break;
    default:
        ImGui::Text("0x%08X", dw);
    }
    ImGui::TableNextColumn();
    // the same bits read the other way
    if (pField->nKind == PF_INT || pField->nKind == PF_HEX)
        ImGui::TextDisabled("%g", *(RwReal *)&dw);
    else if (pField->nKind == PF_I16 || pField->nKind == PF_BYTE || pField->nKind == PF_HEX16)
        ImGui::TextDisabled("0x%X", pField->nKind == PF_BYTE ? dw & 0xFF : dw & 0xFFFF);
    else if (pField->nKind == PF_REAL)
        ImGui::TextDisabled("%d", (RwInt32)dw);
    else if (pField->nKind == PF_INTREAL)
    {
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputFloat("##r", (float *)p, 0.0f, 0.0f, "%g", ImGuiInputTextFlags_EnterReturnsTrue);
    }
    ImGui::TableNextColumn();
    ImGui::TextDisabled("%s", pField->pszDesc);
    ImGui::PopID();
}

static void PgFieldTable(const RwChar *pszId, RwUInt8 *pBase, const PgField *pFields, RwInt32 nFields,
                         RwBool bCommands)
{
    RwInt32 i;

    if (!ImGui::BeginTable(pszId, bCommands ? 5 : 4, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    ImGui::TableSetupColumn("field");
    if (bCommands)
        ImGui::TableSetupColumn("command");
    ImGui::TableSetupColumn("value (Enter sets it)");
    ImGui::TableSetupColumn("the other way");
    ImGui::TableSetupColumn("what it is");
    ImGui::TableHeadersRow();
    __try
    {
        for (i = 0; i < nFields; i++)
            PgFieldRow(pBase, &pFields[i], bCommands);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    ImGui::EndTable();
}

static void TabGenerator()
{
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vFrom = {0.0f, 0.0f, 0.0f};
    RwInt32 n, i, nSel = -1;
    RwChar szPreview[64];

    if (pPlayer == NULL || !PlayerPosition(pPlayer, &vFrom))
        vFrom.x = vFrom.y = vFrom.z = 0.0f;
    n = PgList(&vFrom);
    for (i = 0; i < n; i++)
        if (s_aPg[i].nId == s_nPgSel)
            nSel = i;
    if (nSel < 0 && n > 0)
    {
        nSel = 0;
        s_nPgSel = s_aPg[0].nId;
    }
    if (nSel < 0)
    {
        ImGui::Text("No projectile generators are live.");
        return;
    }
    sprintf(szPreview, "%d (%s, %.0f away)", s_aPg[nSel].nId & 0xFFFF, s_aPg[nSel].nKind ? "shells" : "bullets",
            s_aPg[nSel].fDist);
    ImGui::SetNextItemWidth(240.0f);
    if (ImGui::BeginCombo("generator (nearest first)", szPreview))
    {
        for (i = 0; i < n; i++)
        {
            RwChar sz[64];

            sprintf(sz, "%d (%s, %.0f away)##%d", s_aPg[i].nId & 0xFFFF, s_aPg[i].nKind ? "shells" : "bullets",
                    s_aPg[i].fDist, i);
            if (ImGui::Selectable(sz, i == nSel))
                s_nPgSel = s_aPg[i].nId;
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("look"))
        TrigDrawFreeCamLookAt(&s_aPg[nSel].vPos);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(160.0f);
    ImGui::InputText("filter##pgf", s_szPgFieldFilter, sizeof(s_szPgFieldFilter));
    if (ImGui::CollapsingHeader("The generator (type_1227C0), live", ImGuiTreeNodeFlags_DefaultOpen))
        PgFieldTable("pggen", (RwUInt8 *)s_aPg[nSel].pGen, s_aPgGenFields,
                     sizeof(s_aPgGenFields) / sizeof(s_aPgGenFields[0]), FALSE);
    if (s_aPg[nSel].nKind == 0 &&
        ImGui::CollapsingHeader("The bullets' own (type_11DB10)", ImGuiTreeNodeFlags_DefaultOpen))
        PgFieldTable("pgbul", (RwUInt8 *)s_aPg[nSel].pGen, s_aPgBulletFields,
                     sizeof(s_aPgBulletFields) / sizeof(s_aPgBulletFields[0]), FALSE);
    if (s_aPg[nSel].nKind == 1 &&
        ImGui::CollapsingHeader("The shells' own (type_11E440)", ImGuiTreeNodeFlags_DefaultOpen))
        PgFieldTable("pgshl", (RwUInt8 *)s_aPg[nSel].pGen, s_aPgShellFields,
                     sizeof(s_aPgShellFields) / sizeof(s_aPgShellFields[0]), FALSE);
    if (ImGui::CollapsingHeader("Its trigger (ProjectileGeneratorTrigger)", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (s_aPg[nSel].pTrigger == NULL)
            ImGui::Text("It has no trigger.");
        else
        {
            ImGui::TextDisabled("The generator copies some of these when it is set up (into the rows above) and "
                                "reads others as it fires. Times are in frames (60 a second).");
            PgFieldTable("pgtrig", (RwUInt8 *)s_aPg[nSel].pTrigger, s_aPgTrigFields,
                         sizeof(s_aPgTrigFields) / sizeof(s_aPgTrigFields[0]), TRUE);
        }
    }
}

// ---- Trigger ----

// Every field of any trigger, editable: Enter sets a value. The tables
// (triggerfields.inc, generated by tools/gen_triggerfields.py) hold each
// class's own fields with the attribute command that sets them and what
// they do where traced (tools/triggerfields_desc.json). A trigger's class
// is found by its kind (vf_008); the classes that share one are picked by
// hand. Most fields are read when the trigger acts (its spawn, its set-up);
// the ones marked (live) are read as the game runs.
struct TrigFieldClass
{
    const RwChar *pszClass;
    RwInt32 nKind;
    const RwChar *pszBase;
    const PgField *pFields;
    RwInt32 nFields;
};

#include "triggerfields.inc"

#define TRIGFIELD_CLASSES (RwInt32)(sizeof(s_aTrigFieldClasses) / sizeof(s_aTrigFieldClasses[0]))

static const TrigFieldClass *TrigFieldClassNamed(const RwChar *pszName)
{
    RwInt32 i;

    for (i = 0; i < TRIGFIELD_CLASSES; i++)
        if (strcmp(s_aTrigFieldClasses[i].pszClass, pszName) == 0)
            return &s_aTrigFieldClasses[i];
    return NULL;
}

static RwInt32 TrigKind(Trigger *pTrigger)
{
    __try
    {
        return pTrigger->vf_008();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return -1;
    }
}

// The class picked for a kind shared by several ("view as"), by kind.
static RwInt32 s_anTrigViewAs[0x40];

static void TabTrigger()
{
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vFrom = {0.0f, 0.0f, 0.0f};
    RwInt32 i, nLast = dword_429D00, nKind, nBest = -1, nHandle, nCands = 0;
    RwReal fBest = 1e30f;
    Trigger *pTrigger = NULL;
    const TrigFieldClass *apCands[8];
    const TrigFieldClass *pClass;
    RwChar szPreview[96];

    if (pPlayer == NULL || !PlayerPosition(pPlayer, &vFrom))
        vFrom.x = vFrom.y = vFrom.z = 0.0f;
    if (nLast >= 2000)
        nLast = 1999;
    // (none picked: the nearest)
    if (s_nTrigEdit < 0 || s_nTrigEdit > nLast || dword_4CFE30[s_nTrigEdit] == 0)
    {
        for (i = 0; i <= nLast; i++)
        {
            Trigger *p = (Trigger *)dword_4CFE30[i];
            RwReal fX, fY, fZ, fD;

            if (p == NULL || !ReadF32(&p->unk_90, &fX) || !ReadF32(&p->unk_94, &fY) || !ReadF32(&p->unk_98, &fZ))
                continue;
            fD = (fX - vFrom.x) * (fX - vFrom.x) + (fY - vFrom.y) * (fY - vFrom.y) + (fZ - vFrom.z) * (fZ - vFrom.z);
            if (fD < fBest)
            {
                fBest = fD;
                nBest = i;
            }
        }
        nHandle = nBest;
    }
    else
        nHandle = s_nTrigEdit;
    if (nHandle >= 0)
        pTrigger = (Trigger *)dword_4CFE30[nHandle];
    nKind = pTrigger ? TrigKind(pTrigger) : -1;

    if (pTrigger)
        sprintf(szPreview, "%d: %s%s", nHandle, TrigDrawKindName(pTrigger), s_nTrigEdit < 0 ? " (the nearest)" : "");
    else
        strcpy(szPreview, "none");
    ImGui::SetNextItemWidth(360.0f);
    if (ImGui::BeginCombo("trigger", szPreview, ImGuiComboFlags_HeightLarge))
    {
        if (ImGui::Selectable("the nearest", s_nTrigEdit < 0))
            s_nTrigEdit = -1;
        for (i = 0; i <= nLast; i++)
        {
            Trigger *p = (Trigger *)dword_4CFE30[i];
            RwChar sz[80];

            if (p == NULL || TrigKind(p) < 0)
                continue;
            sprintf(sz, "%d: %s##t%d", i, TrigDrawKindName(p), i);
            if (ImGui::Selectable(sz, i == s_nTrigEdit))
                s_nTrigEdit = i;
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::TextDisabled("at 0x%08X; or pick one in the List tab", (RwUInt32)pTrigger);
    if (pTrigger == NULL)
    {
        ImGui::Text("No trigger to edit.");
        return;
    }
    // its class: by its kind, picked by hand when several share it
    for (i = 0; i < TRIGFIELD_CLASSES && nCands < 8; i++)
        if (s_aTrigFieldClasses[i].nKind == nKind && nKind > 0)
            apCands[nCands++] = &s_aTrigFieldClasses[i];
    pClass = NULL;
    if (nCands > 0)
    {
        RwInt32 nPick = nKind < 0x40 ? s_anTrigViewAs[nKind] : 0;

        if (nPick >= nCands)
            nPick = 0;
        pClass = apCands[nPick];
        if (nCands > 1)
        {
            ImGui::SetNextItemWidth(260.0f);
            if (ImGui::BeginCombo("view as (classes of this kind)", pClass->pszClass))
            {
                for (i = 0; i < nCands; i++)
                    if (ImGui::Selectable(apCands[i]->pszClass, i == nPick) && nKind < 0x40)
                        s_anTrigViewAs[nKind] = i;
                ImGui::EndCombo();
            }
        }
    }
    ImGui::SetNextItemWidth(160.0f);
    ImGui::InputText("filter##tf", s_szPgFieldFilter, sizeof(s_szPgFieldFilter));
    ImGui::SameLine();
    ImGui::TextDisabled("[how] rows: only the storage is known yet");
    if (pClass == NULL)
        ImGui::Text("Kind %d has no table; only the base Trigger's fields.", nKind);
    else
    {
        // the class's own, then its bases' (other than Trigger)
        const TrigFieldClass *pC = pClass;
        RwInt32 nDepth = 0;

        while (pC != NULL && nDepth++ < 4)
        {
            RwChar szHead[96];

            sprintf(szHead, "%s%s", pC->pszClass, pC == pClass ? "" : " (its base)");
            if (ImGui::CollapsingHeader(szHead, ImGuiTreeNodeFlags_DefaultOpen))
                PgFieldTable(pC->pszClass, (RwUInt8 *)pTrigger, pC->pFields, pC->nFields, TRUE);
            if (pC->pszBase[0] == 0 || strcmp(pC->pszBase, "Trigger") == 0)
                break;
            pC = TrigFieldClassNamed(pC->pszBase);
        }
    }
    pClass = TrigFieldClassNamed("Trigger");
    if (pClass && ImGui::CollapsingHeader("Trigger (the base: shape, flags, matrix, script)"))
        PgFieldTable("Trigger", (RwUInt8 *)pTrigger, pClass->pFields, pClass->nFields, TRUE);
}

// ---- Shell ----

// The shell manager's settings (dword_4B8EF0, type_E8F90), live and
// editable: the level's (CShellLevelBehaviorClass: the command column) and
// the front end's (CShellBehaviorClass: its commands in the text). The level
// behaviour's commands 6 and 7 name the opening and closing movies, kept
// elsewhere (unk_4B8EA8, unk_4B8EB0).
static const PgField s_aShellFields[] =
{
    { "unk_00", offsetof(type_E8F90, unk_00), PF_REAL, 0, "north offset, degrees: the compass and radar turn by it (live)", 0 },
    { "unk_04", offsetof(type_E8F90, unk_04), PF_INTREAL, -1, "text manager lines: x, pixels (CShellBehavior 84) (live)", 0 },
    { "unk_08", offsetof(type_E8F90, unk_08), PF_INTREAL, -1, "text manager lines: y, pixels (CShellBehavior 84) (live)", 0 },
    { "unk_0C", offsetof(type_E8F90, unk_0C) + 0, PF_RGBA, -1, "text colour, kind 0 (CShellBehavior 85) (live)", 0 },
    { "unk_0C+4", offsetof(type_E8F90, unk_0C) + 4, PF_RGBA, -1, "text colour, kind 2 (CShellBehavior 86) (live)", 0 },
    { "unk_0C+8", offsetof(type_E8F90, unk_0C) + 8, PF_RGBA, -1, "text colour, kind 1 (CShellBehavior 87) (live)", 0 },
    { "unk_0C+12", offsetof(type_E8F90, unk_0C) + 12, PF_REAL, -1, "text typing interval, seconds (CShellBehavior 88) (live)", 0 },
    { "unk_1C", offsetof(type_E8F90, unk_1C), PF_INTREAL, -1, "CShellBehavior 104, ms (nothing reads it)", 0 },
    { "unk_20", offsetof(type_E8F90, unk_20), PF_INTREAL, -1, "CShellBehavior 105, ms (nothing reads it)", 0 },
    { "unk_24", offsetof(type_E8F90, unk_24), PF_INTREAL, 3, "HUD items: alpha at rest, 0 to 1 (live)", 0 },
    { "unk_28", offsetof(type_E8F90, unk_28), PF_INTREAL, 4, "HUD items: alpha when flashed, 0 to 1 (live)", 0 },
    { "unk_2C", offsetof(type_E8F90, unk_2C), PF_REAL, 2, "how long a flashed HUD item stays lit, ms (live)", 0 },
    { "unk_30", offsetof(type_E8F90, unk_30), PF_RO, -1, "two colours (CShellBehavior 26, 27; nothing reads them)", 0 },
    { "unk_38", offsetof(type_E8F90, unk_38), PF_RGBA, 5, "crosshair colour (the command pushes it to the HUD at once; this copy is unread)", 0 },
    { "unk_3C", offsetof(type_E8F90, unk_3C) + 0, PF_REAL, -1, "the player's aim ray length, units (CShellBehavior 28); 0 skips the aim pass (live)", 0 },
    { "unk_40", offsetof(type_E8F90, unk_40), PF_REAL, -1, "radar range: a blip sits at distance/100/this (5 at set-up) (live)", 0 },
    { "unk_44", offsetof(type_E8F90, unk_44) + 0, PF_RGBA, -1, "vehicle armour bar colour, one end (CShellBehavior 68)", 0 },
    { "unk_44+4", offsetof(type_E8F90, unk_44) + 4, PF_RGBA, -1, "vehicle armour bar colour, the other end (CShellBehavior 69)", 0 },
    { "unk_64", offsetof(type_E8F90, unk_64), PF_INTREAL, -1, "pause screen objectives list: x (CShellBehavior 89; single player)", 0 },
    { "unk_68", offsetof(type_E8F90, unk_68), PF_INTREAL, -1, "pause screen objectives list: y (CShellBehavior 89; single player)", 0 },
    { "unk_6C", offsetof(type_E8F90, unk_6C), PF_RO, -1, "pause fade, help text colour, place, size, fade and hold, box, scroll speed (CShellBehavior 94-118)", 0 },
    { "unk_B4", offsetof(type_E8F90, unk_B4), PF_KEY, -1, "pickup text, kinds 75-77", 0 },
    { "unk_BC", offsetof(type_E8F90, unk_BC), PF_KEY, -1, "Luger ammo pickup text", 0 },
    { "unk_C4", offsetof(type_E8F90, unk_C4), PF_KEY, -1, "PPSH ammo pickup text", 0 },
    { "unk_CC", offsetof(type_E8F90, unk_CC), PF_KEY, -1, "Thompson ammo pickup text", 0 },
    { "unk_D4", offsetof(type_E8F90, unk_D4), PF_KEY, -1, "MP40 ammo pickup text", 0 },
    { "unk_DC", offsetof(type_E8F90, unk_DC), PF_KEY, -1, "Sten ammo pickup text", 0 },
    { "unk_E4", offsetof(type_E8F90, unk_E4), PF_KEY, -1, "BAR ammo pickup text", 0 },
    { "unk_EC", offsetof(type_E8F90, unk_EC), PF_KEY, -1, "DP ammo pickup text", 0 },
    { "unk_F4", offsetof(type_E8F90, unk_F4), PF_KEY, -1, "MG42 ammo pickup text", 0 },
    { "unk_FC", offsetof(type_E8F90, unk_FC), PF_KEY, -1, "Bren ammo pickup text", 0 },
    { "unk_104", offsetof(type_E8F90, unk_104), PF_KEY, -1, "M1919A6 ammo pickup text", 0 },
    { "unk_10C", offsetof(type_E8F90, unk_10C), PF_KEY, -1, "Enfield ammo pickup text", 0 },
    { "unk_114", offsetof(type_E8F90, unk_114), PF_KEY, -1, "G43 ammo pickup text", 0 },
    { "unk_11C", offsetof(type_E8F90, unk_11C), PF_KEY, -1, "Kar98 ammo pickup text", 0 },
    { "unk_124", offsetof(type_E8F90, unk_124), PF_KEY, -1, "Nagant Sniper ammo pickup text", 0 },
    { "unk_12C", offsetof(type_E8F90, unk_12C), PF_KEY, -1, "(nothing reads it)", 0 },
    { "unk_134", offsetof(type_E8F90, unk_134), PF_KEY, -1, "Springfield ammo pickup text", 0 },
    { "unk_13C", offsetof(type_E8F90, unk_13C), PF_KEY, -1, "Bazooka ammo pickup text", 0 },
    { "unk_144", offsetof(type_E8F90, unk_144), PF_KEY, -1, "Mosin Nagant ammo pickup text", 0 },
    { "unk_14C", offsetof(type_E8F90, unk_14C), PF_KEY, -1, "Panzerschreck ammo pickup text", 0 },
    { "unk_154", offsetof(type_E8F90, unk_154), PF_KEY, -1, "Grease Gun ammo pickup text", 0 },
    { "unk_15C", offsetof(type_E8F90, unk_15C), PF_KEY, -1, "M1 Garand ammo pickup text", 0 },
    { "unk_164", offsetof(type_E8F90, unk_164), PF_KEY, -1, "pickup text, kinds 78-79 (?)", 0 },
    { "unk_16C", offsetof(type_E8F90, unk_16C), PF_KEY, -1, "pickup text, kinds 80-81 (?)", 0 },
    { "unk_174", offsetof(type_E8F90, unk_174), PF_KEY, -1, "pickup text, kinds 82-83 (?)", 0 },
    { "unk_17C", offsetof(type_E8F90, unk_17C), PF_KEY, -1, "pickup text, kinds 84-85 (?)", 0 },
    { "unk_184", offsetof(type_E8F90, unk_184), PF_KEY, -1, "pickup text, kinds 86-87 (?)", 0 },
    { "unk_18C", offsetof(type_E8F90, unk_18C), PF_KEY, -1, "pickup text, kinds 88-89 (?)", 0 },
    { "unk_194", offsetof(type_E8F90, unk_194), PF_KEY, -1, "teddy bear pickup text", 0 },
    { "unk_19C", offsetof(type_E8F90, unk_19C), PF_KEY, -1, "Kaiser bear pickup text", 0 },
    { "unk_1A4", offsetof(type_E8F90, unk_1A4), PF_KEY, -1, "Sticky bear pickup text", 0 },
    { "unk_1AC", offsetof(type_E8F90, unk_1AC), PF_KEY, -1, "PPSH weapon pickup text", 0 },
    { "unk_1B4", offsetof(type_E8F90, unk_1B4), PF_KEY, -1, "Luger weapon pickup text", 0 },
    { "unk_1BC", offsetof(type_E8F90, unk_1BC), PF_KEY, -1, "Thompson weapon pickup text", 0 },
    { "unk_1C4", offsetof(type_E8F90, unk_1C4), PF_KEY, -1, "MP40 weapon pickup text", 0 },
    { "unk_1CC", offsetof(type_E8F90, unk_1CC), PF_KEY, -1, "Sten weapon pickup text", 0 },
    { "unk_1D4", offsetof(type_E8F90, unk_1D4), PF_KEY, -1, "BAR weapon pickup text", 0 },
    { "unk_1DC", offsetof(type_E8F90, unk_1DC), PF_KEY, -1, "DP weapon pickup text", 0 },
    { "unk_1E4", offsetof(type_E8F90, unk_1E4), PF_KEY, -1, "MG42 weapon pickup text", 0 },
    { "unk_1EC", offsetof(type_E8F90, unk_1EC), PF_KEY, -1, "Bren weapon pickup text", 0 },
    { "unk_1F4", offsetof(type_E8F90, unk_1F4), PF_KEY, -1, "M1919A6 weapon pickup text", 0 },
    { "unk_1FC", offsetof(type_E8F90, unk_1FC), PF_KEY, -1, "Mosin Nagant weapon pickup text", 0 },
    { "unk_204", offsetof(type_E8F90, unk_204), PF_KEY, -1, "Kar98 weapon pickup text", 0 },
    { "unk_20C", offsetof(type_E8F90, unk_20C), PF_KEY, -1, "M1 Garand weapon pickup text", 0 },
    { "unk_214", offsetof(type_E8F90, unk_214), PF_KEY, -1, "Springfield weapon pickup text", 0 },
    { "unk_21C", offsetof(type_E8F90, unk_21C), PF_KEY, -1, "Bazooka weapon pickup text", 0 },
    { "unk_224", offsetof(type_E8F90, unk_224), PF_KEY, -1, "Panzerschreck weapon pickup text", 0 },
    { "unk_22C", offsetof(type_E8F90, unk_22C), PF_KEY, -1, "Enfield weapon pickup text", 0 },
    { "unk_234", offsetof(type_E8F90, unk_234), PF_KEY, -1, "G43 weapon pickup text", 0 },
    { "unk_23C", offsetof(type_E8F90, unk_23C), PF_KEY, -1, "Grease Gun weapon pickup text", 0 },
    { "unk_244", offsetof(type_E8F90, unk_244), PF_KEY, -1, "Nagant Sniper weapon pickup text", 0 },
    { "unk_24C", offsetof(type_E8F90, unk_24C), PF_KEY, -1, "objective updated message text", 0 },
    { "unk_254", offsetof(type_E8F90, unk_254), PF_KEY, -1, "level end checkpoint message text", 0 },
    { "unk_25C", offsetof(type_E8F90, unk_25C), PF_KEY, -1, "checkpoint message text", 0 },
    { "unk_264", offsetof(type_E8F90, unk_264), PF_INTREAL, -1, "hit direction marker lifetime, ms (CShellBehavior 100) (live)", 0 },
    { "unk_268", offsetof(type_E8F90, unk_268) + 0, PF_REAL, -1, "name label: lift above the head bone (CShellBehavior 12) (live)", 0 },
    { "unk_268+4", offsetof(type_E8F90, unk_268) + 4, PF_REAL, -1, "name label: show time, frames (13) (live)", 0 },
    { "unk_268+8", offsetof(type_E8F90, unk_268) + 8, PF_REAL, -1, "name label: fade start, frames (14) (live)", 0 },
    { "unk_268+12", offsetof(type_E8F90, unk_268) + 12, PF_REAL, -1, "name label: fade distance squared, near (15) (live)", 0 },
    { "unk_268+16", offsetof(type_E8F90, unk_268) + 16, PF_REAL, -1, "name label: fade distance squared, far (16) (live)", 0 },
    { "unk_27C", offsetof(type_E8F90, unk_27C), PF_INT, -1, "CShellBehavior 173 (nothing reads it)", 0 },
    { "unk_280", offsetof(type_E8F90, unk_280), PF_INT, -1, "CShellBehavior 174 (nothing reads it)", 0 },
    { "unk_284", offsetof(type_E8F90, unk_284), PF_RO, -1, "a 2D point and a colour (CShellBehavior 175, 176; nothing reads them)", 0 },
    { "unk_29C", offsetof(type_E8F90, unk_29C), PF_INT, 8, "the credits flag (dword_4B918C): Credits.bik plays after the closing movie", 0 },
    { "unk_2A0", offsetof(type_E8F90, unk_2A0), PF_RO, -1, "the HUD (dword_4B9190), built with flag 4", 0 },
    { "unk_2A4", offsetof(type_E8F90, unk_2A4), PF_HEX, -1, "module flags: 4 the HUD (live)", 0 },
    { "unk_2A8", offsetof(type_E8F90, unk_2A8), PF_RO, -1, "the shell camera", 0 },
    { "unk_2AC", offsetof(type_E8F90, unk_2AC), PF_TEXT, -1, "the shell's fonts path", 128 },
    { "unk_32C", offsetof(type_E8F90, unk_32C), PF_REAL, -1, "loading bar progress, 0 to 1", 0 },
};

static void TabShell()
{
    ImGui::TextDisabled("dword_4B8EF0 at 0x%08X. The rows marked (live) are read as the game runs.",
                        (RwUInt32)&dword_4B8EF0);
    ImGui::SetNextItemWidth(160.0f);
    ImGui::InputText("filter##shell", s_szPgFieldFilter, sizeof(s_szPgFieldFilter));
    PgFieldTable("shell", (RwUInt8 *)(type_E8F90 *)&dword_4B8EF0, s_aShellFields,
                 sizeof(s_aShellFields) / sizeof(s_aShellFields[0]), TRUE);
}

// ---- Switches and tunables ----

// The game's leftover switches and tuning values (a whole-tree scan for
// globals tested but never set, then traced): declared here with their
// definitions' types; those of one build only guarded.
extern RwInt32 dword_4CF444;
extern RwInt32 dword_4E5F00;
extern RwUInt8 byte_4CF400;
extern RwUInt8 byte_4CF7D0;
extern RwInt32 dword_4B6764;
extern RwInt32 dword_4B8210;
#ifndef CODFH_SP
extern RwInt32 dword_4FBC3C;
#endif
extern RwInt32 dword_44E840;
extern RwInt32 dword_44E844;
extern RwInt32 dword_44E848;
extern RwInt32 dword_44E84C;
extern RwInt32 dword_44E850;
extern RwInt32 dword_44E854;
extern RwInt32 dword_44E858;
extern RwInt32 dword_44E85C;
extern RwInt32 dword_44E838;
extern RwInt32 dword_44E83C;
extern RwInt32 dword_44E868;
extern RwInt32 dword_44E884;
extern bool byte_4B92AE;
extern bool byte_4B8975;
extern RwReal flt_429C38;
extern RwReal flt_4CF7CC;
extern RwInt32 dword_4B87DC;
extern bool byte_42929C;
extern RwReal dword_42928C;
extern RwReal dword_4275C8;
extern RwReal dword_4290C0;
extern RwReal dword_4290C4;
extern RwReal dword_4290C8;
extern RwReal flt_427400;
extern RwReal flt_4275B8;
extern RwReal flt_4275BC;
extern RwReal flt_4275C0;
extern RwReal flt_4275C4;
extern RwReal flt_4275DC;
extern RwReal flt_4275E0;
extern RwReal flt_4275E4;
extern RwReal flt_4275E8;
extern RwReal flt_427680;
extern RwReal flt_4290CC;
extern RwReal flt_4290D0;
extern RwReal flt_4290DC;
extern RwReal flt_4290E0;
extern RwReal flt_429AA4;
extern RwReal flt_429CC0;
extern RwReal flt_429CC4;
extern RwReal flt_429E94;
extern RwReal flt_429E98;
extern RwReal flt_429E9C;
extern RwReal flt_4C0198;
extern RwInt32 dword_4296D8;
extern RwUInt32 dword_4296F0;
extern RwReal flt_4296DC;
extern RwReal flt_4296E0;
extern RwReal flt_4296E4;
extern RwReal flt_4296E8;
extern RwInt32 dword_429D74;
extern RwInt32 dword_429D8C;
extern RwReal flt_429D68;
extern RwReal flt_429D88;
extern RwReal flt_429D9C;
extern RwReal flt_429DD8;
extern RwReal flt_429DDC;
extern RwReal flt_429DE0;
extern RwInt32 dword_429B3C;
extern RwReal flt_429748;
extern RwReal flt_42974C;
extern RwReal flt_429B38;
extern RwReal flt_42C778;
extern RwReal flt_42C77C;
extern RwReal dword_429E40;
extern RwReal dword_429E78;
extern RwInt32 dword_429E7C;
extern RwReal dword_429E80;
extern RwReal dword_429E88;
extern RwReal dword_429E8C;
extern RwReal flt_429E20;
extern RwReal flt_429E24;
extern RwReal flt_4293E4;
extern RwReal flt_4293E8;
extern RwReal flt_429BD0;
extern RwReal flt_429E2C;
extern RwReal flt_4290E8;
extern RwReal flt_4290EC;
extern RwReal flt_42925C;
extern RwReal flt_429CA4;
extern RwReal flt_429CA8;

static void CheckInt(const RwChar *pszLabel, RwInt32 *pn);

static void CheckByte(const RwChar *pszLabel, RwUInt8 *pb)
{
    bool b = *pb != 0;

    if (ImGui::Checkbox(pszLabel, &b))
        *pb = b ? 1 : 0;
}

static void CheatsLevelRender()
{
    ImGui::SeparatorText("Level and render (nothing in the game sets these)");
    {
        // the time scale's frame step (mode 5: a frame each "step"; nothing sets it) and its
        // speed lock (mode 3: real time, the slow motion blocked)
        bool bStep = dword_4B87DC == 5, bLock = dword_4B87DC == 3;

        if (ImGui::Checkbox("frame step (time scale mode 5)", &bStep))
            dword_4B87DC = bStep ? 5 : 0;
        ImGui::SameLine();
        if (ImGui::Button("step") && dword_4B87DC == 5)
            byte_42929C = true;
        ImGui::SameLine();
        if (ImGui::Checkbox("speed lock (mode 3: no slow motion)", &bLock))
        {
            dword_4B87DC = bLock ? 3 : 0;
            if (bLock)
                dword_42928C = 0.0f;
        }
        ImGui::SameLine();
        ImGui::TextDisabled("mode %d", dword_4B87DC);
    }
    if (ImGui::Button("widescreen toggle (byte_4B8975)"))
        byte_4B8975 = true;
    ImGui::SameLine();
    ImGui::TextDisabled("now %s", dword_4CF9A8 ? "wide" : "4:3");
    {
        bool b = byte_4CF9AC;

        if (ImGui::Checkbox("FOV zoom (byte_4CF9AC)", &b))
            byte_4CF9AC = b;
        ImGui::SameLine();
        ImGui::SetNextItemWidth(160.0f);
        ImGui::SliderFloat("zoom (flt_429C38)", &flt_429C38, 0.1f, 4.0f, "%.2f");
    }
    {
        static float s_fFar = 5000.0f;

        ImGui::SetNextItemWidth(160.0f);
        ImGui::InputFloat("##far", &s_fFar, 0.0f, 0.0f, "%.0f");
        ImGui::SameLine();
        if (ImGui::Button("fade the far clip to it over 30 s (flt_4CF7CC)") && s_fFar > 0.0f)
            flt_4CF7CC = s_fFar;
    }
    if (ImGui::Button("queue the 'Console initialized' lines (byte_4B92AE)"))
        byte_4B92AE = true;
    CheckInt("hide the moving objects in the level sections (dword_4CF444)", (RwInt32 *)&dword_4CF444);
    CheckInt("camera shake off (dword_4E5F00)", (RwInt32 *)&dword_4E5F00);
    CheckByte("keep the fade quad drawn (byte_4CF400)", (RwUInt8 *)&byte_4CF400);
    CheckByte("draw the memory card message (byte_4CF7D0)", (RwUInt8 *)&byte_4CF7D0);
    CheckInt("find zones by the sections' collision (dword_4B6764)", (RwInt32 *)&dword_4B6764);
    CheckInt("entity zones off (dword_4B8210; set it before a level loads)", (RwInt32 *)&dword_4B8210);
#ifndef CODFH_SP
    CheckInt("remote soldiers in one test animation (dword_4FBC3C; multiplayer)", (RwInt32 *)&dword_4FBC3C);
#endif
}

static void CheatsAudio()
{
    ImGui::SeparatorText("Audio (the level's CGlobalSounds sets these; read live)");
    CheckInt("mute: dialog", (RwInt32 *)&dword_44E840);
    CheckInt("mute: foley", (RwInt32 *)&dword_44E844);
    CheckInt("mute: weapons fire", (RwInt32 *)&dword_44E848);
    CheckInt("mute: vehicles", (RwInt32 *)&dword_44E84C);
    CheckInt("mute: weapon foley", (RwInt32 *)&dword_44E850);
    CheckInt("mute: debris", (RwInt32 *)&dword_44E854);
    CheckInt("mute: ambience 1", (RwInt32 *)&dword_44E858);
    CheckInt("mute: ambience 2", (RwInt32 *)&dword_44E85C);
    CheckInt("warning sound for an untagged index sound (dword_44E838)", &dword_44E838);
    CheckInt("warning sound for an index alias without the index (dword_44E83C)", &dword_44E83C);
    CheckInt("log the music streams (dword_44E868, to the port's log)", &dword_44E868);
    CheckInt("keep the music playing through the pause (dword_44E884; single player)", &dword_44E884);
}

// The tuning values no code changes (each read where its row says).
static const PgField s_aTunables[] =
{
    { "dword_4275C8", (RwUInt32)&dword_4275C8, PF_REAL, -1, "AI: Default distance an AI anchor must move before re-targeting (units, horizontal) (unit_0154C0.cpp:3683)", 0 },
    { "dword_4290C0", (RwUInt32)&dword_4290C0, PF_REAL, -1, "AI: Facing cosine sorting a soldier contact as ahead/behind (~49 degrees) (unit_0929A0.cpp:2926)", 0 },
    { "dword_4290C4", (RwUInt32)&dword_4290C4, PF_REAL, -1, "AI: Cosine margin past perpendicular for side contacts (~6 degrees) (unit_0929A0.cpp:2992)", 0 },
    { "dword_4290C8", (RwUInt32)&dword_4290C8, PF_REAL, -1, "AI: Right-axis cosine splitting side contacts into left/right (60 degrees) (unit_0929A0.cpp:2998)", 0 },
    { "flt_427400", (RwUInt32)&flt_427400, PF_REAL, -1, "AI: AI wait before AttackStand on out-of-range target (frames, deltaTime units) (unit_012000.cpp:1763)", 0 },
    { "flt_4275B8", (RwUInt32)&flt_4275B8, PF_REAL, -1, "AI: Minimum nonzero AI leash distance; small values raised to it (units) (unit_0154C0.cpp:3482)", 0 },
    { "flt_4275BC", (RwUInt32)&flt_4275BC, PF_REAL, -1, "AI: Threshold below which the leash's second distance is raised (units) (unit_0154C0.cpp:3484)", 0 },
    { "flt_4275C0", (RwUInt32)&flt_4275C0, PF_REAL, -1, "AI: Arrival check: distance squared under speed squared x400 (20 frames) (unit_0154C0.cpp:1979)", 0 },
    { "flt_4275C4", (RwUInt32)&flt_4275C4, PF_REAL, -1, "AI: AI speed above which aiming runs a line-of-fire test (units/frame) (unit_0154C0.cpp:2424)", 0 },
    { "flt_4275DC", (RwUInt32)&flt_4275DC, PF_REAL, -1, "AI: Visibility-cache record match radius, squared (300 units) (unit_0154C0.cpp:4336)", 0 },
    { "flt_4275E0", (RwUInt32)&flt_4275E0, PF_REAL, -1, "AI: Visibility-cache height limit; compared unsquared, so effectively 40000 units (unit_0154C0.cpp:4336)", 0 },
    { "flt_4275E4", (RwUInt32)&flt_4275E4, PF_REAL, -1, "AI: Height above cover node where the player spoils it (units) (unit_022C80.cpp:1394)", 0 },
    { "flt_4275E8", (RwUInt32)&flt_4275E8, PF_REAL, -1, "AI: Cover-node spoil radius squared (150 units); also reused as lower height bound (unit_022C80.cpp:1399)", 0 },
    { "flt_427680", (RwUInt32)&flt_427680, PF_REAL, -1, "AI: Squared range (2000 units) beyond which a look at target may wait (unit_040720.cpp:342)", 0 },
    { "flt_4290CC", (RwUInt32)&flt_4290CC, PF_REAL, -1, "AI: Wall must face soldier: normal-direction dot below -0.5 to be contact (unit_0929A0.cpp:2963)", 0 },
    { "flt_4290D0", (RwUInt32)&flt_4290D0, PF_REAL, -1, "AI: Height a triangle must reach above soldier frame to be contact (units) (unit_0929A0.cpp:216)", 0 },
    { "flt_4290DC", (RwUInt32)&flt_4290DC, PF_REAL, -1, "AI: Downward normal limit for steep contact triangles (normal y, ~65 degrees) (unit_0929A0.cpp:2342)", 0 },
    { "flt_4290E0", (RwUInt32)&flt_4290E0, PF_REAL, -1, "AI: Min wall triangle width for contacts unless 400 units high (units) (unit_0929A0.cpp:2907)", 0 },
    { "flt_429AA4", (RwUInt32)&flt_429AA4, PF_REAL, -1, "AI: Squared radius (300 units) of AIs alerted around player's target (unit_0FD730.cpp:3504)", 0 },
    { "flt_429CC0", (RwUInt32)&flt_429CC0, PF_REAL, -1, "AI: Target height above shooter that counts as steep shot (units) (unit_134B40.cpp:4328)", 0 },
    { "flt_429CC4", (RwUInt32)&flt_429CC4, PF_REAL, -1, "AI: Steep shot: horizontal squared / height squared below this lowers aim offset (unit_134B40.cpp:4332)", 0 },
    { "flt_429E94", (RwUInt32)&flt_429E94, PF_REAL, -1, "AI: Mounted-gun NPC gunner max aim turn per step (degrees) (unit_166990.cpp:1716)", 0 },
    { "flt_429E98", (RwUInt32)&flt_429E98, PF_REAL, -1, "AI: NPC gunner aim arc: min cosine to mount facing (~84 degrees) (unit_166990.cpp:1724)", 0 },
    { "flt_429E9C", (RwUInt32)&flt_429E9C, PF_REAL, -1, "AI: NPC gunner fires when aim within this angle of target (degrees) (unit_166990.cpp:1714)", 0 },
    { "flt_4C0198", (RwUInt32)&flt_4C0198, PF_REAL, -1, "AI: AI search rescoring minimum radius (500 units, copied from flt_3D9488) (unit_022C80.cpp:607)", 0 },
    { "dword_4296D8", (RwUInt32)&dword_4296D8, PF_INT, -1, "pathing: A* node expansions allowed per search step (count) (src/Source/GameCore/pathnodemanager/astarpathfinder.cpp:1105)", 0 },
    { "dword_4296F0", (RwUInt32)&dword_4296F0, PF_INT, -1, "pathing: A* search steps before PathNotFound 'max time reached' (steps) (src/Source/GameCore/pathnodemanager/astarpathfinder.cpp:764)", 0 },
    { "flt_4296DC", (RwUInt32)&flt_4296DC, PF_REAL, -1, "pathing: Squared range (500 units) near AI's target where A* cost x10 (src/Source/GameCore/pathnodemanager/astarpathfinder.cpp:484)", 0 },
    { "flt_4296E0", (RwUInt32)&flt_4296E0, PF_REAL, -1, "pathing: Squared range (1000 units) near AI's target where A* cost x3 (src/Source/GameCore/pathnodemanager/astarpathfinder.cpp:488)", 0 },
    { "flt_4296E4", (RwUInt32)&flt_4296E4, PF_REAL, -1, "pathing: A* path length (squared units) beyond which node discounts/scaling apply (src/Source/GameCore/pathnodemanager/astarpathfinder.cpp:526)", 0 },
    { "flt_4296E8", (RwUInt32)&flt_4296E8, PF_REAL, -1, "pathing: Squared step (500 units) under which a flagged node may cost zero (src/Source/GameCore/pathnodemanager/astarpathfinder.cpp:517)", 0 },
    { "dword_429D74", (RwUInt32)&dword_429D74, PF_INT, -1, "vehicles: Flag: cap vehicle velocity at its top speed (unit_147080.cpp:680)", 0 },
    { "dword_429D8C", (RwUInt32)&dword_429D8C, PF_INT, -1, "vehicles: Flag: scale vehicle contact push's vertical part by flt_4D50FC (unit_147080.cpp:1089)", 0 },
    { "flt_429D68", (RwUInt32)&flt_429D68, PF_REAL, -1, "vehicles: Max ground penetration corrected per physics step (units, scaled by step) (unit_147080.cpp:1283)", 0 },
    { "flt_429D88", (RwUInt32)&flt_429D88, PF_REAL, -1, "vehicles: Tilt cosine (40 degrees) beyond which vehicle steering fades out (unit_147080.cpp:526)", 0 },
    { "flt_429D9C", (RwUInt32)&flt_429D9C, PF_REAL, -1, "vehicles: Cosine (30 degrees) choosing which side a body is pushed out (unit_147080.cpp:1500)", 0 },
    { "flt_429DD8", (RwUInt32)&flt_429DD8, PF_REAL, -1, "vehicles: Tank field-of-fire cosine (about 21 degrees) (unit_14C820.cpp:2618)", 0 },
    { "flt_429DDC", (RwUInt32)&flt_429DDC, PF_REAL, -1, "vehicles: Tank engagement aim cone cosine (about 23 degrees) (unit_14C820.cpp:2754)", 0 },
    { "flt_429DE0", (RwUInt32)&flt_429DE0, PF_REAL, -1, "vehicles: Tank engagement facing-toward cosine (about 31 degrees) (unit_14C820.cpp:2711)", 0 },
    { "dword_429B3C", (RwUInt32)&dword_429B3C, PF_INT, -1, "player: Flag: track soldier's peak height while falling (fall damage) (unit_0FD730.cpp:9634)", 0 },
    { "flt_429748", (RwUInt32)&flt_429748, PF_REAL, -1, "player: Aim assist: stick deflection below which strongest slowdown applies (0-1) (unit_0FD730.cpp:2225)", 0 },
    { "flt_42974C", (RwUInt32)&flt_42974C, PF_REAL, -1, "player: Aim assist: stick deflection below which medium slowdown applies (0-1) (unit_0FD730.cpp:2230)", 0 },
    { "flt_429B38", (RwUInt32)&flt_429B38, PF_REAL, -1, "player: Longest fall: fall counter limit (+0.5 per frame, ~240 frames) (unit_0FD730.cpp:9644)", 0 },
    { "flt_42C778", (RwUInt32)&flt_42C778, PF_REAL, -1, "player: Analog button minimum value treated as pressed (0-1 pressure) (unit_19D920.cpp:211)", 0 },
    { "flt_42C77C", (RwUInt32)&flt_42C77C, PF_REAL, -1, "player: Analog stick dead zone (fraction of full deflection) (unit_19D920.cpp:155)", 0 },
    { "dword_429E40", (RwUInt32)&dword_429E40, PF_REAL, -1, "projectiles: Tracer age before it is drawn (game time units) (unit_15F1B0.cpp:850)", 0 },
    { "dword_429E78", (RwUInt32)&dword_429E78, PF_REAL, -1, "projectiles: Maximum grenade spin per frame (degrees) (unit_161C50.cpp:606)", 0 },
    { "dword_429E7C", (RwUInt32)&dword_429E7C, PF_INT, -1, "projectiles: Max recursion depth of a grenade's step within one frame (unit_161C50.cpp:738)", 0 },
    { "dword_429E80", (RwUInt32)&dword_429E80, PF_REAL, -1, "projectiles: Grenade standoff distance from surfaces it hits (units) (unit_161C50.cpp:477)", 0 },
    { "dword_429E88", (RwUInt32)&dword_429E88, PF_REAL, -1, "projectiles: Grenade inner collision sphere radius (units) (unit_161C50.cpp:280)", 0 },
    { "dword_429E8C", (RwUInt32)&dword_429E8C, PF_REAL, -1, "projectiles: Grenade outer collision sphere radius (units) (unit_161C50.cpp:281)", 0 },
    { "flt_429E20", (RwUInt32)&flt_429E20, PF_REAL, -1, "camera: Tank camera clearance from obstacles and minimum distance (units) (unit_155470.cpp:1107)", 0 },
    { "flt_429E24", (RwUInt32)&flt_429E24, PF_REAL, -1, "camera: Tank camera distance below which the camera drops lower (units) (unit_155470.cpp:1085)", 0 },
    { "flt_4293E4", (RwUInt32)&flt_4293E4, PF_REAL, -1, "HUD: Radar path search maximum iterations (count) (unit_0DC400.cpp:4004)", 0 },
    { "flt_4293E8", (RwUInt32)&flt_4293E8, PF_REAL, -1, "HUD: Radar path search tolerance on squared distance (units squared) (unit_0DC400.cpp:3938)", 0 },
    { "flt_429BD0", (RwUInt32)&flt_429BD0, PF_REAL, -1, "rendering: Blob shadow draw distance from camera; fade from half (units) (unit_1279C0.cpp:95)", 0 },
    { "flt_429E2C", (RwUInt32)&flt_429E2C, PF_REAL, -1, "audio: Turret/gun turn speed that starts or stops turning sound (unit_155470.cpp:1496)", 0 },
    { "flt_4290E8", (RwUInt32)&flt_4290E8, PF_REAL, -1, "other: Min floor normal y a soldier can stand on (cos 45 degrees) (unit_0929A0.cpp:2253)", 0 },
    { "flt_4290EC", (RwUInt32)&flt_4290EC, PF_REAL, -1, "other: Normal y below which a triangle counts as vertical for point drops (unit_0929A0.cpp:1492)", 0 },
    { "flt_42925C", (RwUInt32)&flt_42925C, PF_REAL, -1, "other: Object jiggle: bounce turn rate = this / bounce time (max 3) (unit_0D48D0.cpp:253)", 0 },
    { "flt_429CA4", (RwUInt32)&flt_429CA4, PF_REAL, -1, "other: SendFlying knockback: minimum launch strength (units of speed) (unit_134B40.cpp:3916)", 0 },
    { "flt_429CA8", (RwUInt32)&flt_429CA8, PF_REAL, -1, "other: SendFlying knockback: maximum launch strength (units of speed) (unit_134B40.cpp:3918)", 0 },
};

static void TabTunables()
{
    ImGui::TextDisabled("Fixed tuning values no code changes, read live where they are used (Enter sets one).");
    ImGui::SetNextItemWidth(160.0f);
    ImGui::InputText("filter##tun", s_szPgFieldFilter, sizeof(s_szPgFieldFilter));
    PgFieldTable("tunables", (RwUInt8 *)0, s_aTunables, sizeof(s_aTunables) / sizeof(s_aTunables[0]), FALSE);
}

static void TabTriggers()
{
    RwInt32 i, nCount = 0, nLast;
    Trigger *pTrigger;
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vPlayer;
    RwBool bPlayer;

    bPlayer = pPlayer != NULL && PlayerPosition(pPlayer, &vPlayer);
    nLast = dword_429D00;
    if (nLast >= 2000)
        nLast = 1999;
    for (i = 0; i <= nLast; i++)
    {
        RwReal fX, fY, fZ;

        pTrigger = (Trigger *)dword_4CFE30[i];
        if (pTrigger == NULL)
            continue;
        if (!bPlayer || !ReadF32(&pTrigger->unk_90, &fX) || !ReadF32(&pTrigger->unk_94, &fY)
            || !ReadF32(&pTrigger->unk_98, &fZ))
            s_afTrigDist[i] = 0.0f;
        else
            s_afTrigDist[i] = (RwReal)sqrt((fX - vPlayer.x) * (fX - vPlayer.x) + (fY - vPlayer.y) * (fY - vPlayer.y)
                                           + (fZ - vPlayer.z) * (fZ - vPlayer.z));
        s_anTrigOrder[nCount++] = i;
    }
    qsort(s_anTrigOrder, nCount, sizeof(RwInt32), TrigByDistance);
    ImGui::Text("%d triggers (handles 0 to %d), nearest first. Teleporting puts the player at the trigger's "
                "centre; turn noclip on first to stay there.", nCount, nLast);
    if (ImGui::Button("spawn a soldier ahead of me"))
        Request(REQ_SPAWNSOLDIER, -1, 0, 0.0f, 0.0f, 0.0f);
    ImGui::SameLine();
    ImGui::TextDisabled("(from the nearest soldier trigger whose definition this map loaded)");
    if (!ImGui::BeginTable("triggers", 7, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    ImGui::TableSetupColumn("handle");
    ImGui::TableSetupColumn("type");
    ImGui::TableSetupColumn("shape");
    ImGui::TableSetupColumn("centre");
    ImGui::TableSetupColumn("flags");
    ImGui::TableSetupColumn("distance");
    ImGui::TableSetupColumn("");
    ImGui::TableHeadersRow();
    for (i = 0; i < nCount && i < 400; i++)
        TrigRow(s_anTrigOrder[i], (Trigger *)dword_4CFE30[s_anTrigOrder[i]], s_afTrigDist[s_anTrigOrder[i]]);
    ImGui::EndTable();
}

// ---- Scripts ----

static RwUInt8 s_abFree[1100];

// Walks the pool's free list (each free element links the next in the word
// at its size, less the guard word when it has none; sub_16C5A0) into
// s_abFree; FALSE when the pool is unset or faults.
static RwBool PoolFree(type_16C2A0 *pPool, RwUInt32 *pdwBase, RwInt32 *pnStride, RwInt32 *pnCount)
{
    __try
    {
        RwUInt8 *p = pPool->unk_08;
        RwInt32 nNext = pPool->unk_10 - ((pPool->unk_00 & 2) ? 4 : 0);
        RwInt32 i, nIndex;

        *pdwBase = (RwUInt32)pPool->unk_04;
        *pnStride = pPool->unk_10;
        *pnCount = pPool->unk_0C;
        if (*pdwBase == 0 || *pnStride <= 0 || *pnCount <= 0 || *pnCount > 1100)
            return FALSE;
        memset(s_abFree, 0, *pnCount);
        for (i = 0; p != NULL && i < *pnCount; i++)
        {
            nIndex = ((RwUInt32)p - *pdwBase) / *pnStride;
            if (nIndex < 0 || nIndex >= *pnCount)
                break;
            s_abFree[nIndex] = 1;
            p = *(RwUInt8 **)(p + nNext);
        }
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

static void PoolRow(const RwChar *pszName, type_16C2A0 *pPool)
{
    RwUInt32 dwCount, dwSize, dwFree, dwMost;

    if (!ReadU32(&pPool->unk_0C, &dwCount) || !ReadU32(&pPool->unk_10, &dwSize)
        || !ReadU32(&pPool->unk_18, &dwFree) || !ReadU32(&pPool->unk_14, &dwMost))
        return;
    Row(pszName, "%d of %d in use, most %d, 0x%X bytes each", (RwInt32)(dwCount - dwFree), (RwInt32)dwCount,
        (RwInt32)dwMost, dwSize);
}

static void Pools()
{
    if (!BeginRows("pools"))
        return;
    PoolRow("m_pobjectPool", &dword_449A50);
    PoolRow("m_aiObjectPool", &dword_449A10);
    PoolRow("m_stateMachineObjectPool", &dword_449A30);
    PoolRow("m_taskObjectPool", &dword_4499F0);
    PoolRow("m_taskTreeDataPool", &dword_4499D0);
    PoolRow("m_inputListPool", &dword_4499B0);
    PoolRow("m_memPools[0]", &dword_449950[0]);
    PoolRow("m_memPools[1]", &dword_449950[1]);
    PoolRow("m_memPools[2]", &dword_449950[2]);
    ImGui::EndTable();
}

// The word at the code pointer dwCode: its opcode and, for the call
// opcode nCall, the command's name, into psz.
static void CodeWord(RwUInt32 dwCode, RwInt32 nCall, RwChar *psz)
{
    RwUInt32 dw;
    RwChar szName[64];

    if (dwCode == 0 || !ReadU32((void *)dwCode, &dw))
    {
        strcpy(psz, "-");
        return;
    }
    szName[0] = 0;
    if ((RwInt32)(dw & 0xFF) == nCall)
        CommandName((RwInt16)(dw >> 16), szName);
    sprintf(psz, "op %u %s", dw & 0xFF, szName);
}

static RwBool ReportHas(const RwChar *psz, const RwChar *pszPart);

// A script object's name as the debugger gives it (its trigger's object's
// name, sub_6B060) and its object's ID.
static void ScriptName(type_67620 *pScript, RwChar *psz, RwInt32 nMax)
{
    RwChar szName[48];
    RwInt32 nId = -1;

    szName[0] = 0;
    __try
    {
        type_3D2E7C *pObject = pScript ? pScript->vf_024() : NULL;

        if (pObject)
        {
            type_712B0 *pTrigger = pObject->sub_712B0();

            nId = pObject->get_unk_24_d();
            if (pTrigger)
            {
                type_3DF8D8_04 *pKey = pTrigger->vf_01C();

                if (pKey && pKey->unk_00 && pKey->unk_04)
                {
                    type_3DF8D8 *pAsset = sub_198800(pKey);

                    if (pAsset)
                        ReadText((const RwChar *)pAsset->unk_14, szName, 40);
                }
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    if (szName[0])
        _snprintf(psz, nMax, "%s (ID %d)", szName, nId);
    else if (nId >= 0)
        _snprintf(psz, nMax, "ID %d", nId);
    else
        _snprintf(psz, nMax, "-");
    psz[nMax - 1] = 0;
}

// The picked script object and whether it is a state machine (which alone
// keeps variables: unk_74, unk_78 bytes, the words the load and store
// global opcodes, 34 and 32, address by their operand).
static RwUInt32 s_dwSelScript;
static RwBool s_bSelMachine;
static RwChar s_szScriptFilter[48];

// The script table's row for the object dwObj, its name and code pointer;
// FALSE when the filter hides it.
static RwBool ScriptRow(RwUInt32 dwObj, RwBool bMachine, RwUInt32 dwRunning, RwUInt32 dwCodePtr, RwInt32 nCall,
                        RwChar *pszName, RwInt32 nName)
{
    RwChar szObj[32], szCode[96];

    ScriptName((type_67620 *)dwObj, pszName, nName);
    if (s_szScriptFilter[0] && !ReportHas(pszName, s_szScriptFilter))
        return FALSE;
    CodeWord(dwCodePtr, nCall, szCode);
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    sprintf(szObj, "0x%08X%s", dwObj, dwObj == dwRunning ? " <" : "");
    if (ImGui::Selectable(szObj, dwObj == s_dwSelScript, ImGuiSelectableFlags_SpanAllColumns))
    {
        s_dwSelScript = dwObj == s_dwSelScript ? 0 : dwObj;
        s_bSelMachine = bMachine;
    }
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(pszName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(szCode);
    return TRUE;
}

// The live objects of the pool pPool: state machines (type_3D2DB8) with
// their state and family, or performances (type_3D2CD0) and tasks
// (type_3D2E20), both type_3D2C30.
static void ScriptTable(const RwChar *pszId, type_16C2A0 *pPool, RwBool bMachine, RwUInt32 dwRunning, RwInt32 nCall)
{
    RwUInt32 dwBase;
    RwInt32 nStride, nCount, i, nShown = 0, nLive = 0;
    RwChar szName[96];

    if (!PoolFree(pPool, &dwBase, &nStride, &nCount))
    {
        ImGui::Text("The pool is not set up.");
        return;
    }
    if (!ImGui::BeginTable(pszId, bMachine ? 6 : 3, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg |
                                                       ImGuiTableFlags_ScrollY, ImVec2(0.0f, 260.0f)))
        return;
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableSetupColumn("object (< running)");
    ImGui::TableSetupColumn("name");
    ImGui::TableSetupColumn("at the code");
    if (bMachine)
    {
        ImGui::TableSetupColumn("state");
        ImGui::TableSetupColumn("owner");
        ImGui::TableSetupColumn("parent");
    }
    ImGui::TableHeadersRow();
    for (i = 0; i < nCount && nShown < 300; i++)
    {
        RwUInt32 dwObj = dwBase + i * nStride, dwCodePtr;

        if (s_abFree[i])
            continue;
        nLive++;
        if (!ReadU32(&((type_3D2C30 *)dwObj)->unk_68, &dwCodePtr))
            continue;
        if (bMachine)
        {
            type_3D2DB8 *pMachine = (type_3D2DB8 *)dwObj;
            RwUInt32 dwState, dwOwner, dwParent, dw;
            RwInt32 nState = -1;

            if (!ReadU32(&pMachine->unk_68, &dwCodePtr) || !ReadU32(&pMachine->unk_6C, &dwState)
                || !ReadU32(&pMachine->unk_7C, &dwOwner) || !ReadU32(&pMachine->unk_88, &dwParent))
                continue;
            // the state record's index (type_3D2DB8_6C::unk_10)
            if (dwState && ReadU32(&((type_3D2DB8_6C *)dwState)->unk_10, &dw))
                nState = (RwInt16)(dw & 0xFFFF);
            if (!ScriptRow(dwObj, TRUE, dwRunning, dwCodePtr, nCall, szName, sizeof(szName)))
                continue;
            ImGui::TableNextColumn();
            ImGui::Text("%d", nState);
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", dwOwner);
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", dwParent);
        }
        else if (!ScriptRow(dwObj, FALSE, dwRunning, dwCodePtr, nCall, szName, sizeof(szName)))
            continue;
        nShown++;
    }
    ImGui::EndTable();
    ImGui::TextDisabled("%d live, %d shown (up to 300)", nLive, nShown);
}

// The picked script: its name, code and, for a state machine, its
// variables as ints and floats, editable.
static void ScriptSelected(RwInt32 nCall)
{
    type_3D2DB8 *pMachine = (type_3D2DB8 *)s_dwSelScript;
    RwUInt32 dwVtbl, dwCodePtr, dwVars = 0, dwSize = 0;
    RwChar szName[96], szCode[96];
    RwInt32 i, nWords;

    if (s_dwSelScript == 0)
    {
        ImGui::TextDisabled("Click a row for its details and variables.");
        return;
    }
    if (!ReadU32((void *)s_dwSelScript, &dwVtbl) || !ReadU32(&((type_3D2C30 *)s_dwSelScript)->unk_68, &dwCodePtr)
        || (s_bSelMachine && (!ReadU32(&pMachine->unk_74, &dwVars) || !ReadU32(&pMachine->unk_78, &dwSize))))
    {
        ImGui::Text("0x%08X can't be read.", s_dwSelScript);
        s_dwSelScript = 0;
        return;
    }
    ScriptName((type_67620 *)s_dwSelScript, szName, sizeof(szName));
    CodeWord(dwCodePtr, nCall, szCode);
    ImGui::SeparatorText(szName);
    ImGui::Text("0x%08X, code 0x%08X: %s", s_dwSelScript, dwCodePtr, szCode);
    ImGui::SameLine();
    if (ImGui::SmallButton("close"))
        s_dwSelScript = 0;
    if (!s_bSelMachine)
        return;
    nWords = (RwInt32)(dwSize / 4);
    if (dwVars == 0 || nWords <= 0)
    {
        ImGui::TextDisabled("No variables.");
        return;
    }
    if (nWords > 256)
        nWords = 256;
    ImGui::TextDisabled("%d variables (Enter to set one):", nWords);
    if (!ImGui::BeginTable("selvars", 4, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg |
                                             ImGuiTableFlags_ScrollY, ImVec2(0.0f, 200.0f)))
        return;
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableSetupColumn("#");
    ImGui::TableSetupColumn("int");
    ImGui::TableSetupColumn("float");
    ImGui::TableSetupColumn("hex");
    ImGui::TableHeadersRow();
    for (i = 0; i < nWords; i++)
    {
        RwInt32 *pn = (RwInt32 *)dwVars + i;
        RwUInt32 dw;

        if (!ReadU32(pn, &dw))
            break;
        ImGui::PushID(i);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", i);
        ImGui::TableNextColumn();
        {
            RwInt32 n = (RwInt32)dw;

            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::InputInt("##i", &n, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue))
                *pn = n;
        }
        ImGui::TableNextColumn();
        {
            RwReal f = *(RwReal *)&dw;

            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::InputFloat("##f", &f, 0.0f, 0.0f, "%g", ImGuiInputTextFlags_EnterReturnsTrue))
                *(RwReal *)pn = f;
        }
        ImGui::TableNextColumn();
        ImGui::TextDisabled("%08X", dw);
        ImGui::PopID();
    }
    ImGui::EndTable();
}

// The live link's script snapshot (trigweb.cpp, the web suite's Blueprint page), what the
// Scripts tab shows, as one JSON event: {"t":"scripts","frame":n,"running":"obj","machines":[..],
// "performances":[..],"tasks":[..]}. Each entry has "obj", "name" (ScriptName's) and "code" (its
// code pointer). A state machine (type_3D2DB8) adds "image" (its script's header, its object's
// type_3D2E7C::unk_08, a type_72990), "state" (the current state's index), "base" (that state's
// code, type_3D2DB8_6C::unk_04), "pc" (the code pointer's word offset from it, -1 when it is
// elsewhere: another state's code, or a called function), "owner" and "parent" (unk_7C, unk_88)
// and "vars" (the first 16 variables, all of the watched script's). A performance or task
// (type_3D2C30) adds "script" (its script's record, unk_74, a type_67620_74), "start" (its first
// instruction) and "pc" (the offset from it). Each image goes to pfnImage too (the link describes a new one's states, which
// the page matches with its decompiled units). FALSE when there is no room; psz is NUL-ended
// either way.
extern "C" volatile unsigned port_frame;

// A name as JSON text (quotes and backslashes made safe).
static void JsonName(const RwChar *pszIn, RwChar *psz, RwInt32 nMax)
{
    RwChar *pq = psz;

    for (; *pszIn && pq < psz + nMax - 3; pszIn++)
    {
        if (*pszIn == '"' || *pszIn == '\\')
            *pq++ = '\\';
        *pq++ = (RwUInt8)*pszIn < 0x20 ? ' ' : *pszIn;
    }
    *pq = 0;
}

RwUInt32 TrigScriptWatched();

static RwInt32 ScriptsJsonPool(RwChar *psz, RwInt32 n, RwInt32 nMax, const RwChar *pszKey, type_16C2A0 *pPool,
                               RwBool bMachine, void (*pfnImage)(RwUInt32 dwImage))
{
    RwUInt32 dwBase;
    RwInt32 nStride, nCount, i, nShown = 0;

    n += _snprintf(psz + n, nMax - n, ",\"%s\":[", pszKey);
    if (!PoolFree(pPool, &dwBase, &nStride, &nCount))
        nCount = 0;
    for (i = 0; i < nCount; i++)
    {
        RwUInt32 dwObj = dwBase + i * nStride, dwCode, dw;
        RwChar szName[96], szQuoted[200];
        RwInt32 nLen;

        if (s_abFree[i] || !ReadU32(&((type_3D2C30 *)dwObj)->unk_68, &dwCode))
            continue;
        ScriptName((type_67620 *)dwObj, szName, sizeof(szName));
        JsonName(szName, szQuoted, sizeof(szQuoted));
        if (bMachine)
        {
            type_3D2DB8 *pMachine = (type_3D2DB8 *)dwObj;
            RwUInt32 dwState = 0, dwStateCode = 0, dwVars = 0, dwSize = 0, dwImage = 0, dwOwner = 0, dwParent = 0;
            RwInt32 nState = -1, nPc = -1, k, nWords;

            ReadU32(&pMachine->unk_6C, &dwState);
            if (dwState && ReadU32(&((type_3D2DB8_6C *)dwState)->unk_10, &dw))
                nState = (RwInt16)(dw & 0xFFFF);
            if (dwState)
                ReadU32(&((type_3D2DB8_6C *)dwState)->unk_04, &dwStateCode);
            if (dwStateCode && dwCode >= dwStateCode && dwCode - dwStateCode < 0x40000)
                nPc = (RwInt32)((dwCode - dwStateCode) / 4);
            __try
            {
                type_3D2E7C *pObject = pMachine->vf_024();

                if (pObject)
                    dwImage = (RwUInt32)pObject->unk_08;
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
            if (dwImage && pfnImage)
                pfnImage(dwImage);
            ReadU32(&pMachine->unk_74, &dwVars);
            ReadU32(&pMachine->unk_78, &dwSize);
            ReadU32(&pMachine->unk_7C, &dwOwner);
            ReadU32(&pMachine->unk_88, &dwParent);
            nLen = _snprintf(psz + n, nMax - n,
                             "%s{\"obj\":\"%08X\",\"name\":\"%s\",\"image\":\"%08X\",\"state\":%d,\"base\":\"%08X\",\"code\":\"%08X\","
                             "\"pc\":%d,\"owner\":\"%08X\",\"parent\":\"%08X\",\"vars\":[",
                             nShown ? "," : "", dwObj, szQuoted, dwImage, nState, dwStateCode, dwCode, nPc, dwOwner, dwParent);
            if (nLen < 0 || n + nLen > nMax - 1200)
                break;
            n += nLen;
            // (16 in the list; the watched script's all, up to 256: the page edits them)
            nWords = dwVars ? (RwInt32)(dwSize / 4) : 0;
            if (nWords > (dwObj == TrigScriptWatched() ? 256 : 16))
                nWords = dwObj == TrigScriptWatched() ? 256 : 16;
            for (k = 0; k < nWords && ReadU32((RwInt32 *)dwVars + k, &dw); k++)
                n += sprintf(psz + n, "%s%d", k ? "," : "", (RwInt32)dw);
            n += sprintf(psz + n, "]}");
        }
        else
        {
            RwUInt32 dwScript = 0, dwStart = 0, dwId = 0, dwNamePtr = 0;
            RwChar szScript[64], szScriptQuoted[140];
            RwInt32 nPc = -1;

            szScript[0] = 0;
            ReadU32(&((type_3D2C30 *)dwObj)->unk_74, &dwScript);
            if (dwScript)
            {
                ReadU32(&((type_67620_74 *)dwScript)->unk_08, &dwStart);
                if (ReadU32(&((type_67620_74 *)dwScript)->unk_04, &dw))
                    dwId = dw & 0xFFFF;
                if (ReadU32(&((type_67620_74 *)dwScript)->unk_00, &dwNamePtr) && dwNamePtr)
                    ReadText((const RwChar *)dwNamePtr, szScript, 60);
            }
            JsonName(szScript, szScriptQuoted, sizeof(szScriptQuoted));
            if (dwStart && dwCode >= dwStart && dwCode - dwStart < 0x40000)
                nPc = (RwInt32)((dwCode - dwStart) / 4);
            nLen = _snprintf(psz + n, nMax - n,
                             "%s{\"obj\":\"%08X\",\"name\":\"%s\",\"code\":\"%08X\",\"script\":\"%08X\",\"scriptName\":\"%s\","
                             "\"scriptId\":%u,\"start\":\"%08X\",\"pc\":%d}",
                             nShown ? "," : "", dwObj, szQuoted, dwCode, dwScript, szScriptQuoted, dwId, dwStart, nPc);
            if (nLen < 0 || n + nLen > nMax - 1200)
                break;
            n += nLen;
        }
        nShown++;
    }
    n += _snprintf(psz + n, nMax - n, "]");
    return n;
}

RwBool TrigWebScriptsJson(RwChar *psz, RwInt32 nMax, void (*pfnImage)(RwUInt32 dwImage))
{
    RwUInt32 dwRunning;
    RwInt32 n;

    if (!ReadU32(&dword_449328, &dwRunning))
        dwRunning = 0;
    n = _snprintf(psz, nMax, "{\"t\":\"scripts\",\"frame\":%u,\"running\":\"%08X\"", port_frame, dwRunning);
    n = ScriptsJsonPool(psz, n, nMax / 2, "machines", &dword_449A30, TRUE, pfnImage);
    n = ScriptsJsonPool(psz, n, nMax * 3 / 4, "performances", &dword_449A50, FALSE, NULL);
    n = ScriptsJsonPool(psz, n, nMax - 16, "tasks", &dword_4499F0, FALSE, NULL);
    _snprintf(psz + n, nMax - n, "}");
    psz[nMax - 1] = 0;
    return TRUE;
}

// ---- CODFH_SPAWNAI=1: a test of the AI soldier spawn (SpawnSoldierAt) ----
extern "C" void plog(const char *fmt, ...);
// ---- reading god assets of another level (the AI soldiers in multiplayer: single player's soldier
// class) ----
//
// The GodAsset manager reads an object only while a request for it is open, from whatever
// stream of god data passes by (sub_198D30 skips the rest). So an object of another level is
// asked for (sub_198900, as its users ask), then that level's GODDATA.DFF read again through the
// god data records (chunk 0x719, records of kinds 8 and 9: sub_142BC0, as the section reader's
// sub_141C10 hands them on), pass after pass while what it reads asks for more (a script's
// imports). Requests left open after, which no pass could answer, are taken back (the level
// start, and the loading screen, wait on every open request).

void sub_19A7D0(type_4F26D0 *arg_0);
void sub_198F40(type_3DF8D8_base *arg_0);

static RwInt32 ForeignOpenRequests()
{
    type_4F26D0 *p;
    RwInt32 n = 0;

    for (p = (type_4F26D0 *)dword_4F26D0; p && n < 100000; p = p->unk_08)
        n++;
    return n;
}

// One pass of the file pszPath's god data records; FALSE when it will not open.
static RwBool ForeignPass(const RwChar *pszPath)
{
    RwChunkHeaderInfo hdr;
    RwStream *pStream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, (void *)pszPath);

    if (pStream == NULL)
        return FALSE;
    while (RwStreamReadChunkHeaderInfo(pStream, &hdr))
    {
        if (hdr.type == 0x719 && hdr.length >= sizeof(type_141C10))
        {
            type_141C10 rec;

            RwStreamRead(pStream, &rec, sizeof(rec));
            if (rec.unk_00 == 8 || rec.unk_00 == 9)
            {
                sub_12F0A0();
                sub_142BC0(pStream, &rec);
            }
            else
                RwStreamSkip(pStream, hdr.length - sizeof(rec));
        }
        else
            RwStreamSkip(pStream, hdr.length);
    }
    RwStreamClose(pStream, (void *)pszPath);
    return TRUE;
}

// The object *pKey (of the kind nKind) read from the level folder pszLevel's GODDATA.DFF, with
// what it imports; the object, or NULL.
static type_3DF8D8 *ForeignRead(const RwChar *pszLevel, type_3DF8D8_04 *pKey, RwInt32 nKind)
{
    type_4F26D0 *apBefore[512];
    RwInt32 nBefore = 0, nPass, nOpen, nTaken = 0, i;
    RwChar szPath[128];
    type_4F26D0 *p, *pNext;
    type_3DF8D8 *pObject = sub_198800(pKey);

    if (pObject)
        return pObject;
    _snprintf(szPath, sizeof(szPath), "LEVELS\\%s\\GODDATA.DFF", pszLevel);
    szPath[sizeof(szPath) - 1] = 0;
    // (the requests already open: the level's own, left as they are)
    for (p = (type_4F26D0 *)dword_4F26D0; p && nBefore < 512; p = p->unk_08)
        apBefore[nBefore++] = p;
    sub_198900(pKey, nKind, 0, 0, 0, 0);
    for (nPass = 0; nPass < 8; nPass++)
    {
        nOpen = ForeignOpenRequests();
        if (!ForeignPass(szPath))
        {
            plog("foreign: %s will not open", szPath);
            break;
        }
        plog("foreign: %s pass %d: %d requests open before, %d after", szPath, nPass + 1, nOpen, ForeignOpenRequests());
        // (a pass that read nothing, and asked for nothing more, is the last; one that asked for
        // more, an object's imports earlier in the file, is followed by another)
        if (ForeignOpenRequests() == nOpen || ForeignOpenRequests() <= nBefore)
            break;
    }
    // (ours left open taken back)
    for (p = (type_4F26D0 *)dword_4F26D0; p; p = pNext)
    {
        RwBool bOld = FALSE;

        pNext = p->unk_08;
        for (i = 0; i < nBefore; i++)
            if (apBefore[i] == p)
                bOld = TRUE;
        if (bOld)
            continue;
        plog("foreign: no pass read %08X,%08X (kind %d); its request taken back", p->unk_00->unk_04.unk_00,
             p->unk_00->unk_04.unk_04, p->unk_00->vf_008());
        sub_19A7D0(p);
        sub_198F40(p->unk_00);
        memset(p, 0, sizeof(*p));
        dword_4F2708.sub_16C710(p);
        nTaken++;
    }
    pObject = sub_198800(pKey);
    plog("foreign: %08X,%08X from %s: %s (%d requests taken back)", pKey->unk_00, pKey->unk_04, pszLevel,
         pObject ? "read" : "not read", nTaken);
    return pObject;
}

static void SpawnAiLogScripts(RwUInt32 dwObject);
static void SpawnAiDiagStart();
static void SpawnAiDiagLog(RwUInt32 dwObject);

// A flat spot near *pv for a soldier: in rings 2 to 6 m out, 16 directions each, the first
// place with a floor (GroundBelow) within 1.5 m of the player's height whose floor 1 m off on
// four sides is within 10 cm of its own; *pv moved there. FALSE when there is none.
static RwBool LineClear(const RwV3d *pA, const RwV3d *pB);
static RwBool s_bFlatNeedsSight;

static RwBool FindFlatSpot(RwV3d *pv)
{
    static const RwReal s_afRing[4] = { 200.0f, 300.0f, 400.0f, 600.0f };
    RwInt32 r, k, j;

    for (r = 0; r < 4; r++)
        for (k = 0; k < 16; k++)
        {
            RwReal a = k * 6.2831853f / 16.0f;
            RwV3d c = *pv;
            RwBool bFlat = TRUE;

            c.x += (RwReal)cos(a) * s_afRing[r];
            c.z += (RwReal)sin(a) * s_afRing[r];
            c.y = pv->y + 100.0f;
            if (!GroundBelow(&c) || fabs(c.y - pv->y) > 150.0f)
                continue;
            for (j = 0; j < 4 && bFlat; j++)
            {
                RwV3d e = c;

                e.x += j == 0 ? 100.0f : j == 1 ? -100.0f : 0.0f;
                e.z += j == 2 ? 100.0f : j == 3 ? -100.0f : 0.0f;
                e.y = c.y + 100.0f;
                if (!GroundBelow(&e) || fabs(e.y - c.y) > 10.0f)
                    bFlat = FALSE;
            }
            // (and, for the combat test, a clear line between the two at head height)
            if (bFlat && s_bFlatNeedsSight)
            {
                RwV3d a = *pv, b = c;

                a.y += 20.0f;
                b.y += 150.0f;
                bFlat = LineClear(&a, &b);
            }
            if (bFlat)
            {
                *pv = c;
                return TRUE;
            }
        }
    return FALSE;
}

// The god asset named pszName (the GodAsset manager's table of every object, dword_4F2728; an
// object's name is its unk_14), or NULL.
static type_3DF8D8 *FindAssetByName(const RwChar *pszName)
{
    RwInt32 b;

    __try
    {
        if (dword_4F2728.unk_30 == NULL)
            return NULL;
        for (b = 0; b < dword_4F2728.unk_04 && b < 65536; b++)
        {
            alfahash_node *pNode;
            RwInt32 nGuard = 0;

            for (pNode = dword_4F2728.unk_30[b]; pNode && nGuard < 10000; pNode = pNode->unk_04, nGuard++)
            {
                type_3DF8D8 *pAsset = (type_3DF8D8 *)pNode->unk_00;
                RwChar szName[64];

                if (pAsset == NULL || pAsset->unk_14 == 0)
                    continue;
                ReadText((const RwChar *)pAsset->unk_14, szName, sizeof(szName) - 1);
                szName[sizeof(szName) - 1] = 0;
                if (_stricmp(szName, pszName) == 0)
                    return pAsset;
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    return NULL;
}

// -autospawn (port/src/cli.cpp, multiplayer): the local player spawned as soon as the game lets
// it: the team and weapon screens closed as picking a weapon closes them (sub_1C4B10; the team
// the game's automatic pick, the weapon the last one), then the spawn button's own calls
// (type_4F7EB8::sub_1AADF0: the fade, then the playing view, sub_1AB400(0), whose change
// respawns, sub_1AED30), while there is no local soldier and no
// respawn under way, with the button's other conditions, at most every five seconds.
extern "C" int port_autospawn;
// (CODFH_LOGSOLDIERS=1: three seconds into a level, each soldier trigger's class and task
// scripts' keys (commands 7 and 8: unk_E0 as kind 0xA, unk_E8 as kind 0xC), the objects read
// for them, and the key the name "SoldierClass" hashes to, logged once each)
static void LogSoldierTriggersTick()
{
    static RwInt32 s_nStart = -1;
    static RwUInt32 s_dwAt;
    RwInt32 i, k, n = 0;
    RwUInt32 adwSeen[64][4];
    type_3DF8D8_04 keyName;

    if (s_nStart < 0)
        s_nStart = GetEnvironmentVariableA("CODFH_LOGSOLDIERS", NULL, 0) ? 0 : 2;
    if (s_nStart == 2)
        return;
    if (sub_1745A0(0) == NULL)
    {
        s_dwAt = port_frame + 180;
        return;
    }
    if (port_frame < s_dwAt)
        return;
    s_nStart = 2;
    sub_198A20("SoldierClass", &keyName);
    plog("soldiers: \"SoldierClass\" hashes to %08X,%08X", keyName.unk_00, keyName.unk_04);
    for (i = 0; i < 2000 && i <= dword_429D00; i++)
    {
        SoldierTrigger *t = (SoldierTrigger *)dword_4CFE30[i];

        __try
        {
            type_3DF8D8 *pClass, *pTask;

            if (t == NULL || ((Trigger *)t)->vf_008() != 5)
                continue;
            plog("soldiers: trigger %d at (%.0f, %.0f, %.0f): definition %08X,%08X (%s), weapon %d", i, t->unk_90, t->unk_94,
                 t->unk_98, t->unk_D8.unk_00, t->unk_D8.unk_04, sub_198800(&t->unk_D8) ? "read" : "not read", t->unk_130);
            for (k = 0; k < n; k++)
                if (adwSeen[k][0] == (RwUInt32)t->unk_E0.unk_00 && adwSeen[k][1] == (RwUInt32)t->unk_E0.unk_04
                    && adwSeen[k][2] == (RwUInt32)t->unk_E8.unk_00 && adwSeen[k][3] == (RwUInt32)t->unk_E8.unk_04)
                    break;
            if (k < n || n >= 64)
                continue;
            adwSeen[n][0] = t->unk_E0.unk_00;
            adwSeen[n][1] = t->unk_E0.unk_04;
            adwSeen[n][2] = t->unk_E8.unk_00;
            adwSeen[n][3] = t->unk_E8.unk_04;
            n++;
            pClass = sub_198800(&t->unk_E0);
            pTask = sub_198800(&t->unk_E8);
            plog("soldiers: trigger %d: class %08X,%08X (%s kind %d, script %d), task %08X,%08X (%s kind %d, function %d)",
                 i, t->unk_E0.unk_00, t->unk_E0.unk_04, pClass ? "read," : "not read,", pClass ? pClass->vf_008() : -1,
                 pClass ? pClass->get_unk_18() : -1, t->unk_E8.unk_00, t->unk_E8.unk_04, pTask ? "read," : "not read,",
                 pTask ? pTask->vf_008() : -1, pTask ? pTask->get_unk_18() : -1);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    plog("soldiers: %d distinct soldier trigger scripts", n);
}

// ---- path graphs for the multiplayer maps (the AI soldiers' A*) ----
//
// The multiplayer maps ship an empty path record (GodData kind 13: its 28-byte header alone), so
// the A* finds nothing. Here one is made from the map's collision, in the layout sub_F8350 reads
// (C:\cfh-web-suite\PATHFINDING.md): a lattice of waypoints (type 1) every PATH_STEP cm over
// the floor the players can walk from the spawn points, each linked to the lattice neighbours
// (and the ones two out) it can walk to: steps no higher than PATH_STEP_UP, no drops deeper
// than PATH_DROP, nothing in the way at knee or chest height. The graph's grid lists each
// cell's nodes, as the shipped graphs' do. It is saved as paths\<map>.pth beside the exe and
// read back from there next time; loaded through sub_F8350 itself, from a memory stream.
//
// CODFH_PATHS=1 makes one when the map has none (CODFH_SPAWNAI does too); CODFH_PATHS=regen
// makes it again over the saved one; CODFH_PATHS=off neither makes nor loads one.
// CODFH_PATHS_STEP sets the lattice step (cm), CODFH_PATHS_DRAW=1 turns on the path view.

#ifndef CODFH_SP
void sub_F8350(RwStream *arg_0);
extern "C" const char *port_map_name;

#define PATH_STEP       150.0f
#define PATH_STEP_UP    60.0f   // the most a soldier steps up between two samples
#define PATH_DROP       100.0f  // the deepest it steps down
#define PATH_HEAD       170.0f  // the headroom a node needs
#define PATH_MAX_NODES  4000    // node IDs are 12 bits, 0 the null node
#define PATH_MAX_LINKS  24
#define PATH_CELL       500

struct PathGenNode
{
    RwInt32 ix, iz;
    RwV3d v;
    RwInt32 nLinks;
    RwUInt16 anLinks[PATH_MAX_LINKS];
};

static PathGenNode *s_aPathGen;
static RwInt32 s_nPathGen;

// The floor below (x, fTop, z), within fRange under it: its height in *pfY.
static RwBool PathFloor(RwReal x, RwReal fTop, RwReal z, RwReal fRange, RwReal *pfY)
{
    RpIntersection is;
    RwReal fHit = 2.0f;
    RpWorld *pWorld;
    RwInt32 i;

    is.type = rpINTERSECTLINE;
    is.t.line.start.x = is.t.line.end.x = x;
    is.t.line.start.z = is.t.line.end.z = z;
    is.t.line.start.y = fTop;
    is.t.line.end.y = fTop - fRange;
    for (i = 0; i <= 4; i++)
    {
        pWorld = i < 4 ? (dword_4E5D30[i].get_unk_00() ? dword_4E5D30[i].get_unk_28() : NULL) : unk_4E5CD8.get_unk_28();
        if (pWorld)
            RpCollisionWorldForAllIntersections(pWorld, &is, GroundHit, &fHit);
    }
    if (fHit > 1.0f)
        return FALSE;
    *pfY = fTop - fRange * fHit;
    return TRUE;
}

static RwBool PathClear(RwReal ax, RwReal ay, RwReal az, RwReal bx, RwReal by, RwReal bz)
{
    RwV3d a, b;

    a.x = ax;
    a.y = ay;
    a.z = az;
    b.x = bx;
    b.y = by;
    b.z = bz;
    return LineClear(&a, &b);
}

// Whether a soldier walks from *pA (on the floor) to the column (bx, bz): the floor sampled
// along the way, each step up at most PATH_STEP_UP and down at most PATH_DROP, and nothing at
// knee or chest height between the samples; the floor's height there in *pfY.
static RwBool PathWalk(const RwV3d *pA, RwReal bx, RwReal bz, RwReal *pfY)
{
    RwReal fLast = pA->y, fLen = (RwReal)sqrt((bx - pA->x) * (bx - pA->x) + (bz - pA->z) * (bz - pA->z));
    RwReal px = pA->x, pz = pA->z;
    RwInt32 n = (RwInt32)(fLen / 75.0f) + 1, k;

    for (k = 1; k <= n; k++)
    {
        RwReal t = (RwReal)k / n, x = pA->x + (bx - pA->x) * t, z = pA->z + (bz - pA->z) * t, y;

        if (!PathFloor(x, fLast + PATH_STEP_UP, z, PATH_STEP_UP + PATH_DROP, &y))
            return FALSE;
        if (!PathClear(px, fLast + 50.0f, pz, x, y + 50.0f, z) || !PathClear(px, fLast + 130.0f, pz, x, y + 130.0f, z))
            return FALSE;
        fLast = y;
        px = x;
        pz = z;
    }
    *pfY = fLast;
    return TRUE;
}

// Whether a node may stand at *pv: headroom, and no wall within 25 cm at knee height.
static RwBool PathStand(const RwV3d *pv)
{
    static const RwReal s_af[4][2] = { { 25.0f, 0.0f }, { -25.0f, 0.0f }, { 0.0f, 25.0f }, { 0.0f, -25.0f } };
    RwInt32 i;

    if (!PathClear(pv->x, pv->y + 20.0f, pv->z, pv->x, pv->y + PATH_HEAD, pv->z))
        return FALSE;
    for (i = 0; i < 4; i++)
        if (!PathClear(pv->x, pv->y + 50.0f, pv->z, pv->x + s_af[i][0], pv->y + 50.0f, pv->z + s_af[i][1]))
            return FALSE;
    return TRUE;
}

// The node at lattice (ix, iz) within 120 cm of the height y, or -1.
static RwInt32 PathFind(RwInt32 ix, RwInt32 iz, RwReal y)
{
    RwInt32 i;

    // (a linear search: the lattice is a few thousand nodes, made once)
    for (i = 0; i < s_nPathGen; i++)
        if (s_aPathGen[i].ix == ix && s_aPathGen[i].iz == iz && fabs(s_aPathGen[i].v.y - y) < 120.0f)
            return i;
    return -1;
}

static void PathLink(RwInt32 a, RwInt32 b)
{
    RwInt32 i;

    for (i = 0; i < s_aPathGen[a].nLinks; i++)
        if (s_aPathGen[a].anLinks[i] == b)
            return;
    if (s_aPathGen[a].nLinks < PATH_MAX_LINKS)
        s_aPathGen[a].anLinks[s_aPathGen[a].nLinks++] = (RwUInt16)b;
}

static RwInt32 PathAdd(RwInt32 ix, RwInt32 iz, const RwV3d *pv)
{
    PathGenNode *p;

    if (s_nPathGen >= PATH_MAX_NODES)
        return -1;
    p = &s_aPathGen[s_nPathGen];
    memset(p, 0, sizeof(*p));
    p->ix = ix;
    p->iz = iz;
    p->v = *pv;
    return s_nPathGen++;
}

// A seed: the lattice point nearest *pv (on the floor) that it walks to.
static void PathSeed(const RwV3d *pv, RwReal fStep)
{
    RwInt32 ix = (RwInt32)floor(pv->x / fStep + 0.5f), iz = (RwInt32)floor(pv->z / fStep + 0.5f), dx, dz;
    RwV3d vFloor = *pv;

    if (!PathFloor(pv->x, pv->y + 100.0f, pv->z, 400.0f, &vFloor.y))
        return;
    for (dz = 0; dz <= 1; dz++)
        for (dx = 0; dx <= 1; dx++)
        {
            RwReal y;
            RwV3d v;
            RwInt32 jx = ix + (dx ? (pv->x / fStep > ix ? 1 : -1) : 0), jz = iz + (dz ? (pv->z / fStep > iz ? 1 : -1) : 0);

            v.x = jx * fStep;
            v.z = jz * fStep;
            if (!PathWalk(&vFloor, v.x, v.z, &y))
                continue;
            v.y = y;
            if (PathFind(jx, jz, y) < 0 && PathStand(&v))
            {
                PathAdd(jx, jz, &v);
                return;
            }
        }
}

// The graph made: the flood from the seeds, then the longer links.
static void PathGenerate(RwReal fStep)
{
    static const RwInt32 s_anDir[8][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
    RwInt32 i, k, nHead, nPoints = 0, dx, dz;
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d v;

    s_nPathGen = 0;
    // (the seeds: every spawn point, and the player where it is)
    __try
    {
        nPoints = unk_4FBC50.unk_00.unk_08;
        for (i = 0; i < nPoints && i < 256; i++)
        {
            RwMatrix *pAt = unk_4FBC50.sub_1C20F0(i);

            if (pAt)
                PathSeed(&pAt->pos, fStep);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        plog("paths: reading the spawn points faulted");
    }
    if (pPlayer && PlayerPosition(pPlayer, &v))
        PathSeed(&v, fStep);
    plog("paths: %d seeds from %d spawn points and the player", s_nPathGen, nPoints);
    // (the flood: each node's eight lattice neighbours it walks to, both ways)
    for (nHead = 0; nHead < s_nPathGen; nHead++)
    {
        for (k = 0; k < 8; k++)
        {
            RwInt32 jx = s_aPathGen[nHead].ix + s_anDir[k][0], jz = s_aPathGen[nHead].iz + s_anDir[k][1], j;
            RwReal y, yBack;
            RwV3d vTo;

            if (!PathWalk(&s_aPathGen[nHead].v, jx * fStep, jz * fStep, &y))
                continue;
            vTo.x = jx * fStep;
            vTo.y = y;
            vTo.z = jz * fStep;
            if (!PathWalk(&vTo, s_aPathGen[nHead].v.x, s_aPathGen[nHead].v.z, &yBack) || fabs(yBack - s_aPathGen[nHead].v.y) > 30.0f)
                continue;
            j = PathFind(jx, jz, y);
            if (j < 0)
            {
                if (!PathStand(&vTo))
                    continue;
                j = PathAdd(jx, jz, &vTo);
                if (j < 0)
                    break;
            }
            PathLink(nHead, j);
            PathLink(j, nHead);
        }
    }
    // (the longer links: the nodes two lattice steps out, and a knight's move, walked both ways)
    for (i = 0; i < s_nPathGen; i++)
        for (dz = -2; dz <= 2; dz++)
            for (dx = -2; dx <= 2; dx++)
            {
                RwInt32 j;
                RwReal y, yBack;

                if (dx > -2 && dx < 2 && dz > -2 && dz < 2)
                    continue;
                if (s_aPathGen[i].nLinks >= PATH_MAX_LINKS)
                    break;
                for (j = 0; j < s_nPathGen; j++)
                    if (j > i && s_aPathGen[j].ix == s_aPathGen[i].ix + dx && s_aPathGen[j].iz == s_aPathGen[i].iz + dz
                        && fabs(s_aPathGen[j].v.y - s_aPathGen[i].v.y) < 250.0f)
                        break;
                if (j >= s_nPathGen)
                    continue;
                if (!PathWalk(&s_aPathGen[i].v, s_aPathGen[j].v.x, s_aPathGen[j].v.z, &y) || fabs(y - s_aPathGen[j].v.y) > 30.0f)
                    continue;
                if (!PathWalk(&s_aPathGen[j].v, s_aPathGen[i].v.x, s_aPathGen[i].v.z, &yBack)
                    || fabs(yBack - s_aPathGen[i].v.y) > 30.0f)
                    continue;
                PathLink(i, j);
                PathLink(j, i);
            }
}

// A growing byte buffer.
struct PathBuf
{
    RwUInt8 *p;
    RwInt32 n, nMax;
};

static void PathPut(PathBuf *b, const void *pData, RwInt32 n)
{
    if (b->n + n > b->nMax)
    {
        RwInt32 nMax = (b->nMax ? b->nMax * 2 : 65536) + n;
        RwUInt8 *p = (RwUInt8 *)realloc(b->p, nMax);

        if (p == NULL)
            return;
        b->p = p;
        b->nMax = nMax;
    }
    memcpy(b->p + b->n, pData, n);
    b->n += n;
}

static void PathPutU32(PathBuf *b, RwUInt32 dw)
{
    PathPut(b, &dw, 4);
}

// A link list: two 12-bit IDs a word, ended by a zero ID (a zero word after an even count).
static void PathPutLinks(PathBuf *b, const RwUInt16 *pn, RwInt32 n)
{
    RwInt32 i;

    for (i = 0; i < n; i += 2)
        PathPutU32(b, (RwUInt32)pn[i] | (i + 1 < n ? (RwUInt32)pn[i + 1] << 12 : 0));
    if (!(n & 1))
        PathPutU32(b, 0);
}

// A structure chunk (ID 1).
static void PathPutChunk(PathBuf *b, const PathBuf *pData)
{
    PathPutU32(b, 1);
    PathPutU32(b, (RwUInt32)pData->n);
    PathPutU32(b, 0x1803FFFF);  // (the library stamp the level files carry)
    PathPut(b, pData->p, pData->n);
}

// The graph made into the six structures sub_F8350 reads, into *pOut.
static RwBool PathPack(PathBuf *pOut)
{
    PathBuf aPart[6];
    RwInt32 i, nCells, nLists = 0, nMinX, nMinZ, nW, nH;
    RwReal fMinX = 1e30f, fMinZ = 1e30f, fMaxX = -1e30f, fMaxZ = -1e30f;
    RwUInt16 *pnCell;
    RwUInt32 adwHeader[24];

    memset(aPart, 0, sizeof(aPart));
    for (i = 0; i < s_nPathGen; i++)
    {
        fMinX = s_aPathGen[i].v.x < fMinX ? s_aPathGen[i].v.x : fMinX;
        fMinZ = s_aPathGen[i].v.z < fMinZ ? s_aPathGen[i].v.z : fMinZ;
        fMaxX = s_aPathGen[i].v.x > fMaxX ? s_aPathGen[i].v.x : fMaxX;
        fMaxZ = s_aPathGen[i].v.z > fMaxZ ? s_aPathGen[i].v.z : fMaxZ;
    }
    nMinX = (RwInt32)floor(fMinX / PATH_CELL) - 1;
    nMinZ = (RwInt32)floor(fMinZ / PATH_CELL) - 1;
    nW = (RwInt32)floor(fMaxX / PATH_CELL) + 2 - nMinX;
    nH = (RwInt32)floor(fMaxZ / PATH_CELL) + 2 - nMinZ;
    nCells = nW * nH;
    pnCell = (RwUInt16 *)malloc(nCells * sizeof(RwUInt16));
    if (pnCell == NULL)
        return FALSE;
    // (the nodes, IDs from 1: the null node's offset first)
    PathPutU32(&aPart[1], 0);
    for (i = 0; i < s_nPathGen; i++)
    {
        RwUInt16 anTo[PATH_MAX_LINKS];
        RwInt32 k;
        RwUInt32 dwZero = 0;

        PathPutU32(&aPart[1], (RwUInt32)aPart[2].n);
        PathPutU32(&aPart[2], 0);               // flags
        PathPutU32(&aPart[2], 1);               // type 1, a waypoint (and the reserved half)
        PathPutU32(&aPart[2], dwZero);          // the runtime words
        PathPutU32(&aPart[2], dwZero);
        PathPut(&aPart[2], &s_aPathGen[i].v, sizeof(RwV3d));
        for (k = 0; k < s_aPathGen[i].nLinks; k++)
            anTo[k] = (RwUInt16)(s_aPathGen[i].anLinks[k] + 1);
        PathPutLinks(&aPart[2], anTo, s_aPathGen[i].nLinks);
    }
    // (the grid: each cell's own nodes)
    for (i = 0; i < nCells; i++)
    {
        RwUInt16 anIn[512];
        RwInt32 n = 0, k, cx = i % nW, cz = i / nW;

        for (k = 0; k < s_nPathGen && n < 511; k++)
            if ((RwInt32)floor(s_aPathGen[k].v.x / PATH_CELL) - nMinX == cx
                && (RwInt32)floor(s_aPathGen[k].v.z / PATH_CELL) - nMinZ == cz)
                anIn[n++] = (RwUInt16)(k + 1);
        if (n == 0)
        {
            pnCell[i] = 0xFFFF;
            continue;
        }
        pnCell[i] = (RwUInt16)nLists++;
        PathPutU32(&aPart[4], (RwUInt32)aPart[5].n);
        PathPutLinks(&aPart[5], anIn, n);
    }
    PathPut(&aPart[3], pnCell, nCells * sizeof(RwUInt16));
    free(pnCell);
    // (the header: the format, the cell size, the node count with the null node, the grid, the
    // structures' sizes; the pointer slots zero)
    memset(adwHeader, 0, sizeof(adwHeader));
    adwHeader[0] = 5;
    adwHeader[1] = PATH_CELL;
    adwHeader[2] = (RwUInt32)(s_nPathGen + 1);
    {
        RwReal afOrigin[3];

        afOrigin[0] = (RwReal)(nMinX * PATH_CELL);
        afOrigin[1] = 0.0f;
        afOrigin[2] = (RwReal)(nMinZ * PATH_CELL);
        memcpy(&adwHeader[6], afOrigin, sizeof(afOrigin));
    }
    adwHeader[9] = (RwUInt32)nW;
    adwHeader[10] = (RwUInt32)nH;
    adwHeader[12] = (RwUInt32)aPart[1].n;
    adwHeader[14] = (RwUInt32)aPart[2].n;
    adwHeader[16] = (RwUInt32)aPart[3].n;
    adwHeader[17] = (RwUInt32)nLists;
    adwHeader[19] = (RwUInt32)aPart[4].n;
    adwHeader[21] = (RwUInt32)aPart[5].n;
    PathPut(&aPart[0], adwHeader, sizeof(adwHeader));
    for (i = 0; i < 6; i++)
    {
        PathPutChunk(pOut, &aPart[i]);
        free(aPart[i].p);
    }
    plog("paths: packed %d nodes, a %d x %d grid of %d cm cells from (%d, %d), %d cell lists, %d bytes", s_nPathGen, nW, nH,
         PATH_CELL, nMinX * PATH_CELL, nMinZ * PATH_CELL, nLists, pOut->n);
    return TRUE;
}

// The structures pData (n bytes) loaded as the level's graph (sub_F8350, from a memory stream).
static RwBool PathLoad(void *pData, RwInt32 n)
{
    RwMemory mem;
    RwStream *pStream;

    mem.start = (RwUInt8 *)pData;
    mem.length = (RwUInt32)n;
    pStream = RwStreamOpen(rwSTREAMMEMORY, rwSTREAMREAD, &mem);
    if (pStream == NULL)
        return FALSE;
    sub_F8350(pStream);
    RwStreamClose(pStream, &mem);
    plog("paths: loaded: %d nodes, a %d x %d grid; ready %d", unk_4C00E8.unk_08 - 1, unk_4C00E8.unk_24, unk_4C00E8.unk_28,
         unk_4C00E8.unk_64);
    return unk_4C00E8.unk_64 != 0;
}

#endif

// Each frame: once the player is in a map with no graph, the saved one loaded, or one made.
static void PathsTick()
{
#ifndef CODFH_SP
    static RwInt32 s_nMode = -1;    // 0 off, 1 load, 2 make when none is saved, 3 make again
    static RwUInt32 s_dwIn;
    static RwBool s_bDone, s_bHad;
    RwChar szEnv[32], szPath[MAX_PATH];

    if (s_nMode < 0)
    {
        s_nMode = 1;
        if (GetEnvironmentVariableA("CODFH_PATHS", szEnv, sizeof(szEnv)))
            s_nMode = !_stricmp(szEnv, "off") ? 0 : !_stricmp(szEnv, "regen") ? 3 : 2;
        else if (GetEnvironmentVariableA("CODFH_SPAWNAI", NULL, 0) || GetEnvironmentVariableA("CODFH_BOTS", NULL, 0))
            s_nMode = 2;
        if (GetEnvironmentVariableA("CODFH_PATHS_DRAW", NULL, 0))
            g_bTrigDrawPathNodes = TRUE;
    }
    if (s_nMode == 0 || port_map_name == NULL || !port_map_name[0])
        return;
    if (unk_4F7EB8.unk_1A4 == NULL)
    {
        s_dwIn = 0;
        return;
    }
    if (!s_dwIn)
        s_dwIn = port_frame;
    // (a restart releases the graph, sub_F8270: loaded again)
    if (unk_4C00E8.unk_64)
        s_bDone = s_bHad = TRUE;
    else if (s_bHad)
        s_bDone = s_bHad = FALSE;
    if (s_bDone || port_frame - s_dwIn < 10)
        return;
    s_bDone = TRUE;
    CreateDirectoryA("paths", NULL);
    _snprintf(szPath, sizeof(szPath), "paths\\%s.pth", port_map_name);
    szPath[sizeof(szPath) - 1] = 0;
    if (s_nMode != 3)
    {
        FILE *pFile = fopen(szPath, "rb");

        if (pFile)
        {
            RwInt32 n;
            void *p;

            fseek(pFile, 0, SEEK_END);
            n = ftell(pFile);
            fseek(pFile, 0, SEEK_SET);
            p = malloc(n > 0 ? n : 1);
            if (p && fread(p, 1, n, pFile) == (size_t)n)
            {
                plog("paths: %s (%d bytes)", szPath, n);
                PathLoad(p, n);
            }
            free(p);
            fclose(pFile);
            return;
        }
        if (s_nMode == 1)
            return;
    }
    {
        RwChar szStep[16];
        RwReal fStep = GetEnvironmentVariableA("CODFH_PATHS_STEP", szStep, sizeof(szStep)) ? (RwReal)atof(szStep) : PATH_STEP;
        RwUInt32 dwStart = GetTickCount();
        PathBuf out;
        RwInt32 i, nLinks = 0;

        if (fStep < 100.0f)
            fStep = PATH_STEP;
        if (s_aPathGen == NULL)
            s_aPathGen = (PathGenNode *)malloc(PATH_MAX_NODES * sizeof(PathGenNode));
        if (s_aPathGen == NULL)
            return;
        __try
        {
            PathGenerate(fStep);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            plog("paths: making the graph faulted (%d nodes so far)", s_nPathGen);
            return;
        }
        for (i = 0; i < s_nPathGen; i++)
            nLinks += s_aPathGen[i].nLinks;
        plog("paths: made %d nodes%s, %d links, every %.0f cm, in %u ms", s_nPathGen,
             s_nPathGen >= PATH_MAX_NODES ? " (the most there can be: a larger CODFH_PATHS_STEP covers more)" : "", nLinks,
             fStep, GetTickCount() - dwStart);
        if (s_nPathGen < 2)
            return;
        memset(&out, 0, sizeof(out));
        if (!PathPack(&out))
            return;
        {
            FILE *pFile = fopen(szPath, "wb");

            if (pFile)
            {
                fwrite(out.p, 1, out.n, pFile);
                fclose(pFile);
                plog("paths: saved %s", szPath);
            }
        }
        PathLoad(out.p, out.n);
        free(out.p);
    }
#endif
}

// (set when the player is placed at CODFH_SPAWNTRIGGER's trigger: the spawn test's soldier is
// brought back in front of it, SpawnAiTestTick)
static RwBool s_bSpawnAiBringNear;

static void AutoSpawnTick()
{
#ifndef CODFH_SP
    static RwUInt32 s_dwLast;

    // (CODFH_SPAWNPOINT=n: once the player is in, moved to spawn point n, as the respawn places
    // it at the point it was given: the spawn points' matrix, sub_1C20F0)
    {
        static RwInt32 s_nPoint = -2;
        RwChar szPoint[16];

        static RwInt32 s_nTrigger = -2;

        if (s_nPoint == -2)
            s_nPoint = GetEnvironmentVariableA("CODFH_SPAWNPOINT", szPoint, sizeof(szPoint)) ? atoi(szPoint) : -1;
        // (CODFH_SPAWNTRIGGER=n: at trigger n's place instead, unk_90)
        if (s_nTrigger == -2)
            s_nTrigger = GetEnvironmentVariableA("CODFH_SPAWNTRIGGER", szPoint, sizeof(szPoint)) ? atoi(szPoint) : -1;
        static RwUInt32 s_dwIn;
        static RwBool s_bPlaced;

        // (a second after the player is in: the respawn's own placing is done by then; again each
        // life)
        if (unk_4F7EB8.unk_1A4 == NULL)
        {
            s_dwIn = 0;
            s_bPlaced = FALSE;
        }
        else if (!s_dwIn)
            s_dwIn = port_frame;
        if (s_nTrigger >= 0 && !s_bPlaced && s_dwIn && port_frame - s_dwIn > 60)
        {
            Trigger *pTrigger = s_nTrigger < 2000 ? (Trigger *)dword_4CFE30[s_nTrigger] : NULL;

            if (pTrigger)
            {
                RwV3d v;

                v.x = pTrigger->unk_90;
                v.y = pTrigger->unk_94;
                v.z = pTrigger->unk_98;
                Teleport((type_10F710 *)unk_4F7EB8.unk_1A4, &v);
                plog("spawnpoint: the player at trigger %d (kind %d): (%.0f, %.0f, %.0f)", s_nTrigger, pTrigger->vf_008(),
                     v.x, v.y, v.z);
                s_bSpawnAiBringNear = TRUE;
            }
            else
            {
                plog("spawnpoint: no trigger %d", s_nTrigger);
                s_nTrigger = -1;
            }
            s_bPlaced = TRUE;
        }
        if (s_nPoint >= 0 && s_dwIn && port_frame - s_dwIn > 60)
        {
            __try
            {
                RwInt32 nPoints = unk_4FBC50.unk_00.unk_08;
                RwMatrix *pAt = s_nPoint < nPoints ? unk_4FBC50.sub_1C20F0(s_nPoint) : NULL;

                if (pAt)
                {
                    RwV3d v = pAt->pos;

                    Teleport((type_10F710 *)unk_4F7EB8.unk_1A4, &v);
                    plog("spawnpoint: the player at spawn point %d of %d: (%.0f, %.0f, %.0f)", s_nPoint, nPoints, v.x, v.y, v.z);
                }
                else
                    plog("spawnpoint: no spawn point %d (the level has %d)", s_nPoint, nPoints);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                plog("spawnpoint: placing the player faulted");
            }
            s_nPoint = -1;
        }
    }
    if (!port_autospawn)
        return;
    // (the spawn's own screens over the game, the in-game screens' 7, the initial team selection,
    // and 6, the initial weapon selection, answered as pressing A answers them: the team "auto"
    // (type_217F40::sub_218110) and the weapon shown (type_223280::sub_223830))
    __try
    {
        type_1FF250 *pScreens = dword_5043BC;

        if (pScreens && pScreens->unk_3C && pScreens->unk_10[7] && pScreens->unk_0C == 7)
        {
            ((type_217F40 *)pScreens->unk_10[7])->sub_218110();
            plog("autospawn: team selection answered: auto");
        }
        else if (pScreens && pScreens->unk_3C && pScreens->unk_10[6] && pScreens->unk_0C == 6)
        {
            ((type_223280 *)pScreens->unk_10[6])->sub_223830();
            plog("autospawn: weapon selection answered: the weapon shown");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    // (the weapon screen the game opens as the player spawns: for ten seconds after asking, any
    // in-game menu that opens is closed the same way; one opened later is the player's own)
    if (s_dwLast && port_frame - s_dwLast < 600)
    {
        __try
        {
            type_21A5E0 *pMenu = dword_5051D8;

            // (the pause menu's pages: 1 the weapon selection, 2 the team selection, unk_154 the
            // one shown; closed as sub_1C4B10 closes the menu, whether or not its flag is up)
            if (pMenu && (pMenu->unk_154 == 1 || pMenu->unk_154 == 2))
            {
                RwInt32 nPage = pMenu->unk_154;

                sub_227560()->set_unk_A4(0);
                sub_1FF250()->sub_2007A0(0);
                pMenu->sub_21C360();
                dword_4FB9E0.sub_1B5250(1);
                plog("autospawn: closed the %s screen that opened with the spawn", nPage == 1 ? "weapon" : "team");
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    // (a respawn takes a moment to make the soldier: five seconds before asking again)
    if (s_dwLast && port_frame - s_dwLast < 300)
        return;
    __try
    {
        if (unk_4F7EB8.unk_1A4 != NULL || unk_4F7EB8.unk_284 || ((dword_4B86F8 >> 4) & 1)
            || ((kujuUI::type_1C8DF0_104_00 *)&dword_4FB9E0)->sub_1E3480() != 1)
            return;
        s_dwLast = port_frame;
        // (the team and weapon screens' own end, sub_1C4B10: the in-game menu closed and the
        // player marked ready, as picking a weapon does; then the spawn button's calls)
        sub_1C4B10();
        sub_124EE0(0.5f, 1);
        unk_4F7EB8.sub_1AB400(0);
        plog("autospawn: asked to spawn (view %d)", unk_4F7EB8.unk_2A4);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
#endif
}

// (from the sound aliases' play, type_3DFC34::vf_00C, unit_192BE0: CODFH_SPAWNAI's test logs the
// first few plays of each alias from the player, and whether the AI hear it (unk_17))
void TrigSoundAliasPlayed(const void *pAlias, const void *pSource, RwInt32 nKind, RwInt32 bHeard, RwInt32 bAtOnce,
                          RwReal fRange, RwInt32 nVoice)
{
    static RwInt32 s_bOn = -1;
    static const void *s_apSeen[64];
    static RwInt32 s_anSeen[64], s_nSeen;
    RwInt32 i;

    if (s_bOn < 0)
        s_bOn = GetEnvironmentVariableA("CODFH_SPAWNAI", NULL, 0) ? 1 : 0;
    if (!s_bOn)
        return;
    for (i = 0; i < s_nSeen; i++)
        if (s_apSeen[i] == pAlias)
            break;
    if (i == s_nSeen)
    {
        if (s_nSeen >= 64)
            return;
        s_apSeen[s_nSeen] = pAlias;
        s_anSeen[s_nSeen++] = 0;
    }
    if (s_anSeen[i]++ >= 3)
        return;
    __try
    {
        const type_3DF8D8 *p = (const type_3DF8D8 *)pAlias;

        plog("sounds: %s played alias %08X,%08X (kind %d): heard by the AI %d, at once %d, range %.0f, voice %d",
             pSource == NULL ? "nothing" : pSource == (const void *)sub_1745A0(0) ? "the player" : "an entity",
             p->unk_04.unk_00, p->unk_04.unk_04, nKind, bHeard, bAtOnce, fRange, nVoice);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

// (port/src/debug/trigdraw.cpp's noise counts; AIHearing's listeners and its noise, unit_03C1D0)
extern RwInt32 g_nTrigNoisesMade, g_nTrigNoisesHeard;
extern RwInt32 g_nTrigLastNoiseKind, g_nTrigLastNoiseClass;
extern RwReal g_fTrigLastNoiseRange;
extern type_3C720 *dword_43925C;
void sub_3C4B0(type_3D3548 *arg_0, RwInt32 arg_4, RwV3d *arg_8, RwInt32 arg_C, RwReal arg_10,
               RwInt32 arg_14, RwReal arg_18);

// The soldier pSoldier turned to face the point pvAt: its frame upright towards it, and its facing
// told (vf_0D8).
static void SpawnAiFace(type_3D3548 *pSoldier, const RwV3d *pvAt)
{
    RwFrame *pFrame = pSoldier->get_unk_340();
    RwV3d *pv = pSoldier->sub_CD550(), at;
    RwReal fLen;

    if (pFrame == NULL || pv == NULL)
        return;
    at.x = pvAt->x - pv->x;
    at.y = 0.0f;
    at.z = pvAt->z - pv->z;
    fLen = (RwReal)sqrt(at.x * at.x + at.z * at.z);
    if (fLen > 0.01f)
    {
        RwMatrix *m = RwFrameGetMatrix(pFrame);
        RwV3d pos = m->pos;

        at.x /= fLen;
        at.z /= fLen;
        m->at = at;
        m->up.x = 0.0f;
        m->up.y = 1.0f;
        m->up.z = 0.0f;
        RwV3dCrossProduct(&m->right, &m->up, &m->at);
        m->pos = pos;
        RwMatrixUpdate(m);
        RwFrameUpdateObjects(pFrame);
        pSoldier->vf_0D8(&at);
    }
}

// The soldier pSoldier moved 3 m in front of the player (its view, on the floor below its waist)
// and turned to face it.
static void SpawnAiBringNear(type_3D3548 *pSoldier, type_10F710 *pPlayer)
{
    RwV3d v, vMe;

    if (!PlayerPosition(pPlayer, &vMe))
        return;
    v = vMe;
    __try
    {
        RwMatrix *pLtm = dword_4E5C74 ? RwFrameGetLTM(RwCameraGetFrame((RwCamera *)dword_4E5C74)) : NULL;
        RwFrame *pBody = pPlayer->get_unk_340();
        RwMatrix *pBodyLtm = pBody ? RwFrameGetLTM(pBody) : NULL;
        // (the player's body's facing; the camera's only when it has none)
        RwV3d *pAt = pBodyLtm ? &pBodyLtm->at : pLtm ? &pLtm->at : NULL;
        RwReal fLen = pAt ? (RwReal)sqrt(pAt->x * pAt->x + pAt->z * pAt->z) : 0.0f;

        plog("spawnai: facings: camera (%.2f, %.2f), body (%.2f, %.2f)", pLtm ? pLtm->at.x : 0.0f, pLtm ? pLtm->at.z : 0.0f,
             pBodyLtm ? pBodyLtm->at.x : 0.0f, pBodyLtm ? pBodyLtm->at.z : 0.0f);
        if (fLen > 0.01f)
        {
            v.x += pAt->x / fLen * 300.0f;
            v.z += pAt->z / fLen * 300.0f;
        }
        v.y += 40.0f;
        if (!GroundBelow(&v))
            v.y -= 40.0f;
        pSoldier->vf_0C0(&v);
        SpawnAiFace(pSoldier, &vMe);
        plog("spawnai: the soldier brought 3 m in front of the player: (%.0f, %.0f, %.0f)", v.x, v.y, v.z);
        {
            RwFrame *pFrame = pSoldier->get_unk_340();
            RwV3d vFeet = vMe;

            if (pFrame)
                plog("spawnai:   its frame at (%.0f, %.0f, %.0f), its position (%.0f, %.0f, %.0f)",
                     RwFrameGetLTM(pFrame)->pos.x, RwFrameGetLTM(pFrame)->pos.y, RwFrameGetLTM(pFrame)->pos.z,
                     pSoldier->sub_CD550()->x, pSoldier->sub_CD550()->y, pSoldier->sub_CD550()->z);
            plog("spawnai:   the player's floor %s %.0f", GroundBelow(&vFeet) ? "at" : "not found; at", vFeet.y);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        plog("spawnai: bringing the soldier near faulted");
    }
}

// ---- bots: AI soldiers on both teams, at their teams' spawn points (CODFH_BOTS) ----
//
// CODFH_BOTS=n puts n AI soldiers on each team, CODFH_BOTS=a,e a on the local player's and e on
// the other. Each is single player's soldier (SpawnAiSoldierMp) made from the network player's
// trigger dressed as a remote player of its team is (sub_1AED80: the level's network settings
// give the team's soldier definition, sub_1B7910), on its team's side, at one of its team's
// spawn points (the game type's lists, sub_1C2050) facing the way the point does, its vision on
// (AI flag 0x20). A dead bot's place is taken by a new one 5 s later, at a spawn point again.

#ifndef CODFH_SP
#define BOTS_MAX 16

struct TrigBot
{
    type_3D3548 *pSoldier;
    RwInt32 nTeam;          // the team's code: 2 or 4
    RwUInt32 dwSide;        // its entity side (unk_2C & 7)
    RwUInt32 dwRespawnAt;   // the frame it is made again (0: alive or not yet made)
    RwUInt32 dwMadeAt;
};

static TrigBot s_aBots[BOTS_MAX];
static RwInt32 s_nBots;
static RwInt32 s_anBotPoint[2];

// Whether the entity is still in the entity table.
static RwBool BotAlive(type_3D3548 *pSoldier)
{
    RwInt32 k;

    if (pSoldier == NULL)
        return FALSE;
    for (k = 0; k < 0x300; k++)
        if (dword_4B6A00[k].unk_04 == pSoldier)
            break;
    if (k == 0x300)
        return FALSE;
    __try
    {
        return pSoldier->vf_174() > 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

// A spawn point of team nTeam's list (or of all, with none) away from the other team, as the
// game's default rule picks (farthest from the nearest enemy): one of the four farthest from
// the nearest living enemy bot (and the player, when it is one), at random; its matrix.
static RwMatrix *BotPoint(RwInt32 nTeam)
{
    RwInt32 nList = unk_4FBC50.sub_1C2050(nTeam, -1), nCount, i, k, n = 0;
    type_1C0F60 *pList = nList >= 0 ? &unk_4FBC50.unk_26C[nList] : &unk_4FBC50.unk_00;
    RwMatrix *apBest[4];
    RwReal afBest[4];
    RwV3d vMe;
    RwBool bMe = unk_4F7EB8.unk_1A4 && nTeam != unk_4F7EB8.unk_29C && PlayerPosition((type_10F710 *)unk_4F7EB8.unk_1A4, &vMe);

    nCount = pList->unk_08;
    for (i = 0; i < nCount; i++)
    {
        RwMatrix *m = pList->sub_1C1B80(i);
        RwReal fNear = 1e30f, d;

        RwBool bTaken = FALSE;

        if (m == NULL)
            continue;
        for (k = 0; k < s_nBots; k++)
            if (BotAlive(s_aBots[k].pSoldier))
            {
                RwV3d *pv = s_aBots[k].pSoldier->sub_CD550();

                d = pv ? (pv->x - m->pos.x) * (pv->x - m->pos.x) + (pv->z - m->pos.z) * (pv->z - m->pos.z) : 1e30f;
                // (a point a bot stands on is taken: kept only when every point is)
                if (d < 200.0f * 200.0f)
                    bTaken = TRUE;
                if (s_aBots[k].nTeam != nTeam)
                    fNear = d < fNear ? d : fNear;
            }
        if (bTaken)
            fNear = -1.0f;
        if (bMe)
        {
            d = (vMe.x - m->pos.x) * (vMe.x - m->pos.x) + (vMe.z - m->pos.z) * (vMe.z - m->pos.z);
            fNear = d < fNear ? d : fNear;
        }
        // (kept among the four farthest, farthest first)
        if (n == 4 && fNear <= afBest[3])
            continue;
        k = n < 4 ? n++ : 3;
        for (; k > 0 && afBest[k - 1] < fNear; k--)
        {
            apBest[k] = apBest[k - 1];
            afBest[k] = afBest[k - 1];
        }
        apBest[k] = m;
        afBest[k] = fNear;
    }
    return n ? apBest[rand() % n] : NULL;
}

// Bot b made: dressed as its team's remote players, at one of its team's points.
static void BotSpawn(TrigBot *b)
{
    SoldierTrigger *pTrigger = (SoldierTrigger *)dword_4F8134;
    RwMatrix *m = BotPoint(b->nTeam);
    type_3DF8D8_04 oldDef;
    type_3D3548 *pSoldier;
    RwV3d v, vAt;

    b->pSoldier = NULL;
    if (pTrigger == NULL || m == NULL)
    {
        plog("bots: no %s", pTrigger ? "spawn point" : "network soldier trigger");
        return;
    }
    RwBool bTeamDef = FALSE;

    oldDef = pTrigger->unk_D8;
    if (unk_4F7EB8.unk_280 && sub_198800((type_3DF8D8_04 *)unk_4F7EB8.unk_280->sub_1B7910(b->nTeam)))
    {
        pTrigger->unk_D8 = *(type_3DF8D8_04 *)unk_4F7EB8.unk_280->sub_1B7910(b->nTeam);
        bTeamDef = TRUE;
    }
    v = m->pos;
    v.y += 40.0f;
    if (!GroundBelow(&v))
        v.y -= 40.0f;
    s_dwSpawnSide = (RwInt32)b->dwSide;
    pSoldier = SpawnSoldierAt((Trigger *)pTrigger, &v);
    s_dwSpawnSide = 0;
    pTrigger->unk_D8 = oldDef;
    if (pSoldier == NULL)
    {
        plog("bots: a team %d bot could not be made: %s", b->nTeam, s_szReqResult);
        return;
    }
    b->pSoldier = pSoldier;
    b->dwRespawnAt = 0;
    b->dwMadeAt = port_frame;
    __try
    {
        AIData *pAi = pSoldier->vf_120();

        if (pAi)
            pAi->sub_16D70(0x20);
        vAt.x = v.x + m->at.x * 100.0f;
        vAt.y = v.y;
        vAt.z = v.z + m->at.z * 100.0f;
        SpawnAiFace(pSoldier, &vAt);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    plog("bots: a team %d bot (side %u, %s, its definition %s) at (%.0f, %.0f, %.0f)", b->nTeam, b->dwSide,
         b->nTeam == unk_4F7EB8.unk_29C ? "the player's team" : "the other team", bTeamDef ? "its team's" : "the trigger's",
         v.x, v.y, v.z);
}

// Each frame: the bots made once the player is in (one each quarter second), and dead ones
// made again.
static void BotsTick()
{
    static RwInt32 s_nAllies = -1, s_nEnemies;
    static RwUInt32 s_dwIn, s_dwNext;
    RwInt32 i;

    if (s_nAllies < 0)
    {
        RwChar sz[32];

        s_nAllies = s_nEnemies = 0;
        if (GetEnvironmentVariableA("CODFH_BOTS", sz, sizeof(sz)))
        {
            RwChar *pComma = strchr(sz, ',');

            s_nAllies = atoi(sz);
            s_nEnemies = pComma ? atoi(pComma + 1) : s_nAllies;
            if (s_nAllies + s_nEnemies > BOTS_MAX)
            {
                s_nAllies = s_nAllies * BOTS_MAX / (s_nAllies + s_nEnemies);
                s_nEnemies = BOTS_MAX - s_nAllies;
            }
            plog("bots: %d on the player's team, %d on the other", s_nAllies, s_nEnemies);
        }
    }
    if (s_nAllies + s_nEnemies == 0)
        return;
    if (unk_4F7EB8.unk_1A4 == NULL)
    {
        if (s_nBots == 0)
            s_dwIn = 0;
        return;
    }
    if (!s_dwIn)
        s_dwIn = port_frame;
    // (after the path graph, PathsTick's, and the player's own placing)
    if (port_frame - s_dwIn < 90 || port_frame < s_dwNext)
        return;
    if (s_nBots == 0)
    {
        type_3D3548 *pPlayer = sub_1745A0(0);
        RwUInt32 dwMine = pPlayer ? (pPlayer->unk_2C & 7) : 1;
        RwInt32 nMine = unk_4F7EB8.unk_29C == 4 ? 4 : 2;

        plog("bots: the player is on team %d (side %u)", unk_4F7EB8.unk_29C, dwMine);
        // (the game type's spawn lists: whom each serves and how many points)
        {
            RwUInt32 k;

            plog("bots: %d spawn points, %u lists", unk_4FBC50.unk_00.unk_08, unk_4FBC50.unk_268);
            for (k = 0; k < unk_4FBC50.unk_268 && k < 10; k++)
                plog("bots:   list %u: serves %d, group %d, %d points", k, unk_4FBC50.unk_26C[k].unk_00,
                     unk_4FBC50.unk_26C[k].unk_04, unk_4FBC50.unk_26C[k].unk_08);
        }
        for (i = 0; i < s_nAllies + s_nEnemies; i++)
        {
            RwBool bAlly = i < s_nAllies;

            s_aBots[i].nTeam = bAlly ? nMine : (nMine == 4 ? 2 : 4);
            s_aBots[i].dwSide = bAlly ? dwMine : (dwMine == 2 ? 1 : 2);
            s_aBots[i].pSoldier = NULL;
            s_aBots[i].dwRespawnAt = port_frame + i * 15;
        }
        s_nBots = s_nAllies + s_nEnemies;
    }
    for (i = 0; i < s_nBots; i++)
    {
        TrigBot *b = &s_aBots[i];

        if (b->dwRespawnAt == 0 && !BotAlive(b->pSoldier))
        {
            b->dwRespawnAt = port_frame + 300;
            plog("bots: a team %d bot died %u frames after it was made; another in 5 s", b->nTeam, port_frame - b->dwMadeAt);
        }
        if (b->dwRespawnAt && port_frame >= b->dwRespawnAt)
        {
            BotSpawn(b);
            if (b->pSoldier == NULL)
                b->dwRespawnAt = port_frame + 300;
            s_dwNext = port_frame + 15;
            return;
        }
    }
}
#endif

static void SpawnAiTestTick()
{
    static RwInt32 s_nState = -1;
    static RwUInt32 s_dwAt, s_dwUntil;
    static type_3D3548 *s_pSoldier;
    static RwBool s_bTeleported;
    static RwBool s_bCombat;   // CODFH_SPAWNAI_COMBAT: in sight of the player, and left to itself
    type_10F710 *pPlayer;
    RwV3d v;
    RwInt32 i;

    if (s_nState < 0)
        s_nState = GetEnvironmentVariableA("CODFH_SPAWNAI", NULL, 0) ? 0 : 99;
    if (s_nState == 99)
        return;
    pPlayer = (type_10F710 *)sub_1745A0(0);
    if (pPlayer == NULL || !PlayerPosition(pPlayer, &v))
    {
        s_dwAt = port_frame + 120;
        return;
    }
    if (s_nState == 0)
    {
        if (port_frame < s_dwAt)
            return;
        // (CODFH_SPAWNAI_AT's "x y z": the player teleported there first, and the soldier spawned
        // a second later, 3 m in front of it; else a flat spot near the player)
        {
            RwChar szAt[64];
            RwV3d vAt;

            s_bCombat = GetEnvironmentVariableA("CODFH_SPAWNAI_COMBAT", NULL, 0) != 0;
            s_bFlatNeedsSight = s_bCombat;
            if (!s_bCombat && !s_bTeleported && GetEnvironmentVariableA("CODFH_SPAWNAI_AT", szAt, sizeof(szAt))
                && sscanf(szAt, "%f %f %f", &vAt.x, &vAt.y, &vAt.z) == 3)
            {
                // (exactly there: a place the player stood, its own height above the floor)
                Teleport(pPlayer, &vAt);
                plog("spawnai: the player teleported to (%.0f, %.0f, %.0f): %s", vAt.x, vAt.y, vAt.z, s_szReqResult);
                s_bTeleported = TRUE;
                s_dwAt = port_frame + 60;
                return;
            }
            if (s_bTeleported)
            {
                RwReal fLen = 0.0f;

                __try
                {
                    RwMatrix *pLtm = dword_4E5C74 ? RwFrameGetLTM(RwCameraGetFrame((RwCamera *)dword_4E5C74)) : NULL;

                    fLen = pLtm ? (RwReal)sqrt(pLtm->at.x * pLtm->at.x + pLtm->at.z * pLtm->at.z) : 0.0f;
                    if (fLen > 0.01f)
                    {
                        v.x += pLtm->at.x / fLen * 300.0f;
                        v.z += pLtm->at.z / fLen * 300.0f;
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
                // (from the player's waist down, so not onto a ledge or roof above it)
                v.y += 40.0f;
                if (!GroundBelow(&v))
                    v.y -= 40.0f;
                plog("spawnai: 3 m in front of the player: (%.0f, %.0f, %.0f)", v.x, v.y, v.z);
            }
            else if (s_bCombat && GetEnvironmentVariableA("CODFH_SPAWNAI_AT", szAt, sizeof(szAt))
                     && sscanf(szAt, "%f %f %f", &vAt.x, &vAt.y, &vAt.z) == 3)
            {
                // (the combat test with CODFH_SPAWNAI_AT: the soldier there, the player left where it is)
                v = vAt;
                v.y += 40.0f;
                if (!GroundBelow(&v))
                    v.y -= 40.0f;
                plog("spawnai: the soldier at CODFH_SPAWNAI_AT (%.0f, %.0f, %.0f)", v.x, v.y, v.z);
            }
            else
            {
                RwV3d vFlat = v;
                RwChar szDist[16];
                // (CODFH_SPAWNAI_DIST: that far in front of the player, in cm, no flat spot looked for)
                RwReal fDist = GetEnvironmentVariableA("CODFH_SPAWNAI_DIST", szDist, sizeof(szDist)) ? (RwReal)atof(szDist) : 0.0f;

                if (fDist <= 0.0f && FindFlatSpot(&vFlat))
                {
                    plog("spawnai: a flat spot at (%.0f, %.0f, %.0f)", vFlat.x, vFlat.y, vFlat.z);
                    v = vFlat;
                }
                else
                {
                    // (none: 4 m in front of the player, on the floor below its waist)
                    __try
                    {
                        RwMatrix *pLtm = dword_4E5C74 ? RwFrameGetLTM(RwCameraGetFrame((RwCamera *)dword_4E5C74)) : NULL;
                        RwReal fLen = pLtm ? (RwReal)sqrt(pLtm->at.x * pLtm->at.x + pLtm->at.z * pLtm->at.z) : 0.0f;

                        if (fLen > 0.01f)
                        {
                            v.x += pLtm->at.x / fLen * (fDist > 0.0f ? fDist : 400.0f);
                            v.z += pLtm->at.z / fLen * (fDist > 0.0f ? fDist : 400.0f);
                        }
                    }
                    __except (EXCEPTION_EXECUTE_HANDLER)
                    {
                    }
                    v.y += fDist > 0.0f ? 300.0f : 40.0f;
                    if (!GroundBelow(&v))
                        v.y -= fDist > 0.0f ? 300.0f : 40.0f;
                    plog("spawnai: no flat spot in sight (or CODFH_SPAWNAI_DIST); in front of the player (%.0f, %.0f, %.0f)", v.x, v.y, v.z);
                }
            }
        }
        SpawnAiDiagStart();
        SpawnSoldier(-1, &v);
        plog("spawnai: %s", s_szReqResult);
        s_pSoldier = NULL;
        for (i = 0; i < 768; i++)
        {
            type_3D3548 *pEntity = dword_4B6A00[i].unk_04;

            if (pEntity && (pEntity->unk_2C & 0x20) && pEntity != (type_3D3548 *)pPlayer && pEntity->vf_120())
                s_pSoldier = pEntity;
        }
        s_nState = s_pSoldier ? 1 : 99;
        // (turned about, CODFH_SPAWNAI_TURN, default 180 degrees: its facing set as the scripts'
        // teleports set it, vf_0D8 with the at vector)
        if (s_pSoldier)
        {
            __try
            {
                // (its frame as the scripts' teleports read an entity's, get_unk_340)
                RwFrame *pFrame = s_pSoldier->get_unk_340();
                RwChar szTurn[16];
                RwReal fTurn = GetEnvironmentVariableA("CODFH_SPAWNAI_TURN", szTurn, sizeof(szTurn)) ? (RwReal)atof(szTurn) : 180.0f;

                if (pFrame == NULL)
                    plog("spawnai: the soldier has no frame to turn");
                if (pFrame)
                {
                    RwMatrix *m = RwFrameGetMatrix(pFrame);
                    RwV3d at, *pv = s_pSoldier->sub_CD550();
                    RwReal fLen;

                    // (the combat test: facing the player; else turned by CODFH_SPAWNAI_TURN from its own
                    // facing. The frame itself turned, upright, and its facing told (vf_0D8): the setter
                    // alone does not turn the body)
                    RwV3d vMe;

                    // (the player's place now: v is the soldier's spot by here)
                    if (s_bCombat && pv && PlayerPosition(pPlayer, &vMe))
                    {
                        at.x = vMe.x - pv->x;
                        at.z = vMe.z - pv->z;
                        // (CODFH_SPAWNAI_AWAY=1: its back to the player, the hearing test)
                        if (GetEnvironmentVariableA("CODFH_SPAWNAI_AWAY", NULL, 0))
                        {
                            at.x = -at.x;
                            at.z = -at.z;
                        }
                    }
                    else
                    {
                        RwReal a = fTurn * 3.14159265f / 180.0f, c = (RwReal)cos(a), sn = (RwReal)sin(a);

                        at.x = m->at.x * c + m->at.z * sn;
                        at.z = -m->at.x * sn + m->at.z * c;
                    }
                    at.y = 0.0f;
                    fLen = (RwReal)sqrt(at.x * at.x + at.z * at.z);
                    if (fLen <= 0.01f)
                        plog("spawnai: no direction to face");
                    if (fLen > 0.01f)
                    {
                        RwV3d pos = m->pos;

                        at.x /= fLen;
                        at.z /= fLen;
                        m->at = at;
                        m->up.x = 0.0f;
                        m->up.y = 1.0f;
                        m->up.z = 0.0f;
                        RwV3dCrossProduct(&m->right, &m->up, &m->at);
                        m->pos = pos;
                        RwMatrixUpdate(m);
                        RwFrameUpdateObjects(pFrame);
                        s_pSoldier->vf_0D8(&at);
                        plog("spawnai: facing (%.2f, %.2f)%s", at.x, at.z, s_bCombat ? " (the player)" : "");
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                plog("spawnai: turning it faulted");
            }
        }
        // (its looking on, as "SetAIFlag" sets it (sub_16D70): the Vision Scheduler skips an AI without
        // flag 0x20, which single player's soldiers get from their level's task scripts; plus
        // CODFH_SPAWNAI_FLAGS, hex)
        if (s_pSoldier && s_pSoldier->vf_120())
        {
            __try
            {
                AIData *pAi = s_pSoldier->vf_120();
                RwUInt32 dwBefore = pAi->unk_49C, dwAdd = 0x20;
                RwChar szFlags[16];

                if (GetEnvironmentVariableA("CODFH_SPAWNAI_FLAGS", szFlags, sizeof(szFlags)))
                    dwAdd |= strtoul(szFlags, NULL, 16);
                pAi->sub_16D70(dwAdd);
                plog("spawnai: its AI flags %08X, now %08X; its entity flags (unk_28) %08X", dwBefore, pAi->unk_49C,
                     s_pSoldier->unk_28);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                plog("spawnai: setting its AI flags faulted");
            }
        }
        // (the Vision Scheduler's view: the kind lists dword_4B8600[n] holding the player and the
        // soldier (a soldier looks at list 14, and 9 and 0 with side bit 0, 10 and 1 with side bit
        // 1, sub_40FB0), whether each has an AI object, and the soldier's looking flag)
        {
            RwChar szLists[256];
            RwInt32 k, n = 0;

            szLists[0] = 0;
            __try
            {
                for (k = 0; k < 16; k++)
                {
                    type_3D3548 *e;
                    RwInt32 nIn = 0, nCount = 0;

                    for (e = dword_4B8600[k].unk_00; e && nCount < 1000; e = e->unk_10, nCount++)
                    {
                        if (e == (type_3D3548 *)pPlayer)
                            nIn |= 1;
                        if (e == s_pSoldier)
                            nIn |= 2;
                    }
                    if (nCount || nIn)
                        n += _snprintf(szLists + n, sizeof(szLists) - n, " %d:%d%s%s", k, nCount, (nIn & 1) ? "P" : "",
                                       (nIn & 2) ? "S" : "");
                }
                plog("spawnai: kind lists (P the player, S the soldier):%s; the player's AI object %p, the soldier's looking flag %d",
                     szLists, ((type_3D3548 *)pPlayer)->vf_120(),
                     s_pSoldier && s_pSoldier->vf_120() ? (s_pSoldier->vf_120()->unk_49C >> 5) & 1 : -1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                plog("spawnai: reading the kind lists faulted");
            }
        }
        // (the collision proxies the bullets test, unk_274's atomic in a section's collision
        // world: the player's and the soldier's)
        {
            type_3D3548 *apWho[2];
            RwInt32 w;

            apWho[0] = (type_3D3548 *)pPlayer;
            apWho[1] = s_pSoldier;
            for (w = 0; w < 2; w++)
            {
                __try
                {
                    RpAtomic *pAtomic = apWho[w] ? apWho[w]->unk_274.unk_08 : NULL;

                    if (pAtomic == NULL)
                        plog("spawnai: the %s has no collision proxy", w ? "soldier" : "player");
                    else
                        plog("spawnai: the %s's collision proxy %p: flags 0x%X (collision test %d), in world %p, ext flags 0x%X",
                             w ? "soldier" : "player", pAtomic, RpAtomicGetFlags(pAtomic),
                             (RpAtomicGetFlags(pAtomic) & rpATOMICCOLLISIONTEST) != 0, RpAtomicGetWorld(pAtomic),
                             sub_FB7A0(pAtomic)->unk_04.unk_00);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                    plog("spawnai: reading the %s's collision proxy faulted", w ? "soldier" : "player");
                }
            }
        }
        if (s_pSoldier)
        {
            __try
            {
                type_3DAFC8 *pSol = (type_3DAFC8 *)s_pSoldier;

                plog("spawnai: its weapon slot %d%s", pSol->unk_3E0.unk_04, s_bCombat ? "; combat test: left to itself" : "");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
            }
        }
        s_dwAt = port_frame;
        s_dwUntil = port_frame + 3600;
        return;
    }
    // (the combat test, CODFH_SPAWNAI_FACE=1: the soldier turned to face the player every frame
    // (vf_0D8), as its own turning would)
    if (s_bCombat && s_pSoldier && s_nState >= 1 && s_nState != 99 && GetEnvironmentVariableA("CODFH_SPAWNAI_FACE", NULL, 0))
    {
        __try
        {
            RwV3d *pv = s_pSoldier->sub_CD550(), at;

            if (pv)
            {
                RwReal fLen;

                at.x = v.x - pv->x;
                at.y = 0.0f;
                at.z = v.z - pv->z;
                fLen = (RwReal)sqrt(at.x * at.x + at.z * at.z);
                if (fLen > 1.0f)
                {
                    at.x /= fLen;
                    at.z /= fLen;
                    s_pSoldier->vf_0D8(&at);
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
    {
        static RwUInt32 s_dwBring;

        if (s_bSpawnAiBringNear && s_pSoldier && s_nState >= 1 && s_nState != 99)
        {
            if (!s_dwBring)
                s_dwBring = port_frame + 30;
            else if (port_frame >= s_dwBring)
            {
                s_bSpawnAiBringNear = FALSE;
                s_dwBring = 0;
                SpawnAiBringNear(s_pSoldier, pPlayer);
            }
        }
    }
    if (port_frame - s_dwAt < 60)
        return;
    s_dwAt = port_frame;
    __try
    {
        RwV3d *pv = s_pSoldier->sub_CD550();

        for (i = 0; i < 768; i++)
            if (dword_4B6A00[i].unk_04 == s_pSoldier)
                break;
        if (i == 768)
        {
            plog("spawnai: the soldier is gone");
            s_nState = 99;
            return;
        }
        {
            AIData *pAi = s_pSoldier->vf_120();

            plog("spawnai: soldier at (%.0f, %.0f, %.0f), hit points %d, kind 0x%X; AI state %d, control %d, "
                 "maneuver %d, alerted %d, target %p; player at (%.0f, %.0f, %.0f)",
                 pv ? pv->x : 0.0f, pv ? pv->y : 0.0f, pv ? pv->z : 0.0f, s_pSoldier->vf_174(), s_pSoldier->unk_2C,
                 pAi ? pAi->unk_578 : -1, pAi ? pAi->unk_51C : -1, pAi ? pAi->unk_58 : -1, pAi ? pAi->unk_520 : -1,
                 pAi ? (void *)pAi->unk_568 : NULL, v.x, v.y, v.z);
            // (its facing: its frame's at, and toward the player)
            {
                RwFrame *pFrame = s_pSoldier->get_unk_340();

                if (pFrame && pv)
                {
                    RwMatrix *m = RwFrameGetMatrix(pFrame);
                    RwReal dx = v.x - pv->x, dz = v.z - pv->z, d = (RwReal)sqrt(dx * dx + dz * dz);

                    plog("spawnai:   facing (%.2f, %.2f); the player is toward (%.2f, %.2f)", m->at.x, m->at.z,
                         d > 0.0f ? dx / d : 0.0f, d > 0.0f ? dz / d : 0.0f);
                    // (the turn's aim, as SetTurnMode reads it: the turn location unk_500 under flag 30,
                    // else the target point unk_4F0; the animation's turn, GetTurnAmount's)
                    if (pAi)
                        plog("spawnai:   turn: flag30 %d, location (%.0f, %.0f, %.0f), target point %s (%.0f, %.0f, %.0f), "
                             "animation turn %.1f deg",
                             (pAi->unk_49C >> 30) & 1, pAi->unk_500.x, pAi->unk_500.y, pAi->unk_500.z,
                             pAi->unk_4F0 ? "set" : "none", pAi->unk_4F0 ? pAi->unk_4F0->x : 0.0f,
                             pAi->unk_4F0 ? pAi->unk_4F0->y : 0.0f, pAi->unk_4F0 ? pAi->unk_4F0->z : 0.0f,
                             s_pSoldier->unk_284 ? (RwReal)atan2(s_pSoldier->unk_284->unk_1A0, s_pSoldier->unk_284->unk_1A8) * 2.0f * 57.29578f : -1.0f);
                }
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        plog("spawnai: reading the soldier faulted");
        s_nState = 99;
    }
    // (CODFH_SPAWNAI's messages to it: "ReturnToAIControl" at the second look, then
    // "SetAttitude" with CODFH_SPAWNAI_ATT's value (default 2) at the third; the kinds' argument
    // counts logged)
    if (!s_bCombat && (s_nState == 2 || s_nState == 3))
    {
        __try
        {
            type_3D2E7C *pObject = s_pSoldier->vf_098();
            const RwChar *pszMsg = s_nState == 2 ? "ReturnToAIControl" : "SetAttitude";
            type_42E00_00 *pKind = sub_6A7F0(pszMsg);
            RwInt32 anArgs[8], nArgs = pKind ? pKind->unk_10 : -1;
            RwChar szAtt[16];

            memset(anArgs, 0, sizeof(anArgs));
            if (s_nState == 3)
                anArgs[0] = GetEnvironmentVariableA("CODFH_SPAWNAI_ATT", szAtt, sizeof(szAtt)) ? atoi(szAtt) : 2;
            if (pObject && pKind && nArgs >= 0 && nArgs <= 8)
            {
                sub_6B5F0(pszMsg, (type_67620 *)pObject, 0, 0, anArgs, nArgs, true, false);
                plog("spawnai: sent %s (%d arguments, the first %d) to its object", pszMsg, nArgs, anArgs[0]);
            }
            else
                plog("spawnai: not sent %s (kind %p, %d arguments)", pszMsg, pKind, nArgs);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            plog("spawnai: sending faulted");
        }
    }
    // (a task at the fourth look, as the levels' scripts give soldiers theirs:
    // "SetTaskCommand_GoToPoint" (x, y, z, 0) to its object, the player's place, which its
    // class takes (SetupGotoPoint); CODFH_SPAWNAI_TASK names another message of no arguments)
    if (!s_bCombat && s_nState == 4)
    {
        __try
        {
            type_3D2E7C *pObject = s_pSoldier->vf_098();
            RwChar szTask[64];

            if (GetEnvironmentVariableA("CODFH_SPAWNAI_TASK", szTask, sizeof(szTask)))
            {
                RwInt32 nZero = 0;

                sub_6B5F0(szTask, (type_67620 *)pObject, 0, 0, &nZero, 0, true, false);
                plog("spawnai: sent %s", szTask);
            }
            else
            {
                RwReal af[4];

                af[0] = v.x;
                af[1] = v.y;
                af[2] = v.z;
                af[3] = 0.0f;
                sub_6B5F0("SetTaskCommand_GoToPoint", (type_67620 *)pObject, 0, 0, (RwInt32 *)af, 4, true, false);
                plog("spawnai: sent SetTaskCommand_GoToPoint (%.0f, %.0f, %.0f)", v.x, v.y, v.z);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            plog("spawnai: sending the task faulted");
        }
    }
    // (its animation: the player its unk_280 names (sub_78AC0), its ring of records, unk_284,
    // and the animation pools' room)
    __try
    {
        type_78AC0 *pAnim = sub_78AC0(s_pSoldier->unk_280);
        RwChar szRing[160];
        RwInt32 k, n = 0;

        szRing[0] = 0;
        if (pAnim)
            for (k = 0; k < pAnim->unk_24 && k < 12; k++)
            {
                const type_78AC0_34 *r = &pAnim->unk_34[(pAnim->unk_20 + k) % 12];

                n += _snprintf(szRing + n, sizeof(szRing) - n, " %08X/%08X", (RwUInt32)r->unk_00, r->unk_08);
                if (n < 0 || n >= (RwInt32)sizeof(szRing) - 20)
                    break;
            }
        if (s_pSoldier->vf_120())
            plog("spawnai:   flags: AI %08X, entity %08X", s_pSoldier->vf_120()->unk_49C, s_pSoldier->unk_28);
        // (the player's health and what the bullets' hit (type_10F710::vf_064) checks: unk_19FC (no
        // hits at all), unk_19EC (none while positive), unk_19DC the health, unk_19E0 its scale)
        __try
        {
            plog("spawnai:   the player: health %.2f, hit points %d, unk_19FC %d, unk_19EC %.2f, god %d",
                 pPlayer->unk_19DC, pPlayer->unk_19E0, pPlayer->unk_19FC, pPlayer->unk_19EC, (RwInt32)byte_4F28F8);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        // (hearing: the noises made and heard so far, the last one's kind, class and range; the
        // sound flag (dword_4B86F8 bit 4: none made); whether it listens, and for what)
        __try
        {
            AIData *pAi = s_pSoldier->vf_120();
            type_3C720 *pL;
            RwInt32 nListeners = 0, bListens = 0;

            for (pL = dword_43925C; pL && nListeners < 1000; pL = pL->unk_08)
            {
                nListeners++;
                if (pL->unk_00 == s_pSoldier)
                    bListens = 1;
            }
            plog("spawnai:   hearing: %d noises made, %d heard; last kind %d class %d range %.0f; sounds off %d; "
                 "%d listeners (it %s); it hears classes 0x%X kinds 0x%X sides 0x%X, radius %.0f",
                 g_nTrigNoisesMade, g_nTrigNoisesHeard, g_nTrigLastNoiseKind, g_nTrigLastNoiseClass,
                 g_fTrigLastNoiseRange, (dword_4B86F8 >> 4) & 1, nListeners, bListens ? "one" : "not",
                 pAi ? pAi->unk_538 : -1, pAi ? pAi->unk_53C : -1, pAi ? pAi->unk_540 : -1, s_pSoldier->vf_130());
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            plog("spawnai:   reading the hearing state faulted");
        }
        {
            static RwInt32 s_nLooks;

            // (the fourth look: a noise at the player, as a gunshot's alias makes one: kind 1, class 2)
            if (++s_nLooks == 4 && GetEnvironmentVariableA("CODFH_SPAWNAI_NOISE", NULL, 0))
            {
                RwV3d vMe;

                if (PlayerPosition(pPlayer, &vMe))
                {
                    plog("spawnai:   a test noise at the player (%.0f, %.0f, %.0f)", vMe.x, vMe.y, vMe.z);
                    sub_3C4B0((type_3D3548 *)pPlayer, 1, &vMe, 2, 3000.0f, 0, 0.0f);
                }
            }
        }
        // (its weapon's aim: firing at its target (unk_A0), a point given (unk_CC, unk_D0), and its AI's target)
        __try
        {
            type_3DAFC8 *pSol = (type_3DAFC8 *)s_pSoldier;
            AIData *pAi = s_pSoldier->vf_120();

            plog("spawnai:   weapon: at target %d, point given %d (%.0f, %.0f, %.0f); AI target %p", pSol->unk_3E0.unk_A0,
                 pSol->unk_3E0.unk_CC, pSol->unk_3E0.unk_D0.x, pSol->unk_3E0.unk_D0.y, pSol->unk_3E0.unk_D0.z,
                 pAi ? (void *)pAi->get_unk_1374() : NULL);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        // (where it would shoot the player: the target's vf_110, as "SetAdvancedShotLocation" asks)
        {
            RwV3d vAim;

            ((type_3D3548 *)pPlayer)->vf_110(&vAim, s_pSoldier, 0);
            plog("spawnai:   the player's shot point (vf_110) (%.0f, %.0f, %.0f); the player at (%.0f, %.0f, %.0f)", vAim.x,
                 vAim.y, vAim.z, v.x, v.y, v.z);
        }
        plog("spawnai:   anim: handle %d, player %p (%d records:%s), unk_284 %p; pools free %d, %d, %d", s_pSoldier->unk_280,
             pAnim, pAnim ? pAnim->unk_24 : -1, szRing, s_pSoldier->unk_284, get_pool(0).m_pool.unk_18,
             get_pool(1).m_pool.unk_18, get_pool(2).m_pool.unk_18);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        plog("spawnai:   anim: reading it faulted");
    }
    // (its traffic since the last look)
    __try
    {
        type_3D2E7C *pObject = s_pSoldier->vf_098();

        if (pObject)
            SpawnAiDiagLog(pObject->get_unk_04());
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    // (its scripts, the first five times)
    if (s_nState >= 1 && s_nState < 6)
    {
        __try
        {
            type_3D2E7C *pObject = s_pSoldier->vf_098();

            if (pObject)
                SpawnAiLogScripts(pObject->get_unk_04());
            else
                plog("spawnai: the soldier has no script object");
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
        if (s_nState < 6)
            s_nState++;
    }
    if (port_frame > s_dwUntil)
        s_nState = 99;
}

// ---- Waits: what each script is waiting for ----
//
// Nothing polls the scripts: the VM runs one (sub_68310) only when something hands it work,
// a message delivered (alfamessman), a timer firing (alfatimer, sub_73650: its messages), an
// animation ending (a performance's, sub_6DF90), a task woken (opcode 41), returned to or
// spawned. So a script that is not running is waiting for one of those, and this lists which:
// the timers by time left, each task's wait (the messages of its call records, any or all of
// them; a wake; the task it called), each performance's animation or pending switch, each state
// machine's state and the messages it listens for, and the messages queued for delivery.

// A message kind's name (the loaded script image's table, dword_4492F4), or its number.
static void WaitMsgName(RwInt32 nKind, RwChar *psz, RwInt32 nMax)
{
    type_42E00_00 *pKind = NULL;

    __try
    {
        if (nKind >= 0 && nKind < dword_4492F8 && dword_4492F4)
            pKind = &dword_4492F4[nKind];
        if (pKind == NULL)
            pKind = sub_6A7D0(nKind);
        if (pKind && pKind->unk_00)
        {
            ReadText(pKind->unk_00, psz, nMax - 1);
            psz[nMax - 1] = 0;
            if (psz[0])
                return;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    _snprintf(psz, nMax, "message %d", nKind);
    psz[nMax - 1] = 0;
}

// Appends "name" (comma-separated) to psz.
static void WaitAppend(RwChar *psz, RwInt32 nMax, const RwChar *pszAdd)
{
    size_t n = strlen(psz);

    if (n + 3 >= (size_t)nMax)
        return;
    if (n)
    {
        strcat(psz, ", ");
        n += 2;
    }
    strncat(psz, pszAdd, nMax - n - 1);
}

// The messages of the registration list starting at r, the next by nNextKind (0: unk_0C, a
// state machine's handlers; 1: unk_08_s, a call record's), into psz; how many.
static RwInt32 WaitRegistrations(type_6B960 *r, RwInt32 nNextKind, RwChar *psz, RwInt32 nMax)
{
    RwInt32 n = 0;
    RwChar szMsg[64];

    psz[0] = 0;
    __try
    {
        while (r != NULL && n < 32)
        {
            WaitMsgName(r->unk_14, szMsg, sizeof(szMsg));
            WaitAppend(psz, nMax, szMsg);
            n++;
            r = get_registration(nNextKind == 0 ? r->unk_0C : r->unk_08_s);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    return n;
}

// The timers of the object with the handle dwHandle: "X in 2.4 s" each, into psz; how many.
static RwInt32 WaitTimers(RwUInt32 dwHandle, RwInt32 nGeneration, RwChar *psz, RwInt32 nMax)
{
    RwInt32 n = 0;
    RwChar szMsg[64], sz[96];

    psz[0] = 0;
    __try
    {
        type_73360 *t;

        for (t = dword_449B44; t != NULL && n < 64; t = t->unk_14)
        {
            if (t->unk_00 != dwHandle)
                continue;
            WaitMsgName(t->unk_04, szMsg, sizeof(szMsg));
            _snprintf(sz, sizeof(sz), "%s in %.1f s%s", szMsg, (t->unk_10 - dword_449B40) / 60.0f,
                      t->unk_0C != nGeneration ? " (stale: will not fire)" : "");
            sz[sizeof(sz) - 1] = 0;
            WaitAppend(psz, nMax, sz);
            n++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    return n;
}

// The messages queued for delivery (the action queue dword_439904's message actions, kind
// 0x10), for the object with the handle dwTarget (0: every queued message), into psz.
static RwInt32 WaitQueued(RwUInt32 dwTarget, RwBool bAll, RwChar *psz, RwInt32 nMax)
{
    RwInt32 n = 0, nGuard = 0;
    RwChar szMsg[64];

    psz[0] = 0;
    __try
    {
        type_42AF0 *a;

        for (a = dword_439904; a != NULL && nGuard < 2000; a = a->unk_0C, nGuard++)
        {
            type_42E00 *pMsg;
            RwUInt32 dwTo;

            if (a->unk_00 != 0x10)
                continue;
            pMsg = (type_42E00 *)sub_67620(a->unk_08);
            if (pMsg == NULL)
                continue;
            dwTo = pMsg->unk_04;
            if (!bAll && dwTo != dwTarget && dwTo != 0)
                continue;
            if (pMsg->unk_00 && pMsg->unk_00->unk_00)
                ReadText(pMsg->unk_00->unk_00, szMsg, sizeof(szMsg) - 1);
            else
                strcpy(szMsg, "?");
            szMsg[sizeof(szMsg) - 1] = 0;
            if (dwTo == 0 && !bAll)
                strncat(szMsg, " (to all)", sizeof(szMsg) - strlen(szMsg) - 1);
            WaitAppend(psz, nMax, szMsg);
            n++;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    return n;
}

// (CODFH_SPAWNAI: the state machines of the object dwObject, each its name, state, the
// messages it listens for and its timers, logged)
static void SpawnAiLogScripts(RwUInt32 dwObject)
{
    RwUInt32 dwBase;
    RwInt32 nStride, nCount, i, n = 0;
    RwChar szName[96], szMsgs[1200], szTimers[256];

    if (!PoolFree(&dword_449A30, &dwBase, &nStride, &nCount))
        return;
    for (i = 0; i < nCount; i++)
    {
        type_3D2DB8 *m = (type_3D2DB8 *)(dwBase + i * nStride);
        RwInt32 nState = -1;

        if (s_abFree[i])
            continue;
        __try
        {
            if (m->unk_7C != dwObject)
                continue;
            nState = m->unk_90;
            WaitRegistrations(m->unk_9C, 0, szMsgs, sizeof(szMsgs));
            WaitTimers(((type_67620 *)m)->unk_04, m->unk_70, szTimers, sizeof(szTimers));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            continue;
        }
        ScriptName((type_67620 *)m, szName, sizeof(szName));
        plog("spawnai:   script %s: state %d%s%s", szName, nState, szTimers[0] ? "; timers " : "", szTimers);
        plog("spawnai:     listens for %s", szMsgs[0] ? szMsgs : "nothing");
        n++;
    }
    if (n == 0)
        plog("spawnai:   no state machine belongs to its object %08X", dwObject);
}

static void WaitRowStart(RwUInt32 dwObj, const RwChar *pszName, const RwChar *pszKind)
{
    RwChar szObj[16];

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    sprintf(szObj, "0x%08X", dwObj);
    if (ImGui::Selectable(szObj, dwObj == s_dwSelScript, ImGuiSelectableFlags_SpanAllColumns))
    {
        s_dwSelScript = dwObj == s_dwSelScript ? 0 : dwObj;
        s_bSelMachine = strcmp(pszKind, "machine") == 0;
    }
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(pszName);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(pszKind);
}

static void TabWaits()
{
    static RwBool s_bOnlyWaiting = TRUE;
    static RwBool s_bMachines = FALSE;
    RwUInt32 dwBase, dwRunning = 0;
    RwInt32 nStride, nCount, i, nShown = 0;
    RwChar szName[96], szWhat[512], szTimers[256], szQueued[256];

    ReadU32(&dword_449328, &dwRunning);
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(nothing polls the scripts: one runs only when a message is delivered, one of its timers "
                        "fires, its animation ends or it is woken, returned to or spawned. So this lists what each one "
                        "waits for. The script timers' clock is %.1f s; a timer whose script restarted since is stale "
                        "and will not fire)", dword_449B40 / 60.0f);
    ImGui::PopTextWrapPos();
    Check("only scripts waiting on something", &s_bOnlyWaiting);
    ImGui::SameLine();
    Check("state machines too", &s_bMachines);
    {
        RwInt32 nQueued = WaitQueued(0, TRUE, szQueued, sizeof(szQueued));

        if (nQueued)
            ImGui::TextWrapped("%d messages queued for delivery: %s", nQueued, szQueued);
        else
            ImGui::TextDisabled("no messages queued for delivery");
    }
    if (!ImGui::BeginTable("waits", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY |
                                       ImGuiTableFlags_Resizable, ImVec2(0.0f, 380.0f)))
        return;
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableSetupColumn("object", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("name", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("kind", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("waits for");
    ImGui::TableSetupColumn("its timers");
    ImGui::TableHeadersRow();

    // (tasks: the waits of their call records)
    if (PoolFree(&dword_4499F0, &dwBase, &nStride, &nCount))
        for (i = 0; i < nCount && nShown < 400; i++)
        {
            type_3D2E20 *t = (type_3D2E20 *)(dwBase + i * nStride);
            RwBool bWaiting = FALSE;

            if (s_abFree[i])
                continue;
            szWhat[0] = 0;
            __try
            {
                RwChar szMsgs[256];
                type_3D2E20_118 *rec;
                RwInt32 nRec = 0;

                if ((RwUInt32)t == dwRunning)
                    strcpy(szWhat, "running now");
                else if (t->unk_110 == -1)
                    strcpy(szWhat, "not started");
                else if (t->unk_10C)
                {
                    bWaiting = TRUE;
                    if (t->unk_10D == 0)
                        strcpy(szWhat, "a wake (opcode 41)");
                    for (rec = t->unk_118; rec != NULL && nRec < 16; rec = rec->unk_04, nRec++)
                    {
                        RwChar szRec[300];
                        RwInt32 nMsgs = WaitRegistrations(rec->unk_00, 1, szMsgs, sizeof(szMsgs));

                        if (nMsgs == 0)
                            continue;
                        if (rec->unk_14_1 == 2)
                            _snprintf(szRec, sizeof(szRec), "interrupt on %s", szMsgs);
                        else if (nMsgs == 1)
                            _snprintf(szRec, sizeof(szRec), "%s", szMsgs);
                        else
                            _snprintf(szRec, sizeof(szRec), "%s of %s", rec->unk_14_0 ? "any" : "all", szMsgs);
                        szRec[sizeof(szRec) - 1] = 0;
                        WaitAppend(szWhat, sizeof(szWhat), szRec);
                    }
                    if (szWhat[0] == 0)
                        strcpy(szWhat, "a message (no call record)");
                }
                else if (t->unk_FC.unk_00)
                {
                    bWaiting = TRUE;
                    _snprintf(szWhat, sizeof(szWhat), "the task it called (0x%08X) to return", t->unk_FC.unk_00);
                }
                else
                    strcpy(szWhat, "-");
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                continue;
            }
            ScriptName((type_67620 *)t, szName, sizeof(szName));
            if (s_szScriptFilter[0] && !ReportHas(szName, s_szScriptFilter))
                continue;
            WaitTimers(((type_67620 *)t)->unk_04, t->unk_110, szTimers, sizeof(szTimers));
            if (s_bOnlyWaiting && !bWaiting && szTimers[0] == 0)
                continue;
            WaitRowStart((RwUInt32)t, szName, "task");
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", szWhat);
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", szTimers);
            nShown++;
        }

    // (performances: an animation playing, a switch pending, finished)
    if (PoolFree(&dword_449A50, &dwBase, &nStride, &nCount))
        for (i = 0; i < nCount && nShown < 400; i++)
        {
            type_3D2CD0 *p = (type_3D2CD0 *)(dwBase + i * nStride);
            RwBool bWaiting = FALSE;

            if (s_abFree[i])
                continue;
            szWhat[0] = 0;
            __try
            {
                RwInt32 *pCode = ((type_3D2C30 *)p)->unk_68;

                if ((RwUInt32)p == dwRunning)
                    strcpy(szWhat, "running now");
                else if (p->unk_128)
                    strcpy(szWhat, "nothing: finished");
                else if (pCode && (*pCode & 0xFF) == 22)
                {
                    RwInt32 *pStack = ((type_3D2C30 *)p)->unk_6C;

                    bWaiting = TRUE;
                    _snprintf(szWhat, sizeof(szWhat), "its animation (0x%08X) to end, %d plays left",
                              (RwUInt32)pCode[1], pStack ? pStack[-1] : 0);
                }
                else
                    _snprintf(szWhat, sizeof(szWhat), "an event (performance %d)", p->unk_120);
                if (p->unk_148 != -1 && !p->unk_128)
                {
                    RwChar sz[96];

                    bWaiting = TRUE;
                    _snprintf(sz, sizeof(sz), "then performance %d%s", p->unk_148,
                              (p->unk_14C & 0x80) ? " after the animation" : (p->unk_14C & 0x10) ? " after the transition"
                                                                                                : " next tick");
                    sz[sizeof(sz) - 1] = 0;
                    WaitAppend(szWhat, sizeof(szWhat), sz);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                continue;
            }
            ScriptName((type_67620 *)p, szName, sizeof(szName));
            if (s_szScriptFilter[0] && !ReportHas(szName, s_szScriptFilter))
                continue;
            WaitTimers(((type_67620 *)p)->unk_04, ((type_67620 *)p)->vf_028(), szTimers, sizeof(szTimers));
            if (s_bOnlyWaiting && !bWaiting && szTimers[0] == 0)
                continue;
            WaitRowStart((RwUInt32)p, szName, "performance");
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", szWhat);
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", szTimers);
            nShown++;
        }

    // (state machines: idle in a state, listening for its messages; shown with their timers,
    // or all of them with "state machines too")
    if (PoolFree(&dword_449A30, &dwBase, &nStride, &nCount))
        for (i = 0; i < nCount && nShown < 400; i++)
        {
            type_3D2DB8 *m = (type_3D2DB8 *)(dwBase + i * nStride);
            RwChar szMsgs[400];
            RwInt32 nMsgs = 0;

            if (s_abFree[i])
                continue;
            __try
            {
                nMsgs = WaitRegistrations(m->unk_9C, 0, szMsgs, sizeof(szMsgs));
                if ((RwUInt32)m == dwRunning)
                    strcpy(szWhat, "running now");
                else if (nMsgs)
                    _snprintf(szWhat, sizeof(szWhat), "state %d: %s", m->unk_90, szMsgs);
                else
                    _snprintf(szWhat, sizeof(szWhat), "state %d: no messages", m->unk_90);
                szWhat[sizeof(szWhat) - 1] = 0;
                if (m->unk_92 != -1)
                {
                    RwChar sz[48];

                    _snprintf(sz, sizeof(sz), "(going to state %d)", m->unk_92);
                    WaitAppend(szWhat, sizeof(szWhat), sz);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                continue;
            }
            ScriptName((type_67620 *)m, szName, sizeof(szName));
            if (s_szScriptFilter[0] && !ReportHas(szName, s_szScriptFilter))
                continue;
            WaitTimers(((type_67620 *)m)->unk_04, m->unk_70, szTimers, sizeof(szTimers));
            if (!s_bMachines && szTimers[0] == 0)
                continue;
            WaitRowStart((RwUInt32)m, szName, "machine");
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", szWhat);
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", szTimers);
            nShown++;
        }
    ImGui::EndTable();
    ImGui::TextDisabled("%d shown (up to 400); the name filter above applies", nShown);
}

// ---- Messages: who sends what, and sending one ----
//
// Every script message is made by sub_6B710 (alfamessman): the scripts' action opcode (45,
// sub_6A4F0), the engine's sends by name (sub_6B5F0) and by index (sub_6B680). TrigMsgSent,
// from its end, notes each one while recording: its kind, its target (0 for all), its sender
// and other object, the script running then, its first arguments and the code that sent it.

extern "C" void plog(const char *fmt, ...);

#define TRIGMSG_LOG 512
#define TRIGMSG_KINDS 512
#define TRIGMSG_WHO 6
struct TrigMsgRec
{
    RwUInt32 dwFrame;
    const type_42E00_00 *pKind;
    RwChar szKind[40];
    RwChar szTo[48], szFrom[48], szScript[48];
    RwUInt32 dwTo, dwFrom, dwScriptObject;  // the handles: its target, its sender, the running script's object
    RwInt32 nArgs;
    RwInt32 anArgs[4];
    void *apCaller[6];
    RwInt32 nCallers;
};
struct TrigMsgKind
{
    const type_42E00_00 *pKind;
    RwChar szKind[40];
    RwUInt32 nCount, dwLastFrame;
    RwChar aszFrom[TRIGMSG_WHO][48];
    RwInt32 nFrom;
    RwChar aszTo[TRIGMSG_WHO][48];
    RwInt32 nTo;
    void *apCode[TRIGMSG_WHO];      // the code that sent it (the first caller past the senders)
    RwInt32 nCode;
};
static TrigMsgRec s_aMsgLog[TRIGMSG_LOG];
static RwUInt32 s_nMsgLog;
static TrigMsgKind s_aMsgKinds[TRIGMSG_KINDS];
static RwInt32 s_nMsgKinds;
static RwBool s_bMsgRecord;
static CRITICAL_SECTION s_csMsg;
static LONG s_nMsgInit;

static void MsgLock()
{
    if (InterlockedCompareExchange(&s_nMsgInit, 1, 0) == 0)
    {
        InitializeCriticalSection(&s_csMsg);
        s_nMsgInit = 2;
    }
    while (s_nMsgInit != 2)
        Sleep(0);
    EnterCriticalSection(&s_csMsg);
}

// An object's name by its handle (a script, an entity's object, a trigger), or "-".
static void MsgWho(RwUInt32 dwHandle, RwChar *psz, RwInt32 nMax)
{
    type_67620 *p = NULL;

    if (dwHandle == 0)
    {
        _snprintf(psz, nMax, "-");
        psz[nMax - 1] = 0;
        return;
    }
    __try
    {
        p = sub_67620(dwHandle);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        p = NULL;
    }
    if (p)
        ScriptName(p, psz, nMax);
    else
        _snprintf(psz, nMax, "0x%08X (gone)", dwHandle);
    psz[nMax - 1] = 0;
}

static void MsgAddWho(RwChar (*a)[48], RwInt32 *pn, const RwChar *psz)
{
    RwInt32 i;

    for (i = 0; i < *pn; i++)
        if (strcmp(a[i], psz) == 0)
            return;
    if (*pn >= TRIGMSG_WHO)
        return;
    strncpy(a[*pn], psz, 47);
    a[*pn][47] = 0;
    (*pn)++;
}

// A code address's function and offset (the port's symbols: the sub_XXXXX names give the
// image's address).
static void MsgCodeName(void *p, RwChar *psz, RwInt32 nMax)
{
    static RwBool s_bSym;
    RwChar buf[sizeof(SYMBOL_INFO) + 128];
    SYMBOL_INFO *sym = (SYMBOL_INFO *)buf;
    DWORD64 disp = 0;

    if (!s_bSym)
    {
        SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
        SymInitialize(GetCurrentProcess(), NULL, TRUE);
        s_bSym = TRUE;
    }
    memset(buf, 0, sizeof(buf));
    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = 127;
    if (SymFromAddr(GetCurrentProcess(), (DWORD64)(size_t)p, &disp, sym))
        _snprintf(psz, nMax, "%s+0x%X", sym->Name, (RwUInt32)disp);
    else
        _snprintf(psz, nMax, "%p", p);
    psz[nMax - 1] = 0;
}

// The first caller that is not one of the senders themselves (sub_6B5F0, sub_6B680, the
// action opcode sub_6A4F0): the code that decided to send it. Its name into psz.
static void MsgSenderCode(void *const *apCaller, RwInt32 nCallers, RwChar *psz, RwInt32 nMax, void **ppOut)
{
    RwInt32 i;

    psz[0] = 0;
    if (ppOut)
        *ppOut = NULL;
    for (i = 0; i < nCallers; i++)
    {
        MsgCodeName(apCaller[i], psz, nMax);
        if (strncmp(psz, "sub_6B5F0", 9) != 0 && strncmp(psz, "sub_6B680", 9) != 0)
        {
            if (strncmp(psz, "sub_6A4F0", 9) == 0)
                _snprintf(psz, nMax, "the script's action opcode (45)");
            psz[nMax - 1] = 0;
            if (ppOut)
                *ppOut = apCaller[i];
            return;
        }
    }
}

// From sub_6B710's end: the message pMsg was made.
void TrigMsgSent(type_42E00 *pMsg)
{
    TrigMsgRec *r;
    TrigMsgKind *k = NULL;
    RwInt32 i;
    RwUInt32 dwScript = 0;

    if (!s_bMsgRecord || pMsg == NULL)
        return;
    MsgLock();
    __try
    {
        r = &s_aMsgLog[s_nMsgLog % TRIGMSG_LOG];
        memset(r, 0, sizeof(*r));
        r->dwFrame = port_frame;
        r->pKind = pMsg->unk_00;
        if (r->pKind && r->pKind->unk_00)
            ReadText(r->pKind->unk_00, r->szKind, sizeof(r->szKind) - 1);
        else
            strcpy(r->szKind, "?");
        if (pMsg->unk_04)
            MsgWho(pMsg->unk_04, r->szTo, sizeof(r->szTo));
        else
            strcpy(r->szTo, "all");
        MsgWho(pMsg->unk_08, r->szFrom, sizeof(r->szFrom));
        r->dwTo = pMsg->unk_04;
        r->dwFrom = pMsg->unk_08;
        if (ReadU32(&dword_449328, &dwScript) && dwScript)
        {
            type_3D2E7C *pObj = ((type_67620 *)dwScript)->vf_024();

            ScriptName((type_67620 *)dwScript, r->szScript, sizeof(r->szScript));
            r->dwScriptObject = pObj ? pObj->get_unk_04() : 0;
        }
        else
            strcpy(r->szScript, "-");
        r->nArgs = r->pKind ? r->pKind->unk_10 : 0;
        for (i = 0; i < r->nArgs && i < 4 && pMsg->unk_14; i++)
            r->anArgs[i] = pMsg->unk_14[i];
        // (past this function: its sender, then who called that)
        r->nCallers = RtlCaptureStackBackTrace(1, 6, r->apCaller, NULL);
        s_nMsgLog++;
        for (i = 0; i < s_nMsgKinds; i++)
            if (s_aMsgKinds[i].pKind == r->pKind)
            {
                k = &s_aMsgKinds[i];
                break;
            }
        if (k == NULL && s_nMsgKinds < TRIGMSG_KINDS)
        {
            k = &s_aMsgKinds[s_nMsgKinds++];
            memset(k, 0, sizeof(*k));
            k->pKind = r->pKind;
            strcpy(k->szKind, r->szKind);
        }
        if (k)
        {
            void *pCode = NULL;
            RwChar szCode[96];

            k->nCount++;
            k->dwLastFrame = r->dwFrame;
            // (the sender: the running script when there is one, else the message's sender)
            MsgAddWho(k->aszFrom, &k->nFrom, strcmp(r->szScript, "-") != 0 ? r->szScript : r->szFrom);
            MsgAddWho(k->aszTo, &k->nTo, r->szTo);
            MsgSenderCode(r->apCaller, r->nCallers, szCode, sizeof(szCode), &pCode);
            for (i = 0; i < k->nCode; i++)
                if (k->apCode[i] == pCode)
                    break;
            if (i == k->nCode && k->nCode < TRIGMSG_WHO && pCode)
                k->apCode[k->nCode++] = pCode;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    LeaveCriticalSection(&s_csMsg);
}

// A message to send, picked in the tab, sent on the main thread (TrigMsgTick): its kind's
// index in the loaded image's table, its target (0 all) and its arguments.
static struct
{
    RwBool bPending;
    RwInt32 nKind;
    RwUInt32 dwTarget;
    RwInt32 anArgs[16];
    RwChar szResult[128];
} s_msgSend;

static void TrigMsgTick()
{
    static RwInt32 s_nStart = -1;

    static RwUInt32 s_dwSummary;

    if (s_nStart < 0)
    {
        // (CODFH_MSGS=1: record from the start, and log who sent what once, 20 seconds in)
        s_nStart = 0;
        if (GetEnvironmentVariableA("CODFH_MSGS", NULL, 0))
        {
            s_bMsgRecord = TRUE;
            s_dwSummary = port_frame + 1200;
        }
    }
    if (s_dwSummary && port_frame >= s_dwSummary)
    {
        RwInt32 i, k;

        s_dwSummary = 0;
        MsgLock();
        plog("msgs: %u messages, %d kinds", s_nMsgLog, s_nMsgKinds);
        for (i = 0; i < s_nMsgKinds && i < 40; i++)
        {
            TrigMsgKind *m = &s_aMsgKinds[i];
            RwChar szFrom[200], szTo[200], szCode[96];

            szFrom[0] = szTo[0] = 0;
            for (k = 0; k < m->nFrom; k++)
                WaitAppend(szFrom, sizeof(szFrom), m->aszFrom[k]);
            for (k = 0; k < m->nTo; k++)
                WaitAppend(szTo, sizeof(szTo), m->aszTo[k]);
            szCode[0] = 0;
            if (m->nCode)
                MsgSenderCode(&m->apCode[0], 1, szCode, sizeof(szCode), NULL);
            plog("msgs: %5u %s from %s to %s (code %s)", m->nCount, m->szKind, szFrom, szTo, szCode);
        }
        LeaveCriticalSection(&s_csMsg);
    }
    if (!s_msgSend.bPending)
        return;
    s_msgSend.bPending = FALSE;
    __try
    {
        type_67620 *pTarget = s_msgSend.dwTarget ? sub_67620(s_msgSend.dwTarget) : NULL;
        RwChar szKind[48], szTo[64];

        if (s_msgSend.dwTarget && pTarget == NULL)
        {
            _snprintf(s_msgSend.szResult, sizeof(s_msgSend.szResult), "not sent: the target is gone");
            return;
        }
        if (s_msgSend.nKind < 0 || s_msgSend.nKind >= dword_4492F8)
        {
            _snprintf(s_msgSend.szResult, sizeof(s_msgSend.szResult), "not sent: no such message");
            return;
        }
        WaitMsgName(s_msgSend.nKind, szKind, sizeof(szKind));
        if (pTarget)
            ScriptName(pTarget, szTo, sizeof(szTo));
        else
            strcpy(szTo, "all");
        // (queued like the engine's own sends; delivered on the next action tick)
        sub_6B680(s_msgSend.nKind, pTarget, NULL, NULL, s_msgSend.anArgs, 0, false, false);
        _snprintf(s_msgSend.szResult, sizeof(s_msgSend.szResult), "sent %s to %s (frame %u)", szKind, szTo, port_frame);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        _snprintf(s_msgSend.szResult, sizeof(s_msgSend.szResult), "not sent: it faulted");
    }
    s_msgSend.szResult[sizeof(s_msgSend.szResult) - 1] = 0;
}

// The scripts to pick a target from: every live one of the three pools, named.
struct MsgTarget
{
    RwUInt32 dwHandle;
    RwChar szName[80];
};
#define MSG_TARGETS 1200
static MsgTarget s_aMsgTargets[MSG_TARGETS];
static RwInt32 s_nMsgTargets;

static void MsgTargetsRefresh()
{
    type_16C2A0 *apPools[3] = { &dword_4499F0, &dword_449A30, &dword_449A50 };
    static const RwChar *const s_apszKind[3] = { "task", "machine", "performance" };
    RwUInt32 dwBase;
    RwInt32 nStride, nCount, i, p;

    s_nMsgTargets = 0;
    for (p = 0; p < 3; p++)
    {
        if (!PoolFree(apPools[p], &dwBase, &nStride, &nCount))
            continue;
        for (i = 0; i < nCount && s_nMsgTargets < MSG_TARGETS; i++)
        {
            type_67620 *pObj = (type_67620 *)(dwBase + i * nStride);
            MsgTarget *t;
            RwChar szName[64];
            RwUInt32 dwHandle;

            if (s_abFree[i] || !ReadU32(&pObj->unk_04, &dwHandle))
                continue;
            t = &s_aMsgTargets[s_nMsgTargets++];
            t->dwHandle = dwHandle;
            ScriptName(pObj, szName, sizeof(szName));
            _snprintf(t->szName, sizeof(t->szName), "%s (%s)", szName, s_apszKind[p]);
            t->szName[sizeof(t->szName) - 1] = 0;
        }
    }
}

static void MsgSendUi()
{
    static RwChar s_szKindFilter[32], s_szTargetFilter[32];
    static RwInt32 s_nKind = -1;
    static RwUInt32 s_dwTarget;
    static RwChar s_szTarget[80] = "all";
    static RwBool s_abFloat[16];
    static float s_afArgs[16];
    RwChar szKind[64];
    RwInt32 i, nArgs = 0;

    ImGui::SeparatorText("Send a message");
    if (dword_4492F8 <= 0 || dword_4492F4 == NULL)
    {
        ImGui::TextDisabled("(no script image loaded)");
        return;
    }
    // (its kind)
    if (s_nKind >= 0 && s_nKind < dword_4492F8)
        WaitMsgName(s_nKind, szKind, sizeof(szKind));
    else
        strcpy(szKind, "(pick one)");
    ImGui::SetNextItemWidth(260.0f);
    if (ImGui::BeginCombo("message", szKind))
    {
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputText("filter##msgkind", s_szKindFilter, sizeof(s_szKindFilter));
        for (i = 0; i < dword_4492F8 && i < 4000; i++)
        {
            RwChar sz[64];

            WaitMsgName(i, sz, sizeof(sz));
            if (s_szKindFilter[0] && !ReportHas(sz, s_szKindFilter))
                continue;
            ImGui::PushID(i);
            if (ImGui::Selectable(sz, i == s_nKind))
                s_nKind = i;
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }
    // (its target)
    ImGui::SetNextItemWidth(260.0f);
    if (ImGui::BeginCombo("to", s_szTarget))
    {
        if (ImGui::IsWindowAppearing())
            MsgTargetsRefresh();
        ImGui::SetNextItemWidth(200.0f);
        ImGui::InputText("filter##msgto", s_szTargetFilter, sizeof(s_szTargetFilter));
        if (ImGui::Selectable("all (every script listening)", s_dwTarget == 0))
        {
            s_dwTarget = 0;
            strcpy(s_szTarget, "all");
        }
        for (i = 0; i < s_nMsgTargets; i++)
        {
            if (s_szTargetFilter[0] && !ReportHas(s_aMsgTargets[i].szName, s_szTargetFilter))
                continue;
            ImGui::PushID(i);
            if (ImGui::Selectable(s_aMsgTargets[i].szName, s_aMsgTargets[i].dwHandle == s_dwTarget))
            {
                s_dwTarget = s_aMsgTargets[i].dwHandle;
                strncpy(s_szTarget, s_aMsgTargets[i].szName, sizeof(s_szTarget) - 1);
            }
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }
    // (its arguments: as many as the kind takes, each an int or a float)
    if (s_nKind >= 0 && s_nKind < dword_4492F8)
    {
        __try
        {
            nArgs = dword_4492F4[s_nKind].unk_10;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            nArgs = 0;
        }
        if (nArgs < 0 || nArgs > 16)
            nArgs = 0;
    }
    for (i = 0; i < nArgs; i++)
    {
        RwChar szLabel[24];

        ImGui::PushID(100 + i);
        sprintf(szLabel, "argument %d", i + 1);
        ImGui::SetNextItemWidth(140.0f);
        if (s_abFloat[i])
            ImGui::InputFloat(szLabel, &s_afArgs[i]);
        else
        {
            int n = (int)s_afArgs[i];

            if (ImGui::InputInt(szLabel, &n))
                s_afArgs[i] = (float)n;
        }
        ImGui::SameLine();
        Check("float", &s_abFloat[i]);
        ImGui::PopID();
    }
    if (nArgs == 0 && s_nKind >= 0)
        ImGui::TextDisabled("(it takes no arguments)");
    ImGui::BeginDisabled(s_nKind < 0 || s_msgSend.bPending);
    if (ImGui::Button("send"))
    {
        s_msgSend.nKind = s_nKind;
        s_msgSend.dwTarget = s_dwTarget;
        for (i = 0; i < 16; i++)
        {
            union { RwInt32 n; RwReal f; } u;

            if (s_abFloat[i])
                u.f = s_afArgs[i];
            else
                u.n = (RwInt32)s_afArgs[i];
            s_msgSend.anArgs[i] = u.n;
        }
        s_msgSend.bPending = TRUE;
    }
    ImGui::EndDisabled();
    if (s_msgSend.szResult[0])
    {
        ImGui::SameLine();
        ImGui::TextUnformatted(s_msgSend.szResult);
    }
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(queued as the engine's own sends are, sub_6B680, and delivered on the next action tick: "
                        "any script listening for it reacts as if the game had sent it. An object handle as an "
                        "argument is the number in the object column of the Waits and script tables)");
    ImGui::PopTextWrapPos();
}

static void TabMessages()
{
    static RwChar s_szFilter[32];
    static RwInt32 s_nSel = -1;
    static RwBool s_bFollow = TRUE;
    RwInt32 i, k;

    Check("record the messages sent", &s_bMsgRecord);
    ImGui::SameLine();
    if (ImGui::Button("clear##msgs"))
    {
        MsgLock();
        s_nMsgLog = 0;
        s_nMsgKinds = 0;
        s_nSel = -1;
        LeaveCriticalSection(&s_csMsg);
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(160.0f);
    ImGui::InputText("message filter", s_szFilter, sizeof(s_szFilter));
    ImGui::PushTextWrapPos(0.0f);
    ImGui::TextDisabled("(every script message as it is made: by a script's action opcode, or by the engine's code by "
                        "name or index. The sender is the script that was running when there was one; the code is "
                        "the function that sent it. Waits shows who is waiting for each)");
    ImGui::PopTextWrapPos();

    ImGui::SeparatorText("Who sends what");
    MsgLock();
    if (ImGui::BeginTable("msgkinds", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY |
                                         ImGuiTableFlags_Resizable, ImVec2(0.0f, 220.0f)))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("message", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("sent", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("last frame", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("from");
        ImGui::TableSetupColumn("to");
        ImGui::TableHeadersRow();
        for (i = 0; i < s_nMsgKinds; i++)
        {
            TrigMsgKind *m = &s_aMsgKinds[i];
            RwChar szFrom[320], szTo[320];

            if (s_szFilter[0] && !ReportHas(m->szKind, s_szFilter))
                continue;
            szFrom[0] = szTo[0] = 0;
            for (k = 0; k < m->nFrom; k++)
                WaitAppend(szFrom, sizeof(szFrom), m->aszFrom[k]);
            for (k = 0; k < m->nTo; k++)
                WaitAppend(szTo, sizeof(szTo), m->aszTo[k]);
            ImGui::PushID(i);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(m->szKind, i == s_nSel, ImGuiSelectableFlags_SpanAllColumns))
                s_nSel = i == s_nSel ? -1 : i;
            ImGui::TableNextColumn();
            ImGui::Text("%u", m->nCount);
            ImGui::TableNextColumn();
            ImGui::Text("%u", m->dwLastFrame);
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s%s", szFrom, m->nFrom >= TRIGMSG_WHO ? ", ..." : "");
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s%s", szTo, m->nTo >= TRIGMSG_WHO ? ", ..." : "");
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    if (s_nSel >= 0 && s_nSel < s_nMsgKinds)
    {
        TrigMsgKind *m = &s_aMsgKinds[s_nSel];

        ImGui::Text("%s is sent by this code:", m->szKind);
        for (k = 0; k < m->nCode; k++)
        {
            RwChar sz[96];
            void *p = m->apCode[k];

            MsgSenderCode(&p, 1, sz, sizeof(sz), NULL);
            ImGui::BulletText("%s", sz);
        }
    }

    ImGui::SeparatorText("The last messages");
    Check("follow the newest", &s_bFollow);
    if (ImGui::BeginTable("msglog", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY |
                                       ImGuiTableFlags_Resizable, ImVec2(0.0f, 260.0f)))
    {
        RwInt32 nShown = s_nMsgLog < TRIGMSG_LOG ? (RwInt32)s_nMsgLog : TRIGMSG_LOG;

        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("frame", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("message", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("to");
        ImGui::TableSetupColumn("from (sender object)");
        ImGui::TableSetupColumn("while running");
        ImGui::TableSetupColumn("arguments");
        ImGui::TableSetupColumn("code");
        ImGui::TableHeadersRow();
        for (i = nShown; i >= 1; i--)
        {
            const TrigMsgRec *r = &s_aMsgLog[(s_nMsgLog - i) % TRIGMSG_LOG];
            RwChar szArgs[64], szCode[96];

            if (s_szFilter[0] && !ReportHas(r->szKind, s_szFilter))
                continue;
            szArgs[0] = 0;
            for (k = 0; k < r->nArgs && k < 4; k++)
            {
                RwChar sz[16];

                sprintf(sz, "%d", r->anArgs[k]);
                WaitAppend(szArgs, sizeof(szArgs), sz);
            }
            if (r->nArgs > 4)
                WaitAppend(szArgs, sizeof(szArgs), "...");
            MsgSenderCode(r->apCaller, r->nCallers, szCode, sizeof(szCode), NULL);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%u", r->dwFrame);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(r->szKind);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(r->szTo);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(r->szFrom);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(r->szScript);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(szArgs);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(szCode);
        }
        if (s_bFollow && s_bMsgRecord)
            ImGui::SetScrollHereY(1.0f);
        ImGui::EndTable();
    }
    LeaveCriticalSection(&s_csMsg);
    MsgSendUi();
}

// ---- the spawn test's diagnostics: the soldier's messages, the animations not found ----

// Each animation asked for (sub_77B70): its id, how often asked and found, the last caller.
#define TRIGANIM_IDS 512
static struct
{
    RwInt32 nId;
    RwUInt32 nAsked, nFound, nLogged;
    void *pCaller;
} s_aAnimIds[TRIGANIM_IDS];
static RwInt32 s_nAnimIds;
static RwBool s_bAnimRecord;

void TrigAnimLookup(RwInt32 nId, RwInt32 bFound, void *pCaller)
{
    RwInt32 i;

    if (!s_bAnimRecord)
        return;
    for (i = 0; i < s_nAnimIds; i++)
        if (s_aAnimIds[i].nId == nId)
            break;
    if (i == s_nAnimIds)
    {
        if (s_nAnimIds >= TRIGANIM_IDS)
            return;
        memset(&s_aAnimIds[i], 0, sizeof(s_aAnimIds[i]));
        s_aAnimIds[i].nId = nId;
        s_nAnimIds++;
    }
    s_aAnimIds[i].nAsked++;
    if (bFound)
        s_aAnimIds[i].nFound++;
    s_aAnimIds[i].pCaller = pCaller;
}

// Starts recording the messages and the animation lookups (the spawn test).
static void SpawnAiDiagStart()
{
    s_bMsgRecord = TRUE;
    s_bAnimRecord = TRUE;
}

// Logs the soldier's traffic since the last call: the messages to its object (dwObject), from
// it, or sent while one of its scripts ran; and each animation asked for but not found since.
static void SpawnAiDiagLog(RwUInt32 dwObject)
{
    static RwUInt32 s_nNext;
    RwUInt32 n;
    RwInt32 i, k;
    RwChar szCode[96], szArgs[64];

    MsgLock();
    if (s_nMsgLog - s_nNext > TRIGMSG_LOG)
        s_nNext = s_nMsgLog - TRIGMSG_LOG;
    for (n = s_nNext; n < s_nMsgLog; n++)
    {
        const TrigMsgRec *r = &s_aMsgLog[n % TRIGMSG_LOG];

        if (r->dwTo != dwObject && r->dwFrom != dwObject && r->dwScriptObject != dwObject)
            continue;
        szArgs[0] = 0;
        for (k = 0; k < r->nArgs && k < 4; k++)
        {
            RwChar sz[16];

            sprintf(sz, "%d", r->anArgs[k]);
            WaitAppend(szArgs, sizeof(szArgs), sz);
        }
        MsgSenderCode(r->apCaller, r->nCallers, szCode, sizeof(szCode), NULL);
        plog("spawnai:   msg %s%s to %s, from %s, while %s ran (%s) [%s]", r->szKind,
             r->dwTo == dwObject ? " (to it)" : r->dwScriptObject == dwObject ? " (by its script)" : " (from it)",
             r->szTo, r->szFrom, r->szScript, szArgs, szCode);
    }
    s_nNext = s_nMsgLog;
    LeaveCriticalSection(&s_csMsg);
    for (i = 0; i < s_nAnimIds; i++)
    {
        RwUInt32 nMissed = s_aAnimIds[i].nAsked - s_aAnimIds[i].nFound;

        if (nMissed > s_aAnimIds[i].nLogged)
        {
            MsgCodeName(s_aAnimIds[i].pCaller, szCode, sizeof(szCode));
            plog("spawnai:   animation %08X not found (%u of %u asks), asked by %s", (RwUInt32)s_aAnimIds[i].nId, nMissed,
                 s_aAnimIds[i].nAsked, szCode);
            s_aAnimIds[i].nLogged = nMissed;
        }
    }
}

// (CODFH_WAITS=1: logs the timers and the waiting tasks once, 20 seconds in)
extern "C" void plog(const char *fmt, ...);
static void WaitsLogTick()
{
    static RwInt32 s_nStart = -1;
    static RwUInt32 s_dwAt;
    RwUInt32 dwBase;
    RwInt32 nStride, nCount, i, n = 0;
    RwChar szName[96], szMsg[64], szWhat[512];

    if (s_nStart < 0)
    {
        s_nStart = GetEnvironmentVariableA("CODFH_WAITS", NULL, 0) ? 1 : 0;
        s_dwAt = port_frame + 1200;
    }
    if (s_nStart != 1 || port_frame < s_dwAt)
        return;
    s_nStart = 2;
    plog("waits: the timers' clock %.1f s", dword_449B40 / 60.0f);
    __try
    {
        type_73360 *t;

        for (t = dword_449B44; t != NULL && n < 40; t = t->unk_14, n++)
        {
            type_67620 *pObj = sub_67620(t->unk_00);

            if (pObj)
                ScriptName(pObj, szName, sizeof(szName));
            else
                strcpy(szName, "(gone)");
            WaitMsgName(t->unk_04, szMsg, sizeof(szMsg));
            plog("waits: timer %s for %s in %.1f s", szMsg, szName, (t->unk_10 - dword_449B40) / 60.0f);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    n = 0;
    if (PoolFree(&dword_4499F0, &dwBase, &nStride, &nCount))
        for (i = 0; i < nCount && n < 40; i++)
        {
            type_3D2E20 *t = (type_3D2E20 *)(dwBase + i * nStride);
            type_3D2E20_118 *rec;
            RwInt32 nRec = 0;

            if (s_abFree[i])
                continue;
            szWhat[0] = 0;
            __try
            {
                if (!t->unk_10C)
                    continue;
                for (rec = t->unk_118; rec != NULL && nRec < 16; rec = rec->unk_04, nRec++)
                {
                    RwChar szMsgs[256];

                    if (WaitRegistrations(rec->unk_00, 1, szMsgs, sizeof(szMsgs)))
                        WaitAppend(szWhat, sizeof(szWhat), szMsgs);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                continue;
            }
            ScriptName((type_67620 *)t, szName, sizeof(szName));
            plog("waits: task %s waits for %s", szName, szWhat[0] ? szWhat : (t->unk_10D ? "a message" : "a wake"));
            n++;
        }
}

static void TabScripts()
{
    RwUInt32 dwRunning;
    RwInt32 nCall = CallOpcode();

    if (!ReadU32(&dword_449328, &dwRunning))
        dwRunning = 0;
    if (ImGui::CollapsingHeader("Pools (sub_713E0)"))
        Pools();
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("name filter##scripts", s_szScriptFilter, sizeof(s_szScriptFilter));
    if (ImGui::BeginTabBar("scriptkinds"))
    {
        if (ImGui::BeginTabItem("Waits"))
        {
            TabWaits();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Messages"))
        {
            TabMessages();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("State machines"))
        {
            ScriptTable("machines", &dword_449A30, TRUE, dwRunning, nCall);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Performances"))
        {
            ScriptTable("performances", &dword_449A50, FALSE, dwRunning, nCall);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Tasks"))
        {
            ScriptTable("tasks", &dword_4499F0, FALSE, dwRunning, nCall);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ScriptSelected(nCall);
}

// ---- VM ----

// The VM's state as the last script to run halted (TrigWebVmSnapshot, from
// the VM's run, sub_68310, before it puts its own state back: the overlay
// draws between runs, when the registers are the idle ones): the registers,
// the code around the code pointer and the top of the stack, copied then.
struct TrigWebVm
{
    RwUInt32 dwFrame;
    RwUInt32 dwRuns;
    RwUInt32 dwIp, dwSp, dwFp, dwFourth, dwObj;
    RwUInt8 bHalt, bYielded;
    RwUInt32 adwCode[16];       // from the code pointer - 4 words
    RwUInt8 abCode[16];         // which read
    RwUInt32 adwStack[16];      // from the stack pointer down
    RwInt32 nStack;
    RwUInt32 dwObjCode, dwObjStack, dwObjFrame;
};
static TrigWebVm s_vm;
static RwBool s_bVmFreeze;
extern "C" volatile unsigned port_frame;

void TrigScriptRunEnd();

void TrigWebVmSnapshot()
{
    RwInt32 i;

    TrigScriptRunEnd();
    if (s_bVmFreeze)
        return;
    s_vm.dwRuns++;
    s_vm.dwFrame = port_frame;
    s_vm.dwIp = (RwUInt32)dword_449320;
    s_vm.dwSp = (RwUInt32)dword_449318;
    s_vm.dwFp = (RwUInt32)dword_44931C;
    s_vm.dwFourth = (RwUInt32)dword_4492E0;
    s_vm.dwObj = (RwUInt32)dword_449328;
    s_vm.bHalt = byte_449324;
    s_vm.bYielded = byte_449325;
    for (i = 0; i < 16; i++)
        s_vm.abCode[i] = s_vm.dwIp && ReadU32((void *)(s_vm.dwIp + (i - 4) * 4), &s_vm.adwCode[i]);
    s_vm.nStack = 0;
    for (i = 0; s_vm.dwSp && i < 16; i++)
    {
        if (!ReadU32((void *)(s_vm.dwSp - i * 4), &s_vm.adwStack[i]))
            break;
        s_vm.nStack++;
    }
    s_vm.dwObjCode = s_vm.dwObjStack = s_vm.dwObjFrame = 0;
    if (s_vm.dwObj)
    {
        ReadU32(&((type_3D2DB8 *)s_vm.dwObj)->unk_68, &s_vm.dwObjCode);
        ReadU32(&((type_3D2DB8 *)s_vm.dwObj)->unk_6C, &s_vm.dwObjStack);
        ReadU32(&((type_3D2DB8 *)s_vm.dwObj)->unk_70, &s_vm.dwObjFrame);
    }
}

// The script debugger's reports (sub_6A970, a message delivered; sub_6B060,
// a script object's line: "Line Changed", "Print Int", "Script Assert" and
// the like), which the release build builds and never prints: the last 512,
// newest last. The settings deciding which it makes are CDebugScript's
// (unit_042F40), shown under "Script debugger".
#define TRIGWEB_REPORTS 512
#define TRIGWEB_REPORT 200
static RwChar s_aszReport[TRIGWEB_REPORTS][TRIGWEB_REPORT];
static RwUInt32 s_adwReportFrame[TRIGWEB_REPORTS];
static RwUInt32 s_dwReports;
static RwBool s_bReportPause, s_bReportFollow = TRUE;
static RwChar s_szReportFilter[64];
static CRITICAL_SECTION s_csReport;
static LONG s_nReportInit;

static void ReportLock()
{
    if (InterlockedCompareExchange(&s_nReportInit, 1, 0) == 0)
    {
        InitializeCriticalSection(&s_csReport);
        s_nReportInit = 2;
    }
    while (s_nReportInit != 2)
        Sleep(0);
    EnterCriticalSection(&s_csReport);
}

void TrigWebScriptReport(const RwChar *pszWhat, const RwChar *pszLine)
{
    RwChar *psz;
    size_t n;

    if (s_bReportPause || pszLine == NULL)
        return;
    // (the prints and asserts come with their values from TrigWebScriptPrint and
    // TrigWebScriptCheck, whatever the settings)
    if (pszWhat == NULL && (strstr(pszLine, " Print Int at") || strstr(pszLine, " Print Float at")
                            || strstr(pszLine, " Script Assert at")))
        return;
    ReportLock();
    psz = s_aszReport[s_dwReports % TRIGWEB_REPORTS];
    s_adwReportFrame[s_dwReports % TRIGWEB_REPORTS] = port_frame;
    if (pszWhat)
        _snprintf(psz, TRIGWEB_REPORT, "%s: %s", pszWhat, pszLine);
    else
        _snprintf(psz, TRIGWEB_REPORT, "%s", pszLine);
    psz[TRIGWEB_REPORT - 1] = 0;
    n = strlen(psz);
    while (n && (psz[n - 1] == '\n' || psz[n - 1] == '\r'))
        psz[--n] = 0;
    s_dwReports++;
    TrigLiveLog(psz);
    LeaveCriticalSection(&s_csReport);
}

// The script pScript as the debugger names it, with its place when the
// running script has one (release scripts leave "(Release Scripts)" and 0).
static void ScriptWho(type_67620 *pScript, RwChar *psz, RwInt32 nMax)
{
    RwChar szFile[48], szName[96];

    ScriptName(pScript, szName, sizeof(szName));
    if (dword_449284 > 0 && dword_449288 > 0x10000)
    {
        ReadText((const RwChar *)dword_449288, szFile, 40);
        _snprintf(psz, nMax, "%s, %s(%d)", szName, szFile, dword_449284);
    }
    else
        _snprintf(psz, nMax, "%s", szName);
    psz[nMax - 1] = 0;
}

// "PrintInt" and "PrintFloat" (unit_0441B0): their argument, which the
// release build never prints.
void TrigWebScriptPrint(type_67620 *pScript, const RwChar *pszWhat, type_44350 *pCall, RwInt32 nFloat)
{
    RwChar szWho[128], szLine[TRIGWEB_REPORT];

    if (s_bReportPause)
        return;
    ScriptWho(pScript, szWho, sizeof(szWho));
    if (pCall->unk_0C < 1)
        _snprintf(szLine, sizeof(szLine), "%s (no argument), %s", pszWhat, szWho);
    else if (nFloat)
        _snprintf(szLine, sizeof(szLine), "%s %g, %s", pszWhat, SCRIPT_ARGF(pCall, 1), szWho);
    else
        _snprintf(szLine, sizeof(szLine), "%s %d, %s", pszWhat, SCRIPT_ARG(pCall, 1), szWho);
    szLine[sizeof(szLine) - 1] = 0;
    TrigWebScriptReport("print", szLine);
}

// A failed script check (sub_44220's condition clear): the running script,
// its place and the command at its code pointer.
void TrigWebScriptCheck()
{
    RwChar szWho[128], szCommand[64], szLine[TRIGWEB_REPORT];
    RwUInt32 dw;

    if (s_bReportPause)
        return;
    ScriptWho(dword_449328, szWho, sizeof(szWho));
    szCommand[0] = 0;
    if (dword_449320 && ReadU32(dword_449320, &dw) && (RwInt32)(dw & 0xFF) == CallOpcode())
        CommandName((RwInt16)(dw >> 16), szCommand);
    _snprintf(szLine, sizeof(szLine), "%s%s%s", szCommand[0] ? szCommand : "", szCommand[0] ? ", " : "", szWho);
    szLine[sizeof(szLine) - 1] = 0;
    TrigWebScriptReport("check failed", szLine);
}

static RwBool ReportHas(const RwChar *psz, const RwChar *pszPart)
{
    size_t n = strlen(pszPart);

    for (; *psz; psz++)
        if (_strnicmp(psz, pszPart, n) == 0)
            return TRUE;
    return FALSE;
}

static void CheckInt(const RwChar *pszLabel, RwInt32 *pn)
{
    bool b = *pn != 0;

    if (ImGui::Checkbox(pszLabel, &b))
        *pn = b;
}

// The debug switches (RWS::DebugSwitches): the ones the game reads named.
static const RwChar *SwitchName(RwInt32 n)
{
    switch (n)
    {
    case 0x15:
        return "no soldiers or tanks created (the scripts' CreateSoldier, CreateTank)";
    case 0x19:
        return "CDebugScript's command 13 (nothing reads it)";
    }
    return NULL;
}

static void TabScriptLog()
{
    RwInt32 i, nFirst, nCount;
    RwChar szName[0x20];

    ImGui::TextDisabled("The scripts' prints and failed checks are always logged; the reports below as asked.");
    if (ImGui::TreeNode("Reports to make (CDebugScript's settings)"))
    {
        CheckInt("report every script object's lines (dword_44928C)", &dword_44928C);
        CheckInt("report task objects' lines (dword_4492A8)", &dword_4492A8);
        CheckInt("report every message delivered (dword_449294)", &dword_449294);
        CheckInt("report one-argument messages (dword_4492B0)", &dword_4492B0);
        CheckInt("only objects with a name (dword_449310)", &dword_449310);
        memcpy(szName, String, sizeof(szName));
        szName[sizeof(szName) - 1] = 0;
        if (ImGui::InputText("only this name or ID (String; empty: any)", szName, sizeof(szName)))
        {
            memcpy(String, szName, sizeof(szName));
            byte_44930C = String[0] >= '0' && String[0] <= '9' ? 1 : 0;
        }
        ImGui::SameLine();
        ImGui::TextDisabled(byte_44930C ? "(an ID)" : "(a name)");
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Debug switches (RWS::DebugSwitches)"))
    {
        for (i = 0; i < RWS::DebugSwitches::m_last; i++)
        {
            const RwChar *pszName = SwitchName(i);
            RwChar szLabel[96];
            bool b = RWS::DebugSwitches::GetSwitch(i);

            if (pszName == NULL && !b)
                continue;
            _snprintf(szLabel, sizeof(szLabel), "0x%02X %s", i, pszName ? pszName : "");
            szLabel[sizeof(szLabel) - 1] = 0;
            if (ImGui::Checkbox(szLabel, &b))
                RWS::DebugSwitches::SetSwitch(i, b);
        }
        {
            static RwInt32 s_nSwitch;

            ImGui::SetNextItemWidth(120.0f);
            ImGui::InputInt("##switch", &s_nSwitch);
            if (s_nSwitch < 0)
                s_nSwitch = 0;
            if (s_nSwitch >= RWS::DebugSwitches::m_last)
                s_nSwitch = RWS::DebugSwitches::m_last - 1;
            ImGui::SameLine();
            if (ImGui::Button("set"))
                RWS::DebugSwitches::SetSwitch(s_nSwitch, true);
            ImGui::SameLine();
            if (ImGui::Button("clear"))
                RWS::DebugSwitches::SetSwitch(s_nSwitch, false);
            ImGui::SameLine();
            ImGui::TextDisabled("any switch by number (the set ones are listed)");
        }
        ImGui::TreePop();
    }

    ImGui::Separator();
    Check("pause", &s_bReportPause);
    ImGui::SameLine();
    Check("follow", &s_bReportFollow);
    ImGui::SameLine();
    if (ImGui::Button("clear##reports"))
    {
        ReportLock();
        s_dwReports = 0;
        LeaveCriticalSection(&s_csReport);
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(200.0f);
    ImGui::InputText("filter##reports", s_szReportFilter, sizeof(s_szReportFilter));
    ImGui::SameLine();
    ImGui::TextDisabled("%u made", s_dwReports);
    if (ImGui::BeginChild("reports", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_HorizontalScrollbar))
    {
        ReportLock();
        nCount = s_dwReports < TRIGWEB_REPORTS ? (RwInt32)s_dwReports : TRIGWEB_REPORTS;
        nFirst = (RwInt32)(s_dwReports - nCount);
        for (i = 0; i < nCount; i++)
        {
            RwUInt32 dw = (RwUInt32)(nFirst + i) % TRIGWEB_REPORTS;

            if (s_szReportFilter[0] && !ReportHas(s_aszReport[dw], s_szReportFilter))
                continue;
            ImGui::TextDisabled("%6u", s_adwReportFrame[dw]);
            ImGui::SameLine();
            ImGui::TextUnformatted(s_aszReport[dw]);
        }
        LeaveCriticalSection(&s_csReport);
        if (s_bReportFollow && !s_bReportPause && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 20.0f)
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
}

static void TabVm()
{
    RwUInt32 dwTop, dwFrame, dw;
    RwInt32 i, nCall = CallOpcode();
    RwChar szName[64];

    if (s_vm.dwRuns == 0)
    {
        ImGui::Text("No script has run yet.");
        return;
    }
    Check("freeze (keep this snapshot)", &s_bVmFreeze);
    ImGui::SameLine();
    ImGui::TextDisabled("the script that halted last, frame %u (now %u); %u runs seen", s_vm.dwFrame, port_frame,
                        s_vm.dwRuns);
    if (ImGui::CollapsingHeader("Registers, as it halted", ImGuiTreeNodeFlags_DefaultOpen) && BeginRows("regs"))
    {
        Row("code pointer (dword_449320)", "0x%08X", s_vm.dwIp);
        Row("stack pointer (dword_449318)", "0x%08X", s_vm.dwSp);
        Row("frame pointer (dword_44931C)", "0x%08X", s_vm.dwFp);
        Row("fourth word (dword_4492E0)", "0x%08X", s_vm.dwFourth);
        Row("script object (dword_449328)", "0x%08X", s_vm.dwObj);
        Row("halt (byte_449324)", "%d", s_vm.bHalt);
        Row("yielded (byte_449325)", "%d", s_vm.bYielded);
        RowU32("commands (NumOfElements)", &NumOfElements, FALSE);
        Row("call opcode", "%d", nCall);
        ImGui::EndTable();
    }

    // The code around the code pointer: each word with its opcode (the low
    // byte) and, for the call opcode, the command (the high half).
    if (ImGui::CollapsingHeader("Code", ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (i = 0; i < 16; i++)
        {
            if (!s_vm.abCode[i])
                continue;
            dw = s_vm.adwCode[i];
            szName[0] = 0;
            if ((RwInt32)(dw & 0xFF) == nCall)
                CommandName((RwInt16)(dw >> 16), szName);
            ImGui::Text("0x%08X%s  %08X  op %3u  %s", s_vm.dwIp + (i - 4) * 4, i == 4 ? " <" : "  ", dw, dw & 0xFF,
                        szName);
        }
    }

    // The script object's saved state (now: the run stored it back).
    if (ImGui::CollapsingHeader("Script object", ImGuiTreeNodeFlags_DefaultOpen) && BeginRows("obj"))
    {
        if (s_vm.dwObj)
        {
            Row("object", "0x%08X", s_vm.dwObj);
            RowU32("vtable", (void *)s_vm.dwObj, TRUE);
            Row("saved code (unk_68)", "0x%08X", s_vm.dwObjCode);
            Row("saved stack (unk_6C)", "0x%08X", s_vm.dwObjStack);
            Row("saved frame (unk_70)", "0x%08X", s_vm.dwObjFrame);
        }
        else
            Row("object", "none");
        ImGui::EndTable();
    }

    // The VM's stack, from the stack pointer down, as it halted.
    if (ImGui::CollapsingHeader("Stack (from the stack pointer)"))
    {
        for (i = 0; i < s_vm.nStack; i++)
            ImGui::Text("sp-%-3d 0x%08X %d", i * 4, s_vm.adwStack[i], (RwInt32)s_vm.adwStack[i]);
    }

    // The message argument stack (dword_4493FC frame, dword_4493F8 top), now.
    if (ImGui::CollapsingHeader("Message argument stack (now)") && ReadU32(&dword_4493F8, &dwTop) &&
        ReadU32(&dword_4493FC, &dwFrame))
    {
        ImGui::Text("base 0x%08X, frame 0x%08X, top 0x%08X", (RwUInt32)unk_4498D4, dwFrame, dwTop);
        for (dw = (RwUInt32)unk_4498D4; dw < dwTop && dw < (RwUInt32)unk_4498D4 + 64 * 4; dw += 4)
        {
            RwUInt32 dwWord;

            if (!ReadU32((void *)dw, &dwWord))
                break;
            ImGui::Text("0x%08X%s 0x%08X %d", dw, dw == dwFrame ? " (frame)" : "", dwWord, (RwInt32)dwWord);
        }
    }
}

// ---- Sections ----

static void SlotRow(const RwChar *pszName, type_4E5D30 *pSlot)
{
    RwUInt32 dwLive, dwLoading, dwSection, dwWorld, dwColl;

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("%s", pszName);
    if (!ReadU32(&pSlot->unk_00, &dwLive) || !ReadU32(&pSlot->unk_04, &dwLoading)
        || !ReadU32(&pSlot->unk_08, &dwSection) || !ReadU32(&pSlot->unk_20, &dwWorld)
        || !ReadU32(&pSlot->unk_28, &dwColl))
    {
        ImGui::TableNextColumn();
        ImGui::Text("?");
        return;
    }
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(dwLive ? "loaded" : dwLoading ? "loading" : "empty");
    ImGui::TableNextColumn();
    ImGui::Text("%d", dwSection & 0xFFFF);
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(dwWorld ? "yes" : "-");
    ImGui::TableNextColumn();
    ImGui::TextUnformatted(dwColl ? "yes" : "-");
}

#ifdef CODFH_ALL_SECTIONS
// Every section at once (game/sectionslots.h): while on, the section triggers and the restarts'
// reconcile (sub_D8660) unload nothing, and turning it on loads every SECTIONS\S_n.RWS the
// level has and has not loaded (sub_D7F70, on the game thread), while slots are free.
static RwBool s_bAllSections;
static RwBool s_bAllSectionsPending;
static RwInt32 s_nAllSectionsLoaded;

RwInt32 port_all_sections_on()
{
    // (CODFH_ALLSECTIONS=1: on from the start, so a level's start loads them all)
    static RwInt32 s_nEnv = -1;

    if (s_nEnv < 0)
    {
        s_nEnv = GetEnvironmentVariableA("CODFH_ALLSECTIONS", NULL, 0) ? 1 : 0;
        if (s_nEnv)
            s_bAllSections = TRUE;
    }
    return s_bAllSections != 0;
}

void port_all_sections_load()
{
    RwInt32 n, i, nFree, nLoaded = 0;

    for (n = 1; n <= 64; n++)
    {
        if (sub_174640((RwUInt16)n))
            continue;
        for (i = 0, nFree = 0; i < SECTION_SLOTS; i++)
            if (!dword_4E5D30[i].get_unk_00() && dword_4E5D30[i].unk_08 == 0xFFFF)
                nFree++;
        if (nFree == 0)
            break;
        sub_D7F70(n);
        if (sub_174640((RwUInt16)n))
            nLoaded++;
    }
    s_nAllSectionsLoaded = nLoaded;
    sprintf(s_szReqResult, "every section: %d more loaded", nLoaded);
}

// (from TrigWebTick, on the game thread: the load the switch asked for)
static void AllSectionsTick()
{
    if (!s_bAllSectionsPending)
        return;
    s_bAllSectionsPending = FALSE;
    port_all_sections_load();
}
#endif

static void TabSections()
{
    static int s_nSection, s_nSlot;
    RwInt32 i;
    RwChar sz[48];

#ifdef CODFH_ALL_SECTIONS
    {
        RwInt32 nLive = 0;
        RwBool bWas = s_bAllSections;

        Check("load every section at once", &s_bAllSections);
        if (s_bAllSections && !bWas)
            s_bAllSectionsPending = TRUE;
        for (i = 0; i < SECTION_SLOTS; i++)
            nLive += dword_4E5D30[i].get_unk_00() ? 1 : 0;
        ImGui::SameLine();
        ImGui::TextDisabled("%d of %d slots live", nLive, SECTION_SLOTS);
        ImGui::TextDisabled("(on: the level's other sections load now, and the section triggers and restarts "
                            "unload none; off: the triggers stream them again. Only loading and drawing see the "
                            "extra slots: collision, the AI's paths and the lighting zones keep to the first four)");
    }
#endif

    if (ImGui::BeginTable("slots", 5, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("");
        ImGui::TableSetupColumn("state");
        ImGui::TableSetupColumn("section");
        ImGui::TableSetupColumn("world");
        ImGui::TableSetupColumn("collision");
        ImGui::TableHeadersRow();
        for (i = 0; i < SECTION_SLOTS; i++)
        {
            // (the extra slots only while live)
            if (i >= 4 && !dword_4E5D30[i].get_unk_00())
                continue;
            sprintf(sz, "slot %d", i);
            SlotRow(sz, &dword_4E5D30[i]);
        }
        SlotRow("global (0x7FFF)", &unk_4E5CD8);
        ImGui::EndTable();
    }
    ImGui::SetNextItemWidth(120);
    ImGui::InputInt("section", &s_nSection);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("into slot", &s_nSlot, 0, 3);
    ImGui::SameLine();
    if (ImGui::Button("load"))
        Request(REQ_SECTION, s_nSection, s_nSlot, 0.0f, 0.0f, 0.0f);
    ImGui::TextDisabled("Done on the game's main thread like a section trigger: the slot is unloaded and the section "
                        "queued; the other slots are kept.");
    if (ImGui::CollapsingHeader("Level set-up", ImGuiTreeNodeFlags_DefaultOpen) && BeginRows("setup"))
    {
        Row("SectionInfo slots in use", "%d", SectionInfo::sub_B0140());
        RowU32("starting sections set (dword_4B6850)", &dword_4B6850, FALSE);
        for (i = 0; i < 4; i++)
        {
            sprintf(sz, "starting section %d (dword_4B6840)", i);
            RowU32(sz, &dword_4B6840[i], FALSE);
        }
        ImGui::EndTable();
    }
}

// ---- Entities ----

// The entity's kind from its unk_2C bits (type_3D3548.h), into psz.
static void EntityKind(RwUInt32 dwBits, RwChar *psz)
{
    psz[0] = 0;
    if (dwBits & 0x10)
        strcat(psz, "player ");
    if (dwBits & 0x20)
        strcat(psz, "soldier ");
    if (dwBits & 0x100)
        strcat(psz, "animated bg ");
    if (dwBits & 0x4000)
        strcat(psz, "pickup ");
    if (dwBits & 0x10000)
        strcat(psz, "destructible ");
    if (dwBits & 0x20000)
        strcat(psz, "kind 0x20000 ");
    if (dwBits & 1)
        strcat(psz, "(ally) ");
    if (dwBits & 2)
        strcat(psz, "(enemy) ");
    if (psz[0] == 0)
        sprintf(psz, "0x%X", dwBits);
}

// The entity's frame position and hit points; FALSE when it faults.
static RwBool EntityState(type_3D3548 *pEntity, RwV3d *pvPos, RwInt32 *pnHp, RwBool *pbHasPos)
{
    __try
    {
        RwFrame *pFrame = pEntity->unk_338.unk_08;

        *pbHasPos = pFrame != NULL;
        if (pFrame)
            *pvPos = RwFrameGetMatrix(pFrame)->pos;
        // ("GetHitPoints")
        *pnHp = pEntity->vf_174();
        return TRUE;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        return FALSE;
    }
}

static void TabEntities()
{
    static int s_nFilter;
    static const RwInt32 s_anFilters[5] = {0, 0x20, 0x10, 0x4000, 2};
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vPlayer;
    RwBool bPlayer;
    RwInt32 i, nShown = 0, nLive = 0;

    bPlayer = pPlayer != NULL && PlayerPosition(pPlayer, &vPlayer);
    ImGui::Text("Show:");
    ImGui::SameLine();
    ImGui::RadioButton("all", &s_nFilter, 0);
    ImGui::SameLine();
    ImGui::RadioButton("soldiers", &s_nFilter, 1);
    ImGui::SameLine();
    ImGui::RadioButton("players", &s_nFilter, 2);
    ImGui::SameLine();
    ImGui::RadioButton("pickups", &s_nFilter, 3);
    ImGui::SameLine();
    ImGui::RadioButton("enemies", &s_nFilter, 4);
    if (!ImGui::BeginTable("entities", 8, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    {
        static const RwChar *const s_apszCols[8] = {"slot", "handle", "entity", "kind", "position", "hp",
                                                    "distance", ""};
        for (i = 0; i < 8; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
    }
    for (i = 0; i < 768 && nShown < 400; i++)
    {
        RwUInt32 dwHandle, dwEntity, dwBits;
        RwV3d v;
        RwInt32 n;
        RwBool bHas;
        RwChar szKind[96];

        if (!ReadU32(&dword_4B6A00[i].unk_00, &dwHandle) || !ReadU32(&dword_4B6A00[i].unk_04, &dwEntity)
            || dwEntity == 0)
            continue;
        if (!ReadU32(&((type_3D3548 *)dwEntity)->unk_2C, &dwBits))
            continue;
        nLive++;
        if (s_anFilters[s_nFilter] > 0 && !(dwBits & s_anFilters[s_nFilter]))
            continue;
        if (!EntityState((type_3D3548 *)dwEntity, &v, &n, &bHas))
            continue;
        EntityKind(dwBits, szKind);
        ImGui::PushID(i);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", i);
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X", dwHandle);
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X", dwEntity);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(szKind);
        ImGui::TableNextColumn();
        if (bHas)
            ImGui::Text("%.1f, %.1f, %.1f", v.x, v.y, v.z);
        else
            ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::Text("%d", n);
        ImGui::TableNextColumn();
        if (bHas && bPlayer)
            ImGui::Text("%.1f", (RwReal)sqrt((v.x - vPlayer.x) * (v.x - vPlayer.x) + (v.y - vPlayer.y) * (v.y - vPlayer.y)
                                             + (v.z - vPlayer.z) * (v.z - vPlayer.z)));
        else
            ImGui::Text("-");
        ImGui::TableNextColumn();
        if (bHas)
        {
            if (ImGui::SmallButton("teleport"))
                Request(REQ_TELEPORT, 0, 0, v.x, v.y, v.z);
            ImGui::SameLine();
        }
        if (ImGui::SmallButton("kill"))
            Request(REQ_SETHP, i, 0, 0.0f, 0.0f, 0.0f);
        ImGui::SameLine();
        if (ImGui::SmallButton("hp 100"))
            Request(REQ_SETHP, i, 100, 0.0f, 0.0f, 0.0f);
        ImGui::PopID();
        nShown++;
    }
    ImGui::EndTable();
    ImGui::Text("%d live entities; %d shown (up to 400).", nLive, nShown);
}

// ---- Objectives ----

static void TabObjectives()
{
    static int s_nCp, s_nReg, s_nRegValue;
    RwInt32 i;
    RwUInt32 dw;

    if (ImGui::CollapsingHeader("Checkpoint", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ReadU32(&dword_4B8780, &dw))
            ImGui::Text("checkpoint register (dword_4B8780): %d", (RwInt32)dw);
        ImGui::SetNextItemWidth(120);
        ImGui::InputInt("##cp", &s_nCp);
        ImGui::SameLine();
        if (ImGui::Button("set the checkpoint register"))
        {
            // (a plain register the scripts read: written here; "SetCheckPointRegister"
            // also tells the checkpoint object, which this does not)
            dword_4B8780 = s_nCp;
            sprintf(s_szReqResult, "checkpoint register set to %d", s_nCp);
        }
    }

    if (ImGui::CollapsingHeader("Objectives (dword_4E56A0, 15)", ImGuiTreeNodeFlags_DefaultOpen) &&
        ImGui::BeginTable("objectives", 7, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        static const RwChar *const s_apszCols[7] = {"slot", "flags", "object", "key", "marks", "nag timer", "next"};
        for (i = 0; i < 7; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
        for (i = 0; i < 15; i++)
        {
            type_4E56A0 *p = &dword_4E56A0[i];
            RwUInt32 dwFlags = 0, dwObj = 0, dwK0 = 0, dwK1 = 0, dwMarks = 0, dwNext = 0;
            RwReal fNag = 0.0f;

            if (!ReadU32(&p->unk_04, &dwFlags) || !(dwFlags & 1))
                continue;
            ReadU32(&p->unk_00, &dwObj);
            if (dwObj)
            {
                ReadU32(&((type_3DF8D8_base *)dwObj)->unk_04, &dwK0);
                ReadU32((RwUInt8 *)&((type_3DF8D8_base *)dwObj)->unk_04 + 4, &dwK1);
            }
            ReadU32(&p->unk_40, &dwMarks);
            ReadF32(&p->unk_0C, &fNag);
            ReadU32(&p->unk_54, &dwNext);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%d", i);
            ImGui::TableNextColumn();
            ImGui::Text("0x%X%s%s%s", dwFlags, (dwFlags & 4) ? " hidden" : "", (dwFlags & 0x82) ? " radar" : "",
                        (dwFlags & 0x100) ? " long pointer" : "");
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", dwObj);
            ImGui::TableNextColumn();
            ImGui::Text("%08X:%08X", dwK0, dwK1);
            ImGui::TableNextColumn();
            ImGui::TextUnformatted((RwInt32)dwMarks == 0 ? "an object" : (RwInt32)dwMarks == 1 ? "an entity" : "nothing");
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", fNag);
            ImGui::TableNextColumn();
            ImGui::Text("%d", (RwInt8)(dwNext & 0xFF));
        }
        ImGui::EndTable();
        if (ReadU32(&byte_4E564D, &dw))
            ImGui::TextDisabled("list head (byte_4E564D): %d. Objectives have no counter of their own "
                                "(\"Set/ModifyObjectiveCounter\" do nothing in this build).", (RwInt8)(dw & 0xFF));
    }

    if (!ImGui::CollapsingHeader("Global script registers (dword_449408, 0 to 100)", ImGuiTreeNodeFlags_DefaultOpen))
        return;
    ImGui::TextDisabled("Only non-zero ones; a register is an integer, a real or a god name by how the script reads it.");
    if (ImGui::BeginTable("registers", 4, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("index");
        ImGui::TableSetupColumn("as integer");
        ImGui::TableSetupColumn("as real");
        ImGui::TableSetupColumn("second word");
        ImGui::TableHeadersRow();
        for (i = 0; i <= 100; i++)
        {
            RwUInt32 dw0 = 0, dw1 = 0;
            RwReal f;

            if (!ReadU32(&dword_449408[i].unk_00, &dw0) || !ReadU32(&dword_449408[i].unk_04, &dw1))
                continue;
            if (dw0 == 0 && dw1 == 0)
                continue;
            memcpy(&f, &dw0, sizeof(f));
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%d", i);
            ImGui::TableNextColumn();
            ImGui::Text("%d", (RwInt32)dw0);
            ImGui::TableNextColumn();
            ImGui::Text("%g", f);
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", dw1);
        }
        ImGui::EndTable();
    }
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("register", &s_nReg);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(120);
    ImGui::InputInt("integer", &s_nRegValue);
    ImGui::SameLine();
    if (ImGui::Button("set") && s_nReg >= 0 && s_nReg <= 100)
    {
        dword_449408[s_nReg].unk_00 = s_nRegValue;
        sprintf(s_szReqResult, "global register %d set to %d", s_nReg, s_nRegValue);
    }
}

// ---- Memory ----

static void TabMemory()
{
    MEMORYSTATUS ms;
    RwInt32 i;

    memset(&ms, 0, sizeof(ms));
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatus(&ms);
    ImGui::Text("physical %u KB free of %u KB; virtual %u KB free of %u KB (GlobalMemoryStatus)",
                (RwUInt32)(ms.dwAvailPhys / 1024), (RwUInt32)(ms.dwTotalPhys / 1024),
                (RwUInt32)(ms.dwAvailVirtual / 1024), (RwUInt32)(ms.dwTotalVirtual / 1024));

    // the sections' arenas (sub_172820): base, bytes used, size
    if (ImGui::CollapsingHeader("Section arenas (dword_4E5D30[i].unk_10)", ImGuiTreeNodeFlags_DefaultOpen) &&
        ImGui::BeginTable("arenas", 6, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        static const RwChar *const s_apszCols[6] = {"slot", "section", "base", "used", "size", "use"};
        for (i = 0; i < 6; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
        for (i = 0; i < 5; i++)
        {
            type_4E5D30 *pSlot = i < 4 ? &dword_4E5D30[i] : &unk_4E5CD8;
            RwUInt32 dwBase = 0, dwUsed = 0, dwSize = 0, dwSection = 0;

            ReadU32(&pSlot->unk_10.unk_00, &dwBase);
            ReadU32(&pSlot->unk_10.unk_04, &dwUsed);
            ReadU32(&pSlot->unk_10.unk_08, &dwSize);
            ReadU32(&pSlot->unk_08, &dwSection);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (i < 4)
                ImGui::Text("%d", i);
            else
                ImGui::Text("global");
            ImGui::TableNextColumn();
            ImGui::Text("%d", dwSection & 0xFFFF);
            ImGui::TableNextColumn();
            ImGui::Text("0x%08X", dwBase);
            ImGui::TableNextColumn();
            ImGui::Text("%u KB", dwUsed / 1024);
            ImGui::TableNextColumn();
            ImGui::Text("%u KB", dwSize / 1024);
            ImGui::TableNextColumn();
            ImGui::Text("%d%%", dwSize ? (RwInt32)((RwReal)dwUsed * 100.0f / (RwReal)dwSize) : 0);
        }
        ImGui::EndTable();
    }
    if (ImGui::CollapsingHeader("Script pools", ImGuiTreeNodeFlags_DefaultOpen))
        Pools();
    ImGui::TextDisabled("The game's memory handler keeps no statistics in this build (built without its memory "
                        "checking).");
}

// ---- Loading ----

// The loading queue's jobs (types/asynchload.h, which brings the kernel's
// headers in against xtl.h): a file name, a kind (0 a section, 1 a sound
// bank, 2 an anim group, 3 a clump bank), an id and an active flag.
struct type_44BAD8
{
    RwChar unk_00[0x40];
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;
};
extern type_44BAD8 dword_44BAD8[16];
extern type_44BAD8 *dword_44BFF8;
extern type_44BAD8 *dword_44BFFC;
extern RwInt32 dword_44C004;

static void TabLoading()
{
    RwUInt32 dwHead = 0, dwTail = 0, dwRunning = 0;
    RwInt32 i;
    static const RwChar *const s_apszKinds[4] = { "section", "sound bank", "anim group", "clump bank" };

    ReadU32(&dword_44BFF8, &dwHead);
    ReadU32(&dword_44BFFC, &dwTail);
    ReadU32(&dword_44C004, &dwRunning);
    if (dwHead == 0 || dwTail == 0)
        ImGui::Text("loading thread %s; the queue is not set up yet.", dwRunning == 1 ? "running" : "stopped");
    else
        ImGui::Text("loading thread %s; the thread works on slot %d, the next free slot is %d%s.",
                    dwRunning == 1 ? "running" : "stopped",
                    (RwInt32)(dwHead - (RwUInt32)dword_44BAD8) / (RwInt32)sizeof(type_44BAD8),
                    (RwInt32)(dwTail - (RwUInt32)dword_44BAD8) / (RwInt32)sizeof(type_44BAD8),
                    dwHead == dwTail ? " (empty)" : "");
    if (!ImGui::BeginTable("queue", 6, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    {
        static const RwChar *const s_apszCols[6] = {"slot", "active", "kind", "id", "file", ""};
        for (i = 0; i < 6; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
    }
    for (i = 0; i < 16; i++)
    {
        RwUInt32 dwKind = 0, dwId = 0, dwActive = 0;
        RwChar szName[0x44];
        RwUInt32 dwSlot = (RwUInt32)&dword_44BAD8[i];

        ReadU32(&dword_44BAD8[i].unk_40, &dwKind);
        ReadU32(&dword_44BAD8[i].unk_44, &dwId);
        ReadU32(&dword_44BAD8[i].unk_48, &dwActive);
        ReadText(dword_44BAD8[i].unk_00, szName, 0x3F);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", i);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(dwActive ? "yes" : "-");
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(dwKind < 4 ? s_apszKinds[dwKind] : "?");
        ImGui::TableNextColumn();
        ImGui::Text("%d", (RwInt32)dwId);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(szName);
        ImGui::TableNextColumn();
        ImGui::Text("%s%s", dwSlot == dwHead ? "< working" : "", dwSlot == dwTail ? " < next free" : "");
    }
    ImGui::EndTable();
}

// ---- HUD ----

static void TabHud()
{
    RwUInt32 dwHud = 0;
    RwInt32 i;

    ReadU32(&dword_4B9190, &dwHud);
    if (dwHud == 0)
    {
        ImGui::Text("No HUD.");
        return;
    }
    ImGui::TextDisabled("The HUD's %d items (type_DC400_E0); visibility set here holds only for items the "
                        "per-frame update does not drive.", (RwInt32)type_DC400_items);
    if (!ImGui::BeginTable("hud", 8, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    {
        static const RwChar *const s_apszCols[8] = {"item", "name", "visible", "screen x, y", "angle", "texture",
                                                    "text", ""};
        for (i = 0; i < 8; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
    }
    for (i = 0; i < type_DC400_items; i++)
    {
        type_DC400_E0 *pItem = &((type_DC400 *)dwHud)->unk_E0[i];
        RwChar szName[0x24], szText[0x84];
        RwUInt32 dwVis = 0, dwTex = 0;
        RwReal fX = 0.0f, fY = 0.0f, fAngle = 0.0f;

        ReadText(pItem->unk_00, szName, 0x1F);
        if (szName[0] == 0 || szName[0] == '?')
            continue;
        ReadText(pItem->unk_60, szText, 0x7F);
        ReadU32(&pItem->unk_20, &dwVis);
        ReadU32(&pItem->unk_110, &dwTex);
        ReadF32(&pItem->unk_118[0], &fX);
        ReadF32((RwUInt8 *)&pItem->unk_118[0] + 4, &fY);
        ReadF32(&pItem->unk_1E0, &fAngle);
        ImGui::PushID(i);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("0x%02X", i);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(szName);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(dwVis ? "yes" : "-");
        ImGui::TableNextColumn();
        ImGui::Text("%.1f, %.1f", fX, fY);
        ImGui::TableNextColumn();
        ImGui::Text("%.1f", fAngle);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(dwTex ? "yes" : "-");
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(szText);
        ImGui::TableNextColumn();
        if (ImGui::SmallButton(dwVis ? "hide" : "show"))
        {
            __try
            {
                // (the per-frame update sets the items it drives again)
                pItem->unk_20 = dwVis ? 0 : 1;
                sprintf(s_szReqResult, "item %d visible %d", i, dwVis ? 0 : 1);
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                strcpy(s_szReqResult, "the write faulted");
            }
        }
        ImGui::PopID();
    }
    ImGui::EndTable();
}

// ---- the window ----

void TabPerformance();  // (trigperf.cpp: the game's profiler sections, graphed)

// The window's tabs: five groups (what is drawn, the player, the level's objects, the scripts,
// the engine), each a row of its own tabs.
struct ToolTab
{
    const RwChar *pszName;
    void (*pfnDraw)();
};

static void SubTabs(const RwChar *pszId, const ToolTab *pTabs, RwInt32 nTabs)
{
    RwInt32 i;

    if (!ImGui::BeginTabBar(pszId, ImGuiTabBarFlags_FittingPolicyScroll))
        return;
    for (i = 0; i < nTabs; i++)
    {
        if (ImGui::BeginTabItem(pTabs[i].pszName))
        {
            ImGui::BeginChild("tab");
            pTabs[i].pfnDraw();
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
}

// (a list and its selected one, as two tabs of their own)
static void LevelTriggers()
{
    static const ToolTab s_aTabs[] = { { "List", TabTriggers }, { "Selected", TabTrigger } };

    SubTabs("triggers", s_aTabs, 2);
}

static void LevelGenerators()
{
    static const ToolTab s_aTabs[] = { { "List", TabGenerators }, { "Selected", TabGenerator } };

    SubTabs("generators", s_aTabs, 2);
}

// The View group: every overlay in one list by topic, each with its switch beside its name (the
// main one: the page has the rest), and the page of the one picked beside the list.
struct ViewEntry
{
    const RwChar *pszTopic;
    const RwChar *pszName;
    void (*pfnDraw)();
    RwBool *pbOn;
};
extern RwBool g_bTrigDrawGimps;
static const ViewEntry s_aViewEntries[] =
{
    { "World", "Triggers", ViewTriggers, &g_bTrigDrawEnabled },
    { "World", "Collision", ViewCollision, &g_bTrigDrawCollision },
    { "World", "Splines", ViewSplines, &g_bTrigDrawSplines },
    { "World", "Zones", ViewZones, &g_bTrigDrawZones },
    { "World", "Lights", ViewLights, &g_bTrigDrawLights },
    { "World", "Mount points", ViewMounts, &g_bTrigDrawMounts },
    { "World", "Models", ViewModels, &g_bTrigDrawModels },
    { "World", "Skeletons", ViewSkeletons, &g_bTrigDrawSkeletons },
    { "World", "Sounds", ViewSounds, &g_bTrigDrawSounds },
    { "AI", "AI state", ViewAi, &g_bTrigDrawAi },
    { "AI", "Path nodes", ViewAi, &g_bTrigDrawPathNodes },
    { "AI", "Squads", ViewSquads, &g_bTrigDrawSquads },
    { "AI", "Hearing", ViewHearing, &g_bTrigDrawHearing },
    { "AI", "Gimps", ViewGimps, &g_bTrigDrawGimps },
    { "Combat", "Rays", ViewRays, &g_bTrigDrawRays },
    { "Combat", "Hits", ViewHits, &g_bTrigDrawHits },
    { "Combat", "Projectiles", ViewProjectiles, &g_bTrigDrawProjectiles },
    { "Combat", "Generators", ViewGenerators, &g_bTrigDrawPg },
    { "Camera", "Noclip, free camera", ViewCamera, &g_bTrigDrawFreeCam },
    { "Speedrun", "Random numbers", ViewRng, &g_bTrigRngRecord },
    { "Speedrun", "Frame rate", ViewFrameRate, &g_bTrigFrameSample },
};

static void TabView()
{
    static RwInt32 s_nPicked;
    const RwInt32 nEntries = (RwInt32)(sizeof(s_aViewEntries) / sizeof(s_aViewEntries[0]));
    const RwChar *pszTopic = NULL;
    RwInt32 i, nOn = 0;

    ImGui::BeginChild("viewlist", ImVec2(190.0f, 0.0f), ImGuiChildFlags_Borders);
    for (i = 0; i < nEntries; i++)
    {
        const ViewEntry *e = &s_aViewEntries[i];

        if (pszTopic == NULL || strcmp(pszTopic, e->pszTopic))
        {
            pszTopic = e->pszTopic;
            ImGui::SeparatorText(pszTopic);
        }
        ImGui::PushID(i);
        Check("##on", e->pbOn);
        nOn += *e->pbOn ? 1 : 0;
        ImGui::SameLine();
        if (ImGui::Selectable(e->pszName, s_nPicked == i))
            s_nPicked = i;
        ImGui::PopID();
    }
    ImGui::Separator();
    if (ImGui::SmallButton("all off"))
        for (i = 0; i < nEntries; i++)
            *s_aViewEntries[i].pbOn = FALSE;
    ImGui::SameLine();
    ImGui::TextDisabled("%d on", nOn);
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("viewpage");
    if (s_nPicked >= 0 && s_nPicked < nEntries)
    {
        ImGui::SeparatorText(s_aViewEntries[s_nPicked].pszName);
        s_aViewEntries[s_nPicked].pfnDraw();
    }
    ImGui::EndChild();
}

static const ToolTab s_aPlayerTabs[] =
{
    { "Player", TabPlayer }, { "Inventory", TabInventory }, { "Weapons", TabWeapons }, { "Cheats", TabCheats },
};
static const ToolTab s_aLevelTabs[] =
{
    { "Entities", TabEntities }, { "Triggers", LevelTriggers }, { "Generators", LevelGenerators },
    { "Objectives", TabObjectives }, { "Sections", TabSections },
};
static const ToolTab s_aScriptTabs[] =
{
    { "Scripts", TabScripts }, { "Script log", TabScriptLog }, { "VM", TabVm },
};
static const ToolTab s_aEngineTabs[] =
{
    { "Performance", TabPerformance }, { "Level and render", CheatsLevelRender }, { "Audio", CheatsAudio },
    { "Tunables", TabTunables },
    { "Shell", TabShell }, { "HUD", TabHud }, { "Loading", TabLoading }, { "Memory", TabMemory },
    { "Links", EngineLinks },
};
#define TOOL_GROUP(name, tabs) { name, tabs, (RwInt32)(sizeof(tabs) / sizeof(tabs[0])) }
static const struct { const RwChar *pszName; const ToolTab *pTabs; RwInt32 nTabs; } s_aGroups[] =
{
    { "View", NULL, 0 }, TOOL_GROUP("Player", s_aPlayerTabs), TOOL_GROUP("Level", s_aLevelTabs),
    TOOL_GROUP("Scripts", s_aScriptTabs), TOOL_GROUP("Engine", s_aEngineTabs),
};

// The tools' window, drawn by the overlay each frame it is shown
// (pd11_imgui.cpp).
extern "C" void port_debug_tools_window()
{
    ImGui::SetNextWindowPos(ImVec2(420, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(760, 620), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Game debug tools"))
    {
        ImGui::End();
        return;
    }
    // (every text wraps at the window's edge, or its table column's: the hints are long)
    ImGui::PushTextWrapPos(0.0f);
    ResultLine();
    if (ImGui::BeginTabBar("groups"))
    {
        RwInt32 i;

        for (i = 0; i < (RwInt32)(sizeof(s_aGroups) / sizeof(s_aGroups[0])); i++)
        {
            if (ImGui::BeginTabItem(s_aGroups[i].pszName))
            {
                // (View: the overlay list; the rest their tabs)
                if (s_aGroups[i].pTabs == NULL)
                    TabView();
                else
                    SubTabs(s_aGroups[i].pszName, s_aGroups[i].pTabs, s_aGroups[i].nTabs);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::PopTextWrapPos();
    ImGui::End();
}

// The live link's ways in (trigweb.cpp, on the game thread): a teleport through the action
// queue, the trigger Level, Triggers, Selected edits, and the last action's result.
void TrigWebRequestTeleport(const RwV3d *pv)
{
    Request(REQ_TELEPORT, 0, 0, pv->x, pv->y, pv->z);
}

void TrigWebEditTrigger(RwInt32 nHandle)
{
    if (nHandle >= 0 && nHandle < 2000)
        s_nTrigEdit = nHandle;
}

const RwChar *TrigWebResult()
{
    return s_szReqResult;
}

// The live link's script debugger's lookups (scriptdbg.cpp): a command's name, a script's name.
void TrigWebCommandName(RwInt32 nIndex, RwChar *pszOut)
{
    RwInt32 i;

    CommandName(nIndex, pszOut);
    for (i = 0; pszOut[i]; i++)
        if (pszOut[i] == '"' || pszOut[i] == '\\')
            pszOut[i] = '_';
}

void TrigWebScriptName(void *pScript, RwChar *pszOut, RwInt32 nMax)
{
    ScriptName((type_67620 *)pScript, pszOut, nMax);
}

// The Script log tab's settings for the live link: CDebugScript's report switches (the
// debugger's globals), the log's pause, and RWS::DebugSwitches, as {"t":"settings",...}.
RwBool TrigWebSettingsJson(RwChar *psz, RwInt32 nMax)
{
    RwChar szFilter[0x20], szQuoted[80];
    RwInt32 n, i;

    memcpy(szFilter, String, sizeof(szFilter));
    szFilter[sizeof(szFilter) - 1] = 0;
    JsonName(szFilter, szQuoted, sizeof(szQuoted));
    n = _snprintf(psz, nMax,
                  "{\"t\":\"settings\",\"reportAll\":%d,\"reportTasks\":%d,\"reportMessages\":%d,\"reportOneArg\":%d,"
                  "\"namedOnly\":%d,\"filter\":\"%s\",\"filterIsId\":%d,\"logPaused\":%d,\"vmFrozen\":%d,\"switches\":[",
                  dword_44928C, dword_4492A8, dword_449294, dword_4492B0, dword_449310, szQuoted, (RwInt32)byte_44930C,
                  (RwInt32)s_bReportPause, (RwInt32)s_bVmFreeze);
    for (i = 0; i < RWS::DebugSwitches::m_last && n < nMax - 16; i++)
        n += sprintf(psz + n, "%s%d", i ? "," : "", RWS::DebugSwitches::GetSwitch(i) ? 1 : 0);
    _snprintf(psz + n, nMax - n, "]}");
    psz[nMax - 1] = 0;
    return TRUE;
}

// A setting from the live link (the game thread): its name, an index (a switch's) and a value,
// or the text (the report filter's).
void TrigWebSetSetting(const RwChar *pszName, RwInt32 nIndex, RwInt32 nValue, const RwChar *pszText)
{
    if (!strcmp(pszName, "reportAll"))
        dword_44928C = nValue;
    else if (!strcmp(pszName, "reportTasks"))
        dword_4492A8 = nValue;
    else if (!strcmp(pszName, "reportMessages"))
        dword_449294 = nValue;
    else if (!strcmp(pszName, "reportOneArg"))
        dword_4492B0 = nValue;
    else if (!strcmp(pszName, "namedOnly"))
        dword_449310 = nValue;
    else if (!strcmp(pszName, "logPaused"))
        s_bReportPause = nValue != 0;
    else if (!strcmp(pszName, "vmFrozen"))
        s_bVmFreeze = nValue != 0;
    else if (!strcmp(pszName, "switch") && nIndex >= 0 && nIndex < RWS::DebugSwitches::m_last)
        RWS::DebugSwitches::SetSwitch(nIndex, nValue != 0);
    else if (!strcmp(pszName, "filter") && pszText)
    {
        memset(String, 0, 0x20);
        strncpy(String, pszText, 0x1F);
        byte_44930C = String[0] >= '0' && String[0] <= '9' ? 1 : 0;
    }
}

// The VM tab's snapshot for the live link, as {"t":"vm",...}: the registers when the last
// script halted, the code around the code pointer (from 4 words before it) and the stack's top.
RwBool TrigWebVmJson(RwChar *psz, RwInt32 nMax)
{
    RwInt32 n, i;
    RwChar szName[96], szQuoted[200];

    ScriptName((type_67620 *)s_vm.dwObj, szName, sizeof(szName));
    JsonName(szName, szQuoted, sizeof(szQuoted));
    n = _snprintf(psz, nMax,
                  "{\"t\":\"vm\",\"frame\":%u,\"runs\":%u,\"frozen\":%d,\"ip\":\"%08X\",\"sp\":\"%08X\",\"fp\":\"%08X\",\"fourth\":%d,"
                  "\"obj\":\"%08X\",\"name\":\"%s\",\"halted\":%d,\"ended\":%d,\"objCode\":\"%08X\",\"objStack\":\"%08X\","
                  "\"objFrame\":\"%08X\",\"code\":[",
                  s_vm.dwFrame, s_vm.dwRuns, (RwInt32)s_bVmFreeze, s_vm.dwIp, s_vm.dwSp, s_vm.dwFp, (RwInt32)s_vm.dwFourth,
                  s_vm.dwObj, szQuoted, s_vm.bHalt, s_vm.bYielded, s_vm.dwObjCode, s_vm.dwObjStack, s_vm.dwObjFrame);
    for (i = 0; i < 16; i++)
        n += sprintf(psz + n, "%s%s%u", i ? "," : "", s_vm.abCode[i] ? "" : "-", s_vm.abCode[i] ? s_vm.adwCode[i] : 1);
    n += sprintf(psz + n, "],\"stack\":[");
    for (i = 0; i < s_vm.nStack; i++)
        n += sprintf(psz + n, "%s%d", i ? "," : "", (RwInt32)s_vm.adwStack[i]);
    _snprintf(psz + n, nMax - n, "]}");
    psz[nMax - 1] = 0;
    return TRUE;
}

#endif // CODFH_DRAW_TRIGGERS
