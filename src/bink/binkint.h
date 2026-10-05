/*
 * codfh-match: Bink's internal cross-unit declarations; the names are the
 * library members' symbols (binkxbox.lib, docs/reference/Bink).
 */
#ifndef __BINKINTH__
#define __BINKINTH__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

// radmath: (m1 * m2) / d through a 64-bit product
#pragma warning(disable:4035)
static __inline U32 mult64anddiv(U32 m1, U32 m2, U32 d)
{
  __asm
  {
    mov eax, m1
    mov ecx, m2
    mul ecx
    mov ecx, d
    div ecx
  }
}

// radmath: (m1 * m2) >> shift through a 64-bit product
static __inline U32 mult64andshift(U32 m1, U32 m2, U32 shift)
{
  __asm
  {
    mov eax, m1
    mov ecx, m2
    mul ecx
    mov ecx, shift
    shrd eax, edx, cl
  }
}
#pragma warning(default:4035)

// adds to a value the background callbacks also change (the library's
// LockedAddFunc)
static __inline void LockedAddFunc(volatile void *dest, S32 amt)
{
  __asm
  {
    mov eax, dest
    mov edx, amt
    add [eax], edx
  }
}

// radmath: the CPU's cycle counter into *addr, and *addr = cycles since it
static __inline void RADCycleTimerStartAddr(U32 *addr)
{
  __asm
  {
    mov ecx, addr
    rdtsc
    mov [ecx], eax
  }
}

static __inline void RADCycleTimerDeltaAddr(U32 *addr)
{
  __asm
  {
    rdtsc
    mov ecx, addr
    mov edx, eax
    sub eax, [ecx]
    mov [ecx], eax
  }
}

// radmem.obj
RADEXPFUNC void PTR4 *RADEXPLINK radmalloc(U32 numbytes);
RADEXPFUNC void RADEXPLINK radfree(void PTR4 *ptr);

// popmal.obj
RADEXPFUNC void RADEXPLINK pushmalloc(void PTR4 *ptr, U32 amt);
RADEXPFUNC U32 RADEXPLINK popmalloctotal(void);
RADEXPFUNC void PTR4 *RADEXPLINK popmalloc(U32 amt);

// wintimer.obj
RADEXPFUNC U32 RADEXPLINK RADTimerRead(void);

// the Xbox kernel and xapilib functions Bink calls
typedef void *HANDLE;
#define INFINITE 0xFFFFFFFF
U32 __stdcall WaitForSingleObject(HANDLE handle, U32 milliseconds);
U32 __stdcall WaitForMultipleObjects(U32 count, const HANDLE *handles, S32 waitall, U32 milliseconds);
S32 __stdcall ReleaseMutex(HANDLE mutex);
HANDLE __stdcall CreateMutexA(void *attributes, S32 owner, const char *name);
HANDLE __stdcall CreateEventA(void *attributes, S32 manual, S32 state, const char *name);
HANDLE __stdcall CreateThread(void *attributes, U32 stacksize, U32 (__stdcall *start)(void *),
  void *param, U32 flags, U32 *threadid);
S32 __stdcall SetThreadPriority(HANDLE thread, S32 priority);
S32 __stdcall SetEvent(HANDLE event);
U32 __stdcall ResumeThread(HANDLE thread);
S32 __stdcall CloseHandle(HANDLE handle);
HANDLE __stdcall CreateFileA(const char *name, U32 access, U32 share, void *security, U32 creation,
  U32 flags, HANDLE templ);
#ifdef CODFH_WIN32
// the port: the Xbox's d:\ paths mapped to the data root (port/src/xpal_core.cpp)
HANDLE __stdcall xpal_CreateFileA(const char *name, U32 access, U32 share, void *security, U32 creation,
  U32 flags, HANDLE templ);
