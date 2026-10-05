/*
 * codfh-match: RenderWare Audio's Xbox WMA stream source (0x250B20-0x252000;
 * VC7.1): the definition at 0x507E18, a stream node decoding a WMA file
 * (WmaCreateDecoderEx) into a ring of packets. One WMA thread (shared by
 * the sources, counted at 0x507EB8) keeps every listed source's ring filled
 * and seeks or loops them; the play queue reads the filled packets. Then
 * the parameter handlers, the definition's set-up and registration, and the
 * voice interface the voice definition registers (0x250A30).
 */
#include "rwa.h"
#include "rwaint.h"



extern RwUInt32 __stdcall WaitForSingleObject(void *handle, RwUInt32 milliseconds);
extern RwBool __stdcall ReleaseSemaphore(void *semaphore, RwInt32 count, RwInt32 *previous);
extern RwBool __stdcall CloseHandle(void *handle);
extern void __stdcall Sleep(RwUInt32 milliseconds);
extern RwInt32 __stdcall WideCharToMultiByte(RwUInt32 codePage, RwUInt32 flags,
                                             const RwUInt16 *wide, RwInt32 noWide,
                                             RwChar *multi, RwInt32 noMulti,
                                             const RwChar *defaultChar, RwBool *usedDefault);
extern RwInt32 __stdcall WmaCreateDecoderEx(const RwChar *fileName, void *file, RwBool async,
                                            RwUInt32 lookahead, RwUInt32 maxPackets,
                                            RwUInt32 yieldRate, rwaWaveFormatEx *format,
                                            rwaXMediaObject **decoder);
extern void *memset(void *dst, RwInt32 value, RwUInt32 size);

extern RwBool sub_23DB90(rwaObjDef *def);
extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);
extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern void **sub_2416D0(void **semaphore, RwInt32 initial, RwInt32 maximum);
extern void *_RwaThreadCreate(void *thread, RwUInt32 (*func)(void *data), RwInt32 priority,
                              RwUInt32 stackSize);
