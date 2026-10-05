/*
 * codfh-match: Bink's player (RAD's binkread.c, the library's binkread.obj):
 * errors, sound priming and mixing, frame seeking, the IO and sound
 * background callbacks, opening, blitting, frame stepping and closing.
 */
#include "bink.h"
#include "binkint.h"

// RAD builds the player into its own BINK section (its switch tables too)
#pragma code_seg("BINK")

static char binkerr[256];
static BINKSNDSYSOPEN sysopen = 0;
static BINKSNDOPEN sndopen = 0;
static U32 numopensounds = 0;
static U32 cb_bink_IO = 0;
static U32 cb_bink_sound = 0;
static U32 ForceRate = (U32)-1;
static U32 ForceRateDiv;
static U32 IOBufferSize = (U32)-1;
static U32 Simulate = (U32)-1;
static U32 TotTracks = 1;
static U32 TrackNums[8] = {0};
static BINKIOOPEN UserOpen = 0;

#define BINKFROMIODATA(p) ((HBINK)((char *)(p) - offsetof(BINK, bio.callback_control)))
#define BINKFROMSNDDATA(p) ((HBINK)((char *)(p) - offsetof(BINK, snd_callback_buffer)))

// match: _bpopmalloc @ 0x00341480
static void *bpopmalloc(HBINK bink, U32 amt)
{
  bink->totalmem += popmalloctotal() + amt;
  return popmalloc(amt);
}

// match: _BinkSetError@4 @ 0x003414A0
RADEXPFUNC void RADEXPLINK BinkSetError(const char PTR4 *err)
{
  char *d = binkerr;

  *d = *err;
  while (*err)
  {
    d++;
    err++;
    *d = *err;
  }
}

// match: _BinkGetError@0 @ 0x003414D0
RADEXPFUNC char PTR4 *RADEXPLINK BinkGetError(void)
{
  return binkerr;
}

static S32 BinkSetSoundSystem(BINKSNDSYSOPEN open, U32 param)
{
  BINKSNDOPEN o;

  if (open == 0)
    return 0;
  if (sysopen)
  {
    if (sysopen != open)
    {
      if (numopensounds)
        return 0;
      sysopen = open;
    }
  }
  else
    sysopen = open;

  o = sysopen(param);
  if (o)
    sndopen = o;
  if (sndopen)
    return 1;
  return 0;
}

// match: _dosilence @ 0x003414E0
static U32 dosilence(BINKSND *bs)
{
  if (bs->sndamt < bs->sndprime)
  {
    U32 amt = bs->sndprime - bs->sndamt;
    U32 ms = (amt * 1000) / ((bs->freq * bs->bits * bs->chans) >> 3);

    bs->sndreadpos -= amt;
    if (bs->sndreadpos < bs->sndbuf)
    {
      U32 wrap = bs->sndbuf - bs->sndreadpos;

      bs->sndreadpos += bs->sndbufsize;
      memset(bs->sndbuf, 0, amt - wrap);
      memset(bs->sndreadpos, 0, wrap);
    }
    else
      memset(bs->sndreadpos, 0, amt);

    bs->sndamt += amt;
    return ms;
  }
  return 0;
}

static U8 *conv16to8(U16 *src, U8 *dest, U32 bytes)
{
  for (bytes >>= 1; bytes; bytes--)
    *dest++ = (U8)((*src++ >> 8) + 0x80);
  return dest;
}

// match: _checksound@4 @ 0x00341570
static void RADLINK checksound(HBINK bink)
{
  U32 len;
  U8 *addr;
  U32 i;
  void *cbdata;
  U32 avail;

  if (bink->bsnd[bink->playingtracks - 1].Ready == 0)
    return;

  cbdata = bink->snd_callback_buffer;
  if (!RADCB_try_to_suspend_callback(cb_bink_sound, cbdata))
    return;

  for (i = 0; i < bink->playingtracks; i++)
  {
    if (bink->bsnd[i].Ready(&bink->bsnd[i]))
    {
      do
      {
        if (bink->bsnd[i].sndamt <= bink->bsnd[i].BestSizeIn16)
        {
          if ((S32)bink->FrameNum <= (S32)bink->bsnd[i].sndendframe)
            break;
          if (bink->bsnd[i].sndamt == 0)
            break;
        }

        if (!bink->bsnd[i].Lock(&bink->bsnd[i], &addr, &len))
          break;

        if (bink->bsnd[i].sndconvert8)
          len *= 2;
        if (len > bink->bsnd[i].sndamt)
          len = bink->bsnd[i].sndamt;
        if ((S32)bink->FrameNum <= (S32)bink->bsnd[i].sndendframe)
          len &= bink->bsnd[i].BestSizeMask << bink->bsnd[i].sndconvert8;

        bink->bsnd[i].sndamt -= len;

        avail = bink->bsnd[i].sndend - bink->bsnd[i].sndreadpos;
        if (avail < len)
        {
          if (avail)
          {
            if (bink->bsnd[i].sndconvert8)
              addr = conv16to8((U16 *)bink->bsnd[i].sndreadpos, addr, avail);
            else
            {
              memcpy(addr, bink->bsnd[i].sndreadpos, avail);
              addr += avail;
            }
          }
          if (bink->bsnd[i].sndconvert8)
            conv16to8((U16 *)bink->bsnd[i].sndbuf, addr, len - avail);
          else
            memcpy(addr, bink->bsnd[i].sndbuf, len - avail);
          bink->bsnd[i].sndreadpos = bink->bsnd[i].sndbuf - avail + len;
        }
        else
        {
          if (bink->bsnd[i].sndconvert8)
            conv16to8((U16 *)bink->bsnd[i].sndreadpos, addr, len);
          else
            memcpy(addr, bink->bsnd[i].sndreadpos, len);
          bink->bsnd[i].sndreadpos += len;
        }

        if (bink->bsnd[i].sndconvert8)
          len >>= 1;
        bink->bsnd[i].Unlock(&bink->bsnd[i], len);
      } while (bink->bsnd[i].Ready(&bink->bsnd[i]));
    }
  }

  RADCB_resume_callback(cb_bink_sound, cbdata);
}

// match: _inittimer @ 0x00341830
// noinline: BinkWait, its other caller, is transcribed for now
static __declspec(noinline) void inittimer(HBINK bink)
{
  if (bink->startsynctime == 0)
  {
    bink->startsynctime = RADTimerRead();
    bink->startsyncframe = bink->playedframes - 1;
  }
}

