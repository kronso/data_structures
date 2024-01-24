#pragma once

typedef struct _BSTree BSTree;
struct _BSTree {
    void* _val;
    BSTree *_left, *_right;
};

void bstree_inorder(BSTree* tree);
void bstree_preorder(BSTree* tree);
void bstree_postorder(BSTree* tree);

void bstree_insert      (BSTree* tree, void* value);
void bstree_delete      (BSTree* tree, void* value);
BSTree* bstree_search   (BSTree* tree, void* value);
BSTree* bstree_parent   (BSTree* tree, void* value);
void bstree_rebalance   (BSTree** tree);

BSTree* bstree_new      (void* value);
void bstree_destroy     (BSTree* tree);
