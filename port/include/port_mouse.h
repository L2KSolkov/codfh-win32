/* SP front-end mouse input supplied by the Win32 platform layer. */
#ifndef PORT_PORT_MOUSE_H
#define PORT_PORT_MOUSE_H
#ifdef __cplusplus
extern "C" {
#endif
enum
{
    PORT_MENU_MOUSE_MOVE = 1,
    PORT_MENU_MOUSE_BUTTON = 2
};
void port_menu_mouse_reset(void);
void port_menu_mouse_hide(void);
/* Coordinates are in the 640x480 game frame; buttonState is 1 while left is held. */
int port_menu_mouse_poll(int *x, int *y, int *buttonState);
#ifdef __cplusplus
}
#endif
#endif
