// Split from unit_1DBF50.cpp at 0x1DC6C0, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include <string.h>
#include "game/systemlink.h"
#include "types/cXboxLive.h"
#include "game/gameloop.h"
#include "types/cXboxLiveNetGame.h"

// CSession: the MatchSim sample's (match.cpp), statement for statement where
// the game's agrees.
// match: ??0CSession@@QAE@XZ @ 0x001DC6C0
// match: _QuickmatchAttributeSpec @ 0x003E6680
CSession::CSession()
{
    m_State = STATE_IDLE;
    m_hSessionTask = NULL;
    m_bUpdate = FALSE;
    m_bListening = FALSE;
    m_bKeyRegistered = FALSE;
    SetupAttributes();
}
// match: ??1CSession@@QAE@XZ @ 0x001DC750
CSession::~CSession()
{
    Reset();
}
// match: ?Reset@CSession@@QAEXXZ @ 0x001DC770
void CSession::Reset()
{
    Close();
    Listen(FALSE, NO_WAIT);
    PurgeSessionQ(TRUE);
    if (m_bKeyRegistered)
    {
        XNetUnregisterKey(&SessionID);
        m_bKeyRegistered = FALSE;
    }
}
// match: ?Create@CSession@@QAEJXZ @ 0x001DC7C0
HRESULT CSession::Create()
{
    HRESULT hr = XOnlineMatchSessionCreate(PublicFilled, PublicOpen, PrivateFilled, PrivateOpen, 9, m_Attributes, NULL,
                                           &m_hSessionTask);

    switch (hr)
    {
    case S_OK:
        m_State = STATE_CREATING;
        break;
    }
    return hr;
}
// match: ?Update@CSession@@QAEJXZ @ 0x001DC830
HRESULT CSession::Update()
{
    switch (m_State)
    {
    case STATE_IDLE:
    case STATE_DELETING:
        return E_UNEXPECTED;
    case STATE_CREATING:
    case STATE_UPDATING:
        m_bUpdate = TRUE;
        return S_OK;
    case STATE_ACTIVE:
        {
            XOnlineTaskClose(m_hSessionTask);
            m_hSessionTask = NULL;

            HRESULT hr = XOnlineMatchSessionUpdate(SessionID, PublicFilled, PublicOpen, PrivateFilled, PrivateOpen, 9,
                                                   m_Attributes, NULL, &m_hSessionTask);

            m_bUpdate = FALSE;

            if (SUCCEEDED(hr))
                m_State = STATE_UPDATING;
            else
                Close();

            return hr;
        }
    default:
        return E_UNEXPECTED;
    }
}
// match: ?Delete@CSession@@QAEJXZ @ 0x001DC930
HRESULT CSession::Delete()
{
    HRESULT hr = S_OK;

    switch (m_State)
    {
    case STATE_IDLE:
        break;
    case STATE_CREATING:
        Close();
        break;
    case STATE_UPDATING:
        Close();
        Listen(FALSE);
        break;
    case STATE_DELETING:
        break;
    case STATE_ACTIVE:
        if (m_bListening)
        {
            Listen(FALSE);
        }
        else
        {
            INT iResult = XNetUnregisterKey(&SessionID);
        }
        m_bKeyRegistered = FALSE;
        Close();
        hr = XOnlineMatchSessionDelete(SessionID, NULL, &m_hSessionTask);
        if (SUCCEEDED(hr))
            m_State = STATE_DELETING;
        break;
    }
    return hr;
}
// match: ?ProcessStateCreateSession@CSession@@QAEJXZ @ 0x001DCA00
HRESULT CSession::ProcessStateCreateSession()
{
    HRESULT hr = XOnlineTaskContinue(m_hSessionTask);

    switch (hr)
    {
    case XONLINETASK_S_RUNNING:
    case XONLINETASK_S_RESULTS_AVAIL:
        break;
    case XONLINETASK_S_SUCCESS:
        {
            HRESULT hrGet = XOnlineMatchSessionGetInfo(m_hSessionTask, &SessionID, &KeyExchangeKey);
            m_State = STATE_ACTIVE;

            INT iKeyRegistered = XNetRegisterKey(&SessionID, &KeyExchangeKey);
            if (iKeyRegistered == WSAENOMORE)
            {
                PurgeSessionQHead();
                iKeyRegistered = XNetRegisterKey(&SessionID, &KeyExchangeKey);
            }
            m_bKeyRegistered = (iKeyRegistered == NO_ERROR);

            Listen(TRUE);

            if (m_bUpdate)
                hr = Update();
        }
        break;
    default:
        Close();
        m_State = STATE_5;
        break;
    }
    return hr;
}
// match: ?ProcessStateUpdateSession@CSession@@QAEJXZ @ 0x001DCB00
HRESULT CSession::ProcessStateUpdateSession()
{
    HRESULT hr = XOnlineTaskContinue(m_hSessionTask);

    if (hr != XONLINETASK_S_RUNNING)
    {
        if (FAILED(hr))
        {
            Close();
        }
        else
        {
            m_State = STATE_ACTIVE;
            if (m_bUpdate)
                hr = Update();
        }
    }
    return hr;
}
// match: ?ProcessStateDeleteSession@CSession@@QAEJXZ @ 0x001DCB60
HRESULT CSession::ProcessStateDeleteSession()
{
    HRESULT hr = XOnlineTaskContinue(m_hSessionTask);

    if (hr != XONLINETASK_S_RUNNING)
    {
        if (FAILED(hr))
        {
        }
        Close();
    }
    return hr;
}
// match: ?ProcessStateActiveSession@CSession@@QAEJXZ @ 0x001DCB90
HRESULT CSession::ProcessStateActiveSession()
{
    HRESULT hr = XOnlineTaskContinue(m_hSessionTask);

    if (FAILED(hr))
        Close();
    return hr;
}
// match: ?Process@CSession@@QAEJXZ @ 0x001DCBC0
HRESULT CSession::Process()
{
    PurgeSessionQ();
    HRESULT hr;

    switch (m_State)
    {
    case STATE_5:
        hr = XONLINE_E_NO_SESSION;
        break;
    case STATE_IDLE:
        hr = XONLINETASK_S_SUCCESS;
        break;
    case STATE_CREATING:
        hr = ProcessStateCreateSession();
        break;
    case STATE_UPDATING:
        hr = ProcessStateUpdateSession();
        break;
    case STATE_DELETING:
        hr = ProcessStateDeleteSession();
        break;
    case STATE_ACTIVE:
        hr = ProcessStateActiveSession();
        break;
    default:
        return E_UNEXPECTED;
    }

    if (FAILED(hr))
        Reset();
    return hr;
}
// match: ?Close@CSession@@QAEXXZ @ 0x001DCC70
void CSession::Close()
{
    if (m_hSessionTask)
    {
        XOnlineTaskClose(m_hSessionTask);
        m_hSessionTask = NULL;
        m_State = STATE_IDLE;
    }
    m_bUpdate = FALSE;
}
// match: ?PurgeSessionQ@CSession@@QAEXH@Z @ 0x001DCCC0
void CSession::PurgeSessionQ(BOOL fRemoveAll)
{
    const DWORD QOS_PROBE_REJECT_TIMELIMIT = 15000;

    const QosQEntry *pItem;
    while ((pItem = m_SessionQosQ.Head()) != NULL)
    {
        if (fRemoveAll || GetTickCount() - pItem->dwStartTick >= QOS_PROBE_REJECT_TIMELIMIT)
            PurgeSessionQHead();
        else
            break;
    }
}
// match: ?PurgeSessionQHead@CSession@@QAEXXZ @ 0x001DCD10
void CSession::PurgeSessionQHead()
{
    const QosQEntry *pItem;
    if ((pItem = m_SessionQosQ.Head()) != NULL)
    {
        INT iQos = XNetQosListen(&pItem->SessionID, NULL, 0, 0, XNET_QOS_LISTEN_RELEASE);
        if (!m_bKeyRegistered || memcmp(&pItem->SessionID, &SessionID, sizeof(XNKID)) != 0)
        {
            INT iResult = XNetUnregisterKey(&pItem->SessionID);
        }
        m_SessionQosQ.Dequeue();
    }
}
// match: ?Listen@CSession@@QAEXHK@Z @ 0x001DCD90
void CSession::Listen(BOOL bEnable, DWORD dwBitsPerSec)
{
    if (bEnable)
    {
        m_SessionQosQ.Remove(SessionID);
        INT iQos = XNetQosListen(&SessionID, (BYTE *)m_QosResponse.Data, m_QosResponse.Length, dwBitsPerSec,
                                 XNET_QOS_LISTEN_ENABLE | XNET_QOS_LISTEN_SET_DATA | XNET_QOS_LISTEN_SET_BITSPERSEC);
        m_bListening = TRUE;
    }
    else
    {
        if (m_bListening)
        {
            INT iQos;
            m_bListening = FALSE;
            if (dwBitsPerSec == NO_WAIT)
            {
                iQos = XNetQosListen(&SessionID, NULL, 0, 0, XNET_QOS_LISTEN_RELEASE);
            }
            else
            {
                m_SessionQosQ.Add(SessionID, GetTickCount());
                iQos = XNetQosListen(&SessionID, NULL, 0, dwBitsPerSec,
                                     XNET_QOS_LISTEN_DISABLE | XNET_QOS_LISTEN_SET_BITSPERSEC);
            }
        }
    }
}
// match: ?SetupAttributes@CSession@@QAEXXZ @ 0x001DCE70
void CSession::SetupAttributes()
{
    ZeroMemory(&m_Attributes, sizeof(m_Attributes));
    m_Attributes[0].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 1;
    m_Attributes[1].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 2;
    m_Attributes[2].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 3;
    m_Attributes[3].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 4;
    m_Attributes[4].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 5;
    m_Attributes[5].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 6;
    m_Attributes[6].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 7;
    m_Attributes[7].dwAttributeID = X_ATTRIBUTE_DATATYPE_INTEGER | 8;
    m_Attributes[8].dwAttributeID = X_ATTRIBUTE_DATATYPE_STRING | 9;
    m_Attributes[8].info.string.lpValue = m_strName;
    m_strName[0] = L'\0';
}
// match: ?sub_1DCF20@CSession@@QAE_KXZ @ 0x001DCF20
ULONGLONG CSession::sub_1DCF20()
{
    return m_Attributes[0].info.integer.qwValue;
}
// match: ?sub_1DCF40@CSession@@QAEX_K@Z @ 0x001DCF40
void CSession::sub_1DCF40(ULONGLONG arg_0)
{
    m_Attributes[0].info.integer.qwValue = arg_0;
    m_Attributes[0].fChanged = TRUE;
}
// match: ?sub_1DCF70@CSession@@QAE_KXZ @ 0x001DCF70
ULONGLONG CSession::sub_1DCF70()
{
    return m_Attributes[1].info.integer.qwValue;
}
// match: ?sub_1DCF90@CSession@@QAEX_K@Z @ 0x001DCF90
void CSession::sub_1DCF90(ULONGLONG arg_0)
{
    m_Attributes[1].info.integer.qwValue = arg_0;
    m_Attributes[1].fChanged = TRUE;
}
// match: ?sub_1DCFC0@CSession@@QAE_KXZ @ 0x001DCFC0
ULONGLONG CSession::sub_1DCFC0()
{
    return m_Attributes[2].info.integer.qwValue;
}
// match: ?sub_1DCFE0@CSession@@QAEX_K@Z @ 0x001DCFE0
void CSession::sub_1DCFE0(ULONGLONG arg_0)
{
    m_Attributes[2].info.integer.qwValue = arg_0;
    m_Attributes[2].fChanged = TRUE;
}
// match: ?sub_1DD010@CSession@@QAE_KXZ @ 0x001DD010
ULONGLONG CSession::sub_1DD010()
{
    return m_Attributes[3].info.integer.qwValue;
}
// match: ?sub_1DD030@CSession@@QAEX_K@Z @ 0x001DD030
void CSession::sub_1DD030(ULONGLONG arg_0)
{
    m_Attributes[3].info.integer.qwValue = arg_0;
    m_Attributes[3].fChanged = TRUE;
}
// match: ?sub_1DD060@CSession@@QAE_KXZ @ 0x001DD060
ULONGLONG CSession::sub_1DD060()
{
    return m_Attributes[4].info.integer.qwValue;
}
// match: ?sub_1DD080@CSession@@QAEX_K@Z @ 0x001DD080
void CSession::sub_1DD080(ULONGLONG arg_0)
{
    m_Attributes[4].info.integer.qwValue = arg_0;
    m_Attributes[4].fChanged = TRUE;
}
// match: ?sub_1DD0B0@CSession@@QAEX_K@Z @ 0x001DD0B0
void CSession::sub_1DD0B0(ULONGLONG arg_0)
{
    m_Attributes[5].info.integer.qwValue = arg_0;
    m_Attributes[5].fChanged = TRUE;
}
// match: ?sub_1DD0E0@CSession@@QAEX_K@Z @ 0x001DD0E0
void CSession::sub_1DD0E0(ULONGLONG arg_0)
{
    m_Attributes[6].info.integer.qwValue = arg_0;
    m_Attributes[6].fChanged = TRUE;
}
// match: ?sub_1DD110@CSession@@QAE_KXZ @ 0x001DD110
ULONGLONG CSession::sub_1DD110()
{
    return m_Attributes[7].info.integer.qwValue;
}
// match: ?sub_1DD130@CSession@@QAEX_K@Z @ 0x001DD130
void CSession::sub_1DD130(ULONGLONG arg_0)
{
    m_Attributes[7].info.integer.qwValue = arg_0;
    m_Attributes[7].fChanged = TRUE;
}
// match: ?SetName@CSession@@QAEXPBG@Z @ 0x001DD160
void CSession::SetName(const WCHAR *Value)
{
    wcscpy(m_strName, Value);
    m_Attributes[8].fChanged = TRUE;
}
// match: ??0CSessionQosQ@CSession@@QAE@XZ @ 0x001DD190
CSession::CSessionQosQ::CSessionQosQ()
{
    m_pHead = m_pTail = NULL;
}
// match: ?Add@CSessionQosQ@CSession@@QAEXAAUXNKID@@K@Z @ 0x001DD1C0
void CSession::CSessionQosQ::Add(XNKID &SessionID, DWORD dwStartTick)
{
    QosQEntry *pItem = new QosQEntry;
    pItem->SessionID = SessionID;
    pItem->dwStartTick = dwStartTick;
    pItem->pNext = NULL;
    if (m_pTail)
        m_pTail->pNext = pItem;
    m_pTail = pItem;
    if (!m_pHead)
        m_pHead = pItem;
}
// match: ?Remove@CSessionQosQ@CSession@@QAEXAAUXNKID@@@Z @ 0x001DD240
void CSession::CSessionQosQ::Remove(XNKID &SessionID)
{
    QosQEntry *pPrev = NULL;

    for (QosQEntry *pItem = m_pHead; pItem != NULL; pItem = pItem->pNext)
    {
        if (memcmp(&pItem->SessionID, &SessionID, sizeof(XNKID)) == 0)
        {
            if (pPrev)
                pPrev->pNext = pItem->pNext;
            else
                m_pHead = pItem->pNext;
            if (pItem == m_pTail)
                m_pTail = pPrev;
            delete pItem;
            break;
        }
        pPrev = pItem;
    }
}
// match: ?Dequeue@CSessionQosQ@CSession@@QAEXXZ @ 0x001DD2E0
void CSession::CSessionQosQ::Dequeue()
{
    QosQEntry *pItem = m_pHead;
    if (pItem)
    {
        m_pHead = pItem->pNext;
        delete pItem;
        if (!m_pHead)
            m_pTail = NULL;
    }
}
// The search's result attributes (at 0x3E6680): five integers, then the
// host's name (17 characters and the terminator).
static const XONLINE_ATTRIBUTE_SPEC QuickmatchAttributeSpec[] =
{
    { X_ATTRIBUTE_DATATYPE_INTEGER, sizeof(ULONGLONG) },
    { X_ATTRIBUTE_DATATYPE_INTEGER, sizeof(ULONGLONG) },
    { X_ATTRIBUTE_DATATYPE_INTEGER, sizeof(ULONGLONG) },
    { X_ATTRIBUTE_DATATYPE_INTEGER, sizeof(ULONGLONG) },
    { X_ATTRIBUTE_DATATYPE_INTEGER, sizeof(ULONGLONG) },
    { X_ATTRIBUTE_DATATYPE_STRING, 17 * sizeof(WCHAR) },
};

