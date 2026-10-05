// Its pose's procedural part, on its animation's current keyframes: the eye
// height by stance (blended while it changes); node 1 (the root) raised to
// its trigger's height (while dying, by the eye height's change, crouched
// excepted), its view bob (vf_240) and lean (sub_1116A0), placed at the
// camera's while the camera follows it; the root turned about x by half the
// look's pitch. Node 2 (the spine) turned by the weapon's hold by stance (with
// the recoil while aiming, blended while the stance changes) about x, z and
// y, or for weapons with their own pose slerped into it with its offset;
// then the sway (unk_1AF8) added to its translation.
// match: ?sub_10C7B0@type_10F710@@QAEXM@Z @ 0x0010C7B0
void type_10F710::sub_10C7B0(RwReal arg_0)
{
    RtQuat v_D0;
    RtQuat v_C0;
    RwV3d v_B0;
    type_4C19C0 *v_A4;
    RwV3d v_A0;
    RwV3d v_94;
    type_7CBD0_t *v_88;
    RtQuat v_84;
    RwV3d *v_74;
    RtQuat *v_70;
    RwInt32 v_6C;
    type_4C19C0 *v_68;
    RtQuat v_64;
    RwReal *v_54;
    RtQuat v_50;
    RwInt32 v_40;
    RpHAnimHierarchy *v_3C;
    RtQuat v_38;
    type_7CBD0 *v_28;
    type_7CBD0_hdr *v_24;
    RtQuat v_20;
    type_712B0_10F710 *v_10;
    type_3DD948 *v_C;
    RwReal v_8;
    RwInt32 v_4;

    v_10 = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_10 && v_10->vf_008() != 1)
    {
        v_10 = 0;
    }
    v_68 = unk_1A48[unk_1AE4]->unk_448;
    v_3C = unk_284->unk_18;
    if (!v_3C->currentAnim)
        return;
    v_28 = (type_7CBD0 *)((type_80300 *)v_3C->currentAnim)->unk_144;
    v_24 = v_28->unk_04;
    v_88 = (type_7CBD0_t *)&v_28->unk_10[v_24->unk_00];
    v_70 = v_28->unk_10;
    v_40 = 0;
    v_4 = 1;
    v_6C = 2;
    v_54 = v_10->unk_144_a;
    if (unk_1A0C)
        unk_1A00 = sub_112F80(v_54[unk_1A08], v_54[unk_1A04], unk_1A10);
    else
        unk_1A00 = v_54[unk_1A04];
    if (unk_19D0 != 0xA)
        v_88[v_4].unk_00.y = v_10->unk_150;
    else if (unk_1A04 != 2)
        v_88[v_4].unk_00.y += unk_1A00 + v_10->unk_150 - unk_48;
    else
        v_88[v_4].unk_00.y = v_10->unk_150;
    vf_240(&v_88[v_4].unk_00, arg_0);
    sub_1116A0(&v_70[v_4], arg_0);
    v_C = (type_3DD948 *)unk_2110.sub_D4910();
    if (v_C->unk_3B0)
        v_88[v_4].unk_00 = RwFrameGetMatrix(v_C->get_unk_340())->pos;
    v_84.real = (RwReal)cos(v_8 = unk_530 * 0.5f * 0.017453292f);
    v_84.imag.x = (RwReal)sin(v_8);
    v_84.imag.y = v_84.imag.z = 0.0f;
    RtQuatMultiplyMacro(&v_64, &v_70[v_4], &v_84);
    v_70[v_4] = v_64;
    if (!v_68->unk_20)
    {
        if (unk_1B04 || unk_1B08)
        {
            v_A0 = unk_1A48[unk_1AE4]->unk_238_a[unk_1A04];
            RwV3dAddMacro(&v_A0, &unk_1A48[unk_1AE4]->unk_280, &v_A0);
            v_74 = &v_A0;
        }
        else
        {
            v_A0 = unk_1A48[unk_1AE4]->unk_238_a[unk_1A04];
            if (unk_1A0C)
            {
                v_A4 = unk_1A48[unk_1AE4]->unk_448;
                sub_112FC0(&v_A0, &v_A4->unk_1C0_a[unk_1A08], &v_A4->unk_1C0_a[unk_1A04], unk_1A10);
            }
            v_74 = &v_A0;
        }
        v_94.x = v_74->x * 0.5f * 0.017453292f;
        v_94.y = v_74->y * 0.5f * 0.017453292f;
        v_94.z = v_74->z * 0.5f * 0.017453292f;
        v_20.real = (RwReal)cos(v_94.y);
        v_84.real = (RwReal)cos(v_94.x);
        v_38.real = (RwReal)cos(v_94.z);
        v_20.imag.y = (RwReal)sin(v_94.y);
        v_84.imag.x = (RwReal)sin(v_94.x);
        v_38.imag.z = (RwReal)sin(v_94.z);
        v_84.imag.y = v_84.imag.z = v_20.imag.x = v_20.imag.z = v_38.imag.x = v_38.imag.y = 0.0f;
        RtQuatMultiplyMacro(&v_64, &v_70[v_6C], &v_84);
        RtQuatMultiplyMacro(&v_50, &v_64, &v_38);
        RtQuatMultiplyMacro(&v_70[v_6C], &v_50, &v_20);
        v_88[v_6C].unk_00.x = v_88[v_6C].unk_00.x + unk_1AF8.x;
        v_88[v_6C].unk_00.y = v_88[v_6C].unk_00.y + unk_1AF8.y;
        v_88[v_6C].unk_00.z = v_88[v_6C].unk_00.z + unk_1AF8.z;
    }
    else
    {
        if (unk_1B04 || unk_1B08)
        {
            sub_13FBC0(&v_D0, &unk_1A48[unk_1AE4]->unk_170[unk_1A04], &unk_1A48[unk_1AE4]->unk_1A0[unk_1A04],
                       unk_1A48[unk_1AE4]->unk_218);
            sub_112FC0(&v_B0, &unk_1A48[unk_1AE4]->unk_1D0[unk_1A04], &unk_1A48[unk_1AE4]->unk_1F4[unk_1A04],
                       unk_1A48[unk_1AE4]->unk_218);
        }
        else if (unk_1A0C)
        {
            sub_13FBC0(&v_D0, &unk_1A48[unk_1AE4]->unk_170[unk_1A08], &unk_1A48[unk_1AE4]->unk_170[unk_1A04],
                       unk_1A10);
            sub_112FC0(&v_B0, &unk_1A48[unk_1AE4]->unk_1D0[unk_1A08], &unk_1A48[unk_1AE4]->unk_1D0[unk_1A04],
                       unk_1A10);
        }
        else
        {
            v_D0 = unk_1A48[unk_1AE4]->unk_170[unk_1A04];
            v_B0 = unk_1A48[unk_1AE4]->unk_1D0[unk_1A04];
        }
        RtQuatMultiplyMacro(&v_C0, &v_70[v_6C], &v_D0);
        v_70[v_6C] = v_C0;
        v_88[v_6C].unk_00.x += v_B0.x;
        v_88[v_6C].unk_00.y += v_B0.y;
        v_88[v_6C].unk_00.z += v_B0.z;
        v_88[v_6C].unk_00.x = v_88[v_6C].unk_00.x + unk_1AF8.x;
        v_88[v_6C].unk_00.y = v_88[v_6C].unk_00.y + unk_1AF8.y;
        v_88[v_6C].unk_00.z = v_88[v_6C].unk_00.z + unk_1AF8.z;
    }
}
