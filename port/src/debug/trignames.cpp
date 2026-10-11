// Trigger names for the debug drawing (CODFH_DRAW_TRIGGERS): the name a level gives a
// trigger, as the scripts find it ("GetEntityFromName"), for trigdraw.cpp's labels.
//
// A named trigger has a kind-0x2E object (type_3DFEEC, flag 1 of unk_10, the trigger at
// unk_2C) under the key the scripts pass. The object keeps no text: the name is in the
// level's GodData, two references away from the binding's own record (the binding's
// low-nibble-8 reference names a record whose first reference names one holding the name
// as a string; cfh-web-suite's GOD_ASSET_TYPES.md, type 46). So once a level, this reads
// LEVELS\<level>\GODDATA.DFF through the game's own streams (as sub_D8310 does), keeps each
// such record's key and name, then asks sub_198800 which trigger each key binds; the
// triggers are found again (at most every two seconds) when one is missing or a cached
// one no longer matches, as after a restart.
// TrigDrawKeyName names any asset by its key the same way (its record's own string, its
// binding's, or one a reference or two away): a gimp's definition and scripts, a spline path.

#ifdef CODFH_DRAW_TRIGGERS

#include <xtl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bastream.h"
#include "types/type_44350.h"
#include "game/functions.h"
#include "game/gameloop.h"

extern "C" volatile unsigned port_frame;
extern "C" void plog(const char *fmt, ...);

enum
{
    TRIGNAMES_MAX = 4096,       // named records a level may have
    TRIGNAMES_LEN = 48,         // a name's length, with its end
    TRIGNAMES_MAXRECORDS = 32768,
};

struct TrigNameKey
{
    RwUInt32 a, b;
    RwChar szName[TRIGNAMES_LEN];
};

struct TrigNameHit
{
    Trigger *pTrigger;
    RwInt32 nKey;               // its TrigNameKey
};

static TrigNameKey *s_pKeys;
static RwInt32 s_nKeys;
static TrigNameHit *s_pHits;
static RwInt32 s_nHits;
static RwChar s_szLevel[32];
static RwBool s_bRead;
static unsigned s_uLastFind;
static RwBool s_bFound;

// Every asset's name, for TrigDrawKeyName: a record's own string, a binding's, or one a
// reference or two away (the first found), sorted by key.
struct TrigAssetName
{
    RwUInt32 a, b;
    RwChar szName[TRIGNAMES_LEN];
};
static TrigAssetName *s_pNames;
static RwInt32 s_nNames;

// ---- the GodData file's records ----

struct TrigNameRecord
{
    RwUInt32 a, b;
    const RwUInt8 *pData;
    RwUInt32 nSize;
};

static TrigNameRecord *s_pRecords;
static RwInt32 s_nRecords;

static RwUInt32 Dword(const RwUInt8 *p)
{
    return (RwUInt32)p[0] | ((RwUInt32)p[1] << 8) | ((RwUInt32)p[2] << 16) | ((RwUInt32)p[3] << 24);
}

// One record at nAt of the asset block (28-byte header: kind, section, size, tag, key a,
// key b, extra; its payload follows; bits 12-20 of the tag count it and the records that
// follow it as its group). The offset past it and its group, or 0 for a bad record.
static RwUInt32 ReadRecord(const RwUInt8 *pBlock, RwUInt32 nBlock, RwUInt32 nAt, RwInt32 nDepth)
{
    RwUInt32 nSize, nTag, nNext;
    RwInt32 i, nGroup;

    if (nDepth > 64 || nAt + 28 > nBlock)
        return 0;
    nSize = Dword(pBlock + nAt + 8);
    nTag = Dword(pBlock + nAt + 12);
    if (nSize < 28 || nAt + nSize > nBlock)
        return 0;
    if (s_nRecords < TRIGNAMES_MAXRECORDS)
    {
        TrigNameRecord *r = &s_pRecords[s_nRecords++];

        r->a = Dword(pBlock + nAt + 16);
        r->b = Dword(pBlock + nAt + 20);
        r->pData = pBlock + nAt + 28;
        r->nSize = nSize - 28;
    }
    nNext = nAt + nSize;
    nGroup = (RwInt32)((nTag >> 12) & 511) - 1;
    for (i = 0; i < nGroup && nNext != 0; i++)
        nNext = ReadRecord(pBlock, nBlock, nNext, nDepth + 1);
    return nNext;
}

