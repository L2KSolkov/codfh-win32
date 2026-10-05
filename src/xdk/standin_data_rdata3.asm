; codfh-match: XDK library data in .rdata beside other objects (WMA, XNET, calccost)
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat
EXTERN ?EnetPush@CXbdmClient@CXnNic@@UAEXXZ:BYTE
EXTERN ?EnetRecv@CXbdmClient@CXnNic@@UAEXIPAXII@Z:BYTE
EXTERN ?GetXnAddr@CXbdmClient@CXnNic@@UAEKPAUXNADDRXBDM@2@@Z:BYTE
EXTERN ?XmitComplete@CXbdmClient@CXnNic@@UAEXPAX@Z:BYTE

dseg0 SEGMENT BYTE PUBLIC READONLY ALIAS('.rdata') 'DATA'
; // match: _unk_3F13C8 @ 0x003F13C8
PUBLIC _unk_3F13C8
_unk_3F13C8 LABEL BYTE
        dd ?XmitComplete@CXbdmClient@CXnNic@@UAEXPAX@Z
        dd ?EnetRecv@CXbdmClient@CXnNic@@UAEXIPAXII@Z
        dd ?EnetPush@CXbdmClient@CXnNic@@UAEXXZ
        dd ?GetXnAddr@CXbdmClient@CXnNic@@UAEKPAUXNADDRXBDM@2@@Z
dseg0 ENDS




        END
