; codfh-match: XDK XPP (USB peripheral) code at 0x3C4480-0x3CD3D0
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ?AddComplete@IUsbDevice@@QAEXJ@Z:NEAR
EXTERN ?CancelRequest@IUsbDevice@@QAEJPAT_URB@@@Z:NEAR
EXTERN ?GetEndpointDescriptor@IUsbDevice@@QBEPBU_USB_ENDPOINT_DESCRIPTOR@@EEE@Z:NEAR
EXTERN ?GetExtension@IUsbDevice@@QBEPAXXZ:NEAR
EXTERN ?GetInterfaceDescriptor@IUsbDevice@@QBEPBU_USB_INTERFACE_DESCRIPTOR@@XZ:NEAR
EXTERN ?GetInterfaceNumber@IUsbDevice@@QBEEXZ:NEAR
EXTERN ?GetMaxDeviceTypeCount@IUsbInit@@QAEKPAU_XPP_DEVICE_TYPE@@@Z:NEAR
EXTERN ?GetPort@IUsbDevice@@QBEKXZ:NEAR
EXTERN ?InitializeClass@XHawkMediaObject@@SGXKK@Z:NEAR
EXTERN ?MU_DiskIoComplete@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z:BYTE
EXTERN ?MU_DiskReadComplete@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z:BYTE
EXTERN ?MU_DiskStartPartialWrite@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z:NEAR
EXTERN ?MU_fMarkWriteBufferCorrupt@@YIXPAU_MU_REQUEST_BLOCK@@@Z:NEAR
EXTERN ?MU_fStartMrb@@YIXPAU_MU_DEVICE_EXTENSION@@@Z:NEAR
EXTERN ?RegisterResources@IUsbInit@@QAEXPAU_USB_RESOURCE_REQUIREMENTS@@@Z:NEAR
EXTERN ?ReverseEndian@@YGKK@Z_0:NEAR
EXTERN ?SetClassSpecificType@IUsbDevice@@QAEXE@Z:NEAR
EXTERN ?SetExtension@IUsbDevice@@QAEPAXPAX@Z:NEAR
EXTERN ?SubmitRequest@IUsbDevice@@QAEJPAT_URB@@@Z:NEAR
EXTERN ?USBHUB_EnumHubStage1@@YGXPAT_URB@@PAVIUsbDevice@@@Z:BYTE
EXTERN ?USBHUB_SetEnumWatchdog@@YGXK@Z:NEAR
EXTERN ?USBHUB_WatchdogTimerProc@@YGXPAU_KDPC@@PAX11@Z:BYTE
EXTERN ?UseDefaultCount@IUsbInit@@QAEHXZ:NEAR
EXTERN ?XID_EndTypeDescriptionTable@@3KA:BYTE
EXTERN ?XID_EnumLegacy1@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z:NEAR
EXTERN ?XID_fFindNode@@YIPAU_XID_DEVICE_NODE@@PAU_XID_TYPE_INFORMATION@@K@Z:NEAR
EXTERN ?XID_fRemoveDeviceComplete@@YIXPAU_XID_DEVICE_NODE@@@Z:NEAR
EXTERN ?sm_2ndLevelHub@IUsbInit@@0EA:BYTE
EXTERN _GetTypeInformation2:NEAR
EXTERN _USBD_AllocateMemory@8:NEAR
EXTERN __allshr:NEAR
EXTERN __aulldiv:NEAR
EXTERN __imp_@IofCompleteRequest@8:BYTE
EXTERN __imp__ExFreePool@4:BYTE
EXTERN __imp__IoStartNextPacket@4:BYTE
EXTERN __imp__KeCancelTimer@4:BYTE
EXTERN __imp__KeInitializeDpc@12:BYTE
EXTERN __imp__KeInitializeTimerEx@8:BYTE
EXTERN _sub_3C8380:NEAR
EXTERN _sub_3C8958:NEAR
EXTERN _sub_3CC097:NEAR
EXTERN _sub_3CC0DA:NEAR
EXTERN _sub_3CC0F4:NEAR
EXTERN _unk_3C4484:BYTE
EXTERN _unk_3C4598:BYTE
EXTERN _unk_3C459C:BYTE
EXTERN _unk_3C45B0:BYTE
EXTERN _unk_3C45B4:BYTE
EXTERN _unk_3C45B8:BYTE
EXTERN _unk_3C45B9:BYTE
EXTERN _unk_3C45C4:BYTE
EXTERN _unk_3C45F4:BYTE
EXTERN _unk_3C4600:BYTE
EXTERN _unk_3C460C:BYTE
EXTERN _unk_3C4654:BYTE
EXTERN _unk_3C4655:BYTE
EXTERN _unk_3C4660:BYTE
EXTERN _unk_3C46CC:BYTE
EXTERN _unk_3C46D0:BYTE
EXTERN _unk_3C46DC:BYTE
EXTERN _unk_3C46E0:BYTE
EXTERN _unk_3C46E4:BYTE
EXTERN _unk_3C46E8:BYTE
EXTERN _unk_3C46EC:BYTE
EXTERN _unk_3C46F0:BYTE
EXTERN _unk_3C46FC:BYTE
EXTERN _unk_3C4700:BYTE
EXTERN __imp__IoInvalidDeviceRequest@8:BYTE
EXTERN _unk_3F1A14:BYTE
EXTERN _unk_506600:BYTE
EXTERN _unk_506668:BYTE
EXTERN _unk_506690:BYTE
EXTERN _unk_5066B0:BYTE
EXTERN _unk_5066B8:BYTE
EXTERN _unk_5066BA:BYTE
EXTERN _unk_5066BC:BYTE
EXTERN _unk_5066C8:BYTE
EXTERN _unk_5066CA:BYTE
EXTERN _unk_5066CC:BYTE
EXTERN _unk_5066D0:BYTE
EXTERN _unk_5066D4:BYTE
EXTERN _unk_5066D5:BYTE
EXTERN _unk_5066D6:BYTE
EXTERN _unk_5066D8:BYTE
EXTERN _unk_5066D9:BYTE
EXTERN _unk_5066DA:BYTE
EXTERN _unk_5066DB:BYTE
EXTERN _unk_5066E8:BYTE
EXTERN _unk_5066E9:BYTE
EXTERN _unk_5066F0:BYTE
EXTERN _unk_5066F4:BYTE
EXTERN _unk_5066F8:BYTE
EXTERN _unk_5066FC:BYTE
EXTERN _unk_506700:BYTE
EXTERN _unk_506704:BYTE
EXTERN _unk_506705:BYTE
EXTERN _unk_506706:BYTE
EXTERN _unk_506710:BYTE
EXTERN _unk_506711:BYTE
EXTERN _unk_506712:BYTE
EXTERN _unk_506714:BYTE
EXTERN _unk_506716:BYTE
EXTERN _unk_506718:BYTE
EXTERN _unk_506720:BYTE
EXTERN _unk_506748:BYTE
EXTERN _unk_508AD8:BYTE
EXTERN _unk_508AE0:BYTE
EXTERN _unk_508B48:BYTE
EXTERN _unk_508B50:BYTE
EXTERN _unk_50F5BC:BYTE
EXTERN _unk_50F5C4:BYTE
EXTERN _unk_512762:BYTE
EXTERN _unk_512766:BYTE










seg10 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: ?XID_EnumKeyboardComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z @ 0x003C8831
PUBLIC ?XID_EnumKeyboardComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z
?XID_EnumKeyboardComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 068h   ; push 0x506720
        dd _unk_506720
        db 0FFh, 015h   ; call dword ptr [0x3cd39c]
        dd __imp__KeCancelTimer@4
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 08Dh, 07Eh, 00Ah   ; lea edi, [esi + 0xa]
        db 08Bh, 0D7h   ; mov edx, edi
        db 0B1h, 002h   ; mov cl, 2
        call _GetTypeInformation2   ; 0x3C67C6
        db 08Bh, 0D8h   ; mov ebx, eax
        db 085h, 0DBh   ; test ebx, ebx
        db 074h, 03Bh   ; je 0x3c8890
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        call ?GetPort@IUsbDevice@@QBEKXZ   ; 0x3C6B15
        db 08Bh, 0D0h   ; mov edx, eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?XID_fFindNode@@YIPAU_XID_DEVICE_NODE@@PAU_XID_TYPE_INFORMATION@@K@Z   ; 0x3C83CF
        db 085h, 0C0h   ; test eax, eax
        db 075h, 027h   ; jne 0x3c8890
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 088h, 046h, 00Bh   ; mov byte ptr [esi + 0xb], al
        db 08Ah, 007h   ; mov al, byte ptr [edi]
        db 089h, 05Eh, 00Eh   ; mov dword ptr [esi + 0xe], ebx
        db 0C6h, 046h, 00Ch, 008h   ; mov byte ptr [esi + 0xc], 8
        db 0C6h, 046h, 00Dh, 001h   ; mov byte ptr [esi + 0xd], 1
        db 050h   ; push eax
        call ?SetClassSpecificType@IUsbDevice@@QAEXE@Z   ; 0x3C69B5
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 06Ah, 000h   ; push 0
        call ?AddComplete@IUsbDevice@@QAEXJ@Z   ; 0x3C5DAC
        db 080h, 04Eh, 004h, 008h   ; or byte ptr [esi + 4], 8
        db 0EBh, 025h   ; jmp 0x3c88b5
