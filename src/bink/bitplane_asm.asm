; codfh-match: Bink's bit-plane readers (the library's bitplane.obj)
; Only readlossy remains a temporary image transcription pending C restoration.
; ReadBPLossless and ReadBPLossyWithMotion now compile from bitplane.c.

        .686p
        .model flat


seg0 SEGMENT PARA PUBLIC ALIAS('BINK') 'CODE'


; // match: _readlossy @ 0x0034D7D0
; // sp-match: _readlossy @ 0x0025D7D0
_readlossy PROC PUBLIC
$L_34d7d0:
        db 081h, 0ECh, 0E4h, 000h, 000h, 000h   ; sub esp, 0xe4
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 08Bh, 0ACh, 024h, 0F4h, 000h, 000h, 000h   ; mov ebp, dword ptr [esp + 0xf4]
        db 08Bh, 045h, 000h   ; mov eax, dword ptr [ebp]
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 083h, 0FEh, 003h   ; cmp esi, 3
        db 057h   ; push edi
        db 08Bh, 07Dh, 004h   ; mov edi, dword ptr [ebp + 4]
        db 0C7h, 044h, 024h, 014h, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x14], 0
        db 072h, 00Dh   ; jb 0x34d804
        db 08Ah, 0D0h   ; mov dl, al
        db 080h, 0E2h, 007h   ; and dl, 7
        db 0C1h, 0E8h, 003h   ; shr eax, 3
        db 083h, 0EEh, 003h   ; sub esi, 3
        db 0EBh, 01Eh   ; jmp 0x34d822
$L_34d804:
        db 08Bh, 01Fh   ; mov ebx, dword ptr [edi]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 08Ah, 0D3h   ; mov dl, bl
        db 0D2h, 0E2h   ; shl dl, cl
        db 0B9h, 003h, 000h, 000h, 000h   ; mov ecx, 3
        db 02Bh, 0CEh   ; sub ecx, esi
        db 0D3h, 0EBh   ; shr ebx, cl
        db 00Ah, 0D0h   ; or dl, al
        db 080h, 0E2h, 007h   ; and dl, 7
        db 083h, 0C6h, 01Dh   ; add esi, 0x1d
        db 08Bh, 0C3h   ; mov eax, ebx
        db 083h, 0C7h, 004h   ; add edi, 4
$L_34d822:
        db 08Dh, 08Ch, 024h, 0B4h, 000h, 000h, 000h   ; lea ecx, [esp + 0xb4]
        db 089h, 04Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ecx
        db 0FEh, 0C2h   ; inc dl
        db 08Dh, 08Ch, 024h, 0B8h, 000h, 000h, 000h   ; lea ecx, [esp + 0xb8]
        db 089h, 04Ch, 024h, 028h   ; mov dword ptr [esp + 0x28], ecx
        db 033h, 0C9h   ; xor ecx, ecx
        db 08Ah, 0CAh   ; mov cl, dl
        db 0B3h, 001h   ; mov bl, 1
        db 0C6h, 084h, 024h, 0B4h, 000h, 000h, 000h, 010h   ; mov byte ptr [esp + 0xb4], 0x10
        db 0C6h, 084h, 024h, 0B5h, 000h, 000h, 000h, 060h   ; mov byte ptr [esp + 0xb5], 0x60
        db 0C6h, 084h, 024h, 0B6h, 000h, 000h, 000h, 0B0h   ; mov byte ptr [esp + 0xb6], 0xb0
        db 0C6h, 084h, 024h, 0B7h, 000h, 000h, 000h, 002h   ; mov byte ptr [esp + 0xb7], 2
        db 0C7h, 044h, 024h, 018h, 000h, 000h, 000h, 000h   ; mov dword ptr [esp + 0x18], 0
        db 049h   ; dec ecx
        db 0D2h, 0E3h   ; shl bl, cl
        db 084h, 0D2h   ; test dl, dl
        db 088h, 054h, 024h, 01Fh   ; mov byte ptr [esp + 0x1f], dl
        db 088h, 05Ch, 024h, 013h   ; mov byte ptr [esp + 0x13], bl
        db 00Fh, 086h, 008h, 004h, 000h, 000h   ; jbe 0x34dc83
        db 0EBh, 004h   ; jmp 0x34d881
