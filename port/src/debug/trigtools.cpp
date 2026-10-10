// The Win32 port's game debug tools (CODFH_DRAW_TRIGGERS, with the ImGui
// overlay): the plain build's research web pages (research/trigweb.cpp in
// C:\codfh-patches\plain-build\draw-triggers.patch) as tabs of an overlay
// window, live state read straight from memory and the pages' actions:
//   Drawing     trigdraw.cpp's switches (triggers, collision, the AI's path
//               nodes, the AI's state, noclip, the free camera) and
//               the game's own debug menu
//   Player      the local player (sub_1745A0(0), a type_10F710)
//   Inventory   health, the inventory and the 39 weapons, with gives
//   Weapons     the weapon settings (dword_4C19C0), edited in place
//   Entities    the entity table (dword_4B6A00): teleport, kill, hp
//   Triggers    the handle table, nearest first: teleport, spawn soldiers
//   Objectives  the checkpoint and global script registers, the objectives
//   Scripts     the script pools and live state machines
//   VM          the level-script VM's registers, code and stacks, as the last
//               script to run halted (the overlay draws between runs)
//   Sections    the section slots, and a section load into one
//   Loading     the loading queue (AsynchLoadingQueue)
//   Memory      the section arenas and the script pools
//   HUD         the HUD's items (151, single player's 101), shown or hidden
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
extern RwReal g_fTrigDrawRange;
extern RwReal g_fTrigDrawTextScale;
extern RwReal g_fTrigDrawCollisionRange;
extern RwReal g_fTrigDrawCollisionLift;
extern RwBool g_bTrigDrawFreeCam;
extern RwBool g_bTrigDrawAi;
extern RwBool g_bTrigDrawAiText;
extern RwBool g_bTrigDrawAiLines;
extern RwBool g_bTrigDrawAiPath;
extern RwBool g_bTrigDrawAiCover;
extern RwBool g_bTrigDrawAiCombat;
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
    REQ_SPAWNSOLDIER    // a: the soldier trigger's handle (-1 the nearest
                        // that can spawn), f: where
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

