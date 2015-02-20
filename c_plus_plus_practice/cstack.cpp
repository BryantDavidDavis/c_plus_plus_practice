//
//  cstack.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "cstack.h"
#include <list>


cstack::cstack():data { std::list<min_wrapper>::list {} }{};

void cstack::push(int x) {
    min_wrapper new_guy {x};
    
    if (data.empty()) {
        new_guy.minimum = x;
    } else if (data.front().minimum < x) {
        new_guy.minimum = data.front().minimum;
    } else {
        new_guy.minimum = x;
    }
    data.push_front(new_guy);
    return;
}

int cstack::pop() {
    int result = data.front().value;
    data.pop_front();
    return result;
}

int cstack::min() {
    return data.front().minimum;
}