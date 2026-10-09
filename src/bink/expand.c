/*
 * codfh-match: Bink's plane decoder (the library's expand.obj): the
 * Huffman-coded bundles each plane's blocks read their values from, the
 * bundle sizes, and the plane and frame expanders.
 */
#include "bink.h"
#include "binkint.h"

#include <string.h>
#include <mmintrin.h>
#pragma code_seg("BINK")
#undef VarBitsGetMask

// Peek at the next n bits and drop n bits, on the locals bits,
// cur and bitlen

#define VarBitsGetMask(i,n,mask) if(bitlen >= (U32)n) {i=bits&mask;bits>>=n;bitlen-=n;} else {U32 word=*cur; i=((word<<bitlen)|bits)&mask; word>>=(n-bitlen);bitlen+=32-n;cur++;bits=word;}
#define VarBitsPeek(v,n) if(bitlen >= (U32)(n)) (v)=bits & ((1UL<<(n))-1); else (v)=((*cur<<bitlen)|bits) & ((1UL<<(n))-1);
#define VarBitsUse(n)   if (bitlen >= (U32)(n)) { bits >>= (n); bitlen -= (n); }   else { bits = *cur >> ((n) - bitlen); bitlen += 32 - (n); cur++; }
#define VarBitsGetDynamic(i,n) if(bitlen >= (U32)(n)) {i=bits&(0xffffffffUL >> (32-(n)));bits>>=(n);bitlen-=(n);} else {U32 word=*cur; i=((word<<bitlen)|bits)&(0xffffffffUL >> (32-(n)));bits=word>>((n)-bitlen);bitlen+=32-(n);cur++;}
#define HuffGet(v,table,dec,rd,mask) \
  if (bitlen >= (rd)) { \
    U32 hv = (dec)[bits & (mask)]; \
    (v) = (table)[hv & 15]; \
    hv >>= 4; bits >>= hv; bitlen -= hv; \
  } else { \
    U32 word = *cur; \
    U32 hv = (dec)[(bits | (word << bitlen)) & (mask)]; \
    (v) = (table)[hv & 15]; \
    hv >>= 4; \
    if (bitlen >= hv) { bits >>= hv; bitlen -= hv; } \
    else { bits = word >> (hv-bitlen); bitlen += 32-hv; ++cur; } \
  }
#define PLANE_COPY_PITCH() \
  __asm push esi \
  __asm push edi \
  __asm push ebp \
  __asm push ebx \
  __asm mov esi, source \
  __asm mov edi, dest \
  __asm mov ebp, pitch \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + ebp] \
  __asm mov edx, dword ptr [esi + ebp + 4] \
  __asm lea esi, [esi + ebp*2] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm lea edi, [edi + ebp*2] \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + ebp] \
  __asm mov edx, dword ptr [esi + ebp + 4] \
  __asm lea esi, [esi + ebp*2] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm lea edi, [edi + ebp*2] \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + ebp] \
  __asm mov edx, dword ptr [esi + ebp + 4] \
  __asm lea esi, [esi + ebp*2] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm lea edi, [edi + ebp*2] \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + ebp] \
  __asm mov edx, dword ptr [esi + ebp + 4] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm pop ebx \
  __asm pop ebp \
  __asm pop edi \
  __asm pop esi
#define PLANE_COPY_FROM_BLOCK() \
  __asm push esi \
  __asm push edi \
  __asm push ebx \
  __asm mov edi, dest \
  __asm mov esi, pitch \
  __asm mov eax, dword ptr block[0] \
  __asm mov ebx, dword ptr block[4] \
  __asm mov ecx, dword ptr block[8] \
  __asm mov edx, dword ptr block[12] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + esi], ecx \
  __asm mov dword ptr [edi + esi + 4], edx \
  __asm lea edi, [edi + esi*2] \
  __asm mov eax, dword ptr block[16] \
  __asm mov ebx, dword ptr block[20] \
  __asm mov ecx, dword ptr block[24] \
  __asm mov edx, dword ptr block[28] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + esi], ecx \
  __asm mov dword ptr [edi + esi + 4], edx \
  __asm lea edi, [edi + esi*2] \
  __asm mov eax, dword ptr block[32] \
  __asm mov ebx, dword ptr block[36] \
  __asm mov ecx, dword ptr block[40] \
  __asm mov edx, dword ptr block[44] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + esi], ecx \
  __asm mov dword ptr [edi + esi + 4], edx \
  __asm lea edi, [edi + esi*2] \
  __asm mov eax, dword ptr block[48] \
  __asm mov ebx, dword ptr block[52] \
  __asm mov ecx, dword ptr block[56] \
  __asm mov edx, dword ptr block[60] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + esi], ecx \
  __asm mov dword ptr [edi + esi + 4], edx \
  __asm pop ebx \
  __asm pop edi \
  __asm pop esi
#define PLANE_COPY_TO_BLOCK() \
  __asm push esi \
  __asm push edi \
  __asm push ebx \
  __asm mov esi, source \
  __asm mov edi, pitch \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + edi] \
  __asm mov edx, dword ptr [esi + edi + 4] \
  __asm lea esi, [esi + edi*2] \
  __asm mov dword ptr block[0], eax \
  __asm mov dword ptr block[4], ebx \
  __asm mov dword ptr block[8], ecx \
  __asm mov dword ptr block[12], edx \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + edi] \
  __asm mov edx, dword ptr [esi + edi + 4] \
  __asm lea esi, [esi + edi*2] \
  __asm mov dword ptr block[16], eax \
  __asm mov dword ptr block[20], ebx \
  __asm mov dword ptr block[24], ecx \
  __asm mov dword ptr block[28], edx \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + edi] \
  __asm mov edx, dword ptr [esi + edi + 4] \
  __asm lea esi, [esi + edi*2] \
  __asm mov dword ptr block[32], eax \
  __asm mov dword ptr block[36], ebx \
  __asm mov dword ptr block[40], ecx \
  __asm mov dword ptr block[44], edx \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + edi] \
  __asm mov edx, dword ptr [esi + edi + 4] \
  __asm mov dword ptr block[48], eax \
  __asm mov dword ptr block[52], ebx \
  __asm mov dword ptr block[56], ecx \
  __asm mov dword ptr block[60], edx \
  __asm pop ebx \
  __asm pop edi \
  __asm pop esi
#define PLANE_COPY_PACKED() \
  __asm push esi \
  __asm push edi \
  __asm push ebp \
  __asm push ebx \
  __asm mov esi, color.cur \
  __asm mov edi, dest \
  __asm mov ebp, pitch \
  __asm mov eax, dword ptr [esi] \
  __asm mov ebx, dword ptr [esi + 4] \
  __asm mov ecx, dword ptr [esi + 8] \
  __asm mov edx, dword ptr [esi + 0xc] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm lea edi, [edi + ebp*2] \
  __asm mov eax, dword ptr [esi + 0x10] \
  __asm mov ebx, dword ptr [esi + 0x14] \
  __asm mov ecx, dword ptr [esi + 0x18] \
  __asm mov edx, dword ptr [esi + 0x1c] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm lea edi, [edi + ebp*2] \
  __asm mov eax, dword ptr [esi + 0x20] \
  __asm mov ebx, dword ptr [esi + 0x24] \
  __asm mov ecx, dword ptr [esi + 0x28] \
  __asm mov edx, dword ptr [esi + 0x2c] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm lea edi, [edi + ebp*2] \
  __asm mov eax, dword ptr [esi + 0x30] \
  __asm mov ebx, dword ptr [esi + 0x34] \
  __asm mov ecx, dword ptr [esi + 0x38] \
  __asm mov edx, dword ptr [esi + 0x3c] \
  __asm mov dword ptr [edi], eax \
  __asm mov dword ptr [edi + 4], ebx \
  __asm mov dword ptr [edi + ebp], ecx \
  __asm mov dword ptr [edi + ebp + 4], edx \
  __asm pop ebx \
  __asm pop ebp \
  __asm pop edi \
  __asm pop esi
