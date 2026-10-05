// The local player's respawn, once asked for (unk_284). The first step picks
// the team and kit chosen (the second player's team taken when team 1 is
// asked for) and the spawn point: the host's own (sub_1AD380 over the
// point set), a client's asked of the host (type_3E10D4). The next steps
// (after 10 seconds the session gives up and the screen fades) wait for the
// point and the fade, then place the player's trigger at the point (made
// upright), give it the team's kit, respawn it, fade in and tell the peers
// (type_3E117C) and the teams.
// match: ?sub_1ABE30@type_4F7EB8@@QAEXXZ @ 0x001ABE30
void type_4F7EB8::sub_1ABE30()
{
    type_1DDE20_mask var_8;
    type_3E10D4 var_10;
    RwUInt32 *var_14 = 0;
    RwInt32 var_18;

    if (unk_284)
    {
        if (!unk_288)
        {
            unk_29C = unk_2BC;
            unk_2A0 = unk_2C0;
            if (!sub_1AEC70())
            {
                if (unk_29C == 1)
                {
                    sub_1AFB70();
                    unk_29C = unk_2BC;
                    unk_298 = unk_29C;
                }
                // A compiled-out check (docs/toolchain.md): one load on.
                if (!unk_2BC)
                {
                }
                unk_3D0.sub_1C2600(0, unk_29C);
                var_18 = sub_1AC4E0(unk_29C);
                unk_294 = sub_1AD380(var_18, 0);
                unk_290 = 1;
            }
            else
            {
                // Another (docs/toolchain.md): one load on.
                if (!unk_2BC)
                {
                }
                var_10.unk_04 = unk_29C;
                // Two more (docs/toolchain.md): two loads on.
                if (!unk_2BC)
                {
                }
                if (!unk_2BC)
                {
                }
                var_8.put(0);
                dword_4F8058->sub_1DDE20(&var_10, var_8);
                sub_1A8A70(&unk_4F7EB8, "(CLIENT) Requested spawn point from set %d from server\n", var_18);
            }
            unk_288 = 1;
            unk_28C = sub_1CCA10();
        }
        else
        {
            RwInt32 var_30 = sub_1CCA10() - unk_28C;
            RwReal var_34 = var_30 * 0.001f;

            if (var_34 > 10.0f)
            {
                unk_19C->get_unk_B0()->sub_1CD370();
                unk_19C->sub_1CC8F0(7, 6);
                sub_124EE0(0.5f, 0);
            }
            if (unk_290 && fade_done())
            {
                if (unk_29C == 1)
                {
                    // Another (docs/toolchain.md): one load on.
                    if (!unk_2BC)
                    {
                    }
                    unk_2BC = unk_298;
                    unk_29C = unk_2BC;
                }
                // Another (docs/toolchain.md): one load on.
                if (!unk_2BC)
                {
                }
                var_14 = unk_4FBC50.sub_1C20D0(unk_294);
                sub_1C58C0();
                dword_4B6850 = 1;
                // Two more (docs/toolchain.md): two loads on.
                if (!unk_2BC)
                {
                }
                if (!unk_2BC)
                {
                }
                dword_4B6840[0] = var_14[0];
                dword_4B6840[1] = var_14[1];
                dword_4B6840[2] = var_14[2];
                dword_4B6840[3] = var_14[3];
                sub_D8660();
                RwMatrix var_80 = *unk_4FBC50.sub_1C20F0(unk_294);

                {
                    RwV3d *var_84 = &var_80.up;
                    RwV3d *var_88 = &var_80.at;
                    RwV3d *var_8C = &var_80.right;

                    var_84->x = 0;
                    var_84->y = 1.0f;
                    var_84->z = 0;
                    RwV3dCrossProduct(var_88, var_8C, var_84);
                    RwV3dCrossProduct(var_8C, var_84, var_88);
                }
                RwMatrixUpdate(&var_80);
                unk_278->sub_1BEAC0(&var_80);
                if (unk_280)
                {
                    unk_278->unk_470[0] = sub_1C5860(unk_280->sub_1B79A0(unk_29C, unk_2A0));
                    unk_278->unk_470[1] = -1;
                    unk_278->unk_478 = sub_1C5860(unk_280->sub_1B79A0(unk_29C, 4));
                    unk_278->unk_47C = sub_1AF2C0(unk_2A0);
                    unk_278->unk_CC = *(type_3DF8D8_04 *)unk_280->sub_1B7940(unk_29C);
                }
                unk_278->sub_1BE5E0();
                unk_284 = 0;
                sub_124EE0(0.5f, 0);
                dword_4FDA9C = 0;
                type_3E117C var_98;

                var_98.unk_04 = unk_29C;
                var_98.unk_08 = unk_278->unk_108[0];
                // Two more (docs/toolchain.md): two loads on.
                if (!unk_2BC)
                {
                }
                if (!unk_2BC)
                {
                }
                get_unk_1A0()->sub_1DDE20(&var_98, get_unk_19C()->get_unk_B0()->sub_1A8050());
                sub_1A8A70(&unk_4F7EB8, "Local player respawned\n");
                unk_3D0.sub_1C28F0(sub_1AEC70(), unk_29C, 0);
                clear_hud_unk_90();
                unk_290 = 0;
                unk_288 = 0;
            }
        }
    }
}

