// match: ?sub_2016A0@type_200B90@@QAEXXZ @ 0x002016A0
void type_200B90::sub_2016A0()
{
    if (unk_32C.sub_1FD030() == 8)
    {
        if (unk_194.sub_1FD030() == 0)
        {
            RwUInt32 var_10 = 5;
            unk_194.sub_201EC0(var_10);
            byte_5044E0 = 1;
        }
        RwUInt32 var_14 = 0;
        unk_194.sub_202350(var_14);
    }
    else
    {
        RwUInt32 var_18 = 0;
        if (!unk_194.sub_203CA0(var_18))
        {
            RwUInt32 var_38 = 0;
            unk_194.sub_1FCEB0(var_38, type_1CB670("No limit", 0));
            if (byte_5044E0)
            {
                RwUInt32 var_3C = 0;
                unk_194.sub_201EC0(var_3C);
                byte_5044E0 = 0;
            }
        }
    }
    vf_00();
}

// match: ?sub_201890@type_200B90@@QAEXXZ @ 0x00201890
void type_200B90::sub_201890()
{
    type_211860_key var_10(sub_1C4BC0());

    unk_D8.sub_201EC0(var_10);
    unk_90.sub_1F28C0(sub_1CB720(sub_1C4320()));
    unk_32C.sub_201EC0((type_210430_value)unk_4FDBB0.unk_00);
    unk_174.sub_201EC0((type_2138C0_value)dword_4F6300);
    unk_194.sub_201EC0((RwUInt32)(unk_4FDBB0.unk_14 / 60.0f));
    RwUInt32 var_14 = unk_4FDBB0.unk_18;
    if (var_14 > 100)
        var_14 = 0;
    unk_1B4.sub_1E7BB0(var_14);
    unk_2AC.sub_201EC0((type_212C70_value)unk_4FDBB0.unk_24);
    unk_2EC.sub_201EC0((type_214C30_value)(unk_4FDBB0.unk_08 != 0));
    unk_30C.sub_201EC0((type_214C30_value)(unk_4FDBB0.unk_0C != 0));
    unk_230.sub_1E7BB0((RwInt32)unk_4FDBB0.unk_2C);
    unk_2CC.sub_201EC0((type_214C30_value)(unk_4FDBB0.unk_10 != 0));
    unk_F8.sub_1E7BB0(dword_4FDAA4);
}


template <class T> void type_1FCDC0<T>::sub_1FCEB0(const T &arg_0, const type_1CB670 &arg_4)
{
    if (!sub_203CA0(arg_0))
    {
        std::pair<T, type_1CB670> var_30(arg_0, arg_4);
        if (unk_14 == unk_08.end())
        {
            unk_14 = unk_08.insert(var_30).first;
            vf_014();
        }
        else
        {
            unk_08.insert(var_30);
        }
    }
}

template <class T> void type_1FCDC0<T>::sub_202350(const T &arg_0)
{
    if (sub_203CA0(arg_0))
    {
        typename map_type::iterator var_4 = unk_08.find(arg_0);
        if (var_4 == unk_14)
        {
            unk_14 = unk_08.begin();
            sub_2251F0();
        }
        unk_08.erase(var_4);
    }
}

