/*
 * Xbox File System Module
 *
 * Not in the 3.7.2 tree; its Windows version (win/rtfswin.c) with the Xbox
 * changes the Godfather debug build (rwsdk/tool/fsyst/xbox/rtfsxxbx.c) and
 * the image show: asynchronous reads and writes ask XGetDiskSectorSizeA for
 * the device's sector size instead of keeping one per file system, sync
 * closes the event handle, and init clears every file's event handle.
 */
#include <xtl.h>

#include <rwplcore.h>
#include "../rpplugin.h"
#include <rpdbgerr.h>

#include "rtfsxxbx.h"
#include "../rtfsmgr.h"

/* Critical section used for file handle delivery in multithreaded cases */
CRITICAL_SECTION section;

/* The device's root, for XGetDiskSectorSizeA */
static RwChar dev[5];

/****************************************************************************
 * This function must be implemented in every file system
 */
// match: _TkXboxFSGetFileObject @ 0x00258310
// sp-match: _TkXboxFSGetFileObject @ 0x00174180
RtFile *
TkXboxFSGetFileObject( RtFileSystem *fs, RwUInt32 index )
{
    RWFUNCTION(RWSTRING("TkXboxFSGetFileObject"));

    if (index < (RwUInt32)((RtFileSystem *)fs)->maxNbOpenFiles)
    {
        RWRETURN ((RtFile *)&((RtXboxFileSystem *)fs)->files[index]);
    }
    else
    {
        RWRETURN (NULL);
    }
}

/****************************************************************************
 * Perfom any operation needed on closing this file system
 */
// match: _TkXboxFSClose @ 0x00258330
// sp-match: _TkXboxFSClose @ 0x001741A0
static void
TkXboxFSClose( RtFileSystem *xboxFileSystem )
{
    RWFUNCTION(RWSTRING("TkXboxFSClose"));

    RwFree(((RtXboxFileSystem *)xboxFileSystem)->files);

    RWRETURNVOID();
}

/****************************************************************************
 * Here implement all rwfile functions...
 *
 * Open File
 */
// match: _TkXboxFSystemFOpen @ 0x002588F0
// sp-match: _TkXboxFSystemFOpen @ 0x00174760
RtFileSystemError
TkXboxFSystemFOpen ( RtFileSystem  *fs,
                     RtFile        *file,
                     const RwChar  *filename,
                     RwUInt32       flags)
{
    RwChar    lsDeviceFilename[XBOX_FS_MAX_PATH_LENGTH];
    RtXboxFile *xFile = ((RtXboxFile *)file);

    RwUInt32 access;
    RwUInt32 sharing;
    RwUInt32 creation;
    RwUInt32 attributes;

    RWFUNCTION(RWSTRING("TkXboxFSystemFOpen"));

    if (NULL == _rtFSBuildFileName( lsDeviceFilename,
                                    XBOX_FS_MAX_PATH_LENGTH,
                                    fs->deviceName,
                                    _rtGetFileNameFromDeviceName(filename),
                                    '\\'))
    {
        RWRETURN (RTFS_ERROR_FILENAMETOOLONG);
    }

    access = 0;
    sharing = 0;
    creation = 0;
    attributes = 0;

    if (flags & RTFILE_ACCESS_OPEN_ASYNC)
    {
        attributes = FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING;
        file->isAsync = TRUE;
        file->status   = RTFILE_STATUS_BUSY;
    }
    else
    {
        file->isAsync = FALSE;
    }

    if (flags & RTFILE_ACCESS_OPEN_WRITE)
    {
        access = GENERIC_WRITE;
        sharing = FILE_SHARE_WRITE;

        if (flags & RTFILE_ACCESS_OPEN_APPEND)
        {
            creation = OPEN_ALWAYS;
        }
        else
        {
            RWASSERT((flags & RTFILE_ACCESS_OPEN_CREATE));
            creation = CREATE_ALWAYS;
        }

        if (FALSE == file->isAsync)
        {
            attributes = FILE_ATTRIBUTE_NORMAL;
        }

    }
    else
    {
        creation = OPEN_EXISTING;
        attributes |= FILE_ATTRIBUTE_READONLY;
    }

    if (flags & RTFILE_ACCESS_OPEN_READ)
    {
        access |= GENERIC_READ;
        sharing |= FILE_SHARE_READ;
    }

    xFile->fp = CreateFile( lsDeviceFilename,
                            access,
                            sharing,
                            NULL,
                            creation,
                            attributes,
                            NULL);

    if (xFile->fp == INVALID_HANDLE_VALUE)
    {
        RWRETURN (RTFS_ERROR_FILENOTFOUND);
    }

    if (file->isAsync == FALSE)
    {
        file->status   = RTFILE_STATUS_READY;
    }

    file->error    = RTFILE_ERROR_NOERROR;

    file->position.noSupportValue.low  = 0;
    file->position.noSupportValue.high = 0;

    /* Get file size */
    file->length.noSupportValue.low =
                                  GetFileSize(xFile->fp,
                                  (DWORD *)&(file->length.noSupportValue.high));

    /* If we are appending seek to the end */
    if (flags & RTFILE_ACCESS_OPEN_APPEND)
    {
        TkXboxFSystemSetPosition(file, 0, RTFILE_POS_END);
    }

    RWRETURN (RTFS_ERROR_NOERROR);
}

