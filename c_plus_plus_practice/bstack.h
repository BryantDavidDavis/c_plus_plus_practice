//
//  bstack.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__bstack__
#define __c_plus_plus_practice__bstack__

#include <stdio.h>
#include <list>
template <typename T>
struct min_wrapper {
    min_wrapper(T x):value{x}, minimum{}{}
    T value;
    T minimum;
};

template <typename T>
class bstack {

public:
    bstack();
    bool push(T x);
    T pop();
    T peek();
    T min();
    void push_w_min(T x);
private:
    std::list<min_wrapper<T>> data;
    
};

#endif /* defined(__c_plus_plus_practice__bstack__) */
