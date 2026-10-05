/*
 * Win32 port bridge (docs/WIN32_PORT.md W1): stands in for the XDK's xfont.h, the Xbox's system
 * font. The game opens the default font (unit_19CD50) and draws the Live UI's text with it
 * (type_3E0404 in game/xboxlive.h, unit_19BF20); port/xfont draws it with a bitmap font.
 */
#ifndef PORT_XFONT_H
#define PORT_XFONT_H

#include <xtl.h>
#include <d3d8.h>

typedef struct XFONT XFONT;

#ifdef __cplusplus
extern "C" {
#endif

HRESULT __stdcall XFONT_OpenDefaultFont(XFONT **ppFont);
void __stdcall XFONT_Release(XFONT *pFont);
unsigned __stdcall XFONT_GetTextHeight(XFONT *pFont);
HRESULT __stdcall XFONT_SetTextHeight(XFONT *pFont, unsigned uHeight);
void __stdcall XFONT_SetTextColor(XFONT *pFont, D3DCOLOR color);
HRESULT __stdcall XFONT_GetTextExtent(XFONT *pFont, LPCWSTR wstr, unsigned cch, unsigned *puWidth);
HRESULT __stdcall XFONT_TextOut(XFONT *pFont, IDirect3DSurface8 *pSurface, LPCWSTR wstr,
                                unsigned cch, long x, long y);

#ifdef __cplusplus
}

struct XFONT
{
    void Release() { XFONT_Release(this); }
    unsigned GetTextHeight() { return XFONT_GetTextHeight(this); }
    HRESULT SetTextHeight(unsigned uHeight) { return XFONT_SetTextHeight(this, uHeight); }
    void SetTextColor(D3DCOLOR color) { XFONT_SetTextColor(this, color); }
    HRESULT GetTextExtent(LPCWSTR wstr, unsigned cch, unsigned *puWidth)
    {
        return XFONT_GetTextExtent(this, wstr, cch, puWidth);
    }
    HRESULT TextOut(IDirect3DSurface8 *pSurface, LPCWSTR wstr, unsigned cch, long x, long y)
    {
        return XFONT_TextOut(this, pSurface, wstr, cch, x, y);
    }
};
#endif

#endif
