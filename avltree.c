//
// Created by rbbender on 9/11/16.
//
#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"
#include "avltree.h"

AVLTreeNode AVLTreeNode_Init(int key, void* value)
{
    AVLTreeNode res = (AVLTreeNode) malloc(sizeof(struct avltree_node));
    BinTreeNode_Init(key, value, (BinTreeNode) res);
    res->size = 0;
    return res;
}

AVLTreeNode AVLTreeNode_Insert(AVLTreeNode root, AVLTreeNode node)
{
    AVLTreeNode res;
    res = (AVLTreeNode) BinTreeNode_Insert((BinTreeNode) root, (BinTreeNode) node);
    AVLTreeNode_AdjustSize(res);
    return res;
}

int AVLTreeNode_AdjustSize(AVLTreeNode node)
{
    int size, l_size, r_size;
    size = 0;
    if (!node)
    {
        PRINT_DBG("AVLTreeNode_AdjustSize: node is NULL\n");
        return 0;
    }
    if (node->left_child || node->right_child)
        size = 1;
    if (!node->left_child)
        l_size = 0;
    else
        l_size = node->left_child->size;
    if (!node->right_child)
        r_size = 0;
    else
        r_size = node->right_child->size;
    node->size = (size + ((l_size > r_size) ? l_size : r_size));
    AVLTreeNode_AdjustSize(node->parent);
    return node->size;
}

