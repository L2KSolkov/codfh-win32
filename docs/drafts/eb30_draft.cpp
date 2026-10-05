// Built over the layout arg_8 in the pause menu arg_C: by teams when arg_0 is
// set, arg_4 kept in unk_154; its widgets registered by name (the teams'
// flags, names and round scores only by teams, the round scores cleared in
// game type 4) and its layout loaded.
// match: ??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z @ 0x0021EB30
// match: __ehhandler$??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z-0x11E @ 0x00308280
// match: __ehhandler$??0type_21EB30@@QAE@_NHPBDPAUtype_21A5E0@@@Z @ 0x0030839E
// match: ??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ @ 0x0021EFC0
// match: __ehhandler$??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ-0x8 @ 0x003083B0
// match: __ehhandler$??_F?$type_E8780@Utype_1ECCE0@kujuUI@@@@QAEXXZ @ 0x003083B8
type_21EB30::type_21EB30(bool arg_0, RwInt32 arg_4, const RwChar *arg_8, type_21A5E0 *arg_C)
    : type_21CB10(arg_8, arg_C, 0), unk_154(arg_4), unk_158(this, &type_21EB30::sub_220A80), unk_39C(arg_0),
      unk_39D(false), unk_3A0(1), unk_3A4(1)
{
    RwInt32 lv_10;

    for (lv_10 = 0; lv_10 < 2; lv_10++)
    {
        unk_174[lv_10] = 0;
        unk_17C[lv_10] = 0;
    }
    sub_204FC0("continue", &unk_158);
    sub_204FC0("leftnames", &unk_1D4);
    sub_204FC0("rightnames", &unk_1F0);
    sub_204FC0("LeftRoundTotal", &unk_25C);
    sub_204FC0("RightRoundTotal", &unk_284);
    sub_204FC0("HeaderText", &unk_2FC);
    sub_204FC0("CentreText", &unk_324);
    sub_204FC0("AboveCentreText", &unk_34C);
    sub_204FC0("BestPlayerText", &unk_374);
    if (get_unk_39C())
    {
        sub_204FC0("LeftFlag", &unk_164);
        sub_204FC0("RightFlag", &unk_16C);
        sub_204FC0("LeftTeamName", &unk_184);
        sub_204FC0("RightTeamName", &unk_1AC);
        sub_204FC0("LeftRoundScore", &unk_2AC);
        sub_204FC0("RightRoundScore", &unk_2D4);
        if (dword_4FB9E0.get_unk_08() == 4)
        {
            unk_2AC.sub_1F28C0(type_1CB670());
            unk_2D4.sub_1F28C0(type_1CB670());
        }
    }
    else
    {
        sub_204FC0("LeftFlag", &unk_164);
    }
    sub_20EA40();
}