#define CreateFileA xpal_CreateFileA
#endif
U32 __stdcall SetFilePointer(HANDLE file, S32 distance, S32 *distancehigh, U32 method);
S32 __stdcall ReadFile(HANDLE file, void *buffer, U32 bytes, U32 *read, void *overlapped);
void __stdcall Sleep(U32 milliseconds);
U32 __stdcall GetTickCount(void);
S32 __stdcall QueryPerformanceCounter(S64 *count);
S32 __stdcall QueryPerformanceFrequency(S64 *frequency);

// the XDK's DirectSound (dsound.h)
typedef struct IDirectSound IDirectSound;
typedef struct IDirectSoundBuffer IDirectSoundBuffer;

typedef struct DSMIXBINVOLUMEPAIR {
  U32 dwMixBin;
  S32 lVolume;
} DSMIXBINVOLUMEPAIR;

typedef struct DSMIXBINS {
  U32 dwMixBinCount;
  DSMIXBINVOLUMEPAIR *lpMixBinVolumePairs;
} DSMIXBINS;

typedef struct WAVEFORMATEX {
  U16 wFormatTag;
  U16 nChannels;
  U32 nSamplesPerSec;
  U32 nAvgBytesPerSec;
  U16 nBlockAlign;
  U16 wBitsPerSample;
  U16 cbSize;
} WAVEFORMATEX;

typedef struct DSBUFFERDESC {
  U32 dwSize;
  U32 dwFlags;
  U32 dwBufferBytes;
  WAVEFORMATEX *lpwfxFormat;
  DSMIXBINS *lpMixBins;
  U32 dwInputMixBin;
} DSBUFFERDESC;

S32 __stdcall DirectSoundCreate(void *device, IDirectSound **ds, void *outer);
U32 __stdcall IDirectSound_Release(IDirectSound *ds);
S32 __stdcall IDirectSound_CreateSoundBuffer(IDirectSound *ds, const DSBUFFERDESC *desc,
  IDirectSoundBuffer **buf, void *outer);
U32 __stdcall IDirectSoundBuffer_Release(IDirectSoundBuffer *buf);
S32 __stdcall IDirectSoundBuffer_SetFrequency(IDirectSoundBuffer *buf, U32 freq);
S32 __stdcall IDirectSoundBuffer_SetVolume(IDirectSoundBuffer *buf, S32 volume);
S32 __stdcall IDirectSoundBuffer_SetHeadroom(IDirectSoundBuffer *buf, U32 headroom);
S32 __stdcall IDirectSoundBuffer_SetMixBins(IDirectSoundBuffer *buf, const DSMIXBINS *bins);
S32 __stdcall IDirectSoundBuffer_SetMixBinVolumes(IDirectSoundBuffer *buf, const DSMIXBINS *bins);
S32 __stdcall IDirectSoundBuffer_Play(IDirectSoundBuffer *buf, U32 r1, U32 r2, U32 flags);
S32 __stdcall IDirectSoundBuffer_Stop(IDirectSoundBuffer *buf);
S32 __stdcall IDirectSoundBuffer_GetStatus(IDirectSoundBuffer *buf, U32 *status);
S32 __stdcall IDirectSoundBuffer_GetCurrentPosition(IDirectSoundBuffer *buf, U32 *play, U32 *write);
S32 __stdcall IDirectSoundBuffer_SetCurrentPosition(IDirectSoundBuffer *buf, U32 play);
S32 __stdcall IDirectSoundBuffer_SetBufferData(IDirectSoundBuffer *buf, void *data, U32 bytes);
S32 __stdcall IDirectSoundBuffer_Lock(IDirectSoundBuffer *buf, U32 offset, U32 bytes, void **ptr1,
  U32 *bytes1, void **ptr2, U32 *bytes2, U32 flags);
S32 __stdcall IDirectSoundBuffer_Unlock(IDirectSoundBuffer *buf, void *ptr1, U32 bytes1, void *ptr2,
  U32 bytes2);

