/*
 * codfh-match: RAD's background callbacks (the library's radcb.obj): handler
 * threads that call their registered callbacks in priority order, and the
 * suspend, resume, free and unregister calls Bink's player uses for its IO
 * and sound callbacks.
 */
#include "bink.h"
#include "binkint.h"

// RAD puts all of Bink's code in its BINK section (the image's 0x341480-0x34E01C).
#pragma code_seg("BINK")

RADEXPFUNC void RADEXPLINK RADCB_suspend_2_handlers(U32 handle1, U32 handle2);
RADEXPFUNC void RADEXPLINK RADCB_free_handler(U32 handle);
RADEXPFUNC void RADEXPLINK RADCB_free_2_handlers(U32 handle1, U32 handle2);

static S32 remove_cb_from_list(RADCBHANDLER *h, RADCBNODE *n)
{
  RADCBNODE *c;

  if (h == 0)
    return 0;

  c = h->list;
  if (c == n)
  {
    h->list = c->next;
    return 1;
  }

  while (c->next)
  {
    if (c->next == n)
    {
      c->next = n->next;
      return 1;
    }
    c = c->next;
  }
  return 0;
}

static void add_sorted(RADCBNODE **head, RADCBNODE *n)
{
  RADCBNODE *c;

  if (*head == 0)
  {
    n->sorted = *head;
    *head = n;
    return;
  }
  if (n->priority >= (*head)->priority)
  {
    n->sorted = *head;
    *head = n;
    return;
  }

  c = *head;

  while (c->sorted)
  {
    if (n->priority >= c->sorted->priority)
    {
      n->sorted = c->sorted;
      c->sorted = n;
      return;
    }
    c = c->sorted;
  }

  n->sorted = 0;
  c->sorted = n;
}

// match: _my_wait_for_2 @ 0x00344160
static void my_wait_for_2(HANDLE a, HANDLE b)
{
  HANDLE h[2];

  if (a == 0)
  {
    if (b)
      WaitForSingleObject(b, INFINITE);
    return;
  }
  if (b == 0)
  {
    WaitForSingleObject(a, INFINITE);
    return;
  }

  h[0] = a;
  h[1] = b;
  switch (WaitForMultipleObjects(2, h, 0, INFINITE))
  {
    case 0:
      WaitForSingleObject(b, INFINITE);
      break;
    case 1:
      WaitForSingleObject(a, INFINITE);
      break;
  }
}

// match: _call_callbacks @ 0x003441B0
static void call_callbacks(RADCBHANDLER *h)
{
  HANDLE mutexes[16];
  RADCBNODE *nodes[16];
  RADCBNODE *n;
  RADCBNODE *sorted;
  U32 count;
  U32 which;

  h->count++;
  for (;;)
  {
    sorted = 0;
    for (n = h->list; n; n = n->next)
    {
      if (h->state != 1)
        return;
      n->priority = n->getpriority(n, h->count);
      if (n->priority)
        add_sorted(&sorted, n);
    }

    count = 0;
    for (n = sorted; n; n = n->sorted)
    {
      if (count >= 16)
        break;
      mutexes[count] = n->mutex;
      nodes[count] = n;
      count++;
    }
    if (count == 0)
      return;

    which = WaitForMultipleObjects(count, mutexes, 0, 0);
    if (which < count)
    {
      nodes[which]->callback(nodes[which], h->count);
      ReleaseMutex(mutexes[which]);
    }
  }
}

// match: _RAD_callback_thread@4 @ 0x003442B0
static U32 __stdcall RAD_callback_thread(void *param)
{
  RADCBHANDLER *h = (RADCBHANDLER *)param;

  while (WaitForSingleObject(h->event, h->waitms))
  {
    WaitForSingleObject(h->mutex, INFINITE);
    switch (h->state)
    {
      case 1:
        if (h->list)
          call_callbacks(h);
        break;
      case 3:
        ReleaseMutex(h->mutex);
        return 0;
    }
    ReleaseMutex(h->mutex);
  }
  return 0;
}