$L_3c8890:
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 083h, 026h, 000h   ; and dword ptr [esi], 0
        db 080h, 066h, 004h, 0FEh   ; and byte ptr [esi + 4], 0xfe
        db 066h, 0FFh, 00Dh   ; dec word ptr [0x5066ca]
        dd _unk_5066CA
        db 06Ah, 000h   ; push 0
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?SetExtension@IUsbDevice@@QAEPAXPAX@Z   ; 0x3C69A4
        db 068h, 000h, 004h, 000h, 080h   ; push 0x80000400
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?AddComplete@IUsbDevice@@QAEXJ@Z   ; 0x3C5DAC
$L_3c88b5:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8

; // match: ?XID_EnumMouseComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z @ 0x003C88BB
PUBLIC ?XID_EnumMouseComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z
?XID_EnumMouseComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z:
        db 053h   ; push ebx
        db 055h   ; push ebp
        db 056h   ; push esi
        db 057h   ; push edi
        db 068h   ; push 0x506720
        dd _unk_506720
        db 0FFh, 015h   ; call dword ptr [0x3cd39c]
        dd __imp__KeCancelTimer@4
        db 08Bh, 074h, 024h, 018h   ; mov esi, dword ptr [esp + 0x18]
        db 08Dh, 06Eh, 00Ah   ; lea ebp, [esi + 0xa]
        db 08Bh, 0D5h   ; mov edx, ebp
        db 0B1h, 004h   ; mov cl, 4
        call _GetTypeInformation2   ; 0x3C67C6
        db 08Bh, 0F8h   ; mov edi, eax
        db 033h, 0DBh   ; xor ebx, ebx
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 074h, 04Ch   ; je 0x3c892e
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        call ?GetPort@IUsbDevice@@QBEKXZ   ; 0x3C6B15
        db 08Bh, 0D0h   ; mov edx, eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?XID_fFindNode@@YIPAU_XID_DEVICE_NODE@@PAU_XID_TYPE_INFORMATION@@K@Z   ; 0x3C83CF
        db 085h, 0C0h   ; test eax, eax
        db 075h, 038h   ; jne 0x3c892e
        db 08Ah, 04Eh, 006h   ; mov cl, byte ptr [esi + 6]
        db 089h, 07Eh, 00Eh   ; mov dword ptr [esi + 0xe], edi
        db 088h, 05Eh, 00Bh   ; mov byte ptr [esi + 0xb], bl
        db 08Bh, 047h, 008h   ; mov eax, dword ptr [edi + 8]
        db 08Ah, 000h   ; mov al, byte ptr [eax]
        db 03Ah, 0C8h   ; cmp cl, al
        db 073h, 005h   ; jae 0x3c890d
        db 088h, 04Eh, 00Ch   ; mov byte ptr [esi + 0xc], cl
        db 0EBh, 003h   ; jmp 0x3c8910
$L_3c890d:
        db 088h, 046h, 00Ch   ; mov byte ptr [esi + 0xc], al
$L_3c8910:
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 033h, 0C0h   ; xor eax, eax
        db 08Ah, 045h, 000h   ; mov al, byte ptr [ebp]
        db 088h, 05Eh, 00Dh   ; mov byte ptr [esi + 0xd], bl
        db 050h   ; push eax
        call ?SetClassSpecificType@IUsbDevice@@QAEXE@Z   ; 0x3C69B5
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 053h   ; push ebx
        call ?AddComplete@IUsbDevice@@QAEXJ@Z   ; 0x3C5DAC
        db 080h, 04Eh, 004h, 008h   ; or byte ptr [esi + 4], 8
        db 0EBh, 023h   ; jmp 0x3c8951
$L_3c892e:
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 080h, 066h, 004h, 0FEh   ; and byte ptr [esi + 4], 0xfe
        db 089h, 01Eh   ; mov dword ptr [esi], ebx
        db 066h, 0FFh, 00Dh   ; dec word ptr [0x5066ca]
        dd _unk_5066CA
        db 053h   ; push ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?SetExtension@IUsbDevice@@QAEPAXPAX@Z   ; 0x3C69A4
        db 068h, 000h, 004h, 000h, 080h   ; push 0x80000400
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?AddComplete@IUsbDevice@@QAEXJ@Z   ; 0x3C5DAC
$L_3c8951:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8
seg10 ENDS

seg11 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: ?XID_EnumMouse@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z @ 0x003C8A85
PUBLIC ?XID_EnumMouse@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z
?XID_EnumMouse@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z:
        db 056h   ; push esi
        db 068h   ; push 0x506720
        dd _unk_506720
        db 0FFh, 015h   ; call dword ptr [0x3cd39c]
        dd __imp__KeCancelTimer@4
        db 08Bh, 074h, 024h, 00Ch   ; mov esi, dword ptr [esp + 0xc]
        db 033h, 0C0h   ; xor eax, eax
        db 0C6h, 005h   ; mov byte ptr [0x5066e8], 0x30
        dd _unk_5066E8
        db 030h
        db 0C6h, 005h   ; mov byte ptr [0x5066e9], 0x40
        dd _unk_5066E9
        db 040h
        db 0C7h, 005h   ; mov dword ptr [0x5066f0], 0x3c88bb
        dd _unk_5066F0
        dd ?XID_EnumMouseComplete@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z
        db 089h, 035h   ; mov dword ptr [0x5066f4], esi
        dd _unk_5066F4
        db 0A3h   ; mov dword ptr [0x5066f8], eax
        dd _unk_5066F8
        db 0A3h   ; mov dword ptr [0x506700], eax
        dd _unk_506700
        db 0A3h   ; mov dword ptr [0x5066fc], eax
        dd _unk_5066FC
        db 0A2h   ; mov byte ptr [0x506704], al
        dd _unk_506704
        db 0C6h, 005h   ; mov byte ptr [0x506705], 1
        dd _unk_506705
        db 001h
        db 0A2h   ; mov byte ptr [0x506706], al
        dd _unk_506706
        db 0C6h, 005h   ; mov byte ptr [0x506710], 0x21
        dd _unk_506710
        db 021h
        db 0C6h, 005h   ; mov byte ptr [0x506711], 0xa
        dd _unk_506711
        db 00Ah
        db 066h, 0A3h   ; mov word ptr [0x506712], ax
        dd _unk_506712
        db 066h, 00Fh, 0B6h, 04Eh, 005h   ; movzx cx, byte ptr [esi + 5]
        db 066h, 089h, 00Dh   ; mov word ptr [0x506714], cx
        dd _unk_506714
        db 066h, 0A3h   ; mov word ptr [0x506716], ax
        dd _unk_506716
        call _sub_3C8380   ; 0x3C8380
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 068h   ; push 0x5066e8
        dd _unk_5066E8
        call ?SubmitRequest@IUsbDevice@@QAEJPAT_URB@@@Z   ; 0x3C6D55
        db 05Eh   ; pop esi
        db 0C2h, 008h, 000h   ; ret 8
seg11 ENDS

