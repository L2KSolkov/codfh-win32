/*
 * The audio bridge (docs/WIN32_PORT.md W5): the Xbox DirectSound calls RenderWare Audio's Xbox
 * layer (src/rwa/xbox) and the game make, with the signatures they declare them with, over a
 * software mixer feeding one XAudio2 voice (48 kHz stereo, 10 ms blocks from a mixer thread).
 *
 * Each buffer plays its data (the shared output memory RenderWare Audio hands every voice, with a
 * play and a loop region) at its frequency: PCM 8/16 or Xbox ADPCM (36 bytes per channel per 64
 * samples, IMA steps), resampled linearly. Its volume and mix-bin levels are hundredths of a dB.
 * 2D voices go out through mix bins 0-5 (front, centre, back: folded to stereo); 3D voices are
 * attenuated by distance (inverse, with the rolloff factor; by the buffer's rolloff curve when it
 * has one) and panned from their position relative to the listener. A voice routed to another
 * (SetOutputBuffer) mixes into that one's input, which then plays as a source of its own. Play
 * cursors come from the mixer.
 *
 * The DSP image's I3DL2 reverb is a software one (a Freeverb-style network tuned from the
 * listener's settings), fed by the reverb mix bin (10) and the 3D voices' room sends.
 * Not yet: the image's other effects (the filters), Doppler, cones.
 */
#include <windows.h>
#include <xaudio2.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <vector>

#include "../port.h"

typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef float RwReal;

enum
{
    DSBPLAY_LOOPING = 1,
    DSBPLAY_FROMSTART = 2,
    DSBSTATUS_PLAYING = 1,
    DSBSTATUS_LOOPING = 4,
    DSBCAPS_CTRL3D = 0x10,
    DSBCAPS_MIXIN = 0x2000,
    OUT_RATE = 48000,
    BLOCK = 480
};

#pragma pack(push, 1)
struct WaveFormat
{
    WORD formatTag, channels;
    DWORD samplesPerSec, avgBytesPerSec;
    WORD blockAlign, bitsPerSample, size;
};
#pragma pack(pop)

struct MixBinLevel
{
    DWORD bin;
    LONG level;
};

struct MixBins
{
    DWORD count;
    const MixBinLevel *levels;
};

struct BufferDesc
{
    DWORD size, flags, bufferBytes;
    const void *format;
    const MixBins *mixBins;
    DWORD inputMixBin;
};

struct V3 { float x, y, z; };

struct DS3DBuffer
{
    DWORD size;
    V3 position, velocity;
    DWORD insideConeAngle, outsideConeAngle;
    V3 coneOrientation;
    LONG coneOutsideVolume;
    float minDistance, maxDistance;
    DWORD mode;
    float distanceFactor, rolloffFactor, dopplerFactor;
};

struct Voice
{
    LONG refs;
    DWORD flags;
    const BYTE *data;
    DWORD size;
    WaveFormat format;
    DWORD frequency;
    DWORD playOffset, playLength, loopOffset, loopLength;
    int playing, looping;
    double pos;             /* in source frames from the start of the data */
    LONG volume;            /* hundredths of a dB */
    MixBinLevel bins[8];
    LONG room;              /* I3DL2 source: the reverb send of a 3D voice (millibels) */
    int nbins;
    int is3D;
    V3 position;
    float minDistance, maxDistance, rolloff;
    DWORD mode3D;           /* 0 normal, 1 head-relative, 2 disabled */
    /* SetRolloffCurve's: amplitudes evenly spaced from the minimum distance to the maximum, in
       place of the inverse-distance rolloff (RenderWare Audio sets {1}: it attenuates by distance
       itself, through the volume) */
    float curve[32];
    int curvePoints;
    Voice *target;
    /* a mix-in voice's input, one block, per channel */
    float input[2][BLOCK];
    int hasInput;
    /* Xbox ADPCM: the block decoded last */
    long adpcmBlock;
    short adpcmPcm[2][64];
};

static CRITICAL_SECTION lock;
static std::vector<Voice *> voices;
static IXAudio2 *xa;
static IXAudio2MasteringVoice *master;
static IXAudio2SourceVoice *source;
static HANDLE thread;
static volatile int running;
static V3 listener_pos, listener_front = {0, 0, 1}, listener_top = {0, 1, 0};
static float distance_factor = 1, rolloff_factor = 1;
static int dsound_object;

static float db(LONG hundredths)
{
    if (hundredths <= -10000)
        return 0;
    return powf(10.0f, hundredths / 2000.0f);
}

/* Bytes per source frame (ADPCM: the block's share). */
static double frame_bytes(const Voice *v)
{
    if (v->format.formatTag == 0x69)
        return 36.0 * v->format.channels / 64.0;
    int b = v->format.blockAlign ? v->format.blockAlign : v->format.channels * v->format.bitsPerSample / 8;
    return b ? b : 2;
}

