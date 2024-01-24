#pragma once

typedef struct _BSTree BSTree;
struct _BSTree {
    void* _val;
    BSTree *_left, *_right;
};


BSTree* bstree_search   (BSTree* tree, void* value);
void bstree_insert      (BSTree* tree, void* value);
void bstree_delete      (BSTree* tree, void* value);
void bstree_traverse    (BSTree* tree);

BSTree* bstree_parent   (BSTree* tree, void* value);
BSTree* bstree_new      (void* value);
void bstree_destroy     (BSTree* tree);
