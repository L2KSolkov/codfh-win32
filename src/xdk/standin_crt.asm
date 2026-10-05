; codfh-match: XDK C runtime (libcmt) pieces
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ??1type_info@@UAE@XZ:NEAR
EXTERN ??3@YAXPAXI@Z:NEAR
EXTERN ?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z:BYTE
EXTERN _AugmentSinCos:NEAR
EXTERN _SetUnhandledExceptionFilter@4:NEAR
EXTERN __87except:NEAR
EXTERN __FPmtinit:BYTE
EXTERN __FPmtterm:BYTE
EXTERN __SEH_epilog:NEAR
EXTERN __SEH_prolog:NEAR
EXTERN ___badioinfo:BYTE
EXTERN ___doserrno:NEAR
EXTERN ___fastflag:BYTE
EXTERN ___lookuptable:BYTE
EXTERN ___mb_cur_max:BYTE
EXTERN ___mbcodepage:BYTE
EXTERN ___mbctype_initialized:BYTE
EXTERN ___nullstring:BYTE
EXTERN ___piob:BYTE
EXTERN ___pioinfo:BYTE
EXTERN ___wnullstring:BYTE
EXTERN __amsg_exit:NEAR
EXTERN __aulldvrm:NEAR
EXTERN __cfltcvt_tab:BYTE
EXTERN __cintrindisp1:NEAR
EXTERN __convertTOStoQNaN:NEAR
EXTERN __ctrandisp1:NEAR
EXTERN __errno:NEAR
EXTERN __fast_exit:NEAR
EXTERN __fload:NEAR
EXTERN __fload_withFB:NEAR
EXTERN __freeptd:NEAR
EXTERN __getbuf:NEAR
EXTERN __indefinite:BYTE
EXTERN __iob:BYTE
EXTERN __ld12cvt:NEAR
EXTERN __load_CW:NEAR
EXTERN __lock:NEAR
EXTERN __lock_fhandle:NEAR
EXTERN __math_exit:NEAR
EXTERN __nhandle:BYTE
EXTERN __nstream:BYTE
EXTERN __pctype:BYTE
EXTERN __piby2:BYTE
EXTERN __powhlp:NEAR
EXTERN __read_lk:NEAR
EXTERN __rttosnpopde:NEAR
EXTERN __setmbcp:NEAR
EXTERN __startOneArgErrorHandling:NEAR
EXTERN __trandisp2:NEAR
EXTERN __unlock:NEAR
EXTERN __unlock_fhandle:NEAR
EXTERN _calloc:NEAR
EXTERN _fclose:NEAR
EXTERN _flsall:NEAR
EXTERN _free:NEAR
EXTERN _malloc:NEAR
EXTERN _mbtowc:NEAR
EXTERN _unk_41785C:BYTE
EXTERN _unk_417864:BYTE
EXTERN _unk_41786C:BYTE
EXTERN _unk_417870:BYTE
EXTERN _unk_417874:BYTE
EXTERN _unk_41787C:BYTE
EXTERN _unk_417884:BYTE
EXTERN _unk_418058:BYTE
EXTERN _unk_418078:BYTE
EXTERN _unk_435838:BYTE
EXTERN _unk_4358F0:BYTE
EXTERN _unk_435950:BYTE
EXTERN _unk_435B64:BYTE
EXTERN _unk_435B6C:BYTE
EXTERN _unk_435FEA:BYTE
EXTERN _unk_435FFE:BYTE
EXTERN _unk_43604A:BYTE
EXTERN _unk_43606A:BYTE
EXTERN _unk_43608A:BYTE
EXTERN _unk_4360D4:BYTE
EXTERN _unk_4360EC:BYTE
EXTERN _unk_5098C4:BYTE
EXTERN _unk_5098D4:BYTE
EXTERN _write_char_0:NEAR







seg12 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_2C88C4 @ 0x002C88C4
PUBLIC _sub_2C88C4
_sub_2C88C4:
        db 0BAh   ; mov edx, 0x43604a
        dd _unk_43604A
$L_2c88c9:
        jmp __ctrandisp1   ; 0x2CB1F1
        db 0BAh   ; mov edx, 0x43606a
        dd _unk_43606A
        db 0EBh, 0F4h   ; jmp 0x2c88c9
        db 0BAh   ; mov edx, 0x43608a
        dd _unk_43608A
        db 0EBh, 0EDh   ; jmp 0x2c88c9

