//
// Created by castle on 8/25/21.
//

#ifndef CYDWM_CLIENT_OPS_H
#define CYDWM_CLIENT_OPS_H

#include "../infrastructure/repositories/clients_repo.h"

namespace client_ops {
    void focus(client* c);
    void unfocus(client* c);
}


#endif //CYDWM_CLIENT_OPS_H
