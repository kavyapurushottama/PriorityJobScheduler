#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include "task.h"

class ThreadPool
{
public:
    ThreadPool(int num_threads);

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    void enqueue(Task &&task);
    void shutdown();
    void print_summary();

private:
    std::vector<std::thread> workers;
    std::priority_queue<Task> tasks;

    // Synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;

    // For clean console output
    std::mutex cout_mutex;

    // Metrics
    std::mutex metrics_mutex;
    std::vector<long long> wait_times;
    std::vector<long long> turnaround_times;
    int total_tasks_processed;

    std::chrono::steady_clock::time_point start_time_global;
};

#endif
