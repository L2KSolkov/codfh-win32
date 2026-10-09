/*
 * codfh-match: RenderWare Audio's voice manager (rwavoicemanager.c in the
 * library's PS2 header, docs/reference/rwacore_ps2.h): the virtual voices'
 * free and active lists (heads 0x5069C8 and 0x5069C0), their priorities
 * from the listener distance and their binding to real voices.
 */
#include "rwa.h"
#include "rwaint.h"



/* The square root through the library's table (0x42F1A0): the exponent is
 * halved and the mantissa's top bits looked up. */
#define rwaSqrtMacro(_root, _input)                                         \
    if ((_input) != 0.0f)                                                   \
    {                                                                       \
        RwUInt32    _bits = *(RwUInt32 *)&(_input);                         \
        RwInt16     _exp = (RwInt16)((_bits >> 23) - 127);                  \
        RwUInt32    _mant = _bits & 0x7FFFFF;                               \
                                                                            \
        if (_exp & 1)                                                       \
        {                                                                   \
            _mant |= 0x800000;                                              \
        }                                                                   \
                                                                            \
        _exp >>= 1;                                                         \
        *(RwUInt32 *)(_root) = ((RwUInt32)(RwInt32)word_42F1A0[_mant >> 16] << 16) | \
                               ((RwUInt32)(_exp + 127) << 23);              \
    }

extern RwInt16 word_42F1A0[];

/* The active and free voice lists: rwabase.c's (RwaCoreOpen links them empty). */
extern rwaLink dword_5069C0;    /* active voices */
extern rwaLink dword_5069C8;    /* free voices */
static RwUInt32 dword_5069D8;
static void **dword_5069D0;
static RwaObjHandle *dword_5069DC;
static RwInt32 dword_5069E0;
static RwInt32 dword_5069E4;
static RwInt32 dword_5069E8;
static RwaV3d dword_5069EC;     /* listener position */
extern RwReal dword_42E6D8;     /* rolloff */
extern RwUInt32 dword_5069F8;   /* time */

extern RwInt32 sub_23F940(RwaObjHandle *handle, RwInt32 param, RwInt32 type, void *value);
extern void DSPResource_Release(void *resource, RwInt32 a);
extern void sub_2421B0(void *data);
extern void RwaObjHandleSetParamUInt8(RwaObjHandle *handle, RwInt32 param, RwInt32 type, RwUInt32 value);

#define rwaVoiceLink(_sound) ((rwaLink *)(_sound))

/* Original Sub and Dot macros from RWSDK/src/plcore/bavector.h.
 * Preserve the full parentheses for VC7.0 x87 scheduling. */

#define RwaV3dSubMacro(o, a, b)                                  \
do                                                     \
{                                                               \
    (o)->x = (((a)->x) - ( (b)->x));                            \
    (o)->y = (((a)->y) - ( (b)->y));                            \
    (o)->z = (((a)->z) - ( (b)->z));                            \
}                                                               \
while(0)

#define RwaV3dDotProductMacro(a, b)                              \
    ((((( (((a)->x) * ((b)->x))) +                              \
        ( (((a)->y) * ((b)->y))))) +                            \
        ( (((a)->z) * ((b)->z)))))


#define rwaReal(_field) (*(RwReal *)&(_field))

/* Priority comparison: inline with no address, named for its operation.
 * Evidence: sub_23E980 loads the candidate priority before the sound's;
 * pointer operands preserve that order without changing shared field types. */
static __forceinline RwBool
priorityLess(const RwReal *a, const RwReal *b)
{
    return *a < *b;
}

extern RwUInt32 sub_23F960(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, RwBool *success);
extern RwUInt32 sub_2433C0(const RwaWaveFormat *format, RwUInt32 size);
extern RwaObjHandle *Behavior_DispatchCallback(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *value);
/* The shared scalar setter takes float bits here. Evidence: sub_23EBD0
 * passes these values with x87 loads/stores to a by-value argument. */
#define rwaSetRealParam(h,p,v) ((void (*)(RwaObjHandle *, RwInt32, RwInt32, RwReal))RwaObjHandleSetParamUInt8)(h,p,1,v)


extern const RwaUUID unk_3ED7A4;
extern const RwaUUID unk_3ED3CC;
extern RwaObjInterfaceDef *sub_243F40(const RwaUUID *uuid);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void *sub_23E680(RwUInt32 amount, void *data);
extern RwaObjHandle *sub_23F9F0(rwaInstance *obj, void *objInterface, rwaHandleParams *params);

// Its data (PLAN M5): literals, constants and tables where the image has them.

