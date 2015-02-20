//
//  bqueue.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "bqueue.h"
#include <list>

template<typename T>
bqueue<T>::bqueue():data{ std::list<T> {} } {}

template<typename T>
void bqueue<T>::enqueue(T x) {
    data.push_front(x);
}

template<typename T>
void bqueue<T>::dequeue() {
    data.pop_back();
}

template<typename T>
T bqueue<T>::peek() {
    return data.back();
}