static int CompareRecords(const void *p0, const void *p1)
{
    const TrigNameRecord *r0 = (const TrigNameRecord *)p0, *r1 = (const TrigNameRecord *)p1;

    if (r0->a != r1->a)
        return r0->a < r1->a ? -1 : 1;
    if (r0->b != r1->b)
        return r0->b < r1->b ? -1 : 1;
    // (a key read twice: the one with a payload first)
    return (r0->nSize == 0) - (r1->nSize == 0);
}

// The record under the key (the records sorted by key).
static const TrigNameRecord *FindRecord(RwUInt32 a, RwUInt32 b)
{
    RwInt32 nLo = 0, nHi = s_nRecords - 1;

    while (nLo <= nHi)
    {
        RwInt32 nMid = (nLo + nHi) / 2;
        const TrigNameRecord *r = &s_pRecords[nMid];

        if (r->a == a && r->b == b)
        {
            while (nMid > 0 && s_pRecords[nMid - 1].a == a && s_pRecords[nMid - 1].b == b)
                nMid--;
            return s_pRecords[nMid].nSize != 0 ? &s_pRecords[nMid] : NULL;
        }
        if (r->a < a || (r->a == a && r->b < b))
            nLo = nMid + 1;
        else
            nHi = nMid - 1;
    }
    return NULL;
}

// The name a record holds as its payload's start (letters, digits and _ - . : then a 0).
static RwBool RecordString(const TrigNameRecord *r, RwChar *pszOut)
{
    RwUInt32 i;

    for (i = 0; i < r->nSize && i < TRIGNAMES_LEN - 1; i++)
    {
        RwUInt8 c = r->pData[i];

        if (c == 0)
            break;
        if (c < 0x20 || c > 0x7E)
            return FALSE;
        pszOut[i] = (RwChar)c;
    }
    if (i < 2 || i >= r->nSize || r->pData[i] != 0)
        return FALSE;
    pszOut[i] = 0;
    return TRUE;
}

// A binding's name: its low-nibble-8 reference, that record's first reference, its string.
static RwBool BindingName(const TrigNameRecord *r, RwChar *pszOut)
{
    RwUInt32 p;

    if (r->nSize < 12 || r->nSize % 12 != 0)
        return FALSE;
    for (p = 0; p + 12 <= r->nSize; p += 12)
    {
        const TrigNameRecord *pMid, *pText;

        if ((Dword(r->pData + p) & 0xF) != 8)
            continue;
        pMid = FindRecord(Dword(r->pData + p + 4), Dword(r->pData + p + 8));
        if (pMid == NULL || pMid->nSize < 12)
            continue;
        pText = FindRecord(Dword(pMid->pData + 4), Dword(pMid->pData + 8));
        if (pText != NULL && RecordString(pText, pszOut))
            return TRUE;
    }
    return FALSE;
}

// An asset's name: its own string, its binding's, else the first a reference (or two) away.
static RwBool AssetName(const TrigNameRecord *r, RwChar *pszOut, RwInt32 nDepth)
{
    RwUInt32 p;

    if (RecordString(r, pszOut) || BindingName(r, pszOut))
        return TRUE;
    if (nDepth >= 2 || r->nSize < 12 || r->nSize % 12 != 0)
        return FALSE;
    for (p = 0; p + 12 <= r->nSize && p < 12 * 8; p += 12)
    {
        const TrigNameRecord *pRef = FindRecord(Dword(r->pData + p + 4), Dword(r->pData + p + 8));

        if (pRef != NULL && pRef != r && AssetName(pRef, pszOut, nDepth + 1))
            return TRUE;
    }
    return FALSE;
}

