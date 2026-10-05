/*
 * RwStream's open, close and reads and their enums, copied from RenderWare 3.7.2
 * RWSDK/src/bastream.h (the prototypes, the stream and access types, the
 * memory block, the chunk header and RwStream with its union). The game calls the image's
 * RwStreamOpen and RwStreamClose. RwStreamReadInt32 has no body of its own in
 * the image: on a little-endian target it is RwStreamReadInt16 byte for byte,
 * and /OPT:ICF folded the two (config/aliases.txt); likewise RwStreamWriteInt16
 * into RwStreamWriteInt32.
 */
#ifndef RW_BASTREAM_H
#define RW_BASTREAM_H

#include "rw/batypes.h"

typedef struct RwStream RwStream;

enum RwStreamType
{
    rwNASTREAM = 0,
    rwSTREAMFILE,
    rwSTREAMFILENAME,
    rwSTREAMMEMORY,
    rwSTREAMCUSTOM,
    rwSTREAMTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwStreamType RwStreamType;

enum RwStreamAccessType
{
    rwNASTREAMACCESS = 0,
    rwSTREAMREAD,
    rwSTREAMWRITE,
    rwSTREAMAPPEND,
    rwSTREAMACCESSTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RwStreamAccessType RwStreamAccessType;

typedef struct RwMemory RwMemory;
struct RwMemory
{
    RwUInt8 *start;
    RwUInt32 length;
};

typedef struct RwStreamMemory RwStreamMemory;
struct RwStreamMemory
{
    RwUInt32 position;
    RwUInt32 nSize;
    RwUInt8 *memBlock;
};

typedef union RwStreamFile RwStreamFile;
union RwStreamFile
{
    void *fpFile;
    const void *constfpFile;
};

typedef RwBool (*rwCustomStreamFnClose) (void *data);
typedef RwUInt32 (*rwCustomStreamFnRead) (void *data, void *buffer, RwUInt32 length);
typedef RwBool (*rwCustomStreamFnWrite) (void *data, const void *buffer, RwUInt32 length);
typedef RwBool (*rwCustomStreamFnSkip) (void *data, RwUInt32 offset);

typedef struct RwStreamCustom RwStreamCustom;
struct RwStreamCustom
{
    rwCustomStreamFnClose sfnclose;
    rwCustomStreamFnRead sfnread;
    rwCustomStreamFnWrite sfnwrite;
    rwCustomStreamFnSkip sfnskip;
    void *data;
};

typedef union RwStreamUnion RwStreamUnion;
union RwStreamUnion
{
    RwStreamMemory memory;
    RwStreamFile file;
    RwStreamCustom custom;
};

struct RwStream
{
    RwStreamType type;
    RwStreamAccessType accessType;
    RwInt32 position;
    RwStreamUnion Type;
    RwBool rwOwned;
};

typedef struct RwChunkHeaderInfo RwChunkHeaderInfo;
struct RwChunkHeaderInfo
{
    RwUInt32 type;
    RwUInt32 length;
    RwUInt32 version;
    RwUInt32 buildNum;
    RwBool isComplex;
};

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwStream *RwStreamOpen(RwStreamType type, RwStreamAccessType accessType,
                              const void *pData);
extern RwBool RwStreamClose(RwStream * stream, void *pData);
extern RwUInt32 RwStreamRead(RwStream * stream, void *buffer, RwUInt32 length);
/* The resource stream's embedded asset handler (0x1302E0) skips with it. */
extern RwStream *RwStreamSkip(RwStream * stream, RwUInt32 offset);
extern RwStream *RwStreamReadInt16(RwStream * stream, RwInt16 * ints, RwUInt32 numBytes);
extern RwStream *RwStreamReadInt32(RwStream * stream, RwInt32 * ints, RwUInt32 numBytes);
extern RwStream *RwStreamReadChunkHeaderInfo(RwStream * stream, RwChunkHeaderInfo * chunkHeaderInfo);
extern RwStream *RwStreamWrite(RwStream * stream, const void *buffer, RwUInt32 size);
extern RwStream *RwStreamWriteInt32(RwStream * stream, const RwInt32 * ints, RwUInt32 numBytes);
extern RwStream *RwStreamWriteInt16(RwStream * stream, const RwInt16 * ints, RwUInt32 numBytes);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
