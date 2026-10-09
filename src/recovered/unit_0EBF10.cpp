// The game's clump data plugin (include/game/clumpdata.h). The original file
// name is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "game/clumpdata.h"
#include "rw/badevice.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004B92D0
RwInt32 dword_4B92D0;
// End of its data definitions.


// The engine's memory functions' first two slots (include/rw/bamemory.h).

// match: ?sub_EBF10@@YAHXZ @ 0x000EBF10
// sp-match: ?sub_EBF10@@YAHXZ @ 0x000B50E0
RwInt32 sub_EBF10()
{
    dword_4B92D0 = RpClumpRegisterPlugin(0x14, 0x4210, sub_EC570, sub_EC620, sub_EC5C0);
    return 1;
}

// match: ?sub_EBF40@@YAPAURpClump@@PAURwStream@@PAH@Z @ 0x000EBF40
// sp-match: ?sub_EBF40@@YAPAURpClump@@PAURwStream@@PAH@Z @ 0x000B4C40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpClump *sub_EBF40(RwStream *arg_0, RwInt32 *arg_4)
{
    RwV3d *frm_24;
    RpHAnimHierarchy *t20;
    RwUInt32 l1C;
    type_EBF40_04 *m_18;
#ifndef CODFH_SP
    RwUInt32 ebp_14;
#endif
    type_EC6C0 *lv_10;
    RpClump *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    slot_C = 0;
    bp_4 = 0;
    RwStreamReadInt32(arg_0, &bp_8, 4);
    if (arg_4)
    {
        *arg_4 = 0;
    }
    if (RwStreamFindChunk(arg_0, 0x10, 0, 0))
    {
        bp_4++;
        slot_C = RpClumpStreamRead(arg_0);
        lv_10 = sub_EC6C0(slot_C);
        lv_10->unk_00 = true;
    }
    if (RwStreamFindChunk(arg_0, 0x4211, 0, 0))
    {
        bp_4++;
        m_18 = 0;
#ifdef CODFH_SP
        // shape: the count is local to this block; SP 0xB4CB8 gives its slot to lv_10 later.
        RwUInt32 ebp_14;
#endif
        RwStreamReadInt32(arg_0, (RwInt32 *)&ebp_14, 4);
        m_18 = (type_EBF40_04 *)RwMalloc(ebp_14 * 0x50 + 0x10, 0x34251); // not an address: an allocation tag
        lv_10 = sub_EC6C0(slot_C);
        lv_10->unk_04 = m_18;
        m_18->unk_00 = ebp_14;
        for (l1C = 0; l1C < ebp_14; l1C++)
        {
            RwStreamReadInt32(arg_0, &m_18->unk_10[l1C].unk_00, 4);
            RwStreamReadInt32(arg_0, &m_18->unk_10[l1C].unk_04, 4);
            if (RwStreamFindChunk(arg_0, 0xD, 0, 0))
            {
                RwMatrixStreamRead(arg_0, (RwMatrix *)&m_18->unk_10[l1C].unk_10);
            }
        }
    }
    if (RwStreamFindChunk(arg_0, 0x4212, 0, 0))
    {
        bp_4++;
        frm_24 = 0;
        t20 = sub_16D970(slot_C);
        lv_10 = sub_EC6C0(slot_C);
        if (t20 && t20->numNodes > 0)
        {
            frm_24 = (RwV3d *)RwMalloc(t20->numNodes * 0xC, 0x34251); // not an address: an allocation tag
            RwStreamReadInt32(arg_0, (RwInt32 *)frm_24, t20->numNodes * 0xC);
        }
        lv_10->unk_08 = frm_24;
    }
    if (RwStreamFindChunk(arg_0, 0x4213, 0, 0))
    {
        bp_4++;
        lv_10 = sub_EC6C0(slot_C);
        RwStreamReadInt32(arg_0, &lv_10->unk_0C, 4);
        if (lv_10->unk_0C)
        {
            lv_10->unk_10 = (RwInt32 *)RwMalloc(lv_10->unk_0C * 4, 0x34251); // not an address: an allocation tag
            RwStreamReadInt32(arg_0, lv_10->unk_10, lv_10->unk_0C * 4);
        }
    }
    if (arg_4 && bp_4 == 4)
    {
        *arg_4 = 1;
    }
    return slot_C;
}

