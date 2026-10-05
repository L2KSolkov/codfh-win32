// match: sub_1403D0 @ 0x001403D0
// Sets the line *arg_0's end arg_4 from its start, keeping its direction
// in x and y (z is left as it is).
void sub_1403D0(RwLine *arg_0, RwReal arg_4)
{
    RwV3d var_C;

    var_C.x = arg_0->end.x - arg_0->start.x;
    var_C.y = arg_0->end.y - arg_0->start.y;
    RwV3dNormalize(&var_C, &var_C);
    var_C.x *= arg_4;
    var_C.y *= arg_4;
    arg_0->end.x = var_C.x + arg_0->start.x;
    arg_0->end.y = var_C.y + arg_0->start.y;
}
