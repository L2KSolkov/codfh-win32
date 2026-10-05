/*
 * codfh-match: RenderWare Audio's listener object (not in the PS2 header;
 * named by address): its creation, unregistration and parameter handlers
 * (the table at 0x42E488; four handlers were missing from the database).
 */
#include "rwa.h"
#include "rwaint.h"


extern RwUInt8 unk_506858[];
extern RwUInt32 dword_5068CC;
extern RwInt32 sub_23F4C0(void *module, RwInt32 a, RwInt32 b, RwInt32 c, RwInt32 d, RwInt32 e);
extern RwBool sub_243B30(void);
extern RwInt32 sub_23DB90(void *module);

/* RwV3dCrossProductMacro from RWSDK/src/plcore/bavector.h. Keep its
 * operand parentheses: VC7.0 uses them to select the original x87 order. */
#define RwaV3dCrossProductMacro(o, a, b)                         \
do                                                     \
{                                                               \
    (o)->x =                                                    \
        (( (((a)->y) * ( (b)->z))) -                            \
         ( (((a)->z) * ( (b)->y))));                            \
    (o)->y =                                                    \
        (( (((a)->z) * ( (b)->x))) -                            \
         ( (((a)->x) * ( (b)->z))));                            \
    (o)->z =                                                    \
        (( (((a)->x) * ( (b)->y))) -                            \
         ( (((a)->y) * ( (b)->x))));                            \
}                                                               \
while(0)


/* Original vector macros from RWSDK/src/plcore/bavector.h. Preserve
 * their complete operand grouping for VC7.0 x87 scheduling. */
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


/* Evidence: sub_23CD40 reads both x components before its scalar field
 * copies. Qualified accesses preserve those reads; original qualifiers
 * are unknown. Other components use the original subtraction macro form. */
#define RwaListenerPreviousPositionMacro(o,a,b) do { \
 (o)->x = ((*(const volatile RwReal *)&(a)->x) - ( *(const volatile RwReal *)&(b)->x)); \
 (o)->y = (((a)->y) - ( (b)->y)); \
 (o)->z = (((a)->z) - ( (b)->z)); \
 } while(0)

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED278 @ 0x003ED278

// What its data definitions name.
rwaListener *sub_23D150(rwaListener *listener, const RwaUUID *param, const RwaV3d *value);
rwaListener *sub_23D180(rwaListener *listener, const RwaUUID *param, RwaV3d *value);
rwaListener *sub_23D1A0(rwaListener *listener, const RwaUUID *param, const RwaV3d *value);
rwaListener *sub_23D1D0(rwaListener *listener, const RwaUUID *param, RwaV3d *value);
rwaListener *sub_23D1F0(rwaListener *listener, const RwaUUID *param, const rwaOrientation *value);
rwaListener *sub_23D250(rwaListener *listener, const RwaUUID *param, rwaOrientation *value);
rwaListener *sub_23D2A0(rwaListener *listener, const RwaUUID *param, const RwaV3d *value);
rwaListener *sub_23D300(rwaListener *listener, const RwaUUID *param, RwaV3d *value);
rwaListener *sub_23D320(rwaListener *listener, const RwaUUID *param, const RwaV3d *value);
rwaListener *sub_23D380(rwaListener *listener, const RwaUUID *param, RwaV3d *value);
rwaListener *sub_23D3A0(rwaListener *listener, const RwaUUID *param, RwaV3d *value);
rwaListener *sub_23D3C0(rwaListener *listener, const RwaUUID *param, const RwUInt32 *value);
rwaListener *sub_23D3E0(rwaListener *listener, const RwaUUID *param, RwUInt32 *value);
rwaListener *sub_23D3F0(rwaListener *listener, const RwaUUID *param, const RwUInt32 *value);
rwaListener *sub_23D410(rwaListener *listener, const RwaUUID *param, RwUInt32 *value);
rwaListener *sub_23D420(rwaListener *listener, const RwaUUID *param, const RwUInt32 *value);
rwaListener *sub_23D440(rwaListener *listener, const RwaUUID *param, RwUInt32 *value);
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED54C[];
extern RwUInt8 unk_3ED57C[];
extern RwUInt8 unk_3ED680[];
extern RwUInt8 unk_3ED690[];
extern RwUInt8 unk_3ED6A0[];
extern RwUInt8 unk_3ED6B0[];
extern RwUInt8 unk_3ED6C0[];
extern RwUInt8 unk_3ED6D0[];
extern RwUInt8 unk_3ED6E0[];
extern RwUInt8 unk_3ED6F0[];
extern RwUInt8 unk_3ED700[];
extern RwUInt8 unk_3ED710[];
extern RwUInt8 unk_3ED720[];
extern RwUInt8 unk_3ED730[];
extern RwUInt8 unk_3ED740[];
extern RwUInt8 unk_3ED750[];
extern RwUInt8 unk_3ED760[];
extern RwUInt8 unk_3ED770[];
extern RwUInt8 unk_3ED780[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED278
const RwaUUID unk_3ED278 = { 0x5F84D81F, 0x02EF, 0x4B39, { 0x92, 0x3D, 0x7C, 0x9D, 0x4E, 0xB2, 0x29, 0x23 } };
// 0x0042E488
void *unk_42E488[48] =
{
    (void *)&unk_3ED680,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D150,
    (void *)&unk_3ED6A0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D1A0,
    (void *)&unk_3ED6C0,
    0,
    0,
    (void *)&unk_3ED57C,
    (void *)0x1,
    (void *)sub_23D1F0,
    (void *)&unk_3ED6E0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D2A0,
    (void *)&unk_3ED700,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D320,
    (void *)&unk_3ED730,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23D3C0,
    (void *)&unk_3ED750,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23D3F0,
    (void *)&unk_3ED770,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23D420,
};
// 0x0042E548
void *unk_42E548[56] =
{
    (void *)&unk_3ED690,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D180,
    (void *)&unk_3ED6B0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D1D0,
    (void *)&unk_3ED6D0,
    0,
    0,
    (void *)&unk_3ED57C,
    (void *)0x1,
    (void *)sub_23D250,
    (void *)&unk_3ED6F0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D300,
    (void *)&unk_3ED710,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D380,
    (void *)&unk_3ED720,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)sub_23D3A0,
    (void *)&unk_3ED740,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23D3E0,
    (void *)&unk_3ED760,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23D410,
    (void *)&unk_3ED780,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)sub_23D440,
    (void *)0x1,
    0,
};
// 0x00506850
RwUInt8 unk_506850[8];
// 0x00506858
RwUInt8 unk_506858[92];
// 0x005068B4
RwUInt8 unk_5068B4[24];
// 0x005068CC
RwUInt32 dword_5068CC;
// End of its data definitions.


