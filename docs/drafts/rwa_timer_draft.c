// match: _sub_244980 @ 0x00244980
RwUInt32
sub_244980(void)
{
    RwUInt64    now = sub_244940();
    RwUInt64    start = dword_507178;

    if (now < start)
    {
        return (RwUInt32)(now + (0xFFFFFFFF - start));
    }

    return (RwUInt32)(now - start);
}

