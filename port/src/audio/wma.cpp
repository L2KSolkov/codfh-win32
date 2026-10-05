/*
 * WMA for the port (docs/WIN32_PORT.md W5): WmaCreateDecoderEx's media object over Media
 * Foundation's source reader. RenderWare Audio's WMA source (src/rwa/xbox/unit_250B20.c) pulls
 * 16-bit PCM packets through Process (status 2: output wanted), loops with SeekToTime(0) and
 * reads the format, length and duration from GetFileHeader and GetLength.
 */
#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <string.h>

#include <vector>

#include "../port.h"

typedef int RwInt32;
typedef unsigned int RwUInt32;

#pragma pack(push, 1)
struct WaveFormat
{
    WORD formatTag, channels;
    DWORD samplesPerSec, avgBytesPerSec;
    WORD blockAlign, bitsPerSample, size;
};
#pragma pack(pop)

struct MediaPacket
{
    void *buffer;
    DWORD size;
    DWORD *completed;
    DWORD *status;
    void *event;
    void *timestamp;
};

struct WmaHeader
{
    DWORD version, sampleRate, noChannels, duration, bitrate;
};

#pragma pack(push, 1)
struct WmaContentDesc
{
    WORD titleLength, authorLength, copyrightLength, descriptionLength, ratingLength;
    WCHAR *title, *author, *copyright, *description, *rating;
};
#pragma pack(pop)

struct WmaObject;

struct WmaVtbl
{
    RwUInt32(__stdcall *addRef)(WmaObject *);
    RwUInt32(__stdcall *release)(WmaObject *);
    RwInt32(__stdcall *getInfo)(WmaObject *, void *);
    RwInt32(__stdcall *getStatus)(WmaObject *, DWORD *);
    RwInt32(__stdcall *process)(WmaObject *, MediaPacket *, MediaPacket *);
    RwInt32(__stdcall *discontinuity)(WmaObject *);
    RwInt32(__stdcall *flush)(WmaObject *);
    RwInt32(__stdcall *seek)(WmaObject *, RwInt32, DWORD, DWORD *);
    RwInt32(__stdcall *getLength)(WmaObject *, DWORD *);
    RwInt32(__stdcall *doWork)(WmaObject *);
    RwInt32(__stdcall *getFileHeader)(WmaObject *, WmaHeader *);
    RwInt32(__stdcall *getFileContentDescription)(WmaObject *, WmaContentDesc *);
    RwInt32(__stdcall *seekToTime)(WmaObject *, DWORD, DWORD *);
};

struct WmaObject
{
    const WmaVtbl *vtbl;
    LONG refs;
    IMFSourceReader *reader;
    DWORD rate, channels, durationMs;
    std::vector<BYTE> pending;
    size_t pendingAt;
    int ended;
};

static void com_thread(void)
{
    static __declspec(thread) int ready;
    if (!ready)
    {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        ready = 1;
    }
}

static RwUInt32 __stdcall w_addRef(WmaObject *o) { return InterlockedIncrement(&o->refs); }

static RwUInt32 __stdcall w_release(WmaObject *o)
{
    LONG r = InterlockedDecrement(&o->refs);
    if (!r)
    {
        if (o->reader)
            o->reader->Release();
        delete o;
    }
    return r;
}

static RwInt32 __stdcall w_getInfo(WmaObject *, void *info)
{
    if (info)
        memset(info, 0, 12);
    return S_OK;
}

static RwInt32 __stdcall w_getStatus(WmaObject *, DWORD *status)
{
    *status = 2;    /* accepts output packets */
    return S_OK;
}

/* Fills the packet with decoded PCM; at the end it comes back short (RenderWare Audio loops). */
static RwInt32 __stdcall w_process(WmaObject *o, MediaPacket *, MediaPacket *out)
{
    com_thread();
    DWORD done = 0;
    BYTE *dst = (BYTE *)out->buffer;
    while (done < out->size)
    {
        if (o->pendingAt < o->pending.size())
        {
            size_t n = o->pending.size() - o->pendingAt;
            if (n > out->size - done)
                n = out->size - done;
            memcpy(dst + done, &o->pending[o->pendingAt], n);
            o->pendingAt += n;
            done += (DWORD)n;
            continue;
        }
        if (o->ended)
            break;
        DWORD flags = 0;
        IMFSample *sample = NULL;
        HRESULT hr = o->reader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, NULL, &flags, NULL, &sample);
        if (FAILED(hr) || (flags & MF_SOURCE_READERF_ENDOFSTREAM))
        {
            o->ended = 1;
            if (sample)
                sample->Release();
            break;
        }
        if (!sample)
            continue;
        IMFMediaBuffer *buf = NULL;
        if (SUCCEEDED(sample->ConvertToContiguousBuffer(&buf)))
        {
            BYTE *p;
            DWORD len;
            if (SUCCEEDED(buf->Lock(&p, NULL, &len)))
            {
                o->pending.assign(p, p + len);
                o->pendingAt = 0;
                buf->Unlock();
            }
            buf->Release();
        }
        sample->Release();
    }
    if (out->completed)
        *out->completed = done;
    if (out->status)
        *out->status = 0;
    return S_OK;
}

