// The step. The hurt flash's times run down. With its trigger: unless it
// is still (trigger unk_140), the listener is put behind the camera's view
// (3 units back along it, or along the head bone in camera mode) facing along
// it, its sounds follow it, at no health it dies (posture 10, the camera let
// go), the aim pass runs along the camera's (or its mounted weapon's) view
// over the section worlds, and the posture's step runs; while still, the
// pad moves and turns it. Then the weapons' times, a nearby vehicle's weapon
// (29 or 35) taken or put back, the inventory's count, its performance and
// AI, and the pad's weapon handling (fire, reload, the bipod, the second
// weapon, the stance, the soldier under the crosshair's health pack, the
// inventory), the sway (vf_258), aiming in or out and the inventory's next
// kind.
// match: ?vf_03C@type_10F710@@UAEXM@Z @ 0x00101550
void type_10F710::vf_03C(RwReal arg_0)
{
    RwInt32 v_8;
    type_712B0_10F710 *v_C;

    v_8 = unk_1A48[unk_1AE4]->unk_458;
    unk_1B18 = 0;
    if (unk_19EC > 0.0f)
        unk_19EC -= arg_0;
    if (unk_19F0 > 0.0f)
        unk_19F0 -= arg_0;
    v_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_C && v_C->vf_008() != 1)
    {
        v_C = 0;
    }
    if (!v_C)
        return;
    if (!unk_1A48[unk_1AE4]->get_unk_41C())
        unk_1A48[unk_1AE4]->sub_1170B0(1, 0);
    if (!v_C->unk_140)
    {
        type_3DD948 *v_14;
        RpHAnimHierarchy *v_18;
        RwMatrix *v_1C;
        RwMatrix *v_20;
        RwV3d *v_2C;
        RwV3d v_3C;

        v_14 = (type_3DD948 *)((type_10F710 *)sub_1745A0(dword_429EB0))->unk_2110.sub_D4910();
        v_18 = v_14->unk_284->unk_18;
        v_1C = RpHAnimHierarchyGetMatrixArray(v_18);
        v_20 = &v_1C[RpHAnimIDGetIndex(v_18, 0x97)];
        if (!v_14->get_unk_414())
            v_2C = &RwFrameGetLTM(get_unk_340())->at;
        else
            v_2C = &v_20->at;
        if (!v_14->get_unk_414())
            v_3C = *sub_CD550();
        else
            v_3C = v_20->pos;
        v_3C.x -= v_2C->x * 3.0f;
        v_3C.y -= v_2C->y * 3.0f;
        v_3C.z -= v_2C->z * 3.0f;
        do
        {
            dword_44E8AC->unk_28 = v_3C;
            dword_44E8AC->unk_70 |= 1;
        } while (0);
        do
        {
            dword_44E8AC->unk_4C = *v_2C;
            RwV3dCrossProductMacro(&dword_44E8AC->unk_58, &dword_44E8AC->unk_40, &dword_44E8AC->unk_4C);
            dword_44E8AC->unk_70 |= 4;
        } while (0);
        if (!v_14->get_unk_414())
            unk_1C0.sub_89540(sub_CD550());
        else
        {
            unk_1C0.sub_89540(&v_20->pos);
            if (unk_1A48[unk_1AE4]->unk_21C && ((((type_44C4E8 *)unk_1A48[unk_1AE4]->unk_21C)->unk_34 & 2) != 0) != 0)
            {
                unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                unk_1A48[unk_1AE4]->unk_21C = 0;
            }
        }
        if (!unk_19F8 && unk_19DC <= 0.0f && !((dword_4B86F8 >> 6) & 1))
        {
            type_3DD948 *v_44;

            if (unk_19D0 == 5)
                sub_10FBF0();
            unk_19D0 = 0xA;
            unk_1A48[unk_1AE4]->unk_224 = 0;
            v_44 = (type_3DD948 *)unk_2110.sub_D4910();
            if (v_44)
                v_44->unk_3B0 = 0;
            dword_4FDA9C = 1;
        }
        if (flt_4B8F2C != 0.0f)
        {
            RpIntersection v_60;
            type_3D3548 *v_64;
            RwMatrix v_B0;
            RwMatrix *v_B4;
            RwV3d v_C0;
            RwV3d v_CC;
            RwV3d v_D8;

            sub_19A750();
            dword_4C194C.unk_00 = flt_4B8F2C;
            v_60.type = rpINTERSECTLINE;
            v_64 = vf_200();
            if (v_64 && unk_4D0 == 2)
            {
                ((type_3DBC78 *)v_64)->vf_2F4(0, &v_B0);
                v_B4 = &v_B0;
            }
            else
                v_B4 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
            v_60.t.line.start = v_B4->pos;
            v_60.t.line.end.x = v_B4->at.x * v_C->unk_334 + v_60.t.line.start.x;
            v_60.t.line.end.y = v_B4->at.y * v_C->unk_334 + v_60.t.line.start.y;
            v_60.t.line.end.z = v_B4->at.z * v_C->unk_334 + v_60.t.line.start.z;
            unk_1A30 = 1.0f;
            unk_454 = 0;
            dword_4C194C.unk_04 = -1.0f;
            dword_4C194C.unk_08.sub_D48D0(0);
            dword_4C194C.unk_0C = 0;
            if (sub_FCAE0(&v_60.t.line.start, &v_60.t.line.end, &v_C0, 0, 0x10000, 1, 1))
            {
                RwV3dSubMacro(&v_CC, &v_C0, &v_60.t.line.start);
                RwV3dNormalize(&v_D8, &v_CC);
                v_60.t.line.end.x = v_D8.x * 350.0f + v_C0.x;
                v_60.t.line.end.y = v_D8.y * 350.0f + v_C0.y;
                v_60.t.line.end.z = v_D8.z * 350.0f + v_C0.z;
            }
            if (v_60.t.line.start.x != v_60.t.line.end.x || v_60.t.line.start.y != v_60.t.line.end.y ||
                v_60.t.line.start.z != v_60.t.line.end.z)
            {
                for (RwInt32 v_DC = 0; v_DC < 4; v_DC++)
                {
                    type_4E5D30 *v_E0 = &dword_4E5D30[v_DC];

                    if (v_E0->get_unk_00() != 0 && v_E0->get_unk_28() != 0)
                        RpWorldForAllAtomicIntersections(v_E0->get_unk_28(), &v_60, sub_FCD90, &dword_4C194C);
                }
            }
            sub_100880(this, &dword_4C194C);
            sub_100AD0(this, &dword_4C194C);
        }
        switch (unk_19D0)
        {
        case 0:
            if (!((dword_4B86F8 >> 4) & 1))
                sub_10A9D0(arg_0);
            break;
        case 1:
            sub_10AD70(arg_0);
            break;
        case 2:
            sub_10AEB0(arg_0);
            break;
        case 3:
            sub_10AFD0(arg_0);
            break;
        case 5:
            sub_10B120(arg_0);
            break;
        case 6:
            sub_10B2E0(arg_0);
            break;
        case 7:
            sub_10B410(arg_0);
            break;
        case 9:
            sub_10B6F0(arg_0);
            break;
        case 10:
            sub_10B790(arg_0);
            break;
        case 11:
            sub_10B930(arg_0);
            break;
        case 12:
            sub_10B560(arg_0);
            break;
        case 13:
            sub_114AA0(arg_0);
            break;
        case 14:
            sub_10BB30(arg_0);
            break;
        case 16:
            vf_250(arg_0);
            break;
        case 17:
            vf_254(arg_0);
            break;
        }
    }
    else
    {
        RwReal v_F4;

        unk_28 &= ~0x2C;
        unk_28 |= 0x10;
        unk_10C.x = -0.5f;
        unk_10C.y = -0.5f;
        unk_10C.z = -0.5f;
        unk_134.x = -0.5f;
        unk_134.y = -0.5f;
        unk_134.z = -0.5f;
        unk_28 &= ~2;
        unk_DC *= 0.5f;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 0);
        if (v_F4 != 0.0f)
        {
            if (v_F4 > 0.0f)
                unk_C0.z = v_F4 * v_C->unk_164[unk_1A04];
            else
                unk_C0.z = v_F4 * v_C->unk_170[unk_1A04];
        }
        dword_4294C0 = 1;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 3);
        if (v_F4 != 0.0f)
            unk_C0.y = v_F4 * v_C->unk_164[unk_1A04];
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 0xC);
        if (v_F4 != 0.0f)
            unk_C0.y = v_C->unk_164[unk_1A04] * -v_F4;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 2);
        if (v_F4 != 0.0f)
            unk_C0.x = (RwDouble)v_C->unk_1E4[unk_1A04] * v_F4;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 5);
        if (v_F4 != 0.0f)
        {
            RwReal v_F8;
            RwReal v_FC;
            RwReal v_100;

            v_F8 = v_F4 * v_C->unk_154;
            unk_530 += v_F8;
            v_FC = 90.0f;
            v_100 = -90.0f;
            unk_530 = sub_22C20(unk_530, v_100, v_FC);
        }
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 1);
        if (v_F4 != 0.0f)
        {
            unk_E8 = (RwDouble)v_C->unk_1B4 * v_F4 * flt_3CE7F4;
            sub_19B650(unk_E4);
        }
    }
    unk_1A48[unk_1AE4]->unk_220 += arg_0;
    {
        type_10F710_1A48 *v_104 = unk_1A48[unk_1AE4]->unk_460;

        if (v_104)
            v_104->unk_220 += arg_0;
    }
    if (unk_2188 && unk_2148 == 0.0f && unk_19F8 <= 0 && unk_19DC > 0.0f && !((dword_4B86F8 >> 6) & 1))
    {
        RwInt32 v_108 = 8;
        RwInt32 v_10C = unk_19D0;

        if (v_10C == 5)
        {
            sub_10F7E0(1, 0);
            sub_10F7E0(2, 1);
            v_108 = 9;
        }
        else
        {
            RwInt32 v_110 = 0x1D;
            RwInt32 v_114 = 0;
            type_3D3548 *v_118 = dword_4B8610;
            type_4C19C0 *v_128;
            RwInt32 v_12C;

            while (v_118 && !v_114)
            {
                VehicleTrigger *v_120 = (VehicleTrigger *)v_118->get_unk_34C();

                if (v_120->unk_EC == 3 || v_120->unk_EC == 2)
                {
                    v_114 = 1;
                    switch (v_120->unk_114)
                    {
                    case 1:
                        v_110 = 0x23;
                        break;
                    case 0:
                        v_110 = 0x1D;
                        break;
                    }
                }
                if (!v_114)
                    v_118 = v_118->unk_10;
            }
            v_128 = sub_119B70(v_110);
            v_12C = v_128->unk_24;
            if (!sub_10E8C0(v_110) && !sub_16F8A0(v_12C))
                sub_10DA70(v_110);
            if (sub_10E8C0(v_110))
            {
                if (!unk_1A48[v_110]->get_unk_41E())
                {
                    unk_1A48[v_110]->vf_008(this, unk_1A3C.get_unk_08(), v_110);
                    set_bank_state(unk_2134, 1, 1);
                }
                sub_10F7E0(1, 1);
                sub_10F7E0(2, 0);
                if (sub_10F710() == 1)
                    set_bank_state(sub_16F860(v_12C), v_110, 1);
            }
        }
        if (dword_4B9190)
            dword_4B9190->sub_E0410(v_108);
        if (sub_10F710() == 1 || sub_10F710() == 2)
        {
            ((VehicleEnterExitTrigger *)unk_2188)->sub_BF310(this);
            sub_10F8D0(0);
            unk_2240 = 0;
        }
    }
    else
    {
        sub_10F7E0(1, 0);
        sub_10F7E0(2, 0);
        if (get_bank_state(unk_2134) && dword_4E5518[unk_2134] >> 16 == 1)
            clear_bank_state(unk_2134, 1);
    }
    sub_1048E0();
    unk_21B4.sub_115520(arg_0);
    if (unk_284 && unk_88_9)
    {
        type_6D380 *v_148 = vf_090();

        if (v_148)
            v_148->sub_6D5A0(arg_0);
        vf_21C(arg_0);
    }
    sub_16D7F0(0x18);
    unk_550.sub_172F0(arg_0);
    sub_16D850(0x18);
    if (!((dword_4B86F8 >> 4) & 1) && 0.0f == unk_4B9308.sub_EE8F0(0, 0xF))
        unk_2240 = 1;
    unk_1B20 = 0;
    if (0.0f == unk_4B9308.sub_EE8F0(unk_3D8, 3) || (RwUInt32)unk_1A48[unk_1AE4]->unk_414 <= 0)
    {
        unk_1B24 = 0;
        unk_20DC = dword_429744;
    }
    type_4C19C0 *v_14C = unk_1A48[unk_1AE4]->unk_448;

    if ((dword_4B86F8 >> 4) & 1)
    {
        RwInt32 v_150 = unk_4B9308.sub_EE870(unk_3D8, 3);

        if ((v_150 || (RwUInt32)unk_1A48[unk_1AE4]->unk_414 <= 0) && unk_1A48[unk_1AE4]->unk_46)
        {
            unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
            unk_1A48[unk_1AE4]->unk_21C = 0;
            unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
            unk_1A48[unk_1AE4]->unk_46 = 0;
        }
    }
    else
    {
        // PART_B
    }
    vf_258(arg_0);
    unk_538 = 1.0f;
    if (!((dword_4B86F8 >> 4) & 1))
    {
        // PART_C
    }
    sub_10C7B0(arg_0);
    sub_D41A0();
    unk_2174.sub_D48D0(0);
}
