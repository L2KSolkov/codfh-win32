/*
 * RpUserDataArray and the user-data queries the game calls, copied from
 * RenderWare 3.7.2 RWSDK/plugin/userdata/rpusrdat.h. The database names
 * three of them otherwise (config/aliases.txt): RpGeometryGetUserDataArrayCount
 * (0x2E4840) and RpGeometryGetUserDataArray (0x2E4870) as _RwFrame..., since
 * both read a geometry's plugin data at userDataGeometryOffset, and
 * RpUserDataArrayGetName, which /OPT:ICF folded into __rwSListGetBegin
 * (0x2ABA90: both return the first field). RpUserDataArrayGetInt is sub_2E48A0.
 */
#ifndef RW_RPUSRDAT_H
#define RW_RPUSRDAT_H

#include "rw/batypes.h"
#include "rw/rpatomic.h"

enum RpUserDataFormat
{
    rpNAUSERDATAFORMAT = 0,
    rpINTUSERDATA,
    rpREALUSERDATA,
    rpSTRINGUSERDATA,
    rpUSERDATAFORCEENUMSIZEINT = 0x7FFFFFFF
};
typedef enum RpUserDataFormat RpUserDataFormat;

typedef struct RpUserDataArray RpUserDataArray;
struct RpUserDataArray
{
    RwChar              *name;
    RpUserDataFormat    format;
    RwInt32             numElements;
    void                *data;
};

#ifdef __cplusplus
extern              "C"
{
#endif

extern RpUserDataArray *RpGeometryGetUserDataArray(const RpGeometry *geometry, RwInt32 data);
extern RwInt32          RpGeometryGetUserDataArrayCount(const RpGeometry *geometry);
extern RwChar          *RpUserDataArrayGetName(RpUserDataArray *userData);
extern RwInt32          RpUserDataArrayGetInt(RpUserDataArray *userData, RwInt32 index);
/* Folded by /OPT:ICF with RpUserDataArrayGetInt (config/aliases.txt). */
extern RwChar          *RpUserDataArrayGetString(RpUserDataArray *userData, RwInt32 index);

#ifdef __cplusplus
}
#endif

#endif
