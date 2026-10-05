/*
 * RwTexture and RwTexDictionaryFindNamedTexture, copied from RenderWare 3.7.2
 * RWSDK/src/batextur.h. The game's font (type_DA580::sub_DBA80) reads a
 * found texture's raster, its first field. The shell's loading screen
 * (type_4B8EF0::sub_E9CA0) walks a dictionary's textures.
 */
#ifndef RW_BATEXTUR_H
#define RW_BATEXTUR_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

#define rwTEXTUREBASENAMELENGTH     32

typedef struct RwRaster RwRaster;
typedef struct RwTexDictionary RwTexDictionary;

typedef struct RwTexture RwTexture;
struct RwTexture
{
    RwRaster           *raster; /** pointer to RwRaster with data */
    RwTexDictionary    *dict;   /* Dictionary this texture is in */
    RwLLLink            lInDictionary; /* List of textures in this dictionary */

    RwChar              name[rwTEXTUREBASENAMELENGTH];  /* Name of the texture */
    RwChar              mask[rwTEXTUREBASENAMELENGTH];  /* Name of the textures mask */

    /* 31 [xxxxxxxx xxxxxxxx vvvvuuuu ffffffff] 0 */
    RwUInt32            filterAddressing; /* Filtering & addressing mode flags */

    RwInt32             refCount; /* Reference count, surprisingly enough */
};

/* The filter mode and raster accessors' macro forms (the decal system,
 * sub_F00C0, sets its texture's filtering and reads its raster). */
#define rwTEXTUREFILTERMODEMASK 0x000000FF
#define RwTextureSetFilterModeMacro(_tex, _filtering)                   \
    (((_tex)->filterAddressing =                                        \
      ((_tex)->filterAddressing & ~rwTEXTUREFILTERMODEMASK) |           \
      (((RwUInt32)(_filtering)) & rwTEXTUREFILTERMODEMASK)),            \
     (_tex))
#define RwTextureSetFilterMode(_tex, _filtering)                        \
    RwTextureSetFilterModeMacro(_tex, _filtering)
#define RwTextureGetRasterMacro(_tex) ((_tex)->raster)
#define RwTextureGetRaster(_tex) RwTextureGetRasterMacro(_tex)

// A texture's raster: a game inline with no address and so no database
// name, named for what it reads. Evidence: the HUD's text
// (type_DC400::sub_E7600) keeps the texture and the raster in slots of their
// own among its inlines' (RenderWare's RwTextureGetRaster is a macro).
inline RwRaster *get_texture_raster(RwTexture *arg_0)
{
    return arg_0->raster;
}

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

/* The texture find callback (RWSDK batextur.h): the level sections'
 * loaders (unit_141BB0) swap in their own while a BSP is read. */
typedef RwTexture *(*RwTextureCallBackFind)(const RwChar *name);
extern RwBool RwTextureSetFindCallBack(RwTextureCallBackFind callBack);
extern RwTextureCallBackFind RwTextureGetFindCallBack(void);
extern RwTexture   *RwTexDictionaryFindNamedTexture(RwTexDictionary * dict,
                                                    const RwChar * name);
typedef RwTexture *(*RwTextureCallBack)(RwTexture *texture, void *pData);
extern const RwTexDictionary *RwTexDictionaryForAllTextures(const RwTexDictionary * dict,
                                                            RwTextureCallBack fpCallBack,
                                                            void *pData);
extern RwTexDictionary *RwTexDictionarySetCurrent(RwTexDictionary * dict);
typedef RwTexDictionary *(*RwTexDictionaryCallBack)(RwTexDictionary *dict, void *data);
extern RwBool RwTexDictionaryForAllTexDictionaries(RwTexDictionaryCallBack fpCallBack,
                                                   void *pData);

/* The texture read callback (RenderWare Studio's image loader registration
 * hooks the Xbox's DDS reader in front of it, 0x132650). */
typedef RwTexture *(*RwTextureCallBackRead)(const RwChar *name, const RwChar *maskName);
extern RwTextureCallBackRead RwTextureGetReadCallBack(void);
extern RwBool RwTextureSetReadCallBack(RwTextureCallBackRead fpCallBack);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif
