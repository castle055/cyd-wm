//
// Created by castle on 8/25/21.
//

#ifndef CYDWM_CLIENTS_REPO_H
#define CYDWM_CLIENTS_REPO_H

#include "structs.h"

namespace clients_repo {
    client* get_by_window(Window win);
    client* get_focused();
}


#endif //CYDWM_CLIENTS_REPO_H
