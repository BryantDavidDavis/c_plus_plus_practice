//
//  bgraph.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/25/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__bgraph__
#define __c_plus_plus_practice__bgraph__

#include <stdio.h>
#include <vector>
#include <list>

struct Edge {
    int source;
    int dest;
    Edge(int source, int dest):source{source}, dest{dest} {}
};

class bgraph {
public:
    bgraph();
    void insert(int source, int dest);
    bool path_exists(int a, int b);
private:
    std::vector<std::list<Edge*>> nodes;
};

#endif /* defined(__c_plus_plus_practice__bgraph__) */
