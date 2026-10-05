/*
 * The Alfa object manager's state (unit_071360): the pools of the objects
 * scripts run on, named from the strings its set-up sub_713E0 passes, and
 * the global script registers. Each declaration gives the pool's name.
 */
#ifndef ALFAOBJMAN_H
#define ALFAOBJMAN_H

#include "rw/ostypes.h"
#include "types/alfasched.h"

extern type_16C2A0 dword_449A50;    // m_pobjectPool (type_3D2CD0)
extern type_16C2A0 dword_449A10;    // m_aiObjectPool (type_3D2E7C)
extern type_16C2A0 dword_449A30;    // m_stateMachineObjectPool (type_3D2DB8)
extern type_16C2A0 dword_4499F0;    // m_taskObjectPool (type_3D2E20)
extern type_16C2A0 dword_4499D0;    // m_taskTreeDataPool (type_3D2E20_114)
extern type_16C2A0 dword_4499B0;    // m_inputListPool (type_3D2E20_118)
extern type_16C2A0 dword_449950[3]; // m_memPools: scripts' locals by size

// A global script register (101 of them; sub_71DB0 and sub_71E40): two
// words and a third.
struct type_449408
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
extern type_449408 dword_449408[101];

extern RwInt32 dword_4498C4;        // 1 after set-up and restarts
extern RwInt32 dword_449404;        // the next interrupt id
extern RwInt32 dword_4498C8;        // the task pool's size (125)
extern RwReal dword_449400;         // call records per task (3)

void sub_715E0();

#endif
