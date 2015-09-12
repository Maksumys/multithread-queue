//
//  mutex_type.h
//  naychka3
//
//  Created by Maks Kuzin on 13.06.15.
//  Copyright (c) 2015 Maks Kuzin. All rights reserved.
//

#ifndef naychka3_mutex_type_h
#define naychka3_mutex_type_h

#include <atomic>

class spinlock_mutex {
    std::atomic<bool> flag;
public:
    spinlock_mutex() {
        flag.store(false);
    }

    void lock() {
        bool a = false;
        while (!flag.compare_exchange_weak(a, true)) {
            a = false;
        }
    }

    bool try_lock() {
        bool a = false;
        return flag.compare_exchange_weak(a, true);
    }

    void unlock() {
        flag.store(false);
    }
};

#endif
