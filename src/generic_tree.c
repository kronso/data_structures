#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// #include <string.h>
#include "../include/list.h"

#include "../include/generic_tree.h"

/*
 *  Commented out code is code that is incomplete!
 *                      :(
 */

static void _tree_traverse(Tree* tree) {
    Tree* node; 
    for (size_t i = 0; i < vec_size(tree->_children); i++) {
        node = vec_at(tree->_children, i);
        // pre-order traversal
        printf("%d ", node->_val);
        if (!vec_empty(node->_children))
        {
            _tree_traverse(node);
            // post-order traversal
            //  printf("%d ", node->_val);
        }
    }
}
void tree_traverse(Tree* tree) {
    printf("%d ", tree->_val);
    _tree_traverse(tree);
    printf("\n");
}

static void _tree_node_count(Tree* tree, unsigned* count) {
    Tree* node;
    for (size_t i = 0; i < vec_size(tree->_children); i++) {
        node = vec_at(tree->_children, i);
        (*count)++;
        if (!vec_empty(node->_children))
            _tree_node_count(node, count);
    }
}
void tree_node_count(Tree* tree, unsigned* count) {
    (*count)++;
    _tree_node_count(tree, count);
}


// static unsigned _tree_depth(Tree* tree, unsigned* count) {
//     Tree* node;
//     for (size_t i = 0; i < vec_size(tree->_children); i++) {
//         node = vec_at(tree->_children, i);
//         if (!vec_empty(node->_children)) 
//         {
//             _tree_depth(node, count);
//             (*count)++;
//         }
//     }
// }
// void tree_depth(Tree* tree, unsigned* count) {
//     _tree_depth(tree, count);
// }

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

void tree_add(Tree* tree, int val, unsigned depth, ...) {
    Tree* new_tree = tree_new(val);
    
    List* positions = list_new();
    unsigned* temp[depth + 1];

    va_list args;
    va_start(args, depth);
    for (unsigned i = 0; i < depth + 1; i++) {
        temp[i] = malloc(sizeof(unsigned));
        *(temp[i]) = (!i) ? i: va_arg(args, unsigned);
        list_push_back(positions, temp[i]);
    }
    va_end(args);

    Tree* available = tree_availability(tree, positions);
    if (!available)
        printf("Node position is unavailable\n");
    else 
         vec_push_back(available->_children, new_tree);
    // Free malloc shit
    list_destroy(positions);
    for (unsigned i = 0; i < depth + 1; i++)
        free(temp[i]);
}
void tree_clear(Tree* tree) {
    while (vec_size(tree->_children)) {
        Tree* node = vec_at(tree->_children, 0);
        if (!vec_empty(node->_children))
            tree_clear(node);

        // Free more shit
        vec_destroy(node->_children);
        free(vec_front(tree->_children));
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
    unsigned* temp[depth + 1];

    va_list args;
    va_start(args, depth);
    for (unsigned i = 0; i < depth + 1; i++) {
        temp[i] = malloc(sizeof(unsigned));
        *(temp[i])= (!i) ? i: va_arg(args, unsigned);
        list_push_back(positions, temp[i]);
    }
    va_end(args);

    Tree* node = (list_size(positions) == 1) ? tree: tree_node_availability(tree, positions); 
    if (node)
        tree_clear(node);
    else
        printf("Node positions doesn't exist.\n");
    // Free malloc
    list_destroy(positions);
    for (unsigned i = 0; i < depth + 1; i++)
        free(temp[i]);
}

void tree_graft(Tree* src, Tree* dst, unsigned depth, ...) {
    List* positions = list_new();
    unsigned* temp[depth + 1];

    va_list args;
    va_start(args, depth);
    for (unsigned i = 0; i < depth + 1; i++) {
        temp[i] = malloc(sizeof(unsigned));
        *(temp[i])= (!i) ? i: va_arg(args, unsigned);
        list_push_back(positions, temp[i]);
    }
    va_end(args);

    Tree* node = (list_size(positions) == 1) ? dst: tree_node_availability(dst, positions);  
    if (node)
        vec_push_back(node->_children, src);
    else
        printf("Node positions doesn't exist\n");

    list_destroy(positions);
    for (unsigned i = 0; i < depth + 1; i++)
        free(temp[i]);
}
Tree* tree_node_search(Tree* tree, unsigned depth, ...) {
    List* positions = list_new();
    unsigned* temp[depth + 1];

    va_list args;
    va_start(args, depth);
    for (unsigned i = 0; i < depth + 1; i++) {
        temp[i] = malloc(sizeof(unsigned));
        *(temp[i])= (!i) ? i: va_arg(args, unsigned);
        list_push_back(positions, temp[i]);
    }
    va_end(args);

    Tree* node = (list_size(positions) == 1) ? tree: tree_node_availability(tree, positions);

    list_destroy(positions);
    for (unsigned i = 0; i < depth + 1; i++)
        free(temp[i]);
    return node;
}

// static Tree* tree_parent(Tree* tree, Tree* node) {
//     Tree* parent;
//     for (size_t i = 0; i < vec_size(tree->_children); i++){
//         parent = vec_at(tree->_children, i);
// 
//          if (parent == node) 
//               return tree;
// 
//         if (!vec_empty(parent->_children))
//         {
//             for (size_t j = 0; j < vec_size(parent->_children); j++) 
//             {
//                 if (vec_at(parent->_children, j) == node) 
//                     return vec_at(tree->_children, i);
//             }
//             tree_parent(parent, node);
//         }
// 
//     }
// }
// Tree* _tree_LCA(Tree* tree, Tree* parent1, Tree* parent2) {
//     Tree* node;
//     static unsigned par1, par2 = 0;
//     for (size_t i = 0; i < vec_size(tree->_children); i++) {
//         node = vec_at(tree->_children, i);
//         if (!vec_empty(node->_children))
//         {
//             // if (node == parent1 || node == parent2)
//               //  return node;
//             _tree_LCA(node, parent1, parent2);
//             if (node == parent1) {
//                 par1 = 1;
//             }
//             if (node == parent2) {
//                 par2 = 1;
//             }
//             if (par1 && par2)
//                 return node;
//             //if (node == parent1 || node == parent2)
//             //    return node;
//         }
//         par1 = par2 = 0;
// 
//     } 
// }
// Tree* tree_LCA(Tree* tree, Tree* node1, Tree* node2) {
//     Tree* parent1 = tree_parent(tree, node1);
//     Tree* parent2 = tree_parent(tree, node2);
//     
//    // tree_traverse(tree);
//    return _tree_LCA(tree, parent1, parent2);
// }

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