seg24 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: _XID_RemoveDevice@4 @ 0x003C8B10
PUBLIC _XID_RemoveDevice@4
_XID_RemoveDevice@4:
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 056h   ; push esi
        call ?GetExtension@IUsbDevice@@QBEPAXXZ   ; 0x3C69A0
        db 08Bh, 0F0h   ; mov esi, eax
        db 08Bh, 04Eh, 012h   ; mov ecx, dword ptr [esi + 0x12]
        db 080h, 04Eh, 004h, 002h   ; or byte ptr [esi + 4], 2
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 019h   ; je 0x3c8b40
        db 08Bh, 081h, 0A3h, 000h, 000h, 000h   ; mov eax, dword ptr [ecx + 0xa3]
        db 08Bh, 040h, 020h   ; mov eax, dword ptr [eax + 0x20]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 002h   ; je 0x3c8b36
        db 0FFh, 0D0h   ; call eax
$L_3c8b36:
        db 08Bh, 04Eh, 012h   ; mov ecx, dword ptr [esi + 0x12]
        call _sub_3C8958   ; 0x3C8958
        db 0EBh, 007h   ; jmp 0x3c8b47
$L_3c8b40:
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?XID_fRemoveDeviceComplete@@YIXPAU_XID_DEVICE_NODE@@@Z   ; 0x3C83AC
$L_3c8b47:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg24 ENDS

seg12 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: ?XID_EnumStage1@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z @ 0x003C8DEB
PUBLIC ?XID_EnumStage1@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z
?XID_EnumStage1@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 068h   ; push 0x506720
        dd _unk_506720
        db 0FFh, 015h   ; call dword ptr [0x3cd39c]
        dd __imp__KeCancelTimer@4
        db 08Bh, 044h, 024h, 010h   ; mov eax, dword ptr [esp + 0x10]
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 058h, 004h   ; cmp dword ptr [eax + 4], ebx
        db 00Fh, 08Ch, 0C7h, 000h, 000h, 000h   ; jl 0x3c8ecf
        db 083h, 078h, 014h, 008h   ; cmp dword ptr [eax + 0x14], 8
        db 00Fh, 082h, 0BDh, 000h, 000h, 000h   ; jb 0x3c8ecf
        db 080h, 03Dh   ; cmp byte ptr [0x5066d4], 8
        dd _unk_5066D4
        db 008h
        db 00Fh, 082h, 0B0h, 000h, 000h, 000h   ; jb 0x3c8ecf
        db 080h, 03Dh   ; cmp byte ptr [0x5066d5], 0x42
        dd _unk_5066D5
        db 042h
        db 00Fh, 085h, 0A3h, 000h, 000h, 000h   ; jne 0x3c8ecf
        db 066h, 039h, 01Dh   ; cmp word ptr [0x5066d6], bx
        dd _unk_5066D6
        db 00Fh, 084h, 096h, 000h, 000h, 000h   ; je 0x3c8ecf
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 08Ah, 00Dh   ; mov cl, byte ptr [0x5066d8]
        dd _unk_5066D8
        db 08Dh, 07Eh, 00Ah   ; lea edi, [esi + 0xa]
        db 08Bh, 0D7h   ; mov edx, edi
        call _GetTypeInformation2   ; 0x3C67C6
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 089h, 046h, 00Eh   ; mov dword ptr [esi + 0xe], eax
        db 08Ah, 00Dh   ; mov cl, byte ptr [0x5066d9]
        dd _unk_5066D9
        db 088h, 04Eh, 00Bh   ; mov byte ptr [esi + 0xb], cl
        db 08Ah, 00Dh   ; mov cl, byte ptr [0x5066da]
        dd _unk_5066DA
        db 088h, 04Eh, 00Ch   ; mov byte ptr [esi + 0xc], cl
        db 08Ah, 00Dh   ; mov cl, byte ptr [0x5066db]
        dd _unk_5066DB
        db 088h, 04Eh, 00Dh   ; mov byte ptr [esi + 0xd], cl
        db 074h, 03Bh   ; je 0x3c8eaa
        db 0A0h   ; mov al, byte ptr [0x5066da]
        dd _unk_5066DA
        db 03Ch, 002h   ; cmp al, 2
        db 072h, 032h   ; jb 0x3c8eaa
        db 03Ch, 020h   ; cmp al, 0x20
        db 077h, 02Eh   ; ja 0x3c8eaa
        db 08Ah, 046h, 00Ch   ; mov al, byte ptr [esi + 0xc]
        db 03Ah, 046h, 006h   ; cmp al, byte ptr [esi + 6]
        db 077h, 026h   ; ja 0x3c8eaa
        db 038h, 05Eh, 009h   ; cmp byte ptr [esi + 9], bl
        db 074h, 007h   ; je 0x3c8e90
        db 08Ah, 0C1h   ; mov al, cl
        db 03Ah, 046h, 007h   ; cmp al, byte ptr [esi + 7]
        db 077h, 01Ah   ; ja 0x3c8eaa
$L_3c8e90:
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 033h, 0C0h   ; xor eax, eax
        db 08Ah, 007h   ; mov al, byte ptr [edi]
        db 050h   ; push eax
        call ?SetClassSpecificType@IUsbDevice@@QAEXE@Z   ; 0x3C69B5
        db 08Bh, 00Eh   ; mov ecx, dword ptr [esi]
        db 053h   ; push ebx
        call ?AddComplete@IUsbDevice@@QAEXJ@Z   ; 0x3C5DAC
        db 080h, 04Eh, 004h, 008h   ; or byte ptr [esi + 4], 8
        db 0EBh, 02Fh   ; jmp 0x3c8ed9
$L_3c8eaa:
        db 08Bh, 03Eh   ; mov edi, dword ptr [esi]
        db 080h, 066h, 004h, 0FEh   ; and byte ptr [esi + 4], 0xfe
        db 089h, 01Eh   ; mov dword ptr [esi], ebx
        db 066h, 0FFh, 00Dh   ; dec word ptr [0x5066ca]
        dd _unk_5066CA
        db 053h   ; push ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?SetExtension@IUsbDevice@@QAEPAXPAX@Z   ; 0x3C69A4
        db 068h, 000h, 004h, 000h, 080h   ; push 0x80000400
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?AddComplete@IUsbDevice@@QAEXJ@Z   ; 0x3C5DAC
        db 0EBh, 00Ah   ; jmp 0x3c8ed9
$L_3c8ecf:
        db 0FFh, 074h, 024h, 014h   ; push dword ptr [esp + 0x14]
        db 050h   ; push eax
        call ?XID_EnumLegacy1@@YGXPAT_URB@@PAU_XID_DEVICE_NODE@@@Z   ; 0x3C8D0D
$L_3c8ed9:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8
seg12 ENDS





seg19 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: _sub_3CBFDD @ 0x003CBFDD
PUBLIC _sub_3CBFDD
_sub_3CBFDD:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 08Ah, 045h, 00Bh   ; mov al, byte ptr [ebp + 0xb]
        db 088h, 045h, 0FCh   ; mov byte ptr [ebp - 4], al
        db 08Ah, 045h, 00Ah   ; mov al, byte ptr [ebp + 0xa]
        db 088h, 045h, 0FDh   ; mov byte ptr [ebp - 3], al
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 088h, 065h, 0FEh   ; mov byte ptr [ebp - 2], ah
        db 088h, 045h, 0FFh   ; mov byte ptr [ebp - 1], al
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
seg19 ENDS

seg20 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: ?MU_DiskReadCapacityCompletion@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z @ 0x003CC10A
PUBLIC ?MU_DiskReadCapacityCompletion@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
?MU_DiskReadCapacityCompletion@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 014h   ; sub esp, 0x14
        db 08Bh, 055h, 00Ch   ; mov edx, dword ptr [ebp + 0xc]
        db 053h   ; push ebx
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 08Bh, 04Bh, 010h   ; mov ecx, dword ptr [ebx + 0x10]
        db 08Bh, 041h, 05Ch   ; mov eax, dword ptr [ecx + 0x5c]
        db 056h   ; push esi
        db 089h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], eax
        db 0B8h, 000h, 000h, 000h, 0C0h   ; mov eax, 0xc0000000
        db 08Bh, 0F2h   ; mov esi, edx
        db 057h   ; push edi
        db 08Bh, 07Bh, 028h   ; mov edi, dword ptr [ebx + 0x28]
        db 023h, 0F0h   ; and esi, eax
        db 03Bh, 0F0h   ; cmp esi, eax
        db 089h, 07Dh, 0F8h   ; mov dword ptr [ebp - 8], edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 075h, 00Fh   ; jne 0x3cc147
        db 083h, 061h, 014h, 000h   ; and dword ptr [ecx + 0x14], 0
        db 08Bh, 043h, 010h   ; mov eax, dword ptr [ebx + 0x10]
        db 089h, 050h, 010h   ; mov dword ptr [eax + 0x10], edx
        db 0E9h, 075h, 001h, 000h, 000h   ; jmp 0x3cc2bc
