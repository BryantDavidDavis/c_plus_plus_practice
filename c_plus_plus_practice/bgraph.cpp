//
//  bgraph.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/25/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "bgraph.h"
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <queue>
#include <iostream>


bgraph::bgraph():nodes{ std::vector<std::list<Edge*>>(20) } {}

void bgraph::insert(int source, int dest) {
    Edge* new_guy = new Edge{source, dest};
    if (source && (source >= nodes.size())) {
        nodes.resize(source);
    }
    if ((nodes.begin()+source)->empty()) {
        nodes[source] = std::list<Edge*>{};
        nodes[source].push_front(new_guy);
    } else {
        nodes.at(source).push_front(new_guy);
    }
    return;
}

bool bgraph::path_exists(int a, int b) {
    std::vector<bool> identified(nodes.size());
    std::queue<int> theQueue{};
    theQueue.push(a);
    int u {};
    while (!theQueue.empty()) {
        u = theQueue.front();
        theQueue.pop();
        for (auto v = nodes[u].begin(); v != nodes[u].end(); ++v) {
            if((*v)->dest == b) {
                return true;
            }
            if (!identified[(*v)->dest]) {
                identified[(*v)->dest] = true;
                theQueue.push((*v)->dest);
            }
        }
    }
    return false;
}

//nodes.insert(nodes.begin() + source, std::list<Edge*>{})->push_front(new_guy); //we don't want to use insert here, because it adds an element to the vector, rather than changing its value