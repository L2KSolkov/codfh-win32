/* Unmatched wave setter follow-up, VC7.1. The two static helpers match
 * only alongside the caller; the caller is still binary. Build/insert using
 * rwa_voice_wave_shape_trials.py, variant vws_12. */
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

/* The default mix bins of a 3D buffer or one of the channels. */
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
        RwUInt32 flags = state->flags & ~0x4000;
        state->wave = NULL;
        state->flags = flags;
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
    if (!changed)
    {
        if (!created) goto set_region;
    }
    else if (!created)
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
    }
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

set_region:
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