#define plane_bit_level(v) ((v)<=128 ? _bitlevels[v] : ((v)>=2048 ? ((v)>=8192 ? ((v)>=16384 ? 15 : 14) : ((v)>=4096 ? 13 : 12)) : ((v)>=512 ? ((v)>=1024 ? 11 : 10) : ((v)>=256 ? 9 : 8))))
#define PLANE_EXPAND2(v) (((((v)&~255)<<8)|(v))<<8|((v)&255))
/* Plane bit reader: retain the fetched word until both bit-buffer and
 * result updates are complete. The ordinary readers use their own macro. */
#define PlaneVarBitsGet1(i) \
  if (bitlen) { (i)=bits&1; bits>>=1; bitlen--; } \
  else { U32 word=*cur; cur++; bits=word>>1; bitlen=31; (i)=word&1; }
#define PlaneVarBitsGet(i,n,mask) if(bitlen >= (U32)n) {i=bits&mask;bits>>=n;bitlen-=n;} else {U32 word=*cur; i=((word<<bitlen)|bits)&mask; bits=word>>(n-bitlen);bitlen+=32-n;cur++;}
#define PLANE_COLOR32(v) ((((v)<<8)|(v)) | ((((v)<<8)|(v))<<16))

/* expand's tables (the library's expand.obj .rdata, 0x3EE930-0x3EEDF0), in the image's order
   (VC7.1 emits them in definition order). */
