; codfh-match: the Xbox kernel import thunk table (imagebld's, from xboxkrnl.lib's imports) and its padding
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat

dseg0 SEGMENT BYTE PUBLIC READONLY ALIAS('.rdata') 'DATA'
; // match: _unk_3CD300 @ 0x003CD300
PUBLIC _unk_3CD300
_unk_3CD300 LABEL BYTE
        db 026h, 001h, 000h, 080h, 015h, 001h, 000h, 080h, 023h, 001h, 000h, 080h, 0FAh, 000h, 000h, 080h
        db 08Fh, 000h, 000h, 080h, 0F6h, 000h, 000h, 080h, 003h, 001h, 000h, 080h, 0E7h, 000h, 000h, 080h
        db 0E0h, 000h, 000h, 080h, 02Eh, 001h, 000h, 080h, 0EEh, 000h, 000h, 080h, 002h, 001h, 000h, 080h
        db 0FFh, 000h, 000h, 080h, 0BDh, 000h, 000h, 080h, 010h, 000h, 000h, 080h, 021h, 001h, 000h, 080h
        db 0E1h, 000h, 000h, 080h, 0C1h, 000h, 000h, 080h, 0DEh, 000h, 000h, 080h, 0C0h, 000h, 000h, 080h
        db 0DDh, 000h, 000h, 080h, 0EAh, 000h, 000h, 080h, 0EBh, 000h, 000h, 080h, 063h, 000h, 000h, 080h
        db 031h, 001h, 000h, 080h, 080h, 000h, 000h, 080h, 09Ch, 000h, 000h, 080h, 030h, 001h, 000h, 080h
        db 0B2h, 000h, 000h, 080h, 0A5h, 000h, 000h, 080h, 0A4h, 000h, 000h, 080h, 0ABh, 000h, 000h, 080h
        db 02Dh, 001h, 000h, 080h, 031h, 000h, 000h, 080h, 0BBh, 000h, 000h, 080h, 0C5h, 000h, 000h, 080h
        db 0A1h, 000h, 000h, 080h, 081h, 000h, 000h, 080h, 095h, 000h, 000h, 080h, 061h, 000h, 000h, 080h
        db 071h, 000h, 000h, 080h, 06Bh, 000h, 000h, 080h, 0E9h, 000h, 000h, 080h, 0DBh, 000h, 000h, 080h
        db 0ECh, 000h, 000h, 080h, 0E2h, 000h, 000h, 080h, 0D3h, 000h, 000h, 080h, 0DAh, 000h, 000h, 080h
        db 0C6h, 000h, 000h, 080h, 0C8h, 000h, 000h, 080h, 0C4h, 000h, 000h, 080h, 0BEh, 000h, 000h, 080h
        db 0ACh, 000h, 000h, 080h, 0CAh, 000h, 000h, 080h, 0A7h, 000h, 000h, 080h, 018h, 000h, 000h, 080h
        db 028h, 000h, 000h, 080h, 043h, 000h, 000h, 080h, 0D7h, 000h, 000h, 080h, 0CBh, 000h, 000h, 080h
        db 045h, 000h, 000h, 080h, 050h, 001h, 000h, 080h, 04Fh, 001h, 000h, 080h, 051h, 001h, 000h, 080h
        db 043h, 001h, 000h, 080h, 045h, 001h, 000h, 080h, 062h, 001h, 000h, 080h, 046h, 001h, 000h, 080h
        db 00Fh, 000h, 000h, 080h, 011h, 000h, 000h, 080h, 091h, 000h, 000h, 080h, 09Fh, 000h, 000h, 080h
        db 042h, 001h, 000h, 080h, 02Ch, 000h, 000h, 080h, 0A0h, 000h, 000h, 080h, 02Fh, 000h, 000h, 080h
        db 062h, 000h, 000h, 080h, 06Dh, 000h, 000h, 080h, 097h, 000h, 000h, 080h, 064h, 001h, 000h, 080h
        db 0CFh, 000h, 000h, 080h, 0B6h, 000h, 000h, 080h, 0B3h, 000h, 000h, 080h, 044h, 001h, 000h, 080h
        db 054h, 001h, 000h, 080h, 0ADh, 000h, 000h, 080h, 0AFh, 000h, 000h, 080h, 077h, 000h, 000h, 080h
        db 0B0h, 000h, 000h, 080h, 068h, 001h, 000h, 080h, 0A6h, 000h, 000h, 080h, 0B4h, 000h, 000h, 080h
        db 017h, 001h, 000h, 080h, 047h, 001h, 000h, 080h, 048h, 001h, 000h, 080h, 0C7h, 000h, 000h, 080h
        db 0B8h, 000h, 000h, 080h, 00Dh, 001h, 000h, 080h, 0D9h, 000h, 000h, 080h, 065h, 001h, 000h, 080h
        db 0D2h, 000h, 000h, 080h, 001h, 000h, 000h, 080h, 002h, 000h, 000h, 080h, 003h, 000h, 000h, 080h
        db 004h, 000h, 000h, 080h, 02Eh, 000h, 000h, 080h, 064h, 000h, 000h, 080h, 008h, 000h, 000h, 080h
        db 0A8h, 000h, 000h, 080h, 08Eh, 000h, 000h, 080h, 08Bh, 000h, 000h, 080h, 017h, 000h, 000h, 080h
        db 089h, 000h, 000h, 080h, 099h, 000h, 000h, 080h, 0FCh, 000h, 000h, 080h, 0FDh, 000h, 000h, 080h
        db 09Eh, 000h, 000h, 080h, 05Dh, 001h, 000h, 080h, 05Bh, 001h, 000h, 080h, 05Ah, 001h, 000h, 080h
        db 053h, 001h, 000h, 080h, 052h, 001h, 000h, 080h, 059h, 001h, 000h, 080h, 058h, 001h, 000h, 080h
        db 0C3h, 000h, 000h, 080h, 063h, 001h, 000h, 080h, 061h, 001h, 000h, 080h, 056h, 000h, 000h, 080h
        db 03Eh, 000h, 000h, 080h, 0F7h, 000h, 000h, 080h, 096h, 000h, 000h, 080h, 07Eh, 000h, 000h, 080h
        db 07Fh, 000h, 000h, 080h, 02Ah, 000h, 000h, 080h, 029h, 000h, 000h, 080h, 0B5h, 000h, 000h, 080h
        db 0E4h, 000h, 000h, 080h, 0AAh, 000h, 000h, 080h, 0A9h, 000h, 000h, 080h, 038h, 001h, 000h, 080h
        db 05Fh, 000h, 000h, 080h, 004h, 001h, 000h, 080h, 034h, 001h, 000h, 080h, 057h, 000h, 000h, 080h
        db 055h, 000h, 000h, 080h, 054h, 000h, 000h, 080h, 041h, 000h, 000h, 080h, 04Ah, 000h, 000h, 080h
        db 053h, 000h, 000h, 080h, 051h, 000h, 000h, 080h, 067h, 001h, 000h, 080h, 066h, 001h, 000h, 080h
        db 000h, 000h, 000h, 000h