static DWORD region_end(const Voice *v)
{
    return v->playLength ? v->playOffset + v->playLength : v->size;
}

/* Xbox ADPCM: IMA steps; per channel a 4-byte header (sample, index) then 32 bytes of nibbles in
   4-byte groups interleaved by channel. */
static const int ima_index[16] = {-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};
static const int ima_step[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 50, 55, 60, 66, 73, 80, 88, 97,
    107, 118, 130, 143, 157, 173, 190, 209, 230, 253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871,
    5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623,
    27086, 29794, 32767};

static void adpcm_decode(Voice *v, long block)
{
    int ch = v->format.channels ? v->format.channels : 1;
    if (ch > 2)
        ch = 2;
    const BYTE *b = v->data + (size_t)block * 36 * ch;
    if ((DWORD)((block + 1) * 36 * ch) > v->size)
    {
        memset(v->adpcmPcm, 0, sizeof(v->adpcmPcm));
        v->adpcmBlock = block;
        return;
    }
    int pred[2], idx[2];
    for (int c = 0; c < ch; c++)
    {
        pred[c] = (short)(b[c * 4] | (b[c * 4 + 1] << 8));
        idx[c] = b[c * 4 + 2] > 88 ? 88 : b[c * 4 + 2];
    }
    const BYTE *d = b + 4 * ch;
    for (int group = 0; group < 8; group++)
        for (int c = 0; c < ch; c++)
        {
            const BYTE *g = d + (group * ch + c) * 4;
            for (int i = 0; i < 8; i++)
            {
                int nib = (g[i / 2] >> ((i & 1) * 4)) & 15;
                int step = ima_step[idx[c]];
                int diff = step >> 3;
                if (nib & 1) diff += step >> 2;
                if (nib & 2) diff += step >> 1;
                if (nib & 4) diff += step;
                if (nib & 8) diff = -diff;
                pred[c] += diff;
                pred[c] = pred[c] > 32767 ? 32767 : pred[c] < -32768 ? -32768 : pred[c];
                idx[c] += ima_index[nib];
                idx[c] = idx[c] < 0 ? 0 : idx[c] > 88 ? 88 : idx[c];
                v->adpcmPcm[c][group * 8 + i] = (short)pred[c];
            }
        }
    v->adpcmBlock = block;
}

/* A source frame's sample for channel c, as a float. */
static float sample(Voice *v, long frame, int c)
{
    int ch = v->format.channels ? v->format.channels : 1;
    if (c >= ch)
        c = ch - 1;
    if (v->format.formatTag == 0x69)
    {
        long block = frame / 64;
        if (block != v->adpcmBlock)
            adpcm_decode(v, block);
        return v->adpcmPcm[c < 2 ? c : 1][frame % 64] / 32768.0f;
    }
    size_t at = (size_t)frame * frame_bytes(v);
    if (v->format.bitsPerSample == 8)
    {
        if (at + c >= v->size)
            return 0;
        return (v->data[at + c] - 128) / 128.0f;
    }
    if (at + c * 2 + 1 >= v->size)
        return 0;
    return *(const short *)(v->data + at + c * 2) / 32768.0f;
}

