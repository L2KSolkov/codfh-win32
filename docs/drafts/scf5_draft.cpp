// The melee strike (the sequence event's step), unless the player arg_0
// holds it back (unk_217C): as an entity's blow (type_3D3548::sub_D42D0),
// a sphere of the settings' reach (unk_E0) 50 below the player's frame is
// searched for the nearest entity; one not on its side (or any in a
// network game) takes a blow (0x202 for a player of kind 2, else 0x201)
// of the settings' damage (unk_DC; none when the entity hit is a
// type_3DAFC8 or a type_3DDB98 sharing a side bit with the player), and
// its hit sound plays.
// match: ?sub_11CF50@type_10F710_1A48@@QAEXPAUtype_10F710@@@Z @ 0x0011CF50
void type_10F710_1A48::sub_11CF50(type_10F710 *arg_0)
{
    type_75600 var_124;
    type_4E5D30 *var_F4;
    RwReal var_F0;
    RwV3d var_EC;
    RpIntersection var_24;
    RwInt32 var_8;
    RwInt32 var_4;

    if (arg_0->unk_217C)
    {
        return;
    }
    var_EC.x = unk_448->unk_E0;
    var_EC.y = 50.0f;
    var_EC.z = unk_448->unk_E0;
    var_4 = 0;
    type_93DF0 var_E0;
    var_24.type = rpINTERSECTSPHERE;
    var_24.t.sphere.center = *RwMatrixGetPos(RwFrameGetLTM(arg_0->get_unk_340()));
    var_24.t.sphere.center.y -= 50.0f;
    var_24.t.sphere.radius = var_EC.x;
    var_F0 = var_24.t.sphere.radius * var_24.t.sphere.radius;
    var_E0.unk_6C = 0;
    var_E0.unk_24 = var_F0;
    var_E0.unk_20 = 0;
    var_E0.unk_18 = 0;
    var_E0.unk_04 = arg_0;
    var_E0.unk_14 = arg_0->get_unk_340();
    var_E0.unk_0C = 0;
    var_E0.unk_08 = 0;
    var_E0.unk_60 = 0;
    var_E0.unk_64 = 0;
    var_E0.unk_7C = 0;
    var_E0.unk_28 = 0.0f;
    var_E0.unk_48 = arg_0->unk_50_r;
    var_E0.unk_50 = &var_4;
    var_E0.unk_58 = 0;
    var_E0.unk_54 = 0;
    var_E0.unk_70 = sub_8F940();
    var_8 = 0;
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        var_F4 = &dword_4E5D30[var_8];
        if (var_F4->get_unk_00() && var_F4->get_unk_28())
        {
            RpWorldForAllAtomicIntersections(var_F4->get_unk_28(), &var_24, sub_104D00, &var_E0);
        }
    }
    if (var_E0.unk_28 != 0.0f && var_E0.unk_08)
    {
        if (get_4FB9F8() || (unk_42C->unk_2C & 7) != (var_E0.unk_08->unk_2C & 7))
        {
            memset(&var_124, 0, sizeof(type_75600));
            var_124.unk_00_w = 0;
            var_124.unk_02_w = 1;
            if ((unk_42C->unk_2C & 7) == 2)
            {
                var_124.unk_08 = 0x202;
            }
            else
            {
                var_124.unk_08 = 0x201;
            }
            var_124.unk_14 = 0;
            var_124.unk_18 = 0;
            if ((var_E0.unk_08->vf_008() || var_E0.unk_08->vf_024())
                && ((var_E0.unk_08->unk_2C & 7) & (arg_0->unk_2C & 7)))
            {
                var_124.unk_28 = 0.0f;
                var_124.unk_2C = 0.0f;
            }
            else
            {
                var_124.unk_28 = unk_448->unk_DC_f;
                var_124.unk_2C = unk_448->unk_DC_f;
            }
            var_124.unk_0C = arg_0;
            var_124.unk_10 = arg_0->unk_2C;
            var_124.unk_24 = var_E0.unk_08->vf_07C(2, &var_24, 0, 0);
            var_E0.unk_08->vf_064(&var_124);
            var_E0.unk_08->unk_1C0.sub_8A980(&dword_4AF030, (type_3D3548 *)this, 0, var_E0.unk_08->sub_CD550(), 0,
                                             0);
        }
    }
}

