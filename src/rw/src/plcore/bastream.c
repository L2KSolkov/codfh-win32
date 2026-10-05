/*
 * Stream handling functions.
 *
 * Copyright (c) 1998 Criterion Software Ltd.
 *
 */

/**
 * \ingroup rwstream
 * \page rwstreamoverview RwStream Overview
 *
 * \par Requirements
 * \li \b Headers: rwcore.h
 * \li \b Libraries: rwcore.lib
 *
 * \subsection streamoverview Overview
 *
 * Represents a RenderWare Binary Stream.
 *
 * RenderWare has only one primary file format: the RenderWare Binary Stream.
 * Serializable objects can be read from and written to these streams. The resulting data files
 * are generally platform-neutral. (An exception to this is \ref RwTexDictionary, which is
 * platform-dependent.)
 *
 * Serializable objects have dedicated RenderWare Binary Stream read/write functions in
 * their respective APIs. The RwStream API itself is used by these functions to perform
 * the low-level work. Developers can also use these functions to interrogate RenderWare
 * Binary Streams and learn their contents.
 *
 * Developers should note that major version updates to RenderWare may require
 * re-exporting and/or rebuilding of data as the RenderWare Binary Stream system includes
 * a versioning system to prevent RenderWare from attempting to load incomplete data structures.
 *
*/


/****************************************************************************
 Includes
 */

#include <stdlib.h>
#include <string.h>

#include "batypes.h"
#include "balibtyp.h"
#include "badebug.h"
#include "bamemory.h"
#include "fsys36.h"

/* Abstraction of string functionality  -- for unicode support */
#include "rwstring.h"

/* Stream handling */
#include "bastream.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@(#)$Id: //RenderWare/RW36Active/rwsdk/src/plcore/bastream.c#1 $";

/****************************************************************************
 Local (Static) Prototypes
 */

/****************************************************************************
 Local Defines
 */

#define RWSTREAMGLOBAL(var) (RWPLUGINOFFSET(rwStreamGlobals, RwEngineInstance, streamModule.globalsOffset)->var)
#define RWSETERROR(dummy)

#define rwSTREAMMINALLOCSIZE 512

/****************************************************************************
 Local Types
 */

typedef union _rwvoidptr _rwvoidptr;
union _rwvoidptr
{
    const void * constvoidptr;
    void * voidptr;
};

/****************************************************************************
 Globals (across program)
 */

/****************************************************************************
 Local (static) Globals
 */
static RwModuleInfo streamModule;

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   Stream handling open/close

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

static RwInt32 _rwStreamFreeListBlockSize = 16,
               _rwStreamFreeListPreallocBlocks = 1;
static RwFreeList _rwStreamFreeList;

/**
 * \ingroup rwstream
 * \ref RwStreamSetFreeListCreateParams allows the developer to specify
 * how many \ref RwStream s to preallocate space for.
 * Call before \ref RwEngineInit.
 *
 * \param blockSize  number of entries per freelist block.
 * \param numBlocksToPrealloc  number of blocks to allocate on
 * \ref RwFreeListCreateAndPreallocateSpace.
 *
 * \see RwFreeList
 *
 */
void
RwStreamSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc )
{
#if 0
    /*
     * Can not use debugging macros since the debugger is not initialized before
     * RwEngineInit.
     */
    /* Do NOT comment out RWAPIFUNCTION as gnumake verify will not function */
    RWAPIFUNCTION(RWSTRING("RwStreamSetFreeListCreateParams"));
#endif
    _rwStreamFreeListBlockSize = blockSize;
    _rwStreamFreeListPreallocBlocks = numBlocksToPrealloc;
#if 0
    RWRETURNVOID();
#endif
}

/****************************************************************************
 _rwStreamModuleOpen

 On entry   :
 On exit    : TRUE on success
 */

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00416288
// match: ??_C@_02BOGAIONP@ab?$AA@ @ 0x003F2C9C
// match: __rwStreamFreeListBlockSize @ 0x00435488
// match: __rwStreamFreeListPreallocBlocks @ 0x0043548C

