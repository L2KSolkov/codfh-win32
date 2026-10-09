/*
 * The mouse in the menus (kujuUI): pointing at an item focuses it, the left button chooses it (A),
 * the right goes back (B) and the wheel moves up and down (the d-pad). The window gives the
 * cursor's position and the buttons from its messages (winmain.cpp); each frame of the menus' loop
 * (port_cli_frame) maps the cursor into the game's 640x480 frame, finds the widget of the page
 * that has the focus under it and gives it the focus as the page's own navigation does
 * (cLayoutPage::sub_1E8B50); the buttons reach the game as the pad's (xpal_sys.cpp's
 * menu_mouse_state, read with the controllers), each held a few frames so the menus read a press.
 */
#include <xtl.h>
#include <string.h>

#ifndef CODFH_SP
#include "game/kujuui.h"
#endif

#include "port.h"
#include "d3d/pdev.h"

/* the window's, from its messages (port_menu_mouse_pressed: left-button presses not yet looked
   at; port_menu_mouse_clicks: the ones on an item, for the pad's A) */
extern "C" volatile LONG port_menu_mouse_x, port_menu_mouse_y, port_menu_mouse_moved, port_menu_mouse_pressed;
extern "C" volatile LONG port_menu_mouse_clicks, port_menu_mouse_backs, port_menu_mouse_wheel;
extern "C" volatile LONG port_menu_mouse_lefts, port_menu_mouse_rights;
volatile LONG port_menu_mouse_x, port_menu_mouse_y, port_menu_mouse_moved, port_menu_mouse_pressed;
volatile LONG port_menu_mouse_clicks, port_menu_mouse_backs, port_menu_mouse_wheel;
volatile LONG port_menu_mouse_lefts, port_menu_mouse_rights;

/* the frame the menus' loop last ran (the window shows the cursor in the menus) */
extern "C" unsigned port_menu_frame;
unsigned port_menu_frame;

extern "C" int port_in_menus(void)
{
    return port_menu_frame && port_frame - port_menu_frame <= 2;
}

#ifndef CODFH_SP
/* cLayoutPage's vtable (unit_1E8350), to tell a page among the widgets without RTTI: the menus'
   pages are its subclasses (cTopLayoutPage and the menus' own), which keep its slot 13 (vf_034,
   whether a widget is the focused one) */
extern "C" const void *port_cLayoutPage_vftable[];
#pragma comment(linker, "/alternatename:_port_cLayoutPage_vftable=??_7cLayoutPage@kujuUI@@6B@")

static kujuUI::cLayoutPage *as_page(kujuUI::type_3E7D08 *w)
{
    if (!w)
        return NULL;
    const void *const *vt = *(const void *const *const *)w;
    return vt && vt[13] == port_cLayoutPage_vftable[13] ? (kujuUI::cLayoutPage *)w : NULL;
}

/* The page that has the focus: the focus stack's top, or a focused page among its children. */
static kujuUI::cLayoutPage *focused_page(kujuUI::type_3E7D08 *w, int depth)
{
    if (!w || depth > 4)
        return NULL;
    if (kujuUI::cLayoutPage *p = as_page(w))
        return p;
    return NULL;
}

/* The page's widget under (x, y) that can take the focus: the one the point is in, else the one
   whose row it is in (a setting's label is beside its value, the widget; a thin item's row is
   taken 8 pixels taller each way), the nearest when rows overlap. *exact: the point is in it. */
static kujuUI::type_3E7D08 *widget_at(kujuUI::cLayoutPage *page, float x, float y, kujuUI::type_1E0330_rect *rect,
                                      int *exact)
{
    kujuUI::type_3E7D08 *row = NULL;
    float best = 1e9f;
    kujuUI::type_1E0330_rect row_rect;
    for (std::vector<kujuUI::type_3E7D08 *>::iterator it = page->unk_0C.begin(); it != page->unk_0C.end(); ++it)
    {
        kujuUI::type_3E7D08 *w = *it;
        if (!w || !w->vf_010())
            continue;
        kujuUI::type_1E0330_rect r = w->vf_020();
        if (x >= r.unk_00 && x < r.unk_08 && y >= r.unk_04 && y < r.unk_0C)
        {
            *rect = r;
            *exact = 1;
            return w;
        }
        float cy = (r.unk_04 + r.unk_0C) / 2, d = y > cy ? y - cy : cy - y;
        if (y >= r.unk_04 - 8 && y < r.unk_0C + 8 && d < best)
        {
            best = d;
            row = w;
            row_rect = r;
        }
    }
    if (row)
        *rect = row_rect;
    *exact = 0;
    return row;
}

/* Run once a frame by the menus' loop. */
extern "C" void port_menu_mouse_frame(void)
{
    LONG pressed = InterlockedExchange(&port_menu_mouse_pressed, 0);
    if (!InterlockedExchange(&port_menu_mouse_moved, 0) && !pressed)
        return;
    float fx, fy;
    if (!pdev_window_to_frame((int)port_menu_mouse_x, (int)port_menu_mouse_y, &fx, &fy))
        return;
    kujuUI::type_1E7CF0 *stack = kujuUI::sub_1E7CF0();
    kujuUI::type_3E7D08 *top = stack ? stack->sub_1E7FE0() : NULL;
    static const void *told_top;
    if (top && *(const void *const *)top != told_top)
    {
        told_top = *(const void *const *)top;
        plog("menu mouse: the focus stack's top is %p (vtable %p%s)", top, told_top,
             as_page(top) ? ", a layout page" : ", not a layout page");
    }
    kujuUI::cLayoutPage *page = focused_page(top, 0);
    if (!page)
        return;
    /* (each new page's items once, in the log: what the mouse can point at) */
    static kujuUI::cLayoutPage *told_page;
    if (page != told_page)
    {
        told_page = page;
        int n = 0;
        for (std::vector<kujuUI::type_3E7D08 *>::iterator it = page->unk_0C.begin(); it != page->unk_0C.end(); ++it)
        {
            kujuUI::type_3E7D08 *w = *it;
            if (!w)
                continue;
            kujuUI::type_1E0330_rect r = w->vf_020();
            if (n++ < 24)
                plog("menu mouse:   item %p %s (%.0f,%.0f)-(%.0f,%.0f)", w, w->vf_010() ? "focusable" : "-", r.unk_00,
                     r.unk_04, r.unk_08, r.unk_0C);
        }
    }
    kujuUI::type_1E0330_rect r;
    int exact;
    kujuUI::type_3E7D08 *hit = widget_at(page, fx, fy, &r, &exact);
    if (hit && hit != page->sub_1E8C50())
        page->sub_1E8B50(hit);
    /* a click chooses the item under it (A); on a setting's arrows (its value's ends) it changes
       the setting (the d-pad's left and right); elsewhere it does nothing */
    if (pressed && hit)
    {
        if (exact && r.unk_08 - r.unk_00 < 600 && fx < r.unk_00 + 28)
            InterlockedIncrement(&port_menu_mouse_lefts);
        else if (exact && r.unk_08 - r.unk_00 < 600 && fx >= r.unk_08 - 28)
            InterlockedIncrement(&port_menu_mouse_rights);
        else
            InterlockedIncrement(&port_menu_mouse_clicks);
    }
}
#else
/* (single player's menus are Rt2d maestro movies, not kujuUI pages) */
extern "C" void port_menu_mouse_frame(void)
{
}
#endif
