/*
 * codfh-match: RenderWare Audio's Xbox voice object (0x24EC60-0x250AC0;
 * VC7.1): the voice definition at 0x507D80, a DirectSound buffer playing a
 * wave straight from the streamed waves' memory, or (flags rwaXBVOICEMIXTARGET) a
 * buffer other voices mix into. Its 3D, I3DL2, volume, pan and play
 * settings are kept in the state and applied by the update; then its
 * parameter handlers, its definition's set-up and registration.
 */
#include <math.h>

#include "rwa.h"
#include "rwaint.h"



extern void *memset(void *dst, RwInt32 value, RwUInt32 size);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

extern void __stdcall Sleep(RwUInt32 milliseconds);
extern RwInt32 __stdcall IDirectSound_CreateSoundBuffer(void *dsound, const rwaBufferDesc *desc,
                                                        void **buffer, void *outer);
extern RwUInt32 __stdcall IDirectSoundBuffer_Release(void *buffer);
extern RwInt32 __stdcall IDirectSoundBuffer_GetStatus(void *buffer, RwUInt32 *status);
extern RwInt32 __stdcall IDirectSoundBuffer_StopEx(void *buffer, RwInt32 timeHigh,
                                                   RwUInt32 timeLow, RwUInt32 flags);
extern RwInt32 __stdcall IDirectSoundBuffer_Play(void *buffer, RwUInt32 reserved1,
                                                 RwUInt32 reserved2, RwUInt32 flags);
extern RwInt32 __stdcall IDirectSoundBuffer_SetOutputBuffer(void *buffer, void *output);
extern RwInt32 __stdcall IDirectSoundBuffer_SetRolloffCurve(void *buffer, const RwReal *points,
                                                            RwUInt32 count, RwUInt32 apply);
extern RwInt32 __stdcall IDirectSoundBuffer_SetFormat(void *buffer, const void *format);
extern RwInt32 __stdcall IDirectSoundBuffer_SetBufferData(void *buffer, void *data,
                                                          RwUInt32 size);
extern RwInt32 __stdcall IDirectSoundBuffer_SetMixBins(void *buffer, const rwaMixBins *mixBins);
extern RwInt32 __stdcall IDirectSoundBuffer_SetMixBinVolumes(void *buffer,
                                                             const rwaMixBins *mixBins);
extern RwInt32 __stdcall IDirectSoundBuffer_SetPlayRegion(void *buffer, RwUInt32 offset,
                                                          RwUInt32 length);
extern RwInt32 __stdcall IDirectSoundBuffer_SetLoopRegion(void *buffer, RwUInt32 offset,
                                                          RwUInt32 length);
extern RwInt32 __stdcall IDirectSoundBuffer_SetCurrentPosition(void *buffer, RwUInt32 position);
extern RwInt32 __stdcall IDirectSoundBuffer_GetCurrentPosition(void *buffer, RwUInt32 *play,
                                                               RwUInt32 *write);
extern RwInt32 __stdcall IDirectSoundBuffer_SetHeadroom(void *buffer, RwUInt32 headroom);
extern RwInt32 __stdcall IDirectSoundBuffer_SetAllParameters(void *buffer,
                                                             const rwaDS3DBuffer *params,
                                                             RwUInt32 apply);
extern RwInt32 __stdcall IDirectSoundBuffer_SetFrequency(void *buffer, RwUInt32 frequency);
extern RwInt32 __stdcall IDirectSoundBuffer_SetVolume(void *buffer, RwInt32 volume);
extern RwInt32 __stdcall IDirectSoundBuffer_SetI3DL2Source(void *buffer,
                                                           const rwaI3DL2Source *source,
                                                           RwUInt32 apply);

extern rwaInstance *sub_23F4C0(rwaObjDef *def, rwaInstance *parent, RwUInt32 flags, void *params,
                               void *allocFunc, void *data);
extern RwBool sub_23DB90(rwaObjDef *def);
extern void sub_23F090(RwBool (*callback)(rwaInstance *obj, void *data), void *data);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern rwaObjDef *sub_23DCA0(rwaObjDef *root, const void *uuid, rwaObjDef **parentOut);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);
extern void sub_23CD40(rwaInstance **listeners, RwUInt32 count,
                         const rwa3DSource *source, RwReal *gains, RwUInt32 mode);
extern RwInt32 sub_241F90(RwReal gain);
extern void sub_24DF80(const rwaMixBinGains *gains, rwaMixBinLevel *levels);
extern RwUInt8 *sub_24DB60(RwUInt32 handle);
extern void *sub_251FA0(void);
extern RwBool sub_251FF0(void);
extern void sub_24F410(rwaXboxVoice *obj, RwaWave *wave);
extern rwaXboxVoice *sub_250340(rwaXboxVoice *obj);

extern rwaObjDef unk_507D80;        /* the voice definition */
extern RwUInt8 unk_507D68[];
extern RwUInt8 unk_507DDC[];
extern RwBool dword_507DE4;         /* the voice's interface is registered */
extern const RwaUUID unk_3ED5FC;    /* Xbox ADPCM */
extern const RwReal unk_3EDF7C[];   /* the rolloff curve */
extern rwaMixBins unk_430440;       /* stereo */
extern rwaMixBins unk_430448;       /* the default four */
extern rwaMixBins unk_430450;       /* 3D */
extern rwaMixBins unk_430458;       /* 3D, 5.1 */
extern rwaMixBins unk_430460;       /* four channels */
extern rwaMixBins unk_430468;       /* six channels */
extern RwUInt8 unk_430660[];  /* the mix-in buffers' format */

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@4024000000000000 @ 0x003ED060
// match: __real@3a03126f @ 0x003ED1B8
// match: _unk_430660 @ 0x00430660

