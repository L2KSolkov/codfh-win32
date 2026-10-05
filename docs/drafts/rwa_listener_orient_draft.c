// match: _sub_23D2A0 @ 0x0023D2A0
rwaListener *
sub_23D2A0(rwaListener *listener, const RwaUUID *param, const RwaV3d *value)
{
    listener->up = *value;
    listener->right.x = listener->up.y * listener->at.z - listener->up.z * listener->at.y;
    listener->right.y = listener->at.x * listener->up.z - listener->at.z * listener->up.x;
    listener->right.z = listener->up.x * listener->at.y - listener->up.y * listener->at.x;
    listener->dirty |= 8;

    return listener;
}

// match: _sub_23D320 @ 0x0023D320
rwaListener *
sub_23D320(rwaListener *listener, const RwaUUID *param, const RwaV3d *value)
{
    listener->at = *value;
    listener->right.x = listener->up.y * listener->at.z - listener->up.z * listener->at.y;
    listener->right.y = listener->at.x * listener->up.z - listener->up.x * listener->at.z;
    listener->right.z = listener->up.x * listener->at.y - listener->up.y * listener->at.x;
    listener->dirty |= 4;

    return listener;
}

extern const RwReal flt_3CD84C;

// match: _sub_23CC70 @ 0x0023CC70
rwaListener *
sub_23CC70(rwaListener *listener)
{
    RwaV3d  v;

    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    listener->pos = v;
    listener->vel = v;

    v.x = 0.0f;
    v.z = 0.0f;
    listener->at.x = 0.0f;
    listener->at.y = 0.0f;
    v.y = 1.0f;
    listener->up = v;
    listener->at.z = 1.0f;

    listener->right.x = listener->up.y - listener->up.z * flt_3CD84C;
    listener->right.y = listener->up.z * flt_3CD84C - listener->up.x;
    listener->right.z = listener->up.x * flt_3CD84C - listener->up.y * flt_3CD84C;

    listener->unk68 = 0x3F800000;
    listener->unk6C = 0x3F800000;
    listener->unk64 = 0x41200000;
    listener->dirty = 0x7B;

    return listener;
}

