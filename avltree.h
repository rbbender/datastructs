//
// Created by rbbender on 9/11/16.
//

#ifndef DATASTRUCTS_AVLTREE_H
#define DATASTRUCTS_AVLTREE_H

struct avltree_node
{
    int key;
    void* value;
    struct avltree_node* parent;
    struct avltree_node* left_child;
    struct avltree_node* right_child;
    char* repr;
    int size;
};

typedef struct avltree_node* AVLTreeNode;

struct avl_tree
{
    int size;
    AVLTreeNode root;
};

typedef struct avl_tree* AVLTree;

AVLTreeNode AVLTreeNode_Init(int, void*);
AVLTreeNode AVLTreeNode_Insert(AVLTreeNode, AVLTreeNode);
int AVLTreeNode_AdjustSize(AVLTreeNode);


#endif //DATASTRUCTS_AVLTREE_H
