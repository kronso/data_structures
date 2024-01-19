#pragma once

#include "../include/vector.h"

typedef struct _TreeNode {
    void* node;
} TreeNode;

typedef struct _Tree {
    int _val;
    Vector* _children;
} Tree;

void tree_traverse(Tree* tree);
void tree_add(Tree*tree, unsigned depth, int val, ...);
void tree_prune(Tree* tree, unsigned depth, ...);


Tree* tree_new(int root);
void tree_destroy(Tree* tree);
