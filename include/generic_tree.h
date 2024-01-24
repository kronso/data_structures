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

void tree_add(Tree* tree, int val, unsigned depth, ...);
void tree_prune(Tree* tree, unsigned depth, ...);
void tree_graft(Tree* src, Tree* dst, unsigned depth, ...);

void tree_node_count(Tree* tree, unsigned* count);
Tree* tree_node_search(Tree* tree, unsigned depth, ...);

// void tree_depth(Tree* tree, unsigned* count);

// Tree* tree_LCA(Tree* tree, Tree* node1, Tree* node2);

void tree_clear(Tree* tree);
Tree* tree_new(int root);
void tree_destroy(Tree* tree);