// Its data definitions (PLAN M5), in the image's address order.
// 0x0042E6D8
RwReal dword_42E6D8 = 10.0f;
// 0x0042E6DC
void *unk_42E6DC[7] =
{
    (void *)0x636E7546,
    (void *)0x6E6F6974,
    (void *)0x20732520,
    (void *)0x20746F6E,
    (void *)0x6C706D69,
    (void *)0x6E656D65,
    (void *)0x646574,
};
// 0x005069F8
RwUInt32 dword_5069F8;
// End of its data definitions.

// match: _dword_42E6D8 @ 0x0042E6D8


// match: _unk_42E6DC @ 0x0042E6DC



// match: _sub_23E690 @ 0x0023E690
// sp-match: _sub_23E690 @ 0x00150680

RwBool
sub_23E690(rwaInstance *output, rwaInstance **voices, RwInt32 count)
{
    RwUInt32 voiceSize;
    RwUInt8 *memory;
    RwaObjInterfaceDef *outputInterface = sub_243F40(&unk_3ED7A4);
    RwaObjInterfaceDef *voiceInterface = sub_243F40(&unk_3ED3CC);
    RwUInt32 handleBytes = (count + 1) * sizeof(RwaObjHandle);
    RwUInt32 arrayBytes = count * sizeof(RwaObjHandle *);
    RwUInt32 size;
    RwUInt32 outputSize;
    /* Reuse size for the initial input count before forming the total.
     * Keep the qualified voice-output read; original qualification is unknown. */
    size = outputInterface->noInputs;
    outputSize = (outputInterface->noOutputs + size) * sizeof(rwaParamFunc)
                 + sizeof(rwaObjInterface);
    voiceSize = voiceInterface->noInputs * sizeof(rwaParamFunc)
        + *(volatile RwUInt16 *)&voiceInterface->noOutputs * sizeof(rwaParamFunc)
        + sizeof(rwaObjInterface) + 12;
    size = handleBytes + outputSize + voiceSize + arrayBytes;
    memory = (RwUInt8 *)sub_242170(size, rwaMEMHINTDUR_EVENT | rwaID_80D);

    if (!memory) return FALSE;
    {
        rwaHandleParams params;
        rwaHandleList list;
        RwUInt8 *cursor;
        RwUInt32 i;

        params.flags = 2;
        params.unk08 = 0;
        params.unk04 = 0;
        params.unk0C = (RwUInt32)sub_23E680;
        params.unk10 = (RwUInt32)&cursor;
        params.handle = (RwaObjHandle *)memory;
        cursor = memory + sizeof(RwaObjHandle);
        dword_5069DC = sub_23F9F0(output, outputInterface, &params);
        if (!dword_5069DC)
        {
            sub_2421B0(memory);
            return FALSE;
        }

        memory = cursor;
        dword_5069D0 = (void **)memory;
        memory += arrayBytes;
        for (i = 0; i < count; ++i)
        {
            params.handle = (RwaObjHandle *)memory;
            cursor = memory + sizeof(RwaObjHandle);
            dword_5069D0[i] = sub_23F9F0(voices[i], voiceInterface, &params);
            if (!dword_5069D0[i])
            {
                while (i--)
                {
                    DSPResource_Release(dword_5069D0[i], 0);
                }
                DSPResource_Release(dword_5069DC, 0);
                dword_5069E0 = 0;
                dword_5069DC = NULL;
                return FALSE;
            }
            memory = cursor;
        }

        dword_5069D8 = 1;
        dword_5069E0 = count;
        list.count = count;
        list.handles = (RwaObjHandle **)dword_5069D0;
        sub_23F940(dword_5069DC, 5, 1, &list);
        return TRUE;

    }
}

// match: _DSPResourceMgr_Shutdown @ 0x0023E830
void
DSPResourceMgr_Shutdown(void)
{
    RwInt32         i;
    RwaObjHandle   *handle;

    sub_23F940(dword_5069DC, 5, 1, NULL);

    for (i = 0; i < dword_5069E0; i++)
    {
        DSPResource_Release(dword_5069D0[i], 0);
    }

    handle = dword_5069DC;
    DSPResource_Release(handle, 0);
    sub_2421B0(handle);

    dword_5069D8 = 0;
    dword_5069E0 = 0;
}

// match: _sub_23E8A0 @ 0x0023E8A0
// sp-match: _sub_23E8A0 @ 0x00150820
RwBool
sub_23E8A0(rwaEmitter *emitter)
{
    rwaSound   *sound = &emitter->sound;

    rwaVoiceLink(sound)->prev = NULL;
    rwaVoiceLink(sound)->next = NULL;
    rwaVoiceLink(sound)->next = dword_5069C8.next;
    rwaVoiceLink(sound)->prev = &dword_5069C8;
    dword_5069C8.next->prev = rwaVoiceLink(sound);
    dword_5069C8.next = rwaVoiceLink(sound);

    sound->flags &= ~1;

    return TRUE;
}

