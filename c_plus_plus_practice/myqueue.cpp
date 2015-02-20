//
//  myqueue.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/20/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "myqueue.h"
#include <stack>
#include <iostream>
MyQueue::MyQueue():a{new std::stack<int> {}}, b{new std::stack<int>{}}{}

void MyQueue::push(int x) {
    
    if (a->empty()&&b->empty()) {
        a->push(x);
        return;
    }
    if (b->empty()) {
        a->push(x);
        return;
    } else {
        while (!b->empty()) {
            int value = b->top();
            a->push(value);
            b->pop();
        }
        a->push(x);
    }
    return;
}

int MyQueue::pop() {
    int result = -1;
    
    if (a->empty()&&b->empty()) {
        return result;
    }
    if (a->empty()) {
        result = b->top();
        b->pop();
        return result;
    } else {
        while(!a->empty()) {
            int value = a->top();
            b->push(value);
            a->pop();
        }
        result = b->top();
        b->pop();
        return result;
    }
}