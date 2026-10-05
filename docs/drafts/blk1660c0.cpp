// match: ?sub_1660C0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x001660C0
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
    RwInt32 lv_44;
    RwInt32 lv_40;
    RwInt32 lv_3C;
    RwUInt32 lv_38;
    RwInt32 lv_34;
    RwInt32 lv_30;
    RwInt32 lv_2C;
    RwV3d lv_28;
    type_3D3548 *lv_1C;
    type_3D3548 *lv_18;
    RwInt32 lv_14;
    RwInt32 lv_10;
    type_161470 *lv_C;
    RpGeometry *lv_8;
    RwInt32 lv_4;

    lv_C = (type_161470 *)arg_10;
    if (sub_FB9C0(arg_8) & 0x10)
        return arg_8;
    lv_18 = sub_FB960(arg_8);
    if (lv_18)
    {
        lv_30 = lv_18->vf_1D4();
        if (lv_30 == 0x38)
            return arg_8;
    }
    lv_1C = sub_FB960(arg_8);
    lv_14 = 0;
    if (lv_C->unk_18)
        lv_14 = RwFrameGetParent(lv_1C->get_unk_340()) == lv_C->unk_18->get_unk_340();
    if (lv_1C && lv_1C != lv_C->unk_18 && !lv_14 && lv_1C->unk_2C_5 && lv_C->unk_18
        && (lv_1C->unk_2C & 7) != (lv_C->unk_18->unk_2C & 7))
        ((type_3DAFC8 *)lv_1C)->vf_250();
    if (arg_C > lv_C->unk_00)
        return arg_8;
    switch (arg_0->type)
    {
    case rpINTERSECTLINE:
        lv_28 = arg_0->t.line.end;
        break;
    case rpINTERSECTPOINT:
        lv_28 = arg_0->t.point;
        break;
    case rpINTERSECTSPHERE:
        lv_28 = arg_0->t.sphere.center;
        break;
    }
    if (lv_1C == lv_C->unk_18 || lv_14)
        return arg_8;
    if (!sub_12DD80(arg_8))
        return arg_8;
    lv_10 = 0;
    lv_2C = -1;
    lv_4 = 0;
    lv_8 = RpAtomicGetGeometry(arg_8);
    if (lv_1C && arg_0->type == rpINTERSECTLINE)
    {
        if (lv_1C->unk_28_2 || lv_1C->vf_00C() && lv_1C->vf_1E4())
        {
            lv_38 = lv_C->unk_14 & 0x3FFFFF0;
            if (!(lv_38 & lv_1C->unk_30))
                return arg_8;
        }
        else
        {
            return arg_8;
        }
        lv_34 = lv_1C->unk_28_0;
        lv_1C->unk_54 = lv_C->unk_48;
        if (lv_1C->unk_58 == 2)
        {
            lv_3C = lv_1C->vf_084(3, arg_0, &arg_C, &lv_C->unk_38);
            if (lv_3C && arg_C < lv_C->unk_00 && arg_C >= 0.0f)
            {
                lv_4 = 1;
                lv_10 = 1;
            }
        }
        else if (lv_1C->unk_58 == 0 && !lv_34)
        {
            lv_40 = lv_1C->vf_080(1, arg_0, &arg_C, 1.0f);
            if (lv_40 && arg_C < lv_C->unk_00 && arg_C >= 0.0f)
            {
                lv_4 = 1;
                lv_10 = 1;
            }
        }
        else if (lv_1C->unk_58 == 1 && !lv_34)
        {
            lv_44 = 0;
            if (lv_C->unk_18 && (lv_1C->unk_2C & 7) == (lv_C->unk_18->unk_2C & 7))
                lv_44 = 1;
            lv_2C = lv_1C->vf_07C(1, arg_0, &arg_C, lv_44);
            if (lv_2C != -1 && arg_C < lv_C->unk_00 && arg_C >= 0.0f)
            {
                lv_4 = 1;
                lv_10 = 1;
            }
        }
        else if (lv_8)
        {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_166950, arg_10);
        }
    }
    else if (lv_8)
    {
        if (lv_1C->unk_58 == 2 && lv_C->unk_08)
        {
            type_93DF0 lv_118;
            RwV3d lv_124;
            RwReal lv_48;
            RwInt32 lv_128;
            type_D1990 lv_60;
            RwV3d lv_54;
            RwInt32 lv_58;

            lv_118.unk_4C = lv_C->unk_50;
            lv_118.unk_74 = 0x180000; // not an address: material flags
            lv_124.x = 0;
            lv_124.y = 0;
            lv_124.z = 0;
            lv_118.unk_6C = &lv_124;
            lv_118.unk_24 = arg_0->t.sphere.radius * arg_0->t.sphere.radius;
            lv_118.unk_20 = 0;
            lv_118.unk_18 = 0;
            lv_118.unk_04 = 0;
            lv_118.unk_08 = 0;
            lv_118.unk_0C = 0;
            lv_118.unk_60 = 0;
            lv_118.unk_64 = 0;
            lv_118.unk_68 = 0;
            lv_118.unk_B0 = lv_C->unk_58;
            lv_118.unk_7C = 0;
            lv_118.unk_14 = (RwFrame *)lv_C->unk_08;
            lv_48 = 0;
            lv_118.unk_80 = &lv_48;
            lv_118.unk_90 = 0;
            lv_118.unk_78 = -1;
            lv_118.unk_38[0] = 1.0f / lv_C->unk_50;
            lv_118.unk_38[1] = 1.0f / lv_C->unk_54;
            lv_118.unk_38[2] = 1.0f / lv_C->unk_50;
            lv_118.unk_48 = lv_C->unk_54 * 0.5f;
            lv_128 = 0;
            lv_118.unk_50 = &lv_128;
            lv_118.unk_10 = arg_8;
            lv_118.unk_58 = 0;
            lv_118.unk_54 = 0;
            lv_118.unk_70 = sub_8F940();
            lv_118.unk_00 = 0;
            lv_118.unk_84 = 0;
            lv_118.unk_88 = 0;
            lv_118.unk_8C = 0;
            lv_118.unk_44 = 0;
            lv_60.unk_00 = &arg_0->t.sphere;
            lv_60.unk_04 = (type_93700 *)&lv_118;
            lv_58 = lv_1C->vf_084(4, (RpIntersection *)&lv_60, &arg_C, &lv_54);
            if (lv_58 && arg_C < lv_C->unk_00 && arg_C >= 0.0f)
            {
                lv_4 = 0;
                lv_10 = 0;
                lv_C->unk_04 = lv_118.unk_94;
                lv_C->unk_10 = arg_8;
                lv_C->unk_00 = arg_C;
                lv_C->unk_0C = lv_C->unk_10;
                lv_C->unk_44 = lv_2C;
                lv_C->unk_38 = lv_118.unk_98_v;
                lv_C->unk_2C = lv_118.unk_98_v;
                lv_C->unk_20 = lv_118.unk_A4_v;
            }
        }
        else
        {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_166950, arg_10);
            if (arg_C < lv_C->unk_00 && arg_C >= 0.0f)
            {
                lv_4 = 1;
                lv_10 = 1;
            }
        }
    }
    else if (arg_C < lv_C->unk_00 && arg_C >= 0.0f)
    {
        lv_4 = 1;
        if (arg_0->type == rpINTERSECTLINE)
            lv_10 = 1;
    }
    if (lv_4)
    {
        lv_C->unk_10 = arg_8;
        lv_C->unk_00 = arg_C;
        lv_C->unk_0C = lv_C->unk_10;
        lv_C->unk_20 = lv_28;
        lv_C->unk_44 = lv_2C;
    }
    if (lv_10)
    {
        RwV3dSub(&lv_C->unk_2C, &arg_0->t.line.end, &arg_0->t.line.start);
        RwV3dScale(&lv_C->unk_20, &lv_C->unk_2C, arg_C);
        RwV3dAdd(&lv_C->unk_20, &lv_C->unk_20, &arg_0->t.line.start);
        if (lv_1C->unk_58 == 2)
        {
            lv_C->unk_2C = lv_C->unk_38;
        }
        else
        {
            RwV3dNormalize(&lv_C->unk_2C, &lv_C->unk_2C);
            RwV3dNegate(&lv_C->unk_2C, &lv_C->unk_2C);
        }
    }
    return arg_8;
}
