/* Plays wave (NULL: stops), making the buffer when it has none or its 3D
 * use changes, and its format and mix bins when the wave's differ. */
// match: _sub_24F410 @ 0x0024F410
void
sub_24F410(rwaXboxVoice *obj, RwaWave *wave)
{
    rwaXboxVoiceState *state = &obj->state;
    RwBool      created;
    RwBool      is3D;
    RwBool      changed;
    rwaMixBins  mixBins;
    rwaWaveFormatEx pcm;
    rwaAdpcmWaveFormat adpcm;
    rwaBufferDesc desc;

    if (state->wave)
    {
        state->flags &= ~0x4000;
        state->wave = NULL;
    }
    if (!wave)
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
        return;
    }

    is3D = (wave->flags >> 1) & 1;
    created = FALSE;
    if (state->buffer && is3D != ((state->flags >> 5) & 1))
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
        IDirectSoundBuffer_Release(state->buffer);
        state->buffer = NULL;
    }
    if (!state->buffer)
    {
        rwaXboxOutputState *output = state->output;

        sub_24F380(&mixBins, output->speakerMode, is3D, 1);
        desc.size = sizeof(rwaBufferDesc);
        desc.flags = is3D ? 0x20010 : 0;
        desc.bufferBytes = 0;
        desc.format = unk_430660;
        desc.mixBins = &mixBins;
        desc.inputMixBin = 0;
        if (IDirectSound_CreateSoundBuffer(output->dsound, &desc, &state->buffer, NULL) < 0)
        {
            return;
        }
        if (IDirectSoundBuffer_SetBufferData(state->buffer, state->output->memory,
                                             state->output->memorySize) < 0)
        {
            IDirectSoundBuffer_Release(state->buffer);
            state->buffer = NULL;
            return;
        }
        created = TRUE;
    }

    changed = sub_24F350(&state->format, &wave->deviceFormat);
    if (changed && !created)
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
    }
    if (changed || created)
    {
        const RwaWaveFormat *format = &wave->deviceFormat;

        if (!RwaUUIDCompare(format->dataType, &unk_3ED5FC))
        {
            adpcm.wfx.channels = format->noChannels;
            adpcm.wfx.samplesPerSec = format->sampleRate;
            adpcm.wfx.formatTag = 0x69;
            adpcm.wfx.bitsPerSample = 4;
            adpcm.wfx.size = 2;
            adpcm.wfx.blockAlign = 36 * format->noChannels;
            adpcm.wfx.avgBytesPerSec = adpcm.wfx.samplesPerSec * adpcm.wfx.blockAlign / 64;
            adpcm.samplesPerBlock = 64;
            if (IDirectSoundBuffer_SetFormat(state->buffer, &adpcm) < 0)
            {
                IDirectSoundBuffer_Release(state->buffer);
                state->buffer = NULL;
                return;
            }
        }
        else
        {
            memset(&pcm, 0, sizeof(pcm));
            pcm.bitsPerSample = format->bitDepth;
            pcm.channels = format->noChannels;
            pcm.samplesPerSec = format->sampleRate;
            pcm.formatTag = 1;
            pcm.blockAlign = (pcm.bitsPerSample >> 3) * pcm.channels;
            pcm.avgBytesPerSec = pcm.blockAlign * pcm.samplesPerSec;
            if (IDirectSoundBuffer_SetFormat(state->buffer, &pcm) < 0)
            {
                IDirectSoundBuffer_Release(state->buffer);
                state->buffer = NULL;
                return;
            }
        }

        if (state->flags & 0x10000)
        {
            if (IDirectSoundBuffer_SetOutputBuffer(state->buffer,
                                                   state->target->state.buffer) < 0)
            {
                IDirectSoundBuffer_Release(state->buffer);
                state->buffer = NULL;
                return;
            }
        }
        else
        {
            sub_24F380(&mixBins, state->output->speakerMode, is3D, format->noChannels);
            if (state->noMixBins)
            {
                if (is3D)
                {
                    if (state->flags & 0x100000)
                    {
                        mixBins.count = state->noMixBins;
                        mixBins.levels = state->mixBins;
                    }
                }
                else if (state->flags & 0x80000)
                {
                    mixBins.count = state->noMixBins;
                    mixBins.levels = state->mixBins;
                }
            }
            memcpy(state->levels, mixBins.levels, mixBins.count * sizeof(rwaMixBinLevel));
            state->noLevels = mixBins.count;
            if (IDirectSoundBuffer_SetMixBins(state->buffer, &mixBins) < 0)
            {
                IDirectSoundBuffer_Release(state->buffer);
                state->buffer = NULL;
                return;
            }
        }
        state->format = wave->deviceFormat;
    }

    if (IDirectSoundBuffer_SetPlayRegion(state->buffer,
                                         sub_24DB60((RwUInt32)wave->buffer)
                                         - (RwUInt8 *)state->output->memory,
                                         wave->deviceFormat.length) >= 0
        && IDirectSoundBuffer_SetLoopRegion(state->buffer, 0, wave->deviceFormat.length) >= 0
        && IDirectSoundBuffer_SetCurrentPosition(state->buffer, 0) >= 0)
    {
        RwUInt32    headroom;

        if (state->flags & 0x400000)
        {
            headroom = state->headroom;
        }
        else if (is3D)
        {
            headroom = state->output->unk50;
        }
        else
        {
            headroom = state->output->unk54;
        }
        if (IDirectSoundBuffer_SetHeadroom(state->buffer, headroom) >= 0
            && sub_24ECC0(is3D, state))
        {
            state->flags |= 0x4000;
            state->wave = wave;
            return;
        }
    }

    IDirectSoundBuffer_Release(state->buffer);
    state->buffer = NULL;
}


