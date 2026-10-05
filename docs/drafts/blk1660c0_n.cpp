// match: ?sub_1660C0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x001660C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The worlds' atomics' callback of a projectile's query arg_10 (a
// type_161470): skipping atomics collision ignores, kind-0x38 entities, the
// owner and what the owner rides, it suppresses a soldier of another side
// the line passes, then tests the entity by its mode (unk_58: a line for 2,
// vf_080 for 0, vf_07C for 1, else the atomic's triangles, sub_166950) or,
// for a sphere, builds a collision search (sub_95030's context) for mode 2
// with the query's radii. The nearest hit (under unk_00) is kept with its
// point and normal.
RpAtomic *sub_1660C0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    RwInt32 loc44;
    RwInt32 fp_40;
    RwInt32 l3C;
    RwUInt32 local_38;
    RwInt32 local_34;
    RwInt32 local_30;
    RwInt32 stk_2C;
    RwV3d var28;
    type_3D3548 *l1C;
    type_3D3548 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    type_161470 *var_C;
    RpGeometry *bp_8;
    RwInt32 bp_4;

    var_C = (type_161470 *)arg_10;
    if (sub_FB9C0(arg_8) & 0x10)
        return arg_8;
    m_18 = sub_FB960(arg_8);
    if (m_18)
    {
        local_30 = m_18->vf_1D4();
        if (local_30 == 0x38)
            return arg_8;
    }
    l1C = sub_FB960(arg_8);
    ebp_14 = 0;
    if (var_C->unk_18)
        ebp_14 = RwFrameGetParent(l1C->get_unk_340()) == var_C->unk_18->get_unk_340();
    if (l1C && l1C != var_C->unk_18 && !ebp_14 && l1C->unk_2C_5 && var_C->unk_18
        && (l1C->unk_2C & 7) != (var_C->unk_18->unk_2C & 7))
        ((type_3DAFC8 *)l1C)->vf_250();
    if (arg_C > var_C->unk_00)
        return arg_8;
    switch (arg_0->type)
    {
    case rpINTERSECTLINE:
        var28 = arg_0->t.line.end;
        break;
    case rpINTERSECTPOINT:
        var28 = arg_0->t.point;
        break;
    case rpINTERSECTSPHERE:
        var28 = arg_0->t.sphere.center;
        break;
    }
    if (l1C == var_C->unk_18 || ebp_14)
        return arg_8;
    if (!sub_12DD80(arg_8))
        return arg_8;
    lv_10 = 0;
    stk_2C = -1;
    bp_4 = 0;
    bp_8 = RpAtomicGetGeometry(arg_8);
    if (l1C && arg_0->type == rpINTERSECTLINE)
    {
        if (l1C->unk_28_2 || l1C->vf_00C() && l1C->vf_1E4())
        {
            local_38 = var_C->unk_14 & 0x3FFFFF0;
            if (!(local_38 & l1C->unk_30))
                return arg_8;
        }
        else
        {
            return arg_8;
        }
        local_34 = l1C->unk_28_0;
        l1C->unk_54 = var_C->unk_48;
        if (l1C->unk_58 == 2)
        {
            l3C = l1C->vf_084(3, arg_0, &arg_C, &var_C->unk_38);
            if (l3C && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
        else if (l1C->unk_58 == 0 && !local_34)
        {
            fp_40 = l1C->vf_080(1, arg_0, &arg_C, 1.0f);
            if (fp_40 && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
        else if (l1C->unk_58 == 1 && !local_34)
        {
            loc44 = 0;
            if (var_C->unk_18 && (l1C->unk_2C & 7) == (var_C->unk_18->unk_2C & 7))
                loc44 = 1;
            stk_2C = l1C->vf_07C(1, arg_0, &arg_C, loc44);
            if (stk_2C != -1 && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
        else if (bp_8)
        {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_166950, arg_10);
        }
    }
    else if (bp_8)
    {
        if (l1C->unk_58 == 2 && var_C->unk_08)
        {
            RwInt32 var_128;
            RwV3d frm_124;
            type_93DF0 fp_118;
            type_D1990 stk_60;
            RwInt32 stk_58;
            RwV3d lv_54;
            RwReal q48;

            fp_118.unk_4C = var_C->unk_50;
            fp_118.unk_74 = 0x180000; // not an address: material flags
            frm_124.x = 0;
            frm_124.y = 0;
            frm_124.z = 0;
            fp_118.unk_6C = &frm_124;
            fp_118.unk_24 = arg_0->t.sphere.radius * arg_0->t.sphere.radius;
            fp_118.unk_20 = 0;
            fp_118.unk_18 = 0;
            fp_118.unk_04 = 0;
            fp_118.unk_08 = 0;
            fp_118.unk_0C = 0;
            fp_118.unk_60 = 0;
            fp_118.unk_64 = 0;
            fp_118.unk_68 = 0;
            fp_118.unk_B0 = var_C->unk_58;
            fp_118.unk_7C = 0;
            fp_118.unk_14 = (RwFrame *)var_C->unk_08;
            q48 = 0;
            fp_118.unk_80 = &q48;
            fp_118.unk_90 = 0;
            fp_118.unk_78 = -1;
            fp_118.unk_38[0] = 1.0f / var_C->unk_50;
            fp_118.unk_38[1] = 1.0f / var_C->unk_54;
            fp_118.unk_38[2] = 1.0f / var_C->unk_50;
            fp_118.unk_48 = var_C->unk_54 * 0.5f;
            var_128 = 0;
            fp_118.unk_50 = &var_128;
            fp_118.unk_10 = arg_8;
            fp_118.unk_58 = 0;
            fp_118.unk_54 = 0;
            fp_118.unk_70 = sub_8F940();
            fp_118.unk_00 = 0;
            fp_118.unk_84 = 0;
            fp_118.unk_88 = 0;
            fp_118.unk_8C = 0;
            fp_118.unk_44 = 0;
            stk_60.unk_00 = &arg_0->t.sphere;
            stk_60.unk_04 = (type_93700 *)&fp_118;
            stk_58 = l1C->vf_084(4, (RpIntersection *)&stk_60, &arg_C, &lv_54);
            if (stk_58 && arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 0;
                lv_10 = 0;
                var_C->unk_04 = fp_118.unk_94;
                var_C->unk_10 = arg_8;
                var_C->unk_00 = arg_C;
                var_C->unk_0C = var_C->unk_10;
                var_C->unk_44 = stk_2C;
                var_C->unk_38 = fp_118.unk_98_v;
                var_C->unk_2C = fp_118.unk_98_v;
                var_C->unk_20 = fp_118.unk_A4_v;
            }
        }
        else
        {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_166950, arg_10);
            if (arg_C < var_C->unk_00 && arg_C >= 0.0f)
            {
                bp_4 = 1;
                lv_10 = 1;
            }
        }
    }
    else if (arg_C < var_C->unk_00 && arg_C >= 0.0f)
    {
        bp_4 = 1;
        if (arg_0->type == rpINTERSECTLINE)
            lv_10 = 1;
    }
    if (bp_4)
    {
        var_C->unk_10 = arg_8;
        var_C->unk_00 = arg_C;
        var_C->unk_0C = var_C->unk_10;
        var_C->unk_20 = var28;
        var_C->unk_44 = stk_2C;
    }
    if (lv_10)
    {
        RwV3dSub(&var_C->unk_2C, &arg_0->t.line.end, &arg_0->t.line.start);
        RwV3dScale(&var_C->unk_20, &var_C->unk_2C, arg_C);
        RwV3dAdd(&var_C->unk_20, &var_C->unk_20, &arg_0->t.line.start);
        if (l1C->unk_58 == 2)
        {
            var_C->unk_2C = var_C->unk_38;
        }
        else
        {
            RwV3dNormalize(&var_C->unk_2C, &var_C->unk_2C);
            RwV3dNegate(&var_C->unk_2C, &var_C->unk_2C);
        }
    }
    return arg_8;
}
