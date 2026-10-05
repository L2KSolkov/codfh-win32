; codfh-match: XDK library data in .data between library objects (repacked)
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat
EXTERN ?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z:BYTE
EXTERN _XoUpdateLaunchNewImageInternal@16:BYTE


dseg1_10_0 SEGMENT BYTE PUBLIC ALIAS('.CRT$XCU') 'DATA'
; // match: _unk_4271C4 @ 0x004271C4
PUBLIC _unk_4271C4
_unk_4271C4 LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
dseg1_10_0 ENDS




dseg5 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_4273F0 @ 0x004273F0
PUBLIC _unk_4273F0
_unk_4273F0 LABEL BYTE
        dd _XoUpdateLaunchNewImageInternal@16
dseg5 ENDS



dseg8 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_42D8B0 @ 0x0042D8B0
PUBLIC _unk_42D8B0
_unk_42D8B0 LABEL BYTE
        db 006h, 000h, 007h, 000h, 040h, 0B3h, 03Eh, 000h
dseg8 ENDS

dseg10 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_42D940 @ 0x0042D940
PUBLIC _unk_42D940
_unk_42D940 LABEL BYTE
        db 000h, 000h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 001h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 057h, 000h, 000h, 000h, 000h, 001h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 001h, 000h
dseg10 ENDS

dseg12 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_432B90 @ 0x00432B90
PUBLIC _unk_432B90
_unk_432B90 LABEL BYTE
        db 04Ch, 0A3h, 053h, 000h, 030h, 0A3h, 053h, 000h
dseg12 ENDS



dseg14 SEGMENT BYTE PUBLIC ALIAS('.data') 'DATA'
; // match: _unk_432F38 @ 0x00432F38
PUBLIC _unk_432F38
_unk_432F38 LABEL BYTE
        db 001h, 000h, 000h, 000h
dseg14 ENDS












        END
