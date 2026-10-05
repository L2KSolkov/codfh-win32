// match: _sub_23E1C0 @ 0x0023E1C0
RwBool
sub_23E1C0(void)
{
    if (!dword_5069BC)
    {
        void   *openParams;

        if (!RwEngineInit(memFuncs, 0, 0x400))
        {
            return FALSE;
        }

        openParams = (void *)1;
        if (!RwEngineOpen(&openParams))
        {
            RwEngineTerm();

            return FALSE;
        }

        if (!RwEngineStart())
        {
            RwEngineClose();
            RwEngineTerm();

            return FALSE;
        }
    }

    return TRUE;
}

// match: _sub_23E240 @ 0x0023E240
static RwBool
sub_23E240(rwaModule *modules, RwUInt32 count, rwaModuleCallBack closeCallBack,
           rwaModuleCallBack openCallBack)
{
    RwUInt32    i;
    RwBool      result;

    for (i = 0; i < count; i++)
    {
        result = modules[i].open();
        if (!result)
        {
            break;
        }

        if (openCallBack)
        {
            result = openCallBack(&modules[i], i);
        }

        if (!result)
        {
            break;
        }
    }

    if (i == count)
    {
        return TRUE;
    }

    while (i > 0)
    {
        modules[i - 1].close();
        if (closeCallBack)
        {
            closeCallBack(&modules[i - 1], i - 1);
        }

        i--;
    }

    return FALSE;
}

// match: _RwaCoreOpen @ 0x0023E510
RwBool
RwaCoreOpen(RwMemoryFunctions *memoryFunctions, RwBool usingRwGraphics)
{
    sub_23E420(0x10);
    dword_5069BC = usingRwGraphics;
    memFuncs = memoryFunctions;

    if (sub_23E240(unk_42E628, 17, (rwaModuleCallBack)sub_23E320,
                   (rwaModuleCallBack)sub_23E2E0) != TRUE)
    {
        return FALSE;
    }

    dword_5069B8 = 0;
    dword_5069B4 = 0;
    dword_5069A8 = 1;

    return TRUE;
}

// match: _sub_23E680 @ 0x0023E680
void
sub_23E680(RwUInt32 amount, RwUInt32 *total)
{
    *total = amount + *total;
}