// the four-bit Huffman decoders, each one's table at its offset (huff4decodes)
// match: _unk_3EE930 @ 0x003EE930
const U8 unk_3EE930[0x408] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
  0x10, 0x41, 0x10, 0x52, 0x10, 0x53, 0x10, 0x54, 0x10, 0x55, 0x10, 0x56, 0x10, 0x57, 0x10, 0x58,
  0x10, 0x41, 0x10, 0x59, 0x10, 0x5A, 0x10, 0x5B, 0x10, 0x5C, 0x10, 0x5D, 0x10, 0x5E, 0x10, 0x5F,
  0x20, 0x42, 0x21, 0x58, 0x20, 0x54, 0x21, 0x5C, 0x20, 0x43, 0x21, 0x5A, 0x20, 0x56, 0x21, 0x5E,
  0x20, 0x42, 0x21, 0x59, 0x20, 0x55, 0x21, 0x5D, 0x20, 0x43, 0x21, 0x5B, 0x20, 0x57, 0x21, 0x5F,
  0x20, 0x43, 0x31, 0x58, 0x20, 0x45, 0x32, 0x5C, 0x20, 0x44, 0x31, 0x5A, 0x20, 0x56, 0x32, 0x5E,
  0x20, 0x43, 0x31, 0x59, 0x20, 0x45, 0x32, 0x5D, 0x20, 0x44, 0x31, 0x5B, 0x20, 0x57, 0x32, 0x5F,
  0x30, 0x44, 0x32, 0x58, 0x31, 0x46, 0x33, 0x5C, 0x30, 0x45, 0x32, 0x5A, 0x31, 0x47, 0x33, 0x5E,
  0x30, 0x44, 0x32, 0x59, 0x31, 0x46, 0x33, 0x5D, 0x30, 0x45, 0x32, 0x5B, 0x31, 0x47, 0x33, 0x5F,
  0x30, 0x46, 0x42, 0x4A, 0x31, 0x48, 0x44, 0x5C, 0x30, 0x47, 0x43, 0x4B, 0x31, 0x49, 0x45, 0x5E,
  0x30, 0x46, 0x42, 0x4A, 0x31, 0x48, 0x44, 0x5D, 0x30, 0x47, 0x43, 0x4B, 0x31, 0x49, 0x45, 0x5F,
  0x20, 0x45, 0x41, 0x49, 0x20, 0x47, 0x43, 0x5C, 0x20, 0x46, 0x42, 0x5A, 0x20, 0x48, 0x44, 0x5E,
  0x20, 0x45, 0x41, 0x49, 0x20, 0x47, 0x43, 0x5D, 0x20, 0x46, 0x42, 0x5B, 0x20, 0x48, 0x44, 0x5F,
  0x10, 0x31, 0x10, 0x53, 0x10, 0x32, 0x10, 0x68, 0x10, 0x31, 0x10, 0x55, 0x10, 0x32, 0x10, 0x6C,
  0x10, 0x31, 0x10, 0x54, 0x10, 0x32, 0x10, 0x6A, 0x10, 0x31, 0x10, 0x66, 0x10, 0x32, 0x10, 0x6E,
  0x10, 0x31, 0x10, 0x53, 0x10, 0x32, 0x10, 0x69, 0x10, 0x31, 0x10, 0x55, 0x10, 0x32, 0x10, 0x6D,
  0x10, 0x31, 0x10, 0x54, 0x10, 0x32, 0x10, 0x6B, 0x10, 0x31, 0x10, 0x67, 0x10, 0x32, 0x10, 0x6F,
  0x10, 0x21, 0x10, 0x52, 0x10, 0x21, 0x10, 0x68, 0x10, 0x21, 0x10, 0x64, 0x10, 0x21, 0x10, 0x6C,
  0x10, 0x21, 0x10, 0x53, 0x10, 0x21, 0x10, 0x6A, 0x10, 0x21, 0x10, 0x66, 0x10, 0x21, 0x10, 0x6E,
  0x10, 0x21, 0x10, 0x52, 0x10, 0x21, 0x10, 0x69, 0x10, 0x21, 0x10, 0x65, 0x10, 0x21, 0x10, 0x6D,
  0x10, 0x21, 0x10, 0x53, 0x10, 0x21, 0x10, 0x6B, 0x10, 0x21, 0x10, 0x67, 0x10, 0x21, 0x10, 0x6F,
  0x10, 0x31, 0x10, 0x54, 0x10, 0x42, 0x10, 0x68, 0x10, 0x31, 0x10, 0x56, 0x10, 0x43, 0x10, 0x6C,
  0x10, 0x31, 0x10, 0x55, 0x10, 0x42, 0x10, 0x6A, 0x10, 0x31, 0x10, 0x57, 0x10, 0x43, 0x10, 0x6E,
  0x10, 0x31, 0x10, 0x54, 0x10, 0x42, 0x10, 0x69, 0x10, 0x31, 0x10, 0x56, 0x10, 0x43, 0x10, 0x6D,
  0x10, 0x31, 0x10, 0x55, 0x10, 0x42, 0x10, 0x6B, 0x10, 0x31, 0x10, 0x57, 0x10, 0x43, 0x10, 0x6F,
  0x20, 0x32, 0x21, 0x55, 0x20, 0x43, 0x21, 0x59, 0x20, 0x32, 0x21, 0x57, 0x20, 0x44, 0x21, 0x6C,
  0x20, 0x32, 0x21, 0x56, 0x20, 0x43, 0x21, 0x6A, 0x20, 0x32, 0x21, 0x58, 0x20, 0x44, 0x21, 0x6E,
  0x20, 0x32, 0x21, 0x55, 0x20, 0x43, 0x21, 0x59, 0x20, 0x32, 0x21, 0x57, 0x20, 0x44, 0x21, 0x6D,
  0x20, 0x32, 0x21, 0x56, 0x20, 0x43, 0x21, 0x6B, 0x20, 0x32, 0x21, 0x58, 0x20, 0x44, 0x21, 0x6F,
  0x10, 0x41, 0x10, 0x55, 0x10, 0x43, 0x10, 0x59, 0x10, 0x42, 0x10, 0x57, 0x10, 0x44, 0x10, 0x6C,
  0x10, 0x41, 0x10, 0x56, 0x10, 0x43, 0x10, 0x6A, 0x10, 0x42, 0x10, 0x58, 0x10, 0x44, 0x10, 0x6E,
  0x10, 0x41, 0x10, 0x55, 0x10, 0x43, 0x10, 0x59, 0x10, 0x42, 0x10, 0x57, 0x10, 0x44, 0x10, 0x6D,
  0x10, 0x41, 0x10, 0x56, 0x10, 0x43, 0x10, 0x6B, 0x10, 0x42, 0x10, 0x58, 0x10, 0x44, 0x10, 0x6F,
  0x20, 0x22, 0x21, 0x53, 0x20, 0x22, 0x21, 0x68, 0x20, 0x22, 0x21, 0x55, 0x20, 0x22, 0x21, 0x6C,
  0x20, 0x22, 0x21, 0x54, 0x20, 0x22, 0x21, 0x6A, 0x20, 0x22, 0x21, 0x66, 0x20, 0x22, 0x21, 0x6E,
  0x20, 0x22, 0x21, 0x53, 0x20, 0x22, 0x21, 0x69, 0x20, 0x22, 0x21, 0x55, 0x20, 0x22, 0x21, 0x6D,
  0x20, 0x22, 0x21, 0x54, 0x20, 0x22, 0x21, 0x6B, 0x20, 0x22, 0x21, 0x67, 0x20, 0x22, 0x21, 0x6F,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x64, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x78,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x66, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7C,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x65, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7A,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x67, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7E,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x64, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x79,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x66, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7D,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x65, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7B,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x67, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7F,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x54, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x78,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x65, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7C,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x54, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7A,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x76, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7E,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x54, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x79,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x65, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7D,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x54, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7B,
  0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x77, 0x10, 0x31, 0x10, 0x33, 0x10, 0x32, 0x10, 0x7F,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x65, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x69,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x67, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x7C,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x66, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x7A,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x68, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x7E,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x65, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x69,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x67, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x7D,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x66, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x7B,
  0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x68, 0x20, 0x32, 0x21, 0x34, 0x20, 0x33, 0x21, 0x7F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// match: _huff4reads @ 0x003EED38
