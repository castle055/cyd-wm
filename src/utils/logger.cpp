//
// Created by castle on 8/25/21.
//

#include "logger.h"

#include <ctime>
#include <iostream>

void log(logger::log_level level, const std::string& log_msg, ...) {
    if (level <= logger::current_log_level) {
        std::string log_hdr = "[";

        std::time_t time = std::time(nullptr);
        log_hdr.append(std::to_string(time));
        log_hdr.append("]");

        switch (level) {
            case logger::CRITICAL:
                log_hdr.append("[CRITICAL] ");
                break;
            case logger::ERROR:
                log_hdr.append("[ERROR] ");
                break;
            case logger::WARNING:
                log_hdr.append("[WARNING] ");
                break;
            case logger::INFO:
                log_hdr.append("[INFO] ");
                break;
            case logger::DEBUG:
                log_hdr.append("[DEBUG] ");
                break;
            case logger::TRACE:
                log_hdr.append("[TRACE] ");
                break;
        }

        char buf[log_msg.size() * 2];
        va_list args;
        snprintf(buf, sizeof(buf), log_msg.c_str(), args);

        std::cout << log_hdr << buf << std::endl;
    }
}