/* The voice's gains to the stereo output, per source channel. */
static void voice_gains(const Voice *v, float g[2][2], float *send)
{
    float vol = db(v->volume);
    memset(g, 0, sizeof(float) * 4);
    *send = 0;
    int ch = v->format.channels ? v->format.channels : 1;
    if (v->is3D && v->mode3D != 2)
    {
        V3 rel = v->position;
        if (v->mode3D != 1)
        {
            rel.x -= listener_pos.x;
            rel.y -= listener_pos.y;
            rel.z -= listener_pos.z;
        }
        float d = sqrtf(rel.x * rel.x + rel.y * rel.y + rel.z * rel.z) * distance_factor;
        float mind = v->minDistance > 0 ? v->minDistance : 1;
        float dd = d < mind ? mind : (v->maxDistance > 0 && d > v->maxDistance ? v->maxDistance : d);
        float att;
        if (v->curvePoints)
        {
            float span = v->maxDistance > mind ? v->maxDistance - mind : 0;
            float at = span > 0 ? (dd - mind) / span * (v->curvePoints - 1) : 0;
            int i = (int)at;
            if (i >= v->curvePoints - 1)
                att = v->curve[v->curvePoints - 1];
            else
                att = v->curve[i] + (v->curve[i + 1] - v->curve[i]) * (at - i);
        }
        else
            att = mind / (mind + (dd - mind) * rolloff_factor * (v->rolloff > 0 ? v->rolloff : 1));
        /* the listener's right: top x front (DirectSound's left-handed axes) */
        V3 t = listener_top, f = listener_front;
        V3 right = {t.y * f.z - t.z * f.y, t.z * f.x - t.x * f.z, t.x * f.y - t.y * f.x};
        float rl = sqrtf(right.x * right.x + right.y * right.y + right.z * right.z);
        float pan = 0;
        if (d > 1e-4f && rl > 1e-6f)
            pan = (rel.x * right.x + rel.y * right.y + rel.z * right.z) / (sqrtf(rel.x * rel.x + rel.y * rel.y + rel.z * rel.z) * rl);
        float a = (pan + 1) * 0.785398f;    /* equal power */
        float level = 0;
        for (int i = 0; i < v->nbins; i++)
            if (v->bins[i].bin >= 6 && v->bins[i].bin <= 9)
                level = level > db(v->bins[i].level) ? level : db(v->bins[i].level);
        if (!v->nbins)
            level = 1;
        for (int c = 0; c < ch && c < 2; c++)
        {
            g[c][0] = vol * att * level * cosf(a) / (ch > 1 ? 2 : 1);
            g[c][1] = vol * att * level * sinf(a) / (ch > 1 ? 2 : 1);
        }
        /* the room send falls off more slowly than the direct sound */
        *send = vol * sqrtf(att) * db(v->room) / (ch > 1 ? 2 : 1);
        return;
    }
    if (!v->nbins)
    {
        for (int c = 0; c < ch && c < 2; c++)
            g[c][ch == 1 ? 0 : c] = vol, g[c][ch == 1 ? 1 : c] = vol;
        return;
    }
    for (int i = 0; i < v->nbins; i++)
    {
        int c = ch > 1 ? i % ch : 0;
        if (c > 1)
            c = 1;
        float lv = vol * db(v->bins[i].level);
        switch (v->bins[i].bin)
        {
        case 0: case 4: g[c][0] += lv; break;               /* front and back left */
        case 1: case 5: g[c][1] += lv; break;               /* right */
        case 2: g[c][0] += lv * 0.707f; g[c][1] += lv * 0.707f; break;    /* centre */
        case 10: *send += lv / (ch > 1 ? 2 : 1); break;      /* I3DL2 reverb */
        default: break;                                     /* LFE and effect sends */
        }
    }
}

/* Renders one block of a data voice into out[ch][BLOCK] (its own channels, before gains). */
static int render_source(Voice *v, float out[2][BLOCK])
{
    memset(out, 0, sizeof(float) * 2 * BLOCK);
    if (!v->playing || !v->data || !v->size)
        return 0;
    DWORD rate = v->frequency ? v->frequency : v->format.samplesPerSec;
    if (!rate)
        rate = 44100;
    double step = (double)rate / OUT_RATE;
    double fb = frame_bytes(v);
    double startF = v->playOffset / fb, endF = region_end(v) / fb;
    /* (the loop region is relative to the play region, as the positions are) */
    double loopStart = v->loopLength ? (v->playOffset + v->loopOffset) / fb : startF;
    double loopEnd = v->loopLength ? (v->playOffset + v->loopOffset + v->loopLength) / fb : endF;
    if (loopEnd > endF)
        loopEnd = endF;
    int ch = v->format.channels ? (v->format.channels > 2 ? 2 : v->format.channels) : 1;
    for (int i = 0; i < BLOCK; i++)
    {
        double limit = v->looping ? loopEnd : endF;
        if (v->pos >= limit)
        {
            if (v->looping && loopEnd > loopStart)
                v->pos = loopStart + fmod(v->pos - loopStart, loopEnd - loopStart);
            else
            {
                v->playing = 0;
                v->pos = startF;
                return 1;
            }
        }
        long f0 = (long)v->pos;
        float t = (float)(v->pos - f0);
        for (int c = 0; c < ch; c++)
        {
            float a = sample(v, f0, c), b = (f0 + 1 < (long)limit) ? sample(v, f0 + 1, c) : a;
            out[c][i] = a + (b - a) * t;
        }
        v->pos += step;
    }
    return 1;
}

/*
 * I3DL2 reverb: four combs and two all-passes a side (Freeverb's tunings at 48 kHz). The decay
 * time sets the combs' feedback, the HF ratio their damping, room + reverb (millibels) the wet
 * level; a room of -10000 (the default) turns it off.
 */
static const int comb_len[4] = {1215, 1293, 1390, 1476};
static const int pass_len[2] = {605, 480};
enum { SPREAD = 25 };
static float comb_buf[2][4][1500 + SPREAD], pass_buf[2][2][620 + SPREAD];
static int comb_at[2][4], pass_at[2][2];
static float comb_store[2][4];
static volatile float reverb_feedback[4], reverb_damp, reverb_wet, reverb_diffusion = 0.5f;

