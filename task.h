#ifndef TASK_H
#define TASK_H

#include <chrono>
#include <string>

class Task
{
public:
    int id;
    std::string job_type;
    int priority;
    int execution_time;

    std::chrono::steady_clock::time_point arrival_time;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point finish_time;

    Task(int id, std::string job_type, int priority, int execution_time)
        : id(id),
          job_type(job_type),
          priority(priority),
          execution_time(execution_time),
          arrival_time(std::chrono::steady_clock::now()) {}

    bool operator<(const Task &other) const
    {
        return priority < other.priority;
    }
};

#endif