// match: __real@43aa0000 @ 0x003ED288


// match: _unk_42E488 @ 0x0042E488


// match: _unk_42E548 @ 0x0042E548

// match: _RwaListenerCreate @ 0x0023CC10

RwInt32
RwaListenerCreate(RwInt32 a, RwInt32 b, RwInt32 c)
{
    return sub_23F4C0(unk_506858, 0, a, 0, b, c);
}

// match: _sub_23CC40 @ 0x0023CC40
RwInt32
sub_23CC40(void)
{
    if (dword_5068CC)
    {
        if (!sub_243B30())
        {
            return 0;
        }

        dword_5068CC = 0;
    }

    return sub_23DB90(unk_506858);
}

// match: _sub_23CC70 @ 0x0023CC70
rwaListener *
sub_23CC70(rwaListener *listener)
{
    RwaV3d  v;

    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    listener->pos = v;
    listener->vel = v;

    v.z = v.x = listener->at.y = listener->at.x = 0.0f;
    v.y = listener->at.z = 1.0f;
    listener->up = v;

    RwaV3dCrossProductMacro(&listener->right, &listener->up, &listener->at);

    listener->unk68 = 0x3F800000;
    listener->unk6C = 0x3F800000;
    listener->unk64 = 0x41200000;
    listener->dirty = 0x7B;

    return listener;
}


extern void sub_242050(RwReal *length, const RwaV3d *vector);
extern RwReal RwV3dNormalize(RwaV3d *out, const RwaV3d *in);

