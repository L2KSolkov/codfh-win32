// The world manager (game/worldmgr.h).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "rw/bamemory.h"
#include "rw/rplight.h"
#include "rw/rpworld.h"
#include "rw/rtdict.h"
#include "rw/rt2d.h"
#include "rw/rpuvanim.h"
#include "rws/mainloop.h"
#include "game/worldmgr.h"
#include "game/particles.h"
#include "game/render.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/frontend.h"
#include "game/functions.h"
#include "game/clumpbank.h"
#include "game/weaponbank.h"
#include "game/clumputil.h"
#include "types/WorldLight.h"
#include "types/type_141C10.h"
#include "types/SectionInfo.h"
#include "types/StartingSections.h"
#include "rw/bavector.h"
#include "types/type_3D96F0.h"
#include "types/type_44350.h"
#include "types/type_3D3548.h"
#include "types/type_4B85F8.h"
#include <stdio.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DD530
extern const RwReal flt_3DD530 = 16.666666f;
// 0x00429EAC
RwInt16 word_429EAC = -1;
// 0x00429EB0
RwInt32 dword_429EB0 = -1;
// 0x004E5BD0
type_4E5BD0 dword_4E5BD0;
// 0x004E5BE0
type_8F3E0 dword_4E5BE0;
// 0x004E5C60
#ifndef CODFH_PLAIN
RwRGBAReal unk_4E5C60;
#endif
// 0x004E5C70
#ifndef CODFH_PLAIN
RwInt32 dword_4E5C70;
#endif
// 0x004E5C74
#ifndef CODFH_PLAIN
RwInt32 dword_4E5C74;
#endif
// 0x004E5C78
#ifndef CODFH_PLAIN
RpWorld *dword_4E5C78;
#endif
// 0x004E5C7C
#ifndef CODFH_PLAIN
RpLight *dword_4E5C7C;
#endif
// 0x004E5C80
#ifndef CODFH_PLAIN
RpWorld *world;
#endif
// 0x004E5C84
#ifndef CODFH_PLAIN
RpWorld *dword_4E5C84;
#endif
// 0x004E5C88
#ifndef CODFH_PLAIN
RpWorld *dword_4E5C88;
#endif
// 0x004E5C8C
#ifndef CODFH_PLAIN
RwTexDictionary *dword_4E5C8C;
#endif
// 0x004E5C90
#ifndef CODFH_PLAIN
RwTexDictionary *dword_4E5C90;
#endif
// 0x004E5C94
#ifndef CODFH_PLAIN
RpLight *clump;
#endif
// 0x004E5C98
#ifndef CODFH_PLAIN
RpLight *dword_4E5C98[4];
#endif
// 0x004E5CA8
#ifndef CODFH_PLAIN
RpLight *camera;
#endif
// 0x004E5CAC
#ifndef CODFH_PLAIN
RwInt32 dword_4E5CAC;
#endif
// 0x004E5CB0
RwUInt32 dword_4E5CB0;
// 0x004E5CB4
RwInt32 dword_4E5CB4;
// 0x004E5CB8
RwInt32 dword_4E5CB8;
// 0x004E5CBC
RwInt32 dword_4E5CBC;
// 0x004E5CC0
RtDict *schema;
// 0x004E5CC4
RwInt32 dword_4E5CC4;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4E5CC8 unk_4E5CC8;
type_4E5D30 dword_4E5D30[4];
type_4E5D30 unk_4E5CD8;
type_D48D0 dword_4E5D1C[4];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DD530@@3MB @ 0x003DD530
// match: ??_C@_0DC@FPHJFKFE@Default?5world?5is?5not?5empty?5at?5re@ @ 0x003DD534
// match: ??_C@_0DH@IIHFDNKL@SkyBox?5extra?5world?5is?5not?5empty?5@ @ 0x003DD568
// match: ??_C@_0DH@LMCCMACG@SkyBox?5alpha?5world?5is?5not?5empty?5@ @ 0x003DD5A0
// match: ??_C@_0DB@MAELLHLJ@SkyBox?5world?5is?5not?5empty?5at?5res@ @ 0x003DD5D8
// match: ??_C@_0EJ@DFCCCHGE@Extra?5world?5is?5not?5empty?5for?5sec@ @ 0x003DD610
// match: ??_C@_0EN@HBLNFFHA@Collision?5world?5is?5not?5empty?5for@ @ 0x003DD660
// match: ??_C@_0EJ@DFALFKJL@Alpha?5world?5is?5not?5empty?5for?5sec@ @ 0x003DD6B0
// match: ??_C@_0EK@DOOOFNEC@Opaque?5world?5is?5not?5empty?5for?5se@ @ 0x003DD700
// match: __real@49800000 @ 0x003DD74C
// match: ??_C@_0DP@BLLPEIIN@Unable?5to?5destroy?5Texture?5Dictio@ @ 0x003DD750
// match: ??_C@_04BOJCACFA@?$CB?$CB?$CB?6?$AA@ @ 0x003DD790
// match: ??_C@_0BN@COEDKBFM@Removing?5world?5?$CFd?5in?5bank?5?$CFd?$AA@ @ 0x003DD798
// match: ??_C@_0BO@JHNIKDDH@Unable?5to?5destroy?5shared?4txd?$CB?$AA@ @ 0x003DD7B8
// match: ??_C@_0ED@LEJBFOCK@Extra?5world?5was?5not?5deleted?5for?5@ @ 0x003DD7D8
// match: ??_C@_0EK@CGFCAIBB@Texture?5dictionary?5was?5not?5delet@ @ 0x003DD820
// match: ??_C@_0EH@GJEMCFLJ@Collision?5world?5was?5not?5deleted?5@ @ 0x003DD870
// match: ??_C@_0ED@MCKPCCMB@Alpha?5world?5was?5not?5deleted?5for?5@ @ 0x003DD8B8
// match: ??_C@_0EE@HNOIHEEK@Opaque?5world?5was?5not?5deleted?5for@ @ 0x003DD900
// match: .CRT$XCU+0 @ 0x00427148
// match: .CRT$XCU+4 @ 0x0042714C
// match: .CRT$XCU+8 @ 0x00427150
// match: .CRT$XCU+12 @ 0x00427154
// match: ?word_429EAC@@3FA @ 0x00429EAC
// match: ?dword_429EB0@@3HA @ 0x00429EB0

