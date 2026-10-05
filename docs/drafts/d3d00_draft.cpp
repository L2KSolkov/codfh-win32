// Its picture and hint for the weapon class arg_0: the look for the class
// and team shown (while the looks are loaded), and the class's text with its
// grenades.
// match: ?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z @ 0x00223D00
// match: __ehhandler$?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z-0x28 @ 0x00308DA0
// match: __ehhandler$?sub_223D00@type_223280@@QAEXW4type_224010_value@@@Z @ 0x00308DC8
void type_223280::sub_223D00(type_224010_value arg_0)
{
    unk_18C = arg_0;
    if (!unk_194[0].sub_E87C0() && unk_18C >= 0 && unk_18C <= 3)
    {
        RwInt32 lv_6C = 0;

        if (unk_190 == 4)
            lv_6C = 1;
        unk_184.sub_1E7510(unk_19C[lv_6C][unk_18C]);
    }
    type_1CB670 lv_68 = sub_1C43C0(unk_190, unk_18C);
    RwInt32 lv_4C = sub_1AF2C0(arg_0);
    type_1CB670 lv_48;

    lv_48.sub_202430(lv_4C);
    type_1CB670 lv_2C = sub_1CB7B0("Grenades: %1", lv_48.c_str(), 0);

    lv_68.sub_1FBB90(*sub_1CB9B0()).sub_1FBB90(*sub_1CB9B0()).sub_1FBB90(lv_2C);
    unk_1E8.sub_1F28C0(lv_68);
}

