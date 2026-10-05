/****************************************************************************
 *
 * fsystplatform.h
 *
 * Purpose: Xbox specific include for fsyst.
 *
 * Not in the 3.7.2 tree (only its Windows version, win/fsystplatform.h);
 * written from the image: the manager's file list is guarded by a critical
 * section (RtlEnterCriticalSection/RtlLeaveCriticalSection around the
 * outstanding operations, as on Windows).
 *
 ****************************************************************************/
#ifndef FSYSTPLATFORM_H
#define FSYSTPLATFORM_H

/* RWPUBLIC */
#include <xtl.h>

extern CRITICAL_SECTION section;

#define RTFS_INITIALIZE_INTERRUPT_HANDLING InitializeCriticalSection(&section)
#define RTFS_DISABLE_INTERRUPT EnterCriticalSection(&section)
#define RTFS_ENABLE_INTERRUPT  LeaveCriticalSection(&section)
#define RTFS_SHUTDOWN_INTERRUPT_HANDLING DeleteCriticalSection(&section)

/* RWPUBLICEND */

#endif /* FSYSTPLATFORM_H */
