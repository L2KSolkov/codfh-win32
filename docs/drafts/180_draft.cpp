// The game types (1, 2, 4 and 8) by name, with 0x20 (picked) when arg_0 is
// 1; the hook arg_4.
// match: ??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00210180
// match: __ehhandler$??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z-0x39 @ 0x00306A30
// match: __ehhandler$??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306A69
type_210180::type_210180(RwInt32 arg_0, type_1ED670_object *arg_4) : type_1FCDC0<type_210430_value>(0, arg_4)
{
    sub_1FCEB0((type_210430_value)1, type_1CB670(sub_1C4E60(1), 0));
    sub_1FCEB0((type_210430_value)2, type_1CB670(sub_1C4E60(2), 0));
    sub_1FCEB0((type_210430_value)4, type_1CB670(sub_1C4E60(4), 0));
    sub_1FCEB0((type_210430_value)8, type_1CB670(sub_1C4E60(8), 0));
    if (arg_0 == 1)
    {
        sub_1FCEB0((type_210430_value)0x20, type_1CB670(sub_1C4E60(0x20), 0));
        sub_201EC0((type_210430_value)0x20);
    }
}