$L_3cc147:
        db 066h, 08Bh, 047h, 006h   ; mov ax, word ptr [edi + 6]
        db 0FFh, 037h   ; push dword ptr [edi]
        db 088h, 065h, 00Ah   ; mov byte ptr [ebp + 0xa], ah
        db 088h, 045h, 00Bh   ; mov byte ptr [ebp + 0xb], al
        db 066h, 08Bh, 047h, 004h   ; mov ax, word ptr [edi + 4]
        db 00Fh, 0B7h, 04Dh, 00Ah   ; movzx ecx, word ptr [ebp + 0xa]
        db 088h, 065h, 00Eh   ; mov byte ptr [ebp + 0xe], ah
        db 088h, 045h, 00Fh   ; mov byte ptr [ebp + 0xf], al
        db 00Fh, 0B7h, 075h, 00Eh   ; movzx esi, word ptr [ebp + 0xe]
        db 00Fh, 0AFh, 0F1h   ; imul esi, ecx
        call ?ReverseEndian@@YGKK@Z_0   ; 0x3CBFDD
        db 00Fh, 0B7h, 04Dh, 00Ah   ; movzx ecx, word ptr [ebp + 0xa]
        db 040h   ; inc eax
        db 089h, 045h, 00Ch   ; mov dword ptr [ebp + 0xc], eax
        db 0F7h, 0E1h   ; mul ecx
        db 085h, 0F6h   ; test esi, esi
        db 089h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], eax
        db 089h, 055h, 0F0h   ; mov dword ptr [ebp - 0x10], edx
        db 075h, 005h   ; jne 0x3cc186
        db 0BEh, 000h, 020h, 000h, 000h   ; mov esi, 0x2000
$L_3cc186:
        db 051h   ; push ecx
        call _sub_3CC0DA   ; 0x3CC0DA
        db 085h, 0C0h   ; test eax, eax
        db 00Fh, 084h, 049h, 001h, 000h, 000h   ; je 0x3cc2dd
        db 00Fh, 0B7h, 055h, 00Ah   ; movzx edx, word ptr [ebp + 0xa]
        db 081h, 0FAh, 000h, 010h, 000h, 000h   ; cmp edx, 0x1000
        db 00Fh, 087h, 039h, 001h, 000h, 000h   ; ja 0x3cc2dd
        db 081h, 0FEh, 000h, 040h, 000h, 000h   ; cmp esi, 0x4000
        db 00Fh, 087h, 02Dh, 001h, 000h, 000h   ; ja 0x3cc2dd
        db 066h, 0F7h, 0C6h, 0FFh, 00Fh   ; test si, 0xfff
        db 00Fh, 085h, 022h, 001h, 000h, 000h   ; jne 0x3cc2dd
        db 033h, 0C9h   ; xor ecx, ecx
        db 039h, 04Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ecx
        db 00Fh, 084h, 017h, 001h, 000h, 000h   ; je 0x3cc2dd
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 03Bh, 0C1h   ; cmp eax, ecx
        db 00Fh, 082h, 00Ch, 001h, 000h, 000h   ; jb 0x3cc2dd
        db 077h, 009h   ; ja 0x3cc1dc
        db 039h, 075h, 0ECh   ; cmp dword ptr [ebp - 0x14], esi
        db 00Fh, 082h, 001h, 001h, 000h, 000h   ; jb 0x3cc2dd
$L_3cc1dc:
        db 083h, 0F8h, 001h   ; cmp eax, 1
        db 00Fh, 087h, 0F8h, 000h, 000h, 000h   ; ja 0x3cc2dd
        db 072h, 00Ah   ; jb 0x3cc1f1
        db 083h, 07Dh, 0ECh, 000h   ; cmp dword ptr [ebp - 0x14], 0
        db 00Fh, 087h, 0ECh, 000h, 000h, 000h   ; ja 0x3cc2dd
$L_3cc1f1:
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 052h   ; push edx
        db 089h, 08Bh, 060h, 001h, 000h, 000h   ; mov dword ptr [ebx + 0x160], ecx
        db 089h, 083h, 064h, 001h, 000h, 000h   ; mov dword ptr [ebx + 0x164], eax
        db 089h, 0B3h, 068h, 001h, 000h, 000h   ; mov dword ptr [ebx + 0x168], esi
        call _sub_3CC0F4   ; 0x3CC0F4
        db 00Fh, 0B6h, 0C0h   ; movzx eax, al
        db 089h, 083h, 058h, 001h, 000h, 000h   ; mov dword ptr [ebx + 0x158], eax
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 056h   ; push esi
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 0C7h, 083h, 048h, 001h, 000h, 000h, 00Ch, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x148], 0xc
        db 0FFh, 075h, 0ECh   ; push dword ptr [ebp - 0x14]
        db 08Dh, 0BBh, 040h, 001h, 000h, 000h   ; lea edi, [ebx + 0x140]
        call __aulldiv   ; 0x2C87C0
        db 089h, 007h   ; mov dword ptr [edi], eax
        db 08Bh, 045h, 0F4h   ; mov eax, dword ptr [ebp - 0xc]
        db 0C1h, 0EEh, 00Ch   ; shr esi, 0xc
        db 089h, 057h, 004h   ; mov dword ptr [edi + 4], edx
        db 0C7h, 083h, 04Ch, 001h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [ebx + 0x14c], 1
        db 089h, 0B3h, 050h, 001h, 000h, 000h   ; mov dword ptr [ebx + 0x150], esi
        db 0C7h, 083h, 054h, 001h, 000h, 000h, 000h, 010h, 000h, 000h   ; mov dword ptr [ebx + 0x154], 0x1000
        db 08Bh, 040h, 010h   ; mov eax, dword ptr [eax + 0x10]
        db 03Dh, 000h, 000h, 007h, 000h   ; cmp eax, 0x70000
        db 074h, 038h   ; je 0x3cc29b
        db 03Dh, 004h, 040h, 007h, 000h   ; cmp eax, 0x74004
        db 075h, 04Fh   ; jne 0x3cc2b9
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 08Bh, 050h, 030h   ; mov edx, dword ptr [eax + 0x30]
        db 033h, 0C0h   ; xor eax, eax
        db 06Ah, 008h   ; push 8
        db 059h   ; pop ecx
        db 08Bh, 0FAh   ; mov edi, edx
        db 0F3h, 0ABh   ; rep stosd dword ptr es:[edi], eax
        db 08Bh, 083h, 060h, 001h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x160]
        db 089h, 042h, 008h   ; mov dword ptr [edx + 8], eax
        db 08Bh, 083h, 064h, 001h, 000h, 000h   ; mov eax, dword ptr [ebx + 0x164]
        db 089h, 042h, 00Ch   ; mov dword ptr [edx + 0xc], eax
        db 0C6h, 042h, 01Ah, 001h   ; mov byte ptr [edx + 0x1a], 1
        db 08Bh, 043h, 010h   ; mov eax, dword ptr [ebx + 0x10]
        db 0C7h, 040h, 014h, 020h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 0x20
        db 0EBh, 017h   ; jmp 0x3cc2b2
$L_3cc29b:
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 06Ah, 006h   ; push 6
        db 08Bh, 0F7h   ; mov esi, edi
        db 08Bh, 078h, 030h   ; mov edi, dword ptr [eax + 0x30]
        db 059h   ; pop ecx
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 043h, 010h   ; mov eax, dword ptr [ebx + 0x10]
        db 0C7h, 040h, 014h, 018h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 0x18
$L_3cc2b2:
        db 08Bh, 043h, 010h   ; mov eax, dword ptr [ebx + 0x10]
        db 083h, 060h, 010h, 000h   ; and dword ptr [eax + 0x10], 0
$L_3cc2b9:
        db 08Bh, 07Dh, 0F8h   ; mov edi, dword ptr [ebp - 8]
