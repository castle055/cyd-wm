//
// Created by castle on 8/23/21.
//

#include <X11/cursorfont.h>
#include "x11_ops.h"
#include "drw.h"
#include "../config_mgr/config_mgr.h"

static unsigned int numlock_mask = 0;

static Display *_dpy;
static Drw *drw;
static Cur *cursor[x11_ops::CurLast];
static int screen, sw, sh;
static Window root, wm_check_win;

static Atom wmatom[x11_ops::WMLast], netatom[x11_ops::NetLast];

void updatenumlockmask() {
    unsigned int i, j;
    XModifierKeymap *modmap;

    numlock_mask = 0;
    modmap = XGetModifierMapping(_dpy);
    for (i = 0; i < 8; i++)
        for (j = 0; j < modmap->max_keypermod; j++)
            if (modmap->modifiermap[i * modmap->max_keypermod + j]
                == XKeysymToKeycode(_dpy, XK_Num_Lock))
                numlock_mask = (1 << i);
    XFreeModifiermap(modmap);
}

void x11_ops::init() {

    [[maybe_unused]] bool supports_locale = setlocale(LC_CTYPE, "") || !XSupportsLocale();
    [[maybe_unused]] bool could_open_display = (_dpy = XOpenDisplay(NULL));

    XSetWindowAttributes wa;
    Atom utf8string;
    /* clean up any zombies immediately */
    // TODO ¬/
    //sigchld(0);

    /* init screen */
    screen = DefaultScreen(_dpy);
    sw = DisplayWidth(_dpy, screen);
    sh = DisplayHeight(_dpy, screen);
    root = RootWindow(_dpy, screen);
    drw = drw_create(_dpy, screen, root, sw, sh);
    static const char *fonts[] = { "Fira Code Retina:style=Bold:size=9:antialias=true:autohint:true" };
    [[maybe_unused]] bool could_load_fonts = drw_fontset_create(drw, fonts, 1);

        /* init atoms */
    utf8string = XInternAtom(_dpy, "UTF8_STRING", False);
    wmatom[WMProtocols] = XInternAtom(_dpy, "WM_PROTOCOLS", False);
    wmatom[WMDelete] = XInternAtom(_dpy, "WM_DELETE_WINDOW", False);
    wmatom[WMState] = XInternAtom(_dpy, "WM_STATE", False);
    wmatom[WMTakeFocus] = XInternAtom(_dpy, "WM_TAKE_FOCUS", False);
    netatom[NetActiveWindow] = XInternAtom(_dpy, "_NET_ACTIVE_WINDOW", False);
    netatom[NetSupported] = XInternAtom(_dpy, "_NET_SUPPORTED", False);
    netatom[NetWMName] = XInternAtom(_dpy, "_NET_WM_NAME", False);
    netatom[NetWMState] = XInternAtom(_dpy, "_NET_WM_STATE", False);
    netatom[NetWMCheck] = XInternAtom(_dpy, "_NET_SUPPORTING_WM_CHECK", False);
    netatom[NetWMFullscreen] = XInternAtom(_dpy, "_NET_WM_STATE_FULLSCREEN", False);
    netatom[NetWMWindowType] = XInternAtom(_dpy, "_NET_WM_WINDOW_TYPE", False);
    netatom[NetWMWindowTypeDialog] = XInternAtom(_dpy, "_NET_WM_WINDOW_TYPE_DIALOG", False);
    netatom[NetClientList] = XInternAtom(_dpy, "_NET_CLIENT_LIST", False);
    /* init cursors */
    cursor[CurNormal] = drw_cur_create(drw, XC_left_ptr);
    cursor[CurResize] = drw_cur_create(drw, XC_sizing);
    cursor[CurMove] = drw_cur_create(drw, XC_fleur);

/* supporting window for NetWMCheck */
    wm_check_win = XCreateSimpleWindow(_dpy, root, 0, 0, 1, 1, 0, 0, 0);
    XChangeProperty(_dpy, wm_check_win, netatom[NetWMCheck], XA_WINDOW, 32,
                    PropModeReplace, (unsigned char *) &wm_check_win, 1);
    XChangeProperty(_dpy, wm_check_win, netatom[NetWMName], utf8string, 8,
                    PropModeReplace, (unsigned char *) "dwm", 3);
    XChangeProperty(_dpy, root, netatom[NetWMCheck], XA_WINDOW, 32,
                    PropModeReplace, (unsigned char *) &wm_check_win, 1);
    /* EWMH support per view */
    XChangeProperty(_dpy, root, netatom[NetSupported], XA_ATOM, 32,
                    PropModeReplace, (unsigned char *) netatom, NetLast);
    XDeleteProperty(_dpy, root, netatom[NetClientList]);

    /* select events */
    wa.cursor = cursor[CurNormal]->cursor;
    wa.event_mask = SubstructureRedirectMask | SubstructureNotifyMask
                    | ButtonPressMask | PointerMotionMask | EnterWindowMask
                    | LeaveWindowMask | StructureNotifyMask | PropertyChangeMask;
    XChangeWindowAttributes(_dpy, root, CWEventMask | CWCursor, &wa);
    XSelectInput(_dpy, root, wa.event_mask);

    /* grab keys */
    updatenumlockmask();
    unsigned int j;
    unsigned int modifiers[] = {0, LockMask, numlock_mask, numlock_mask | LockMask};
    KeyCode code;

    XUngrabKey(_dpy, AnyKey, AnyModifier, root);
    for (const auto &keybinding : config_mgr::get_keybindings()) {
        code = XKeysymToKeycode(_dpy, keybinding.first);

        for (const auto &kb_mod_pair : keybinding.second) {

            for (j = 0; j < (sizeof modifiers / sizeof modifiers[0]); j++)
                XGrabKey(_dpy, code, kb_mod_pair.first | modifiers[j], root,
                         True, GrabModeAsync, GrabModeAsync);
        }
    }
    //focusNULL();  // TODO - what is this? is this needed? Hopefully you'll just delete this line like 'whaaaaª...?
}

void x11_ops::deinit() {
    XDestroyWindow(_dpy, wm_check_win);

    XSync(_dpy, False);
    XSetInputFocus(_dpy, PointerRoot, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(_dpy, root, netatom[NetActiveWindow]);
}


Display *x11_ops::get_dpy() {
    return _dpy;
}

unsigned int x11_ops::get_numlock_mask() {
    return numlock_mask;
}

Window x11_ops::get_root() {
    return root;
}

void x11_ops::focus_root() {
    XSetInputFocus(_dpy, root, RevertToPointerRoot, CurrentTime);
    XDeleteProperty(_dpy, root, netatom[NetActiveWindow]);
}

bool x11_ops::send_event(Window win, Atom proto) {
    int n;
    Atom *protocols;
    int exists = 0;
    XEvent ev;

    if (XGetWMProtocols(_dpy, win, &protocols, &n)) {
        while (!exists && n--)
            exists = protocols[n] == proto;
        XFree(protocols);
    }
    if (exists) {
        ev.type = ClientMessage;
        ev.xclient.window = win;
        ev.xclient.message_type = wmatom[WMProtocols];
        ev.xclient.format = 32;
        ev.xclient.data.l[0] = proto;
        ev.xclient.data.l[1] = CurrentTime;
        XSendEvent(_dpy, win, False, NoEventMask, &ev);
    }
    return exists;
}
