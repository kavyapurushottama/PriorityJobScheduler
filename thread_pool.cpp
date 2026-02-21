#include "thread_pool.h"
#include <iostream>

using namespace std;

ThreadPool::ThreadPool(int num_threads)
    : stop(false), total_tasks_processed(0)
{
    start_time_global = chrono::steady_clock::now();

    for (int i = 0; i < num_threads; ++i)
    {
        workers.emplace_back([this]()
                             {
            while (true)
            {
                Task task(0, "", 0, 0);

                {
                    unique_lock<mutex> lock(queue_mutex);

                    condition.wait(lock, [this]() {
                        return stop || !tasks.empty();
                    });

                    if (stop && tasks.empty())
                        return;

                    task = tasks.top();
                    tasks.pop();
                }

                task.start_time = chrono::steady_clock::now();

                auto wait_time =
                    chrono::duration_cast<chrono::milliseconds>(
                        task.start_time - task.arrival_time).count();

                {
                    lock_guard<mutex> lock(cout_mutex);
                    cout << "[Worker " << this_thread::get_id()
                         << "] Processing "
                         << task.job_type
                         << " Job " << task.id << "\n";
                }

                this_thread::sleep_for(
                    chrono::milliseconds(task.execution_time));

                task.finish_time = chrono::steady_clock::now();

                auto turnaround_time =
                    chrono::duration_cast<chrono::milliseconds>(
                        task.finish_time - task.arrival_time).count();

                {
                    lock_guard<mutex> lock(metrics_mutex);
                    wait_times.push_back(wait_time);
                    turnaround_times.push_back(turnaround_time);
                    total_tasks_processed++;
                }

                {
                    lock_guard<mutex> lock(cout_mutex);
                    cout << "[Worker " << this_thread::get_id()
                         << "] Completed "
                         << task.job_type
                         << " Job " << task.id
                         << " | Wait: " << wait_time
                         << " ms | Turnaround: "
                         << turnaround_time << " ms\n";
                }
            } });
    }
}

void ThreadPool::enqueue(Task &&task)
{
    {
        lock_guard<mutex> lock(queue_mutex);
        tasks.push(task);
    }

    condition.notify_one();
}

void ThreadPool::shutdown()
{
    {
        lock_guard<mutex> lock(queue_mutex);
        stop = true;
    }

    condition.notify_all();

    for (thread &worker : workers)
    {
        if (worker.joinable())
            worker.join();
    }
}

void ThreadPool::print_summary()
{
    long long total_wait = 0;
    long long total_turnaround = 0;

    for (auto w : wait_times)
        total_wait += w;

    for (auto t : turnaround_times)
        total_turnaround += t;

    double avg_wait = wait_times.empty() ? 0 : (double)total_wait / wait_times.size();
    double avg_turnaround = turnaround_times.empty() ? 0 : (double)total_turnaround / turnaround_times.size();

    auto end_time_global = chrono::steady_clock::now();

    double total_execution_time =
        chrono::duration_cast<chrono::milliseconds>(
            end_time_global - start_time_global)
            .count() /
        1000.0;

    double throughput =
        total_execution_time > 0 ? total_tasks_processed / total_execution_time : 0;

    cout << "\n================ DASHBOARD SUMMARY ================\n";
    cout << "Total Jobs Processed      : " << total_tasks_processed << "\n";
    cout << "Average Waiting Time      : " << avg_wait << " ms\n";
    cout << "Average Turnaround Time   : " << avg_turnaround << " ms\n";
    cout << "Throughput                : " << throughput << " jobs/sec\n";
    cout << "Total Execution Time      : " << total_execution_time << " sec\n";
    cout << "===================================================\n";
}
