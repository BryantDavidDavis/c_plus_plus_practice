//
//  SetOfStacks.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//
#include <iostream>
#include "SetOfStacks.h"
#include <stack>
#include <list>

SetOfStacks::SetOfStacks():capacity{30}, mystacks{new std::list<std::stack<int>*>} {}

void SetOfStacks::push(int x) {
    if ((mystacks->front() == nullptr)||((mystacks->front()->size() == capacity))) {
        mystacks->push_front(new std::stack<int>);
    }
    mystacks->front()->push(x);
}

int SetOfStacks::pop() {
    if (mystacks->front()->empty()) {
        mystacks->pop_front();
    }
    int result = mystacks->front()->top();
    mystacks->front()->pop();
    return result;
}