// match: _$E2 @ 0x0030BDE0
// match: _$E3 @ 0x0030E900
// match: _$E5 @ 0x0030BE00
// match: _$E6 @ 0x0030E910
// match: _$E8 @ 0x0030BE30
// match: _$E9 @ 0x0030E930
// match: _$E11 @ 0x0030BE50
// match: _$E12 @ 0x0030E940
// match: ?sub_171DC0@@YAXXZ @ 0x00171DC0
// sp-match: _$E2 @ 0x0021DD10
// sp-match: _$E5 @ 0x0021DD30
// sp-match: _$E8 @ 0x0021DD60
// sp-match: _$E11 @ 0x0021DD80
// sp-match: _$E3 @ 0x0021ECC0
// sp-match: _$E6 @ 0x0021ECD0
// sp-match: _$E12 @ 0x0021ED00
// sp-match: ?sub_171DC0@@YAXXZ @ 0x0010F610
// sp-match: _$E9 @ 0x0021ECF0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets the manager up: everything cleared, the UV animation dictionary,
// the four directional lights, the default zone, the sections, the
// default world with the main camera in it.
void sub_171DC0()
{
    RwFrame *var_34;
    RpLight *lv_30;
    RwRGBAReal fp_2C;
    RwCamera *ebp_1C;
    RpWorld *l18;
    RwInt32 v14;
    RwRGBAReal lv_10;

    v14 = 0;
    dword_4E5CC4 = 0;
    dword_4E5C74 = 0;
    dword_4E5CBC = 0;
    dword_4E5C78 = 0;
    dword_4E5C7C = 0;
    world = 0;
    dword_4E5C84 = 0;
    dword_4E5C88 = 0;
    dword_4E5C8C = 0;
    dword_4E5C90 = 0;
    word_429EAC = -1;
    schema = 0;
    dword_429EB0 = 0;
    clump = 0;
    unk_4E5C60.alpha = 0;
    unk_4E5C60.blue = 0;
    unk_4E5C60.green = 0;
    unk_4E5C60.red = 0;
    for (v14 = 0; v14 < 4; v14++)
        dword_4E5C98[v14] = 0;
    schema = RtDictSchemaCreateDict(&_rpUVAnimDictSchema);
    RtDictSchemaSetCurrentDict(&_rpUVAnimDictSchema, schema);
    sub_159AC0();
    fp_2C.red = 0;
    fp_2C.green = 0;
    fp_2C.blue = 0;
    fp_2C.alpha = 1.0f;
    camera = RpLightCreate(rpLIGHTDIRECTIONAL);
    RpLightSetColor(camera, &fp_2C);
    RpLightSetFrame(camera, RwFrameCreate());
    lv_10.red = 0;
    lv_10.green = 0;
    lv_10.blue = 0;
    lv_10.alpha = 0;
    for (v14 = 1; v14 < 4; v14++)
    {
        lv_30 = RpLightCreate(rpLIGHTDIRECTIONAL);
        RpLightSetColor(lv_30, &lv_10);
        var_34 = RwFrameCreate();
        RwFrameSetIdentity(var_34);
        RpLightSetFrame(lv_30, var_34);
        dword_4E5C98[v14] = lv_30;
    }
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_10.unk_00 = 500000.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_10.unk_04 = 500000.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_10.unk_08 = 500000.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_10.unk_0C = 1.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_00.unk_00 = -500000.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_00.unk_04 = -500000.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_00.unk_08 = -500000.0f;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_00.unk_0C = 1.0f;
#ifdef CODFH_SP
    // shape: the cleared red stored as the integer 0 (SP 0x10F610 stores esi)
    *(RwInt32 *)&unk_4E5C60.red = 0;
#else
    unk_4E5C60.red = 0;
#endif
    for (v14 = 0; v14 < 3; v14++)
    {
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_10.unk_00 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_10.unk_04 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_10.unk_08 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_10.unk_0C = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_00.unk_00 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_00.unk_04 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_00.unk_08 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[v14].unk_00.unk_0C = 0;
    }
    for (v14 = 0; v14 < 4; v14++)
    {
        dword_4E5D30[v14].sub_174790();
        dword_4E5D30[v14].unk_0A = (RwUInt16)v14;
        dword_4E5D30[v14].unk_1C = 0;
    }
    unk_4E5CD8.sub_174790();
    unk_4E5CD8.unk_0A = 0x7FFF;
    sub_173CE0(sub_1331E0(), 0, (RwUInt16)0x7FFF);
    sub_173CE0(sub_1331E0(), 1, (RwUInt16)0x7FFF);
    sub_173CE0(sub_1331E0(), 2, (RwUInt16)0x7FFF);
    for (v14 = 0; v14 < 4; v14++)
        dword_4E5D1C[v14].sub_D48D0(0);
    dword_4E5CAC = 0;
    dword_4E5CB0 = 0;
    dword_4E5BD0.unk_00 = 0;
    dword_4E5BD0.unk_04 = 0;
    dword_4E5BD0.unk_08 = 0;
    dword_4E5CB4 = 0;
    dword_4E5CB8 = 0;
    sub_2DA2F0(0, 0);
    l18 = sub_1331E0();
    dword_4E5C78 = l18;
    ebp_1C = RWS::MainLoop::Render::GetCamera();
    dword_4E5C74 = (RwInt32)ebp_1C;
    ebp_1C = RWS::MainLoop::Render::sub_1323C0();
    dword_4E5CBC = (RwInt32)ebp_1C;
    RpWorldAddCamera(l18, ebp_1C);
    dword_4E5C70 = 1;
}

// match: ?sub_172210@@YAXXZ @ 0x00172210
// sp-match: ?sub_172210@@YAXXZ @ 0x0010F990
void sub_172210()
{
    sub_1724C0();
    sub_172480();
    word_429EAC = -1;
}

// match: ?sub_172230@@YAXXZ @ 0x00172230
// sp-match: ?sub_172230@@YAXXZ @ 0x0010FF50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shuts the manager down: the lights, the cameras taken out of their
// worlds, the sections, the default world, shared.txd.
void sub_172230()
{
    RwFrame *var_18;
    RpWorld *var_14;
    RwInt32 lv_10;
    RwFrame *var_C;
    RwCamera *bp_8;
    RpWorld *bp_4;

    if (camera)
    {
        var_C = RpLightGetFrame(camera);
        if (var_C)
        {
            RpLightSetFrame(camera, 0);
            RwFrameDestroy(var_C);
        }
        RpLightDestroy(camera);
    }
    for (lv_10 = 1; lv_10 < 4; lv_10++)
    {
        if (dword_4E5C98[lv_10])
        {
            var_14 = RpLightGetWorld(dword_4E5C98[lv_10]);
            if (var_14)
                RpWorldRemoveLight(var_14, dword_4E5C98[lv_10]);
            var_18 = RpLightGetFrame(dword_4E5C98[lv_10]);
            RwFrameDestroy(var_18);
            RpLightDestroy(dword_4E5C98[lv_10]);
        }
    }
    sub_172480();
    bp_8 = (RwCamera *)dword_4E5C74;
    bp_4 = 0;
    if (bp_8)
    {
        bp_4 = RwCameraGetWorld(bp_8);
        if (bp_4)
            RpWorldRemoveCamera(bp_4, bp_8);
        dword_4E5C74 = 0;
    }
    bp_8 = (RwCamera *)dword_4E5CBC;
    if (bp_8)
    {
        bp_4 = RwCameraGetWorld(bp_8);
        if (bp_4)
            RpWorldRemoveCamera(bp_4, bp_8);
        dword_4E5CBC = 0;
    }
    sub_1724C0();
    sub_172430();
    sub_174060(&unk_4E5CD8, 0);
    unk_4E5CD8.sub_1747D0();
#ifdef CODFH_SP
    // shape: an unsigned 0xFFFF store, not CSE'd with the -1 below (SP 0x10FF50 stores both as immediates)
    *(RwUInt16 *)&word_429EAC = 0xFFFF;
#else
    word_429EAC = -1;
#endif
    sub_1744A0();
    bp_4 = dword_4E5C78;
    if (bp_4)
    {
        RpWorldDestroy(bp_4);
        dword_4E5C78 = 0;
    }
    sub_174530();
    sub_1746B0();
    dword_429EB0 = -1;
    if (dword_4E5CC4)
    {
        operator delete((void *)dword_4E5CC4);
        dword_4E5CC4 = 0;
    }
    dword_4E5C70 = 0;
}

// match: ?sub_172430@@YAXXZ @ 0x00172430
// sp-match: ?sub_172430@@YAXXZ @ 0x0010FF00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Unloads the four sections.
void sub_172430()
{
    type_4E5D30 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 4; l4++)
    {
        var_8 = &dword_4E5D30[l4];
        sub_174060(var_8, 0);
        var_8->sub_1747D0();
    }
}

// match: ?sub_172480@@YAXXZ @ 0x00172480
// sp-match: ?sub_172480@@YAXXZ @ 0x0010E510
void sub_172480()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
        dword_4E5D1C[var_4].sub_D48D0(0);
}

// match: ?sub_1724C0@@YAXXZ @ 0x001724C0
// sp-match: ?sub_1724C0@@YAXXZ @ 0x0010E530
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Warns of every world still holding something at a restart or shutdown.
void sub_1724C0()
{
    type_4E5D30 *var_114;
    RwChar var_110[0x100];
    RwInt32 var_8;
    RpWorld *l4;

    for (var_8 = 0; var_8 < 5; var_8++)
    {
        if (var_8 < 4)
            var_114 = &dword_4E5D30[var_8];
        else
            var_114 = &unk_4E5CD8;
        l4 = var_114->unk_20;
        if (l4 && !sub_16E5C0(l4, 0, 0))
        {
            sprintf(var_110, "Opaque world is not empty for section ID %d bank %d at restart//shutdown\n",
                    var_114->get_unk_08(), var_8);
#ifndef CODFH_SP
            // single player compiles the debug prints out (SP 0x10E530)
            sub_19A750(var_110);
#endif
        }
        l4 = var_114->unk_24;
        if (l4 && !sub_16E5C0(l4, 0, 0))
        {
            sprintf(var_110, "Alpha world is not empty for section ID %d bank %d at restart//shutdown\n",
                    var_114->get_unk_08(), var_8);
#ifndef CODFH_SP
            sub_19A750(var_110);
#endif
        }
        l4 = var_114->unk_28;
        if (l4 && !sub_16E5C0(l4, 0, 0))
        {
            sprintf(var_110, "Collision world is not empty for section ID %d bank %d at restart//shutdown\n",
                    var_114->get_unk_08(), var_8);
#ifndef CODFH_SP
            sub_19A750(var_110);
#endif
        }
        l4 = var_114->unk_2C;
        if (l4 && !sub_16E5C0(l4, 0, 0))
        {
            sprintf(var_110, "Extra world is not empty for section ID %d bank %d at restart//shutdown\n",
                    var_114->get_unk_08(), var_8);
#ifndef CODFH_SP
            sub_19A750(var_110);
#endif
        }
    }
    if (world && !sub_16E5C0(world, 0, 0))
    {
        sprintf(var_110, "SkyBox world is not empty at restart//shutdown!\n");
#ifndef CODFH_SP
        sub_19A750(var_110);
#endif
    }
    if (dword_4E5C84 && !sub_16E5C0(dword_4E5C84, 0, 0))
    {
        sprintf(var_110, "SkyBox alpha world is not empty at restart//shutdown!\n");
#ifndef CODFH_SP
        sub_19A750(var_110);
#endif
    }
    if (dword_4E5C88 && !sub_16E5C0(dword_4E5C88, 0, 0))
    {
        sprintf(var_110, "SkyBox extra world is not empty at restart//shutdown!\n");
#ifndef CODFH_SP
        sub_19A750(var_110);
#endif
    }
    if (dword_4E5C78 && !sub_16E5C0(dword_4E5C78, 0, 0))
    {
        sprintf(var_110, "Default world is not empty at restart//shutdown!\n");
#ifndef CODFH_SP
        sub_19A750(var_110);
#endif
    }
}

