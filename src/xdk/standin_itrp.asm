; codfh-match: XDK TrueType interpreter (itrp_*) pieces
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN _AddDistance@20:NEAR
EXTERN _AddProportion@20:NEAR
EXTERN _DoubleCheckLinkColor@16:NEAR
EXTERN _ExecutePhaseControl@8:NEAR
EXTERN _FixDiv@8:NEAR
EXTERN _InterAlign@16:NEAR
EXTERN _LongMulDiv@12:NEAR
EXTERN _Mul26Dot6@8:NEAR
EXTERN _ShortFracMul@8:NEAR
EXTERN _itrp_CheckSingleWidth@8:NEAR
EXTERN _itrp_Check_PF_Proj@4:NEAR
EXTERN _itrp_ComputeAndCheck_PF_Proj@4:NEAR
EXTERN _itrp_DeltaEngine@20:NEAR
EXTERN _itrp_GetCVTScale@4:NEAR
EXTERN _itrp_MovePoint@16:BYTE
EXTERN _itrp_Project@12:BYTE
EXTERN _itrp_PushSomeBytes@12:NEAR
EXTERN _itrp_PushSomeWords@12:NEAR
EXTERN _itrp_RoundOff@12:NEAR
EXTERN _itrp_RoundOffSP@12:NEAR
EXTERN _itrp_RoundToGrid@12:NEAR
EXTERN _itrp_SHP_Common@24:NEAR
EXTERN _itrp_SH_Common@20:NEAR
EXTERN _itrp_SetRoundValues@12:NEAR
EXTERN _itrp_SkipPushData@8:NEAR
EXTERN _itrp_XMovePoint@16:BYTE
EXTERN _itrp_YMovePoint@16:BYTE
EXTERN _sub_236796:BYTE
EXTERN _sub_23684E:BYTE
EXTERN ??_GCDirectSoundStream@DirectSound@@UAEPAXI@Z:NEAR
EXTERN _unk_327ECE:NEAR
EXTERN _unk_3ECF00:BYTE
EXTERN _unk_3ECF04:BYTE
EXTERN _unk_3ECF08:BYTE
EXTERN _unk_3ECF0C:BYTE
EXTERN _unk_3ECF10:BYTE
EXTERN _unk_3ECF14:BYTE
EXTERN _unk_3ECF18:BYTE
EXTERN _unk_3ECF1C:BYTE
EXTERN _unk_3ECF40:BYTE

seg0 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SVTCA_0@12 @ 0x002368F3
PUBLIC _itrp_SVTCA_0@12
_itrp_SVTCA_0@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 066h, 083h, 060h, 00Ch, 000h   ; and word ptr [eax + 0xc], 0
        db 066h, 083h, 060h, 010h, 000h   ; and word ptr [eax + 0x10], 0
        db 08Bh, 048h, 024h   ; mov ecx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 0BEh   ; mov esi, 0x236796
        dd _sub_236796
        db 066h, 0C7h, 040h, 00Eh, 000h, 040h   ; mov word ptr [eax + 0xe], 0x4000
        db 066h, 0C7h, 040h, 012h, 000h, 040h   ; mov word ptr [eax + 0x12], 0x4000
        db 0C7h, 040h, 048h   ; mov dword ptr [eax + 0x48], 0x236717
        dd _itrp_YMovePoint@16
        db 089h, 070h, 04Ch   ; mov dword ptr [eax + 0x4c], esi
        db 066h, 08Bh, 091h, 06Ch, 001h, 000h, 000h   ; mov dx, word ptr [ecx + 0x16c]
        db 0F6h, 0C2h, 001h   ; test dl, 1
        db 057h   ; push edi
        db 074h, 00Ah   ; je 0x236937
        db 0F6h, 0C2h, 004h   ; test dl, 4
        db 074h, 005h   ; je 0x236937
        db 033h, 0D2h   ; xor edx, edx
        db 042h   ; inc edx
        db 0EBh, 002h   ; jmp 0x236939
$L_236937:
        db 033h, 0D2h   ; xor edx, edx
$L_236939:
        db 066h, 085h, 0D2h   ; test dx, dx
        db 066h, 089h, 090h, 080h, 000h, 000h, 000h   ; mov word ptr [eax + 0x80], dx
        db 074h, 014h   ; je 0x236959
        db 0F6h, 041h, 06Ch, 004h   ; test byte ptr [ecx + 0x6c], 4
        db 075h, 009h   ; jne 0x236954
        db 080h, 0B9h, 025h, 001h, 000h, 000h, 000h   ; cmp byte ptr [ecx + 0x125], 0
        db 074h, 005h   ; je 0x236959
$L_236954:
        db 033h, 0D2h   ; xor edx, edx
        db 042h   ; inc edx
        db 0EBh, 002h   ; jmp 0x23695b
$L_236959:
        db 033h, 0D2h   ; xor edx, edx
$L_23695b:
        db 00Fh, 0B7h, 079h, 078h   ; movzx edi, word ptr [ecx + 0x78]
        db 08Dh, 014h, 0D7h   ; lea edx, [edi + edx*8]
        db 08Bh, 014h, 095h   ; mov edx, dword ptr [edx*4 + 0x3ecf00]
        dd _unk_3ECF00
        db 089h, 051h, 074h   ; mov dword ptr [ecx + 0x74], edx
        db 066h, 083h, 088h, 084h, 000h, 000h, 000h, 0FFh   ; or word ptr [eax + 0x84], 0xffff
        db 066h, 083h, 088h, 082h, 000h, 000h, 000h, 0FFh   ; or word ptr [eax + 0x82], 0xffff
        db 066h, 083h, 078h, 068h, 000h   ; cmp word ptr [eax + 0x68], 0
        db 05Fh   ; pop edi
        db 089h, 070h, 050h   ; mov dword ptr [eax + 0x50], esi
        db 066h, 0C7h, 040h, 044h, 000h, 040h   ; mov word ptr [eax + 0x44], 0x4000
        db 05Eh   ; pop esi
        db 074h, 006h   ; je 0x236994
        db 066h, 0C7h, 040h, 068h, 002h, 000h   ; mov word ptr [eax + 0x68], 2
$L_236994:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg0 ENDS

seg24 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SVTCA_1@12 @ 0x0023699B
PUBLIC _itrp_SVTCA_1@12
_itrp_SVTCA_1@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 066h, 083h, 060h, 00Eh, 000h   ; and word ptr [eax + 0xe], 0
        db 066h, 083h, 060h, 012h, 000h   ; and word ptr [eax + 0x12], 0
        db 08Bh, 048h, 024h   ; mov ecx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 0BEh   ; mov esi, 0x23a06a
        dd _itrp_EIF@12
        db 066h, 0C7h, 040h, 00Ch, 000h, 040h   ; mov word ptr [eax + 0xc], 0x4000
        db 066h, 0C7h, 040h, 010h, 000h, 040h   ; mov word ptr [eax + 0x10], 0x4000
        db 0C7h, 040h, 048h   ; mov dword ptr [eax + 0x48], 0x2366f7
        dd _itrp_XMovePoint@16
        db 089h, 070h, 04Ch   ; mov dword ptr [eax + 0x4c], esi
        db 066h, 08Bh, 091h, 06Ch, 001h, 000h, 000h   ; mov dx, word ptr [ecx + 0x16c]
        db 0F6h, 0C2h, 001h   ; test dl, 1
        db 057h   ; push edi
        db 074h, 00Ah   ; je 0x2369df
        db 0F6h, 0C2h, 004h   ; test dl, 4
        db 075h, 005h   ; jne 0x2369df
        db 033h, 0D2h   ; xor edx, edx
        db 042h   ; inc edx
        db 0EBh, 002h   ; jmp 0x2369e1
$L_2369df:
        db 033h, 0D2h   ; xor edx, edx
$L_2369e1:
        db 066h, 085h, 0D2h   ; test dx, dx
        db 066h, 089h, 090h, 080h, 000h, 000h, 000h   ; mov word ptr [eax + 0x80], dx
        db 074h, 014h   ; je 0x236a01
        db 0F6h, 041h, 06Ch, 004h   ; test byte ptr [ecx + 0x6c], 4
        db 075h, 009h   ; jne 0x2369fc
        db 080h, 0B9h, 025h, 001h, 000h, 000h, 000h   ; cmp byte ptr [ecx + 0x125], 0
        db 074h, 005h   ; je 0x236a01
$L_2369fc:
        db 033h, 0D2h   ; xor edx, edx
        db 042h   ; inc edx
        db 0EBh, 002h   ; jmp 0x236a03
$L_236a01:
        db 033h, 0D2h   ; xor edx, edx
$L_236a03:
        db 00Fh, 0B7h, 079h, 078h   ; movzx edi, word ptr [ecx + 0x78]
        db 08Dh, 014h, 0D7h   ; lea edx, [edi + edx*8]
        db 08Bh, 014h, 095h   ; mov edx, dword ptr [edx*4 + 0x3ecf00]
        dd _unk_3ECF00
        db 089h, 051h, 074h   ; mov dword ptr [ecx + 0x74], edx
        db 066h, 083h, 088h, 084h, 000h, 000h, 000h, 0FFh   ; or word ptr [eax + 0x84], 0xffff
        db 066h, 083h, 088h, 082h, 000h, 000h, 000h, 0FFh   ; or word ptr [eax + 0x82], 0xffff
        db 066h, 083h, 078h, 068h, 000h   ; cmp word ptr [eax + 0x68], 0
        db 05Fh   ; pop edi
        db 089h, 070h, 050h   ; mov dword ptr [eax + 0x50], esi
        db 066h, 0C7h, 040h, 044h, 000h, 040h   ; mov word ptr [eax + 0x44], 0x4000
        db 05Eh   ; pop esi
        db 074h, 006h   ; je 0x236a3c
        db 066h, 0C7h, 040h, 068h, 001h, 000h   ; mov word ptr [eax + 0x68], 1
$L_236a3c:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg24 ENDS

seg1 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SPVTCA_1@12 @ 0x00236AE0
PUBLIC _itrp_SPVTCA_1@12
_itrp_SPVTCA_1@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 066h, 083h, 066h, 00Eh, 000h   ; and word ptr [esi + 0xe], 0
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 066h, 0C7h, 046h, 00Ch, 000h, 040h   ; mov word ptr [esi + 0xc], 0x4000
        db 0C7h, 046h, 04Ch   ; mov dword ptr [esi + 0x4c], 0x23a06a
        dd _itrp_EIF@12
        db 066h, 08Bh, 088h, 06Ch, 001h, 000h, 000h   ; mov cx, word ptr [eax + 0x16c]
        db 0F6h, 0C1h, 001h   ; test cl, 1
        db 074h, 00Ah   ; je 0x236b10
        db 0F6h, 0C1h, 004h   ; test cl, 4
        db 075h, 005h   ; jne 0x236b10
        db 033h, 0C9h   ; xor ecx, ecx
        db 041h   ; inc ecx
        db 0EBh, 002h   ; jmp 0x236b12
$L_236b10:
        db 033h, 0C9h   ; xor ecx, ecx
$L_236b12:
        db 066h, 085h, 0C9h   ; test cx, cx
        db 066h, 089h, 08Eh, 080h, 000h, 000h, 000h   ; mov word ptr [esi + 0x80], cx
        db 074h, 014h   ; je 0x236b32
        db 0F6h, 040h, 06Ch, 004h   ; test byte ptr [eax + 0x6c], 4
        db 075h, 009h   ; jne 0x236b2d
        db 080h, 0B8h, 025h, 001h, 000h, 000h, 000h   ; cmp byte ptr [eax + 0x125], 0
        db 074h, 005h   ; je 0x236b32
$L_236b2d:
        db 033h, 0C9h   ; xor ecx, ecx
        db 041h   ; inc ecx
        db 0EBh, 002h   ; jmp 0x236b34
$L_236b32:
        db 033h, 0C9h   ; xor ecx, ecx
$L_236b34:
        db 00Fh, 0B7h, 050h, 078h   ; movzx edx, word ptr [eax + 0x78]
        db 08Dh, 00Ch, 0CAh   ; lea ecx, [edx + ecx*8]
        db 08Bh, 00Ch, 08Dh   ; mov ecx, dword ptr [ecx*4 + 0x3ecf00]
        dd _unk_3ECF00
        db 089h, 048h, 074h   ; mov dword ptr [eax + 0x74], ecx
        db 066h, 08Bh, 046h, 010h   ; mov ax, word ptr [esi + 0x10]
        db 066h, 083h, 08Eh, 084h, 000h, 000h, 000h, 0FFh   ; or word ptr [esi + 0x84], 0xffff
        db 066h, 083h, 08Eh, 082h, 000h, 000h, 000h, 0FFh   ; or word ptr [esi + 0x82], 0xffff
        db 056h   ; push esi
        db 066h, 089h, 046h, 044h   ; mov word ptr [esi + 0x44], ax
        call _itrp_Check_PF_Proj@4   ; 0x236862
        db 08Bh, 046h, 04Ch   ; mov eax, dword ptr [esi + 0x4c]
        db 066h, 083h, 066h, 068h, 000h   ; and word ptr [esi + 0x68], 0
        db 089h, 046h, 050h   ; mov dword ptr [esi + 0x50], eax
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 0C7h, 046h, 048h   ; mov dword ptr [esi + 0x48], 0x23661e
        dd _itrp_MovePoint@16
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg1 ENDS

seg25 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SFVTCA_0@12 @ 0x00236B7D
PUBLIC _itrp_SFVTCA_0@12
_itrp_SFVTCA_0@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 066h, 08Bh, 046h, 00Eh   ; mov ax, word ptr [esi + 0xe]
        db 066h, 083h, 066h, 010h, 000h   ; and word ptr [esi + 0x10], 0
        db 056h   ; push esi
        db 066h, 0C7h, 046h, 012h, 000h, 040h   ; mov word ptr [esi + 0x12], 0x4000
        db 066h, 089h, 046h, 044h   ; mov word ptr [esi + 0x44], ax
        call _itrp_Check_PF_Proj@4   ; 0x236862
        db 066h, 083h, 066h, 068h, 000h   ; and word ptr [esi + 0x68], 0
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 0C7h, 046h, 048h   ; mov dword ptr [esi + 0x48], 0x23661e
        dd _itrp_MovePoint@16
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_SFVTCA_1@12 @ 0x00236BAF
PUBLIC _itrp_SFVTCA_1@12
_itrp_SFVTCA_1@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 066h, 08Bh, 046h, 00Ch   ; mov ax, word ptr [esi + 0xc]
        db 066h, 083h, 066h, 012h, 000h   ; and word ptr [esi + 0x12], 0
        db 056h   ; push esi
        db 066h, 0C7h, 046h, 010h, 000h, 040h   ; mov word ptr [esi + 0x10], 0x4000
        db 066h, 089h, 046h, 044h   ; mov word ptr [esi + 0x44], ax
        call _itrp_Check_PF_Proj@4   ; 0x236862
        db 066h, 083h, 066h, 068h, 000h   ; and word ptr [esi + 0x68], 0
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 0C7h, 046h, 048h   ; mov dword ptr [esi + 0x48], 0x23661e
        dd _itrp_MovePoint@16
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg25 ENDS

seg2 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_WPV@12 @ 0x00236FF9
PUBLIC _itrp_WPV@12
_itrp_WPV@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 08Dh, 048h, 0F8h   ; lea ecx, [eax - 8]
        db 03Bh, 00Ah   ; cmp ecx, dword ptr [edx]
        db 073h, 00Fh   ; jae 0x23701a
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0E9h, 0B9h, 000h, 000h, 000h   ; jmp 0x2370d3
$L_23701a:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 066h, 08Bh, 008h   ; mov cx, word ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 066h, 089h, 04Eh, 00Eh   ; mov word ptr [esi + 0xe], cx
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 066h, 08Bh, 000h   ; mov ax, word ptr [eax]
        db 066h, 083h, 08Eh, 084h, 000h, 000h, 000h, 0FFh   ; or word ptr [esi + 0x84], 0xffff
        db 066h, 083h, 08Eh, 082h, 000h, 000h, 000h, 0FFh   ; or word ptr [esi + 0x82], 0xffff
        db 056h   ; push esi
        db 066h, 089h, 046h, 00Ch   ; mov word ptr [esi + 0xc], ax
        call _itrp_ComputeAndCheck_PF_Proj@4   ; 0x236892
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 0C7h, 046h, 048h   ; mov dword ptr [esi + 0x48], 0x23661e
        dd _itrp_MovePoint@16
        db 0C7h, 046h, 04Ch   ; mov dword ptr [esi + 0x4c], 0x236738
        dd _itrp_Project@12
        db 066h, 08Bh, 088h, 06Ch, 001h, 000h, 000h   ; mov cx, word ptr [eax + 0x16c]
        db 033h, 0D2h   ; xor edx, edx
        db 0F6h, 0C1h, 001h   ; test cl, 1
        db 074h, 026h   ; je 0x23708f
        db 0F6h, 0C1h, 004h   ; test cl, 4
        db 075h, 00Eh   ; jne 0x23707c
        db 066h, 081h, 07Eh, 00Eh, 000h, 040h   ; cmp word ptr [esi + 0xe], 0x4000
        db 075h, 014h   ; jne 0x23708a
        db 066h, 039h, 056h, 00Ch   ; cmp word ptr [esi + 0xc], dx
        db 0EBh, 00Ch   ; jmp 0x237088
$L_23707c:
        db 066h, 081h, 07Eh, 00Ch, 000h, 040h   ; cmp word ptr [esi + 0xc], 0x4000
        db 075h, 006h   ; jne 0x23708a
        db 066h, 039h, 056h, 00Eh   ; cmp word ptr [esi + 0xe], dx
$L_237088:
        db 074h, 005h   ; je 0x23708f
$L_23708a:
        db 033h, 0C9h   ; xor ecx, ecx
        db 041h   ; inc ecx
        db 0EBh, 002h   ; jmp 0x237091
$L_23708f:
        db 033h, 0C9h   ; xor ecx, ecx
$L_237091:
        db 066h, 03Bh, 0CAh   ; cmp cx, dx
        db 066h, 089h, 08Eh, 080h, 000h, 000h, 000h   ; mov word ptr [esi + 0x80], cx
        db 074h, 013h   ; je 0x2370b0
        db 0F6h, 040h, 06Ch, 004h   ; test byte ptr [eax + 0x6c], 4
        db 075h, 008h   ; jne 0x2370ab
        db 038h, 090h, 025h, 001h, 000h, 000h   ; cmp byte ptr [eax + 0x125], dl
        db 074h, 005h   ; je 0x2370b0
$L_2370ab:
        db 033h, 0C9h   ; xor ecx, ecx
        db 041h   ; inc ecx
        db 0EBh, 002h   ; jmp 0x2370b2
$L_2370b0:
        db 033h, 0C9h   ; xor ecx, ecx
$L_2370b2:
        db 057h   ; push edi
        db 00Fh, 0B7h, 078h, 078h   ; movzx edi, word ptr [eax + 0x78]
        db 08Dh, 00Ch, 0CFh   ; lea ecx, [edi + ecx*8]
        db 08Bh, 00Ch, 08Dh   ; mov ecx, dword ptr [ecx*4 + 0x3ecf00]
        dd _unk_3ECF00
        db 089h, 048h, 074h   ; mov dword ptr [eax + 0x74], ecx
        db 08Bh, 046h, 04Ch   ; mov eax, dword ptr [esi + 0x4c]
        db 089h, 046h, 050h   ; mov dword ptr [esi + 0x50], eax
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 066h, 089h, 056h, 068h   ; mov word ptr [esi + 0x68], dx
        db 05Fh   ; pop edi
$L_2370d3:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg2 ENDS

seg26 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_WFV@12 @ 0x002370D7
PUBLIC _itrp_WFV@12
_itrp_WFV@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x2370f5
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 030h   ; jmp 0x237125
$L_2370f5:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 066h, 08Bh, 008h   ; mov cx, word ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 066h, 089h, 04Eh, 012h   ; mov word ptr [esi + 0x12], cx
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 066h, 08Bh, 000h   ; mov ax, word ptr [eax]
        db 056h   ; push esi
        db 066h, 089h, 046h, 010h   ; mov word ptr [esi + 0x10], ax
        call _itrp_ComputeAndCheck_PF_Proj@4   ; 0x236892
        db 066h, 083h, 066h, 068h, 000h   ; and word ptr [esi + 0x68], 0
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 0C7h, 046h, 048h   ; mov dword ptr [esi + 0x48], 0x23661e
        dd _itrp_MovePoint@16
$L_237125:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RPV@12 @ 0x00237129
PUBLIC _itrp_RPV@12
_itrp_RPV@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 008h   ; lea esi, [ecx + 8]
        db 03Bh, 0B2h, 05Ch, 001h, 000h, 000h   ; cmp esi, dword ptr [edx + 0x15c]
        db 05Eh   ; pop esi
        db 076h, 00Ch   ; jbe 0x23714c
        db 0C7h, 040h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1111
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 01Bh   ; jmp 0x237167
$L_23714c:
        db 00Fh, 0BFh, 050h, 00Ch   ; movsx edx, word ptr [eax + 0xc]
        db 089h, 011h   ; mov dword ptr [ecx], edx
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 00Fh, 0BFh, 050h, 00Eh   ; movsx edx, word ptr [eax + 0xe]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 089h, 011h   ; mov dword ptr [ecx], edx
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237167:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RFV@12 @ 0x0023716A
PUBLIC _itrp_RFV@12
_itrp_RFV@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 008h   ; lea esi, [ecx + 8]
        db 03Bh, 0B2h, 05Ch, 001h, 000h, 000h   ; cmp esi, dword ptr [edx + 0x15c]
        db 05Eh   ; pop esi
        db 076h, 00Ch   ; jbe 0x23718d
        db 0C7h, 040h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1111
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 01Bh   ; jmp 0x2371a8
$L_23718d:
        db 00Fh, 0BFh, 050h, 010h   ; movsx edx, word ptr [eax + 0x10]
        db 089h, 011h   ; mov dword ptr [ecx], edx
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 00Fh, 0BFh, 050h, 012h   ; movsx edx, word ptr [eax + 0x12]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 089h, 011h   ; mov dword ptr [ecx], edx
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_2371a8:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg26 ENDS

seg3 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_ISECT@12 @ 0x002371CE
PUBLIC _itrp_ISECT@12
_itrp_ISECT@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 024h   ; sub esp, 0x24
        db 053h   ; push ebx
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 08Bh, 043h, 018h   ; mov eax, dword ptr [ebx + 0x18]
        db 08Bh, 04Bh, 024h   ; mov ecx, dword ptr [ebx + 0x24]
        db 08Dh, 050h, 0ECh   ; lea edx, [eax - 0x14]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 057h   ; push edi
        db 08Bh, 03Bh   ; mov edi, dword ptr [ebx]
        db 073h, 00Ch   ; jae 0x2371f4
        db 08Bh, 043h, 070h   ; mov eax, dword ptr [ebx + 0x70]
        db 0C7h, 043h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ebx + 0x6c], 0x1110
        db 0EBh, 030h   ; jmp 0x237224
$L_2371f4:
        db 08Bh, 04Bh, 024h   ; mov ecx, dword ptr [ebx + 0x24]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 039h, 07Bh, 020h   ; cmp dword ptr [ebx + 0x20], edi
        db 056h   ; push esi
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 075h, 023h   ; jne 0x23722a
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0D1h   ; cmp edx, ecx
$L_237213:
        db 07Dh, 004h   ; jge 0x237219
        db 085h, 0D2h   ; test edx, edx
        db 07Dh, 019h   ; jge 0x237232
$L_237219:
        db 08Bh, 043h, 070h   ; mov eax, dword ptr [ebx + 0x70]
        db 0C7h, 043h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [ebx + 0x6c], 0x1112
$L_237223:
        db 05Eh   ; pop esi
$L_237224:
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_23722a:
        db 03Bh, 091h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [ecx + 0x160]
        db 0EBh, 0E1h   ; jmp 0x237213
$L_237232:
        db 039h, 07Bh, 020h   ; cmp dword ptr [ebx + 0x20], edi
        db 08Bh, 04Bh, 024h   ; mov ecx, dword ptr [ebx + 0x24]
        db 075h, 066h   ; jne 0x2372a0
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0F1h   ; cmp esi, ecx
$L_237246:
        db 07Dh, 0D1h   ; jge 0x237219
        db 085h, 0F6h   ; test esi, esi
        db 07Ch, 0CDh   ; jl 0x237219
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 08Bh, 034h, 0B1h   ; mov esi, dword ptr [ecx + esi*4]
        db 089h, 075h, 0E8h   ; mov dword ptr [ebp - 0x18], esi
        db 08Bh, 034h, 091h   ; mov esi, dword ptr [ecx + edx*4]
        db 08Bh, 04Fh, 004h   ; mov ecx, dword ptr [edi + 4]
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 08Bh, 03Ch, 0B9h   ; mov edi, dword ptr [ecx + edi*4]
        db 02Bh, 075h, 0E8h   ; sub esi, dword ptr [ebp - 0x18]
        db 089h, 07Dh, 0E4h   ; mov dword ptr [ebp - 0x1c], edi
        db 08Bh, 03Ch, 091h   ; mov edi, dword ptr [ecx + edx*4]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 02Bh, 07Dh, 0E4h   ; sub edi, dword ptr [ebp - 0x1c]
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 089h, 04Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ecx
        db 08Bh, 04Bh, 004h   ; mov ecx, dword ptr [ebx + 4]
        db 089h, 055h, 0E0h   ; mov dword ptr [ebp - 0x20], edx
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 039h, 04Bh, 020h   ; cmp dword ptr [ebx + 0x20], ecx
        db 08Bh, 04Bh, 024h   ; mov ecx, dword ptr [ebx + 0x24]
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 075h, 01Fh   ; jne 0x2372a8
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0D1h   ; cmp edx, ecx
        db 07Dh, 082h   ; jge 0x237219
        db 085h, 0D2h   ; test edx, edx
        db 07Dh, 024h   ; jge 0x2372bf
        db 0E9h, 079h, 0FFh, 0FFh, 0FFh   ; jmp 0x237219
$L_2372a0:
        db 03Bh, 0B1h, 060h, 001h, 000h, 000h   ; cmp esi, dword ptr [ecx + 0x160]
        db 0EBh, 09Eh   ; jmp 0x237246
$L_2372a8:
        db 08Bh, 055h, 0F0h   ; mov edx, dword ptr [ebp - 0x10]
        db 03Bh, 091h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [ecx + 0x160]
        db 00Fh, 08Dh, 062h, 0FFh, 0FFh, 0FFh   ; jge 0x237219
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 08Ch, 05Ah, 0FFh, 0FFh, 0FFh   ; jl 0x237219
$L_2372bf:
        db 08Bh, 04Bh, 020h   ; mov ecx, dword ptr [ebx + 0x20]
        db 03Bh, 04Bh, 004h   ; cmp ecx, dword ptr [ebx + 4]
        db 00Fh, 085h, 0ADh, 000h, 000h, 000h   ; jne 0x237378
        db 08Bh, 04Bh, 024h   ; mov ecx, dword ptr [ebx + 0x24]
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 051h, 010h   ; movzx edx, word ptr [ecx + 0x10]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 03Bh, 0CAh   ; cmp ecx, edx
$L_2372dc:
        db 00Fh, 08Dh, 037h, 0FFh, 0FFh, 0FFh   ; jge 0x237219
        db 085h, 0C9h   ; test ecx, ecx
        db 00Fh, 08Ch, 02Fh, 0FFh, 0FFh, 0FFh   ; jl 0x237219
        db 08Bh, 053h, 004h   ; mov edx, dword ptr [ebx + 4]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 0C1h, 0E1h, 002h   ; shl ecx, 2
        db 089h, 04Dh, 0ECh   ; mov dword ptr [ebp - 0x14], ecx
        db 08Bh, 00Ch, 00Ah   ; mov ecx, dword ptr [edx + ecx]
        db 08Bh, 055h, 0F0h   ; mov edx, dword ptr [ebp - 0x10]
        db 089h, 04Dh, 0F8h   ; mov dword ptr [ebp - 8], ecx
        db 08Bh, 04Bh, 004h   ; mov ecx, dword ptr [ebx + 4]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 08Bh, 00Ch, 091h   ; mov ecx, dword ptr [ecx + edx*4]
        db 02Bh, 04Dh, 0F8h   ; sub ecx, dword ptr [ebp - 8]
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 08Bh, 04Bh, 004h   ; mov ecx, dword ptr [ebx + 4]
        db 08Bh, 049h, 004h   ; mov ecx, dword ptr [ecx + 4]
        db 08Bh, 014h, 011h   ; mov edx, dword ptr [ecx + edx]
        db 089h, 055h, 0F4h   ; mov dword ptr [ebp - 0xc], edx
        db 08Bh, 055h, 0F0h   ; mov edx, dword ptr [ebp - 0x10]
        db 08Bh, 00Ch, 091h   ; mov ecx, dword ptr [ecx + edx*4]
        db 02Bh, 04Dh, 0F4h   ; sub ecx, dword ptr [ebp - 0xc]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 085h, 0D2h   ; test edx, edx
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 07Dh, 002h   ; jge 0x237330
        db 0F7h, 0DAh   ; neg edx
