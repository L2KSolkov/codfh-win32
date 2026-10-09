/*
 * codfh-match: RenderWare Audio's Xbox output object (0x24DF20-0x24EC60;
 * VC7.1): the DirectSound device behind the output definition at 0x507CE8.
 * Creating it makes the DirectSound object, downloads the effects image,
 * sets the mix bins' levels and the 3D defaults; each update applies what
 * its listener and I3DL2 settings changed, then lets DirectSound work. Its
 * parameter handlers, its definition's set-up and the registration lists'
 * unregistration follow.
 */
#include "rwa.h"
#include "rwaint.h"



extern RwUInt32 __stdcall XGetAudioFlags(void);
extern RwInt32 __stdcall DirectSoundCreate(void *guid, void **dsound, void *outer);
extern RwInt32 __stdcall DirectSoundUseFullHRTF(void);
extern void __stdcall DirectSoundDoWork(void);
extern RwUInt32 __stdcall IDirectSound_Release(void *dsound);
extern RwInt32 __stdcall IDirectSound_SetI3DL2Listener(void *dsound,
                                                       const rwaI3DL2Listener *listener,
                                                       RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_GetOutputLevels(void *dsound, void *levels,
                                                      RwBool reset);
extern RwInt32 __stdcall IDirectSound_SetEffectData(void *dsound, RwUInt32 index,
                                                    RwUInt32 offset, void *data,
                                                    RwUInt32 size, RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_GetEffectData(void *dsound, RwUInt32 index,
                                                    RwUInt32 offset, void *data,
                                                    RwUInt32 size);
extern RwInt32 __stdcall IDirectSound_CommitEffectData(void *dsound);
extern RwInt32 __stdcall IDirectSound_GetSpeakerConfig(void *dsound, RwUInt32 *config);
extern RwInt32 __stdcall IDirectSound_DownloadEffectsImage(void *dsound, void *image,
                                                           RwUInt32 size, void *loc,
                                                           void **desc);
extern RwInt32 __stdcall IDirectSound_SetDopplerFactor(void *dsound, RwReal factor,
                                                       RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_SetDistanceFactor(void *dsound, RwReal factor,
                                                        RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_SetRolloffFactor(void *dsound, RwReal factor,
                                                       RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_SetVelocity(void *dsound, RwReal x, RwReal y, RwReal z,
                                                  RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_SetPosition(void *dsound, RwReal x, RwReal y, RwReal z,
                                                  RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_SetOrientation(void *dsound, RwReal xFront,
                                                     RwReal yFront, RwReal zFront,
                                                     RwReal xTop, RwReal yTop, RwReal zTop,
                                                     RwUInt32 apply);
extern RwInt32 __stdcall IDirectSound_CommitDeferredSettings(void *dsound);
extern RwInt32 __stdcall IDirectSound_EnableHeadphones(void *dsound, RwBool enabled);

extern void *RwFopen(const RwChar *name, const RwChar *access);
extern RwInt32 RwFseek(void *file, RwInt32 offset, RwInt32 origin);
extern RwInt32 RwFtell(void *file);
extern RwUInt32 RwFread(void *buffer, RwUInt32 size, RwUInt32 count, void *file);
extern RwInt32 RwFclose(void *file);

typedef RwBool (*rwaOpenFunc)(void);
extern RwBool _rwaWaveDefUnregister(rwaOpenFunc *funcs, RwUInt32 count);
extern rwaInstance *sub_23F4C0(rwaObjDef *def, rwaInstance *parent, RwUInt32 flags, void *params,
                               void *allocFunc, void *data);
extern RwBool sub_23DB90(rwaObjDef *def);
extern rwaInstance *sub_23F140(rwaInstance *obj, RwBool ok);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);
extern RwInt32 sub_241F90(RwReal gain);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void *sub_2421C0(RwUInt32 count, RwUInt32 size, RwUInt32 hint);
extern RwaUUID *sub_24DF00(void);
extern void *sub_250AC0(void);
extern RwBool sub_250B10(void);
extern void *sub_2FEB90(void *obj, const void *param, void *value);
extern void *sub_2FEC00(void *obj, const void *param, void *value);
extern void sub_24E710(rwaXboxOutput *obj, void *a, void *b);

extern rwaObjDef unk_507CE8;        /* the output definition */
extern RwUInt8 unk_507D44[];
extern RwUInt8 unk_507D4C[];
extern RwBool dword_507D64;         /* the listener is registered */
extern rwaObjDef *dword_516C60;
extern const RwUInt8 unk_3EDF5C[];
extern rwaMixBinLevel unk_4302C0[];
extern rwaMixBinLevel unk_430340[];
extern rwaMixBinLevel unk_430380[];
extern rwaMixBinLevel unk_4303C0[];
extern rwaMixBinLevel unk_430400[];
extern rwaOpenFunc unk_430608[];
extern rwaOpenFunc unk_430624[];
extern rwaOpenFunc unk_430640[];
extern rwaOpenFunc unk_430644[];
extern rwaOpenFunc unk_430648[];
extern rwaOpenFunc unk_430654[];

extern RwaUniqueID *sub_240C30(RwaUniqueID *uniqueID);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_430440 @ 0x00430440
// match: _unk_430448 @ 0x00430448
// match: _unk_430450 @ 0x00430450
// match: _unk_430458 @ 0x00430458
// match: _unk_430460 @ 0x00430460
// match: _unk_430468 @ 0x00430468
// match: _unk_430470 @ 0x00430470
// match: _unk_430518 @ 0x00430518
// match: _unk_4305EC @ 0x004305EC
// match: _unk_4302C0 @ 0x004302C0
// match: _unk_430340 @ 0x00430340
// match: _unk_430608 @ 0x00430608
// match: _unk_430624 @ 0x00430624
// match: _unk_430640 @ 0x00430640
// match: _unk_430644 @ 0x00430644

// What its data definitions name.
RwBool RwaListenerUnregister_0(void);
extern void RwaListenerUnregister_1(void);
extern void RwaStreamNodeInterfaceRegister(void);
extern void RwaStreamRendererInterfaceRegister(void);
extern void sub_23FB00(void);
extern void sub_2408C0(void);
extern void sub_240900(void);
extern void sub_240C50(void);
extern void sub_241660(void);
extern void sub_245240(void);
extern void sub_245290(void);
extern void sub_249420(void);
extern void sub_24CC40(void);
extern void sub_24D400(void);
extern void sub_24D4B0(void);
extern void sub_24DAB0(void);
extern void sub_24DE40(void);
rwaObjDef *sub_24EB20(void);
rwaObjDef *sub_24EB50(void);
extern void sub_2509F0(void);
extern void sub_250A30(void);
extern void sub_250B20(void);
extern void sub_251F20(void);
extern void sub_2FDB00(void);
extern void sub_2FEB10(void);
// What its parameter tables name (the handlers are defined below; the identifiers are
// unit_24EC60's and the RWA core's).
extern void _rwerror(void);
rwaXboxOutput *sub_24E270(rwaXboxOutput *obj, const void *param, void *value);
rwaXboxOutput *sub_24E290(rwaXboxOutput *obj, const void *param, const rwaEffectData *value);
rwaXboxOutput *sub_24E2B0(rwaXboxOutput *obj, const void *param, const rwaEffectData *value);
rwaXboxOutput *sub_24E2D0(rwaXboxOutput *obj, const void *param, const RwReal *value);
rwaXboxOutput *sub_24E2F0(rwaXboxOutput *obj, const void *param, RwReal *value);
rwaXboxOutput *sub_24E310(rwaXboxOutput *obj, const void *param, rwaInstance *value);
rwaXboxOutput *sub_24E330(rwaXboxOutput *obj, const void *param, rwaInstance **value);
rwaXboxOutput *sub_24E350(rwaXboxOutput *obj, const void *param, const rwaI3DL2Listener *value);
rwaXboxOutput *sub_24E370(rwaXboxOutput *obj, const void *param, rwaI3DL2Listener *value);
rwaXboxOutput *sub_24E390(rwaXboxOutput *obj, const void *param, RwUInt32 *value);
rwaXboxOutput *sub_24E3B0(rwaXboxOutput *obj, const void *param, void *value);
rwaXboxOutput *sub_24E3D0(rwaXboxOutput *obj, const void *param, RwUInt32 *value);
extern RwUInt8 unk_3ED4FC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED56C[];
extern RwUInt8 unk_3ED7B4[];
extern RwUInt8 unk_3ED7C4[];
extern RwUInt8 unk_3ED7D4[];
extern RwUInt8 unk_3ED7E4[];
extern RwUInt8 unk_3ED7F4[];
extern RwUInt8 unk_3ED804[];
extern RwUInt8 unk_3ED814[];
extern RwUInt8 unk_3ED824[];
extern RwUInt8 unk_3ED834[];
extern RwUInt8 unk_3ED844[];
extern RwUInt8 unk_3ED854[];
extern const RwaUUID unk_3EDF98;
extern const RwaUUID unk_3EDFA8;
extern const RwaUUID unk_3EDFB8;

// Its data definitions (PLAN M5), in the image's address order.
#if !defined(CODFH_SP) || CODFH_SP_PART == 1 // single player: part 1, the output object (sp_unit_24DF20_1.c, after unit_24DA70: SP 0x163F60, data 0x32CB50)
// 0x004302C0
rwaMixBinLevel unk_4302C0[16] = {
    { 0x0, 0 },
    { 0x1, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x6, 0 },
    { 0x8, 0 },
    { 0x7, 0 },
    { 0x9, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
};
// 0x00430340
rwaMixBinLevel unk_430340[8] = {
    { 0x6, 0 },
    { 0x8, 0 },
    { 0x7, 0 },
    { 0x9, 0 },
    { 0xA, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
};
// 0x00430380
rwaMixBinLevel unk_430380[8] = {
    { 0x6, 0 },
    { 0x8, 0 },
    { 0x7, 0 },
    { 0x9, 0 },
    { 0x2, -900 },
    { 0xA, 0 },
    { 0x3, -1200 },
    { 0x0, 0 },
};
// 0x004303C0
rwaMixBinLevel unk_4303C0[8] = {
    { 0x0, 0 },
    { 0x1, 0 },
    { 0x4, 0 },
    { 0x5, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
};
// 0x00430400
rwaMixBinLevel unk_430400[8] = {
    { 0x0, 0 },
    { 0x1, 0 },
    { 0x2, 0 },
    { 0x3, 0 },
    { 0x4, 0 },
    { 0x5, 0 },
    { 0x0, 0 },
    { 0x0, 0 },
};
// 0x00430440
rwaMixBins unk_430440 = { 0x2, unk_4302C0 };
// 0x00430448: the second half of unk_4302C0 (0x430300)
rwaMixBins unk_430448 = { 0x4, &unk_4302C0[8] };
// 0x00430450
rwaMixBins unk_430450 = { 0x5, &unk_430340 };
// 0x00430458
rwaMixBins unk_430458 = { 0x7, &unk_430380 };
// 0x00430460
rwaMixBins unk_430460 = { 0x4, &unk_4303C0 };
// 0x00430468
rwaMixBins unk_430468 = { 0x6, &unk_430400 };
// 0x00430470
void *unk_430470[42] =
{
    (void *)&unk_3EDFA8,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E290,
    (void *)&unk_3ED7B4,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24E2D0,
    (void *)&unk_3ED7D4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E310,
    (void *)&unk_3ED7F4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E350,
    (void *)&unk_3ED814,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)_rwerror,
    (void *)&unk_3ED834,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)_rwerror,
    (void *)&unk_3ED844,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E3B0,
};
// 0x00430518
void *unk_430518[42] =
{
    (void *)&unk_3EDF98,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E270,
    (void *)&unk_3EDFB8,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E2B0,
    (void *)&unk_3ED7C4,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24E2F0,
    (void *)&unk_3ED7E4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E330,
    (void *)&unk_3ED804,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E370,
    (void *)&unk_3ED824,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24E390,
    (void *)&unk_3ED854,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24E3D0,
};
// 0x00507CE8
rwaObjDef unk_507CE8;
// 0x00507D44
RwUInt8 unk_507D44[8];
// 0x00507D4C
RwUInt8 unk_507D4C[24];
// 0x00507D64
RwBool dword_507D64;
// End of its data definitions.

// match: _unk_430648 @ 0x00430648


// match: _unk_430654 @ 0x00430654


// match: _unk_430380 @ 0x00430380


// match: _unk_4303C0 @ 0x004303C0


// match: _unk_430400 @ 0x00430400


// match: _sub_24E050>30 @ 0x004305C0


// match: _sub_24E3F0>11 @ 0x004305D4


// match: _sub_24E3F0>16 @ 0x004305E8

// match: _RwaStreamCreate_1 @ 0x0024DF20
// sp-match: _RwaStreamCreate_1 @ 0x00163F60

rwaInstance *
RwaStreamCreate_1(rwaInstance *parent, void *params, RwUInt32 flags, void *allocFunc, void *data)
{
    return sub_23F4C0(&unk_507CE8, parent, flags, params, allocFunc, data);
}

// match: _RwaListenerUnregister_0 @ 0x0024DF50
// sp-match: _RwaListenerUnregister_0 @ 0x00163F90
RwBool
RwaListenerUnregister_0(void)
{
    if (dword_507D64)
    {
        if (!sub_250B10())
        {
            return FALSE;
        }
        dword_507D64 = FALSE;
    }

    return sub_23DB90(&unk_507CE8);
}

/* Converts mix bin gains to levels. */
// match: _sub_24DF80 @ 0x0024DF80
// sp-match: _sub_24DF80 @ 0x00163FC0
void
sub_24DF80(const rwaMixBinGains *gains, rwaMixBinLevel *levels)
{
    RwUInt32    i;

    for (i = 0; i < gains->count; i++)
    {
        levels[i].mixBin = gains->entries[i].mixBin;
        levels[i].level = sub_241F90(gains->entries[i].gain);
    }
}

// match: _sub_24DFC0 @ 0x0024DFC0
// sp-match: _sub_24DFC0 @ 0x00164000
static RwBool
sub_24DFC0(const rwaI3DL2Listener *listener, void *dsound, RwUInt32 flags)
{
    if (flags & 1)
    {
        rwaI3DL2Listener settings;

        settings.room = listener->room;
        settings.roomHF = listener->roomHF;
        settings.roomRolloffFactor = listener->roomRolloffFactor;
        settings.decayTime = listener->decayTime;
        settings.decayHFRatio = listener->decayHFRatio;
        settings.reflections = listener->reflections;
        settings.reflectionsDelay = listener->reflectionsDelay;
        settings.reverb = listener->reverb;
        settings.reverbDelay = listener->reverbDelay;
        settings.diffusion = listener->diffusion;
        settings.density = listener->density;
        settings.hfReference = listener->hfReference;
        if (IDirectSound_SetI3DL2Listener(dsound, &settings, 0) < 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/* The default creation parameters. */
// match: _sub_24E050 @ 0x0024E050
// sp-match: _sub_24E050 @ 0x00164090
static void *
sub_24E050(void *obj, rwaXboxOutputParams *params)
{
    RwUInt32    audioFlags = XGetAudioFlags();
    RwUInt32    mode;

    params->unk00 = 0x100;
    params->effectsPath = "d:\\data\\dsstdfx.bin";
    params->unk08 = 3;
    params->unk0C = 4;
    params->memory = NULL;
    params->memorySize = 0x7FBD80;
    params->i3dl2 = TRUE;
    switch (audioFlags & 0xFFFF)
    {
        case 1:
            mode = 2;
            break;
        case 2:
            mode = 4;
            if (audioFlags & 0x10000)
            {
                mode = 5;
            }
            break;
        default:
            mode = 1;
            break;
    }
    params->speakerMode = mode;
    params->mixBins[0] = NULL;
    params->mixBins[1] = NULL;
    params->mixBins[2] = NULL;
    params->mixBins[3] = NULL;
    params->mixBins[4] = NULL;
    params->unk34 = 1.0f;
    params->unk38 = 0.5f;

    return obj;
}

// match: _sub_24E0E0 @ 0x0024E0E0
// sp-match: _sub_24E0E0 @ 0x00164120
RwInt32
sub_24E0E0(rwaXboxOutput *obj, void *levels)
{
    return IDirectSound_GetOutputLevels(obj->state.dsound, levels, TRUE);
}

// match: _sub_24E100 @ 0x0024E100
// sp-match: _sub_24E100 @ 0x00164140
void
sub_24E100(rwaXboxOutput *obj, const rwaEffectData *effect)
{
    if (IDirectSound_SetEffectData(obj->state.dsound, effect->index, effect->offset,
                                   effect->data, effect->size, 1) >= 0)
    {
        obj->state.flags |= 8;
    }
}

// match: _sub_24E140 @ 0x0024E140
// sp-match: _sub_24E140 @ 0x00164180
RwInt32
sub_24E140(rwaXboxOutput *obj, const rwaEffectData *effect)
{
    return IDirectSound_GetEffectData(obj->state.dsound, effect->index, effect->offset,
                                      effect->data, effect->size);
}

// match: _sub_24E170 @ 0x0024E170
// sp-match: _sub_24E170 @ 0x001641B0
void
sub_24E170(rwaXboxOutput *obj, RwReal value)
{
    obj->state.unk04 = value;
}

/* The ICF-folded copy of this getter is at 0x24F1C0. */
RwReal
rwaXboxOutputGetUnk04(rwaXboxOutput *obj)
{
    return obj->state.unk04;
}

// match: _sub_24E180 @ 0x0024E180
// sp-match: _sub_24E180 @ 0x001641C0
void
sub_24E180(rwaXboxOutput *obj, rwaInstance *listener)
{
    obj->state.listener = listener;
}

// The output's setting the game turns on after creating it (arg 1): empty in
// this build. Defined here for the authentic link (PLAN M7).
// _sub_22C6E0 (folded into 0x22C6E0)
void
sub_22C6E0(rwaXboxOutput *obj, RwInt32 value)
{
}

// match: _sub_24E190 @ 0x0024E190
// sp-match: _sub_24E190 @ 0x001641D0
rwaInstance *
sub_24E190(rwaXboxOutput *obj)
{
    return obj->state.listener;
}

// match: _sub_24E1A0 @ 0x0024E1A0
// sp-match: _sub_24E1A0 @ 0x001641E0
void
sub_24E1A0(rwaXboxOutput *obj, const rwaI3DL2Listener *listener)
{
    obj->state.i3dl2 = *listener;
    obj->state.flags |= 2;
}

// match: _sub_24E1C0 @ 0x0024E1C0
// sp-match: _sub_24E1C0 @ 0x00164200
void
sub_24E1C0(rwaXboxOutput *obj, rwaI3DL2Listener *listener)
{
    *listener = obj->state.i3dl2;
}

/* The speaker mode DirectSound is set to. */
// match: _sub_24E1E0 @ 0x0024E1E0
// sp-match: _sub_24E1E0 @ 0x00164220
RwUInt32
sub_24E1E0(rwaXboxOutput *obj)
{
    RwUInt32    config;
    RwUInt32    mode;

    IDirectSound_GetSpeakerConfig(obj->state.dsound, &config);
    switch (config & 0xFFFF)
    {
        case 0:
            mode = 1;
            break;
        case 1:
            mode = 2;
            break;
        case 2:
            mode = (config & 0x10000) ? 5 : 4;
            break;
        default:
            mode = 0;
            break;
    }

    return mode;
}

// match: _sub_24E230 @ 0x0024E230
// sp-match: _sub_24E230 @ 0x00164270
void *
sub_24E230(rwaXboxOutput *obj, void *value)
{
    return sub_2FEB90(obj, NULL, value);
}

// match: _sub_24E250 @ 0x0024E250
// sp-match: _sub_24E250 @ 0x00164290
RwUInt32
sub_24E250(rwaXboxOutput *obj)
{
    sub_2FEC00(obj, NULL, &obj);
    return (RwUInt32)obj;
}

// match: _sub_24E270 @ 0x0024E270
// sp-match: _sub_24E270 @ 0x001642B0
rwaXboxOutput *
sub_24E270(rwaXboxOutput *obj, const void *param, void *value)
{
    sub_24E0E0(obj, value);
    return obj;
}

// match: _sub_24E290 @ 0x0024E290
// sp-match: _sub_24E290 @ 0x001642D0
rwaXboxOutput *
sub_24E290(rwaXboxOutput *obj, const void *param, const rwaEffectData *value)
{
    sub_24E100(obj, value);
    return obj;
}

// match: _sub_24E2B0 @ 0x0024E2B0
// sp-match: _sub_24E2B0 @ 0x001642F0
rwaXboxOutput *
sub_24E2B0(rwaXboxOutput *obj, const void *param, const rwaEffectData *value)
{
    sub_24E140(obj, value);
    return obj;
}

// match: _sub_24E2D0 @ 0x0024E2D0
// sp-match: _sub_24E2D0 @ 0x00164310
rwaXboxOutput *
sub_24E2D0(rwaXboxOutput *obj, const void *param, const RwReal *value)
{
    sub_24E170(obj, *value);
    return obj;
}

// match: _sub_24E2F0 @ 0x0024E2F0
// sp-match: _sub_24E2F0 @ 0x00162C00
rwaXboxOutput *
sub_24E2F0(rwaXboxOutput *obj, const void *param, RwReal *value)
{
    *value = rwaXboxOutputGetUnk04(obj);
    return obj;
}

// match: _sub_24E310 @ 0x0024E310
// sp-match: _sub_24E310 @ 0x00164330
rwaXboxOutput *
sub_24E310(rwaXboxOutput *obj, const void *param, rwaInstance *value)
{
    sub_24E180(obj, value);
    return obj;
}

// match: _sub_24E330 @ 0x0024E330
// sp-match: _sub_24E330 @ 0x00164350
rwaXboxOutput *
sub_24E330(rwaXboxOutput *obj, const void *param, rwaInstance **value)
{
    *value = sub_24E190(obj);
    return obj;
}

// match: _sub_24E350 @ 0x0024E350
// sp-match: _sub_24E350 @ 0x00164370
rwaXboxOutput *
sub_24E350(rwaXboxOutput *obj, const void *param, const rwaI3DL2Listener *value)
{
    sub_24E1A0(obj, value);
    return obj;
}

// match: _sub_24E370 @ 0x0024E370
// sp-match: _sub_24E370 @ 0x00164390
rwaXboxOutput *
sub_24E370(rwaXboxOutput *obj, const void *param, rwaI3DL2Listener *value)
{
    sub_24E1C0(obj, value);
    return obj;
}

// match: _sub_24E390 @ 0x0024E390
// sp-match: _sub_24E390 @ 0x001643B0
rwaXboxOutput *
sub_24E390(rwaXboxOutput *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24E1E0(obj);
    return obj;
}

// match: _sub_24E3B0 @ 0x0024E3B0
// sp-match: _sub_24E3B0 @ 0x001643D0
rwaXboxOutput *
sub_24E3B0(rwaXboxOutput *obj, const void *param, void *value)
{
    sub_24E230(obj, value);
    return obj;
}

// match: _sub_24E3D0 @ 0x0024E3D0
// sp-match: _sub_24E3D0 @ 0x001643F0
rwaXboxOutput *
sub_24E3D0(rwaXboxOutput *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24E250(obj);
    return obj;
}

/* Downloads the effects image (path, or the standard one). */
// match: _sub_24E3F0 @ 0x0024E3F0
// sp-match: _sub_24E3F0 @ 0x00164410
static RwBool
sub_24E3F0(const RwChar *path, rwaXboxOutput *obj, RwUInt32 a, RwUInt32 b)
{
    void       *file;
    RwUInt32    size;
    void       *image;

    if (!path)
    {
        path = "d:\\data\\dsstdfx.bin";
    }
    file = RwFopen(path, "rb");
    if (!file)
    {
        return FALSE;
    }
    if (RwFseek(file, 0, 2))
    {
        RwFclose(file);
        return FALSE;
    }
    size = RwFtell(file);
    if (RwFseek(file, 0, 0))
    {
        RwFclose(file);
        return FALSE;
    }
    image = sub_242170(size, rwaMEMHINTDUR_FUNCTION | rwaID_801);
    if (!image)
    {
        RwFclose(file);
        return FALSE;
    }
    if (size != RwFread(image, 1, size, file))
    {
        sub_2421B0(image);
        RwFclose(file);
        return FALSE;
    }
    RwFclose(file);

    obj->state.unk58 = a;
    obj->state.unk5C = b;
    if (IDirectSound_DownloadEffectsImage(obj->state.dsound, image, size, &obj->state.unk58,
                                          &obj->state.effects) < 0)
    {
        sub_2421B0(image);
        return FALSE;
    }
    sub_2421B0(image);
    return TRUE;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 2 // single player: part 2, the module tables (sp_unit_24DF20_2.c, before unit_24EC60: SP 0x32C668)
/* The image has these after sub_24E050's and sub_24E3F0's local statics: defined
 * here, after them. */
// 0x004305EC
void *unk_4305EC[7] =
{
    (void *)sub_24EB20,
    (void *)sub_2509F0,
    (void *)sub_2408C0,
    (void *)sub_2FEB10,
    (void *)sub_241660,
    (void *)sub_24D400,
    (void *)sub_251F20,
};
// 0x00430608
rwaOpenFunc unk_430608[7] = {
    sub_24EB50,
    sub_250A30,
    sub_240900,
    sub_2FEB10,
    sub_241660,
    sub_24D400,
    sub_251F20,
};
// 0x00430624
rwaOpenFunc unk_430624[7] = {
    sub_24CC40,
    sub_240C50,
    sub_2FDB00,
    sub_23FB00,
    RwaListenerUnregister_1,
    RwaListenerUnregister_0,
    sub_250B20,
};
// 0x00430640
rwaOpenFunc unk_430640[1] = {
    sub_24DE40,
};
// 0x00430644
rwaOpenFunc unk_430644[1] = {
    sub_24DAB0,
};
// 0x00430648
rwaOpenFunc unk_430648[3] = {
    sub_245240,
    RwaStreamNodeInterfaceRegister,
    RwaStreamRendererInterfaceRegister,
};
// 0x00430654
rwaOpenFunc unk_430654[3] = {
    sub_24D4B0,
    sub_249420,
    sub_245290,
};

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 1
// match: _sub_24E500 @ 0x0024E500
// sp-match: _sub_24E500 @ 0x00164520
static rwaXboxOutput *
sub_24E500(rwaXboxOutput *obj, rwaInstance *parent, rwaXboxOutputParams *params)
{
    obj->state.flags = 0;
    if (params->memory)
    {
        obj->state.flags |= 0x10;
    }
    else
    {
        obj->state.memory = sub_2421C0(params->memorySize, 1, rwaMEMHINTDUR_EVENT | rwaID_80C);
        if (!obj->state.memory)
        {
            return NULL;
        }
    }

    obj->state.listener = NULL;
    obj->state.unk00 = (RwUInt16)params->unk00;
    obj->state.unk02 = 0;
    obj->state.dsound = NULL;
    obj->state.memorySize = params->memorySize;
    obj->state.speakerMode = params->speakerMode;
    if (DirectSoundCreate(NULL, &obj->state.dsound, NULL) < 0)
    {
        return NULL;
    }
    DirectSoundUseFullHRTF();
    if (!sub_24E3F0(params->effectsPath, obj, params->unk08, params->unk0C))
    {
        return NULL;
    }

    if (params->mixBins[0])
    {
        sub_24DF80(params->mixBins[0], unk_430340);
    }
    if (params->mixBins[1])
    {
        sub_24DF80(params->mixBins[1], unk_430380);
    }
    if (params->mixBins[2])
    {
        sub_24DF80(params->mixBins[2], unk_4302C0);
    }
    if (params->mixBins[3])
    {
        sub_24DF80(params->mixBins[3], unk_4303C0);
    }
    if (params->mixBins[4])
    {
        sub_24DF80(params->mixBins[4], unk_430400);
    }
    obj->state.unk50 = -sub_241F90(params->unk34);
    obj->state.unk54 = -sub_241F90(params->unk38);

    IDirectSound_SetDopplerFactor(obj->state.dsound, 1.0f, 1);
    IDirectSound_SetVelocity(obj->state.dsound, 0.0f, 0.0f, 0.0f, 1);
    IDirectSound_SetOrientation(obj->state.dsound, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1);
    sub_24E170(obj, 1.0f);
    if (params->i3dl2)
    {
        obj->state.flags |= 1;
    }
    if (obj->state.flags & 1)
    {
        rwaI3DL2Listener listener = {
            -10000, -10000, 0.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f,
            100.0f, 100.0f, 5000.0f
        };

        sub_24E1A0(obj, &listener);
    }
    IDirectSound_CommitDeferredSettings(obj->state.dsound);

    return obj;
}

// match: _sub_24E710 @ 0x0024E710
// sp-match: _sub_24E710 @ 0x00164730
void
sub_24E710(rwaXboxOutput *obj, void *a, void *b)
{
    rwaXboxOutputState *state = (rwaXboxOutputState *)obj->inst.state;
    RwaUniqueID zero;

    sub_24E180(obj, NULL);
    /* The image retains a three-word zero temporary. RwaUniqueID and its
     * folded empty cleanup reconstruct the exact stores and scheduling;
     * the original temporary type/cleanup expression remain unknown. */
    zero.uuid = NULL;
    zero.name = NULL;
    zero.flags = 0;
    if (zero.flags)
    {
        sub_240C30(&zero);
    }
    sub_24DF00();
    IDirectSound_Release(state->dsound);
    if (!(state->flags & 0x10) && state->memory)
    {
        sub_2421B0(state->memory);
        state->memory = NULL;
        state->memorySize = 0;
    }
}

/* Applies what changed and lets DirectSound work. */
// match: _sub_24E770 @ 0x0024E770
// sp-match: _sub_24E770 @ 0x00164790
static rwaXboxOutput *
sub_24E770(rwaXboxOutput *obj)
{
    sub_23F140(&obj->inst, TRUE);
    if (obj->state.listener)
    {
        rwaXboxListenerState *listener = (rwaXboxListenerState *)obj->state.listener->state;

        if (listener->flags & 0x20)
        {
            IDirectSound_SetDopplerFactor(obj->state.dsound, listener->doppler, 0);
            listener->flags &= ~0x20;
        }
        if (listener->flags & 0x40)
        {
            IDirectSound_SetDistanceFactor(obj->state.dsound, listener->distance, 0);
            listener->flags &= ~0x40;
        }
        if (listener->flags & 0x10)
        {
            IDirectSound_SetRolloffFactor(obj->state.dsound, listener->rolloff, 0);
            listener->flags &= ~0x10;
        }
        if (listener->flags & 0xC)
        {
            IDirectSound_SetOrientation(obj->state.dsound, -listener->front.x, listener->front.y,
                                        listener->front.z, -listener->top.x, listener->top.y,
                                        listener->top.z, 0);
            listener->flags &= ~0xC;
        }
        if (listener->flags & 1)
        {
            IDirectSound_SetPosition(obj->state.dsound, -listener->pos.x, listener->pos.y,
                                     listener->pos.z, 0);
            listener->flags &= ~1;
        }
        if (listener->flags & 2)
        {
            IDirectSound_SetVelocity(obj->state.dsound, -listener->vel.x, listener->vel.y,
                                     listener->vel.z, 0);
            listener->flags &= ~2;
        }
    }
    if (obj->state.flags & 2)
    {
        rwaI3DL2Listener *settings = &obj->state.i3dl2;

        sub_24DFC0(settings, obj->state.dsound, obj->state.flags);
        obj->state.flags &= ~2;
    }
    if (obj->state.flags & 8)
    {
        obj->state.flags &= ~8;
        IDirectSound_CommitEffectData(obj->state.dsound);
    }
    if (obj->state.flags & 4)
    {
        RwUInt32 config;

        switch (obj->state.speakerMode)
        {
            /* the modes' speaker configurations, unused */
            case 1:
                config = 0;
                break;
            case 2:
                config = 1;
                break;
            case 3:
                IDirectSound_EnableHeadphones(obj->state.dsound, TRUE);
                break;
            case 4:
                config = 2;
                break;
            case 5:
                config = 0x10002;
                break;
        }
        obj->state.flags &= ~4;
    }
    DirectSoundDoWork();

    return obj;
}

// match: _sub_24E8E0 @ 0x0024E8E0
// sp-match: _sub_24E8E0 @ 0x00164900
static void
sub_24E8E0(rwaObjDef *def)
{
    RwaObjDefAssignID(def, unk_3EDF5C, NULL);

    def->flags = sizeof(rwaXboxOutputState);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_24E500;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_24E710;
    def->unk30 = (rwaInstance *(*)(rwaInstance *))sub_24E770;
    def->query = (void (*)(void *, void *))sub_24E050;
    def->paramsSize = sizeof(rwaXboxOutputParams);
}

// match: _sub_24EB20 @ 0x0024EB20
// sp-match: _sub_24EB20 @ 0x00164B40
rwaObjDef *
sub_24EB20(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0, &unk_507CE8, NULL, NULL,
                                 rwaMEMHINTDUR_EVENT | rwaID_80C);

    if (!def)
    {
        return NULL;
    }

    sub_24E8E0(def);

    return def;
}

// match: _sub_24EB50 @ 0x0024EB50
// sp-match: _sub_24EB50 @ 0x00164B70
rwaObjDef *
sub_24EB50(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0xC, &unk_507CE8, unk_507D4C, unk_507D44,
                                 rwaMEMHINTDUR_EVENT | rwaID_80C);
    void       *iface;

    if (!def)
    {
        return NULL;
    }

    sub_24E8E0(def);

    if (!_rwaObjDefSetupParams(def, unk_430470, 7, unk_430518, 7))
    {
        sub_23DB90(def);

        return NULL;
    }

    iface = sub_250AC0();
    if (!iface)
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, iface);
    dword_507D64 = TRUE;

    return def;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 2 // single player: part 2, the module open/close (sp_unit_24DF20_2.c, before unit_24EC60: SP 0x161BC0)
// match: _sub_24EBD0 @ 0x0024EBD0
// sp-match: _sub_24EBD0 @ 0x00161BC0
RwBool
sub_24EBD0(void)
{
    if (_rwaWaveDefUnregister(unk_430654, 3) != TRUE ||
        _rwaWaveDefUnregister(unk_430624, 7) != TRUE ||
        _rwaWaveDefUnregister(unk_430644, 1) != TRUE)
    {
        return FALSE;
    }

    return TRUE;
}

// match: _sub_24EC10 @ 0x0024EC10
// sp-match: _sub_24EC10 @ 0x00161C00
RwBool
sub_24EC10(void)
{
    if (!_rwaWaveDefUnregister(unk_430648, 3) ||
        !_rwaWaveDefUnregister(unk_430608, 7) ||
        !_rwaWaveDefUnregister(unk_430640, 1))
    {
        sub_24EBD0();
        return FALSE;
    }

    return TRUE;
}
#endif