// binkds.obj: a sound track's DirectSound stream, kept in BINKSND.snddata
typedef struct SNDCHANNEL {
  IDirectSoundBuffer *dsbuf;
  U8 *buffer;
  U32 bufsize;
  U32 chunk;                  // the smallest worthwhile write
  U32 freq;
  S32 bits;
  S32 chans;
  S32 volume;
  S32 pan;
  S32 started;
  volatile S32 paused;
  U32 writepos;
  U32 avail;                  // bytes Lock hands out
  U32 initavail;
  U32 lastwrite;              // the last cursors read
  U32 lastplay;
  U32 maxfree;                // free space that means the sound ran dry
  U32 lasttime;
  U32 interval;
  U32 len1;                   // the current lock
  void *ptr1;
  U32 len2;
  void *ptr2;
  U32 nmixbins;
  U32 nmixvols;
  U32 mixbins[8];
  U32 volbins[8];
  S32 volumes[8];
} SNDCHANNEL;

// radcb.obj: background callback threads. A handler runs one thread that
// calls its registered callbacks in priority order; a callback's node lives
// in the caller's control buffer (BINKIO.callback_control,
// BINK.snd_callback_buffer).
typedef S32 (RADLINK *RADCBPRIORITY)(void *data, U32 count);
typedef void (RADLINK *RADCBCALLBACK)(void *data, U32 count);

typedef struct RADCBNODE {
  struct RADCBNODE *next;     // the handler's list
  HANDLE mutex;               // held while the callback runs or is suspended
  struct RADCBNODE *sorted;   // this round's priority order
  U32 priority;
  RADCBPRIORITY getpriority;
  RADCBCALLBACK callback;
} RADCBNODE;

typedef struct RADCBHANDLER {
  S32 state;                  // 0 created, 1 running, 2 suspended, 3 freeing, 4 suspending
  U32 waitms;                 // the thread's period
  HANDLE event;               // signalled to end the thread
  HANDLE thread;
  U32 threadid;
  HANDLE mutex;               // held while the callbacks run
  RADCBNODE *list;
  U32 count;                  // rounds run
  S32 registered;
} RADCBHANDLER;

RADEXPFUNC S32 RADEXPLINK RADCB_try_to_suspend_callback(U32 handle, void PTR4 *data);
RADEXPFUNC void RADEXPLINK RADCB_suspend_callback(U32 handle, void PTR4 *data);
RADEXPFUNC void RADEXPLINK RADCB_resume_callback(U32 handle, void PTR4 *data);
RADEXPFUNC void RADEXPLINK RADCB_idle_on_callbacks(void);
RADEXPFUNC U32 RADEXPLINK RADCB_allocate_handler(S32 priority);
RADEXPFUNC void RADEXPLINK RADCB_resume_handler(U32 handle);
RADEXPFUNC void RADEXPLINK RADCB_suspend_2_callbacks(U32 handle1, void PTR4 *data1, U32 handle2,
  void PTR4 *data2);
RADEXPFUNC S32 RADEXPLINK RADCB_unregister_2_callbacks(U32 handle1, void PTR4 *data1, U32 handle2,
  void PTR4 *data2, S32 wait);
RADEXPFUNC void RADEXPLINK RADCB_register_callback(U32 handle, void PTR4 *data,
  S32 (RADLINK *priority)(void *data, U32 count), void (RADLINK *callback)(void *data, U32 count));

// binkfile.obj: the default IO's state, kept in BINKIO.iodata
typedef struct BINKFILE {
  HANDLE FileHandle;
  U32 FileIOPos;              // file offset of the next read
  U32 FileBufPos;             // file offset of the next byte handed out
  U8 *BufPos;                 // the next byte handed out
  U32 BufEmpty;               // free bytes in the buffer
  U32 unk14;
  U8 *Buffer;
  U8 *BufEnd;
  U8 *BufBack;                // where the next read lands
  U32 DontClose;              // opened from a caller's handle
  U32 StartFile;              // the movie's offset in the file
  U32 FileSize;
  U32 Simulate;               // simulated bytes per second
  S32 SimulateTime;           // simulated time owed
} BINKFILE;