$L_237330:
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 07Dh, 002h   ; jge 0x237338
        db 0F7h, 0D9h   ; neg ecx
$L_237338:
        db 03Bh, 0D1h   ; cmp edx, ecx
        db 07Eh, 00Bh   ; jle 0x237347
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 089h, 04Dh, 0E0h   ; mov dword ptr [ebp - 0x20], ecx
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 04Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ecx
$L_237347:
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 04Dh, 0ECh   ; mov dword ptr [ebp - 0x14], ecx
        db 08Bh, 04Bh, 008h   ; mov ecx, dword ptr [ebx + 8]
        db 039h, 04Bh, 020h   ; cmp dword ptr [ebx + 0x20], ecx
        db 08Bh, 04Bh, 024h   ; mov ecx, dword ptr [ebx + 0x24]
        db 075h, 02Eh   ; jne 0x237388
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 051h, 010h   ; movzx edx, word ptr [ecx + 0x10]
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 00Fh, 08Dh, 0AAh, 0FEh, 0FFh, 0FFh   ; jge 0x237219
        db 085h, 0C9h   ; test ecx, ecx
        db 07Dh, 02Eh   ; jge 0x2373a1
        db 0E9h, 0A1h, 0FEh, 0FFh, 0FFh   ; jmp 0x237219
$L_237378:
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 08Bh, 053h, 024h   ; mov edx, dword ptr [ebx + 0x24]
        db 03Bh, 08Ah, 060h, 001h, 000h, 000h   ; cmp ecx, dword ptr [edx + 0x160]
        db 0E9h, 054h, 0FFh, 0FFh, 0FFh   ; jmp 0x2372dc
$L_237388:
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 03Bh, 091h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [ecx + 0x160]
        db 00Fh, 08Dh, 082h, 0FEh, 0FFh, 0FFh   ; jge 0x237219
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 08Ch, 07Ah, 0FEh, 0FFh, 0FFh   ; jl 0x237219
        db 08Bh, 0CAh   ; mov ecx, edx
$L_2373a1:
        db 08Bh, 053h, 008h   ; mov edx, dword ptr [ebx + 8]
        db 089h, 043h, 018h   ; mov dword ptr [ebx + 0x18], eax
        db 08Bh, 043h, 020h   ; mov eax, dword ptr [ebx + 0x20]
        db 03Bh, 0D0h   ; cmp edx, eax
        db 074h, 026h   ; je 0x2373d4
        db 08Bh, 043h, 024h   ; mov eax, dword ptr [ebx + 0x24]
        db 080h, 0B8h, 025h, 001h, 000h, 000h, 002h   ; cmp byte ptr [eax + 0x125], 2
        db 075h, 01Ah   ; jne 0x2373d4
        db 0F6h, 080h, 06Ch, 001h, 000h, 000h, 002h   ; test byte ptr [eax + 0x16c], 2
        db 074h, 011h   ; je 0x2373d4
        db 0FFh, 075h, 0E0h   ; push dword ptr [ebp - 0x20]
        db 051h   ; push ecx
        db 0FFh, 075h, 0DCh   ; push dword ptr [ebp - 0x24]
        db 052h   ; push edx
        db 053h   ; push ebx
        call _AddProportion@20   ; 0x235D10
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
$L_2373d4:
        db 08Bh, 043h, 008h   ; mov eax, dword ptr [ebx + 8]
        db 08Bh, 040h, 024h   ; mov eax, dword ptr [eax + 0x24]
        db 003h, 0C1h   ; add eax, ecx
        db 080h, 008h, 003h   ; or byte ptr [eax], 3
        db 085h, 0FFh   ; test edi, edi
        db 08Bh, 05Bh, 008h   ; mov ebx, dword ptr [ebx + 8]
        db 08Bh, 013h   ; mov edx, dword ptr [ebx]
        db 08Bh, 05Bh, 004h   ; mov ebx, dword ptr [ebx + 4]
        db 089h, 055h, 0E0h   ; mov dword ptr [ebp - 0x20], edx
        db 089h, 05Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ebx
        db 075h, 02Ah   ; jne 0x23741b
        db 039h, 07Dh, 008h   ; cmp dword ptr [ebp + 8], edi
        db 075h, 010h   ; jne 0x237406
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 089h, 00Ch, 010h   ; mov dword ptr [eax + edx], ecx
        db 08Bh, 04Dh, 0E4h   ; mov ecx, dword ptr [ebp - 0x1c]
        db 0EBh, 02Ch   ; jmp 0x237432
$L_237406:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 02Bh, 05Dh, 0E4h   ; sub ebx, dword ptr [ebp - 0x1c]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0F7h, 0D8h   ; neg eax
        db 089h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], eax
        db 0E9h, 09Eh, 000h, 000h, 000h   ; jmp 0x2374b9
$L_23741b:
        db 085h, 0F6h   ; test esi, esi
        db 075h, 030h   ; jne 0x23744f
        db 039h, 075h, 0FCh   ; cmp dword ptr [ebp - 4], esi
        db 075h, 016h   ; jne 0x23743a
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Dh, 0E8h   ; mov ecx, dword ptr [ebp - 0x18]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 089h, 00Ch, 010h   ; mov dword ptr [eax + edx], ecx
        db 08Bh, 04Dh, 0F4h   ; mov ecx, dword ptr [ebp - 0xc]
$L_237432:
        db 089h, 00Ch, 018h   ; mov dword ptr [eax + ebx], ecx
        db 0E9h, 0E3h, 000h, 000h, 000h   ; jmp 0x23751d
$L_23743a:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 05Dh, 0F8h   ; mov ebx, dword ptr [ebp - 8]
        db 02Bh, 05Dh, 0E8h   ; sub ebx, dword ptr [ebp - 0x18]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 0F7h, 0D9h   ; neg ecx
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 0EBh, 06Dh   ; jmp 0x2374bc
$L_23744f:
        db 08Bh, 0CEh   ; mov ecx, esi
        db 07Dh, 002h   ; jge 0x237455
        db 0F7h, 0D9h   ; neg ecx
$L_237455:
        db 085h, 0FFh   ; test edi, edi
        db 08Bh, 0C7h   ; mov eax, edi
        db 07Dh, 002h   ; jge 0x23745d
        db 0F7h, 0D8h   ; neg eax
$L_23745d:
        db 03Bh, 0C8h   ; cmp ecx, eax
        db 07Ch, 028h   ; jl 0x237489
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 02Bh, 045h, 0E8h   ; sub eax, dword ptr [ebp - 0x18]
        db 056h   ; push esi
        db 057h   ; push edi
        db 050h   ; push eax
        call _LongMulDiv@12   ; 0x2358E9
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 02Bh, 05Dh, 0E4h   ; sub ebx, dword ptr [ebp - 0x1c]
        db 056h   ; push esi
        db 057h   ; push edi
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 02Bh, 0D8h   ; sub ebx, eax
        call _LongMulDiv@12   ; 0x2358E9
        db 02Bh, 045h, 0FCh   ; sub eax, dword ptr [ebp - 4]
        db 089h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], eax
        db 0EBh, 02Ah   ; jmp 0x2374b3
$L_237489:
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 02Bh, 045h, 0E4h   ; sub eax, dword ptr [ebp - 0x1c]
        db 057h   ; push edi
        db 056h   ; push esi
        db 050h   ; push eax
        call _LongMulDiv@12   ; 0x2358E9
        db 08Bh, 0D8h   ; mov ebx, eax
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
        db 02Bh, 045h, 0F8h   ; sub eax, dword ptr [ebp - 8]
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 003h, 0D8h   ; add ebx, eax
        call _LongMulDiv@12   ; 0x2358E9
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 02Bh, 0C8h   ; sub ecx, eax
        db 089h, 04Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ecx
$L_2374b3:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 055h, 0E0h   ; mov edx, dword ptr [ebp - 0x20]
$L_2374b9:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
$L_2374bc:
        db 083h, 07Dh, 0F0h, 000h   ; cmp dword ptr [ebp - 0x10], 0
        db 074h, 030h   ; je 0x2374f2
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Bh, 075h, 0ECh   ; mov esi, dword ptr [ebp - 0x14]
        db 053h   ; push ebx
        db 050h   ; push eax
        db 0C1h, 0E6h, 002h   ; shl esi, 2
        call _LongMulDiv@12   ; 0x2358E9
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 003h, 045h, 0F8h   ; add eax, dword ptr [ebp - 8]
        db 08Bh, 04Dh, 0E0h   ; mov ecx, dword ptr [ebp - 0x20]
        db 053h   ; push ebx
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 089h, 004h, 00Eh   ; mov dword ptr [esi + ecx], eax
        call _LongMulDiv@12   ; 0x2358E9
        db 003h, 045h, 0F4h   ; add eax, dword ptr [ebp - 0xc]
        db 08Bh, 04Dh, 0DCh   ; mov ecx, dword ptr [ebp - 0x24]
        db 089h, 004h, 00Eh   ; mov dword ptr [esi + ecx], eax
        db 0EBh, 02Bh   ; jmp 0x23751d
$L_2374f2:
        db 08Bh, 05Dh, 0ECh   ; mov ebx, dword ptr [ebp - 0x14]
        db 0D1h, 0F8h   ; sar eax, 1
        db 003h, 045h, 0F8h   ; add eax, dword ptr [ebp - 8]
        db 0D1h, 0FEh   ; sar esi, 1
        db 0D1h, 0F9h   ; sar ecx, 1
        db 003h, 04Dh, 0F4h   ; add ecx, dword ptr [ebp - 0xc]
        db 003h, 0F0h   ; add esi, eax
        db 003h, 075h, 0E8h   ; add esi, dword ptr [ebp - 0x18]
        db 08Bh, 045h, 0DCh   ; mov eax, dword ptr [ebp - 0x24]
        db 0D1h, 0FFh   ; sar edi, 1
        db 003h, 0F9h   ; add edi, ecx
        db 003h, 07Dh, 0E4h   ; add edi, dword ptr [ebp - 0x1c]
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 0D1h, 0FEh   ; sar esi, 1
        db 0D1h, 0FFh   ; sar edi, 1
        db 089h, 034h, 013h   ; mov dword ptr [ebx + edx], esi
        db 089h, 03Ch, 003h   ; mov dword ptr [ebx + eax], edi
$L_23751d:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0E9h, 0FEh, 0FCh, 0FFh, 0FFh   ; jmp 0x237223
seg3 ENDS

