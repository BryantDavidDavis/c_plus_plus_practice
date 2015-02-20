//
//  priority_queue.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 2/5/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__priority_queue__
#define __c_plus_plus_practice__priority_queue__

#include <stdio.h>
#include <vector>

class Priority_queue {
public:
    Priority_queue();
    int poll();
    int peek();
    void offer(int x);
    
private:
    std::vector<int> the_heap;
    int* parent(int* child);
    int* child(int* parent);
};
#endif /* defined(__c_plus_plus_practice__priority_queue__) */