$L_34d87d:
        db 08Ah, 05Ch, 024h, 013h   ; mov bl, byte ptr [esp + 0x13]
$L_34d881:
        db 08Bh, 04Ch, 024h, 018h   ; mov ecx, dword ptr [esp + 0x18]
        db 033h, 0EDh   ; xor ebp, ebp
        db 085h, 0C9h   ; test ecx, ecx
        db 07Eh, 063h   ; jle 0x34d8ee
        db 0EBh, 003h   ; jmp 0x34d890
        db 08Dh, 049h, 000h   ; lea ecx, [ecx]
$L_34d890:
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x34d89e
        db 08Bh, 0C8h   ; mov ecx, eax
        db 083h, 0E1h, 001h   ; and ecx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34d8af
$L_34d89e:
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 08Bh, 0C1h   ; mov eax, ecx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E1h, 001h   ; and ecx, 1
$L_34d8af:
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 032h   ; je 0x34d8e5
        db 00Fh, 0B6h, 054h, 02Ch, 030h   ; movzx edx, byte ptr [esp + ebp + 0x30]
        db 08Bh, 08Ch, 024h, 0F8h, 000h, 000h, 000h   ; mov ecx, dword ptr [esp + 0xf8]
        db 003h, 0CAh   ; add ecx, edx
        db 080h, 039h, 000h   ; cmp byte ptr [ecx], 0
        db 00Fh, 0BEh, 0D3h   ; movsx edx, bl
        db 07Dh, 002h   ; jge 0x34d8cb
        db 0F7h, 0DAh   ; neg edx
$L_34d8cb:
        db 000h, 011h   ; add byte ptr [ecx], dl
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 041h   ; inc ecx
        db 089h, 04Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], ecx
        db 03Bh, 094h, 024h, 000h, 001h, 000h, 000h   ; cmp edx, dword ptr [esp + 0x100]
        db 00Fh, 084h, 097h, 003h, 000h, 000h   ; je 0x34dc7c
$L_34d8e5:
        db 08Bh, 04Ch, 024h, 018h   ; mov ecx, dword ptr [esp + 0x18]
        db 045h   ; inc ebp
        db 03Bh, 0E9h   ; cmp ebp, ecx
        db 07Ch, 0A2h   ; jl 0x34d890
$L_34d8ee:
        db 08Bh, 06Ch, 024h, 020h   ; mov ebp, dword ptr [esp + 0x20]
        db 03Bh, 06Ch, 024h, 028h   ; cmp ebp, dword ptr [esp + 0x28]
        db 08Bh, 0DDh   ; mov ebx, ebp
        db 089h, 05Ch, 024h, 024h   ; mov dword ptr [esp + 0x24], ebx
        db 00Fh, 083h, 060h, 003h, 000h, 000h   ; jae 0x34dc62
$L_34d902:
        db 08Ah, 00Bh   ; mov cl, byte ptr [ebx]
        db 084h, 0C9h   ; test cl, cl
        db 088h, 04Ch, 024h, 02Ch   ; mov byte ptr [esp + 0x2c], cl
        db 00Fh, 084h, 043h, 003h, 000h, 000h   ; je 0x34dc53
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x34d91e
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34d92f
$L_34d91e:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34d92f:
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 084h, 01Ch, 003h, 000h, 000h   ; je 0x34dc53
        db 08Bh, 054h, 024h, 02Ch   ; mov edx, dword ptr [esp + 0x2c]
        db 083h, 0E2h, 003h   ; and edx, 3
        db 083h, 0FAh, 003h   ; cmp edx, 3
        db 00Fh, 087h, 00Ch, 003h, 000h, 000h   ; ja 0x34dc53
        db 0FFh, 024h, 095h   ; jmp dword ptr [edx*4 + 0x34dc98]
        dd $L_34dc98
