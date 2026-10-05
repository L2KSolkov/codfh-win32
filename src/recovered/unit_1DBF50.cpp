// cXboxSocket (the game's UDP socket) and the Xbox Live matchmaking queries: split from
// unit_1D7CE0.cpp at 0x1DBF50, an original object boundary (docs/units.md; PLAN M7).

#include <string.h>
#include "game/systemlink.h"
#include "types/cXboxLive.h"
#include "game/gameloop.h"
#include "types/cXboxLiveNetGame.h"

// 0x0042CD30
type_42CD30 unk_42CD30[33] = {
    { 10013, "Permission denied" },
    { 10048, "Address already in use" },
    { 10049, "Cannot assign requested address" },
    { 10047, "Address family not supported by protocol family" },
    { 10037, "Operation already in progress" },
    { 10103, "Operation cancelled" },
    { 10061, "Connection refused" },
    { 10054, "Connection reset by peer" },
    { 10014, "Bad address" },
    { 10065, "No route to host" },
    { 10036, "Operation now in progress" },
    { 10022, "Invalid argument" },
    { 10056, "Socket is already connected" },
    { 10040, "Message too long" },
    { 10050, "Network is down" },
    { 10055, "No buffer space available" },
    { 10042, "Bad protocol option" },
    { 10057, "Socket is not connected" },
    { 10038, "Socket operation on nonsocket" },
    { 10043, "Protocol not supported" },
    { 10058, "Cannot send after socket shutdown" },
    { 10044, "Socket type not supported" },
    { 10060, "Connection timed out" },
    { 10035, "Resource temporarily unavailable" },
    { 11001, "Host not found" },
    { 996, "Overlapped I/O event object not in signaled state" },
    { 997, "Overlapped operations will complete later" },
    { 10093, "Successful WSAStartup not yet performed" },
    { 11004, "Valid name, no data record of requested type" },
    { 10107, "System call failure" },
    { 10091, "Network subsystem is unavailable" },
    { 11002, "Nonauthoritative host not found" },
    { 10092, "Winsock version out of range" },
};
// End of its data definitions.


