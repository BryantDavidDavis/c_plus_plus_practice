//
//  blist.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/14/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__blist__
#define __c_plus_plus_practice__blist__

#include <stdio.h>
#include <iostream>

template<typename T>
struct Node {
    Node(T x, Node<T>* next):data{x}, next{next}{}
    T data;
    Node<T>* next;
};

template<typename T>
class blist {
    
public:
    blist();
    void push_front(T x);
    void pop_front();
    void remove(T x);
    void deduplicate();
    void print_list();
    void partition(T x);

private:
    Node<T>* head;
};


#endif /* defined(__c_plus_plus_practice__blist__) */
