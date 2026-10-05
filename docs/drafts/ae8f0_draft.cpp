// A grenade thrown by peer arg_4 (type_3E11AC), on the same terms and not
// while the manager's state is 4: thrown (sub_15F2C0, flags 0x401) from the
// thrower's entity at the message's position with its velocity, with the
// weapon's projectile settings (table 2: its damage, spawned object and the
// values for the throw's hand, unk_1C) in a static record.
// match: ?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x001AE8F0
// match: __ehhandler$?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z-0xE @ 0x00302B80
// match: __ehhandler$?sub_1AE8F0@@YAXHHPAUtype_3DA44C@@@Z @ 0x00302B8E
void sub_1AE8F0(RwInt32 arg_0, RwInt32 arg_4, type_3DA44C *arg_8)
{
    sub_1A8A70(&unk_4F7EB8, "Player %d threw a grenade\n", arg_4);
    if (dword_4FB9E0.sub_1E3480() != 1 || dword_4FB9E0.get_unk_C8() || dword_4FB9E0.get_unk_C4()
        || unk_4F7EB8.unk_2A4 == 4)
    {
        return;
    }
    type_3E11AC *m = (type_3E11AC *)arg_8;
    RwInt32 v_20 = 0x401;
    RwMatrix v_60;
    RwV3d v_6C;

    v_60.up.x = 0;
    v_60.up.y = 1.0f;
    v_60.up.z = 0;
    v_60.at.x = 0;
    v_60.at.y = 0;
    v_60.at.z = 1.0f;
    v_60.right.x = 1.0f;
    v_60.right.y = 0;
    v_60.right.z = 0;
    // Two compiled-out checks (docs/toolchain.md): the registers after them
    // are two loads on.
    if (!m->unk_1C)
    {
    }
    if (!m->unk_1C)
    {
    }
    v_60.pos.x = m->unk_04.unk_00;
    v_60.pos.y = m->unk_04.unk_04;
    v_60.pos.z = m->unk_04.unk_08;
    v_6C.x = m->unk_10.unk_00;
    v_6C.y = m->unk_10.unk_04;
    v_6C.z = m->unk_10.unk_08;
    static type_F4890_blast unk_4F83F0;

    memset(&unk_4F83F0, 0, sizeof(unk_4F83F0));
    type_4C19C0 *v_70 = sub_119B70(m->unk_20);

    unk_4F83F0.unk_00 = 2;
    unk_4F83F0.unk_04_r = (RwReal)(RwUInt32)v_70->unk_C4;
    unk_4F83F0.unk_38 = projectile_object(sub_198800(&v_70->unk_00));
    unk_4F83F0.unk_3C = 1;
    unk_4F83F0.unk_40 = v_70->unk_C0;
    unk_4F83F0.unk_44_r = v_70->unk_498_a[m->unk_1C];
    unk_4F83F0.unk_48 = v_70->unk_4AC_a[m->unk_1C];
    unk_4F83F0.unk_4C_r = v_70->unk_D0;
    unk_4F83F0.unk_50.unk_00_r = v_70->unk_4B4;
    unk_4F83F0.unk_50.unk_04 = v_70->unk_4B8;
    unk_4F83F0.unk_50.unk_08 = v_70->unk_4BC;
    unk_4F83F0.unk_50.unk_10 = v_70->unk_4C4;
    unk_4F83F0.unk_50.unk_0C = v_70->unk_4C0;
    unk_4F83F0.unk_50.unk_14 = v_70->unk_4C8;
    unk_4F83F0.unk_50.unk_18_r = v_70->unk_4CC;
    sub_15F2C0(v_20, (RwInt32)unk_4F7EB8.sub_1AECA0(arg_4, 0), &v_60, &v_6C, 0, (type_439A48 *)&unk_4F83F0,
               0);
}

