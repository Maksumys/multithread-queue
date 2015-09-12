//
// Created by maks on 12.09.15.
//

#ifndef NAYCHKA_MULTIQUEUE_H
#define NAYCHKA_MULTIQUEUE_H

#include <memory>

template<class type_value, class type_mutex>
class multiQueue {
    type_value **_mas_queue;
    type_mutex *_mutex_head;
    type_mutex *_mutex_tail;

public:
    multiQueue(std::size_t n, std::size_t m) {
        _mas_queue = *new type_value[];
        _mutex_head = *new type_mutex[];
        _mutex_tail = *new type_mutex[];


    }
};

#endif //NAYCHKA_MULTIQUEUE_H
