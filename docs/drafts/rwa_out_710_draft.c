// match: _sub_24E710 @ 0x0024E710
static void
sub_24E710(rwaXboxOutput *obj, void *a, void *b)
{
    rwaXboxOutputState *state = (rwaXboxOutputState *)obj->inst.state;
    RwaV3d      zero;

    sub_24E180(obj, NULL);
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    sub_24DF00();
    IDirectSound_Release(state->dsound);
    if (!(state->flags & 0x10) && state->memory)
    {
        sub_2421B0(state->memory);
        state->memory = NULL;
        state->memorySize = 0;
    }
}

