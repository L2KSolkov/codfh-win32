/*
 * codfh-match: RenderWare Audio's core (rwabase.c in the library's PS2
 * header, docs/reference/rwacore_ps2.h: RwaCoreOpen, RwaCoreUpdateStart,
 * RwaCoreUpdateFinish, RwaCoreClose): its module tables and the RenderWare
 * engine start-up used when no graphics engine runs.
 */
#include "rwa.h"
#include "rwaint.h"



typedef struct RwMemoryFunctions RwMemoryFunctions;

extern RwUInt32 dword_5069BC;
RwMemoryFunctions *memFuncs;
extern RwBool RwEngineInit(RwMemoryFunctions *memFuncs, RwUInt32 initFlags, RwUInt32 resArenaSize);
extern RwBool RwEngineOpen(void *initParams);
extern RwBool RwEngineStart(void);
extern RwBool RwEngineStop(void);
extern RwBool RwEngineClose(void);
extern RwBool RwEngineTerm(void);

extern RwBool sub_23E1C0(void);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_42E628 @ 0x0042E628

// What its data definitions name.
extern void RwaListenerInterfaceRegister(void);
extern void RwaVoice3DInterfaceRegister(void);
extern void nullsub_6(void);
extern void sub_23CA00(void);
extern void sub_23CB80(void);
extern void sub_23CC40(void);
extern void sub_23D690(void);
extern void _rwaObjDefCloseModule(void);
extern void sub_23E0C0(void);
void sub_23E220(void);
RwBool sub_23E5C0(void);
void sub_23E600(void);
extern void _rwaObjCloseModule(void);
extern void sub_23F6E0(void);
extern void sub_23F770(void);
extern void sub_23F9A0(void);
extern void sub_240A90(void);
extern void sub_240AC0(void);
extern void sub_241810(void);
extern void sub_241870(void);
extern void sub_241A20(void);
extern void sub_241EB0(void);
extern void sub_2422B0(void);
extern void sub_2422E0(void);
extern void sub_242910(void);
extern void _rwaWaveDefCloseModule(void);
extern void _rwaLListModuleOpen(void);
extern void sub_2434C0(void);
extern void sub_243900(void);
extern void sub_243A80(void);
extern void sub_243B40(void);
extern void sub_243F90(void);
extern void sub_244220(void);
extern void sub_244510(void);
extern void sub_244790(void);
extern void sub_244880(void);
extern void sub_2448D0(void);
extern void sub_244920(void);
extern void sub_244970(void);
extern void sub_2449B0(void);
extern void _rwaRwStreamCacheOpenModule(void);
extern void sub_244AA0(void);
extern void sub_2451F0(void);
typedef RwBool (*rwaOpenFunc)(void);
// Its data definitions (PLAN M5), in the image's address order.
// 0x0042E628
rwaModule unk_42E628[17] = {
    { sub_23E1C0, sub_23E220 },
    { sub_2451F0, nullsub_6 },
    { sub_243A80, sub_243900 },
    { sub_244220, sub_244510 },
    { sub_240A90, sub_240AC0 },
    { _rwaLListModuleOpen, sub_2434C0 },
    { sub_241EB0, sub_241A20 },
    { sub_23E0C0, _rwaObjDefCloseModule },
    { sub_23F6E0, _rwaObjCloseModule },
    { sub_243B40, sub_243F90 },
    { sub_242910, _rwaWaveDefCloseModule },
    { sub_23CA00, sub_2422E0 },
    { sub_2422B0, sub_23CB80 },
    { sub_23E5C0, sub_23E600 },
    { _rwaRwStreamCacheOpenModule, sub_244AA0 },
    { sub_23F770, sub_23F9A0 },
    { sub_244970, sub_2449B0 },
};
// 0x0042E6B0
rwaOpenFunc unk_42E6B0[1] = {
    sub_23D690,
};
// 0x0042E6B4
rwaOpenFunc unk_42E6B4[3] = {
    sub_2448D0,
    RwaListenerInterfaceRegister,
    RwaVoice3DInterfaceRegister,
};
// 0x0042E6C0
rwaOpenFunc unk_42E6C0[1] = {
    sub_244880,
};
// 0x0042E6C4
rwaOpenFunc unk_42E6C4[1] = {
    sub_23CC40,
};
// 0x0042E6C8
rwaOpenFunc unk_42E6C8[3] = {
    sub_244920,
    sub_241810,
    sub_241870,
};
// 0x0042E6D4
rwaOpenFunc unk_42E6D4[1] = {
    sub_244790,
};
// 0x005069A8
RwUInt32 dword_5069A8;
// 0x005069AC
RwUInt32 dword_5069AC;
// 0x005069B4
RwUInt32 dword_5069B4;
// 0x005069B8
RwUInt32 dword_5069B8;
// 0x005069BC
RwUInt32 dword_5069BC;
// 0x005069C0
rwaLink dword_5069C0;
// 0x005069C8
rwaLink dword_5069C8;
// 0x005069D4
RwUInt32 dword_5069D4;
// 0x005069FC
RwUInt32 dword_5069FC;
// 0x00516C5C
RwUInt32 dword_516C5C;

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
// End of its data definitions.

