/* Bink bitplane.obj. Names and coefficient order verified against the
 * supplied library and the image. IDA: sub_34CEC0, sub_34D7D0, sub_34DCB0. */
#include "bink.h"
#include "binkint.h"
#pragma code_seg("BINK")

void readlossy(S8 *coeffs,VARBITS *vb,S32 limit);
// symbol: _readlossy = 0x0034D7D0

// The coefficient tree visits adjacent 2x2 blocks in this order.
#define SCATTER_BLOCK \
  SCATTER_ROW(0,0,1,4,5,8,9,12,13); destrow=out+pitch; \
  SCATTER_ROW2(1,2,3,6,7,10,11,14,15); destrow+=pitch; \
  SCATTER_ROW2(2,24,25,44,45,16,17,20,21); destrow+=pitch; \
  SCATTER_ROW2(3,26,27,46,47,18,19,22,23); destrow+=pitch; \
  SCATTER_ROW2(4,28,29,32,33,48,49,52,53); destrow+=pitch; \
  SCATTER_ROW2(5,30,31,34,35,50,51,54,55); destrow+=pitch; \
  SCATTER_ROW2(6,36,37,40,41,56,57,60,61); destrow+=pitch; \
  SCATTER_ROW2(7,38,39,42,43,58,59,62,63);

#define SCATTER_ROW(row,a,b,c,d,e,f,g,h) \
  out[0]=coeffs[a]+motion[row*8+0]; out[1]=coeffs[b]+motion[row*8+1]; \
  out[2]=coeffs[c]+motion[row*8+2]; out[3]=coeffs[d]+motion[row*8+3]; \
  out[4]=coeffs[e]+motion[row*8+4]; out[5]=coeffs[f]+motion[row*8+5]; \
  out[6]=coeffs[g]+motion[row*8+6]; out[7]=coeffs[h]+motion[row*8+7];


#define SCATTER_ROW2(row,a,b,c,d,e,f,g,h) \
  destrow[0]=coeffs[a]+motion[row*8+0]; destrow[1]=coeffs[b]+motion[row*8+1]; \
  destrow[2]=coeffs[c]+motion[row*8+2]; destrow[3]=coeffs[d]+motion[row*8+3]; \
  destrow[4]=coeffs[e]+motion[row*8+4]; destrow[5]=coeffs[f]+motion[row*8+5]; \
  destrow[6]=coeffs[g]+motion[row*8+6]; destrow[7]=coeffs[h]+motion[row*8+7];

#define LL_GET1(i) if(bitlen){i=bits&1;bits>>=1;bitlen--;}else{U32 word=*cur;cur++;bits=word>>1;bitlen=31;(i)=word&1;}
#define LL_GETMASK(i,n,mask) if(bitlen>=(U32)(n)){(i)=bits&(mask);bits>>=(n);bitlen-=(n);}else{U32 word=*cur;(i)=((word<<bitlen)|bits)&(mask);bits=word>>((n)-bitlen);bitlen+=32-(n);cur++;}
#define LL_VALUE() \
  LL_GETMASK(value,plane,0xffffffffUL>>(32-plane)); \
  value|=mask; \
  LL_GET1(work.v); \
  work.coeffs[index]=work.v?-value:value;
#define LL_COEFF() \
  LL_GET1(work.v); \
  if (work.v) *--start=(index<<2)+3; \
  else { LL_VALUE(); }
#define LL_LASTVALUE() \
  LL_GET1(work.v); \
  work.coeffs[lastindex]=work.v?-1:1;
#define LL_LASTCOEFF() \
  LL_GET1(work.v); \
  if (work.v) *--start=(lastindex<<2)+3; \
  else { LL_LASTVALUE(); }

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _zigzagalign @ 0x003F0F60
// match: _zigzag @ 0x003F0F80
// match: _patternsalign @ 0x003F0FC0
// match: _patterns @ 0x003F0FC8