; // match: _sub_2C88DC @ 0x002C88DC
PUBLIC _sub_2C88DC
_sub_2C88DC:
        db 0BAh   ; mov edx, 0x43604a
        dd _unk_43604A
$L_2c88e1:
        jmp __cintrindisp1   ; 0x2CB01E
        db 0BAh   ; mov edx, 0x43606a
        dd _unk_43606A
        db 0EBh, 0F4h   ; jmp 0x2c88e1
        db 0BAh   ; mov edx, 0x43608a
        dd _unk_43608A
        db 0EBh, 0EDh   ; jmp 0x2c88e1
seg12 ENDS



seg17 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: __fread_lk @ 0x002C90B9
PUBLIC __fread_lk
__fread_lk:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 00Ch   ; sub esp, 0xc
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 056h   ; push esi
        db 08Bh, 075h, 00Ch   ; mov esi, dword ptr [ebp + 0xc]
        db 00Fh, 0AFh, 075h, 010h   ; imul esi, dword ptr [ebp + 0x10]
        db 085h, 0F6h   ; test esi, esi
        db 057h   ; push edi
        db 08Bh, 0FEh   ; mov edi, esi
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 089h, 075h, 0F4h   ; mov dword ptr [ebp - 0xc], esi
        db 089h, 07Dh, 0FCh   ; mov dword ptr [ebp - 4], edi
        db 075h, 007h   ; jne 0x2c90e1
        db 033h, 0C0h   ; xor eax, eax
        db 0E9h, 0B7h, 000h, 000h, 000h   ; jmp 0x2c9198
$L_2c90e1:
        db 053h   ; push ebx
        db 08Bh, 05Dh, 014h   ; mov ebx, dword ptr [ebp + 0x14]
        db 066h, 0F7h, 043h, 00Ch, 00Ch, 001h   ; test word ptr [ebx + 0xc], 0x10c
        db 074h, 008h   ; je 0x2c90f5
        db 08Bh, 043h, 018h   ; mov eax, dword ptr [ebx + 0x18]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 0EBh, 007h   ; jmp 0x2c90fc
$L_2c90f5:
        db 0C7h, 045h, 0F8h, 000h, 010h, 000h, 000h   ; mov dword ptr [ebp - 8], 0x1000
$L_2c90fc:
        db 066h, 0F7h, 043h, 00Ch, 00Ch, 001h   ; test word ptr [ebx + 0xc], 0x10c
        db 074h, 035h   ; je 0x2c9139
        db 08Bh, 043h, 004h   ; mov eax, dword ptr [ebx + 4]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 02Eh   ; je 0x2c9139
        db 03Bh, 0F8h   ; cmp edi, eax
        db 073h, 002h   ; jae 0x2c9111
        db 08Bh, 0C7h   ; mov eax, edi
$L_2c9111:
        db 08Bh, 033h   ; mov esi, dword ptr [ebx]
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 029h, 045h, 0FCh   ; sub dword ptr [ebp - 4], eax
        db 08Bh, 0C8h   ; mov ecx, eax
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 0CAh   ; mov ecx, edx
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F3h, 0A4h   ; rep movsb byte ptr es:[edi], byte ptr [esi]
        db 029h, 043h, 004h   ; sub dword ptr [ebx + 4], eax
        db 001h, 003h   ; add dword ptr [ebx], eax
        db 001h, 045h, 008h   ; add dword ptr [ebp + 8], eax
        db 08Bh, 07Dh, 0FCh   ; mov edi, dword ptr [ebp - 4]
        db 08Bh, 075h, 0F4h   ; mov esi, dword ptr [ebp - 0xc]
        db 0EBh, 053h   ; jmp 0x2c918c
$L_2c9139:
        db 03Bh, 07Dh, 0F8h   ; cmp edi, dword ptr [ebp - 8]
        db 072h, 030h   ; jb 0x2c916e
        db 083h, 07Dh, 0F8h, 000h   ; cmp dword ptr [ebp - 8], 0
        db 08Bh, 0C7h   ; mov eax, edi
        db 074h, 009h   ; je 0x2c914f
        db 033h, 0D2h   ; xor edx, edx
        db 0F7h, 075h, 0F8h   ; div dword ptr [ebp - 8]
        db 08Bh, 0C7h   ; mov eax, edi
        db 02Bh, 0C2h   ; sub eax, edx