$L_34d94e:
        db 0C0h, 0E9h, 002h   ; shr cl, 2
        db 08Ah, 0D1h   ; mov dl, cl
        db 0C0h, 0E2h, 002h   ; shl dl, 2
        db 080h, 0C2h, 011h   ; add dl, 0x11
        db 088h, 013h   ; mov byte ptr [ebx], dl
        db 0EBh, 03Fh   ; jmp 0x34d99c
$L_34d95d:
        db 0C0h, 0E9h, 002h   ; shr cl, 2
        db 0C0h, 0E1h, 002h   ; shl cl, 2
        db 08Ah, 0D1h   ; mov dl, cl
        db 080h, 0C2h, 002h   ; add dl, 2
        db 088h, 013h   ; mov byte ptr [ebx], dl
        db 08Bh, 054h, 024h, 028h   ; mov edx, dword ptr [esp + 0x28]
        db 08Ah, 0D9h   ; mov bl, cl
        db 080h, 0C3h, 012h   ; add bl, 0x12
        db 088h, 01Ah   ; mov byte ptr [edx], bl
        db 08Ah, 0D9h   ; mov bl, cl
        db 080h, 0C3h, 022h   ; add bl, 0x22
        db 042h   ; inc edx
        db 088h, 01Ah   ; mov byte ptr [edx], bl
        db 08Bh, 05Ch, 024h, 024h   ; mov ebx, dword ptr [esp + 0x24]
        db 042h   ; inc edx
        db 080h, 0C1h, 032h   ; add cl, 0x32
        db 088h, 00Ah   ; mov byte ptr [edx], cl
        db 042h   ; inc edx
        db 089h, 054h, 024h, 028h   ; mov dword ptr [esp + 0x28], edx
        db 0E9h, 0C7h, 002h, 000h, 000h   ; jmp 0x34dc58
$L_34d991:
        db 0C0h, 0E9h, 002h   ; shr cl, 2
        db 0C6h, 003h, 000h   ; mov byte ptr [ebx], 0
        db 043h   ; inc ebx
        db 089h, 05Ch, 024h, 024h   ; mov dword ptr [esp + 0x24], ebx
$L_34d99c:
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x34d9aa
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34d9bb
$L_34d9aa:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34d9bb:
        db 085h, 0D2h   ; test edx, edx
        db 074h, 019h   ; je 0x34d9d8
        db 08Bh, 09Ch, 024h, 0F8h, 000h, 000h, 000h   ; mov ebx, dword ptr [esp + 0xf8]
        db 08Ah, 0D1h   ; mov dl, cl
        db 04Dh   ; dec ebp
        db 0C0h, 0E2h, 002h   ; shl dl, 2
        db 080h, 0C2h, 003h   ; add dl, 3
        db 089h, 06Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ebp
        db 088h, 055h, 000h   ; mov byte ptr [ebp], dl
        db 0EBh, 060h   ; jmp 0x34da38
$L_34d9d8:
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 088h, 04Ch, 014h, 030h   ; mov byte ptr [esp + edx + 0x30], cl
        db 042h   ; inc edx
        db 085h, 0F6h   ; test esi, esi
        db 089h, 054h, 024h, 018h   ; mov dword ptr [esp + 0x18], edx
        db 074h, 00Ah   ; je 0x34d9f3
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34da04
$L_34d9f3:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34da04:
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 0BEh, 054h, 024h, 013h   ; movsx edx, byte ptr [esp + 0x13]
        db 074h, 002h   ; je 0x34da0f
        db 0F7h, 0DAh   ; neg edx
