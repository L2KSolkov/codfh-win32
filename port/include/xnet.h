/*
 * Win32 port bridge (docs/WIN32_PORT.md W7): XNet, the Xbox's secure networking layer, which the
 * XDK's xtl.h brings in with its sockets API. The port runs XNet over plain IP (System Link only):
 * port/xnet implements these calls, Winsock 2 (from xtl.h) provides the sockets themselves.
 *
 * Declared from what the game's network code (systemlink.h, cXboxLive, unit_1D8370, unit_1DC6C0,
 * unit_1DBF50) uses. The structures are byte-packed: the game embeds them in its own packed
 * messages and session records, so their sizes are part of the game's layouts.
 */
#ifndef PORT_XNET_H
#define PORT_XNET_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

/* A console's network address, as hosts advertise it and peers resolve it (0x24 bytes). */
typedef struct
{
    IN_ADDR ina;            /* its LAN address */
    IN_ADDR inaOnline;
    WORD wPortOnline;
    BYTE abEnet[6];         /* its Ethernet address */
    BYTE abOnline[20];
} XNADDR;

/* A session's key id and its key-exchange key. */
typedef struct
{
    BYTE ab[8];
} XNKID;

typedef struct
{
    BYTE ab[16];
} XNKEY;

/* One probed host's quality-of-service result. */
typedef struct
{
    BYTE bFlags;            /* XNET_XNQOSINFO_* */
    BYTE bReserved;
    WORD cProbesXmit;
    WORD cProbesRecv;
    WORD cbData;            /* the host's reply data (its XNetQosListen block) */
    BYTE *pbData;
    WORD wRttMinInMsecs;
    WORD wRttMedInMsecs;
    DWORD dwUpBitsPerSec;
    DWORD dwDnBitsPerSec;
} XNQOSINFO;

/* An XNetQosLookup's results: one entry per host asked. */
typedef struct
{
    UINT cxnqos;
    UINT cxnqosPending;
    XNQOSINFO axnqosinfo[1];
} XNQOS;

#pragma pack(pop)

#define XNET_XNQOSINFO_COMPLETE 0x01
#define XNET_XNQOSINFO_TARGET_CONTACTED 0x02
#define XNET_XNQOSINFO_TARGET_DISABLED 0x04
#define XNET_XNQOSINFO_DATA_RECEIVED 0x08

#define XNET_QOS_LISTEN_ENABLE 0x01
#define XNET_QOS_LISTEN_DISABLE 0x02
#define XNET_QOS_LISTEN_SET_DATA 0x04
#define XNET_QOS_LISTEN_SET_BITSPERSEC 0x08
#define XNET_QOS_LISTEN_RELEASE 0x10

/* The Xbox's voice/data protocol: UDP with an unencrypted voice section (the game's sockets). */
#define IPPROTO_VDP 254

/* XNetGetTitleXnAddr's result flags. */
#define XNET_GET_XNADDR_PENDING 0x0000
#define XNET_GET_XNADDR_NONE 0x0001
#define XNET_GET_XNADDR_ETHERNET 0x0002
#define XNET_GET_XNADDR_STATIC 0x0004
#define XNET_GET_XNADDR_DHCP 0x0008

/* XNetGetEthernetLinkStatus's flags. */
#define XNET_ETHERNET_LINK_ACTIVE 0x01

INT WINAPI XNetRandom(BYTE *pb, UINT cb);
INT WINAPI XNetCreateKey(XNKID *pxnkid, XNKEY *pxnkey);
INT WINAPI XNetRegisterKey(const XNKID *pxnkid, const XNKEY *pxnkey);
INT WINAPI XNetUnregisterKey(const XNKID *pxnkid);
INT WINAPI XNetXnAddrToInAddr(const XNADDR *pxna, const XNKID *pxnkid, IN_ADDR *pina);
INT WINAPI XNetInAddrToXnAddr(const IN_ADDR ina, XNADDR *pxna, XNKID *pxnkid);
INT WINAPI XNetQosListen(const XNKID *pxnkid, const BYTE *pb, UINT cb, DWORD dwBitsPerSec,
                         DWORD dwFlags);
INT WINAPI XNetQosLookup(UINT cxna, const XNADDR *apxna[], const XNKID *apxnkid[],
                         const XNKEY *apxnkey[], UINT cina, const IN_ADDR aina[],
                         const DWORD adwServiceId[], UINT cProbes, DWORD dwBitsPerSec,
                         DWORD dwFlags, WSAEVENT hEvent, XNQOS **ppxnqos);
INT WINAPI XNetQosRelease(XNQOS *pxnqos);
DWORD WINAPI XNetGetTitleXnAddr(XNADDR *pxna);
DWORD WINAPI XNetGetEthernetLinkStatus(void);

typedef char port_check_XNADDR[sizeof(XNADDR) == 0x24 ? 1 : -1];
typedef char port_check_XNQOSINFO[sizeof(XNQOSINFO) == 0x18 ? 1 : -1];

#ifdef __cplusplus
}
#endif

#endif
