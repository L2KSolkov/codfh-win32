// The game's RenderWare object extensions (types/type_3D96F0.h): the
// plugins that build one in an atomic's, clump's, frame's, light's,
// material's and world's plugin data, and the extensions' own methods. The
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/rpatomic.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_3D96F0.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D96EC
extern const RwReal flt_3D96EC = 16.666666f;
// 0x004C1928
RwInt32 dword_4C1928;
// 0x004C192C
RwInt32 dword_4C192C;
// 0x004C1930
RwInt32 dword_4C1930;
// 0x004C1934
RwInt32 dword_4C1934;
// 0x004C1938
RwInt32 dword_4C1938;
// 0x004C193C
RwInt32 dword_4C193C;
// End of its data definitions.


// The plugins' offsets.
extern RwInt32 dword_4C1928;
extern RwInt32 dword_4C192C;
extern RwInt32 dword_4C1930;
extern RwInt32 dword_4C1934;
extern RwInt32 dword_4C1938;
extern RwInt32 dword_4C193C;

// The plugin registrations (RenderWare 3.7.2) and their streaming.
extern "C"
{
RwInt32 RpAtomicRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB,
                               RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
RwInt32 RwFrameRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB,
                              RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
RwInt32 RpLightRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB,
                              RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
RwInt32 RpWorldRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB,
                              RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
RwInt32 RpMaterialRegisterPlugin(RwInt32 size, RwUInt32 pluginID, RwPluginObjectConstructor constructCB,
                                 RwPluginObjectDestructor destructCB, RwPluginObjectCopy copyCB);
typedef RwStream *(*RwPluginDataChunkReadCallBack)(RwStream *stream, RwInt32 binaryLength, void *object,
                                                   RwInt32 offsetInObject, RwInt32 sizeInObject);
typedef RwStream *(*RwPluginDataChunkWriteCallBack)(RwStream *stream, RwInt32 binaryLength,
                                                    const void *object, RwInt32 offsetInObject,
                                                    RwInt32 sizeInObject);
typedef RwInt32 (*RwPluginDataChunkGetSizeCallBack)(const void *object, RwInt32 offsetInObject,
                                                    RwInt32 sizeInObject);
RwInt32 RpMaterialRegisterPluginStream(RwUInt32 pluginID, RwPluginDataChunkReadCallBack readCB,
                                       RwPluginDataChunkWriteCallBack writeCB,
                                       RwPluginDataChunkGetSizeCallBack getSizeCB);
}