const U8 huff4reads[16] = { 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07 };
// the run lengths CheckReadRLEHuff4Bundle reads (0x3EED48)
static const U8 rlelens[4] = {4, 8, 12, 32};
// a word nothing in the image reads
// match: _unk_3EED4C @ 0x003EED4C
const U32 unk_3EED4C = 0;
// match: _mask2 @ 0x003EED50
const U32 mask2[16] = { 0x00000000, 0x000000FF, 0x0000FF00, 0x0000FFFF, 0x00FF0000, 0x00FF00FF, 0x00FFFF00, 0x00FFFFFF, 0xFF000000, 0xFF0000FF, 0xFF00FF00, 0xFF00FFFF, 0xFFFF0000, 0xFFFF00FF, 0xFFFFFF00, 0xFFFFFFFF };
// match: _mask1 @ 0x003EED90
const U32 mask1[16] = { 0xFFFFFFFF, 0xFFFFFF00, 0xFFFF00FF, 0xFFFF0000, 0xFF00FFFF, 0xFF00FF00, 0xFF0000FF, 0xFF000000, 0x00FFFFFF, 0x00FFFF00, 0x00FF00FF, 0x00FF0000, 0x0000FFFF, 0x0000FF00, 0x000000FF, 0x00000000 };
// match: _mask4 @ 0x003EEDD0
const U32 mask4[4] = { 0x00000000, 0x0000FFFF, 0xFFFF0000, 0xFFFFFFFF };
// match: _mask3 @ 0x003EEDE0
const U32 mask3[4] = { 0xFFFFFFFF, 0xFFFF0000, 0x0000FFFF, 0x00000000 };

