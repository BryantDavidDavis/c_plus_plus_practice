//
//  bry_stack.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 12/2/14.
//  Copyright (c) 2014 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__bry_stack__
#define __c_plus_plus_practice__bry_stack__

#include <stdio.h>
#include <vector>


class Bry_stack {
private:
    int* contents;
    int tp;
    int sz;
    int cp;
public:
    Bry_stack(int s);
    int size()const;
    int capacity()const;
    int peek()const;
    int push(int newguy);
};
#endif /* defined(__c_plus_plus_practice__bry_stack__) */
