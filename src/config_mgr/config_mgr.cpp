//
// Created by castle on 8/23/21.
//

#include "config_mgr.h"
#include <X11/keysym.h>

#include "../utils/logger.h"

static config_mgr::keybinding_map keybindings;

static void aye(const config_mgr::arg _arg) {
    log(logger::log_level::INFO, (char*)_arg.v);
}

void config_mgr::reload() {
    const arg _arg = { .v = "aye" };
    static keybinding_action kb_action = { aye, _arg };

    keybinding_mod_map kb_mod_map;
    kb_mod_map[Mod4Mask] = &kb_action;

    keybindings[XK_a] = kb_mod_map;
}

config_mgr::keybinding_map& config_mgr::get_keybindings() {
    return keybindings;
}
