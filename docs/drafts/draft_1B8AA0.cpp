// PARKED vf_068 (0x1B8AA0). Status: with two checks `if (!unk_2288) {}`
// after msg.unk_1C and `type_4F8054::get()->unk_B0->others()` the code up to
// the mask matches; inside the mask the image is one register on (it
// expands sub_1A8050 with its checks), and any check added to others()
// stops it being expanded. Same problem as sub_1ACBA0.
// 2026-09-28: a checked copy of get_unk_B0 (`r = unk_B0; if (!unk_B0) {}`)
// fixes the shift at the start of the mask; the one before the mask's copy
// into `mask` (dx not cx) is still missing: a check at the end of others()
// stops its expansion, the RwUInt16 conversion constructor adds a slot.

// An explosion's hit: the player's own hit (vf_068), then the health lost
// (a percentage, at most 100) sent to the other peers. Killed: the kill
// message, logged and shown ("MW_GEN_KILLS_YOUACCIDENT" for its own grenade,
// else "MW_GEN_KILLS_YOUGREN" with the thrower's name, who is told), counted,
// and when not hosting scored and its pickups dropped. Wounded: the wound
// message, logged.
// match: ?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z @ 0x001B8AA0
// match: __ehhandler$?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z-0xB @ 0x00302DB0
// match: __ehhandler$?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z @ 0x00302DBB
RwInt32 type_17DBD0_player::vf_068(type_758F0 *arg_0)
{
    if (unk_19DC > flt_3CD84C)
    {
        RwReal health = unk_19DC;

        type_10F710::vf_068(arg_0);
        RwReal lost = (health - unk_19DC) * unk_19E0;
        lost = sub_22C20(lost, 0.0f, 100.0f);
        if (unk_19DC <= flt_3CD84C)
        {
            RwChar text[0x100];
            type_3E1164 msg;
            RwInt32 thrower;

            msg.unk_04 = lost;
            msg.unk_08.unk_00 = arg_0->unk_0C->pos.x;
            msg.unk_08.unk_04 = arg_0->unk_0C->pos.y;
            msg.unk_08.unk_08 = arg_0->unk_0C->pos.z;
            msg.unk_14 = arg_0->unk_10;
            thrower = unk_4F7EB8.sub_1AF1B0(arg_0->unk_04.sub_D4910());
            if (thrower == -1)
                msg.unk_18 = (RwUInt8)unk_4F7EB8.sub_1AEC70();
            else
                msg.unk_18 = (RwUInt8)thrower;
            msg.unk_1C = unk_4F7EB8.sub_1AD730();
            type_1DDE20_mask mask = type_4F8054::get()->get_unk_B0()->others();
            type_4F8058::get()->sub_1DDDB0(&msg, mask);
            sub_1A8A70(&unk_4F7EB8, "Local player killed by grenade from player %d\n", msg.unk_18);
            if (msg.unk_18 == unk_4F7EB8.sub_1AEC70())
            {
                strcpy(text, sub_E3970("MW_GEN_KILLS_YOUACCIDENT", 1).c_str());
            }
            else
            {
                sub_1CB000(text, sub_E3970("MW_GEN_KILLS_YOUGREN", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[msg.unk_18].unk_00);
                unk_4F7EB8.sub_1ADB40(msg.unk_18);
            }
            sub_EACA0(text, 0, 0);
            dword_4F8288.sub_1C28F0(unk_4F7EB8.sub_1AEC70(), 1, 1);
            if (!unk_4F61F8.unk_104)
            {
                unk_4F7EBC.sub_1B2D00(unk_2288, unk_4F7EB8.sub_1AF1B0(arg_0->unk_04.sub_D4910()), 1);
                unk_4F7EB8.sub_1ADB80(msg.unk_1C, 0);
            }
        }
        else
        {
            type_1DDE20_mask mask2 = type_4F8054::get()->get_unk_B0()->others();
            type_3E1194 wound;

            wound.unk_04 = lost;
            wound.unk_08.unk_00 = arg_0->unk_0C->pos.x;
            wound.unk_08.unk_04 = arg_0->unk_0C->pos.y;
            wound.unk_08.unk_08 = arg_0->unk_0C->pos.z;
            wound.unk_14 = arg_0->unk_10;
            type_4F8058::get()->sub_1DDE90(&wound, mask2);
            sub_1A8A70(&unk_4F7EB8, "Local player wounded by grenade from player %d\n",
                       unk_4F7EB8.sub_1AF1B0(arg_0->unk_04.sub_D4910()));
        }
    }
    return 0;
}
