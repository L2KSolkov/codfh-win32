/*
 * codfh-match: RenderWare Audio's virtual voice object (rwavirtualvoiceobj.c
 * in the library's PS2 header, docs/reference/rwacore_ps2.h): its creation,
 * stop and parameter handlers. The handlers are reached only through the
 * parameter table at 0x42E1C8 ({parameter id, 0, 0, type id, 1, handler});
 * the parameters are the header's virtual voice inputs and outputs
 * (frequency, gain, trigger, wave position, loop, wave, pan, priority, bias,
 * position, velocity, distances).
 */
#include <string.h>

#include "rwa.h"
#include "rwaint.h"


extern RwUInt8 unk_506798[];
extern RwUInt32 dword_5067FC;
extern RwUInt32 dword_5069F8;

extern RwInt32 sub_23F4C0(void *module, RwInt32 a, RwInt32 b, RwInt32 c, RwInt32 d, RwInt32 e);
extern RwBool sub_2418D0(void);
extern RwInt32 sub_23DB90(void *module);
extern void sub_23E8A0(rwaEmitter *emitter);
extern void SoundStopper_Transition(rwaSound *sound, RwInt32 state);
extern RwInt32 sub_23F960(RwaObjHandle *handle, RwInt32 param, RwInt32 type, RwInt32 value);
extern RwInt32 sub_23F940(RwaObjHandle *handle, RwInt32 param, RwInt32 type, void *value);
extern void Behavior_DispatchCallback(RwaObjHandle *handle, RwInt32 param, RwInt32 type, const void *value);
extern void RwaObjHandleSetParamUInt8(RwaObjHandle *handle, RwInt32 param, RwInt32 type, RwUInt32 value);

void sub_23B8F0(rwaEmitter *emitter, rwaWave *wave);
void SoundEmitter_Stop(rwaEmitter *emitter, RwInt32 now);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED218 @ 0x003ED218
// match: _unk_3ED228 @ 0x003ED228
// match: _unk_3ED238 @ 0x003ED238