// Called each frame on the main thread (sub_D7880): carries out the pending
// action from a tab, and a weapon give in progress.
void TrigWebTick()
{
    type_10F710 *pPlayer;
    RwV3d v;

    TickGive();
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

static void TabDrawing()
{
    Check("draw the trigger volumes", &g_bTrigDrawEnabled);
    Check("through walls", &g_bTrigDrawSeeThrough);
    ImGui::SameLine();
    Check("labels (each trigger's type)", &g_bTrigDrawLabels);
    ImGui::SliderFloat("trigger draw distance (0 unlimited)", &g_fTrigDrawRange, 0.0f, 1000.0f, "%.0f");
    ImGui::SliderFloat("label height (of the distance)", &g_fTrigDrawTextScale, 0.005f, 0.1f, "%.3f");
    ImGui::Separator();
    Check("draw the collision worlds", &g_bTrigDrawCollision);
    ImGui::SliderFloat("collision draw distance", &g_fTrigDrawCollisionRange, 5.0f, 200.0f, "%.0f");
    ImGui::SliderFloat("collision lift along the normal", &g_fTrigDrawCollisionLift, 0.0f, 0.5f, "%.3f");
    ImGui::Separator();
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
    ImGui::Separator();
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
    ImGui::Separator();
    Check("noclip for the local player", &g_bTrigDrawNoclip);
    ImGui::SliderFloat("noclip speed", &g_fTrigDrawNoclipSpeed, 1.0f, 500.0f, "%.0f");
    ImGui::TextDisabled("(noclip: the left stick moves along the view, Black up, White down)");
    ImGui::Separator();
    Check("free camera", &g_bTrigDrawFreeCam);
    ImGui::SliderFloat("free camera speed (units a second)", &g_fTrigDrawFreeCamSpeed, 50.0f, 10000.0f, "%.0f",
                       ImGuiSliderFlags_Logarithmic);
    ImGui::SliderFloat("free camera look (radians a second)", &g_fTrigDrawFreeCamLook, 0.5f, 6.0f, "%.1f");
    ImGui::TextDisabled("(free camera: the pad is the camera's, not the player's; the left stick (WASD) moves, the "
                        "right (the mouse) looks, Black/White (Q/E) up and down, the right trigger faster, the left "
                        "slower; start and back stay the game's)");
    ImGui::Separator();
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

    ResultLine();
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
enum { WF_INT, WF_REAL, WF_BOOL, WF_V3D };

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
    ResultLine();
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
static void TrigRow(RwInt32 nHandle, Trigger *pTrigger, RwReal fDist)
{
    RwChar szShape[64], szFlags[48];
    const RwChar *pszKind;
    RwV3d vAt;
    RwBool bSoldier;

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
    if (bSoldier)
    {
        ImGui::SameLine();
        if (ImGui::SmallButton("spawn its soldier ahead of me"))
            Request(REQ_SPAWNSOLDIER, nHandle, 0, 0.0f, 0.0f, 0.0f);
    }
    ImGui::PopID();
}

static void TabTriggers()
{
    RwInt32 i, nCount = 0, nLast;
    Trigger *pTrigger;
    type_10F710 *pPlayer = (type_10F710 *)sub_1745A0(0);
    RwV3d vPlayer;
    RwBool bPlayer;

    ResultLine();
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

static void TabScripts()
{
    RwUInt32 dwBase, dwRunning;
    RwInt32 nStride, nCount, i, nCall = CallOpcode(), nShown = 0;
    RwChar szFile[48], szCode[96];

    if (!ReadU32(&dword_449328, &dwRunning))
        dwRunning = 0;
    if (ImGui::CollapsingHeader("Pools (sub_713E0)", ImGuiTreeNodeFlags_DefaultOpen))
        Pools();

    // the live state machines (type_3D2DB8): the elements of their pool not
    // on its free list
    if (!ImGui::CollapsingHeader("State machines (m_stateMachineObjectPool, type_3D2DB8)",
                                 ImGuiTreeNodeFlags_DefaultOpen))
        return;
    if (!PoolFree(&dword_449A30, &dwBase, &nStride, &nCount))
    {
        ImGui::Text("The pool is not set up.");
        return;
    }
    if (!ImGui::BeginTable("machines", 9, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg))
        return;
    {
        static const RwChar *const s_apszCols[9] = {"object", "handle", "line", "file", "code", "at the code",
                                                    "state", "owner", "parent"};
        for (i = 0; i < 9; i++)
            ImGui::TableSetupColumn(s_apszCols[i]);
        ImGui::TableHeadersRow();
    }
    for (i = 0; i < nCount && nShown < 300; i++)
    {
        RwUInt32 dwObj = dwBase + i * nStride, dwHandle, dwLine, dwFile, dwCodePtr, dwState, dwOwner, dwParent;
        RwUInt32 dwStateIndex = (RwUInt32)-1;
        type_3D2DB8 *pMachine = (type_3D2DB8 *)dwObj;

        if (s_abFree[i])
            continue;
        if (!ReadU32(&pMachine->unk_04, &dwHandle) || !ReadU32(&pMachine->unk_08, &dwLine)
            || !ReadU32(&pMachine->unk_0C, &dwFile) || !ReadU32(&pMachine->unk_68, &dwCodePtr)
            || !ReadU32(&pMachine->unk_6C, &dwState) || !ReadU32(&pMachine->unk_7C, &dwOwner)
            || !ReadU32(&pMachine->unk_88, &dwParent))
            continue;
        // the state record's index (type_3D2DB8_6C::unk_10)
        if (dwState)
        {
            RwUInt32 dw;

            if (ReadU32(&((type_3D2DB8_6C *)dwState)->unk_10, &dw))
                dwStateIndex = (RwInt16)(dw & 0xFFFF);
        }
        // the file: a name when it reads as text, else the number
        if (dwFile > 0x10000)
            ReadText((const RwChar *)dwFile, szFile, 40);
        else
            sprintf(szFile, "%d", (RwInt32)dwFile);
        CodeWord(dwCodePtr, nCall, szCode);
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X%s", dwObj, dwObj == dwRunning ? " < running" : "");
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X", dwHandle);
        ImGui::TableNextColumn();
        ImGui::Text("%d", (RwInt32)dwLine);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(szFile);
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X", dwCodePtr);
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(szCode);
        ImGui::TableNextColumn();
        ImGui::Text("%d", (RwInt32)dwStateIndex);
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X", dwOwner);
        ImGui::TableNextColumn();
        ImGui::Text("0x%08X", dwParent);
        nShown++;
    }
    ImGui::EndTable();
    ImGui::Text("%d shown (up to 300).", nShown);
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

void TrigWebVmSnapshot()
{
    RwInt32 i;

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
static RwBool s_bReportPause, s_bReportLines = TRUE, s_bReportFollow = TRUE;
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
    if (!s_bReportLines && strstr(pszLine, "Line Changed") != NULL)
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
    LeaveCriticalSection(&s_csReport);
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

static void VmDebugger()
{
    RwInt32 i, nFirst, nCount;
    RwChar szName[0x20];

    if (!ImGui::CollapsingHeader("Script debugger (CDebugScript's settings)"))
        return;
    ImGui::TextDisabled("Which reports the game makes; it prints none, they go to the log below.");
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

    ImGui::SeparatorText("Reports");
    Check("pause", &s_bReportPause);
    ImGui::SameLine();
    Check("line changes", &s_bReportLines);
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
    if (ImGui::BeginChild("reports", ImVec2(0.0f, 260.0f), ImGuiChildFlags_Borders,
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

    VmDebugger();
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

    ResultLine();
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

    ResultLine();
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

    ResultLine();
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

    ResultLine();
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
    if (ImGui::BeginTabBar("tabs", ImGuiTabBarFlags_FittingPolicyScroll))
    {
        if (ImGui::BeginTabItem("Drawing"))
        {
            TabDrawing();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Player"))
        {
            TabPlayer();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Inventory"))
        {
            TabInventory();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Weapons"))
        {
            TabWeapons();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Entities"))
        {
            TabEntities();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Triggers"))
        {
            TabTriggers();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Objectives"))
        {
            TabObjectives();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Scripts"))
        {
            TabScripts();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("VM"))
        {
            TabVm();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Sections"))
        {
            TabSections();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Loading"))
        {
            TabLoading();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Memory"))
        {
            TabMemory();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("HUD"))
        {
            TabHud();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

#endif // CODFH_DRAW_TRIGGERS
