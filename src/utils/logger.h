//
// Created by castle on 8/25/21.
//

#ifndef CYDWM_LOGGER_H
#define CYDWM_LOGGER_H

#include <string>

namespace logger {
    enum log_level {
        CRITICAL = 0,
        ERROR = 1,
        WARNING = 2,
        INFO = 3,
        DEBUG = 4,
        TRACE = 5
    };

    static log_level current_log_level = TRACE;
}

void log(logger::log_level level, const std::string& log_msg, ...);


#endif //CYDWM_LOGGER_H
