//
//  AnimalQueue.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/21/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "AnimalQueue.h"
#include <list>
#include <string>

AnimalQueue::AnimalQueue():data{new std::list<Animal> {}}{}

void AnimalQueue::enqueue(int animal_type, std::string name) {
    Animal new_guy = Animal(animal_type, name);
    data->push_back(new_guy);
}

Animal AnimalQueue::dequeueAny() {
    Animal result = *(data->begin());
    data->pop_front();
    return result;
}

Animal AnimalQueue::dequeueCat() {
    
    for (auto curr = data->begin(); curr != data->end(); ++curr) {
        if (curr->animal_type == 1) {
            Animal result = *curr;
            data->erase(curr);
            return result;
        }
    }
    return dequeueAny();
    
}

Animal AnimalQueue::dequeueDog() {
    
    for (auto curr = data->begin(); curr != data->end(); ++curr) {
        if (curr->animal_type == 2) {
            Animal result = *curr;
            data->erase(curr);
            return result;
        }
    }
    return dequeueAny();
    
}