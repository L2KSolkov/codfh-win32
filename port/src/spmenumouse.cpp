/*
 * The mouse in single player's menus, as in multiplayer's (menumouse.cpp): pointing at an item
 * focuses it, the left button chooses it (A), the right goes back (B) and the wheel moves up and
 * down (the d-pad). The window's messages and the pad's buttons are multiplayer's (winmain.cpp,
 * xpal_sys.cpp's menu_mouse_state); what differs is finding the items and the focus.
 *
 * Single player's menus are Rt2d maestro movies (src/sp/units/sp_fend*.cpp): their only buttons
 * are the pad's (btnUp, btnDown, btnAction... with pick regions off the stage, for the key presses
 * the movies were made with), so RenderWare's own maestro mouse has nothing to point at. The items
 * are the movie's strings: each drawn as two or more copies in the same place (a shadow and the
 * text), the focused one with one more (its highlight layer shows only the focused item's copy).
 * Pointing at an item moves the focus to it as the pad does, a press of btnUp or btnDown (or
 * btnLeft / btnRight for a row) at a time, until the highlight is on it.
 *
 * CODFH_SPDUMP=n logs the screen's items and the focus every 40 frames from frame n;
 * CODFH_SPMOUSE="frame:x:y[:c],..." points (and with c clicks) at x,y of the 640x480 frame at
 * those frames, for driving the menus without a person.
 */
#ifdef CODFH_SP
#include <xtl.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "port.h"
#include "d3d/pdev.h"

/* RenderWare 3.7.2's Rt2dObject (RWSDK/tool/2d/rt2d.h) as far as the mouse reads it; the image's
   keeps its matrices 16-byte aligned (a word before the first) */
struct sp_matrix
{
    float right[3];
    unsigned flags;
    float up[3];
    unsigned pad1;
    float at[3];
    unsigned pad2;
    float pos[3];
    unsigned pad3;
};
struct sp_rgba_real
{
    float r, g, b, a;
};
struct sp_font_node
{
    char *name;
    void *font;
};
struct sp_object
{
    int type;                   /* 1 scene, 3 pick region, 4 string */
    int depth;
    int flag;                   /* 4: visible */
    int pad;
    sp_matrix MTM;
    sp_matrix LTM;              /* (in the 2d device's units: the frame's height is 1, y up) */
    sp_rgba_real colorMult;
    sp_rgba_real colorOffs;
    struct
    {
        char *text;
        const float *brush;     /* (its bottom colour from word 12) */
        int maxLength;
        float height;
        sp_font_node *font;
    } str;
};
typedef sp_object *(*sp_object_cb)(sp_object *object, sp_object *parent, void *data);
extern "C" sp_object *Rt2dSceneForAllChildren(sp_object *scene, sp_object_cb callback, void *data);
extern "C" sp_object *Rt2dMaestroGetScene(void *maestro);
extern "C" float Rt2dFontGetStringWidth(void *font, const char *string, float height);
extern "C" int Rt2dFontIsUnicode(void *font);

/* A text's width in the font's units: a Unicode font measures UTF-16 (the front end's texts are
   its 8-bit ones, widened as type_DA580::sub_DA860 does). */
static float text_width(void *font, const char *text, size_t n, float height)
{
    if (!Rt2dFontIsUnicode(font))
    {
        char a[256];
        n = n < 255 ? n : 255;
        memcpy(a, text, n);
        a[n] = 0;
        return Rt2dFontGetStringWidth(font, a, height);
    }
    unsigned short w[256];
    n = n < 255 ? n : 255;
    for (size_t i = 0; i < n; i++)
        w[i] = (unsigned char)text[i];
    w[n] = 0;
    return Rt2dFontGetStringWidth(font, (const char *)w, height);
}

/* the window's (menumouse.cpp, winmain.cpp) */
extern "C" volatile LONG port_menu_mouse_x, port_menu_mouse_y, port_menu_mouse_moved, port_menu_mouse_pressed;
extern "C" volatile LONG port_menu_mouse_clicks;
extern "C" unsigned port_menu_frame;

/* One string as drawn: its text and its box in the 640x480 frame. */
struct sp_text
{
    const char *text;
    float x0, y0, x1, y1;
    float bright;
};
/* An item: the copies of one text in one place. */
struct sp_item
{
    const char *text;
    float x0, y0, x1, y1;
    int copies;
    float bright;
};