extern void (*off_42CD14)(const RwChar *arg_0, ...);
// match: ??0cXboxSocket@@QAE@XZ @ 0x001DBF50
// match: ??_C@_0BN@NCBCBEJJ@Winsock?5version?5out?5of?5range?$AA@ @ 0x003E5EFC
// match: ??_C@_0CA@DOKOCCFB@Nonauthoritative?5host?5not?5found?$AA@ @ 0x003E5F1C
// match: ??_C@_0CB@PLJNFILF@Network?5subsystem?5is?5unavailable@ @ 0x003E5F3C
// match: ??_C@_0BE@GAGGAMME@System?5call?5failure?$AA@ @ 0x003E5F60
// match: ??_C@_0CN@KFPNHBIN@Valid?5name?0?5no?5data?5record?5of?5re@ @ 0x003E5F74
// match: ??_C@_0CI@CFJNLLNI@Successful?5WSAStartup?5not?5yet?5pe@ @ 0x003E5FA4
// match: ??_C@_0CK@PEHIHHCA@Overlapped?5operations?5will?5compl@ @ 0x003E5FCC
// match: ??_C@_0DC@LHCPDIL@Overlapped?5I?1O?5event?5object?5not?5@ @ 0x003E5FF8
// match: ??_C@_0P@CAFMJNJH@Host?5not?5found?$AA@ @ 0x003E602C
// match: ??_C@_0CB@EPFKGNAK@Resource?5temporarily?5unavailable@ @ 0x003E603C
// match: ??_C@_0BF@IBBHAGLD@Connection?5timed?5out?$AA@ @ 0x003E6060
// match: ??_C@_0BK@LMAIHBL@Socket?5type?5not?5supported?$AA@ @ 0x003E6078
// match: ??_C@_0CC@DAIJOIKC@Cannot?5send?5after?5socket?5shutdow@ @ 0x003E6094
// match: ??_C@_0BH@JNBKLLAJ@Protocol?5not?5supported?$AA@ @ 0x003E60B8
// match: ??_C@_0BO@PFGGHOGH@Socket?5operation?5on?5nonsocket?$AA@ @ 0x003E60D0
// match: ??_C@_0BI@ILAOGBJJ@Socket?5is?5not?5connected?$AA@ @ 0x003E60F0
// match: ??_C@_0BE@NEGCDJON@Bad?5protocol?5option?$AA@ @ 0x003E6108
// match: ??_C@_0BK@OCAHGMEA@No?5buffer?5space?5available?$AA@ @ 0x003E611C
// match: ??_C@_0BA@LPIEBGEK@Network?5is?5down?$AA@ @ 0x003E6138
// match: ??_C@_0BB@NDAKHOCP@Message?5too?5long?$AA@ @ 0x003E6148
// match: ??_C@_0BM@CCONNCKE@Socket?5is?5already?5connected?$AA@ @ 0x003E615C
// match: ??_C@_0BB@HMGGCEBG@Invalid?5argument?$AA@ @ 0x003E6178
// match: ??_C@_0BK@LBMNDGCG@Operation?5now?5in?5progress?$AA@ @ 0x003E618C
// match: ??_C@_0BB@PFBILCPA@No?5route?5to?5host?$AA@ @ 0x003E61A8
// match: ??_C@_0M@LOEHLCJD@Bad?5address?$AA@ @ 0x003E61BC
// match: ??_C@_0BJ@FJAMCHKE@Connection?5reset?5by?5peer?$AA@ @ 0x003E61C8
// match: ??_C@_0BD@NPDMPPFP@Connection?5refused?$AA@ @ 0x003E61E4
// match: ??_C@_0BE@BBLFCLHJ@Operation?5cancelled?$AA@ @ 0x003E61F8
// match: ??_C@_0BO@BMABNIPB@Operation?5already?5in?5progress?$AA@ @ 0x003E620C
// match: ??_C@_0DA@KDGLCJJO@Address?5family?5not?5supported?5by?5@ @ 0x003E622C
// match: ??_C@_0CA@NBHADPNL@Cannot?5assign?5requested?5address?$AA@ @ 0x003E625C
// match: ??_C@_0BH@LOKACPE@Address?5already?5in?5use?$AA@ @ 0x003E627C
// match: ??_C@_0BC@HFNFNKAI@Permission?5denied?$AA@ @ 0x003E6294
// match: ??_C@_0CP@BDFJHOKO@cXboxSocket?3?3create?$CI?$CJ?5failed?5to?5@ @ 0x003E62A8
// match: ??_C@_0DK@IKJLFOFE@cXboxSocket?3?3create?$CI?$CJ?5failed?5to?5@ @ 0x003E62D8
// match: ??_C@_0EC@CKONFCNG@cXboxSocket?3?3create?$CI?$CJ?5failed?5to?5@ @ 0x003E6318
// match: ??_C@_0DJ@CINIEJCI@cXboxSocket?3?3create?$CI?$CJ?5failed?5to?5@ @ 0x003E635C
// match: ??_C@_0EL@CKBANNPN@cXboxSocket?3?3receiveMessage?$CI?$CJ?5?9?5@ @ 0x003E6398
// match: ??_C@_0EK@KFECJPAK@cXboxSocket?3?3receiveMessage?$CI?$CJ?5?9?5@ @ 0x003E63E8
// match: ??_C@_0GF@BNCFFIDE@cXboxSocket?3?3receiveMessage?$CI?$CJ?5?9?5@ @ 0x003E6438
// match: ??_C@_0EN@DNEPAOOF@cXboxSocket?3?3receiveMessage?$CI?$CJ?5?9?5@ @ 0x003E64A0
// match: ??_C@_0EM@PBDBHLNH@cXboxSocket?3?3receiveMessage?$CI?$CJ?5?9?5@ @ 0x003E64F0
// match: ??_C@_0DD@CFMLBCPF@cXboxSocket?3?3receiveMessage?$CI?$CJ?5?9?5@ @ 0x003E653C
// match: ??_C@_0CE@BGLLEMNF@cXboxSocket?3?3broadcast?$CI?$CJ?5?9?5Failu@ @ 0x003E6570
// match: ??_C@_0DN@OPHHCGGB@cXboxSocket?3?3sendMessage?$CI?$CJ?5?9?5Inc@ @ 0x003E6594
// match: ??_C@_0DA@JMOOBCJN@cXboxSocket?3?3sendMessage?$CI?$CJ?5?9?5SOC@ @ 0x003E65D4
// match: ??_C@_0DL@EEDCHHDM@cXboxSocket?3?3incomingMessageWait@ @ 0x003E6604
// match: ??_C@_0DP@ILEKNMPF@cXboxSocket?5?3?5Unrecoverable?5erro@ @ 0x003E6640
// match: ?unk_42CD30@@3PAUtype_42CD30@@A @ 0x0042CD30
cXboxSocket::cXboxSocket()
{
    unk_04 = INVALID_SOCKET;
}

