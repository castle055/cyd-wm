//
// Created by castle on 8/23/21.
//

#ifndef CYDWM_X11_OPS_H
#define CYDWM_X11_OPS_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <clocale>

namespace x11_ops {

    enum {
        CurNormal, CurResize, CurMove, CurLast
    }; /* cursor */
    enum {
        NetSupported, NetWMName, NetWMState, NetWMCheck,
        NetWMFullscreen, NetActiveWindow, NetWMWindowType,
        NetWMWindowTypeDialog, NetClientList, NetLast
    }; /* EWMH atoms */
    enum {
        WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast
    }; /* default atoms */

    void init();

    void deinit();

    Display *get_dpy();
    unsigned int get_numlock_mask();

    Window get_root();

    void focus_window(Window* win);

    void focus_root();

    bool send_event(Window win, Atom proto);
}

#endif //CYDWM_X11_OPS_H