// match: _sub_23CD40 @ 0x0023CD40
void
sub_23CD40(rwaInstance **listeners, RwUInt32 count,
           const rwa3DSource *source, RwReal *gains, RwUInt32 mode)
{
    rwaListenerState *listener = &((rwaListener *)*listeners)->state;
    RwReal doppler = *(RwReal *)&listener->unk6C;
    RwReal rolloff = *(RwReal *)&listener->unk64;
    const RwaV3d *at = &listener->at;
    RwReal velocityScale = *(RwReal *)&listener->unk68;
    RwaV3d direction, previousDirection;
    RwaV3d listenerPrevious, sourcePrevious;
    RwReal distance, previousDistance;
    RwReal delta, speed;


    RwaListenerPreviousPositionMacro(&listenerPrevious, &listener->pos, &listener->vel);
    RwaV3dSubMacro(&sourcePrevious, &source->position, &source->velocity);
    RwaV3dSubMacro(&previousDirection, &sourcePrevious, &listenerPrevious);
    sub_242050(&previousDistance, &previousDirection);

    RwaV3dSubMacro(&direction, &source->position, &listener->pos);
    sub_242050(&distance, &direction);
    delta = distance - previousDistance;
    if(delta > 150.0f)delta = 150.0f;
    else if(delta < -150.0f)delta = -150.0f;
    speed = doppler * 340.0f;
    gains[1] = (speed - delta * velocityScale) / speed;
    if(distance > source->maxDistance)gains[0] = 0.0f;
    else if(distance < source->minDistance)gains[0] = 1.0f;
    else
    {
        RwReal range;
        distance -= source->minDistance;
        range = source->maxDistance - source->minDistance;
        gains[0] = (range - distance) / (distance * rolloff + range);
    }

    if(direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f)
        direction = *at;
    else RwV3dNormalize(&direction, &direction);
    if(previousDirection.x == 0.0f && previousDirection.y == 0.0f && previousDirection.z == 0.0f)
        previousDirection = *at;
    else RwV3dNormalize(&previousDirection, &previousDirection);

    gains[2] = 0.5f - RwaV3dDotProductMacro(&direction, &listener->right) * 0.5f;
    gains[2] = gains[2] < 0.0f ? 0.0f : gains[2] > 1.0f ? 1.0f : gains[2];
    gains[3] = 0.5f - RwaV3dDotProductMacro(&direction, at) * 0.5f;
    gains[3] = gains[3] < 0.0f ? 0.0f : gains[3] > 1.0f ? 1.0f : gains[3];
    gains[4] = 0.5f - RwaV3dDotProductMacro(&previousDirection, &listener->right) * 0.5f;
    gains[4] = gains[4] < 0.0f ? 0.0f : gains[4] > 1.0f ? 1.0f : gains[4];
    gains[5] = 0.5f - RwaV3dDotProductMacro(&previousDirection, at) * 0.5f;
    gains[5] = gains[5] < 0.0f ? 0.0f : gains[5] > 1.0f ? 1.0f : gains[5];
    switch(mode)
    {
    case 2:
        gains[2] -= 0.5f;
        gains[4] -= 0.5f;
        gains[2] *= 0.0f;
        gains[4] *= 0.0f;
        gains[2] += 0.5f;
        gains[4] += 0.5f;
        break;
    case 3:
        gains[2] -= 0.5f;
        gains[4] -= 0.5f;
        gains[2] *= 0.5f;
        gains[4] *= 0.5f;
        gains[2] += 0.5f;
        gains[4] += 0.5f;
        break;
    }
}

// match: _sub_23D150 @ 0x0023D150
rwaListener *
sub_23D150(rwaListener *listener, const RwaUUID *param, const RwaV3d *value)
{
    listener->pos = *value;
    listener->dirty |= 1;

    return listener;
}

// match: _sub_23D180 @ 0x0023D180
rwaListener *
sub_23D180(rwaListener *listener, const RwaUUID *param, RwaV3d *value)
{
    *value = listener->pos;

    return listener;
}

// match: _sub_23D1A0 @ 0x0023D1A0
rwaListener *
sub_23D1A0(rwaListener *listener, const RwaUUID *param, const RwaV3d *value)
{
    listener->vel = *value;
    listener->dirty |= 2;

    return listener;
}

// match: _sub_23D1D0 @ 0x0023D1D0
rwaListener *
sub_23D1D0(rwaListener *listener, const RwaUUID *param, RwaV3d *value)
{
    *value = listener->vel;

    return listener;
}

// match: _sub_23D1F0 @ 0x0023D1F0
rwaListener *
sub_23D1F0(rwaListener *listener, const RwaUUID *param, const rwaOrientation *value)
{
    listener->up = value->up;
    listener->at = value->at;
    listener->right = value->right;
    listener->dirty |= 0xC;

    return listener;
}

// match: _sub_23D250 @ 0x0023D250
rwaListener *
sub_23D250(rwaListener *listener, const RwaUUID *param, rwaOrientation *value)
{
    value->up = listener->up;
    value->at = listener->at;
    value->right = listener->right;

    return listener;
}

