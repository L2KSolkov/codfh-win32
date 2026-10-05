extern void sub_242050(RwReal *length, const RwaV3d *vector);
extern RwReal RwV3dNormalize(RwaV3d *out, const RwaV3d *in);

// match: _sub_23CD40 @ 0x0023CD40
void
sub_23CD40(rwaListener **listeners, RwUInt32 count,
           const rwa3DSource *source, RwReal *gains, RwUInt32 mode)
{
    rwaListener *listener = *listeners;
    RwReal doppler = *(RwReal *)&listener->unk6C;
    RwReal velocityScale = *(RwReal *)&listener->unk68;
    RwReal rolloff = *(RwReal *)&listener->unk64;
    RwaV3d direction, previousDirection;
    RwaV3d listenerPrevious, sourcePrevious;
    RwReal distance, previousDistance;
    RwReal delta, speed;
    const RwaV3d *at = &listener->at;

    listenerPrevious.x = listener->pos.x - listener->vel.x;
    listenerPrevious.y = listener->pos.y - listener->vel.y;
    listenerPrevious.z = listener->pos.z - listener->vel.z;
    sourcePrevious.x = source->position.x - source->velocity.x;
    sourcePrevious.y = source->position.y - source->velocity.y;
    sourcePrevious.z = source->position.z - source->velocity.z;
    previousDirection.x = sourcePrevious.x - listenerPrevious.x;
    previousDirection.y = sourcePrevious.y - listenerPrevious.y;
    previousDirection.z = sourcePrevious.z - listenerPrevious.z;
    sub_242050(&previousDistance, &previousDirection);

    direction.x = source->position.x - listener->pos.x;
    direction.y = source->position.y - listener->pos.y;
    direction.z = source->position.z - listener->pos.z;
    sub_242050(&distance, &direction);
    delta = distance - previousDistance;
    if(delta > 150.0f)delta = 150.0f;
    else if(delta < -150.0f)delta = -150.0f;
    speed = doppler * 340.0f;
    gains[1] = (speed - delta * velocityScale) / speed;
    if(distance > source->maxDistance)gains[0] = 0.0f;
    else if(distance < source->minDistance)gains[0] = 1.0f;
    else
    {
        RwReal range;
        distance -= source->minDistance;
        range = source->maxDistance - source->minDistance;
        gains[0] = (range - distance) / (distance * rolloff + range);
    }

    if(direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f)
        direction = *at;
    else RwV3dNormalize(&direction, &direction);
    if(previousDirection.x == 0.0f && previousDirection.y == 0.0f && previousDirection.z == 0.0f)
        previousDirection = *at;
    else RwV3dNormalize(&previousDirection, &previousDirection);

    gains[2] = 0.5f - (direction.x * listener->right.x + direction.y * listener->right.y + direction.z * listener->right.z) * 0.5f;
    if(gains[2] < 0.0f)gains[2] = 0.0f;
    else if(gains[2] > 1.0f)gains[2] = 1.0f;
    gains[3] = 0.5f - (direction.x * at->x + direction.y * at->y + direction.z * at->z) * 0.5f;
    if(gains[3] < 0.0f)gains[3] = 0.0f;
    else if(gains[3] > 1.0f)gains[3] = 1.0f;
    gains[4] = 0.5f - (previousDirection.x * listener->right.x + previousDirection.y * listener->right.y + previousDirection.z * listener->right.z) * 0.5f;
    if(gains[4] < 0.0f)gains[4] = 0.0f;
    else if(gains[4] > 1.0f)gains[4] = 1.0f;
    gains[5] = 0.5f - (previousDirection.x * at->x + previousDirection.y * at->y + previousDirection.z * at->z) * 0.5f;
    if(gains[5] < 0.0f)gains[5] = 0.0f;
    else if(gains[5] > 1.0f)gains[5] = 1.0f;
    switch(mode)
    {
    case 2:
        gains[2] -= 0.5f;
        gains[4] -= 0.5f;
        gains[2] *= 0.0f;
        gains[4] *= 0.0f;
        gains[2] += 0.5f;
        gains[4] += 0.5f;
        break;
    case 3:
        gains[2] -= 0.5f;
        gains[4] -= 0.5f;
        gains[2] *= 0.5f;
        gains[4] *= 0.5f;
        gains[2] += 0.5f;
        gains[4] += 0.5f;
        break;
    }
}