static sp_text texts[256];
static int text_count;

static sp_object *collect(sp_object *o, sp_object *parent, void *data)
{
    (void)parent;
    int visible = (int)(size_t)data && (o->flag & 4);
    if (o->type == 1)
        Rt2dSceneForAllChildren(o, collect, (void *)(size_t)visible);
    else if (o->type == 4 && visible && o->str.text && text_count < 256)
    {
        const char *t = o->str.text;
        while (*t == ' ')
            t++;
        if (!*t)
            return o;
        float sx = o->LTM.right[0] * 480, sy = o->LTM.up[1] * 480;
        float x = o->LTM.pos[0] * 480, y = (1 - o->LTM.pos[1]) * 480;
        void *font = o->str.font ? o->str.font->font : NULL;
        float lead = 0, w = 0;
        if (font)
        {
            /* (the leading spaces centre the text in the movies: its box starts after them) */
            lead = text_width(font, o->str.text, t - o->str.text, o->str.height) * sx;
            w = text_width(font, t, strlen(t), o->str.height) * sx;
        }
        else
            w = strlen(t) * o->str.height * 0.5f * sx;
        float h = o->str.height * sy;
        sp_text &s = texts[text_count++];
        s.text = t;
        s.x0 = x + lead;
        s.x1 = x + lead + w;
        s.y0 = y - h * 0.8f;
        s.y1 = y + h * 0.1f;
        s.bright = o->str.brush ? o->str.brush[12] + o->str.brush[13] + o->str.brush[14] : 0;
    }
    return o;
}

static sp_item items[64];
static int item_count, focus;

/* The screen's items and the focused one: the texts (bar the buttons' legends) gathered by place,
   the focused one drawn in more copies than any other (or, as many, the brightest; -1 when none
   stands out), the items the texts of its list: its height, in its column (or its row). */
static void find_items(void *maestro)
{
    text_count = 0;
    collect(Rt2dMaestroGetScene(maestro), NULL, (void *)1);
    item_count = 0;
    focus = -1;
    static sp_item all[128];
    int n = 0;
    for (int i = 0; i < text_count; i++)
    {
        sp_text &t = texts[i];
        /* (the legends: the pad's glyphs, "$ms$" and the like, and the texts on their row) */
        int legend = 0;
        for (int j = 0; j < text_count && !legend; j++)
            if (texts[j].text[0] == '$' && texts[j].y1 > t.y0 && texts[j].y0 < t.y1)
                legend = 1;
        if (legend)
            continue;
        int k;
        for (k = 0; k < n; k++)
            if (!strcmp(all[k].text, t.text) && fabsf(all[k].x0 - t.x0) < 4 && fabsf(all[k].y1 - t.y1) < 4)
                break;
        if (k == n)
        {
            if (n == 128)
                continue;
            all[n].text = t.text;
            all[n].x0 = t.x0;
            all[n].y0 = t.y0;
            all[n].x1 = t.x1;
            all[n].y1 = t.y1;
            all[n].copies = 0;
            all[n].bright = 0;
            n++;
        }
        all[k].copies++;
        if (t.bright > all[k].bright)
            all[k].bright = t.bright;
    }
    int most = 0, most_n = 0, f = -1;
    for (int k = 0; k < n; k++)
        if (all[k].copies > most)
            most = all[k].copies, most_n = 1, f = k;
        else if (all[k].copies == most)
            most_n++;
    if (most_n != 1)
    {
        float best = -1;
        int best_n = 0;
        f = -1;
        for (int k = 0; k < n; k++)
            if (all[k].copies != most)
                continue;
            else if (all[k].bright > best + 1)
                best = all[k].bright, best_n = 1, f = k;
            else if (all[k].bright > best - 1)
                best_n++;
        if (best_n != 1)
            f = -1;
    }
    if (f < 0)
        return;
    /* (a column of items, else a row: a setting's value beside its name is not an item) */
    sp_item &fi = all[f];
    float fh = fi.y1 - fi.y0;
    for (int pass = 0; pass < 2 && item_count < 2; pass++)
    {
        item_count = 0;
        for (int k = 0; k < n && item_count < 64; k++)
        {
            sp_item &it = all[k];
            float h = it.y1 - it.y0;
            int in = pass ? it.y1 > fi.y0 && it.y0 < fi.y1 : it.x1 > fi.x0 && it.x0 < fi.x1;
            if (h > fh * 0.85f && h < fh * 1.15f && in)
            {
                if (k == f)
                    focus = item_count;
                items[item_count++] = it;
            }
        }
    }
}