// match: _ReadBPLossless@8 @ 0x0034CEC0
void __stdcall ReadBPLossless(S16 *out,VARBITS *vb)
{
  /* The coefficient workspace also holds the current bit result. Keeping
   * this used scalar with the buffer preserves the original stack layout. */
  BINKLOSSLESSWORK work;
  U8 nodes[128];
  U8 nbits;
  U8 index;
  U8 plane;
  S16 mask;
  S16 value;
  U32 bits;
  U32 bitlen;
  U32 * cur;
  U8 * start;
  U8 * end;
  U8 * p;
  ((U32*)work.coeffs)[0]=0;((U32*)work.coeffs)[1]=0;memset(work.coeffs+4,0,120);
  cur=vb->cur;bits=vb->bits;bitlen=vb->bitlen;
  LL_GETMASK(nbits,4,15);
  start=nodes+64;end=start+6;
  start[0]=16;start[1]=96;start[2]=176;start[3]=7;start[4]=11;start[5]=15;
  mask=1<<(nbits-1);
  for(plane=nbits;plane>1;)
  {
    --plane;
    for(p=start;p<end;)
    {
      index=*p;
      if(!index) goto ll_next;
      {
        LL_GET1(work.v);
        if(!work.v) goto ll_next;
        {
          switch(index&3)
          {
          default: goto ll_next;
          case 0:index>>=2;*p=(index<<2)+17;goto ll_four;
          case 1:index>>=2;*p=(index<<2)+2;
            *end++=(index<<2)+18;*end++=(index<<2)+34;*end++=(index<<2)+50;break;
          case 2:index>>=2;*p++=0;
ll_four:
            LL_COEFF();++index;
            LL_COEFF();++index;
            LL_COEFF();++index;
            LL_COEFF();break;
          case 3:index>>=2;LL_VALUE();*p=0;goto ll_next;
          }
        }

      }

      continue;
ll_next:
      ++p;
    }
    mask>>=1;
  }
  if(nbits)
  {
    U8 lastindex;
    for(p=start;p<end;)
    {
      lastindex=*p;
      if(lastindex)
      {
        LL_GET1(work.v);
        if(work.v)
        {
          switch(lastindex&3)
          {
          default: goto ll_lastnext;
          case 0:lastindex>>=2;*p=(lastindex<<2)+17;goto ll_lastfour;
          case 1:lastindex>>=2;*p=(lastindex<<2)+2;
            *end++=(lastindex<<2)+18;*end++=(lastindex<<2)+34;*end++=(lastindex<<2)+50;break;
          case 2:lastindex>>=2;*p++=0;
ll_lastfour:
            LL_LASTCOEFF();++lastindex;
            LL_LASTCOEFF();++lastindex;
            LL_LASTCOEFF();++lastindex;
            LL_LASTCOEFF();break;
          case 3:lastindex>>=2;LL_LASTVALUE();*p=0;goto ll_lastnext;
          }
        }
        else {
ll_lastnext:
          ++p;
        }
      }
      else goto ll_lastnext;
    }
  }
  vb->cur=cur;vb->bits=bits;vb->bitlen=bitlen;
  out[1]=work.coeffs[1];
  *(U32*)(out+2)=*(U32*)(work.coeffs+4);
  *(U32*)(out+4)=*(U32*)(work.coeffs+8);
  *(U32*)(out+6)=*(U32*)(work.coeffs+12);
  *(U32*)(out+8)=*(U32*)(work.coeffs+2);
  *(U32*)(out+10)=*(U32*)(work.coeffs+6);
  *(U32*)(out+12)=*(U32*)(work.coeffs+10);
  *(U32*)(out+14)=*(U32*)(work.coeffs+14);
  *(U32*)(out+16)=*(U32*)(work.coeffs+24);
  *(U32*)(out+18)=*(U32*)(work.coeffs+44);
  *(U32*)(out+20)=*(U32*)(work.coeffs+16);
  *(U32*)(out+22)=*(U32*)(work.coeffs+20);
  *(U32*)(out+24)=*(U32*)(work.coeffs+26);
  *(U32*)(out+26)=*(U32*)(work.coeffs+46);
  *(U32*)(out+28)=*(U32*)(work.coeffs+18);
  *(U32*)(out+30)=*(U32*)(work.coeffs+22);
  *(U32*)(out+32)=*(U32*)(work.coeffs+28);
  *(U32*)(out+34)=*(U32*)(work.coeffs+32);
  *(U32*)(out+36)=*(U32*)(work.coeffs+48);
  *(U32*)(out+38)=*(U32*)(work.coeffs+52);
  *(U32*)(out+40)=*(U32*)(work.coeffs+30);
  *(U32*)(out+42)=*(U32*)(work.coeffs+34);
  *(U32*)(out+44)=*(U32*)(work.coeffs+50);
  *(U32*)(out+46)=*(U32*)(work.coeffs+54);
  *(U32*)(out+48)=*(U32*)(work.coeffs+36);
  *(U32*)(out+50)=*(U32*)(work.coeffs+40);
  *(U32*)(out+52)=*(U32*)(work.coeffs+56);
  *(U32*)(out+54)=*(U32*)(work.coeffs+60);
  *(U32*)(out+56)=*(U32*)(work.coeffs+38);
  *(U32*)(out+58)=*(U32*)(work.coeffs+42);
  *(U32*)(out+60)=*(U32*)(work.coeffs+58);
  *(U32*)(out+62)=*(U32*)(work.coeffs+62);
}


