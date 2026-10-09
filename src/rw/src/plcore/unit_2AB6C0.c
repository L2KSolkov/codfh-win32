/*
 * codfh-match: RenderWare 3.6's file function table, which 3.7.2 dropped
 * (RwGlobals.fileFuncs at 0x5201A4). Written from the image: the table's
 * getter, its default exists test and the call that fills it with the C
 * library's stdio functions (RwEngineInit makes it after _rwMemoryOpen).
 */

#include <stdio.h>

#include "batypes.h"
#include "balibtyp.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@(#)$Id: //RenderWare/RW36Active/rwsdk/src/plcore/bafsys.c#1 $";

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00416458

// match: _RwOsGetFileInterface @ 0x002AB6C0
// sp-match: _RwOsGetFileInterface @ 0x001C6AF0
RwFileFunctions *
RwOsGetFileInterface(void)
{
    return &RWSRCGLOBAL(fileFuncs);
}

// match: _sub_2AB6D0 @ 0x002AB6D0
// sp-match: _sub_2AB6D0 @ 0x001C6B00
RwBool
sub_2AB6D0(const RwChar *name)
{
    void       *fptr;
    RwBool      exists;

    fptr = RWSRCGLOBAL(fileFuncs).rwfopen(name, RWSTRING("rb"));
    exists = (fptr != NULL);
    if (fptr)
    {
        RWSRCGLOBAL(fileFuncs).rwfclose(fptr);
    }

    return exists;
}

// match: _sub_2AB700 @ 0x002AB700
// sp-match: _sub_2AB700 @ 0x001C6B30
RwBool
sub_2AB700(void)
{
    RWSRCGLOBAL(fileFuncs).rwfexist = sub_2AB6D0;
    RWSRCGLOBAL(fileFuncs).rwfopen = (rwFnFopen)fopen;
    RWSRCGLOBAL(fileFuncs).rwfclose = (rwFnFclose)fclose;
    RWSRCGLOBAL(fileFuncs).rwfread = (rwFnFread)fread;
    RWSRCGLOBAL(fileFuncs).rwfwrite = (rwFnFwrite)fwrite;
    RWSRCGLOBAL(fileFuncs).rwfgets = (rwFnFgets)fgets;
    RWSRCGLOBAL(fileFuncs).rwfputs = (rwFnFputs)fputs;
    RWSRCGLOBAL(fileFuncs).rwfeof = (rwFnFeof)(feof);
    RWSRCGLOBAL(fileFuncs).rwfseek = (rwFnFseek)fseek;
    RWSRCGLOBAL(fileFuncs).rwfflush = (rwFnFflush)fflush;
    RWSRCGLOBAL(fileFuncs).rwftell = (rwFnFtell)ftell;

    return TRUE;
}

/* The file functions' close: empty (RwEngineInit and RwEngineTerm call it;
 * /OPT:ICF folded it into another empty function, 0x22C6E0, the database's
 * nullsub_1). */
void
nullsub_1(void)
{
}
