#pragma once

typedef struct _AVLTree AVLTree;
struct _AVLTree {
    int _val;
    AVLTree *_left, *_right;
};

void avl_inorder    (AVLTree* tree);
void avl_postorder  (AVLTree* tree);
void avl_preorder   (AVLTree* tree);

void avl_insert     (AVLTree** tree, int value);
void avl_delete     (AVLTree* tree, int value);

AVLTree* avl_new    (int value);
