//
// Created by castle on 8/23/21.
//

#ifndef CYDWM_EVENT_HANDLERS_H
#define CYDWM_EVENT_HANDLERS_H

#include <X11/Xlib.h>
#include <unordered_map>

namespace event_handlers {
    void keypress               (XEvent* ev);
    void buttonpress            (XEvent* ev);
    void motion_notify          (XEvent* ev);
    void enter_notify           (XEvent* ev);
    void focus_in               (XEvent* ev);
    void expose                 (XEvent* ev);
    void destroy_notify         (XEvent* ev);
    void unmap_notify           (XEvent* ev);
    void map_request            (XEvent* ev);
    void configure_notify       (XEvent* ev);
    void property_notify        (XEvent* ev);
    void client_message         (XEvent* ev);
    void mapping_notify         (XEvent* ev);
    void configure_request      (XEvent* ev);

    static std::unordered_map<int, void (*)(XEvent*)> handlers {
          /*  EVENT TYPE             FUNCTION HANDLER           */
            {KeyPress,              keypress                    },
            {ButtonPress,           buttonpress                 },
            {MotionNotify,          motion_notify               },
            {EnterNotify,           enter_notify                },
            {FocusIn,               focus_in                    },
            {Expose,                expose                      },
            {DestroyNotify,         destroy_notify              },
            {UnmapNotify,           unmap_notify                },
            {MapRequest,            map_request                 },
            {ConfigureNotify,       configure_notify            },
            {PropertyNotify,        property_notify             },
            {ClientMessage,         client_message              },
            {MappingNotify,         mapping_notify              },
            {ConfigureRequest,      configure_request           }
    };
}

#endif //CYDWM_EVENT_HANDLERS_H