RADEXPFUNC S32 RADEXPLINK BinkFileOpen(BINKIO PTR4 *bio, const char PTR4 *name, U32 flags);

// binkds.obj
RADEXPFUNC BINKSNDOPEN RADEXPLINK BinkOpenDirectSound(U32 param);

// the bit reader (Bink 1.6's layout). The reading macros work on the
// locals bits, cur and bitlen (VarBitsGet*) or on a VARBITS (*Struct).
typedef struct VARBITS {
  U32 bits;                   // the unread bits of the current word
  U32 *cur;                   // the next word
  U32 bitlen;                 // how many bits remain in bits
  U32 *init;                  // the first word
} VARBITS;

// Lossless bit-plane coefficient workspace and current bit result.
typedef struct BINKLOSSLESSWORK {
  U16 coeffs[64];
  U32 v;
} BINKLOSSLESSWORK;

#define VarBitsGet1(i)   if (bitlen) { (i) = bits & 1; bits >>= 1; bitlen--; }   else { (i) = *cur++; bits = (i) >> 1; bitlen = 31; (i) &= 1; }

#define VarBitsGetMask(i, n, mask)   if (bitlen >= (U32)(n)) { (i) = bits & (mask); bits >>= (n); bitlen -= (n); }   else { U32 _v = *cur; (i) = ((_v << bitlen) | bits) & (mask); bits = _v >> ((n) - bitlen);          bitlen += 32 - (n); cur++; }

#define VarBitsGet(i, n) VarBitsGetMask(i, n, (1 << (n)) - 1)

#define VarBitsGetStruct(vb, i, n)   if ((vb).bitlen >= (U32)(n)) { (i) = (vb).bits & ((1 << (n)) - 1); (vb).bits >>= (n); (vb).bitlen -= (n); }   else { U32 _v = *(vb).cur; (i) = ((_v << (vb).bitlen) | (vb).bits) & ((1 << (n)) - 1);          (vb).bits = _v >> ((n) - (vb).bitlen); (vb).bitlen += 32 - (n); (vb).cur++; }

// binkacd.obj
typedef struct BINKAC {
  U32 size;                   // transform size
  F32 scale;                  // 2 / sqrt(size)
  U32 blocksize;              // bytes of output per block
  U32 overlap;                // bytes blended into the next block
  U32 chans;
  S16 *outbuf;
  U32 first;                  // no previous block to blend
  U32 bands;
  U32 *bandtops;
  U32 *ip;                    // fft.obj's work area
  F32 *work;
  S16 *prev;                  // the previous block's tail
  U32 flags;
} BINKAC;

// a 29-bit packed float: 23 bits of mantissa, a 5-bit exponent, a sign
#define fxptof(x) ((((x) & 0x10000000) ? -1.0f : 1.0f) * (F32)(((x) >> 5) & 0x77fffff) * invertbins[(x) & 0x1f])

// fft.obj
RADEXPFUNC void RADEXPLINK ddct(S32 n, S32 isgn, F32 *a, U32 *ip, F32 *w);
RADEXPFUNC void RADEXPLINK rdft(S32 n, S32 isgn, F32 *a, U32 *ip, F32 *w);

RADEXPFUNC U32 RADEXPLINK BinkAudioDecompressOpen(U32 rate, U32 chans, U32 flags);
RADEXPFUNC void RADEXPLINK BinkAudioDecompress(U32 handle, void PTR4 *PTR4 *out, U32 PTR4 *outlen,
  void PTR4 *in, void PTR4 *PTR4 *inend);
RADEXPFUNC void RADEXPLINK BinkAudioDecompressClose(U32 handle);

// expand.obj
// a bundle's 16 Huffman tables (StartReadHuff8Bundle) and a bundle reader
typedef struct HUFF8 {
  U8 tabs[16][16];             // +0x000
  U32 reads[16];               // +0x100
  U8 *decodes[16];             // +0x140
  U32 last;                    // +0x180
} HUFF8;

