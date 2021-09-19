//
// Created by castle on 8/25/21.
//

#ifndef CYDWM_CLIENT_OPS_H
#define CYDWM_CLIENT_OPS_H

#include "../infrastructure/repositories/clients_repo.h"
#include "../infrastructure/repositories/monitors_repo.h"

#include "monitor_ops.h"
#include "x11_ops.h"

namespace client_ops {
    void focus(client* c);
    void unfocus(client* c);

    void set_urgent(client* c, bool urgent);
}


#endif //CYDWM_CLIENT_OPS_H