/* The item under (x, y): the one the point is in, else the one whose row it is in (8 pixels
   taller each way, as multiplayer's), the nearest when rows overlap. */
static int item_at(float x, float y)
{
    int row = -1;
    float best = 1e9f;
    for (int k = 0; k < item_count; k++)
    {
        sp_item &it = items[k];
        if (x >= it.x0 - 8 && x < it.x1 + 8 && y >= it.y0 - 4 && y < it.y1 + 4)
            return k;
        float cy = (it.y0 + it.y1) / 2, d = y > cy ? y - cy : cy - y;
        if (y >= it.y0 - 8 && y < it.y1 + 8 && d < best)
        {
            /* (a row only when the item is alone on it: in a row of items, the one pointed at) */
            int alone = 1;
            for (int j = 0; j < item_count; j++)
                if (j != k && fabsf((items[j].y0 + items[j].y1) / 2 - cy) < (it.y1 - it.y0) / 2)
                    alone = 0;
            if (alone)
                best = d, row = k;
        }
    }
    return row;
}

/* CODFH_SPMOUSE's points (the frame's coordinates) */
struct sp_scripted
{
    unsigned frame;
    float x, y;
    int click;
};
static sp_scripted script[64];
static int script_count = -1;

static void load_script(void)
{
    script_count = 0;
    char v[2048];
    if (!GetEnvironmentVariableA("CODFH_SPMOUSE", v, sizeof(v)))
        return;
    for (char *tok = strtok(v, ","); tok && script_count < 64; tok = strtok(NULL, ","))
    {
        sp_scripted &s = script[script_count];
        char c = 0;
        if (sscanf(tok, "%u:%f:%f:%c", &s.frame, &s.x, &s.y, &c) >= 3)
        {
            s.click = c == 'c';
            script_count++;
        }
    }
    plog("sp menu mouse: %d scripted points", script_count);
}

/* The window's point and click, read once a frame (the menus' step runs for each screen up;
   the one with a focus takes them). */
static int input_have, input_pressed;
static float input_x, input_y;
static unsigned input_frame;

static void read_input(int log)
{
    if (input_frame == port_frame)
        return;
    input_frame = port_frame;
    LONG moved = InterlockedExchange(&port_menu_mouse_moved, 0);
    LONG pressed = InterlockedExchange(&port_menu_mouse_pressed, 0);
    input_have = input_pressed = 0;
    if ((moved || pressed) &&
        pdev_window_to_frame((int)port_menu_mouse_x, (int)port_menu_mouse_y, &input_x, &input_y))
    {
        input_have = 1;
        input_pressed = pressed != 0;
        if (log)
            plog("sp menu mouse: frame %u, window point %.0f,%.0f%s", port_frame, input_x, input_y,
                 pressed ? ", click" : "");
    }
    if (script_count < 0)
        load_script();
    for (int i = 0; i < script_count; i++)
        if (script[i].frame == port_frame)
        {
            input_x = script[i].x;
            input_y = script[i].y;
            input_have = 1;
            input_pressed |= script[i].click;
            plog("sp menu mouse: frame %u, scripted point %.0f,%.0f%s", port_frame, input_x, input_y,
                 script[i].click ? ", click" : "");
        }
}

/* Run once a frame by each screen's step (type_sp_AD970::sp_sub_AE0D0) while it reads the pad:
   the d-pad press that moves its focus toward the item pointed at (1 up, 2 down, 3 left, 4 right;
   0 none), or 5: Start (a click on the title's "Press START"). A click chooses the item under it
   once the focus is on it (A); on a setting's value (the text beside its name) it changes the
   setting instead, its right half to the next (the d-pad's right), its left half back (left). */
