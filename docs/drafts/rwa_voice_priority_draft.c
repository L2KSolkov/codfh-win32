// match: _sub_23E8E0 @ 0x0023E8E0
static void
sub_23E8E0(rwaSound *sound)
{
    if (sound->flags & 1)
    {
        RwaObjHandle   *handle;

        sound->prev->next = sound->next;
        sound->next->prev = sound->prev;

        handle = sound->handle;
        if (handle)
        {
            RwaObjHandleSetParamUInt8(handle, 6, 1, 0);
            sub_23F940(handle, 9, 1, NULL);
            sound->handle = NULL;
        }

        rwaVoiceLink(sound)->next = dword_5069C8.next;
        rwaVoiceLink(sound)->prev = &dword_5069C8;
        dword_5069C8.next->prev = rwaVoiceLink(sound);
        dword_5069C8.next = rwaVoiceLink(sound);

        dword_5069E4--;
        dword_5069E8 -= sound->unk38;
        sound->unk48 = sound->unk4C;
        sound->flags &= ~3;
        sound->unk80 = 0;
        sound->unk38 = 0;
    }
}

#define rwaReal(_field) (*(RwReal *)&(_field))

// match: _sub_23E980 @ 0x0023E980
static void
sub_23E980(rwaSound *sound)
{
    rwaReal(sound->unk80) = 0.0f;

    if (rwaReal(sound->unk40) > 0.0f)
    {
        RwReal  volume;

        if (((rwaVoiceWave *)sound->unk50)->flags & 2)
        {
            RwReal  maxDistance = rwaReal(sound->unk74);
            RwReal  minDistance = rwaReal(sound->unk70);
            RwReal  dx, dy, dz;
            RwReal  distance;

            dx = dword_5069EC.x - sound->unk58.x;
            dy = dword_5069EC.y - sound->unk58.y;
            dz = dword_5069EC.z - sound->unk58.z;
            distance = dx * dx + dy * dy + dz * dz;

            if (!(maxDistance * maxDistance > distance))
            {
                goto prioritised;
            }

            rwaSqrtMacro(&distance, distance);

            if (distance > minDistance)
            {
                RwReal  beyond = distance - minDistance;
                RwReal  range = maxDistance - minDistance;

                volume = (range - beyond) / (dword_42E6D8 * beyond + range) * rwaReal(sound->unk40);
                if (!(volume > 0.0f))
                {
                    goto prioritised;
                }
            }
            else
            {
                volume = 1.0f;
            }
        }
        else
        {
            volume = 1.0f;
        }

        rwaReal(sound->unk80) = (1.0f - rwaReal(sound->unk7C)) * volume +
                                rwaReal(sound->unk78) * rwaReal(sound->unk7C);
    }

prioritised:
    if (sound->flags & 1)
    {
        RwReal      priority = rwaReal(sound->unk80);
        rwaSound   *node = sound;

        for (;;)
        {
            rwaSound   *next = node->next;
            rwaSound   *prev = node->prev;
            RwReal      nextPriority;
            RwReal      prevPriority;

            nextPriority = (rwaLink *)next == &dword_5069C0 ? flt_3CDC78 : rwaReal(next->unk80);
            prevPriority = (rwaLink *)prev == &dword_5069C0 ? -1.0f : rwaReal(prev->unk80);

            if (priority > nextPriority)
            {
                node = next;
            }
            else if (priority < prevPriority)
            {
                node = prev;
            }
            else
            {
                break;
            }
        }

        if (node != sound)
        {
            sound->prev->next = sound->next;
            sound->next->prev = sound->prev;
            sound->prev = node->prev;
            sound->next = node;
            node->prev->next = sound;
            node->prev = sound;
        }

        sound->flags |= 1;
    }
    else
    {
        rwaLink    *cur;

        sound->prev->next = sound->next;
        sound->next->prev = sound->prev;

        for (cur = dword_5069C0.next; cur != &dword_5069C0; cur = cur->next)
        {
            if (rwaReal(sound->unk80) < rwaReal(((rwaSound *)cur)->unk80))
            {
                break;
            }
        }

        if (cur != &dword_5069C0)
        {
            sound->prev = (rwaSound *)cur->prev;
            sound->next = (rwaSound *)cur;
            cur->prev->next = rwaVoiceLink(sound);
            cur->prev = rwaVoiceLink(sound);
        }
        else
        {
            sound->prev = (rwaSound *)dword_5069C0.prev;
            sound->next = (rwaSound *)&dword_5069C0;
            dword_5069C0.prev->next = rwaVoiceLink(sound);
            dword_5069C0.prev = rwaVoiceLink(sound);
        }

        sound->flags |= 1;
    }
}

// match: _sub_23EE70 @ 0x0023EE70
static void
sub_23EE70(rwaSound *sound)
{
    if (sound->flags & 1)
    {
        sub_23E8E0(sound);
    }

    sub_23E980(sound);

    sound->unk38 = 1;
    sound->flags |= 2;
    sound->unk4C = 0;
    dword_5069E8++;
    dword_5069E4++;
}

// match: _SoundStopper_Transition @ 0x0023EEC0
void
SoundStopper_Transition(rwaSound *sound, RwInt32 state)
{
    switch (state)
    {
        case 0:
            sub_23EE70(sound);
            break;
        case 1:
            sub_23E8E0(sound);
            break;
        case 2:
            if (sound->flags & 1)
            {
                sub_23E980(sound);
            }
            break;
    }
}