$L_3cc2bc:
        db 057h   ; push edi
        db 0FFh, 015h   ; call dword ptr [0x3cd414]
        dd __imp__ExFreePool@4
        db 08Bh, 04Bh, 010h   ; mov ecx, dword ptr [ebx + 0x10]
        db 032h, 0D2h   ; xor dl, dl
        db 0FFh, 015h   ; call dword ptr [0x3cd53c]
        dd __imp_@IofCompleteRequest@8
        db 0FFh, 033h   ; push dword ptr [ebx]
        db 0FFh, 015h   ; call dword ptr [0x3cd554]
        dd __imp__IoStartNextPacket@4
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 008h, 000h   ; ret 8
$L_3cc2dd:
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 083h, 060h, 014h, 000h   ; and dword ptr [eax + 0x14], 0
        db 08Bh, 043h, 010h   ; mov eax, dword ptr [ebx + 0x10]
        db 0C7h, 040h, 010h, 04Fh, 001h, 000h, 0C0h   ; mov dword ptr [eax + 0x10], 0xc000014f
        db 0EBh, 0CCh   ; jmp 0x3cc2bc

; // match: ?MU_fDiskVerify@@YIXPAU_MU_DEVICE_EXTENSION@@PAU_IRP@@@Z @ 0x003CC2F0
PUBLIC ?MU_fDiskVerify@@YIXPAU_MU_DEVICE_EXTENSION@@PAU_IRP@@@Z
?MU_fDiskVerify@@YIXPAU_MU_DEVICE_EXTENSION@@PAU_IRP@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 08Bh, 042h, 05Ch   ; mov eax, dword ptr [edx + 0x5c]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 057h   ; push edi
        db 08Bh, 078h, 008h   ; mov edi, dword ptr [eax + 8]
        db 0C6h, 046h, 04Fh, 02Fh   ; mov byte ptr [esi + 0x4f], 0x2f
        db 08Bh, 08Eh, 058h, 001h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x158]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 057h, 004h   ; mov edx, dword ptr [edi + 4]
        call __allshr   ; 0x2C75D0
        db 08Bh, 08Eh, 058h, 001h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x158]
        db 08Bh, 05Fh, 008h   ; mov ebx, dword ptr [edi + 8]
        db 08Bh, 0D0h   ; mov edx, eax
        db 033h, 0C0h   ; xor eax, eax
        db 089h, 046h, 028h   ; mov dword ptr [esi + 0x28], eax
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 0C7h, 046h, 030h   ; mov dword ptr [esi + 0x30], 0x3cc057
        dd ?MU_DiskIoComplete@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
        db 0D3h, 0EBh   ; shr ebx, cl
        db 066h, 08Bh, 04Fh, 00Ah   ; mov cx, word ptr [edi + 0xa]
        db 066h, 06Bh, 0C9h, 064h   ; imul cx, cx, 0x64
        db 066h, 089h, 04Eh, 034h   ; mov word ptr [esi + 0x34], cx
        db 08Dh, 04Eh, 04Fh   ; lea ecx, [esi + 0x4f]
        db 088h, 046h, 037h   ; mov byte ptr [esi + 0x37], al
        db 0C6h, 046h, 036h, 002h   ; mov byte ptr [esi + 0x36], 2
        db 08Bh, 0F9h   ; mov edi, ecx
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 052h   ; push edx
        db 0C6h, 001h, 02Fh   ; mov byte ptr [ecx], 0x2f
        call ?ReverseEndian@@YGKK@Z_0   ; 0x3CBFDD
        db 089h, 046h, 051h   ; mov dword ptr [esi + 0x51], eax
        db 088h, 07Dh, 0FCh   ; mov byte ptr [ebp - 4], bh
        db 088h, 05Dh, 0FDh   ; mov byte ptr [ebp - 3], bl
        db 066h, 08Bh, 045h, 0FCh   ; mov ax, word ptr [ebp - 4]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 066h, 089h, 046h, 056h   ; mov word ptr [esi + 0x56], ax
        call ?MU_fStartMrb@@YIXPAU_MU_DEVICE_EXTENSION@@@Z   ; 0x3CD292
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C3h   ; ret 
seg20 ENDS

seg21 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: ?MU_DiskWriteBuildPartialRequest@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z @ 0x003CC43F
PUBLIC ?MU_DiskWriteBuildPartialRequest@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
?MU_DiskWriteBuildPartialRequest@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 05Eh, 00Ch   ; mov ebx, dword ptr [esi + 0xc]
        db 08Bh, 04Eh, 010h   ; mov ecx, dword ptr [esi + 0x10]
        db 081h, 0E3h, 000h, 000h, 000h, 0F0h   ; and ebx, 0xf0000000
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 057h   ; push edi
        db 08Bh, 079h, 05Ch   ; mov edi, dword ptr [ecx + 0x5c]
        db 089h, 04Dh, 008h   ; mov dword ptr [ebp + 8], ecx
        db 00Fh, 08Ch, 0B1h, 000h, 000h, 000h   ; jl 0x3cc515
        db 081h, 0C3h, 000h, 000h, 000h, 010h   ; add ebx, 0x10000000
        db 081h, 0FBh, 000h, 000h, 000h, 020h   ; cmp ebx, 0x20000000
        db 075h, 00Bh   ; jne 0x3cc47d
        db 0F6h, 046h, 00Fh, 002h   ; test byte ptr [esi + 0xf], 2
        db 075h, 018h   ; jne 0x3cc490
        db 0BBh, 000h, 000h, 000h, 040h   ; mov ebx, 0x40000000
$L_3cc47d:
        db 081h, 0FBh, 000h, 000h, 000h, 040h   ; cmp ebx, 0x40000000
        db 075h, 00Bh   ; jne 0x3cc490
        db 0F6h, 046h, 00Fh, 004h   ; test byte ptr [esi + 0xf], 4
        db 075h, 005h   ; jne 0x3cc490
$L_3cc48b:
        db 0BBh, 000h, 000h, 000h, 060h   ; mov ebx, 0x60000000
$L_3cc490:
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 0BAh, 0FFh, 0FFh, 0FFh, 00Fh   ; mov edx, 0xfffffff
        db 023h, 0C2h   ; and eax, edx
        db 00Bh, 0C3h   ; or eax, ebx
        db 081h, 0FBh, 000h, 000h, 000h, 020h   ; cmp ebx, 0x20000000
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 00Fh, 084h, 023h, 001h, 000h, 000h   ; je 0x3cc5ce
        db 081h, 0FBh, 000h, 000h, 000h, 030h   ; cmp ebx, 0x30000000
        db 00Fh, 084h, 0EBh, 000h, 000h, 000h   ; je 0x3cc5a2
        db 081h, 0FBh, 000h, 000h, 000h, 040h   ; cmp ebx, 0x40000000
        db 00Fh, 084h, 0BFh, 000h, 000h, 000h   ; je 0x3cc582
        db 081h, 0FBh, 000h, 000h, 000h, 050h   ; cmp ebx, 0x50000000
        db 00Fh, 084h, 081h, 000h, 000h, 000h   ; je 0x3cc550
        db 081h, 0FBh, 000h, 000h, 000h, 060h   ; cmp ebx, 0x60000000
        db 00Fh, 085h, 043h, 001h, 000h, 000h   ; jne 0x3cc61e
        db 023h, 0C2h   ; and eax, edx
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0A1h   ; mov eax, dword ptr [0x50f5bc]
        dd _unk_50F5BC
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 089h, 010h   ; mov dword ptr [eax], edx
        db 089h, 042h, 004h   ; mov dword ptr [edx + 4], eax
        db 08Bh, 047h, 004h   ; mov eax, dword ptr [edi + 4]
        db 089h, 041h, 014h   ; mov dword ptr [ecx + 0x14], eax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 032h, 0D2h   ; xor dl, dl
        db 089h, 041h, 010h   ; mov dword ptr [ecx + 0x10], eax
        db 0FFh, 015h   ; call dword ptr [0x3cd53c]
        dd __imp_@IofCompleteRequest@8
        call _sub_3CC097   ; 0x3CC097
        db 0FFh, 036h   ; push dword ptr [esi]
        db 0FFh, 015h   ; call dword ptr [0x3cd554]
        dd __imp__IoStartNextPacket@4
        db 0E9h, 009h, 001h, 000h, 000h   ; jmp 0x3cc61e
