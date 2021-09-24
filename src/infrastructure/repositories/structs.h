

#ifndef CYDWM_STRUCTS_H
#define CYDWM_STRUCTS_H

#include <X11/X.h>
#include <cstdint>
#include <list>
#include <vector>
#include <string>

struct client {
    uint16_t x, y, w, h;
    Window win;
};
struct workspace {
    std::string title;
    std::list<client*> clients;
};
struct monitor {
    uint16_t x, y, w, h;
    std::vector<workspace*> workspaces;
};
struct layout;
struct rules;
struct keybind;

#endif // CYDWM_STRUCTS_H
