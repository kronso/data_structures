#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// #include <string.h>
#include "../include/list.h"

#include "../include/tree.h"

void tree_traverse(Tree* tree) {
    Tree* node;
    for (size_t i = 0; i < vec_size(tree->_children); i++) {
        node = vec_at(tree->_children, i);
        // pre-order traversal
        printf("%d ", node->_val);
        if (!vec_empty(node->_children))
        {
            tree_traverse(node);
            // post-order traversal
            //  printf("%d ", node->_val);
        }
    }
}

static Tree* tree_availability(Tree* tree, List* positions) {
    list_pop_front(positions);
    if (vec_empty(tree->_children))
    {
        if (list_empty(positions))
        {
            return tree;
        }
        return NULL; // nodes given do not exist.
    }
    else if (list_empty(positions))
    {
        return tree;
    }
   tree_availability(vec_at(tree->_children, *(int *)list_front(positions)), positions);
}

void tree_add(Tree* tree, unsigned depth, int val, ...) {
    Tree* new_tree = tree_new(val);
    
    List* positions = list_new();
    unsigned *pos[depth];

    va_list args;
    va_start(args, depth);
    for (unsigned i = 0; i < depth; i++) {
        pos[i] = malloc(sizeof(unsigned));
        *(pos[i]) = va_arg(args, unsigned);
        list_push_back(positions, pos[i]);
    }
    va_end(args);

    Tree* available = tree_availability(tree, positions);
    if (!available)
        printf("Node position is unavailable\n");
    else 
         vec_push_back(available->_children, new_tree);

    // Free malloc shit
    list_destroy(positions);
    for (unsigned i = 0; i < depth; i++)
        free(pos[i]);
}
void tree_clear(Tree* tree) {
    while (vec_size(tree->_children)) {
        Tree* node = vec_at(tree->_children, 0);
        if (!vec_empty(node->_children)) {
            tree_clear(node);
        }
        // vec_destroy(node->_children);
        // free(vec_at(tree->_children, i));
        vec_erase(tree->_children, 0);
    }
}
static Tree* tree_node_availability(Tree* tree, List* positions) {
    list_pop_front(positions);
    if (vec_empty(tree->_children)) {
        if (list_size(positions) == 1) {
            return vec_at(tree->_children, *(int *)list_front(positions));
        }
        return NULL;
    }
    else if (list_size(positions) == 1) 
    {
        return vec_at(tree->_children, *(int *)list_front(positions));
    }
    tree_node_availability(vec_at(tree->_children, *(int *)list_front(positions)), positions);
}
void tree_prune(Tree* tree, unsigned depth, ...) {    
    List* positions = list_new();
    unsigned *pos[depth];

    va_list args;
    va_start(args, depth);
    for (unsigned i = 0; i < depth; i++) {
        pos[i] = malloc(sizeof(unsigned));
        *(pos[i]) = va_arg(args, unsigned);
        list_push_back(positions, pos[i]);
    }
    va_end(args);

    Tree* node = tree_node_availability(tree, positions); 
    if (node)
        tree_clear(node);
    else
        printf("Node positions doesn't exist.\n");

    // Free malloc
    list_destroy(positions);
    for (unsigned i = 0; i < depth; i++)
        free(pos[i]);
}



Tree* tree_new(int root) {
    Tree* tree = malloc(sizeof(Tree));
    *tree = (Tree) {
        ._val  = root,
        ._children = vec_new()
    };
    return tree;
}
void tree_destroy(Tree* tree) {
    tree_clear(tree);
    vec_destroy(tree->_children);
    free(tree);
    tree = NULL;
}