// CQuickmatchQuery: the MatchSim sample's (match.cpp).
// match: ??0CQuickmatchQuery@@QAE@XZ @ 0x001DD330
CQuickmatchQuery::CQuickmatchQuery()
{
    m_State = STATE_IDLE;
    m_hrQuery = S_FALSE;
    m_hSearchTask = NULL;
    m_pXnQos = NULL;
}
// match: ??1CQuickmatchQuery@@QAE@XZ @ 0x001DD380
CQuickmatchQuery::~CQuickmatchQuery()
{
    Cancel();
}
// match: ?Cancel@CQuickmatchQuery@@QAEXXZ @ 0x001DD3A0
void CQuickmatchQuery::Cancel()
{
    switch (m_State)
    {
    case STATE_IDLE:
        break;
    case STATE_RUNNING:
    case STATE_PROBING_BANDWIDTH:
    case STATE_PROBING_CONNECTIVITY:
    case STATE_DONE:
        if (m_hSearchTask)
        {
            XOnlineTaskClose(m_hSearchTask);
            m_hSearchTask = NULL;
        }
        Clear();
        m_State = STATE_IDLE;
        m_hrQuery = S_FALSE;
        break;
    }
}
// match: ?Clear@CQuickmatchQuery@@QAEXXZ @ 0x001DD420
void CQuickmatchQuery::Clear()
{
    if (m_pXnQos)
    {
        XNetQosRelease(m_pXnQos);
        m_pXnQos = NULL;
    }
    Results.Clear();
}
// An integer query argument left out (the MatchSim sample's match.h).
const ULONGLONG X_MATCH_NULL_INTEGER = 0x7FFFFFFFFFFFFFFFui64;
// match: ?Query@CQuickmatchQuery@@QAEJ_K0000000@Z @ 0x001DD460
HRESULT CQuickmatchQuery::Query(ULONGLONG arg_0, ULONGLONG arg_8, ULONGLONG arg_10, ULONGLONG arg_18, ULONGLONG arg_20,
                                ULONGLONG arg_28, ULONGLONG arg_30, ULONGLONG arg_38)
{
    const DWORD SEARCH_PROC_ID = 0x1;

    if (m_State == STATE_DONE)
    {
        Clear();
        m_State = STATE_IDLE;
    }
    if (m_State != STATE_IDLE)
        return E_UNEXPECTED;

    XONLINE_ATTRIBUTE QueryAttributes[8] = {0};

    QueryAttributes[0].dwAttributeID = arg_0 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[0].info.integer.qwValue = arg_0;
    QueryAttributes[1].dwAttributeID = arg_8 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[1].info.integer.qwValue = arg_8;
    QueryAttributes[2].dwAttributeID = arg_10 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[2].info.integer.qwValue = arg_10;
    QueryAttributes[3].dwAttributeID = arg_18 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[3].info.integer.qwValue = arg_18;
    QueryAttributes[4].dwAttributeID = arg_20 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[4].info.integer.qwValue = arg_20;
    QueryAttributes[5].dwAttributeID = arg_28 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[5].info.integer.qwValue = arg_28;
    QueryAttributes[6].dwAttributeID = arg_30 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[6].info.integer.qwValue = arg_30;
    QueryAttributes[7].dwAttributeID = arg_38 == X_MATCH_NULL_INTEGER ? X_ATTRIBUTE_DATATYPE_NULL : X_ATTRIBUTE_DATATYPE_INTEGER;
    QueryAttributes[7].info.integer.qwValue = arg_38;

    DWORD dwResultsLen = XOnlineMatchSearchResultsLen(25, sizeof(QuickmatchAttributeSpec) / sizeof(QuickmatchAttributeSpec[0]),
                                                      QuickmatchAttributeSpec);

    HRESULT hr = XOnlineMatchSearch(SEARCH_PROC_ID, 25, 8, QueryAttributes, dwResultsLen, NULL, &m_hSearchTask);
    if (SUCCEEDED(hr))
        m_State = STATE_RUNNING;
    return hr;
}
// match: ?Process@CQuickmatchQuery@@QAEJXZ @ 0x001DD710
HRESULT CQuickmatchQuery::Process()
{
    if (m_State == STATE_IDLE)
        return S_OK;

    if (m_State == STATE_DONE)
        return m_hrQuery;

    if (m_State == STATE_PROBING_BANDWIDTH)
    {
        for (DWORD iResult = 0; iResult < Results.Size(); ++iResult)
        {
            if (!Results[iResult].unk_96 && (m_pXnQos->axnqosinfo[iResult].bFlags & XNET_XNQOSINFO_COMPLETE))
                Results[iResult].unk_96 = &m_pXnQos->axnqosinfo[iResult];
        }

        if (m_pXnQos->cxnqosPending == 0)
        {
            m_State = STATE_DONE;
            return m_hrQuery;
        }
        return XONLINETASK_S_RUNNING;
    }

    if (m_State == STATE_PROBING_CONNECTIVITY)
    {
        if (m_pXnQos->cxnqosPending == 0)
        {
            DWORD dwNumQosResults = Results.Size();
            DWORD iResult = 0;
            for (DWORD iQos = 0; iQos < dwNumQosResults; ++iQos)
            {
                if ((m_pXnQos->axnqosinfo[iQos].bFlags & XNET_XNQOSINFO_TARGET_CONTACTED) &&
                    !(m_pXnQos->axnqosinfo[iQos].bFlags & XNET_XNQOSINFO_TARGET_DISABLED))
                {
                    Results[iResult].unk_96 = &m_pXnQos->axnqosinfo[iQos];
                    iResult++;
                }
                else
                {
                    Results.Remove(iResult);
                }
            }
            m_State = STATE_DONE;
            return m_hrQuery;
        }
        return XONLINETASK_S_RUNNING;
    }

    HRESULT hr = XOnlineTaskContinue(m_hSearchTask);
    if (hr != XONLINETASK_S_RUNNING)
    {
        m_hrQuery = hr;
        m_State = STATE_DONE;
        if (SUCCEEDED(hr))
        {
            XONLINE_MATCH_SEARCHRESULT **ppSearchResults;
            DWORD dwNumSessions;
            hr = XOnlineMatchSearchGetResults(m_hSearchTask, &ppSearchResults, &dwNumSessions);
            if (SUCCEEDED(hr))
            {
                Results.SetSize(dwNumSessions);
                for (DWORD i = 0; i < dwNumSessions; ++i)
                {
                    XONLINE_MATCH_SEARCHRESULT *pxms = ppSearchResults[i];

                    Results.v[i].unk_4A = pxms->SessionID;
                    Results.v[i].unk_52 = pxms->KeyExchangeKey;
                    Results.v[i].unk_62 = pxms->HostAddress;
                    Results.v[i].unk_86 = pxms->dwPublicOpen;
                    Results.v[i].unk_8A = pxms->dwPrivateOpen;
                    Results.v[i].unk_8E = pxms->dwPublicFilled;
                    Results.v[i].unk_92 = pxms->dwPrivateFilled;
                    hr = XOnlineMatchSearchParse(ppSearchResults[i],
                                                 sizeof(QuickmatchAttributeSpec) / sizeof(QuickmatchAttributeSpec[0]),
                                                 QuickmatchAttributeSpec, &Results.v[i]);
                    Results.v[i].unk_96 = NULL;
                    m_rgpXnAddr[i] = &Results.v[i].unk_62;
                    m_rgpXnKid[i] = &Results.v[i].unk_4A;
                    m_rgpXnKey[i] = &Results.v[i].unk_52;
                }
                if (dwNumSessions)
                {
                    INT iQos = XNetQosLookup(dwNumSessions, m_rgpXnAddr, m_rgpXnKid, m_rgpXnKey, 0, NULL, NULL, 0, 64000, 0,
                                             NULL, &m_pXnQos);
                    if (iQos == 0)
                        m_State = STATE_PROBING_CONNECTIVITY;
                }
            }
        }

        XOnlineTaskClose(m_hSearchTask);
        m_hSearchTask = NULL;
    }
    return hr;
}
// match: ?Remove@CQuickmatchQueryResults@@QAEXK@Z @ 0x001DDB70
void CQuickmatchQueryResults::Remove(DWORD i)
{
    if (i < m_dwSize)
    {
        m_dwSize--;
        memcpy(&v[i], &v[i + 1], sizeof(v[0]) * (m_dwSize - i));
    }
}