// match: __rwStreamModuleOpen @ 0x002A6C50

void               *
_rwStreamModuleOpen(void *instance, RwInt32 offset,
                    RwInt32 __RWUNUSED__ size)
{
    RWFUNCTION(RWSTRING("_rwStreamModuleOpen"));

    /* Store the globals offset (same for all instances) */
    streamModule.globalsOffset = offset;

    /* Get on with the initialization */
    RWSTREAMGLOBAL(streamFreeList) = RwFreeListCreateAndPreallocateSpace(sizeof(RwStream), _rwStreamFreeListBlockSize, sizeof(RwUInt32), _rwStreamFreeListPreallocBlocks, &_rwStreamFreeList, rwID_STREAMMODULE | rwMEMHINTDUR_GLOBAL);
    if (!RWSTREAMGLOBAL(streamFreeList))
    {
        /* Failure */
        RWRETURN(NULL);
    }

    /* One more module instance */
    ++streamModule.numInstances;

    /* Success */
    RWRETURN(instance);
}

/****************************************************************************
 _rwStreamModuleClose

 On entry   :
 On exit    : TRUE on success
 */

// match: __rwStreamModuleClose @ 0x002A6CA0
void               *
_rwStreamModuleClose(void *instance,
                     RwInt32 __RWUNUSED__ offset,
                     RwInt32 __RWUNUSED__ size )
{
    RWFUNCTION(RWSTRING("_rwStreamModuleClose"));

    if (RWSTREAMGLOBAL(streamFreeList))
    {
        RwFreeListDestroy(RWSTREAMGLOBAL(streamFreeList));
    }

    /* One less module instance */
    --streamModule.numInstances;

    /* Success */
    RWRETURN(instance);
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   Stream Handling

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


static RwStream    *
StreamFileInitialize(RwStream * stream,
                     const void *pData)
{
    _rwvoidptr voidptr;
    RWFUNCTION(RWSTRING("StreamFileInitialize"));

    /*
     * if it's not a file the ftell won't work
     */

    /*
     * Evil trick so that calling ftel with a
     * const ptr won't trigger any warning :)
     */
    voidptr.constvoidptr = pData;
    if (-1 == RwFtell(voidptr.voidptr))
    {
        RWASSERT(-1 != RwFtell(voidptr.voidptr));
        RWRETURN(NULL);
    }

    /*
     * Copy the file handle
     */
    stream->Type.file.constfpFile = pData;
    /* codfh-match: 3.6 keeps the stream's position */
    stream->position = 0;

    RWRETURN(stream);
}

// match: _StreamFileNameInitialize @ 0x002A6CD0
static RwStream    *
StreamFileNameInitialize(RwStream * stream,
                         RwStreamAccessType accessType,
                         const void *pData)
{

    RwStream           *result = (RwStream *)NULL;
    void               *fp = NULL; /* File handle */
    const RwChar       *cpFile = (const RwChar *) pData;

    RWFUNCTION(RWSTRING("StreamFileNameInitialize"));

    switch (accessType)
    {
        case rwSTREAMREAD:
            {
                fp = RwFopen(cpFile, RWSTRING("rb"));
                break;
            }
        case rwSTREAMWRITE:
            {
                fp = RwFopen(cpFile, RWSTRING("wb"));
                break;
            }
        case rwSTREAMAPPEND:
            {
                fp = RwFopen(cpFile, RWSTRING("ab"));
                break;
            }
        default:
            {
                RWERROR((E_RW_INVSTREAMACCESSTYPE));
                break;
            }
    }

    if (fp)
    {
        /* Correctly opened */
        stream->Type.file.fpFile = fp;
        /* codfh-match: 3.6 keeps the stream's position */
        stream->position = 0;
        result = stream;
    }
    else
    {
        RWERROR((E_RW_BADOPEN, cpFile));
    }

    RWRETURN(result);

}

// match: _StreamMemoryInitialize @ 0x002A6D60
static RwStream    *
StreamMemoryInitialize(RwStream * stream,
                       RwStreamAccessType accessType,
                       const void *pData)
{
    RwStream           *result = (RwStream *)NULL;
    const RwMemory     *mepMem = (const RwMemory *) pData;

    RWFUNCTION(RWSTRING("StreamMemoryInitialize"));

    switch (accessType)
    {
        case rwSTREAMREAD:
            {
                /* At start */
                stream->Type.memory.position = 0;
                /* Length */
                stream->Type.memory.nSize = mepMem->length;
                /* Data */
                stream->Type.memory.memBlock = mepMem->start;

                result = stream;
                break;
            }
        case rwSTREAMWRITE:
            {
                stream->Type.memory.position = 0;
                stream->Type.memory.nSize = 0;
                stream->Type.memory.memBlock = (unsigned char *)NULL;

                result = stream;
                break;
            }
        case rwSTREAMAPPEND:
            {
                stream->Type.memory.position = mepMem->length;
                stream->Type.memory.nSize = mepMem->length;
                /* Data */
                stream->Type.memory.memBlock = mepMem->start;

                result = stream;
                break;
            }
        default:
            {
                RWERROR((E_RW_INVSTREAMACCESSTYPE));
                break;
            }

    }

    /* codfh-match: 3.6 keeps the stream's position */
    stream->position = 0;

    RWRETURN(result);
}

static RwStream    *
StreamCustomInitialize(RwStream * stream,
                       const void *pData)
{
    RWFUNCTION(RWSTRING("StreamCustomInitialize"));

    /* copy the vTable across */
    memcpy(&stream->Type.custom, pData, sizeof(RwStreamCustom));
    /* codfh-match: 3.6 keeps the stream's position */
    stream->position = 0;

    RWRETURN(stream);
}

/**************************************************************************
 * \ref _rwStreamInitialize is used to open and initialize a binary stream
 * according to the specified stream type and access mode.
 *
 * \param Stream Structure to initialise and open.
 * \param Wether this structure was allocated by RenderWare.
 * Should always be FALSE in application code.
 * \param Type of stream to open. Stream types currently supported are:
 * \li rwSTREAMFILE | The stream is to a disk file that has been set
 * up by the user. The access mode must correspond to that when the file was
 * first opened. The type specific argument should be set to the file's pointer
 * (FILE *).
 * \li rwSTREAMFILENAME | The stream is a disk file specified by name.
 * The type specific argument should be set to a string containing the file's
 * name.
 * \li rwSTREAMMEMORY | The stream is to a chunk of memory. If access
 * type is rwSTREAMAPPEND then the chunk of memory must have been created
 * using \ref RwMalloc as RenderWare may subsequently try to use \ref RwRealloc
 * to gain more memory. The type specific argument should be a pointer to the
 * memory chunk (RwMemory *) giving the position and size of the chunk
 * to use.
 * \param Access mode of stream:
 * \li rwSTREAMREAD | Open a stream for reading only.
 * \li rwSTREAMWRITE | Open a stream for writing only. If the stream
 * is of type rwSTREAMFILE or rwSTREAMFILENAME the file size will be reduced
 * to zero when the stream is opened.
 * \li rwSTREAMAPPEND | Open a stream for appending to.
 * \paramStream type specific data.
 *
 * \return Returns pointer to the new stream if successful or NULL if there
 * is an error.
 *
 * \see RwStreamClose
 * \see RwStreamRead
 * \see RwStreamWrite
 * \see RwStreamSkip
 *
 */
// match: __rwStreamInitialize @ 0x002A6DE0
RwStream           *
_rwStreamInitialize(RwStream * stream, RwBool rwOwned, RwStreamType type,
                   RwStreamAccessType accessType, const void *pData)
{
    RwStream           *result = (RwStream *)NULL;
    RWFUNCTION(RWSTRING("_rwStreamInitialize"));
    RWASSERT(streamModule.numInstances);
    RWASSERT(pData);

    if (!stream)
    {
        RWRETURN(result);
    }

    stream->type = type;
    stream->accessType = accessType;

    stream->rwOwned = rwOwned;

    switch (type)
    {
        case rwSTREAMFILE:
            result = StreamFileInitialize(stream, pData);
            break;

        case rwSTREAMFILENAME:
            result = StreamFileNameInitialize(stream, accessType, pData);
            break;

        case rwSTREAMMEMORY:
            result = StreamMemoryInitialize(stream, accessType, pData);
            break;

        case rwSTREAMCUSTOM:
            result = StreamCustomInitialize(stream, pData);
            break;

        default:
            RWERROR((E_RW_INVSTREAMTYPE));
            break;
    }

    RWRETURN(result);
}


/**
 * \ingroup rwstream
 * \ref RwStreamRead is used to read a number of bytes from the specified
 * stream into the given data buffer. This function can only be used on a
 * stream that has been opened for reading using the rwSTREAMREAD flag.
 *
 * \param stream  Pointer to the stream to read data from.
 * \param buffer  Pointer to the buffer that will receive data from stream.
 * \param length  A RwUInt32 value equal to the number of bytes to read from the stream.
 *
 * \return Returns the number of bytes read, this may be less than the number
 * reqested if an error or the end of file is encountered
 *
 * \see RwStreamWrite
 * \see RwStreamReadInt32
 * \see RwStreamReadReal
 * \see RwStreamOpen
 *
 */
// match: _RwStreamRead @ 0x002A6EE0
RwUInt32
RwStreamRead(RwStream *stream, void *buffer, RwUInt32 length)
{
    RWAPIFUNCTION(RWSTRING("RwStreamRead"));
    RWASSERT(streamModule.numInstances);
    RWASSERT(stream);
    RWASSERT(stream->accessType == rwSTREAMREAD);
    RWASSERT(buffer);
    RWASSERT(length > 0);

    /* codfh-match: 3.6 keeps the stream's position */
    switch (stream->type)
    {
        case rwSTREAMFILENAME:
        case rwSTREAMFILE:
            {
                void               *fp = stream->Type.file.fpFile;
                RwUInt32            nBytesRead;

                /* Handle reading from the stream */
                nBytesRead = RwFread(buffer, 1, length, fp);
                stream->position += nBytesRead;
                if (nBytesRead != length)
                {
                    if (RwFeof(fp))
                    {
                        RWERROR((E_RW_ENDOFSTREAM));
                    }
                    else
                    {
                        RWERROR((E_RW_READ));
                    }
                }

                RWRETURN(nBytesRead);
            }

        case rwSTREAMMEMORY:
            {
                RwStreamMemory     *smpMem = &stream->Type.memory;

                if (length > smpMem->nSize - smpMem->position)
                {
                    length = smpMem->nSize - smpMem->position;
                    RWERROR((E_RW_ENDOFSTREAM));
                }

                memcpy(buffer, &smpMem->memBlock[smpMem->position],
                       length);

                /* Move the position foward */
                smpMem->position += length;
                stream->position += length;

                RWRETURN(length);
            }

        case rwSTREAMCUSTOM:
            {
                RwUInt32            nBytesRead;

                nBytesRead = stream->Type.custom.sfnread(stream->Type.custom.data,
                                                      buffer, length);
                stream->position += nBytesRead;

                RWRETURN(nBytesRead);
            }

        default:
            {
                RWERROR((E_RW_INVSTREAMTYPE));
                RWRETURN(0);
                break;
            }
    }
}

/**
 * \ingroup rwstream
 * \ref RwStreamWrite is used to write a number of bytes to the specified
 * stream from the given data buffer. This function can only be used on a
 * stream which has been opened for writing or appending using the
 * rwSTREAMWRITE or rwSTREAMAPPEND flags, respectively.
 *
 * \param stream  Pointer to the stream to write data to.
 * \param buffer  Pointer to the buffer that contains the data.
 * \param length  A RwUInt32 value equal to the number of bytes to write to stream.
 *
 * \return Returns pointer to the stream if successful or NULL if there is
 * error.
 *
 * \see RwStreamRead
 * \see RwStreamWriteInt32
 * \see RwStreamWriteReal
 * \see RwStreamOpen
 *
 */
// match: _RwStreamWrite @ 0x002A7050
RwStream *
RwStreamWrite(RwStream *stream, void const *buffer, RwUInt32 length)
{
    RWAPIFUNCTION(RWSTRING("RwStreamWrite"));
    RWASSERT(streamModule.numInstances);
    RWASSERT(stream);
    RWASSERT((stream->accessType == rwSTREAMWRITE) ||
             (stream->accessType == rwSTREAMAPPEND));
    RWASSERT(buffer);
    RWASSERT(length > 0);

    switch (stream->type)
    {
        case rwSTREAMFILENAME:
        case rwSTREAMFILE:
            {
                void        *fp = stream->Type.file.fpFile;
                RwUInt32    nBytesWritten;

                /* Handle reading from the stream */

                nBytesWritten = RwFwrite(buffer, 1, length, fp);

                if (nBytesWritten != length)
                {
                    RWERROR((E_RW_WRITE));
                    RWRETURN((RwStream *)NULL);
                }

                RWRETURN(stream);
            }
        case rwSTREAMMEMORY:
            {
                RwStreamMemory  *smpMem = &stream->Type.memory;

                if (!smpMem->memBlock)
                {
                    /* Allocate some memory */
                    smpMem->memBlock = (RwUInt8 *) RwMalloc(rwSTREAMMINALLOCSIZE, rwID_STREAMMODULE | rwMEMHINTDUR_EVENT);
                    if (!smpMem->memBlock)
                    {
                        RWERROR((E_RW_NOMEM, rwSTREAMMINALLOCSIZE));
                        RWRETURN((RwStream *)NULL);
                    }

                    /* Have the memory */
                    smpMem->nSize = rwSTREAMMINALLOCSIZE;
                }

                if (smpMem->nSize - smpMem->position < length)
                {
                    RwUInt32            nAllocSize;
                    void               *pData;

                    /* Have to realloc to get more memory */
                    if (length < rwSTREAMMINALLOCSIZE)
                    {
                        nAllocSize =
                            rwSTREAMMINALLOCSIZE + smpMem->nSize;
                    }
                    else
                    {
                        nAllocSize = length + smpMem->nSize;
                    }

                    pData = RwRealloc(smpMem->memBlock, nAllocSize, rwMEMHINTDUR_EVENT | rwMEMHINTFLAG_RESIZABLE | rwID_STREAMMODULE);
                    if (!pData)
                    {
                        RWERROR((E_RW_NOMEM, nAllocSize - smpMem->nSize));
                        RWRETURN((RwStream *)NULL);
                    }

                    smpMem->memBlock = (RwUInt8 *) pData;
                    smpMem->nSize = nAllocSize;
                }

                /* Do the copy */
                memcpy(&smpMem->memBlock[smpMem->position], buffer,
                       length);
                smpMem->position += length;

                RWRETURN(stream);
            }
        case rwSTREAMCUSTOM:
            {
                if (stream->Type.
                    custom.sfnwrite(stream->Type.custom.data, buffer, length))
                {
                    RWRETURN(stream);
                }
                RWRETURN((RwStream *)NULL);

                break;
            }
        default:
            {
                RWERROR((E_RW_INVSTREAMTYPE));
                RWRETURN((RwStream *)NULL);
                break;
            }
    }
}

/**
 * \ingroup rwstream
 * \ref RwStreamSkip is used to skip the specified number of bytes in
 * the given stream. This function can only be used on a stream opened for
 * reading and after calling \ref RwStreamSkip subsequent reads will begin
 * from the new position within the stream.
 *
 * \param stream  Pointer to the stream.
 * \param offset  A RwUInt32 value equal to the number of bytes to move.
 *
 * \return Returns pointer to the stream if successful or NULL if there
 * is an error.
 *
 * \see RwStreamOpen
 * \see RwStreamClose
 * \see RwStreamRead
 * \see RwStreamWrite
 * \see RwStreamFindChunk
 *
 */
// match: _RwStreamSkip @ 0x002A7210
RwStream *
RwStreamSkip(RwStream *stream, RwUInt32 offset)
{
    RWAPIFUNCTION(RWSTRING("RwStreamSkip"));
    RWASSERT(streamModule.numInstances);
    RWASSERT(stream);
    RWASSERT(stream->accessType == rwSTREAMREAD);

    if (offset == 0)
    {
        RWRETURN(stream);
    }

    /* codfh-match: 3.6 keeps the stream's position */
    switch (stream->type)
    {
        case rwSTREAMFILENAME:
        case rwSTREAMFILE:
            {
                void *fp = stream->Type.file.fpFile;
                /* Godfather debug _RwStreamSkip (0xBB6760) retains this
                 * file-branch result. VC7.1 also needs its single return
                 * for the original memory-branch LEA operand order. */
                RwStream *retVal;

                stream->position += offset;

                /* Handle reading from the stream */
                if (RwFseek(fp, offset, SEEK_CUR))
                {
                    if (RwFeof(fp))
                    {
                        RWERROR((E_RW_ENDOFSTREAM));
                    }
                    retVal = (RwStream *)NULL;
                }

                else
                {
                    retVal = stream;
                }
                RWRETURN(retVal);
            }
            break;

        case rwSTREAMMEMORY:
            {
                RwStreamMemory     *smpMem = &stream->Type.memory;

                if (smpMem->position + offset > smpMem->nSize)
                {
                    smpMem->position = smpMem->nSize;
                    stream->position = smpMem->nSize;
                    RWERROR((E_RW_ENDOFSTREAM));
                    RWRETURN((RwStream *)NULL);
                }

                smpMem->position += offset;
                stream->position += offset;

                RWRETURN(stream);
            }
            break;

        case rwSTREAMCUSTOM:
            {
                stream->position += offset;

                if (stream->Type.
                    custom.sfnskip(stream->Type.custom.data, offset))
                {
                    RWRETURN(stream);
                }

                RWRETURN((RwStream *)NULL);
                break;
            }

        default:
            {
                RWERROR((E_RW_INVSTREAMTYPE));
                RWRETURN((RwStream *)NULL);
                break;
            }
    }
}


/**
 * \ingroup rwstream
 * \ref RwStreamClose is used to close the specified binary stream. For
 * streams of type rwSTREAMMEMORY the stream specific argument should point
 * to a RwMemory structure that will receive the position and size of the
 * memory block used by the stream. For other stream types set the argument to
 * NULL.
 *
 * \param stream  Pointer to the currently opened stream.
 * \param pData  Pointer to the stream specific data
 *
 * \return Returns TRUE if successful or FALSE if there is an error
 *
 * \see RwStreamOpen
 * \see RwStreamRead
 * \see RwStreamWrite
 * \see RwStreamSkip
 *
 */
// match: _RwStreamClose @ 0x002A7340
RwBool
RwStreamClose(RwStream *stream, void *pData)
{
    RwBool  result;

    RWAPIFUNCTION(RWSTRING("RwStreamClose"));
    RWASSERT(streamModule.numInstances);
    RWASSERT(stream);

    switch (stream->type)
    {
        case rwSTREAMFILE:
            {
                result = TRUE;
                break;
            }
        case rwSTREAMFILENAME:
            {
                result = (RwFclose(stream->Type.file.fpFile) ==0) ? TRUE
                    : FALSE;
                break;
            }
        case rwSTREAMMEMORY:
            {
                RwMemory    *mepMem = (RwMemory *)pData;

                if (stream->accessType != rwSTREAMREAD)
                {
                    /* write back position if its requested */
                    if (pData)
                    {
                        mepMem->start = stream->Type.memory.memBlock;
                        mepMem->length = stream->Type.memory.position;
                    }
                }

                result = TRUE;
                break;
            }
        case rwSTREAMCUSTOM:
            {
                if (stream->Type.custom.sfnclose)
                {
                    stream->Type.custom.sfnclose(stream->Type.custom.data);
                }
                result = TRUE;
                break;
            }
        default:
            {
                RWERROR((E_RW_INVSTREAMTYPE));
                RWRETURN(FALSE);
            }
    }

    /* All done */
    if (stream->rwOwned)
    {
        RwFreeListFree(RWSTREAMGLOBAL(streamFreeList), stream);
    }

    RWRETURN(result);
}


/**
 * \ingroup rwstream
 * \ref RwStreamOpen is used to open and initialize a new binary stream
 * according to the specified stream type and access mode.
 *
 * \param type  Type of stream to open. Stream types currently supported are:
 *       \li \ref rwSTREAMFILE  The stream is to a disk file that has been
 *           set up by the user. The access mode must correspond to the one
 *           used when the the file was first opened. The type specific
 *           argument should be set to the file's pointer (FILE *).
 *       \li \ref rwSTREAMFILENAME  The stream is to a disk file specified by
 *           name. The type specific argument should be set to a string
 *           containing the file's name.
 *       \li \ref rwSTREAMMEMORY  The stream is to a chunk of memory. If the
 *           access type is \ref rwSTREAMAPPEND then the chunk of memory
 *           must have been created using \ref RwMalloc as RenderWare may
 *           subsequently try to use \ref RwRealloc to gain more memory.
 *           The type specific argument should be a pointer to the memory
 *           chunk ( \ref RwMemory *) giving the position and size of the
 *           chunk to use.
 * \param accessType  Access mode of stream:
 *       \li \ref rwSTREAMREAD  Opens a stream for reading only. This
 *           corresponds to using fopen with "rb" access mode.
 *       \li \ref rwSTREAMWRITE  Opens a stream for writing only. This
 *           corresponds to using fopen with "wb" access mode.If the
 *           stream is of type \ref rwSTREAMFILE or \ref rwSTREAMFILENAME
 *           the file size will be reduced to zero when the stream is opened.
 *       \li \ref rwSTREAMAPPEND  Opens a stream for appending to. This
 *           corresponds to using fopen with "ab" access mode.
 * \param pData  Stream type specific data.
 *
 * \return Returns a pointer to the new stream if successful or NULL if there
 * is an error.
 *
 * \see RwStreamClose
 * \see RwStreamRead
 * \see RwStreamWrite
 * \see RwStreamSkip
 *
 */
// match: _RwStreamOpen @ 0x002A7410
RwStream *
RwStreamOpen(RwStreamType type, RwStreamAccessType accessType,
             const void *pData)
{
    RwStream    *stream;

    RWAPIFUNCTION(RWSTRING("RwStreamOpen"));
    RWASSERT(streamModule.numInstances);
    RWASSERT(pData);

    stream = (RwStream *)RwFreeListAlloc(RWSTREAMGLOBAL(streamFreeList),
                                 rwMEMHINTDUR_EVENT | rwID_STREAMMODULE);
    RWASSERT(RWFREELISTALIGNED(stream, RWSTREAMGLOBAL(streamFreeList)));

    if (NULL == _rwStreamInitialize(stream, TRUE, type, accessType, pData))
    {
        RwFreeListFree(RWSTREAMGLOBAL(streamFreeList), stream);
        stream = (RwStream *)NULL;
    }

    RWRETURN(stream);
}