// match: ?sub_1727E0@@YAXPAH@Z @ 0x001727E0
// sp-match: ?sub_1727E0@@YAXPAH@Z @ 0x0010E700
void sub_1727E0(RwInt32 *arg_0)
{
    dword_4B6850 = 1;
    dword_4B6840[0] = arg_0[0];
    dword_4B6840[1] = arg_0[1];
    dword_4B6840[2] = arg_0[2];
    dword_4B6840[3] = arg_0[3];
}

// match: ?sub_172820@@YAHXZ @ 0x00172820
// sp-match: ?sub_172820@@YAHXZ @ 0x0010E740
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Allocates the arena: the clump banks' heap, the weapon banks' heaps and
// the sections' (the four sizes SectionInfo gives, else a global
// dictionary of its megabytes, 8MB by default), each 128-aligned; 0 when
// it cannot.
RwInt32 sub_172820()
{
    type_4E5D30_10 *w38;
    RwInt32 ebp_34;
    RwUInt32 var_30;
    RwInt32 v2C;
    type_4E5D30_10 *lcl_28;
    RwInt32 frm_24;
    RwUInt32 *var_20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwReal var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    m_18 = 1;
    bp_8 = 0;
    ebp_14 = 0;
    l1C = 0;
    var_C = SectionInfo::sub_B0160();
    bp_4 = SectionInfo::sub_B0140();
    if (!bp_4)
    {
        if (var_C == 0.0f)
            bp_8 = 0x800000;
        else
            bp_8 = (RwInt32)(1048576.0f * var_C);
    }
    else
    {
        var_20 = SectionInfo::sub_B0150();
        for (frm_24 = 0; frm_24 < 4; frm_24++)
        {
            v2C = var_20[frm_24];
            if (v2C & 0x7F)
                v2C = 0x80 - (v2C & 0x7F) + v2C;
            lcl_28 = &dword_4E5D30[frm_24].unk_10;
            lcl_28->unk_00 = 0;
            lcl_28->unk_04 = 0;
            lcl_28->unk_08 = v2C;
            bp_8 += v2C;
        }
    }
    lv_10 = 0x80;
    if ((lv_10 - 1) & bp_8)
        bp_8 = lv_10 - ((lv_10 - 1) & bp_8) + bp_8;
    ebp_14 = dword_4E51B8.unk_08;
    if ((lv_10 - 1) & ebp_14)
        ebp_14 = lv_10 - ((lv_10 - 1) & ebp_14) + ebp_14;
    l1C = sub_16FF40();
    if ((lv_10 - 1) & l1C)
        l1C = lv_10 - ((lv_10 - 1) & l1C) + l1C;
    dword_4E5CB4 = 0;
    dword_4E5CB8 = 0;
    dword_4E5CB0 = (RwUInt32)RwMalloc(bp_8 + ebp_14 + l1C, 0x3425B); // not an address: a memory hint
    dword_4E5CAC = dword_4E5CB0 + ebp_14 + l1C;
    sub_16F280(dword_4E5CB0);
    sub_16FE80(dword_4E5CB0 + ebp_14);
    if (dword_4E5CAC)
    {
        dword_4E5CB8 = bp_8 + ebp_14 + l1C;
        dword_4E5CB4 = bp_8;
        dword_50F250 = dword_4E5CB0;
        dword_50F254 = dword_4E5CB0 + dword_4E5CB8;
        if (bp_4)
        {
            var_30 = dword_4E5CAC;
            for (ebp_34 = 0; ebp_34 < 4; ebp_34++)
            {
                w38 = &dword_4E5D30[ebp_34].unk_10;
                w38->unk_00 = var_30;
                var_30 += w38->unk_08;
            }
        }
    }
    else
    {
        m_18 = 0;
    }
    return m_18;
}

// match: ?sub_172A80@@YAXXZ @ 0x00172A80
// sp-match: ?sub_172A80@@YAXXZ @ 0x0010E930
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Frees the arena and its heaps, and gives RenderWare its memory functions
// back.
void sub_172A80()
{
    type_4E5D30_10 *var_C;
    RwInt32 bp_8;
    RwMemoryFunctions *bp_4;

    if (dword_4E5CB0)
    {
        dword_50F250 = 0;
        dword_50F254 = 0;
        RwFree((void *)dword_4E5CB0);
        dword_4E5CAC = 0;
        dword_4E5CB0 = 0;
        dword_4E5BD0.unk_00 = 0;
        dword_4E5BD0.unk_04 = 0;
        dword_4E5BD0.unk_08 = 0;
        dword_4E5CB8 = 0;
        dword_4E5CB4 = 0;
        sub_16F280(0);
        set_clump_heap_size(0);
        sub_16FE80(0);
        sub_16FF00(0);
        for (bp_8 = 0; bp_8 < 4; bp_8++)
        {
            var_C = &dword_4E5D30[bp_8].unk_10;
            var_C->unk_00 = 0;
            var_C->unk_04 = 0;
            var_C->unk_08 = 0;
        }
        bp_4 = RwOsGetMemoryInterface();
        bp_4->rwmalloc = dword_50F258;
        bp_4->rwrealloc = dword_50F25C;
        bp_4->rwcalloc = dword_50F260;
        bp_4->rwfree = dword_524488;
    }
}

// match: ?sub_172BB0@@YAXXZ @ 0x00172BB0
// sp-match: ?sub_172BB0@@YAXXZ @ 0x0010EA10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shares the sections' part of the arena (after the global dictionary's)
// between the four sections, 128-aligned.
void sub_172BB0()
{
    type_4E5D30_10 *var_18;
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    bp_8 = (dword_4E5CB4 - dword_4E5BD0.unk_08) / 4;
    if (bp_8 >= 0x80)
    {
        lv_10 = bp_8 / 0x80;
        var_C = lv_10 << 7;
        bp_8 = var_C;
    }
    bp_4 = dword_4E5CAC + dword_4E5BD0.unk_08;
    for (var_14 = 0; var_14 < 4; var_14++)
    {
        var_18 = &dword_4E5D30[var_14].unk_10;
        var_18->unk_00 = bp_4;
        var_18->unk_04 = 0;
        var_18->unk_08 = bp_8;
        bp_4 += bp_8;
    }
}

// match: ?sub_172C60@@YAGPAURwFrame@@PAUtype_3D96F0@@@Z @ 0x00172C60
// sp-match: ?sub_172C60@@YAGPAURwFrame@@PAUtype_3D96F0@@@Z @ 0x0010EA90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The section whose world (by the extension arg_4's flags: alpha,
// collision or opaque) holds the frame arg_0's position, the nearest
// centre winning; 0x7FFF (the global section) when none does.
RwUInt16 sub_172C60(RwFrame *arg_0, type_3D96F0 *arg_4)
{
    RwV3d var_3C;
    RwV3d var_30;
    RwBBox *var_24;
    RwInt32 var_20;
    RwReal l1C;
    RwInt32 m_18;
    RwV3d *ebp_14;
    RwReal lv_10;
    RwUInt16 var_C;
    type_3D96F0_04 bp_8;
    RpWorld *bp_4;

    ebp_14 = &RwFrameGetLTM(arg_0)->pos;
    bp_4 = 0;
    var_C = 0xFFFF;
    lv_10 = 1.0e12f;
    bp_8 = arg_4->unk_04;
    for (m_18 = 0; m_18 < 4; m_18++)
    {
        if (dword_4E5D30[m_18].get_unk_00())
        {
            bp_4 = 0;
            if (bp_8.unk_00_1)
                bp_4 = dword_4E5D30[m_18].unk_24;
            else if (bp_8.unk_00_2)
                bp_4 = dword_4E5D30[m_18].unk_28;
            else
                bp_4 = dword_4E5D30[m_18].unk_20;
            if (bp_4)
            {
                var_24 = &bp_4->boundingBox;
                var_20 = 0;
                l1C = 0;
                var_3C.x = 0;
                var_3C.y = 0;
                var_3C.z = 0;
                var_30.x = 0;
                var_30.y = 0;
                var_30.z = 0;
                RwV3dSubMacro(&var_3C, &var_24->sup, &var_24->inf);
                RwV3dAddMacro(&var_30, &var_24->inf, &var_3C);
                RwV3dSubMacro(&var_3C, &var_30, ebp_14);
#ifdef CODFH_SP
                // shape: the squared length summed from z down (SP 0x10EA90)
                l1C = var_3C.z * var_3C.z + var_3C.y * var_3C.y + var_3C.x * var_3C.x;
#else
                l1C = RwV3dDotProductMacro(&var_3C, &var_3C);
#endif
                if (ebp_14->x <= var_24->sup.x && ebp_14->x >= var_24->inf.x && ebp_14->y <= var_24->sup.y
                    && ebp_14->y >= var_24->inf.y && ebp_14->z <= var_24->sup.z && ebp_14->z >= var_24->inf.z)
                    var_20 = 1;
                if (var_20 && l1C < lv_10)
                {
                    var_C = (RwUInt16)m_18;
                    lv_10 = l1C;
                }
            }
        }
    }
    if (var_C != 0xFFFF)
        return var_C;
    return 0x7FFF;
}

