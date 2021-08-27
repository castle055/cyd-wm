cmake_minimum_required(VERSION 3.19)
project(CydWM)

set(CMAKE_CXX_STANDARD 20)

add_executable(cydwm
        main.cpp
        watched_tasks/event_handling/event_loop.h
        watched_tasks/event_handling/event_loop.cpp
        watched_tasks/event_handling/event_handlers.h
        watched_tasks/watched_tasks.h
        watched_tasks/watched_tasks.cpp
        config_mgr/config_mgr.h
        config_mgr/config_mgr.cpp watched_tasks/watched_tasks_cfg.h watched_tasks/program_shell/program_shell.cpp watched_tasks/program_shell/program_shell.h ops/x11_ops.h watched_tasks/event_handling/keyboard_handler.cpp ops/x11_ops.cpp
        ops/drw.h ops/drw.cpp
        infrastructure/repositories/structs.h
        utils/logger.cpp utils/logger.h watched_tasks/event_handling/notify_handlers.cpp infrastructure/repositories/clients_repo.cpp infrastructure/repositories/clients_repo.h ops/client_ops.cpp ops/client_ops.h infrastructure/repositories/monitors_repo.cpp infrastructure/repositories/monitors_repo.h ops/monitor_ops.cpp ops/monitor_ops.h)

include_directories (/usr/include/freetype2)
target_link_libraries(cydwm X11 fontconfig Xft pthread)