// match: _RADCB_allocate_handler@4 @ 0x00344320
RADEXPFUNC U32 RADEXPLINK RADCB_allocate_handler(S32 rate)
{
  RADCBHANDLER *h = (RADCBHANDLER *)radmalloc(sizeof(RADCBHANDLER));

  if (h)
  {
    S32 lower;

    if (rate < 0)
    {
      rate = -rate;
      lower = 1;
    }
    else
      lower = 0;

    h->state = 0;
    h->list = 0;
    h->count = 1;
    h->registered = 0;
    h->waitms = 1000 / rate;
    h->thread = CreateThread(0, 0x3000, RAD_callback_thread, h, 4, &h->threadid);
    if (lower)
      SetThreadPriority(h->thread, -1);

    if (h->thread == 0)
    {
      radfree(h);
      return 0;
    }

    h->mutex = CreateMutexA(0, 0, 0);
    h->event = CreateEventA(0, 0, 0, 0);
    return (U32)h;
  }
  return 0;
}

// match: _RADCB_register_callback@16 @ 0x003443D0
RADEXPFUNC void RADEXPLINK RADCB_register_callback(U32 handle, void PTR4 *data,
  S32 (RADLINK *priority)(void *data, U32 count), void (RADLINK *callback)(void *data, U32 count))
{
  RADCBHANDLER *h = (RADCBHANDLER *)handle;
  RADCBNODE *n = (RADCBNODE *)data;

  n->getpriority = priority;
  n->callback = callback;
  n->mutex = CreateMutexA(0, 0, 0);
  n->next = h->list;
  h->list = n;
  h->registered++;
}

// match: _request_free @ 0x00344410
static void request_free(RADCBHANDLER *h)
{
  S32 old = h->state;

  SetEvent(h->event);
  h->state = 3;
  SetThreadPriority(h->thread, 15);
  switch (old)
  {
    case 0:
      ResumeThread(h->thread);
      break;
    case 2:
      ReleaseMutex(h->mutex);
      break;
  }
}

// match: _do_free @ 0x00344450
static void do_free(RADCBHANDLER *h)
{
  CloseHandle(h->mutex);
  CloseHandle(h->thread);
  CloseHandle(h->event);
  radfree(h);
}

// match: _RADCB_suspend_2_handlers@8 @ 0x00344480
RADEXPFUNC void RADEXPLINK RADCB_suspend_2_handlers(U32 handle1, U32 handle2)
{
  RADCBHANDLER *h1 = (RADCBHANDLER *)handle1;
  RADCBHANDLER *h2 = (RADCBHANDLER *)handle2;

  if ((h1) && (h2))
  {
    h1->state = 4;
    h2->state = 4;
    my_wait_for_2(h1->mutex, h2->mutex);
    h1->state = 2;
    h2->state = 2;
  }
  else if (h1)
  {
    h1->state = 4;
    WaitForSingleObject(h1->mutex, INFINITE);
    h1->state = 2;
  }
  else if (h2)
  {
    h2->state = 4;
    WaitForSingleObject(h2->mutex, INFINITE);
    h2->state = 2;
  }
}

// match: _RADCB_resume_handler@4 @ 0x00344500
RADEXPFUNC void RADEXPLINK RADCB_resume_handler(U32 handle)
{
  RADCBHANDLER *h = (RADCBHANDLER *)handle;

  if (h->state == 0)
  {
    h->state = 1;
    ResumeThread(h->thread);
  }
  else
  {
    h->state = 1;
    ReleaseMutex(h->mutex);
  }
}

// match: _RADCB_free_handler@4 @ 0x00344530
RADEXPFUNC void RADEXPLINK RADCB_free_handler(U32 handle)
{
  RADCBHANDLER *h = (RADCBHANDLER *)handle;

  request_free(h);
  WaitForSingleObject(h->thread, INFINITE);
  do_free(h);
}

// match: _RADCB_try_to_suspend_callback@8 @ 0x003445B0
RADEXPFUNC S32 RADEXPLINK RADCB_try_to_suspend_callback(U32 handle, void PTR4 *data)
{
  RADCBNODE *n = (RADCBNODE *)data;

  if ((n) && (n->mutex))
    return WaitForSingleObject(n->mutex, 0) == 0;
  return 1;
}

// match: _RADCB_suspend_callback@8 @ 0x003445E0
RADEXPFUNC void RADEXPLINK RADCB_suspend_callback(U32 handle, void PTR4 *data)
{
  RADCBNODE *n = (RADCBNODE *)data;

  if ((n) && (n->mutex))
    WaitForSingleObject(n->mutex, INFINITE);
}

