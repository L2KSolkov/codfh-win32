
// match: ?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z @ 0x0014C820
// match: __ehhandler$?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z-0x11 @ 0x00301CE0
// match: __ehhandler$?sub_14C820@@YAPAUtype_3DBC78@@PAUtype_712B0@@@Z @ 0x00301CF1
// Builds the vehicle for the trigger arg_0, or warns that there is no
// entity memory for it.
type_3DBC78 *sub_14C820(type_712B0 *arg_0)
{
    type_3DBC78 *var_10;

    var_10 = (type_3DBC78 *)sub_D56D0(0x2860, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_3DBC78(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   trigger_pos(arg_0)->x, trigger_pos(arg_0)->y, trigger_pos(arg_0)->z);
    }
    return var_10;
}
