/*
 * codfh-match: Bink's default file IO (the library's binkfile.obj): the
 * BINKIO callbacks over a file handle, reading 16K blocks into the IO
 * buffer in the background and handing frames out of it, with optional
 * simulated data rates.
 */
#include "bink.h"
#include "binkint.h"

// RAD puts all of Bink's code in its BINK section (the image's 0x341480-0x34E01C).
#pragma code_seg("BINK")

#define BF(bio) ((volatile BINKFILE *)(bio)->iodata)
#define BLOCK 0x4000

// match: _BinkFileReadHeader@16 @ 0x00349BA0
// sp-match: _BinkFileReadHeader@16 @ 0x00259BA0
static U32 RADLINK BinkFileReadHeader(BINKIO PTR4 *bio, S32 offset, void PTR4 *dest, U32 size)
{
  U32 amt;
  U32 left;

  if (bio->suspend_callback)
    bio->suspend_callback(bio);

  if ((offset != -1) && (BF(bio)->FileIOPos != (U32)offset))
  {
    SetFilePointer(BF(bio)->FileHandle, offset + BF(bio)->StartFile, 0, 0);
    BF(bio)->FileIOPos = offset;
  }

  ReadFile(BF(bio)->FileHandle, dest, size, &amt, 0);
  BF(bio)->FileIOPos += amt;
  BF(bio)->FileBufPos = BF(bio)->FileIOPos;
  left = BF(bio)->FileSize - BF(bio)->FileBufPos;
  if (left >= bio->BufSize)
    left = bio->BufSize;
  bio->CurBufSize = left;

  if (bio->resume_callback)
    bio->resume_callback(bio);
  return amt;
}

// match: _dosimulate @ 0x00349C30
// sp-match: _dosimulate @ 0x00259C30
static void dosimulate(BINKIO *bio, U32 amt, U32 start)
{
  U32 ms = mult64anddiv(amt, 1000, BF(bio)->Simulate);
  U32 now = RADTimerRead();

  BF(bio)->SimulateTime += start + ms - now;
  while (BF(bio)->SimulateTime > 0)
  {
    U32 t;

    do
    {
      t = RADTimerRead();
    } while ((S32)(t - now) < BF(bio)->SimulateTime);

    BF(bio)->SimulateTime += now - t;
    now = t;
  }
}

// match: _BinkFileReadFrame@20 @ 0x00349CC0
// sp-match: _BinkFileReadFrame@20 @ 0x00259CC0
static U32 RADLINK BinkFileReadFrame(BINKIO PTR4 *bio, U32 frame, S32 offset, void PTR4 *dest, U32 size)
{
  S32 suspended = 0;
  U32 ret = 0;
  U32 start;
  U32 amt;
  U32 got;
  U32 end;
  U32 first;

  if (bio->ReadError)
    return 0;

  start = RADTimerRead();

  if ((offset != -1) && (BF(bio)->FileBufPos != (U32)offset))
  {
    suspended = 1;
    if (bio->suspend_callback)
      bio->suspend_callback(bio);

    if (((U32)offset > BF(bio)->FileBufPos) && ((U32)offset <= BF(bio)->FileIOPos))
    {
      got = offset - BF(bio)->FileBufPos;
      BF(bio)->FileBufPos = offset;
      BF(bio)->BufEmpty += got;
      bio->CurBufUsed -= got;
      BF(bio)->BufPos += got;
      if (BF(bio)->BufPos > BF(bio)->BufEnd)
        BF(bio)->BufPos -= bio->BufSize;
    }
    else
    {
      SetFilePointer(BF(bio)->FileHandle, offset + BF(bio)->StartFile, 0, 0);
      BF(bio)->FileIOPos = offset;
      BF(bio)->FileBufPos = offset;
      BF(bio)->BufEmpty = bio->BufSize;
      bio->CurBufUsed = 0;
      BF(bio)->BufPos = BF(bio)->Buffer;
      BF(bio)->BufBack = BF(bio)->Buffer;
    }
  }

  for (;;)
  {
    amt = bio->CurBufUsed;
    if (amt)
    {
      if (amt > size)
        amt = size;
      size -= amt;
      ret += amt;
      BF(bio)->FileBufPos += amt;
      first = BF(bio)->BufEnd - BF(bio)->BufPos;
      if (first <= amt)
      {
        memcpy(dest, BF(bio)->BufPos, first);
        dest = (U8 *)dest + first;
        BF(bio)->BufPos = BF(bio)->Buffer;
        amt -= first;
        LockedAddFunc(&bio->CurBufUsed, -(S32)first);
        LockedAddFunc(&BF(bio)->BufEmpty, first);
        if (amt == 0)
          goto copied;
      }

      memcpy(dest, BF(bio)->BufPos, amt);
      dest = (U8 *)dest + amt;
      BF(bio)->BufPos += amt;
      LockedAddFunc(&bio->CurBufUsed, -(S32)amt);
      LockedAddFunc(&BF(bio)->BufEmpty, amt);
    }

   copied:
    if (size)
    {
      if (!suspended)
      {
        suspended = 1;
        if (bio->suspend_callback)
          bio->suspend_callback(bio);
        continue;
      }

      {
        U32 t = RADTimerRead();

        ReadFile(BF(bio)->FileHandle, dest, size, &got, 0);
        if (got < size)
          bio->ReadError = 1;
        BF(bio)->FileIOPos += got;
        BF(bio)->FileBufPos += got;
        bio->BytesRead += got;
        ret += got;
        if (BF(bio)->Simulate)
          dosimulate(bio, got, t);

        end = RADTimerRead();
        bio->TotalTime += end - t;
        bio->ForegroundTime += end - start;
      }
    }
    else
      bio->ForegroundTime += RADTimerRead() - start;
    break;
  }

  got = BF(bio)->FileSize - BF(bio)->FileBufPos;
  bio->CurBufSize = (got < bio->BufSize) ? got : bio->BufSize;
  if (bio->CurBufUsed + BLOCK > bio->CurBufSize)
    bio->CurBufSize = bio->CurBufUsed;

  if ((suspended) && (bio->resume_callback))
    bio->resume_callback(bio);
  return ret;
}

