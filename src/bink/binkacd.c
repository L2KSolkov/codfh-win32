/*
 * codfh-match: Bink's audio decompressor (the library's binkacd.obj): each
 * block's band scales and run-length coded coefficients, the inverse DCT or
 * real FFT (fft.obj) and the conversion to 16-bit samples with the block
 * overlap blended in. Bink 1.6 reads the band scales from a table instead
 * of calling pow, as the 1.5s library does.
 */
#include "bink.h"
#include "binkint.h"

#pragma code_seg("BINK")

#pragma data_seg("BINKDATA")
static U8 rlelens[16] = { 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 32, 64 };
static U32 bandtopfreq[25] = {
  0, 100, 200, 300, 400, 510, 630, 770, 920, 1080, 1270, 1480, 1720, 2000, 2320, 2700, 3150,
  3700, 4400, 5300, 6400, 7700, 9500, 12000, 15500,
};
// 10 to the power of i * 0.0664 (the 1.5s library's Undecibel)
static F32 unk_52F2E8[256] = {
  1.0f, 1.16519868f, 1.35768807f, 1.58197641f,
  1.84331691f, 2.14783049f, 2.50264931f, 2.91608381f,
  3.39781713f, 3.95913219f, 4.61317587f, 5.37526655f,
  6.26325369f, 7.29793501f, 8.50354481f, 9.90831947f,
  11.5451612f, 13.4524069f, 15.6747274f, 18.2641716f,
  21.2813911f, 24.7970486f, 28.8934898f, 33.6666565f,
  39.2283478f, 45.7088203f, 53.2598572f, 62.0583191f,
  72.3102722f, 84.2558365f, 98.1747971f, 114.393143f,
  133.290741f, 155.310211f, 180.967255f, 210.862808f,
  245.697083f, 286.285919f, 333.579987f, 388.686981f,
  452.897583f, 527.715698f, 614.893616f, 716.473267f,
  834.83374f, 972.747253f, 1133.44385f, 1320.68726f,
  1538.86316f, 1793.08142f, 2089.29614f, 2434.44507f,
  2836.6123f, 3305.21729f, 3851.23486f, 4487.4541f,
  5228.77539f, 6092.5625f, 7099.04639f, 8271.7998f,
  9638.29004f, 11230.5234f, 13085.792f, 15247.5479f,
  17766.4238f, 20701.4141f, 24121.2598f, 28106.0625f,
  32749.1484f, 38159.2656f, 44463.125f, 51808.3789f,
  60367.0547f, 70339.6172f, 81959.6328f, 95499.2578f,
  111275.617f, 129658.203f, 151077.578f, 176035.391f,
  205116.219f, 239001.156f, 278483.844f, 324489.031f,
  378094.188f, 440554.875f, 513333.969f, 598136.062f,
  696947.375f, 812082.188f, 946237.188f, 1102554.38f,
  1284694.88f, 1496924.88f, 1744214.88f, 2032357.0f,
  2368099.75f, 2759306.75f, 3215140.75f, 3746278.0f,
  4365158.5f, 5086277.0f, 5926523.5f, 6905577.5f,
  8046370.0f, 9375620.0f, 10924461.0f, 12729167.0f,
  14832010.0f, 17282238.0f, 20137242.0f, 23463890.0f,
  27340094.0f, 31856642.0f, 37119320.0f, 43251384.0f,
  50396456.0f, 58721888.0f, 68422664.0f, 79726008.0f,
  92896640.0f, 108243048.0f, 126124656.0f, 146960288.0f,
  171237936.0f, 199526224.0f, 232487712.0f, 270894368.0f,
  315645792.0f, 367790080.0f, 428548512.0f, 499344192.0f,
  581835200.0f, 677953664.0f, 789950720.0f, 920449600.0f,
  1.07250669e+09f, 1.24968346e+09f, 1.45612954e+09f, 1.69668019e+09f,
  1.9769696e+09f, 2.3035625e+09f, 2.68410803e+09f, 3.12751923e+09f,
  3.6441815e+09f, 4.24619571e+09f, 4.94766182e+09f, 5.7650089e+09f,
  6.71738112e+09f, 7.82708429e+09f, 9.12010854e+09f, 1.06267382e+10f,
  1.23822623e+10f, 1.44277965e+10f, 1.68112497e+10f, 1.95884462e+10f,
  2.28244337e+10f, 2.65950003e+10f, 3.098846e+10f, 3.61077146e+10f,
  4.2072662e+10f, 4.90230129e+10f, 5.71215503e+10f, 6.65579602e+10f,
  7.75532462e+10f, 9.03649444e+10f, 1.05293119e+11f, 1.22687414e+11f,
  1.42955217e+11f, 1.66571229e+11f, 1.94088583e+11f, 2.26151776e+11f,
  2.63511753e+11f, 3.07043566e+11f, 3.57766758e+11f, 4.16869384e+11f,
  4.85735662e+11f, 5.65978595e+11f, 6.59477496e+11f, 7.6842238e+11f,
  8.9536476e+11f, 1.04327787e+12f, 1.21562608e+12f, 1.41644595e+12f,
  1.65044093e+12f, 1.92309179e+12f, 2.24078411e+12f, 2.6109587e+12f,
  3.04228572e+12f, 3.54486741e+12f, 4.13047508e+12f, 4.81282438e+12f,
  5.60789665e+12f, 6.53431407e+12f, 7.6137743e+12f, 8.87156009e+12f,
  1.03371306e+13f, 1.20448111e+13f, 1.40345984e+13f, 1.63530964e+13f,
  1.90546077e+13f, 2.22024035e+13f, 2.58702133e+13f, 3.01439386e+13f,
  3.51236784e+13f, 4.09260639e+13f, 4.76870009e+13f, 5.55648308e+13f,
  6.47440693e+13f, 7.5439708e+13f, 8.79022519e+13f, 1.02423595e+14f,
  1.19343837e+14f, 1.39059289e+14f, 1.62031701e+14f, 1.88799129e+14f,
  2.1998851e+14f, 2.56330326e+14f, 2.98675784e+14f, 3.48016637e+14f,
  4.05508532e+14f, 4.72498043e+14f, 5.50554107e+14f, 6.41504905e+14f,
  7.4748074e+14f, 8.709636e+14f, 1.01484568e+15f, 1.18249684e+15f,
  1.3778439e+15f, 1.60546186e+15f, 1.87068213e+15f, 2.17971644e+15f,
  2.53980287e+15f, 2.95937501e+15f, 3.44825986e+15f, 4.01790808e+15f,
  4.68166146e+15f, 5.45506588e+15f, 6.35623592e+15f, 7.40627758e+15f,
  8.62978545e+15f, 1.0055415e+16f, 1.1716557e+16f, 1.36521173e+16f,
  1.59074293e+16f, 1.85353158e+16f, 2.15973268e+16f, 2.51651776e+16f,
  2.93224332e+16f, 3.41664605e+16f, 3.98107176e+16f, 4.63873948e+16f,
  5.40505356e+16f, 6.29796137e+16f, 7.33837683e+16f, 8.55066742e+16f,
};
static F32 invertbins[24] = {
  1.1920929e-07f, 2.38418579e-07f, 4.76837158e-07f, 9.53674316e-07f,
  1.90734863e-06f, 3.81469727e-06f, 7.62939453e-06f, 1.52587891e-05f,
  3.05175781e-05f, 6.10351562e-05f, 0.000122070312f, 0.000244140625f,
  0.00048828125f, 0.0009765625f, 0.001953125f, 0.00390625f,
  0.0078125f, 0.015625f, 0.03125f, 0.0625f,
  0.125f, 0.25f, 0.5f, 1.0f,
};
/* a word nothing in the image reads (0x52F748, before binkds' data) */
U32 unk_52F748 = 0;
#pragma data_seg()

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@40000000 @ 0x003CDC78
// match: _rlelens @ 0x0052F270
// match: _bandtopfreq @ 0x0052F280
// match: _unk_52F2E8 @ 0x0052F2E8
// match: _invertbins @ 0x0052F6E8
// match: _unk_52F748 @ 0x0052F748

