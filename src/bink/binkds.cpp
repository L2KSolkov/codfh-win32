/*
 * codfh-match: Bink's DirectSound output (the library's binkds.obj, C++): a
 * sound track's looping DirectSound buffer, the BINKSND callbacks that fill
 * it through Lock/Unlock, the cursor checks that find drop-outs, and the
 * sound system's open (BinkOpenDirectSound).
 */
#include "bink.h"
#include "binkint.h"

// RAD puts all of Bink's code in its BINK section (the image's 0x341480-0x34E01C).
#pragma code_seg("BINK")

#define CH(bs) ((SNDCHANNEL *)(bs)->snddata)

// BINKDATA, in the image's order (0x52F74C-0x52F770; its code reaches each there)
#pragma data_seg("BINKDATA")
IDirectSound *lpds = (IDirectSound *)-1;
extern "C" {
static S32 owned_DS = 0;
static U32 numopen = 0;
static U32 dslib = 0;
static S32 (__stdcall *dsc)(void *device, IDirectSound **ds, void *outer) = 0;
// two words nothing in the image reads
U32 unk_52F760 = 0;
U32 unk_52F764 = 0;
}
S32 emulated_ds = 0;
extern "C" {
static S32 opened_ds = 0;
// four words nothing in the image reads (0x52F770, before expand's data)
U32 unk_52F770[4] = { 0 };
}
#pragma data_seg()

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@45505555 @ 0x003EE928
// match: __real@38000100 @ 0x003EE92C
// match: ?lpds@@3PAUIDirectSound@@A @ 0x0052F74C
// match: _owned_DS @ 0x0052F750
// match: _numopen @ 0x0052F754
// match: _dslib @ 0x0052F758
// match: _dsc @ 0x0052F75C
// match: _unk_52F760 @ 0x0052F760
// match: _unk_52F764 @ 0x0052F764
// match: ?emulated_ds@@3JA @ 0x0052F768
// match: _opened_ds @ 0x0052F76C
// match: _unk_52F770 @ 0x0052F770

// match: ?set_rate_volume_and_pan@@YGXPAUSNDCHANNEL@@@Z @ 0x00345540

static void __stdcall set_rate_volume_and_pan(SNDCHANNEL *ch)
{
  DSMIXBINS mb;
  DSMIXBINVOLUMEPAIR pairs[8];
  S32 vol;
  U32 i;

  if (ch->dsbuf)
  {
    U32 fr = ch->freq;
    vol = ch->volume;
    if (vol > 32767)
      vol = 32767;
    ch->dsbuf->SetFrequency(fr);
    if (vol)
    {
      F32 db = (F32)log10((F32)vol * 3.0518509e-5f);

      vol = (S32)(db * 3333.3333f);
      if (vol < -10000)
        vol = -10000;
    }
    else
      vol = -10000;
    ch->dsbuf->SetVolume(vol);
    ch->dsbuf->SetHeadroom(0);

    mb.lpMixBinVolumePairs = pairs;
    if (ch->nmixbins == 0)
    {
      mb.dwMixBinCount = 6;
      pairs[0].dwMixBin = 0;
      pairs[0].lVolume = 0;
      pairs[1].dwMixBin = 1;
      pairs[1].lVolume = 0;
      pairs[2].dwMixBin = 2;
      pairs[2].lVolume = 0;
      pairs[3].dwMixBin = 3;
      pairs[3].lVolume = 0;
      pairs[4].dwMixBin = 4;
      pairs[4].lVolume = 0;
      pairs[5].dwMixBin = 5;
      pairs[5].lVolume = 0;
    }
    else
    {
      mb.dwMixBinCount = ch->nmixbins;
      for (i = 0; i < mb.dwMixBinCount; i++)
      {
        pairs[i].dwMixBin = ch->mixbins[i];
        pairs[i].lVolume = 0;
      }
    }
    ch->dsbuf->SetMixBins(&mb);

    if (ch->nmixvols)
    {
      mb.dwMixBinCount = ch->nmixvols;
      for (i = 0; i < ch->nmixvols; i++)
      {
        pairs[i].dwMixBin = ch->volbins[i];
        pairs[i].lVolume = ch->volumes[i];
      }
      ch->dsbuf->SetMixBinVolumes(&mb);
    }
  }
}

static void DS_lock(SNDCHANNEL *ch, S32 start, S32 len)
{
  ch->ptr1 = 0;
  ch->len1 = 0;
  ch->dsbuf->Lock(start, len, &ch->ptr1, &ch->len1, &ch->ptr2, &ch->len2, 0);
}

static void DS_unlock(SNDCHANNEL *ch)
{
  ch->dsbuf->Unlock(ch->ptr1, ch->len1, ch->ptr2, ch->len2);
}

