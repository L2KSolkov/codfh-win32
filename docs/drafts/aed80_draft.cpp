// SUPERSEDED for sub_1AED80: matched in src/recovered/unit_1A8B20.cpp.
// A checked network-player accessor fixes the post-conversion registers.
// This historical snapshot must not replace the current unit.

// Respawns the remote player arg_0 as team arg_4's spawn arg_8 (-1 for
// any): its old soldier (taken out of view first while the second player
// shows it) is let go and kept in unk_238, or, with none, the one kept there
// is let go unless another player holds it or it is marked. With the level's
// parameters the maker (unk_27C) takes the team's and the spawn's settings
// and the spawn's index; it is given the player's name, makes the soldier
// (with room made in the entity pool), which the network player and the
// session are told of, and is moved back to where it was (its matrix up 1
// and down 1000).
// match: ?sub_1AED80@type_4F7EB8@@QAEXHII@Z @ 0x001AED80
void type_4F7EB8::sub_1AED80(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8)
{
    if (unk_1F0[arg_0])
    {
        if (unk_4F6B00[arg_0].is_visible())
        {
            unk_4F6B00[arg_0].sub_1A63E0();
            unk_4F7EB8.sub_1AB2C0();
        }
        unk_4F6B00[arg_0].sub_1A6460();
        unk_238[arg_0] = unk_1F0[arg_0];
        sub_D5A60(unk_1F0[arg_0], 0);
        unk_1F0[arg_0] = 0;
    }
    else if (unk_238[arg_0])
    {
        bool var_1;
        RwInt32 var_8;

        var_1 = false;
        for (var_8 = 0; var_8 < 16; var_8++)
        {
            if (unk_1F0[var_8] == unk_238[arg_0])
                var_1 = true;
        }
        if (!var_1 && !(unk_238[arg_0]->unk_28 & 1))
            sub_D5A60(unk_238[arg_0], 0);
    }
    if (unk_4F7EB8.unk_280)
    {
        unk_27C->unk_D8 = *unk_280->sub_1B7910(arg_4);
        unk_27C->unk_120 = *unk_280->sub_1B7970(arg_4, arg_8);
        unk_27C->unk_12C = 0;
        unk_27C->unk_128 = 0;
        if (arg_8 == -1)
            unk_27C->unk_130 = unk_280->sub_1B79A0(arg_4, 0);
        else
            unk_27C->unk_130 = sub_1C5800(arg_8);
        unk_27C->unk_134 = -1;
    }
    strcpy(unk_27C->unk_174, type_4F8054::get()->get_unk_B0()->unk_90[arg_0].unk_00);
    sub_D5D20(1);
    unk_1F0[arg_0] = unk_27C->vf_020();
    unk_4F6B00[arg_0].sub_1A6420(unk_1F0[arg_0]);
    unk_1F0[arg_0]->pvf_010(unk_1A0);
    RwReal &var_1C = unk_27C->unk_60.pos.x;

    var_1C += 1.0f;
    RwReal &var_20 = unk_27C->unk_60.pos.y;

    var_20 -= 1000.0f;
    RwMatrixUpdate(&unk_27C->unk_60);
}