extern void *sub_241770(void *thread, void *data);
extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern RwUInt32 sub_242A30(const RwaWaveFormat *format);
extern RwUInt32 sub_242E30(const RwaWaveFormat *format);
extern RwBool sub_243B80(void *objInterface);
extern void *sub_243E20(void *iface);
extern void RwaWaveDictAssignID(void *iface, const void *uuid, const void *textID);
extern void sub_243CD0(void *iface, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_243EA0(void *iface);
extern void *sub_243F40(const void *uuid);
extern void *sub_243FF0(void *objInterface, rwaObjDef *def, RwUInt32 a, RwUInt32 b);
extern RwBool sub_246FD0(rwaDecoder *obj, rwaInstance *parent, rwaStreamNodeParams *params,
                         void *a, void *b);
extern void RwaStreamNodeCreationComplete(rwaDecoder *obj);
extern void sub_2470A0(rwaDecoder *obj);
extern rwaDecoder *RwaStreamNodeGetParams(rwaDecoder *obj, rwaStreamNodeParams *params);
extern void sub_247120(rwaDecoder *obj, void *a, void *b);
extern void sub_247160(rwaDecoder *obj, void *data, RwInt32 *mode);
extern void sub_2471D0(rwaDecoder *obj, void *data, rwaStreamConnect *connect);
extern void sub_2472E0(rwaQueue *queue, rwaQueueItem *items, RwUInt32 count);
extern rwaQueueItem *sub_247300(rwaQueue *queue);
extern void sub_247340(rwaQueue *queue, rwaQueueItem *item);
extern void sub_24D9F0(rwaStreamMarker *marker);
extern void sub_24DA10(rwaStreamTrack *track);
extern void sub_24DA40(rwaStreamInfo *info);

extern rwaObjDef *dword_516C60;
extern rwaObjDef unk_507E18;        /* the WMA stream source definition */
extern RwUInt8 unk_507E74[];
extern RwUInt8 unk_507EA8[];
extern RwBool dword_507E10;         /* the WMA thread runs */
extern void *dword_507E8C;          /* the thread's exit */
extern void *dword_507E90;          /* the list's semaphore */
extern RwUInt8 dword_507E94[];      /* the WMA thread */
extern rwaLink dword_507EB0;        /* the sources the thread fills */
extern RwInt32 dword_507EB8;        /* the sources open */
extern RwUInt8 dword_507EBC[];      /* the voice interface */
extern RwInt32 dword_506B44;        /* the thread's priority */
extern const RwUInt8 unk_3ED9C4[];
extern const RwaUUID unk_3ED5CC;    /* PCM */
extern const RwUInt8 unk_3EDFC8[];  /* the WMA stream source */
extern const RwUInt8 unk_3EDFD8[];  /* the voice interface */

#define rwaINFINITE 0xFFFFFFFF

extern void sub_250D90(rwaWmaSource *obj, rwaStreamPosition *position);
extern RwUInt32 sub_251210(void *data);
extern rwaWmaSource *sub_2516E0(rwaWmaSource *obj, rwaInstance *parent, rwaWmaParams *params,
                                void *a, void *b);
extern void *sub_250C10(rwaWmaSource *obj, rwaWmaParams *params);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3EDE98 @ 0x003EDE98
// match: _unk_3EDE8C @ 0x003EDE8C
// match: _unk_3EDE80 @ 0x003EDE80
// match: _unk_3EDE74 @ 0x003EDE74
// match: _unk_3EDE68 @ 0x003EDE68
// match: _unk_3EDE5C @ 0x003EDE5C
// match: _unk_3EDE50 @ 0x003EDE50
// match: _unk_3EDE44 @ 0x003EDE44
// match: _unk_3EDE38 @ 0x003EDE38
// match: _unk_3EDE2C @ 0x003EDE2C
// match: _unk_3EDE20 @ 0x003EDE20
// match: _unk_3EDE14 @ 0x003EDE14
// match: _unk_3EDE08 @ 0x003EDE08
// match: _unk_3EDDFC @ 0x003EDDFC
// match: _unk_3EDDF0 @ 0x003EDDF0
// match: _unk_3EDDE4 @ 0x003EDDE4
// match: _unk_3EDDD8 @ 0x003EDDD8
// match: _unk_3EDDCC @ 0x003EDDCC
// match: _unk_3EDDC0 @ 0x003EDDC0
// match: _unk_3EDDB4 @ 0x003EDDB4
// match: _unk_3EDDA8 @ 0x003EDDA8
// match: _unk_3EDD9C @ 0x003EDD9C
// match: _unk_3EDD90 @ 0x003EDD90
// match: _unk_3EDD84 @ 0x003EDD84
// match: _unk_3EDD78 @ 0x003EDD78
// match: _unk_3EDD6C @ 0x003EDD6C
// match: _unk_3EDD60 @ 0x003EDD60
// match: _unk_3EDD54 @ 0x003EDD54
// match: _unk_3EDD48 @ 0x003EDD48
// match: _unk_3EDD3C @ 0x003EDD3C
// match: _unk_3EDD30 @ 0x003EDD30
// match: _unk_3EDD24 @ 0x003EDD24
// match: _unk_3EDD18 @ 0x003EDD18
// match: _unk_3EDD0C @ 0x003EDD0C
// match: _unk_3EDD00 @ 0x003EDD00
// match: _unk_3EDCF4 @ 0x003EDCF4
// match: _unk_3EDCE8 @ 0x003EDCE8
// match: _unk_3EDCDC @ 0x003EDCDC
// match: _unk_3EDCD0 @ 0x003EDCD0
// match: _unk_3EDCC4 @ 0x003EDCC4
// match: _unk_3EDCB8 @ 0x003EDCB8
// match: _unk_3EDCAC @ 0x003EDCAC
// match: _unk_3EDCA0 @ 0x003EDCA0
// match: _unk_3EDC94 @ 0x003EDC94
// match: _unk_3EDC88 @ 0x003EDC88
// match: _unk_3EDC7C @ 0x003EDC7C
// match: _unk_3EDC70 @ 0x003EDC70
// match: _unk_3EDC64 @ 0x003EDC64
// match: _unk_3EDC58 @ 0x003EDC58
// match: _unk_3EDC4C @ 0x003EDC4C
// match: _unk_3EDC40 @ 0x003EDC40
// match: _unk_3EDC2C @ 0x003EDC2C
// match: _unk_3EDC18 @ 0x003EDC18
// match: _unk_3EDC04 @ 0x003EDC04
// match: _unk_3EDBF0 @ 0x003EDBF0
// match: _off_430BD0 @ 0x00430BD0
// match: _off_430C48 @ 0x00430C48
// match: _unk_430CD0 @ 0x00430CD0

// What its data definitions name.
extern void sub_247140(void);
extern void sub_2471F0(void);
rwaWmaSource *sub_250FF0(rwaWmaSource *obj, const void *param, rwaStreamPosition *value);
rwaWmaSource *sub_251010(rwaWmaSource *obj, const void *param, const RwBool *value);
rwaWmaSource *sub_251030(rwaWmaSource *obj, const void *param, RwBool *value);
rwaWmaSource *sub_251050(rwaWmaSource *obj, const void *param, const RwInt32 *value);
rwaWmaSource *sub_251070(rwaWmaSource *obj, const void *param, rwaStreamInfo **value);
rwaWmaSource *sub_251090(rwaWmaSource *obj, const void *param, rwaStreamConnect *value);
rwaWmaSource *sub_2510B0(rwaWmaSource *obj, const void *param, const RwUInt32 *value);
rwaWmaSource *sub_2511F0(rwaWmaSource *obj, const void *param, rwaStreamSeek *value);
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
extern RwUInt8 unk_3ED60C[];
extern RwUInt8 unk_3ED65C[];
extern RwUInt8 unk_3ED974[];
extern RwUInt8 unk_3ED984[];
extern RwUInt8 unk_3ED994[];
extern RwUInt8 unk_3ED9A4[];
extern RwUInt8 unk_3ED9B4[];
extern RwUInt8 unk_3ED9D4[];
extern RwUInt8 unk_3ED9E4[];
extern RwUInt8 unk_3ED9F4[];
extern RwUInt8 unk_3EDA04[];
extern RwUInt8 unk_3EDA14[];
extern RwUInt8 unk_3EDA24[];
extern RwUInt8 unk_3EDA38[];
extern RwUInt8 unk_3EDA4C[];
extern RwUInt8 unk_3EDA60[];
extern RwUInt8 unk_3EDA74[];
extern RwUInt8 unk_3EDA88[];
extern RwUInt8 unk_3EDA9C[];
extern RwUInt8 unk_3EDAB0[];
extern RwUInt8 unk_3EDAC4[];
extern RwUInt8 unk_3EDAD8[];
extern RwUInt8 unk_3EDAEC[];
extern RwUInt8 unk_3EDB00[];
extern RwUInt8 unk_3EDB14[];
extern RwUInt8 unk_3EDB28[];
extern RwUInt8 unk_3EDB3C[];
extern RwUInt8 unk_3EDB50[];
extern RwUInt8 unk_3EDB64[];
extern RwUInt8 unk_3EDB8C[];
extern RwUInt8 unk_3EDBA0[];
extern RwUInt8 unk_3EDFE8[];
extern RwUInt8 unk_3EDFF8[];
extern RwUInt8 unk_3EE008[];
extern RwUInt8 unk_3EE018[];
extern RwUInt8 unk_3EE028[];
extern RwUInt8 unk_3EE038[];
extern RwUInt8 unk_3EE048[];
extern RwUInt8 unk_3EE058[];
extern RwUInt8 unk_3EE068[];
extern RwUInt8 unk_3EE078[];
extern RwUInt8 unk_3EE088[];
extern RwUInt8 unk_3EE098[];
extern RwUInt8 unk_3EE0A8[];
extern RwUInt8 unk_3EE0B8[];
extern RwUInt8 unk_3EE0C8[];
extern RwUInt8 unk_3EE0D8[];
extern RwUInt8 unk_3EE0E8[];
extern RwUInt8 unk_3EE0F8[];
extern RwUInt8 unk_3EE108[];
extern RwUInt8 unk_3EE118[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003EDBF0
void *const unk_3EDBF0[5] =
{
    (void *)&unk_3ED60C,
    (void *)0x110,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDC04
void *const unk_3EDC04[5] =
{
    (void *)&unk_3ED60C,
    (void *)0x210,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDC18
void *const unk_3EDC18[5] =
{
    (void *)&unk_3ED65C,
    (void *)0x104,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDC2C
void *const unk_3EDC2C[5] =
{
    (void *)&unk_3ED65C,
    (void *)0x204,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDC40
void *const unk_3EDC40[3] =
{
    (void *)&unk_3EDB00,
    (void *)&unk_3EDB8C,
    0,
};
// 0x003EDC4C
void *const unk_3EDC4C[3] =
{
    (void *)&unk_3EDA24,
    (void *)&unk_3EDA24,
    (void *)0x1,
};
// 0x003EDC58
void *const unk_3EDC58[3] =
{
    (void *)&unk_3EDA24,
    (void *)&unk_3EDA38,
    0,
};
// 0x003EDC64
void *const unk_3EDC64[3] =
{
    (void *)&unk_3EDA24,
    (void *)&unk_3EDA74,
    0,
};
// 0x003EDC70
void *const unk_3EDC70[3] =
{
    (void *)&unk_3EDA24,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDC7C
void *const unk_3EDC7C[3] =
{
    (void *)&unk_3EDA24,
    (void *)&unk_3EDA4C,
    0,
};
// 0x003EDC88
void *const unk_3EDC88[3] =
{
    (void *)&unk_3EDA4C,
    (void *)&unk_3EDA24,
    0,
};
// 0x003EDC94
void *const unk_3EDC94[3] =
{
    (void *)&unk_3EDA4C,
    (void *)&unk_3EDA4C,
    (void *)0x1,
};
// 0x003EDCA0
void *const unk_3EDCA0[3] =
{
    (void *)&unk_3EDA38,
    (void *)&unk_3EDA38,
    (void *)0x1,
};
// 0x003EDCAC
void *const unk_3EDCAC[3] =
{
    (void *)&unk_3EDA38,
    (void *)&unk_3EDA24,
    0,
};
// 0x003EDCB8
void *const unk_3EDCB8[3] =
{
    (void *)&unk_3EDA38,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDCC4
void *const unk_3EDCC4[3] =
{
    (void *)&unk_3EDA38,
    (void *)&unk_3EDA74,
    0,
};
// 0x003EDCD0
void *const unk_3EDCD0[3] =
{
    (void *)&unk_3EDA38,
    (void *)&unk_3EDA60,
    0,
};
// 0x003EDCDC
void *const unk_3EDCDC[3] =
{
    (void *)&unk_3EDA60,
    (void *)&unk_3EDA38,
    0,
};
// 0x003EDCE8
void *const unk_3EDCE8[3] =
{
    (void *)&unk_3EDA60,
    (void *)&unk_3EDA60,
    (void *)0x1,
};
// 0x003EDCF4
void *const unk_3EDCF4[3] =
{
    (void *)&unk_3EDA74,
    (void *)&unk_3EDA74,
    (void *)0x1,
};
// 0x003EDD00
void *const unk_3EDD00[3] =
{
    (void *)&unk_3EDA74,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDD0C
void *const unk_3EDD0C[3] =
{
    (void *)&unk_3EDA74,
    (void *)&unk_3EDA24,
    0,
};
// 0x003EDD18
void *const unk_3EDD18[3] =
{
    (void *)&unk_3EDA74,
    (void *)&unk_3EDA38,
    0,
};
// 0x003EDD24
void *const unk_3EDD24[3] =
{
    (void *)&unk_3EDA74,
    (void *)&unk_3EDA9C,
    0,
};
// 0x003EDD30
void *const unk_3EDD30[3] =
{
    (void *)&unk_3EDA9C,
    (void *)&unk_3EDA74,
    0,
};
// 0x003EDD3C
void *const unk_3EDD3C[3] =
{
    (void *)&unk_3EDA9C,
    (void *)&unk_3EDA9C,
    (void *)0x1,
};
// 0x003EDD48
void *const unk_3EDD48[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDA88,
    (void *)0x1,
};
// 0x003EDD54
void *const unk_3EDD54[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDA74,
    0,
};
// 0x003EDD60
void *const unk_3EDD60[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDA38,
    0,
};
// 0x003EDD6C
void *const unk_3EDD6C[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDA24,
    0,
};
// 0x003EDD78
void *const unk_3EDD78[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDAEC,
    0,
};
// 0x003EDD84
void *const unk_3EDD84[3] =
{
    (void *)&unk_3EDAEC,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDD90
void *const unk_3EDD90[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDB00,
    0,
};
// 0x003EDD9C
void *const unk_3EDD9C[3] =
{
    (void *)&unk_3EDB00,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDDA8
void *const unk_3EDDA8[3] =
{
    (void *)&unk_3EDB00,
    (void *)&unk_3EDB00,
    0,
};
// 0x003EDDB4
void *const unk_3EDDB4[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDAB0,
    0,
};
// 0x003EDDC0
void *const unk_3EDDC0[3] =
{
    (void *)&unk_3EDAB0,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDDCC
void *const unk_3EDDCC[3] =
{
    (void *)&unk_3EDAB0,
    (void *)&unk_3EDAB0,
    (void *)0x1,
};
// 0x003EDDD8
void *const unk_3EDDD8[3] =
{
    (void *)&unk_3EDAB0,
    (void *)&unk_3EDB14,
    0,
};
// 0x003EDDE4
void *const unk_3EDDE4[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDB8C,
    0,
};
// 0x003EDDF0
void *const unk_3EDDF0[3] =
{
    (void *)&unk_3EDB8C,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDDFC
void *const unk_3EDDFC[3] =
{
    (void *)&unk_3EDAB0,
    (void *)&unk_3EDBA0,
    0,
};
// 0x003EDE08
void *const unk_3EDE08[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDB28,
    0,
};
// 0x003EDE14
void *const unk_3EDE14[3] =
{
    (void *)&unk_3EDAB0,
    (void *)&unk_3EDB3C,
    0,
};
// 0x003EDE20
void *const unk_3EDE20[3] =
{
    (void *)&unk_3EDB28,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDE2C
void *const unk_3EDE2C[3] =
{
    (void *)&unk_3EDB3C,
    (void *)&unk_3EDAB0,
    0,
};
// 0x003EDE38
void *const unk_3EDE38[3] =
{
    (void *)&unk_3EDB28,
    (void *)&unk_3EDB28,
    0,
};
// 0x003EDE44
void *const unk_3EDE44[3] =
{
    (void *)&unk_3EDAC4,
    (void *)&unk_3EDB50,
    0,
};
// 0x003EDE50
void *const unk_3EDE50[3] =
{
    (void *)&unk_3EDAD8,
    (void *)&unk_3EDB64,
    0,
};
// 0x003EDE5C
void *const unk_3EDE5C[3] =
{
    (void *)&unk_3EDAC4,
    (void *)&unk_3EDAC4,
    (void *)0x1,
};
// 0x003EDE68
void *const unk_3EDE68[3] =
{
    (void *)&unk_3EDAD8,
    (void *)&unk_3EDAD8,
    (void *)0x1,
};
// 0x003EDE74
void *const unk_3EDE74[3] =
{
    (void *)&unk_3EDA88,
    (void *)&unk_3EDC18,
    0,
};
// 0x003EDE80
void *const unk_3EDE80[3] =
{
    (void *)&unk_3EDAB0,
    (void *)&unk_3EDC2C,
    0,
};
// 0x003EDE8C
void *const unk_3EDE8C[3] =
{
    (void *)&unk_3EDC18,
    (void *)&unk_3EDA88,
    0,
};
// 0x003EDE98
void *const unk_3EDE98[3] =
{
    (void *)&unk_3EDC2C,
    (void *)&unk_3EDAB0,
    0,
};
// 0x00430BD0
void *off_430BD0[30] =
{
    (void *)&unk_3ED9D4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2511F0,
    (void *)&unk_3ED9F4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_251010,
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_251050,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_251090,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_2510B0,
};
// 0x00430C48
void *off_430C48[34] =
{
    (void *)&unk_3ED9E4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_250FF0,
    (void *)&unk_3EDA04,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)sub_251030,
    (void *)&unk_3EDA14,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_251070,
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)sub_247140,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)sub_2471F0,
    (void *)0x616D77,
    (void *)&off_430C48[30],
    (void *)&unk_3EDBF0,
    (void *)&unk_3EDC04,
};
// 0x00430CD0
void *unk_430CD0[6] =
{
    (void *)0x3,
    (void *)&off_430C48[31],
    (void *)0x1,
    (void *)&off_430C48[32],
    (void *)0x2,
    0,
};
// 0x00430CE8
void *off_430CE8[110] =
{
    (void *)&unk_3EDFE8,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3EE008,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3EE028,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3EE048,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3EE068,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3EE088,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3EE0A8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3EE0C8,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3EE0E8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3EE108,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED3DC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED3FC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED41C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED43C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2DC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2FC,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED31C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED33C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED35C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED37C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED3AC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
};
// 0x00430EA0
void *off_430EA0[117] =
{
    (void *)&unk_3EDFF8,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3EE018,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3EE038,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3EE058,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3EE078,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3EE098,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3EE0B8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3EE0D8,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3EE0F8,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3EE118,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED3EC,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED40C,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED42C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED44C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2CC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED2EC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED30C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED32C,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED34C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED36C,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED38C,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED39C,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED3BC,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)0x80,
    (void *)0x1,
};
// 0x00506B44
RwInt32 dword_506B44;
// 0x00507E10
RwBool dword_507E10;
// 0x00507E18
rwaObjDef unk_507E18;
// 0x00507E74
RwUInt8 unk_507E74[24];
// 0x00507E8C
void *dword_507E8C;
// 0x00507E90
void *dword_507E90;
// 0x00507E94
RwUInt8 dword_507E94[20];
// 0x00507EA8
RwUInt8 unk_507EA8[8];
// 0x00507EB0
rwaLink dword_507EB0;
// 0x00507EB8
RwInt32 dword_507EB8;
// 0x00507EBC
RwUInt8 dword_507EBC[40];
// End of its data definitions.

// match: _off_430CE8 @ 0x00430CE8


// match: _off_430EA0 @ 0x00430EA0

// match: _sub_250B20 @ 0x00250B20

RwBool
sub_250B20(void)
{
    return sub_23DB90(&unk_507E18);
}

/* Closes a source: the last stops the WMA thread. */
// match: _sub_250B30 @ 0x00250B30
void
sub_250B30(void)
{
    if (!--dword_507EB8)
    {
        dword_507E10 = FALSE;
        WaitForSingleObject(dword_507E8C, rwaINFINITE);
        CloseHandle(dword_507E90);
        CloseHandle(dword_507E8C);
    }
}

// match: _sub_250B70 @ 0x00250B70
void
sub_250B70(rwaWmaSource *obj, void *a, void *b)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;

    WaitForSingleObject(dword_507E90, rwaINFINITE);
    if (state->link.next)
    {
        state->link.prev->next = state->link.next;
        state->link.next->prev = state->link.prev;
    }
    ReleaseSemaphore(dword_507E90, 1, NULL);

    state->decoder->vtbl->release(state->decoder);
    CloseHandle(state->semaphore);
    sub_2421B0(state->items);
    sub_250B30();
    sub_243B80(state->objInterface);
    sub_247120((rwaDecoder *)obj, a, b);
}

/* The default creation parameters. */
// match: _sub_250C10 @ 0x00250C10
void *
sub_250C10(rwaWmaSource *obj, rwaWmaParams *params)
{
    RwaStreamNodeGetParams((rwaDecoder *)obj, (rwaStreamNodeParams *)params);
    params->unk00 = 0;
    params->unk04 = 1;
    params->unk34 = 0;
    params->unk38 = 0;
    params->unk24 = 0;
    params->unk1C = 0;
    params->unk20 = 0;
    params->file = NULL;
    params->unk28 = 0;
    params->unk4C = 0;
    params->unk54 = 0;
    params->unk50 = 0;
    params->unk48 = 0;
    params->yieldRate = 0;
    params->fileType = 1;
    params->minPackets = 2;
    params->noPackets = 4;
    params->lookahead = 0xF000;

    return obj;
}


/* The play queue's read: the next filled packet, as a queue item. */
// match: _sub_250C80 @ 0x00250C80
rwaQueueItem *
sub_250C80(rwaWmaSource *obj)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    rwaWmaPacket *packet = &state->packets[state->read];
    rwaQueueItem *item;

    if (packet->state)
    {
        WaitForSingleObject(state->semaphore, rwaINFINITE);
        item = sub_247300(&state->queue);
        if (item)
        {
            RwUInt32    size = *packet->header.completed;

            if (packet->state == 2)
            {
                item->flags |= 8;
            }
            if (size < state->packetSize)
            {
                memset(item->unk04 + size, 0, state->packetSize - size);
                size = state->packetSize;
            }
            item->unk04 = packet->header.buffer;
            item->unk08 = size;
            item->position->pos =
                (RwUInt32)((RwUInt64)(state->format.sampleRate * 8) / state->bitrate
                           * state->position >> 3);
            ((rwaWmaPosition *)item->position)->packet = packet;
            if (++state->read == state->noPackets)
            {
                state->read = 0;
            }
        }
        ReleaseSemaphore(state->semaphore, 1, NULL);

        return item;
    }

    return NULL;
}

/* The play position, in seconds or (unit 2) samples.
 * The unit switch preserves the original SUB dispatch and ECX state pointer. */
// match: _sub_250D90 @ 0x00250D90
void
sub_250D90(rwaWmaSource *obj, rwaStreamPosition *position)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    RwReal      seconds;

    position->type = 3;
    position->value = 0;
    seconds = (RwReal)state->position * 0.001f;
    *(RwReal *)&position->pos = seconds;
    switch (position->unit)
    {
    case 2:
        position->pos = (RwUInt32)(state->format.sampleRate * seconds);
        break;
    }
}

// match: _sub_250E00 @ 0x00250E00
void
sub_250E00(rwaWmaSource *obj, RwBool loop)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;

    if (loop)
    {
        state->flags |= 1;
    }
    else
    {
        state->flags &= ~1;
    }
}

// match: _sub_250E30 @ 0x00250E30
RwBool
sub_250E30(rwaWmaSource *obj)
{
    return ((rwaWmaState *)obj->inst.state)->flags & 1;
}

/* Sets the node's mode, and lists the source for the WMA thread. */
// match: _sub_250E50 @ 0x00250E50
void
sub_250E50(rwaWmaSource *obj, RwInt32 mode)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    RwInt32     value = mode;

    sub_247160((rwaDecoder *)obj, NULL, &value);
    WaitForSingleObject(dword_507E90, rwaINFINITE);
    if (state->link.next)
    {
        state->link.prev->next = state->link.next;
        state->link.next->prev = state->link.prev;
    }
    if (obj->inst.link.next && (mode != 1 || state->node.status != 3))
    {
        state->link.next = dword_507EB0.next;
        state->link.prev = &dword_507EB0;
        dword_507EB0.next->prev = &state->link;
        dword_507EB0.next = &state->link;
    }
    ReleaseSemaphore(dword_507E90, 1, NULL);

    if (obj->inst.subObjLink.next)
    {
        obj->inst.subObjLink.prev->next = obj->inst.subObjLink.next;
        obj->inst.subObjLink.next->prev = obj->inst.subObjLink.prev;
        obj->inst.subObjLink.prev = NULL;
        obj->inst.subObjLink.next = NULL;
    }
}

// match: _sub_250F10 @ 0x00250F10
rwaStreamInfo *
sub_250F10(rwaWmaSource *obj)
{
    return &((rwaWmaState *)obj->inst.state)->info;
}

// match: _sub_250F20 @ 0x00250F20
void
sub_250F20(rwaWmaSource *obj, rwaStreamConnect *connect)
{
    sub_2471D0((rwaDecoder *)obj, NULL, connect);
    connect->reader->read = (rwaQueueItem *(*)(rwaDecoder *))sub_250C80;
    connect->reader->data = (rwaDecoder *)obj;
}

/* Drops the decoded packets. */
// match: _sub_250F50 @ 0x00250F50
void
sub_250F50(rwaWmaSource *obj, RwUInt32 unused)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;

    WaitForSingleObject(state->semaphore, rwaINFINITE);
    state->decoder->vtbl->flush(state->decoder);
    while (state->read != state->write)
    {
        state->packets[state->read].state = 0;
        if (++state->read == state->noPackets)
        {
            state->read = 0;
        }
    }
    if (!(state->flags & 4))
    {
        ReleaseSemaphore(state->semaphore, 1, NULL);
    }
}

// match: _sub_250FF0 @ 0x00250FF0
rwaWmaSource *
sub_250FF0(rwaWmaSource *obj, const void *param, rwaStreamPosition *value)
{
    sub_250D90(obj, value);
    return obj;
}

// match: _sub_251010 @ 0x00251010
rwaWmaSource *
sub_251010(rwaWmaSource *obj, const void *param, const RwBool *value)
{
    sub_250E00(obj, *value);
    return obj;
}

// match: _sub_251030 @ 0x00251030
rwaWmaSource *
sub_251030(rwaWmaSource *obj, const void *param, RwBool *value)
{
    *value = sub_250E30(obj);
    return obj;
}

// match: _sub_251050 @ 0x00251050
rwaWmaSource *
sub_251050(rwaWmaSource *obj, const void *param, const RwInt32 *value)
{
    sub_250E50(obj, *value);
    return obj;
}

// match: _sub_251070 @ 0x00251070
rwaWmaSource *
sub_251070(rwaWmaSource *obj, const void *param, rwaStreamInfo **value)
{
    *value = sub_250F10(obj);
    return obj;
}

// match: _sub_251090 @ 0x00251090
rwaWmaSource *
sub_251090(rwaWmaSource *obj, const void *param, rwaStreamConnect *value)
{
    sub_250F20(obj, value);
    return obj;
}

// match: _sub_2510B0 @ 0x002510B0
rwaWmaSource *
sub_2510B0(rwaWmaSource *obj, const void *param, const RwUInt32 *value)
{
    sub_250F50(obj, *value);
    return obj;
}

/* A queue item played: its packet is free again (the last one ends the
 * stream). */
// match: _sub_2510D0 @ 0x002510D0
void
sub_2510D0(rwaQueueItem *item, rwaWmaSource *obj)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    rwaWmaPacket *packet = ((rwaWmaPosition *)item->position)->packet;

    if (packet->state == 2)
    {
        sub_250E50(obj, 1);
    }
    WaitForSingleObject(state->semaphore, rwaINFINITE);
    sub_247340(&state->queue, item);
    ReleaseSemaphore(state->semaphore, 1, NULL);
    packet->state = 0;
}

/* Seeks (in seconds or samples; flushing first when asked) at the WMA
 * thread's next pass. */
// match: _sub_251130 @ 0x00251130
void
sub_251130(rwaWmaSource *obj, rwaStreamSeek *seek)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    RwReal      seconds;

    if (seek->flush)
    {
        state->flags |= 4;
        sub_250F50(obj, 1);
    }
    switch (seek->position->unit)
    {
        case 1:
            seconds = *(RwReal *)&seek->position->pos;
            break;
        case 2:
            seconds = (RwReal)seek->position->pos / (RwReal)state->format.sampleRate;
            break;
        default:
            seconds = 0.0f;
            break;
    }
    state->seekTime = (RwUInt32)(seconds * 1000.0f);
    state->flags |= 2;
    if (state->flags & 4)
    {
        state->flags &= ~4;
        ReleaseSemaphore(state->semaphore, 1, NULL);
    }
}

// match: _sub_2511F0 @ 0x002511F0
rwaWmaSource *
sub_2511F0(rwaWmaSource *obj, const void *param, rwaStreamSeek *value)
{
    sub_251130(obj, value);
    return obj;
}

/* Opens a source: the first starts the WMA thread. */
/* The decode loop retains its next-link iterator and initializes the
 * per-packet output position after the other status and loop locals. */
// match: _sub_251210 @ 0x00251210
RwUInt32
sub_251210(void *data)
{
    while (dword_507E10)
    {
        rwaLink    *cur;
        rwaLink    *next;

        WaitForSingleObject(dword_507E90, rwaINFINITE);
        for (next = dword_507EB0.next; next != &dword_507EB0;)
        {
            rwaWmaSource *obj = rwaWmaFromLink(next);
            rwaWmaState *state = (rwaWmaState *)obj->inst.state;

            next = next->next;
            if (state->flags & 2)
            {
                RwUInt32    actual;

                state->flags &= ~2;
                if (state->decoder->vtbl->seekToTime(state->decoder, state->seekTime,
                                                     &actual) >= 0)
                {
                    state->position = *state->marker.unk0C * actual
                                      / state->duration;
                }
            }

            switch (state->node.mode)
            {
            case 1:
                if (state->node.status != 3)
                {
                    sub_2470A0((rwaDecoder *)obj);
                    state->link.prev->next = state->link.next;
                    state->link.next->prev = state->link.prev;
                }
                break;
            case 2:
            case 3:
            {
                rwaWmaPacket *packet;
                RwBool      more;
                RwUInt32    status;

                WaitForSingleObject(state->semaphore, rwaINFINITE);
                packet = &state->packets[state->write];
                if (state->node.mode == 3)
                {
                    more = TRUE;
                    if (state->node.status != 5 && state->write == state->read
                        && state->packets[state->read].state)
                    {
                        sub_2470A0((rwaDecoder *)obj);
                    }
                }
                else
                {
                    RwUInt32    filled;

                    if (state->write == state->read)
                    {
                        filled = packet->state ? 0 : state->noPackets;
                    }
                    else if (state->write > state->read)
                    {
                        filled = state->write - state->read;
                    }
                    else
                    {
                        filled = state->noPackets - state->read + state->write;
                    }
                    more = state->minPackets < filled;
                    if (state->node.status != 6 && state->packets[state->read].state)
                    {
                        sub_2470A0((rwaDecoder *)obj);
                    }
                }
                ReleaseSemaphore(state->semaphore, 1, NULL);

                if (!packet->state && more
                    && state->decoder->vtbl->getStatus(state->decoder, &status) >= 0
                    && (status & 2))
                {
                    RwInt32     packetState = 1;
                    RwUInt32 size = 0;
                    RwBool      ok = TRUE;
                    RwBool looped = FALSE;
                    RwUInt32    loopedAt = 0;

                    RwUInt32 newPosition = 0;
                    do
                    {
                        packet->header.size = state->packetSize - size;
                        packet->header.buffer = state->buffers
                                                + state->write * state->packetSize + size;
                        *packet->header.completed = 0;
                        *packet->header.status = 0;
                        if (state->decoder->vtbl->process(state->decoder, NULL,
                                                          &packet->header) < 0)
                        {
                            ok = FALSE;
                            break;
                        }
                        size += *packet->header.completed;
                        if (size >= state->packetSize)
                        {
                            break;
                        }
                        if (!(state->flags & 1))
                        {
                            rwaStreamPosition position;
                            rwaStreamSeek seek;

                            position.value = 0;
                            position.pos = 0;
                            seek.flush = FALSE;
                            position.type = 3;
                            position.unit = 2;
                            seek.position = &position;
                            sub_251130(obj, &seek);
                            packetState = 2;
                            goto filled;
                        }
                        {
                            RwUInt32    actual = 0;

                            if (state->decoder->vtbl->seekToTime(state->decoder, 0,
                                                                 &actual) >= 0)
                            {
                                newPosition = *state->marker.unk0C * actual
                                              / state->duration;
                                looped = TRUE;
                                loopedAt = size;
                            }
                        }
                    }
                    while (size < state->packetSize);
                    packet->header.buffer = state->buffers + state->write * state->packetSize;
                    *packet->header.completed = size;

                  filled:
                    packet->position = state->position;
                    if (looped)
                    {
                        state->position = newPosition - loopedAt + size;
                    }
                    else
                    {
                        state->position += size;
                    }
                    if (ok && !*packet->header.status)
                    {
                        WaitForSingleObject(state->semaphore, rwaINFINITE);
                        if (++state->write == state->noPackets)
                        {
                            state->write = 0;
                        }
                        packet->state = packetState;
                        ReleaseSemaphore(state->semaphore, 1, NULL);
                    }
                }
                if (state->node.status == 6 && state->write == state->read
                    && !state->packets[state->write].state)
                {
                    state->node.status = 7;
                }
                break;
            }
            }
        }
        ReleaseSemaphore(dword_507E90, 1, NULL);
        Sleep(34);
    }

    ReleaseSemaphore(dword_507E8C, 1, NULL);

    return 0;
}



// match: _sub_251630 @ 0x00251630
RwBool
sub_251630(void)
{
    if (!dword_507EB8)
    {
        dword_507E10 = TRUE;
        dword_507EB0.next = &dword_507EB0;
        dword_507EB0.prev = &dword_507EB0;
        if (!sub_2416D0(&dword_507E90, 1, 1))
        {
            return FALSE;
        }
        if (sub_2416D0(&dword_507E8C, 0, 1))
        {
            if (_RwaThreadCreate(dword_507E94, sub_251210, dword_506B44, 0)
                && sub_241770(dword_507E94, NULL))
            {
                dword_507EB8++;
                return TRUE;
            }
            CloseHandle(dword_507E8C);
        }
        CloseHandle(dword_507E90);
        return FALSE;
    }
    dword_507EB8++;

    return TRUE;
}

// match: _sub_2516E0 @ 0x002516E0
rwaWmaSource *
sub_2516E0(rwaWmaSource *obj, rwaInstance *parent, rwaWmaParams *params, void *a, void *b)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    rwaWmaPosition *positions;
    RwUInt32    i;
    const RwChar *fileName;
    void       *file;
    rwaWaveFormatEx wfx;
    RwUInt16 strings[3][128];

    if (!sub_246FD0((rwaDecoder *)obj, parent, (rwaStreamNodeParams *)params, a, b))
    {
        return NULL;
    }

    obj->state.objInterface = sub_243FF0(sub_243F40(unk_3ED9C4), obj->inst.def, params->unk14,
        params->unk18);
    state->noPackets = params->noPackets;
    state->flags = 0;
    if (!params->lookahead)
    {
        params->lookahead = params->noPackets * 0x3C00;
    }
    if (!sub_251630())
    {
        sub_243B80(obj->state.objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    state->packetSize = params->lookahead / params->noPackets;
    state->minPackets = params->minPackets;
    state->items = (rwaQueueItem *)sub_242170(state->noPackets * (state->packetSize + 80) + 4,
        rwaMEMHINTDUR_EVENT | rwaID_80B);
    if (!state->items)
    {
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    positions = (rwaWmaPosition *)(state->items + state->noPackets);
    state->packets = (rwaWmaPacket *)(positions + state->noPackets);
    state->buffers = (RwUInt8 *)&state->packets[state->noPackets];
    state->marker.unk0C = (RwUInt32 *)(state->buffers + state->packetSize * state->noPackets);
    state->write = 0;
    state->read = 0;
    memset(state->packets, 0, state->noPackets * sizeof(rwaWmaPacket));
    {
        rwaQueueCallback *callback = &state->callback;
        callback->func = (void (*)(rwaQueueItem *, rwaDecoder *))sub_2510D0;
        callback->data = (rwaDecoder *)obj;
    }
    for (i = 0; i < state->noPackets; i++)
    {
        state->items[i].flags = 0;
        state->items[i].unk04 = (RwUInt8 *)obj;
        state->items[i].callback = &state->callback;
        state->items[i].unk08 = state->packetSize;
        state->items[i].position = &positions[i].position;
        positions[i].position.value = 0;
        positions[i].position.type = 3;
        positions[i].position.unit = 2;
        positions[i].position.pos = 0;
        state->packets[i].header.status = &state->packets[i].status;
        state->packets[i].header.completed = &state->packets[i].completed;
    }
    sub_2472E0(&state->queue, state->items, state->noPackets);

    fileName = NULL;
    file = NULL;
    if (!sub_2416D0(&state->semaphore, 1, 1))
    {
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }
    switch (params->fileType)
    {
        case 1:
        fileName = (const RwChar *)params->file;
        break;
        case 2:
        file = (void *)params->file;
        break;
    }
    if (WmaCreateDecoderEx(fileName, file, FALSE, params->lookahead * params->noPackets,
        params->noPackets, params->yieldRate, &wfx, &state->decoder) < 0)
    {
        CloseHandle(state->semaphore);
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    {
        rwaWmaFileHeader header;
        rwaWmaContentDesc desc;
        rwaWmaContentDesc *content = &desc;
        content->title = strings[0];
        content->titleLength = 128;
        content->authorLength = 128;
        content->descriptionLength = 128;
        {
            rwaXMediaObject *decoder = state->decoder;
            state->title[0] = '\0';
            state->author[0] = '\0';
            state->description[0] = '\0';
            content->author = strings[1];
            content->description = strings[2];
            content->copyright = NULL;
            content->copyrightLength = 0;
            content->rating = NULL;
            content->ratingLength = 0;
            if (decoder->vtbl->getFileContentDescription(decoder, &desc) >= 0)
            {
                WideCharToMultiByte(0, 0, desc.title, desc.titleLength, state->title, 128, NULL, NULL);
                WideCharToMultiByte(0, 0, desc.author, desc.authorLength, state->author, 128, NULL,
                    NULL);
                WideCharToMultiByte(0, 0, desc.description, desc.authorLength, state->description,
                    128, NULL, NULL);
            }
        }
        if (state->decoder->vtbl->getFileHeader(state->decoder, &header) < 0)
        {
            state->decoder->vtbl->release(state->decoder);
            CloseHandle(state->semaphore);
            sub_2421B0(state->items);
            sub_250B30();
            sub_243B80(state->objInterface);
            sub_247120((rwaDecoder *)obj, NULL, NULL);
            return NULL;
        }
        {
            rwaWmaFileHeader *fileHeader = &header;
            state->duration = fileHeader->duration;
            state->bitrate = fileHeader->bitrate;
        }
        state->position = 0;
        state->seekTime = 0;
        if (state->decoder->vtbl->getLength(state->decoder, &state->length) >= 0)
        {

            sub_24DA40(&state->info);
            {
                rwaStreamTrack *track = &state->track;
                sub_24DA10(track);
                sub_24D9F0(&state->marker);
                state->info.markers = &state->marker;
                state->info.unk0C = 1;
                state->info.noTracks = 1;
                state->info.unk20 = state->packetSize;
                state->info.tracks = track;
                state->info.unk24 = 0;
                state->info.unk1C = 2048;
                sub_240BF0((RwaUniqueID *)&state->info, state->title);
                sub_240BF0((RwaUniqueID *)&state->marker, state->author);
                rwaWaveFormatInit(&state->format);
                state->format.bitDepth = (RwUInt8)wfx.bitsPerSample;
                state->format.dataType = &unk_3ED5CC;
                state->format.length = state->length;
                state->format.noChannels = (RwUInt8)wfx.channels;
                state->format.sampleRate = wfx.samplesPerSec;
                sub_240BF0((RwaUniqueID *)track, state->description);
                track->format = (rwaStreamFormat *)&state->format;
                track->unk1A = (RwUInt16)sub_242A30(&state->format);
                track->unk18 = state->track.unk1A;
                track->unk20 = state->info.unk20;
                track->unk1C = (RwUInt16)(state->track.unk20 / state->track.unk18);
                track->unk0C = sub_242E30(&state->format);
                track->unk10 = state->track.unk20;
                *state->marker.unk0C = wfx.channels * state->duration * wfx.samplesPerSec
                    / track->unk0C * track->unk1A / 1000;
            }
            RwaStreamNodeCreationComplete((rwaDecoder *)obj);
            if (obj->inst.subObjLink.next)
            {
                obj->inst.subObjLink.prev->next = obj->inst.subObjLink.next;
                obj->inst.subObjLink.next->prev = obj->inst.subObjLink.prev;
                obj->inst.subObjLink.prev = NULL;
                obj->inst.subObjLink.next = NULL;
            }
            state->link.prev = NULL;
            state->link.next = NULL;

            return obj;

        }
        else
        {

            state->decoder->vtbl->release(state->decoder);
            CloseHandle(state->semaphore);
            sub_2421B0(state->items);
            sub_250B30();
            sub_243B80(state->objInterface);
            sub_247120((rwaDecoder *)obj, NULL, NULL);
            return NULL;

        }
    }
}

// match: _sub_251CE0 @ 0x00251CE0
static void
sub_251CE0(rwaObjDef *def)
{
    RwaObjDefAssignID(def, unk_3EDFC8, NULL);

    def->flags = sizeof(rwaWmaState);
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_2516E0;
    def->unlink = (void (*)(rwaInstance *, void *, void *))sub_250B70;
    def->query = (void (*)(void *, void *))sub_250C10;
    def->paramsSize = sizeof(rwaWmaParams);
    def->unk54 = unk_430CD0;
}

// match: _sub_251F20 @ 0x00251F20
rwaObjDef *
sub_251F20(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0xC, &unk_507E18, unk_507E74, unk_507EA8,
                                 rwaMEMHINTDUR_EVENT | rwaID_80B);
    void       *iface;

    if (!def)
    {
        return NULL;
    }

    sub_251CE0(def);

    if (!_rwaObjDefSetupParams(def, off_430BD0, 5, off_430C48, 5))
    {
        sub_23DB90(def);

        return NULL;
    }

    iface = sub_243F40(unk_3ED9C4);
    if (!iface)
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, iface);

    return def;
}

// match: _sub_251FA0 @ 0x00251FA0
void *
sub_251FA0(void)
{
    if (!sub_243E20(dword_507EBC))
    {
        return NULL;
    }

    RwaWaveDictAssignID(dword_507EBC, unk_3EDFD8, NULL);
    sub_243CD0(dword_507EBC, off_430CE8, 22, off_430EA0, 23);

    return dword_507EBC;
}

// match: _sub_251FF0 @ 0x00251FF0
RwBool
sub_251FF0(void)
{
    return sub_243EA0(dword_507EBC);
}