// match: ?DS_clear@@YAXPAUSNDCHANNEL@@KK@Z @ 0x00345680
static void DS_clear(SNDCHANNEL *ch, U32 start, U32 len)
{
  U32 fill;

  DS_lock(ch, start, len);
  fill = (ch->bits == 16) ? 0 : 0x80808080;
  memset(ch->ptr1, fill, ch->len1);
  if (ch->ptr2)
    memset(ch->ptr2, fill, ch->len2);
  DS_unlock(ch);
}

static void DS_start_secondary(SNDCHANNEL *ch)
{
  ch->dsbuf->Play(0, 0, 1);
  ch->paused = 0;
}

static void DS_stop_secondary(SNDCHANNEL *ch)
{
  ch->dsbuf->Stop();
  ch->paused = 1;
}

// match: ?GoodGetCurrentPosition@@YAXPAUIDirectSoundBuffer@@PAK1@Z @ 0x00345730
static void GoodGetCurrentPosition(IDirectSoundBuffer *buf, U32 *play, U32 *write)
{
  U32 p0, w0, p1, w1;

  for (;;)
  {
    buf->GetCurrentPosition(&p0, &w0);
    buf->GetCurrentPosition(&p1, &w1);
    buf->GetCurrentPosition(&p1, &w1);
    if ((p1 - p0 < 0x400) && (w1 - w0 < 0x400))
      break;
  }
  *play = p1;
  *write = w1;
}

// match: ?Ready@@YGJPAUBINKSND@@@Z @ 0x003457A0
static S32 __stdcall Ready(BINKSND *bs)
{
  U32 play;
  U32 write;
  U32 free;

  if ((CH(bs)->paused) || (!bs->OnOff))
    return 0;
  if (!CH(bs)->started)
    return 1;

  write = CH(bs)->lastwrite;
  play = CH(bs)->lastplay;
  if (RADTimerRead() - CH(bs)->lasttime > 12)
  {
    U32 now;
    S32 played;
    S32 written;

    GoodGetCurrentPosition(CH(bs)->dsbuf, &play, &write);
    now = RADTimerRead();

    if (CH(bs)->lastwrite <= write)
      written = write - CH(bs)->lastwrite;
    else
      written = CH(bs)->bufsize - CH(bs)->lastwrite + write;
    if (CH(bs)->lastplay <= play)
      played = play - CH(bs)->lastplay;
    else
      played = CH(bs)->bufsize - CH(bs)->lastplay + play;
    if (abs(played - written) > (S32)(CH(bs)->bufsize >> 1))
      return 0;

    if (now - CH(bs)->lasttime >= CH(bs)->interval)
    {
      CH(bs)->lasttime = now;
      CH(bs)->lastplay = play;
      CH(bs)->lastwrite = write;
      goto dropped;
    }
    CH(bs)->lasttime = now;
    CH(bs)->lastplay = play;
    CH(bs)->lastwrite = write;
  }

  for (;;)
  {
    if (play < CH(bs)->writepos)
      free = CH(bs)->bufsize - CH(bs)->writepos + play;
    else
      free = play - CH(bs)->writepos;
    free = (free < 0x400) ? 0 : (free - 0x400) & ~3;

    if (free < CH(bs)->chunk)
    {
      if ((!CH(bs)->avail) || (!free))
        return 0;
    }
    if (free < CH(bs)->maxfree)
    {
      CH(bs)->avail = free;
      return 1;
    }

   dropped:
    bs->SoundDroppedOut = 1;
    DS_clear(CH(bs), CH(bs)->lastwrite, CH(bs)->chunk * 2);
    CH(bs)->writepos = CH(bs)->lastwrite + CH(bs)->chunk * 2;
    if (CH(bs)->writepos >= CH(bs)->bufsize)
      CH(bs)->writepos -= CH(bs)->bufsize;
  }
}

// match: ?Lock@@YGJPAUBINKSND@@PAPAEPAK@Z @ 0x00345950
static S32 __stdcall Lock(BINKSND *bs, U8 **addr, U32 *len)
{
  DS_lock(CH(bs), CH(bs)->writepos, CH(bs)->avail);
  *addr = (U8 *)CH(bs)->ptr1;
  *len = CH(bs)->len1;
  if ((CH(bs)->ptr1) && (CH(bs)->len1))
    return 1;
  return 0;
}

// match: ?start_streaming@@YAXPAUSNDCHANNEL@@@Z @ 0x003459E0
static void start_streaming(SNDCHANNEL *ch)
{
  U32 play;
  U32 write;
  U32 t;
  S32 moved = 0;

  ch->started = 1;
  DS_start_secondary(ch);
  t = RADTimerRead();
  ch->dsbuf->GetCurrentPosition(&play, &write);
  do
  {
    ch->dsbuf->GetCurrentPosition(&ch->lastplay, &ch->lastwrite);
    if (ch->lastplay != play)
      moved = 1;
    else if ((!moved) && (RADTimerRead() - t > 50))
    {
      moved = 0;
      DS_start_secondary(ch);
      t = RADTimerRead();
      ch->dsbuf->GetCurrentPosition(&play, &write);
    }
  } while (ch->lastplay > ch->chunk);
  ch->lasttime = RADTimerRead();
}

