//
// Created by castle on 8/25/21.
//

#include "client_ops.h"

void client_ops::focus(client* c) {
    client* focused = clients_repo::get_focused();
    if (c != focused) unfocus(focused);

    if (c) {
        monitor *c_mon = monitors_repo::get_by_client(c);
        monitor_ops::focus(c_mon);

        set_urgent(c, false);


    } else {
        x11_ops::focus_root();
    }

}

void client_ops::set_urgent(client *c, bool urgent) {


}
