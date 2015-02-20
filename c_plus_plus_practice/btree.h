//
//  btree.h
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/22/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#ifndef __c_plus_plus_practice__btree__
#define __c_plus_plus_practice__btree__

#include <stdio.h>
#include <vector>
#include <list>
struct BTNode {
    int value;
    BTNode* right;
    BTNode* left;
    BTNode(int x):value{x},right{nullptr}, left{nullptr}{}
};

class BSTree {
public:
    BSTree();
    void insert(int x);
    int depth();
    bool is_balanced();
    static BSTree min_height(const std::vector<int>& a);
    void build_lists(std::vector<std::list<int>>& lists);
    bool isBST();
    static bool is_subtree(BSTree a, BSTree b);
    //BTNode* first(BTNode* a, BTNode* b, BTNode* leaf);
private:
    BTNode* root;
    void insert(int x, BTNode* leaf);
    int depth(BTNode* leaf);
    bool is_balanced(BTNode* leaf);
    void build_lists(int current_depth, std::vector<std::list<int>>& lists, BTNode* leaf);
    void inorder_traverse(BTNode* leaf, std::vector<int>& storage);
    static bool is_subtree(BTNode* big, BTNode* small);
    static bool compare_trees(BTNode* big, BTNode* small);
    //bool contains(BTNode* a, BTNode* leaf);
};

#endif /* defined(__c_plus_plus_practice__btree__) */
