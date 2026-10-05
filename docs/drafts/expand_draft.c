/*
 * codfh-match: Bink's plane decoder (the library's expand.obj): the
 * Huffman-coded bundles each plane's blocks read their values from, the
 * bundle sizes, and the plane and frame expanders.
 */
#include "bink.h"
#include "binkint.h"

// match: _simpmergesort @ 0x00346170
static U32 simpmergesort(U8 *a, U32 n, U8 *out, U32 bits, U8 *b)
{
  U32 nb = n;
  U32 flags = bits;

  // RAD reuses bits as the count of merge decisions it returns
  bits = 0;
  do
  {
    bits++;
    if (flags & 1)
    {
      *out++ = *b++;
      nb--;
    }
    else
    {
      *out++ = *a++;
      n--;
    }
    flags >>= 1;
  } while ((n) && (nb));

  if (n)
  {
    do
    {
      *out++ = *a++;
    } while (--n);
    return bits;
  }

  while (nb)
  {
    *out++ = *b++;
    nb--;
  }
  return bits;
}

U32 expand_probe(U8 *a, U8 *out, U8 *b, U32 bits)
{
  return simpmergesort(a, 4, out, bits, b) + simpmergesort(b, 2, out, bits, a);
}