// match: _GotoFrame @ 0x00341860
static void GotoFrame(HBINK bink, U32 frame)
{
  if (frame)
    frame--;

  bink->skipped_this_frame = 0;
  if (bink->playingtracks)
    checksound(bink);

  bink->LastFrameNum = bink->FrameNum;

  if (frame == 0)
  {
    U32 t = RADTimerRead();

    if (bink->lastresynctime == 0)
      bink->lastresynctime = t;
    if (t - bink->lastresynctime > 300000)
    {
      bink->lastresynctime = t;
      bink->doresync = 1;
    }
  }

  if (bink->preloadptr)
    bink->compframe = (U8 *)bink->preloadptr + ((bink->frameoffsets[frame] & ~1) - (bink->frameoffsets[0] & ~1));
  else
    bink->bio.ReadFrame(&bink->bio, frame, bink->frameoffsets[frame] & ~1, bink->compframe,
                        (bink->frameoffsets[frame + 1] & ~1) - (bink->frameoffsets[frame] & ~1));

  if (bink->playingtracks)
    checksound(bink);

  bink->FrameNum = frame + 1;
}

// match: _BinkSetSoundTrack@8 @ 0x00341940
RADEXPFUNC void RADEXPLINK BinkSetSoundTrack(U32 total_tracks, U32 PTR4 *tracks)
{
  U32 i;

  if (total_tracks > 8)
    total_tracks = 8;
  TotTracks = total_tracks;
  for (i = 0; i < total_tracks; i++)
    TrackNums[i] = tracks[i];
}

// match: _high1secrate @ 0x00341990
static U32 high1secrate(U32 *offs, S32 frames, S32 persec, U32 *highframe, U32 *allkeys)
{
  U32 keys = 1;
  U32 high = 0;
  U32 at = 0;
  S32 n = frames - persec;
  S32 i;

  for (i = 0; i < n; i++)
  {
    U32 r = offs[i + persec] - offs[i];

    if (r > high)
    {
      high = r;
      at = i;
    }
  }

  if (high == 0)
    high = mult64anddiv(offs[frames] - offs[0], persec, frames);

  for (i = 0; i < frames; i++)
  {
    if ((offs[i] & 1) == 0)
    {
      keys = 0;
      break;
    }
  }

  *allkeys = keys;
  *highframe = at;
  return high;
}

// match: _bink_get_priority_IO@8 @ 0x00341A40
static S32 RADLINK bink_get_priority_IO(void *data, U32 count)
{
  HBINK bink = BINKFROMIODATA(data);
  U32 pct = ((bink->bio.CurBufUsed + 1) * 100) / (bink->bio.CurBufSize + 1);

  if (pct < 50)
    return -1 - pct;
  if (bink->last_read_count != count)
    return 0x80000000 - bink->last_read_count;
  return 0;
}

// match: _bink_IO_callback@8 @ 0x00341A90
static void RADLINK bink_IO_callback(void *data, U32 count)
{
  HBINK bink = BINKFROMIODATA(data);

  bink->bio.Idle(&bink->bio);
  bink->last_read_count = count;
}

// match: _bink_suspend_io@4 @ 0x00341AB0
static void RADLINK bink_suspend_io(BINKIO *bio)
{
  RADCB_suspend_callback(cb_bink_IO, (void *)bio->callback_control);
}

// match: _bink_try_suspend_io@4 @ 0x00341AD0
static S32 RADLINK bink_try_suspend_io(BINKIO *bio)
{
  return RADCB_try_to_suspend_callback(cb_bink_IO, (void *)bio->callback_control);
}

// match: _bink_resume_io@4 @ 0x00341AF0
static void RADLINK bink_resume_io(BINKIO *bio)
{
  RADCB_resume_callback(cb_bink_IO, (void *)bio->callback_control);
}

// match: _bink_idle_on_io@4 @ 0x00341B10
static void RADLINK bink_idle_on_io(BINKIO *bio)
{
  RADCB_idle_on_callbacks();
}

// match: _bink_get_priority_sound@8 @ 0x00341B20
static S32 RADLINK bink_get_priority_sound(void *data, U32 count)
{
  HBINK bink = BINKFROMSNDDATA(data);

  if (bink->last_sound_count != count)
    return -1 - bink->last_sound_count;
  return 0;
}

// match: _bink_sound_callback@8 @ 0x00341B40
static void RADLINK bink_sound_callback(void *data, U32 count)
{
  HBINK bink = BINKFROMSNDDATA(data);

  if (bink->playingtracks)
    checksound(bink);
  bink->last_sound_count = count;
}