static void set_reverb(LONG room, LONG reverb, float decayTime, float hfRatio, float diffusion)
{
    float wet = room <= -10000 ? 0 : db(room + (reverb < 2000 ? reverb : 2000));
    if (decayTime < 0.1f)
        decayTime = 0.1f;
    for (int i = 0; i < 4; i++)
        reverb_feedback[i] = powf(10.0f, -3.0f * comb_len[i] / (OUT_RATE * decayTime));
    float d = 1.0f - (hfRatio > 0 ? hfRatio : 0.5f);
    reverb_damp = d < 0 ? 0 : d > 0.9f ? 0.9f : d;
    reverb_diffusion = 0.3f + 0.4f * (diffusion < 0 ? 0 : diffusion > 1 ? 1 : diffusion);
    reverb_wet = wet;
}

static void run_reverb(const float *in, float *stereo)
{
    float wet = reverb_wet;
    if (wet <= 0)
        return;
    for (int s = 0; s < BLOCK; s++)
    {
        float x = in[s] * 0.015f;
        for (int c = 0; c < 2; c++)
        {
            float out = 0;
            for (int i = 0; i < 4; i++)
            {
                int len = comb_len[i] + c * SPREAD;
                float *b = comb_buf[c][i];
                float y = b[comb_at[c][i]];
                comb_store[c][i] = y * (1 - reverb_damp) + comb_store[c][i] * reverb_damp;
                b[comb_at[c][i]] = x + comb_store[c][i] * reverb_feedback[i];
                if (++comb_at[c][i] >= len)
                    comb_at[c][i] = 0;
                out += y;
            }
            for (int i = 0; i < 2; i++)
            {
                int len = pass_len[i] + c * SPREAD;
                float *b = pass_buf[c][i];
                float y = b[pass_at[c][i]];
                b[pass_at[c][i]] = out + y * reverb_diffusion;
                out = y - out;
                if (++pass_at[c][i] >= len)
                    pass_at[c][i] = 0;
            }
            stereo[s * 2 + c] += out * 3.0f * wet;
        }
    }
}

static void mix_block(float *stereo)
{
    static float send[BLOCK];
    memset(send, 0, sizeof(send));
    memset(stereo, 0, sizeof(float) * 2 * BLOCK);
    EnterCriticalSection(&lock);
    for (size_t i = 0; i < voices.size(); i++)
        voices[i]->hasInput = 0;
    for (size_t i = 0; i < voices.size(); i++)
        if (voices[i]->hasInput == 0)
            memset(voices[i]->input, 0, sizeof(voices[i]->input));
    static float buf[2][BLOCK];
    /* sources routed into mix-in voices first, then everything that reaches the output */
    for (int pass = 0; pass < 2; pass++)
        for (size_t i = 0; i < voices.size(); i++)
        {
            Voice *v = voices[i];
            int mixin = (v->flags & DSBCAPS_MIXIN) != 0;
            if ((pass == 0) == mixin)
                continue;   /* pass 0: data voices; pass 1: mix-in voices */
            int have;
            if (mixin)
            {
                have = v->hasInput;
                memcpy(buf, v->input, sizeof(buf));
            }
            else
                have = render_source(v, buf);
            if (!have)
                continue;
            int ch = v->format.channels ? (v->format.channels > 2 ? 2 : v->format.channels) : 1;
            if (mixin && !v->format.channels)
                ch = 2;
            if (v->target)
            {
                float vol = db(v->volume);
                for (int c = 0; c < ch; c++)
                    for (int s = 0; s < BLOCK; s++)
                    {
                        v->target->input[c][s] += buf[c][s] * vol;
                        if (ch == 1)
                            v->target->input[1][s] += buf[0][s] * vol;
                    }
                v->target->hasInput = 1;
                continue;
            }
            float g[2][2], sg;
            voice_gains(v, g, &sg);
            for (int c = 0; c < ch; c++)
                for (int s = 0; s < BLOCK; s++)
                {
                    stereo[s * 2] += buf[c][s] * g[c][0];
                    stereo[s * 2 + 1] += buf[c][s] * g[c][1];
                    send[s] += buf[c][s] * sg;
                }
        }
    LeaveCriticalSection(&lock);
    run_reverb(send, stereo);
    for (int s = 0; s < BLOCK * 2; s++)
        stereo[s] = stereo[s] > 1 ? 1 : stereo[s] < -1 ? -1 : stereo[s];
}

/* CODFH_WAV=<file>: the mixed output recorded (48 kHz stereo 16-bit), for checking it without
   listening. */