// The material extension's stream size (the value's four bytes; 0x200B80).
RwInt32 sub_200B80(const void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
// A light's take-down (sub_1738D0).
struct RpLight;
RwInt32 sub_1738D0(RpLight *arg_0);
// The index of arg_4 in the array arg_0, and its removal.
RwInt32 sub_19A930(RwInt32 arg_0, RwInt32 arg_4);
void sub_19A8A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D96EC@@3MB @ 0x003D96EC
// match: ??_7type_3D96F0@@6B@ @ 0x003D96F0
// match: ??_7type_3D96FC@@6B@ @ 0x003D96FC
// match: ??_7type_3D970C@@6B@ @ 0x003D970C
// match: ??_7type_3D9718@@6B@ @ 0x003D9718

// match: ?sub_FB7A0@@YAPAUtype_3D96F0@@PAX@Z @ 0x000FB7A0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D96F0 *sub_FB7A0(void *arg_0)
{
    void *bp_8;
    type_3D96F0 *bp_4;

    bp_8 = arg_0;
    bp_4 = RWPLUGINOFFSET(type_3D96F0, bp_8, dword_4C1928);
    return bp_4;
}

void *sub_FB880(void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
void *sub_FB800(void *arg_0, RwInt32 arg_4, RwInt32 arg_8);
// match: ?sub_FB7C0@@YAHXZ @ 0x000FB7C0
RwInt32 sub_FB7C0()
{
    dword_4C1928 = RpAtomicRegisterPlugin(0x1C, 0x42B0, sub_FB800, sub_FB880,
                                          (RwPluginObjectCopy)RenderWare_ReturnObjectUnchanged);
    return dword_4C1928 != 0;
}

// match: ?sub_FB800@@YAPAXPAXHH@Z @ 0x000FB800
void *sub_FB800(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FB7A0(arg_0);

    var_4 = new (var_4) type_3D96F0;
    var_4->vf_000();
    return arg_0;
}

// match: ?sub_FB880@@YAPAXPAXHH@Z @ 0x000FB880
void *sub_FB880(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FB7A0(arg_0);

    var_4->vf_008(arg_0);
    delete var_4;
    return arg_0;
}

// match: ??1type_3D96F0@@QAE@XZ @ 0x000FB8F0
type_3D96F0::~type_3D96F0()
{
}

// Sets the atomic's entity (none for 0), the handle copied in.
// match: ?sub_FB910@@YAXPAURpAtomic@@PAUtype_3D3548@@@Z @ 0x000FB910
void sub_FB910(RpAtomic *arg_0, type_3D3548 *arg_4)
{
    type_3D96F0 *var_4 = sub_FB7A0(arg_0);

    if (arg_4)
    {
        var_4->unk_14.set_h(arg_4->get_unk_384_h());
    }
    else
    {
        type_3D96F0_14 lv_8;

        var_4->unk_14 = lv_8;
    }
}

// match: ?sub_FB960@@YAPAUtype_3D3548@@PAURpAtomic@@@Z @ 0x000FB960
type_3D3548 *sub_FB960(RpAtomic *arg_0)
{
    type_3D96F0 *var_4 = sub_FB7A0(arg_0);

    if (var_4)
    {
        return var_4->unk_14.sub_D4910();
    }
    return 0;
}

// match: ?sub_FB990@@YAXPAURpAtomic@@H@Z @ 0x000FB990
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_FB990(RpAtomic *arg_0, RwInt32 arg_4)
{
    type_3D96F0 *bp_8;
    type_3D96F0_04 bp_4;

    bp_4.unk_00 = arg_4;
    bp_8 = sub_FB7A0(arg_0);
    bp_8->unk_04 = bp_4;
}

// match: ?sub_FB9C0@@YAHPAURpAtomic@@@Z @ 0x000FB9C0
RwInt32 sub_FB9C0(RpAtomic *arg_0)
{
    type_3D96F0_04 bp_8;
    type_3D96F0 *bp_4;

    bp_4 = sub_FB7A0(arg_0);
    bp_8 = bp_4->unk_04;
    return bp_8.unk_00;
}

// match: ?sub_FB9F0@@YAXPAURpAtomic@@H@Z @ 0x000FB9F0
void sub_FB9F0(RpAtomic *arg_0, RwInt32 arg_4)
{
    type_3D96F0 *var_4 = sub_FB7A0(arg_0);

    var_4->unk_10 = arg_4;
}

// match: ?sub_FBA10@@YAPAUtype_3D96F0@@PAX@Z @ 0x000FBA10
type_3D96F0 *sub_FBA10(void *arg_0)
{
    void *bp_8;
    type_3D96F0 *bp_4;

    bp_8 = arg_0;
    bp_4 = RWPLUGINOFFSET(type_3D96F0, bp_8, dword_4C192C);
    return bp_4;
}

void *sub_FBA70(void *, RwInt32, RwInt32);
void *sub_FBAF0(void *, RwInt32, RwInt32);

// match: ?sub_FBA30@@YAHXZ @ 0x000FBA30
RwInt32 sub_FBA30()
{
    dword_4C192C = RpClumpRegisterPlugin(0x1C, 0x42B1, sub_FBA70, sub_FBAF0,
                                         (RwPluginObjectCopy)RenderWare_ReturnObjectUnchanged);
    return dword_4C192C != 0;
}

// match: ?sub_FBA70@@YAPAXPAXHH@Z @ 0x000FBA70
void *sub_FBA70(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FBA10(arg_0);

    var_4 = new (var_4) type_3D96F0;
    var_4->vf_000();
    return arg_0;
}

// match: ?sub_FBAF0@@YAPAXPAXHH@Z @ 0x000FBAF0
void *sub_FBAF0(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FBA10(arg_0);

    var_4->vf_008(arg_0);
    delete var_4;
    return arg_0;
}

// Likewise for a clump.
// match: ?sub_FBB60@@YAXPAURpClump@@PAUtype_3D3548@@@Z @ 0x000FBB60
void sub_FBB60(RpClump *arg_0, type_3D3548 *arg_4)
{
    type_3D96F0 *var_4 = sub_FBA10(arg_0);

    if (arg_4)
    {
        var_4->unk_14.set_h(arg_4->get_unk_384_h());
    }
    else
    {
        type_3D96F0_14 lv_8;

        var_4->unk_14 = lv_8;
    }
}

// match: ?sub_FBBB0@@YAPAUtype_3D3548@@PAURpClump@@@Z @ 0x000FBBB0
type_3D3548 *sub_FBBB0(RpClump *arg_0)
{
    type_3D96F0 *var_4 = sub_FBA10(arg_0);

    return var_4->unk_14.sub_D4910();
}

// match: ?sub_FBBE0@@YAXPAURpClump@@H@Z @ 0x000FBBE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_FBBE0(RpClump *arg_0, RwInt32 arg_4)
{
    type_3D96F0 *bp_8;
    type_3D96F0_04 bp_4;

    bp_4.unk_00 = arg_4;
    bp_8 = sub_FBA10(arg_0);
    bp_8->unk_04 = bp_4;
}

// match: ?sub_FBC10@@YAXPAURpClump@@PAX@Z @ 0x000FBC10
void sub_FBC10(RpClump *arg_0, void *arg_4)
{
    type_3D96F0 *var_4 = sub_FBA10(arg_0);

    var_4->unk_0C = arg_4;
}

// match: ?sub_FBC30@@YAPAUtype_3D96F0@@PAURwFrame@@@Z @ 0x000FBC30
type_3D96F0 *sub_FBC30(RwFrame *arg_0)
{
    void *bp_8;
    type_3D96F0 *bp_4;

    bp_8 = arg_0;
    bp_4 = RWPLUGINOFFSET(type_3D96F0, bp_8, dword_4C1930);
    return bp_4;
}

void *sub_FBC90(void *, RwInt32, RwInt32);
void *sub_FBD10(void *, RwInt32, RwInt32);

// match: ?sub_FBC50@@YAHXZ @ 0x000FBC50
RwInt32 sub_FBC50()
{
    dword_4C1930 = RwFrameRegisterPlugin(0x1C, 0x42B2, sub_FBC90, sub_FBD10,
                                         (RwPluginObjectCopy)RenderWare_ReturnObjectUnchanged);
    return dword_4C1930 != 0;
}

// match: ?sub_FBC90@@YAPAXPAXHH@Z @ 0x000FBC90
void *sub_FBC90(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FBC30((RwFrame *)arg_0);

    var_4 = new (var_4) type_3D96F0;
    var_4->vf_000();
    return arg_0;
}

// match: ?sub_FBD10@@YAPAXPAXHH@Z @ 0x000FBD10
void *sub_FBD10(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FBC30((RwFrame *)arg_0);

    var_4->vf_008(arg_0);
    delete var_4;
    return arg_0;
}

// Likewise for a frame.
// match: ?sub_FBD80@@YAXPAURwFrame@@PAUtype_3D3548@@@Z @ 0x000FBD80
void sub_FBD80(RwFrame *arg_0, type_3D3548 *arg_4)
{
    type_3D96F0 *var_4 = sub_FBC30(arg_0);

    if (arg_4)
    {
        var_4->unk_14.set_h(arg_4->get_unk_384_h());
    }
    else
    {
        type_3D96F0_14 lv_8;

        var_4->unk_14 = lv_8;
    }
}

// match: ?sub_FBDD0@@YAPAUtype_3D96F0@@PAX@Z @ 0x000FBDD0
type_3D96F0 *sub_FBDD0(void *arg_0)
{
    void *bp_8;
    type_3D96F0 *bp_4;

    bp_8 = arg_0;
    bp_4 = RWPLUGINOFFSET(type_3D96F0, bp_8, dword_4C1934);
    return bp_4;
}

void *sub_FBE30(void *, RwInt32, RwInt32);
void *sub_FBEB0(void *, RwInt32, RwInt32);

// match: ?sub_FBDF0@@YAHXZ @ 0x000FBDF0
RwInt32 sub_FBDF0()
{
    dword_4C1934 = RpLightRegisterPlugin(0x24, 0x42B3, sub_FBE30, sub_FBEB0,
                                         (RwPluginObjectCopy)RenderWare_ReturnObjectUnchanged);
    return dword_4C1934 != 0;
}

// match: ?sub_FBE30@@YAPAXPAXHH@Z @ 0x000FBE30
void *sub_FBE30(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FBDD0(arg_0);

    var_4 = new (var_4) type_3D96FC;
    var_4->vf_000();
    return arg_0;
}

// match: ?sub_FBEB0@@YAPAXPAXHH@Z @ 0x000FBEB0
void *sub_FBEB0(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *var_4 = sub_FBDD0(arg_0);

    var_4->vf_008(arg_0);
    delete var_4;
    return arg_0;
}

// Likewise for a light.
// match: ?sub_FBF20@@YAXPAURpLight@@PAUtype_3D3548@@@Z @ 0x000FBF20
void sub_FBF20(RpLight *arg_0, type_3D3548 *arg_4)
{
    type_3D96F0 *var_4 = sub_FBDD0(arg_0);

    if (arg_4)
    {
        var_4->unk_14.set_h(arg_4->get_unk_384_h());
    }
    else
    {
        type_3D96F0_14 lv_8;

        var_4->unk_14 = lv_8;
    }
}

// match: ?vf_000@type_3D96FC@@UAEXXZ @ 0x000FBF70
void type_3D96FC::vf_000()
{
    type_3D96F0::vf_000();
    unk_1C = 0;
    unk_20 = 0;
}

// match: ?vf_00C@type_3D96FC@@UAEXPAU1@@Z @ 0x000FBFA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D96FC::vf_00C(type_3D96FC *arg_0)
{
    type_3D96F0::vf_004(arg_0);
    unk_1C = 0;
    unk_20 = 0;
}

// match: ?vf_008@type_3D96FC@@UAEXPAX@Z @ 0x000FBFD0
void type_3D96FC::vf_008(void *arg_0)
{

    type_3D96F0::vf_008(arg_0);
    sub_1738D0((RpLight *)arg_0);
}

// match: ?sub_FC000@@YAPAUtype_3D970C@@PAX@Z @ 0x000FC000
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D970C *sub_FC000(void *arg_0)
{
    void *bp_8;
    type_3D970C *bp_4;

    bp_8 = arg_0;
    bp_4 = RWPLUGINOFFSET(type_3D970C, bp_8, dword_4C1938);
    return bp_4;
}

void *sub_FC070(void *, RwInt32, RwInt32);
void *sub_FC0D0(void *, const void *, RwInt32, RwInt32);
void *sub_FC110(void *, RwInt32, RwInt32);
RwStream *sub_FC140(RwStream *, RwInt32, void *, RwInt32, RwInt32);
RwStream *sub_FC1A0(RwStream *, RwInt32, const void *, RwInt32, RwInt32);

// match: ?sub_FC020@@YAHXZ @ 0x000FC020
RwInt32 sub_FC020()
{
    dword_4C1938;

   dword_4C1938 = RpMaterialRegisterPlugin(8, 0x7A7, sub_FC070, sub_FC110, sub_FC0D0);
    RpMaterialRegisterPluginStream(0x7A7, sub_FC140, sub_FC1A0, sub_200B80);
    return dword_4C1938 != 0;
}

// match: ?sub_FC070@@YAPAXPAXHH@Z @ 0x000FC070
void *sub_FC070(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D970C *var_4 = sub_FC000(arg_0);

    var_4 = new (var_4) type_3D970C;
    var_4->vf_000();
    return arg_0;
}

// match: ?sub_FC0D0@@YAPAXPAXPBXHH@Z @ 0x000FC0D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_FC0D0(void *arg_0, const void *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_3D970C *bp_8;
    type_3D970C *bp_4;

    bp_8 = sub_FC000((void *)arg_4);
    bp_4 = sub_FC000(arg_0);
    bp_4->vf_004(bp_8);
    return arg_0;
}

// match: ?sub_FC110@@YAPAXPAXHH@Z @ 0x000FC110
void *sub_FC110(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D970C *var_4 = sub_FC000(arg_0);

    var_4->vf_008(arg_0);
    return arg_0;
}

// match: ?sub_FC140@@YAPAURwStream@@PAU1@HPAXHH@Z @ 0x000FC140
RwStream *sub_FC140(RwStream *arg_0, RwInt32 arg_4, void *arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    type_3D970C *var_4 = sub_FC000(arg_8);

    if (RwStreamRead(arg_0, &var_4->unk_04, 4) != 4)
    {
        return 0;
    }
    if ((var_4->unk_04 & 0xFFFF0000) == 0xFFFF0000)
    {
        var_4->unk_04 = var_4->unk_04 & 0xFFFF;
    }
    return arg_0;
}

// match: ?sub_FC1A0@@YAPAURwStream@@PAU1@HPBXHH@Z @ 0x000FC1A0
RwStream *sub_FC1A0(RwStream *arg_0, RwInt32 arg_4, const void *arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    type_3D970C *var_4 = sub_FC000((void *)arg_8);

    if (!RwStreamWrite(arg_0, &var_4->unk_04, 4))
    {
        return 0;
    }
    return arg_0;
}

// match: ?vf_000@type_3D970C@@UAEXXZ @ 0x000FC1E0
void type_3D970C::vf_000()
{
    unk_04 = 0;
}

// match: ?vf_004@type_3D970C@@UAEXPAU1@@Z @ 0x000FC200
void type_3D970C::vf_004(type_3D970C *arg_0)
{
    unk_04 = arg_0->unk_04;
    if ((unk_04 & 0xFFFF0000) == 0xFFFF0000)
    {
        unk_04 = unk_04 & 0xFFFF;
    }
}

// match: ?vf_000@type_3D96F0@@UAEXXZ @ 0x000FC240
void type_3D96F0::vf_000()
{
    unk_04.unk_00 = 1;
    unk_0A = 0xFFFF;
    unk_08 = 0xFF;
    unk_0C = 0;
    unk_18 = 0;
    unk_10 = 0;
}

// match: ?vf_004@type_3D96F0@@UAEXPAU1@@Z @ 0x000FC280
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D96F0::vf_004(type_3D96F0 *arg_0)
{
    RwInt32 bp_8;
    type_3D96F0_04 bp_4;

    bp_4 = arg_0->unk_04;
    unk_04.unk_00 = bp_4.unk_00;
    unk_0A = 0xFFFF;
    unk_08 = 0xFF;
    bp_8 = arg_0->unk_10;
    unk_10 = bp_8;
}

// match: ?vf_008@type_3D96F0@@UAEXPAX@Z @ 0x000FC2D0
void type_3D96F0::vf_008(void *arg_0)
{
    if (unk_18)
    {
        type_3D96F0_node *next;
        type_3D96F0_node *node;

        node = unk_18;
        next = 0;

        while (node)
        {
            next = node->unk_00;
            sub_FC3B0(node);
            node = next;
        }
        unk_18 = 0;
    }
    if (unk_0C)
    {
        RwInt32 index = sub_19A930((RwInt32)unk_0C, (RwInt32)arg_0);

        if (index >= 0)
        {
            sub_19A8A0((RwInt32)unk_0C, index, (RwInt32)arg_0);
        }
    }
}

// match: ?sub_FC360@type_3D96F0@@QAEXPAUtype_3D96F0_node@@@Z @ 0x000FC360
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D96F0::sub_FC360(type_3D96F0_node *arg_0)
{
    type_3D96F0_node *bp_8;
    type_3D96F0_node *bp_4;

    bp_4 = unk_18;
    arg_0->unk_00 = bp_4;
    arg_0->unk_04 = 0;
    if (unk_18)
    {
        bp_8 = unk_18;
        bp_8->unk_04 = arg_0;
    }
    unk_18 = arg_0;
}

// match: ?sub_FC3B0@type_3D96F0@@QAEXPAUtype_3D96F0_node@@@Z @ 0x000FC3B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D96F0::sub_FC3B0(type_3D96F0_node *arg_0)
{
    type_3D96F0_node *lv_10;
    type_3D96F0_node *slot_C;
    type_3D96F0_node *bp_8;
    type_3D96F0_node *bp_4;

    bp_4 = arg_0->unk_04;
    if (bp_4)
    {
        bp_8 = arg_0->unk_00;
        bp_4->unk_00 = bp_8;
    }
    bp_4 = arg_0->unk_00;
    if (bp_4)
    {
        slot_C = arg_0->unk_04;
        bp_4->unk_04 = slot_C;
    }
    if (arg_0 == unk_18)
    {
        lv_10 = arg_0->unk_00;
        unk_18 = lv_10;
    }
    arg_0->unk_00 = 0;
    arg_0->unk_04 = 0;
    arg_0->unk_08 = 0;
}

// match: ?sub_FC440@type_3D96F0@@QAEGXZ @ 0x000FC440
RwUInt16 type_3D96F0::sub_FC440()
{
    RwUInt16 var_4;

    if (unk_08 == 0xFF)
    {
        var_4 = 0xFFFF;
    }
    else if (unk_08 == 0x7F)
    {
        var_4 = 0x7FFF;
    }
    else
    {
        var_4 = unk_08;
    }
    return var_4;
}

// match: ?sub_FC490@type_3D96F0@@QAEXG@Z @ 0x000FC490
void type_3D96F0::sub_FC490(RwUInt16 arg_0)
{
    unk_08 = (RwUInt8)arg_0;
    if (arg_0 == 0xFFFF)
    {
        unk_08 = 0xFF;
    }
    else if (arg_0 == 0x7FFF)
    {
        unk_08 = 0x7F;
    }
    else
    {
        unk_08 = (RwUInt8)arg_0;
    }
}

// match: ?sub_FC4E0@@YAPAUtype_3D9718@@PAX@Z @ 0x000FC4E0
type_3D9718 *sub_FC4E0(void *arg_0)
{
    void *bp_8;
    type_3D9718 *bp_4;

    bp_8 = arg_0;
    bp_4 = RWPLUGINOFFSET(type_3D9718, bp_8, dword_4C193C);
    return bp_4;
}

void *sub_FC540(void *, RwInt32, RwInt32);
void *sub_FC5E0(void *, RwInt32, RwInt32);

// match: ?sub_FC500@@YAHXZ @ 0x000FC500
RwInt32 sub_FC500()
{
    dword_4C193C = RpWorldRegisterPlugin(0x24, 0x42B5, sub_FC540, sub_FC5E0,
                                         (RwPluginObjectCopy)RenderWare_ReturnObjectUnchanged);
    return dword_4C193C != 0;
}

// match: ?sub_FC540@@YAPAXPAXHH@Z @ 0x000FC540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_FC540(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D9718 *slot_C;
    type_3D9718 *bp_8;
    RwInt32 *bp_4;

    slot_C = sub_FC4E0(arg_0);
    slot_C = new (slot_C) type_3D9718;
    slot_C->vf_000();
    bp_8 = slot_C;
    bp_8++;
    bp_4 = (RwInt32 *)bp_8;
    *bp_4 = 1;
    return arg_0;
}