// match: ?sub_EC1F0@@YAPAUtype_EC1F0@@PAURpClump@@H@Z @ 0x000EC1F0
// sp-match: ?sub_EC1F0@@YAPAUtype_EC1F0@@PAURpClump@@H@Z @ 0x000B4E30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_EC1F0 *sub_EC1F0(RpClump *arg_0, RwInt32 arg_4)
{
    type_EC6C0 *slot_C;
    type_EC1F0 *bp_8;
    RwUInt32 bp_4;

    bp_8 = 0;
    slot_C = sub_EC6C0(arg_0);
    if (slot_C->unk_04)
    {
        for (bp_4 = 0; bp_4 < slot_C->unk_04->unk_00; bp_4++)
        {
            if (slot_C->unk_04->unk_10[bp_4].unk_00 == arg_4)
            {
                bp_8 = &slot_C->unk_04->unk_10[bp_4];
                break;
            }
        }
    }
    return bp_8;
}

// match: ?sub_EC270@@YAPAURwV3d@@PAURpClump@@@Z @ 0x000EC270
// sp-match: ?sub_EC270@@YAPAURwV3d@@PAURpClump@@@Z @ 0x000B4E80
RwV3d *sub_EC270(RpClump *arg_0)
{
    type_EC6C0 *var_4;

    var_4 = sub_EC6C0(arg_0);
    return var_4->unk_08;
}

// match: ?sub_EC290@@YAHPAURpClump@@@Z @ 0x000EC290
// sp-match: ?sub_EC290@@YAHPAURpClump@@@Z @ 0x000B4EA0
RwInt32 sub_EC290(RpClump *arg_0)
{
    type_EC6C0 *var_4;

    var_4 = sub_EC6C0(arg_0);
    return var_4->unk_0C;
}

// match: ?sub_EC2B0@@YAPAHPAURpClump@@@Z @ 0x000EC2B0
RwInt32 *sub_EC2B0(RpClump *arg_0)
{
    type_EC6C0 *var_4;

    var_4 = sub_EC6C0(arg_0);
    return var_4->unk_10;
}

// match: ?sub_EC2D0@@YAHPAURpClump@@HHHH@Z @ 0x000EC2D0
// sp-match: ?sub_EC2D0@@YAHPAURpClump@@HHHH@Z @ 0x000B5110
RwInt32 sub_EC2D0(RpClump *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    RpHAnimHierarchy *var_4;

    var_4 = sub_16D970(arg_0);
    return sub_EC310(arg_0, var_4, (RwMatrix *)arg_4, arg_8, arg_C, arg_10);
}

