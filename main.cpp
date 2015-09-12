//
//  main.cpp
//  naychka2.1
//
//  Created by Maks Kuzin on 20.03.15.
//  Copyright (c) 2015 Maks Kuzin. All rights reserved.
//

#include <iostream>
#include "mutexqueue.h"
#include "mutexqueue_oneLock.h"
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>

constexpr int rw_count = 500000;
constexpr int size_repit = 10;
constexpr int max_thread = 6;

int main() {
    std::cout << "!bez nagryzki!" << std::endl;
    std::cout << "thread_queue_threeLock" << std::endl;
    for (std::size_t size_thread = 1; size_thread <= max_thread; size_thread++) {
        std::cout << "{";
        for (std::size_t multiplier = 1; multiplier <= 4; multiplier++) {
            double elapsed_seconds = 0;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            thread_queue_oneLock<int, spinlock_mutex> a(100000);
            start = std::chrono::system_clock::now();
            for (std::size_t i = 1; i <= size_repit; i++) {
                std::vector<std::thread> read_thread;
                std::vector<std::thread> write_thread;
                for (std::size_t j = 0; j < size_thread; j++) {
                    write_thread.push_back(std::thread([&] {
                        for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                            a.try_push(1);
                        }
                    }));
                    read_thread.push_back(std::thread([&] {
                        for (std::size_t k = 0; k < ceil((rw_count * multiplier) / size_thread); k++) {
                            a.try_pop();
                        }
                    }));
                }
                std::for_each(read_thread.begin(), read_thread.end(), std::mem_fn(&std::thread::join));
                std::for_each(write_thread.begin(), write_thread.end(), std::mem_fn(&std::thread::join));
            }
            end = std::chrono::system_clock::now();
            elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
            elapsed_seconds = elapsed_seconds / size_repit;
            elapsed_seconds = (rw_count * multiplier) / elapsed_seconds;
                //переводим в секунды
            elapsed_seconds = elapsed_seconds * 1000;
            std::cout << "{";
            std::cout << rw_count * multiplier << "," << std::setprecision(8) << elapsed_seconds << "}";
            (multiplier != 4) ? std::cout << "," : std::cout << "}";
        }
        std::cout << std::endl;
    }
    return 0;
}