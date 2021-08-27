//
// Created by castle on 8/25/21.
//

#include "event_handlers.h"
#include "../../ops/x11_ops.h"
#include "../../ops/client_ops.h"
#include "../../ops/monitor_ops.h"

void event_handlers::motion_notify(XEvent *ev) {}

void event_handlers::enter_notify(XEvent *ev) {
    XCrossingEvent *e = &ev->xcrossing;

    if ((e->mode != NotifyNormal || e->detail == NotifyInferior)
        && e->window != x11_ops::get_root()) return;

    client* c = clients_repo::get_by_window(e->window);
    monitor* m = monitors_repo::get_by_client(c);

    if (m != monitors_repo::get_focused()) {

    }

    client_ops::focus(c);

}

void event_handlers::destroy_notify(XEvent *ev) {}
void event_handlers::unmap_notify(XEvent *ev) {}
void event_handlers::configure_notify(XEvent *ev) {}
void event_handlers::property_notify(XEvent *ev) {}
void event_handlers::mapping_notify(XEvent *ev) {}