seg27 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_LMD@12 @ 0x00237525
PUBLIC _itrp_LMD@12
_itrp_LMD@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x237544
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 00Fh   ; jmp 0x237553
$L_237544:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 042h, 070h   ; mov dword ptr [edx + 0x70], eax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237553:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_LWTCI@12 @ 0x00237556
PUBLIC _itrp_LWTCI@12
_itrp_LWTCI@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x237575
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 00Fh   ; jmp 0x237584
$L_237575:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 042h, 05Ch   ; mov dword ptr [edx + 0x5c], eax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237584:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_LSWCI@12 @ 0x00237587
PUBLIC _itrp_LSWCI@12
_itrp_LSWCI@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x2375a6
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 014h   ; jmp 0x2375ba
$L_2375a6:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 089h, 04Ah, 060h   ; mov dword ptr [edx + 0x60], ecx
        db 066h, 083h, 060h, 068h, 000h   ; and word ptr [eax + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_2375ba:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_LSW@12 @ 0x002375BD
PUBLIC _itrp_LSW@12
_itrp_LSW@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 066h, 083h, 060h, 068h, 000h   ; and word ptr [eax + 0x68], 0
        db 056h   ; push esi
        db 08Bh, 070h, 024h   ; mov esi, dword ptr [eax + 0x24]
        db 08Dh, 051h, 0FCh   ; lea edx, [ecx - 4]
        db 03Bh, 016h   ; cmp edx, dword ptr [esi]
        db 073h, 00Ch   ; jae 0x2375e0
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 027h   ; jmp 0x237607
$L_2375e0:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 00Fh, 0BFh, 0C1h   ; movsx eax, cx
        db 050h   ; push eax
        db 08Dh, 086h, 000h, 001h, 000h, 000h   ; lea eax, [esi + 0x100]
        db 050h   ; push eax
        db 066h, 089h, 08Eh, 08Eh, 000h, 000h, 000h   ; mov word ptr [esi + 0x8e], cx
        db 0FFh, 096h, 0ACh, 000h, 000h, 000h   ; call dword ptr [esi + 0xac]
        db 089h, 046h, 064h   ; mov dword ptr [esi + 0x64], eax
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_237607:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_SRP0@12 @ 0x0023760B
PUBLIC _itrp_SRP0@12
_itrp_SRP0@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x23762a
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Fh   ; jmp 0x237639
$L_23762a:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 089h, 048h, 02Ch   ; mov dword ptr [eax + 0x2c], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237639:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_SRP1@12 @ 0x0023763C
PUBLIC _itrp_SRP1@12
_itrp_SRP1@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x23765b
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Fh   ; jmp 0x23766a
$L_23765b:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 089h, 048h, 030h   ; mov dword ptr [eax + 0x30], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_23766a:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_SRP2@12 @ 0x0023766D
PUBLIC _itrp_SRP2@12
_itrp_SRP2@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x23768c
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Fh   ; jmp 0x23769b
$L_23768c:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 089h, 048h, 034h   ; mov dword ptr [eax + 0x34], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_23769b:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg27 ENDS

seg4 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SetElementPtr@12 @ 0x002376D0
PUBLIC _itrp_SetElementPtr@12
_itrp_SetElementPtr@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 009h   ; jae 0x2376ec
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 0EBh, 04Dh   ; jmp 0x237739
$L_2376ec:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0F9h, 002h   ; cmp ecx, 2
        db 07Dh, 039h   ; jge 0x237732
        db 085h, 0C9h   ; test ecx, ecx
        db 07Ch, 035h   ; jl 0x237732
        db 08Bh, 054h, 024h, 00Ch   ; mov edx, dword ptr [esp + 0xc]
        db 06Bh, 0C9h, 038h   ; imul ecx, ecx, 0x38
        db 003h, 048h, 020h   ; add ecx, dword ptr [eax + 0x20]
        db 083h, 0EAh, 013h   ; sub edx, 0x13
        db 074h, 00Fh   ; je 0x23771b
        db 04Ah   ; dec edx
        db 074h, 01Eh   ; je 0x23772d
        db 04Ah   ; dec edx
        db 074h, 016h   ; je 0x237728
        db 04Ah   ; dec edx
        db 075h, 008h   ; jne 0x23771d
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
$L_23771b:
        db 089h, 008h   ; mov dword ptr [eax], ecx
$L_23771d:
        db 066h, 083h, 060h, 068h, 000h   ; and word ptr [eax + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0EBh, 014h   ; jmp 0x23773c
$L_237728:
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 0EBh, 0F0h   ; jmp 0x23771d
$L_23772d:
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 0EBh, 0EBh   ; jmp 0x23771d
$L_237732:
        db 0C7h, 040h, 06Ch, 016h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1116
$L_237739:
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
$L_23773c:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg4 ENDS

seg28 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_RTG@12 @ 0x0023773F
PUBLIC _itrp_RTG@12
_itrp_RTG@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 003h, 000h   ; mov word ptr [eax + 0x1c], 3
        db 00Fh, 0B7h, 089h, 080h, 000h, 000h, 000h   ; movzx ecx, word ptr [ecx + 0x80]
        db 0C1h, 0E1h, 005h   ; shl ecx, 5
        db 08Bh, 089h   ; mov ecx, dword ptr [ecx + 0x3ecf0c]
        dd _unk_3ECF0C
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RTHG@12 @ 0x00237769
PUBLIC _itrp_RTHG@12
_itrp_RTHG@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 004h, 000h   ; mov word ptr [eax + 0x1c], 4
        db 00Fh, 0B7h, 091h, 080h, 000h, 000h, 000h   ; movzx edx, word ptr [ecx + 0x80]
        db 0C1h, 0E2h, 005h   ; shl edx, 5
        db 08Bh, 092h   ; mov edx, dword ptr [edx + 0x3ecf10]
        dd _unk_3ECF10
        db 089h, 050h, 018h   ; mov dword ptr [eax + 0x18], edx
        db 066h, 083h, 061h, 068h, 000h   ; and word ptr [ecx + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RTDG@12 @ 0x00237798
PUBLIC _itrp_RTDG@12
_itrp_RTDG@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 066h, 083h, 060h, 078h, 000h   ; and word ptr [eax + 0x78], 0
        db 00Fh, 0B7h, 091h, 080h, 000h, 000h, 000h   ; movzx edx, word ptr [ecx + 0x80]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 0C1h, 0E2h, 005h   ; shl edx, 5
        db 08Bh, 092h   ; mov edx, dword ptr [edx + 0x3ecf00]
        dd _unk_3ECF00
        db 089h, 050h, 018h   ; mov dword ptr [eax + 0x18], edx
        db 066h, 083h, 061h, 068h, 000h   ; and word ptr [ecx + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_ROFF@12 @ 0x002377C6
PUBLIC _itrp_ROFF@12
_itrp_ROFF@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 005h, 000h   ; mov word ptr [eax + 0x1c], 5
        db 00Fh, 0B7h, 091h, 080h, 000h, 000h, 000h   ; movzx edx, word ptr [ecx + 0x80]
        db 0C1h, 0E2h, 005h   ; shl edx, 5
        db 08Bh, 092h   ; mov edx, dword ptr [edx + 0x3ecf14]
        dd _unk_3ECF14
        db 089h, 050h, 018h   ; mov dword ptr [eax + 0x18], edx
        db 066h, 083h, 061h, 068h, 000h   ; and word ptr [ecx + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RDTG@12 @ 0x002377F5
PUBLIC _itrp_RDTG@12
_itrp_RDTG@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 001h, 000h   ; mov word ptr [eax + 0x1c], 1
        db 00Fh, 0B7h, 091h, 080h, 000h, 000h, 000h   ; movzx edx, word ptr [ecx + 0x80]
        db 0C1h, 0E2h, 005h   ; shl edx, 5
        db 08Bh, 092h   ; mov edx, dword ptr [edx + 0x3ecf04]
        dd _unk_3ECF04
        db 089h, 050h, 018h   ; mov dword ptr [eax + 0x18], edx
        db 066h, 083h, 061h, 068h, 000h   ; and word ptr [ecx + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RUTG@12 @ 0x00237824
PUBLIC _itrp_RUTG@12
_itrp_RUTG@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 002h, 000h   ; mov word ptr [eax + 0x1c], 2
        db 00Fh, 0B7h, 091h, 080h, 000h, 000h, 000h   ; movzx edx, word ptr [ecx + 0x80]
        db 0C1h, 0E2h, 005h   ; shl edx, 5
        db 08Bh, 092h   ; mov edx, dword ptr [edx + 0x3ecf08]
        dd _unk_3ECF08
        db 089h, 050h, 018h   ; mov dword ptr [eax + 0x18], edx
        db 066h, 083h, 061h, 068h, 000h   ; and word ptr [ecx + 0x68], 0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg28 ENDS

seg5 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_RAW@12 @ 0x00237948
PUBLIC _itrp_RAW@12
_itrp_RAW@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 057h   ; push edi
        db 08Bh, 078h, 024h   ; mov edi, dword ptr [eax + 0x24]
        db 080h, 0BFh, 025h, 001h, 000h, 000h, 002h   ; cmp byte ptr [edi + 0x125], 2
        db 074h, 00Ch   ; je 0x237965
        db 0C7h, 040h, 06Ch, 00Dh, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x110d
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 043h   ; jmp 0x2379a8
$L_237965:
        db 08Bh, 048h, 020h   ; mov ecx, dword ptr [eax + 0x20]
        db 00Fh, 0BFh, 051h, 060h   ; movsx edx, word ptr [ecx + 0x60]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 071h, 040h   ; mov esi, dword ptr [ecx + 0x40]
        db 08Bh, 049h, 058h   ; mov ecx, dword ptr [ecx + 0x58]
        db 00Fh, 0BFh, 04Ch, 051h, 0FEh   ; movsx ecx, word ptr [ecx + edx*2 - 2]
        db 08Bh, 050h, 018h   ; mov edx, dword ptr [eax + 0x18]
        db 08Dh, 05Ah, 004h   ; lea ebx, [edx + 4]
        db 041h   ; inc ecx
        db 03Bh, 09Fh, 05Ch, 001h, 000h, 000h   ; cmp ebx, dword ptr [edi + 0x15c]
        db 076h, 00Ch   ; jbe 0x237994
        db 0C7h, 040h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1111
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 012h   ; jmp 0x2379a6
$L_237994:
        db 08Dh, 00Ch, 08Eh   ; lea ecx, [esi + ecx*4]
        db 08Bh, 071h, 004h   ; mov esi, dword ptr [ecx + 4]
        db 02Bh, 031h   ; sub esi, dword ptr [ecx]
        db 089h, 032h   ; mov dword ptr [edx], esi
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
$L_2379a6:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
$L_2379a8:
        db 05Fh   ; pop edi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg5 ENDS

seg29 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_DUP@12 @ 0x002379AC
PUBLIC _itrp_DUP@12
_itrp_DUP@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 073h, 009h   ; jae 0x2379c7
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 0EBh, 017h   ; jmp 0x2379de
$L_2379c7:
        db 08Bh, 071h, 0FCh   ; mov esi, dword ptr [ecx - 4]
        db 057h   ; push edi
        db 08Dh, 079h, 004h   ; lea edi, [ecx + 4]
        db 03Bh, 0BAh, 05Ch, 001h, 000h, 000h   ; cmp edi, dword ptr [edx + 0x15c]
        db 05Fh   ; pop edi
        db 076h, 00Ch   ; jbe 0x2379e3
        db 0C7h, 040h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1111
$L_2379de:
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Ah   ; jmp 0x2379ed
$L_2379e3:
        db 089h, 031h   ; mov dword ptr [ecx], esi
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_2379ed:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg29 ENDS

seg6 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SWAP@12 @ 0x00237A04
PUBLIC _itrp_SWAP@12
_itrp_SWAP@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x237a23
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 010h   ; jmp 0x237a33
$L_237a23:
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 08Bh, 050h, 0F8h   ; mov edx, dword ptr [eax - 8]
        db 089h, 050h, 0FCh   ; mov dword ptr [eax - 4], edx
        db 089h, 048h, 0F8h   ; mov dword ptr [eax - 8], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237a33:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg6 ENDS

seg30 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_DEPTH@12 @ 0x00237A36
PUBLIC _itrp_DEPTH@12
_itrp_DEPTH@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 051h, 018h   ; mov edx, dword ptr [ecx + 0x18]
        db 056h   ; push esi
        db 08Bh, 071h, 024h   ; mov esi, dword ptr [ecx + 0x24]
        db 08Bh, 0C2h   ; mov eax, edx
        db 02Bh, 006h   ; sub eax, dword ptr [esi]
        db 057h   ; push edi
        db 08Dh, 07Ah, 004h   ; lea edi, [edx + 4]
        db 0C1h, 0F8h, 002h   ; sar eax, 2
        db 03Bh, 0BEh, 05Ch, 001h, 000h, 000h   ; cmp edi, dword ptr [esi + 0x15c]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 076h, 00Ch   ; jbe 0x237a62
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1111
        db 0EBh, 00Ah   ; jmp 0x237a6c
$L_237a62:
        db 089h, 002h   ; mov dword ptr [edx], eax
        db 083h, 041h, 018h, 004h   ; add dword ptr [ecx + 0x18], 4
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237a6c:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_CINDEX@12 @ 0x00237A6F
PUBLIC _itrp_CINDEX@12
_itrp_CINDEX@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 056h   ; push esi
        db 08Bh, 071h, 024h   ; mov esi, dword ptr [ecx + 0x24]
        db 057h   ; push edi
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 08Dh, 050h, 0FCh   ; lea edx, [eax - 4]
        db 03Bh, 0D7h   ; cmp edx, edi
        db 072h, 014h   ; jb 0x237a98
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 053h   ; push ebx
        db 08Bh, 0DAh   ; mov ebx, edx
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 08Bh, 0D0h   ; mov edx, eax
        db 02Bh, 0D3h   ; sub edx, ebx
        db 03Bh, 0D7h   ; cmp edx, edi
        db 05Bh   ; pop ebx
        db 073h, 009h   ; jae 0x237aa1
$L_237a98:
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 019h   ; jmp 0x237aba
$L_237aa1:
        db 03Bh, 096h, 05Ch, 001h, 000h, 000h   ; cmp edx, dword ptr [esi + 0x15c]
        db 073h, 00Ah   ; jae 0x237ab3
        db 08Bh, 00Ah   ; mov ecx, dword ptr [edx]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 0EBh, 00Ah   ; jmp 0x237abd
$L_237ab3:
        db 0C7h, 041h, 06Ch, 013h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1113
$L_237aba:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
$L_237abd:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_MINDEX@12 @ 0x00237AC2
PUBLIC _itrp_MINDEX@12
_itrp_MINDEX@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Bh, 042h, 018h   ; mov eax, dword ptr [edx + 0x18]
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Ah, 024h   ; mov edi, dword ptr [edx + 0x24]
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 0F1h   ; cmp esi, ecx
        db 073h, 00Ch   ; jae 0x237ae5
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0EBh, 057h   ; jmp 0x237b3c
$L_237ae5:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 053h   ; push ebx
        db 08Bh, 0DEh   ; mov ebx, esi
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 08Bh, 0C8h   ; mov ecx, eax
        db 02Bh, 0CBh   ; sub ecx, ebx
        db 03Bh, 00Fh   ; cmp ecx, dword ptr [edi]
        db 073h, 009h   ; jae 0x237b01
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0EBh, 037h   ; jmp 0x237b38
$L_237b01:
        db 03Bh, 08Fh, 05Ch, 001h, 000h, 000h   ; cmp ecx, dword ptr [edi + 0x15c]
        db 073h, 028h   ; jae 0x237b31
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 039h   ; mov edi, dword ptr [ecx]
        db 089h, 07Dh, 008h   ; mov dword ptr [ebp + 8], edi
        db 07Eh, 00Fh   ; jle 0x237b21
$L_237b12:
        db 04Eh   ; dec esi
        db 08Dh, 079h, 004h   ; lea edi, [ecx + 4]
        db 08Bh, 01Fh   ; mov ebx, dword ptr [edi]
        db 089h, 019h   ; mov dword ptr [ecx], ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        db 075h, 0F4h   ; jne 0x237b12
        db 083h, 0E8h, 004h   ; sub eax, 4
$L_237b21:
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 083h, 0C0h, 004h   ; add eax, 4
        db 089h, 042h, 018h   ; mov dword ptr [edx + 0x18], eax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 00Ah   ; jmp 0x237b3b
$L_237b31:
        db 0C7h, 042h, 06Ch, 013h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1113
$L_237b38:
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
$L_237b3b:
        db 05Bh   ; pop ebx
$L_237b3c:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_ROTATE@12 @ 0x00237B42
PUBLIC _itrp_ROTATE@12
_itrp_ROTATE@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F4h   ; lea esi, [eax - 0xc]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x237b61
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 01Ah   ; jmp 0x237b7b
$L_237b61:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 010h   ; mov dword ptr [eax], edx
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_237b7b:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_MDAP@12 @ 0x00237B7E
PUBLIC _itrp_MDAP@12
_itrp_MDAP@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Bh, 01Eh   ; mov ebx, dword ptr [esi]
        db 08Dh, 050h, 0FCh   ; lea edx, [eax - 4]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 073h, 00Ch   ; jae 0x237ba4
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 02Bh   ; jmp 0x237bcf
$L_237ba4:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 039h, 05Eh, 020h   ; cmp dword ptr [esi + 0x20], ebx
        db 057h   ; push edi
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 075h, 023h   ; jne 0x237bd5
        db 08Bh, 081h, 030h, 001h, 000h, 000h   ; mov eax, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 040h, 010h   ; movzx eax, word ptr [eax + 0x10]
        db 03Bh, 0F8h   ; cmp edi, eax
$L_237bbe:
        db 07Dh, 004h   ; jge 0x237bc4
        db 085h, 0FFh   ; test edi, edi
        db 07Dh, 019h   ; jge 0x237bdd
$L_237bc4:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_237bce:
        db 05Fh   ; pop edi
$L_237bcf:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_237bd5:
        db 03Bh, 0B9h, 060h, 001h, 000h, 000h   ; cmp edi, dword ptr [ecx + 0x160]
        db 0EBh, 0E1h   ; jmp 0x237bbe
$L_237bdd:
        db 0F6h, 045h, 010h, 001h   ; test byte ptr [ebp + 0x10], 1
        db 089h, 07Eh, 02Ch   ; mov dword ptr [esi + 0x2c], edi
        db 089h, 07Eh, 030h   ; mov dword ptr [esi + 0x30], edi
        db 074h, 025h   ; je 0x237c0e
        db 08Bh, 043h, 004h   ; mov eax, dword ptr [ebx + 4]
        db 0FFh, 034h, 0B8h   ; push dword ptr [eax + edi*4]
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 0FFh, 034h, 0B8h   ; push dword ptr [eax + edi*4]
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 0FFh, 071h, 014h   ; push dword ptr [ecx + 0x14]
        db 089h, 045h, 010h   ; mov dword ptr [ebp + 0x10], eax
        db 050h   ; push eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 056h   ; push esi
        db 0FFh, 050h, 074h   ; call dword ptr [eax + 0x74]
        db 02Bh, 045h, 010h   ; sub eax, dword ptr [ebp + 0x10]
        db 0EBh, 002h   ; jmp 0x237c10
$L_237c0e:
        db 033h, 0C0h   ; xor eax, eax
$L_237c10:
        db 050h   ; push eax
        db 057h   ; push edi
        db 053h   ; push ebx
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 0B2h   ; jmp 0x237bce
; // match: _itrp_MIAP@12 @ 0x00237C1C
PUBLIC _itrp_MIAP@12
_itrp_MIAP@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 057h   ; push edi
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 089h, 04Dh, 0F8h   ; mov dword ptr [ebp - 8], ecx
        db 073h, 00Ch   ; jae 0x237c45
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0E9h, 004h, 001h, 000h, 000h   ; jmp 0x237d49
$L_237c45:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 00Fh, 0B7h, 089h, 034h, 001h, 000h, 000h   ; movzx ecx, word ptr [ecx + 0x134]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 00Fh, 08Dh, 0E6h, 000h, 000h, 000h   ; jge 0x237d42
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 0DEh, 000h, 000h, 000h   ; jl 0x237d42
        db 050h   ; push eax
        db 056h   ; push esi
        db 0FFh, 056h, 058h   ; call dword ptr [esi + 0x58]
        db 083h, 046h, 018h, 0FCh   ; add dword ptr [esi + 0x18], -4
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 089h, 05Dh, 0FCh   ; mov dword ptr [ebp - 4], ebx
        db 075h, 01Eh   ; jne 0x237ca0
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0D9h   ; cmp ebx, ecx
$L_237c8e:
        db 07Dh, 004h   ; jge 0x237c94
        db 085h, 0DBh   ; test ebx, ebx
        db 07Dh, 014h   ; jge 0x237ca8
$L_237c94:
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
        db 0E9h, 0A9h, 000h, 000h, 000h   ; jmp 0x237d49
$L_237ca0:
        db 03Bh, 099h, 060h, 001h, 000h, 000h   ; cmp ebx, dword ptr [ecx + 0x160]
        db 0EBh, 0E6h   ; jmp 0x237c8e
$L_237ca8:
        db 03Bh, 0F8h   ; cmp edi, eax
        db 089h, 05Eh, 02Ch   ; mov dword ptr [esi + 0x2c], ebx
        db 089h, 05Eh, 030h   ; mov dword ptr [esi + 0x30], ebx
        db 075h, 046h   ; jne 0x237cf8
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 046h, 00Ch   ; mov ax, word ptr [esi + 0xc]
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call _ShortFracMul@8   ; 0x23590D
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 089h, 004h, 00Bh   ; mov dword ptr [ebx + ecx], eax
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 004h, 003h   ; mov eax, dword ptr [ebx + eax]
        db 08Bh, 04Fh, 008h   ; mov ecx, dword ptr [edi + 8]
        db 089h, 004h, 00Bh   ; mov dword ptr [ebx + ecx], eax
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 046h, 00Eh   ; mov ax, word ptr [esi + 0xe]
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call _ShortFracMul@8   ; 0x23590D
        db 08Bh, 04Fh, 004h   ; mov ecx, dword ptr [edi + 4]
        db 089h, 004h, 00Bh   ; mov dword ptr [ebx + ecx], eax
        db 08Bh, 047h, 004h   ; mov eax, dword ptr [edi + 4]
        db 08Bh, 004h, 003h   ; mov eax, dword ptr [ebx + eax]
        db 08Bh, 04Fh, 00Ch   ; mov ecx, dword ptr [edi + 0xc]
        db 089h, 004h, 00Bh   ; mov dword ptr [ebx + ecx], eax
        db 08Bh, 05Dh, 0FCh   ; mov ebx, dword ptr [ebp - 4]
$L_237cf8:
        db 08Bh, 047h, 004h   ; mov eax, dword ptr [edi + 4]
        db 0FFh, 034h, 098h   ; push dword ptr [eax + ebx*4]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 0FFh, 034h, 098h   ; push dword ptr [eax + ebx*4]
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
        db 0F6h, 045h, 010h, 001h   ; test byte ptr [ebp + 0x10], 1
        db 08Bh, 0D0h   ; mov edx, eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 089h, 055h, 0FCh   ; mov dword ptr [ebp - 4], edx
        db 074h, 01Eh   ; je 0x237d33
        db 02Bh, 0C2h   ; sub eax, edx
        db 079h, 002h   ; jns 0x237d1b
        db 0F7h, 0D8h   ; neg eax
$L_237d1b:
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 03Bh, 041h, 05Ch   ; cmp eax, dword ptr [ecx + 0x5c]
        db 07Eh, 003h   ; jle 0x237d26
        db 089h, 055h, 008h   ; mov dword ptr [ebp + 8], edx
$L_237d26:
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 0FFh, 070h, 014h   ; push dword ptr [eax + 0x14]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 056h   ; push esi
        db 0FFh, 051h, 074h   ; call dword ptr [ecx + 0x74]
$L_237d33:
        db 02Bh, 045h, 0FCh   ; sub eax, dword ptr [ebp - 4]
        db 050h   ; push eax
        db 053h   ; push ebx
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 00Ah   ; jmp 0x237d4c
$L_237d42:
        db 0C7h, 046h, 06Ch, 01Bh, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x111b
$L_237d49:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_237d4c:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg30 ENDS

seg7 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SHP@12 @ 0x002382A4
PUBLIC _itrp_SHP@12
_itrp_SHP@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 0F6h, 045h, 010h, 001h   ; test byte ptr [ebp + 0x10], 1
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 074h, 00Fh   ; je 0x2382c7
        db 03Bh, 006h   ; cmp eax, dword ptr [esi]
        db 08Bh, 046h, 030h   ; mov eax, dword ptr [esi + 0x30]
        db 074h, 010h   ; je 0x2382cf
$L_2382bf:
        db 03Bh, 081h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [ecx + 0x160]
        db 0EBh, 014h   ; jmp 0x2382db
$L_2382c7:
        db 03Bh, 046h, 004h   ; cmp eax, dword ptr [esi + 4]
        db 08Bh, 046h, 034h   ; mov eax, dword ptr [esi + 0x34]
        db 075h, 0F0h   ; jne 0x2382bf
$L_2382cf:
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0C1h   ; cmp eax, ecx
$L_2382db:
        db 07Dh, 04Dh   ; jge 0x23832a
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 049h   ; jl 0x23832a
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Dh, 045h, 010h   ; lea eax, [ebp + 0x10]
        db 050h   ; push eax
        db 056h   ; push esi
        call _itrp_SH_Common@20   ; 0x238080
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 0B8h, 0FFh, 0FFh, 0FFh, 03Fh   ; mov eax, 0x3fffffff
        db 02Bh, 046h, 03Ch   ; sub eax, dword ptr [esi + 0x3c]
        db 08Dh, 004h, 081h   ; lea eax, [ecx + eax*4]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 03Bh, 001h   ; cmp eax, dword ptr [ecx]
        db 073h, 009h   ; jae 0x238314
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 01Dh   ; jmp 0x238331
$L_238314:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 06Ah, 000h   ; push 0
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 056h   ; push esi
        call _itrp_SHP_Common@24   ; 0x23814D
        db 0EBh, 00Ah   ; jmp 0x238334
$L_23832a:
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_238331:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_238334:
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg7 ENDS

seg31 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SHC@12 @ 0x00238339
PUBLIC _itrp_SHC@12
_itrp_SHC@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 010h   ; sub esp, 0x10
        db 0F6h, 045h, 010h, 001h   ; test byte ptr [ebp + 0x10], 1
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 057h   ; push edi
        db 074h, 00Fh   ; je 0x238360
        db 03Bh, 006h   ; cmp eax, dword ptr [esi]
        db 08Bh, 046h, 030h   ; mov eax, dword ptr [esi + 0x30]
        db 074h, 010h   ; je 0x238368
$L_238358:
        db 03Bh, 081h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [ecx + 0x160]
        db 0EBh, 014h   ; jmp 0x238374
$L_238360:
        db 03Bh, 046h, 004h   ; cmp eax, dword ptr [esi + 4]
        db 08Bh, 046h, 034h   ; mov eax, dword ptr [esi + 0x34]
        db 075h, 0F0h   ; jne 0x238358
$L_238368:
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0C1h   ; cmp eax, ecx
$L_238374:
        db 00Fh, 08Dh, 0FEh, 000h, 000h, 000h   ; jge 0x238478
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 0F6h, 000h, 000h, 000h   ; jl 0x238478
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 08Dh, 045h, 010h   ; lea eax, [ebp + 0x10]
        db 050h   ; push eax
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 056h   ; push esi
        call _itrp_SH_Common@20   ; 0x238080
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 08Bh, 0D0h   ; mov edx, eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Dh, 079h, 0FCh   ; lea edi, [ecx - 4]
        db 03Bh, 038h   ; cmp edi, dword ptr [eax]
        db 089h, 055h, 0FCh   ; mov dword ptr [ebp - 4], edx
        db 073h, 00Ch   ; jae 0x2383bb
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0E9h, 0C4h, 000h, 000h, 000h   ; jmp 0x23847f
$L_2383bb:
        db 08Bh, 07Dh, 010h   ; mov edi, dword ptr [ebp + 0x10]
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 04Eh, 018h   ; mov dword ptr [esi + 0x18], ecx
        db 080h, 0B8h, 025h, 001h, 000h, 000h, 002h   ; cmp byte ptr [eax + 0x125], 2
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 075h, 033h   ; jne 0x238402
        db 066h, 08Bh, 080h, 06Ch, 001h, 000h, 000h   ; mov ax, word ptr [eax + 0x16c]
        db 0A8h, 001h   ; test al, 1
        db 074h, 028h   ; je 0x238402
        db 0A8h, 002h   ; test al, 2
        db 074h, 024h   ; je 0x238402
        db 0A8h, 004h   ; test al, 4
        db 075h, 020h   ; jne 0x238402
        db 083h, 07Ah, 030h, 000h   ; cmp dword ptr [edx + 0x30], 0
        db 075h, 01Ah   ; jne 0x238402
        db 052h   ; push edx
        db 056h   ; push esi
        call _ExecutePhaseControl@8   ; 0x235FCB
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 049h, 034h   ; mov ecx, dword ptr [ecx + 0x34]
        db 08Dh, 004h, 07Fh   ; lea eax, [edi + edi*2]
        db 08Bh, 044h, 081h, 008h   ; mov eax, dword ptr [ecx + eax*4 + 8]
        db 003h, 045h, 008h   ; add eax, dword ptr [ebp + 8]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
$L_238402:
        db 08Bh, 07Eh, 024h   ; mov edi, dword ptr [esi + 0x24]
        db 08Ah, 087h, 025h, 001h, 000h, 000h   ; mov al, byte ptr [edi + 0x125]
        db 03Ch, 002h   ; cmp al, 2
        db 074h, 015h   ; je 0x238424
        db 084h, 0C0h   ; test al, al
        db 075h, 008h   ; jne 0x23841b
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 03Bh, 046h, 008h   ; cmp eax, dword ptr [esi + 8]
        db 074h, 009h   ; je 0x238424
$L_23841b:
        db 0C7h, 046h, 06Ch, 01Ch, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x111c
        db 0EBh, 05Bh   ; jmp 0x23847f
$L_238424:
        db 085h, 0DBh   ; test ebx, ebx
        db 00Fh, 08Ch, 0B0h, 000h, 000h, 000h   ; jl 0x2384dc
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 00Fh, 0BFh, 048h, 028h   ; movsx ecx, word ptr [eax + 0x28]
        db 03Bh, 0D9h   ; cmp ebx, ecx
        db 00Fh, 08Dh, 0A1h, 000h, 000h, 000h   ; jge 0x2384dc
        db 066h, 08Bh, 04Eh, 010h   ; mov cx, word ptr [esi + 0x10]
        db 066h, 089h, 04Dh, 008h   ; mov word ptr [ebp + 8], cx
        db 066h, 08Bh, 04Eh, 012h   ; mov cx, word ptr [esi + 0x12]
        db 08Dh, 014h, 01Bh   ; lea edx, [ebx + ebx]
        db 08Bh, 058h, 020h   ; mov ebx, dword ptr [eax + 0x20]
        db 066h, 089h, 04Dh, 0F4h   ; mov word ptr [ebp - 0xc], cx
        db 08Bh, 048h, 01Ch   ; mov ecx, dword ptr [eax + 0x1c]
        db 00Fh, 0BFh, 00Ch, 011h   ; movsx ecx, word ptr [ecx + edx]
        db 00Fh, 0BFh, 014h, 013h   ; movsx edx, word ptr [ebx + edx]
        db 02Bh, 0D1h   ; sub edx, ecx
        db 039h, 046h, 020h   ; cmp dword ptr [esi + 0x20], eax
        db 08Dh, 01Ch, 00Ah   ; lea ebx, [edx + ecx]
        db 075h, 023h   ; jne 0x238489
        db 08Bh, 0BFh, 030h, 001h, 000h, 000h   ; mov edi, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 07Fh, 010h   ; movzx edi, word ptr [edi + 0x10]
        db 03Bh, 0DFh   ; cmp ebx, edi
$L_238472:
        db 07Dh, 004h   ; jge 0x238478
        db 085h, 0DBh   ; test ebx, ebx
        db 07Dh, 019h   ; jge 0x238491
$L_238478:
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_23847f:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_238482:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_238489:
        db 03Bh, 09Fh, 060h, 001h, 000h, 000h   ; cmp ebx, dword ptr [edi + 0x160]
        db 0EBh, 0E1h   ; jmp 0x238472
$L_238491:
        db 085h, 0D2h   ; test edx, edx
        db 07Ch, 042h   ; jl 0x2384d7
        db 042h   ; inc edx
$L_238496:
        db 03Bh, 04Dh, 010h   ; cmp ecx, dword ptr [ebp + 0x10]
        db 075h, 005h   ; jne 0x2384a0
        db 039h, 045h, 0FCh   ; cmp dword ptr [ebp - 4], eax
        db 074h, 033h   ; je 0x2384d3
$L_2384a0:
        db 066h, 083h, 07Dh, 008h, 000h   ; cmp word ptr [ebp + 8], 0
        db 074h, 012h   ; je 0x2384b9
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 08Bh, 07Dh, 0F8h   ; mov edi, dword ptr [ebp - 8]
        db 08Dh, 034h, 08Eh   ; lea esi, [esi + ecx*4]
        db 001h, 03Eh   ; add dword ptr [esi], edi
        db 08Bh, 070h, 024h   ; mov esi, dword ptr [eax + 0x24]
        db 003h, 0F1h   ; add esi, ecx
        db 080h, 00Eh, 001h   ; or byte ptr [esi], 1
$L_2384b9:
        db 066h, 083h, 07Dh, 0F4h, 000h   ; cmp word ptr [ebp - 0xc], 0
        db 074h, 013h   ; je 0x2384d3
        db 08Bh, 070h, 004h   ; mov esi, dword ptr [eax + 4]
        db 08Bh, 07Dh, 0F0h   ; mov edi, dword ptr [ebp - 0x10]
        db 08Dh, 034h, 08Eh   ; lea esi, [esi + ecx*4]
        db 001h, 03Eh   ; add dword ptr [esi], edi
        db 08Bh, 070h, 024h   ; mov esi, dword ptr [eax + 0x24]
        db 003h, 0F1h   ; add esi, ecx
        db 080h, 00Eh, 002h   ; or byte ptr [esi], 2
$L_2384d3:
        db 041h   ; inc ecx
        db 04Ah   ; dec edx
        db 075h, 0BFh   ; jne 0x238496
$L_2384d7:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 0A6h   ; jmp 0x238482
$L_2384dc:
        db 0C7h, 046h, 06Ch, 01Ah, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x111a
        db 0EBh, 09Ah   ; jmp 0x23847f
; // match: _itrp_SHE@12 @ 0x002384E5
PUBLIC _itrp_SHE@12
_itrp_SHE@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 014h   ; sub esp, 0x14
        db 0F6h, 045h, 010h, 001h   ; test byte ptr [ebp + 0x10], 1
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 057h   ; push edi
        db 074h, 00Fh   ; je 0x23850c
        db 03Bh, 006h   ; cmp eax, dword ptr [esi]
        db 08Bh, 046h, 030h   ; mov eax, dword ptr [esi + 0x30]
        db 074h, 010h   ; je 0x238514
$L_238504:
        db 03Bh, 081h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [ecx + 0x160]
        db 0EBh, 014h   ; jmp 0x238520
$L_23850c:
        db 03Bh, 046h, 004h   ; cmp eax, dword ptr [esi + 4]
        db 08Bh, 046h, 034h   ; mov eax, dword ptr [esi + 0x34]
        db 075h, 0F0h   ; jne 0x238504
$L_238514:
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0C1h   ; cmp eax, ecx
$L_238520:
        db 00Fh, 08Dh, 0A5h, 000h, 000h, 000h   ; jge 0x2385cb
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 09Dh, 000h, 000h, 000h   ; jl 0x2385cb
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 056h   ; push esi
        call _itrp_SH_Common@20   ; 0x238080
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 08Bh, 07Eh, 024h   ; mov edi, dword ptr [esi + 0x24]
        db 089h, 045h, 010h   ; mov dword ptr [ebp + 0x10], eax
        db 08Dh, 041h, 0FCh   ; lea eax, [ecx - 4]
        db 03Bh, 007h   ; cmp eax, dword ptr [edi]
        db 073h, 009h   ; jae 0x23855c
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 076h   ; jmp 0x2385d2
$L_23855c:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 04Eh, 018h   ; mov dword ptr [esi + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0F9h, 002h   ; cmp ecx, 2
        db 00Fh, 08Dh, 02Bh, 001h, 000h, 000h   ; jge 0x238698
        db 085h, 0C9h   ; test ecx, ecx
        db 00Fh, 08Ch, 023h, 001h, 000h, 000h   ; jl 0x238698
        db 08Ah, 087h, 025h, 001h, 000h, 000h   ; mov al, byte ptr [edi + 0x125]
        db 03Ch, 002h   ; cmp al, 2
        db 074h, 01Bh   ; je 0x23859a
        db 084h, 0C0h   ; test al, al
        db 075h, 00Eh   ; jne 0x238591
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 06Bh, 0D2h, 038h   ; imul edx, edx, 0x38
        db 003h, 0D0h   ; add edx, eax
        db 03Bh, 0C2h   ; cmp eax, edx
        db 074h, 009h   ; je 0x23859a
$L_238591:
        db 0C7h, 046h, 06Ch, 01Ch, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x111c
        db 0EBh, 038h   ; jmp 0x2385d2
$L_23859a:
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 06Bh, 0D2h, 038h   ; imul edx, edx, 0x38
        db 08Dh, 00Ch, 002h   ; lea ecx, [edx + eax]
        db 039h, 04Eh, 020h   ; cmp dword ptr [esi + 0x20], ecx
        db 00Fh, 0BFh, 041h, 028h   ; movsx eax, word ptr [ecx + 0x28]
        db 08Bh, 059h, 020h   ; mov ebx, dword ptr [ecx + 0x20]
        db 00Fh, 0BFh, 044h, 043h, 0FEh   ; movsx eax, word ptr [ebx + eax*2 - 2]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 075h, 023h   ; jne 0x2385dc
        db 08Bh, 09Fh, 030h, 001h, 000h, 000h   ; mov ebx, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 05Bh, 010h   ; movzx ebx, word ptr [ebx + 0x10]
        db 03Bh, 0C3h   ; cmp eax, ebx
$L_2385c5:
        db 07Dh, 004h   ; jge 0x2385cb
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 019h   ; jge 0x2385e4
$L_2385cb:
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_2385d2:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_2385d5:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_2385dc:
        db 03Bh, 087h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [edi + 0x160]
        db 0EBh, 0E1h   ; jmp 0x2385c5
$L_2385e4:
        db 039h, 04Eh, 020h   ; cmp dword ptr [esi + 0x20], ecx
        db 08Bh, 041h, 01Ch   ; mov eax, dword ptr [ecx + 0x1c]
        db 00Fh, 0BFh, 000h   ; movsx eax, word ptr [eax]
        db 075h, 042h   ; jne 0x238631
        db 08Bh, 0BFh, 030h, 001h, 000h, 000h   ; mov edi, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 07Fh, 010h   ; movzx edi, word ptr [edi + 0x10]
        db 03Bh, 0C7h   ; cmp eax, edi
$L_2385fb:
        db 07Dh, 0CEh   ; jge 0x2385cb
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 0CAh   ; jl 0x2385cb
        db 039h, 04Dh, 010h   ; cmp dword ptr [ebp + 0x10], ecx
        db 075h, 017h   ; jne 0x23861d
        db 08Bh, 07Dh, 0FCh   ; mov edi, dword ptr [ebp - 4]
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 08Bh, 01Ch, 01Fh   ; mov ebx, dword ptr [edi + ebx]
        db 089h, 05Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ebx
        db 08Bh, 059h, 004h   ; mov ebx, dword ptr [ecx + 4]
        db 08Bh, 03Ch, 01Fh   ; mov edi, dword ptr [edi + ebx]
        db 089h, 07Dh, 0ECh   ; mov dword ptr [ebp - 0x14], edi
$L_23861d:
        db 066h, 083h, 07Eh, 010h, 000h   ; cmp word ptr [esi + 0x10], 0
        db 074h, 021h   ; je 0x238645
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 08Dh, 03Ch, 081h   ; lea edi, [ecx + eax*4]
        db 08Dh, 00Ch, 099h   ; lea ecx, [ecx + ebx*4]
        db 0EBh, 010h   ; jmp 0x238641
$L_238631:
        db 03Bh, 087h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [edi + 0x160]
        db 0EBh, 0C2h   ; jmp 0x2385fb
$L_238639:
        db 08Bh, 05Dh, 0F8h   ; mov ebx, dword ptr [ebp - 8]
        db 001h, 01Fh   ; add dword ptr [edi], ebx
        db 083h, 0C7h, 004h   ; add edi, 4
$L_238641:
        db 03Bh, 0F9h   ; cmp edi, ecx
        db 076h, 0F4h   ; jbe 0x238639
$L_238645:
        db 066h, 083h, 07Eh, 012h, 000h   ; cmp word ptr [esi + 0x12], 0
        db 074h, 01Eh   ; je 0x23866a
        db 08Bh, 04Eh, 020h   ; mov ecx, dword ptr [esi + 0x20]
        db 08Bh, 04Ch, 011h, 004h   ; mov ecx, dword ptr [ecx + edx + 4]
        db 08Dh, 03Ch, 081h   ; lea edi, [ecx + eax*4]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Dh, 00Ch, 081h   ; lea ecx, [ecx + eax*4]
        db 0EBh, 008h   ; jmp 0x238666
$L_23865e:
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 001h, 007h   ; add dword ptr [edi], eax
        db 083h, 0C7h, 004h   ; add edi, 4
$L_238666:
        db 03Bh, 0F9h   ; cmp edi, ecx
        db 076h, 0F4h   ; jbe 0x23865e
$L_23866a:
        db 08Bh, 046h, 020h   ; mov eax, dword ptr [esi + 0x20]
        db 08Dh, 00Ch, 010h   ; lea ecx, [eax + edx]
        db 039h, 04Dh, 010h   ; cmp dword ptr [ebp + 0x10], ecx
        db 075h, 01Bh   ; jne 0x238690
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 08Bh, 07Dh, 0F0h   ; mov edi, dword ptr [ebp - 0x10]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 089h, 03Ch, 008h   ; mov dword ptr [eax + ecx], edi
        db 08Bh, 04Eh, 020h   ; mov ecx, dword ptr [esi + 0x20]
        db 08Bh, 04Ch, 011h, 004h   ; mov ecx, dword ptr [ecx + edx + 4]
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 089h, 014h, 008h   ; mov dword ptr [eax + ecx], edx
$L_238690:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0E9h, 03Dh, 0FFh, 0FFh, 0FFh   ; jmp 0x2385d5
$L_238698:
        db 0C7h, 046h, 06Ch, 016h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1116
        db 0E9h, 02Eh, 0FFh, 0FFh, 0FFh   ; jmp 0x2385d2
; // match: _itrp_SHPIX@12 @ 0x002386A4
PUBLIC _itrp_SHPIX@12
_itrp_SHPIX@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 0B9h, 0FEh, 0FFh, 0FFh, 03Fh   ; mov ecx, 0x3ffffffe
        db 02Bh, 04Eh, 03Ch   ; sub ecx, dword ptr [esi + 0x3c]
        db 08Dh, 00Ch, 088h   ; lea ecx, [eax + ecx*4]
        db 03Bh, 00Ah   ; cmp ecx, dword ptr [edx]
        db 073h, 00Ch   ; jae 0x2386ca
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 04Ah   ; jmp 0x238714
$L_2386ca:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 053h   ; push ebx
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 057h   ; push edi
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 046h, 010h   ; mov ax, word ptr [esi + 0x10]
        db 066h, 085h, 0C0h   ; test ax, ax
        db 074h, 00Bh   ; je 0x2386ea
        db 050h   ; push eax
        db 057h   ; push edi
        call _ShortFracMul@8   ; 0x23590D
        db 08Bh, 0D8h   ; mov ebx, eax
        db 0EBh, 002h   ; jmp 0x2386ec
$L_2386ea:
        db 033h, 0DBh   ; xor ebx, ebx
$L_2386ec:
        db 033h, 0C0h   ; xor eax, eax
        db 066h, 08Bh, 046h, 012h   ; mov ax, word ptr [esi + 0x12]
        db 066h, 085h, 0C0h   ; test ax, ax
        db 074h, 009h   ; je 0x238700
        db 050h   ; push eax
        db 057h   ; push edi
        call _ShortFracMul@8   ; 0x23590D
        db 0EBh, 002h   ; jmp 0x238702
$L_238700:
        db 033h, 0C0h   ; xor eax, eax
$L_238702:
        db 050h   ; push eax
        db 053h   ; push ebx
        db 06Ah, 001h   ; push 1
        db 06Ah, 0FFh   ; push -1
        db 0FFh, 074h, 024h, 024h   ; push dword ptr [esp + 0x24]
        db 056h   ; push esi
        call _itrp_SHP_Common@24   ; 0x23814D
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
$L_238714:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg31 ENDS

seg8 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_ALIGNRP@12 @ 0x00238D50
PUBLIC _itrp_ALIGNRP@12
_itrp_ALIGNRP@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 00Ch   ; sub esp, 0xc
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 08Bh, 049h, 004h   ; mov ecx, dword ptr [ecx + 4]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 08Bh, 014h, 010h   ; mov edx, dword ptr [eax + edx]
        db 08Bh, 004h, 008h   ; mov eax, dword ptr [eax + ecx]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 08Bh, 046h, 03Ch   ; mov eax, dword ptr [esi + 0x3c]
        db 089h, 055h, 0F4h   ; mov dword ptr [ebp - 0xc], edx
        db 08Bh, 056h, 018h   ; mov edx, dword ptr [esi + 0x18]
        db 0B9h, 0FFh, 0FFh, 0FFh, 03Fh   ; mov ecx, 0x3fffffff
        db 02Bh, 0C8h   ; sub ecx, eax
        db 08Dh, 00Ch, 08Ah   ; lea ecx, [edx + ecx*4]
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 03Bh, 00Ah   ; cmp ecx, dword ptr [edx]
        db 073h, 00Fh   ; jae 0x238d9d
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0E9h, 0E5h, 000h, 000h, 000h   ; jmp 0x238e82
$L_238d9d:
        db 085h, 0C0h   ; test eax, eax
        db 057h   ; push edi
        db 00Fh, 08Ch, 0D4h, 000h, 000h, 000h   ; jl 0x238e7a
$L_238da6:
        db 083h, 046h, 018h, 0FCh   ; add dword ptr [esi + 0x18], -4
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 020h   ; mov ecx, dword ptr [esi + 0x20]
        db 03Bh, 0CBh   ; cmp ecx, ebx
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 075h, 00Eh   ; jne 0x238dc7
        db 08Bh, 090h, 030h, 001h, 000h, 000h   ; mov edx, dword ptr [eax + 0x130]
        db 00Fh, 0B7h, 052h, 010h   ; movzx edx, word ptr [edx + 0x10]
        db 03Bh, 0FAh   ; cmp edi, edx
        db 0EBh, 006h   ; jmp 0x238dcd
$L_238dc7:
        db 03Bh, 0B8h, 060h, 001h, 000h, 000h   ; cmp edi, dword ptr [eax + 0x160]
$L_238dcd:
        db 00Fh, 08Dh, 0B5h, 000h, 000h, 000h   ; jge 0x238e88
        db 085h, 0FFh   ; test edi, edi
        db 00Fh, 08Ch, 0ADh, 000h, 000h, 000h   ; jl 0x238e88
        db 03Bh, 0D9h   ; cmp ebx, ecx
        db 074h, 06Eh   ; je 0x238e4d
        db 080h, 0B8h, 025h, 001h, 000h, 000h, 002h   ; cmp byte ptr [eax + 0x125], 2
        db 075h, 065h   ; jne 0x238e4d
        db 066h, 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [esi + 0x80], 0
        db 074h, 05Bh   ; je 0x238e4d
        db 0F6h, 080h, 06Ch, 001h, 000h, 000h, 002h   ; test byte ptr [eax + 0x16c], 2
        db 074h, 052h   ; je 0x238e4d
        db 066h, 08Bh, 08Eh, 082h, 000h, 000h, 000h   ; mov cx, word ptr [esi + 0x82]
        db 066h, 083h, 0F9h, 0FFh   ; cmp cx, -1
        db 074h, 038h   ; je 0x238e40
        db 066h, 08Bh, 086h, 084h, 000h, 000h, 000h   ; mov ax, word ptr [esi + 0x84]
        db 066h, 03Dh, 0FFh, 0FFh   ; cmp ax, 0xffff
        db 074h, 02Bh   ; je 0x238e40
        db 00Fh, 0BFh, 0C0h   ; movsx eax, ax
        db 050h   ; push eax
        db 00Fh, 0BFh, 0C9h   ; movsx ecx, cx
        db 057h   ; push edi
        db 051h   ; push ecx
        db 0FFh, 076h, 004h   ; push dword ptr [esi + 4]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        call _InterAlign@16   ; 0x236205
        db 085h, 0C0h   ; test eax, eax
        db 074h, 010h   ; je 0x238e40
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 057h   ; push edi
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 053h   ; push ebx
        db 056h   ; push esi
        call _AddProportion@20   ; 0x235D10
        db 0EBh, 00Dh   ; jmp 0x238e4d
$L_238e40:
        db 06Ah, 003h   ; push 3
        db 057h   ; push edi
        db 0FFh, 076h, 02Ch   ; push dword ptr [esi + 0x2c]
        db 053h   ; push ebx
        db 056h   ; push esi
        call _AddDistance@20   ; 0x235C12
$L_238e4d:
        db 08Bh, 043h, 004h   ; mov eax, dword ptr [ebx + 4]
        db 08Bh, 004h, 0B8h   ; mov eax, dword ptr [eax + edi*4]
        db 02Bh, 045h, 0F8h   ; sub eax, dword ptr [ebp - 8]
        db 050h   ; push eax
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 08Bh, 004h, 0B8h   ; mov eax, dword ptr [eax + edi*4]
        db 02Bh, 045h, 0F4h   ; sub eax, dword ptr [ebp - 0xc]
        db 050h   ; push eax
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
        db 0F7h, 0D8h   ; neg eax
        db 050h   ; push eax
        db 057h   ; push edi
        db 053h   ; push ebx
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 0FFh, 04Eh, 03Ch   ; dec dword ptr [esi + 0x3c]
        db 083h, 07Eh, 03Ch, 000h   ; cmp dword ptr [esi + 0x3c], 0
        db 00Fh, 08Dh, 02Ch, 0FFh, 0FFh, 0FFh   ; jge 0x238da6
$L_238e7a:
        db 083h, 066h, 03Ch, 000h   ; and dword ptr [esi + 0x3c], 0
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
$L_238e81:
        db 05Fh   ; pop edi
$L_238e82:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_238e88:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
        db 0EBh, 0EDh   ; jmp 0x238e81
seg8 ENDS

seg32 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_ALIGNPTS@12 @ 0x00238E94
PUBLIC _itrp_ALIGNPTS@12
_itrp_ALIGNPTS@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 05Eh, 024h   ; mov ebx, dword ptr [esi + 0x24]
        db 08Dh, 048h, 0F8h   ; lea ecx, [eax - 8]
        db 03Bh, 00Bh   ; cmp ecx, dword ptr [ebx]
        db 073h, 00Ch   ; jae 0x238eb7
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 03Eh   ; jmp 0x238ef5
$L_238eb7:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 07Eh, 020h   ; mov edi, dword ptr [esi + 0x20]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 08Bh, 046h, 004h   ; mov eax, dword ptr [esi + 4]
        db 03Bh, 0F8h   ; cmp edi, eax
        db 089h, 055h, 0F8h   ; mov dword ptr [ebp - 8], edx
        db 075h, 023h   ; jne 0x238efb
        db 08Bh, 08Bh, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ebx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0D1h   ; cmp edx, ecx
$L_238ee4:
        db 07Dh, 004h   ; jge 0x238eea
        db 085h, 0D2h   ; test edx, edx
        db 07Dh, 019h   ; jge 0x238f03
$L_238eea:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_238ef4:
        db 05Fh   ; pop edi
$L_238ef5:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_238efb:
        db 03Bh, 093h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [ebx + 0x160]
        db 0EBh, 0E1h   ; jmp 0x238ee4
$L_238f03:
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 03Bh, 0F9h   ; cmp edi, ecx
        db 075h, 017h   ; jne 0x238f20
        db 08Bh, 0BBh, 030h, 001h, 000h, 000h   ; mov edi, dword ptr [ebx + 0x130]
        db 00Fh, 0B7h, 07Fh, 010h   ; movzx edi, word ptr [edi + 0x10]
        db 039h, 07Dh, 008h   ; cmp dword ptr [ebp + 8], edi
        db 07Dh, 0D2h   ; jge 0x238eea
        db 083h, 07Dh, 008h, 000h   ; cmp dword ptr [ebp + 8], 0
        db 07Dh, 011h   ; jge 0x238f2f
        db 0EBh, 0CAh   ; jmp 0x238eea
$L_238f20:
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 03Bh, 0BBh, 060h, 001h, 000h, 000h   ; cmp edi, dword ptr [ebx + 0x160]
        db 07Dh, 0BFh   ; jge 0x238eea
        db 085h, 0FFh   ; test edi, edi
        db 07Ch, 0BBh   ; jl 0x238eea
$L_238f2f:
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 08Bh, 049h, 004h   ; mov ecx, dword ptr [ecx + 4]
        db 0C1h, 0E2h, 002h   ; shl edx, 2
        db 08Bh, 03Ch, 017h   ; mov edi, dword ptr [edi + edx]
        db 089h, 055h, 0FCh   ; mov dword ptr [ebp - 4], edx
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 03Ch, 093h   ; sub edi, dword ptr [ebx + edx*4]
        db 08Bh, 055h, 0FCh   ; mov edx, dword ptr [ebp - 4]
        db 08Bh, 004h, 010h   ; mov eax, dword ptr [eax + edx]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 004h, 091h   ; sub eax, dword ptr [ecx + edx*4]
        db 08Bh, 04Eh, 04Ch   ; mov ecx, dword ptr [esi + 0x4c]
        db 081h, 0F9h   ; cmp ecx, 0x23a06a
        dd _itrp_EIF@12
        db 074h, 00Fh   ; je 0x238f6e
        db 081h, 0F9h   ; cmp ecx, 0x236796
        dd _sub_236796
        db 074h, 005h   ; je 0x238f6c
        db 050h   ; push eax
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 0D1h   ; call ecx
$L_238f6c:
        db 08Bh, 0F8h   ; mov edi, eax
$L_238f6e:
        db 08Bh, 0DFh   ; mov ebx, edi
        db 0D1h, 0FBh   ; sar ebx, 1
        db 053h   ; push ebx
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0FFh, 036h   ; push dword ptr [esi]
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 02Bh, 0DFh   ; sub ebx, edi
        db 053h   ; push ebx
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 0FFh, 076h, 004h   ; push dword ptr [esi + 4]
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0E9h, 063h, 0FFh, 0FFh, 0FFh   ; jmp 0x238ef4
; // match: _itrp_SANGW@12 @ 0x00238F91
PUBLIC _itrp_SANGW@12
_itrp_SANGW@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x238fb0
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 014h   ; jmp 0x238fc4
$L_238fb0:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 066h, 08Bh, 000h   ; mov ax, word ptr [eax]
        db 066h, 089h, 082h, 08Ch, 000h, 000h, 000h   ; mov word ptr [edx + 0x8c], ax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_238fc4:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg32 ENDS

seg9 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_FLIPRGON@12 @ 0x00239045
PUBLIC _itrp_FLIPRGON@12
_itrp_FLIPRGON@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 08Bh, 04Fh, 018h   ; mov ecx, dword ptr [edi + 0x18]
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Dh, 071h, 0F8h   ; lea esi, [ecx - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 073h, 009h   ; jae 0x23906b
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 0EBh, 025h   ; jmp 0x239090
$L_23906b:
        db 039h, 078h, 020h   ; cmp dword ptr [eax + 0x20], edi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 075h, 024h   ; jne 0x239099
        db 053h   ; push ebx
        db 08Bh, 09Ah, 030h, 001h, 000h, 000h   ; mov ebx, dword ptr [edx + 0x130]
        db 00Fh, 0B7h, 05Bh, 010h   ; movzx ebx, word ptr [ebx + 0x10]
        db 03Bh, 0CBh   ; cmp ecx, ebx
        db 05Bh   ; pop ebx
$L_239083:
        db 07Dh, 004h   ; jge 0x239089
        db 085h, 0C9h   ; test ecx, ecx
        db 07Dh, 018h   ; jge 0x2390a1
$L_239089:
        db 0C7h, 040h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1112
$L_239090:
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
$L_239093:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_239099:
        db 03Bh, 08Ah, 060h, 001h, 000h, 000h   ; cmp ecx, dword ptr [edx + 0x160]
        db 0EBh, 0E2h   ; jmp 0x239083
$L_2390a1:
        db 083h, 0EEh, 004h   ; sub esi, 4
        db 039h, 078h, 020h   ; cmp dword ptr [eax + 0x20], edi
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 075h, 02Bh   ; jne 0x2390d6
        db 08Bh, 092h, 030h, 001h, 000h, 000h   ; mov edx, dword ptr [edx + 0x130]
        db 00Fh, 0B7h, 052h, 010h   ; movzx edx, word ptr [edx + 0x10]
        db 03Bh, 0FAh   ; cmp edi, edx
$L_2390b7:
        db 07Dh, 0D0h   ; jge 0x239089
        db 085h, 0FFh   ; test edi, edi
        db 07Ch, 0CCh   ; jl 0x239089
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 003h, 0D7h   ; add edx, edi
        db 02Bh, 0CFh   ; sub ecx, edi
        db 078h, 008h   ; js 0x2390ce
        db 041h   ; inc ecx
$L_2390c7:
        db 080h, 00Ah, 001h   ; or byte ptr [edx], 1
        db 042h   ; inc edx
        db 049h   ; dec ecx
        db 075h, 0F9h   ; jne 0x2390c7
$L_2390ce:
        db 089h, 070h, 018h   ; mov dword ptr [eax + 0x18], esi
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 0BDh   ; jmp 0x239093
$L_2390d6:
        db 03Bh, 0BAh, 060h, 001h, 000h, 000h   ; cmp edi, dword ptr [edx + 0x160]
        db 0EBh, 0D9h   ; jmp 0x2390b7
seg9 ENDS

seg33 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_FLIPRGOFF@12 @ 0x002390DE
PUBLIC _itrp_FLIPRGOFF@12
_itrp_FLIPRGOFF@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 056h   ; push esi
        db 08Bh, 070h, 024h   ; mov esi, dword ptr [eax + 0x24]
        db 057h   ; push edi
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 08Bh, 04Fh, 018h   ; mov ecx, dword ptr [edi + 0x18]
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Dh, 051h, 0F8h   ; lea edx, [ecx - 8]
        db 03Bh, 016h   ; cmp edx, dword ptr [esi]
        db 073h, 009h   ; jae 0x239104
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 0EBh, 028h   ; jmp 0x23912c
$L_239104:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 039h, 078h, 020h   ; cmp dword ptr [eax + 0x20], edi
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 075h, 024h   ; jne 0x239135
        db 053h   ; push ebx
        db 08Bh, 09Eh, 030h, 001h, 000h, 000h   ; mov ebx, dword ptr [esi + 0x130]
        db 00Fh, 0B7h, 05Bh, 010h   ; movzx ebx, word ptr [ebx + 0x10]
        db 03Bh, 0D3h   ; cmp edx, ebx
        db 05Bh   ; pop ebx
$L_23911f:
        db 07Dh, 004h   ; jge 0x239125
        db 085h, 0D2h   ; test edx, edx
        db 07Dh, 018h   ; jge 0x23913d
$L_239125:
        db 0C7h, 040h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1112
$L_23912c:
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
$L_23912f:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_239135:
        db 03Bh, 096h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [esi + 0x160]
        db 0EBh, 0E2h   ; jmp 0x23911f
$L_23913d:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 039h, 078h, 020h   ; cmp dword ptr [eax + 0x20], edi
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 075h, 02Ah   ; jne 0x239174
        db 08Bh, 0B6h, 030h, 001h, 000h, 000h   ; mov esi, dword ptr [esi + 0x130]
        db 00Fh, 0B7h, 076h, 010h   ; movzx esi, word ptr [esi + 0x10]
        db 03Bh, 0CEh   ; cmp ecx, esi
$L_239156:
        db 07Dh, 0CDh   ; jge 0x239125
        db 085h, 0C9h   ; test ecx, ecx
        db 07Ch, 0C9h   ; jl 0x239125
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 003h, 0C1h   ; add eax, ecx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 078h, 00Ah   ; js 0x23916f
        db 08Dh, 04Ah, 001h   ; lea ecx, [edx + 1]
$L_239168:
        db 080h, 020h, 0FEh   ; and byte ptr [eax], 0xfe
        db 040h   ; inc eax
        db 049h   ; dec ecx
        db 075h, 0F9h   ; jne 0x239168
$L_23916f:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 0BBh   ; jmp 0x23912f
$L_239174:
        db 03Bh, 08Eh, 060h, 001h, 000h, 000h   ; cmp ecx, dword ptr [esi + 0x160]
        db 0EBh, 0DAh   ; jmp 0x239156
; // match: _itrp_SCANCTRL@12 @ 0x0023917C
PUBLIC _itrp_SCANCTRL@12
_itrp_SCANCTRL@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 04Ah, 018h   ; mov ecx, dword ptr [edx + 0x18]
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 030h   ; cmp esi, dword ptr [eax]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x23919b
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0EBh, 018h   ; jmp 0x2391b3
$L_23919b:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 04Ah, 018h   ; mov dword ptr [edx + 0x18], ecx
        db 08Bh, 050h, 068h   ; mov edx, dword ptr [eax + 0x68]
        db 081h, 0E2h, 000h, 000h, 0FFh, 0FFh   ; and edx, 0xffff0000
        db 00Bh, 011h   ; or edx, dword ptr [ecx]
        db 089h, 050h, 068h   ; mov dword ptr [eax + 0x68], edx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_2391b3:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_SCANTYPE@12 @ 0x002391B6
PUBLIC _itrp_SCANTYPE@12
_itrp_SCANTYPE@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 04Ah, 018h   ; mov ecx, dword ptr [edx + 0x18]
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 030h   ; cmp esi, dword ptr [eax]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x2391d5
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0EBh, 01Dh   ; jmp 0x2391f2
$L_2391d5:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 04Ah, 018h   ; mov dword ptr [edx + 0x18], ecx
        db 08Bh, 050h, 068h   ; mov edx, dword ptr [eax + 0x68]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 081h, 0E2h, 0FFh, 0FFh, 000h, 000h   ; and edx, 0xffff
        db 0C1h, 0E1h, 010h   ; shl ecx, 0x10
        db 00Bh, 0D1h   ; or edx, ecx
        db 089h, 050h, 068h   ; mov dword ptr [eax + 0x68], edx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_2391f2:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_INSTCTRL@12 @ 0x002391F5
PUBLIC _itrp_INSTCTRL@12
_itrp_INSTCTRL@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 073h, 00Ch   ; jae 0x239213
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 03Fh   ; jmp 0x239252
$L_239213:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 080h, 0BAh, 024h, 001h, 000h, 000h, 000h   ; cmp byte ptr [edx + 0x124], 0
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 074h, 022h   ; je 0x23924e
        db 083h, 0FEh, 001h   ; cmp esi, 1
        db 075h, 006h   ; jne 0x239237
        db 083h, 062h, 06Ch, 0FEh   ; and dword ptr [edx + 0x6c], 0xfffffffe
        db 0EBh, 014h   ; jmp 0x23924b
$L_239237:
        db 083h, 0FEh, 002h   ; cmp esi, 2
        db 075h, 006h   ; jne 0x239242
        db 083h, 062h, 06Ch, 0FDh   ; and dword ptr [edx + 0x6c], 0xfffffffd
        db 0EBh, 009h   ; jmp 0x23924b
$L_239242:
        db 083h, 0FEh, 003h   ; cmp esi, 3
        db 075h, 004h   ; jne 0x23924b
        db 083h, 062h, 06Ch, 0FBh   ; and dword ptr [edx + 0x6c], 0xfffffffb
$L_23924b:
        db 009h, 042h, 06Ch   ; or dword ptr [edx + 0x6c], eax
$L_23924e:
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_239252:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg33 ENDS

seg10 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_PUSHB@12 @ 0x00239330
PUBLIC _itrp_PUSHB@12
_itrp_PUSHB@12:
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 005h, 051h, 0FFh, 0FFh, 0FFh   ; add eax, 0xffffff51
        db 050h   ; push eax
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        call _itrp_PushSomeBytes@12   ; 0x239256
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg10 ENDS

seg34 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_NPUSHB@12 @ 0x0023934A
PUBLIC _itrp_NPUSHB@12
_itrp_NPUSHB@12:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 040h   ; inc eax
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        call _itrp_PushSomeBytes@12   ; 0x239256
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_PUSHW1@12 @ 0x00239360
PUBLIC _itrp_PUSHW1@12
_itrp_PUSHW1@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Bh, 071h, 018h   ; mov esi, dword ptr [ecx + 0x18]
        db 08Dh, 056h, 004h   ; lea edx, [esi + 4]
        db 03Bh, 090h, 05Ch, 001h, 000h, 000h   ; cmp edx, dword ptr [eax + 0x15c]
        db 076h, 00Ch   ; jbe 0x239382
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1111
        db 0EBh, 020h   ; jmp 0x2393a2
$L_239382:
        db 08Bh, 054h, 024h, 00Ch   ; mov edx, dword ptr [esp + 0xc]
        db 066h, 00Fh, 0B6h, 002h   ; movzx ax, byte ptr [edx]
        db 042h   ; inc edx
        db 057h   ; push edi
        db 066h, 00Fh, 0B6h, 03Ah   ; movzx di, byte ptr [edx]
        db 0C1h, 0E0h, 008h   ; shl eax, 8
        db 003h, 0C7h   ; add eax, edi
        db 00Fh, 0BFh, 0C0h   ; movsx eax, ax
        db 089h, 006h   ; mov dword ptr [esi], eax
        db 083h, 041h, 018h, 004h   ; add dword ptr [ecx + 0x18], 4
        db 08Dh, 042h, 001h   ; lea eax, [edx + 1]
        db 05Fh   ; pop edi
$L_2393a2:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg34 ENDS

seg11 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_NPUSHW@12 @ 0x002393C0
PUBLIC _itrp_NPUSHW@12
_itrp_NPUSHW@12:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 040h   ; inc eax
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        call _itrp_PushSomeWords@12   ; 0x23929F
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg11 ENDS

seg35 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_WS@12 @ 0x002393D6
PUBLIC _itrp_WS@12
_itrp_WS@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 073h, 009h   ; jae 0x2393f1
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 037h   ; jmp 0x239428
$L_2393f1:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 057h   ; push edi
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 0BAh, 030h, 001h, 000h, 000h   ; mov edi, dword ptr [edx + 0x130]
        db 00Fh, 0B7h, 07Fh, 012h   ; movzx edi, word ptr [edi + 0x12]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 03Bh, 0C7h   ; cmp eax, edi
        db 05Fh   ; pop edi
        db 07Dh, 010h   ; jge 0x239421
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 00Ch   ; jl 0x239421
        db 08Bh, 04Ah, 004h   ; mov ecx, dword ptr [edx + 4]
        db 089h, 034h, 081h   ; mov dword ptr [ecx + eax*4], esi
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 0EBh, 00Ah   ; jmp 0x23942b
$L_239421:
        db 0C7h, 041h, 06Ch, 019h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1119
$L_239428:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
$L_23942b:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RS@12 @ 0x0023942F
PUBLIC _itrp_RS@12
_itrp_RS@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 050h, 018h   ; mov edx, dword ptr [eax + 0x18]
        db 08Bh, 048h, 024h   ; mov ecx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 072h, 0FCh   ; lea esi, [edx - 4]
        db 03Bh, 031h   ; cmp esi, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x23944d
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 064h   ; jmp 0x2394b1
$L_23944d:
        db 083h, 0C2h, 0FCh   ; add edx, -4
        db 089h, 050h, 018h   ; mov dword ptr [eax + 0x18], edx
        db 08Bh, 0B1h, 030h, 001h, 000h, 000h   ; mov esi, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 076h, 012h   ; movzx esi, word ptr [esi + 0x12]
        db 057h   ; push edi
        db 08Bh, 03Ah   ; mov edi, dword ptr [edx]
        db 03Bh, 0FEh   ; cmp edi, esi
        db 07Dh, 042h   ; jge 0x2394a6
        db 085h, 0FFh   ; test edi, edi
        db 07Ch, 03Eh   ; jl 0x2394a6
        db 083h, 0FFh, 008h   ; cmp edi, 8
        db 075h, 027h   ; jne 0x239494
        db 0F6h, 081h, 06Ch, 001h, 000h, 000h, 001h   ; test byte ptr [ecx + 0x16c], 1
        db 074h, 01Eh   ; je 0x239494
        db 0F6h, 041h, 06Ch, 004h   ; test byte ptr [ecx + 0x6c], 4
        db 075h, 018h   ; jne 0x239494
        db 08Dh, 0B1h, 06Eh, 001h, 000h, 000h   ; lea esi, [ecx + 0x16e]
        db 066h, 0F7h, 006h, 000h, 008h   ; test word ptr [esi], 0x800
        db 076h, 00Bh   ; jbe 0x239494
        db 080h, 00Eh, 008h   ; or byte ptr [esi], 8
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 083h, 021h, 000h   ; and dword ptr [ecx], 0
        db 0EBh, 008h   ; jmp 0x23949c
$L_239494:
        db 08Bh, 049h, 004h   ; mov ecx, dword ptr [ecx + 4]
        db 08Bh, 00Ch, 0B9h   ; mov ecx, dword ptr [ecx + edi*4]
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
$L_23949c:
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 0EBh, 00Ah   ; jmp 0x2394b0
$L_2394a6:
        db 0C7h, 040h, 06Ch, 019h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1119
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
$L_2394b0:
        db 05Fh   ; pop edi
$L_2394b1:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_WCVT@12 @ 0x002394B5
PUBLIC _itrp_WCVT@12
_itrp_WCVT@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x2394d3
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 058h   ; jmp 0x23952b
$L_2394d3:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 053h   ; push ebx
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 057h   ; push edi
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 00Fh, 0B7h, 081h, 034h, 001h, 000h, 000h   ; movzx eax, word ptr [ecx + 0x134]
        db 03Bh, 0F8h   ; cmp edi, eax
        db 07Dh, 02Fh   ; jge 0x23951f
        db 085h, 0FFh   ; test edi, edi
        db 07Ch, 02Bh   ; jl 0x23951f
        db 085h, 0DBh   ; test ebx, ebx
        db 074h, 018h   ; je 0x239510
        db 081h, 07Eh, 058h   ; cmp dword ptr [esi + 0x58], 0x23684e
        dd _sub_23684E
        db 074h, 00Fh   ; je 0x239510
        db 056h   ; push esi
        call _itrp_GetCVTScale@4   ; 0x23679D
        db 050h   ; push eax
        db 053h   ; push ebx
        call _FixDiv@8   ; 0x235A7C
        db 08Bh, 0D8h   ; mov ebx, eax
$L_239510:
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Bh, 040h, 008h   ; mov eax, dword ptr [eax + 8]
        db 089h, 01Ch, 0B8h   ; mov dword ptr [eax + edi*4], ebx
        db 08Bh, 044h, 024h, 014h   ; mov eax, dword ptr [esp + 0x14]
        db 0EBh, 00Ah   ; jmp 0x239529
$L_23951f:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 01Bh, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x111b
$L_239529:
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
$L_23952b:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_WCVTFOD@12 @ 0x0023952F
PUBLIC _itrp_WCVTFOD@12
_itrp_WCVTFOD@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 056h   ; push esi
        db 08Bh, 071h, 024h   ; mov esi, dword ptr [ecx + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 016h   ; cmp edx, dword ptr [esi]
        db 073h, 00Ch   ; jae 0x23954d
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 045h   ; jmp 0x239592
$L_23954d:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 057h   ; push edi
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 00Fh, 0B7h, 086h, 034h, 001h, 000h, 000h   ; movzx eax, word ptr [esi + 0x134]
        db 03Bh, 0F8h   ; cmp edi, eax
        db 07Dh, 01Eh   ; jge 0x239587
        db 085h, 0FFh   ; test edi, edi
        db 07Ch, 01Ah   ; jl 0x239587
        db 052h   ; push edx
        db 08Dh, 086h, 000h, 001h, 000h, 000h   ; lea eax, [esi + 0x100]
        db 050h   ; push eax
        db 0FFh, 096h, 0ACh, 000h, 000h, 000h   ; call dword ptr [esi + 0xac]
        db 08Bh, 04Eh, 008h   ; mov ecx, dword ptr [esi + 8]
        db 089h, 004h, 0B9h   ; mov dword ptr [ecx + edi*4], eax
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 0EBh, 00Ah   ; jmp 0x239591
$L_239587:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 01Bh, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x111b
$L_239591:
        db 05Fh   ; pop edi
$L_239592:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RCVT@12 @ 0x00239596
PUBLIC _itrp_RCVT@12
_itrp_RCVT@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0FCh   ; lea edx, [eax - 4]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x2395b4
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 044h   ; jmp 0x2395f8
$L_2395b4:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 057h   ; push edi
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 00Fh, 0B7h, 081h, 034h, 001h, 000h, 000h   ; movzx eax, word ptr [ecx + 0x134]
        db 03Bh, 0F8h   ; cmp edi, eax
        db 07Ch, 008h   ; jl 0x2395d0
        db 081h, 0FFh, 0FFh, 000h, 000h, 000h   ; cmp edi, 0xff
        db 07Fh, 004h   ; jg 0x2395d4
$L_2395d0:
        db 085h, 0FFh   ; test edi, edi
        db 07Dh, 00Ch   ; jge 0x2395e0
$L_2395d4:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 01Bh, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x111b
        db 0EBh, 017h   ; jmp 0x2395f7
$L_2395e0:
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 056h, 058h   ; call dword ptr [esi + 0x58]
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 056h, 058h   ; call dword ptr [esi + 0x58]
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 083h, 046h, 018h, 004h   ; add dword ptr [esi + 0x18], 4
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
$L_2395f7:
        db 05Fh   ; pop edi
$L_2395f8:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_RC@12 @ 0x002395FC
PUBLIC _itrp_RC@12
_itrp_RC@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 08Dh, 048h, 0FCh   ; lea ecx, [eax - 4]
        db 03Bh, 00Ah   ; cmp ecx, dword ptr [edx]
        db 073h, 009h   ; jae 0x239617
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 029h   ; jmp 0x239640
$L_239617:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 039h, 046h, 020h   ; cmp dword ptr [esi + 0x20], eax
        db 075h, 020h   ; jne 0x239647
        db 08Bh, 092h, 030h, 001h, 000h, 000h   ; mov edx, dword ptr [edx + 0x130]
        db 00Fh, 0B7h, 052h, 010h   ; movzx edx, word ptr [edx + 0x10]
        db 03Bh, 0CAh   ; cmp ecx, edx
$L_239633:
        db 07Dh, 004h   ; jge 0x239639
        db 085h, 0C9h   ; test ecx, ecx
        db 07Dh, 016h   ; jge 0x23964f
$L_239639:
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_239640:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_239643:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_239647:
        db 03Bh, 08Ah, 060h, 001h, 000h, 000h   ; cmp ecx, dword ptr [edx + 0x160]
        db 0EBh, 0E4h   ; jmp 0x239633
$L_23964f:
        db 0C1h, 0E1h, 002h   ; shl ecx, 2
        db 0F6h, 044h, 024h, 010h, 001h   ; test byte ptr [esp + 0x10], 1
        db 074h, 012h   ; je 0x23966b
        db 08Bh, 050h, 00Ch   ; mov edx, dword ptr [eax + 0xc]
        db 0FFh, 034h, 00Ah   ; push dword ptr [edx + ecx]
        db 08Bh, 040h, 008h   ; mov eax, dword ptr [eax + 8]
        db 0FFh, 034h, 008h   ; push dword ptr [eax + ecx]
        db 056h   ; push esi
        db 0FFh, 056h, 050h   ; call dword ptr [esi + 0x50]
        db 0EBh, 00Fh   ; jmp 0x23967a
$L_23966b:
        db 08Bh, 050h, 004h   ; mov edx, dword ptr [eax + 4]
        db 0FFh, 034h, 00Ah   ; push dword ptr [edx + ecx]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 0FFh, 034h, 008h   ; push dword ptr [eax + ecx]
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
$L_23967a:
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 083h, 046h, 018h, 004h   ; add dword ptr [esi + 0x18], 4
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 0EBh, 0BAh   ; jmp 0x239643
; // match: _itrp_WC@12 @ 0x00239689
PUBLIC _itrp_WC@12
_itrp_WC@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x2396aa
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 03Ch   ; jmp 0x2396e6
$L_2396aa:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 057h   ; push edi
        db 08Bh, 07Eh, 008h   ; mov edi, dword ptr [esi + 8]
        db 039h, 07Eh, 020h   ; cmp dword ptr [esi + 0x20], edi
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 055h, 008h   ; mov dword ptr [ebp + 8], edx
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        db 075h, 022h   ; jne 0x2396eb
        db 08Bh, 089h, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0C1h   ; cmp eax, ecx
$L_2396d5:
        db 07Dh, 004h   ; jge 0x2396db
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 018h   ; jge 0x2396f3
$L_2396db:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_2396e5:
        db 05Fh   ; pop edi
$L_2396e6:
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_2396eb:
        db 03Bh, 081h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [ecx + 0x160]
        db 0EBh, 0E2h   ; jmp 0x2396d5
$L_2396f3:
        db 053h   ; push ebx
        db 08Bh, 0D8h   ; mov ebx, eax
        db 08Bh, 047h, 004h   ; mov eax, dword ptr [edi + 4]
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 0FFh, 034h, 018h   ; push dword ptr [eax + ebx]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 0FFh, 034h, 018h   ; push dword ptr [eax + ebx]
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 02Bh, 0C8h   ; sub ecx, eax
        db 051h   ; push ecx
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 057h   ; push edi
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 03Bh, 07Eh, 020h   ; cmp edi, dword ptr [esi + 0x20]
        db 075h, 017h   ; jne 0x239732
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 004h, 003h   ; mov eax, dword ptr [ebx + eax]
        db 08Bh, 04Fh, 008h   ; mov ecx, dword ptr [edi + 8]
        db 089h, 004h, 00Bh   ; mov dword ptr [ebx + ecx], eax
        db 08Bh, 047h, 004h   ; mov eax, dword ptr [edi + 4]
        db 08Bh, 04Fh, 00Ch   ; mov ecx, dword ptr [edi + 0xc]
        db 08Bh, 004h, 003h   ; mov eax, dword ptr [ebx + eax]
        db 089h, 004h, 00Bh   ; mov dword ptr [ebx + ecx], eax
$L_239732:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 05Bh   ; pop ebx
        db 0EBh, 0ADh   ; jmp 0x2396e5
; // match: _itrp_MD@12 @ 0x00239738
PUBLIC _itrp_MD@12
_itrp_MD@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 051h   ; push ecx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 057h   ; push edi
        db 08Bh, 07Eh, 024h   ; mov edi, dword ptr [esi + 0x24]
        db 08Dh, 048h, 0F8h   ; lea ecx, [eax - 8]
        db 03Bh, 00Fh   ; cmp ecx, dword ptr [edi]
        db 073h, 00Ch   ; jae 0x23975b
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 03Ah   ; jmp 0x239795
$L_23975b:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 083h, 0E8h, 004h   ; sub eax, 4
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 053h   ; push ebx
        db 08Bh, 05Eh, 020h   ; mov ebx, dword ptr [esi + 0x20]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 03Bh, 0D8h   ; cmp ebx, eax
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 089h, 055h, 0FCh   ; mov dword ptr [ebp - 4], edx
        db 075h, 023h   ; jne 0x23979b
        db 08Bh, 08Fh, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 03Bh, 0D1h   ; cmp edx, ecx
$L_239784:
        db 07Dh, 004h   ; jge 0x23978a
        db 085h, 0D2h   ; test edx, edx
        db 07Dh, 019h   ; jge 0x2397a3
$L_23978a:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_239794:
        db 05Bh   ; pop ebx
$L_239795:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_23979b:
        db 03Bh, 097h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [edi + 0x160]
        db 0EBh, 0E1h   ; jmp 0x239784
$L_2397a3:
        db 08Bh, 04Eh, 004h   ; mov ecx, dword ptr [esi + 4]
        db 03Bh, 0D9h   ; cmp ebx, ecx
        db 00Fh, 085h, 097h, 000h, 000h, 000h   ; jne 0x239845
        db 08Bh, 097h, 030h, 001h, 000h, 000h   ; mov edx, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 052h, 010h   ; movzx edx, word ptr [edx + 0x10]
        db 039h, 055h, 008h   ; cmp dword ptr [ebp + 8], edx
        db 07Dh, 0CDh   ; jge 0x23978a
        db 083h, 07Dh, 008h, 000h   ; cmp dword ptr [ebp + 8], 0
        db 07Ch, 0C7h   ; jl 0x23978a
        db 08Bh, 055h, 0FCh   ; mov edx, dword ptr [ebp - 4]
$L_2397c6:
        db 08Bh, 05Dh, 010h   ; mov ebx, dword ptr [ebp + 0x10]
        db 04Bh   ; dec ebx
        db 0F6h, 0C3h, 001h   ; test bl, 1
        db 00Fh, 084h, 00Eh, 001h, 000h, 000h   ; je 0x2398e1
        db 08Bh, 05Eh, 020h   ; mov ebx, dword ptr [esi + 0x20]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 00Fh, 084h, 0D2h, 000h, 000h, 000h   ; je 0x2398b0
        db 03Bh, 0CBh   ; cmp ecx, ebx
        db 00Fh, 084h, 0CAh, 000h, 000h, 000h   ; je 0x2398b0
        db 080h, 0BFh, 04Dh, 001h, 000h, 000h, 000h   ; cmp byte ptr [edi + 0x14d], 0
        db 00Fh, 085h, 0BDh, 000h, 000h, 000h   ; jne 0x2398b0
        db 080h, 0BFh, 02Ch, 001h, 000h, 000h, 000h   ; cmp byte ptr [edi + 0x12c], 0
        db 08Bh, 049h, 014h   ; mov ecx, dword ptr [ecx + 0x14]
        db 074h, 062h   ; je 0x239861
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 0C1h, 0E2h, 002h   ; shl edx, 2
        db 089h, 055h, 010h   ; mov dword ptr [ebp + 0x10], edx
        db 08Bh, 014h, 011h   ; mov edx, dword ptr [ecx + edx]
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 089h, 05Dh, 008h   ; mov dword ptr [ebp + 8], ebx
        db 08Bh, 058h, 014h   ; mov ebx, dword ptr [eax + 0x14]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 02Bh, 014h, 00Bh   ; sub edx, dword ptr [ebx + ecx]
        db 08Bh, 05Dh, 010h   ; mov ebx, dword ptr [ebp + 0x10]
        db 08Bh, 040h, 010h   ; mov eax, dword ptr [eax + 0x10]
        db 052h   ; push edx
        db 08Bh, 056h, 004h   ; mov edx, dword ptr [esi + 4]
        db 08Bh, 052h, 010h   ; mov edx, dword ptr [edx + 0x10]
        db 08Bh, 014h, 01Ah   ; mov edx, dword ptr [edx + ebx]
        db 02Bh, 014h, 008h   ; sub edx, dword ptr [eax + ecx]
        db 052h   ; push edx
        db 056h   ; push esi
        db 0FFh, 056h, 050h   ; call dword ptr [esi + 0x50]
        db 050h   ; push eax
        db 08Dh, 087h, 000h, 001h, 000h, 000h   ; lea eax, [edi + 0x100]
        db 050h   ; push eax
        db 0FFh, 097h, 0ACh, 000h, 000h, 000h   ; call dword ptr [edi + 0xac]
        db 0E9h, 0E6h, 000h, 000h, 000h   ; jmp 0x23992b
$L_239845:
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 03Bh, 09Fh, 060h, 001h, 000h, 000h   ; cmp ebx, dword ptr [edi + 0x160]
        db 00Fh, 08Dh, 036h, 0FFh, 0FFh, 0FFh   ; jge 0x23978a
        db 085h, 0DBh   ; test ebx, ebx
        db 00Fh, 08Ch, 02Eh, 0FFh, 0FFh, 0FFh   ; jl 0x23978a
        db 0E9h, 065h, 0FFh, 0FFh, 0FFh   ; jmp 0x2397c6
$L_239861:
        db 08Bh, 040h, 014h   ; mov eax, dword ptr [eax + 0x14]
        db 08Bh, 0DAh   ; mov ebx, edx
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 08Bh, 00Ch, 019h   ; mov ecx, dword ptr [ecx + ebx]
        db 0C1h, 0E2h, 002h   ; shl edx, 2
        db 02Bh, 00Ch, 010h   ; sub ecx, dword ptr [eax + edx]
        db 08Dh, 087h, 0F0h, 000h, 000h, 000h   ; lea eax, [edi + 0xf0]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 089h, 055h, 008h   ; mov dword ptr [ebp + 8], edx
        db 0FFh, 097h, 0A8h, 000h, 000h, 000h   ; call dword ptr [edi + 0xa8]
        db 08Bh, 04Eh, 004h   ; mov ecx, dword ptr [esi + 4]
        db 08Bh, 049h, 010h   ; mov ecx, dword ptr [ecx + 0x10]
        db 08Bh, 00Ch, 019h   ; mov ecx, dword ptr [ecx + ebx]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 040h, 010h   ; mov eax, dword ptr [eax + 0x10]
        db 02Bh, 00Ch, 010h   ; sub ecx, dword ptr [eax + edx]
        db 08Dh, 087h, 0E0h, 000h, 000h, 000h   ; lea eax, [edi + 0xe0]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0FFh, 097h, 0A4h, 000h, 000h, 000h   ; call dword ptr [edi + 0xa4]
        db 050h   ; push eax
$L_2398aa:
        db 056h   ; push esi
        db 0FFh, 056h, 050h   ; call dword ptr [esi + 0x50]
        db 0EBh, 07Bh   ; jmp 0x23992b
$L_2398b0:
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 058h, 00Ch   ; mov ebx, dword ptr [eax + 0xc]
        db 08Bh, 040h, 008h   ; mov eax, dword ptr [eax + 8]
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 089h, 07Dh, 008h   ; mov dword ptr [ebp + 8], edi
        db 08Bh, 079h, 00Ch   ; mov edi, dword ptr [ecx + 0xc]
        db 08Bh, 049h, 008h   ; mov ecx, dword ptr [ecx + 8]
        db 0C1h, 0E2h, 002h   ; shl edx, 2
        db 08Bh, 03Ch, 017h   ; mov edi, dword ptr [edi + edx]
        db 089h, 055h, 010h   ; mov dword ptr [ebp + 0x10], edx
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 03Ch, 013h   ; sub edi, dword ptr [ebx + edx]
        db 057h   ; push edi
        db 08Bh, 07Dh, 010h   ; mov edi, dword ptr [ebp + 0x10]
        db 08Bh, 00Ch, 039h   ; mov ecx, dword ptr [ecx + edi]
        db 02Bh, 00Ch, 010h   ; sub ecx, dword ptr [eax + edx]
        db 051h   ; push ecx
        db 0EBh, 0C9h   ; jmp 0x2398aa
$L_2398e1:
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 08Bh, 058h, 004h   ; mov ebx, dword ptr [eax + 4]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 0C1h, 0E7h, 002h   ; shl edi, 2
        db 0C1h, 0E2h, 002h   ; shl edx, 2
        db 08Bh, 01Ch, 013h   ; mov ebx, dword ptr [ebx + edx]
        db 089h, 07Dh, 008h   ; mov dword ptr [ebp + 8], edi
        db 08Bh, 079h, 004h   ; mov edi, dword ptr [ecx + 4]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 089h, 055h, 010h   ; mov dword ptr [ebp + 0x10], edx
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 01Ch, 017h   ; sub ebx, dword ptr [edi + edx]
        db 08Bh, 07Dh, 010h   ; mov edi, dword ptr [ebp + 0x10]
        db 08Bh, 004h, 007h   ; mov eax, dword ptr [edi + eax]
        db 02Bh, 004h, 011h   ; sub eax, dword ptr [ecx + edx]
        db 053h   ; push ebx
        db 050h   ; push eax
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Ah, 089h, 06Eh, 001h, 000h, 000h   ; mov cl, byte ptr [ecx + 0x16e]
        db 080h, 0E1h, 00Bh   ; and cl, 0xb
        db 080h, 0F9h, 00Bh   ; cmp cl, 0xb
        db 075h, 008h   ; jne 0x23992b
        db 083h, 0F8h, 040h   ; cmp eax, 0x40
        db 075h, 003h   ; jne 0x23992b
        db 06Ah, 041h   ; push 0x41
        db 058h   ; pop eax
$L_23992b:
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 089h, 001h   ; mov dword ptr [ecx], eax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 083h, 0C1h, 004h   ; add ecx, 4
        db 089h, 04Eh, 018h   ; mov dword ptr [esi + 0x18], ecx
        db 0E9h, 056h, 0FEh, 0FFh, 0FFh   ; jmp 0x239794
seg35 ENDS

seg12 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_MPS@12 @ 0x00239995
PUBLIC _itrp_MPS@12
_itrp_MPS@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 050h, 018h   ; mov edx, dword ptr [eax + 0x18]
        db 08Bh, 048h, 024h   ; mov ecx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 072h, 004h   ; lea esi, [edx + 4]
        db 03Bh, 0B1h, 05Ch, 001h, 000h, 000h   ; cmp esi, dword ptr [ecx + 0x15c]
        db 05Eh   ; pop esi
        db 076h, 00Ch   ; jbe 0x2399b8
        db 0C7h, 040h, 06Ch, 011h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1111
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Eh   ; jmp 0x2399c6
$L_2399b8:
        db 00Fh, 0B7h, 049h, 00Eh   ; movzx ecx, word ptr [ecx + 0xe]
        db 089h, 00Ah   ; mov dword ptr [edx], ecx
        db 083h, 040h, 018h, 004h   ; add dword ptr [eax + 0x18], 4
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_2399c6:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg12 ENDS

seg36 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_GETINFO@12 @ 0x002399C9
PUBLIC _itrp_GETINFO@12
_itrp_GETINFO@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 042h, 018h   ; mov eax, dword ptr [edx + 0x18]
        db 08Bh, 04Ah, 024h   ; mov ecx, dword ptr [edx + 0x24]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 033h, 0DBh   ; xor ebx, ebx
        db 03Bh, 031h   ; cmp esi, dword ptr [ecx]
        db 073h, 00Fh   ; jae 0x2399ed
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0E9h, 0A2h, 000h, 000h, 000h   ; jmp 0x239a8f
$L_2399ed:
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 089h, 072h, 018h   ; mov dword ptr [edx + 0x18], esi
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 0A8h, 001h   ; test al, 1
        db 074h, 003h   ; je 0x2399fc
        db 06Ah, 025h   ; push 0x25
        db 05Bh   ; pop ebx
$L_2399fc:
        db 0A8h, 002h   ; test al, 2
        db 074h, 00Fh   ; je 0x239a0f
        db 0F6h, 081h, 019h, 001h, 000h, 000h, 001h   ; test byte ptr [ecx + 0x119], 1
        db 074h, 006h   ; je 0x239a0f
        db 081h, 0CBh, 000h, 001h, 000h, 000h   ; or ebx, 0x100
$L_239a0f:
        db 0A8h, 004h   ; test al, 4
        db 057h   ; push edi
        db 0BFh, 000h, 002h, 000h, 000h   ; mov edi, 0x200
        db 074h, 00Bh   ; je 0x239a24
        db 0F6h, 081h, 019h, 001h, 000h, 000h, 002h   ; test byte ptr [ecx + 0x119], 2
        db 074h, 002h   ; je 0x239a24
        db 00Bh, 0DFh   ; or ebx, edi
$L_239a24:
        db 0A8h, 020h   ; test al, 0x20
        db 074h, 00Fh   ; je 0x239a37
        db 083h, 0B9h, 048h, 001h, 000h, 000h, 000h   ; cmp dword ptr [ecx + 0x148], 0
        db 074h, 006h   ; je 0x239a37
        db 081h, 0CBh, 000h, 010h, 000h, 000h   ; or ebx, 0x1000
$L_239a37:
        db 0A8h, 040h   ; test al, 0x40
        db 074h, 00Fh   ; je 0x239a4a
        db 0F6h, 081h, 06Ch, 001h, 000h, 000h, 001h   ; test byte ptr [ecx + 0x16c], 1
        db 074h, 006h   ; je 0x239a4a
        db 081h, 0CBh, 000h, 020h, 000h, 000h   ; or ebx, 0x2000
$L_239a4a:
        db 084h, 0C0h   ; test al, al
        db 079h, 00Fh   ; jns 0x239a5d
        db 0F6h, 081h, 06Ch, 001h, 000h, 000h, 002h   ; test byte ptr [ecx + 0x16c], 2
        db 074h, 006h   ; je 0x239a5d
        db 081h, 0CBh, 000h, 040h, 000h, 000h   ; or ebx, 0x4000
$L_239a5d:
        db 0F6h, 0C4h, 001h   ; test ah, 1
        db 074h, 00Fh   ; je 0x239a71
        db 0F6h, 081h, 06Ch, 001h, 000h, 000h, 004h   ; test byte ptr [ecx + 0x16c], 4
        db 074h, 006h   ; je 0x239a71
        db 081h, 0CBh, 000h, 080h, 000h, 000h   ; or ebx, 0x8000
$L_239a71:
        db 085h, 0C7h   ; test edi, eax
        db 05Fh   ; pop edi
        db 074h, 00Fh   ; je 0x239a85
        db 0F6h, 081h, 06Ch, 001h, 000h, 000h, 008h   ; test byte ptr [ecx + 0x16c], 8
        db 074h, 006h   ; je 0x239a85
        db 081h, 0CBh, 000h, 000h, 001h, 000h   ; or ebx, 0x10000
$L_239a85:
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 089h, 01Eh   ; mov dword ptr [esi], ebx
        db 083h, 042h, 018h, 004h   ; add dword ptr [edx + 0x18], 4
$L_239a8f:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg36 ENDS

seg13 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_DEBUG@12 @ 0x00239ABE
PUBLIC _itrp_DEBUG@12
_itrp_DEBUG@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239add
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Ah   ; jmp 0x239ae7
$L_239add:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239ae7:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg13 ENDS

seg37 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_LT@12 @ 0x00239AEA
PUBLIC _itrp_LT@12
_itrp_LT@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239b09
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 017h   ; jmp 0x239b20
$L_239b09:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 033h, 0D2h   ; xor edx, edx
        db 03Bh, 008h   ; cmp ecx, dword ptr [eax]
        db 00Fh, 09Ch, 0C2h   ; setl dl
        db 089h, 050h, 0FCh   ; mov dword ptr [eax - 4], edx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239b20:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_LTEQ@12 @ 0x00239B23
PUBLIC _itrp_LTEQ@12
_itrp_LTEQ@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239b42
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 017h   ; jmp 0x239b59
$L_239b42:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 033h, 0D2h   ; xor edx, edx
        db 03Bh, 008h   ; cmp ecx, dword ptr [eax]
        db 00Fh, 09Eh, 0C2h   ; setle dl
        db 089h, 050h, 0FCh   ; mov dword ptr [eax - 4], edx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239b59:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_GT@12 @ 0x00239B5C
PUBLIC _itrp_GT@12
_itrp_GT@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239b7b
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 017h   ; jmp 0x239b92
$L_239b7b:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 033h, 0D2h   ; xor edx, edx
        db 03Bh, 008h   ; cmp ecx, dword ptr [eax]
        db 00Fh, 09Fh, 0C2h   ; setg dl
        db 089h, 050h, 0FCh   ; mov dword ptr [eax - 4], edx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239b92:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_GTEQ@12 @ 0x00239B95
PUBLIC _itrp_GTEQ@12
_itrp_GTEQ@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239bb4
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 017h   ; jmp 0x239bcb
$L_239bb4:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 033h, 0D2h   ; xor edx, edx
        db 03Bh, 008h   ; cmp ecx, dword ptr [eax]
        db 00Fh, 09Dh, 0C2h   ; setge dl
        db 089h, 050h, 0FCh   ; mov dword ptr [eax - 4], edx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239bcb:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_EQ@12 @ 0x00239BCE
PUBLIC _itrp_EQ@12
_itrp_EQ@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239bed
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 017h   ; jmp 0x239c04
$L_239bed:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 048h, 0FCh   ; mov ecx, dword ptr [eax - 4]
        db 02Bh, 008h   ; sub ecx, dword ptr [eax]
        db 0F7h, 0D9h   ; neg ecx
        db 01Bh, 0C9h   ; sbb ecx, ecx
        db 041h   ; inc ecx
        db 089h, 048h, 0FCh   ; mov dword ptr [eax - 4], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239c04:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg37 ENDS

seg14 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_AND@12 @ 0x00239C40
PUBLIC _itrp_AND@12
_itrp_AND@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239c5f
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 019h   ; jmp 0x239c78
$L_239c5f:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 033h, 0C9h   ; xor ecx, ecx
        db 039h, 048h, 0FCh   ; cmp dword ptr [eax - 4], ecx
        db 074h, 005h   ; je 0x239c71
        db 039h, 008h   ; cmp dword ptr [eax], ecx
        db 074h, 001h   ; je 0x239c71
        db 041h   ; inc ecx
$L_239c71:
        db 089h, 048h, 0FCh   ; mov dword ptr [eax - 4], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239c78:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg14 ENDS

seg38 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_OR@12 @ 0x00239C7B
PUBLIC _itrp_OR@12
_itrp_OR@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239c9a
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 01Bh   ; jmp 0x239cb5
$L_239c9a:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 033h, 0C9h   ; xor ecx, ecx
        db 039h, 048h, 0FCh   ; cmp dword ptr [eax - 4], ecx
        db 075h, 004h   ; jne 0x239cab
        db 039h, 008h   ; cmp dword ptr [eax], ecx
        db 074h, 003h   ; je 0x239cae
$L_239cab:
        db 033h, 0C9h   ; xor ecx, ecx
        db 041h   ; inc ecx
$L_239cae:
        db 089h, 048h, 0FCh   ; mov dword ptr [eax - 4], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239cb5:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_ADD@12 @ 0x00239CB8
PUBLIC _itrp_ADD@12
_itrp_ADD@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239cd7
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 00Fh   ; jmp 0x239ce6
$L_239cd7:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 001h, 048h, 0FCh   ; add dword ptr [eax - 4], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239ce6:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_SUB@12 @ 0x00239CE9
PUBLIC _itrp_SUB@12
_itrp_SUB@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239d08
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 00Fh   ; jmp 0x239d17
$L_239d08:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 029h, 048h, 0FCh   ; sub dword ptr [eax - 4], ecx
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239d17:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_MUL@12 @ 0x00239D1A
PUBLIC _itrp_MUL@12
_itrp_MUL@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0F8h   ; lea esi, [ecx - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 073h, 00Ch   ; jae 0x239d38
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 017h   ; jmp 0x239d4f
$L_239d38:
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 089h, 070h, 018h   ; mov dword ptr [eax + 0x18], esi
        db 0FFh, 036h   ; push dword ptr [esi]
        db 0FFh, 076h, 0FCh   ; push dword ptr [esi - 4]
        call _Mul26Dot6@8   ; 0x235950
        db 089h, 046h, 0FCh   ; mov dword ptr [esi - 4], eax
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_239d4f:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_DIV@12 @ 0x00239D53
PUBLIC _itrp_DIV@12
_itrp_DIV@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0F8h   ; lea esi, [ecx - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 073h, 009h   ; jae 0x239d6e
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 0EBh, 013h   ; jmp 0x239d81
$L_239d6e:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 08Bh, 031h   ; mov esi, dword ptr [ecx]
        db 085h, 0F6h   ; test esi, esi
        db 075h, 00Ch   ; jne 0x239d86
        db 0C7h, 040h, 06Ch, 003h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1103
$L_239d81:
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 010h   ; jmp 0x239d96
$L_239d86:
        db 08Bh, 041h, 0FCh   ; mov eax, dword ptr [ecx - 4]
        db 0C1h, 0E0h, 006h   ; shl eax, 6
        db 099h   ; cdq 
        db 0F7h, 0FEh   ; idiv esi
        db 089h, 041h, 0FCh   ; mov dword ptr [ecx - 4], eax
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_239d96:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg38 ENDS

seg16 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_EVEN@12 @ 0x00239E40
PUBLIC _itrp_EVEN@12
_itrp_EVEN@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 024h   ; mov ecx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Bh, 070h, 018h   ; mov esi, dword ptr [eax + 0x18]
        db 08Dh, 056h, 0FCh   ; lea edx, [esi - 4]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x239e5e
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 019h   ; jmp 0x239e77
$L_239e5e:
        db 06Ah, 000h   ; push 0
        db 0FFh, 076h, 0FCh   ; push dword ptr [esi - 4]
        db 050h   ; push eax
        call _itrp_RoundToGrid@12   ; 0x23640C
        db 0C1h, 0F8h, 006h   ; sar eax, 6
        db 048h   ; dec eax
        db 083h, 0E0h, 001h   ; and eax, 1
        db 089h, 046h, 0FCh   ; mov dword ptr [esi - 4], eax
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_239e77:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg16 ENDS

seg39 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_NOT@12 @ 0x00239E7B
PUBLIC _itrp_NOT@12
_itrp_NOT@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239e9a
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 00Fh   ; jmp 0x239ea9
$L_239e9a:
        db 033h, 0C0h   ; xor eax, eax
        db 039h, 041h, 0FCh   ; cmp dword ptr [ecx - 4], eax
        db 00Fh, 094h, 0C0h   ; sete al
        db 089h, 041h, 0FCh   ; mov dword ptr [ecx - 4], eax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239ea9:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_ABS@12 @ 0x00239EAC
PUBLIC _itrp_ABS@12
_itrp_ABS@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239ecb
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 010h   ; jmp 0x239edb
$L_239ecb:
        db 08Bh, 041h, 0FCh   ; mov eax, dword ptr [ecx - 4]
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 005h   ; jge 0x239ed7
        db 0F7h, 0D8h   ; neg eax
        db 089h, 041h, 0FCh   ; mov dword ptr [ecx - 4], eax
$L_239ed7:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239edb:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_NEG@12 @ 0x00239EDE
PUBLIC _itrp_NEG@12
_itrp_NEG@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239efd
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 007h   ; jmp 0x239f04
$L_239efd:
        db 0F7h, 059h, 0FCh   ; neg dword ptr [ecx - 4]
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239f04:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_CEILING@12 @ 0x00239F07
PUBLIC _itrp_CEILING@12
_itrp_CEILING@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239f26
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 010h   ; jmp 0x239f36
$L_239f26:
        db 08Bh, 041h, 0FCh   ; mov eax, dword ptr [ecx - 4]
        db 083h, 0C0h, 03Fh   ; add eax, 0x3f
        db 083h, 0E0h, 0C0h   ; and eax, 0xffffffc0
        db 089h, 041h, 0FCh   ; mov dword ptr [ecx - 4], eax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239f36:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_FLOOR@12 @ 0x00239F39
PUBLIC _itrp_FLOOR@12
_itrp_FLOOR@12:
        db 08Bh, 044h, 024h, 004h   ; mov eax, dword ptr [esp + 4]
        db 08Bh, 048h, 018h   ; mov ecx, dword ptr [eax + 0x18]
        db 08Bh, 050h, 024h   ; mov edx, dword ptr [eax + 0x24]
        db 056h   ; push esi
        db 08Dh, 071h, 0FCh   ; lea esi, [ecx - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x239f58
        db 0C7h, 040h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [eax + 0x6c], 0x1110
        db 08Bh, 040h, 070h   ; mov eax, dword ptr [eax + 0x70]
        db 0EBh, 008h   ; jmp 0x239f60
$L_239f58:
        db 083h, 061h, 0FCh, 0C0h   ; and dword ptr [ecx - 4], 0xffffffc0
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_239f60:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg39 ENDS

seg17 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_IF@12 @ 0x00239F92
PUBLIC _itrp_IF@12
_itrp_IF@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 042h, 018h   ; mov eax, dword ptr [edx + 0x18]
        db 08Bh, 04Ah, 024h   ; mov ecx, dword ptr [edx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 031h   ; cmp esi, dword ptr [ecx]
        db 073h, 00Ch   ; jae 0x239fb0
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0EBh, 072h   ; jmp 0x23a022
$L_239fb0:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 042h, 018h   ; mov dword ptr [edx + 0x18], eax
        db 083h, 038h, 000h   ; cmp dword ptr [eax], 0
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
        db 057h   ; push edi
        db 075h, 061h   ; jne 0x23a021
        db 08Bh, 072h, 070h   ; mov esi, dword ptr [edx + 0x70]
        db 033h, 0FFh   ; xor edi, edi
        db 047h   ; inc edi
$L_239fc6:
        db 03Bh, 0C6h   ; cmp eax, esi
        db 073h, 04Ah   ; jae 0x23a014
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 040h   ; inc eax
        db 083h, 0F9h, 059h   ; cmp ecx, 0x59
        db 075h, 003h   ; jne 0x239fd6
        db 04Fh   ; dec edi
        db 0EBh, 038h   ; jmp 0x23a00e
$L_239fd6:
        db 083h, 0F9h, 058h   ; cmp ecx, 0x58
        db 075h, 003h   ; jne 0x239fde
        db 047h   ; inc edi
        db 0EBh, 030h   ; jmp 0x23a00e
$L_239fde:
        db 083h, 0F9h, 01Bh   ; cmp ecx, 0x1b
        db 075h, 007h   ; jne 0x239fea
        db 083h, 0FFh, 001h   ; cmp edi, 1
        db 074h, 02Ah   ; je 0x23a012
        db 0EBh, 024h   ; jmp 0x23a00e
$L_239fea:
        db 00Fh, 0B6h, 089h   ; movzx ecx, byte ptr [ecx + 0x3ecf40]
        dd _unk_3ECF40
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 019h   ; je 0x23a00e
        db 083h, 0F9h, 015h   ; cmp ecx, 0x15
        db 075h, 006h   ; jne 0x23a000
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 041h   ; inc ecx
        db 0EBh, 00Ch   ; jmp 0x23a00c
$L_23a000:
        db 083h, 0F9h, 016h   ; cmp ecx, 0x16
        db 075h, 007h   ; jne 0x23a00c
        db 00Fh, 0B6h, 008h   ; movzx ecx, byte ptr [eax]
        db 08Dh, 04Ch, 009h, 001h   ; lea ecx, [ecx + ecx + 1]
$L_23a00c:
        db 003h, 0C1h   ; add eax, ecx
$L_23a00e:
        db 085h, 0FFh   ; test edi, edi
        db 075h, 0B4h   ; jne 0x239fc6
$L_23a012:
        db 03Bh, 0C6h   ; cmp eax, esi
$L_23a014:
        db 075h, 00Bh   ; jne 0x23a021
        db 085h, 0FFh   ; test edi, edi
        db 074h, 007h   ; je 0x23a021
        db 0C7h, 042h, 06Ch, 005h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1105
$L_23a021:
        db 05Fh   ; pop edi
$L_23a022:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg17 ENDS

seg40 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_ELSE@12 @ 0x0023A026
PUBLIC _itrp_ELSE@12
_itrp_ELSE@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 056h   ; push esi
        db 033h, 0F6h   ; xor esi, esi
        db 057h   ; push edi
        db 08Bh, 07Ah, 070h   ; mov edi, dword ptr [edx + 0x70]
        db 046h   ; inc esi
$L_23a036:
        db 03Bh, 0C7h   ; cmp eax, edi
        db 073h, 01Fh   ; jae 0x23a059
        db 08Ah, 008h   ; mov cl, byte ptr [eax]
        db 040h   ; inc eax
        db 080h, 0F9h, 059h   ; cmp cl, 0x59
        db 075h, 003h   ; jne 0x23a045
        db 04Eh   ; dec esi
        db 0EBh, 00Fh   ; jmp 0x23a054
$L_23a045:
        db 080h, 0F9h, 058h   ; cmp cl, 0x58
        db 075h, 003h   ; jne 0x23a04d
        db 046h   ; inc esi
        db 0EBh, 007h   ; jmp 0x23a054
$L_23a04d:
        db 050h   ; push eax
        db 052h   ; push edx
        call _itrp_SkipPushData@8   ; 0x239F63
$L_23a054:
        db 066h, 085h, 0F6h   ; test si, si
        db 075h, 0DDh   ; jne 0x23a036
$L_23a059:
        db 05Fh   ; pop edi
        db 066h, 085h, 0F6h   ; test si, si
        db 05Eh   ; pop esi
        db 074h, 007h   ; je 0x23a067
        db 0C7h, 042h, 06Ch, 005h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1105
$L_23a067:
        db 0C2h, 00Ch, 000h   ; ret 0xc

; // match: _itrp_EIF@12 @ 0x0023A06A
PUBLIC _itrp_EIF@12
_itrp_EIF@12:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg40 ENDS

seg41 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_JMPR@12 @ 0x0023A071
PUBLIC _itrp_JMPR@12
_itrp_JMPR@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 009h   ; jae 0x23a08d
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 02Ah   ; jmp 0x23a0b7
$L_23a08d:
        db 08Bh, 054h, 024h, 008h   ; mov edx, dword ptr [esp + 8]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 0FFh, 049h, 078h   ; dec dword ptr [ecx + 0x78]
        db 08Dh, 044h, 002h, 0FFh   ; lea eax, [edx + eax - 1]
        db 075h, 009h   ; jne 0x23a0ab
        db 0C7h, 041h, 06Ch, 007h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1107
        db 0EBh, 00Ch   ; jmp 0x23a0b7
$L_23a0ab:
        db 03Bh, 041h, 074h   ; cmp eax, dword ptr [ecx + 0x74]
        db 073h, 00Ah   ; jae 0x23a0ba
        db 0C7h, 041h, 06Ch, 00Bh, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x110b
$L_23a0b7:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
$L_23a0ba:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_JROT@12 @ 0x0023A0BD
PUBLIC _itrp_JROT@12
_itrp_JROT@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 009h   ; jae 0x23a0d9
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 036h   ; jmp 0x23a10f
$L_23a0d9:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 085h, 0D2h   ; test edx, edx
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 074h, 029h   ; je 0x23a114
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 0FFh, 049h, 078h   ; dec dword ptr [ecx + 0x78]
        db 08Bh, 054h, 024h, 008h   ; mov edx, dword ptr [esp + 8]
        db 08Dh, 044h, 002h, 0FFh   ; lea eax, [edx + eax - 1]
        db 075h, 009h   ; jne 0x23a103
        db 0C7h, 041h, 06Ch, 007h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1107
        db 0EBh, 00Ch   ; jmp 0x23a10f
$L_23a103:
        db 03Bh, 041h, 074h   ; cmp eax, dword ptr [ecx + 0x74]
        db 073h, 010h   ; jae 0x23a118
        db 0C7h, 041h, 06Ch, 00Bh, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x110b
$L_23a10f:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0EBh, 004h   ; jmp 0x23a118
$L_23a114:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_23a118:
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_JROF@12 @ 0x0023A11B
PUBLIC _itrp_JROF@12
_itrp_JROF@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0F8h   ; lea esi, [eax - 8]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 009h   ; jae 0x23a137
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 036h   ; jmp 0x23a16d
$L_23a137:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 085h, 0D2h   ; test edx, edx
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 075h, 029h   ; jne 0x23a172
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 0FFh, 049h, 078h   ; dec dword ptr [ecx + 0x78]
        db 08Bh, 054h, 024h, 008h   ; mov edx, dword ptr [esp + 8]
        db 08Dh, 044h, 002h, 0FFh   ; lea eax, [edx + eax - 1]
        db 075h, 009h   ; jne 0x23a161
        db 0C7h, 041h, 06Ch, 007h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1107
        db 0EBh, 00Ch   ; jmp 0x23a16d
$L_23a161:
        db 03Bh, 041h, 074h   ; cmp eax, dword ptr [ecx + 0x74]
        db 073h, 010h   ; jae 0x23a176
        db 0C7h, 041h, 06Ch, 00Bh, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x110b
$L_23a16d:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0EBh, 004h   ; jmp 0x23a176
$L_23a172:
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_23a176:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg41 ENDS

seg19 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_MDRP@12 @ 0x0023A248
PUBLIC _itrp_MDRP@12
_itrp_MDRP@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 010h   ; sub esp, 0x10
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 08Bh, 05Eh, 004h   ; mov ebx, dword ptr [esi + 4]
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 057h   ; push edi
        db 08Bh, 07Eh, 024h   ; mov edi, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0FCh   ; lea edx, [eax - 4]
        db 03Bh, 017h   ; cmp edx, dword ptr [edi]
        db 089h, 04Dh, 0F8h   ; mov dword ptr [ebp - 8], ecx
        db 073h, 009h   ; jae 0x23a278
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 02Ch   ; jmp 0x23a2a4
$L_23a278:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 039h, 04Eh, 020h   ; cmp dword ptr [esi + 0x20], ecx
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        db 075h, 026h   ; jne 0x23a2ae
        db 08Bh, 08Fh, 030h, 001h, 000h, 000h   ; mov ecx, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 049h, 010h   ; movzx ecx, word ptr [ecx + 0x10]
        db 039h, 04Dh, 008h   ; cmp dword ptr [ebp + 8], ecx
        db 07Dh, 006h   ; jge 0x23a29d
        db 083h, 07Dh, 008h, 000h   ; cmp dword ptr [ebp + 8], 0
        db 07Dh, 022h   ; jge 0x23a2bf
$L_23a29d:
        db 0C7h, 046h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1112
$L_23a2a4:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_23a2a7:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
$L_23a2ae:
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 03Bh, 097h, 060h, 001h, 000h, 000h   ; cmp edx, dword ptr [edi + 0x160]
        db 07Dh, 0E4h   ; jge 0x23a29d
        db 085h, 0D2h   ; test edx, edx
        db 07Ch, 0E0h   ; jl 0x23a29d
        db 0EBh, 003h   ; jmp 0x23a2c2
$L_23a2bf:
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
$L_23a2c2:
        db 039h, 05Eh, 020h   ; cmp dword ptr [esi + 0x20], ebx
        db 075h, 078h   ; jne 0x23a33f
        db 08Bh, 097h, 030h, 001h, 000h, 000h   ; mov edx, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 052h, 010h   ; movzx edx, word ptr [edx + 0x10]
        db 03Bh, 0C2h   ; cmp eax, edx
$L_23a2d3:
        db 07Dh, 0C8h   ; jge 0x23a29d
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 0C4h   ; jl 0x23a29d
        db 080h, 0BFh, 025h, 001h, 000h, 000h, 002h   ; cmp byte ptr [edi + 0x125], 2
        db 075h, 07Bh   ; jne 0x23a35d
        db 066h, 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [esi + 0x80], 0
        db 074h, 071h   ; je 0x23a35d
        db 0F6h, 087h, 06Ch, 001h, 000h, 000h, 002h   ; test byte ptr [edi + 0x16c], 2
        db 074h, 068h   ; je 0x23a35d
        db 03Bh, 05Eh, 020h   ; cmp ebx, dword ptr [esi + 0x20]
        db 074h, 050h   ; je 0x23a34a
        db 066h, 08Bh, 096h, 082h, 000h, 000h, 000h   ; mov dx, word ptr [esi + 0x82]
        db 066h, 083h, 0FAh, 0FFh   ; cmp dx, -1
        db 074h, 043h   ; je 0x23a34a
        db 066h, 08Bh, 08Eh, 084h, 000h, 000h, 000h   ; mov cx, word ptr [esi + 0x84]
        db 066h, 083h, 0F9h, 0FFh   ; cmp cx, -1
        db 074h, 036h   ; je 0x23a34a
        db 00Fh, 0BFh, 0C9h   ; movsx ecx, cx
        db 051h   ; push ecx
        db 00Fh, 0BFh, 0D2h   ; movsx edx, dx
        db 050h   ; push eax
        db 052h   ; push edx
        db 053h   ; push ebx
        db 089h, 04Dh, 0F4h   ; mov dword ptr [ebp - 0xc], ecx
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        call _InterAlign@16   ; 0x236205
        db 085h, 0C0h   ; test eax, eax
        db 074h, 01Ah   ; je 0x23a347
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 053h   ; push ebx
        db 056h   ; push esi
        call _AddProportion@20   ; 0x235D10
        db 0EBh, 018h   ; jmp 0x23a357
$L_23a33f:
        db 03Bh, 087h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [edi + 0x160]
        db 0EBh, 08Ch   ; jmp 0x23a2d3
$L_23a347:
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
$L_23a34a:
        db 06Ah, 003h   ; push 3
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 053h   ; push ebx
        db 056h   ; push esi
        call _AddDistance@20   ; 0x235C12
$L_23a357:
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
$L_23a35d:
        db 08Bh, 056h, 020h   ; mov edx, dword ptr [esi + 0x20]
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 00Fh, 084h, 08Bh, 000h, 000h, 000h   ; je 0x23a3f3
        db 03Bh, 0DAh   ; cmp ebx, edx
        db 00Fh, 084h, 083h, 000h, 000h, 000h   ; je 0x23a3f3
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 080h, 0BAh, 04Dh, 001h, 000h, 000h, 000h   ; cmp byte ptr [edx + 0x14d], 0
        db 075h, 077h   ; jne 0x23a3f3
        db 08Bh, 053h, 014h   ; mov edx, dword ptr [ebx + 0x14]
        db 08Bh, 004h, 082h   ; mov eax, dword ptr [edx + eax*4]
        db 08Bh, 049h, 014h   ; mov ecx, dword ptr [ecx + 0x14]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 004h, 091h   ; sub eax, dword ptr [ecx + edx*4]
        db 080h, 0BFh, 02Ch, 001h, 000h, 000h, 000h   ; cmp byte ptr [edi + 0x12c], 0
        db 050h   ; push eax
        db 074h, 02Ah   ; je 0x23a3bf
        db 08Bh, 04Bh, 010h   ; mov ecx, dword ptr [ebx + 0x10]
        db 08Bh, 055h, 0FCh   ; mov edx, dword ptr [ebp - 4]
        db 08Bh, 00Ch, 091h   ; mov ecx, dword ptr [ecx + edx*4]
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 040h, 010h   ; mov eax, dword ptr [eax + 0x10]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 00Ch, 090h   ; sub ecx, dword ptr [eax + edx*4]
        db 051h   ; push ecx
        db 056h   ; push esi
        db 0FFh, 056h, 050h   ; call dword ptr [esi + 0x50]
        db 050h   ; push eax
        db 08Dh, 087h, 000h, 001h, 000h, 000h   ; lea eax, [edi + 0x100]
        db 050h   ; push eax
        db 0FFh, 097h, 0ACh, 000h, 000h, 000h   ; call dword ptr [edi + 0xac]
        db 0EBh, 05Eh   ; jmp 0x23a41d
$L_23a3bf:
        db 08Dh, 087h, 0F0h, 000h, 000h, 000h   ; lea eax, [edi + 0xf0]
        db 050h   ; push eax
        db 0FFh, 097h, 0A8h, 000h, 000h, 000h   ; call dword ptr [edi + 0xa8]
        db 08Bh, 04Bh, 010h   ; mov ecx, dword ptr [ebx + 0x10]
        db 08Bh, 055h, 0FCh   ; mov edx, dword ptr [ebp - 4]
        db 08Bh, 00Ch, 091h   ; mov ecx, dword ptr [ecx + edx*4]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 040h, 010h   ; mov eax, dword ptr [eax + 0x10]
        db 02Bh, 00Ch, 090h   ; sub ecx, dword ptr [eax + edx*4]
        db 08Dh, 087h, 0E0h, 000h, 000h, 000h   ; lea eax, [edi + 0xe0]
        db 051h   ; push ecx
        db 050h   ; push eax
        db 0FFh, 097h, 0A4h, 000h, 000h, 000h   ; call dword ptr [edi + 0xa4]
        db 050h   ; push eax
        db 0EBh, 026h   ; jmp 0x23a419
$L_23a3f3:
        db 08Bh, 053h, 00Ch   ; mov edx, dword ptr [ebx + 0xc]
        db 08Bh, 004h, 082h   ; mov eax, dword ptr [edx + eax*4]
        db 08Bh, 049h, 00Ch   ; mov ecx, dword ptr [ecx + 0xc]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 02Bh, 004h, 091h   ; sub eax, dword ptr [ecx + edx*4]
        db 08Bh, 055h, 0FCh   ; mov edx, dword ptr [ebp - 4]
        db 08Bh, 04Bh, 008h   ; mov ecx, dword ptr [ebx + 8]
        db 08Bh, 00Ch, 091h   ; mov ecx, dword ptr [ecx + edx*4]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 040h, 008h   ; mov eax, dword ptr [eax + 8]
        db 02Bh, 00Ch, 090h   ; sub ecx, dword ptr [eax + edx*4]
        db 051h   ; push ecx
$L_23a419:
        db 056h   ; push esi
        db 0FFh, 056h, 050h   ; call dword ptr [esi + 0x50]
$L_23a41d:
        db 083h, 07Fh, 060h, 000h   ; cmp dword ptr [edi + 0x60], 0
        db 074h, 007h   ; je 0x23a42a
        db 050h   ; push eax
        db 056h   ; push esi
        call _itrp_CheckSingleWidth@8   ; 0x23A207
$L_23a42a:
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 0FFh, 074h, 08Fh, 014h   ; push dword ptr [edi + ecx*4 + 0x14]
        db 089h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], eax
        db 050h   ; push eax
        db 056h   ; push esi
        db 074h, 005h   ; je 0x23a444
        db 0FFh, 057h, 074h   ; call dword ptr [edi + 0x74]
        db 0EBh, 005h   ; jmp 0x23a449
$L_23a444:
        call _itrp_RoundOff@12   ; 0x2364ED
$L_23a449:
        db 0F6h, 045h, 010h, 008h   ; test byte ptr [ebp + 0x10], 8
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 074h, 02Dh   ; je 0x23a47f
        db 066h, 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [esi + 0x80], 0
        db 08Bh, 07Fh, 070h   ; mov edi, dword ptr [edi + 0x70]
        db 074h, 009h   ; je 0x23a468
        db 08Bh, 0C7h   ; mov eax, edi
        db 099h   ; cdq 
        db 02Bh, 0C2h   ; sub eax, edx
        db 0D1h, 0F8h   ; sar eax, 1
        db 08Bh, 0F8h   ; mov edi, eax
$L_23a468:
        db 083h, 07Dh, 0F0h, 000h   ; cmp dword ptr [ebp - 0x10], 0
        db 07Ch, 007h   ; jl 0x23a475
        db 039h, 07Dh, 0F4h   ; cmp dword ptr [ebp - 0xc], edi
        db 07Dh, 00Ch   ; jge 0x23a47f
        db 0EBh, 007h   ; jmp 0x23a47c
$L_23a475:
        db 0F7h, 0DFh   ; neg edi
        db 039h, 07Dh, 0F4h   ; cmp dword ptr [ebp - 0xc], edi
        db 07Eh, 003h   ; jle 0x23a47f
$L_23a47c:
        db 089h, 07Dh, 0F4h   ; mov dword ptr [ebp - 0xc], edi
$L_23a47f:
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 048h, 004h   ; mov ecx, dword ptr [eax + 4]
        db 08Bh, 043h, 004h   ; mov eax, dword ptr [ebx + 4]
        db 08Bh, 07Dh, 0FCh   ; mov edi, dword ptr [ebp - 4]
        db 08Bh, 014h, 0B8h   ; mov edx, dword ptr [eax + edi*4]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 02Bh, 014h, 081h   ; sub edx, dword ptr [ecx + eax*4]
        db 08Bh, 00Bh   ; mov ecx, dword ptr [ebx]
        db 08Bh, 00Ch, 0B9h   ; mov ecx, dword ptr [ecx + edi*4]
        db 052h   ; push edx
        db 08Bh, 055h, 0F8h   ; mov edx, dword ptr [ebp - 8]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 02Bh, 00Ch, 082h   ; sub ecx, dword ptr [edx + eax*4]
        db 051h   ; push ecx
        db 056h   ; push esi
        db 0FFh, 056h, 04Ch   ; call dword ptr [esi + 0x4c]
        db 029h, 045h, 0F4h   ; sub dword ptr [ebp - 0xc], eax
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 057h   ; push edi
        db 053h   ; push ebx
        db 056h   ; push esi
        db 0FFh, 056h, 048h   ; call dword ptr [esi + 0x48]
        db 0F6h, 045h, 010h, 010h   ; test byte ptr [ebp + 0x10], 0x10
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 089h, 046h, 030h   ; mov dword ptr [esi + 0x30], eax
        db 089h, 07Eh, 034h   ; mov dword ptr [esi + 0x34], edi
        db 074h, 003h   ; je 0x23a4c5
        db 089h, 07Eh, 02Ch   ; mov dword ptr [esi + 0x2c], edi
$L_23a4c5:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0E9h, 0DAh, 0FDh, 0FFh, 0FFh   ; jmp 0x23a2a7
seg19 ENDS

seg42 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_MIRP@12 @ 0x0023A4CD
PUBLIC _itrp_MIRP@12
_itrp_MIRP@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 018h   ; sub esp, 0x18
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 057h   ; push edi
        db 08Bh, 079h, 024h   ; mov edi, dword ptr [ecx + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 017h   ; cmp edx, dword ptr [edi]
        db 073h, 00Fh   ; jae 0x23a4f3
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0E9h, 0B2h, 005h, 000h, 000h   ; jmp 0x23aaa5
$L_23a4f3:
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 053h   ; push ebx
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 00Fh, 0B7h, 09Fh, 034h, 001h, 000h, 000h   ; movzx ebx, word ptr [edi + 0x134]
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 03Bh, 0D3h   ; cmp edx, ebx
        db 056h   ; push esi
        db 08Bh, 071h, 004h   ; mov esi, dword ptr [ecx + 4]
        db 089h, 055h, 0E8h   ; mov dword ptr [ebp - 0x18], edx
        db 00Fh, 08Dh, 082h, 005h, 000h, 000h   ; jge 0x23aa99
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 08Ch, 07Ah, 005h, 000h, 000h   ; jl 0x23aa99
        db 08Bh, 051h, 020h   ; mov edx, dword ptr [ecx + 0x20]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 03Bh, 0D6h   ; cmp edx, esi
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 075h, 01Eh   ; jne 0x23a54f
        db 08Bh, 09Fh, 030h, 001h, 000h, 000h   ; mov ebx, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 05Bh, 010h   ; movzx ebx, word ptr [ebx + 0x10]
        db 03Bh, 0C3h   ; cmp eax, ebx
$L_23a53d:
        db 07Dh, 004h   ; jge 0x23a543
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 014h   ; jge 0x23a557
$L_23a543:
        db 0C7h, 041h, 06Ch, 012h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1112
        db 0E9h, 051h, 005h, 000h, 000h   ; jmp 0x23aaa0
$L_23a54f:
        db 03Bh, 087h, 060h, 001h, 000h, 000h   ; cmp eax, dword ptr [edi + 0x160]
        db 0EBh, 0E6h   ; jmp 0x23a53d
$L_23a557:
        db 03Bh, 055h, 0F0h   ; cmp edx, dword ptr [ebp - 0x10]
        db 08Bh, 059h, 02Ch   ; mov ebx, dword ptr [ecx + 0x2c]
        db 00Fh, 085h, 010h, 001h, 000h, 000h   ; jne 0x23a673
        db 08Bh, 087h, 030h, 001h, 000h, 000h   ; mov eax, dword ptr [edi + 0x130]
        db 00Fh, 0B7h, 040h, 010h   ; movzx eax, word ptr [eax + 0x10]
        db 03Bh, 0D8h   ; cmp ebx, eax
$L_23a56f:
        db 07Dh, 0D2h   ; jge 0x23a543
        db 085h, 0DBh   ; test ebx, ebx
        db 07Ch, 0CEh   ; jl 0x23a543
        db 03Bh, 0F2h   ; cmp esi, edx
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 089h, 059h, 030h   ; mov dword ptr [ecx + 0x30], ebx
        db 089h, 041h, 034h   ; mov dword ptr [ecx + 0x34], eax
        db 074h, 03Eh   ; je 0x23a5c0
        db 080h, 0BFh, 025h, 001h, 000h, 000h, 002h   ; cmp byte ptr [edi + 0x125], 2
        db 075h, 035h   ; jne 0x23a5c0
        db 066h, 083h, 0B9h, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [ecx + 0x80], 0
        db 074h, 02Bh   ; je 0x23a5c0
        db 0F6h, 087h, 06Ch, 001h, 000h, 000h, 002h   ; test byte ptr [edi + 0x16c], 2
        db 074h, 022h   ; je 0x23a5c0
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 083h, 0E0h, 003h   ; and eax, 3
        db 050h   ; push eax
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 053h   ; push ebx
        db 056h   ; push esi
        call _DoubleCheckLinkColor@16   ; 0x23605D
        db 050h   ; push eax
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call _AddDistance@20   ; 0x235C12
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
$L_23a5c0:
        db 066h, 08Bh, 041h, 068h   ; mov ax, word ptr [ecx + 0x68]
        db 066h, 085h, 0C0h   ; test ax, ax
        db 00Fh, 085h, 052h, 002h, 000h, 000h   ; jne 0x23a81f
        db 0FFh, 075h, 0E8h   ; push dword ptr [ebp - 0x18]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 050h   ; push eax
        db 0FFh, 050h, 058h   ; call dword ptr [eax + 0x58]
        db 083h, 07Fh, 060h, 000h   ; cmp dword ptr [edi + 0x60], 0
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 074h, 00Ch   ; je 0x23a5ec
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call _itrp_CheckSingleWidth@8   ; 0x23A207
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
$L_23a5ec:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 03Bh, 070h, 020h   ; cmp esi, dword ptr [eax + 0x20]
        db 075h, 058h   ; jne 0x23a64c
        db 00Fh, 0BFh, 040h, 00Ch   ; movsx eax, word ptr [eax + 0xc]
        db 050h   ; push eax
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        call _ShortFracMul@8   ; 0x23590D
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 049h, 008h   ; mov ecx, dword ptr [ecx + 8]
        db 003h, 004h, 099h   ; add eax, dword ptr [ecx + ebx*4]
        db 08Bh, 04Eh, 008h   ; mov ecx, dword ptr [esi + 8]
        db 08Bh, 055h, 0F4h   ; mov edx, dword ptr [ebp - 0xc]
        db 089h, 004h, 091h   ; mov dword ptr [ecx + edx*4], eax
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 08Bh, 004h, 090h   ; mov eax, dword ptr [eax + edx*4]
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 089h, 004h, 091h   ; mov dword ptr [ecx + edx*4], eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Fh, 0BFh, 040h, 00Eh   ; movsx eax, word ptr [eax + 0xe]
        db 050h   ; push eax
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        call _ShortFracMul@8   ; 0x23590D
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 049h, 00Ch   ; mov ecx, dword ptr [ecx + 0xc]
        db 003h, 004h, 099h   ; add eax, dword ptr [ecx + ebx*4]
        db 08Bh, 04Eh, 00Ch   ; mov ecx, dword ptr [esi + 0xc]
        db 08Bh, 055h, 0F4h   ; mov edx, dword ptr [ebp - 0xc]
        db 089h, 004h, 091h   ; mov dword ptr [ecx + edx*4], eax
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 08Bh, 04Eh, 004h   ; mov ecx, dword ptr [esi + 4]
        db 08Bh, 004h, 090h   ; mov eax, dword ptr [eax + edx*4]
        db 089h, 004h, 091h   ; mov dword ptr [ecx + edx*4], eax
$L_23a64c:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 040h, 050h   ; mov eax, dword ptr [eax + 0x50]
        db 0C1h, 0E3h, 002h   ; shl ebx, 2
        db 03Dh   ; cmp eax, 0x23a06a
        dd _itrp_EIF@12
        db 089h, 045h, 0E8h   ; mov dword ptr [ebp - 0x18], eax
        db 075h, 01Fh   ; jne 0x23a67e
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 055h, 0F4h   ; mov edx, dword ptr [ebp - 0xc]
        db 08Bh, 049h, 008h   ; mov ecx, dword ptr [ecx + 8]
        db 08Bh, 004h, 090h   ; mov eax, dword ptr [eax + edx*4]
        db 02Bh, 004h, 019h   ; sub eax, dword ptr [ecx + ebx]
        db 0EBh, 052h   ; jmp 0x23a6c5
$L_23a673:
        db 03Bh, 09Fh, 060h, 001h, 000h, 000h   ; cmp ebx, dword ptr [edi + 0x160]
        db 0E9h, 0F1h, 0FEh, 0FFh, 0FFh   ; jmp 0x23a56f
$L_23a67e:
        db 03Dh   ; cmp eax, 0x236796
        dd _sub_236796
        db 075h, 017h   ; jne 0x23a69c
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 055h, 0F4h   ; mov edx, dword ptr [ebp - 0xc]
        db 08Bh, 049h, 00Ch   ; mov ecx, dword ptr [ecx + 0xc]
        db 08Bh, 004h, 090h   ; mov eax, dword ptr [eax + edx*4]
        db 02Bh, 004h, 019h   ; sub eax, dword ptr [ecx + ebx]
        db 089h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], eax
        db 0EBh, 02Ch   ; jmp 0x23a6c8
$L_23a69c:
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 050h, 00Ch   ; mov edx, dword ptr [eax + 0xc]
        db 08Bh, 04Eh, 00Ch   ; mov ecx, dword ptr [esi + 0xc]
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 08Bh, 00Ch, 081h   ; mov ecx, dword ptr [ecx + eax*4]
        db 02Bh, 00Ch, 01Ah   ; sub ecx, dword ptr [edx + ebx]
        db 08Bh, 055h, 0F0h   ; mov edx, dword ptr [ebp - 0x10]
        db 08Bh, 052h, 008h   ; mov edx, dword ptr [edx + 8]
        db 051h   ; push ecx
        db 08Bh, 04Eh, 008h   ; mov ecx, dword ptr [esi + 8]
        db 08Bh, 004h, 081h   ; mov eax, dword ptr [ecx + eax*4]
        db 02Bh, 004h, 01Ah   ; sub eax, dword ptr [edx + ebx]
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0FFh, 055h, 0E8h   ; call dword ptr [ebp - 0x18]
$L_23a6c5:
        db 089h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], eax
$L_23a6c8:
        db 08Bh, 0C8h   ; mov ecx, eax
        db 033h, 04Dh, 0F8h   ; xor ecx, dword ptr [ebp - 8]
        db 07Dh, 00Ch   ; jge 0x23a6db
        db 080h, 0BFh, 090h, 000h, 000h, 000h, 000h   ; cmp byte ptr [edi + 0x90], 0
        db 074h, 003h   ; je 0x23a6db
        db 0F7h, 05Dh, 0F8h   ; neg dword ptr [ebp - 8]
$L_23a6db:
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 066h, 083h, 0BAh, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [edx + 0x80], 0
        db 08Bh, 04Ch, 08Fh, 014h   ; mov ecx, dword ptr [edi + ecx*4 + 0x14]
        db 089h, 04Dh, 0E8h   ; mov dword ptr [ebp - 0x18], ecx
        db 074h, 04Dh   ; je 0x23a742
        db 066h, 08Bh, 04Fh, 06Ch   ; mov cx, word ptr [edi + 0x6c]
        db 066h, 083h, 0E1h, 004h   ; and cx, 4
        db 066h, 089h, 04Dh, 0FEh   ; mov word ptr [ebp - 2], cx
        db 075h, 018h   ; jne 0x23a71b
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 02Bh, 0C8h   ; sub ecx, eax
        db 0C1h, 0E1h, 004h   ; shl ecx, 4
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 07Fh, 006h   ; jg 0x23a718
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 07Dh, 003h   ; jge 0x23a71b
$L_23a718:
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
$L_23a71b:
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 074h, 011h   ; je 0x23a732
        db 066h, 083h, 07Dh, 0FEh, 000h   ; cmp word ptr [ebp - 2], 0
        db 074h, 035h   ; je 0x23a75d
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 02Bh, 0C8h   ; sub ecx, eax
        db 0C1h, 0E1h, 004h   ; shl ecx, 4
        db 0EBh, 01Bh   ; jmp 0x23a74d
$L_23a732:
        db 0FFh, 075h, 0E8h   ; push dword ptr [ebp - 0x18]
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call _itrp_RoundOffSP@12   ; 0x236512
        db 0EBh, 035h   ; jmp 0x23a777
$L_23a742:
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 074h, 023h   ; je 0x23a76b
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 02Bh, 0C8h   ; sub ecx, eax
$L_23a74d:
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 07Fh, 006h   ; jg 0x23a75a
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 07Dh, 003h   ; jge 0x23a75d
$L_23a75a:
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
$L_23a75d:
        db 0FFh, 075h, 0E8h   ; push dword ptr [ebp - 0x18]
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0FFh, 057h, 074h   ; call dword ptr [edi + 0x74]
        db 0EBh, 00Ch   ; jmp 0x23a777
$L_23a76b:
        db 051h   ; push ecx
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        call _itrp_RoundOff@12   ; 0x2364ED
$L_23a777:
        db 0F6h, 045h, 010h, 008h   ; test byte ptr [ebp + 0x10], 8
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 074h, 030h   ; je 0x23a7b0
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 066h, 083h, 0B8h, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [eax + 0x80], 0
        db 08Bh, 07Fh, 070h   ; mov edi, dword ptr [edi + 0x70]
        db 074h, 009h   ; je 0x23a799
        db 08Bh, 0C7h   ; mov eax, edi
        db 099h   ; cdq 
        db 02Bh, 0C2h   ; sub eax, edx
        db 0D1h, 0F8h   ; sar eax, 1
        db 08Bh, 0F8h   ; mov edi, eax
$L_23a799:
        db 083h, 07Dh, 0ECh, 000h   ; cmp dword ptr [ebp - 0x14], 0
        db 07Ch, 007h   ; jl 0x23a7a6
        db 039h, 07Dh, 0F8h   ; cmp dword ptr [ebp - 8], edi
        db 07Dh, 00Ch   ; jge 0x23a7b0
        db 0EBh, 007h   ; jmp 0x23a7ad
$L_23a7a6:
        db 0F7h, 0DFh   ; neg edi
        db 039h, 07Dh, 0F8h   ; cmp dword ptr [ebp - 8], edi
        db 07Eh, 003h   ; jle 0x23a7b0
$L_23a7ad:
        db 089h, 07Dh, 0F8h   ; mov dword ptr [ebp - 8], edi
$L_23a7b0:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 040h, 04Ch   ; mov eax, dword ptr [eax + 0x4c]
        db 03Dh   ; cmp eax, 0x23a06a
        dd _itrp_EIF@12
        db 08Bh, 07Dh, 0F4h   ; mov edi, dword ptr [ebp - 0xc]
        db 089h, 045h, 0E8h   ; mov dword ptr [ebp - 0x18], eax
        db 075h, 00Fh   ; jne 0x23a7d2
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 08Bh, 004h, 0B8h   ; mov eax, dword ptr [eax + edi*4]
        db 02Bh, 004h, 00Bh   ; sub eax, dword ptr [ebx + ecx]
        db 0EBh, 039h   ; jmp 0x23a80b
$L_23a7d2:
        db 03Dh   ; cmp eax, 0x236796
        dd _sub_236796
        db 075h, 011h   ; jne 0x23a7ea
        db 08Bh, 046h, 004h   ; mov eax, dword ptr [esi + 4]
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 08Bh, 049h, 004h   ; mov ecx, dword ptr [ecx + 4]
        db 08Bh, 004h, 0B8h   ; mov eax, dword ptr [eax + edi*4]
        db 02Bh, 004h, 019h   ; sub eax, dword ptr [ecx + ebx]
        db 0EBh, 021h   ; jmp 0x23a80b
$L_23a7ea:
        db 08Bh, 04Eh, 004h   ; mov ecx, dword ptr [esi + 4]
        db 08Bh, 00Ch, 0B9h   ; mov ecx, dword ptr [ecx + edi*4]
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 050h, 004h   ; mov edx, dword ptr [eax + 4]
        db 02Bh, 00Ch, 01Ah   ; sub ecx, dword ptr [edx + ebx]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 051h   ; push ecx
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 08Bh, 00Ch, 0B9h   ; mov ecx, dword ptr [ecx + edi*4]
        db 02Bh, 00Ch, 003h   ; sub ecx, dword ptr [ebx + eax]
        db 051h   ; push ecx
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0FFh, 055h, 0E8h   ; call dword ptr [ebp - 0x18]
$L_23a80b:
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 02Bh, 0C8h   ; sub ecx, eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 051h   ; push ecx
        db 057h   ; push edi
        db 056h   ; push esi
        db 050h   ; push eax
        db 0FFh, 050h, 048h   ; call dword ptr [eax + 0x48]
        db 0E9h, 066h, 002h, 000h, 000h   ; jmp 0x23aa85
$L_23a81f:
        db 066h, 03Dh, 001h, 000h   ; cmp ax, 1
        db 08Bh, 047h, 008h   ; mov eax, dword ptr [edi + 8]
        db 00Fh, 085h, 038h, 001h, 000h, 000h   ; jne 0x23a964
        db 08Bh, 055h, 0E8h   ; mov edx, dword ptr [ebp - 0x18]
        db 08Bh, 004h, 090h   ; mov eax, dword ptr [eax + edx*4]
        db 08Bh, 055h, 0F0h   ; mov edx, dword ptr [ebp - 0x10]
        db 08Bh, 052h, 008h   ; mov edx, dword ptr [edx + 8]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 08Bh, 0C3h   ; mov eax, ebx
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 089h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], eax
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 08Bh, 01Ch, 098h   ; mov ebx, dword ptr [eax + ebx*4]
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 02Bh, 01Ch, 002h   ; sub ebx, dword ptr [edx + eax]
        db 08Bh, 0C3h   ; mov eax, ebx
        db 033h, 045h, 0F8h   ; xor eax, dword ptr [ebp - 8]
        db 07Dh, 00Ch   ; jge 0x23a865
        db 080h, 0BFh, 090h, 000h, 000h, 000h, 000h   ; cmp byte ptr [edi + 0x90], 0
        db 074h, 003h   ; je 0x23a865
        db 0F7h, 05Dh, 0F8h   ; neg dword ptr [ebp - 8]
$L_23a865:
        db 066h, 08Bh, 081h, 080h, 000h, 000h, 000h   ; mov ax, word ptr [ecx + 0x80]
        db 066h, 085h, 0C0h   ; test ax, ax
        db 074h, 064h   ; je 0x23a8d5
        db 066h, 08Bh, 047h, 06Ch   ; mov ax, word ptr [edi + 0x6c]
        db 066h, 025h, 004h, 000h   ; and ax, 4
        db 066h, 089h, 045h, 0FEh   ; mov word ptr [ebp - 2], ax
        db 075h, 018h   ; jne 0x23a897
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 02Bh, 0C3h   ; sub eax, ebx
        db 0C1h, 0E0h, 004h   ; shl eax, 4
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Fh, 006h   ; jg 0x23a894
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Dh, 003h   ; jge 0x23a897
$L_23a894:
        db 089h, 05Dh, 0F8h   ; mov dword ptr [ebp - 8], ebx
$L_23a897:
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 074h, 073h   ; je 0x23a910
        db 066h, 083h, 07Dh, 0FEh, 000h   ; cmp word ptr [ebp - 2], 0
        db 074h, 018h   ; je 0x23a8bc
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 02Bh, 0C3h   ; sub eax, ebx
        db 0C1h, 0E0h, 004h   ; shl eax, 4
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Fh, 006h   ; jg 0x23a8b9
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Dh, 003h   ; jge 0x23a8bc
$L_23a8b9:
        db 089h, 05Dh, 0F8h   ; mov dword ptr [ebp - 8], ebx
$L_23a8bc:
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 008h   ; jl 0x23a8cb
        db 083h, 0C0h, 002h   ; add eax, 2
        db 083h, 0E0h, 0FCh   ; and eax, 0xfffffffc
        db 0EBh, 033h   ; jmp 0x23a8fe
$L_23a8cb:
        db 06Ah, 002h   ; push 2
        db 05Ah   ; pop edx
        db 02Bh, 0D0h   ; sub edx, eax
        db 083h, 0E2h, 0FCh   ; and edx, 0xfffffffc
        db 0EBh, 036h   ; jmp 0x23a90b
$L_23a8d5:
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 074h, 035h   ; je 0x23a910
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 02Bh, 0C3h   ; sub eax, ebx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Fh, 006h   ; jg 0x23a8ed
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Dh, 004h   ; jge 0x23a8f1
$L_23a8ed:
        db 08Bh, 0C3h   ; mov eax, ebx
        db 0EBh, 003h   ; jmp 0x23a8f4
$L_23a8f1:
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
$L_23a8f4:
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 00Bh   ; jl 0x23a903
        db 083h, 0C0h, 020h   ; add eax, 0x20
        db 083h, 0E0h, 0C0h   ; and eax, 0xffffffc0
$L_23a8fe:
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 0EBh, 00Dh   ; jmp 0x23a910
$L_23a903:
        db 06Ah, 020h   ; push 0x20
        db 05Ah   ; pop edx
        db 02Bh, 0D0h   ; sub edx, eax
        db 083h, 0E2h, 0C0h   ; and edx, 0xffffffc0
$L_23a90b:
        db 0F7h, 0DAh   ; neg edx
        db 089h, 055h, 0F8h   ; mov dword ptr [ebp - 8], edx
$L_23a910:
        db 0F6h, 045h, 010h, 008h   ; test byte ptr [ebp + 0x10], 8
        db 074h, 02Bh   ; je 0x23a941
        db 066h, 083h, 0B9h, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [ecx + 0x80], 0
        db 08Bh, 07Fh, 070h   ; mov edi, dword ptr [edi + 0x70]
        db 074h, 009h   ; je 0x23a92c
        db 08Bh, 0C7h   ; mov eax, edi
        db 099h   ; cdq 
        db 02Bh, 0C2h   ; sub eax, edx
        db 0D1h, 0F8h   ; sar eax, 1
        db 08Bh, 0F8h   ; mov edi, eax
$L_23a92c:
        db 085h, 0DBh   ; test ebx, ebx
        db 07Ch, 007h   ; jl 0x23a937
        db 039h, 07Dh, 0F8h   ; cmp dword ptr [ebp - 8], edi
        db 07Dh, 00Ch   ; jge 0x23a941
        db 0EBh, 007h   ; jmp 0x23a93e
$L_23a937:
        db 0F7h, 0DFh   ; neg edi
        db 039h, 07Dh, 0F8h   ; cmp dword ptr [ebp - 8], edi
        db 07Eh, 003h   ; jle 0x23a941
$L_23a93e:
        db 089h, 07Dh, 0F8h   ; mov dword ptr [ebp - 8], edi
$L_23a941:
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 08Bh, 014h, 002h   ; mov edx, dword ptr [edx + eax]
        db 003h, 055h, 0F8h   ; add edx, dword ptr [ebp - 8]
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 089h, 014h, 087h   ; mov dword ptr [edi + eax*4], edx
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 003h, 0C2h   ; add eax, edx
        db 080h, 008h, 001h   ; or byte ptr [eax], 1
        db 0E9h, 024h, 001h, 000h, 000h   ; jmp 0x23aa88
$L_23a964:
        db 08Bh, 04Dh, 0E8h   ; mov ecx, dword ptr [ebp - 0x18]
        db 08Bh, 00Ch, 088h   ; mov ecx, dword ptr [eax + ecx*4]
        db 08Bh, 055h, 0F0h   ; mov edx, dword ptr [ebp - 0x10]
        db 08Bh, 052h, 00Ch   ; mov edx, dword ptr [edx + 0xc]
        db 08Bh, 0C3h   ; mov eax, ebx
        db 08Bh, 05Dh, 0F4h   ; mov ebx, dword ptr [ebp - 0xc]
        db 0C1h, 0E0h, 002h   ; shl eax, 2
        db 089h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], eax
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 08Bh, 01Ch, 098h   ; mov ebx, dword ptr [eax + ebx*4]
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 02Bh, 01Ch, 002h   ; sub ebx, dword ptr [edx + eax]
        db 08Bh, 0C3h   ; mov eax, ebx
        db 033h, 0C1h   ; xor eax, ecx
        db 07Dh, 00Bh   ; jge 0x23a998
        db 080h, 0BFh, 090h, 000h, 000h, 000h, 000h   ; cmp byte ptr [edi + 0x90], 0
        db 074h, 002h   ; je 0x23a998
        db 0F7h, 0D9h   ; neg ecx
$L_23a998:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 066h, 08Bh, 080h, 080h, 000h, 000h, 000h   ; mov ax, word ptr [eax + 0x80]
        db 066h, 085h, 0C0h   ; test ax, ax
        db 074h, 05Dh   ; je 0x23aa04
        db 066h, 08Bh, 047h, 06Ch   ; mov ax, word ptr [edi + 0x6c]
        db 066h, 025h, 004h, 000h   ; and ax, 4
        db 066h, 089h, 045h, 0FEh   ; mov word ptr [ebp - 2], ax
        db 075h, 016h   ; jne 0x23a9cb
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 02Bh, 0C3h   ; sub eax, ebx
        db 0C1h, 0E0h, 004h   ; shl eax, 4
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Fh, 006h   ; jg 0x23a9c9
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Dh, 002h   ; jge 0x23a9cb
$L_23a9c9:
        db 08Bh, 0CBh   ; mov ecx, ebx
$L_23a9cb:
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 074h, 064h   ; je 0x23aa35
        db 066h, 083h, 07Dh, 0FEh, 000h   ; cmp word ptr [ebp - 2], 0
        db 074h, 016h   ; je 0x23a9ee
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 02Bh, 0C3h   ; sub eax, ebx
        db 0C1h, 0E0h, 004h   ; shl eax, 4
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Fh, 006h   ; jg 0x23a9ec
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Dh, 002h   ; jge 0x23a9ee
$L_23a9ec:
        db 08Bh, 0CBh   ; mov ecx, ebx
$L_23a9ee:
        db 085h, 0C9h   ; test ecx, ecx
        db 07Ch, 008h   ; jl 0x23a9fa
        db 083h, 0C1h, 002h   ; add ecx, 2
        db 083h, 0E1h, 0FCh   ; and ecx, 0xfffffffc
        db 0EBh, 03Bh   ; jmp 0x23aa35
$L_23a9fa:
        db 06Ah, 002h   ; push 2
        db 058h   ; pop eax
        db 02Bh, 0C1h   ; sub eax, ecx
        db 083h, 0E0h, 0FCh   ; and eax, 0xfffffffc
        db 0EBh, 02Dh   ; jmp 0x23aa31
$L_23aa04:
        db 0F6h, 045h, 010h, 004h   ; test byte ptr [ebp + 0x10], 4
        db 074h, 02Bh   ; je 0x23aa35
        db 08Bh, 057h, 05Ch   ; mov edx, dword ptr [edi + 0x5c]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 02Bh, 0C3h   ; sub eax, ebx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Fh, 006h   ; jg 0x23aa1b
        db 0F7h, 0DAh   ; neg edx
        db 03Bh, 0C2h   ; cmp eax, edx
        db 07Dh, 002h   ; jge 0x23aa1d
$L_23aa1b:
        db 08Bh, 0CBh   ; mov ecx, ebx
$L_23aa1d:
        db 085h, 0C9h   ; test ecx, ecx
        db 07Ch, 008h   ; jl 0x23aa29
        db 083h, 0C1h, 020h   ; add ecx, 0x20
        db 083h, 0E1h, 0C0h   ; and ecx, 0xffffffc0
        db 0EBh, 00Ch   ; jmp 0x23aa35
$L_23aa29:
        db 06Ah, 020h   ; push 0x20
        db 058h   ; pop eax
        db 02Bh, 0C1h   ; sub eax, ecx
        db 083h, 0E0h, 0C0h   ; and eax, 0xffffffc0
$L_23aa31:
        db 0F7h, 0D8h   ; neg eax
        db 08Bh, 0C8h   ; mov ecx, eax
$L_23aa35:
        db 0F6h, 045h, 010h, 008h   ; test byte ptr [ebp + 0x10], 8
        db 074h, 02Bh   ; je 0x23aa66
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 066h, 083h, 0B8h, 080h, 000h, 000h, 000h, 000h   ; cmp word ptr [eax + 0x80], 0
        db 08Bh, 07Fh, 070h   ; mov edi, dword ptr [edi + 0x70]
        db 074h, 009h   ; je 0x23aa54
        db 08Bh, 0C7h   ; mov eax, edi
        db 099h   ; cdq 
        db 02Bh, 0C2h   ; sub eax, edx
        db 0D1h, 0F8h   ; sar eax, 1
        db 08Bh, 0F8h   ; mov edi, eax
$L_23aa54:
        db 085h, 0DBh   ; test ebx, ebx
        db 07Ch, 006h   ; jl 0x23aa5e
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 07Dh, 00Ah   ; jge 0x23aa66
        db 0EBh, 006h   ; jmp 0x23aa64
$L_23aa5e:
        db 0F7h, 0DFh   ; neg edi
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 07Eh, 002h   ; jle 0x23aa66
$L_23aa64:
        db 08Bh, 0CFh   ; mov ecx, edi
$L_23aa66:
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 08Bh, 055h, 0ECh   ; mov edx, dword ptr [ebp - 0x14]
        db 08Bh, 014h, 010h   ; mov edx, dword ptr [eax + edx]
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 003h, 0D1h   ; add edx, ecx
        db 08Bh, 04Eh, 004h   ; mov ecx, dword ptr [esi + 4]
        db 089h, 014h, 081h   ; mov dword ptr [ecx + eax*4], edx
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 003h, 0C1h   ; add eax, ecx
        db 080h, 008h, 002h   ; or byte ptr [eax], 2
$L_23aa85:
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
$L_23aa88:
        db 0F6h, 045h, 010h, 010h   ; test byte ptr [ebp + 0x10], 0x10
        db 074h, 006h   ; je 0x23aa94
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 089h, 041h, 02Ch   ; mov dword ptr [ecx + 0x2c], eax
$L_23aa94:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 00Ah   ; jmp 0x23aaa3
$L_23aa99:
        db 0C7h, 041h, 06Ch, 01Bh, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x111b
$L_23aaa0:
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
$L_23aaa3:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
$L_23aaa5:
        db 05Fh   ; pop edi
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_CALL@12 @ 0x0023AAAA
PUBLIC _itrp_CALL@12
_itrp_CALL@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 010h   ; sub esp, 0x10
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 04Eh, 018h   ; mov ecx, dword ptr [esi + 0x18]
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 033h, 0D2h   ; xor edx, edx
        db 057h   ; push edi
        db 08Dh, 079h, 0FCh   ; lea edi, [ecx - 4]
        db 03Bh, 038h   ; cmp edi, dword ptr [eax]
        db 088h, 055h, 0FCh   ; mov byte ptr [ebp - 4], dl
        db 088h, 055h, 0FDh   ; mov byte ptr [ebp - 3], dl
        db 088h, 055h, 0FEh   ; mov byte ptr [ebp - 2], dl
        db 088h, 055h, 0FFh   ; mov byte ptr [ebp - 1], dl
        db 089h, 055h, 0F8h   ; mov dword ptr [ebp - 8], edx
        db 073h, 00Ch   ; jae 0x23aae0
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0E9h, 0B5h, 001h, 000h, 000h   ; jmp 0x23ac95
$L_23aae0:
        db 083h, 0C1h, 0FCh   ; add ecx, -4
        db 089h, 04Eh, 018h   ; mov dword ptr [esi + 0x18], ecx
        db 08Bh, 0B8h, 030h, 001h, 000h, 000h   ; mov edi, dword ptr [eax + 0x130]
        db 00Fh, 0B7h, 07Fh, 014h   ; movzx edi, word ptr [edi + 0x14]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 03Bh, 0CFh   ; cmp ecx, edi
        db 00Fh, 08Dh, 094h, 001h, 000h, 000h   ; jge 0x23ac8e
        db 03Bh, 0CAh   ; cmp ecx, edx
        db 00Fh, 08Ch, 08Ch, 001h, 000h, 000h   ; jl 0x23ac8e
        db 08Bh, 090h, 094h, 000h, 000h, 000h   ; mov edx, dword ptr [eax + 0x94]
        db 08Dh, 03Ch, 0CAh   ; lea edi, [edx + ecx*8]
        db 066h, 08Bh, 057h, 006h   ; mov dx, word ptr [edi + 6]
        db 066h, 083h, 0FAh, 002h   ; cmp dx, 2
        db 072h, 00Ch   ; jb 0x23ab21
        db 0C7h, 046h, 06Ch, 015h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1115
        db 0E9h, 074h, 001h, 000h, 000h   ; jmp 0x23ac95
$L_23ab21:
        db 08Bh, 05Eh, 070h   ; mov ebx, dword ptr [esi + 0x70]
        db 00Fh, 0B7h, 0D2h   ; movzx edx, dx
        db 08Bh, 094h, 0D0h, 0B0h, 000h, 000h, 000h   ; mov edx, dword ptr [eax + edx*8 + 0xb0]
        db 003h, 017h   ; add edx, dword ptr [edi]
        db 083h, 0F9h, 040h   ; cmp ecx, 0x40
        db 089h, 05Dh, 0F4h   ; mov dword ptr [ebp - 0xc], ebx
        db 08Bh, 05Eh, 074h   ; mov ebx, dword ptr [esi + 0x74]
        db 089h, 05Dh, 0F0h   ; mov dword ptr [ebp - 0x10], ebx
        db 07Ch, 030h   ; jl 0x23ab6e
        db 083h, 0F9h, 042h   ; cmp ecx, 0x42
        db 07Fh, 02Bh   ; jg 0x23ab6e
        db 0F6h, 080h, 06Ch, 001h, 000h, 000h, 001h   ; test byte ptr [eax + 0x16c], 1
        db 074h, 022h   ; je 0x23ab6e
        db 0F6h, 040h, 06Ch, 004h   ; test byte ptr [eax + 0x6c], 4
        db 075h, 01Ch   ; jne 0x23ab6e
        db 066h, 0F7h, 080h, 06Eh, 001h, 000h, 000h, 000h, 002h   ; test word ptr [eax + 0x16e], 0x200
        db 076h, 011h   ; jbe 0x23ab6e
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 08Bh, 058h, 058h   ; mov ebx, dword ptr [eax + 0x58]
        db 083h, 060h, 058h, 000h   ; and dword ptr [eax + 0x58], 0
        db 089h, 05Dh, 008h   ; mov dword ptr [ebp + 8], ebx
        db 0C6h, 045h, 0FCh, 001h   ; mov byte ptr [ebp - 4], 1
$L_23ab6e:
        db 085h, 0C9h   ; test ecx, ecx
        db 07Ch, 005h   ; jl 0x23ab77
        db 083h, 0F9h, 001h   ; cmp ecx, 1
        db 07Eh, 005h   ; jle 0x23ab7c
$L_23ab77:
        db 083h, 0F9h, 004h   ; cmp ecx, 4
        db 075h, 02Dh   ; jne 0x23aba9
$L_23ab7c:
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 0F6h, 080h, 06Ch, 001h, 000h, 000h, 001h   ; test byte ptr [eax + 0x16c], 1
        db 074h, 021h   ; je 0x23aba9
        db 0F6h, 040h, 06Ch, 004h   ; test byte ptr [eax + 0x6c], 4
        db 075h, 01Bh   ; jne 0x23aba9
        db 066h, 0F7h, 080h, 06Eh, 001h, 000h, 000h, 000h, 004h   ; test word ptr [eax + 0x16e], 0x400
        db 076h, 010h   ; jbe 0x23aba9
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 08Bh, 058h, 060h   ; mov ebx, dword ptr [eax + 0x60]
        db 083h, 060h, 060h, 000h   ; and dword ptr [eax + 0x60], 0
        db 0C6h, 045h, 0FDh, 001h   ; mov byte ptr [ebp - 3], 1
        db 0EBh, 003h   ; jmp 0x23abac
$L_23aba9:
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
$L_23abac:
        db 083h, 0F9h, 020h   ; cmp ecx, 0x20
        db 075h, 025h   ; jne 0x23abd6
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 0F6h, 080h, 06Ch, 001h, 000h, 000h, 001h   ; test byte ptr [eax + 0x16c], 1
        db 074h, 053h   ; je 0x23ac10
        db 0F6h, 040h, 06Ch, 004h   ; test byte ptr [eax + 0x6c], 4
        db 075h, 04Dh   ; jne 0x23ac10
        db 005h, 06Eh, 001h, 000h, 000h   ; add eax, 0x16e
        db 066h, 0F7h, 000h, 000h, 001h   ; test word ptr [eax], 0x100
        db 076h, 041h   ; jbe 0x23ac10
        db 080h, 008h, 004h   ; or byte ptr [eax], 4
        db 0C6h, 045h, 0FEh, 001h   ; mov byte ptr [ebp - 2], 1
$L_23abd6:
        db 083h, 0F9h, 03Ah   ; cmp ecx, 0x3a
        db 075h, 035h   ; jne 0x23ac10
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 0F6h, 080h, 06Ch, 001h, 000h, 000h, 001h   ; test byte ptr [eax + 0x16c], 1
        db 074h, 029h   ; je 0x23ac10
        db 0F6h, 040h, 06Ch, 004h   ; test byte ptr [eax + 0x6c], 4
        db 075h, 023h   ; jne 0x23ac10
        db 005h, 06Eh, 001h, 000h, 000h   ; add eax, 0x16e
        db 066h, 0F7h, 000h, 000h, 010h   ; test word ptr [eax], 0x1000
        db 076h, 017h   ; jbe 0x23ac10
        db 080h, 008h, 010h   ; or byte ptr [eax], 0x10
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Bh, 048h, 05Ch   ; mov ecx, dword ptr [eax + 0x5c]
        db 089h, 04Dh, 0F8h   ; mov dword ptr [ebp - 8], ecx
        db 0C7h, 040h, 05Ch, 0FFh, 0FFh, 0FFh, 07Fh   ; mov dword ptr [eax + 0x5c], 0x7fffffff
        db 0C6h, 045h, 0FFh, 001h   ; mov byte ptr [ebp - 1], 1
$L_23ac10:
        db 0FFh, 04Eh, 07Ch   ; dec dword ptr [esi + 0x7c]
        db 075h, 009h   ; jne 0x23ac1e
        db 0C7h, 046h, 06Ch, 006h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1106
        db 0EBh, 077h   ; jmp 0x23ac95
$L_23ac1e:
        db 00Fh, 0B7h, 047h, 004h   ; movzx eax, word ptr [edi + 4]
        db 003h, 0C2h   ; add eax, edx
        db 050h   ; push eax
        db 052h   ; push edx
        db 056h   ; push esi
        db 0FFh, 056h, 054h   ; call dword ptr [esi + 0x54]
        db 0FFh, 046h, 07Ch   ; inc dword ptr [esi + 0x7c]
        db 080h, 07Dh, 0FFh, 000h   ; cmp byte ptr [ebp - 1], 0
        db 074h, 013h   ; je 0x23ac46
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Bh, 04Dh, 0F8h   ; mov ecx, dword ptr [ebp - 8]
        db 089h, 048h, 05Ch   ; mov dword ptr [eax + 0x5c], ecx
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 080h, 0A0h, 06Eh, 001h, 000h, 000h, 0EFh   ; and byte ptr [eax + 0x16e], 0xef
$L_23ac46:
        db 080h, 07Dh, 0FEh, 000h   ; cmp byte ptr [ebp - 2], 0
        db 074h, 00Ah   ; je 0x23ac56
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 080h, 0A0h, 06Eh, 001h, 000h, 000h, 0FBh   ; and byte ptr [eax + 0x16e], 0xfb
$L_23ac56:
        db 080h, 07Dh, 0FDh, 000h   ; cmp byte ptr [ebp - 3], 0
        db 074h, 009h   ; je 0x23ac65
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 089h, 058h, 060h   ; mov dword ptr [eax + 0x60], ebx
$L_23ac65:
        db 080h, 07Dh, 0FCh, 000h   ; cmp byte ptr [ebp - 4], 0
        db 074h, 00Ch   ; je 0x23ac77
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 089h, 048h, 058h   ; mov dword ptr [eax + 0x58], ecx
$L_23ac77:
        db 083h, 07Eh, 06Ch, 000h   ; cmp dword ptr [esi + 0x6c], 0
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 08Bh, 04Dh, 0F0h   ; mov ecx, dword ptr [ebp - 0x10]
        db 089h, 046h, 070h   ; mov dword ptr [esi + 0x70], eax
        db 089h, 04Eh, 074h   ; mov dword ptr [esi + 0x74], ecx
        db 075h, 00Fh   ; jne 0x23ac98
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 00Ah   ; jmp 0x23ac98
$L_23ac8e:
        db 0C7h, 046h, 06Ch, 014h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1114
$L_23ac95:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_23ac98:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_FDEF@12 @ 0x0023AC9F
PUBLIC _itrp_FDEF@12
_itrp_FDEF@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 038h   ; sub esp, 0x38
        db 033h, 0C0h   ; xor eax, eax
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 0C6h, 045h, 0C8h, 001h   ; mov byte ptr [ebp - 0x38], 1
        db 0C6h, 045h, 0C9h, 020h   ; mov byte ptr [ebp - 0x37], 0x20
        db 0C6h, 045h, 0CAh, 0B0h   ; mov byte ptr [ebp - 0x36], 0xb0
        db 0C6h, 045h, 0CBh, 003h   ; mov byte ptr [ebp - 0x35], 3
        db 0C6h, 045h, 0CCh, 025h   ; mov byte ptr [ebp - 0x34], 0x25
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 04Ah, 024h   ; mov ecx, dword ptr [edx + 0x24]
        db 08Dh, 07Dh, 0CDh   ; lea edi, [ebp - 0x33]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0AAh   ; stosb byte ptr es:[edi], al
        db 033h, 0C0h   ; xor eax, eax
        db 0C6h, 045h, 0D2h, 0B0h   ; mov byte ptr [ebp - 0x2e], 0xb0
        db 0C6h, 045h, 0D3h, 016h   ; mov byte ptr [ebp - 0x2d], 0x16
        db 0C6h, 045h, 0D4h, 043h   ; mov byte ptr [ebp - 0x2c], 0x43
        db 0C6h, 045h, 0D5h, 058h   ; mov byte ptr [ebp - 0x2b], 0x58
        db 08Dh, 07Dh, 0D6h   ; lea edi, [ebp - 0x2a]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 066h, 0ABh   ; stosw word ptr es:[edi], ax
        db 033h, 0C0h   ; xor eax, eax
        db 0C6h, 045h, 0DCh, 001h   ; mov byte ptr [ebp - 0x24], 1
        db 0C6h, 045h, 0DDh, 0B0h   ; mov byte ptr [ebp - 0x23], 0xb0
        db 0C6h, 045h, 0DEh, 018h   ; mov byte ptr [ebp - 0x22], 0x18
        db 0C6h, 045h, 0DFh, 043h   ; mov byte ptr [ebp - 0x21], 0x43
        db 0C6h, 045h, 0E0h, 058h   ; mov byte ptr [ebp - 0x20], 0x58
        db 08Dh, 07Dh, 0E1h   ; lea edi, [ebp - 0x1f]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0AAh   ; stosb byte ptr es:[edi], al
        db 033h, 0C0h   ; xor eax, eax
        db 0C6h, 045h, 0E6h, 045h   ; mov byte ptr [ebp - 0x1a], 0x45
        db 0C6h, 045h, 0E7h, 023h   ; mov byte ptr [ebp - 0x19], 0x23
        db 0C6h, 045h, 0E8h, 046h   ; mov byte ptr [ebp - 0x18], 0x46
        db 0C6h, 045h, 0E9h, 060h   ; mov byte ptr [ebp - 0x17], 0x60
        db 0C6h, 045h, 0EAh, 020h   ; mov byte ptr [ebp - 0x16], 0x20
        db 0C6h, 045h, 0EBh, 0B0h   ; mov byte ptr [ebp - 0x15], 0xb0
        db 0C6h, 045h, 0ECh, 026h   ; mov byte ptr [ebp - 0x14], 0x26
        db 08Dh, 07Dh, 0EDh   ; lea edi, [ebp - 0x13]
        db 066h, 0ABh   ; stosw word ptr es:[edi], ax
        db 0AAh   ; stosb byte ptr es:[edi], al
        db 08Bh, 042h, 018h   ; mov eax, dword ptr [edx + 0x18]
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 031h   ; cmp esi, dword ptr [ecx]
        db 0C6h, 045h, 0F0h, 020h   ; mov byte ptr [ebp - 0x10], 0x20
        db 0C6h, 045h, 0F1h, 020h   ; mov byte ptr [ebp - 0xf], 0x20
        db 0C6h, 045h, 0F2h, 0B0h   ; mov byte ptr [ebp - 0xe], 0xb0
        db 0C6h, 045h, 0F3h, 001h   ; mov byte ptr [ebp - 0xd], 1
        db 0C6h, 045h, 0F4h, 060h   ; mov byte ptr [ebp - 0xc], 0x60
        db 0C6h, 045h, 0F5h, 046h   ; mov byte ptr [ebp - 0xb], 0x46
        db 0C6h, 045h, 0F6h, 0B0h   ; mov byte ptr [ebp - 0xa], 0xb0
        db 0C6h, 045h, 0F7h, 040h   ; mov byte ptr [ebp - 9], 0x40
        db 0C6h, 045h, 0F8h, 023h   ; mov byte ptr [ebp - 8], 0x23
        db 0C6h, 045h, 0F9h, 042h   ; mov byte ptr [ebp - 7], 0x42
        db 073h, 00Fh   ; jae 0x23ad60
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
        db 0C7h, 042h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1110
        db 0E9h, 056h, 001h, 000h, 000h   ; jmp 0x23aeb6
$L_23ad60:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 042h, 018h   ; mov dword ptr [edx + 0x18], eax
        db 053h   ; push ebx
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 08Bh, 081h, 030h, 001h, 000h, 000h   ; mov eax, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 040h, 014h   ; movzx eax, word ptr [eax + 0x14]
        db 03Bh, 0D8h   ; cmp ebx, eax
        db 00Fh, 08Dh, 030h, 001h, 000h, 000h   ; jge 0x23aeab
        db 085h, 0DBh   ; test ebx, ebx
        db 00Fh, 08Ch, 028h, 001h, 000h, 000h   ; jl 0x23aeab
        db 08Ah, 081h, 025h, 001h, 000h, 000h   ; mov al, byte ptr [ecx + 0x125]
        db 03Ch, 002h   ; cmp al, 2
        db 072h, 00Ch   ; jb 0x23ad99
        db 0C7h, 042h, 06Ch, 008h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1108
        db 0E9h, 019h, 001h, 000h, 000h   ; jmp 0x23aeb2
$L_23ad99:
        db 08Bh, 0B1h, 094h, 000h, 000h, 000h   ; mov esi, dword ptr [ecx + 0x94]
        db 066h, 00Fh, 0B6h, 0C0h   ; movzx ax, al
        db 08Dh, 034h, 0DEh   ; lea esi, [esi + ebx*8]
        db 066h, 089h, 046h, 006h   ; mov word ptr [esi + 6], ax
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        db 00Fh, 0B7h, 0F0h   ; movzx esi, ax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 08Bh, 0F8h   ; mov edi, eax
        db 02Bh, 0BCh, 0F1h, 0B0h, 000h, 000h, 000h   ; sub edi, dword ptr [ecx + esi*8 + 0xb0]
        db 083h, 0FBh, 020h   ; cmp ebx, 0x20
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 089h, 039h   ; mov dword ptr [ecx], edi
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        db 075h, 01Fh   ; jne 0x23ade8
        db 06Ah, 005h   ; push 5
        db 08Bh, 0F0h   ; mov esi, eax
        db 059h   ; pop ecx
        db 08Dh, 07Dh, 0C8h   ; lea edi, [ebp - 0x38]
        db 033h, 0C0h   ; xor eax, eax
        db 0F3h, 0A6h   ; repe cmpsb byte ptr [esi], byte ptr es:[edi]
        db 00Fh, 085h, 092h, 000h, 000h, 000h   ; jne 0x23ae6d
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 080h, 088h, 06Fh, 001h, 000h, 000h, 001h   ; or byte ptr [eax + 0x16f], 1
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
$L_23ade8:
        db 083h, 0FBh, 040h   ; cmp ebx, 0x40
        db 07Ch, 018h   ; jl 0x23ae05
        db 083h, 0FBh, 042h   ; cmp ebx, 0x42
        db 07Fh, 013h   ; jg 0x23ae05
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 08Dh, 04Dh, 0D2h   ; lea ecx, [ebp - 0x2e]
        db 03Bh, 031h   ; cmp esi, dword ptr [ecx]
        db 075h, 00Ah   ; jne 0x23ae05
        db 08Bh, 04Ah, 024h   ; mov ecx, dword ptr [edx + 0x24]
        db 080h, 089h, 06Fh, 001h, 000h, 000h, 002h   ; or byte ptr [ecx + 0x16f], 2
$L_23ae05:
        db 085h, 0DBh   ; test ebx, ebx
        db 07Ch, 005h   ; jl 0x23ae0e
        db 083h, 0FBh, 001h   ; cmp ebx, 1
        db 07Eh, 005h   ; jle 0x23ae13
$L_23ae0e:
        db 083h, 0FBh, 004h   ; cmp ebx, 4
        db 075h, 01Bh   ; jne 0x23ae2e
$L_23ae13:
        db 06Ah, 005h   ; push 5
        db 08Bh, 0F0h   ; mov esi, eax
        db 059h   ; pop ecx
        db 08Dh, 07Dh, 0DCh   ; lea edi, [ebp - 0x24]
        db 033h, 0C0h   ; xor eax, eax
        db 0F3h, 0A6h   ; repe cmpsb byte ptr [esi], byte ptr es:[edi]
        db 075h, 00Ah   ; jne 0x23ae2b
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 080h, 088h, 06Fh, 001h, 000h, 000h, 004h   ; or byte ptr [eax + 0x16f], 4
$L_23ae2b:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
$L_23ae2e:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 01Bh   ; jne 0x23ae4d
        db 06Ah, 007h   ; push 7
        db 08Bh, 0F0h   ; mov esi, eax
        db 059h   ; pop ecx
        db 08Dh, 07Dh, 0E6h   ; lea edi, [ebp - 0x1a]
        db 033h, 0C0h   ; xor eax, eax
        db 0F3h, 0A6h   ; repe cmpsb byte ptr [esi], byte ptr es:[edi]
        db 075h, 02Dh   ; jne 0x23ae6d
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 080h, 088h, 06Fh, 001h, 000h, 000h, 008h   ; or byte ptr [eax + 0x16f], 8
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
$L_23ae4d:
        db 083h, 0FBh, 03Ah   ; cmp ebx, 0x3a
        db 075h, 01Eh   ; jne 0x23ae70
        db 06Ah, 005h   ; push 5
        db 059h   ; pop ecx
        db 08Dh, 07Dh, 0F0h   ; lea edi, [ebp - 0x10]
        db 08Bh, 0F0h   ; mov esi, eax
        db 033h, 0DBh   ; xor ebx, ebx
        db 066h, 0F3h, 0A7h   ; repe cmpsw word ptr [esi], word ptr es:[edi]
        db 075h, 00Fh   ; jne 0x23ae70
        db 08Bh, 04Ah, 024h   ; mov ecx, dword ptr [edx + 0x24]
        db 080h, 089h, 06Fh, 001h, 000h, 000h, 010h   ; or byte ptr [ecx + 0x16f], 0x10
        db 0EBh, 003h   ; jmp 0x23ae70
$L_23ae6d:
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
$L_23ae70:
        db 080h, 038h, 02Dh   ; cmp byte ptr [eax], 0x2d
        db 074h, 014h   ; je 0x23ae89
        db 08Bh, 072h, 070h   ; mov esi, dword ptr [edx + 0x70]
$L_23ae78:
        db 040h   ; inc eax
        db 03Bh, 0C6h   ; cmp eax, esi
        db 073h, 00Dh   ; jae 0x23ae8a
        db 050h   ; push eax
        db 052h   ; push edx
        call _itrp_SkipPushData@8   ; 0x239F63
        db 080h, 038h, 02Dh   ; cmp byte ptr [eax], 0x2d
        db 075h, 0EFh   ; jne 0x23ae78
$L_23ae89:
        db 040h   ; inc eax
$L_23ae8a:
        db 03Bh, 042h, 070h   ; cmp eax, dword ptr [edx + 0x70]
        db 075h, 00Dh   ; jne 0x23ae9c
        db 080h, 078h, 0FFh, 02Dh   ; cmp byte ptr [eax - 1], 0x2d
        db 074h, 007h   ; je 0x23ae9c
        db 0C7h, 042h, 06Ch, 004h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1104
$L_23ae9c:
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 02Bh, 04Dh, 0FCh   ; sub ecx, dword ptr [ebp - 4]
        db 049h   ; dec ecx
        db 066h, 089h, 04Ah, 004h   ; mov word ptr [edx + 4], cx
        db 0EBh, 00Ah   ; jmp 0x23aeb5
$L_23aeab:
        db 0C7h, 042h, 06Ch, 014h, 011h, 000h, 000h   ; mov dword ptr [edx + 0x6c], 0x1114
$L_23aeb2:
        db 08Bh, 042h, 070h   ; mov eax, dword ptr [edx + 0x70]
$L_23aeb5:
        db 05Bh   ; pop ebx
$L_23aeb6:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_LOOPCALL@12 @ 0x0023AEBC
PUBLIC _itrp_LOOPCALL@12
_itrp_LOOPCALL@12:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 00Ch   ; sub esp, 0xc
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 04Eh, 024h   ; mov ecx, dword ptr [esi + 0x24]
        db 08Dh, 050h, 0F8h   ; lea edx, [eax - 8]
        db 03Bh, 011h   ; cmp edx, dword ptr [ecx]
        db 057h   ; push edi
        db 073h, 00Fh   ; jae 0x23aee3
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0E9h, 0BBh, 000h, 000h, 000h   ; jmp 0x23af9e
$L_23aee3:
        db 053h   ; push ebx
        db 08Dh, 058h, 0FCh   ; lea ebx, [eax - 4]
        db 089h, 05Eh, 018h   ; mov dword ptr [esi + 0x18], ebx
        db 08Bh, 091h, 030h, 001h, 000h, 000h   ; mov edx, dword ptr [ecx + 0x130]
        db 00Fh, 0B7h, 052h, 014h   ; movzx edx, word ptr [edx + 0x14]
        db 08Bh, 003h   ; mov eax, dword ptr [ebx]
        db 03Bh, 0C2h   ; cmp eax, edx
        db 00Fh, 08Dh, 095h, 000h, 000h, 000h   ; jge 0x23af93
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 08Ch, 08Dh, 000h, 000h, 000h   ; jl 0x23af93
        db 08Bh, 091h, 094h, 000h, 000h, 000h   ; mov edx, dword ptr [ecx + 0x94]
        db 08Dh, 004h, 0C2h   ; lea eax, [edx + eax*8]
        db 066h, 08Bh, 050h, 006h   ; mov dx, word ptr [eax + 6]
        db 066h, 083h, 0FAh, 002h   ; cmp dx, 2
        db 072h, 009h   ; jb 0x23af22
        db 0C7h, 046h, 06Ch, 015h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1115
        db 0EBh, 078h   ; jmp 0x23af9a
$L_23af22:
        db 00Fh, 0B7h, 0D2h   ; movzx edx, dx
        db 08Bh, 08Ch, 0D1h, 0B0h, 000h, 000h, 000h   ; mov ecx, dword ptr [ecx + edx*8 + 0xb0]
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 08Dh, 03Ch, 00Ah   ; lea edi, [edx + ecx]
        db 089h, 07Dh, 0FCh   ; mov dword ptr [ebp - 4], edi
        db 00Fh, 0B7h, 078h, 004h   ; movzx edi, word ptr [eax + 4]
        db 08Bh, 046h, 054h   ; mov eax, dword ptr [esi + 0x54]
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 08Dh, 043h, 0FCh   ; lea eax, [ebx - 4]
        db 08Bh, 05Eh, 070h   ; mov ebx, dword ptr [esi + 0x70]
        db 003h, 0FAh   ; add edi, edx
        db 003h, 0F9h   ; add edi, ecx
        db 08Bh, 04Eh, 074h   ; mov ecx, dword ptr [esi + 0x74]
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 0FFh, 04Eh, 07Ch   ; dec dword ptr [esi + 0x7c]
        db 089h, 04Dh, 0F4h   ; mov dword ptr [ebp - 0xc], ecx
        db 075h, 00Bh   ; jne 0x23af63
        db 0C7h, 046h, 06Ch, 006h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1106
$L_23af5f:
        db 08Bh, 0C3h   ; mov eax, ebx
        db 0EBh, 03Ah   ; jmp 0x23af9d
$L_23af63:
        db 048h   ; dec eax
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 078h, 013h   ; js 0x23af7c
$L_23af69:
        db 083h, 07Eh, 06Ch, 000h   ; cmp dword ptr [esi + 0x6c], 0
        db 075h, 00Dh   ; jne 0x23af7c
        db 057h   ; push edi
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 056h   ; push esi
        db 0FFh, 055h, 0F8h   ; call dword ptr [ebp - 8]
        db 0FFh, 04Dh, 008h   ; dec dword ptr [ebp + 8]
        db 079h, 0EDh   ; jns 0x23af69
$L_23af7c:
        db 0FFh, 046h, 07Ch   ; inc dword ptr [esi + 0x7c]
        db 083h, 07Eh, 06Ch, 000h   ; cmp dword ptr [esi + 0x6c], 0
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 089h, 05Eh, 070h   ; mov dword ptr [esi + 0x70], ebx
        db 089h, 046h, 074h   ; mov dword ptr [esi + 0x74], eax
        db 075h, 0D1h   ; jne 0x23af5f
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 0EBh, 00Ah   ; jmp 0x23af9d
$L_23af93:
        db 0C7h, 046h, 06Ch, 014h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1114
$L_23af9a:
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
$L_23af9d:
        db 05Bh   ; pop ebx
$L_23af9e:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg42 ENDS

seg21 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SDB@12 @ 0x0023B1C1
PUBLIC _itrp_SDB@12
_itrp_SDB@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x23b1e0
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 014h   ; jmp 0x23b1f4
$L_23b1e0:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 066h, 08Bh, 000h   ; mov ax, word ptr [eax]
        db 066h, 089h, 082h, 088h, 000h, 000h, 000h   ; mov word ptr [edx + 0x88], ax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_23b1f4:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg21 ENDS

seg43 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SDS@12 @ 0x0023B1F7
PUBLIC _itrp_SDS@12
_itrp_SDS@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 018h   ; mov eax, dword ptr [ecx + 0x18]
        db 08Bh, 051h, 024h   ; mov edx, dword ptr [ecx + 0x24]
        db 056h   ; push esi
        db 08Dh, 070h, 0FCh   ; lea esi, [eax - 4]
        db 03Bh, 032h   ; cmp esi, dword ptr [edx]
        db 05Eh   ; pop esi
        db 073h, 00Ch   ; jae 0x23b216
        db 08Bh, 041h, 070h   ; mov eax, dword ptr [ecx + 0x70]
        db 0C7h, 041h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [ecx + 0x6c], 0x1110
        db 0EBh, 014h   ; jmp 0x23b22a
$L_23b216:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 089h, 041h, 018h   ; mov dword ptr [ecx + 0x18], eax
        db 066h, 08Bh, 000h   ; mov ax, word ptr [eax]
        db 066h, 089h, 082h, 08Ah, 000h, 000h, 000h   ; mov word ptr [edx + 0x8a], ax
        db 08Bh, 044h, 024h, 008h   ; mov eax, dword ptr [esp + 8]
$L_23b22a:
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg43 ENDS

seg22 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_DELTAP1@12 @ 0x0023B42B
PUBLIC _itrp_DELTAP1@12
_itrp_DELTAP1@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 033h, 0D2h   ; xor edx, edx
        db 066h, 08Bh, 050h, 02Eh   ; mov dx, word ptr [eax + 0x2e]
        db 00Fh, 0BFh, 040h, 02Ch   ; movsx eax, word ptr [eax + 0x2c]
        db 052h   ; push edx
        db 050h   ; push eax
        db 0FFh, 071h, 048h   ; push dword ptr [ecx + 0x48]
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 051h   ; push ecx
        call _itrp_DeltaEngine@20   ; 0x23B22D
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg22 ENDS

seg44 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_DELTAP2@12 @ 0x0023B451
PUBLIC _itrp_DELTAP2@12
_itrp_DELTAP2@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 033h, 0C9h   ; xor ecx, ecx
        db 066h, 08Bh, 048h, 02Ch   ; mov cx, word ptr [eax + 0x2c]
        db 00Fh, 0BFh, 040h, 02Eh   ; movsx eax, word ptr [eax + 0x2e]
        db 066h, 083h, 0C1h, 010h   ; add cx, 0x10
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 072h, 048h   ; push dword ptr [edx + 0x48]
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 052h   ; push edx
        call _itrp_DeltaEngine@20   ; 0x23B22D
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_DELTAP3@12 @ 0x0023B47B
PUBLIC _itrp_DELTAP3@12
_itrp_DELTAP3@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 033h, 0C9h   ; xor ecx, ecx
        db 066h, 08Bh, 048h, 02Ch   ; mov cx, word ptr [eax + 0x2c]
        db 00Fh, 0BFh, 040h, 02Eh   ; movsx eax, word ptr [eax + 0x2e]
        db 066h, 083h, 0C1h, 020h   ; add cx, 0x20
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 072h, 048h   ; push dword ptr [edx + 0x48]
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 052h   ; push edx
        call _itrp_DeltaEngine@20   ; 0x23B22D
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_DELTAC1@12 @ 0x0023B4A5
PUBLIC _itrp_DELTAC1@12
_itrp_DELTAC1@12:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 08Bh, 041h, 024h   ; mov eax, dword ptr [ecx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 033h, 0D2h   ; xor edx, edx
        db 066h, 08Bh, 050h, 02Eh   ; mov dx, word ptr [eax + 0x2e]
        db 00Fh, 0BFh, 040h, 02Ch   ; movsx eax, word ptr [eax + 0x2c]
        db 052h   ; push edx
        db 050h   ; push eax
        db 0FFh, 071h, 060h   ; push dword ptr [ecx + 0x60]
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 051h   ; push ecx
        call _itrp_DeltaEngine@20   ; 0x23B22D
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_DELTAC2@12 @ 0x0023B4CB
PUBLIC _itrp_DELTAC2@12
_itrp_DELTAC2@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 033h, 0C9h   ; xor ecx, ecx
        db 066h, 08Bh, 048h, 02Ch   ; mov cx, word ptr [eax + 0x2c]
        db 00Fh, 0BFh, 040h, 02Eh   ; movsx eax, word ptr [eax + 0x2e]
        db 066h, 083h, 0C1h, 010h   ; add cx, 0x10
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 072h, 060h   ; push dword ptr [edx + 0x60]
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 052h   ; push edx
        call _itrp_DeltaEngine@20   ; 0x23B22D
        db 0C2h, 00Ch, 000h   ; ret 0xc
; // match: _itrp_DELTAC3@12 @ 0x0023B4F5
PUBLIC _itrp_DELTAC3@12
_itrp_DELTAC3@12:
        db 08Bh, 054h, 024h, 004h   ; mov edx, dword ptr [esp + 4]
        db 08Bh, 042h, 024h   ; mov eax, dword ptr [edx + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 033h, 0C9h   ; xor ecx, ecx
        db 066h, 08Bh, 048h, 02Ch   ; mov cx, word ptr [eax + 0x2c]
        db 00Fh, 0BFh, 040h, 02Eh   ; movsx eax, word ptr [eax + 0x2e]
        db 066h, 083h, 0C1h, 020h   ; add cx, 0x20
        db 050h   ; push eax
        db 051h   ; push ecx
        db 0FFh, 072h, 060h   ; push dword ptr [edx + 0x60]
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 052h   ; push edx
        call _itrp_DeltaEngine@20   ; 0x23B22D
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg44 ENDS

seg23 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_SROUND@12 @ 0x0023B572
PUBLIC _itrp_SROUND@12
_itrp_SROUND@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 08Dh, 048h, 0FCh   ; lea ecx, [eax - 4]
        db 03Bh, 00Ah   ; cmp ecx, dword ptr [edx]
        db 073h, 00Ch   ; jae 0x23b590
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 038h   ; jmp 0x23b5c8
$L_23b590:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 06Ah, 001h   ; push 1
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 0FFh, 030h   ; push dword ptr [eax]
        db 056h   ; push esi
        call _itrp_SetRoundValues@12   ; 0x237853
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 006h, 000h   ; mov word ptr [eax + 0x1c], 6
        db 00Fh, 0B7h, 08Eh, 080h, 000h, 000h, 000h   ; movzx ecx, word ptr [esi + 0x80]
        db 0C1h, 0E1h, 005h   ; shl ecx, 5
        db 08Bh, 089h   ; mov ecx, dword ptr [ecx + 0x3ecf18]
        dd _unk_3ECF18
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 066h, 083h, 066h, 068h, 000h   ; and word ptr [esi + 0x68], 0
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_23b5c8:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg23 ENDS

seg45 SEGMENT BYTE PUBLIC ALIAS('.text') 'CODE'

; // match: _itrp_S45ROUND@12 @ 0x0023B5CC
PUBLIC _itrp_S45ROUND@12
_itrp_S45ROUND@12:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 08Bh, 046h, 018h   ; mov eax, dword ptr [esi + 0x18]
        db 08Bh, 056h, 024h   ; mov edx, dword ptr [esi + 0x24]
        db 08Dh, 048h, 0FCh   ; lea ecx, [eax - 4]
        db 03Bh, 00Ah   ; cmp ecx, dword ptr [edx]
        db 073h, 00Ch   ; jae 0x23b5ea
        db 08Bh, 046h, 070h   ; mov eax, dword ptr [esi + 0x70]
        db 0C7h, 046h, 06Ch, 010h, 011h, 000h, 000h   ; mov dword ptr [esi + 0x6c], 0x1110
        db 0EBh, 038h   ; jmp 0x23b622
$L_23b5ea:
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 06Ah, 000h   ; push 0
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 0FFh, 030h   ; push dword ptr [eax]
        db 056h   ; push esi
        call _itrp_SetRoundValues@12   ; 0x237853
        db 08Bh, 046h, 024h   ; mov eax, dword ptr [esi + 0x24]
        db 083h, 0C0h, 05Ch   ; add eax, 0x5c
        db 066h, 0C7h, 040h, 01Ch, 007h, 000h   ; mov word ptr [eax + 0x1c], 7
        db 00Fh, 0B7h, 08Eh, 080h, 000h, 000h, 000h   ; movzx ecx, word ptr [esi + 0x80]
        db 0C1h, 0E1h, 005h   ; shl ecx, 5
        db 08Bh, 089h   ; mov ecx, dword ptr [ecx + 0x3ecf1c]
        dd _unk_3ECF1C
        db 089h, 048h, 018h   ; mov dword ptr [eax + 0x18], ecx
        db 066h, 083h, 066h, 068h, 000h   ; and word ptr [esi + 0x68], 0
        db 08Bh, 044h, 024h, 00Ch   ; mov eax, dword ptr [esp + 0xc]
$L_23b622:
        db 05Eh   ; pop esi
        db 0C2h, 00Ch, 000h   ; ret 0xc

; // match: ??_ECDirectSoundStream@DirectSound@@W3AEPAXI@Z @ 0x0023B626
PUBLIC ??_ECDirectSoundStream@DirectSound@@W3AEPAXI@Z
??_ECDirectSoundStream@DirectSound@@W3AEPAXI@Z:
        db 083h, 0E9h, 004h   ; sub ecx, 4
        jmp ??_GCDirectSoundStream@DirectSound@@UAEPAXI@Z   ; 0x325005

; // match: ??_ECMcpxAPU@DirectSound@@W7AEPAXI@Z @ 0x0023B62E
PUBLIC ??_ECMcpxAPU@DirectSound@@W7AEPAXI@Z
??_ECMcpxAPU@DirectSound@@W7AEPAXI@Z:
        db 083h, 0E9h, 008h   ; sub ecx, 8
        jmp _unk_327ECE   ; 0x327ECE
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
        db 0CCh   ; int3 
seg45 ENDS

        END
