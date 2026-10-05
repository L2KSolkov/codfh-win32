/*
 * codfh-match: Bink's MMX check (the library's mmx.obj): whether the CPU
 * has MMX (CPUID's feature bit 23), cached, and whether the decoder uses it
 * (not with BINKNOMMX).
 */
#include "bink.h"
#include "binkint.h"

S32 decode_MMX_avail = -1;
S32 decode_use_MMX;

static S32 MMX_available(void)
{
  S32 avail = 0;

  __asm
  {
    push ebx
    pushfd
    pop eax
    mov ebx, eax
    xor eax, 0x200000    // EFLAGS.ID, not an address
    push eax
    popfd
    pushfd
    pop eax
    push ebx
    popfd
    cmp eax, ebx
    je nommx
    mov eax, 1
    cpuid
    test edx, 0x800000
    je nommx
    mov avail, 1
    pop ebx
  nommx:
  }
  return avail;
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _decode_MMX_avail @ 0x00431188

// match: _check_for_MMX @ 0x0025D910

void check_for_MMX(U32 flags)
{
  if (decode_MMX_avail < 0)
    decode_MMX_avail = MMX_available();

  if ((decode_MMX_avail) && (!(flags & BINKNOMMX)))
    decode_use_MMX = 1;
  else
    decode_use_MMX = 0;
}
