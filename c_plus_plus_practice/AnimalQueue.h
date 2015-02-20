//
//  AnimalQueue.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/21/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__AnimalQueue__
#define __c_plus_plus_practice__AnimalQueue__

#include <stdio.h>
#include <list>
#include <string>

struct Animal {
    Animal(int x, std::string y):animal_type{x}, name{new std::string {y}}{}
    int animal_type; //1 is cat, 2 is dog
    std::string* name;
};

class AnimalQueue {
public:
    AnimalQueue();
    void enqueue(int animal_type, std::string name);
    Animal dequeueAny();
    Animal dequeueCat();
    Animal dequeueDog();
private:
    std::list<Animal>* data;
};
#endif /* defined(__c_plus_plus_practice__AnimalQueue__) */
