//
// Created by castle on 8/23/21.
//

#include <thread>
#include "watched_tasks.h"
#include "event_handling/event_loop.h"
#include <unordered_map>

struct watched_task {
    std::string name;
    void (*task)();
};

#include "watched_tasks_cfg.h"

std::unordered_map<std::string, std::thread*> running_tasks;

void watched_tasks::start_all() {
    for (const auto & task : tasks) {
        if (running_tasks.contains(task.name))
            continue;
        running_tasks[task.name] = new std::thread(task.task);
    }
    running_tasks["event_loop"]->detach();
    while(1) {
        std::this_thread::yield();
    }
}

void watched_tasks::stop_all() {

}