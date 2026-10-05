; codfh-match: XDK library data in XON_RD (repacked)
; An XDK stand-in repacked from the image (PLAN M3: library data the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2data.py, never decompiled).

        .686p
        .model flat
EXTERN ?dircrawlCleanupHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z:BYTE
EXTERN ?dircrawlCrawlDirHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z:BYTE
EXTERN ?dircrawlOnDirHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z:BYTE
EXTERN ?dircrawlOnFileHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z:BYTE
EXTERN ?storulCleanup@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulCloseFile@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulCompleteMetadata@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulCompletePackage@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulCreateMetadata@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulFinalWrite@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulGetTickets@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulOpenReadFile@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulPostTask@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulPreTask@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulReadFile@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulResolveName@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulScanFiles@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulStartUpload@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulUpload@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?storulWriteFile@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE
EXTERN ?sub_F0000@@YAXXZ:BYTE
EXTERN ?xrldlCleanupHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrldlConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrldlPostDownloadHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrldlPreConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrldlProcessDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrldlReceiveHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrldlSendHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulCleanupHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulDelayedConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulPostUploadHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulPreConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulReadDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulReceivePagedStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulReceiveStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulResultsAvailableHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?xrlulSendDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z:BYTE
EXTERN ?storulCreatePackage@CXo@@IAEJPAUXONLINETASK_STORAGE_UPLOAD@@@Z:BYTE












dseg11 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_538F6A @ 0x00538F6A
PUBLIC _unk_538F6A
_unk_538F6A LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h
dseg11 ENDS






dseg17 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_539058 @ 0x00539058
PUBLIC _unk_539058
_unk_539058 LABEL BYTE
        dd ?xrldlPreConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulDelayedConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrldlConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrldlSendHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrldlReceiveHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrldlProcessDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrldlPostDownloadHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrldlCleanupHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulPreConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulDelayedConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulConnectHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulReadDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulSendDataHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulReceiveStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulReceivePagedStatusHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulResultsAvailableHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulPostUploadHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
        dd ?xrlulCleanupHandler@CXo@@IAEJPAUXRL_ASYNC@@@Z
dseg17 ENDS

dseg17_s1 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_5390B4 @ 0x005390B4
PUBLIC _unk_5390B4
_unk_5390B4 LABEL BYTE
        db 000h, 000h, 000h, 000h
dseg17_s1 ENDS











dseg26 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_53972E @ 0x0053972E
PUBLIC _unk_53972E
_unk_53972E LABEL BYTE
        db 000h, 000h, 001h, 000h, 000h, 000h, 0D9h, 016h, 009h, 000h
dseg26 ENDS

dseg27 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_539775 @ 0x00539775
PUBLIC _unk_539775
_unk_539775 LABEL BYTE
        db 000h, 000h, 000h, 031h, 02Eh, 030h, 030h, 02Eh, 035h, 038h, 034h, 039h, 02Eh, 039h, 000h
dseg27 ENDS











dseg38 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_539EF5 @ 0x00539EF5
PUBLIC _unk_539EF5
_unk_539EF5 LABEL BYTE
        db 000h, 000h, 000h, 025h, 073h, 05Ch, 025h, 073h, 000h, 000h, 000h, 054h, 03Ah, 05Ch, 000h
        dd ?dircrawlCrawlDirHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z
        dd ?dircrawlOnDirHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z
        dd ?dircrawlOnFileHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z
        dd ?dircrawlCleanupHandler@CXo@@IAEJPAUXONLINETASK_DIRCRAWL@@@Z
dseg38 ENDS







dseg45 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_53A279 @ 0x0053A279
PUBLIC _unk_53A279
_unk_53A279 LABEL BYTE
        db 000h, 000h, 000h, 02Fh, 029h, 03Dh, 000h, 0CCh, 0A2h, 053h, 000h, 0C0h, 0A2h, 053h, 000h, 0B4h
        db 0A2h, 053h, 000h, 0A4h, 0A2h, 053h, 000h, 094h, 0A2h, 053h, 000h
dseg45 ENDS


dseg46 SEGMENT BYTE PUBLIC READONLY ALIAS('XON_RD') 'DATA'

; // match: _unk_53A32F @ 0x0053A32F
PUBLIC _unk_53A32F
_unk_53A32F LABEL BYTE
        db 000h, 02Fh, 06Dh, 073h, 067h, 073h, 065h, 072h, 076h, 065h, 072h, 02Fh, 067h, 065h, 074h, 073h
        db 074h, 072h, 069h, 06Eh, 067h, 02Eh, 061h, 073h, 068h, 078h, 000h, 000h, 000h, 02Fh, 06Dh, 073h
        db 067h, 073h, 065h, 072h, 076h, 065h, 072h, 02Fh, 076h, 065h, 074h, 073h, 074h, 072h, 069h, 06Eh
        db 067h, 02Eh, 061h, 073h, 068h, 078h, 000h, 000h, 000h
dseg46 ENDS

        END