// match: _sub_23D2A0 @ 0x0023D2A0
rwaListener *
sub_23D2A0(rwaListener *listener, const RwaUUID *param, const RwaV3d *value)
{
    listener->up = *value;
    RwaV3dCrossProductMacro(&listener->right, &listener->up, &listener->at);
    listener->dirty |= 8;

    return listener;
}

// match: _sub_23D300 @ 0x0023D300
rwaListener *
sub_23D300(rwaListener *listener, const RwaUUID *param, RwaV3d *value)
{
    *value = listener->up;

    return listener;
}

// match: _sub_23D320 @ 0x0023D320
rwaListener *
sub_23D320(rwaListener *listener, const RwaUUID *param, const RwaV3d *value)
{
    listener->at = *value;
    RwaV3dCrossProductMacro(&listener->right, &listener->up, &listener->at);
    listener->dirty |= 4;

    return listener;
}

// match: _sub_23D380 @ 0x0023D380
rwaListener *
sub_23D380(rwaListener *listener, const RwaUUID *param, RwaV3d *value)
{
    *value = listener->at;

    return listener;
}

// match: _sub_23D3A0 @ 0x0023D3A0
rwaListener *
sub_23D3A0(rwaListener *listener, const RwaUUID *param, RwaV3d *value)
{
    *value = listener->right;

    return listener;
}

// match: _sub_23D3C0 @ 0x0023D3C0
rwaListener *
sub_23D3C0(rwaListener *listener, const RwaUUID *param, const RwUInt32 *value)
{
    listener->unk68 = *value;
    listener->dirty |= 0x20;

    return listener;
}

// match: _sub_23D3E0 @ 0x0023D3E0
rwaListener *
sub_23D3E0(rwaListener *listener, const RwaUUID *param, RwUInt32 *value)
{
    *value = listener->unk68;

    return listener;
}

// match: _sub_23D3F0 @ 0x0023D3F0
rwaListener *
sub_23D3F0(rwaListener *listener, const RwaUUID *param, const RwUInt32 *value)
{
    listener->unk6C = *value;
    listener->dirty |= 0x40;

    return listener;
}

// match: _sub_23D410 @ 0x0023D410
rwaListener *
sub_23D410(rwaListener *listener, const RwaUUID *param, RwUInt32 *value)
{
    *value = listener->unk6C;

    return listener;
}

// match: _sub_23D420 @ 0x0023D420
rwaListener *
sub_23D420(rwaListener *listener, const RwaUUID *param, const RwUInt32 *value)
{
    listener->unk64 = *value;
    listener->dirty |= 0x10;

    return listener;
}

// match: _sub_23D440 @ 0x0023D440
rwaListener *
sub_23D440(rwaListener *listener, const RwaUUID *param, RwUInt32 *value)
{
    *value = listener->unk64;

    return listener;
}

extern rwaObjDef *RwaObjDefAssignID(rwaObjDef *def, const void *uuid, const void *textID);
extern rwaListener *sub_23CC70(rwaListener *listener);

// match: _sub_23D450 @ 0x0023D450
static void
sub_23D450(rwaObjDef *def)
{
    RwaObjDefAssignID(def, &unk_3ED278, NULL);

    def->flags = 0x4C;
    rwaObjDefSetStateAlignment(def, rwaPow2(0x28));

    def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_23CC70;
    def->paramsSize = 0;
    def->maxInstances = 1;
}

extern rwaObjDef *dword_516C60;
extern RwUInt8 unk_506850[];
extern RwUInt8 unk_5068B4[];
extern rwaObjDef *sub_23DFB0(void *parent, RwInt32 a, void *b, void *c, void *d, RwUInt32 hint);
extern RwBool _rwaObjDefSetupParams(rwaObjDef *def, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern void *RwaListenerInterfaceRegister_0(void);
extern rwaObjDef *sub_23D740(rwaObjDef *def, void *iface);

// match: _sub_23D690 @ 0x0023D690
rwaObjDef *
sub_23D690(void)
{
    rwaObjDef  *def = sub_23DFB0(dword_516C60, 0xC, unk_506858, unk_5068B4, unk_506850,
                                 rwaMEMHINTDUR_EVENT | rwaID_80B);
    void       *iface;

    if (!def)
    {
        return NULL;
    }

    sub_23D450(def);

    if (!_rwaObjDefSetupParams(def, unk_42E488, 8, unk_42E548, 9))
    {
        sub_23DB90(def);

        return NULL;
    }

    iface = RwaListenerInterfaceRegister_0();
    if (!iface)
    {
        sub_23DB90(def);

        return NULL;
    }

    sub_23D740(def, iface);
    dword_5068CC = 1;

    return def;
}