$L_2c914f:
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0FFh, 073h, 010h   ; push dword ptr [ebx + 0x10]
        call __read_1   ; 0x2CDD48
        db 083h, 0C4h, 00Ch   ; add esp, 0xc
        db 085h, 0C0h   ; test eax, eax
        db 074h, 03Ah   ; je 0x2c919c
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 074h, 044h   ; je 0x2c91ab
        db 02Bh, 0F8h   ; sub edi, eax
        db 001h, 045h, 008h   ; add dword ptr [ebp + 8], eax
        db 0EBh, 01Bh   ; jmp 0x2c9189
$L_2c916e:
        db 053h   ; push ebx
        call __filbuf   ; 0x2CDA90
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 059h   ; pop ecx
        db 074h, 026h   ; je 0x2c91a0
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 0FFh, 045h, 008h   ; inc dword ptr [ebp + 8]
        db 088h, 001h   ; mov byte ptr [ecx], al
        db 08Bh, 043h, 018h   ; mov eax, dword ptr [ebx + 0x18]
        db 04Fh   ; dec edi
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
$L_2c9189:
        db 089h, 07Dh, 0FCh   ; mov dword ptr [ebp - 4], edi
$L_2c918c:
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 085h, 068h, 0FFh, 0FFh, 0FFh   ; jne 0x2c90fc
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
$L_2c9197:
        db 05Bh   ; pop ebx
$L_2c9198:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C3h   ; ret 
$L_2c919c:
        db 083h, 04Bh, 00Ch, 010h   ; or dword ptr [ebx + 0xc], 0x10
$L_2c91a0:
        db 08Bh, 0C6h   ; mov eax, esi
        db 02Bh, 0C7h   ; sub eax, edi
        db 033h, 0D2h   ; xor edx, edx
        db 0F7h, 075h, 00Ch   ; div dword ptr [ebp + 0xc]
        db 0EBh, 0ECh   ; jmp 0x2c9197
$L_2c91ab:
        db 083h, 04Bh, 00Ch, 020h   ; or dword ptr [ebx + 0xc], 0x20
        db 0EBh, 0EFh   ; jmp 0x2c91a0
seg17 ENDS







seg25 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_2CC993 @ 0x002CC993
PUBLIC _sub_2CC993
_sub_2CC993:
$L_2cc993:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 056h   ; push esi
        db 08Bh, 0F0h   ; mov esi, eax
        db 0EBh, 014h   ; jmp 0x2cc9af
$L_2cc99b:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 0FFh, 04Dh, 00Ch   ; dec dword ptr [ebp + 0xc]
        call _write_char_0   ; 0x2CC96E
        db 083h, 03Eh, 0FFh   ; cmp dword ptr [esi], -1
        db 059h   ; pop ecx
        db 074h, 006h   ; je 0x2cc9b5
$L_2cc9af:
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 07Fh, 0E6h   ; jg 0x2cc99b
$L_2cc9b5:
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C3h   ; ret 

; // match: _sub_2CC9B8 @ 0x002CC9B8
PUBLIC _sub_2CC9B8
_sub_2CC9B8:
$L_2cc9b8:
        db 0F6h, 047h, 00Ch, 040h   ; test byte ptr [edi + 0xc], 0x40
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 0F0h   ; mov esi, eax
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 074h, 027h   ; je 0x2cc9eb
        db 083h, 07Fh, 008h, 000h   ; cmp dword ptr [edi + 8], 0
        db 075h, 021h   ; jne 0x2cc9eb
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 001h, 006h   ; add dword ptr [esi], eax
        db 0EBh, 020h   ; jmp 0x2cc9f2
$L_2cc9d2:
        db 0FFh, 04Ch, 024h, 00Ch   ; dec dword ptr [esp + 0xc]
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 003h   ; mov ax, word ptr [ebx]
        db 050h   ; push eax
        db 08Bh, 0C7h   ; mov eax, edi
        call _write_char_0   ; 0x2CC96E
        db 043h   ; inc ebx
        db 043h   ; inc ebx
        db 083h, 03Eh, 0FFh   ; cmp dword ptr [esi], -1
        db 059h   ; pop ecx
        db 074h, 007h   ; je 0x2cc9f2
$L_2cc9eb:
        db 083h, 07Ch, 024h, 00Ch, 000h   ; cmp dword ptr [esp + 0xc], 0
        db 07Fh, 0E0h   ; jg 0x2cc9d2