// match: ?sub_172EB0@@YAPAURpWorld@@GPAUtype_3D96F0@@@Z @ 0x00172EB0
// sp-match: ?sub_172EB0@@YAPAURpWorld@@GPAUtype_3D96F0@@@Z @ 0x0010EBE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The world of the section arg_0 (0x7FFF: the global section) the
// extension arg_4's flags pick; the default world without one.
RpWorld *sub_172EB0(RwUInt16 arg_0, type_3D96F0 *arg_4)
{
    type_3D96F0_04 var_C;
    type_4E5D30 *bp_8;
    RpWorld *bp_4;

    bp_4 = 0;
    bp_8 = 0;
    if ((RwInt16)arg_0 >= 0 && arg_0 < 4)
        bp_8 = &dword_4E5D30[arg_0];
    else if (arg_0 == 0x7FFF)
        bp_8 = &unk_4E5CD8;
    if (bp_8)
    {
        var_C = arg_4->unk_04;
        if (var_C.unk_00_1)
            bp_4 = bp_8->unk_24;
        else if (var_C.unk_00_2)
            bp_4 = bp_8->unk_28;
        else
            bp_4 = bp_8->unk_20;
    }
    if (!bp_4)
        bp_4 = dword_4E5C78;
    return bp_4;
}

// match: ?sub_172F60@@YAHPAURpWorld@@0@Z @ 0x00172F60
// sp-match: ?sub_172F60@@YAHPAURpWorld@@0@Z @ 0x0010EC40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether the worlds arg_0 and arg_4 are one world of one section.
RwInt32 sub_172F60(RpWorld *arg_0, RpWorld *arg_4)
{
    type_3D9718 *var_C;
    type_3D9718 *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    if (arg_0 && arg_4 && arg_0 == arg_4)
    {
        bp_8 = sub_FC4E0(arg_0);
        var_C = sub_FC4E0(arg_4);
        if (bp_8->get_unk_0A() == var_C->get_unk_0A() && bp_8->sub_FC440() == var_C->sub_FC440())
            bp_4 = 1;
    }
    return bp_4;
}

// match: ?sub_172FF0@@YAPAURpWorld@@PAHPAURwFrame@@PAUtype_3D96F0@@PAU1@@Z @ 0x00172FF0
// sp-match: ?sub_172FF0@@YAPAURpWorld@@PAHPAURwFrame@@PAUtype_3D96F0@@PAU1@@Z @ 0x0010F9B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The world the frame arg_4 (with the extension arg_8) belongs in; *arg_0
// says whether it moves (1), stays (0) or is new (2, no world arg_C), and
// the extension takes the section when it is not staying.
RpWorld *sub_172FF0(RwInt32 *arg_0, RwFrame *arg_4, type_3D96F0 *arg_8, RpWorld *arg_C)
{
    RwInt32 var_C;
    RwUInt16 bp_8;
    RpWorld *bp_4;

    bp_8 = sub_172C60(arg_4, arg_8);
    bp_4 = sub_172EB0(bp_8, arg_8);
    if (arg_C)
    {
        var_C = sub_172F60(bp_4, arg_C);
        if (!var_C)
            *arg_0 = 1;
        else
            *arg_0 = 0;
    }
    else
    {
        *arg_0 = 2;
    }
    if (*arg_0)
        sub_173080(bp_8, arg_8);
    return bp_4;
}

// match: ?sub_173080@@YAXGPAUtype_3D96F0@@@Z @ 0x00173080
// sp-match: ?sub_173080@@YAXGPAUtype_3D96F0@@@Z @ 0x0010ECB0
// Gives the extension arg_4 the section arg_0 (and its level section).
void sub_173080(RwUInt16 arg_0, type_3D96F0 *arg_4)
{
    if (arg_0 == 0xFFFF)
    {
        arg_4->sub_FC490(0xFFFF);
        arg_4->unk_0A = 0xFFFF;
    }
    else if (arg_0 == 0x7FFF)
    {
        arg_4->sub_FC490(0x7FFF);
        arg_4->unk_0A = 0x7FFF;
    }
    else
    {
        arg_4->sub_FC490(arg_0);
        arg_4->unk_0A = dword_4E5D30[arg_0].get_unk_08();
    }
}

// match: ?sub_173100@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x00173100
// sp-match: ?sub_173100@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010ED20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// An atomic callback: the atomic arg_0 takes the section arg_4.
RpAtomic *sub_173100(RpAtomic *arg_0, void *arg_4)
{
    type_3D96F0 *var_8;
    RwUInt16 l4;

    l4 = (RwUInt16)(RwUInt32)arg_4;
    var_8 = sub_FB7A0(arg_0);
    sub_173080(l4, var_8);
    return arg_0;
}

// match: ?sub_173140@@YAPAURpLight@@PAU1@PAX@Z @ 0x00173140
// sp-match: ?sub_173140@@YAPAURpLight@@PAU1@PAX@Z @ 0x0010ED40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise for the light arg_0.
RpLight *sub_173140(RpLight *arg_0, void *arg_4)
{
    type_3D96F0 *var_8;
    RwUInt16 l4;

    l4 = (RwUInt16)(RwUInt32)arg_4;
    var_8 = sub_FBDD0(arg_0);
    sub_173080(l4, var_8);
    return arg_0;
}

// match: ?sub_173180@@YAPAURpWorld@@PAURpClump@@@Z @ 0x00173180
// sp-match: ?sub_173180@@YAPAURpWorld@@PAURpClump@@@Z @ 0x0010FA30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Puts the clump arg_0 in the world its position picks (the global
// section's opaque world for an entity whose trigger has flag 10 of +0x24,
// unless its extension is a collision one), with its atomics and lights
// tagged; returns the world.
RpWorld *sub_173180(RpClump *arg_0)
{
    type_3D96F0_04 var_24;
    type_712B0 *var_20;
    type_3D3548 *l1C;
    type_3D96F0 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RpWorld *var_C;
    RpWorld *bp_8;
    RwFrame *bp_4;

    bp_4 = RpClumpGetFrame(arg_0);
    m_18 = sub_FBA10(arg_0);
    var_C = RpClumpGetWorld(arg_0);
    ebp_14 = -1;
    lv_10 = 0;
    var_24 = m_18->unk_04;
    if (!var_24.unk_00_2)
    {
        l1C = sub_FBBB0(arg_0);
        if (l1C)
        {
            var_20 = l1C->get_unk_34C();
            if (var_20)
                lv_10 = var_20->unk_24_10;
        }
    }
    if (lv_10)
    {
        bp_8 = unk_4E5CD8.unk_20;
        if (var_C && var_C != bp_8)
            ebp_14 = 1;
        else
            ebp_14 = var_C != bp_8 ? 2 : 0;
        if (ebp_14)
            sub_173080(0x7FFF, m_18);
    }
    else
    {
        bp_8 = sub_172FF0(&ebp_14, bp_4, m_18, var_C);
    }
    switch (ebp_14)
    {
    case 1:
        RpClumpForAllAtomics(arg_0, sub_1734E0, 0);
        RpClumpForAllLights(arg_0, sub_173540, 0);
        RpWorldRemoveClump(var_C, arg_0);
    case 2:
        RpWorldAddClump(bp_8, arg_0);
        RpClumpForAllAtomics(arg_0, sub_173100, (void *)m_18->sub_FC440());
        RpClumpForAllLights(arg_0, sub_173140, (void *)m_18->sub_FC440());
        break;
    }
    return bp_8;
}