typedef struct BUNDLE {
  U8 *cur;                     // +0x00
  U8 *end;                     // +0x04
  U32 unk08;                   // +0x08
  U32 unk0C;                   // +0x0C
  U8 tab[16];                  // +0x10
  U32 reads;                   // +0x20
  U8 *decode;                  // +0x24
  U32 lenbits;                 // +0x28
  U8 *start;                   // +0x2C
} BUNDLE;

RADEXPFUNC void RADEXPLINK ExpandBundleSizes(BUNDLEPOINTERS *bunp, U32 width);
RADEXPFUNC U32 RADEXPLINK ExpandBink(void *ycur, void *ynext, void *acur, void *anext, void *mask,
  U32 width, U32 height, U32 ywidth, U32 yheight, void *data, U32 key, BUNDLEPOINTERS *bunp,
  U32 openflags, U32 binktype);

// yuv.obj and the colour converters
// The format-specific row-pair converters and C edge helpers.
typedef void (__stdcall *ROWPAIRFN)(S32 n);
typedef void (*EDGEROWFN)(U32 x, U32 n);
typedef S32 (*EDGECOLFN)(U32 n, S32 x);
typedef struct BLITS {
  U32 bpp;
  U32 evenshift;
  ROWPAIRFN even;
  U32 oddshift;
  ROWPAIRFN odd;
  U32 monoshift;
  ROWPAIRFN mono;
  U32 even2shift;
  ROWPAIRFN even2;
  U32 odd2shift;
  ROWPAIRFN odd2;
  U32 mono2shift;
  ROWPAIRFN mono2;
  U32 dbltime[8];             // setdbls' words at [1], [3], [5], [7]
  U32 alntime[8];             // the edges' timing words at the same
  EDGEROWFN row;
  EDGECOLFN col;
  EDGEROWFN rowm;
  EDGECOLFN colm;
  EDGEROWFN row2w;
  EDGECOLFN col2w;
  EDGEROWFN rowm2w;
  EDGECOLFN colm2w;
  EDGEROWFN row2h;
  EDGECOLFN col2h;
  EDGEROWFN rowm2h;
  EDGECOLFN colm2h;
  EDGEROWFN row2wh;
  EDGECOLFN col2wh;
  EDGEROWFN rowm2wh;
  EDGECOLFN colm2wh;
  U32 unused[2];              // zero: the image's tables are 0xC0 apart
} BLITS;

void FreeYUVGlobalMemory(void);
RADEXPFUNC void RADEXPLINK YUV_init(U32 surface);
#define YUVBLIT(name) RADEXPFUNC void RADEXPLINK name(void *dest, U32 destx, U32 desty, S32 destpitch, \
  void *yplane, U32 srcx, U32 srcy, U32 srcw, U32 srch, U32 ywidth, U32 yheight, void *aplane, U32 flags)
#define YUVBLITMASK(name) RADEXPFUNC void RADEXPLINK name(void *dest, U32 destx, U32 desty, S32 destpitch, \
  void *mask, U32 maskpitch, void *yplane, U32 srcx, U32 srcy, U32 srcw, U32 srch, U32 ywidth, \
  U32 yheight, void *aplane, U32 flags)
YUVBLIT(YUV_blit_32bpp);
YUVBLIT(YUV_blit_32abpp);
YUVBLIT(YUV_blit_16bpp);
YUVBLIT(YUV_blit_16a4bpp);
YUVBLIT(YUV_blit_16a1bpp);
YUVBLIT(YUV_blit_YUY2);
YUVBLITMASK(YUV_blit_32bpp_mask);
YUVBLITMASK(YUV_blit_32abpp_mask);
YUVBLITMASK(YUV_blit_16bpp_mask);
YUVBLITMASK(YUV_blit_16a4bpp_mask);
YUVBLITMASK(YUV_blit_16a1bpp_mask);
YUVBLITMASK(YUV_blit_YUY2_mask);

