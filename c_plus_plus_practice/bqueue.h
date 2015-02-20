//
//  bqueue.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__bqueue__
#define __c_plus_plus_practice__bqueue__

#include <stdio.h>
#include <list>

template<typename T>
class bqueue {

public:
    bqueue();
    void enqueue(T x);
    void dequeue();
    T peek();
private:
    std::list<T> data;
};

#endif /* defined(__c_plus_plus_practice__bqueue__) */
