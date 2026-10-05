// "Yes" (1) and "No" (0), with "Any" (2) when arg_0 is 1; picks arg_4; the
// hook arg_8.
// match: ??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00214A90
// match: __ehhandler$??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x23 @ 0x00306ED0
// match: __ehhandler$??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306EF3
type_214A90::type_214A90(RwInt32 arg_0, type_214C30_value arg_4, type_1ED670_object *arg_8) : type_1FCDC0<type_214C30_value>(0, arg_8)
{
    sub_1FCEB0((type_214C30_value)1, type_1CB670("Yes", 0));
    sub_1FCEB0((type_214C30_value)0, type_1CB670("No", 0));
    if (arg_0 == 1)
        sub_1FCEB0((type_214C30_value)2, type_1CB670("Any", 0));
    sub_201EC0(arg_4);
}

// Its deleting destructor, over the implicit destructor the host options'
// unit defines (0x201370).
// match: ??_Gtype_214A90@@UAEPAXI@Z @ 0x00214C00

