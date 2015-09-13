//
//  main.cpp
//  naychka 0.2.4
//
//  Created by Maks Kuzin on 20.03.15.
//  Copyright (c) 2015 Maks Kuzin. All rights reserved.
//

#include <iostream>
#include "mutexqueue.h"
#include "mutexqueue_oneLock.h"
#include "multiQueue.h"
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>

constexpr int rw_count = 500000;
constexpr int size_repit = 10;
constexpr int max_thread = 8;
constexpr int max_multiplier = 4;

int main() {
    for (auto type = 0; type < 18; type++) {
        if (type == 0) {
            std::cout << "multiQueue + spinlock_mutex 1x100000" << std::endl;
        }
        if (type == 1) {
            std::cout << "multiQueue + spinlock_mutex 2x100000" << std::endl;
        }
        if (type == 2) {
            std::cout << "multiQueue + spinlock_mutex 4x100000" << std::endl;
        }
        if (type == 3) {
            std::cout << "multiQueue + spinlock_mutex 8x100000" << std::endl;
        }
        if (type == 4) {
            std::cout << "multiQueue + spinlock_mutex 16x100000" << std::endl;
        }
        if (type == 5) {
            std::cout << "multiQueue + spinlock_mutex 32x100000" << std::endl;
        }
        if (type == 6) {
            std::cout << "multiQueue + spinlock_mutex 100x100000" << std::endl;
        }
        if (type == 7) {
            std::cout << "multiQueue + std::mutex 1x100000" << std::endl;
        }
        if (type == 8) {
            std::cout << "multiQueue + std::mutex 2x100000" << std::endl;
        }
        if (type == 9) {
            std::cout << "multiQueue + std::mutex 4x100000" << std::endl;
        }
        if (type == 10) {
            std::cout << "multiQueue + std::mutex 8x100000" << std::endl;
        }
        if (type == 11) {
            std::cout << "multiQueue + std::mutex 16x100000" << std::endl;
        }
        if (type == 12) {
            std::cout << "multiQueue + std::mutex 32x100000" << std::endl;
        }
        if (type == 13) {
            std::cout << "multiQueue + std::mutex 100x100000" << std::endl;
        }
        if (type == 14) {
            std::cout << "thread_queue_threeLock + std::mutex 100000" << std::endl;
        }
        if (type == 15) {
            std::cout << "thread_queue_threeLock + spinlock_mutex 100000" << std::endl;
        }
        if (type == 16) {
            std::cout << "thread_queue_oneLock + std::mutex 100000" << std::endl;
        }
        if (type == 17) {
            std::cout << "thread_queue_oneLock + spinlock_mutex 100000" << std::endl;
        }
        for (std::size_t size_thread = 1; size_thread <= max_thread; size_thread++) {
            std::cout << size_thread <<" thread " << std::endl;
            std::cout << "{";
            for (std::size_t multiplier = 1; multiplier <= max_multiplier; multiplier++) {
                double elapsed_seconds = 0;
                std::chrono::time_point<std::chrono::system_clock> start, end;
                if (type == 0) {
                    multiQueue<int, spinlock_mutex> a(1, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 1) {
                    multiQueue<int, spinlock_mutex> a(2, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 2) {
                    multiQueue<int, spinlock_mutex> a(4, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 3) {
                    multiQueue<int, spinlock_mutex> a(8, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 4) {
                    multiQueue<int, spinlock_mutex> a(16, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 5) {
                    multiQueue<int, spinlock_mutex> a(32, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 6) {
                    multiQueue<int, spinlock_mutex> a(100, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 7) {
                    multiQueue<int, std::mutex> a(1, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 8) {
                    multiQueue<int, std::mutex> a(2, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 9) {
                    multiQueue<int, std::mutex> a(4, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 10) {
                    multiQueue<int, std::mutex> a(8, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 11) {
                    multiQueue<int, std::mutex> a(16, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 12) {
                    multiQueue<int, std::mutex> a(32, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 13) {
                    multiQueue<int, std::mutex> a(100, 100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 14) {
                    thread_queue_threeLock<int, std::mutex> a(100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 15) {
                    thread_queue_threeLock<int, spinlock_mutex> a(100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 16) {
                    thread_queue_oneLock<int, std::mutex> a(100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                if (type == 17) {
                    thread_queue_oneLock<int, spinlock_mutex> a(100000);
                    start = std::chrono::system_clock::now();
                    for (std::size_t i = 1; i <= size_repit; i++) {
                        std::vector<std::thread> read_thread;
                        std::vector<std::thread> write_thread;
                        for (std::size_t j = 0; j < size_thread; j++) {
                            write_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.push(1);
                                }
                            }));
                            read_thread.push_back(std::thread([&] {
                                for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                                    a.pop();
                                }
                            }));
                        }
                        std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                        std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
                    }
                    end = std::chrono::system_clock::now();
                }
                elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                elapsed_seconds = elapsed_seconds / size_repit;
                elapsed_seconds = (rw_count * multiplier) / elapsed_seconds;
                //переводим в секунды
                elapsed_seconds = elapsed_seconds * 1000;
                std::cout << "{";
                std::cout << rw_count * multiplier << "," << std::setprecision(8) << elapsed_seconds << "}";
                (multiplier != max_multiplier) ? std::cout << "," : std::cout << "}";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "asd";
    return 0;
}