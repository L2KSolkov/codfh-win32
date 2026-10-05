/*
 * Networking for the port (docs/WIN32_PORT.md W7): XNet over plain IP and the minimum of XOnline
 * that System Link needs. A console's XNADDR is its LAN address and Ethernet address; session
 * keys are random and need no registration; the Xbox's VDP sockets (game data plus voice, the
 * game's own framing) are UDP; QoS probes report every host as reached at once.
 *
 * Xbox Live is not available: nobody is signed in (four empty users), and the matchmaking,
 * friends, mute-list and logon-state calls fail as with no connection.
 */
#include <xtl.h>
#include <xonline.h>
#include <iphlpapi.h>
#include <bcrypt.h>
#include <stdlib.h>
#include <string.h>

#include "port.h"

#undef socket

static int wsa_ready;

static void wsa_start(void)
{
    if (!wsa_ready)
    {
        WSADATA wd;
        wsa_ready = WSAStartup(MAKEWORD(2, 2), &wd) == 0;
    }
}

extern "C" SOCKET WSAAPI xpal_socket(int af, int type, int protocol)
{
    wsa_start();
    int vdp = protocol == IPPROTO_VDP;
    if (vdp)
        protocol = IPPROTO_UDP;
    SOCKET s = socket(af, type, protocol);
    plog("socket(%d, %d, %s) = %d%s", af, type, vdp ? "VDP as UDP" : "UDP", (int)s,
         s == INVALID_SOCKET ? " (failed)" : "");
    return s;
}

/*
 * XNet
 */

