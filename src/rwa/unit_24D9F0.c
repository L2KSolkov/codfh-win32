/*
 * codfh-match: RenderWare Audio's packed stream description fix-up and
 * clears (0x24D670-0x24DA70): a marker, a track and a stream description.
 */
#include "rwa.h"
#include "rwaint.h"

extern RwaUniqueID *sub_240B40(RwaUniqueID *uniqueID);

extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern RwaUniqueID *sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern RwUInt32 sub_242D60(const RwaWaveFormat *format);
extern RwBool sub_243160(RwaWaveFormat *format, RwUInt8 *buffer, RwBool write, RwBool swap);
extern RwUInt32 dword_516C5C;
extern const RwaUUID unk_3ED5FC;
extern const RwaUUID unk_3ED65C;
#define rwaPackedNameSize(_name) ((rwstrlen(_name) + dword_516C5C) & ~(dword_516C5C - 1))

/* _rwaStreamFormatCreateFromPack, rwad.dll 0x10069E30: shared header
 * and marker ID locals; cue loops retain their own index and ID locals. */
// match: _sub_24D670 @ 0x0024D670
// sp-match: _sub_24D670 @ 0x001617C0
rwaStreamInfo *
sub_24D670(rwaStreamInfo *info)
{
    RwUInt8 *cursor;
    const RwaUUID *uuid;
    const RwChar *name;
    RwUInt32 i;
    RwUInt32 size;

    cursor = (RwUInt8 *)info;
    cursor += sizeof(rwaStreamInfo);
    uuid = ((RwaUniqueID *)info)->uuid;
    if (uuid)
    {
        sub_240C10((RwaUniqueID *)info, (const RwaUUID *)cursor);
        cursor += sizeof(RwaUUID);
    }
    name = ((RwaUniqueID *)info)->name;
    if (name)
    {
        sub_240BF0((RwaUniqueID *)info, (const RwChar *)cursor);
        cursor += rwaPackedNameSize((const RwChar *)cursor);
    }
    info->markers = (rwaStreamMarker *)cursor;
    cursor += info->unk0C * sizeof(rwaStreamMarker);
    size = info->noTracks * sizeof(RwUInt32);
    for (i = 0; i < info->unk0C; i++)
    {
        rwaStreamMarker *marker = &info->markers[i];
        if (marker->unk0C)
        {
            marker->unk0C = (RwUInt32 *)cursor;
            cursor += size;
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        uuid = ((RwaUniqueID *)&info->markers[i])->uuid;
        if (uuid)
        {
            sub_240C10((RwaUniqueID *)&info->markers[i], (const RwaUUID *)cursor);
            cursor += sizeof(RwaUUID);
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        name = ((RwaUniqueID *)&info->markers[i])->name;
        if (name)
        {
            sub_240BF0((RwaUniqueID *)&info->markers[i], (const RwChar *)cursor);
            cursor += rwaPackedNameSize((const RwChar *)cursor);
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        rwaStreamMarker *marker = &info->markers[i];
        if (marker->cues)
        {
            marker->cues = (rwaMarkerCue *)cursor;
            cursor += marker->noCues * sizeof(rwaMarkerCue);
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        rwaStreamMarker *marker = &info->markers[i];
        RwUInt32 j;
        for (j = 0; j < marker->noCues; j++)
        {
            const RwaUUID *cueUUID = marker->cues[j].uniqueID.uuid;
            if (cueUUID)
            {
                sub_240C10(&marker->cues[j].uniqueID, (const RwaUUID *)cursor);
                cursor += sizeof(RwaUUID);
            }
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        rwaStreamMarker *marker = &info->markers[i];
        RwUInt32 j;
        for (j = 0; j < marker->noCues; j++)
        {
            const RwChar *cueName = marker->cues[j].uniqueID.name;
            if (cueName)
            {
                sub_240BF0(&marker->cues[j].uniqueID, (const RwChar *)cursor);
                cursor += rwaPackedNameSize((const RwChar *)cursor);
            }
        }
    }
    info->tracks = (rwaStreamTrack *)cursor;
    cursor += info->noTracks * sizeof(rwaStreamTrack);
    for (i = 0; i < info->noTracks; i++)
    {
        if (info->tracks[i].format)
        {
            info->tracks[i].format = (rwaStreamFormat *)cursor;
            if (!sub_243160((RwaWaveFormat *)cursor, cursor, FALSE, FALSE))
            {
                return NULL;
            }
            cursor += (dword_516C5C - 1 + sub_242D60((RwaWaveFormat *)cursor))
                      & ~(dword_516C5C - 1);
        }
    }
    if (!RwaUUIDCompare(((RwaWaveFormat *)info->tracks[0].format)->dataType, &unk_3ED5FC)
        || !RwaUUIDCompare(((RwaWaveFormat *)info->tracks[0].format)->dataType, &unk_3ED65C))
    {
        if (((RwaWaveFormat *)info->tracks[0].format)->noChannels == 2)
        {
            info->tracks[0].unk0C = 64;
            info->tracks[0].unk1A = 36;
            info->tracks[0].unk18 = 4;
        }
    }
    for (i = 0; i < info->noTracks; i++)
    {
        if (((RwaUniqueID *)&info->tracks[i])->uuid)
        {
            sub_240C10((RwaUniqueID *)&info->tracks[i], (const RwaUUID *)cursor);
            cursor += sizeof(RwaUUID);
        }
    }
    for (i = 0; i < info->noTracks; i++)
    {
        if (((RwaUniqueID *)&info->tracks[i])->name)
        {
            sub_240BF0((RwaUniqueID *)&info->tracks[i], (const RwChar *)cursor);
            cursor += rwaPackedNameSize((const RwChar *)cursor);
        }
    }
    return info;
}

// match: _sub_24D9F0 @ 0x0024D9F0
// sp-match: _sub_24D9F0 @ 0x00161B40
RwInt32
sub_24D9F0(rwaStreamMarker *marker)
{
    sub_240B40((RwaUniqueID *)marker);
    marker->cues = NULL;
    marker->noCues = 0;
    marker->unk18 = 0;
    marker->unk1C = 0;

    return 0;
}

// match: _sub_24DA10 @ 0x0024DA10
// sp-match: _sub_24DA10 @ 0x00161B60
RwInt32
sub_24DA10(rwaStreamTrack *track)
{
    sub_240B40((RwaUniqueID *)track);
    track->unk1A = 0;
    track->unk18 = 0;
    track->unk24 = 0;
    track->unk20 = 0;
    track->unk10 = 0;
    track->unk1C = 0;
    track->unk0C = 0;

    return 0;
}

// match: _sub_24DA40 @ 0x0024DA40
// sp-match: _sub_24DA40 @ 0x00161B90
RwInt32
sub_24DA40(rwaStreamInfo *info)
{
    sub_240B40((RwaUniqueID *)info);
    info->unk0C = 0;
    info->markers = NULL;
    info->noTracks = 0;
    info->tracks = NULL;
    info->unk1C = 0;
    info->unk20 = 0;
    info->unk28 = 0;

    return 0;
}
