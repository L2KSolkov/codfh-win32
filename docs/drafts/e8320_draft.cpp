// Reads the texture dictionary arg_0 (a level path, sub_D7F20); 0 when it
// will not open or holds none.
// match: ?sub_E8320@@YAPAURwTexDictionary@@PBD@Z @ 0x000E8320
RwTexDictionary *sub_E8320(const RwChar *arg_0)
{
    RwChar var_210[0x200];
    RwTexDictionary *var8;
    RwStream *l4;

    l4 = 0;
    var8 = 0;
    sub_D7F20(var_210, arg_0);
    sub_19A750("Loading HUD Texture Dictionary file from: %s...", var_210);
    l4 = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_210);
    if (l4)
    {
        if (RwStreamFindChunk(l4, rwID_TEXDICTIONARY, 0, 0))
        {
            var8 = RwTexDictionaryStreamRead(l4, 0);
        }
        RwStreamClose(l4, 0);
    }
    return var8;
}