$L_34da0f:
        db 08Bh, 09Ch, 024h, 0F8h, 000h, 000h, 000h   ; mov ebx, dword ptr [esp + 0xf8]
        db 00Fh, 0B6h, 0E9h   ; movzx ebp, cl
        db 088h, 014h, 02Bh   ; mov byte ptr [ebx + ebp], dl
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 08Bh, 0EAh   ; mov ebp, edx
        db 042h   ; inc edx
        db 089h, 054h, 024h, 014h   ; mov dword ptr [esp + 0x14], edx
        db 03Bh, 0ACh, 024h, 000h, 001h, 000h, 000h   ; cmp ebp, dword ptr [esp + 0x100]
        db 00Fh, 084h, 048h, 002h, 000h, 000h   ; je 0x34dc7c
        db 08Bh, 06Ch, 024h, 020h   ; mov ebp, dword ptr [esp + 0x20]
$L_34da38:
        db 0FEh, 0C1h   ; inc cl
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x34da48
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34da59
$L_34da48:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34da59:
        db 085h, 0D2h   ; test edx, edx
        db 074h, 012h   ; je 0x34da6f
        db 08Ah, 0D1h   ; mov dl, cl
        db 04Dh   ; dec ebp
        db 0C0h, 0E2h, 002h   ; shl dl, 2
        db 080h, 0C2h, 003h   ; add dl, 3
        db 089h, 06Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ebp
        db 088h, 055h, 000h   ; mov byte ptr [ebp], dl
        db 0EBh, 059h   ; jmp 0x34dac8
$L_34da6f:
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 088h, 04Ch, 014h, 030h   ; mov byte ptr [esp + edx + 0x30], cl
        db 042h   ; inc edx
        db 085h, 0F6h   ; test esi, esi
        db 089h, 054h, 024h, 018h   ; mov dword ptr [esp + 0x18], edx
        db 074h, 00Ah   ; je 0x34da8a
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34da9b
$L_34da8a:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34da9b:
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 0BEh, 054h, 024h, 013h   ; movsx edx, byte ptr [esp + 0x13]
        db 074h, 002h   ; je 0x34daa6
        db 0F7h, 0DAh   ; neg edx
$L_34daa6:
        db 00Fh, 0B6h, 0E9h   ; movzx ebp, cl
        db 088h, 014h, 02Bh   ; mov byte ptr [ebx + ebp], dl
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 08Bh, 0EAh   ; mov ebp, edx
        db 042h   ; inc edx
        db 089h, 054h, 024h, 014h   ; mov dword ptr [esp + 0x14], edx
        db 03Bh, 0ACh, 024h, 000h, 001h, 000h, 000h   ; cmp ebp, dword ptr [esp + 0x100]
        db 00Fh, 084h, 0B8h, 001h, 000h, 000h   ; je 0x34dc7c
        db 08Bh, 06Ch, 024h, 020h   ; mov ebp, dword ptr [esp + 0x20]
$L_34dac8:
        db 0FEh, 0C1h   ; inc cl
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x34dad8
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34dae9
$L_34dad8:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34dae9:
        db 085h, 0D2h   ; test edx, edx
        db 074h, 012h   ; je 0x34daff
        db 08Ah, 0D1h   ; mov dl, cl
        db 04Dh   ; dec ebp
        db 0C0h, 0E2h, 002h   ; shl dl, 2
        db 080h, 0C2h, 003h   ; add dl, 3
        db 089h, 06Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ebp
        db 088h, 055h, 000h   ; mov byte ptr [ebp], dl
        db 0EBh, 059h   ; jmp 0x34db58
$L_34daff:
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 088h, 04Ch, 014h, 030h   ; mov byte ptr [esp + edx + 0x30], cl
        db 042h   ; inc edx
        db 085h, 0F6h   ; test esi, esi
        db 089h, 054h, 024h, 018h   ; mov dword ptr [esp + 0x18], edx
        db 074h, 00Ah   ; je 0x34db1a
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34db2b
$L_34db1a:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34db2b:
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 0BEh, 054h, 024h, 013h   ; movsx edx, byte ptr [esp + 0x13]
        db 074h, 002h   ; je 0x34db36
        db 0F7h, 0DAh   ; neg edx
