// The levels in the level list by name, with "Any" (unk_505188, picked)
// when arg_0 is 1; the hook arg_4.
// match: ??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00211680
// match: __ehhandler$??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z-0x30 @ 0x00306B60
// match: __ehhandler$??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306B90
type_211680::type_211680(RwInt32 arg_0, type_1ED670_object *arg_4) : type_1FCDC0<type_211860_key>(0, arg_4)
{
    RwUInt32 lv_10;
    RwInt32 lv_14;

    lv_10 = dword_4FD970;
    for (lv_14 = 0; lv_14 != lv_10; lv_14++)
    {
        LEVELS_CHECK(lv_14);
        LEVELS_CHECK(lv_14);
        type_505188 *lv_18 = &dword_4FD974[lv_14];
        sub_1FCEB0(lv_18, type_1CB670(lv_18->sub_1A5F60().c_str(), 0));
    }
    if (arg_0 == 1)
    {
        sub_1FCEB0(&unk_505188, type_1CB670("Any", 0));
        sub_201EC0(&unk_505188);
    }
}

