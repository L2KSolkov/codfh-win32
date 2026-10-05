// The aim's zoom (after the step's aiming). Zooming in (sub_1014E0 allows it
// and the weapon's zoom time is under its settings' bounds for the stance):
// the time runs on (back while leaving), the field of view and the scope's
// scale follow the settings' zoom by the fraction reached, and the weapon's
// sway offsets by it. Otherwise the zoom is left at once or, allowed, set to
// the settings' full zoom. Zoomed beyond 16, the near clip plane follows the
// nearest surface or entity in a sphere of 400 around the player (at least
// 10; 400 with none).
// match: ?sub_104FF0@type_10F710@@QAEXM@Z @ 0x00104FF0
void type_10F710::sub_104FF0(RwReal arg_0)
{
    type_4C19C0 *v_8;
    type_712B0_10F710 *v_C;
    RwReal v_10;

    v_8 = unk_1A48[unk_1AE4]->unk_448;
    v_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_C && v_C->vf_008() != 1)
    {
        v_C = 0;
    }
    v_10 = v_C->get_unk_F0();
    if (sub_1014E0() && (unk_1A48[unk_1AE4]->unk_298 < v_8->unk_3B0_a[unk_1A04] ||
                         unk_1A48[unk_1AE4]->unk_298 < v_8->unk_410_a[unk_1A04]))
    {
        RwReal v_14;
        RwReal v_18;

        unk_1B0C = 1;
        if (unk_1B08)
            unk_1A48[unk_1AE4]->unk_298 -= arg_0;
        else
            unk_1A48[unk_1AE4]->unk_298 += arg_0;
        if (unk_1A48[unk_1AE4]->unk_298 < 0.0f)
        {
            unk_1A48[unk_1AE4]->unk_298 = 0.0f;
            unk_1B04 = 0;
            unk_1B08 = 0;
            unk_1B0C = 0;
            unk_1B10 = 0;
        }
        v_14 = unk_1A48[unk_1AE4]->unk_298;
        if (v_8->unk_3B0_a[unk_1A04] != 0.0f)
            v_18 = v_14 / v_8->unk_3B0_a[unk_1A04];
        else
            v_18 = 1.0f;
        if (v_18 > 1.0f)
            v_18 = 1.0f;
        unk_534 = (v_10 / v_8->unk_3A4_r[unk_1A04] - v_10) * v_18 + v_10;
        if (v_8->unk_410_a[unk_1A04] != 0.0f)
            v_18 = v_14 / v_8->unk_410_a[unk_1A04];
        else
            v_18 = 1.0f;
        if (v_18 > 1.0f)
            v_18 = 1.0f;
        unk_1A48[unk_1AE4]->unk_218 = v_18;
        unk_1A48[unk_1AE4]->unk_28C.x = v_18 * v_8->unk_3C8_a[unk_1A04].x;
        unk_1A48[unk_1AE4]->unk_28C.y = v_18 * v_8->unk_3C8_a[unk_1A04].y;
        unk_1A48[unk_1AE4]->unk_28C.z = v_18 * v_8->unk_3C8_a[unk_1A04].z;
        unk_1A48[unk_1AE4]->unk_280.x = v_18 * unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].x;
        unk_1A48[unk_1AE4]->unk_280.y = v_18 * unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].y;
        unk_1A48[unk_1AE4]->unk_280.z = v_18 * unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].z;
        unk_538 = (v_8->unk_3A4_r[unk_1A04] - 1.0f) * v_18 + 1.0f;
    }
    else
    {
        unk_1B0C = 0;
        if (unk_1B08)
        {
            unk_1B08 = 0;
            unk_1A48[unk_1AE4]->unk_28C.x = 0.0f;
            unk_1A48[unk_1AE4]->unk_28C.y = 0.0f;
            unk_1A48[unk_1AE4]->unk_28C.z = 0.0f;
            unk_1A48[unk_1AE4]->unk_298 = 0.0f;
        }
        else if (sub_1014E0())
        {
            if (v_8->unk_3B0_a[unk_1A04] > v_8->unk_410_a[unk_1A04])
                unk_1A48[unk_1AE4]->unk_298 = v_8->unk_3B0_a[unk_1A04];
            else
                unk_1A48[unk_1AE4]->unk_298 = v_8->unk_410_a[unk_1A04];
            if (unk_1A0C)
                unk_538 = sub_112F80(v_8->unk_3A4_r[unk_1A08], v_8->unk_3A4_r[unk_1A04], unk_1A10);
            else
                unk_538 = v_8->unk_3A4_r[unk_1A04];
            unk_534 = v_10 / unk_538;
            unk_1B04 = 1;
            unk_1A48[unk_1AE4]->unk_218 = 1.0f;
            unk_1A48[unk_1AE4]->unk_28C = v_8->unk_3C8_a[unk_1A04];
            unk_1A48[unk_1AE4]->unk_280 = unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04];
        }
    }
    if (v_8->unk_3A4_r[unk_1A04] > 16.0f)
    {
        RwV3d v_24;
        RwInt32 v_28;
        RwReal v_104;
        RwInt32 v_10C;

        v_24.x = 400.0f;
        v_24.y = 100.0f;
        v_24.z = 400.0f;
        v_28 = 0;
        type_93DF0 v_E0;
        RpIntersection v_FC;

        v_FC.type = rpINTERSECTSPHERE;
        v_FC.t.sphere.center = RwFrameGetLTM(get_unk_340())->pos;
        v_FC.t.sphere.radius = v_24.x;
        v_104 = v_FC.t.sphere.radius * v_FC.t.sphere.radius;
        v_E0.unk_6C = 0;
        v_E0.unk_24 = v_104;
        v_E0.unk_20 = 0;
        v_E0.unk_18 = 0;
        v_E0.unk_04 = this;
        v_E0.unk_14 = get_unk_340();
        v_E0.unk_0C = 0;
        v_E0.unk_08 = 0;
        v_E0.unk_60 = 0;
        v_E0.unk_64 = 0;
        v_E0.unk_7C = 0;
        v_E0.unk_28 = 0.0f;
        v_E0.unk_48 = unk_50_r;
        v_E0.unk_50 = &v_28;
        v_E0.unk_58 = 0;
        v_E0.unk_54 = 0;
        v_E0.unk_70 = sub_8F940();
        v_10C = 0;
        for (v_10C = 0; v_10C < 4; v_10C++)
        {
            type_4E5D30 *v_110 = &dword_4E5D30[v_10C];

            if (v_110->get_unk_00())
            {
                if (v_110->get_unk_20())
                    RpWorldForAllAtomicIntersections(v_110->get_unk_20(), &v_FC, sub_104D00, &v_E0);
                if (v_110->get_unk_28())
                    RpCollisionWorldForAllIntersections(v_110->get_unk_28(), &v_FC, sub_104B30, &v_E0);
            }
        }
        if (v_E0.unk_28 != 0.0f)
        {
            RwReal v_184;

            do
            {
                __m128 v_140 = _mm_set_ss(v_E0.unk_28);
                __m128 v_170 = _mm_sqrt_ss(v_140);
                _mm_store_ss(&v_184, v_170);
            } while (0);
            if (v_184 < 10.0f)
                v_184 = 10.0f;
            *(RwReal *)&dword_4CF540 = v_184;
        }
        else
            *(RwReal *)&dword_4CF540 = 400.0f;
    }
}
