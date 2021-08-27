//
// Created by castle on 8/23/21.
//

#include <stdexcept>
#include "event_loop.h"
#include "event_handlers.h"
#include "../../ops/x11_ops.h"
#include "../../utils/logger.h"

static bool running = true;

void event_loop::run() {
    XEvent ev;

    XSync(x11_ops::get_dpy(), false);
    while (running) {
        if (!XNextEvent(x11_ops::get_dpy(), &ev)) {
            try {
                event_handlers::handlers.at(ev.type)(&ev);
            } catch (std::out_of_range& e) {
                log(logger::log_level::WARNING, "[ev_loop] Unhandled event: %d",  ev.type);
                continue;
            }
        }
    }
}

void event_loop::stop() {
    running = false;
}
