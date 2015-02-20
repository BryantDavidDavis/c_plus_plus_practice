//
//  myqueue.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/20/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__myqueue__
#define __c_plus_plus_practice__myqueue__

#include <stdio.h>
#include <stack>

class MyQueue {
public:
    MyQueue();
    void push(int x);
    int pop();
private:
    std::stack<int>* a;
    std::stack<int>* b;
};

#endif /* defined(__c_plus_plus_practice__myqueue__) */
