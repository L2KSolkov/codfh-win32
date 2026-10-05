; codfh-match: Bink's data: tables, the blit state and the embedded logo movie
; Transcribed from the image (tools/img2data.py), like Bink's assembly the owner
; allows as transcription ("asm the rest of bink", docs/questions.md): the
; tables its C and assembly units declare extern, its BINKDATA statics and the
; embedded movie, byte for byte.

        .686p
        option casemap:none


dseg2 SEGMENT BYTE PUBLIC USE32 ALIAS('.data') 'DATA'
; (0x43118C-0x4311A8 is rgb32mx2's and rgb32m's .data, each padded to 16)
; // match: _unk_4311A8 @ 0x004311A8
PUBLIC _unk_4311A8
_unk_4311A8 LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
PUBLIC _pmemw16
_pmemw16 LABEL BYTE
        db 010h, 000h, 010h, 000h, 010h, 000h, 010h, 000h
PUBLIC _pmemwYscale
_pmemwYscale LABEL BYTE
        db 085h, 04Ah, 085h, 04Ah, 085h, 04Ah, 085h, 04Ah
PUBLIC _pmemw7F00
_pmemw7F00 LABEL BYTE
        db 000h, 07Fh, 000h, 07Fh, 000h, 07Fh, 000h, 07Fh
PUBLIC _pmemwRGB
_pmemwRGB LABEL BYTE
        db 021h, 004h, 021h, 004h
PUBLIC _unk_4311D4
_unk_4311D4 LABEL BYTE
        db 021h, 004h, 021h, 004h
PUBLIC _pmemwYscalem
_pmemwYscalem LABEL BYTE
        db 085h, 04Ah, 085h, 04Ah
PUBLIC _unk_4311DC
_unk_4311DC LABEL BYTE
        db 085h, 04Ah, 085h, 04Ah
PUBLIC _pmemw7F00m
_pmemw7F00m LABEL BYTE
        db 000h, 07Fh, 000h, 07Fh
PUBLIC _unk_4311E4
_unk_4311E4 LABEL BYTE
        db 000h, 07Fh, 000h, 07Fh
PUBLIC _pmemb80
_pmemb80 LABEL BYTE
        db 080h, 080h, 080h, 080h, 080h, 080h, 080h, 080h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
; (0x4311F8-0x43129C is xonline's, reboot's and logon's .data: g_pszDNSName, the
; reboot paths and the logon retry counts)
dseg2 ENDS

        END
