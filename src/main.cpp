#include <iostream>
#include "watched_tasks/watched_tasks.h"
#include "config_mgr/config_mgr.h"
#include "ops/x11_ops.h"

void init() {
    config_mgr::reload();
    x11_ops::init();
    watched_tasks::start_all();
}

int main() {
    init();

    return 0;
}