extern type_42CD30 unk_42CD30[];
// match: ?create@cXboxSocket@@QAEHI@Z @ 0x001DBF70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxSocket::create(RwUInt32 arg_0)
{
    sockaddr_in var_38;
    RwInt32 var_28;
    sockaddr_in ebp_24;
    u_long lv_10;
    u_long var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = arg_0 == 1 ? IPPROTO_VDP : IPPROTO_UDP;
    unk_04 = socket(AF_INET, SOCK_DGRAM, bp_8);
    if (unk_04 != INVALID_SOCKET)
    {
        unk_00 = arg_0;
        if (arg_0 == 2)
        {
            ebp_24.sin_family = AF_INET;
            ebp_24.sin_addr.s_addr = INADDR_ANY;
            ebp_24.sin_port = htons(1001);
            var_28 = bind(unk_04, (sockaddr *)&ebp_24, sizeof(ebp_24));
            if (var_28 == 0)
            {
            }
            else
            {
                if (0)
                    off_42CD14("cXboxSocket::create() failed to bind socket, closing it\n");
                sub_1DC130();
            }
            var_C = 1;
            bp_4 = setsockopt(unk_04, SOL_SOCKET, SO_BROADCAST, (const RwChar *)&var_C, sizeof(var_C));
            if (bp_4 == 0)
            {
            }
            else
            {
                if (0)
                    off_42CD14("cXboxSocket::create() failed to set broadcast socket, closing it\n");
                sub_1DC130();
            }
            lv_10 = 1;
            var_28 = ioctlsocket(unk_04, FIONBIO, &lv_10);
            if (var_28 == 0)
                return 1;
            if (0)
                off_42CD14("cXboxSocket::create() failed to make socket non-blocking\n");
            sub_1DC130();
        }
        else
        {
            var_38.sin_addr.s_addr = INADDR_ANY;
            var_38.sin_family = AF_INET;
            var_38.sin_port = htons(1000);
            // A compiled-out check (docs/toolchain.md).
            if (!unk_00)
            {
            }
            bp_4 = bind(unk_04, (sockaddr *)&var_38, sizeof(var_38));
            if (bp_4 == 0)
                return 1;
            if (0)
                off_42CD14("cXboxSocket::create() failed to bind socket, closing it\n");
            sub_1DC130();
        }
    }
    else if (0)
        off_42CD14("cXboxSocket::create() failed to create socket\n");
    return 0;
}
// match: ?sub_1DC130@cXboxSocket@@QAEXXZ @ 0x001DC130
void cXboxSocket::sub_1DC130()
{
    // A compiled-out check (docs/toolchain.md).
    if (!unk_00)
    {
    }
    if (unk_04 != INVALID_SOCKET)
    {
        closesocket(unk_04);
        unk_04 = INVALID_SOCKET;
    }
}
// match: ?receiveMessage@cXboxSocket@@QAEHPAEH0HPAH1PAUsockaddr_in@@@Z @ 0x001DC160
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 cXboxSocket::receiveMessage(RwUInt8 *arg_0, RwInt32 arg_4, RwUInt8 *arg_8, RwInt32 arg_C, RwInt32 *arg_10,
                                    RwInt32 *arg_14, sockaddr_in *arg_18)
{
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (unk_00 == 1)
    {
        bp_8 = sizeof(sockaddr_in);
        // A compiled-out check (docs/toolchain.md).
        if (!unk_00)
        {
        }
        bp_4 = recvfrom(unk_04, (RwChar *)&unk_08, 0xA32, 0, (sockaddr *)arg_18, &bp_8);
        if (bp_4 == SOCKET_ERROR)
        {
            if (0)
                off_42CD14("cXboxSocket::receiveMessage() - SOCKET_ERROR (%s)\n", sub_1DC5C0());
            sub_1DC600();
            return 0;
        }
        if (bp_8 != sizeof(sockaddr_in))
        {
            if (0)
                off_42CD14("cXboxSocket::receiveMessage() - Returned socket address of unexpected size\n");
            return 0;
        }
        if (bp_4 < 2)
        {
            if (0)
                off_42CD14("cXboxSocket::receiveMessage() - Got VDP packet with less than 2 bytes in it\n");
            return 0;
        }
        *arg_10 = unk_08;
        *arg_14 = bp_4 - *arg_10 - 2;
        if ((RwUInt32)*arg_10 > (RwUInt32)(bp_4 - 2))
        {
            if (0)
                off_42CD14("cXboxSocket::receiveMessage() - Game message size in packet is invalid (larger than "
                           "remaining data)\n");
            return 0;
        }
        if (arg_0 && (RwUInt32)*arg_10 > (RwUInt32)arg_4)
        {
            if (0)
                off_42CD14("cXboxSocket::receiveMessage() - Game message larger than provided buffer\n");
            return 0;
        }
        if (arg_8 && (RwUInt32)*arg_14 > (RwUInt32)arg_C)
        {
            if (0)
                off_42CD14("cXboxSocket::receiveMessage() - Voice message larger than provided buffer\n");
            return 0;
        }
        if (arg_0 && *arg_10)
            memcpy(arg_0, unk_0A, *arg_10);
        if (arg_8 && *arg_14)
            memcpy(arg_8, &unk_0A[*arg_10], *arg_14);
        return 1;
    }
    // A compiled-out check (docs/toolchain.md).
    if (!unk_00)
    {
    }
    var_C = recv(unk_04, (RwChar *)arg_0, arg_4, 0);
    if (var_C != SOCKET_ERROR)
    {
        // A compiled-out check (docs/toolchain.md).
        if (!unk_00)
        {
        }
        *arg_10 = var_C;
        return 1;
    }
    return 0;
}
// match: ?broadcast@cXboxSocket@@QAEHPBDH@Z @ 0x001DC340
RwInt32 cXboxSocket::broadcast(const RwChar *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
    sockaddr_in var_18;

    var_18.sin_family = AF_INET;
    var_18.sin_addr.s_addr = INADDR_BROADCAST;
    var_18.sin_port = htons(1001);
    var_4 = sendto(unk_04, arg_0, arg_4, 0, (sockaddr *)&var_18, sizeof(var_18));
    if (var_4 == arg_4)
        return 1;
    if (0)
        off_42CD14("cXboxSocket::broadcast() - Failure\n");
    return 0;
}
// match: ?sendMessage@cXboxSocket@@QAEHPBXHHHPBUsockaddr_in@@@Z @ 0x001DC3C0
RwInt32 cXboxSocket::sendMessage(const void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                 const sockaddr_in *arg_10)
{
    RwInt32 var_4;

    // A compiled-out check (docs/toolchain.md).
    if (!unk_08)
    {
    }
    unk_08 = (RwUInt16)arg_4;
    if (arg_4)
        memcpy(unk_0A, arg_0, arg_4);
    if (arg_C)
        memcpy(&unk_0A[arg_4], (const void *)arg_8, arg_C);
    var_4 = sendto(unk_04, (const RwChar *)&unk_08, arg_4 + arg_C + 2, 0, (const sockaddr *)arg_10, sizeof(sockaddr_in));
    if (var_4 == SOCKET_ERROR)
    {
        if (0)
            off_42CD14("cXboxSocket::sendMessage() - SOCKET_ERROR (%s)\n", sub_1DC5C0());
        sub_1DC600();
        return 0;
    }
    if (var_4 != arg_4 + arg_C + 2)
    {
        if (0)
            off_42CD14("cXboxSocket::sendMessage() - Incorrect number of bytes sent\n");
        return 0;
    }
    return 1;
}
// match: ?incomingMessageWaiting@cXboxSocket@@QAEHXZ @ 0x001DC4A0
RwInt32 cXboxSocket::incomingMessageWaiting()
{
    RwInt32 var_4;
    fd_set var_110;
    timeval var_118;

    var_118.tv_sec = 0;
    var_118.tv_usec = 0;
    FD_ZERO(&var_110);
    // A compiled-out check (docs/toolchain.md).
    if (!unk_00)
    {
    }
    FD_SET(unk_04, &var_110);
    var_4 = select(0, &var_110, NULL, NULL, &var_118);
    if (var_4 == SOCKET_ERROR)
    {
        if (0)
            off_42CD14("cXboxSocket::incomingMessageWaiting() - SOCKET_ERROR (%s)\n", sub_1DC5C0());
        sub_1DC600();
        return 0;
    }
    return var_4 == 1;
}
// match: ?sub_1DC5C0@cXboxSocket@@QAEPBDXZ @ 0x001DC5C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
const RwChar *cXboxSocket::sub_1DC5C0()
{
    type_42CD30 *l4 = unk_42CD30;
    RwInt32 var_8 = WSAGetLastError();

    do
    {
        if (l4->unk_00 == var_8)
            break;
        l4++;
    } while (l4->unk_00 != 0);
    return l4->unk_04;
}
// match: ?sub_1DC600@cXboxSocket@@QAEXXZ @ 0x001DC600
void cXboxSocket::sub_1DC600()
{
    RwInt32 var_4 = WSAGetLastError();

    switch (var_4)
    {
    case WSAEACCES:
    case WSAEINVAL:
    case WSAENOTSOCK:
    case WSAEAFNOSUPPORT:
    case WSAEADDRNOTAVAIL:
    case WSAECONNRESET:
    case WSAENOTCONN:
    case WSAESHUTDOWN:
    case WSAETIMEDOUT:
    case WSANOTINITIALISED:
        if (0)
            off_42CD14("cXboxSocket : Unrecoverable error encountered, closing socket\n");
        sub_1DC130();
        break;
    }
}
