/*
 * codfh-match: RenderWare 3.6's Xbox material pixel shader plugin
 * (world/pipe/p2/xbox/xbpixelshader.c); names from the Godfather PDB.
 */
#ifndef XBPIXELSHADER_H
#define XBPIXELSHADER_H

extern RwInt32 _RpXboxMaterialPixelShaderOffset;
extern DWORD RpXboxMaterialDummyPixelShader;

extern RwBool _rpXboxMaterialPixelShaderOpen(void);
extern void _rpXboxMaterialPixelShaderClose(void);
extern void RpXboxMaterialSetPixelShader(RpMaterial *material, DWORD pixelShader);

#endif /* XBPIXELSHADER_H */