// match: _BinkCopyToBufferRect@44 @ 0x00342AA0
RADEXPFUNC S32 RADEXPLINK BinkCopyToBufferRect(HBINK bink, void *dest, S32 destpitch, U32 destheight,
                                               U32 destx, U32 desty, U32 srcx, U32 srcy, U32 srcw,
                                               U32 srch, U32 flags)
{
  S32 skipped = 0;
  U32 surface;
  S32 usemask;

  if (bink == 0)
    return 0;
  if (dest == 0)
    return 0;

  srcx = mult64anddiv(srcx, bink->decompwidth, bink->Width);
  srcw = mult64anddiv(srcw, bink->decompwidth, bink->Width);
  srcy = mult64anddiv(srcy, bink->decompheight, bink->Height);
  srch = mult64anddiv(srch, bink->decompheight, bink->Height);

  if (srcx >= bink->decompwidth)
    srcx = bink->decompwidth;
  if (srcy >= bink->decompheight)
    srcy = bink->decompheight;
  if (srcx + srcw > bink->decompwidth)
    srcw = bink->decompwidth - srcx;
  if (srcy + srch > bink->decompheight)
    srch = bink->decompheight - srcy;

  if ((srcw == 0) || (srch == 0) || (bink->skipped_this_frame))
    return bink->skipped_this_frame;

  flags |= bink->OpenFlags & 0x70030000;
  bink->bio.Working = 1;
  if (bink->APlane[0] == 0)
    flags &= ~BINKYAINVERT;

  surface = flags & BINKSURFACEMASK;
  YUV_init(surface);

  if (destpitch < 0)
  {
    dest = (U8 *)dest - (S32)(destheight - desty - 1) * destpitch;
    desty = 0;
  }

  if ((bink->playingtracks) && (bink->FrameRate) && (bink->Paused == 0))
  {
    U32 t;
    U32 frametime;
    U32 diff;

    inittimer(bink);
    t = RADTimerRead();

    frametime = mult64anddiv((bink->playedframes - bink->startsyncframe) * 1000, bink->FrameRateDiv,
                             bink->FrameRate);
    frametime = mult64andshift(frametime, bink->bsnd[0].VideoScale, 16);

    diff = t - bink->big_sound_skip_adj - bink->startsynctime;
    if (diff >= frametime)
    {
      diff -= frametime;
      if (diff > bink->twoframestime)
      {
        if (++bink->skipped_in_a_row > 3)
        {
          bink->skipped_in_a_row = 0;
          goto blit;
        }

        if (!(flags & BINKNOSKIP) && !(bink->OpenFlags & BINKNOSKIP))
        {
          bink->skipped_this_frame = 1;
          bink->skippedlastblit = 1;
          bink->skippedblits++;
          bink->bio.Working = 0;
          return 1;
        }

        skipped = 1;
        goto blit;
      }
      bink->skipped_in_a_row = 0;
    }
    bink->skippedlastblit = 0;
  }

 blit:
  if ((bink->preloadptr == 0) && (bink->bio.DoingARead == 0) &&
      (((bink->bio.CurBufUsed + 1) * 100) / (bink->bio.CurBufSize + 1) < 75))
  {
    if (RADCB_try_to_suspend_callback(cb_bink_IO, (void *)bink->bio.callback_control))
    {
      bink->bio.Idle(&bink->bio);
      RADCB_resume_callback(cb_bink_IO, (void *)bink->bio.callback_control);
    }
    else if (!(bink->OpenFlags & BINKNOTHREADEDIO))
      RADCB_idle_on_callbacks();
  }

  bink->lastblitflags = flags;

  usemask = (!(flags & BINKCOPYALL)) && (bink->skipcount >= bink->toofewskipstomask);
  if (!usemask)
  {
    switch (surface)
    {
      case BINKSURFACE32A:
        if (bink->APlane[0])
        {
          YUV_blit_32abpp(dest, destx, desty, destpitch, bink->YPlane[bink->PlaneNum], srcx, srcy, srcw,
                          srch, bink->YWidth, bink->YHeight, bink->APlane[bink->PlaneNum], flags);
          break;
        }
      case BINKSURFACE32:
        YUV_blit_32bpp(dest, destx, desty, destpitch, bink->YPlane[bink->PlaneNum], srcx, srcy, srcw,
                       srch, bink->YWidth, bink->YHeight, bink->APlane[bink->PlaneNum], flags);
        break;
      case BINKSURFACE5551:
        if (bink->APlane[0])
        {
          YUV_blit_16a1bpp(dest, destx, desty, destpitch, bink->YPlane[bink->PlaneNum], srcx, srcy,
                           srcw, srch, bink->YWidth, bink->YHeight, bink->APlane[bink->PlaneNum], flags);
          break;
        }
      case BINKSURFACE4444:
        if (bink->APlane[0])
        {
          YUV_blit_16a4bpp(dest, destx, desty, destpitch, bink->YPlane[bink->PlaneNum], srcx, srcy,
                           srcw, srch, bink->YWidth, bink->YHeight, bink->APlane[bink->PlaneNum], flags);
          break;
        }
      case BINKSURFACE555:
      case BINKSURFACE565:
      case BINKSURFACE655:
      case BINKSURFACE664:
        YUV_blit_16bpp(dest, destx, desty, destpitch, bink->YPlane[bink->PlaneNum], srcx, srcy, srcw,
                       srch, bink->YWidth, bink->YHeight, bink->APlane[bink->PlaneNum], flags);
        break;
      case BINKSURFACEYUY2:
        YUV_blit_YUY2(dest, destx, desty, destpitch, bink->YPlane[bink->PlaneNum], srcx, srcy, srcw,
                      srch, bink->YWidth, bink->YHeight, bink->APlane[bink->PlaneNum], flags);
        break;
    }
  }
  else
  {
    switch (surface)
    {
      case BINKSURFACE32A:
        if (bink->APlane[0])
        {
          YUV_blit_32abpp_mask(dest, destx, desty, destpitch, bink->MaskPlane, bink->MaskPitch,
                               bink->YPlane[bink->PlaneNum], srcx, srcy, srcw, srch, bink->YWidth,
                               bink->YHeight, bink->APlane[bink->PlaneNum], flags);
          break;
        }
      case BINKSURFACE32:
        YUV_blit_32bpp_mask(dest, destx, desty, destpitch, bink->MaskPlane, bink->MaskPitch,
                            bink->YPlane[bink->PlaneNum], srcx, srcy, srcw, srch, bink->YWidth,
                            bink->YHeight, bink->APlane[bink->PlaneNum], flags);
        break;
      case BINKSURFACE5551:
        if (bink->APlane[0])
        {
          YUV_blit_16a1bpp_mask(dest, destx, desty, destpitch, bink->MaskPlane, bink->MaskPitch,
                                bink->YPlane[bink->PlaneNum], srcx, srcy, srcw, srch, bink->YWidth,
                                bink->YHeight, bink->APlane[bink->PlaneNum], flags);
          break;
        }
      case BINKSURFACE4444:
        if (bink->APlane[0])
        {
          YUV_blit_16a4bpp_mask(dest, destx, desty, destpitch, bink->MaskPlane, bink->MaskPitch,
                                bink->YPlane[bink->PlaneNum], srcx, srcy, srcw, srch, bink->YWidth,
                                bink->YHeight, bink->APlane[bink->PlaneNum], flags);
          break;
        }
      case BINKSURFACE555:
      case BINKSURFACE565:
      case BINKSURFACE655:
      case BINKSURFACE664:
        YUV_blit_16bpp_mask(dest, destx, desty, destpitch, bink->MaskPlane, bink->MaskPitch,
                            bink->YPlane[bink->PlaneNum], srcx, srcy, srcw, srch, bink->YWidth,
                            bink->YHeight, bink->APlane[bink->PlaneNum], flags);
        break;
      case BINKSURFACEYUY2:
        YUV_blit_YUY2_mask(dest, destx, desty, destpitch, bink->MaskPlane, bink->MaskPitch,
                           bink->YPlane[bink->PlaneNum], srcx, srcy, srcw, srch, bink->YWidth,
                           bink->YHeight, bink->APlane[bink->PlaneNum], flags);
        break;
    }
  }
  bink->bio.Working = 0;
  return skipped;
}

// match: _BinkOpen@8 @ 0x00341B80
RADEXPFUNC HBINK RADEXPLINK BinkOpen(const char PTR4 *name, U32 flags)
{
  BINKHDR h;
  BINK b;
  U32 sim;
  U32 frommem;
  U32 allkeys;
  U32 i;
  BINKIOOPEN io = BinkFileOpen;
  HBINK bink;

  if (!(flags & BINKSNDTRACK))
  {
    TotTracks = 1;
    TrackNums[0] = 0;
  }

  memset(&b, 0, sizeof(b));
  b.timeopen = RADTimerRead();

  binkerr[0] = 0;
  frommem = flags & BINKFROMMEMORY;

  if (frommem)
  {
    memcpy(&h, name, sizeof(h));
  }
  else
  {
    if ((flags & BINKIOPROCESSOR) && (UserOpen))
      io = UserOpen;
    UserOpen = 0;
    if (!io(&b.bio, name, flags))
    {
      if (binkerr[0] == 0)
        BinkSetError("Error opening file.");
      return 0;
    }
    b.bio.ReadHeader(&b.bio, 0, &h, sizeof(h));
  }

  if ((h.Marker != BINKMARKER1) && (h.Marker != BINKMARKER2) && (h.Marker != BINKMARKER3) &&
      (h.Marker != BINKMARKER4))
  {
    BinkSetError("Not a Bink file.");
    goto fail;
  }

  if (h.Frames == 0)
  {
    BinkSetError("The file doesn't contain any compressed frames yet.");
    goto fail;
  }

  b.Width = h.Width;
  b.Height = h.Height;
  b.decompwidth = h.Width;
  b.decompheight = h.Height;
  b.UVWidth = (((h.Width + 1) >> 1) + 7) & ~7;
  b.UVHeight = (((h.Height + 1) >> 1) + 7) & ~7;
  b.YWidth = b.UVWidth * 2;
  b.BinkType = h.Flags;
  b.YHeight = b.UVHeight * 2;
  b.MaskPitch = b.YWidth >> 4;
  b.OpenFlags = ((h.Flags & BINKGRAYSCALE) | flags) & 0x8fffffff;
  if (!(h.Flags & BINKALPHA))
    b.OpenFlags &= ~BINKALPHA;

  if ((flags & BINKCOPYNOSCALING) != BINKCOPYNOSCALING)
  {
    if (flags & BINKCOPYNOSCALING)
      b.OpenFlags |= flags & BINKCOPYNOSCALING;
    else
      b.OpenFlags |= h.Flags & BINKCOPYNOSCALING;

    switch (b.OpenFlags & BINKCOPYNOSCALING)
    {
      case BINKCOPY2XH:
      case BINKCOPY2XHI:
        b.Height = h.Height * 2;
        break;
      case BINKCOPY2XW:
        b.Width = h.Width * 2;
        break;
      case BINKCOPY2XWH:
      case BINKCOPY2XWHI:
        b.Width = h.Width * 2;
        b.Height = h.Height * 2;
        break;
    }
  }

  if ((h.Marker == BINKMARKER1) || (h.Marker == BINKMARKER2))
    b.OpenFlags |= BINKOLDFRAMEFORMAT | BINKRBINVERT;
  else if (h.Marker == BINKMARKER3)
    b.OpenFlags |= BINKOLDFRAMEFORMAT;

  b.Frames = h.Frames;
  b.InternalFrames = h.InternalFrames;
  if ((flags & BINKFRAMERATE) && (ForceRate != (U32)-1))
  {
    b.FrameRate = ForceRate;
    b.FrameRateDiv = ForceRateDiv;
    ForceRate = (U32)-1;
  }
  else
  {
    b.FrameRate = h.FrameRate;
    b.FrameRateDiv = h.FrameRateDiv;
  }
  b.Size = h.Size;
  b.NumTracks = h.NumTracks;
  b.LargestFrameSize = h.LargestFrameSize;
  b.fileframerate = h.FrameRate;
  b.fileframeratediv = h.FrameRateDiv;
  b.MaskLength = (b.MaskPitch * b.YHeight) >> 4;
  b.toofewskipstomask = b.MaskLength >> 2;
  b.runtimeframes = (h.FrameRate + (h.FrameRateDiv >> 1)) / h.FrameRateDiv;
  if (b.runtimeframes == 0)
    b.runtimeframes = 1;

  pushmalloc(&b.MaskPlane, b.MaskLength + 16);
  pushmalloc(&b.rtframetimes, b.runtimeframes * 4);
  pushmalloc(&b.rtadecomptimes, b.runtimeframes * 4);
  pushmalloc(&b.rtvdecomptimes, b.runtimeframes * 4);
  pushmalloc(&b.rtblittimes, b.runtimeframes * 4);
  pushmalloc(&b.rtreadtimes, b.runtimeframes * 4);
  pushmalloc(&b.rtidlereadtimes, b.runtimeframes * 4);
  pushmalloc(&b.rtthreadreadtimes, b.runtimeframes * 4);
  pushmalloc(&b.bsnd, (TotTracks ? TotTracks : 1) * sizeof(BINKSND));
  pushmalloc(&b.trackindexes, TotTracks * 4);

  ExpandBundleSizes(&b.bunp, b.YWidth);
  pushmalloc(&b.bunp.typeptr, (U32)b.bunp.typeptr);
  pushmalloc(&b.bunp.type16ptr, (U32)b.bunp.type16ptr);
  pushmalloc(&b.bunp.colorptr, (U32)b.bunp.colorptr);
  pushmalloc(&b.bunp.bits2ptr, (U32)b.bunp.bits2ptr);
  pushmalloc(&b.bunp.motionXptr, (U32)b.bunp.motionXptr);
  pushmalloc(&b.bunp.motionYptr, (U32)b.bunp.motionYptr);
  pushmalloc(&b.bunp.dctptr, (U32)b.bunp.dctptr);
  pushmalloc(&b.bunp.mdctptr, (U32)b.bunp.mdctptr);
  pushmalloc(&b.bunp.patptr, (U32)b.bunp.patptr);

  if (!frommem)
  {
    pushmalloc(&b.frameoffsets, b.InternalFrames * 4 + 4);
    pushmalloc(&b.tracksizes, b.NumTracks * 4);
    pushmalloc(&b.tracktypes, b.NumTracks * 4);
    pushmalloc(&b.trackIDs, b.NumTracks * 4);
  }

  b.totalmem += popmalloctotal() + sizeof(BINK);
  bink = (HBINK)popmalloc(sizeof(BINK));
  if (bink == 0)
    goto nomem;

  *bink = b;
  bink->bio.bink = bink;

  bink->rtadecomptimes[0] = 0;
  bink->rtvdecomptimes[0] = 0;
  bink->rtblittimes[0] = 0;
  bink->rtreadtimes[0] = 0;
  bink->rtidlereadtimes[0] = 0;
  bink->rtthreadreadtimes[0] = 0;

  if (frommem)
  {
    bink->tracksizes = (U32 *)(name + sizeof(BINKHDR));
    bink->tracktypes = (U32 *)(name + sizeof(BINKHDR)) + bink->NumTracks;
    bink->trackIDs = (S32 *)(name + sizeof(BINKHDR)) + bink->NumTracks * 2;
    bink->frameoffsets = (U32 *)(name + sizeof(BINKHDR)) + bink->NumTracks * 3;
  }
  else
  {
    bink->bio.ReadHeader(&bink->bio, -1, bink->tracksizes, bink->NumTracks * 4);
    bink->bio.ReadHeader(&bink->bio, -1, bink->tracktypes, bink->NumTracks * 4);
    bink->bio.ReadHeader(&bink->bio, -1, bink->trackIDs, bink->NumTracks * 4);
    bink->bio.ReadHeader(&bink->bio, -1, bink->frameoffsets, bink->InternalFrames * 4 + 4);
  }

  bink->Highest1SecRate = high1secrate(bink->frameoffsets, bink->Frames, bink->runtimeframes,
                                       &bink->Highest1SecFrame, &allkeys);

  if (bink->OpenFlags & BINKALPHA)
  {
    pushmalloc(&bink->APlane[0], bink->YWidth * bink->YHeight);
    if (!allkeys)
      pushmalloc(&bink->APlane[1], bink->YWidth * bink->YHeight);
  }
  if (!allkeys)
    pushmalloc(&bink->YPlane[1], bink->YWidth * bink->YHeight + bink->UVWidth * bink->UVHeight * 2);

  bink->YPlane[0] = bpopmalloc(bink, bink->YWidth * bink->YHeight + bink->UVWidth * bink->UVHeight * 2);
  if (bink->YPlane[0] == 0)
    goto freebink;

  if (allkeys)
  {
    bink->YPlane[1] = bink->YPlane[0];
    bink->APlane[1] = bink->APlane[0];
  }

  if ((flags & BINKIOSIZE) && (IOBufferSize != (U32)-1))
  {
    bink->iosize = IOBufferSize;
    IOBufferSize = (U32)-1;
  }
  else
    bink->iosize = bink->Highest1SecRate;

  if ((flags & BINKSIMULATE) && (Simulate != (U32)-1))
  {
    sim = Simulate;
    Simulate = (U32)-1;
  }
  else
    sim = 0;

  if (frommem)
  {
    bink->preloadptr = (U8 *)name + (bink->frameoffsets[0] & ~1);
  }
  else
  {
    bink->iosize = bink->bio.GetBufferSize(&bink->bio, bink->iosize);
    if (bink->iosize >= (bink->Size * 9) / 10)
    {
      flags |= BINKPRELOADALL;
      bink->OpenFlags |= BINKPRELOADALL;
    }

    if (flags & BINKPRELOADALL)
    {
      U32 size = bink->Size - (bink->frameoffsets[0] & ~1) + 8;

      bink->preloadptr = bpopmalloc(bink, size);
      if (bink->preloadptr == 0)
      {
        radfree(b.YPlane[0]);
       freebink:
        radfree(bink);
       nomem:
        BinkSetError("Out of memory.");
       fail:
        if (!(flags & BINKFROMMEMORY))
          b.bio.Close(&b.bio);
        return 0;
      }

      bink->bio.SetInfo(&bink->bio, 0, 0, bink->Size + 8, sim);
      bink->bio.ReadFrame(&bink->bio, 0, bink->frameoffsets[0] & ~1, bink->preloadptr, size);
      bink->bio.Close(&bink->bio);
      bink->bio.ForegroundTime = 0;
    }
    else
    {
      pushmalloc(&bink->compframe, bink->LargestFrameSize);
      bink->ioptr = (U8 *)bpopmalloc(bink, bink->iosize);
      if (bink->ioptr == 0)
        bink->iosize = 0;
      bink->bio.SetInfo(&bink->bio, bink->ioptr, bink->iosize, bink->Size + 8, sim);
    }
  }

  ((U8 *)bink->MaskPlane)[bink->MaskLength] = 0;
  bink->FrameNum = (U32)-1;

  if (bink->FrameRate)
    bink->twoframestime = mult64anddiv(2000, bink->FrameRateDiv, bink->FrameRate);
  else
    bink->twoframestime = 2000;

  bink->videoon = 1;
  GotoFrame(bink, 1);
  bink->timeopen = RADTimerRead() - bink->timeopen;

  bink->bsnd[0].VideoScale = 0x10000;
  bink->playingtracks = 0;

  if ((bink->NumTracks) && (TotTracks))
  {
    for (i = 0; i < TotTracks; i++)
    {
      S32 j;

      for (j = 0; j < bink->NumTracks; j++)
      {
        if (bink->trackIDs[j] == (S32)TrackNums[i])
        {
          bink->trackindexes[bink->playingtracks++] = j;
          break;
        }
      }
    }
  }

  TrackNums[0] = 0;
  TotTracks = 1;

  for (i = 0; i < bink->playingtracks;)
  {
    bink->bsnd[i].sndbuf = 0;

    if (bink->tracktypes[bink->trackindexes[i]] & 0x90000000)
    {
      if ((sndopen) || (BinkSetSoundSystem(BinkOpenDirectSound, 0)))
      {
        S32 freq = bink->tracktypes[bink->trackindexes[i]] & 0xffff;

        if ((b.FrameRate) && (b.FrameRateDiv))
          freq = (U32)(((F64)freq * (S32)b.fileframeratediv * (S32)b.FrameRate) /
                       ((F64)(S32)b.fileframerate * (S32)b.FrameRateDiv));

        if (sndopen(&bink->bsnd[i], freq, ((bink->tracktypes[bink->trackindexes[i]] >> 30) & 1) * 8 + 8, ((bink->tracktypes[bink->trackindexes[i]] >> 29) & 1) + 1,
                    bink->OpenFlags, bink))
        {
          if (bink->bsnd[i].BestSizeMask == 0)
            bink->bsnd[i].BestSizeMask = 0xffffffff;

          bink->bsnd[i].sndbufsize = (bink->tracksizes[bink->trackindexes[i]] + 0xff) & ~0xff;
          bink->bsnd[i].sndbuf = (U8 *)bpopmalloc(bink, bink->bsnd[i].sndbufsize);
          if (bink->bsnd[i].sndbuf == 0)
          {
            bink->bsnd[i].Close(&bink->bsnd[i]);
          }
          else
          {
            U32 latency;

            numopensounds++;
            bink->bsnd[i].sndconvert8 = ((((bink->tracktypes[bink->trackindexes[i]] >> 30) & 1) * 8) == 0);
            bink->bsnd[i].sndend = bink->bsnd[i].sndbuf + bink->bsnd[i].sndbufsize;
            bink->bsnd[i].sndwritepos = bink->bsnd[i].sndbuf;
            bink->bsnd[i].sndreadpos = bink->bsnd[i].sndbuf;

            latency = 750 - bink->bsnd[i].Latency;
            bink->bsnd[i].sndprime = mult64anddiv((((bink->tracktypes[bink->trackindexes[i]] >> 29) & 1) + 1) * freq * 2, latency, 1000) & ~3;
            if (bink->bsnd[i].sndprime > bink->bsnd[i].sndbufsize)
              bink->bsnd[i].sndprime = bink->bsnd[i].sndbufsize;

            bink->bsnd[i].sndcomp = BinkAudioDecompressOpen(bink->tracktypes[bink->trackindexes[i]] & 0xffff, ((bink->tracktypes[bink->trackindexes[i]] >> 29) & 1) + 1,
                                                            (!(bink->tracktypes[bink->trackindexes[i]] & 0x80000000) && (bink->tracktypes[bink->trackindexes[i]] & 0x10000000)) ? 1 : 0);
            bink->bsnd[i].sndendframe = bink->Frames - (bink->fileframerate * 3) / (bink->fileframeratediv * 4);
            bink->bsnd[i].sndamt = 0;
          }
        }
      }
    }

    if (bink->bsnd[i].VideoScale == 0)
      bink->bsnd[i].VideoScale = 0x10000;

    if (bink->bsnd[i].sndbuf == 0)
    {
      bink->playingtracks--;
      memcpy(&bink->trackindexes[i], &bink->trackindexes[i + 1], (bink->playingtracks - i) * 4);
    }
    else
      i++;
  }

  if (bink->playingtracks)
  {
    bink->soundon = 1;
    if (!bink->bsnd[0].NoThreadService)
    {
      if (!cb_bink_sound)
      {
        cb_bink_sound = RADCB_allocate_handler(-13);
        RADCB_resume_handler(cb_bink_sound);
      }
      RADCB_register_callback(cb_bink_sound, bink->snd_callback_buffer, bink_get_priority_sound,
                              bink_sound_callback);
    }
  }

  if (!(bink->OpenFlags & BINKNOTHREADEDIO) && (bink->preloadptr == 0))
  {
    if (!cb_bink_IO)
    {
      cb_bink_IO = RADCB_allocate_handler(5);
      RADCB_resume_handler(cb_bink_IO);
    }
    RADCB_register_callback(cb_bink_IO, (void *)bink->bio.callback_control, bink_get_priority_IO,
                            bink_IO_callback);
  }

  bink->bio.resume_callback = bink_resume_io;
  bink->bio.suspend_callback = bink_suspend_io;
  bink->bio.try_suspend_callback = bink_try_suspend_io;
  bink->bio.idle_on_callback = bink_idle_on_io;

  if ((bink->preloadptr == 0) && !(flags & BINKNOFILLIOBUF))
  {
    while (bink->bio.Idle(&bink->bio))
      ;
  }

  return bink;
}

