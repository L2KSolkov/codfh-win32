// match: ??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z @ 0x001FC320
// match: __ehhandler$??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z-0x15A @ 0x00304C60
// match: __ehhandler$??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z @ 0x00304DBA
type_1FC320::type_1FC320(type_1ED670_object *arg_0, type_1ED670_object *arg_4, type_1ED670_object *arg_8,
                         type_1ED670_object *arg_C)
    : unk_00(0x32, 0, 0x64, 5, 10, 10, 1, type_1CB670(), type_1CB670(), *sub_1CBAB0(), arg_4),
      unk_7C(0x32, 0, 0x64, 5, 10, 10, 1, type_1CB670(), type_1CB670(), *sub_1CBAB0(), arg_8),
      unk_F8(0, arg_0), unk_118(0, 0), unk_138(0, 0), unk_158(0, 0), unk_178(0, 0), unk_198(0, arg_C)
{
    unk_F8.sub_1FCEB0((type_1FCDC0_value)2, type_1CB670("5.1 Surround", 0));
    unk_F8.sub_1FCEB0((type_1FCDC0_value)1, type_1CB670("Stereo", 0));
    unk_F8.sub_1FCEB0((type_1FCDC0_value)0, type_1CB670("Mono", 0));
    unk_118.sub_1FCEB0((type_1FD050_value)0, type_1CB670("Normal", 0));
    unk_118.sub_1FCEB0((type_1FD050_value)1, type_1CB670("Slow", 0));
    unk_118.sub_1FCEB0((type_1FD050_value)2, type_1CB670("Fast", 0));
    unk_138.sub_1FCEB0((type_1FD1C0_value)0, type_1CB670("Off", 0));
    unk_138.sub_1FCEB0((type_1FD1C0_value)1, type_1CB670("On", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)0, type_1CB670("CTRL_STANDARD", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)1, type_1CB670("CTRL_LEFTY", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)2, type_1CB670("CTRL_HYBRID", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)3, type_1CB670("CTRL_SOLDIER", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)4, type_1CB670("CTRL_COMMANDO", 0));
    unk_178.sub_1FCEB0((type_1FD3A0_value)0, type_1CB670("On", 0));
    unk_178.sub_1FCEB0((type_1FD3A0_value)1, type_1CB670("Off", 0));
    unk_198.sub_1FCEB0((type_1FD490_value)0, type_1CB670("On", 0));
    get_unk_198()->sub_1FCEB0((type_1FD490_value)1, type_1CB670("Off", 0));
}