/* each Huffman table's decoder (BINKDATA, the image's 0x52F780) */
#pragma data_seg("BINKDATA")
// match: _huff4decodes @ 0x0052F780
U8 *huff4decodes[16] = {
  (U8 *)unk_3EE930 + 0x30, (U8 *)unk_3EE930 + 0x40, (U8 *)unk_3EE930 + 0x60, (U8 *)unk_3EE930 + 0x80,
  (U8 *)unk_3EE930 + 0xA0, (U8 *)unk_3EE930 + 0xC0, (U8 *)unk_3EE930 + 0xE0, (U8 *)unk_3EE930 + 0x100,
  (U8 *)unk_3EE930 + 0x140, (U8 *)unk_3EE930 + 0x180, (U8 *)unk_3EE930 + 0x1C0, (U8 *)unk_3EE930 + 0x200,
  (U8 *)unk_3EE930 + 0x240, (U8 *)unk_3EE930 + 0x280, (U8 *)unk_3EE930 + 0x300, (U8 *)unk_3EE930 + 0x380
};
#pragma data_seg()

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rlelens @ 0x003EED48

// ReadHuffTable (0x003461E0) stays binary in expand_asm.asm with simpmergesort, whose C
// does not match (owner, 2026-10-04: unmatched Bink may be binarized).
void ReadHuffTable(VARBITS *vb, U8 **decode, U32 *reads, U8 *tab);

// match: _StartReadHuff8Bundle @ 0x00346870
// sp-match: _StartReadHuff8Bundle @ 0x00256870
void StartReadHuff8Bundle(BUNDLE *b, VARBITS *vb, HUFF8 *h)
{
  U32 i;

  for (i = 0; i < 16; i++)
    ReadHuffTable(vb, &h->decodes[i], &h->reads[i], h->tabs[i]);
  ReadHuffTable(vb, &b->decode, &b->reads, b->tab);
  h->last = 0;
}

static U32 getbunsize(U32 width, U32 extra, U32 bits, U32 per)
{
  if (bits <= 8)
    bits = 8;
  else if (bits < 16)
    bits = 16;
  return ((((width >> 3) * bits * per) >> 3) + ((extra * bits) >> 3) + 3) & ~3;
}

// match: _ExpandBundleSizes@8 @ 0x00347AA0
// sp-match: _ExpandBundleSizes@8 @ 0x00257AA0
RADEXPFUNC void RADEXPLINK ExpandBundleSizes(BUNDLEPOINTERS *bunp, U32 width)
{
  bunp->typeptr = (void *)getbunsize(width, 512, 4, 1);
  bunp->type16ptr = (void *)getbunsize(width >> 1, 512, 4, 1);
  bunp->colorptr = (void *)getbunsize(width, 512, 8, 64);
  bunp->bits2ptr = (void *)getbunsize(width, 512, 8, 8);
  bunp->motionXptr = (void *)getbunsize(width, 512, 8, 1);
  bunp->motionYptr = (void *)getbunsize(width, 512, 8, 1);
  bunp->dctptr = (void *)getbunsize(width, 512, 16, 1);
  bunp->mdctptr = (void *)getbunsize(width, 512, 16, 1);
  bunp->patptr = (void *)getbunsize(width, 512, 8, 48);
}



// match: _CheckReadHuff4Bundle @ 0x003470F0
// sp-match: _CheckReadHuff4Bundle @ 0x002570F0

void CheckReadHuff4Bundle(BUNDLE *b, VARBITS *vb)
{
  if (b->cur == b->end) {
    U32 bits = vb->bits, *cur = vb->cur, bitlen = vb->bitlen;
    U32 n;
    VarBitsGetDynamic(n, b->lenbits);
    if (n) {
      U8 *out = b->start;
      U32 v;
      b->cur = out; b->end = out + n;
      VarBitsGet1(v);
      if (!v) {
        U8 *to = out;
        U32 reads = b->reads;
        U8 *decode = b->decode;
        U32 mask = 0xffffffffUL >> (32-reads);
        do {
          --n;
          HuffGet(*to++,b->tab,decode,reads,mask);
        } while (n);
      } else {
        VarBitsGet(v,4);
        memset(out,v,n);
      }
    } else {
      b->cur = b->start + 4;
      b->end = b->start;
    }
    vb->bitlen = bitlen; vb->bits = bits; vb->cur = cur;
  }
}