// match: _endframe @ 0x00343360
static void endframe(HBINK bink, U32 time)
{
  if (bink->entireframetime)
  {
    U32 t = time - bink->entireframetime;

    bink->entireframetime = 0;
    if (t > bink->slowestframetime)
    {
      bink->slowest2frametime = bink->slowestframetime;
      bink->slowest2frame = bink->slowestframe;
      bink->slowestframetime = t;
      bink->slowestframe = bink->FrameNum;
    }
    else if (t > bink->slowest2frametime)
    {
      bink->slowest2frametime = t;
      bink->slowest2frame = bink->FrameNum;
    }
  }
}

// match: _BinkWait@4 @ 0x003433C0
RADEXPFUNC S32 RADEXPLINK BinkWait(HBINK bink)
{
  U32 start;
  U32 t;

  if (bink == 0)
    return 0;
  if ((bink->playedframes == 0) && (bink->Paused == 0))
    return 0;
  if (bink->ReadError)
    return 0;

  start = bink->startsynctime;
  if (start == 0)
  {
    inittimer(bink);
    start = bink->startsynctime;
  }

  if (bink->playingtracks)
    checksound(bink);

  t = RADTimerRead();
  if (bink->startblittime)
  {
    bink->timeblit += t - bink->startblittime;
    bink->startblittime = 0;
  }
  endframe(bink, t);

  if ((bink->Paused == 0) && ((bink->playingtracks == 0) || (bink->soundon)))
  {
    if (bink->FrameRate)
    {
      U32 frametime;
      S32 diff;

      frametime = mult64anddiv((bink->playedframes - bink->startsyncframe) * 1000, bink->FrameRateDiv,
                               bink->FrameRate);
      frametime = mult64andshift(frametime, bink->bsnd[0].VideoScale, 16);

      diff = t - bink->big_sound_skip_adj - start;
      if (diff < (S32)frametime)
        goto service;

      diff -= frametime;
      if (diff > (S32)bink->twoframestime)
      {
        if (bink->playingtracks == 0)
        {
          bink->startsynctime = t;
          bink->startsyncframe = bink->playedframes - 1;
        }
        else
        {
          bink->big_sound_skip_adj = diff;
          bink->big_sound_skip_reduce = mult64anddiv(bink->big_sound_skip_adj, bink->FrameRateDiv, bink->FrameRate);
        }
      }

      if (bink->big_sound_skip_adj < bink->big_sound_skip_reduce)
        bink->big_sound_skip_adj = 0;
      else
        bink->big_sound_skip_adj -= bink->big_sound_skip_reduce;
    }
    return 0;
  }

 service:
  if (bink->preloadptr == 0)
  {
    if (RADCB_try_to_suspend_callback(cb_bink_IO, (void *)bink->bio.callback_control))
    {
      bink->bio.Idle(&bink->bio);
      RADCB_resume_callback(cb_bink_IO, (void *)bink->bio.callback_control);
    }
  }
  return 1;
}

