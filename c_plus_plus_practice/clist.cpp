//
//  clist.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/17/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <list>
#include <unordered_set>
#include "clist.h"

template<typename T>
void clist<T>::deduplicate(clist<T> my_list) {
    std::unordered_set<T> my_set {};
    for (auto curr = my_list.begin(); curr != my_list.end(); ++curr) {
        if(!my_set.insert(*curr).second) {
            my_list.erase(curr);
        }
    }
    return;
}

template<typename T>
clist<T> clist<T>::sumlists(clist<T> a, clist<T> b) {
    clist<T> new_list {};
    auto acurr = a.begin();
    auto bcurr = b.begin();
    bool carryover = false;
    while ((acurr != a.end()||(bcurr!=b.end()))) {
        auto result = (*acurr)*(acurr != a.end()) + (*bcurr)*(bcurr != b.end());
        new_list.push_back(carryover + (result % 10));
        if (result >= 10) {
            carryover = true;
        } else {
            carryover = false;
        }
        if(acurr != a.end()) {
           ++acurr;
        }
        if(bcurr != b.end()) {
            ++bcurr;
        }
    }
    return new_list;
}

template<typename T>
bool clist<T>::is_palindrome(clist<T> a) {
    auto f = a.begin();
    auto b = --a.end();
    bool ispalindrome = true;
    while ((f != b)&&(ispalindrome)) {
        if (*f != *b) {
            ispalindrome = false;
            return ispalindrome;
        }
        ++f;
        --b;
    }
    return true;
}