// match: ?sub_173320@@YAPAURpWorld@@PAURpAtomic@@@Z @ 0x00173320
// sp-match: ?sub_173320@@YAPAURpWorld@@PAURpAtomic@@@Z @ 0x0010FB60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise for the atomic arg_0.
RpWorld *sub_173320(RpAtomic *arg_0)
{
    type_3D96F0_04 var_24;
    type_712B0 *var_20;
    type_3D3548 *l1C;
    type_3D96F0 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RpWorld *var_C;
    RpWorld *bp_8;
    RwFrame *bp_4;

    bp_4 = RpAtomicGetFrame(arg_0);
    m_18 = sub_FB7A0(arg_0);
    var_C = RpAtomicGetWorld(arg_0);
    ebp_14 = -1;
    lv_10 = 0;
    var_24 = m_18->unk_04;
    if (!var_24.unk_00_2)
    {
        l1C = sub_FB960(arg_0);
        if (l1C)
        {
            var_20 = l1C->get_unk_34C();
            if (var_20)
                lv_10 = var_20->unk_24_10;
        }
    }
    if (lv_10)
    {
        bp_8 = unk_4E5CD8.unk_20;
        if (var_C && var_C != bp_8)
            ebp_14 = 1;
        else
            ebp_14 = var_C != bp_8 ? 2 : 0;
        if (ebp_14)
            sub_173080(0x7FFF, m_18);
    }
    else
    {
        bp_8 = sub_172FF0(&ebp_14, bp_4, m_18, var_C);
    }
    switch (ebp_14)
    {
    case 1:
        RpWorldRemoveAtomic(var_C, arg_0);
    case 2:
        RpWorldAddAtomic(bp_8, arg_0);
        break;
    }
    return bp_8;
}

// match: ?sub_173450@@YAPAURpWorld@@PAURpLight@@@Z @ 0x00173450
// sp-match: ?sub_173450@@YAPAURpWorld@@PAURpLight@@@Z @ 0x0010FC40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise for the light arg_0 (by its position alone).
RpWorld *sub_173450(RpLight *arg_0)
{
    type_3D96F0 *var_14;
    RwInt32 lv_10;
    RpWorld *var_C;
    RpWorld *bp_8;
    RwFrame *bp_4;

    bp_4 = RpLightGetFrame(arg_0);
    var_14 = sub_FBDD0(arg_0);
    var_C = RpLightGetWorld(arg_0);
    lv_10 = -1;
    bp_8 = sub_172FF0(&lv_10, bp_4, var_14, var_C);
    switch (lv_10)
    {
    case 1:
        RpWorldRemoveLight(var_C, arg_0);
    case 2:
        RpWorldAddLight(bp_8, arg_0);
        break;
    }
    return bp_8;
}

// match: ?sub_1734E0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x001734E0
// sp-match: ?sub_1734E0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010ED60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the atomic arg_0 out of its world, untagged.
RpAtomic *sub_1734E0(RpAtomic *arg_0, void *arg_4)
{
    type_3D96F0 *var_8;
    RpWorld *l4;

    l4 = RpAtomicGetWorld(arg_0);
    if (l4)
        RpWorldRemoveAtomic(l4, arg_0);
    var_8 = sub_FB7A0(arg_0);
    sub_173080(0xFFFF, var_8);
    return arg_0;
}

// match: ?sub_173540@@YAPAURpLight@@PAU1@PAX@Z @ 0x00173540
// sp-match: ?sub_173540@@YAPAURpLight@@PAU1@PAX@Z @ 0x0010EDA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise the light arg_0.
RpLight *sub_173540(RpLight *arg_0, void *arg_4)
{
    type_3D96F0 *var_8;
    RpWorld *l4;

    l4 = RpLightGetWorld(arg_0);
    if (l4)
        RpWorldRemoveLight(l4, arg_0);
    var_8 = sub_FBDD0(arg_0);
    sub_173080(0xFFFF, var_8);
    return arg_0;
}

// match: ?sub_1735A0@@YAPAURpWorld@@PAURpClump@@@Z @ 0x001735A0
// sp-match: ?sub_1735A0@@YAPAURpWorld@@PAURpClump@@@Z @ 0x0010EDE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the clump arg_0 (and its atomics and lights) out of its world,
// untagged; returns the world.
RpWorld *sub_1735A0(RpClump *arg_0)
{
    type_3D96F0 *var_8;
    RpWorld *l4;

    l4 = RpClumpGetWorld(arg_0);
    if (l4)
    {
        RpClumpForAllAtomics(arg_0, sub_1734E0, 0);
        RpClumpForAllLights(arg_0, sub_173540, 0);
        RpWorldRemoveClump(l4, arg_0);
        var_8 = sub_FBA10(arg_0);
        sub_173080(0xFFFF, var_8);
    }
    return l4;
}

// match: ?sub_173620@@YAPAURpWorld@@PAURpAtomic@@@Z @ 0x00173620
// sp-match: ?sub_173620@@YAPAURpWorld@@PAURpAtomic@@@Z @ 0x0010EE30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpWorld *sub_173620(RpAtomic *arg_0)
{
    type_3D96F0 *var_8;
    RpWorld *l4;

    l4 = RpAtomicGetWorld(arg_0);
    if (l4)
    {
        RpWorldRemoveAtomic(l4, arg_0);
        var_8 = sub_FB7A0(arg_0);
        sub_173080(0xFFFF, var_8);
    }
    return l4;
}

// match: ?sub_173680@@YAPAURpClump@@PAU1@PAX@Z @ 0x00173680
// sp-match: ?sub_173680@@YAPAURpClump@@PAU1@PAX@Z @ 0x0010FCB0
RpClump *sub_173680(RpClump *arg_0, void *arg_4)
{
    sub_173180(arg_0);
    return arg_0;
}

// match: ?sub_1736A0@@YAPAURpLight@@PAU1@PAX@Z @ 0x001736A0
// sp-match: ?sub_1736A0@@YAPAURpLight@@PAU1@PAX@Z @ 0x0010FCD0
RpLight *sub_1736A0(RpLight *arg_0, void *arg_4)
{
    sub_173450(arg_0);
    return arg_0;
}

// match: ?sub_1736C0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x001736C0
// sp-match: ?sub_1736C0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0010FCF0
RpAtomic *sub_1736C0(RpAtomic *arg_0, void *arg_4)
{
    sub_173320(arg_0);
    return arg_0;
}

// match: ?sub_1736E0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x001736E0
// sp-match: ?sub_1736E0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x0010FD10
RpWorldSector *sub_1736E0(RpWorldSector *arg_0, void *arg_4)
{
    RpWorldSectorForAllAtomics(arg_0, sub_1736C0, 0);
    return arg_0;
}

// match: ?sub_173700@@YAXPAURpWorld@@@Z @ 0x00173700
// sp-match: ?sub_173700@@YAXPAURpWorld@@@Z @ 0x0010FD30
// Puts everything in the world arg_0 back in the world its position picks.
void sub_173700(RpWorld *arg_0)
{
    if (arg_0)
    {
        RpWorldForAllClumps(arg_0, sub_173680, 0);
        RpWorldForAllLights(arg_0, sub_1736A0, 0);
        RpWorldForAllWorldSectors(arg_0, sub_1736E0, 0);
    }
}

// match: ?sub_173750@@YAXXZ @ 0x00173750
// sp-match: ?sub_173750@@YAXXZ @ 0x0010FD70
// Likewise for every section's opaque and collision worlds, the default
// world and the global section's.
void sub_173750()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (dword_4E5D30[var_4].get_unk_00())
        {
            sub_173700(dword_4E5D30[var_4].get_unk_20());
            sub_173700(dword_4E5D30[var_4].get_unk_28());
        }
    }
    sub_173700(dword_4E5C78);
    sub_173700(unk_4E5CD8.get_unk_20());
    sub_173700(get_4E5D00());
}

// match: ?sub_173800@@YAHPAURpLight@@@Z @ 0x00173800
// sp-match: ?sub_173800@@YAHPAURpLight@@@Z @ 0x0010EE70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Adds the level's light arg_0 at the head of the list (an ambient one is
// the ambient light, its colour kept; a directional one light 0).
RwInt32 sub_173800(RpLight *arg_0)
{
    type_3D96FC *var_C;
    type_3D96FC *bp_8;
    RwInt32 bp_4;

    if (arg_0)
    {
        bp_4 = RpLightGetType(arg_0);
        if (bp_4 == rpLIGHTAMBIENT)
        {
            clump = arg_0;
            unk_4E5C60 = arg_0->color;
        }
        else if (bp_4 == rpLIGHTDIRECTIONAL)
        {
            dword_4E5C98[0] = arg_0;
        }
        bp_8 = (type_3D96FC *)sub_FBDD0(arg_0);
        bp_8->unk_1C = get_4E5C7C();
        bp_8->unk_20 = 0;
        if (dword_4E5C7C)
        {
            var_C = (type_3D96FC *)sub_FBDD0(dword_4E5C7C);
            var_C->unk_20 = arg_0;
        }
        dword_4E5C7C = arg_0;
        return 1;
    }
    return 0;
}