// match: ?Unlock@@YGJPAUBINKSND@@K@Z @ 0x00345A90
static S32 __stdcall Unlock(BINKSND *bs, U32 filled)
{
  CH(bs)->writepos += filled;
  if (CH(bs)->writepos >= CH(bs)->bufsize)
    CH(bs)->writepos -= CH(bs)->bufsize;
  CH(bs)->avail -= filled;
  DS_unlock(CH(bs));
  CH(bs)->ptr1 = 0;
  if ((!CH(bs)->started) && (!CH(bs)->avail) && (!CH(bs)->paused))
    start_streaming(CH(bs));
  return 1;
}

// match: ?Volume@@YGXPAUBINKSND@@J@Z @ 0x00345B20
static void __stdcall Volume(BINKSND *bs, S32 volume)
{
  if (volume > 32767)
    volume = 32767;
  CH(bs)->volume = volume;
  set_rate_volume_and_pan(CH(bs));
}

// match: ?Pan@@YGXPAUBINKSND@@J@Z @ 0x00345B50
static void __stdcall Pan(BINKSND *bs, S32 pan)
{
  if (pan > 65536)
    pan = 65536;
  CH(bs)->pan = pan;
  set_rate_volume_and_pan(CH(bs));
}

// match: ?MixBins@@YGXPAUBINKSND@@PAKK@Z @ 0x00345B80
static void __stdcall MixBins(BINKSND *bs, U32 *bins, U32 total)
{
  if (total > 8)
    total = 8;
  CH(bs)->nmixbins = total;
  memcpy(CH(bs)->mixbins, bins, total * 4);
  set_rate_volume_and_pan(CH(bs));
}

// match: ?MixBinVolumes@@YGXPAUBINKSND@@PAKPAJK@Z @ 0x00345BC0
static void __stdcall MixBinVolumes(BINKSND *bs, U32 *bins, S32 *volumes, U32 total)
{
  U32 i;

  if (total > 8)
    total = 8;
  CH(bs)->nmixvols = total;
  memcpy(CH(bs)->volbins, bins, total * 4);
  for (i = 0; i < total; i++)
  {
    S32 v = volumes[i];

    if (v > 32767)
      v = 32767;
    if (v)
    {
      F32 db = (F32)log10((F32)v * 3.0518509e-5f);

      v = (S32)(db * 3333.3333f);
      if (v < -10000)
        v = -10000;
    }
    else
      v = -10000;
    CH(bs)->volumes[i] = v;
  }
  set_rate_volume_and_pan(CH(bs));
}

// match: ?SetOnOff@@YGJPAUBINKSND@@J@Z @ 0x00345C70
static S32 __stdcall SetOnOff(BINKSND *bs, S32 status)
{
  if (status)
  {
    if (bs->OnOff == 0)
    {
      CH(bs)->started = 0;
      bs->OnOff = 1;
      CH(bs)->writepos = 0;
      CH(bs)->avail = CH(bs)->initavail;
    }
  }
  else if (bs->OnOff)
  {
    U32 st;

    CH(bs)->dsbuf->Stop();
    do
    {
      st = 0;
      CH(bs)->dsbuf->GetStatus(&st);
    } while (st);
    CH(bs)->dsbuf->SetCurrentPosition(0);
    DS_clear(CH(bs), 0, CH(bs)->bufsize);
    bs->OnOff = 0;
  }
  return bs->OnOff;
}

// match: ?Pause@@YGJPAUBINKSND@@J@Z @ 0x00345D00
static S32 __stdcall Pause(BINKSND *bs, S32 status)
{
  if (status)
  {
    if (CH(bs)->started)
      DS_stop_secondary(CH(bs));
    CH(bs)->paused = 1;
    return 1;
  }

  if ((CH(bs)->started) || (!CH(bs)->avail))
    start_streaming(CH(bs));
  CH(bs)->paused = 0;
  return CH(bs)->paused;
}

// match: ?open_ds@@YAJXZ @ 0x00345D70
static S32 open_ds(void)
{
  if (++opened_ds == 1)
  {
    if (owned_DS)
    {
      if (!dsc)
      {
        opened_ds = 0;
        return 0;
      }
      if (dsc(0, &lpds, 0) < 0)
      {
        opened_ds--;
        return 0;
      }
    }
    emulated_ds = 0;
  }
  return 1;
}