dseg0 ENDS

dseg0_s1 SEGMENT BYTE PUBLIC READONLY ALIAS('.rdata') 'DATA'
; (0x3CD564-0x3CD580: zeros after the table's terminator; the M7 link's are the import
; address table's own, src/xbe/dataalign.asm)
; // match: _unk_3CD564 @ 0x003CD564
PUBLIC _unk_3CD564
_unk_3CD564 LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
dseg0_s1 ENDS

dseg0_s2 SEGMENT BYTE PUBLIC READONLY ALIAS('.rdata') 'DATA'
; (0x3CD580-0x3CD59C: the link's debug directory, /DEBUG's, pointing at the CodeView
; record at 0x41AC40; the M7 link makes its own)
; // match: _unk_3CD580 @ 0x003CD580
PUBLIC _unk_3CD580
_unk_3CD580 LABEL BYTE
        db 000h, 000h, 000h, 000h, 081h, 0A8h, 081h, 041h, 000h, 000h, 000h, 000h, 002h, 000h, 000h, 000h
        db 05Bh, 000h, 000h, 000h, 0C0h, 093h, 040h, 000h, 0C0h, 093h, 040h, 000h
dseg0_s2 ENDS

dseg0_s3 SEGMENT BYTE PUBLIC READONLY ALIAS('.rdata') 'DATA'
; (0x3CD59C-0x3CD5A0: 4 bytes no code or data refers to, before unit_012000's .rdata;
; their object is not known yet)
; // match: _unk_3CD59C @ 0x003CD59C
PUBLIC _unk_3CD59C
_unk_3CD59C LABEL BYTE
        db 055h, 055h, 085h, 041h
dseg0_s3 ENDS

        END