// What its data definitions name.
rwaEmitter *sub_23B950(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23B960(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23B970(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23B980(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23B990(rwaEmitter *emitter, const RwaUUID *param, const RwaV3d *value);
rwaEmitter *sub_23B9D0(rwaEmitter *emitter, const RwaUUID *param, const RwaV3d *value);
rwaEmitter *sub_23BA10(rwaEmitter *emitter, const RwaUUID *param, RwaV3d *value);
rwaEmitter *sub_23BA30(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BA60(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BA70(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BAA0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BAB0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BAE0(rwaEmitter *emitter, const RwaUUID *param, RwReal *value);
rwaEmitter *sub_23BAF0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BB20(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BB30(rwaEmitter *emitter, const RwaUUID *param, const RwInt32 *value);
rwaEmitter *sub_23BB50(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BB70(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BBA0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BBE0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BC20(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BC40(rwaEmitter *emitter, const RwaUUID *param, rwaWave *value);
rwaEmitter *sub_23BC60(rwaEmitter *emitter, const RwaUUID *param, void **value);
rwaEmitter *sub_23BC70(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BCA0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BCB0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
rwaEmitter *sub_23BCC0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value);
rwaEmitter *sub_23BCF0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value);
extern void sub_23D3A0(void);
extern RwUInt8 unk_3ED2BC[];
extern RwUInt8 unk_3ED2CC[];
extern RwUInt8 unk_3ED2DC[];
extern RwUInt8 unk_3ED2EC[];
extern RwUInt8 unk_3ED2FC[];
extern RwUInt8 unk_3ED30C[];
extern RwUInt8 unk_3ED31C[];
extern RwUInt8 unk_3ED32C[];
extern RwUInt8 unk_3ED33C[];
extern RwUInt8 unk_3ED34C[];
extern RwUInt8 unk_3ED35C[];
extern RwUInt8 unk_3ED36C[];
extern RwUInt8 unk_3ED37C[];
extern RwUInt8 unk_3ED38C[];
extern RwUInt8 unk_3ED39C[];
extern RwUInt8 unk_3ED3AC[];
extern RwUInt8 unk_3ED3BC[];
extern RwUInt8 unk_3ED3DC[];
extern RwUInt8 unk_3ED3EC[];
extern RwUInt8 unk_3ED3FC[];
extern RwUInt8 unk_3ED40C[];
extern RwUInt8 unk_3ED41C[];
extern RwUInt8 unk_3ED42C[];
extern RwUInt8 unk_3ED43C[];
extern RwUInt8 unk_3ED44C[];
extern RwUInt8 unk_3ED46C[];
extern RwUInt8 unk_3ED47C[];
extern RwUInt8 unk_3ED48C[];
extern RwUInt8 unk_3ED49C[];
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED54C[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED218
const RwaUUID unk_3ED218 = { 0x31103D6C, 0x684A, 0x4F16, { 0x98, 0xBC, 0x3D, 0x66, 0x52, 0x58, 0x78, 0xFA } };
// 0x003ED228
const RwaUUID unk_3ED228 = { 0xAAEAC9AC, 0xFC38, 0x4917, { 0xAE, 0x81, 0x64, 0xEA, 0xDB, 0xC7, 0x93, 0x53 } };
// 0x003ED238
const RwaUUID unk_3ED238 = { 0x44E50A10, 0x08BA, 0x4250, { 0xB9, 0x71, 0x69, 0xE9, 0x21, 0xB9, 0xCF, 0x4F } };
// 0x0042E1C8
void *unk_42E1C8[84] =
{
    (void *)&unk_3ED46C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23B950,
    (void *)&unk_3ED48C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23B970,
    (void *)&unk_3ED3DC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23B990,
    (void *)&unk_3ED3FC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23B9D0,
    (void *)&unk_3ED41C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BA30,
    (void *)&unk_3ED43C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BA70,
    (void *)&unk_3ED2BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BAB0,
    (void *)&unk_3ED2DC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BAF0,
    (void *)&unk_3ED2FC,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_23BB30,
    (void *)&unk_3ED31C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_23BB70,
    (void *)&unk_3ED33C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_23BBE0,
    (void *)&unk_3ED35C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_23BC40,
    (void *)&unk_3ED37C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BC70,
    (void *)&unk_3ED3AC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BCC0,
};
// 0x0042E318
void *unk_42E318[90] =
{
    (void *)&unk_3ED47C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23B960,
    (void *)&unk_3ED49C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23B980,
    (void *)&unk_3ED3EC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D3A0,
    (void *)&unk_3ED40C,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23BA10,
    (void *)&unk_3ED42C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BA60,
    (void *)&unk_3ED44C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BAA0,
    (void *)&unk_3ED2CC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BAE0,
    (void *)&unk_3ED2EC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BB20,
    (void *)&unk_3ED30C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_23BB50,
    (void *)&unk_3ED32C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_23BBA0,
    (void *)&unk_3ED34C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_23BC20,
    (void *)&unk_3ED36C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_23BC60,
    (void *)&unk_3ED38C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BCA0,
    (void *)&unk_3ED39C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_23BCB0,
    (void *)&unk_3ED3BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23BCF0,
};
// 0x00506780
RwUInt8 unk_506780[24];
// 0x00506798
RwUInt8 unk_506798[92];
// 0x005067F4
RwUInt8 unk_5067F4[8];
// 0x005067FC
RwUInt32 dword_5067FC;
// End of its data definitions.


// match: _unk_42E1C8 @ 0x0042E1C8


// match: _unk_42E318 @ 0x0042E318

// match: _RwaStreamCreate @ 0x0023B750

RwInt32
RwaStreamCreate(RwInt32 a, RwInt32 b, RwInt32 c, RwInt32 d, RwInt32 e)
{
    return sub_23F4C0(unk_506798, a, c, b, d, e);
}

// match: _RwaListenerUnregister @ 0x0023B780
RwInt32
RwaListenerUnregister(void)
{
    if (dword_5067FC)
    {
        if (!sub_2418D0())
        {
            return 0;
        }

        dword_5067FC = 0;
    }

    return sub_23DB90(unk_506798);
}

// match: _sub_23B7B0 @ 0x0023B7B0
rwaEmitter *
sub_23B7B0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *flags)
{
    rwaSound   *sound = &emitter->sound;

    memset(sound, 0, sizeof(rwaSound));
    sound->prev = NULL;
    sound->next = NULL;

    sub_23E8A0(emitter);

    sound->flags = *flags & 0x18;
    sound->unk40 = 0x3F800000;
    sound->unk70 = 0x3F800000;
    sound->unk44 = 0;
    sound->unk54 = 0;
    sound->unk48 = 0;
    sound->unk4C = 0;
    sound->unk80 = 0;
    sound->handle = NULL;
    sound->unk84 = 0;
    sound->unk78 = 0x3F000000;
    sound->unk7C = 0x3F000000;
    sound->unk3C = 22050.0f;
    sound->unk74 = 0x461C4000;

    return emitter;
}

// match: _sub_23B820 @ 0x0023B820
void
sub_23B820(rwaEmitter *emitter)
{
    rwaSound   *sound = &emitter->sound;

    SoundStopper_Transition(sound, 1);

    if (sound->next)
    {
        emitter->sound.prev->next = sound->next;
        sound->next->prev = emitter->sound.prev;
    }
}

// match: _sub_23B850 @ 0x0023B850
rwaEmitter *
sub_23B850(rwaEmitter *emitter)
{
    rwaSound   *sound = &emitter->sound;

    if (sound->flags & 2)
    {
        RwInt32 state = 2;

        if (sound->handle)
        {
            if (!sub_23F960(sound->handle, 6, 2, 0))
            {
                state = 1;
            }
        }

        SoundStopper_Transition(sound, state);
    }

    sound->unk84 = 0;

    return emitter;
}

// match: _sub_23B8A0 @ 0x0023B8A0
rwaEmitter *
sub_23B8A0(rwaEmitter *emitter, RwUInt32 *value)
{
    *value = 0;

    return emitter;
}

// match: _SoundEmitter_Stop @ 0x0023B8B0
void
SoundEmitter_Stop(rwaEmitter *emitter, RwInt32 now)
{
    if (now)
    {
        SoundStopper_Transition(&emitter->sound, 0);
        emitter->sound.unk54 = dword_5069F8;
    }
    else
    {
        SoundStopper_Transition(&emitter->sound, 1);
    }
}

// match: _sub_23B8F0 @ 0x0023B8F0
void
sub_23B8F0(rwaEmitter *emitter, rwaWave *wave)
{
    if (emitter->sound.unk50)
    {
        emitter->sound.unk50 = NULL;
    }

    if (wave)
    {
        emitter->sound.unk50 = wave;

        if (!emitter->sound.unk84)
        {
            emitter->sound.unk3C = (RwReal)wave->unk2C;
        }
    }

    if (emitter->sound.handle)
    {
        sub_23F940(emitter->sound.handle, 9, 1, emitter->sound.unk50);
    }
}

// match: _sub_23B950 @ 0x0023B950
rwaEmitter *
sub_23B950(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk78 = *value;

    return emitter;
}

// match: _sub_23B960 @ 0x0023B960
rwaEmitter *
sub_23B960(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk78;

    return emitter;
}

// match: _sub_23B970 @ 0x0023B970
rwaEmitter *
sub_23B970(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk7C = *value;

    return emitter;
}

// match: _sub_23B980 @ 0x0023B980
rwaEmitter *
sub_23B980(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk7C;

    return emitter;
}

// match: _sub_23B990 @ 0x0023B990
rwaEmitter *
sub_23B990(rwaEmitter *emitter, const RwaUUID *param, const RwaV3d *value)
{
    emitter->sound.unk58 = *value;

    if (emitter->sound.handle)
    {
        Behavior_DispatchCallback(emitter->sound.handle, 0, 1, value);
    }

    return emitter;
}

// match: _sub_23B9D0 @ 0x0023B9D0
rwaEmitter *
sub_23B9D0(rwaEmitter *emitter, const RwaUUID *param, const RwaV3d *value)
{
    emitter->sound.unk64 = *value;

    if (emitter->sound.handle)
    {
        Behavior_DispatchCallback(emitter->sound.handle, 1, 1, value);
    }

    return emitter;
}

// match: _sub_23BA10 @ 0x0023BA10
rwaEmitter *
sub_23BA10(rwaEmitter *emitter, const RwaUUID *param, RwaV3d *value)
{
    *value = emitter->sound.unk64;

    return emitter;
}

// match: _sub_23BA30 @ 0x0023BA30
rwaEmitter *
sub_23BA30(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk70 = *value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 2, 1, *value);
    }

    return emitter;
}

// match: _sub_23BA60 @ 0x0023BA60
rwaEmitter *
sub_23BA60(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk70;

    return emitter;
}

// match: _sub_23BA70 @ 0x0023BA70
rwaEmitter *
sub_23BA70(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk74 = *value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 3, 1, *value);
    }

    return emitter;
}

// match: _sub_23BAA0 @ 0x0023BAA0
rwaEmitter *
sub_23BAA0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk74;

    return emitter;
}

// match: _sub_23BAB0 @ 0x0023BAB0
rwaEmitter *
sub_23BAB0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk3C = *(const RwReal *)value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 4, 1, *value);
    }

    return emitter;
}

// match: _sub_23BAE0 @ 0x0023BAE0
rwaEmitter *
sub_23BAE0(rwaEmitter *emitter, const RwaUUID *param, RwReal *value)
{
    *value = emitter->sound.unk3C;

    return emitter;
}

// match: _sub_23BAF0 @ 0x0023BAF0
rwaEmitter *
sub_23BAF0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk40 = *value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 5, 1, *value);
    }

    return emitter;
}