// match: _unk_42E6B0 @ 0x0042E6B0


// match: _unk_42E6B4 @ 0x0042E6B4


// match: _unk_42E6C0 @ 0x0042E6C0


// match: _unk_42E6C4 @ 0x0042E6C4


// match: _unk_42E6C8 @ 0x0042E6C8


// match: _unk_42E6D4 @ 0x0042E6D4

// match: _sub_23E220 @ 0x0023E220

void
sub_23E220(void)
{
    if (!dword_5069BC)
    {
        RwEngineStop();
        RwEngineClose();
        RwEngineTerm();
    }
}

extern RwMemoryFunctions *RwOsGetMemoryInterface(void);
extern RwInt32 sub_242240(RwMemoryFunctions *memFuncs);

// match: _sub_23E240 @ 0x0023E240
static RwBool
sub_23E240(rwaModule *modules, RwUInt32 count, rwaModuleCallBack closeCallBack, rwaModuleCallBack openCallBack)
{
    RwUInt32    i;
    RwBool      result;

    for (i = 0; i < count;)
    {
        result = modules[i].open();
        if (!result)
        {
            goto failed;
        }

        if (openCallBack)
        {
            result = openCallBack(&modules[i], i);
        }

        i++;
        if (!result)
        {
            goto failed;
        }
    }

    return TRUE;

  failed:

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

extern void nullsub_6(void);

// match: _sub_23E2B0 @ 0x0023E2B0
static void
sub_23E2B0(rwaModule *modules, RwUInt32 count, rwaModuleCallBack closeCallBack)
{
    RwUInt32    i;

    for (i = count; i > 0; i--)
    {
        modules[i - 1].close();
        if (closeCallBack)
        {
            closeCallBack(&modules[i - 1], i - 1);
        }
    }
}

extern RwUInt32 dword_5069B4;
extern RwUInt32 dword_5069B8;
void sub_23E610(void);
extern rwaInstance *sub_23F2F0(void);
extern rwaInstance *sub_23F0D0(rwaInstance *obj, RwBool skipSelf);
extern rwaInstance *sub_23F140(rwaInstance *obj, RwBool skipSelf);
extern void sub_23EBD0(void);

// match: _sub_23E2E0 @ 0x0023E2E0
RwBool
sub_23E2E0(rwaModule *module, RwUInt32 index)
{
    if (module->open == sub_23E1C0)
    {
        if (!memFuncs)
        {
            memFuncs = RwOsGetMemoryInterface();
        }

        return sub_242240(memFuncs) == 1;
    }

    return TRUE;
}

// match: _sub_23E320 @ 0x0023E320
void
sub_23E320(rwaModule *module, RwUInt32 index)
{
    if (module->close == sub_23E220)
    {
        nullsub_6();
    }
}

extern RwBool _rwaWaveDefUnregister(rwaOpenFunc *funcs, RwUInt32 count);
extern rwaOpenFunc unk_42E6B0[];
extern rwaOpenFunc unk_42E6B4[];
extern rwaOpenFunc unk_42E6C0[];
extern rwaOpenFunc unk_42E6C4[];
extern rwaOpenFunc unk_42E6C8[];
extern rwaOpenFunc unk_42E6D4[];

// match: _RwaCoreUpdateStart @ 0x0023E340
void
RwaCoreUpdateStart(void)
{
    dword_5069B8 = 1;
    sub_23E610();
    sub_23F0D0(sub_23F2F0(), FALSE);
    sub_23EBD0();
}

// match: _RwaCoreUpdateFinish @ 0x0023E370
void
RwaCoreUpdateFinish(void)
{
    sub_23F140(sub_23F2F0(), FALSE);
    dword_5069B8 = 0;
    dword_5069B4++;
}

extern RwUInt32 dword_516C5C;

// match: _sub_23E3A0 @ 0x0023E3A0
RwBool
sub_23E3A0(void)
{
    if (_rwaWaveDefUnregister(unk_42E6B4, 3) != TRUE ||
        _rwaWaveDefUnregister(unk_42E6B0, 1) != TRUE ||
        _rwaWaveDefUnregister(unk_42E6C0, 1) != TRUE)
    {
        return FALSE;
    }

    return TRUE;
}

// match: _sub_23E3E0 @ 0x0023E3E0
RwBool
sub_23E3E0(void)
{
    if (_rwaWaveDefUnregister(unk_42E6C8, 3) != TRUE ||
        _rwaWaveDefUnregister(unk_42E6C4, 1) != TRUE ||
        _rwaWaveDefUnregister(unk_42E6D4, 1) != TRUE)
    {
        return FALSE;
    }

    return TRUE;
}

extern rwaModule unk_42E628[];
extern RwUInt32 dword_5069A8;
extern RwUInt32 dword_5069AC;

// match: _sub_23E420 @ 0x0023E420
RwUInt32
sub_23E420(RwUInt32 size)
{
    if (size < 0x10)
    {
        dword_516C5C = 0x10;

        return 0x10;
    }

    dword_516C5C = size;

    return size;
}

// match: _sub_23E440 @ 0x0023E440
RwInt32
sub_23E440(RwInt32 format)
{
    switch (format)
    {
        case 1:
        case 2:
            return 1;
        case 4:
        case 8:
            return 2;
        case 0x10:
        case 0x20:
            return 4;
        case 0x40:
        case 0x80:
            return 8;
        case 0x100:
        case 0x200:
            return 0x10;
        case 0x400:
            return 4;
        case 0x800:
            return 4;
        case 0x1000:
            return 4;
        case 0x2000:
            return 4;
    }

    return 0;
}

extern rwaLink dword_5069C0;
extern rwaLink dword_5069C8;
extern RwUInt32 dword_5069D4;
extern void *RwaVirtualVoiceRegister(void);
extern RwInt32 RwaListenerUnregister(void);

// match: _RwaCoreOpen @ 0x0023E510
RwBool
RwaCoreOpen(RwMemoryFunctions *memoryFunctions, RwBool usingRwGraphics)
{
    sub_23E420(0x10);
    dword_5069BC = usingRwGraphics;
    memFuncs = memoryFunctions;

    if (sub_23E240(unk_42E628, 17, (rwaModuleCallBack)sub_23E320, (rwaModuleCallBack)sub_23E2E0) == TRUE)
    {
        dword_5069B8 = 0;
        dword_5069B4 = 0;
        dword_5069A8 = 1;
        return TRUE;
    }
    return FALSE;
}

// match: _RwaCoreClose @ 0x0023E570
void
RwaCoreClose(void)
{
    dword_5069AC = 1;
    if (dword_5069B8 == 1)
    {
        RwaCoreUpdateFinish();
    }

    sub_23E2B0(unk_42E628, 17, (rwaModuleCallBack)sub_23E320);
    dword_5069A8 = 0;
    dword_5069AC = 0;
}

extern RwUInt32 dword_5069F8;
extern RwUInt32 dword_5069FC;
extern RwUInt32 sub_244940(void);
extern RwUInt32 sub_244960(void);

// match: _RwaCoreUpdate @ 0x0023E5B0
void
RwaCoreUpdate(void)
{
    RwaCoreUpdateStart();
    RwaCoreUpdateFinish();
}

// match: _sub_23E5C0 @ 0x0023E5C0
RwBool
sub_23E5C0(void)
{
    dword_5069C8.next = &dword_5069C8;
    dword_5069C8.prev = &dword_5069C8;
    dword_5069D4 = 1;
    dword_5069C0.next = &dword_5069C0;
    dword_5069C0.prev = &dword_5069C0;
    RwaVirtualVoiceRegister();

    return TRUE;
}

// match: _sub_23E600 @ 0x0023E600
void
sub_23E600(void)
{
    RwaListenerUnregister();
    dword_5069D4 = 0;
}