/* Applies what changed: the 3D position (relative to the listener's
 * when head relative) and gain, frequency, volume, pan, play state, the
 * play position and the I3DL2 settings. */
// match: _sub_250340 @ 0x00250340
static rwaXboxVoice *
sub_250340(rwaXboxVoice *obj)
{
    if (obj->state.output->listener && (obj->state.flags & 0x20)
        && (obj->state.wave || (obj->state.flags & 0x68000))
        && ((obj->state.flags & 0x10)
            || (((rwaListener *)obj->state.output->listener)->dirty & 0xF)))
    {
        rwa3DSource source;
        RwReal      gains[6];

        source.maxDistance = sub_24F190(obj);
        source.minDistance = sub_24F160(obj);
        sub_24F0B0(obj, &source.position);
        sub_24F110(obj, &source.velocity);
        if (obj->state.flags & 8)
        {
            rwaListener *listener = (rwaListener *)obj->state.output->listener;
            RwaV3d      pos = listener->pos;
            RwaV3d      vel = listener->vel;

            source.position.x = pos.x + source.position.x;
            source.position.y = pos.y + source.position.y;
            source.position.z = pos.z + source.position.z;
            source.velocity.x = vel.x + source.velocity.x;
            source.velocity.y = vel.y + source.velocity.y;
            source.velocity.z = vel.z + source.velocity.z;
        }
        sub_23CD40(&obj->state.output->listener, 1, &source, gains,
                   obj->state.output->speakerMode);
        obj->state.gain = gains[0];
        obj->state.flags |= 0x100;
        if (obj->state.flags & 0x10)
        {
            IDirectSoundBuffer_SetAllParameters(obj->state.buffer, &obj->state.ds3d, 0);
            obj->state.flags &= ~0x10;
        }
    }

    if (obj->state.flags & 0x4000)
    {
        if (!(obj->state.flags & 0x80))
        {
            sub_24F1A0(obj, (RwReal)obj->state.wave->deviceFormat.sampleRate);
        }
        obj->state.flags &= ~0x4000;
    }
    if (obj->state.wave && (obj->state.flags & 0x80))
    {
        IDirectSoundBuffer_SetFrequency(obj->state.buffer, (RwInt32)obj->state.frequency);
        obj->state.flags &= ~0x80;
    }
    if ((obj->state.flags & 0x100) && (obj->state.wave || (obj->state.flags & 0x68000)))
    {
        IDirectSoundBuffer_SetVolume(obj->state.buffer,
                                     sub_241F90(obj->state.output->unk04 * obj->state.gain
                                                * obj->state.volume * 0.99936903f
                                                + 0.00063095737f));
        obj->state.flags &= ~0x100;
    }
    if ((obj->state.flags & 0x200) && obj->state.wave && !(obj->state.flags & 0x20))
    {
        RwReal      left;
        RwReal      right;
        rwaMixBins  mixBins;

        left = (obj->state.pan > 0.0f) ? 1.0f : obj->state.pan + 1.0f;
        right = (obj->state.pan < 0.0f) ? 1.0f : 1.0f - obj->state.pan;
        obj->state.levels[0].level = sub_241F90(right);
        obj->state.levels[1].level = sub_241F90(left);
        mixBins.count = obj->state.noLevels;
        mixBins.levels = obj->state.levels;
        IDirectSoundBuffer_SetMixBinVolumes(obj->state.buffer, &mixBins);
        obj->state.flags &= ~0x200;
    }

    if (sub_24ED90(obj->state.buffer))
    {
        IDirectSoundBuffer_GetCurrentPosition(obj->state.buffer, &obj->state.current, NULL);
    }
    else
    {
        obj->state.current = obj->state.start;
    }
    if (obj->state.wave)
    {
        if (obj->state.flags & 0x400)
        {
            if (obj->state.flags & 0x800)
            {
                IDirectSoundBuffer_SetCurrentPosition(obj->state.buffer, obj->state.start);
                if (IDirectSoundBuffer_Play(obj->state.buffer, 0, 0,
                                            (obj->state.flags >> 13) & 1) >= 0)
                {
                    obj->state.current = obj->state.start;
                    obj->state.start = 0;
                }
            }
            else
            {
                IDirectSoundBuffer_StopEx(obj->state.buffer, 0, 0, 0);
                obj->state.current = 0;
            }
            obj->state.flags &= ~0xC00;
        }
        if (!RwaUUIDCompare(obj->state.wave->format.dataType, &unk_3ED5FC))
        {
            obj->state.position = (obj->state.current / obj->state.wave->format.noChannels << 6)
                                  / 36;
        }
        else
        {
            obj->state.position = obj->state.current * 8
                                  / (obj->state.wave->format.bitDepth
                                     * obj->state.wave->format.noChannels);
        }
    }
    else
    {
        obj->state.position = 0;
    }

    obj->state.flags &= ~0x1000;
    if ((obj->state.flags & 0x40) && (obj->state.wave || (obj->state.flags & 0x68000)))
    {
        if ((obj->state.output->flags & 1) && (obj->state.flags & 0x200000))
        {
            rwaI3DL2Source source;

            source.direct = obj->state.direct;
            source.directHF = 0;
            source.room = obj->state.i3dl2.room;
            source.roomHF = obj->state.i3dl2.roomHF;
            source.roomRolloffFactor = obj->state.i3dl2.roomRolloffFactor;
            source.obstruction = obj->state.obstruction;
            source.obstructionLFRatio = obj->state.obstructionLFRatio;
            source.occlusion = obj->state.occlusion;
            source.occlusionLFRatio = obj->state.occlusionLFRatio;
            IDirectSoundBuffer_SetI3DL2Source(obj->state.buffer, &source, 0);
        }
        obj->state.flags &= ~0x40;
    }

    return obj;
}


/* Stops the buffer, waiting (up to timeout tries, or for ever) until it
 * has. */
// match: _sub_24EDC0 @ 0x0024EDC0
static RwBool
sub_24EDC0(void *buffer, RwUInt32 timeout)
{
    RwBool      result = TRUE;

    if (buffer && sub_24ED90(buffer))
    {
        RwUInt32    tries = 0;
        RwUInt32    status;

        IDirectSoundBuffer_StopEx(buffer, 0, 0, 0);
        result = FALSE;
        do
        {
            if (timeout < (RwUInt32)-1)
            {
                tries++;
            }
            Sleep(0);
            IDirectSoundBuffer_GetStatus(buffer, &status);
            if (!(status & 1))
            {
                result = TRUE;
                IDirectSoundBuffer_SetOutputBuffer(buffer, NULL);
                break;
            }
        }
        while (tries <= timeout);
    }

    return result;
}


/* Whether the buffer must change format. */
// match: _sub_24F350 @ 0x0024F350
static RwBool
sub_24F350(const RwaWaveFormat *current, const RwaWaveFormat *format)
{
    if (format->noChannels != current->noChannels || format->dataType != current->dataType
        || format->bitDepth != current->bitDepth)
    {
        return TRUE;
    }

    return FALSE;
}

