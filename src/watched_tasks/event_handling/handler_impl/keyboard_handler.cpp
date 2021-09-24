//
// Created by castle on 8/23/21.
//

#include "../event_handlers.h"
#include "../../../ops/x11_ops.h"
#include "../../../config_mgr/config_mgr.h"

#define CLEANMASK(mask)         ((mask) & ~(x11_ops::get_numlock_mask()|LockMask) & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))

void event_handlers::keypress(XEvent *ev) {
    KeySym keysym;
    XKeyEvent *key_event;

    key_event = &ev->xkey;
    keysym = XLookupKeysym(key_event, 0);

    if (config_mgr::get_keybindings().contains(keysym)
    && config_mgr::get_keybindings().at(keysym).contains(CLEANMASK(key_event->state))) {
        config_mgr::keybinding_action* action = config_mgr::get_keybindings()
                .at(keysym)
                .at(CLEANMASK(key_event->state));

        action->first(action->second);
    }
}