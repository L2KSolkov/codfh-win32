/*
 * RwFileFunctions and RwOsGetFileInterface, copied from RenderWare 3.7.2
 * RWSDK/src/plcore/osintf.h (the struct and the prototype). The interface is
 * RWSRCGLOBAL(fileFuncs), 0x5201A4, which sub_2AB6C0 returns
 * (config/aliases.txt); the resource manager's Load (0x130000) sizes a file
 * through it.
 */
#ifndef RW_OSINTF_H
#define RW_OSINTF_H

#include <stddef.h>

#include "rw/ostypes.h"

// The C library's fseek offset (a long), which rwfseek takes; the game's
// replacements (game/pak.h) declare it through this name.
typedef long RwFileSeekOffset;

typedef struct RwFileFunctions RwFileFunctions;
struct RwFileFunctions
{
    RwBool (*rwfexist)(const RwChar *name);
    void *(*rwfopen)(const RwChar *name, const RwChar *mode);
    RwInt32 (*rwfclose)(void *fptr);
    size_t (*rwfread)(void *addr, size_t size, size_t count, void *fptr);
    size_t (*rwfwrite)(const void *addr, size_t size, size_t count, void *fptr);
    RwChar *(*rwfgets)(RwChar *buffer, RwInt32 maxLen, void *fptr);
    RwInt32 (*rwfputs)(const RwChar *buffer, void *fptr);
    RwInt32 (*rwfeof)(void *fptr);
    RwInt32 (*rwfseek)(void *fptr, RwFileSeekOffset offset, RwInt32 origin);
    RwInt32 (*rwfflush)(void *fptr);
    RwInt32 (*rwftell)(void *fptr);
};

#ifdef    __cplusplus
extern "C"
{
#endif

extern RwFileFunctions *RwOsGetFileInterface(void);

#ifdef    __cplusplus
}
#endif

#endif