extern "C" INT WINAPI XNetRandom(BYTE *pb, UINT cb)
{
    BCryptGenRandom(NULL, pb, cb, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    return 0;
}

extern "C" INT WINAPI XNetCreateKey(XNKID *pxnkid, XNKEY *pxnkey)
{
    XNetRandom(pxnkid->ab, sizeof(pxnkid->ab));
    pxnkid->ab[0] &= 0x0F;  /* a System Link key id (the top bits clear) */
    XNetRandom(pxnkey->ab, sizeof(pxnkey->ab));
    return 0;
}

extern "C" INT WINAPI XNetRegisterKey(const XNKID *, const XNKEY *)
{
    return 0;
}

extern "C" INT WINAPI XNetUnregisterKey(const XNKID *)
{
    return 0;
}

/* This machine's LAN address and Ethernet address: the first adapter that is up with IPv4. */
static int local_address(IN_ADDR *ina, BYTE *mac)
{
    ULONG size = 16 * 1024;
    IP_ADAPTER_ADDRESSES *list = (IP_ADAPTER_ADDRESSES *)malloc(size);
    int found = 0;
    if (GetAdaptersAddresses(AF_INET, GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER,
                             NULL, list, &size) == NO_ERROR)
    {
        for (IP_ADAPTER_ADDRESSES *a = list; a && !found; a = a->Next)
        {
            if (a->OperStatus != IfOperStatusUp || a->IfType == IF_TYPE_SOFTWARE_LOOPBACK || !a->FirstUnicastAddress)
                continue;
            sockaddr_in *sin = (sockaddr_in *)a->FirstUnicastAddress->Address.lpSockaddr;
            *ina = sin->sin_addr;
            memset(mac, 0, 6);
            memcpy(mac, a->PhysicalAddress, a->PhysicalAddressLength < 6 ? a->PhysicalAddressLength : 6);
            found = 1;
        }
    }
    free(list);
    return found;
}

extern "C" DWORD WINAPI XNetGetTitleXnAddr(XNADDR *pxna)
{
    wsa_start();
    memset(pxna, 0, sizeof(*pxna));
    if (!local_address(&pxna->ina, pxna->abEnet))
        return XNET_GET_XNADDR_NONE;
    return XNET_GET_XNADDR_ETHERNET | XNET_GET_XNADDR_DHCP;
}

extern "C" DWORD WINAPI XNetGetEthernetLinkStatus(void)
{
    IN_ADDR ina;
    BYTE mac[6];
    return local_address(&ina, mac) ? (XNET_ETHERNET_LINK_ACTIVE | 0x02 /* 100 Mbps */ | 0x08 /* full duplex */) : 0;
}

extern "C" INT WINAPI XNetXnAddrToInAddr(const XNADDR *pxna, const XNKID *, IN_ADDR *pina)
{
    *pina = pxna->ina;
    return 0;
}

extern "C" INT WINAPI XNetInAddrToXnAddr(const IN_ADDR ina, XNADDR *pxna, XNKID *pxnkid)
{
    if (pxna)
    {
        memset(pxna, 0, sizeof(*pxna));
        pxna->ina = ina;
    }
    if (pxnkid)
        memset(pxnkid, 0, sizeof(*pxnkid));
    return 0;
}

extern "C" INT WINAPI XNetQosListen(const XNKID *, const BYTE *, UINT, DWORD, DWORD)
{
    return 0;
}

extern "C" INT WINAPI XNetQosLookup(UINT cxna, const XNADDR *[], const XNKID *[], const XNKEY *[], UINT cina,
                                    const IN_ADDR[], const DWORD[], UINT cProbes, DWORD, DWORD, WSAEVENT hEvent,
                                    XNQOS **ppxnqos)
{
    UINT n = cxna + cina;
    XNQOS *q = (XNQOS *)calloc(1, sizeof(XNQOS) + (n ? n - 1 : 0) * sizeof(XNQOSINFO));
    q->cxnqos = n;
    q->cxnqosPending = 0;
    for (UINT i = 0; i < n; i++)
    {
        XNQOSINFO *e = &q->axnqosinfo[i];
        e->bFlags = XNET_XNQOSINFO_COMPLETE | XNET_XNQOSINFO_TARGET_CONTACTED;
        e->cProbesXmit = e->cProbesRecv = (WORD)cProbes;
        e->wRttMinInMsecs = e->wRttMedInMsecs = 1;
        e->dwUpBitsPerSec = e->dwDnBitsPerSec = 100000000;
    }
    *ppxnqos = q;
    if (hEvent)
        WSASetEvent(hEvent);
    return 0;
}

extern "C" INT WINAPI XNetQosRelease(XNQOS *pxnqos)
{
    free(pxnqos);
    return 0;
}

/*
 * XOnline: started; nobody signed in; the Live services unreachable.
 */

static XONLINE_USER logon_users[XONLINE_MAX_LOGON_USERS];

extern "C" HRESULT WINAPI XOnlineStartup(const XONLINE_STARTUP_PARAMS *)
{
    wsa_start();
    return S_OK;
}

extern "C" HRESULT WINAPI XOnlineTaskContinue(XONLINETASK_HANDLE)
{
    /* (no task ever starts: each Live call below fails) */
    return E_FAIL;
}

extern "C" HRESULT WINAPI XOnlineTaskClose(XONLINETASK_HANDLE)
{
    return S_OK;
}

extern "C" PXONLINE_USER WINAPI XOnlineGetLogonUsers(void)
{
    return logon_users;
}

extern "C" HRESULT WINAPI XOnlineLogonTaskGetResults(XONLINETASK_HANDLE)
{
    return E_FAIL;
}

extern "C" HRESULT WINAPI XOnlineSaveLogonState(PXONLINE_LOGON_STATE pLogonState)
{
    memset(pLogonState, 0, sizeof(*pLogonState));
    return E_FAIL;
}

extern "C" HRESULT WINAPI XOnlineRetrieveLogonState(const XONLINE_LOGON_STATE *, PXONLINE_USER, DWORD *,
                                                    DWORD *pdwServices)
{
    if (pdwServices)
        *pdwServices = 0;
    return E_FAIL;
}

#define LIVE_UNAVAILABLE(...)  \
    {                          \
        if (phTask)            \
            *phTask = NULL;    \
        return E_FAIL;         \
    }

extern "C" HRESULT WINAPI XOnlineMatchSessionCreate(DWORD, DWORD, DWORD, DWORD, DWORD, PXONLINE_ATTRIBUTE, HANDLE,
                                                    PXONLINETASK_HANDLE phTask)
LIVE_UNAVAILABLE()

extern "C" HRESULT WINAPI XOnlineMatchSessionUpdate(XNKID, DWORD, DWORD, DWORD, DWORD, DWORD, PXONLINE_ATTRIBUTE,
                                                    HANDLE, PXONLINETASK_HANDLE phTask)
LIVE_UNAVAILABLE()

extern "C" HRESULT WINAPI XOnlineMatchSessionDelete(XNKID, HANDLE, PXONLINETASK_HANDLE phTask)
LIVE_UNAVAILABLE()

extern "C" HRESULT WINAPI XOnlineMatchSessionFindFromID(XNKID, HANDLE, PXONLINETASK_HANDLE phTask)
LIVE_UNAVAILABLE()

extern "C" HRESULT WINAPI XOnlineMatchSearch(DWORD, DWORD, DWORD, const XONLINE_ATTRIBUTE *, DWORD, HANDLE,
                                             PXONLINETASK_HANDLE phTask)
LIVE_UNAVAILABLE()

extern "C" HRESULT WINAPI XOnlineMutelistStartup(HANDLE, PXONLINETASK_HANDLE phTask)
LIVE_UNAVAILABLE()

extern "C" HRESULT WINAPI XOnlineMutelistGet(DWORD, DWORD, HANDLE, PXONLINETASK_HANDLE phTask,
                                             PXONLINE_MUTELISTUSER, DWORD *pdwNumMutelistUsers)
{
    if (pdwNumMutelistUsers)
        *pdwNumMutelistUsers = 0;
    LIVE_UNAVAILABLE()
}

extern "C" HRESULT WINAPI XOnlineMatchSessionGetInfo(XONLINETASK_HANDLE, XNKID *pSessionID, XNKEY *pKeyExchangeKey)
{
    if (pSessionID)
        memset(pSessionID, 0, sizeof(*pSessionID));
    if (pKeyExchangeKey)
        memset(pKeyExchangeKey, 0, sizeof(*pKeyExchangeKey));
    return E_FAIL;
}

extern "C" DWORD WINAPI XOnlineMatchSearchResultsLen(DWORD dwNumResults, DWORD, const XONLINE_ATTRIBUTE_SPEC *)
{
    return dwNumResults * sizeof(XONLINE_MATCH_SEARCHRESULT);
}

extern "C" HRESULT WINAPI XOnlineMatchSearchGetResults(XONLINETASK_HANDLE, PXONLINE_MATCH_SEARCHRESULT **pp,
                                                       DWORD *pdwReturnedResults)
{
    if (pp)
        *pp = NULL;
    if (pdwReturnedResults)
        *pdwReturnedResults = 0;
    return E_FAIL;
}

extern "C" HRESULT WINAPI XOnlineMatchSearchParse(const XONLINE_MATCH_SEARCHRESULT *, DWORD,
                                                  const XONLINE_ATTRIBUTE_SPEC *, PVOID)
{
    return E_FAIL;
}

extern "C" HRESULT WINAPI XOnlineFriendsGetAcceptedGameInvite(PXONLINE_ACCEPTED_GAMEINVITE p)
{
    if (p)
        memset(p, 0, sizeof(*p));
    return S_FALSE;     /* no invite */
}