// match: _BinkFileGetBufferSize@8 @ 0x00349FA0
// sp-match: _BinkFileGetBufferSize@8 @ 0x00259FA0
static U32 RADLINK BinkFileGetBufferSize(BINKIO PTR4 *bio, U32 size)
{
  return ((size + BLOCK - 1) / BLOCK) * BLOCK;
}

// match: _BinkFileSetInfo@20 @ 0x00349FC0
// sp-match: _BinkFileSetInfo@20 @ 0x00259FC0
static void RADLINK BinkFileSetInfo(BINKIO PTR4 *bio, void PTR4 *buf, U32 size, U32 filesize, U32 simulate)
{
  if (bio->suspend_callback)
    bio->suspend_callback(bio);

  size = (size / BLOCK) * BLOCK;
  BF(bio)->Buffer = (U8 *)buf;
  BF(bio)->BufPos = (U8 *)buf;
  BF(bio)->BufBack = (U8 *)buf;
  BF(bio)->BufEnd = (U8 *)buf + size;
  bio->BufSize = size;
  BF(bio)->BufEmpty = size;
  bio->CurBufUsed = 0;
  BF(bio)->FileSize = filesize;
  BF(bio)->Simulate = simulate;

  if (bio->resume_callback)
    bio->resume_callback(bio);
}

// match: _BinkFileClose@4 @ 0x0034A020
// sp-match: _BinkFileClose@4 @ 0x0025A020
static void RADLINK BinkFileClose(BINKIO PTR4 *bio)
{
  if (bio->suspend_callback)
    bio->suspend_callback(bio);
  if (!BF(bio)->DontClose)
    CloseHandle(BF(bio)->FileHandle);
  if (bio->resume_callback)
    bio->resume_callback(bio);
}

// match: _BinkFileIdle@4 @ 0x0034A060
// sp-match: _BinkFileIdle@4 @ 0x0025A060
static U32 RADLINK BinkFileIdle(BINKIO PTR4 *bio)
{
  U32 amt = 0;
  U32 working = bio->Working;

  if (bio->ReadError)
    return 0;

  if ((bio->try_suspend_callback) && (bio->try_suspend_callback(bio)))
  {
    U32 left = BF(bio)->FileSize - BF(bio)->FileIOPos;

    if ((BF(bio)->BufEmpty >= BLOCK) && (left >= BLOCK))
    {
      U32 t = RADTimerRead();

      bio->DoingARead = 1;
      ReadFile(BF(bio)->FileHandle, BF(bio)->BufBack, BLOCK, &amt, 0);
      bio->DoingARead = 0;
      if (amt < BLOCK)
        bio->ReadError = 1;

      bio->BytesRead += amt;
      BF(bio)->FileIOPos += amt;
      BF(bio)->BufBack += amt;
      if (BF(bio)->BufBack >= BF(bio)->BufEnd)
        BF(bio)->BufBack = BF(bio)->Buffer;

      LockedAddFunc(&BF(bio)->BufEmpty, -(S32)amt);
      LockedAddFunc(&bio->CurBufUsed, amt);
      if (bio->CurBufUsed > bio->BufHighUsed)
        bio->BufHighUsed = bio->CurBufUsed;

      if (BF(bio)->Simulate)
        dosimulate(bio, amt, t);

      t = RADTimerRead() - t;
      bio->TotalTime += t;
      if ((!working) && (!bio->Working))
        bio->IdleTime += t;
      else
        bio->ThreadTime += t;
    }
    else
      bio->CurBufSize = bio->CurBufUsed;

    if (bio->resume_callback)
      bio->resume_callback(bio);
  }
  else
  {
    if (bio->idle_on_callback)
      bio->idle_on_callback(bio);
    amt = (U32)-1;
  }
  return amt;
}

// match: _BinkFileOpen@12 @ 0x0034A1F0
// sp-match: _BinkFileOpen@12 @ 0x0025A1F0
RADEXPFUNC S32 RADEXPLINK BinkFileOpen(BINKIO PTR4 *bio, const char PTR4 *name, U32 flags)
{
  memset(bio, 0, sizeof(BINKIO));

  if (flags & BINKFILEHANDLE)
  {
    BF(bio)->FileHandle = (HANDLE)name;
    BF(bio)->DontClose = 1;
    BF(bio)->StartFile = SetFilePointer((HANDLE)name, 0, 0, 1);
  }
  else
  {
    BF(bio)->FileHandle = CreateFileA(name, 0x80000000, 1, 0, 3, 0x8000080, 0);
    if (BF(bio)->FileHandle == (HANDLE)-1)
    {
      BF(bio)->FileHandle = CreateFileA(name, 0x80000000, 3, 0, 3, 0x8000080, 0);
      if (BF(bio)->FileHandle == (HANDLE)-1)
        return 0;
    }
  }

  bio->ReadHeader = BinkFileReadHeader;
  bio->ReadFrame = BinkFileReadFrame;
  bio->GetBufferSize = BinkFileGetBufferSize;
  bio->SetInfo = BinkFileSetInfo;
  bio->Idle = BinkFileIdle;
  bio->Close = BinkFileClose;
  return 1;
}