// match: _sub_23E8E0 @ 0x0023E8E0
// sp-match: _sub_23E8E0 @ 0x00150860
static void
sub_23E8E0(rwaSound *sound)
{
    if (sound->flags & 1)
    {
        RwaObjHandle   *handle;

        sound->prev->next = sound->next;
        sound->next->prev = sound->prev;

        handle = sound->handle;
        if (handle)
        {
            RwaObjHandleSetParamUInt8(handle, 6, 1, 0);
            sub_23F940(handle, 9, 1, NULL);
            sound->handle = NULL;
        }

        rwaVoiceLink(sound)->next = dword_5069C8.next;
        rwaVoiceLink(sound)->prev = &dword_5069C8;
        dword_5069C8.next->prev = rwaVoiceLink(sound);
        dword_5069C8.next = rwaVoiceLink(sound);

        dword_5069E4--;
        dword_5069E8 -= sound->unk38;
        sound->unk48 = sound->unk4C;
        sound->flags &= ~3;
        sound->unk80 = 0;
        sound->unk38 = 0;
    }
}




// match: _sub_23E980 @ 0x0023E980
// sp-match: _sub_23E980 @ 0x00150900
static void
sub_23E980(rwaSound *sound)
{
    rwaReal(sound->unk80) = 0.0f;

    if (rwaReal(sound->unk40) > 0.0f)
    {
        RwReal  volume;

        RwUInt32 maxDistanceBits;
        RwUInt32 minDistanceBits;
        RwaV3d delta;
        RwReal distance;
        if (!(((rwaVoiceWave *)sound->unk50)->flags & 2))
        {
            goto unity;
        }
        minDistanceBits = sound->unk70;
        maxDistanceBits = sound->unk74;
            RwaV3dSubMacro(&delta, &dword_5069EC, &sound->unk58);
            distance = RwaV3dDotProductMacro(&delta, &delta);

            if (!(rwaReal(maxDistanceBits) * rwaReal(maxDistanceBits) > distance))
            {
                goto prioritised;
            }

            rwaSqrtMacro(&distance, distance);

        if (distance < rwaReal(minDistanceBits))
        {
            goto unity;
        }
        {
                RwReal  beyond = distance - rwaReal(minDistanceBits);
                RwReal  range = rwaReal(maxDistanceBits) - rwaReal(minDistanceBits);

                volume = (range - beyond) / (dword_42E6D8 * beyond + range) * rwaReal(sound->unk40);
                if (!(volume > 0.0f))
                {
                    goto prioritised;
                }
        }
        goto weighted;
unity:
        volume = 1.0f;
weighted:

        rwaReal(sound->unk80) = (1.0f - rwaReal(sound->unk7C)) * volume +
                                rwaReal(sound->unk78) * rwaReal(sound->unk7C);
    }

prioritised:
    if (sound->flags & 1)
    {
        RwReal      priority = rwaReal(sound->unk80);
        rwaSound   *node = sound;

        for (;;)
        {
            rwaSound   *next = node->next;
            rwaSound   *prev = node->prev;
            RwReal      nextPriority;
            RwUInt32 prevPriorityBits;

            nextPriority = (rwaLink *)next == &dword_5069C0 ? 2.0f : rwaReal(next->unk80);
            prevPriorityBits = (rwaLink *)prev == &dword_5069C0 ? 0xBF800000 : prev->unk80;

            if (priority > nextPriority)
            {
                node = next;
            }
            else if (priority < rwaReal(prevPriorityBits))
            {
                node = prev;
            }
            else
            {
                break;
            }
        }

        if (node != sound)
        {
            sound->prev->next = sound->next;
            sound->next->prev = sound->prev;
            sound->prev = node->prev;
            sound->next = node;
            node->prev->next = sound;
            node->prev = sound;
        }

        goto listed;
    }
    else
    {
        rwaLink    *cur;

        sound->prev->next = sound->next;
        sound->next->prev = sound->prev;

        for (cur = dword_5069C0.next; cur != &dword_5069C0; cur = cur->next)
        {
            if (priorityLess((const RwReal *)&sound->unk80, (const RwReal *)&((rwaSound *)cur)->unk80))
            {
                break;
            }
        }

        if (cur == &dword_5069C0)
        {
            sound->prev = (rwaSound *)dword_5069C0.prev;
            sound->next = (rwaSound *)&dword_5069C0;
            dword_5069C0.prev->next = rwaVoiceLink(sound);
            dword_5069C0.prev = rwaVoiceLink(sound);
        }
        else
        {
            sound->prev = (rwaSound *)cur->prev;
            sound->next = (rwaSound *)cur;
            cur->prev->next = rwaVoiceLink(sound);
            cur->prev = rwaVoiceLink(sound);
        }
    }
listed:
    sound->flags |= 1;
}