// match: _sub_23BB20 @ 0x0023BB20
rwaEmitter *
sub_23BB20(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk40;

    return emitter;
}

// match: _sub_23BB30 @ 0x0023BB30
rwaEmitter *
sub_23BB30(rwaEmitter *emitter, const RwaUUID *param, const RwInt32 *value)
{
    SoundEmitter_Stop(emitter, *value);

    return emitter;
}

// match: _sub_23BB50 @ 0x0023BB50
rwaEmitter *
sub_23BB50(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = (emitter->sound.flags >> 1) & 1;

    return emitter;
}

// match: _sub_23BB70 @ 0x0023BB70
rwaEmitter *
sub_23BB70(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk48 = *value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 7, 1, *value);
    }

    return emitter;
}

// match: _sub_23BBA0 @ 0x0023BBA0
rwaEmitter *
sub_23BBA0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    emitter->sound.unk48 = (emitter->sound.handle && (emitter->sound.flags & 2)) ?
        sub_23F960(emitter->sound.handle, 7, 2, 0) : emitter->sound.unk48;
    *value = emitter->sound.unk48;

    return emitter;
}

// match: _sub_23BBE0 @ 0x0023BBE0
rwaEmitter *
sub_23BBE0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    if (*value)
    {
        emitter->sound.flags |= 4;
    }
    else
    {
        emitter->sound.flags &= ~4;
    }

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 8, 1, *value);
    }

    return emitter;
}