extern "C" int port_sp_menu_mouse(void *maestro)
{
    static void *target_maestro;
    static int target = -1, steps, wait, action, last_focus;
    static unsigned last_frame;
    static float tx, ty;
    if (!maestro)
        return 0;
    /* (the menus are up: the window shows the cursor and gives its buttons to the pad) */
    port_menu_frame = port_frame ? port_frame : 1;
    static int dump = -1;
    if (dump < 0)
    {
        char v[16];
        dump = GetEnvironmentVariableA("CODFH_SPDUMP", v, sizeof(v)) ? atoi(v) : 0;
    }
    int log_steps = dump != 0;
    read_input(log_steps);
    if (target >= 0 && port_frame > last_frame + 2)
        target = -1;
    if (target >= 0 && maestro != target_maestro)
        return 0;
    int dumping = dump && port_frame >= (unsigned)dump && (port_frame - dump) % 40 == 0;
    if (!input_have && target < 0 && !dumping)
        return 0;
    find_items(maestro);
    if (dumping)
    {
        plog("sp menu mouse: frame %u, maestro %p, %d items, focus %d", port_frame, maestro, item_count, focus);
        for (int k = 0; k < item_count; k++)
            plog("sp menu mouse:   %d '%s' (%.0f,%.0f)-(%.0f,%.0f), %d copies, brightness %.0f", k, items[k].text,
                 items[k].x0, items[k].y0, items[k].x1, items[k].y1, items[k].copies, items[k].bright);
    }

    if (input_have)
    {
        float fx = input_x, fy = input_y;
        if (focus < 0)
        {
            /* the title's prompt has no item: a click on it is Start */
            if (input_pressed)
                for (int i = 0; i < text_count; i++)
                    if (strstr(texts[i].text, "START") && fx >= texts[i].x0 - 8 && fx < texts[i].x1 + 8 &&
                        fy >= texts[i].y0 - 8 && fy < texts[i].y1 + 8)
                    {
                        input_have = 0;
                        plog("sp menu mouse: click on '%s' (Start)", texts[i].text);
                        return 5;
                    }
            return 0;
        }
        input_have = 0;
        int hit = item_at(fx, fy);
        int act = 0;
        if (input_pressed && hit >= 0)
        {
            act = 1;
            /* (a value: a text on the item's row, after its name) */
            sp_item &it = items[hit];
            for (int i = 0; i < text_count; i++)
            {
                sp_text &v = texts[i];
                if (v.x0 >= it.x1 && v.y1 > it.y0 && v.y0 < it.y1 && fx >= v.x0 - 8 && fx < v.x1 + 8)
                    act = fx < (v.x0 + v.x1) / 2 ? 3 : 4;
            }
        }
        if (hit >= 0 && (target < 0 || hit != target || act))
        {
            target = hit;
            target_maestro = maestro;
            tx = (items[hit].x0 + items[hit].x1) / 2;
            ty = (items[hit].y0 + items[hit].y1) / 2;
            steps = 0;
            wait = 0;
            action = act;
        }
    }
    if (target < 0)
        return 0;
    last_frame = port_frame;
    /* (the target found again by place: a step can change the items' texts, not where they are) */
    int t = -1;
    for (int k = 0; k < item_count; k++)
        if (tx >= items[k].x0 - 2 && tx < items[k].x1 + 2 && ty >= items[k].y0 - 2 && ty < items[k].y1 + 2)
            t = k;
    if (t < 0 || focus < 0)
    {
        target = -1;
        return 0;
    }
    if (t == focus)
    {
        target = -1;
        if (action == 1)
        {
            plog("sp menu mouse: click on '%s' (A)", items[t].text);
            InterlockedIncrement(&port_menu_mouse_clicks);
        }
        else if (action)
            plog("sp menu mouse: click on '%s' value (%s)", items[t].text, action == 3 ? "left" : "right");
        return action == 1 ? 0 : action;
    }
    /* one press, then the next once the highlight has moved (or after a quarter second); given up
       after more presses than the screen has items (an item the pad cannot reach) */
    if (wait > 0 && focus == last_focus && --wait > 0)
        return 0;
    if (++steps > item_count + 1)
    {
        target = -1;
        return 0;
    }
    last_focus = focus;
    wait = 15;
    sp_item &f = items[focus], &g = items[t];
    float fcy = (f.y0 + f.y1) / 2, gcy = (g.y0 + g.y1) / 2;
    int step = gcy < fcy - 4 ? 1 : gcy > fcy + 4 ? 2 : g.x0 < f.x0 ? 3 : 4;
    if (log_steps)
        plog("sp menu mouse: frame %u, '%s' to '%s': %s", port_frame, f.text, g.text,
             step == 1 ? "up" : step == 2 ? "down" : step == 3 ? "left" : "right");
    return step;
}
#endif
