// Historical draft, superseded by the exact match in
// src/recovered/unit_08AB60.cpp (2026-10-02).
// match: ?sub_8AFF0@@YAHHPAUtype_8AFF0_node@@PAUtype_8AEB0@@@Z @ 0x0008AFF0
// The pick of the slot arg_8 (answering the slot kind arg_0) among the
// trackers from arg_4: a random free one with room, or else the one it last
// picked if that has room; takes it (a round's use), marks its child entity
// picked and returns 1, or 0 when there is none or it has no child.
RwInt32 sub_8AFF0(RwInt32 arg_0, type_8AFF0_node *arg_4, type_8AEB0 *arg_8)
{
    RwInt32 lv_4;
    type_8AFF0_node *lv_8;
    type_8AFF0_node *lv_c;
    type_8AFF0_node *lv_1a0[100];
    type_8AFF0_node *lv_1a4;
    RwUInt32 lv_1a8;
    type_3D3548 *lv_1ac;

    lv_c = 0;
    lv_8 = 0;
    lv_4 = 0;
    for (lv_1a4 = arg_4; lv_1a4 != 0; lv_1a4 = lv_1a4->unk_0C) {
        if (lv_1a4->unk_00->vf_024() != arg_0)
            continue;
        if (lv_1a4->unk_08 != 0)
            continue;
        if (lv_1a4->unk_00 == arg_8->unk_00) {
            lv_c = lv_1a4;
            continue;
        }
        if (lv_1a4->unk_00->vf_00C() > lv_1a4->unk_04) {
            lv_1a0[lv_4] = lv_1a4;
            lv_4++;
        }
    }
    if (lv_4 == 0) {
        if (lv_c != 0 && lv_c->unk_00->vf_00C() > lv_c->unk_04)
            lv_8 = lv_c;
    } else {
        lv_1a8 = RpRandom() % (0, lv_4);
        lv_8 = lv_1a0[lv_1a8];
    }
    if (lv_8 != 0) {
        lv_1ac = lv_8->unk_00->vf_020();
        if (lv_1ac != 0) {
            lv_8->unk_04++;
            lv_8->unk_08 = 1;
            arg_8->unk_00 = lv_8->unk_00;
            lv_1ac->unk_88_8 = 1;
            return 1;
        }
    }
    return 0;
}
