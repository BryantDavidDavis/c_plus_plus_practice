//
//  cstack.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__cstack__
#define __c_plus_plus_practice__cstack__

#include <stdio.h>
#include <list>

struct min_wrapper {
    min_wrapper(int x):value{x}, minimum{}{};
    int minimum;
    int value;
};

class cstack {

public:
    cstack();
    void push(int x);
    int pop();
    int min();
private:
    std::list<min_wrapper> data;
};

#endif /* defined(__c_plus_plus_practice__cstack__) */
