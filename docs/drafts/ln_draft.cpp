// The weapon's recoil scaled by the stance: unk_13C crouched, unk_140 prone,
// else 1; an inline with no address and so no database name, named for what
// it gives. Evidence: sub_1116A0 copies the stance into a temporary and
// then each branch's scale into the result's.
inline RwReal stance_recoil(type_4C19C0 *arg_0, RwInt32 arg_4)
{
    if (arg_4 == 1)
        return arg_0->unk_13C;
    else if (arg_4 == 2)
        return arg_0->unk_140;
    return 1.0f;
}

// Adds arg_4 to arg_0 and bounds it by arg_8 (the lower bound sets arg_8
// too, as the image does); an inline with no address and so no database
// name. Evidence: sub_1116A0 keeps the target's address in a temporary of
// its own, and the bound in another when it is not a constant.
inline void add_bounded(RwReal &arg_0, RwReal arg_4, RwReal arg_8)
{
    arg_0 += arg_4;
    if (arg_0 > arg_8)
        arg_0 = arg_8;
    else if (-arg_8 > arg_0)
        arg_0 = arg_8;
}

// Wraps the angle arg_0 into -180 to 180 degrees; an inline with no
// address. Evidence: sub_1116A0 keeps the angle's address in a temporary.
inline void wrap_180(RwReal &arg_0)
{
    if (arg_0 > 180.0f)
        arg_0 -= 360.0f;
    else if (arg_0 < -180.0f)
        arg_0 += 360.0f;
}