$L_2cc9f2:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C3h   ; ret 

seg25 ENDS



seg29 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: __filbuf @ 0x002CDA90
PUBLIC __filbuf
__filbuf:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 0A8h, 083h   ; test al, 0x83
        db 00Fh, 084h, 0CCh, 000h, 000h, 000h   ; je 0x2cdb6c
        db 0A8h, 040h   ; test al, 0x40
        db 00Fh, 085h, 0C4h, 000h, 000h, 000h   ; jne 0x2cdb6c
        db 0A8h, 002h   ; test al, 2
        db 074h, 00Bh   ; je 0x2cdab7
        db 083h, 0C8h, 020h   ; or eax, 0x20
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0E9h, 0B5h, 000h, 000h, 000h   ; jmp 0x2cdb6c
$L_2cdab7:
        db 083h, 0C8h, 001h   ; or eax, 1
        db 066h, 0A9h, 00Ch, 001h   ; test ax, 0x10c
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 075h, 009h   ; jne 0x2cdacc
        db 056h   ; push esi
        call __getbuf   ; 0x2CF4D9
        db 059h   ; pop ecx
        db 0EBh, 005h   ; jmp 0x2cdad1
$L_2cdacc:
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 089h, 006h   ; mov dword ptr [esi], eax
$L_2cdad1:
        db 0FFh, 076h, 018h   ; push dword ptr [esi + 0x18]
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        call __read_1   ; 0x2CDD48
        db 083h, 0C4h, 00Ch   ; add esp, 0xc
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 004h   ; mov dword ptr [esi + 4], eax
        db 074h, 072h   ; je 0x2cdb5b
        db 083h, 0F8h, 0FFh   ; cmp eax, -1
        db 074h, 06Dh   ; je 0x2cdb5b
        db 08Bh, 056h, 00Ch   ; mov edx, dword ptr [esi + 0xc]
        db 0F6h, 0C2h, 082h   ; test dl, 0x82
        db 075h, 03Ah   ; jne 0x2cdb30
        db 08Bh, 04Eh, 010h   ; mov ecx, dword ptr [esi + 0x10]
        db 083h, 0F9h, 0FFh   ; cmp ecx, -1
        db 057h   ; push edi
        db 074h, 017h   ; je 0x2cdb16
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0C1h, 0FFh, 005h   ; sar edi, 5
        db 08Bh, 03Ch, 0BDh   ; mov edi, dword ptr [edi*4 + 0x524360]
        dd ___pioinfo
        db 083h, 0E1h, 01Fh   ; and ecx, 0x1f
        db 08Dh, 00Ch, 089h   ; lea ecx, [ecx + ecx*4]
        db 08Dh, 03Ch, 0CFh   ; lea edi, [edi + ecx*8]
        db 0EBh, 005h   ; jmp 0x2cdb1b
$L_2cdb16:
        db 0BFh   ; mov edi, 0x4360ac
        dd ___badioinfo
$L_2cdb1b:
        db 08Ah, 04Fh, 004h   ; mov cl, byte ptr [edi + 4]
        db 080h, 0E1h, 082h   ; and cl, 0x82
        db 080h, 0F9h, 082h   ; cmp cl, 0x82
        db 05Fh   ; pop edi
        db 075h, 009h   ; jne 0x2cdb30
        db 081h, 0CAh, 000h, 020h, 000h, 000h   ; or edx, 0x2000
        db 089h, 056h, 00Ch   ; mov dword ptr [esi + 0xc], edx
$L_2cdb30:
        db 081h, 07Eh, 018h, 000h, 002h, 000h, 000h   ; cmp dword ptr [esi + 0x18], 0x200
        db 075h, 014h   ; jne 0x2cdb4d
        db 08Bh, 04Eh, 00Ch   ; mov ecx, dword ptr [esi + 0xc]
        db 0F6h, 0C1h, 008h   ; test cl, 8
        db 074h, 00Ch   ; je 0x2cdb4d
        db 0F6h, 0C5h, 004h   ; test ch, 4
        db 075h, 007h   ; jne 0x2cdb4d
        db 0C7h, 046h, 018h, 000h, 010h, 000h, 000h   ; mov dword ptr [esi + 0x18], 0x1000
