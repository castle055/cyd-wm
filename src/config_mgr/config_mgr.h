//
// Created by castle on 8/23/21.
//

#ifndef CYDWM_CONFIG_MGR_H
#define CYDWM_CONFIG_MGR_H

#include <string>
#include <X11/X.h>
#include <unordered_map>

namespace config_mgr {
    typedef union {
        int i;
        unsigned int ui;
        float f;
        const void *v;
    } arg;

    typedef std::pair<void (*)(const arg), const arg> keybinding_action;
    typedef std::unordered_map<int, keybinding_action*> keybinding_mod_map;
    typedef std::unordered_map<KeySym , keybinding_mod_map> keybinding_map;

    void reload();

    int get_int(std::string int_option);
    double get_double(std::string double_option);
    std::string get_str(std::string string_option);


    keybinding_map& get_keybindings();

}

#endif //CYDWM_CONFIG_MGR_H