// match: _quanttos16s @ 0x00344AB0

static void quanttos16s(U32 count, S16 *out, F32 *src, F32 scale)
{
  for (; count; count--)
  {
    S32 v = (S32)(scale * *src);

    *out = (S16)((v >= 32767) ? 32767 : ((v <= -32768) ? -32768 : (S16)v));
    out++;
    src++;
  }
}

// match: _quanttos16chans2 @ 0x00344B00
static void quanttos16chans2(S16 *out, F32 *src, U32 count, F32 scale)
{
  U32 i;

  for (i = count; i; i--)
  {
    S32 v = (S32)(scale * src[0]);

    *out++ = (S16)((v >= 32767) ? 32767 : ((v <= -32768) ? -32768 : (S16)v));
    v = (S32)(scale * src[count]);
    *out++ = (S16)((v >= 32767) ? 32767 : ((v <= -32768) ? -32768 : (S16)v));
    src++;
  }
}

// match: _read_rle_samples @ 0x00344B80
static void read_rle_samples(F32 *coeffs, U32 count, VARBITS *vb, F32 *quants, U32 *bandtops)
{
  U32 *cur = vb->cur;
  U32 bits = vb->bits;
  U32 bitlen = vb->bitlen;
  F32 q = 0.0f;
  F32 nq = 0.0f;
  U32 k = 0;
  U32 i;
  U32 j;
  U32 width;
  U32 v;
  F32 *dst;

  while ((U32)(bandtops[k] * 2) < 2)
  {
    q = quants[k];
    nq = -q;
    k++;
  }

  dst = coeffs + 2;
  for (i = 2; i < count;)
  {
    VarBitsGet1(v);
    if (v)
    {
      VarBitsGet(v, 4);
      j = i + rlelens[v] * 8;
    }
    else
      j = i + 8;
    if (j > count)
      j = count;

    VarBitsGet(width, 4);
    if (width == 0)
    {
      i = j-i;
      memset(dst, 0, i*4);
      dst += i;
      i = j;
      while (i > bandtops[k] * 2)
      {
        q = quants[k];
        nq = -q;
        k++;
      }
    }
    else
    {


      for (; i < j; i++)
      {
        S32 c;

        if (i == bandtops[k] * 2)
        {
          q = quants[k];
          nq = -q;
          k++;
        }

        VarBitsGetMask(c, width, (0xffffffff >> (32 - width)));
        if (c)
        {
          VarBitsGet1(v);
          *dst++ = (v ? nq : q) * (F32)c;
        }
        else
          *dst++ = 0;
      }
    }
  }

  vb->cur = cur;
  vb->bitlen = bitlen;
  vb->bits = bits;
}


