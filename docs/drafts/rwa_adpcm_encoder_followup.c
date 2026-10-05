RwUInt8
sub_24BD30(RwInt16 sample, RwInt32 *predicted, RwInt32 *index)
{
    RwInt32     step = word_42FD38[*index];
    RwInt32     s = sample;
    RwInt32     diff = s - *predicted;
    RwUInt8     code = 0;

    if (diff < 0)
    {
        code = 8;
        diff = -diff;
    }
    if (diff >= step)
    {
        code |= 4;
        diff -= step;
    }
    step >>= 1;
    if (diff >= step)
    {
        code |= 2;
        diff -= step;
    }
    step >>= 1;
    if (diff >= step)
    {
        code |= 1;
        diff -= step;
    }
    step >>= 1;
    if (!(code & 8))
    {
        *predicted = step - diff + s;
    }
    else
    {
        *predicted = s - step + diff;
    }
    if (*predicted > 32767)
    {
        *predicted = 32767;
    }
    else if (*predicted < -32768)
    {
        *predicted = -32768;
    }
    *index += word_42FD18[code];
    if (*index < 0)
    {
        *index = 0;
    }
    else if (*index > 88)
    {
        *index = 88;
    }

    return code;
}
