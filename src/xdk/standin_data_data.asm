; codfh-match: XDK library data in .data (repacked)
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat
EXTERN ??_C@_04CCAEFLLI@HOST?$AA@:BYTE
EXTERN ?sub_100200@type_10F710@@QAEXH@Z:BYTE
EXTERN __fFATN2:BYTE
EXTERN __nan2:BYTE
EXTERN __nosnan2:BYTE
EXTERN __rtindfpop:BYTE
EXTERN __rtzeropop:BYTE
EXTERN __tosnan2:BYTE
EXTERN _sub_2897B8:BYTE
EXTERN _sub_28BA68:BYTE
EXTERN _sub_28BB68:BYTE
EXTERN _sub_28BC98:BYTE
EXTERN _sub_28BDC8:BYTE
EXTERN _sub_2CEF8E:BYTE
EXTERN _unk_3F6060:BYTE
EXTERN _unk_3F6C60:BYTE


dseg9 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_436026 @ 0x00436026
PUBLIC _unk_436026
_unk_436026 LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
dseg9 ENDS





dseg14 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_437934 @ 0x00437934
PUBLIC _unk_437934
_unk_437934 LABEL BYTE
        db 02Fh, 029h, 03Dh, 000h
dseg14 ENDS




        END