$L_3cc515:
        db 081h, 0FBh, 000h, 000h, 000h, 020h   ; cmp ebx, 0x20000000
        db 074h, 00Ch   ; je 0x3cc529
        db 081h, 0FBh, 000h, 000h, 000h, 040h   ; cmp ebx, 0x40000000
        db 00Fh, 085h, 062h, 0FFh, 0FFh, 0FFh   ; jne 0x3cc48b
$L_3cc529:
        db 081h, 07Dh, 00Ch, 03Eh, 000h, 000h, 0C0h   ; cmp dword ptr [ebp + 0xc], 0xc000003e
        db 00Fh, 085h, 055h, 0FFh, 0FFh, 0FFh   ; jne 0x3cc48b
        db 08Dh, 04Eh, 028h   ; lea ecx, [esi + 0x28]
        call ?MU_fMarkWriteBufferCorrupt@@YIXPAU_MU_REQUEST_BLOCK@@@Z   ; 0x3CC0B3
        db 083h, 065h, 00Ch, 000h   ; and dword ptr [ebp + 0xc], 0
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 081h, 0C3h, 000h, 000h, 000h, 010h   ; add ebx, 0x10000000
        db 0E9h, 040h, 0FFh, 0FFh, 0FFh   ; jmp 0x3cc490
$L_3cc550:
        db 083h, 066h, 038h, 000h   ; and dword ptr [esi + 0x38], 0
        db 0C6h, 046h, 037h, 006h   ; mov byte ptr [esi + 0x37], 6
        db 08Bh, 046h, 01Ch   ; mov eax, dword ptr [esi + 0x1c]
        db 089h, 046h, 03Ch   ; mov dword ptr [esi + 0x3c], eax
        db 0C6h, 046h, 04Fh, 02Ah   ; mov byte ptr [esi + 0x4f], 0x2a
        db 08Bh, 047h, 008h   ; mov eax, dword ptr [edi + 8]
        db 02Bh, 046h, 01Ch   ; sub eax, dword ptr [esi + 0x1c]
        db 003h, 047h, 004h   ; add eax, dword ptr [edi + 4]
        db 089h, 046h, 028h   ; mov dword ptr [esi + 0x28], eax
        db 08Bh, 086h, 068h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x168]
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 08Bh, 047h, 00Ch   ; mov eax, dword ptr [edi + 0xc]
        db 02Bh, 046h, 01Ch   ; sub eax, dword ptr [esi + 0x1c]
$L_3cc57d:
        db 003h, 047h, 004h   ; add eax, dword ptr [edi + 4]
        db 0EBh, 06Dh   ; jmp 0x3cc5ef
$L_3cc582:
        db 0C7h, 046h, 028h   ; mov dword ptr [esi + 0x28], 0x50f5c4
        dd _unk_50F5C4
        db 08Bh, 086h, 068h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x168]
        db 02Bh, 046h, 01Ch   ; sub eax, dword ptr [esi + 0x1c]
        db 0C6h, 046h, 037h, 001h   ; mov byte ptr [esi + 0x37], 1
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 0C6h, 046h, 04Fh, 028h   ; mov byte ptr [esi + 0x4f], 0x28
        db 08Bh, 047h, 00Ch   ; mov eax, dword ptr [edi + 0xc]
        db 0EBh, 0DBh   ; jmp 0x3cc57d
$L_3cc5a2:
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 089h, 046h, 038h   ; mov dword ptr [esi + 0x38], eax
        db 0C6h, 046h, 037h, 006h   ; mov byte ptr [esi + 0x37], 6
        db 08Dh, 086h, 068h, 001h, 000h, 000h   ; lea eax, [esi + 0x168]
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 089h, 04Eh, 03Ch   ; mov dword ptr [esi + 0x3c], ecx
        db 08Bh, 04Fh, 008h   ; mov ecx, dword ptr [edi + 8]
        db 089h, 04Eh, 028h   ; mov dword ptr [esi + 0x28], ecx
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 0C6h, 046h, 04Fh, 02Ah   ; mov byte ptr [esi + 0x4f], 0x2a
        db 08Bh, 047h, 00Ch   ; mov eax, dword ptr [edi + 0xc]
        db 02Bh, 046h, 038h   ; sub eax, dword ptr [esi + 0x38]
        db 0EBh, 021h   ; jmp 0x3cc5ef
$L_3cc5ce:
        db 0C7h, 046h, 028h   ; mov dword ptr [esi + 0x28], 0x50f5c4
        dd _unk_50F5C4
        db 08Bh, 086h, 068h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x168]
        db 02Bh, 046h, 018h   ; sub eax, dword ptr [esi + 0x18]
        db 0C6h, 046h, 037h, 001h   ; mov byte ptr [esi + 0x37], 1
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 0C6h, 046h, 04Fh, 028h   ; mov byte ptr [esi + 0x4f], 0x28
        db 08Bh, 047h, 00Ch   ; mov eax, dword ptr [edi + 0xc]
        db 02Bh, 046h, 02Ch   ; sub eax, dword ptr [esi + 0x2c]
$L_3cc5ef:
        db 08Dh, 0BEh, 058h, 001h, 000h, 000h   ; lea edi, [esi + 0x158]
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 0D3h, 0E8h   ; shr eax, cl
        db 050h   ; push eax
        call ?ReverseEndian@@YGKK@Z_0   ; 0x3CBFDD
        db 089h, 046h, 051h   ; mov dword ptr [esi + 0x51], eax
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 0D3h, 0E8h   ; shr eax, cl
        db 08Bh, 0CEh   ; mov ecx, esi
        db 088h, 065h, 00Eh   ; mov byte ptr [ebp + 0xe], ah
        db 088h, 045h, 00Fh   ; mov byte ptr [ebp + 0xf], al
        db 066h, 08Bh, 045h, 00Eh   ; mov ax, word ptr [ebp + 0xe]
        db 066h, 089h, 046h, 056h   ; mov word ptr [esi + 0x56], ax
        call ?MU_fStartMrb@@YIXPAU_MU_DEVICE_EXTENSION@@@Z   ; 0x3CD292
$L_3cc61e:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 008h, 000h   ; ret 8

; // match: ?MU_DiskWriteBuildMiddlePartialRequest@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z @ 0x003CC625
PUBLIC ?MU_DiskWriteBuildMiddlePartialRequest@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
?MU_DiskWriteBuildMiddlePartialRequest@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 08Bh, 05Eh, 010h   ; mov ebx, dword ptr [esi + 0x10]
        db 08Bh, 053h, 05Ch   ; mov edx, dword ptr [ebx + 0x5c]
        db 057h   ; push edi
        db 08Bh, 07Eh, 00Ch   ; mov edi, dword ptr [esi + 0xc]
        db 081h, 0E7h, 000h, 000h, 000h, 0F0h   ; and edi, 0xf0000000
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 089h, 055h, 008h   ; mov dword ptr [ebp + 8], edx
        db 07Ch, 008h   ; jl 0x3cc64e
        db 081h, 0C7h, 000h, 000h, 000h, 010h   ; add edi, 0x10000000
        db 0EBh, 035h   ; jmp 0x3cc683
$L_3cc64e:
        db 081h, 0FFh, 000h, 000h, 000h, 020h   ; cmp edi, 0x20000000
        db 074h, 008h   ; je 0x3cc65e
        db 081h, 0FFh, 000h, 000h, 000h, 030h   ; cmp edi, 0x30000000
        db 075h, 020h   ; jne 0x3cc67e
$L_3cc65e:
        db 081h, 07Dh, 00Ch, 03Eh, 000h, 000h, 0C0h   ; cmp dword ptr [ebp + 0xc], 0xc000003e
        db 075h, 017h   ; jne 0x3cc67e
        db 08Dh, 04Eh, 028h   ; lea ecx, [esi + 0x28]
        call ?MU_fMarkWriteBufferCorrupt@@YIXPAU_MU_REQUEST_BLOCK@@@Z   ; 0x3CC0B3
        db 083h, 065h, 00Ch, 000h   ; and dword ptr [ebp + 0xc], 0
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 081h, 0C7h, 000h, 000h, 000h, 010h   ; add edi, 0x10000000
        db 0EBh, 005h   ; jmp 0x3cc683
$L_3cc67e:
        db 0BFh, 000h, 000h, 000h, 050h   ; mov edi, 0x50000000