// Reads the level's GodData and keeps its bindings' keys and names.
static void ReadLevel(const RwChar *pszLevel)
{
    RwChar szPath[128];
    RwStream *pStream;
    RwUInt8 *pFile = NULL;
    RwUInt32 nFile = 0, nCap = 0, nAt;
    RwInt32 i;

    s_nKeys = 0;
    s_nHits = 0;
    if (s_pKeys == NULL)
        s_pKeys = (TrigNameKey *)malloc(sizeof(TrigNameKey) * TRIGNAMES_MAX);
    if (s_pHits == NULL)
        s_pHits = (TrigNameHit *)malloc(sizeof(TrigNameHit) * TRIGNAMES_MAX);
    if (s_pKeys == NULL || s_pHits == NULL)
        return;
    _snprintf(szPath, sizeof(szPath) - 1, "LEVELS\\%s\\GODDATA.DFF", pszLevel);
    szPath[sizeof(szPath) - 1] = 0;
    pStream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, szPath);
    if (pStream == NULL)
        return;
    for (;;)
    {
        RwUInt32 nGot;

        if (nFile + 65536 > nCap)
        {
            RwUInt8 *pGrown = (RwUInt8 *)realloc(pFile, nCap + 1048576);

            if (pGrown == NULL)
                break;
            pFile = pGrown;
            nCap += 1048576;
        }
        nGot = RwStreamRead(pStream, pFile + nFile, 65536);
        nFile += nGot;
        if (nGot < 65536)
            break;
    }
    RwStreamClose(pStream, szPath);
    if (pFile == NULL)
        return;

    s_pRecords = (TrigNameRecord *)malloc(sizeof(TrigNameRecord) * TRIGNAMES_MAXRECORDS);
    s_nRecords = 0;
    // the file's chunks (type, size, version); a 0x719 chunk whose first word is 8 or 9
    // holds a block of asset records
    for (nAt = 0; s_pRecords != NULL && nAt + 12 <= nFile;)
    {
        RwUInt32 nType = Dword(pFile + nAt), nSize = Dword(pFile + nAt + 4);
        const RwUInt8 *pBody = pFile + nAt + 12;

        if (nAt + 12 + nSize > nFile)
            break;
        if (nType == 0x719 && nSize >= 28 && (Dword(pBody) == 8 || Dword(pBody) == 9))
            ReadRecord(pBody, nSize, 0, 0);
        nAt += 12 + nSize;
    }
    if (s_pRecords != NULL)
        qsort(s_pRecords, s_nRecords, sizeof(TrigNameRecord), CompareRecords);
    for (i = 0; s_pRecords != NULL && i < s_nRecords && s_nKeys < TRIGNAMES_MAX; i++)
    {
        TrigNameKey *k = &s_pKeys[s_nKeys];

        if (BindingName(&s_pRecords[i], k->szName))
        {
            k->a = s_pRecords[i].a;
            k->b = s_pRecords[i].b;
            s_nKeys++;
        }
    }
    // every asset's name
    free(s_pNames);
    s_nNames = 0;
    s_pNames = s_pRecords != NULL ? (TrigAssetName *)malloc(sizeof(TrigAssetName) * (s_nRecords + 1)) : NULL;
    for (i = 0; s_pNames != NULL && i < s_nRecords; i++)
    {
        TrigAssetName *n = &s_pNames[s_nNames];

        if (s_pRecords[i].nSize == 0 || (s_nNames && s_pNames[s_nNames - 1].a == s_pRecords[i].a &&
                                         s_pNames[s_nNames - 1].b == s_pRecords[i].b))
            continue;
        if (AssetName(&s_pRecords[i], n->szName, 0))
        {
            n->a = s_pRecords[i].a;
            n->b = s_pRecords[i].b;
            s_nNames++;
        }
    }
    plog("trigger names: %s has %d named records, %d named assets (%d records, %u bytes)", pszLevel, s_nKeys,
         s_nNames, s_nRecords, nFile);
    free(s_pRecords);
    s_pRecords = NULL;
    s_nRecords = 0;
    free(pFile);
}

