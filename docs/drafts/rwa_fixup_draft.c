/*
 * codfh-match: RenderWare Audio's stream description fix-up (0x24D670-
 * 0x24DA70): a stream file's description as read (pointers as flags, the
 * data packed after it) gets its pointers back: its markers and their
 * per-track values, cues, UUIDs and names, its tracks and their formats.
 * Then the description, track and marker clears.
 */
#include "rwa.h"
#include "rwaint.h"

extern RwaUniqueID *sub_240B40(RwaUniqueID *uniqueID);
extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern RwaUniqueID *sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern RwUInt32 sub_242D60(const RwaWaveFormat *format);
extern RwBool sub_243160(RwaWaveFormat *format, RwUInt8 *buffer, RwBool write, RwBool swap);

extern RwUInt32 dword_516C5C;       /* the data alignment */
extern const RwaUUID unk_3ED5FC;    /* Xbox ADPCM */
extern const RwaUUID unk_3ED65C;

/* A name's packed size. */
#define rwaNameSize(_name) ((rwstrlen(_name) + dword_516C5C) & ~(dword_516C5C - 1))

// match: _sub_24D670 @ 0x0024D670
rwaStreamInfo *
sub_24D670(rwaStreamInfo *info)
{
    RwUInt8    *cursor = (RwUInt8 *)(info + 1);
    RwUInt32    i;
    RwUInt32    j;
    RwaWaveFormat *format;
    RwUInt32    size;

    if (((RwaUniqueID *)info)->uuid)
    {
        sub_240C10((RwaUniqueID *)info, (const RwaUUID *)cursor);
        cursor += sizeof(RwaUUID);
    }
    if (((RwaUniqueID *)info)->name)
    {
        sub_240BF0((RwaUniqueID *)info, (const RwChar *)cursor);
        cursor += rwaNameSize((const RwChar *)cursor);
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
        rwaStreamMarker *marker = &info->markers[i];

        if (marker->uuid)
        {
            sub_240C10((RwaUniqueID *)marker, (const RwaUUID *)cursor);
            cursor += sizeof(RwaUUID);
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        rwaStreamMarker *marker = &info->markers[i];

        if (marker->name)
        {
            sub_240BF0((RwaUniqueID *)marker, (const RwChar *)cursor);
            cursor += rwaNameSize((const RwChar *)cursor);
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

        for (j = 0; j < marker->noCues; j++)
        {
            if (marker->cues[j].uniqueID.uuid)
            {
                sub_240C10(&marker->cues[j].uniqueID, (const RwaUUID *)cursor);
                cursor += sizeof(RwaUUID);
            }
        }
    }
    for (i = 0; i < info->unk0C; i++)
    {
        rwaStreamMarker *marker = &info->markers[i];

        for (j = 0; j < marker->noCues; j++)
        {
            if (marker->cues[j].uniqueID.name)
            {
                sub_240BF0(&marker->cues[j].uniqueID, (const RwChar *)cursor);
                cursor += rwaNameSize((const RwChar *)cursor);
            }
        }
    }

    info->tracks = (rwaStreamTrack *)cursor;
    cursor += info->noTracks * sizeof(rwaStreamTrack);
    for (i = 0; i < info->noTracks; i++)
    {
        rwaStreamTrack *track = &info->tracks[i];

        if (track->format)
        {
            track->format = (rwaStreamFormat *)cursor;
            if (!sub_243160((RwaWaveFormat *)cursor, cursor, FALSE, FALSE))
            {
                return NULL;
            }
            cursor += (dword_516C5C - 1 + sub_242D60((RwaWaveFormat *)cursor))
                      & ~(dword_516C5C - 1);
        }
    }
    format = (RwaWaveFormat *)info->tracks[0].format;
    if (!RwaUUIDCompare(format->dataType, &unk_3ED5FC)
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
        RwaUniqueID *id = (RwaUniqueID *)&info->tracks[i];

        if (id->uuid)
        {
            sub_240C10(id, (const RwaUUID *)cursor);
            cursor += sizeof(RwaUUID);
        }
    }
    for (i = 0; i < info->noTracks; i++)
    {
        RwaUniqueID *id = (RwaUniqueID *)&info->tracks[i];

        if (id->name)
        {
            sub_240BF0(id, (const RwChar *)cursor);
            cursor += rwaNameSize((const RwChar *)cursor);
        }
    }

    return info;
}

// match: _sub_24D9F0 @ 0x0024D9F0
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