$L_34db36:
        db 00Fh, 0B6h, 0E9h   ; movzx ebp, cl
        db 088h, 014h, 02Bh   ; mov byte ptr [ebx + ebp], dl
        db 08Bh, 054h, 024h, 014h   ; mov edx, dword ptr [esp + 0x14]
        db 08Bh, 0EAh   ; mov ebp, edx
        db 042h   ; inc edx
        db 089h, 054h, 024h, 014h   ; mov dword ptr [esp + 0x14], edx
        db 03Bh, 0ACh, 024h, 000h, 001h, 000h, 000h   ; cmp ebp, dword ptr [esp + 0x100]
        db 00Fh, 084h, 028h, 001h, 000h, 000h   ; je 0x34dc7c
        db 08Bh, 06Ch, 024h, 020h   ; mov ebp, dword ptr [esp + 0x20]
$L_34db58:
        db 0FEh, 0C1h   ; inc cl
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Ah   ; je 0x34db68
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34db79
$L_34db68:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34db79:
        db 085h, 0D2h   ; test edx, edx
        db 074h, 017h   ; je 0x34db94
        db 08Bh, 05Ch, 024h, 024h   ; mov ebx, dword ptr [esp + 0x24]
        db 04Dh   ; dec ebp
        db 0C0h, 0E1h, 002h   ; shl cl, 2
        db 080h, 0C1h, 003h   ; add cl, 3
        db 089h, 06Ch, 024h, 020h   ; mov dword ptr [esp + 0x20], ebp
        db 088h, 04Dh, 000h   ; mov byte ptr [ebp], cl
        db 0E9h, 0C4h, 000h, 000h, 000h   ; jmp 0x34dc58
$L_34db94:
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 088h, 04Ch, 014h, 030h   ; mov byte ptr [esp + edx + 0x30], cl
        db 042h   ; inc edx
        db 085h, 0F6h   ; test esi, esi
        db 089h, 054h, 024h, 018h   ; mov dword ptr [esp + 0x18], edx
        db 074h, 00Ah   ; je 0x34dbaf
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34dbc0
$L_34dbaf:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34dbc0:
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 0BEh, 054h, 024h, 013h   ; movsx edx, byte ptr [esp + 0x13]
        db 074h, 002h   ; je 0x34dbcb
        db 0F7h, 0DAh   ; neg edx
$L_34dbcb:
        db 00Fh, 0B6h, 0C9h   ; movzx ecx, cl
        db 088h, 014h, 019h   ; mov byte ptr [ecx + ebx], dl
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 041h   ; inc ecx
        db 089h, 04Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], ecx
        db 03Bh, 094h, 024h, 000h, 001h, 000h, 000h   ; cmp edx, dword ptr [esp + 0x100]
        db 00Fh, 084h, 093h, 000h, 000h, 000h   ; je 0x34dc7c
        db 08Bh, 05Ch, 024h, 024h   ; mov ebx, dword ptr [esp + 0x24]
        db 0EBh, 069h   ; jmp 0x34dc58
$L_34dbef:
        db 08Bh, 054h, 024h, 018h   ; mov edx, dword ptr [esp + 0x18]
        db 0C0h, 0E9h, 002h   ; shr cl, 2
        db 088h, 04Ch, 014h, 030h   ; mov byte ptr [esp + edx + 0x30], cl
        db 042h   ; inc edx
        db 085h, 0F6h   ; test esi, esi
        db 089h, 054h, 024h, 018h   ; mov dword ptr [esp + 0x18], edx
        db 074h, 00Ah   ; je 0x34dc0d
        db 08Bh, 0D0h   ; mov edx, eax
        db 083h, 0E2h, 001h   ; and edx, 1
        db 0D1h, 0E8h   ; shr eax, 1
        db 04Eh   ; dec esi
        db 0EBh, 011h   ; jmp 0x34dc1e
