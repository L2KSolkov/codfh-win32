/*
 * RenderWare scalar types, copied from RenderWare 3.7.2
 * D:\RW_372_src\RWSDK\os\win\ostypes.h (the "RWPUBLIC" typedef block only).
 *
 * The image links RenderWare 3.6, not 3.7.2. These typedefs are the plain C
 * scalars both versions use on x86; anything else from 3.7.2 is checked
 * against the bytes before it is copied.
 */
#ifndef WIN_OSTYPES_H
#define WIN_OSTYPES_H

#define rwLITTLEENDIAN         /* This is a little endian machine */

typedef long RwFixed;
typedef int  RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;

#ifdef RWUNICODE
typedef wchar_t RwChar;
#else /* RWUNICODE */
typedef char RwChar;
#endif /* RWUNICODE */
typedef float RwReal;
/* Not a RenderWare type: the C library's double, for the calls that pass one
 * explicitly (unit_07CA20's sub_7DEB0 calls fabs on one). */
typedef double RwDouble;
typedef RwInt32 RwBool;

typedef __int64 RwInt64;
typedef unsigned __int64 RwUInt64;

/*
 * Structure alignment. The Windows ostypes.h defines RWALIGN as nothing and
 * rwMATRIXALIGNMENT as 4; the Xbox build aligns. Evidence: sub_19F90 copies an
 * RwMatrix into a local and realigns its stack frame to 16 (and esp, -16)
 * to hold it. No Xbox ostypes.h is in either reference tree, so the form
 * below is inferred from that.
 */
#define RWALIGN(type, x)   __declspec(align(x)) type
#define rwMATRIXALIGNMENT 16

/*
 * The game's debug logs its retail build compiled out (an if (0) round each call in the image):
 * the Win32 port runs them. (Here since every unit that logs takes RwChar from this header.)
 */
#ifdef CODFH_WIN32
#define CODFH_DEBUG_LOGS 1
#else
#define CODFH_DEBUG_LOGS 0
#endif

#endif /* WIN_OSTYPES_H */