// ---- the triggers the keys bind ----

static Trigger *KeyTrigger(const TrigNameKey *k)
{
    type_3DF8D8_04 key;
    type_3DF8D8 *pObj;
    type_3DFEEC *pBinding;

    key.unk_00 = k->a;
    key.unk_04 = k->b;
    pObj = sub_198800(&key);
    if (pObj == NULL || pObj->vf_008() != 0x2E)
        return NULL;
    pBinding = (type_3DFEEC *)pObj;
    if ((pBinding->unk_10 & 1) == 0)
        return NULL;
    return (Trigger *)pBinding->unk_2C_trigger;
}

static void FindTriggers()
{
    RwInt32 i, nBefore = s_nHits;

    s_nHits = 0;
    for (i = 0; i < s_nKeys && s_nHits < TRIGNAMES_MAX; i++)
    {
        Trigger *pTrigger = KeyTrigger(&s_pKeys[i]);

        if (pTrigger != NULL)
        {
            s_pHits[s_nHits].pTrigger = pTrigger;
            s_pHits[s_nHits].nKey = i;
            s_nHits++;
        }
    }
    s_uLastFind = port_frame;
    s_bFound = TRUE;
    if (s_nHits != nBefore)
        plog("trigger names: %d triggers named (of %d names), e.g. %s", s_nHits, s_nKeys,
             s_nHits ? s_pKeys[s_pHits[0].nKey].szName : "-");
}

// The level's GodData read, once a level; FALSE with no level.
static RwBool EnsureLevel()
{
    const RwChar *pszLevel = sub_19B060(sub_19B050());

    if (pszLevel == NULL || pszLevel[0] == 0)
        return FALSE;
    if (!s_bRead || strcmp(s_szLevel, pszLevel) != 0)
    {
        strncpy(s_szLevel, pszLevel, sizeof(s_szLevel) - 1);
        s_szLevel[sizeof(s_szLevel) - 1] = 0;
        ReadLevel(s_szLevel);
        s_bRead = TRUE;
        s_bFound = FALSE;
    }
    return TRUE;
}

// The level's name for the asset under the key (a, b), or NULL.
const RwChar *TrigDrawKeyName(RwUInt32 a, RwUInt32 b)
{
    RwInt32 nLo = 0, nHi;

    if ((a == 0 && b == 0) || !EnsureLevel())
        return NULL;
    nHi = s_nNames - 1;
    while (nLo <= nHi)
    {
        RwInt32 nMid = (nLo + nHi) / 2;
        const TrigAssetName *n = &s_pNames[nMid];

        if (n->a == a && n->b == b)
            return n->szName;
        if (n->a < a || (n->a == a && n->b < b))
            nLo = nMid + 1;
        else
            nHi = nMid - 1;
    }
    return NULL;
}

// The level's name for the trigger, or NULL when it has none (or the level's data has not
// been read).
const RwChar *TrigDrawTriggerName(Trigger *pTrigger)
{
    RwInt32 i;

    if (pTrigger == NULL || !EnsureLevel())
        return NULL;
    if (!s_bFound)
        FindTriggers();
    for (i = 0; i < s_nHits; i++)
        if (s_pHits[i].pTrigger == pTrigger)
        {
            // (still bound to it: a restart rebuilds the triggers)
            if (KeyTrigger(&s_pKeys[s_pHits[i].nKey]) == pTrigger)
                return s_pKeys[s_pHits[i].nKey].szName;
            break;
        }
    // (missing or moved: look again, but not every frame for a trigger with no name)
    if (port_frame - s_uLastFind > 120)
    {
        FindTriggers();
        for (i = 0; i < s_nHits; i++)
            if (s_pHits[i].pTrigger == pTrigger)
                return s_pKeys[s_pHits[i].nKey].szName;
    }
    return NULL;
}

#endif
