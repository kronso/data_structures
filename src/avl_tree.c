#include <stdio.h>
#include <stdlib.h>


#include "../include/avl_tree.h"

// inorder traversal
void avl_inorder(AVLTree* bstree) {
    if (bstree) 
    {
        avl_inorder(bstree->_left);
        printf("%d ", bstree->_val);
        avl_inorder(bstree->_right);
    }
}
void avl_postorder(AVLTree* bstree) {
    if (bstree) 
    {
        avl_postorder(bstree->_left);
        avl_postorder(bstree->_right);
        printf("%d ", bstree->_val);
    }
}
void avl_preorder(AVLTree* bstree) {
    if (bstree) 
    {
        printf("%d ", bstree->_val);
        avl_preorder(bstree->_left);
        avl_preorder(bstree->_right);
    }
}


struct _avl_parents { AVLTree *top, *mid; };
// left-side of new_node
void LL_rotation(struct _avl_parents parent) {
    // int val = parent.top->_val;
    // parent.top->_val = parent.mid->_val;
    // parent.mid->_val = parent.mid->_left->_val;
    // free(parent.mid->_left);
    // parent.mid->_left = NULL;
    // parent.top->_right = avl_new(val);
    parent.top->_left  = parent.mid->_left;
    parent.top->_right = parent.mid;
    parent.top->_right->_left = NULL;

    int val = parent.top->_val;
    parent.top->_val = parent.top->_right->_val;
    parent.top->_right->_val = val;
}
void LL_rotation_extra(struct _avl_parents parent) {
    AVLTree* top_right = parent.top->_right;
    parent.top->_left  = parent.mid->_left;
    parent.top->_right = parent.mid;

    parent.top->_right->_left  = parent.mid->_right;
    parent.top->_right->_right = top_right;

    int val = parent.top->_val;
    parent.top->_val = parent.top->_right->_val;
    parent.top->_right->_val = val;
}
void RR_rotation(struct _avl_parents parent) {
    parent.top->_right  = parent.mid->_right;
    parent.top->_left = parent.mid;
    parent.top->_left->_right = NULL; 

    int val = parent.top->_val;
    parent.top->_val = parent.top->_left->_val;
    parent.top->_left->_val = val; 
}
void RR_rotation_extra(struct _avl_parents parent) {
    AVLTree* top_left = parent.top->_left;
    parent.top->_right  = parent.mid->_right;
    parent.top->_left = parent.mid;

    parent.top->_left->_right  = parent.mid->_left;
    parent.top->_left->_left = top_left;

    int val = parent.top->_val;
    parent.top->_val = parent.top->_left->_val;
    parent.top->_left->_val = val;
}

void LR_rotation(struct _avl_parents parent) {
    int val = parent.top->_val;
    parent.top->_val = parent.mid->_right->_val;
    free(parent.mid->_right);
    parent.mid->_right = NULL;
    parent.top->_right = avl_new(val);
}
void RL_rotation(struct _avl_parents parent) {
    int val = parent.top->_val;
    parent.top->_val = parent.mid->_left->_val;
    free(parent.mid->_left);
    parent.mid->_left = NULL;
    parent.top->_left = avl_new(val);
}
void RL_rotation_extra(struct _avl_parents parent) {
    int val;
    AVLTree* top_left = parent.top->_right;
    parent.top->_left = parent.mid->_left;

    parent.top->_right = parent.mid;
    parent.top->_right->_left = parent.mid->_right;

    parent.top->_right->_right = top_left;

    val = parent.top->_val;
    parent.top->_val = parent.mid->_val;
    parent.mid->_val = val;
    // int val;
    // AVLTree* top_left = parent.top->_left;
    // parent.top->_right = parent.mid->_right;

    // parent.top->_left = parent.mid;
    // parent.top->_left->_right = parent.mid->_left;

    // parent.top->_left->_left = top_left;

    // val = parent.top->_val;
    // parent.top->_val = parent.mid->_val;
    // parent.mid->_val = val;
}
void LR_rotation_extra(struct _avl_parents parent) {
    AVLTree* A_r = parent.top->_right;
    int top_val = parent.top->_val;
    
    parent.top->_right = parent.mid->_right;

    parent.mid->_right = parent.mid->_right->_left;
    parent.top->_right->_left = parent.top->_right->_right;
    parent.top->_right->_right = A_r;

    parent.top->_val = parent.top->_right->_val;
    parent.top->_right->_val = top_val;
    //int val;
    //AVLTree* top_right = parent.top->_right;
    //parent.top->_left = parent.mid->_left;

    //parent.top->_right = parent.mid;
    //parent.top->_right->_left = parent.mid->_right;

    //parent.top->_right->_right = top_right;

    //val = parent.top->_val;
    //parent.top->_val = parent.mid->_val;
    //parent.mid->_val = val;
}
unsigned height(AVLTree* tree) {
    if (tree) 
    {
        unsigned height_left  = height(tree->_left);
        unsigned height_right = height(tree->_right);

        if (height_left > height_right) 
            return height_left + 1;
        else 
            return height_right + 1;
    }
    return 0;
}

