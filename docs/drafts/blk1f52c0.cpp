// match: ?sub_1F52C0@type_3E7BCC@kujuUI@@QAEXI@Z @ 0x001F52C0
void type_3E7BCC::sub_1F52C0(RwUInt32 arg_0)
{
    if (arg_0 == 0x1B)
    {
        if (unk_EC && unk_EC->pvf_00C())
            unk_EC->pvf_008();
    }
    else if (arg_0 < 0x20)
        ;
    else if (arg_0 < 0x10000 && arg_0 != 0x22B2 && arg_0 != 0x22B3)
    {
        if (sub_1F5230().size() < (RwUInt32)unk_B8)
        {
            type_1A5EA0 var_2C(sub_1F5230());
            var_2C.sub_1C8300(unk_E4, (RwChar)arg_0);
            if ((RwReal)unk_1C.sub_1F1ED0(var_2C.c_str(), -1) < static_cast<type_3E76B4 *>(this)->pvf_004()->width())
            {
                sub_1F51B0(var_2C.c_str());
                ++unk_E4;
                if (unk_E4 > var_2C.size())
                    unk_E4 = var_2C.size();
                sub_1F5070();
            }
        }
    }
    else
    {
        switch (arg_0)
        {
        case 0x10000:
            if (unk_E4 > 0)
            {
                --unk_E4;
                type_1A5EA0 var_48(sub_1F5230());
                var_48.sub_1C8330(unk_E4, 1);
                sub_1F51B0(var_48.c_str());
                sub_1F5070();
            }
            break;
        case 0x10001:
            if (sub_1F5230().size() > 0)
            {
                type_1A5EA0 var_64(sub_1F5230());
                var_64.sub_1C8330(unk_E4, 1);
                sub_1F51B0(var_64.c_str());
                sub_1F5070();
            }
            break;
        case 0x22B2:
            if (unk_E4 > 0)
            {
                --unk_E4;
                sub_1F5070();
            }
            break;
        case 0x22B3:
            if (unk_E4 < sub_1F5230().size())
            {
                ++unk_E4;
                sub_1F5070();
            }
            break;
        case 0x1000B:
            if (unk_E8 && unk_E8->pvf_00C())
                unk_E8->pvf_008();
            break;
        }
    }
}