// match: ?sub_1738D0@@YAHPAURpLight@@@Z @ 0x001738D0
// sp-match: ?sub_1738D0@@YAHPAURpLight@@@Z @ 0x0010EF00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the light arg_0 out of the list.
RwInt32 sub_1738D0(RpLight *arg_0)
{
    type_3D96FC *var_C;
    type_3D96FC *bp_8;
    RpLight *bp_4;

    if (arg_0)
    {
        if (arg_0 == clump)
            clump = 0;
        if (arg_0 == dword_4E5C98[0])
            dword_4E5C98[0] = 0;
        bp_8 = 0;
        var_C = (type_3D96FC *)sub_FBDD0(arg_0);
        bp_4 = var_C->unk_20;
        if (bp_4)
        {
            bp_8 = (type_3D96FC *)sub_FBDD0(bp_4);
            bp_8->unk_1C = var_C->get_unk_1C();
        }
        bp_4 = var_C->unk_1C;
        if (bp_4)
        {
            bp_8 = (type_3D96FC *)sub_FBDD0(bp_4);
            bp_8->unk_20 = var_C->get_unk_20();
        }
        if (arg_0 == dword_4E5C7C)
            dword_4E5C7C = var_C->get_unk_1C();
        var_C->unk_1C = 0;
        var_C->unk_20 = 0;
        return 1;
    }
    return 0;
}

// match: ?sub_1739C0@@YAXXZ @ 0x001739C0
// sp-match: ?sub_1739C0@@YAXXZ @ 0x0010EF90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Copies the ambient light's colour and direction (its frame's at vector)
// into the default zone's first pair, directional light 0's into its
// second, and clears the third (each direction's w 1 while its light is
// there).
void sub_1739C0()
{
    RwV3d *var_8;
    RwRGBAReal *l4;

    l4 = 0;
    var_8 = 0;
    if (clump)
    {
        l4 = &clump->color;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_00 = l4->red;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_04 = l4->green;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_08 = l4->blue;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_0C = l4->alpha;
        var_8 = &RwFrameGetLTM(RpLightGetFrame(clump))->at;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_00 = var_8->x;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_04 = var_8->y;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_08 = var_8->z;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_0C = 1.0f;
    }
    else
    {
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_00 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_04 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_08 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_10.unk_0C = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_00 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_04 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_08 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[0].unk_00.unk_0C = 0;
    }
    if (dword_4E5C98[0])
    {
        l4 = &dword_4E5C98[0]->color;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_00 = l4->red;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_04 = l4->green;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_08 = l4->blue;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_0C = l4->alpha;
        var_8 = &RwFrameGetLTM(RpLightGetFrame(dword_4E5C98[0]))->at;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_00 = var_8->x;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_04 = var_8->y;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_08 = var_8->z;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_0C = 1.0f;
    }
    else
    {
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_00 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_04 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_08 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_10.unk_0C = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_00 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_04 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_08 = 0;
        ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[1].unk_00.unk_0C = 0;
    }
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_10.unk_00 = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_10.unk_04 = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_10.unk_08 = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_10.unk_0C = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_00.unk_00 = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_00.unk_04 = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_00.unk_08 = 0;
    ((type_4E5BE0 *)&dword_4E5BE0)->unk_20[2].unk_00.unk_0C = 0;
}

// match: ?sub_173BE0@@YAXPAURpWorld@@HGG@Z @ 0x00173BE0
// sp-match: ?sub_173BE0@@YAXPAURpWorld@@HGG@Z @ 0x0010F150
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Tags the world arg_0's extension with the section slot arg_C and level
// section arg_8, and whether the PVS shows it (the world passed as a
// sector). Its flags are worked out by the world kind arg_4 into a copy
// that is then dropped.
void sub_173BE0(RpWorld *arg_0, RwInt32 arg_4, RwUInt16 arg_8, RwUInt16 arg_C)
{
    type_3D9718 *var_8;
    type_3D96F0_04 l4;

    var_8 = sub_FC4E0(arg_0);
    var_8->unk_0A = arg_8;
    var_8->sub_FC490(arg_C);
    l4 = var_8->unk_04;
    switch (arg_4)
    {
    case 0:
        l4.unk_00_0 = 1;
        l4.unk_00_2 = 0;
        l4.unk_00_0 = 0;
        break;
    case 1:
        l4.unk_00_0 = 0;
        l4.unk_00_2 = 1;
        l4.unk_00_0 = 0;
        break;
    case 4:
        l4.unk_00_0 = 0;
        l4.unk_00_2 = 0;
        l4.unk_00_0 = 0;
        break;
    case 2:
        l4.unk_00_0 = 0;
        l4.unk_00_2 = 0;
        l4.unk_00_0 = 1;
    }
    if (RpPVSQuery(arg_0))
        var_8->unk_1C = 1;
    else
        var_8->unk_1C = 0;
}

// match: ?sub_173CE0@@YAHPAURpWorld@@HG@Z @ 0x00173CE0
// sp-match: ?sub_173CE0@@YAHPAURpWorld@@HG@Z @ 0x0010F1D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Gives the level section arg_8 (0x7FFF: the global section) the world
// arg_0 of kind arg_4 (0 opaque, 1 alpha, 2 collision, 4 UV-animated): its
// slot, else a free one taken; the world's flags kept, a collision world's
// zones found, its materials' animations started and it tagged. Returns
// the slot, or -1 when there is none.
RwInt32 sub_173CE0(RpWorld *arg_0, RwInt32 arg_4, RwUInt16 arg_8)
{
    type_4E5D30_10 *var_10;
    type_4E5D30 *var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = 0;
    if (arg_8 == 0x7FFF)
    {
        var_C = &unk_4E5CD8;
        bp_8 = 0x7FFF;
        bp_4 = 0x7FFF;
    }
    else
    {
        var_C = 0;
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            var_C = &dword_4E5D30[bp_4];
            if ((var_C->get_unk_04() || var_C->get_unk_00()) && var_C->get_unk_08() == arg_8)
            {
                bp_8 = bp_4;
                break;
            }
        }
        if (bp_4 == 4)
        {
            var_C = 0;
            for (bp_4 = 0; bp_4 < 4; bp_4++)
            {
                if (!dword_4E5D30[bp_4].get_unk_00() && !dword_4E5D30[bp_4].get_unk_04())
                {
                    bp_8 = bp_4;
                    var_C = &dword_4E5D30[bp_4];
                    var_C->unk_04 = 1;
                    break;
                }
            }
        }
    }
    if (var_C)
    {
        switch (arg_4)
        {
        case 0:
            var_C->unk_20 = arg_0;
            var_C->unk_34 = RpWorldGetFlags(arg_0);
            break;
        case 1:
            var_C->unk_24 = arg_0;
            var_C->unk_38 = RpWorldGetFlags(arg_0);
            break;
        case 4:
            var_C->unk_2C = arg_0;
            var_C->unk_40 = RpWorldGetFlags(arg_0);
            break;
        case 2:
            var_C->unk_28 = arg_0;
            var_C->unk_3C = RpWorldGetFlags(arg_0);
            if (!dword_4B8210)
                dword_4B2550.sub_8F570(arg_0);
        }
        var_C->unk_08 = arg_8;
        RpWorldForAllMaterials(arg_0, sub_173F30, arg_0);
        sub_173BE0(arg_0, arg_4, arg_8, (RwUInt16)bp_8);
        var_10 = &var_C->unk_10;
        if (var_10->unk_04 > var_C->get_unk_1C())
            var_C->unk_1C = var_10->get_unk_04();
        return bp_4;
    }
    return -1;
}

// match: ?sub_173F30@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x00173F30
// sp-match: ?sub_173F30@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x0010F190
// A material callback: starts the material arg_0's texture animation
// (arg_4 the world).
RpMaterial *sub_173F30(RpMaterial *arg_0, void *arg_4)
{
    unk_4E5CC8.sub_144590(arg_0, (RwInt32)arg_4);
    return arg_0;
}

// match: ?sub_173F50@@YAPAUtype_4E5D30@@G@Z @ 0x00173F50
// sp-match: ?sub_173F50@@YAPAUtype_4E5D30@@G@Z @ 0x0010F310
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The slot holding the level section arg_0, else a free one (taken), else 0.
type_4E5D30 *sub_173F50(RwUInt16 arg_0)
{
    type_4E5D30 *var_8;
    RwInt32 l4;

    var_8 = 0;
    for (l4 = 0; l4 < 4; l4++)
    {
        var_8 = &dword_4E5D30[l4];
        if ((var_8->get_unk_04() || var_8->get_unk_00()) && var_8->get_unk_08() == arg_0)
            break;
    }
    if (l4 == 4)
    {
        var_8 = 0;
        for (l4 = 0; l4 < 4; l4++)
        {
            if (!dword_4E5D30[l4].get_unk_00() && !dword_4E5D30[l4].get_unk_04())
            {
                var_8 = &dword_4E5D30[l4];
                var_8->unk_04 = 1;
                break;
            }
        }
    }
    return var_8;
}