// The lean and recoil on the root's rotation arg_0 (the pose, sub_10C7B0):
// on foot or on a mounted weapon (or while vf_1E4 allows), a fire records the
// look's pitch and the view's heading; after the burst the pitch returns
// there and the view turns back when it moved by more than 10 degrees. The
// weapon's recoil by kind (random, building up to 1000, or every so many
// fires up to its settings' bounds) springs into the pitch and yaw offsets
// (sub_112DA0) with the pad's rumble; aiming, the scope's sway (sines by the
// stance, blended while it changes) follows its settings, else decays. The
// sideways sway (unk_4F0) and the offsets then turn the rotation.
// match: ?sub_1116A0@type_10F710@@QAEXPAURtQuat@@M@Z @ 0x001116A0
void type_10F710::sub_1116A0(RtQuat *arg_0, RwReal arg_4)
{
    RwInt32 v_4;
    RwReal v_8;
    type_4C19C0 *v_C;
    RwInt32 v_10;
    RwReal v_14;
    RwReal v_18;
    RwReal v_1C;
    RwReal v_20;
    type_10F710_1A48 *v_24;
    RwFrame *v_28;
    RwMatrix *v_2C;
    RwFrame *v_30;
    RwReal v_34;
    RwReal v_38;
    RwMatrix *v_3C;
    RwReal v_40;
    RwReal v_44;
    RwReal v_48;
    RwReal v_4C;
    RwReal v_50;
    RwReal v_54;
    RwReal v_58;
    RwReal v_5C;
    RwReal v_60;
    RwReal v_64;
    RwReal v_68;
    RtQuat v_78;
    RtQuat v_88;
    RwReal v_8C;
    RwReal v_90;
    RwReal v_94;
    RwReal v_98;
    RwReal v_9C;
    RtQuat v_AC;
    RtQuat v_BC;
    RwReal v_C0;
    RtQuat v_D0;
    RwReal v_D4;
    RtQuat v_E4;
    RwReal v_E8;
    RwReal v_EC;
    RwReal v_F0;
    RwReal v_F4;
    RwReal v_F8;
    RwReal v_FC;

    if (unk_19D0 != 0 && unk_19D0 != 1 && unk_19D0 != 2 && unk_19D0 != 3 && unk_19D0 != 7 && !vf_1E4())
        return;
    v_8 = 0.1f;
    v_1C = 0.6f;
    v_24 = unk_1A48[unk_1AE4];
    v_C = v_24->unk_448;
    v_14 = 1.0f;
    if (unk_1B04 && !unk_1B0C)
        v_14 = v_C->unk_144;
    v_4 = 0;
    if (unk_1B20)
    {
        v_4 = 1;
        if (!unk_20E8)
        {
            unk_20E8 = 1;
            unk_20E0 = unk_530;
            v_28 = unk_338.unk_08;
            if (v_28 && (v_2C = RwFrameGetMatrix(v_28)) != 0)
            {
                if (v_2C->at.x == 0.0f)
                    unk_20E4 = (RwReal)atan(v_E8 = ratio(-v_2C->up.z, -v_2C->up.x));
                else
                    unk_20E4 = (RwReal)atan(v_EC = v_2C->at.z / v_2C->at.x);
                unk_20E4 *= 57.295784f;
            }
        }
    }
    else if (!unk_1B24)
    {
        if (unk_20E8 == 1)
        {
            v_38 = (RwReal)fabs(v_F0 = unk_530 - unk_20E0);
            unk_20C8 = unk_20C8 - unk_530 + unk_20E0;
            unk_20D8 = 0.0f;
            unk_530 = unk_20E0;
            v_30 = unk_338.unk_08;
            if (v_30 && (v_3C = RwFrameGetMatrix(v_30)) != 0)
            {
                if (v_3C->at.x == 0.0f)
                    v_34 = (RwReal)atan(v_F4 = ratio(-v_3C->up.z, -v_3C->up.x));
                else
                    v_34 = (RwReal)atan(v_F8 = v_3C->at.z / v_3C->at.x);
                v_34 *= 57.295784f;
                if ((RwReal)fabs(v_FC = v_34 - unk_20E4) > 10.0f || v_38 > 10.0f)
                {
                    RwFrameRotate(v_30, &stru_3D973C, -unk_20CC, rwCOMBINEPRECONCAT);
                    unk_20CC = 0.0f;
                    unk_20D4 = 0.0f;
                }
            }
        }
        unk_20E8 = 0;
    }
    else if (unk_20E8)
        v_4 = 1;
    if (v_4)
    {
        v_40 = unk_4B9308.sub_EE8F0(unk_3D8, 5);
        if (v_40 != 0.0f)
        {
        }
    }
    v_10 = v_24->unk_458;
    if (unk_19D0 == 7)
        v_10 = 3;
    switch (v_10)
    {
    case 3:
    case 4:
    case 5:
    case 6:
    case 23:
        v_8 = v_C->unk_10C;
        v_1C = v_C->unk_110;
        if (unk_1B20)
        {
            v_44 = v_C->unk_104;
            v_48 = v_C->unk_108;
            v_4C = stance_recoil(v_C, unk_1A04) * v_14 * 1.0f;
            if (v_24->unk_230)
                v_4C *= 0.1f;
            v_44 *= v_4C;
            v_48 *= v_4C;
            unk_20C4 = frand_range(-v_44, v_44);
            unk_20D0 = frand_range(-v_48, v_48);
        }
        else if (!unk_1B24 || unk_20C4 == 0.0f)
        {
            unk_20C4 = 0.0f;
            unk_20D0 = 0.0f;
            v_8 = v_C->unk_114;
            v_1C = v_C->unk_118;
        }
        break;
    case 0:
    case 1:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        v_8 = v_C->unk_F4;
        v_1C = v_C->unk_F8;
        if (unk_1B20)
        {
            v_50 = v_C->unk_EC;
            v_54 = v_C->unk_F0;
            v_58 = stance_recoil(v_C, unk_1A04) * v_14 * 1.0f;
            v_50 *= v_58;
            v_54 *= v_58;
            add_bounded(unk_20C4, v_50, 1000.0f);
            add_bounded(unk_20D0, v_54, 1000.0f);
        }
        else if (!unk_1B24 || unk_20C4 == 0.0f)
        {
            unk_20C4 = 0.0f;
            unk_20D0 = 0.0f;
            v_8 = v_C->unk_FC;
            v_1C = v_C->unk_100;
        }
        break;
    case 2:
    case 7:
    case 8:
    case 9:
    case 10:
    case 24:
    case 37:
        v_8 = v_C->unk_12C;
        v_1C = v_C->unk_130;
        if (unk_1B20)
        {
            unk_20DC--;
            if (unk_20DC < 0)
            {
                unk_20DC = 0;
                v_5C = v_C->unk_11C;
                v_60 = v_C->unk_120;
                v_64 = stance_recoil(v_C, unk_1A04) * v_14 * 1.0f;
                if (v_24->unk_230)
                    v_64 *= 0.1f;
                v_5C *= v_64;
                v_60 *= v_64;
                add_bounded(unk_20C4, v_5C, v_C->unk_124);
                add_bounded(unk_20D0, v_60, v_C->unk_128);
            }
        }
        else if (!unk_1B24 || unk_20C4 == 0.0f)
        {
            unk_20C4 = 0.0f;
            unk_20D0 = 0.0f;
            v_8 = v_C->unk_134;
            v_1C = v_C->unk_138;
        }
        break;
    }
    sub_112DA0(&unk_20C8, unk_20C4, &unk_20D8, v_8, v_1C, 10000.0f, arg_4);
    sub_112DA0(&unk_20CC, unk_20D0, &unk_20D4, v_8, v_1C, 10000.0f, arg_4);
    if (unk_1B20)
        unk_4B9308.sub_EED30(unk_3D8, v_C->unk_148, v_C->unk_14C, v_C->unk_14D);
    v_18 = 0.0f;
    v_20 = 0.0f;
    if (unk_1B04 && !unk_1B0C && !unk_50C)
    {
        v_68 = 1.0f;
        if (unk_1A0C)
        {
            if (!unk_1A08 && unk_1A04 == 1)
                v_68 = (flt_429B00 - 1.0f) * unk_1A10 + 1.0f;
            else if (unk_1A08 == 1 && !unk_1A04)
                v_68 = (1.0f - flt_429B00) * unk_1A10 + flt_429B00;
            else if (unk_1A08 == 1 && unk_1A04 == 2)
                v_68 = (flt_429B04 - flt_429B00) * unk_1A10 + flt_429B00;
            else if (unk_1A08 == 2 && unk_1A04 == 1)
                v_68 = (flt_429B00 - flt_429B04) * unk_1A10 + flt_429B04;
        }
        else if (unk_1A04 == 1)
            v_68 = v_C->unk_160;
        else if (unk_1A04 == 2)
            v_68 = v_C->unk_164;
        unk_4FC += v_C->unk_154;
        wrap_180(unk_4FC);
        unk_500 += v_C->unk_150;
        wrap_180(unk_500);
        unk_504 = v_68 * v_C->unk_15C * sin_ref(unk_4FC);
        v_18 = unk_504;
        unk_508 = v_68 * v_C->unk_158 * sin_ref(unk_500);
        v_20 = unk_508;
    }
    else
    {
        unk_4FC = 0.0f;
        unk_500 = 0.0f;
        unk_504 *= 0.9f;
        if (ABS(unk_504) < 0.1f)
            unk_504 = 0.0f;
        unk_508 *= 0.9f;
        if (ABS(unk_508) < 0.1f)
            unk_508 = 0.0f;
        v_18 = unk_504;
        v_20 = unk_508;
        if (unk_504 == 0.0f && unk_508 == 0.0f)
            unk_50C = 0;
        else
            unk_50C = 1;
    }
    if (unk_4F0 > 0.01 || unk_4F0 < -0.01f)
    {
        v_90 = unk_4F0 / flt_429ADC;
        if (v_90 > 1.0f)
            v_90 = 1.0f;
        else if (v_90 < -1.0f)
            v_90 = -1.0f;
        v_8C = -((v_94 = v_90 * flt_429B0C) * 0.017453292f * 0.5f);
        v_78.imag.x = 0.0f;
        v_78.imag.y = 0.0f;
        v_78.imag.z = (RwReal)sin(v_8C);
        v_78.real = (RwReal)cos(v_8C);
        RtQuatMultiplyMacro(&v_88, arg_0, &v_78);
        arg_0->imag.x = v_88.imag.x;
        arg_0->imag.y = v_88.imag.y;
        arg_0->imag.z = v_88.imag.z;
        arg_0->real = v_88.real;
    }
    if (v_18 != 0.0f || v_20 != 0.0f || unk_20C8 != 0.0f || unk_20CC != 0.0f)
    {
        v_E4.imag.x = (RwReal)sin(v_98 = -((v_9C = v_18 + unk_20C8) * 0.017453292f * 0.5f));
        v_E4.imag.y = 0.0f;
        v_E4.imag.z = 0.0f;
        v_E4.real = (RwReal)cos(v_98);
        v_D4 = -((v_C0 = v_20 + unk_20CC) * 0.017453292f * 0.5f);
        v_D0.imag.x = 0.0f;
        v_D0.imag.y = (RwReal)sin(v_D4);
        v_D0.imag.z = 0.0f;
        v_D0.real = (RwReal)cos(v_D4);
        RtQuatMultiplyMacro(&v_AC, &v_D0, &v_E4);
        RtQuatMultiplyMacro(&v_BC, arg_0, &v_AC);
        arg_0->imag.x = v_BC.imag.x;
        arg_0->imag.y = v_BC.imag.y;
        arg_0->imag.z = v_BC.imag.z;
        arg_0->real = v_BC.real;
    }
}
