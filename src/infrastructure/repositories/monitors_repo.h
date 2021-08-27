//
// Created by castle on 8/25/21.
//

#ifndef CYDWM_MONITORS_REPO_H
#define CYDWM_MONITORS_REPO_H

#include "structs.h"

namespace monitors_repo {
    monitor* get_by_client(client*);
    monitor* get_focused();
}


#endif //CYDWM_MONITORS_REPO_H
