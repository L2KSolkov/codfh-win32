// match: _sub_242570 @ 0x00242570
RwBool
sub_242570(RwaWave *wave)
{
    RwBool    (*busy)(RwaWave *wave) = wave->waveDef->busy;

    if (!busy)
    {
        return FALSE;
    }

    return busy(wave);
}

// match: _sub_242810 @ 0x00242810
RwaWave *
sub_242810(RwaWave *wave, RwUInt32 offset, void *buffer, RwUInt32 size)
{
    RwaWave      *(*upload)(RwaWave *wave, RwUInt32 offset, void *buffer, RwUInt32 size);
    RwaWaveFormat  *source = &wave->format;
    RwaWaveFormat  *target = &wave->deviceFormat;
    void           *converted = NULL;

    upload = (RwaWave *(*)(RwaWave *, RwUInt32, void *, RwUInt32))wave->waveDef->unk14;

    if (upload)
    {
        RwaWave    *result;

        if (!sub_2429D0(source, target))
        {
            RwaWaveFormat   format = *source;

            offset = sub_2498D0(&format, buffer, offset, target);
            format.length = size;
            size = sub_249900(&format, (RwUInt32)buffer, target);
            converted = sub_242180(size, rwaMEMHINTDUR_EVENT | rwaID_806);
            if (!converted)
            {
                return NULL;
            }

            if (!sub_249920(&format, buffer, 0, target, converted))
            {
                sub_2422A0(converted);

                return NULL;
            }

            buffer = converted;
        }

        dword_506FFC = wave;
        dword_507000 = offset;
        result = upload(wave, offset, buffer, size);
        sub_242550(result, TRUE);

        if (converted)
        {
            while (sub_242570(result))
            {
            }

            sub_2422A0(converted);
        }

        return result;
    }

    return NULL;
}

