; codfh-match: Bink's copyright banner (the library's yuv32.obj)
; binkxbox.lib's yuv32.obj, a MASM unit, holds the banner in its 16-aligned BINK code
; segment, which the image keeps last in BINK, after the bit-plane code: the link pads up to
; it with int3 (0xCC), as within a code group (a BINK$z group of its own got zeros). Its MMX
; constants (the library's yuv32 .data, pmemw*) are transcribed in binkdata.asm.

        .686p
        option casemap:none

bcopy SEGMENT PARA PUBLIC USE32 ALIAS('BINK') 'CODE'
; // match: _aBinkCopyrightC @ 0x0034DFE0
PUBLIC _aBinkCopyrightC
_aBinkCopyrightC LABEL BYTE
        db 0Dh, 0Ah, 0Dh, 0Ah, 'Bink', 0Dh, 0Ah
        db 'Copyright (C) 1994-2002 RAD Game Tools, Inc.', 0Dh, 0Ah, 0Dh, 0Ah
        db 0, 0
bcopy ENDS

        END
