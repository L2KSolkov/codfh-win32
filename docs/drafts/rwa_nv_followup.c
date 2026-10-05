// match: _sub_24DAD0 @ 0x0024DAD0
static RwUInt32
sub_24DAD0(RwUInt32 size)
{
    RwUInt32    handle;

    if (dword_507CD4)
    {
        return dword_507CD4(size);
    }
    sub_2FD880(&dword_51DE60, (size + rwaSTREAMEDUNIT - 1) / rwaSTREAMEDUNIT, &handle);
    return handle;
}

// match: _sub_24DBA0 @ 0x0024DBA0
RwaWave *
sub_24DBA0(RwaWave *wave, rwaInstance *obj)
{
    rwaStreamedMemory *memory = (rwaStreamedMemory *)obj->state;

    if (!dword_51DE60.size
        && sub_2FD5D0(memory->size / rwaSTREAMEDUNIT, &dword_51DE60, unk_516CC0))
    {
        dword_51DE60.base = memory->base;
        dword_51DE60.size = memory->size;
        dword_51DE60.unitSize = rwaSTREAMEDUNIT;
    }

    if (!RwaUUIDCompare(wave->deviceFormat.dataType, &unk_3ED5CC))
    {
        wave->unk48 = ((volatile RwaWave *)wave)->deviceFormat.length;
    }
    else if (!RwaUUIDCompare(wave->deviceFormat.dataType, &unk_3ED5FC))
    {
        wave->unk48 = (7 * ((volatile RwaWave *)wave)->deviceFormat.length) >> 1;
    }
    else
    {
        return NULL;
    }

    wave->buffer = (RwUInt8 *)sub_24DAD0((((volatile RwaWave *)wave)->deviceFormat.length + 255) & ~255);
    return wave->buffer ? wave : NULL;
}