// match: _sub_23EBD0 @ 0x0023EBD0
// sp-match: _sub_23EBD0 @ 0x00150B50
void
sub_23EBD0(void)
{
    if (dword_5069DC)
    {
        rwaListener *listener = (rwaListener *)sub_23F960(dword_5069DC, 1, 2, NULL);
        rwaSound *sound;
        RwInt32 used;

        if (listener)
        {
            dword_5069EC = listener->pos;
            *(RwUInt32 *)&dword_42E6D8 = listener->unk64;
        }

        used = 0;
        for (sound = (rwaSound *)dword_5069C0.next; (rwaLink *)sound != &dword_5069C0; )
        {
            RwaObjHandle *handle = sound->handle;
            rwaSound *next = sound->next;

            if (used < dword_5069E8 - dword_5069E0)
            {
                if (sound->flags & 0x10)
                {
                    sub_23E8E0(sound);
                }
                else if (handle)
                {
                    if (sound->flags & 8)
                    {
                        sound->unk48 = sound->unk4C;
                    }
                    else
                    {
                        sound->unk48 = sub_23F960(handle, 7, 2, NULL);
                    }
                    RwaObjHandleSetParamUInt8(handle, 6, 1, 0);
                    sub_23F940(handle, 9, 1, NULL);
                    sound->unk54 = dword_5069F8;
                    sound->handle = NULL;
                }
                if ((sound->flags & 1) && !(sound->flags & 8))
                {
                    RwaWave *wave = (RwaWave *)sound->unk50;
                    RwUInt32 length = sub_2433C0(&wave->format, wave->format.length);
                    sound->unk48 += (RwUInt32)((RwReal)(dword_5069F8 - sound->unk54) * sound->unk3C * 0.001f);
                    if (sound->unk48 >= length)
                    {
                        if (sound->flags & 4)
                        {
                            while (sound->unk48 >= length)
                            {
                                sound->unk48 -= length;
                            }
                        }
                        else
                        {
                            sub_23E8E0(sound);
                            sound->handle = NULL;
                        }
                    }
                    sound->unk54 = dword_5069F8;
                }
            }
            else if (!handle)
            {
                handle = (RwaObjHandle *)sub_23F960(dword_5069DC, 4, 2, NULL);
                sound->handle = handle;
                if (handle)
                {
                    sub_23F940(handle, 9, 1, sound->unk50);
                    rwaSetRealParam(handle, 4, sound->unk3C);
                    rwaSetRealParam(handle, 5, rwaReal(sound->unk40));
                    RwaObjHandleSetParamUInt8(handle, 8, 1, (sound->flags >> 2) & 1);
                    if (!(sound->flags & 8))
                    {
                        RwaObjHandleSetParamUInt8(handle, 7, 1, sound->unk48);
                    }
                    rwaSetRealParam(handle, 10, rwaReal(sound->unk44));
                    Behavior_DispatchCallback(handle, 0, 1, &sound->unk58);
                    Behavior_DispatchCallback(handle, 1, 1, &sound->unk64);
                    rwaSetRealParam(handle, 2, rwaReal(sound->unk70));
                    rwaSetRealParam(handle, 3, rwaReal(sound->unk74));
                    rwaSetRealParam(handle, 11, rwaReal(sound->unk88));
                    RwaObjHandleSetParamUInt8(handle, 6, 1, 1);
                }
            }
            used += sound->unk38;
            sound = next;
        }
    }
}

// match: _sub_23EE70 @ 0x0023EE70
// sp-match: _sub_23EE70 @ 0x00150DF0
static void
sub_23EE70(rwaSound *sound)
{
    if (sound->flags & 1)
    {
        sub_23E8E0(sound);
    }

    sub_23E980(sound);

    sound->unk38 = 1;
    sound->flags |= 2;
    sound->unk4C = 0;
    dword_5069E8++;
    dword_5069E4++;
}

// match: _SoundStopper_Transition @ 0x0023EEC0
// sp-match: _SoundStopper_Transition @ 0x00150E40
void
SoundStopper_Transition(rwaSound *sound, RwInt32 state)
{
    switch (state)
    {
        case 0:
            sub_23EE70(sound);
            break;
        case 1:
            sub_23E8E0(sound);
            break;
        case 2:
            if (sound->flags & 1)
            {
                sub_23E980(sound);
            }
            break;
    }
}
