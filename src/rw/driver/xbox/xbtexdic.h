/*
 * codfh-match: RenderWare 3.6's Xbox driver native textures
 * (driver/xbox/xbtexdic.c).
 */
#ifndef XBTEXDIC_H
#define XBTEXDIC_H

extern RwBool _rwXbNativeTextureGetSize(void *sizeIn, void *textureIn, RwInt32 unused3);
extern RwBool _rwXbNativeTextureWrite(void *streamIn, void *textureIn, RwInt32 size);
extern RwBool _rwXbNativeTextureRead(void *streamIn, void *textureIn, RwInt32 unused3);

#endif /* XBTEXDIC_H */