// match: _BinkPause@8 @ 0x003435C0
RADEXPFUNC S32 RADEXPLINK BinkPause(HBINK bink, S32 pause)
{
  U32 i;
  U32 t;

  if (bink == 0)
    return 0;

  t = RADTimerRead();
  if (bink->startblittime)
  {
    bink->timeblit += t - bink->startblittime;
    bink->startblittime = 0;
  }
  endframe(bink, t);

  if ((pause == 0) && (bink->Paused))
  {
    bink->startsynctime = 0;
    bink->big_sound_skip_adj = 0;
  }
  bink->Paused = pause;

  for (i = 0; i < bink->playingtracks; i++)
    bink->bsnd[i].Pause(&bink->bsnd[i], pause);

  if ((bink->playedframes) && (bink->playingtracks))
    checksound(bink);

  return bink->Paused;
}

// match: _idtoindex @ 0x00343680
static S32 idtoindex(HBINK bink, S32 id)
{
  S32 i;

  for (i = 0; i < (S32)bink->playingtracks; i++)
  {
    if (bink->trackIDs[bink->trackindexes[i]] == id)
      return i;
  }
  return -1;
}

// match: _BinkSetVolume@12 @ 0x003436C0
RADEXPFUNC void RADEXPLINK BinkSetVolume(HBINK bink, U32 trackid, S32 volume)
{
  if ((bink) && (bink->playingtracks))
  {
    S32 i = idtoindex(bink, trackid);

    if ((i != -1) && (bink->bsnd[i].Volume))
      bink->bsnd[i].Volume(&bink->bsnd[i], volume);
  }
}

// match: _BinkGetTrackID@8 @ 0x00343710
RADEXPFUNC U32 RADEXPLINK BinkGetTrackID(HBINK bink, U32 trackindex)
{
  if (bink)
    return bink->trackIDs[trackindex];
  return 0;
}

// match: _BinkSetSoundOnOff@8 @ 0x00343730
RADEXPFUNC S32 RADEXPLINK BinkSetSoundOnOff(HBINK bink, S32 onoff)
{
  S32 ret = 0;
  U32 i;
  S32 suspended;

  if (bink)
  {
    suspended = 0;
    for (i = 0; i < bink->playingtracks; i++)
    {
      if (bink->bsnd[i].SetOnOff)
      {
        if (!suspended)
        {
          suspended = 1;
          RADCB_suspend_callback(cb_bink_sound, bink->snd_callback_buffer);
        }

        if (bink->bsnd[i].SetOnOff(&bink->bsnd[i], onoff != 0))
        {
          ret = 1;
          if (!bink->soundon)
          {
            bink->soundon = 1;
            bink->startsynctime = 0;
            bink->big_sound_skip_adj = 0;
          }
        }
        else if (bink->soundon)
        {
          bink->bsnd[i].sndwritepos = bink->bsnd[i].sndbuf;
          bink->bsnd[i].sndreadpos = bink->bsnd[i].sndbuf;
          bink->bsnd[i].sndamt = 0;
          if ((bink->FrameNum != 1) || (bink->lastdecompframe == 1))
            dosilence(&bink->bsnd[i]);
          bink->soundon = 0;
        }
      }
    }

    if (suspended)
      RADCB_resume_callback(cb_bink_sound, bink->snd_callback_buffer);
  }
  return ret;
}

// match: _BinkCopyToBuffer@28 @ 0x00343870
RADEXPFUNC S32 RADEXPLINK BinkCopyToBuffer(HBINK bink, void *dest, S32 destpitch, U32 destheight,
                                           U32 destx, U32 desty, U32 flags)
{
  return BinkCopyToBufferRect(bink, dest, destpitch, destheight, destx, desty, 0, 0, bink->Width,
                              bink->Height, flags);
}

// match: _BinkNextFrame@4 @ 0x00343E90
RADEXPFUNC void RADEXPLINK BinkNextFrame(HBINK bink)
{
  U32 i;
  U32 dropped = 0;
  U32 t;

  if (bink == 0)
    return;

  bink->bio.Working = 1;
  bink->skipped_this_frame = 0;
  bink->bio.Working = 0;

  for (i = 0; i < bink->playingtracks; i++)
  {
    if (bink->bsnd[i].SoundDroppedOut)
    {
      bink->bsnd[i].SoundDroppedOut = 0;
      if ((bink->FrameNum > 1) && ((S32)bink->FrameNum <= (S32)bink->bsnd[i].sndendframe))
        dropped = 1;
    }
  }

  if (dropped)
  {
    bink->soundskips++;
    RADCB_suspend_2_callbacks(cb_bink_sound, bink->snd_callback_buffer, cb_bink_IO,
                              (void *)bink->bio.callback_control);
    BinkSetSoundOnOff(bink, 0);
    while (((bink->bio.CurBufUsed + 1) * 100) / (bink->bio.CurBufSize + 1) < 90)
    {
      if (!bink->bio.Idle(&bink->bio))
        break;
    }
    bink->startsynctime = 0;
    bink->big_sound_skip_adj = 0;
    BinkSetSoundOnOff(bink, 1);
    RADCB_resume_callback(cb_bink_sound, bink->snd_callback_buffer);
    RADCB_resume_callback(cb_bink_IO, (void *)bink->bio.callback_control);
  }

  bink->bio.Working = 1;
  if (bink->playingtracks)
    checksound(bink);

  t = RADTimerRead();
  if (bink->startblittime)
  {
    bink->timeblit += t - bink->startblittime;
    bink->startblittime = 0;
  }

  GotoFrame(bink, (bink->FrameNum >= bink->Frames) ? 1 : bink->FrameNum + 1);

  bink->bio.Working = 0;
}

// match: _BinkClose@4 @ 0x00344030
RADEXPFUNC void RADEXPLINK BinkClose(HBINK bink)
{
  U32 i;
  U32 io;
  U32 snd;

  if (bink == 0)
    return;

  BinkPause(bink, 1);

  io = (!(bink->OpenFlags & BINKNOTHREADEDIO) && (bink->preloadptr == 0)) ? cb_bink_IO : 0;
  snd = bink->playingtracks ? cb_bink_sound : 0;
  switch (RADCB_unregister_2_callbacks(io, (void *)bink->bio.callback_control, snd,
                                       bink->snd_callback_buffer, 1))
  {
    case 3:
      cb_bink_sound = 0;
      cb_bink_IO = 0;
      break;
    case 1:
      cb_bink_IO = 0;
      break;
    case 2:
      cb_bink_sound = 0;
      break;
  }

  for (i = 0; i < bink->playingtracks; i++)
  {
    bink->bsnd[i].Close(&bink->bsnd[i]);
    BinkAudioDecompressClose(bink->bsnd[i].sndcomp);
    if (bink->bsnd[i].sndbuf)
      radfree(bink->bsnd[i].sndbuf);
  }

  FreeYUVGlobalMemory();

  if (bink->preloadptr)
  {
    if (!(bink->OpenFlags & BINKFROMMEMORY))
      radfree(bink->preloadptr);
  }
  else
  {
    bink->bio.Close(&bink->bio);
    radfree(bink->ioptr);
  }

  if (bink->YPlane[0])
    radfree(bink->YPlane[0]);

  memset(bink, 0, sizeof(BINK));
  radfree(bink);
}