// What its data definitions name.
extern void sub_24E270(void);
extern void sub_24E290(void);
extern void sub_24E2B0(void);
extern void sub_24E2D0(void);
extern void sub_24E2F0(void);
extern void sub_24E310(void);
extern void sub_24E330(void);
extern void sub_24E350(void);
extern void sub_24E370(void);
extern void sub_24E390(void);
extern void sub_24E3B0(void);
extern void sub_24E3D0(void);
rwaXboxVoice *sub_24F890(rwaXboxVoice *obj, const void *param, const RwaV3d *value);
rwaXboxVoice *sub_24F8B0(rwaXboxVoice *obj, const void *param, RwaV3d *value);
rwaXboxVoice *sub_24F8D0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24F8F0(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24F910(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24F930(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24F950(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24F970(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24F990(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24F9B0(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24F9D0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24F9F0(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24FA10(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FA30(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24FA50(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24FA70(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24FA90(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FAB0(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24FAD0(rwaXboxVoice *obj, const void *param, const rwaI3DL2Listener *value);
rwaXboxVoice *sub_24FAF0(rwaXboxVoice *obj, const void *param, rwaI3DL2Listener *value);
rwaXboxVoice *sub_24FB10(rwaXboxVoice *obj, const void *param, const RwaV3d *value);
rwaXboxVoice *sub_24FB30(rwaXboxVoice *obj, const void *param, RwaV3d *value);
rwaXboxVoice *sub_24FB50(rwaXboxVoice *obj, const void *param, const RwaV3d *value);
rwaXboxVoice *sub_24FB70(rwaXboxVoice *obj, const void *param, RwaV3d *value);
rwaXboxVoice *sub_24FB90(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FBB0(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24FBD0(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FBF0(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24FC10(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FC30(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FC50(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24FC70(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24FC90(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24FCB0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24FCD0(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24FCF0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value);
rwaXboxVoice *sub_24FD10(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24FD30(rwaXboxVoice *obj, const void *param, RwaWave *value);
rwaXboxVoice *sub_24FD50(rwaXboxVoice *obj, const void *param, RwaWave **value);
rwaXboxVoice *sub_24FD70(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FD90(rwaXboxVoice *obj, const void *param, RwReal *value);
rwaXboxVoice *sub_24FDB0(rwaXboxVoice *obj, const void *param, RwUInt32 *value);
rwaXboxVoice *sub_24FDD0(rwaXboxVoice *obj, const void *param, const RwReal *value);
rwaXboxVoice *sub_24FDF0(rwaXboxVoice *obj, const void *param, RwReal *value);
extern void _rwerror(void);
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
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED4FC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED54C[];
extern RwUInt8 unk_3ED55C[];
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
extern rwaMixBinLevel unk_4302C0[];
extern RwUInt8 unk_430340[];
extern RwUInt8 unk_430380[];
extern RwUInt8 unk_4303C0[];
extern RwUInt8 unk_430400[];
// The shared constants (unit_3EDEBC).
extern const RwaUUID unk_3EDEBC;
extern const RwaUUID unk_3EDECC;
extern const RwaUUID unk_3EDEDC;
extern const RwaUUID unk_3EDEEC;
extern const RwaUUID unk_3EDEFC;
extern const RwaUUID unk_3EDF0C;
extern const RwaUUID unk_3EDF1C;
extern const RwaUUID unk_3EDF2C;
extern const RwaUUID unk_3EDF3C;
extern const RwaUUID unk_3EDF4C;
extern const RwaUUID unk_3EDF5C;
extern const RwaUUID unk_3EDF6C;
extern const RwaUUID unk_3EDF88;
extern const RwaUUID unk_3EDF98;
extern const RwaUUID unk_3EDFA8;
extern const RwaUUID unk_3EDFB8;
extern const RwaUUID unk_3EDFC8;
extern const RwaUUID unk_3EDFD8;
extern const RwaUUID unk_3EDFE8;
extern const RwaUUID unk_3EDFF8;
extern const RwaUUID unk_3EE008;
extern const RwaUUID unk_3EE018;
extern const RwaUUID unk_3EE028;
extern const RwaUUID unk_3EE038;
extern const RwaUUID unk_3EE048;
extern const RwaUUID unk_3EE058;
extern const RwaUUID unk_3EE068;
extern const RwaUUID unk_3EE078;
extern const RwaUUID unk_3EE088;
extern const RwaUUID unk_3EE098;
extern const RwaUUID unk_3EE0A8;
extern const RwaUUID unk_3EE0B8;
extern const RwaUUID unk_3EE0C8;
extern const RwaUUID unk_3EE0D8;
extern const RwaUUID unk_3EE0E8;
extern const RwaUUID unk_3EE0F8;
extern const RwaUUID unk_3EE108;
extern const RwaUUID unk_3EE118;
extern const RwReal flt_3EDF80;   /* the volume curve: 0.00063095737 + */
extern const RwReal flt_3EDF84;   /* 0.99936903 * the volume */
// Its data definitions (PLAN M5), in the image's address order.
// 0x00430660
RwUInt8 unk_430660[24] = {
    0x1,
    0x0,
    0x1,
    0x0,
    0x80,
    0xBB,
    0x0,
    0x0,
    0x0,
    0x77,
    0x1,
    0x0,
    0x2,
    0x0,
    0x10,
    0x0,
    0x12,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
};
// 0x00430678
void *off_430678[132] =
{
    (void *)&unk_3EDFE8,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_24F890,
    (void *)&unk_3EE008,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24F8D0,
    (void *)&unk_3EE028,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24F910,
    (void *)&unk_3EE048,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24F950,
    (void *)&unk_3EE068,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24F990,
    (void *)&unk_3EE088,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24F9D0,
    (void *)&unk_3EE0A8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FA10,
    (void *)&unk_3EE0C8,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24FA50,
    (void *)&unk_3EE0E8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FA90,
    (void *)&unk_3EE108,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24FAD0,
    (void *)&unk_3ED3DC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_24FB10,
    (void *)&unk_3ED3FC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_24FB50,
    (void *)&unk_3ED41C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FB90,
    (void *)&unk_3ED43C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FBD0,
    (void *)&unk_3ED2BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FC10,
    (void *)&unk_3ED2DC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FC30,
    (void *)&unk_3ED2FC,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_24FC70,
    (void *)&unk_3ED31C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24FCB0,
    (void *)&unk_3ED33C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_24FCF0,
    (void *)&unk_3ED35C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24FD30,
    (void *)&unk_3ED37C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FD70,
    (void *)&unk_3ED3AC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FDD0,
};
// 0x00430888
void *off_430888[138] =
{
    (void *)&unk_3EDFF8,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_24F8B0,
    (void *)&unk_3EE018,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24F8F0,
    (void *)&unk_3EE038,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24F930,
    (void *)&unk_3EE058,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24F970,
    (void *)&unk_3EE078,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24F9B0,
    (void *)&unk_3EE098,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24F9F0,
    (void *)&unk_3EE0B8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FA30,
    (void *)&unk_3EE0D8,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)sub_24FA70,
    (void *)&unk_3EE0F8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FAB0,
    (void *)&unk_3EE118,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24FAF0,
    (void *)&unk_3ED3EC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_24FB30,
    (void *)&unk_3ED40C,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_24FB70,
    (void *)&unk_3ED42C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FBB0,
    (void *)&unk_3ED44C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FBF0,
    (void *)&unk_3ED2CC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24E2F0,
    (void *)&unk_3ED2EC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FC50,
    (void *)&unk_3ED30C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_24FC90,
    (void *)&unk_3ED32C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_24FCD0,
    (void *)&unk_3ED34C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_24FD10,
    (void *)&unk_3ED36C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_24FD50,
    (void *)&unk_3ED38C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FD90,
    (void *)&unk_3ED39C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_24FDB0,
    (void *)&unk_3ED3BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_24FDF0,
};
// 0x00507D68
RwUInt8 unk_507D68[24];
// 0x00507D80
rwaObjDef unk_507D80;
// 0x00507DDC
RwUInt8 unk_507DDC[8];
// 0x00507DE4
RwBool dword_507DE4;
// End of its data definitions.

// match: _off_430678 @ 0x00430678


// match: _off_430888 @ 0x00430888













// match: _RwaStreamCreate_2 @ 0x0024EC60
// sp-match: _RwaStreamCreate_2 @ 0x00161C50

rwaInstance *
RwaStreamCreate_2(rwaInstance *parent, void *params, RwUInt32 flags, void *allocFunc, void *data)
{
    return sub_23F4C0(&unk_507D80, parent, flags, params, allocFunc, data);
}

// match: _RwaListenerUnregister_1 @ 0x0024EC90
// sp-match: _RwaListenerUnregister_1 @ 0x00161C80
RwBool
RwaListenerUnregister_1(void)
{
    if (dword_507DE4)
    {
        if (!sub_251FF0())
        {
            return FALSE;
        }
        dword_507DE4 = FALSE;
    }

    return sub_23DB90(&unk_507D80);
}

/* Sets the buffer up for 3D (or not) and finds its I3DL2 mix bin. */
// match: _sub_24ECC0 @ 0x0024ECC0
// sp-match: _sub_24ECC0 @ 0x00161CB0
static RwBool
sub_24ECC0(rwaXboxVoiceState *state, RwBool is3D)
{
    RwUInt32    i;
    RwBool      found;

    if (is3D)
    {
        state->flags |= 0x20;
        if (IDirectSoundBuffer_SetRolloffCurve(state->buffer, unk_3EDF7C, 1, 1) < 0)
        {
            return FALSE;
        }
    }
    else
    {
        state->flags &= ~0x20;
    }

    found = FALSE;
    for (i = 0; i < state->noLevels; i++)
    {
        if (state->levels[i].mixBin == 10)
        {
            found = TRUE;
            break;
        }
    }
    if (found)
    {
        state->flags |= rwaXBVOICEI3DL2;
    }
    else
    {
        state->flags &= ~rwaXBVOICEI3DL2;
    }
    state->position = 0;
    state->current = 0;
    state->start = 0;
    state->gain = 1.0f;

    return TRUE;
}

/* Finds the voice whose mix bin is search's. */
// match: _sub_24ED50 @ 0x0024ED50
// sp-match: _sub_24ED50 @ 0x00161D40
RwBool
sub_24ED50(rwaXboxVoice *obj, rwaXboxVoiceFind *search)
{
    if (!RwaUUIDCompare(&unk_3EDF6C, obj->inst.def->uniqueID.uuid)
        && obj->state.id == search->id)
    {
        search->found = obj;
        return TRUE;
    }

    return FALSE;
}

/* Whether the buffer plays. */
// match: _sub_24ED90 @ 0x0024ED90
// sp-match: _sub_24ED90 @ 0x00161D80
static RwBool
sub_24ED90(void *buffer)
{
    RwUInt32    status = 0;

    if (buffer && IDirectSoundBuffer_GetStatus(buffer, &status) >= 0)
    {
        return status & 1;
    }

    return FALSE;
}

/* The default creation parameters. */
// match: _sub_24EDC0 @ 0x0024EDC0
// sp-match: _sub_24EDC0 @ 0x00161DB0
static RwBool
sub_24EDC0(void *buffer, RwUInt32 timeout)
{
    RwBool      result = TRUE;

    if (buffer && sub_24ED90(buffer))
    {
        RwUInt32    tries = 0;
        RwUInt32    status;

        IDirectSoundBuffer_StopEx(buffer, 0, 0, 0);
        result = FALSE;
        do
        {
            if (timeout < (RwUInt32)-1)
            {
                tries++;
            }
            Sleep(0);
            IDirectSoundBuffer_GetStatus(buffer, &status);
            if (!(status & 1))
            {
                result = TRUE;
                IDirectSoundBuffer_SetOutputBuffer(buffer, NULL);
                break;
            }
        }
        while (tries <= timeout);
    }

    return result;
}


// match: _sub_24EE40 @ 0x0024EE40
// sp-match: _sub_24EE40 @ 0x00161E30
static void *
sub_24EE40(void *obj, rwaXboxVoiceParams *params)
{
    params->flags = 7;
    params->id = 0;
    params->mixBins = NULL;
    params->target = NULL;
    params->headroomGain = 1.0f;

    return obj;
}

// match: _sub_24EE70 @ 0x0024EE70
// sp-match: _sub_24EE70 @ 0x00161E60
void
sub_24EE70(rwaXboxVoice *obj, const RwaV3d *orientation)
{
    obj->state.ds3d.coneOrientation.x = -orientation->x;
    obj->state.ds3d.coneOrientation.y = orientation->y;
    obj->state.ds3d.coneOrientation.z = orientation->z;
    obj->state.flags |= 0x10;
}

// match: _sub_24EEA0 @ 0x0024EEA0
// sp-match: _sub_24EEA0 @ 0x00161E90
void
sub_24EEA0(rwaXboxVoice *obj, RwaV3d *orientation)
{
    orientation->x = -obj->state.ds3d.coneOrientation.x;
    orientation->y = obj->state.ds3d.coneOrientation.y;
    orientation->z = obj->state.ds3d.coneOrientation.z;
}

// match: _sub_24EED0 @ 0x0024EED0
// sp-match: _sub_24EED0 @ 0x00161EC0
void
sub_24EED0(rwaXboxVoice *obj, RwUInt32 angle)
{
    obj->state.ds3d.insideConeAngle = angle;
    obj->state.flags |= 0x10;
}

// match: _sub_24EEF0 @ 0x0024EEF0
RwUInt32
sub_24EEF0(rwaXboxVoice *obj)
{
    return obj->state.ds3d.insideConeAngle;
}

// match: _sub_24EF00 @ 0x0024EF00
// sp-match: _sub_24EF00 @ 0x00161EE0
void
sub_24EF00(rwaXboxVoice *obj, RwUInt32 angle)
{
    obj->state.ds3d.outsideConeAngle = angle;
    obj->state.flags |= 0x10;
}

// match: _sub_24EF20 @ 0x0024EF20
// sp-match: _sub_24EF20 @ 0x00161F00
RwUInt32
sub_24EF20(rwaXboxVoice *obj)
{
    return obj->state.ds3d.outsideConeAngle;
}

// match: _sub_24EF30 @ 0x0024EF30
// sp-match: _sub_24EF30 @ 0x00161F10
void
sub_24EF30(rwaXboxVoice *obj, RwReal gain)
{
    obj->state.ds3d.coneOutsideVolume = sub_241F90(gain);
    obj->state.flags |= 0x10;
}

// match: _sub_24EF60 @ 0x0024EF60
// sp-match: _sub_24EF60 @ 0x00161F40
RwReal
sub_24EF60(rwaXboxVoice *obj)
{
    RwReal      gain = (RwReal)pow(10.0, obj->state.ds3d.coneOutsideVolume * 0.0005f);

    return gain;
}

// match: _sub_24EF80 @ 0x0024EF80
// sp-match: _sub_24EF80 @ 0x00161F60
void
sub_24EF80(rwaXboxVoice *obj, RwInt32 level)
{
    obj->state.direct = level;
    obj->state.flags |= 0x40;
}

// match: _sub_24EF90 @ 0x0024EF90
// sp-match: _sub_24EF90 @ 0x00161F70
RwInt32
sub_24EF90(rwaXboxVoice *obj)
{
    return obj->state.direct;
}

// match: _sub_24EFA0 @ 0x0024EFA0
// sp-match: _sub_24EFA0 @ 0x00161F80
void
sub_24EFA0(rwaXboxVoice *obj, RwInt32 level)
{
    obj->state.obstruction = level;
    obj->state.flags |= 0x40;
}

// match: _sub_24EFB0 @ 0x0024EFB0
// sp-match: _sub_24EFB0 @ 0x00161F90
RwInt32
sub_24EFB0(rwaXboxVoice *obj)
{
    return obj->state.obstruction;
}

// match: _sub_24EFC0 @ 0x0024EFC0
// sp-match: _sub_24EFC0 @ 0x00161FA0
void
sub_24EFC0(rwaXboxVoice *obj, RwReal ratio)
{
    obj->state.obstructionLFRatio = ratio;
    obj->state.flags |= 0x40;
}

// match: _sub_24EFE0 @ 0x0024EFE0
// sp-match: _sub_24EFE0 @ 0x00161FC0
RwReal
sub_24EFE0(rwaXboxVoice *obj)
{
    return obj->state.obstructionLFRatio;
}

// match: _sub_24EFF0 @ 0x0024EFF0
// sp-match: _sub_24EFF0 @ 0x00161FD0
void
sub_24EFF0(rwaXboxVoice *obj, RwInt32 level)
{
    obj->state.occlusion = level;
    obj->state.flags |= 0x40;
}

// match: _sub_24F000 @ 0x0024F000
// sp-match: _sub_24F000 @ 0x00161FE0
RwInt32
sub_24F000(rwaXboxVoice *obj)
{
    return obj->state.occlusion;
}

// match: _sub_24F010 @ 0x0024F010
// sp-match: _sub_24F010 @ 0x00161FF0
void
sub_24F010(rwaXboxVoice *obj, RwReal ratio)
{
    obj->state.occlusionLFRatio = ratio;
    obj->state.flags |= 0x40;
}

// match: _sub_24F030 @ 0x0024F030
// sp-match: _sub_24F030 @ 0x00162010
RwReal
sub_24F030(rwaXboxVoice *obj)
{
    return obj->state.occlusionLFRatio;
}

// match: _sub_24F040 @ 0x0024F040
// sp-match: _sub_24F040 @ 0x00162020
void
sub_24F040(rwaXboxVoice *obj, const rwaI3DL2Listener *settings)
{
    obj->state.i3dl2 = *settings;
    obj->state.flags |= 0x40;
}

// match: _sub_24F060 @ 0x0024F060
// sp-match: _sub_24F060 @ 0x00162040
void
sub_24F060(rwaXboxVoice *obj, rwaI3DL2Listener *settings)
{
    *settings = obj->state.i3dl2;
}

// match: _sub_24F080 @ 0x0024F080
// sp-match: _sub_24F080 @ 0x00162060
void
sub_24F080(rwaXboxVoice *obj, const RwaV3d *position)
{
    obj->state.ds3d.position.x = -position->x;
    obj->state.ds3d.position.y = position->y;
    obj->state.ds3d.position.z = position->z;
    obj->state.flags |= 0x10;
}

// match: _sub_24F0B0 @ 0x0024F0B0
// sp-match: _sub_24F0B0 @ 0x00162090
void
sub_24F0B0(rwaXboxVoice *obj, RwaV3d *position)
{
    position->x = -obj->state.ds3d.position.x;
    position->y = obj->state.ds3d.position.y;
    position->z = obj->state.ds3d.position.z;
}

// match: _sub_24F0E0 @ 0x0024F0E0
// sp-match: _sub_24F0E0 @ 0x001620C0
void
sub_24F0E0(rwaXboxVoice *obj, const RwaV3d *velocity)
{
    obj->state.ds3d.velocity.x = -velocity->x;
    obj->state.ds3d.velocity.y = velocity->y;
    obj->state.ds3d.velocity.z = velocity->z;
    obj->state.flags |= 0x10;
}

// match: _sub_24F110 @ 0x0024F110
// sp-match: _sub_24F110 @ 0x001620F0
void
sub_24F110(rwaXboxVoice *obj, RwaV3d *velocity)
{
    velocity->x = -obj->state.ds3d.velocity.x;
    velocity->y = obj->state.ds3d.velocity.y;
    velocity->z = obj->state.ds3d.velocity.z;
}

// match: _sub_24F140 @ 0x0024F140
// sp-match: _sub_24F140 @ 0x00162120
void
sub_24F140(rwaXboxVoice *obj, RwReal distance)
{
    obj->state.ds3d.minDistance = distance;
    obj->state.flags |= 0x10;
}

// match: _sub_24F160 @ 0x0024F160
// sp-match: _sub_24F160 @ 0x00162140
RwReal
sub_24F160(rwaXboxVoice *obj)
{
    return obj->state.ds3d.minDistance;
}

// match: _sub_24F170 @ 0x0024F170
// sp-match: _sub_24F170 @ 0x00162150
void
sub_24F170(rwaXboxVoice *obj, RwReal distance)
{
    obj->state.ds3d.maxDistance = distance;
    obj->state.flags |= 0x10;
}

// match: _sub_24F190 @ 0x0024F190
// sp-match: _sub_24F190 @ 0x00162170
RwReal
sub_24F190(rwaXboxVoice *obj)
{
    return obj->state.ds3d.maxDistance;
}

// match: _sub_24F1A0 @ 0x0024F1A0
// sp-match: _sub_24F1A0 @ 0x00162180
void
sub_24F1A0(rwaXboxVoice *obj, RwReal frequency)
{
    obj->state.frequency = frequency;
    obj->state.flags |= 0x80;
}

// match: _sub_24F1C0 @ 0x0024F1C0
// sp-match: _sub_24F1C0 @ 0x0018F390
RwReal
sub_24F1C0(rwaXboxVoice *obj)
{
    return obj->state.frequency;
}

// match: _sub_24F1D0 @ 0x0024F1D0
// sp-match: _sub_24F1D0 @ 0x001621A0
void
sub_24F1D0(rwaXboxVoice *obj, RwReal volume)
{
    obj->state.volume = volume;
    obj->state.flags |= 0x100;
}

// match: _sub_24F1F0 @ 0x0024F1F0
// sp-match: _sub_24F1F0 @ 0x001621C0
RwReal
sub_24F1F0(rwaXboxVoice *obj)
{
    return obj->state.volume;
}

/* Starts (play) or stops the voice at the next update. */
// match: _sub_24F200 @ 0x0024F200
// sp-match: _sub_24F200 @ 0x001621D0
void
sub_24F200(rwaXboxVoice *obj, RwBool play)
{
    if (play)
    {
        obj->state.flags |= 0x800;
    }
    else
    {
        obj->state.flags &= ~0x800;
    }
    obj->state.flags |= 0x400;
}

// match: _sub_24F240 @ 0x0024F240
// sp-match: _sub_24F240 @ 0x00162210
RwBool
sub_24F240(rwaXboxVoice *obj)
{
    RwBool      playing = FALSE;

    if (obj->state.flags & 0x400)
    {
        playing = (obj->state.flags >> 11) & 1;
    }
    else if (obj->state.buffer)
    {
        playing = sub_24ED90(obj->state.buffer);
    }

    return playing;
}

/* Sets the play position (in frames). */
// match: _sub_24F270 @ 0x0024F270
// sp-match: _sub_24F270 @ 0x00162240
void
sub_24F270(rwaXboxVoice *obj, RwUInt32 position)
{
    RwUInt32    bytes;

    if (!RwaUUIDCompare(obj->state.wave->format.dataType, &unk_3ED5FC))
    {
        bytes = 36 * (obj->state.wave->format.noChannels * (position >> 6));
    }
    else
    {
        bytes = position * ((obj->state.wave->deviceFormat.bitDepth >> 3)
                            * obj->state.wave->deviceFormat.noChannels);
    }
    obj->state.current = bytes;
    obj->state.start = bytes;
    obj->state.position = position;
    obj->state.flags |= 0x1000;
}

// match: _sub_24F2F0 @ 0x0024F2F0
// sp-match: _sub_24F2F0 @ 0x001622C0
RwUInt32
sub_24F2F0(rwaXboxVoice *obj)
{
    return obj->state.position;
}

// match: _sub_24F300 @ 0x0024F300
// sp-match: _sub_24F300 @ 0x001622D0
void
sub_24F300(rwaXboxVoice *obj, RwBool loop)
{
    if (loop)
    {
        obj->state.flags |= 0x2000;
    }
    else
    {
        obj->state.flags &= ~0x2000;
    }
}

// match: _sub_24F330 @ 0x0024F330
// sp-match: _sub_24F330 @ 0x00162300
RwBool
sub_24F330(rwaXboxVoice *obj)
{
    return (obj->state.flags & 0x2000) == 0x2000;
}

// match: _sub_24F350 @ 0x0024F350
// sp-match: _sub_24F350 @ 0x00162320
static RwBool
sub_24F350(const RwaWaveFormat *current, const RwaWaveFormat *format)
{
    if (format->noChannels != current->noChannels || format->dataType != current->dataType
        || format->bitDepth != current->bitDepth)
    {
        return TRUE;
    }

    return FALSE;
}


/* The default mix bins of a 3D buffer or one of the channels. */
// match: _sub_24F380 @ 0x0024F380
// sp-match: _sub_24F380 @ 0x00162350
static void
sub_24F380(rwaMixBins *mixBins, RwUInt32 speakerMode, RwBool is3D, RwUInt32 noChannels)
{
    if (is3D)
    {
        if (speakerMode == 5)
        {
            *mixBins = unk_430458;
        }
        else
        {
            *mixBins = unk_430450;
        }
    }
    else
    {
        switch (noChannels)
        {
            case 1:
            case 2:
                *mixBins = unk_430440;
                break;
            case 4:
                *mixBins = unk_430460;
                break;
            case 6:
                *mixBins = unk_430468;
                break;
        }
    }
}

/* Keep the first format pointer across buffer creation and format setup;
 * refresh it after the separately computed play-region offset. */
// match: _sub_24F410 @ 0x0024F410
// sp-match: _sub_24F410 @ 0x001623E0
void
sub_24F410(rwaXboxVoice *obj, RwaWave *wave)
{
    rwaXboxVoiceState *state = &obj->state;
    RwBool      created;
    RwBool      is3D;
    RwBool      changed;
    const RwaWaveFormat *format;
    rwaMixBins  mixBins;
    rwaWaveFormatEx pcm;
    rwaAdpcmWaveFormat adpcm;
    rwaBufferDesc desc;
    RwUInt32 offset;

    if (state->wave)
    {
        state->wave = NULL;
        state->flags &= ~0x4000;
    }
    if (wave)
    {

        format = &wave->deviceFormat;
        created = FALSE;
        is3D = (wave->flags >> 1) & 1;
        if (state->buffer && is3D != ((state->flags >> 5) & 1))
        {
            sub_24EDC0(state->buffer, (RwUInt32)-1);
            IDirectSoundBuffer_Release(state->buffer);
            state->buffer = NULL;
        }
        if (!state->buffer)
        {
            rwaXboxOutputState *output = state->output;

            sub_24F380(&mixBins, output->speakerMode, is3D, 1);
            desc.bufferBytes = 0;
            desc.flags = is3D ? ((1u << 17) | 0x10) : 0;
            desc.inputMixBin = 0;
            desc.size = sizeof(desc);
            desc.mixBins = &mixBins;
            desc.format = unk_430660;
            if (IDirectSound_CreateSoundBuffer(output->dsound, &desc, &state->buffer, NULL) < 0)
            {
                return;
            }
            if (IDirectSoundBuffer_SetBufferData(state->buffer, state->output->memory,
                                                 state->output->memorySize) < 0)
            {
                IDirectSoundBuffer_Release(state->buffer);
                state->buffer = NULL;
                return;
            }
            created = TRUE;
        }

        changed = sub_24F350(&state->format, format);
        if (changed || created)
        {
            if (!created)
            {
                sub_24EDC0(state->buffer, (RwUInt32)-1);
            }

            if (!RwaUUIDCompare(format->dataType, &unk_3ED5FC))
            {
                adpcm.wfx.channels = format->noChannels;
                adpcm.wfx.samplesPerSec = format->sampleRate;
                adpcm.wfx.formatTag = 0x69;
                adpcm.wfx.bitsPerSample = 4;
                adpcm.wfx.size = 2;
                adpcm.wfx.blockAlign = 36 * format->noChannels;
                adpcm.wfx.avgBytesPerSec = adpcm.wfx.samplesPerSec * adpcm.wfx.blockAlign / 64;
                adpcm.samplesPerBlock = 64;
                if (IDirectSoundBuffer_SetFormat(state->buffer, &adpcm) < 0)
                {
                    IDirectSoundBuffer_Release(state->buffer);
                    state->buffer = NULL;
                    return;
                }
            }
            else
            {
                memset(&pcm, 0, sizeof(pcm));
                pcm.bitsPerSample = format->bitDepth;
                pcm.channels = format->noChannels;
                pcm.samplesPerSec = format->sampleRate;
                pcm.formatTag = 1;
                pcm.blockAlign = (pcm.bitsPerSample >> 3) * pcm.channels;
                pcm.avgBytesPerSec = pcm.blockAlign * pcm.samplesPerSec;
                if (IDirectSoundBuffer_SetFormat(state->buffer, &pcm) < 0)
                {
                    IDirectSoundBuffer_Release(state->buffer);
                    state->buffer = NULL;
                    return;
                }
            }

            if (state->flags & 0x10000)
            {
                if (IDirectSoundBuffer_SetOutputBuffer(state->buffer,
                                                       state->target->state.buffer) < 0)
                {
                    IDirectSoundBuffer_Release(state->buffer);
                    state->buffer = NULL;
                    return;
                }
            }
            else
            {
                sub_24F380(&mixBins, state->output->speakerMode, is3D, format->noChannels);
                if (state->noMixBins)
                {
                    if (is3D)
                    {
                        if (state->flags & rwaXBVOICE3DBINS)
                        {
                            mixBins.count = state->noMixBins;
                            mixBins.levels = state->mixBins;
                        }
                    }
                    else if (state->flags & rwaXBVOICE2DBINS)
                    {
                        mixBins.count = state->noMixBins;
                        mixBins.levels = state->mixBins;
                    }
                }
                memcpy(state->levels, mixBins.levels, mixBins.count * sizeof(rwaMixBinLevel));
                state->noLevels = mixBins.count;
                if (IDirectSoundBuffer_SetMixBins(state->buffer, &mixBins) < 0)
                {
                    IDirectSoundBuffer_Release(state->buffer);
                    state->buffer = NULL;
                    return;
                }
            }
            state->format = *format;
        }

        offset = sub_24DB60((RwUInt32)wave->buffer) - (RwUInt8 *)state->output->memory;
        format = &wave->deviceFormat;
        if (IDirectSoundBuffer_SetPlayRegion(state->buffer, offset,
                                             format->length) >= 0
            && IDirectSoundBuffer_SetLoopRegion(state->buffer, 0, format->length) >= 0
            && IDirectSoundBuffer_SetCurrentPosition(state->buffer, 0) >= 0)
        {
            RwUInt32    headroom;

            if (state->flags & rwaXBVOICEHEADROOM)
            {
                headroom = state->headroom;
            }
            else if (is3D)
            {
                headroom = state->output->unk50;
            }
            else
            {
                headroom = state->output->unk54;
            }
            if (IDirectSoundBuffer_SetHeadroom(state->buffer, headroom) >= 0
                && sub_24ECC0(state, is3D))
            {
                state->flags |= 0x4000;
                state->wave = wave;
                return;
            }
        }

        IDirectSoundBuffer_Release(state->buffer);
        state->buffer = NULL;
    }
    else
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
    }

}

// match: _sub_24F7E0 @ 0x0024F7E0
// sp-match: _sub_24F7E0 @ 0x001627B0
RwaWave *
sub_24F7E0(rwaXboxVoice *obj)
{
    return obj->state.wave;
}

// match: _sub_24F7F0 @ 0x0024F7F0
// sp-match: _sub_24F7F0 @ 0x001627C0
void
sub_24F7F0(rwaXboxVoice *obj, RwReal pan)
{
    obj->state.pan = pan;
    obj->state.flags |= 0x200;
}

// match: _sub_24F810 @ 0x0024F810
// sp-match: _sub_24F810 @ 0x001627E0
RwReal
sub_24F810(rwaXboxVoice *obj)
{
    return obj->state.pan;
}

/* Whether the voice plays in 2D (the wave is not positional). */
// match: _sub_24F820 @ 0x0024F820
// sp-match: _sub_24F820 @ 0x001627F0
RwBool
sub_24F820(rwaXboxVoice *obj)
{
    RwBool      result = FALSE;

    if (obj->state.wave)
    {
        result = !(obj->state.wave->flags & 2);
    }
    else if (obj->state.flags & 0x8000)
    {
        result = !(obj->state.flags & 7);
    }

    return result;
}

// match: _sub_24F850 @ 0x0024F850
// sp-match: _sub_24F850 @ 0x00162820
void
sub_24F850(rwaXboxVoice *obj, RwReal gain)
{
    obj->state.i3dl2.room = sub_241F90(gain);
    obj->state.flags |= 0x40;
}

// match: _sub_24F870 @ 0x0024F870
// sp-match: _sub_24F870 @ 0x00162840
RwReal
sub_24F870(rwaXboxVoice *obj)
{
    RwReal      gain = (RwReal)pow(10.0, obj->state.i3dl2.room * 0.0005f);

    return gain;
}

// match: _sub_24F890 @ 0x0024F890
// sp-match: _sub_24F890 @ 0x00162860
rwaXboxVoice *
sub_24F890(rwaXboxVoice *obj, const void *param, const RwaV3d *value)
{
    sub_24EE70(obj, value);
    return obj;
}

// match: _sub_24F8B0 @ 0x0024F8B0
// sp-match: _sub_24F8B0 @ 0x00162880
rwaXboxVoice *
sub_24F8B0(rwaXboxVoice *obj, const void *param, RwaV3d *value)
{
    sub_24EEA0(obj, value);
    return obj;
}

// match: _sub_24F8D0 @ 0x0024F8D0
// sp-match: _sub_24F8D0 @ 0x001628A0
rwaXboxVoice *
sub_24F8D0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24EED0(obj, *value);
    return obj;
}

// match: _sub_24F8F0 @ 0x0024F8F0
// sp-match: _sub_24F8F0 @ 0x001628C0
rwaXboxVoice *
sub_24F8F0(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24EEF0(obj);
    return obj;
}

// match: _sub_24F910 @ 0x0024F910
// sp-match: _sub_24F910 @ 0x001628E0
rwaXboxVoice *
sub_24F910(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24EF00(obj, *value);
    return obj;
}

// match: _sub_24F930 @ 0x0024F930
// sp-match: _sub_24F930 @ 0x00162900
rwaXboxVoice *
sub_24F930(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24EF20(obj);
    return obj;
}

// match: _sub_24F950 @ 0x0024F950
// sp-match: _sub_24F950 @ 0x00162920
rwaXboxVoice *
sub_24F950(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24EF30(obj, *value);
    return obj;
}

// match: _sub_24F970 @ 0x0024F970
// sp-match: _sub_24F970 @ 0x00162940
rwaXboxVoice *
sub_24F970(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24EF60(obj);
    return obj;
}

// match: _sub_24F990 @ 0x0024F990
// sp-match: _sub_24F990 @ 0x00162960
rwaXboxVoice *
sub_24F990(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24EF80(obj, *value);
    return obj;
}

// match: _sub_24F9B0 @ 0x0024F9B0
// sp-match: _sub_24F9B0 @ 0x00162980
rwaXboxVoice *
sub_24F9B0(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24EF90(obj);
    return obj;
}

// match: _sub_24F9D0 @ 0x0024F9D0
// sp-match: _sub_24F9D0 @ 0x001629A0
rwaXboxVoice *
sub_24F9D0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24EFA0(obj, *value);
    return obj;
}

// match: _sub_24F9F0 @ 0x0024F9F0
// sp-match: _sub_24F9F0 @ 0x001629C0
rwaXboxVoice *
sub_24F9F0(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24EFB0(obj);
    return obj;
}

// match: _sub_24FA10 @ 0x0024FA10
// sp-match: _sub_24FA10 @ 0x001629E0
rwaXboxVoice *
sub_24FA10(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24EFC0(obj, *value);
    return obj;
}

// match: _sub_24FA30 @ 0x0024FA30
// sp-match: _sub_24FA30 @ 0x00162A00
rwaXboxVoice *
sub_24FA30(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24EFE0(obj);
    return obj;
}

// match: _sub_24FA50 @ 0x0024FA50
// sp-match: _sub_24FA50 @ 0x00162A20
rwaXboxVoice *
sub_24FA50(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24EFF0(obj, *value);
    return obj;
}

// match: _sub_24FA70 @ 0x0024FA70
// sp-match: _sub_24FA70 @ 0x00162A40
rwaXboxVoice *
sub_24FA70(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24F000(obj);
    return obj;
}

// match: _sub_24FA90 @ 0x0024FA90
// sp-match: _sub_24FA90 @ 0x00162A60
rwaXboxVoice *
sub_24FA90(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F010(obj, *value);
    return obj;
}

// match: _sub_24FAB0 @ 0x0024FAB0
// sp-match: _sub_24FAB0 @ 0x00162A80
rwaXboxVoice *
sub_24FAB0(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24F030(obj);
    return obj;
}

// match: _sub_24FAD0 @ 0x0024FAD0
// sp-match: _sub_24FAD0 @ 0x00162AA0
rwaXboxVoice *
sub_24FAD0(rwaXboxVoice *obj, const void *param, const rwaI3DL2Listener *value)
{
    sub_24F040(obj, value);
    return obj;
}

// match: _sub_24FAF0 @ 0x0024FAF0
// sp-match: _sub_24FAF0 @ 0x00162AC0
rwaXboxVoice *
sub_24FAF0(rwaXboxVoice *obj, const void *param, rwaI3DL2Listener *value)
{
    sub_24F060(obj, value);
    return obj;
}

// match: _sub_24FB10 @ 0x0024FB10
// sp-match: _sub_24FB10 @ 0x00162AE0
rwaXboxVoice *
sub_24FB10(rwaXboxVoice *obj, const void *param, const RwaV3d *value)
{
    sub_24F080(obj, value);
    return obj;
}

// match: _sub_24FB30 @ 0x0024FB30
// sp-match: _sub_24FB30 @ 0x00162B00
rwaXboxVoice *
sub_24FB30(rwaXboxVoice *obj, const void *param, RwaV3d *value)
{
    sub_24F0B0(obj, value);
    return obj;
}

// match: _sub_24FB50 @ 0x0024FB50
// sp-match: _sub_24FB50 @ 0x00162B20
rwaXboxVoice *
sub_24FB50(rwaXboxVoice *obj, const void *param, const RwaV3d *value)
{
    sub_24F0E0(obj, value);
    return obj;
}

// match: _sub_24FB70 @ 0x0024FB70
// sp-match: _sub_24FB70 @ 0x00162B40
rwaXboxVoice *
sub_24FB70(rwaXboxVoice *obj, const void *param, RwaV3d *value)
{
    sub_24F110(obj, value);
    return obj;
}

// match: _sub_24FB90 @ 0x0024FB90
// sp-match: _sub_24FB90 @ 0x00162B60
rwaXboxVoice *
sub_24FB90(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F140(obj, *value);
    return obj;
}

// match: _sub_24FBB0 @ 0x0024FBB0
// sp-match: _sub_24FBB0 @ 0x00162B80
rwaXboxVoice *
sub_24FBB0(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24F160(obj);
    return obj;
}

// match: _sub_24FBD0 @ 0x0024FBD0
// sp-match: _sub_24FBD0 @ 0x00162BA0
rwaXboxVoice *
sub_24FBD0(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F170(obj, *value);
    return obj;
}

// match: _sub_24FBF0 @ 0x0024FBF0
// sp-match: _sub_24FBF0 @ 0x00162BC0
rwaXboxVoice *
sub_24FBF0(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24F190(obj);
    return obj;
}

// match: _sub_24FC10 @ 0x0024FC10
// sp-match: _sub_24FC10 @ 0x00162BE0
rwaXboxVoice *
sub_24FC10(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F1A0(obj, *value);
    return obj;
}

// match: _sub_24FC30 @ 0x0024FC30
// sp-match: _sub_24FC30 @ 0x00162C20
rwaXboxVoice *
sub_24FC30(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F1D0(obj, *value);
    return obj;
}

// match: _sub_24FC50 @ 0x0024FC50
// sp-match: _sub_24FC50 @ 0x00162C40
rwaXboxVoice *
sub_24FC50(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24F1F0(obj);
    return obj;
}

// match: _sub_24FC70 @ 0x0024FC70
// sp-match: _sub_24FC70 @ 0x00162C60
rwaXboxVoice *
sub_24FC70(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24F200(obj, *value);
    return obj;
}

// match: _sub_24FC90 @ 0x0024FC90
// sp-match: _sub_24FC90 @ 0x00162C80
rwaXboxVoice *
sub_24FC90(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24F240(obj);
    return obj;
}

// match: _sub_24FCB0 @ 0x0024FCB0
// sp-match: _sub_24FCB0 @ 0x00162CA0
rwaXboxVoice *
sub_24FCB0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24F270(obj, *value);
    return obj;
}

// match: _sub_24FCD0 @ 0x0024FCD0
// sp-match: _sub_24FCD0 @ 0x00162CC0
rwaXboxVoice *
sub_24FCD0(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24F2F0(obj);
    return obj;
}

// match: _sub_24FCF0 @ 0x0024FCF0
// sp-match: _sub_24FCF0 @ 0x00162CE0
rwaXboxVoice *
sub_24FCF0(rwaXboxVoice *obj, const void *param, const RwUInt32 *value)
{
    sub_24F300(obj, *value);
    return obj;
}

// match: _sub_24FD10 @ 0x0024FD10
// sp-match: _sub_24FD10 @ 0x00162D00
rwaXboxVoice *
sub_24FD10(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24F330(obj);
    return obj;
}

// match: _sub_24FD30 @ 0x0024FD30
// sp-match: _sub_24FD30 @ 0x00162D20
rwaXboxVoice *
sub_24FD30(rwaXboxVoice *obj, const void *param, RwaWave *value)
{
    sub_24F410(obj, value);
    return obj;
}

// match: _sub_24FD50 @ 0x0024FD50
// sp-match: _sub_24FD50 @ 0x00162D40
rwaXboxVoice *
sub_24FD50(rwaXboxVoice *obj, const void *param, RwaWave **value)
{
    *value = sub_24F7E0(obj);
    return obj;
}

// match: _sub_24FD70 @ 0x0024FD70
// sp-match: _sub_24FD70 @ 0x00162D60
rwaXboxVoice *
sub_24FD70(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F7F0(obj, *value);
    return obj;
}

// match: _sub_24FD90 @ 0x0024FD90
// sp-match: _sub_24FD90 @ 0x00162D80
rwaXboxVoice *
sub_24FD90(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24F810(obj);
    return obj;
}

// match: _sub_24FDB0 @ 0x0024FDB0
// sp-match: _sub_24FDB0 @ 0x00162DA0
rwaXboxVoice *
sub_24FDB0(rwaXboxVoice *obj, const void *param, RwUInt32 *value)
{
    *value = sub_24F820(obj);
    return obj;
}

// match: _sub_24FDD0 @ 0x0024FDD0
// sp-match: _sub_24FDD0 @ 0x00162DC0
rwaXboxVoice *
sub_24FDD0(rwaXboxVoice *obj, const void *param, const RwReal *value)
{
    sub_24F850(obj, *value);
    return obj;
}

// match: _sub_24FDF0 @ 0x0024FDF0
// sp-match: _sub_24FDF0 @ 0x00162DE0
rwaXboxVoice *
sub_24FDF0(rwaXboxVoice *obj, const void *param, RwReal *value)
{
    *value = sub_24F870(obj);
    return obj;
}

/* Creates a voice: its mix bins (from the parameters' gains, all of the
 * default four or none of them), the voice it mixes into, the 3D and I3DL2
 * defaults, and the buffer of a voice others mix into. */
// match: _sub_24FE10 @ 0x0024FE10
// sp-match: _sub_24FE10 @ 0x00162E00
static rwaXboxVoice *
sub_24FE10(rwaXboxVoice *obj, rwaInstance *parent, rwaXboxVoiceParams *params)
{
    rwaXboxVoiceState *state = &obj->state;
    rwaMixBinGains *gains;

    state->flags = params->flags;
    state->target = params->target;
    state->id = params->id;
    state->flags |= params->flags & rwaXBVOICEHEADROOM;
    state->headroom = -sub_241F90(params->headroomGain);
    state->buffer = NULL;
    memset(&state->noLevels, 0, sizeof(RwUInt32) + sizeof(state->levels));
    memset(&state->noMixBins, 0, sizeof(RwUInt32) + sizeof(state->mixBins));

    gains = params->mixBins;
    if (gains)
    {
        RwUInt32    matched = 0;
        RwUInt32    i;
        rwaXboxVoiceFind search;

        for (i = 0; i < unk_430448.count; i++)
        {
            RwUInt32    j;

            for (j = 0; j < gains->count; j++)
            {
                if (unk_430448.levels[i].mixBin == gains->entries[j].mixBin)
                {
                    matched++;
                    break;
                }
            }
            if (matched == unk_430448.count)
            {
                break;
            }
        }
        if (matched == unk_430448.count)
        {
            state->flags |= rwaXBVOICE3DBINS;
            state->noMixBins = params->mixBins->count;
            sub_24DF80(params->mixBins, state->mixBins);
        }
        else if (matched <= 0)
        {
            state->flags |= rwaXBVOICE2DBINS;
            state->noMixBins = params->mixBins->count;
            sub_24DF80(params->mixBins, state->mixBins);
        }

        search.id = 0;
        search.found = NULL;
        for (i = 0; i < state->noMixBins; i++)
        {
            search.id = state->mixBins[i].mixBin;
            sub_23F090((RwBool (*)(rwaInstance *, void *))sub_24ED50, &search);
            if (search.found)
            {
                state->target = search.found;
                break;
            }
        }
    }

    state->flags |= state->target ? 0x10000 : 0;
    state->output = (rwaXboxOutputState *)parent->state;
    {
    RwaV3d      zero;

    state->ds3d.mode = (state->flags >> 3) & 1;
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    state->ds3d.size = sizeof(rwaDS3DBuffer);
    state->ds3d.coneOrientation.x = 0.0f;
    state->ds3d.coneOrientation.y = 0.0f;
    state->ds3d.coneOrientation.z = 1.0f;
    state->ds3d.insideConeAngle = 360;
    state->ds3d.outsideConeAngle = 360;
    state->ds3d.coneOutsideVolume = 0;
    state->ds3d.distanceFactor = 1.0f;
    state->ds3d.rolloffFactor = 1.0f;
    state->ds3d.dopplerFactor = 1.0f;
    state->gain = 1.0f;
    state->frequency = 48000.0f;
    state->pan = 0.0f;
    state->position = 0;
    state->current = 0;
    state->start = 0;
    state->wave = NULL;
    if (!(state->flags & rwaXBVOICEMIXTARGET))
    {
        sub_24F410(obj, NULL);
        sub_24F200(obj, FALSE);
        sub_24F300(obj, FALSE);
    }
    sub_24F1D0(obj, 1.0f);
    sub_24F080(obj, &zero);
    sub_24F0E0(obj, &zero);
    sub_24F140(obj, 1.0f);
    sub_24F170(obj, 10000.0f);
    }
    rwaWaveFormatInit(&state->format);
    if (state->output->flags & 1)
    {
        rwaI3DL2Listener settings = {
            0, 0, 10.0f, 1.49f, 0.83f, -2602, 0.007f, 200, 0.011f, 100.0f, 100.0f, 5000.0f
        };

        sub_24F040(obj, &settings);
        state->flags |= rwaXBVOICEI3DL2;
        sub_24EF80(obj, 0);
        sub_24EFA0(obj, 0);
        sub_24EFC0(obj, 0.25f);
        sub_24EFF0(obj, 0);
        sub_24F010(obj, 0.25f);
    }

    if (state->flags & rwaXBVOICEMIXTARGET)
    {
        rwaXboxOutputState *output = state->output;
        rwaMixBins  mixBins;
        rwaBufferDesc desc;

        state->flags |= (state->flags & 7) ? 0x20 : 0;
        sub_24F380(&mixBins, output->speakerMode, (state->flags >> 5) & 1, 2);
        if (state->flags & 0x20)
        {
            if (state->flags & rwaXBVOICE3DBINS)
            {
                mixBins.count = state->noMixBins;
                mixBins.levels = state->mixBins;
            }
        }
        else if (state->flags & rwaXBVOICE2DBINS)
        {
            mixBins.count = state->noMixBins;
            mixBins.levels = state->mixBins;
        }
        desc.bufferBytes = 0;
        desc.format = NULL;
        desc.flags = ((state->flags & 0x8000) ? 0x2000 : rwaDSBCAPS_FXIN)
                     | ((state->flags & 7) ? 0x10 : 0);
        desc.inputMixBin = state->id;
        desc.size = sizeof(rwaBufferDesc);
        desc.mixBins = &mixBins;
        if (IDirectSound_CreateSoundBuffer(output->dsound, &desc, &state->buffer, NULL) < 0)
        {
            return NULL;
        }
        sub_24ECC0(state, (state->flags >> 5) & 1);
        state->noLevels = mixBins.count;
        memcpy(state->levels, mixBins.levels, mixBins.count * sizeof(rwaMixBinLevel));
    }

    state->output->unk02++;

    return obj;
}

/* Stops a voice mixing into target (a voice being destroyed). */
// match: _sub_2502A0 @ 0x002502A0
// sp-match: _sub_2502A0 @ 0x00163290
static RwBool
sub_2502A0(rwaXboxVoice *obj, rwaXboxVoice *target)
{
    if (!RwaUUIDCompare(obj->inst.def->uniqueID.uuid, &unk_3EDF6C)
        && obj->state.target == target && sub_24F240(obj))
    {
        sub_24F410(obj, NULL);
    }

    return TRUE;
}

// match: _sub_2502F0 @ 0x002502F0
// sp-match: _sub_2502F0 @ 0x001632E0
static void
sub_2502F0(rwaXboxVoice *obj, void *a, void *b)
{
    if (obj->state.flags & rwaXBVOICEMIXTARGET)
    {
        sub_23F090((RwBool (*)(rwaInstance *, void *))sub_2502A0, obj);
    }
    sub_24F410(obj, NULL);
    if (obj->state.buffer)
    {
        IDirectSoundBuffer_Release(obj->state.buffer);
        obj->state.buffer = NULL;
    }
    obj->state.output->unk02--;
}

/* Applies what changed: the 3D position (relative to the listener's
 * when head relative) and gain, frequency, volume, pan, play state, the
 * play position and the I3DL2 settings.
 * The qualified listener/gain reads retain the observed reload and x87
 * operand order without changing the shared output type. The local getter
 * pointer preserves the call's unknown-write boundary; VC7.1 resolves it
 * to the original direct call. The original declaration forms are unknown. */
// match: _sub_250340 @ 0x00250340
// sp-match: _sub_250340 @ 0x00163330
rwaXboxVoice *
sub_250340(rwaXboxVoice *obj)
{
    if (*(rwaInstance *volatile *)&obj->state.output->listener && (obj->state.flags & 0x20)
        && (obj->state.wave || (obj->state.flags & rwaXBVOICEMIXTARGET))
        && ((obj->state.flags & 0x10)
            || (((rwaListener *)obj->state.output->listener)->dirty & 0xF)))
    {
        rwa3DSource source;
        RwReal      gains[6];

        source.maxDistance = sub_24F190(obj);
        source.minDistance = sub_24F160(obj);
        sub_24F0B0(obj, &source.position);
        {
            void (*getVelocity)(rwaXboxVoice *, RwaV3d *) = sub_24F110;
            getVelocity(obj, &source.velocity);
        }
        if (obj->state.flags & 8)
        {
            rwaListener *listener = (rwaListener *)obj->state.output->listener;
            RwaV3d      pos = listener->pos;
            RwaV3d      vel = listener->vel;

            source.position.x = source.position.x + pos.x;
            source.position.y = source.position.y + pos.y;
            source.position.z = source.position.z + pos.z;
            source.velocity.x = source.velocity.x + vel.x;
            source.velocity.y = source.velocity.y + vel.y;
            source.velocity.z = source.velocity.z + vel.z;
        }
        sub_23CD40(&obj->state.output->listener, 1, &source, gains,
                   obj->state.output->speakerMode);
        obj->state.gain = gains[0];
        obj->state.flags |= 0x100;
        if (obj->state.flags & 0x10)
        {
            IDirectSoundBuffer_SetAllParameters(obj->state.buffer, &obj->state.ds3d, 0);
            obj->state.flags &= ~0x10;
        }
    }

    if (obj->state.flags & 0x4000)
    {
        if (!(obj->state.flags & 0x80))
        {
            sub_24F1A0(obj, (RwReal)obj->state.wave->deviceFormat.sampleRate);
        }
        obj->state.flags &= ~0x4000;
    }
    if (obj->state.wave && (obj->state.flags & 0x80))
    {
        IDirectSoundBuffer_SetFrequency(obj->state.buffer, (RwInt32)obj->state.frequency);
        obj->state.flags &= ~0x80;
    }
    if ((obj->state.flags & 0x100) && (obj->state.wave || (obj->state.flags & rwaXBVOICEMIXTARGET)))
    {
        IDirectSoundBuffer_SetVolume(obj->state.buffer,
                                     sub_241F90(*(volatile RwReal *)&obj->state.output->unk04
                                                * obj->state.gain * obj->state.volume
                                                * flt_3EDF84
                                                + flt_3EDF80));
        obj->state.flags &= ~0x100;
    }
    if ((obj->state.flags & 0x200) && obj->state.wave && !(obj->state.flags & 0x20))
    {
        RwReal      left;
        RwReal      right;
        rwaMixBins  mixBins;

        left = (obj->state.pan > 0.0f) ? 1.0f : obj->state.pan + 1.0f;
        right = (obj->state.pan < 0.0f) ? 1.0f : 1.0f - obj->state.pan;
        obj->state.levels[0].level = sub_241F90(right);
        obj->state.levels[1].level = sub_241F90(left);
        mixBins.count = obj->state.noLevels;
        mixBins.levels = obj->state.levels;
        IDirectSoundBuffer_SetMixBinVolumes(obj->state.buffer, &mixBins);
        obj->state.flags &= ~0x200;
    }

    if (sub_24ED90(obj->state.buffer))
    {
        IDirectSoundBuffer_GetCurrentPosition(obj->state.buffer, &obj->state.current, NULL);
    }
    else
    {
        obj->state.current = obj->state.start;
    }
    if (obj->state.wave)
    {
        if (obj->state.flags & 0x400)
        {
            if (obj->state.flags & 0x800)
            {
                IDirectSoundBuffer_SetCurrentPosition(obj->state.buffer, obj->state.start);
                if (IDirectSoundBuffer_Play(obj->state.buffer, 0, 0,
                                            (obj->state.flags >> 13) & 1) >= 0)
                {
                    obj->state.current = obj->state.start;
                    obj->state.start = 0;
                }
            }
            else
            {
                IDirectSoundBuffer_StopEx(obj->state.buffer, 0, 0, 0);
                obj->state.current = 0;
            }
            obj->state.flags &= ~0xC00;
        }
        {
            RwUInt32 position;
            if (!RwaUUIDCompare(obj->state.wave->format.dataType, &unk_3ED5FC))
            {
                position = (obj->state.current / obj->state.wave->format.noChannels << 6)
                                      / 36;
            }
            else
            {
                position = obj->state.current * 8
                                      / (obj->state.wave->format.bitDepth
                                         * obj->state.wave->format.noChannels);
            }
            obj->state.position = position;
        }
    }
    else
    {
        obj->state.position = 0;
    }

    obj->state.flags &= ~0x1000;
    if ((obj->state.flags & 0x40) && (obj->state.wave || (obj->state.flags & rwaXBVOICEMIXTARGET)))
    {
        if ((obj->state.output->flags & 1) && (obj->state.flags & rwaXBVOICEI3DL2))
        {
            rwaI3DL2Source source;

            source.directHF = 0;
            source.roomRolloffFactor = obj->state.i3dl2.roomRolloffFactor;
            source.direct = obj->state.direct;
            source.room = obj->state.i3dl2.room;
            source.roomHF = obj->state.i3dl2.roomHF;
            source.obstructionLFRatio = obj->state.obstructionLFRatio;
            source.obstruction = obj->state.obstruction;
            source.occlusionLFRatio = obj->state.occlusionLFRatio;
            source.occlusion = obj->state.occlusion;
            IDirectSoundBuffer_SetI3DL2Source(obj->state.buffer, &source, 0);
        }
        obj->state.flags &= ~0x40;
    }

    return obj;
}


// match: _sub_2507B0 @ 0x002507B0
// sp-match: _sub_2507B0 @ 0x001637A0
static void
sub_2507B0(rwaObjDef *def)
{
    RwaObjDefAssignID(def, &unk_3EDF6C, NULL);

    def->flags = sizeof(rwaXboxVoiceState);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_24FE10;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_2502F0;
    def->unk30 = (rwaInstance *(*)(rwaInstance *))sub_250340;
    def->query = (void (*)(void *, void *))sub_24EE40;
    def->paramsSize = sizeof(rwaXboxVoiceParams);
}

// match: _sub_2509F0 @ 0x002509F0
// sp-match: _sub_2509F0 @ 0x001639E0
rwaObjDef *
sub_2509F0(void)
{
    rwaObjDef  *def = sub_23DFB0(sub_23DCA0(NULL, &unk_3EDF5C, NULL), 0, &unk_507D80, NULL, NULL,
                                 rwaMEMHINTDUR_EVENT | rwaID_80D);

    if (!def)
    {
        return NULL;
    }

    sub_2507B0(def);

    return def;
}

// match: _sub_250A30 @ 0x00250A30
// sp-match: _sub_250A30 @ 0x00163A20
rwaObjDef *
sub_250A30(void)
{
    rwaObjDef  *def = sub_23DFB0(sub_23DCA0(NULL, &unk_3EDF5C, NULL), 0xC, &unk_507D80, unk_507D68,
                                 unk_507DDC, rwaMEMHINTDUR_EVENT | rwaID_80D);
    void       *iface;

    if (!def)
    {
        return NULL;
    }

    sub_2507B0(def);

    if (!_rwaObjDefSetupParams(def, off_430678, 22, off_430888, 23))
    {
        sub_23DB90(def);

        return NULL;
    }

    iface = sub_251FA0();
    if (!iface)
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, iface);
    dword_507DE4 = TRUE;

    return def;
}