/****************************************************************************
 * Close File
 */
// match: _TkXboxFSystemFClose @ 0x00258350
// sp-match: _TkXboxFSystemFClose @ 0x001741C0
void
TkXboxFSystemFClose ( RtFile *file )
{
    RtXboxFile *xFile = ((RtXboxFile *)file);

    RWFUNCTION(RWSTRING("TkXboxFSystemFClose"));

    file->status = RTFILE_STATUS_CLOSED;
    CloseHandle(xFile->fp);

    RWRETURNVOID();
}

/****************************************************************************
 * Read File
 */
// match: _TkXboxFSystemFRead @ 0x00258370
// sp-match: _TkXboxFSystemFRead @ 0x001741E0
RwUInt32
TkXboxFSystemFRead ( RtFile     *file,
                     void       *pBuffer,
                     RwUInt32    nBytes )
{
    RwUInt32     nbBytesRead = 0;
    RtXboxFile   *xFile  = (RtXboxFile *)file;
    RtFileSystemFileFunctionTable *fileFuncs = &file->fileSystem->fsFileFunc;

    HANDLE fp     = xFile->fp;

    RWFUNCTION(RWSTRING("TkXboxFSystemFRead"));

    if (file->isAsync)
    {
        file->outstandingFileOp = RTFS_FILEOP_READ;
    }

    /*
     * As sync is called to check the status of async operations
     * we must not read unless file status is READY
     */
    if (file->status != RTFILE_STATUS_READY)
    {
        RWASSERT (FALSE);
        RWRETURN (0);
    }

    /* Asynchronous read */
    if (file->isAsync)
    {
        RwBool   readResult        = FALSE;
        DWORD    nbBytesTransfered = 0;
        RwUInt32 len;
        RwUInt32 diskSectorSize;

        /* The sector size of the device's root */
        len = rwstrlen(file->fileSystem->deviceName);
        if (file->fileSystem->deviceName[len - 1] != '\\')
        {
            rwstrcpy(dev, file->fileSystem->deviceName);
            rwstrcat(dev, "\\");
            rwstrcat(dev, "");
        }
        else
        {
            rwstrcpy(dev, file->fileSystem->deviceName);
        }

        diskSectorSize = XGetDiskSectorSizeA(dev);

        if (diskSectorSize > 0)
        {
            /* Assert if read size is not a multiple of the sector size */
            RWASSERT(nBytes % diskSectorSize == 0);

            /*
             * Event handle for async readfile operation. Need this
             * later to find out when read has actually  finished.
             */
            xFile->eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);

            /* Overlap structure used for asynchronous read */
            xFile->overlap.Offset     = (DWORD)file->position.noSupportValue.low;
            xFile->overlap.OffsetHigh = (DWORD)file->position.noSupportValue.high;
            xFile->overlap.hEvent     = xFile->eventHandle;

            /* Attempt an asynchronous read using overlapped IO */
            readResult = ReadFile(fp, pBuffer, nBytes, (LPDWORD)&nbBytesTransfered,
                                  &xFile->overlap);
            LASTERROR  = GetLastError();

            /* If read finished before readfile function returned */
            if (readResult)
            {
                if (nbBytesTransfered != nBytes)
                {
                    RWASSERT(FALSE);
                    file->status = RTFILE_STATUS_ERROR;
                }

                /* Adjust file pointer to new position */
                fileFuncs->setPosition(file, nbBytesTransfered,
                                       RTFILE_POS_CURRENT);

                file->status = RTFILE_STATUS_READY;

                /* Trigger Callback */
                rtFSTriggerFileOutstandingOpCallback(file);
            }
            else if ((LASTERROR == ERROR_IO_PENDING) ||
                     (LASTERROR == ERROR_SUCCESS))
            {
                file->status = RTFILE_STATUS_BUSY;
            }
            else
            {
                RWASSERT(FALSE);
                file->status = RTFILE_STATUS_ERROR;
            }
        }
        else
        {
            RWASSERT(diskSectorSize > 0);
            LASTERROR = GetLastError();
        }
    }
    /* Synchronous read */
    else
    {
        file->status = RTFILE_STATUS_BUSY;
        if (ReadFile(fp, pBuffer, nBytes, (LPDWORD)&nbBytesRead, NULL))
        {
            RwInt32 low = file->position.noSupportValue.low;
            if (low + (RwInt32)nbBytesRead >= low)
            {
                file->position.noSupportValue.low += nbBytesRead;
            }
            else
            {
                RwInt32 nbToMaxInt = RwInt32MAXVAL - low;
                file->position.noSupportValue.low = nbBytesRead - nbToMaxInt;
                ++ file->position.noSupportValue.high;
            }

            file->status = RTFILE_STATUS_READY;
        }
        else
        {
            file->status = RTFILE_STATUS_ERROR;
        }

        LASTERROR = GetLastError();
    }

    RWRETURN (nbBytesRead);
}