$L_3cc683:
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 0B9h, 0FFh, 0FFh, 0FFh, 00Fh   ; mov ecx, 0xfffffff
        db 023h, 0C1h   ; and eax, ecx
        db 00Bh, 0C7h   ; or eax, edi
        db 081h, 0FFh, 000h, 000h, 000h, 020h   ; cmp edi, 0x20000000
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 00Fh, 084h, 0ACh, 000h, 000h, 000h   ; je 0x3cc74a
        db 081h, 0FFh, 000h, 000h, 000h, 030h   ; cmp edi, 0x30000000
        db 00Fh, 084h, 087h, 000h, 000h, 000h   ; je 0x3cc731
        db 081h, 0FFh, 000h, 000h, 000h, 040h   ; cmp edi, 0x40000000
        db 074h, 048h   ; je 0x3cc6fa
        db 081h, 0FFh, 000h, 000h, 000h, 050h   ; cmp edi, 0x50000000
        db 00Fh, 085h, 0DBh, 000h, 000h, 000h   ; jne 0x3cc799
        db 023h, 0C1h   ; and eax, ecx
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
        db 0A1h   ; mov eax, dword ptr [0x50f5bc]
        dd _unk_50F5BC
        db 08Bh, 008h   ; mov ecx, dword ptr [eax]
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 089h, 008h   ; mov dword ptr [eax], ecx
        db 089h, 041h, 004h   ; mov dword ptr [ecx + 4], eax
        db 08Bh, 042h, 004h   ; mov eax, dword ptr [edx + 4]
        db 089h, 043h, 014h   ; mov dword ptr [ebx + 0x14], eax
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 032h, 0D2h   ; xor dl, dl
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 043h, 010h   ; mov dword ptr [ebx + 0x10], eax
        db 0FFh, 015h   ; call dword ptr [0x3cd53c]
        dd __imp_@IofCompleteRequest@8
        call _sub_3CC097   ; 0x3CC097
        db 0FFh, 036h   ; push dword ptr [esi]
        db 0FFh, 015h   ; call dword ptr [0x3cd554]
        dd __imp__IoStartNextPacket@4
        db 0E9h, 09Fh, 000h, 000h, 000h   ; jmp 0x3cc799
$L_3cc6fa:
        db 0C6h, 046h, 04Fh, 02Ah   ; mov byte ptr [esi + 0x4f], 0x2a
        db 0C6h, 046h, 037h, 006h   ; mov byte ptr [esi + 0x37], 6
        db 08Bh, 086h, 068h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x168]
        db 02Bh, 046h, 018h   ; sub eax, dword ptr [esi + 0x18]
        db 089h, 046h, 038h   ; mov dword ptr [esi + 0x38], eax
        db 08Bh, 086h, 068h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x168]
        db 02Bh, 046h, 01Ch   ; sub eax, dword ptr [esi + 0x1c]
        db 089h, 046h, 03Ch   ; mov dword ptr [esi + 0x3c], eax
        db 08Bh, 042h, 008h   ; mov eax, dword ptr [edx + 8]
        db 089h, 046h, 028h   ; mov dword ptr [esi + 0x28], eax
        db 08Bh, 086h, 068h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x168]
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 08Bh, 042h, 00Ch   ; mov eax, dword ptr [edx + 0xc]
        db 02Bh, 046h, 038h   ; sub eax, dword ptr [esi + 0x38]
        db 0EBh, 039h   ; jmp 0x3cc76a
$L_3cc731:
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 005h   ; add eax, 0x50f5c4
        dd _unk_50F5C4
        db 089h, 046h, 028h   ; mov dword ptr [esi + 0x28], eax
        db 08Bh, 046h, 01Ch   ; mov eax, dword ptr [esi + 0x1c]
        db 089h, 046h, 02Ch   ; mov dword ptr [esi + 0x2c], eax
        db 08Bh, 042h, 00Ch   ; mov eax, dword ptr [edx + 0xc]
        db 003h, 042h, 004h   ; add eax, dword ptr [edx + 4]
        db 0EBh, 020h   ; jmp 0x3cc76a
$L_3cc74a:
        db 0C6h, 046h, 037h, 001h   ; mov byte ptr [esi + 0x37], 1
        db 0C6h, 046h, 04Fh, 028h   ; mov byte ptr [esi + 0x4f], 0x28
        db 0C7h, 046h, 028h   ; mov dword ptr [esi + 0x28], 0x50f5c4
        dd _unk_50F5C4
        db 08Bh, 08Eh, 068h, 001h, 000h, 000h   ; mov ecx, dword ptr [esi + 0x168]
        db 02Bh, 04Eh, 018h   ; sub ecx, dword ptr [esi + 0x18]
        db 089h, 04Eh, 02Ch   ; mov dword ptr [esi + 0x2c], ecx
        db 08Bh, 042h, 00Ch   ; mov eax, dword ptr [edx + 0xc]
        db 02Bh, 0C1h   ; sub eax, ecx
$L_3cc76a:
        db 08Dh, 0BEh, 058h, 001h, 000h, 000h   ; lea edi, [esi + 0x158]
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 0D3h, 0E8h   ; shr eax, cl
        db 050h   ; push eax
        call ?ReverseEndian@@YGKK@Z_0   ; 0x3CBFDD
        db 089h, 046h, 051h   ; mov dword ptr [esi + 0x51], eax
        db 08Bh, 00Fh   ; mov ecx, dword ptr [edi]
        db 08Bh, 046h, 02Ch   ; mov eax, dword ptr [esi + 0x2c]
        db 0D3h, 0E8h   ; shr eax, cl
        db 08Bh, 0CEh   ; mov ecx, esi
        db 088h, 065h, 00Eh   ; mov byte ptr [ebp + 0xe], ah
        db 088h, 045h, 00Fh   ; mov byte ptr [ebp + 0xf], al
        db 066h, 08Bh, 045h, 00Eh   ; mov ax, word ptr [ebp + 0xe]
        db 066h, 089h, 046h, 056h   ; mov word ptr [esi + 0x56], ax
        call ?MU_fStartMrb@@YIXPAU_MU_DEVICE_EXTENSION@@@Z   ; 0x3CD292
$L_3cc799:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 008h, 000h   ; ret 8
seg21 ENDS

seg22 SEGMENT BYTE PUBLIC ALIAS('.XPPCODE') 'CODE'

; // match: ?MU_fDiskReadWrite@@YIXPAU_MU_DEVICE_EXTENSION@@PAU_IRP@@@Z @ 0x003CC96F
PUBLIC ?MU_fDiskReadWrite@@YIXPAU_MU_DEVICE_EXTENSION@@PAU_IRP@@@Z
?MU_fDiskReadWrite@@YIXPAU_MU_DEVICE_EXTENSION@@PAU_IRP@@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 00Ch   ; sub esp, 0xc
        db 083h, 065h, 0FCh, 000h   ; and dword ptr [ebp - 4], 0
        db 053h   ; push ebx
        db 08Bh, 0C2h   ; mov eax, edx
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 08Bh, 048h, 05Ch   ; mov ecx, dword ptr [eax + 0x5c]
        db 08Bh, 051h, 00Ch   ; mov edx, dword ptr [ecx + 0xc]
        db 08Bh, 059h, 004h   ; mov ebx, dword ptr [ecx + 4]
        db 057h   ; push edi
        db 0BFh, 0FFh, 00Fh, 000h, 000h   ; mov edi, 0xfff
        db 085h, 0D7h   ; test edi, edx
        db 089h, 045h, 0F8h   ; mov dword ptr [ebp - 8], eax
        db 089h, 055h, 0F4h   ; mov dword ptr [ebp - 0xc], edx
        db 075h, 053h   ; jne 0x3cc9eb
        db 085h, 0DFh   ; test edi, ebx
        db 075h, 04Fh   ; jne 0x3cc9eb
        db 033h, 0C0h   ; xor eax, eax
        db 08Bh, 0FBh   ; mov edi, ebx
        db 003h, 0FAh   ; add edi, edx
        db 013h, 041h, 010h   ; adc eax, dword ptr [ecx + 0x10]
        db 03Bh, 086h, 064h, 001h, 000h, 000h   ; cmp eax, dword ptr [esi + 0x164]
        db 07Fh, 03Bh   ; jg 0x3cc9e8
        db 07Ch, 008h   ; jl 0x3cc9b7
        db 03Bh, 0BEh, 060h, 001h, 000h, 000h   ; cmp edi, dword ptr [esi + 0x160]
        db 077h, 031h   ; ja 0x3cc9e8