static F32 binkaudioagent_fxptof(U32 v)
{
  F32 result = (F32)(S32)((v >> 5) & 0x77fffff) * invertbins[v & 31];
  if (v & 0x10000000) result = -result;
  return result;
}

// match: _Unquant @ 0x00344E70
static U32 Unquant(U32 size, F32 scale, U32 chans, U32 flags, U32 *ip, F32 *work, S16 *out, void *in,
                   U32 bands, U32 *bandtops)
{
  VARBITS vb;
  F32 quants[26];
  F32 coeffs[4096];
  F32 *c;
  U32 ch;
  U32 i;
  U32 v;

  vb.cur = vb.init = (U32 *)in;
  vb.bitlen = 0;
  vb.bits = 0;
  if (flags & 1)
  {
    vb.bits = *vb.cur >> 2;
    vb.bitlen = 30;
    vb.cur++;
  }

  c = coeffs;
  for (ch = 0; ch < chans; ch++)
  {
    VarBitsGetStruct(vb, v, 29);
    c[0] = binkaudioagent_fxptof(v);
    VarBitsGetStruct(vb, v, 29);
    c[1] = binkaudioagent_fxptof(v);

    for (i = 0; i < bands; i++)
    {
      VarBitsGetStruct(vb, v, 8);
      quants[i] = unk_52F2E8[v];
    }

    read_rle_samples(c, size, &vb, quants, bandtops);
    if (flags & 1)
      ddct(size, 1, c, ip, work);
    else
      rdft(size, -1, c, ip, work);
    c += size;
  }

  if (chans == 1)
    quanttos16s(size, out, coeffs, scale);
  else
    quanttos16chans2(out, coeffs, size, scale);

  return (U32)(((U8 *)vb.cur - (U8 *)vb.init) << 3) >> 3;
}