static void record(const float *stereo)
{
    static FILE *f;
    static int state;
    static DWORD bytes;
    if (state < 0)
        return;
    if (!state)
    {
        char path[MAX_PATH];
        if (!GetEnvironmentVariableA("CODFH_WAV", path, sizeof(path)) || !(f = fopen(path, "wb")))
        {
            state = -1;
            return;
        }
        state = 1;
        BYTE hdr[44] = {0};
        fwrite(hdr, 1, 44, f);
    }
    short pcm[BLOCK * 2];
    for (int i = 0; i < BLOCK * 2; i++)
        pcm[i] = (short)(stereo[i] * 32767.0f);
    fwrite(pcm, 2, BLOCK * 2, f);
    bytes += sizeof(pcm);
    /* (the header rewritten each second, so the file is valid whenever the game stops) */
    if ((bytes / sizeof(pcm)) % 100 == 0)
    {
        long at = ftell(f);
        DWORD riff = 36 + bytes, fmt = 16, rate = OUT_RATE, byterate = OUT_RATE * 4;
        WORD pcmtag = 1, ch = 2, align = 4, bits = 16;
        fseek(f, 0, SEEK_SET);
        fwrite("RIFF", 1, 4, f); fwrite(&riff, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f); fwrite(&fmt, 4, 1, f);
        fwrite(&pcmtag, 2, 1, f); fwrite(&ch, 2, 1, f); fwrite(&rate, 4, 1, f); fwrite(&byterate, 4, 1, f);
        fwrite(&align, 2, 1, f); fwrite(&bits, 2, 1, f); fwrite("data", 1, 4, f); fwrite(&bytes, 4, 1, f);
        fseek(f, at, SEEK_SET);
        fflush(f);
    }
}

static DWORD WINAPI mixer_thread(void *)
{
    static float blocks[4][BLOCK * 2];
    int next = 0;
    LARGE_INTEGER freq, next_t, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&next_t);
    while (running)
    {
        if (!source)
        {
            /* no output device: the blocks paced by the clock, so the cursors still advance */
            QueryPerformanceCounter(&now);
            if (now.QuadPart < next_t.QuadPart)
            {
                Sleep(1);
                continue;
            }
            next_t.QuadPart += freq.QuadPart * BLOCK / OUT_RATE;
            mix_block(blocks[next]);
            record(blocks[next]);
            next = (next + 1) % 4;
            continue;
        }
        XAUDIO2_VOICE_STATE vs;
        source->GetState(&vs, XAUDIO2_VOICE_NOSAMPLESPLAYED);
        if (vs.BuffersQueued < 3)
        {
            mix_block(blocks[next]);
            record(blocks[next]);
            XAUDIO2_BUFFER b;
            memset(&b, 0, sizeof(b));
            b.AudioBytes = BLOCK * 2 * sizeof(float);
            b.pAudioData = (const BYTE *)blocks[next];
            source->SubmitSourceBuffer(&b);
            next = (next + 1) % 4;
        }
        else
            Sleep(2);
    }
    return 0;
}