static S32 tracktoindex(HBINK bink, U32 track)
{
  S32 i;

  for (i = 0; i < (S32)bink->playingtracks; i++)
  {
    if (bink->trackindexes[i] == (S32)track)
      return i;
  }
  return -1;
}

// match: _BinkDoFrame@4 @ 0x003438B0
RADEXPFUNC S32 RADEXPLINK BinkDoFrame(HBINK bink)
{
  U8 *out;
  U8 *in;
  U32 i;
  S32 suspended = 0;
  U32 remaining;
  U8 *data;
  U32 size;
  U32 t;
  U32 amt;

  if (bink == 0)
    return 0;
  if (bink->lastdecompframe == bink->FrameNum)
    return 0;

  if (bink->doresync)
  {
    bink->doresync = 0;
    if (bink->soundon)
    {
      BinkSetSoundOnOff(bink, 0);
      BinkSetSoundOnOff(bink, 1);
    }
    bink->startsynctime = 0;
    bink->big_sound_skip_adj = 0;
  }

  bink->skipped_this_frame = 0;
  bink->bio.Working = 1;
  bink->startframetime = RADTimerRead();

  {
    S32 rt = bink->rtindex;

    if (--bink->rtindex < 0)
      bink->rtindex = bink->runtimeframes - 1;

    bink->rtframetimes[bink->rtindex] = bink->startframetime;
    bink->rtvdecomptimes[bink->rtindex] = bink->timevdecomp;
    bink->rtadecomptimes[bink->rtindex] = bink->timeadecomp;
    bink->rtblittimes[bink->rtindex] = bink->timeblit;
    bink->rtreadtimes[bink->rtindex] = bink->bio.ForegroundTime;
    bink->rtidlereadtimes[bink->rtindex] = bink->bio.IdleTime;
    bink->rtthreadreadtimes[bink->rtindex] = bink->bio.ThreadTime;

    if (bink->firstframetime == 0)
    {
      bink->rtframetimes[rt] = bink->startframetime - mult64anddiv(1000, bink->fileframeratediv,
                                                                   bink->fileframerate);
      bink->bio.ThreadTime = 0;
      bink->firstframetime = bink->startframetime;
      bink->bio.IdleTime = 0;
    }
    else if (bink->playingtracks)
      checksound(bink);
  }

  bink->entireframetime = bink->startframetime;
  data = (U8 *)bink->compframe;

  if (bink->bio.ReadError)
    bink->ReadError = 1;
  if (bink->ReadError)
    return 1;

  for (i = 0; (S32)i < bink->NumTracks; i++)
  {
    S32 ti;

    size = *(U32 *)data;
    data += 4;

    ti = tracktoindex(bink, i);
    if ((ti != -1) && (size))
    {
      in = data;
      remaining = *(U32 *)in;
      in += 4;

      if (!suspended)
      {
        suspended = 1;
        RADCB_suspend_callback(cb_bink_sound, bink->snd_callback_buffer);
      }

      while (remaining)
      {
        U32 space = bink->bsnd[ti].sndbufsize - bink->bsnd[ti].sndamt;
        U32 avail;

        BinkAudioDecompress(bink->bsnd[ti].sndcomp, (void **)&out, &amt, in, (void **)&in);
        if (amt > remaining)
          amt = remaining;
        remaining -= amt;

        if (amt > space)
        {
          U32 over = amt - space;

          bink->bsnd[ti].sndreadpos += over;
          LockedAddFunc(&bink->bsnd[ti].sndamt, -(S32)over);
          if (bink->bsnd[ti].sndreadpos > bink->bsnd[ti].sndend)
            bink->bsnd[ti].sndreadpos -= bink->bsnd[ti].sndbufsize;
        }
        LockedAddFunc(&bink->bsnd[ti].sndamt, amt);

        avail = bink->bsnd[ti].sndend - bink->bsnd[ti].sndwritepos;
        if (avail < amt)
        {
          if (avail)
          {
            memcpy(bink->bsnd[ti].sndwritepos, out, avail);
            amt -= avail;
            out += avail;
          }
          memcpy(bink->bsnd[ti].sndbuf, out, amt);
          bink->bsnd[ti].sndwritepos = bink->bsnd[ti].sndbuf + amt;
        }
        else
        {
          memcpy(bink->bsnd[ti].sndwritepos, out, amt);
          bink->bsnd[ti].sndwritepos += amt;
        }
      }
    }

    data += size;
  }

  if (suspended)
    RADCB_resume_callback(cb_bink_sound, bink->snd_callback_buffer);

  t = RADTimerRead();

  if (bink->videoon)
  {
    if (!bink->skippedlastblit)
      memset(bink->MaskPlane, 0, (bink->YHeight >> 4) * (bink->YWidth >> 4));

    if ((bink->preloadptr == 0) && (bink->bio.DoingARead == 0) &&
        (((bink->bio.CurBufUsed + 1) * 100) / (bink->bio.CurBufSize + 1) < 75))
    {
      if (RADCB_try_to_suspend_callback(cb_bink_IO, (void *)bink->bio.callback_control))
      {
        bink->bio.Idle(&bink->bio);
        RADCB_resume_callback(cb_bink_IO, (void *)bink->bio.callback_control);
      }
      else if (!(bink->OpenFlags & BINKNOTHREADEDIO))
        RADCB_idle_on_callbacks();
    }

    bink->skipcount = ExpandBink(bink->YPlane[bink->PlaneNum ^ 1], bink->YPlane[bink->PlaneNum],
                                 bink->APlane[bink->PlaneNum ^ 1], bink->APlane[bink->PlaneNum],
                                 bink->MaskPlane, bink->decompwidth, bink->decompheight,
                                 bink->YWidth, bink->YHeight, data,
                                 bink->frameoffsets[bink->FrameNum - 1] & 1, &bink->bunp,
                                 bink->OpenFlags, bink->BinkType);
    bink->PlaneNum ^= 1;
  }

  if (bink->playingtracks)
    checksound(bink);

  bink->NumRects = -1;
  bink->playedframes++;
  inittimer(bink);

  {
    U32 t2 = RADTimerRead();

    bink->timeadecomp += t - bink->startframetime;
    bink->startblittime = t2;
    bink->timevdecomp += t2 - t;
  }

  bink->bio.Working = 0;
  bink->lastdecompframe = bink->FrameNum;
  bink->LastFrameNum = bink->FrameNum;
  return 0;
}