// match: _sub_23BC20 @ 0x0023BC20
rwaEmitter *
sub_23BC20(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = (emitter->sound.flags >> 2) & 1;

    return emitter;
}

// match: _sub_23BC40 @ 0x0023BC40
rwaEmitter *
sub_23BC40(rwaEmitter *emitter, const RwaUUID *param, rwaWave *value)
{
    sub_23B8F0(emitter, value);

    return emitter;
}

// match: _sub_23BC60 @ 0x0023BC60
rwaEmitter *
sub_23BC60(rwaEmitter *emitter, const RwaUUID *param, void **value)
{
    *value = emitter->sound.unk50;

    return emitter;
}

// match: _sub_23BC70 @ 0x0023BC70
rwaEmitter *
sub_23BC70(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk44 = *value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 10, 1, *value);
    }

    return emitter;
}

// match: _sub_23BCA0 @ 0x0023BCA0
rwaEmitter *
sub_23BCA0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk44;

    return emitter;
}

// match: _sub_23BCB0 @ 0x0023BCB0
rwaEmitter *
sub_23BCB0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = 0;

    return emitter;
}

// match: _sub_23BCC0 @ 0x0023BCC0
rwaEmitter *
sub_23BCC0(rwaEmitter *emitter, const RwaUUID *param, const RwUInt32 *value)
{
    emitter->sound.unk88 = *value;

    if (emitter->sound.handle)
    {
        RwaObjHandleSetParamUInt8(emitter->sound.handle, 11, 1, *value);
    }

    return emitter;
}

// match: _sub_23BCF0 @ 0x0023BCF0
rwaEmitter *
sub_23BCF0(rwaEmitter *emitter, const RwaUUID *param, RwUInt32 *value)
{
    *value = emitter->sound.unk88;

    return emitter;
}

extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);

// match: _sub_23BD10 @ 0x0023BD10
static void
sub_23BD10(rwaObjDef *def)
{
    RwaObjDefAssignID(def, &unk_3ED218, NULL);

    def->flags = 0x64;
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_23B7B0;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_23B820;
    def->unk2C = (rwaInstance *(*)(rwaInstance *))sub_23B850;
    def->query = (void (*)(void *, void *))sub_23B8A0;
    def->paramsSize = 4;
}

extern rwaObjDef *dword_516C60;
extern RwUInt8 unk_506780[];
extern RwUInt8 unk_5067F4[];
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern void *RwaVirtualVoiceInterfaceRegister(void);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);

// match: _RwaVirtualVoiceRegister @ 0x0023BF60
rwaObjDef *
RwaVirtualVoiceRegister(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0xC, unk_506798, unk_506780, unk_5067F4,
                                 rwaMEMHINTDUR_EVENT | rwaID_810);
    void       *iface;

    if (!def)
    {
        return NULL;
    }

    sub_23BD10(def);

    if (!_rwaObjDefSetupParams(def, unk_42E1C8, 14, unk_42E318, 15))
    {
        sub_23DB90(def);

        return NULL;
    }

    iface = RwaVirtualVoiceInterfaceRegister();
    if (!iface)
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, iface);
    dword_5067FC = 1;

    return def;
}
