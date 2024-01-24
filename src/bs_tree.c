#include <stdlib.h>
#include <stdio.h>

#include "../include/bs_tree.h"

// inorder traversal
void bstree_traverse(BSTree* bstree) {
    if (bstree) 
    {
        bstree_traverse(bstree->_left);
        printf("%d ", *(int *)bstree->_val);
        bstree_traverse(bstree->_right);
    }
}
BSTree* bstree_search(BSTree* tree, void* value) {

    while (tree)
    {
        if (value < tree->_val) 
            tree = tree->_left;
        else if (value > tree->_val)
            tree = tree->_right;
        else if (value == tree->_val)
            return tree;
    }
    return NULL;
}
void bstree_insert(BSTree* tree, void* value) {
    BSTree* new_tree = bstree_new(value);
    
    while (tree) 
    {
        if (value < tree->_val) 
            if (tree->_left == NULL)
            {
                tree->_left = new_tree;
                tree = NULL;
            }
            else 
                tree = tree->_left;
        else if (value > tree->_val)
            if (tree->_right == NULL) 
            { 
                tree->_right = new_tree;
                tree = NULL;
            }
            else 
                tree = tree->_right;
        else if (value == tree->_val)
        {
            printf("Node already exists.");
            tree = NULL;
        }
    }
}

BSTree* bstree_parent(BSTree* tree, void* value) {
    BSTree* parent = tree;
    while (tree)
    {
        if (value < tree->_val) 
        {
            parent = tree;
            tree = tree->_left;
        }
        else if (value > tree->_val)
        {
            parent = tree;
            tree = tree->_right;
        }
        else if (value == tree->_val)
            return parent;

    }
    return NULL;
}   
BSTree* _bstree_find_min(BSTree* tree) {
    if (tree) 
    {
        if (!tree->_left)
            return tree;
        _bstree_find_min(tree->_left);
        _bstree_find_min(tree->_right);
    }
}
void bstree_delete(BSTree* tree, void* value) {
    BSTree* parent = NULL;
    while (tree)
    {
        if (value < tree->_val) 
        {
            parent = tree;
            tree = tree->_left;
        }
        else if (value > tree->_val)
        {
            parent = tree;
            tree = tree->_right;
        }
        else if (value == tree->_val)
        {
            if (!tree->_left && !tree->_right)
            {
                parent->_left  = (parent->_left  == tree) ?  NULL: parent->_left;
                parent->_right = (parent->_right == tree) ?  NULL: parent->_right;
                free(tree);
            }                
            else if (tree->_left && !tree->_right) 
            {
                parent->_left  = (parent->_left  == tree) ? tree->_left: parent->_left;
                parent->_right = (parent->_right == tree) ? tree->_left: parent->_right;
                free(tree);
            }
            else if (!tree->_left && tree->_right)
            {
                parent->_left  = (parent->_left  == tree) ? tree->_right: parent->_left;
                parent->_right = (parent->_right == tree) ? tree->_right: parent->_right;
                free(tree);
            }
            else 
            {
                    BSTree* Y = _bstree_find_min(tree->_right);
                    BSTree* Y_parent = bstree_parent(tree, Y->_val);
                    
                    Y->_left = tree->_left;
                    Y_parent->_left  = (Y_parent->_left  == Y) ? Y->_right:  Y_parent->_left; 
                    Y_parent->_right = (Y_parent->_right == Y) ? Y->_right: Y_parent->_right; 
                    tree->_val = Y->_val;

                    free(Y);
                    Y = NULL;
            }
            tree = NULL;
        }
    }
}
BSTree* bstree_new(void* value) {
    BSTree* tree = malloc(sizeof(BSTree));
    *tree = (BSTree) {
        ._val = value
    };
    return tree;
}
void bstree_destroy(BSTree* tree) {
    if (tree) 
    {
        bstree_destroy(tree->_left);
        bstree_destroy(tree->_right);
        free(tree);
        tree = NULL;
    }
}
