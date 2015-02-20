//
//  SetOfStacks.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__SetOfStacks__
#define __c_plus_plus_practice__SetOfStacks__

#include <stdio.h>
#include <stack>
#include <list>

class SetOfStacks {
public:
    SetOfStacks();
    void push(int x);
    int pop();
private:
    std::list<std::stack<int>*>* mystacks;
    int capacity;
};

#endif /* defined(__c_plus_plus_practice__SetOfStacks__) */
