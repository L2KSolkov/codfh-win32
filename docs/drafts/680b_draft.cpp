// "4", "8" and "16" players (1, 2 and 4), with "Any" (8, picked) when arg_0
// is 1; the hook arg_4.
// match: ??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00213680
// match: __ehhandler$??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z-0x2E @ 0x00306DB0
// match: __ehhandler$??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306DDE
type_213680::type_213680(RwInt32 arg_0, type_1ED670_object *arg_4) : type_1FCDC0<type_2138C0_value>(0, arg_4)
{
    sub_1FCEB0((type_2138C0_value)1, sub_1CB720("4"));
    sub_1FCEB0((type_2138C0_value)2, sub_1CB720("8"));
    sub_1FCEB0((type_2138C0_value)4, sub_1CB720("16"));
    if (arg_0 == 1)
    {
        sub_1FCEB0((type_2138C0_value)8, type_1CB670("Any", 0));
        sub_201EC0((type_2138C0_value)8);
    }
}

