/* SP front-end mouse input supplied by the Win32 platform layer. */
#ifndef PORT_PORT_MOUSE_H
#define PORT_PORT_MOUSE_H
#ifdef __cplusplus
extern "C" {
#endif
enum
{
    PORT_MENU_MOUSE_UP = 1,
    PORT_MENU_MOUSE_DOWN = 2,
    PORT_MENU_MOUSE_LEFT = 4,
    PORT_MENU_MOUSE_RIGHT = 8,
    PORT_MENU_MOUSE_ACCEPT = 16
};
void port_menu_mouse_reset(void);
void port_menu_mouse_hide(void);
int port_menu_mouse_poll(void);
#ifdef __cplusplus
}
#endif
#endif