// match: _BinkAudioDecompressOpen@12 @ 0x00345230
RADEXPFUNC U32 RADEXPLINK BinkAudioDecompressOpen(U32 freq, U32 chans, U32 flags)
{
  U32 size;
  U32 outsize;
  U32 half;
  U32 stereo;
  U32 bands;
  U32 i;
  U32 *bandtops;
  U32 *ip;
  F32 *work;
  S16 *prev;
  S16 *outbuf;
  BINKAC *ba;

  if (freq >= 44100)
    size = 2048;
  else if (freq >= 22050)
    size = 1024;
  else
    size = 512;

  outsize = size * chans * 2;
  stereo = flags & 1;
  if (!stereo)
  {
    freq *= chans;
    size *= chans;
    chans = 1;
  }

  half = size >> 1;
  freq = (freq + 1) >> 1;
  for (i = 0; i < 25; i++)
  {
    if (bandtopfreq[i] >= freq)
      break;
  }

  bands = i;
  pushmalloc(&bandtops, bands * 4 + 4);
  pushmalloc(&ip, (U32)sqrt((F32)half) * 4 + 8);
  if (stereo)
    pushmalloc(&work, size * 5 * 4 / 4);
  else
    pushmalloc(&work, half * 4 - 1);
  pushmalloc(&prev, outsize >> 1);
  pushmalloc(&outbuf, outsize);

  ba = (BINKAC *)popmalloc(sizeof(BINKAC));
  if (ba)
  {
    memset(ba, 0, sizeof(BINKAC));
    ba->bandtops = bandtops;
    ba->ip = ip;
    ba->work = work;
    ba->prev = prev;
    ba->outbuf = outbuf;
    ba->flags = flags;
    ba->chans = chans;
    ba->blocksize = outsize;
    ba->bands = bands;
    ba->size = size;
    ba->overlap = outsize >> 4;
    ba->scale = 2.0f / (F32)sqrt((F32)size);

    for (i = 0; i < bands; i++)
    {
      ba->bandtops[i] = (bandtopfreq[i] * half) / freq;
      if (ba->bandtops[i] == 0)
        ba->bandtops[i] = 1;
    }
    ba->bandtops[i] = half;
    ba->ip[0] = 0;
    ba->first = 1;
    return (U32)ba;
  }
  return 0;
}

static void copyoverlap(void *dst, void *src, U32 bytes, U32 overlap)
{
  memcpy(dst, (U8 *)src + (bytes - overlap), overlap);
}

// match: _BinkAudioDecompress@20 @ 0x00345460
RADEXPFUNC void RADEXPLINK BinkAudioDecompress(U32 handle, void PTR4 *PTR4 *out, U32 PTR4 *outlen,
  void PTR4 *in, void PTR4 *PTR4 *inend)
{
  BINKAC *ba = (BINKAC *)handle;
  U32 used = Unquant(ba->size, ba->scale, ba->chans, ba->flags, ba->ip, ba->work, ba->outbuf, in,
                     ba->bands, ba->bandtops);
  U32 i;

  if (ba->first)
    ba->first = 0;
  else
  {
    U32 n = ba->overlap >> 1;

    for (i = 0; i < n; i++)
      ba->outbuf[i] = (S16)((U32)(ba->prev[i] * (S32)(n - i) + ba->outbuf[i] * (S32)i) / n);
  }

  copyoverlap(ba->prev, ba->outbuf, ba->blocksize, ba->overlap);

  if (outlen)
    *outlen = ba->blocksize - ba->overlap;
  if (out)
    *out = ba->outbuf;
  if (inend)
    *inend = (U8 *)in + used;
}

// match: _BinkAudioDecompressClose@4 @ 0x00345530
RADEXPFUNC void RADEXPLINK BinkAudioDecompressClose(U32 handle)
{
  radfree((void *)handle);
}