// match: _CheckReadHuff4SBundle @ 0x00347500
// sp-match: _CheckReadHuff4SBundle @ 0x00257500
void CheckReadHuff4SBundle(BUNDLE *b, VARBITS *vb)
{
  if (b->cur == b->end) {
    U32 bits = vb->bits, *cur = vb->cur, bitlen = vb->bitlen;
    U32 n;
    VarBitsGetDynamic(n,b->lenbits);
    if (n) {
      U8 *out = b->start;
      U32 v;
      b->cur = out; b->end = out + n;
      VarBitsGet1(v);
      if (!v) {
        U8 *to = out;
        U32 reads = b->reads;
        U8 *decode = b->decode;
        
        do {
          S8 val;
          --n;
          HuffGet(val,b->tab,decode,reads,(0xffffffffUL >> (32-reads)));
          if (val) { VarBitsGet1(v); if (v) val = -val; }
          *to++ = val;
        } while(n);
      } else {
        S8 val;
        VarBitsGet(val,4);
        if (val) { VarBitsGet1(v); if (v) val = -val; }
        memset(out,val,n);
      }
    } else {
      b->cur = b->start + 4;
      b->end = b->start;
    }
    vb->bitlen = bitlen; vb->cur = cur; vb->bits = bits;
  }
}

// match: _CheckReadRLEHuff4Bundle @ 0x003468E0
// sp-match: _CheckReadRLEHuff4Bundle @ 0x002568E0
void CheckReadRLEHuff4Bundle(BUNDLE *b, VARBITS *vb)
{
  if (b->cur == b->end) {
    U32 bits = vb->bits, *cur = vb->cur, bitlen = vb->bitlen;
    U32 n;
    VarBitsGetDynamic(n,b->lenbits);
    if (n) {
      U8 *out = b->start;
      U32 v;
      b->cur = out; b->end = out + n;
      VarBitsGet1(v);
      if (!v) {
        U8 *to = out;
        U8 val,last;
        U8 *decode = b->decode;
        U8 reads = (U8)b->reads;
        
        last = 0;
        do {
          HuffGet(val,b->tab,decode,reads,(0xffffffffUL >> (32-reads)));
          if (val >= 12) {
            U32 value = last | (last << 8);
            U8 count = rlelens[val-12];
            value |= value << 16;
            n -= count;
            if ((U32)to & 3) {
              do { *to++ = (U8)value; } while (--count);
            } else {
              do {
                *(U32*)to = value;
                to += 4;
                count -= 4;
              } while(count);
            }
          } else {
            *to++ = val;
            last = val;
            --n;
          }
        } while(n);
      } else {
        U8 val;
        VarBitsGetDynamic(val,4);
        memset(out,val,n);
      }
    } else {
      b->cur = b->start + 4;
      b->end = b->start;
    }
    vb->bitlen = bitlen; vb->cur = cur; vb->bits = bits;
  }
}

// match: _CheckReadHuff8Bundle @ 0x00346B60
// sp-match: _CheckReadHuff8Bundle @ 0x00256B60
void CheckReadHuff8Bundle(BUNDLE *b, VARBITS *vb, HUFF8 *h)
{
  if (b->cur == b->end) {
    U32 bits = vb->bits, *cur = vb->cur, bitlen = vb->bitlen;
    S32 n;
    VarBitsGetDynamic(n,b->lenbits);
    if (n) {
      U8 *out;
      U32 reads,mask;
      U8 *decode;
      U32 last;
      U32 v;
      out=b->start; 
      b->end=out+n; b->cur=out;
      last = h->last; reads = b->reads; decode = b->decode;
      VarBitsGet1(v);
      if (v) n = -20-n;
      mask=0xffffffffUL >> (32-reads);
      do {
        U8 hi,lo;
        --n;
        HuffGet(hi,h->tabs[last],h->decodes[last],h->reads[last],(0xffffffffUL >> (32-h->reads[last])));
        last = hi;
        HuffGet(lo,b->tab,decode,reads,mask);
        { U8 byteValue = (U8)(lo | (hi << 4)); S32 value = (byteValue & 0x80) ? -(byteValue & 0x7f) : (byteValue & 0x7f); *out++ = (U8)(value + 0x80); }
      } while(n>0);
      if(n < -22) memset(b->start,*b->start,-21-n);
      h->last = last;
    } else {
      b->cur = b->start + 4;
      b->end = b->start;
    }
    vb->bitlen = bitlen; vb->bits = bits; vb->cur = cur;
  }
}

