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
#include "rws/debugswitches.h"
#include "rws/camerahelper.h"
#include "game/cheats.h"
#include "game/gameloop.h"
#include "game/savestate.h"
#include "types/AIData.h"
#include "types/type_3DBC78_450.h"
#include "types/type_1227C0.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_3D2E7C.h"
#include "game/godassetmanager.h"
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
extern type_4E5D30 dword_4E5D30[4];
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
    RwFrameGetMatrix(pFrame)->pos = *pv;
    RwFrameUpdateObjects(pFrame);
    pPlayer->unk_434 = *pv;
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

// Spawns the soldier of the soldier trigger pTrigger (kind 5) at *pv: its
// place (unk_90) and matrix are moved there for the spawn and put back, and
// its free-spawn flag (unk_24_18: no starting cover point needed, entity
// memory past the soldier pool's room) set for it. Its spawn (vf_020) needs
// the trigger's soldier definition loaded, so a trigger of this map. Returns
// the soldier, or NULL.
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
        pSoldier = pTrigger->vf_020();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pSoldier = NULL;
        strcpy(s_szReqResult, "the spawn faulted");
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
        sprintf(s_szReqResult, "spawned a soldier from trigger %d at %.1f, %.1f, %.1f", n, pv->x, pv->y, pv->z);
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
    if (s_bCheatIgnoreMe)
        byte_4C1940 = 1;
    if (s_bCheatGod)
        byte_4F28F8 = 1;
    if (s_bCheatAmmo)
        dword_4C19AC = 1;
    if (s_bCheatFreezeAi || s_nCheatFrozen)
        CheatFreezeTick();
}

// Called each frame on the main thread (sub_D7880): carries out the pending
// action from a tab, and a weapon give in progress.
void TrigWebTick()
{
    type_10F710 *pPlayer;
    RwV3d v;

    CheatTick();
    TickGive();
    TrigLiveTick();
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
    CheckSet("god mode (byte_4F28F8: bullets and explosions take no health)", &s_bCheatGod, FALSE, CheatGodOff);
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

static void ViewCollision()
{
    Check("draw the collision worlds", &g_bTrigDrawCollision);
    ImGui::SliderFloat("collision draw distance", &g_fTrigDrawCollisionRange, 5.0f, 200.0f, "%.0f");
    ImGui::SliderFloat("collision lift along the normal", &g_fTrigDrawCollisionLift, 0.0f, 0.5f, "%.3f");
    CollisionKinds();
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
static void ViewLights()
{
    RwInt32 i;

    Check("draw the lights", &g_bTrigDrawLights);
    ImGui::SameLine();
    Check("their lines##lights", &g_bTrigDrawLightLabels);
    ImGui::SameLine();
    Check("radii", &g_bTrigDrawLightRadii);
    ImGui::SliderFloat("light draw distance (0 unlimited)", &g_fTrigDrawLightRange, 0.0f, 50000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    ImGui::TextDisabled("(the level's lights (the world manager's list), the ambient and the directional slots; the "
                        "directionals as arrows in front of the camera. Most entities are lit by their zone's "
                        "colours instead, which are not lights)");
    if (!g_bTrigDrawLights)
        return;
    if (ImGui::BeginTable("lights", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                          ImVec2(0.0f, 260.0f)))
    {
        static const RwChar *const s_apszSource[4] = { "the level's", "the ambient", "a directional slot", "the fallback" };

        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("type");
        ImGui::TableSetupColumn("from");
        ImGui::TableSetupColumn("where");
        ImGui::TableSetupColumn("radius");
        ImGui::TableSetupColumn("colour");
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

static void TabSections()
{
    static int s_nSection, s_nSlot;
    RwInt32 i;
    RwChar sz[48];

    if (ImGui::BeginTable("slots", 5, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("");
        ImGui::TableSetupColumn("state");
        ImGui::TableSetupColumn("section");
        ImGui::TableSetupColumn("world");
        ImGui::TableSetupColumn("collision");
        ImGui::TableHeadersRow();
        for (i = 0; i < 4; i++)
        {
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
