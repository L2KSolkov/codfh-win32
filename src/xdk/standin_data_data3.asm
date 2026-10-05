; codfh-match: XDK library data in .data beside other objects (XGraphics, IPP, CRT)
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat

dseg0 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_42DC48 @ 0x0042DC48
PUBLIC _unk_42DC48
_unk_42DC48 LABEL BYTE
        db 0FFh, 07Fh, 03Fh, 01Fh, 00Fh, 007h, 003h, 001h, 000h, 080h, 0C0h, 0E0h, 0F0h, 0F8h, 0FCh, 0FEh
        db 0FFh, 000h, 000h, 000h
dseg0 ENDS



dseg1 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_435250 @ 0x00435250
PUBLIC _unk_435250
_unk_435250 LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
dseg1 ENDS


        END
