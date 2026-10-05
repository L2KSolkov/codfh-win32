// "Respawn" and "Last Man Standing", with "Any" (picked) when arg_0 is 1;
// the hook arg_4.
// match: ??0type_20EE00@@QAE@HH@Z @ 0x0020EE00
// match: __ehhandler$??0type_20EE00@@QAE@HH@Z-0x23 @ 0x00306920
// match: __ehhandler$??0type_20EE00@@QAE@HH@Z @ 0x00306943
type_20EE00::type_20EE00(RwInt32 arg_0, RwInt32 arg_4) : type_1FCDC0<type_20EFD0_value>(0, (type_1ED670_object *)arg_4)
{
    sub_1FCEB0((type_20EFD0_value)1, type_1CB670("Respawn", 0));
    sub_1FCEB0((type_20EFD0_value)2, type_1CB670("Last Man Standing", 0));
    if (arg_0 == 1)
    {
        sub_1FCEB0((type_20EFD0_value)4, type_1CB670("Any", 0));
        sub_201EC0((type_20EFD0_value)4);
    }
}