static void start_output(void)
{
    InitializeCriticalSection(&lock);
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    HRESULT hr = XAudio2Create(&xa, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (SUCCEEDED(hr))
        hr = xa->CreateMasteringVoice(&master, 2, OUT_RATE);
    if (FAILED(hr))
    {
        plog("audio: no XAudio2 output (0x%08lX): mixing without a device", hr);
        running = 1;
        thread = CreateThread(NULL, 0, mixer_thread, NULL, 0, NULL);
        return;
    }
    WAVEFORMATEX wf;
    memset(&wf, 0, sizeof(wf));
    wf.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
    wf.nChannels = 2;
    wf.nSamplesPerSec = OUT_RATE;
    wf.wBitsPerSample = 32;
    wf.nBlockAlign = 8;
    wf.nAvgBytesPerSec = OUT_RATE * 8;
    if (FAILED(xa->CreateSourceVoice(&source, &wf)))
    {
        plog("audio: no XAudio2 voice: mixing without a device");
        source = NULL;
        running = 1;
        thread = CreateThread(NULL, 0, mixer_thread, NULL, 0, NULL);
        return;
    }
    source->Start();
    running = 1;
    thread = CreateThread(NULL, 0, mixer_thread, NULL, 0, NULL);
    SetThreadPriority(thread, THREAD_PRIORITY_TIME_CRITICAL);
    plog("audio: XAudio2, 48 kHz stereo");
}

/* The mixer stopped and the output closed (the window's close, before the process exits). */
extern "C" void port_audio_shutdown(void)
{
    if (!running)
        return;
    running = 0;
    if (thread)
    {
        WaitForSingleObject(thread, 1000);
        CloseHandle(thread);
        thread = NULL;
    }
    if (source)
    {
        source->Stop();
        source->DestroyVoice();
        source = NULL;
    }
    if (master)
    {
        master->DestroyVoice();
        master = NULL;
    }
    if (xa)
    {
        xa->Release();
        xa = NULL;
    }
}

/*
 * The DirectSound object
 */

extern "C" RwInt32 __stdcall DirectSoundCreate(void *, void **dsound, void *)
{
    if (!running)
        start_output();
    *dsound = &dsound_object;
    return S_OK;
}

extern "C" RwInt32 __stdcall DirectSoundUseFullHRTF(void) { return S_OK; }
extern "C" void __stdcall DirectSoundDoWork(void) {}
extern "C" RwUInt32 __stdcall IDirectSound_Release(void *) { return 0; }
/* dsound.h's DSI3DL2LISTENER */
struct I3DL2Listener
{
    LONG room, roomHF;
    float roomRolloffFactor, decayTime, decayHFRatio;
    LONG reflections;
    float reflectionsDelay;
    LONG reverb;
    float reverbDelay, diffusion, density, hfReference;
};

extern "C" RwInt32 __stdcall IDirectSound_SetI3DL2Listener(void *, const void *settings, RwUInt32)
{
    const I3DL2Listener *l = (const I3DL2Listener *)settings;
    if (!l)
        return S_OK;
    set_reverb(l->room, l->reverb, l->decayTime, l->decayHFRatio, l->diffusion / 100.0f);
    static int told;
    if (told++ < 8)
        plog("audio: I3DL2 reverb room %ld mB, reverb %ld mB, decay %.2f s, HF ratio %.2f, diffusion %.0f%%", l->room,
             l->reverb, l->decayTime, l->decayHFRatio, l->diffusion);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_GetOutputLevels(void *, void *levels, RwInt32)
{
    memset(levels, 0, 8 * 4);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetEffectData(void *, RwUInt32, RwUInt32, const void *, RwUInt32, RwUInt32)
{
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_GetEffectData(void *, RwUInt32, RwUInt32, void *data, RwUInt32 size)
{
    memset(data, 0, size);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_CommitEffectData(void *) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSound_GetSpeakerConfig(void *, RwUInt32 *config)
{
    *config = 0;    /* stereo */
    return S_OK;
}

/* The DSP image: its descriptor lists no effects (its effects are to be rebuilt). */
static DWORD empty_image_desc[4];

extern "C" RwInt32 __stdcall IDirectSound_DownloadEffectsImage(void *, void *, RwUInt32, void *, void **desc)
{
    if (desc)
        *desc = empty_image_desc;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetDopplerFactor(void *, RwReal, RwUInt32) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSound_SetDistanceFactor(void *, RwReal f, RwUInt32)
{
    if (f != distance_factor)
        plog("audio: distance factor %g", f);
    distance_factor = f > 0 ? f : 1;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetRolloffFactor(void *, RwReal f, RwUInt32)
{
    if (f != rolloff_factor)
        plog("audio: rolloff factor %g", f);
    rolloff_factor = f >= 0 ? f : 1;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetVelocity(void *, RwReal, RwReal, RwReal, RwUInt32) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSound_SetPosition(void *, RwReal x, RwReal y, RwReal z, RwUInt32)
{
    listener_pos.x = x;
    listener_pos.y = y;
    listener_pos.z = z;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_SetOrientation(void *, RwReal fx, RwReal fy, RwReal fz, RwReal tx, RwReal ty,
                                                         RwReal tz, RwUInt32)
{
    V3 f = {fx, fy, fz}, t = {tx, ty, tz};
    listener_front = f;
    listener_top = t;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSound_CommitDeferredSettings(void *) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_EnableHeadphones(void *, RwInt32) { return S_OK; }
extern "C" RwInt32 __stdcall IDirectSound_SetMixBinHeadroom(void *, RwUInt32, RwUInt32) { return S_OK; }

/*
 * Buffers
 */

static void set_bins(Voice *v, const MixBins *m)
{
    v->nbins = 0;
    if (!m || !m->levels)
        return;
    for (DWORD i = 0; i < m->count && i < 8; i++)
        v->bins[v->nbins++] = m->levels[i];
}

extern "C" RwInt32 __stdcall IDirectSound_CreateSoundBuffer(void *, const BufferDesc *desc, void **buffer, void *)
{
    Voice *v = (Voice *)calloc(1, sizeof(Voice));
    v->refs = 1;
    v->flags = desc->flags;
    v->is3D = (desc->flags & DSBCAPS_CTRL3D) != 0;
    v->adpcmBlock = -1;
    v->minDistance = 1;
    v->maxDistance = 1e9f;
    v->rolloff = 1;
    if (desc->format)
        memcpy(&v->format, desc->format, sizeof(WaveFormat));
    v->size = desc->bufferBytes;
    set_bins(v, desc->mixBins);
    if (running)
        EnterCriticalSection(&lock);
    voices.push_back(v);
    if (running)
        LeaveCriticalSection(&lock);
    *buffer = v;
    return S_OK;
}

extern "C" RwUInt32 __stdcall IDirectSoundBuffer_Release(void *buffer)
{
    Voice *v = (Voice *)buffer;
    LONG r = InterlockedDecrement(&v->refs);
    if (!r)
    {
        if (running)
            EnterCriticalSection(&lock);
        for (size_t i = 0; i < voices.size(); i++)
        {
            if (voices[i] == v)
            {
                voices.erase(voices.begin() + i);
                i--;
            }
            else if (voices[i]->target == v)
                voices[i]->target = NULL;
        }
        if (running)
            LeaveCriticalSection(&lock);
        free(v);
    }
    return r;
}

#define LOCKED(stmt)                      \
    do                                    \
    {                                     \
        if (running)                      \
            EnterCriticalSection(&lock);  \
        stmt;                             \
        if (running)                      \
            LeaveCriticalSection(&lock);  \
    } while (0)

extern "C" RwInt32 __stdcall IDirectSoundBuffer_GetStatus(void *buffer, RwUInt32 *status)
{
    Voice *v = (Voice *)buffer;
    LOCKED(*status = (v->playing ? DSBSTATUS_PLAYING : 0) | (v->playing && v->looping ? DSBSTATUS_LOOPING : 0));
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Play(void *buffer, RwUInt32, RwUInt32, RwUInt32 flags)
{
    Voice *v = (Voice *)buffer;
    static int logged;
    if (logged < 40)
    {
        logged++;
        plog("audio: play %p tag 0x%X ch %d rate %lu freq %lu flags 0x%lX data %p size %lu region %lu+%lu loop %lu+%lu "
             "vol %ld bins %d target %p%s", v, v->format.formatTag, v->format.channels, v->format.samplesPerSec,
             v->frequency, v->flags, v->data, v->size, v->playOffset, v->playLength, v->loopOffset, v->loopLength,
             v->volume, v->nbins, v->target, (flags & DSBPLAY_LOOPING) ? " looping" : "");
    }
    /* CODFH_AUDIOTRACE=1: every play, with its 3D state, mix bins and gains to the output */
    static int trace = -1;
    if (trace < 0)
    {
        char e[4];
        trace = GetEnvironmentVariableA("CODFH_AUDIOTRACE", e, sizeof(e)) ? 1 : 0;
    }
    if (trace)
    {
        float g[2][2], sg;
        char bins[160] = "";
        LOCKED(voice_gains(v, g, &sg));
        for (int i = 0; i < v->nbins; i++)
            _snprintf(bins + strlen(bins), sizeof(bins) - strlen(bins) - 1, " %lu:%ld", v->bins[i].bin, v->bins[i].level);
        float dx = v->position.x - listener_pos.x, dy = v->position.y - listener_pos.y, dz = v->position.z - listener_pos.z;
        plog("audio trace: frame %u play %p size %lu tag 0x%X freq %lu vol %ld 3d %d mode %lu dist %.1f min %.1f max %.1f "
             "bins%s target %p gain %.3f/%.3f send %.3f", port_frame, v, v->playLength ? v->playLength : v->size,
             v->format.formatTag, v->frequency, v->volume, v->is3D, v->mode3D, sqrtf(dx * dx + dy * dy + dz * dz),
             v->minDistance, v->maxDistance, bins, v->target, g[0][0] + g[1][0], g[0][1] + g[1][1], sg);
    }
    LOCKED({
        if (flags & DSBPLAY_FROMSTART)
            v->pos = v->playOffset / frame_bytes(v);
        v->looping = (flags & DSBPLAY_LOOPING) != 0;
        v->playing = 1;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_StopEx(void *buffer, RwInt32, RwUInt32, RwUInt32)
{
    Voice *v = (Voice *)buffer;
    LOCKED(v->playing = 0);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Stop(void *buffer)
{
    return IDirectSoundBuffer_StopEx(buffer, 0, 0, 0);
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetOutputBuffer(void *buffer, void *output)
{
    Voice *v = (Voice *)buffer;
    LOCKED(v->target = (Voice *)output);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetRolloffCurve(void *buffer, const RwReal *points, RwUInt32 count,
                                                                RwUInt32)
{
    Voice *v = (Voice *)buffer;
    LOCKED({
        v->curvePoints = points ? (int)(count < 32 ? count : 32) : 0;
        for (int i = 0; i < v->curvePoints; i++)
            v->curve[i] = points[i];
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetFormat(void *buffer, const void *format)
{
    Voice *v = (Voice *)buffer;
    LOCKED({
        if (format)
            memcpy(&v->format, format, sizeof(WaveFormat));
        v->adpcmBlock = -1;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetBufferData(void *buffer, void *data, RwUInt32 size)
{
    Voice *v = (Voice *)buffer;
    LOCKED({
        v->data = (const BYTE *)data;
        v->size = size;
        v->playOffset = v->playLength = v->loopOffset = v->loopLength = 0;
        v->pos = 0;
        v->adpcmBlock = -1;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetMixBins(void *buffer, const void *mixBins)
{
    Voice *v = (Voice *)buffer;
    LOCKED(set_bins(v, (const MixBins *)mixBins));
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetMixBinVolumes(void *buffer, const void *mixBins)
{
    Voice *v = (Voice *)buffer;
    const MixBins *m = (const MixBins *)mixBins;
    LOCKED({
        for (DWORD i = 0; m && m->levels && i < m->count; i++)
            for (int k = 0; k < v->nbins; k++)
                if (v->bins[k].bin == m->levels[i].bin)
                    v->bins[k].level = m->levels[i].level;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetPlayRegion(void *buffer, RwUInt32 offset, RwUInt32 length)
{
    Voice *v = (Voice *)buffer;
    LOCKED({
        v->playOffset = offset;
        v->playLength = length;
        double f = offset / frame_bytes(v);
        if (v->pos < f || !v->playing)
            v->pos = f;
        v->adpcmBlock = -1;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetLoopRegion(void *buffer, RwUInt32 offset, RwUInt32 length)
{
    Voice *v = (Voice *)buffer;
    LOCKED({
        v->loopOffset = offset;
        v->loopLength = length;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetCurrentPosition(void *buffer, RwUInt32 pos)
{
    Voice *v = (Voice *)buffer;
    LOCKED(v->pos = (v->playOffset + pos) / frame_bytes(v));
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_GetCurrentPosition(void *buffer, RwUInt32 *play, RwUInt32 *write)
{
    Voice *v = (Voice *)buffer;
    DWORD p;
    LOCKED({
        double b = v->pos * frame_bytes(v);
        p = b > v->playOffset ? (DWORD)b - v->playOffset : 0;
    });
    if (play)
        *play = p;
    if (write)
        *write = p;
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetHeadroom(void *, RwUInt32) { return S_OK; }

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetAllParameters(void *buffer, const void *params, RwUInt32)
{
    Voice *v = (Voice *)buffer;
    const DS3DBuffer *p = (const DS3DBuffer *)params;
    LOCKED({
        v->position = p->position;
        v->minDistance = p->minDistance;
        v->maxDistance = p->maxDistance;
        v->mode3D = p->mode;
        v->rolloff = p->rolloffFactor > 0 ? p->rolloffFactor : 1;
    });
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetFrequency(void *buffer, RwUInt32 frequency)
{
    Voice *v = (Voice *)buffer;
    LOCKED(v->frequency = frequency);
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetVolume(void *buffer, RwInt32 volume)
{
    Voice *v = (Voice *)buffer;
    LOCKED(v->volume = volume);
    return S_OK;
}

/* dsound.h's DSI3DL2BUFFER: direct, direct HF, room, room HF (millibels), then the rest */
extern "C" RwInt32 __stdcall IDirectSoundBuffer_SetI3DL2Source(void *buffer, const void *settings, RwUInt32)
{
    Voice *v = (Voice *)buffer;
    if (settings)
        v->room = ((const LONG *)settings)[2];
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Lock(void *buffer, RwUInt32 offset, RwUInt32 bytes, void **p1,
                                                     RwUInt32 *n1, void **p2, RwUInt32 *n2, RwUInt32)
{
    /* a region past the end wraps to the start (Bink's looping stream buffer) */
    Voice *v = (Voice *)buffer;
    if (p2)
        *p2 = NULL;
    if (n2)
        *n2 = 0;
    if (!v->data || !v->size)
    {
        *p1 = NULL;
        *n1 = 0;
        return E_FAIL;
    }
    offset %= v->size;
    if (bytes > v->size)
        bytes = v->size;
    *p1 = (void *)(v->data + offset);
    *n1 = bytes;
    if (offset + bytes > v->size)
    {
        *n1 = v->size - offset;
        if (p2 && n2)
        {
            *p2 = (void *)v->data;
            *n2 = bytes - *n1;
        }
    }
    return S_OK;
}

extern "C" RwInt32 __stdcall IDirectSoundBuffer_Unlock(void *buffer, void *, RwUInt32, void *, RwUInt32)
{
    Voice *v = (Voice *)buffer;
    LOCKED(v->adpcmBlock = -1);
    return S_OK;
}
