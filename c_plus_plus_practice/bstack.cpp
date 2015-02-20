//
//  bstack.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/19/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "bstack.h"
#include <list>

template<typename T>
bstack<T>::bstack():data{} {
    std::list<T> data;
}

template<typename T>
bool bstack<T>::push(T x) {
    data.push_front(x);
    return true;
}
//
//template<typename T>
//T bstack<T>::peek() {
//    return data.front();
//}
//
//template<typename T>
//T bstack<T>::pop() {
//    int result = data.front();
//    data.pop_front();
//    return result;
//}

//template<typename T>
//T bstack<T>::min() {
//    return data.front().minimum;
//}

//template<typename T>
//void bstack<T>::push_w_min(T x) {
//    if (x < the_min) {
//        the_min = x;
//    }
//    //data.push_front(new min_wrapper{x, the_min});
//    return;
//    
//}