// match: ?sub_FC5E0@@YAPAXPAXHH@Z @ 0x000FC5E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_FC5E0(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3D96F0 *slot_C;
    type_3D9718 *bp_8;
    RwInt32 *bp_4;

    slot_C = sub_FC4E0(arg_0);
    bp_8 = (type_3D9718 *)slot_C;
    bp_8++;
    bp_4 = (RwInt32 *)bp_8;
    if (*bp_4 == 1)
    {
        slot_C->vf_008(arg_0);
        delete slot_C;
    }
    return arg_0;
}

// match: ?vf_000@type_3D9718@@UAEXXZ @ 0x000FC670
void type_3D9718::vf_000()
{
    type_3D96F0::vf_000();
    unk_1C = 0;
    unk_04.unk_00 = 0;
}

// match: ?vf_00C@type_3D9718@@UAEXPAU1@@Z @ 0x000FC6A0
void type_3D9718::vf_00C(type_3D9718 *arg_0)
{
    RwInt32 var_4;

    type_3D96F0::vf_004(arg_0);
    var_4 = arg_0->unk_1C;
    unk_1C = var_4;
}

// match: ?vf_008@type_3D9718@@UAEXPAX@Z @ 0x000FC6D0
void type_3D9718::vf_008(void *arg_0)
{
    type_3D96F0::vf_008(arg_0);
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_008@type_3D970C@@UAEXPAX@Z (folded into the empty body at 0x15FB30)
void type_3D970C::vf_008(void *arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3D96F0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D96F0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ??2type_3D970C@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D970C::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?sub_D4910@type_3D96F0_14@@QAEPAUtype_3D3548@@XZ (folded into 0xD4910)
struct type_3D3548 *type_3D96F0_14::sub_D4910()
{
    type_3D3548 *var_4;

    var_4 = 0;
    if (dword_4B6A00[(RwInt16)unk_00].unk_00 == unk_00)
    {
        var_4 = dword_4B6A00[(RwInt16)unk_00].unk_04;
    }
    return var_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3D96F0@@SAXPAX@Z (folded into 0x19A750)
void type_3D96F0::operator delete(void * arg_0)
{
}

// The material extension's stream size: the value's four bytes, the body
// /OPT:ICF shares with the element sizes at 0x200B80.
// ?sub_200B80@@YAHPBXHH@Z (folded into 0x200B80)
RwInt32 sub_200B80(const void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    return 4;
}
