// Its set-up ("Player::Init()"): its trigger (unk_344's, when a player
// trigger) gives its collision boxes, field of view, eye height and yaw
// scale; the inventory is emptied, then refilled with the health from the
// checkpoint when the trigger says so ("using player attribs from previous
// level or from memCard"); the states, the aim assist and the view are
// cleared; its frame, animation, collision atomic and weapons' names (by
// language) are made; the pad's buttons 29 and 30 are read; the HUD shows
// the health packs' count. 1.
// match: ?sub_FDC10@type_10F710@@QAEHPAUtype_712B0@@@Z @ 0x000FDC10
RwInt32 type_10F710::sub_FDC10(type_712B0 *arg_0)
{
    RwV3d var_C;
    type_712B0_10F710 *var_10;
    RwInt32 var_14 = 0;
    type_7C8D0 *var_18;
    RwChar var_3C[32];
    RpAtomic *var_40;
    RwInt32 var_44;
    RwFrame *var_48;
    type_D90B0 *var_4C;
    RwInt32 var_50;
    RwInt32 var_54;
    RwInt32 var_58;
    RwInt32 var_5C;

    unk_2254 = 1;
    unk_2258 = 0;
    sub_CCCD0(arg_0);
    var_10 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_10 && var_10->vf_008() != 1)
    {
        var_10 = 0;
    }
    unk_28 = 0x2017C;
    unk_2C = 0x11;
    unk_30 = 0x32FFFE7;
    unk_530 = 0.0f;
    unk_19D4 = 0;
    unk_10C = var_10->unk_190;
    unk_134 = var_10->unk_1A8;
    unk_130 = 0;
    unk_1AE8 = 0;
    unk_2134 = 2;
    unk_2138 = 1;
    unk_3D8 = 0;
    unk_3DC = dword_4F28F0->get_unk_1C();
    sub_FEFE0();
    unk_3E0 = 90.0f;
    unk_3D4 = -1;
    unk_48 = 100.5f;
    unk_4C = 90.0f;
    unk_50_r = 52.6f;
    unk_534 = var_10->unk_F0;
    unk_538 = 1.0f;
    unk_53C = 0.0f;
    unk_540 = 0.0f;
    zero_v3d(&unk_3C_v);
    unk_108 = flt_3D9728;
    for (var_14 = 0; var_14 < 2; var_14++)
        unk_1B30[var_14] = -1;
    unk_21B4.sub_1154A0();
    if (var_10->unk_254)
    {
        sub_19A750("NOTE: !!! Player::Init(): using player attribs from previous level or from memCard !!!\n");
        var_4C = &dword_4F28F0->unk_5C;
        for (var_50 = 0; var_50 < 13; var_50++)
        {
            if (var_4C->unk_18.unk_04[var_50])
            {
                switch (var_50)
                {
                case 2:
                case 5:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                    if (var_4C->unk_18.unk_04[var_50])
                    {
                    }
                    break;
                case 3:
                case 4:
                case 6:
                    unk_21B4.sub_116080(var_50, var_4C->unk_18.unk_04[var_50]);
                    unk_21B4.sub_115980(var_50);
                }
            }
        }
        unk_19E0 = var_4C->unk_50;
        unk_19DC = var_4C->unk_54;
    }
    else
    {
        unk_19E0 = 100;
        unk_19DC = 1.0f;
    }
    unk_3EC = 0.0f;
    unk_3F0 = 0.0f;
    unk_3F4 = 0.0f;
    unk_3F8 = 0.0f;
    unk_1A38 = 0.0f;
    unk_3FC = 0.0f;
    unk_400 = 0.0f;
    unk_404 = 0.0f;
    unk_408 = 0.0f;
    unk_414 = 0;
    unk_40C = 0.0f;
    unk_410 = 0.0f;
    unk_418 = 0.0f;
    unk_41C = 0.0f;
    unk_4F0 = 0.0f;
    unk_4F4 = 0.0f;
    unk_4F8 = 0;
    unk_51C = 0;
    unk_520 = 0;
    unk_420 = 0.0f;
    unk_424 = -3;
    unk_430 = 0;
    unk_428 = 0.0f;
    unk_42C = 0;
    unk_4FC = 0.0f;
    unk_500 = 0.0f;
    unk_504 = 0.0f;
    unk_508 = 0.0f;
    unk_50C = 0;
    unk_20CC = 0.0f;
    unk_20D0 = 0.0f;
    unk_20D4 = 0.0f;
    unk_20C8 = 0.0f;
    unk_20C4 = 0.0f;
    unk_20D8 = 0.0f;
    unk_20DC = dword_429744;
    unk_20E8 = 0;
    unk_20E0 = 0.0f;
    unk_20E4 = 0.0f;
    unk_1B20 = 0;
    unk_1B24 = 0;
    unk_510 = -1000000.0f;
    unk_518 = 0.0f;
    unk_514 = 0;
    unk_52C = 0.0f;
    unk_434.x = unk_434.y = unk_434.z = 0.0f;
    unk_440.x = unk_440.y = unk_440.z = 0.0f;
    unk_44C = dword_429750;
    unk_454 = 0;
    unk_46C = 0;
    unk_470 = var_10->unk_1CC;
    unk_458 = 0;
    unk_45C = dword_429758;
    unk_460 = 0;
    unk_464 = 0.0f;
    unk_468 = 0.0f;
    unk_4D0 = 0;
    unk_4D4 = 2;
    unk_4D8 = 0;
    unk_4DC = 0.0f;
    unk_4E0 = unk_534;
    unk_4E4 = unk_534;
    unk_4E8 = 0.0f;
    unk_4EC = unk_534;
    unk_544 = 0.0f;
    unk_548 = 0.0f;
    unk_19D0 = 0;
    unk_19F8 = 0;
    unk_19FC = 0;
    unk_19F4 = 0;
    unk_19E4 = 0.0f;
    unk_19E8 = 0.0f;
    unk_19EC = 0.0f;
    unk_19F0 = 0.0f;
    unk_1A04 = 0;
    unk_1A08 = 0;
    unk_1A00 = var_10->unk_144_a[0];
    unk_1A0C = 0;
    unk_1A10 = 0.0f;
    unk_1A18 = 0.0f;
    unk_19D8 = 0;
    unk_1A1C = 0;
    unk_1B28 = 0;
    unk_1B3C = 1;
    unk_1B40 = 1;
    unk_90.sub_CCC60();
    var_48 = RwFrameCreate();
    if (var_48)
    {
        RwFrameSetIdentity(var_48);
        unk_338.sub_129A70(var_48);
        unk_338.sub_129AE0(this);
    }
    var_5C = sub_78830(2);
    unk_280 = var_5C;
    var_18 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = var_18;
    var_18->unk_1C = (RwInt32)this;
    sub_D5B80(this, 0xE);
    unk_1AE4 = 0;
    unk_1AEC = 0;
    unk_1AF4 = 0.0f;
    unk_1AF8.x = 0.0f;
    unk_1AF8.y = 0.0f;
    unk_1AF8.z = 0.0f;
    unk_1B04 = 0;
    unk_1B08 = 0;
    unk_1B0C = 0;
    unk_1B10 = 0;
    unk_1B14 = 0;
    unk_1B1C = 0;
    unk_1B2C = 0;
    unk_1B44 = 0;
    unk_20EC = 0;
    for (var_14 = 0; var_14 < 39; var_14++)
        unk_1A48[var_14] = 0;
    unk_2108.sub_D48D0(0);
    unk_210C.sub_D48D0(0);
    unk_2114.sub_D48D0(0);
    unk_1A34.sub_D48D0(0);
    unk_2180.sub_D48D0(0);
    unk_2184 = 0;
    unk_2188 = 0;
    unk_54C = 0;
    unk_550.sub_16BC0(this);
    unk_20FC = 0;
    var_C.x = 0.0f;
    var_C.y = 0.0f;
    var_C.z = 0.0f;
    var_40 = RpAtomicCreate();
    var_48 = RwFrameCreate();
    RwFrameSetIdentity(var_48);
    RpAtomicSetFrame(var_40, var_48);
    RwFrameAddChild(unk_338.get_unk_08(), var_48);
    var_40->boundingSphere.center = var_C;
    var_40->boundingSphere.radius = unk_4C;
    RpAtomicSetFlags(var_40, rpATOMICCOLLISIONTEST);
    sub_FB990(var_40, 4);
    sub_173320(var_40);
    unk_274.sub_129430(var_40);
    unk_274.sub_1294A0(this);
    unk_219C[0] = 75.0f;
    unk_219C[1] = 45.0f;
    unk_219C[2] = 25.0f;
    unk_21A8[0] = -45.0f;
    unk_21A8[1] = -15.0f;
    unk_21A8[2] = 20.0f;
    unk_58 = 0;
    unk_2100 = 0.0f;
    for (var_54 = 0; var_54 < 20; var_54++)
        unk_21F0[var_54] = 0;
    unk_2240 = 1;
    unk_1A30 = 1.0f;
    unk_2244 = 0;
    unk_2248 = unk_4B9308.sub_EED00(0x1D);
    unk_224C = unk_4B9308.sub_EED00(0x1E);
    unk_1B38 = 0;
    unk_2110.sub_D48D0(0);
    unk_2178 = 0;
    unk_2250 = 0;
    unk_2118.sub_D48D0(0);
    unk_213C.x = unk_213C.y = unk_213C.z = 0.0f;
    unk_2148 = 0.0f;
    unk_214C = 0.0f;
    unk_2150 = 0.0f;
    unk_2154 = 0;
    unk_2158 = 0.0f;
    unk_215C = 0;
    unk_2160 = 0;
@@TABLE@@
    var_44 = sub_19B0A0();
    for (var_58 = 0; var_58 < 39; var_58++)
    {
        if (strlen(dword_429A84[var_44][var_58]) >= 24)
        {
            strncpy(unk_1D1C[var_58], dword_429A84[var_44][var_58], 23);
            unk_1D1C[var_58][23] = 0;
        }
        else
            strcpy(unk_1D1C[var_58], dword_429A84[var_44][var_58]);
    }
    ((PlayerTrigger *)arg_0)->sub_ACA70();
    unk_3DC = dword_4F28F0->get_unk_1C();
    sub_FEFE0();
    sub_108FF0(0);
    unk_2174.sub_D48D0(0);
    byte_4C1940 = 0;
    dword_4C19AC = 0;
    byte_429700 = 1;
    byte_4CF9AC = 0;
    flt_429C38 = 1.0f;
    sprintf(var_3C, "%d", unk_21B4.sub_1E3BF0(1));
    sub_EAB80(var_3C, 7);
    unk_20F0 = 1.0f;
    unk_20F4 = 0;
    ((PlayerTrigger *)arg_0)->unk_304 = dword_4F28F0->unk_181;
    return 1;
}

