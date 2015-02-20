//
//  clist.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/17/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__clist__
#define __c_plus_plus_practice__clist__

#include <stdio.h>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_set>

template <typename T>
class clist: public std::list<T> {
    
    
public:
    using std::list<T>::list;
    
    void deduplicate(clist<T> my_list);
    static clist<T> sumlists(clist<T> a, clist<T> b);
    static bool is_palindrome(clist<T> a);
    void push_w_min();
    T min();
    
};

#endif /* defined(__c_plus_plus_practice__clist__) */
