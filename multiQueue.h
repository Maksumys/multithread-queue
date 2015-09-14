//
// Created by maks on 12.09.15.
//

#ifndef NAYCHKA_MULTIQUEUE_H
#define NAYCHKA_MULTIQUEUE_H

#include <memory>
#include <mutex>
#include <bits/unique_ptr.h>

template<class type_value, class type_mutex>
class multiQueue {
    std::unique_ptr<type_value[]> _mas_queue;
    std::unique_ptr<std::size_t[]> _mas_head;
    std::unique_ptr<std::size_t[]> _mas_tail;
    std::unique_ptr<std::size_t[]> _mas_distance;
    std::size_t _length_n;
    std::size_t _length_m;
    std::unique_ptr<type_mutex[]> _mas_mutex_head;
    std::unique_ptr<type_mutex[]> _mas_mutex_tail;
    std::unique_ptr<type_mutex[]> _mas_mutex_distance;
public:
    multiQueue(std::size_t n, std::size_t m) {
        _mas_queue.reset(new type_value[n*m]);
        _mas_head.reset(new std::size_t[n]);
        _mas_tail.reset(new std::size_t[n]);
        _mas_distance.reset(new std::size_t[n]);
        _mas_mutex_head.reset(new type_mutex[n]);
        _mas_mutex_tail.reset(new type_mutex[n]);
        _mas_mutex_distance.reset(new type_mutex[n]);

        _length_n = n;
        _length_m = m;
        for(auto i = 0; i < _length_n; i++) {
            _mas_head[i] = m - 1;
            _mas_tail[i] = m - 1;
            _mas_distance[i] = m;
        }
    }

    void push(type_value elem) {
        std::size_t i = 0;
        //прыгаем по очередям пока не найдем свободную или подходящую
        while(true) {
            if (_mas_mutex_tail[i].try_lock()) {
                while(!_mas_mutex_distance[i].try_lock()){}
                if (_mas_distance[i] > 0) {
                    _mas_mutex_distance[i].unlock();
                    break;
                }
                _mas_mutex_distance[i].unlock();
                _mas_mutex_tail[i].unlock();
            }
            (i < _length_n - 1) ? i++ : i = 0;
        }
        _mas_queue[_length_m * i + _mas_tail[i]] = elem;
        (_mas_tail[i] == 0) ? _mas_tail[i] = _length_m - 1 : _mas_tail[i]--;
        while(!_mas_mutex_distance[i].try_lock()){}
        _mas_distance[i]--;
        _mas_mutex_distance[i].unlock();
        _mas_mutex_tail[i].unlock();
    }

    void pop() {
        std::size_t i = 0;
        while(true) {
            if (_mas_mutex_head[i].try_lock()) {
                while(!_mas_mutex_distance[i].try_lock()){}
                if(_mas_distance[i] != _length_m) {
                    _mas_mutex_distance[i].unlock();
                    break;
                }
                _mas_mutex_distance[i].unlock();
                _mas_mutex_head[i].unlock();
            }
            (i < _length_n - 1)? i++ : i = 0;
        }
        (_mas_head[i] == 0) ? _mas_head[i] = _length_m - 1 : _mas_head[i]--;
        while(!_mas_mutex_distance[i].try_lock()){}
        _mas_distance[i]++;
        _mas_mutex_distance[i].unlock();
        _mas_mutex_head[i].unlock();
    }

    type_value front() {
        for (auto i = 0; i < _length_n; i++) {
            if(_mas_distance[i] != _length_m) {
                std::lock_guard<type_mutex> lock(_mas_mutex_head[i]);
                return _mas_queue[_length_m * i + _mas_head[i]];
            }
        }
    }

    type_value back() {
        for (auto i = 0; i < _length_n; i++) {
            if(_mas_distance[i] != _length_m) {
                std::lock_guard<type_mutex> lock(_mas_mutex_tail[i]);
                return _mas_queue[_length_m * i + _mas_tail[i]];
            }
        }
    }
};

#endif //NAYCHKA_MULTIQUEUE_H
