/*
 * codfh-match: RenderWare Audio's stream container commands (0x246D50-0x246FD0): the command's
 * initialisation and the node set's entries for the tracks' channels. Split from
 * unit_2452A0.c at an original object boundary: in one unit VC7.0 emits the functions calling
 * these, defined later, at the unit's end (docs/units.md; PLAN M7).
 */

#include "rwa.h"
#include "rwaint.h"

/* Local reconstruction helper, not an original symbol. Typed entry arguments
 * preserve the four store groups at 0x246DF4-0x246E31 when VC7 inlines it. */
static __forceinline void
initEntry(rwaNodeSetEntry *entry, RwUInt32 channel, RwUInt32 track, RwUInt32 kind)
{
    entry->channel = channel;
    entry->track = track;
    entry->kind = kind;
    entry->value = 1.0f;
}

// match: _rwaStreamContainerCommandInitialize @ 0x00246D50
// sp-match: _rwaStreamContainerCommandInitialize @ 0x0015ACA0
rwaContainerCommand *
rwaStreamContainerCommandInitialize(rwaContainerCommand *command)
{
    command->flags = 0;
    command->mode = 1;
    command->source = NULL;
    command->settings = NULL;
    command->rate = 1.0f;
    command->unk14 = 0;
    return command;
}
/* The node set's entries for the tracks' channels: four per channel (kinds
 * 0 to 3, value 1.0); the number of entries, or 0 when they do not fit. */
// match: _sub_246D70 @ 0x00246D70
// sp-match: _sub_246D70 @ 0x0015ACC0
RwUInt32
sub_246D70(rwaNodeSetEntry *entries, RwUInt32 maxEntries, const rwaStreamInfo *info)
{
    RwUInt32    numChannels = 0;
    RwUInt32    track;
    RwUInt32    n;

    for (track = 0; track < info->noTracks; track++)
    {
        numChannels += info->tracks[track].format->channels;
    }
    if (numChannels * 4 > maxEntries)
    {
        return 0;
    }

    n = 0;
    for (track = 0; track < info->noTracks; track++)
    {
        RwUInt32    channel;

        for (channel = 0; channel < info->tracks[track].format->channels; channel++)
        {
            initEntry(&entries[n * 4 + 0], channel, track, 0);
            initEntry(&entries[n * 4 + 1], channel, track, 1);
            initEntry(&entries[n * 4 + 2], channel, track, 2);
            initEntry(&entries[n * 4 + 3], channel, track, 3);
            n++;
        }
    }

    return n * 4;
}
// match: _sub_246E70 @ 0x00246E70
// sp-match: _sub_246E70 @ 0x0015ADC0
rwaContainerCommand *
sub_246E70(rwaContainerCommand *command, const rwaContainerSource *source)
{
    command->source = source;
    command->flags = (command->flags & ~8) | 4;
    command->settings = NULL;
    command->rate = 1.0f;
    command->mode = 1;
    command->unk14 = 0;
    return command;
}
// match: _sub_246EA0 @ 0x00246EA0
// sp-match: _sub_246EA0 @ 0x0015ADF0
rwaContainerCommand *
sub_246EA0(rwaContainerCommand *command, rwaPlaySettings *settings)
{
    command->settings = settings;
    command->flags |= 8;
    return command;
}
// match: _sub_246EB0 @ 0x00246EB0
// sp-match: _sub_246EB0 @ 0x0015AE00
RwBool
sub_246EB0(rwaContainerCommand *command, RwReal rate, const rwaNodeSet *set)
{
    if (set->unk00 & 1)
    {
        return FALSE;
    }
    command->flags |= 0x20;
    command->rate = rate;
    return TRUE;
}
/* Sets value for the entries of the given track, channel and kind (-1:
 * any; kinds 0 to 3). */
/* Debug source-flow evidence: rwad.dll _rwaStreamContainerCommandSetStreamGain,
 * 0x100C04BA; void return and range initialization before the entry loop.
 * The gain arrives as raw 32-bit data, as declared by its caller in unit_23FAD0. */
// match: _sub_246ED0 @ 0x00246ED0
// sp-match: _sub_246ED0 @ 0x0015AE20
void
sub_246ED0(rwaContainerCommand *command, const rwaNodeSet *set, RwInt32 track, RwInt32 channel,
           RwInt32 kind, RwUInt32 value)
{
    RwInt32 trackStart = 0;
    RwInt32 kindStart = 0;
    RwInt32 kindEnd = 4;
    RwInt32 trackEnd;
    RwUInt32 i;

    trackEnd = set->numNodes;

    if (track != -1)
    {
        trackStart = track;
        trackEnd = trackStart + 1;
    }
    if (kind != -1)
    {
        kindStart = kind;
        kindEnd = kindStart + 1;
    }

    for (i = 0; i < set->numEntries; i++)
    {
        RwInt32     index = command->entries[i].track;

        index = (index & 0x80000000) ? index & ~0x80000000 : index;
        if (index >= trackStart && index < trackEnd
            && (RwInt32)command->entries[i].kind >= kindStart
            && (RwInt32)command->entries[i].kind < kindEnd
            && ((RwInt32)command->entries[i].channel == channel || channel < 0))
        {
            command->entries[i].value = *(RwReal *)&value;
            command->entries[i].track = index | 0x80000000;
        }
    }

    command->flags |= 0x10;
}
// match: _sub_246F80 @ 0x00246F80
// sp-match: _sub_246F80 @ 0x0015AED0
rwaContainerCommand *
sub_246F80(rwaContainerCommand *command, RwUInt32 value)
{
    command->unk14 = value;
    command->flags |= 0x40;
    return command;
}
// match: _sub_246F90 @ 0x00246F90
// sp-match: _sub_246F90 @ 0x0015AEE0
rwaContainerCommand *
sub_246F90(rwaContainerCommand *command, RwInt32 mode)
{
    command->mode = mode;
    command->flags |= 0x80;
    return command;
}
// match: _sub_246FB0 @ 0x00246FB0
// sp-match: _sub_246FB0 @ 0x0015AF00
void *
sub_246FB0(RwUInt32 size, RwUInt32 unused)
{
    return sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80F);
}
// match: _sub_246FC0 @ 0x00246FC0
// sp-match: _sub_246FC0 @ 0x0015AF10
void
sub_246FC0(void *mem, RwUInt32 unused)
{
    sub_2421B0(mem);
}
