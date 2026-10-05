// The vehicle seat state (state 12): it looks and turns by its trigger's
// speeds, and when it is in a vehicle's seat its frame is set to the seat's
// matrix (sub_EC2D0 on the vehicle's clump), raised by its height on an
// animated entity plus 35.
// match: ?sub_10B560@type_10F710@@QAEXM@Z @ 0x0010B560
void type_10F710::sub_10B560(RwReal arg_0)
{
    type_712B0_10F710 *v_8;
    type_3D3548 *v_10;
    RpClump *v_14;
    RwMatrix v_60;
    RwFrame *v_6C;

    v_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_8 && v_8->vf_008() != 1)
    {
        v_8 = 0;
    }
    if (!v_8)
    {
        return;
    }
    unk_28 &= 0xFFFFFF51;
    unk_28 |= 0x50;
    zero_v3d(&unk_D8_v);
    sub_10A330(v_8->unk_154, arg_0);
    sub_109AE0(v_8->unk_1B4, arg_0);
    v_10 = unk_2180.sub_D4910();
    if (v_10 && unk_2184)
    {
        v_14 = v_10->unk_25C.unk_08;
        if (sub_EC2D0(v_14, (RwInt32)&v_60, unk_2184, 0, 1))
        {
            v_60.pos.y += ((type_712B0_10F710 *)unk_344.get_unk_08())->unk_148 + 35.0f;
            v_6C = unk_338.get_unk_08();
            RwFrameTransform(v_6C, &v_60, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(v_6C);
            unk_160.y = unk_178.y;
        }
    }
}