/****************************************************************************
 * Write File
 */
// match: _TkXboxFSystemFWrite @ 0x00258560
// sp-match: _TkXboxFSystemFWrite @ 0x001743D0
RwUInt32
TkXboxFSystemFWrite ( RtFile       *file,
                      const void   *buffer,
                      RwUInt32      nBytes )
{
    RwUInt32     nbBytesWriten;
    RtXboxFile   *xFile  = (RtXboxFile *)file;
    RtFileSystemFileFunctionTable *fileFuncs = &file->fileSystem->fsFileFunc;

    HANDLE fp     = xFile->fp;

    RWFUNCTION(RWSTRING("TkXboxFSystemFWrite"));

    if (file->isAsync)
    {
        RwBool   writeResult       = FALSE;
        DWORD    nbBytesTransfered = 0;
        RwUInt32 len;
        RwUInt32 diskSectorSize;

        /* The sector size of the device's root */
        len = rwstrlen(file->fileSystem->deviceName);
        if (file->fileSystem->deviceName[len - 1] != '\\')
        {
            rwstrcpy(dev, file->fileSystem->deviceName);
            rwstrcat(dev, "\\");
            rwstrcat(dev, "");
        }
        else
        {
            rwstrcpy(dev, file->fileSystem->deviceName);
        }

        diskSectorSize = XGetDiskSectorSizeA(dev);

        if (diskSectorSize > 0)
        {
            /* Assert if write size is not a multiple of the sector size */
            RWASSERT(nBytes % diskSectorSize == 0);

            /*
             * Event handle for async write operation. Need this
             * later to find out when write has actually finished.
             */
            xFile->eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);

            /*
             * Overlap structure used for async write
             * This structure define the offset at which to start writing
             */
            xFile->overlap.Offset     = (DWORD)file->position.noSupportValue.low;
            xFile->overlap.OffsetHigh = (DWORD)file->position.noSupportValue.high;
            xFile->overlap.hEvent     = xFile->eventHandle;

            writeResult = WriteFile(fp, buffer, nBytes, &nbBytesTransfered,
                                    &xFile->overlap);

            LASTERROR   = GetLastError();

            /* If write finished before write file function returned */
            if (writeResult)
            {
                if (nbBytesTransfered != nBytes)
                {
                    RWASSERT(FALSE);
                    file->status = RTFILE_STATUS_ERROR;
                }

                /* Update file's information to the new position*/
                fileFuncs->setPosition(file, nbBytesTransfered,
                                       RTFILE_POS_CURRENT);

                file->status = RTFILE_STATUS_READY;
            }
            else if ((LASTERROR == ERROR_IO_PENDING) ||
                     (LASTERROR == ERROR_SUCCESS))
            {
                file->status  = RTFILE_STATUS_BUSY;
            }
            else
            {
                RWASSERT(FALSE);
                file->status  = RTFILE_STATUS_ERROR;
            }
        }
        else
        {
            RWASSERT(diskSectorSize > 0);
            LASTERROR = GetLastError();
        }
    }
    else
    {
        file->status = RTFILE_STATUS_BUSY;
        if (WriteFile(fp, buffer, nBytes, (LPDWORD)&nbBytesWriten, NULL))
        {
            file->status   = RTFILE_STATUS_READY;
            file->position.noSupportValue.low += nbBytesWriten;
        }
        else
        {
            LASTERROR = GetLastError();
            file->status = RTFILE_STATUS_ERROR;
        }
    }

    RWRETURN (nbBytesWriten);
}

/****************************************************************************
 * Set Position File
 */