void avl_rotation(AVLTree* bottom_node, struct _avl_parents parent, int bf) {
    if (bf == 2)
    {
        if (parent.mid->_right && parent.mid->_left)
            LR_rotation_extra(parent);
        //else if (bottom_node == parent.mid->_left && parent.mid->_right)
        //    LL_rotation_extra(parent);
        else if (parent.mid->_left)
            LL_rotation(parent);
        else if (parent.mid->_right)
            LR_rotation(parent);
    }
    else if (bf == -2)
    {
        if (parent.mid->_left && parent.mid->_right) 
            RL_rotation_extra(parent);
        //else if (bottom_node == parent.mid->_right && parent.mid->_left)
        //    RR_rotation_extra(parent);
        else if (parent.mid->_right)
            RR_rotation(parent);
        else if (parent.mid->_left)
            RL_rotation(parent);
    }

}
void traverse(AVLTree* tree, struct _avl_parents* parent, int  h_left, int  h_right, int balance_factor, AVLTree* bottom_node) {
    if (tree)
    {
        traverse(tree->_left, parent, h_left, h_right, balance_factor, bottom_node);
        traverse(tree->_right, parent, h_left, h_right, balance_factor, bottom_node);

        h_left  = height(tree->_left);
        h_right = height(tree->_right);

        balance_factor = h_left - h_right;

        if (balance_factor == 2 || balance_factor == -2)
        {
            parent->top = tree;
            parent->mid = (balance_factor == 2) ? tree->_left: tree->_right;

            avl_rotation(bottom_node, *parent, balance_factor);
        }
   }
}
void wrapper(AVLTree* tree, AVLTree* bottom_node) {
    int h_left, h_right;
    h_left = h_right = 0;

    int balance_factor = 0;

    struct _avl_parents parent = { 0 };
    
    traverse(tree, &parent, h_left, h_right, balance_factor, bottom_node);
}

void avl_insert(AVLTree** tree, int value) {
    AVLTree* new_tree = avl_new(value);
    AVLTree* saved_tree = *tree;
    while (saved_tree) 
    {
        if (value < saved_tree->_val) 
            if (saved_tree->_left == NULL)
            {
                saved_tree->_left = new_tree;
                //avl_rotations(tree, new_tree);
                wrapper(*tree, new_tree);
                saved_tree = NULL;
            }
            else 
                saved_tree = saved_tree->_left;
        else if (value > saved_tree->_val)
            if (saved_tree->_right == NULL) 
            { 
                saved_tree->_right = new_tree;
                //avl_rotations(tree, new_tree);
                wrapper(*tree, new_tree);
                saved_tree = NULL;
            }
            else 
                saved_tree = saved_tree->_right;
        else if (value == saved_tree->_val)
        {
            printf("Node already exists.");
            saved_tree = NULL;
        }
    }
}

AVLTree* avl_new(int value) {
    AVLTree* tree = malloc(sizeof(AVLTree));
    *tree = (AVLTree) {
        ._val  = value
    };
    return tree;
}
