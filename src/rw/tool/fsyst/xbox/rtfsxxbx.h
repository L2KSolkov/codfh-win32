/*
 * Xbox File System Module
 *
 * Copyright (c) Criterion Software Limited
 *
 * Not in the 3.7.2 tree (only its Windows version, win/rtfswin.h); the
 * layouts are the Godfather debug build's RtXboxFile (96 bytes) and
 * RtXboxFileSystem (92 bytes, no sector size), which the image's offsets
 * confirm.
 */

#ifndef RTFSXXBX_H
#define RTFSXXBX_H

/* RWPUBLIC */

/**
 * \defgroup rtfsxbox Xbox
 * \ingroup  rtfsyst
 *
 * The Xbox file system allows for synchronous and asynchronous file
 * operations to be performed.
 */

/* RWPUBLICEND */

#include "../rtfsyst.h"

/* RWPUBLIC */
#include <xtl.h>

#define XBOX_FS_MAX_PATH_LENGTH 256

typedef struct RtXboxFile RtXboxFile;
/**
 * \ingroup rtfsxbox
 * \struct RtXboxFile
 * File object used by the Xbox file system.
 */
struct RtXboxFile
{
    RtFile       file;          /**< Parent \ref RtFile object. */
    HANDLE       fp;            /**< Xbox file handle. */
    OVERLAPPED   overlap;       /**< Structure for dealing with asynchronous
                                     file loading. */
    HANDLE       eventHandle;   /**< Event handle for dealing with asynchronous
                                     file loading. */
};

typedef struct RtXboxFileSystem RtXboxFileSystem;
/**
 * \ingroup rtfsxbox
 * \struct RtXboxFileSystem
 * This represents the Xbox file system.
 */
struct RtXboxFileSystem
{
    RtFileSystem  xfs;          /**< Parent \ref RtFileSystem object. */
    RtXboxFile    *files;       /**< Xbox file system files. */
};

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* RWPUBLICEND */

RtFile            *
TkXboxFSGetFileObject( RtFileSystem *fs,
                       RwUInt32 index );

RtFileSystemError
TkXboxFSystemFOpen( RtFileSystem *fs,
                    RtFile *file,
                    const RwChar *filename,
                    RwUInt32 flags);

void
TkXboxFSystemFClose( RtFile *file);

RwUInt32
TkXboxFSystemFRead( RtFile *file,
                    void *pBuffer,
                    RwUInt32 nBytes );

RwUInt32
TkXboxFSystemFWrite( RtFile *file,
                     const void *buffer,
                     RwUInt32 nBytes );

RtInt64
TkXboxFSystemSetPosition( RtFile *file,
                          RwInt32 offset,
                          RtFileSeekMethod fPosition );

RtFileStatus
TkXboxFSystemFSync( RtFile *file, RwBool block );

RwBool
TkXboxFSystemAbort( RtFile *file );

/* RWPUBLIC */

RtFileSystem      *
RtXboxFSystemInit( RwInt32 maxNbOpenFiles, RwChar *deviceName, RwChar *fileSystemName );

#ifdef __cplusplus
}
#endif  /* cplusplus */

/* RWPUBLICEND */

#endif /* RTFSXXBX_H */
