#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "thread_pool.h"
#include "task.h"

using namespace std;

int main()
{
    int num_threads, num_jobs;

    cout << "================ JOB PROCESSING ENGINE ================\n";
    cout << "Enter number of worker threads: ";
    cin >> num_threads;

    if (num_threads <= 0)
    {
        cout << "Thread count must be positive.\n";
        return 1;
    }

    ThreadPool pool(num_threads);

    cout << "Enter number of jobs to submit: ";
    cin >> num_jobs;

    if (num_jobs <= 0)
    {
        cout << "Number of jobs must be positive.\n";
        return 1;
    }

    vector<Task> jobs;

    for (int i = 0; i < num_jobs; ++i)
    {
        string job_type;
        int priority, execution_time;

        cout << "\nJob " << i + 1 << ":\n";
        cout << "Job Type (Email/Video/Analytics/Backup/Report): ";
        cin >> job_type;

        cout << "Priority (Higher number = Higher priority): ";
        cin >> priority;

        cout << "Execution time (ms): ";
        cin >> execution_time;

        jobs.emplace_back(i + 1, job_type, priority, execution_time);
    }

    cout << "\n---------------- JOB QUEUE ----------------\n";
    for (const auto &job : jobs)
    {
        cout << "Job " << job.id
             << " | Type: " << job.job_type
             << " | Priority: " << job.priority
             << " | Exec: " << job.execution_time << " ms\n";
    }

    cout << "\n---------------- EXECUTION LOG ----------------\n";

    for (auto &job : jobs)
    {
        pool.enqueue(move(job));
    }

    pool.shutdown();
    pool.print_summary();

    return 0;
}
