//
//  bry_stack.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 12/2/14.
//  Copyright (c) 2014 Bryant Davis. All rights reserved.
//

#include "bry_stack.h"


Bry_stack::Bry_stack(int s)
    :cp{s}, tp{-1}, sz{0}, contents{new int[s]} {
}

int Bry_stack::size()const {
    return sz;
}

int Bry_stack::peek()const {
    return contents[tp];
}

int Bry_stack::capacity()const {
    return cp;
}

int Bry_stack::push(int newguy) {
    ++tp;
    contents[tp] = newguy;
    ++sz;
    return newguy;
}

