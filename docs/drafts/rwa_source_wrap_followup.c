static __forceinline RwUInt32 wrapCount(RwUInt32 size, RwUInt32 unit) { RwUInt32 high; RwUInt32 count = size % unit; sub_2420D0(size % unit, 0xFFFFFFFF / unit, &high, &count); return count; }
// match: _sub_247F20 @ 0x00247F20
RwInt32
sub_247F20(rwaDecoderState *state)
{
    rwaStreamMarker *marker = state->current;
    rwaStreamInfo *info = state->info;
    RwUInt32    result = 0;
    RwUInt32    largest = 0;
    RwUInt32    track = 0;
    RwUInt32 *chunk;

    if (info->noTracks > 0)
    {
    chunk = &info->tracks[0].unk20;
    do
    {
        RwUInt32    size = marker->unk0C[track];

        if (size > largest)
        {
            RwUInt32    unit = *chunk;
            RwUInt32    high;
            RwUInt32    count;

            largest = size;
            count = wrapCount(size, unit);
            if (++count > result)
            {
                result = count;
            }
        }
        track++;
        chunk += sizeof(rwaStreamTrack) / sizeof(RwUInt32);
    }
    while (track < state->info->noTracks);

    if (result == 1)
    {
        return -1;
    }
    }
    return result;
}