static void close_ds(void)
{
  if (--opened_ds == 0)
  {
    if ((owned_DS) && (lpds) && (lpds != (IDirectSound *)-1))
    {
      lpds->Release();
      lpds = (IDirectSound *)-1;
    }
  }
}

// match: ?Close@@YGXPAUBINKSND@@@Z @ 0x00345DC0
static void __stdcall Close(BINKSND *bs)
{
  if (CH(bs)->dsbuf)
  {
    DS_stop_secondary(CH(bs));
    CH(bs)->dsbuf->Release();
    CH(bs)->dsbuf = 0;
    radfree(CH(bs)->buffer);
    numopen--;
    close_ds();
  }
}

// match: ?Open@@YGJPAUBINKSND@@KJJKPAUBINK@@@Z @ 0x00345E40
static S32 __stdcall Open(BINKSND *bs, U32 freq, S32 bits, S32 chans, U32 flags, BINK *bink)
{
  WAVEFORMATEX wf;
  DSBUFFERDESC desc;
  U32 init;

  memset(bs, 0, sizeof(*bs));
  if (!open_ds())
    return 0;

  bs->bits = CH(bs)->bits = bits;
  bs->chans = CH(bs)->chans = chans;
  bs->freq = CH(bs)->freq = freq;
  bs->SoundDroppedOut = 0;

  wf.wFormatTag = 1;
  wf.nChannels = (U8)chans;
  wf.wBitsPerSample = (U16)bs->bits;
  wf.nSamplesPerSec = freq;
  wf.nAvgBytesPerSec = wf.nSamplesPerSec * (wf.wBitsPerSample / 8) * wf.nChannels;
  wf.nBlockAlign = (wf.wBitsPerSample / 8) * wf.nChannels;
  wf.cbSize = 0;

  CH(bs)->bufsize = ((wf.nAvgBytesPerSec * 600 / 1000) + 1023) & ~1023;
  CH(bs)->chunk = ((wf.nAvgBytesPerSec * 50 / 1000) + 255) & ~255;
  CH(bs)->maxfree = CH(bs)->bufsize * 90 / 100;
  CH(bs)->interval = 600 * 90 / 100;
  bs->Latency = 0;
  if (bink->FrameRate && bink->FrameRateDiv)
    init = (U32)((U64)bink->Frames * bink->FrameRateDiv * wf.nAvgBytesPerSec / bink->FrameRate);
  else
    init = CH(bs)->chunk;

  CH(bs)->buffer = (U8 *)radmalloc(CH(bs)->bufsize);
  memset(&desc, 0, sizeof(desc));
  desc.dwSize = sizeof(desc);
  desc.dwFlags = 0xa0;
  desc.dwBufferBytes = 0;
  desc.lpwfxFormat = &wf;
  if (lpds->CreateSoundBuffer(&desc, &CH(bs)->dsbuf, 0) < 0)
    return 0;
  CH(bs)->dsbuf->SetBufferData(CH(bs)->buffer, CH(bs)->bufsize);
  bs->BestSizeIn16 = CH(bs)->chunk;
  if (bs->bits == 8)
    bs->BestSizeIn16 *= 2;
  CH(bs)->volume = 32767;
  CH(bs)->pan = 32767;
  CH(bs)->nmixbins = 0;
  CH(bs)->nmixvols = 0;
  set_rate_volume_and_pan(CH(bs));
  DS_clear(CH(bs), 0, CH(bs)->bufsize);
  CH(bs)->writepos = 0;
  CH(bs)->started = 0;
  CH(bs)->avail = CH(bs)->initavail = (init < CH(bs)->bufsize) ? init : CH(bs)->bufsize;
  CH(bs)->paused = 0;
  bs->OnOff = 1;
  bs->Ready = Ready;
  bs->Lock = Lock;
  bs->Unlock = Unlock;
  bs->Volume = Volume;
  bs->Pan = Pan;
  bs->Pause = Pause;
  bs->SetOnOff = SetOnOff;
  bs->Close = Close;
  bs->MixBins = MixBins;
  bs->MixBinVols = MixBinVolumes;
  ++numopen;
  return 1;
}

// match: _BinkOpenDirectSound@4 @ 0x003460D0
RADEXPFUNC BINKSNDOPEN RADEXPLINK BinkOpenDirectSound(U32 param)
{
  if (lpds == (IDirectSound *)-1)
    lpds = (IDirectSound *)param;
  else if (lpds != (IDirectSound *)param)
  {
    if (numopen)
      return 0;
    lpds = (IDirectSound *)param;
  }

  if (lpds)
  {
    owned_DS = 0;
    dslib = 0;
  }
  else
  {
    owned_DS = 1;
    dsc = DirectSoundCreate;
  }

  if (!open_ds())
    return 0;
  close_ds();
  return Open;
}