/* The coefficient order and the block patterns (binkxbox.lib's bitplane.obj .rdata), each after
   the zeros that align it (the library's `...align` symbols). */
const S32 zigzagalign[8] = { 0 };

const U8 zigzag[64] =
{
  0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15,
  20, 21, 28, 29, 22, 23, 30, 31, 16, 17, 24, 25, 32, 33, 40, 41,
  34, 35, 42, 43, 48, 49, 56, 57, 50, 51, 58, 59, 18, 19, 26, 27,
  36, 37, 44, 45, 38, 39, 46, 47, 52, 53, 60, 61, 54, 55, 62, 63,
};

const S32 patternsalign[2] = { 0 };

const U8 patterns[16][64] =
{
  { 0, 8, 16, 24, 32, 40, 48, 56, 57, 49, 41, 33, 25, 17, 9, 1,
    2, 10, 18, 26, 34, 42, 50, 58, 59, 51, 43, 35, 27, 19, 11, 3,
    4, 12, 20, 28, 36, 44, 52, 60, 61, 53, 45, 37, 29, 21, 13, 5,
    6, 14, 22, 30, 38, 46, 54, 62, 63, 55, 47, 39, 31, 23, 15, 7 },
  { 59, 58, 57, 56, 48, 49, 50, 51, 43, 42, 41, 40, 32, 33, 34, 35,
    27, 26, 25, 24, 16, 17, 18, 19, 11, 10, 9, 8, 0, 1, 2, 3,
    4, 5, 6, 7, 15, 14, 13, 12, 20, 21, 22, 23, 31, 30, 29, 28,
    36, 37, 38, 39, 47, 46, 45, 44, 52, 53, 54, 55, 63, 62, 61, 60 },
  { 25, 17, 18, 26, 27, 19, 11, 3, 2, 10, 9, 1, 0, 8, 16, 24,
    32, 40, 48, 56, 57, 49, 41, 42, 50, 58, 59, 51, 43, 35, 34, 33,
    29, 21, 22, 30, 31, 23, 15, 7, 6, 14, 13, 5, 4, 12, 20, 28,
    36, 44, 52, 60, 61, 53, 45, 46, 54, 62, 63, 55, 47, 39, 38, 37 },
  { 3, 11, 2, 10, 1, 9, 0, 8, 16, 24, 17, 25, 18, 26, 19, 27,
    35, 43, 34, 42, 33, 41, 32, 40, 48, 56, 49, 57, 50, 58, 51, 59,
    60, 52, 61, 53, 62, 54, 63, 55, 47, 39, 46, 38, 45, 37, 44, 36,
    28, 20, 29, 21, 30, 22, 31, 23, 15, 7, 14, 6, 13, 5, 12, 4 },
  { 24, 25, 16, 17, 8, 9, 0, 1, 2, 3, 10, 11, 18, 19, 26, 27,
    28, 29, 20, 21, 12, 13, 4, 5, 6, 7, 14, 15, 22, 23, 30, 31,
    39, 38, 47, 46, 55, 54, 63, 62, 61, 60, 53, 52, 45, 44, 37, 36,
    35, 34, 43, 42, 51, 50, 59, 58, 57, 56, 49, 48, 41, 40, 33, 32 },
  { 0, 1, 2, 3, 8, 9, 10, 11, 16, 17, 18, 19, 24, 25, 26, 27,
    32, 33, 34, 35, 40, 41, 42, 43, 48, 49, 50, 51, 56, 57, 58, 59,
    4, 5, 6, 7, 12, 13, 14, 15, 20, 21, 22, 23, 28, 29, 30, 31,
    36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 60, 61, 62, 63 },
  { 6, 7, 15, 14, 13, 5, 12, 4, 3, 11, 2, 10, 9, 1, 0, 8,
    16, 24, 17, 25, 18, 26, 19, 27, 20, 28, 21, 29, 22, 30, 23, 31,
    39, 47, 38, 46, 37, 45, 36, 44, 35, 43, 34, 42, 33, 41, 32, 40,
    49, 48, 56, 57, 58, 50, 59, 51, 60, 52, 61, 53, 54, 55, 63, 62 },
  { 0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8,
    16, 17, 18, 19, 20, 21, 22, 23, 31, 30, 29, 28, 27, 26, 25, 24,
    32, 33, 34, 35, 36, 37, 38, 39, 47, 46, 45, 44, 43, 42, 41, 40,
    48, 49, 50, 51, 52, 53, 54, 55, 63, 62, 61, 60, 59, 58, 57, 56 },
  { 0, 8, 9, 1, 2, 3, 11, 10, 18, 19, 27, 26, 25, 17, 16, 24,
    32, 40, 41, 33, 34, 35, 43, 42, 50, 49, 48, 56, 57, 58, 59, 51,
    52, 60, 61, 62, 63, 55, 54, 53, 45, 44, 36, 37, 38, 46, 47, 39,
    31, 23, 22, 30, 29, 28, 20, 21, 13, 12, 4, 5, 6, 14, 15, 7 },
  { 24, 25, 16, 17, 8, 9, 0, 1, 2, 3, 10, 11, 18, 19, 26, 27,
    28, 29, 20, 21, 12, 13, 4, 5, 6, 7, 14, 15, 22, 23, 30, 31,
    38, 39, 46, 47, 54, 55, 62, 63, 60, 61, 52, 53, 44, 45, 36, 37,
    34, 35, 42, 43, 50, 51, 58, 59, 56, 57, 48, 49, 40, 41, 32, 33 },
  { 0, 8, 1, 9, 2, 10, 3, 11, 19, 27, 18, 26, 17, 25, 16, 24,
    32, 40, 33, 41, 34, 42, 35, 43, 51, 59, 50, 58, 49, 57, 48, 56,
    60, 52, 61, 53, 62, 54, 63, 55, 47, 39, 46, 38, 45, 37, 44, 36,
    31, 23, 30, 22, 29, 21, 28, 20, 12, 4, 13, 5, 14, 6, 15, 7 },
  { 0, 8, 16, 24, 25, 26, 27, 19, 11, 3, 2, 1, 9, 17, 18, 10,
    4, 12, 20, 28, 29, 30, 31, 23, 15, 7, 6, 5, 13, 21, 22, 14,
    36, 44, 52, 60, 61, 62, 63, 55, 47, 39, 38, 37, 45, 53, 54, 46,
    32, 40, 48, 56, 57, 58, 59, 51, 43, 35, 34, 33, 41, 49, 50, 42 },
  { 0, 8, 9, 1, 2, 3, 11, 10, 19, 27, 26, 18, 17, 16, 24, 25,
    33, 32, 40, 41, 42, 34, 35, 43, 51, 59, 58, 50, 49, 57, 56, 48,
    52, 60, 61, 53, 54, 62, 63, 55, 47, 39, 38, 46, 45, 44, 36, 37,
    29, 28, 20, 21, 22, 30, 31, 23, 14, 15, 7, 6, 5, 13, 12, 4 },
  { 24, 16, 8, 0, 1, 2, 3, 11, 19, 27, 26, 25, 17, 10, 9, 18,
    28, 20, 12, 4, 5, 6, 7, 15, 23, 31, 30, 29, 21, 14, 13, 22,
    60, 52, 44, 36, 37, 38, 39, 47, 55, 63, 62, 61, 53, 46, 45, 54,
    56, 48, 40, 32, 33, 34, 35, 43, 51, 59, 58, 57, 49, 42, 41, 50 },
  { 0, 8, 9, 1, 2, 10, 18, 17, 16, 24, 25, 26, 27, 19, 11, 3,
    7, 6, 14, 15, 23, 22, 21, 13, 5, 4, 12, 20, 28, 29, 30, 31,
    63, 62, 54, 55, 47, 46, 45, 53, 61, 60, 52, 44, 36, 37, 38, 39,
    56, 48, 49, 57, 58, 50, 42, 41, 40, 32, 33, 34, 35, 43, 51, 59 },
  { 0, 1, 8, 9, 16, 17, 24, 25, 32, 33, 40, 41, 48, 49, 56, 57,
    58, 59, 50, 51, 42, 43, 34, 35, 26, 27, 18, 19, 10, 11, 2, 3,
    4, 5, 12, 13, 20, 21, 28, 29, 36, 37, 44, 45, 52, 53, 60, 61,
    62, 63, 54, 55, 46, 47, 38, 39, 30, 31, 22, 23, 14, 15, 6, 7 },
};

// match: _ReadBPLossyWithMotion@20 @ 0x0034DCB0
void __stdcall ReadBPLossyWithMotion(U8 *out, U32 pitch, VARBITS *vb,S32 limit,U8 *motion)
{
  S8 coeffs[64];
  ((U32*)coeffs)[0]=0;
  ((U32*)coeffs)[1]=0;
  memset(coeffs+8,0,56);
  readlossy(coeffs,vb,limit);
  { U8 *destrow; SCATTER_BLOCK; }
}