// match: _TkXboxFSystemSetPosition @ 0x00258710
// sp-match: _TkXboxFSystemSetPosition @ 0x00174580
RtInt64
TkXboxFSystemSetPosition ( RtFile           *file,
                           RwInt32           offset,
                           RtFileSeekMethod  fPosition)
{
    DWORD     moveMethod;
    LONG      moveDistanceLow   = (RwInt32)offset;
    LONG      moveDistanceHigh  = 0;

    RtXboxFile    *xFile = (RtXboxFile *)file;

    RWFUNCTION(RWSTRING("TkXboxFSystemSetPosition"));

    if (fPosition == RTFILE_POS_BEGIN)
    {
        moveMethod = FILE_BEGIN;
    }
    else if (fPosition == RTFILE_POS_CURRENT)
    {
        moveMethod = FILE_CURRENT;
    }
    else
    {
        moveMethod = FILE_END;
    }

    moveDistanceLow = SetFilePointer(xFile->fp, moveDistanceLow, NULL,
                                     moveMethod);

    file->position.noSupportValue.low  = moveDistanceLow;
    file->position.noSupportValue.high = moveDistanceHigh;

    RWRETURN (file->position);
}

/****************************************************************************
 * Sync
 */
// match: _TkXboxFSystemFSync @ 0x00258750
// sp-match: _TkXboxFSystemFSync @ 0x001745C0
RtFileStatus
TkXboxFSystemFSync ( RtFile *file, RwBool block )
{
    RtXboxFile    *xFile = (RtXboxFile *)file;
    RtFileSystemFileFunctionTable *fileFuncs = &file->fileSystem->fsFileFunc;

    RWFUNCTION(RWSTRING("TkXboxFSystemFSync"));

    /* If this is an asynchronous file */
    if (file->isAsync)
    {
        /* If there is an IO operation pending */
        if (file->status == RTFILE_STATUS_BUSY)
        {
            DWORD nbBytesTransfered  = 0;
            RtFileStatus statusUpdate = RTFILE_STATUS_READY;

            /* default size callback parameter to file length */
            file->outstandingSize = TkFSManagerGetValue(file->length);

            if(file->outstandingFileOp == RTFS_FILEOP_READ)
            {
                if (!GetOverlappedResult(xFile->fp, &xFile->overlap,
                                         &nbBytesTransfered, block))
                {
                    LASTERROR = GetLastError();

                    if ((LASTERROR == ERROR_IO_PENDING) ||
                        (LASTERROR == ERROR_SUCCESS) ||
                        (LASTERROR == ERROR_IO_INCOMPLETE))
                    {
                        /* operation not complete */
                        RWRETURN (file->status);
                    }

                    statusUpdate = RTFILE_STATUS_ERROR;
                    file->outstandingSize = 0;
                }
                else
                {
                    /* Update file's information, everything is ok */
                    fileFuncs->setPosition(file, nbBytesTransfered,
                                           RTFILE_POS_CURRENT);

                    /* for a read, size callback paramter == bytes read */
                    if(file->outstandingFileOp == RTFS_FILEOP_READ)
                    {
                        file->outstandingSize = nbBytesTransfered;
                    }
                }
            }

            file->status = statusUpdate;

            /* Now trigger the callback */
            rtFSTriggerFileOutstandingOpCallback(file);

            /* The operation is over: release its event */
            if (xFile->eventHandle != NULL)
            {
                if (!CloseHandle(xFile->eventHandle))
                {
                    LASTERROR = GetLastError();
                }
                else
                {
                    xFile->eventHandle = NULL;
                }
            }
        }
    }
    RWRETURN (file->status);
}

/****************************************************************************
 * Abort
 */
// match: _TkXboxFSystemAbort @ 0x00258860
// sp-match: _TkXboxFSystemAbort @ 0x001746D0
RwBool
TkXboxFSystemAbort ( RtFile *file )
{
    RWFUNCTION(RWSTRING("TkXboxFSystemAbort"));
    file->status = RTFILE_STATUS_CLOSED;
    RWRETURN (TRUE);
}

/****************************************************************************
 * This function must be implemented in every file system
 * It returns the status of this file
 */
// match: _TkXboxFSFileGetStatus @ 0x00258870
// sp-match: _TkXboxFSFileGetStatus @ 0x001746E0
static RtFileStatus
TkXboxFSFileGetStatus( RtFile *file )
{
    RWFUNCTION(RWSTRING("TkXboxFSFileGetStatus"));

    if (file->status != RTFILE_STATUS_CLOSED)
    {
        TkXboxFSystemFSync(file, FALSE);
    }

    RWRETURN (file->status);
}