// match: ?sub_EC310@@YAHPAURpClump@@PAURpHAnimHierarchy@@PAURwMatrixTag@@HHH@Z @ 0x000EC310
// sp-match: ?sub_EC310@@YAHPAURpClump@@PAURpHAnimHierarchy@@PAURwMatrixTag@@HHH@Z @ 0x000B4EC0
// *arg_8 becomes the clump arg_0's tagged matrix arg_C in world space: the
// tag's offset times its hierarchy node's matrix (the hierarchy's own with an
// atomic from RWS::SkinHelper::FindFirstSkin, else the node frame's LTM; local-space matrices
// times the clump frame's modelling matrix with arg_10, else its LTM) or the
// clump frame's LTM for node 0. Identity and 0 without the tag, else 1.
RwInt32 sub_EC310(RpClump *arg_0, RpHAnimHierarchy *arg_4, RwMatrix *arg_8, RwInt32 arg_C, RwInt32 arg_10,
                  RwInt32 arg_14)
{
    RwInt32 var_4;
    type_EC1F0 *var_8;
    RwMatrix *var_C;
    RpHAnimNodeInfo *var_10;
    RwMatrix var_50;

    var_4 = 1;
    var_8 = sub_EC1F0(arg_0, arg_C);
    if (var_8)
    {
        if (var_8->unk_04)
        {
            if (RWS::SkinHelper::FindFirstSkin(*arg_0))
            {
                var_C = &arg_4->pMatrixArray[var_8->unk_04];
            }
            else
            {
                var_10 = &arg_4->pNodeInfo[var_8->unk_04];
                var_C = RwFrameGetLTM(var_10->pFrame);
            }
            if (arg_4->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES)
            {
                if (arg_10)
                {
                    RwMatrixMultiply(&var_50, var_C, RwFrameGetMatrix(RpClumpGetFrame(arg_0)));
                }
                else
                {
                    RwMatrixMultiply(&var_50, var_C, RwFrameGetLTM(RpClumpGetFrame(arg_0)));
                }
            }
            else
            {
                var_50 = *var_C;
            }
        }
        else
        {
            var_50 = *RwFrameGetLTM(RpClumpGetFrame(arg_0));
        }
        RwMatrixSetIdentityMacro(arg_8);
        RwMatrixMultiply(arg_8, &var_8->unk_10, &var_50);
    }
    else
    {
        RwMatrixSetIdentityMacro(arg_8);
        var_4 = 0;
    }
    return var_4;
}

// match: ?sub_EC570@@YAPAXPAXHH@Z @ 0x000EC570
// sp-match: ?sub_EC570@@YAPAXPAXHH@Z @ 0x000B5020
void *sub_EC570(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_EC6C0 *var_4;

    var_4 = sub_EC6C0((RpClump *)arg_0);
    var_4->unk_04 = 0;
    var_4->unk_08 = 0;
    var_4->unk_00 = false;
    var_4->unk_0C = 0;
    var_4->unk_10 = 0;
    return arg_0;
}

// match: ?sub_EC5C0@@YAPAXPAXPBXHH@Z @ 0x000EC5C0
// sp-match: ?sub_EC5C0@@YAPAXPAXPBXHH@Z @ 0x000B5040
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_EC5C0(void *arg_0, const void *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_EC6C0 *bp_8;
    type_EC6C0 *bp_4;

    bp_8 = sub_EC6C0((RpClump *)arg_4);
    bp_4 = sub_EC6C0((RpClump *)arg_0);
    bp_4->unk_04 = bp_8->unk_04;
    bp_4->unk_08 = bp_8->unk_08;
    bp_4->unk_0C = bp_8->unk_0C;
    bp_4->unk_10 = bp_8->unk_10;
    return arg_0;
}

// match: ?sub_EC620@@YAPAXPAXHH@Z @ 0x000EC620
// sp-match: ?sub_EC620@@YAPAXPAXHH@Z @ 0x000B5080
void *sub_EC620(void *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_EC6C0 *var_4;

    var_4 = sub_EC6C0((RpClump *)arg_0);
    if (var_4->unk_00)
    {
        if (var_4->unk_04)
        {
            RwFree(var_4->unk_04);
            var_4->unk_04 = 0;
        }
        if (var_4->unk_08)
        {
            RwFree(var_4->unk_08);
            var_4->unk_08 = 0;
        }
        if (var_4->unk_10)
        {
            RwFree(var_4->unk_10);
            var_4->unk_10 = 0;
            var_4->unk_0C = 0;
        }
    }
    return arg_0;
}

// match: ?sub_EC6C0@@YAPAUtype_EC6C0@@PAURpClump@@@Z @ 0x000EC6C0
// sp-match: ?sub_EC6C0@@YAPAUtype_EC6C0@@PAURpClump@@@Z @ 0x000B4C30
type_EC6C0 *sub_EC6C0(RpClump *arg_0)
{
    return RWPLUGINOFFSET(type_EC6C0, arg_0, dword_4B92D0);
}
