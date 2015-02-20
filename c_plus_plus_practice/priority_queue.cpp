//
//  priority_queue.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 2/5/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "priority_queue.h"
#include <vector>

Priority_queue::Priority_queue():the_heap{std::vector<int>{}} {}

void Priority_queue::offer(int x) {
    the_heap.push_back(x);
    int index = the_heap.size() - 1;
    int temp = 0;
    int parent = (index -1)/2;
    while ((the_heap.at(parent) > x)&&index) {
        temp = the_heap.at((index -1)/2);
        parent =(index - 1)/2;
        the_heap.at(parent) = x;
        the_heap.at(index) = temp;
        index = parent;
        parent = (parent - 1)/2;
    }
}

int Priority_queue::peek() {
    int y = the_heap.front();
    return y;
}

int Priority_queue::poll() {
    int to_return = the_heap.front();
    the_heap.at(0) = the_heap.at(the_heap.size() - 1);
    the_heap.pop_back();
    int replacer_value = the_heap.at(0);
    int current_pos = 0;
    int child_left = 1;
    int child_right = 2;
    int small_child = 0;

    while ((child_left <= (the_heap.size() - 1))&&(child_right <= (the_heap.size()-1))) {
        if((the_heap.at(child_left) < the_heap.at(current_pos)) || (the_heap.at(child_right) < the_heap.at(current_pos))) {
            if(the_heap.at(child_left) <= the_heap.at(child_right)) {
                small_child = child_left;
            } else {
                small_child = child_right;
            }
            the_heap.at(current_pos) = the_heap.at(small_child);
            the_heap.at(small_child) = replacer_value;
            current_pos = small_child;
            child_left = (current_pos * 2) + 1;
            child_right = (current_pos * 2) + 2;
        } else {
            return to_return;
        }
    }
    return to_return;
}

//int* parent(int* child) {
//    int* parent = child;
//    parent = parent - 1;
//    parent = parent/2;
//    return parent;
//}
