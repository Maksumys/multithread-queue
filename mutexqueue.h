//
//  Queue.h
//  naychka2.1
//
//  Created by Maks Kuzin on 20.03.15.
//  Copyright (c) 2015 Maks Kuzin. All rights reserved.
//

#ifndef __naychka2_1__Queue__
#define __naychka2_1__Queue__

#include <stdio.h>
#include <iostream>
#include <mutex>
#include "mutex_type.h"
#include <condition_variable>
#include "queue.h"


//потокобезопасная очередь с мелкогранулярными блокировками(три мьютекса)+шаблонный мьютекс
template <class type_value, class type_mutex>
class thread_queue_threeLock : public queue<type_value> {
protected:
    type_mutex mutex_distance;
    type_mutex mutex_head;
    type_mutex mutex_tail;
    std::condition_variable_any condition_head;
    std::condition_variable_any condition_tail;
public:
    thread_queue_threeLock() {}
    thread_queue_threeLock(const std::size_t n) : queue<type_value>(n) {}
    
    virtual void push(const type_value elem) {
        std::unique_lock<type_mutex> tail_lock(mutex_tail);
        condition_head.wait(tail_lock, [&] {
            return getDistance() > 0;
        });
        this -> mas_queue[this -> tail] = elem;
        (this -> tail == 0) ? this -> tail = this -> length - 1 : this -> tail--;
        mutex_distance.lock();
        this -> distance--;
        mutex_distance.unlock();
        condition_tail.notify_one();
    }

    virtual void pop() {
        std::unique_lock<type_mutex> head_lock(mutex_head);
        condition_tail.wait(head_lock, [&] {
            return getDistance() != this -> length;
        });
        (this -> head == 0) ? this -> head = this -> length - 1 : this -> head--;
        mutex_distance.lock();
        this -> distance++;
        mutex_distance.unlock();
        condition_head.notify_one();
    }

    void try_push(const type_value elem) {
        while (!mutex_tail.try_lock()) {}
        while (true) {
            if  (try_getDistance() > 0) {
                break;
            }
        }
        this -> mas_queue[this -> tail] = elem;
        (this -> tail == 0) ? this -> tail = this -> length - 1 : this -> tail--;
        while (!mutex_distance.try_lock()) {}
        this -> distance--;
        mutex_distance.unlock();
        mutex_tail.unlock();
    }

    void try_pop() {
        while (!mutex_head.try_lock()) {}
        while (true) {
            if (try_getDistance() != this -> length) {
                break;
            }
        }
        (this -> head == 0) ? this -> head = this -> length - 1 : this -> head--;
        while (!mutex_distance.try_lock()) {}
        this -> distance++;
        mutex_distance.unlock();
        mutex_head.unlock();
    }

    virtual type_value front() {
        std::lock_guard<type_mutex> lock(mutex_head);
        return this -> mas_queue[this -> head];
    }

    virtual type_value back() {
        std::lock_guard<type_mutex> lock(mutex_tail);
        return this -> mas_queue[this -> tail];
    }

    virtual std::size_t getDistance() {
        std::lock_guard<type_mutex> lock(mutex_distance);
        return this -> distance;
    }

    std::size_t try_getDistance() {
        while (true) {
            if(mutex_distance.try_lock()) {
                break;
            }
        }
        std::size_t _distance = this -> distance;
        mutex_distance.unlock();
        return _distance;
    }
};
#endif /* defined(__naychka2_1__Queue__) */
