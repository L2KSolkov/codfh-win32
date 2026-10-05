// match: ?sub_1A2A80@@YAXM@Z @ 0x001A2A80
// match: __ehhandler$?sub_1A2A80@@YAXM@Z-0x11 @ 0x003027E0
// match: __ehhandler$?sub_1A2A80@@YAXM@Z @ 0x003027F1
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The network's step by arg_0: the multiplayer manager's step; then, where
// the in-game warnings screen exists, the lost connection's warning: shown
// ("NO_NETWORK_CONNECTION" while the voice runs, else
// "NO_SYSTEMLINK_CONNECTION"; a client tells the others, then the manager
// ends the game) once the network game reports it, hidden again (going back
// to the game) once it no longer does.
void sub_1A2A80(RwReal arg_0)
{
    unk_4F7EB8.sub_1AAB50(arg_0);
    if (type_215740::sub_215A50())
    {
        RwInt32 m_18;
        type_4F8054 *ebp_14;
        bool bp_D;

        ebp_14 = dword_4F8054;
        m_18 = sub_1CCA10().get_unk_00();
        bp_D = true;
        if (ebp_14 && ebp_14->vf_050())
            bp_D = false;
        if (type_215740::sub_215910(&dword_5051D0))
        {
            dword_4CF410 = 1;
            if (!bp_D)
            {
                type_215740::sub_2156B0(&dword_5051D0);
                sub_1C44A0();
            }
        }
        else if (bp_D && !dword_4FB9E0.get_unk_C8() && type_215740::sub_2155A0(&dword_5051D0))
        {
            if (sub_1D8810()->voice_running())
                type_215740::sub_215970(type_1A5EA0("NO_NETWORK_CONNECTION", 0), &dword_5051D0);
            else
                type_215740::sub_215970(type_1A5EA0("NO_SYSTEMLINK_CONNECTION", 0), &dword_5051D0);
            if (!dword_4F62FC)
            {
                type_1DDE20_mask var_20;
                type_3E0EB8 l1C;

                var_20 = type_4F8054::get()->get_unk_B0()->others();
                type_4F8058::get()->sub_1DDDB0(&l1C, var_20);
            }
            unk_4F7EB8.sub_1AF6F0();
        }
    }
}