static RwInt32 __stdcall w_ok(WmaObject *) { return S_OK; }

static RwInt32 __stdcall w_seekToTime(WmaObject *o, DWORD ms, DWORD *actual)
{
    com_thread();
    PROPVARIANT pv;
    PropVariantInit(&pv);
    pv.vt = VT_I8;
    pv.hVal.QuadPart = (LONGLONG)ms * 10000;
    HRESULT hr = o->reader->SetCurrentPosition(GUID_NULL, pv);
    o->pending.clear();
    o->pendingAt = 0;
    o->ended = 0;
    if (actual)
        *actual = ms;
    return SUCCEEDED(hr) ? S_OK : hr;
}

static RwInt32 __stdcall w_seek(WmaObject *o, RwInt32 offset, DWORD, DWORD *position)
{
    DWORD bytesPerMs = o->rate * o->channels * 2 / 1000;
    DWORD ms = bytesPerMs ? (DWORD)offset / bytesPerMs : 0;
    if (position)
        *position = (DWORD)offset;
    return w_seekToTime(o, ms, NULL);
}

static RwInt32 __stdcall w_getLength(WmaObject *o, DWORD *length)
{
    *length = (DWORD)((unsigned long long)o->durationMs * o->rate / 1000 * o->channels * 2);
    return S_OK;
}

static RwInt32 __stdcall w_getFileHeader(WmaObject *o, WmaHeader *h)
{
    h->version = 2;
    h->sampleRate = o->rate;
    h->noChannels = o->channels;
    h->duration = o->durationMs;
    h->bitrate = 128000;
    return S_OK;
}

static RwInt32 __stdcall w_getFileContentDescription(WmaObject *, WmaContentDesc *d)
{
    d->titleLength = d->authorLength = d->copyrightLength = d->descriptionLength = d->ratingLength = 0;
    return S_OK;
}

static const WmaVtbl wma_vtbl = {w_addRef, w_release, w_getInfo, w_getStatus, w_process, w_ok, w_ok, w_seek,
                                 w_getLength, w_ok, w_getFileHeader, w_getFileContentDescription, w_seekToTime};

extern "C" RwInt32 __stdcall WmaCreateDecoderEx(const char *fileName, void *file, RwInt32, RwUInt32, RwUInt32, RwUInt32,
                                                void *format, void **decoder)
{
    *decoder = NULL;
    com_thread();
    static int started;
    if (!started)
    {
        started = 1;
        MFStartup(MF_VERSION, MFSTARTUP_LITE);
    }
    WCHAR wpath[MAX_PATH] = L"";
    if (fileName)
    {
        char mapped[520];
        MultiByteToWideChar(CP_ACP, 0, port_map_path(fileName, mapped), -1, wpath, MAX_PATH);
    }
    else if (file)
        GetFinalPathNameByHandleW((HANDLE)file, wpath, MAX_PATH, 0);
    IMFSourceReader *reader = NULL;
    if (!wpath[0] || FAILED(MFCreateSourceReaderFromURL(wpath, NULL, &reader)))
    {
        plog("audio: WMA %s not opened", fileName ? fileName : "(file)");
        return E_FAIL;
    }
    IMFMediaType *pcm = NULL;
    MFCreateMediaType(&pcm);
    pcm->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
    pcm->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
    pcm->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
    HRESULT hr = reader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, NULL, pcm);
    pcm->Release();
    IMFMediaType *actual = NULL;
    if (FAILED(hr) || FAILED(reader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &actual)))
    {
        reader->Release();
        plog("audio: WMA %s: no PCM output", fileName ? fileName : "(file)");
        return E_FAIL;
    }
    WmaObject *o = new WmaObject();
    o->vtbl = &wma_vtbl;
    o->refs = 1;
    o->reader = reader;
    UINT32 rate = 44100, ch = 2;
    actual->GetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, &rate);
    actual->GetUINT32(MF_MT_AUDIO_NUM_CHANNELS, &ch);
    actual->Release();
    o->rate = rate;
    o->channels = ch;
    PROPVARIANT dur;
    PropVariantInit(&dur);
    if (SUCCEEDED(reader->GetPresentationAttribute(MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &dur)))
        o->durationMs = (DWORD)(dur.uhVal.QuadPart / 10000);
    PropVariantClear(&dur);
    o->pendingAt = 0;
    o->ended = 0;
    WaveFormat *wf = (WaveFormat *)format;
    if (wf)
    {
        memset(wf, 0, sizeof(*wf));
        wf->formatTag = 1;
        wf->channels = (WORD)ch;
        wf->samplesPerSec = rate;
        wf->bitsPerSample = 16;
        wf->blockAlign = (WORD)(ch * 2);
        wf->avgBytesPerSec = rate * ch * 2;
    }
    plog("audio: WMA %s: %u Hz, %u channels, %lu ms", fileName ? fileName : "(file)", rate, ch, o->durationMs);
    *decoder = o;
    return S_OK;
}