$L_2cdb4d:
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 048h   ; dec eax
        db 089h, 046h, 004h   ; mov dword ptr [esi + 4], eax
        db 00Fh, 0B6h, 001h   ; movzx eax, byte ptr [ecx]
        db 041h   ; inc ecx
        db 089h, 00Eh   ; mov dword ptr [esi], ecx
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
$L_2cdb5b:
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 083h, 0C0h, 010h   ; add eax, 0x10
        db 009h, 046h, 00Ch   ; or dword ptr [esi + 0xc], eax
        db 083h, 066h, 004h, 000h   ; and dword ptr [esi + 4], 0
$L_2cdb6c:
        db 083h, 0C8h, 0FFh   ; or eax, 0xffffffff
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg29 ENDS

seg30 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: __read_1 @ 0x002CDD48
PUBLIC __read_1
__read_1:
        db 06Ah, 00Ch   ; push 0xc
        db 068h   ; push 0x418078
        dd _unk_418078
        call __SEH_prolog   ; 0x2C8308
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 03Bh, 01Dh   ; cmp ebx, dword ptr [0x524340]
        dd __nhandle
        db 073h, 078h   ; jae 0x2cddd7
        db 08Bh, 0C3h   ; mov eax, ebx
        db 0C1h, 0F8h, 005h   ; sar eax, 5
        db 08Dh, 03Ch, 085h   ; lea edi, [eax*4 + 0x524360]
        dd ___pioinfo
        db 08Bh, 0C3h   ; mov eax, ebx
        db 083h, 0E0h, 01Fh   ; and eax, 0x1f
        db 08Dh, 034h, 080h   ; lea esi, [eax + eax*4]
        db 0C1h, 0E6h, 003h   ; shl esi, 3
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 0F6h, 044h, 030h, 004h, 001h   ; test byte ptr [eax + esi + 4], 1
        db 074h, 058h   ; je 0x2cddd7
        db 053h   ; push ebx
        call __lock_fhandle   ; 0x2CF825
        db 059h   ; pop ecx
        db 083h, 065h, 0FCh, 000h   ; and dword ptr [ebp - 4], 0
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 0F6h, 044h, 030h, 004h, 001h   ; test byte ptr [eax + esi + 4], 1
        db 074h, 014h   ; je 0x2cdda7
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 053h   ; push ebx
        call __read_lk   ; 0x2CDB71
        db 083h, 0C4h, 00Ch   ; add esp, 0xc
        db 089h, 045h, 0E4h   ; mov dword ptr [ebp - 0x1c], eax
        db 0EBh, 017h   ; jmp 0x2cddbe
$L_2cdda7:
        call __errno   ; 0x2CC340
        db 0C7h, 000h, 009h, 000h, 000h, 000h   ; mov dword ptr [eax], 9
        call ___doserrno   ; 0x2CC349
        db 083h, 020h, 000h   ; and dword ptr [eax], 0
        db 083h, 04Dh, 0E4h, 0FFh   ; or dword ptr [ebp - 0x1c], 0xffffffff
$L_2cddbe:
        db 083h, 04Dh, 0FCh, 0FFh   ; or dword ptr [ebp - 4], 0xffffffff
        db 0E8h, 008h, 000h, 000h, 000h   ; call 0x2cddcf
        db 08Bh, 045h, 0E4h   ; mov eax, dword ptr [ebp - 0x1c]
        db 0EBh, 021h   ; jmp 0x2cdded
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
$L_2cddcf:
        db 053h   ; push ebx
        call __unlock_fhandle   ; 0x2CF8C5
        db 059h   ; pop ecx
        db 0C3h   ; ret 
$L_2cddd7:
        call __errno   ; 0x2CC340
        db 0C7h, 000h, 009h, 000h, 000h, 000h   ; mov dword ptr [eax], 9
        call ___doserrno   ; 0x2CC349
        db 083h, 020h, 000h   ; and dword ptr [eax], 0
        db 083h, 0C8h, 0FFh   ; or eax, 0xffffffff
$L_2cdded:
        call __SEH_epilog   ; 0x2C8343
        db 0C3h   ; ret 
seg30 ENDS


seg32 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _sub_2CEF8E @ 0x002CEF8E
PUBLIC _sub_2CEF8E
_sub_2CEF8E:
        db 06Ah, 002h   ; push 2
        call __amsg_exit   ; 0x2CBD71
        db 059h   ; pop ecx
        db 0C3h   ; ret 
seg32 ENDS


        END
