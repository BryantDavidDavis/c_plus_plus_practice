//
//  btree.cpp
//  c_plus_plus_practice
//
//  Created by Bryant Davis on 1/22/15.
//  Copyright (c) 2015 Bryant Davis. All rights reserved.
//

#include "btree.h"
#include <stdlib.h>
#include <vector>

BSTree::BSTree():root{} {}

void BSTree::insert(int x) {
    if (root == nullptr) {
        root = new BTNode{x};
    } else {
        insert(x, root);
    }
    return;
}

void BSTree::insert(int x, BTNode* leaf) {
    if (x < leaf->value) {
        if (leaf->left != nullptr) {
            insert(x, leaf->left);
            return;
        } else {
            leaf->left = new BTNode{x};
            return;
        }
    } else {
        if (leaf->right != nullptr) {
            insert(x, leaf->right);
            return;
        } else {
            leaf->right = new BTNode{x};
            return;
        }
    }
    return;
}

BSTree BSTree::min_height(const std::vector<int>& a) {
    BSTree new_tree{};
    if (a.empty()) {
        return new_tree;
    }
    int middle = a.size()/2;
    new_tree.insert(a[middle]);
    //int value = a[middle];
    std::vector<int> left_vector;
    std::vector<int> right_vector;
    for (auto p = a.begin(); p != (a.begin() + middle); ++p) {
        left_vector.push_back(*p);
    }
    for (auto p = ((a.begin() + middle) + 1); p != a.end(); ++p) {
        right_vector.push_back(*p);
    }
    new_tree.root->left = min_height(left_vector).root;
    new_tree.root->right = min_height(right_vector).root;
    return new_tree;
}

int BSTree::depth() {
    return depth(root);
}

int BSTree::depth(BTNode* leaf) {
    if (leaf == nullptr) {
        return 0;
    } else {
        if (depth(leaf->left) > depth(leaf->right)) {
            return 1 + depth(leaf->left);
        } else {
            return 1 + depth(leaf->right);
        }
    }
}

bool BSTree::is_balanced() {
    return is_balanced(root);
}

void BSTree::build_lists(std::vector<std::list<int>>& lists) {
    build_lists(0, lists, root);
    return;
}

void BSTree::build_lists(int current_depth, std::vector<std::list<int>>& lists, BTNode *leaf) {
    if (leaf == nullptr) {
        return;
    }
    if (!lists.size()) {
        lists.resize(10);
    }
    lists[current_depth].push_front(leaf->value);
    build_lists(current_depth + 1, lists, leaf->left);
    build_lists(current_depth + 1, lists, leaf->right);
    return;
}

bool BSTree::is_balanced(BTNode* leaf) {
    if (leaf == nullptr) {
        return true;
    }
    if (abs(depth(leaf->left) - depth(leaf->right)) < 2) {
        return true* is_balanced(leaf->left) * is_balanced(leaf->right);
    } else {
        return false;
    }
}

bool BSTree::isBST() {
    std::vector<int> storage {};
    inorder_traverse(root, storage);
    for (auto p = storage.begin(); p != (storage.end() - 1); ++p) {
        if (*(p+1) < *p) {
            return false;
        }
    }
    return true;
}

void BSTree::inorder_traverse(BTNode *leaf, std::vector<int>& storage) {
    if (leaf == nullptr) {
        return;
    }
    inorder_traverse(leaf->left, storage);
    storage.push_back(leaf->value);
    inorder_traverse(leaf->right, storage);
}

bool BSTree::is_subtree(BTNode* big, BTNode* small) {
    if (big == nullptr) {
        return false;
    }
    if (big->value == small->value) {
        bool compare_outcome = compare_trees(big, small);
        return compare_outcome;
    }
    bool outcome = (is_subtree(big->left, small) || is_subtree(big->right, small));
    return outcome;
}

bool BSTree::is_subtree(BSTree big, BSTree small) {
    return is_subtree(big.root, small.root);
}

bool BSTree::compare_trees(BTNode* big, BTNode* small) {
    if (small == nullptr) {
        return true;
    }
    if ((big == nullptr) || (big->value != small->value)) {
        return false;
    }
    return compare_trees(big->left, small->left) * compare_trees(big->right, small->right);
}