// match: _NewCheckReadHuff8Bundle @ 0x00346E30
// sp-match: _NewCheckReadHuff8Bundle @ 0x00256E30
void NewCheckReadHuff8Bundle(BUNDLE *b, VARBITS *vb, HUFF8 *h)
{
  if (b->cur == b->end) {
    U32 bits = vb->bits, *cur = vb->cur, bitlen = vb->bitlen;
    S32 n;
    VarBitsGetDynamic(n,b->lenbits);
    if (n) {
      U8 *out;
      U32 reads,mask;
      U8 *decode;
      U32 last;
      U32 v;
      out=b->start; 
      b->end=out+n; b->cur=out;
      last = h->last; reads = b->reads; decode = b->decode;
      VarBitsGet1(v);
      if (v) n = -20-n;
      mask=0xffffffffUL >> (32-reads);
      do {
        U8 hi,lo;
        --n;
        HuffGet(hi,h->tabs[last],h->decodes[last],h->reads[last],(0xffffffffUL >> (32-h->reads[last])));
        last = hi;
        HuffGet(lo,b->tab,decode,reads,mask);
        *out++ = lo | (hi << 4);
      } while(n>0);
      if(n < -22) memset(b->start,*b->start,-21-n);
      h->last = last;
    } else {
      b->cur = b->start + 4;
      b->end = b->start;
    }
    vb->bitlen = bitlen; vb->bits = bits; vb->cur = cur;
  }
}

// Original RAD low-level primitive: named _radmemset16 in supplied expand.obj.
static __inline void radmemset16(void *dest, U16 value, U32 count)
{
  __asm {
    mov edi, dest
    mov ax, value
    mov ecx, count
    shl eax, 16
    cld
    mov ax, value
    mov bl, cl
    shr ecx, 1
    rep stosd
    mov cl, bl
    and cl, 1
    rep stosw
  }
}

// match: _CheckReadDelta16Bundle @ 0x00347780
// sp-match: _CheckReadDelta16Bundle @ 0x00257780
void CheckReadDelta16Bundle(BUNDLE *b, VARBITS *vb)
{
  if (b->cur == b->end) {
    U32 bits=vb->bits, *cur=vb->cur, bitlen=vb->bitlen;
    U32 n;
    VarBitsGetDynamic(n,b->lenbits);
    if (n) {
      S16 *out=(S16*)b->start;
      S16 value;
      U32 precision;
      if (b->unk0C) {
        U32 sign;
        VarBitsGetDynamic(value,b->unk08-1);
        if (value) { VarBitsGet1(sign); if(sign) value=-value; }
      } else {
        VarBitsGetDynamic(value,b->unk08);
      }
      *out++=value;
      b->cur=b->start; b->end=b->start+n*2;
      --n;
      while (n) {
        U32 count=(n>8)?8:n;
        VarBitsGetDynamic(precision,4);
        if (precision) {
          U32 i=count;
          while (i) {
            S16 delta;
            U32 sign;
            VarBitsGetDynamic(delta,precision);
            if(delta) { VarBitsGet1(sign); if(sign) delta=-delta; }
            value=(S16)(value+delta);
            *out++=value;
            --i;
          }
        } else {
          radmemset16(out,value,count*2);
          out+=count;
        }
        n-=count;
      }
    } else {
      b->cur=b->start+4; b->end=b->start;
    }
    vb->bitlen=bitlen; vb->cur=cur; vb->bits=bits;
  }
}

// CheckReadHuff4PairBundle, ExpandPlane and ExpandBink stay binary in expand_asm.asm: the
// first two take an argument in a register, and CheckReadHuff4PairBundle's C does not match.