$L_34dc0d:
        db 08Bh, 017h   ; mov edx, dword ptr [edi]
        db 08Bh, 0C2h   ; mov eax, edx
        db 083h, 0C7h, 004h   ; add edi, 4
        db 0D1h, 0E8h   ; shr eax, 1
        db 0BEh, 01Fh, 000h, 000h, 000h   ; mov esi, 0x1f
        db 083h, 0E2h, 001h   ; and edx, 1
$L_34dc1e:
        db 085h, 0D2h   ; test edx, edx
        db 00Fh, 0BEh, 054h, 024h, 013h   ; movsx edx, byte ptr [esp + 0x13]
        db 074h, 002h   ; je 0x34dc29
        db 0F7h, 0DAh   ; neg edx
$L_34dc29:
        db 08Bh, 09Ch, 024h, 0F8h, 000h, 000h, 000h   ; mov ebx, dword ptr [esp + 0xf8]
        db 00Fh, 0B6h, 0C9h   ; movzx ecx, cl
        db 088h, 014h, 019h   ; mov byte ptr [ecx + ebx], dl
        db 08Bh, 04Ch, 024h, 014h   ; mov ecx, dword ptr [esp + 0x14]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 041h   ; inc ecx
        db 089h, 04Ch, 024h, 014h   ; mov dword ptr [esp + 0x14], ecx
        db 03Bh, 094h, 024h, 000h, 001h, 000h, 000h   ; cmp edx, dword ptr [esp + 0x100]
        db 074h, 032h   ; je 0x34dc7c
        db 08Bh, 04Ch, 024h, 024h   ; mov ecx, dword ptr [esp + 0x24]
        db 0C6h, 001h, 000h   ; mov byte ptr [ecx], 0
        db 08Bh, 0D9h   ; mov ebx, ecx
$L_34dc53:
        db 043h   ; inc ebx
        db 089h, 05Ch, 024h, 024h   ; mov dword ptr [esp + 0x24], ebx
$L_34dc58:
        db 03Bh, 05Ch, 024h, 028h   ; cmp ebx, dword ptr [esp + 0x28]
        db 00Fh, 082h, 0A0h, 0FCh, 0FFh, 0FFh   ; jb 0x34d902
$L_34dc62:
        db 08Ah, 054h, 024h, 013h   ; mov dl, byte ptr [esp + 0x13]
        db 08Ah, 04Ch, 024h, 01Fh   ; mov cl, byte ptr [esp + 0x1f]
        db 0D0h, 0FAh   ; sar dl, 1
        db 0FEh, 0C9h   ; dec cl
        db 088h, 054h, 024h, 013h   ; mov byte ptr [esp + 0x13], dl
        db 088h, 04Ch, 024h, 01Fh   ; mov byte ptr [esp + 0x1f], cl
        db 00Fh, 085h, 001h, 0FCh, 0FFh, 0FFh   ; jne 0x34d87d
$L_34dc7c:
        db 08Bh, 0ACh, 024h, 0FCh, 000h, 000h, 000h   ; mov ebp, dword ptr [esp + 0xfc]
$L_34dc83:
        db 089h, 07Dh, 004h   ; mov dword ptr [ebp + 4], edi
        db 05Fh   ; pop edi
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        db 05Eh   ; pop esi
        db 089h, 045h, 000h   ; mov dword ptr [ebp], eax
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 081h, 0C4h, 0E4h, 000h, 000h, 000h   ; add esp, 0xe4
        db 0C3h   ; ret 
        db 090h   ; nop 
$L_34dc98:
        dd $L_34d94e
        dd $L_34d95d
        dd $L_34d991
        dd $L_34dbef
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
        db 0CCh
_readlossy ENDP

seg0 ENDS

        END
