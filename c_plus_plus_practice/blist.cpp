//
//  blist.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/14/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "blist.h"
#include <iostream>
#include <unordered_set>

template<typename T>
blist<T>::blist():head{nullptr} {}

template<typename T>
void blist<T>::push_front(T x) {
    head = new Node<T>(x, head);
}

template<typename T>
void blist<T>::pop_front() {
    if(head != nullptr) {
        Node<T>* tmp = head;
        std::cout << head->data;
        head = head->next;
        delete tmp;
    }
}

template<typename T>
void blist<T>::remove(T x) {
    
    Node<T>* curr = head;
    Node<T>* prev = nullptr;
    
    while ( (curr != nullptr) && (curr->data != x) ) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == nullptr) {
        return;
    }
    if (prev == nullptr) {
        head = head->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;
    return;
}

template<typename T>
void blist<T>::print_list() {
    for (auto curr = head; curr != nullptr; curr = curr->next) {
        std::cout << curr->data;
    }
}

template<typename T>
void blist<T>::deduplicate() {
    std::unordered_set<T> my_set {};
    Node<T>* curr = head;
    Node<T>* prev = nullptr;
    
    while (curr != nullptr) {
        if(!my_set.insert(curr->data).second) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return;
}

template<typename T>
void blist<T>::partition(T x) {
    Node<T>* curr = head->next;
    Node<T>* prev = head;
    while (curr != nullptr) {
        if (curr->data < x) {
            prev->next = curr->next;
            curr->next = head;
            head = curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}