// match: _RADCB_suspend_2_callbacks@16 @ 0x00344610
RADEXPFUNC void RADEXPLINK RADCB_suspend_2_callbacks(U32 handle1, void PTR4 *data1, U32 handle2,
  void PTR4 *data2)
{
  my_wait_for_2(((RADCBNODE *)data1)->mutex, ((RADCBNODE *)data2)->mutex);
}

// match: _RADCB_resume_callback@8 @ 0x00344670
RADEXPFUNC void RADEXPLINK RADCB_resume_callback(U32 handle, void PTR4 *data)
{
  RADCBNODE *n = (RADCBNODE *)data;

  if ((n) && (n->mutex))
    ReleaseMutex(n->mutex);
}

// match: _RADCB_free_2_handlers@8 @ 0x00344690
RADEXPFUNC void RADEXPLINK RADCB_free_2_handlers(U32 handle1, U32 handle2)
{
  RADCBHANDLER *h1 = (RADCBHANDLER *)handle1;
  RADCBHANDLER *h2 = (RADCBHANDLER *)handle2;

  if (h1 == 0)
  {
    if (h2)
      RADCB_free_handler(handle2);
    return;
  }
  if (h2 == 0)
  {
    RADCB_free_handler(handle1);
    return;
  }

  request_free(h1);
  request_free(h2);
  my_wait_for_2(h1->thread, h2->thread);
  do_free(h1);
  do_free(h2);
}

// match: _RADCB_idle_on_callbacks@0 @ 0x00344730
RADEXPFUNC void RADEXPLINK RADCB_idle_on_callbacks(void)
{
  Sleep(0);
}

// match: _do_unregister @ 0x00344740
static S32 do_unregister(RADCBHANDLER *h, RADCBNODE *n, S32 wait)
{
  S32 ret;

  h->registered--;
  if ((wait & 1) && (h->list == 0))
  {
    RADCB_free_handler((U32)h);
    ret = 1;
  }
  else
  {
    h->state = 4;
    WaitForSingleObject(h->mutex, INFINITE);
    h->state = 1;
    ReleaseMutex(h->mutex);
    ret = 0;
  }

  CloseHandle(n->mutex);
  n->mutex = 0;
  return ret;
}

// match: _RADCB_unregister_2_callbacks@20 @ 0x003447B0
RADEXPFUNC S32 RADEXPLINK RADCB_unregister_2_callbacks(U32 handle1, void PTR4 *data1, U32 handle2,
  void PTR4 *data2, S32 wait)
{
  RADCBHANDLER *h1 = (RADCBHANDLER *)handle1;
  RADCBHANDLER *h2 = (RADCBHANDLER *)handle2;
  RADCBNODE *n1 = (RADCBNODE *)data1;
  RADCBNODE *n2 = (RADCBNODE *)data2;
  S32 which = 0;
  S32 ret;

  if (remove_cb_from_list(h1, n1))
    which = 1;
  if (remove_cb_from_list(h2, n2))
    which |= 2;

  switch (which)
  {
    case 1:
      return do_unregister(h1, n1, wait);
    case 2:
      return do_unregister(h2, n2, wait) << 1;
    case 3:
      break;
    default:
      return 0;
  }

  h1->registered--;
  h2->registered--;

  if (wait & 1)
  {
    if (h1->list == 0)
    {
      if (h2->list == 0)
      {
        RADCB_free_2_handlers(handle1, handle2);
        ret = 3;
      }
      else
      {
        request_free(h1);
        h2->state = 4;
        my_wait_for_2(h1->thread, h2->mutex);
        do_free(h1);
        h2->state = 2;
        RADCB_resume_handler(handle2);
        ret = 1;
      }
      goto close;
    }
    if (h2->list == 0)
    {
      request_free(h2);
      h1->state = 4;
      my_wait_for_2(h2->thread, h1->mutex);
      do_free(h2);
      h1->state = 2;
      RADCB_resume_handler(handle1);
      ret = 2;
      goto close;
    }
  }

  RADCB_suspend_2_handlers(handle1, handle2);
  RADCB_resume_handler(handle1);
  RADCB_resume_handler(handle2);
  ret = 0;

 close:
  CloseHandle(n1->mutex);
  CloseHandle(n2->mutex);
  n1->mutex = 0;
  n2->mutex = 0;
  return ret;
}