$L_3cc9b7:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 008h   ; jne 0x3cc9c3
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 021h, 058h, 010h   ; and dword ptr [eax + 0x10], ebx
        db 0EBh, 035h   ; jmp 0x3cc9f8
$L_3cc9c3:
        db 0F6h, 041h, 002h, 080h   ; test byte ptr [ecx + 2], 0x80
        db 074h, 00Bh   ; je 0x3cc9d4
        db 08Bh, 041h, 008h   ; mov eax, dword ptr [ecx + 8]
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 0EBh, 00Ch   ; jmp 0x3cc9e0
$L_3cc9d4:
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
        db 08Bh, 078h, 030h   ; mov edi, dword ptr [eax + 0x30]
        db 003h, 079h, 008h   ; add edi, dword ptr [ecx + 8]
        db 089h, 07Dh, 0FCh   ; mov dword ptr [ebp - 4], edi
$L_3cc9e0:
        db 08Bh, 07Dh, 0FCh   ; mov edi, dword ptr [ebp - 4]
        db 089h, 079h, 008h   ; mov dword ptr [ecx + 8], edi
        db 0EBh, 00Ah   ; jmp 0x3cc9f2
$L_3cc9e8:
        db 08Bh, 045h, 0F8h   ; mov eax, dword ptr [ebp - 8]
$L_3cc9eb:
        db 0C7h, 040h, 010h, 00Dh, 000h, 000h, 0C0h   ; mov dword ptr [eax + 0x10], 0xc000000d
$L_3cc9f2:
        db 083h, 07Dh, 0FCh, 000h   ; cmp dword ptr [ebp - 4], 0
        db 075h, 01Bh   ; jne 0x3cca13
$L_3cc9f8:
        db 083h, 060h, 014h, 000h   ; and dword ptr [eax + 0x14], 0
        db 032h, 0D2h   ; xor dl, dl
        db 08Bh, 0C8h   ; mov ecx, eax
        db 0FFh, 015h   ; call dword ptr [0x3cd53c]
        dd __imp_@IofCompleteRequest@8
        db 0FFh, 036h   ; push dword ptr [esi]
        db 0FFh, 015h   ; call dword ptr [0x3cd554]
        dd __imp__IoStartNextPacket@4
        db 0E9h, 0E7h, 000h, 000h, 000h   ; jmp 0x3ccafa
$L_3cca13:
        db 033h, 0C0h   ; xor eax, eax
        db 08Dh, 07Eh, 04Fh   ; lea edi, [esi + 0x4f]
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 0ABh   ; stosd dword ptr es:[edi], eax
        db 080h, 039h, 003h   ; cmp byte ptr [ecx], 3
        db 00Fh, 085h, 087h, 000h, 000h, 000h   ; jne 0x3ccaac
        db 08Bh, 0BEh, 068h, 001h, 000h, 000h   ; mov edi, dword ptr [esi + 0x168]
        db 08Bh, 0C2h   ; mov eax, edx
        db 033h, 0D2h   ; xor edx, edx
        db 0F7h, 0F7h   ; div edi
        db 080h, 066h, 00Fh, 0F1h   ; and byte ptr [esi + 0xf], 0xf1
        db 08Bh, 04Eh, 00Ch   ; mov ecx, dword ptr [esi + 0xc]
        db 085h, 0D2h   ; test edx, edx
        db 074h, 02Ch   ; je 0x3cca68
        db 08Bh, 0C7h   ; mov eax, edi
        db 02Bh, 0C2h   ; sub eax, edx
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 089h, 046h, 018h   ; mov dword ptr [esi + 0x18], eax
        db 076h, 010h   ; jbe 0x3cca57
        db 081h, 0C9h, 000h, 000h, 000h, 008h   ; or ecx, 0x8000000
        db 02Bh, 0C3h   ; sub eax, ebx
        db 089h, 04Eh, 00Ch   ; mov dword ptr [esi + 0xc], ecx
        db 089h, 046h, 01Ch   ; mov dword ptr [esi + 0x1c], eax
        db 0EBh, 028h   ; jmp 0x3cca7f
$L_3cca57:
        db 001h, 045h, 0F4h   ; add dword ptr [ebp - 0xc], eax
        db 001h, 045h, 0FCh   ; add dword ptr [ebp - 4], eax
        db 02Bh, 0D8h   ; sub ebx, eax
        db 081h, 0C9h, 000h, 000h, 000h, 002h   ; or ecx, 0x2000000
        db 089h, 04Eh, 00Ch   ; mov dword ptr [esi + 0xc], ecx
$L_3cca68:
        db 033h, 0D2h   ; xor edx, edx
        db 08Bh, 0C3h   ; mov eax, ebx
        db 0F7h, 0F7h   ; div edi
        db 085h, 0D2h   ; test edx, edx
        db 074h, 009h   ; je 0x3cca7b
        db 02Bh, 0DAh   ; sub ebx, edx
        db 080h, 04Eh, 00Fh, 004h   ; or byte ptr [esi + 0xf], 4
        db 089h, 056h, 01Ch   ; mov dword ptr [esi + 0x1c], edx
$L_3cca7b:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 00Ah   ; jne 0x3cca89
$L_3cca7f:
        db 06Ah, 000h   ; push 0
        db 056h   ; push esi
        call ?MU_DiskStartPartialWrite@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z   ; 0x3CC7FD
        db 0EBh, 071h   ; jmp 0x3ccafa
$L_3cca89:
        db 0F6h, 046h, 00Fh, 00Eh   ; test byte ptr [esi + 0xf], 0xe
        db 074h, 009h   ; je 0x3cca98
        db 0C7h, 046h, 030h   ; mov dword ptr [esi + 0x30], 0x3cc7fd
        dd ?MU_DiskStartPartialWrite@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
        db 0EBh, 007h   ; jmp 0x3cca9f
$L_3cca98:
        db 0C7h, 046h, 030h   ; mov dword ptr [esi + 0x30], 0x3cc057
        dd ?MU_DiskIoComplete@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
$L_3cca9f:
        db 08Bh, 055h, 0F4h   ; mov edx, dword ptr [ebp - 0xc]
        db 0C6h, 046h, 037h, 002h   ; mov byte ptr [esi + 0x37], 2
        db 0C6h, 046h, 04Fh, 02Ah   ; mov byte ptr [esi + 0x4f], 0x2a
        db 0EBh, 00Fh   ; jmp 0x3ccabb
$L_3ccaac:
        db 0C7h, 046h, 030h   ; mov dword ptr [esi + 0x30], 0x3cc371
        dd ?MU_DiskReadComplete@@YGXPAU_MU_DEVICE_EXTENSION@@J@Z
        db 0C6h, 046h, 037h, 001h   ; mov byte ptr [esi + 0x37], 1
        db 0C6h, 046h, 04Fh, 028h   ; mov byte ptr [esi + 0x4f], 0x28
$L_3ccabb:
        db 08Bh, 0BEh, 058h, 001h, 000h, 000h   ; mov edi, dword ptr [esi + 0x158]
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0EAh   ; shr edx, cl
        db 089h, 046h, 028h   ; mov dword ptr [esi + 0x28], eax
        db 089h, 05Eh, 02Ch   ; mov dword ptr [esi + 0x2c], ebx
        db 066h, 0C7h, 046h, 034h, 008h, 000h   ; mov word ptr [esi + 0x34], 8
        db 052h   ; push edx
        db 0C6h, 046h, 036h, 002h   ; mov byte ptr [esi + 0x36], 2
        call ?ReverseEndian@@YGKK@Z_0   ; 0x3CBFDD
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D3h, 0EBh   ; shr ebx, cl
        db 089h, 046h, 051h   ; mov dword ptr [esi + 0x51], eax
        db 08Bh, 0CEh   ; mov ecx, esi
        db 088h, 07Dh, 0FEh   ; mov byte ptr [ebp - 2], bh
        db 088h, 05Dh, 0FFh   ; mov byte ptr [ebp - 1], bl
        db 066h, 08Bh, 045h, 0FEh   ; mov ax, word ptr [ebp - 2]
        db 066h, 089h, 046h, 056h   ; mov word ptr [esi + 0x56], ax
        call ?MU_fStartMrb@@YIXPAU_MU_DEVICE_EXTENSION@@@Z   ; 0x3CD292
$L_3ccafa:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C3h   ; ret 
seg22 ENDS


        END
