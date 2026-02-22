# 🚀 PriorityTaskScheduler

A high-performance, priority-based multithreaded job processing engine built using modern C++ concurrency primitives.

This project simulates an operating system–style scheduler using a thread pool architecture and priority-driven execution. It demonstrates strong understanding of multithreading, synchronization, scheduling algorithms, and performance monitoring in C++.

---

## 📌 Overview

PriorityTaskScheduler is designed to:

- Process jobs concurrently using multiple worker threads
- Schedule tasks based on priority (higher priority executes first)
- Ensure thread-safe execution using mutexes and condition variables
- Measure and report performance metrics such as:
  - Waiting Time
  - Turnaround Time
  - Throughput
  - Total Execution Time

---

## 🧠 Core Concepts Implemented

- Thread Pool Design Pattern
- Producer-Consumer Model
- Priority Scheduling (Max Heap)
- Concurrency Control
- Deadlock Prevention
- Performance Monitoring
- Graceful Shutdown Mechanism

---

Each worker thread:

1. Waits for task availability
2. Picks highest priority task
3. Executes the task
4. Updates performance metrics
5. Continues until shutdown

---

## 🛠 Technologies Used

- C++17
- STL (thread, mutex, condition_variable, priority_queue, chrono)
- Multithreading
- Synchronization Primitives
- Scheduling Algorithms

---
## 📸 Screenshots


---

## ▶ How to Compile

### On Windows (MinGW / g++):

```bash
g++ main.cpp thread_pool.cpp -std=c++17 -pthread -o job_engine
job_engine //command prompt
.\job_engine.exe //powershell

```

### On Windows (MinGW / g++):

```bash
g++ main.cpp thread_pool.cpp -std=c++17 -pthread -o job_engine
```