// yuv.obj: the blit state S: two output rows, two Y rows and the shared U and V rows
// (one pair of output rows per pair of Y rows), the output pitch.
typedef struct YUVSTATE {
  U8 *out0;
  U8 *out1;
  U8 *y0;
  U8 *y1;
  U8 *u;
  U8 *v;
  U8 *a0;                     // the two alpha rows (32a, 16a4, 16a1)
  U8 *a1;
  S32 pitch;
  void *dest;                 // the blit's destination as given
} YUVSTATE;

/* Reconstructed private mask work state. All fields are used; this grouping
 * reproduces the original local allocation at 34B150, without padding. */
typedef struct BINKYUVMASKWORK
{
  U8 *secondmask;
  U32 origywidth;
  U32 yskip;
  S32 endy;
  S32 lastx;
  U32 uvskip32;
} BINKYUVMASKWORK;

void *memset(void *dst, S32 value, size_t size);
void *memcpy(void *dst, const void *src, size_t size);
char *strcpy(char *dst, const char *src);
S32 abs(S32 value);
F64 sqrt(F64 value);
F64 log10(F64 value);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// dsound.h's C++ wrappers, which binkds.cpp calls (binkds.obj carries their
// COMDAT copies)
struct IDirectSound
{
  __inline U32 __stdcall Release(void)
  {
    return IDirectSound_Release(this);
  }

  __inline S32 __stdcall CreateSoundBuffer(const DSBUFFERDESC *desc, IDirectSoundBuffer **buf, void *outer)
  {
    return IDirectSound_CreateSoundBuffer(this, desc, buf, outer);
  }
};

struct IDirectSoundBuffer
{
  __inline U32 __stdcall Release(void)
  {
    return IDirectSoundBuffer_Release(this);
  }

  __inline S32 __stdcall SetFrequency(U32 freq)
  {
    return IDirectSoundBuffer_SetFrequency(this, freq);
  }

  __inline S32 __stdcall SetVolume(S32 volume)
  {
    return IDirectSoundBuffer_SetVolume(this, volume);
  }

  __inline S32 __stdcall SetHeadroom(U32 headroom)
  {
    return IDirectSoundBuffer_SetHeadroom(this, headroom);
  }

  __inline S32 __stdcall SetMixBins(const DSMIXBINS *bins)
  {
    return IDirectSoundBuffer_SetMixBins(this, bins);
  }

  __inline S32 __stdcall SetMixBinVolumes(const DSMIXBINS *bins)
  {
    return IDirectSoundBuffer_SetMixBinVolumes(this, bins);
  }

  __inline S32 __stdcall Play(U32 r1, U32 r2, U32 flags)
  {
    return IDirectSoundBuffer_Play(this, r1, r2, flags);
  }

  __inline S32 __stdcall Stop(void)
  {
    return IDirectSoundBuffer_Stop(this);
  }

  __inline S32 __stdcall GetStatus(U32 *status)
  {
    return IDirectSoundBuffer_GetStatus(this, status);
  }

  __inline S32 __stdcall GetCurrentPosition(U32 *play, U32 *write)
  {
    return IDirectSoundBuffer_GetCurrentPosition(this, play, write);
  }

  __inline S32 __stdcall SetCurrentPosition(U32 play)
  {
    return IDirectSoundBuffer_SetCurrentPosition(this, play);
  }

  __inline S32 __stdcall SetBufferData(void *data, U32 bytes)
  {
    return IDirectSoundBuffer_SetBufferData(this, data, bytes);
  }

  __inline S32 __stdcall Lock(U32 offset, U32 bytes, void **ptr1, U32 *bytes1, void **ptr2, U32 *bytes2, U32 flags)
  {
    return IDirectSoundBuffer_Lock(this, offset, bytes, ptr1, bytes1, ptr2, bytes2, flags);
  }

  __inline S32 __stdcall Unlock(void *ptr1, U32 bytes1, void *ptr2, U32 bytes2)
  {
    return IDirectSoundBuffer_Unlock(this, ptr1, bytes1, ptr2, bytes2);
  }
};
#endif

#endif