// match: ?sub_174030@@YAXGH@Z @ 0x00174030
// sp-match: ?sub_174030@@YAXGH@Z @ 0x0010FF30
// Drops the section slot arg_0 (sub_174060 with arg_4).
void sub_174030(RwUInt16 arg_0, RwInt32 arg_4)
{
    type_4E5D30 *var_4;

    var_4 = &dword_4E5D30[arg_0];
    sub_174060(var_4, arg_4);
}

// match: ?sub_174060@@YAXPAUtype_4E5D30@@H@Z @ 0x00174060
// sp-match: ?sub_174060@@YAXPAUtype_4E5D30@@H@Z @ 0x0010FDD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Drops the section slot arg_0 (arg_4 unused), under the section lock: its
// collision world's zones and its worlds' material animations released,
// the worlds emptied and destroyed, its texture dictionary's textures and
// the dictionary destroyed, the slot cleared.
void sub_174060(type_4E5D30 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_18;
    RwTexDictionary *var_14;
    RpWorld *lv_10[4];

    RtlEnterCriticalSection(&dword_44BFB8);
#ifndef CODFH_SP
    // single player compiles the debug prints out (SP 0x10FDD0)
    sub_19A750("Removing world %d in bank %d", arg_0->get_unk_08(), arg_0->get_unk_0A());
    if (arg_0->get_unk_08() == 0xFFFF)
        sub_19A750("!!!\n");
#endif
    lv_10[0] = arg_0->get_unk_20();
    lv_10[1] = arg_0->get_unk_24();
    lv_10[2] = arg_0->get_unk_28();
    lv_10[3] = arg_0->get_unk_2C();
    var_14 = arg_0->unk_30;
    arg_0->unk_00 = 0;
    arg_0->unk_04 = 0;
    if (!dword_4B8210 && lv_10[2])
        dword_4B2550.sub_8F870(lv_10[2]);
    if (lv_10[0])
        RpWorldForAllMaterials(lv_10[0], sub_1742B0, lv_10[0]);
    if (lv_10[1])
        RpWorldForAllMaterials(lv_10[1], sub_1742B0, lv_10[1]);
    if (lv_10[2])
        RpWorldForAllMaterials(lv_10[2], sub_1742B0, lv_10[2]);
    if (lv_10[3])
        RpWorldForAllMaterials(lv_10[3], sub_1742B0, lv_10[3]);
    for (var_18 = 0; var_18 < 4; var_18++)
    {
        if (lv_10[var_18])
        {
            _rwFrameSyncDirty();
            sub_173700(lv_10[var_18]);
            _rwFrameSyncDirty();
            RpWorldDestroy(lv_10[var_18]);
        }
    }
    if (var_14)
    {
#ifdef CODFH_SP
        sub_16E6F0(var_14);
#else
        if (!sub_16E6F0(var_14))
            sub_19A750("Unable to destroy Texture Dictionary for section %d in bank %d", arg_0->get_unk_08(),
                       arg_0->get_unk_0A());
#endif
        RwTexDictionaryDestroy(arg_0->get_unk_30());
    }
    arg_0->unk_20 = 0;
    arg_0->unk_24 = 0;
    arg_0->unk_28 = 0;
    arg_0->unk_2C = 0;
    arg_0->unk_30 = 0;
    arg_0->unk_10.unk_04 = 0;
    arg_0->sub_174700(1);
    RtlLeaveCriticalSection(&dword_44BFB8);
}

// match: ?sub_1742B0@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x001742B0
// sp-match: ?sub_1742B0@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x0010F1B0
// A material callback: stops the material arg_0's texture animation
// (arg_4 the world).
RpMaterial *sub_1742B0(RpMaterial *arg_0, void *arg_4)
{
    unk_4E5CC8.sub_1444B0(arg_0, (RwInt32)arg_4);
    return arg_0;
}

// match: ?sub_1742D0@@YAHPAURwTexDictionary@@G@Z @ 0x001742D0
// sp-match: ?sub_1742D0@@YAHPAURwTexDictionary@@G@Z @ 0x0010F380
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Gives the level section arg_4's slot (else a free one) the texture
// dictionary arg_0; returns the slot, or -1.
RwInt32 sub_1742D0(RwTexDictionary *arg_0, RwUInt16 arg_4)
{
    type_4E5D30_10 *var_C;
    type_4E5D30 *bp_8;
    RwInt32 bp_4;

    bp_8 = 0;
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        bp_8 = &dword_4E5D30[bp_4];
        if ((bp_8->get_unk_04() || bp_8->get_unk_00()) && bp_8->get_unk_08() == arg_4)
            break;
    }
    if (bp_4 == 4)
    {
        bp_8 = 0;
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            if (!dword_4E5D30[bp_4].get_unk_00())
            {
                bp_8 = &dword_4E5D30[bp_4];
                break;
            }
        }
    }
    if (bp_8)
    {
        bp_8->unk_08 = arg_4;
        bp_8->unk_30 = arg_0;
        var_C = &bp_8->unk_10;
        if (var_C->unk_04 > bp_8->get_unk_1C())
            bp_8->unk_1C = var_C->get_unk_04();
        return bp_4;
    }
    return -1;
}

// match: ?sub_1743E0@@YAPAURwTexDictionary@@H@Z @ 0x001743E0
// sp-match: ?sub_1743E0@@YAPAURwTexDictionary@@H@Z @ 0x0010F400
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The texture dictionary of the level section arg_0's slot, or 0.
RwTexDictionary *sub_1743E0(RwInt32 arg_0)
{
    type_4E5D30 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 4; l4++)
    {
        var_8 = &dword_4E5D30[l4];
        if ((var_8->get_unk_00() || var_8->get_unk_04()) && var_8->get_unk_08() == arg_0)
            return var_8->get_unk_30();
    }
    return 0;
}

// match: ?sub_174460@@YAXPAURpWorld@@@Z @ 0x00174460
// sp-match: ?sub_174460@@YAXPAURpWorld@@@Z @ 0x0010F440
// Setters for the skybox worlds and the shared texture dictionary.
void sub_174460(RpWorld *arg_0)
{
    world = arg_0;
}

// match: ?sub_174470@@YAXPAURpWorld@@@Z @ 0x00174470
// sp-match: ?sub_174470@@YAXPAURpWorld@@@Z @ 0x0010F450
void sub_174470(RpWorld *arg_0)
{
    dword_4E5C84 = arg_0;
}

// match: ?sub_174480@@YAXPAURpWorld@@@Z @ 0x00174480
// sp-match: ?sub_174480@@YAXPAURpWorld@@@Z @ 0x0010F460
void sub_174480(RpWorld *arg_0)
{
    dword_4E5C88 = arg_0;
}

// match: ?sub_174490@@YAXPAURwTexDictionary@@@Z @ 0x00174490
// sp-match: ?sub_174490@@YAXPAURwTexDictionary@@@Z @ 0x0010F470
void sub_174490(RwTexDictionary *arg_0)
{
    dword_4E5C8C = arg_0;
}

// match: ?sub_1744A0@@YAXXZ @ 0x001744A0
// sp-match: ?sub_1744A0@@YAXXZ @ 0x0010F480
// Destroys the skybox worlds.
void sub_1744A0()
{
    if (world)
    {
        RpWorldDestroy(world);
        world = 0;
    }
    if (dword_4E5C84)
    {
        RpWorldDestroy(dword_4E5C84);
        dword_4E5C84 = 0;
    }
    if (dword_4E5C88)
    {
        RpWorldDestroy(dword_4E5C88);
        dword_4E5C88 = 0;
    }
}

// match: ?sub_174510@@YAXPAURwTexDictionary@@@Z @ 0x00174510
// sp-match: ?sub_174510@@YAXPAURwTexDictionary@@@Z @ 0x0010F4E0
// Sets shared.txd, and sub_174520 gets it.
void sub_174510(RwTexDictionary *arg_0)
{
    dword_4E5C90 = arg_0;
}

// match: ?sub_174520@@YAPAURwTexDictionary@@XZ @ 0x00174520
// sp-match: ?sub_174520@@YAPAURwTexDictionary@@XZ @ 0x0010F4F0
RwTexDictionary *sub_174520()
{
    return dword_4E5C90;
}