/****************************************************************************
 * File Exists
 */
// match: _TkXboxFSystemFileExists @ 0x00258890
// sp-match: _TkXboxFSystemFileExists @ 0x00174700
static RwBool
TkXboxFSystemFileExists( RtFileSystem *fs,
                         const RwChar *fileName )
{
    RwChar      lsDeviceFilename[XBOX_FS_MAX_PATH_LENGTH];

    RWFUNCTION(RWSTRING("TkXboxFSystemFileExists"));

    if (NULL == _rtFSBuildFileName( lsDeviceFilename,
                                    XBOX_FS_MAX_PATH_LENGTH,
                                    ((RtFileSystem *)fs)->deviceName,
                                    _rtGetFileNameFromDeviceName(fileName),
                                    '\\'))
    {
        RWRETURN (FALSE);
    }

    RWRETURN ( GetFileAttributes(lsDeviceFilename) != 0xffffffff );
}

/****************************************************************************
 * Initialise File System
 */

/**
 * \ingroup rtfsxbox
 * \ref RtXboxFSystemInit is called to initialise the Xbox file system.
 *
 * \param maxNbOpenFiles    Maximum number of concurrently opened file this
 *                          file system can handle.
 * \param deviceName        Name of the device this file system represents.
 * \param fileSystemName    This is the unique name for this file system.
 *
 * \return                  A pointer to the newly created Xbox file system,
 *                          or NULL if initialization failed.
 */
// match: _RtXboxFSystemInit @ 0x00258A30
// sp-match: _RtXboxFSystemInit @ 0x001748A0
RtFileSystem *
RtXboxFSystemInit( RwInt32 maxNbOpenFiles,
                   RwChar *deviceName,
                   RwChar *fileSystemName )
{
    RwInt32          i;
    RtXboxFile       *files;
    RtXboxFileSystem *xboxFileSystem;

    RWAPIFUNCTION(RWSTRING("RtXboxFSystemInit"));
    RWASSERT (deviceName != NULL);

    /* First check that this file system hasn't already been registered */
    if (RtFSManagerGetFileSystemFromName(fileSystemName) != NULL)
    {
        RWRETURN(NULL);
    }

    xboxFileSystem = (RtXboxFileSystem *)RwMalloc(sizeof (RtXboxFileSystem),
                            rwID_FILESYSTEMPLUGIN | rwMEMHINTDUR_GLOBAL);

    /* Initialise the get object function for this file system */
    xboxFileSystem->xfs.fsGetObject    = TkXboxFSGetFileObject;
    xboxFileSystem->xfs.fsClose        = TkXboxFSClose;

    xboxFileSystem->xfs.fsFileFunc.open             = TkXboxFSystemFOpen;
    xboxFileSystem->xfs.fsFileFunc.close            = TkXboxFSystemFClose;
    xboxFileSystem->xfs.fsFileFunc.read             = TkXboxFSystemFRead;
    xboxFileSystem->xfs.fsFileFunc.write            = TkXboxFSystemFWrite;
    xboxFileSystem->xfs.fsFileFunc.setPosition      = TkXboxFSystemSetPosition;
    xboxFileSystem->xfs.fsFileFunc.sync             = TkXboxFSystemFSync;
    xboxFileSystem->xfs.fsFileFunc.abort            = TkXboxFSystemAbort;
    xboxFileSystem->xfs.fsFileFunc.isEOF            = _rtFSIsEOF;
    xboxFileSystem->xfs.fsFileFunc.getStatus        = TkXboxFSFileGetStatus;
    xboxFileSystem->xfs.fsFileFunc.fExists          = TkXboxFSystemFileExists;

    /* Now allocate memory for maximum number of open files */
    xboxFileSystem->files = (RtXboxFile *)RwCalloc(maxNbOpenFiles,
                            sizeof (RtXboxFile),
                            rwID_FILESYSTEMPLUGIN | rwMEMHINTDUR_GLOBAL);

    files = xboxFileSystem->files;

    for (i = 0; i < maxNbOpenFiles; ++i)
    {
        files[i].file.fileSystem = &xboxFileSystem->xfs;
        files[i].eventHandle     = NULL;
    }

    /* Init will also automatically try to register this file system */
    if (_rtFSInit(&xboxFileSystem->xfs, maxNbOpenFiles,
                  fileSystemName, deviceName) != RTFS_ERROR_NOERROR)
    {
        RwFree(xboxFileSystem->files);
        RwFree(xboxFileSystem);
        RWRETURN (NULL);
    }

    RWRETURN (&xboxFileSystem->xfs);
}
