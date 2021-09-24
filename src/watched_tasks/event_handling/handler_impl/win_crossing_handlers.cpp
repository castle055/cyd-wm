
#include "../event_handlers.h"

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