// match: ?sub_174530@@YAXXZ @ 0x00174530
// sp-match: ?sub_174530@@YAXXZ @ 0x0010F500
// Destroys shared.txd and its textures.
void sub_174530()
{
    if (dword_4E5C90)
    {
#ifdef CODFH_SP
        // single player compiles the debug print out, keeping the check's call (SP 0x10F500)
        sub_16E6F0(dword_4E5C90);
#else
        if (!sub_16E6F0(dword_4E5C90))
            sub_19A750("Unable to destroy shared.txd!");
#endif
        RwTexDictionaryDestroy(dword_4E5C90);
        dword_4E5C90 = 0;
    }
}

// match: ?sub_174580@@YAXPAUtype_3D3548@@H@Z @ 0x00174580
// sp-match: ?sub_174580@@YAXPAUtype_3D3548@@H@Z @ 0x0010F530
// Points the entity table's entry arg_4 at the entity arg_0 (sub_1745A0
// reads it back, sub_1745C0 clears it).
void sub_174580(type_3D3548 *arg_0, RwInt32 arg_4)
{
    if (arg_0)
        dword_4E5D1C[arg_4].sub_D48D0(arg_0);
}

// match: ?sub_1745A0@@YAPAUtype_3D3548@@H@Z @ 0x001745A0
// sp-match: ?sub_1745A0@@YAPAUtype_3D3548@@H@Z @ 0x0010F550
type_3D3548 *sub_1745A0(RwInt32 arg_0)
{
    return dword_4E5D1C[arg_0].sub_D4910();
}

// match: ?sub_1745C0@@YAXPAUtype_3D3548@@H@Z @ 0x001745C0
// sp-match: ?sub_1745C0@@YAXPAUtype_3D3548@@H@Z @ 0x0010F560
void sub_1745C0(type_3D3548 *arg_0, RwInt32 arg_4)
{
    if (arg_4 != -1 && dword_4E5D1C[arg_4].sub_D4910() == arg_0)
        dword_4E5D1C[arg_4].sub_D48D0(0);
}

// match: ?sub_1745F0@@YAHH@Z @ 0x001745F0
// sp-match: ?sub_1745F0@@YAHH@Z @ 0x0010F590
// The slot whose level section is arg_0 (live or not), or -1.
RwInt32 sub_1745F0(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (dword_4E5D30[var_4].get_unk_08() == arg_0)
            return var_4;
    }
    return -1;
}

// match: ?sub_174640@@YAHG@Z @ 0x00174640
// sp-match: ?sub_174640@@YAHG@Z @ 0x0010F5C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether the level section arg_0 is loaded in a live slot.
RwInt32 sub_174640(RwUInt16 arg_0)
{
    type_4E5D30 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 4; l4++)
    {
        var_8 = &dword_4E5D30[l4];
        if (var_8->get_unk_00() && var_8->get_unk_08() == arg_0)
            return 1;
    }
    return 0;
}

// match: ?sub_1746B0@@YAXXZ @ 0x001746B0
// sp-match: ?sub_1746B0@@YAXXZ @ 0x0010F5F0
// Destroys the UV animation dictionary.
void sub_1746B0()
{
    if (schema)
    {
        RtDictDestroy(schema);
        schema = 0;
    }
}

// match: ??0type_4E5D30@@QAE@XZ @ 0x001746E0
// sp-match: ??0type_4E5D30@@QAE@XZ @ 0x001101D0
type_4E5D30::type_4E5D30()
{
    unk_1C = 0;
    sub_174790();
}

// match: ?sub_174700@type_4E5D30@@QAEXH@Z @ 0x00174700
// sp-match: ?sub_174700@type_4E5D30@@QAEXH@Z @ 0x001100A0
void type_4E5D30::sub_174700(RwInt32 arg_0)
{
    unk_00 = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_30 = 0;
    unk_2C = 0;
    unk_08 = 0xFFFF;
    unk_0C = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_3C = 0;
    unk_04 = 0;
}

// match: ?sub_174790@type_4E5D30@@QAEXXZ @ 0x00174790
// sp-match: ?sub_174790@type_4E5D30@@QAEXXZ @ 0x001100D0
void type_4E5D30::sub_174790()
{
    sub_174700(0);
    unk_0A = 0xFFFF;
    unk_10.unk_00 = 0;
    unk_10.unk_04 = 0;
    unk_10.unk_08 = 0;
}

// match: ?sub_1747D0@type_4E5D30@@QAEXXZ @ 0x001747D0
// sp-match: ?sub_1747D0@type_4E5D30@@QAEXXZ @ 0x001100F0
// Warns of each world and the texture dictionary still held at shutdown.
void type_4E5D30::sub_1747D0()
{
    RwChar var_108[0x100];

    if (unk_20)
    {
        sprintf(var_108, "Opaque world was not deleted for section ID %d bank %d on shutdown\n", unk_08, unk_0A);
#ifndef CODFH_SP
        // single player compiles the debug prints out (SP 0x1100F0)
        sub_19A750(var_108);
#endif
    }
    if (unk_24)
    {
        sprintf(var_108, "Alpha world was not deleted for section ID %d bank %d on shutdown\n", unk_08, unk_0A);
#ifndef CODFH_SP
        sub_19A750(var_108);
#endif
    }
    if (unk_28)
    {
        sprintf(var_108, "Collision world was not deleted for section ID %d bank %d on shutdown\n", unk_08,
                unk_0A);
#ifndef CODFH_SP
        sub_19A750(var_108);
#endif
    }
    if (unk_30)
    {
        sprintf(var_108, "Texture dictionary was not deleted for section ID %d bank %d on shutdown\n", unk_08,
                unk_0A);
#ifndef CODFH_SP
        sub_19A750(var_108);
#endif
    }
    if (unk_2C)
    {
        sprintf(var_108, "Extra world was not deleted for section ID %d bank %d on shutdown\n", unk_08, unk_0A);
#ifndef CODFH_SP
        sub_19A750(var_108);
#endif
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_4E5D30@@QAE@XZ (folded into 0x1E41C0)
#ifndef CODFH_SP // single player keeps the call (unk_4E5CD8's exit function, SP 0x21ECF0): the empty body is not in this object
type_4E5D30::~type_4E5D30()
{
}
#endif


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004E5C60: dword_4E5BE0 + 0x80
RwRGBAReal &unk_4E5C60 = *(RwRGBAReal *)((RwUInt8 *)&dword_4E5BE0 + 0x80);
// 0x004E5C70: dword_4E5BE0 + 0x90
RwInt32 &dword_4E5C70 = *(RwInt32 *)((RwUInt8 *)&dword_4E5BE0 + 0x90);
// 0x004E5C74: dword_4E5BE0 + 0x94
RwInt32 &dword_4E5C74 = *(RwInt32 *)((RwUInt8 *)&dword_4E5BE0 + 0x94);
// 0x004E5C78: dword_4E5BE0 + 0x98
RpWorld *&dword_4E5C78 = *(RpWorld * *)((RwUInt8 *)&dword_4E5BE0 + 0x98);
// 0x004E5C7C: dword_4E5BE0 + 0x9C
RpLight *&dword_4E5C7C = *(RpLight * *)((RwUInt8 *)&dword_4E5BE0 + 0x9C);
// 0x004E5C80: dword_4E5BE0 + 0xA0
RpWorld *&world = *(RpWorld * *)((RwUInt8 *)&dword_4E5BE0 + 0xA0);
// 0x004E5C84: dword_4E5BE0 + 0xA4
RpWorld *&dword_4E5C84 = *(RpWorld * *)((RwUInt8 *)&dword_4E5BE0 + 0xA4);
// 0x004E5C88: dword_4E5BE0 + 0xA8
RpWorld *&dword_4E5C88 = *(RpWorld * *)((RwUInt8 *)&dword_4E5BE0 + 0xA8);
// 0x004E5C8C: dword_4E5BE0 + 0xAC
RwTexDictionary *&dword_4E5C8C = *(RwTexDictionary * *)((RwUInt8 *)&dword_4E5BE0 + 0xAC);
// 0x004E5C90: dword_4E5BE0 + 0xB0
RwTexDictionary *&dword_4E5C90 = *(RwTexDictionary * *)((RwUInt8 *)&dword_4E5BE0 + 0xB0);
// 0x004E5C94: dword_4E5BE0 + 0xB4
RpLight *&clump = *(RpLight * *)((RwUInt8 *)&dword_4E5BE0 + 0xB4);
// 0x004E5C98: dword_4E5BE0 + 0xB8
RpLight * (&dword_4E5C98)[4] = *(RpLight * (*)[4])((RwUInt8 *)&dword_4E5BE0 + 0xB8);
// 0x004E5CA8: dword_4E5BE0 + 0xC8
RpLight *&camera = *(RpLight * *)((RwUInt8 *)&dword_4E5BE0 + 0xC8);
// 0x004E5CAC: dword_4E5BE0 + 0xCC
RwInt32 &dword_4E5CAC = *(RwInt32 *)((RwUInt8 *)&dword_4E5BE0 + 0xCC);
#endif
