//
// Created by rbbender on 9/11/16.
//
#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"
#include "avltree.h"

char* AVLTreeNode_Repr(AVLTreeNode node)
{
    return BinTreeNode_Repr((BinTreeNode) node);
}

int AVLTreeNode_Print(AVLTreeNode node)
{
    return BinTreeNode_Print((BinTreeNode) node);
}

int AVLTreeNode_PrintLink(AVLTreeNode node1, AVLTreeNode node2)
{
    return BinTreeNode_PrintLink((BinTreeNode) node1, (BinTreeNode) node2);
}



AVLTreeNode AVLTreeNode_Init(int key, void* value)
{
    AVLTreeNode res = (AVLTreeNode) malloc(sizeof(struct avltree_node));
    BinTreeNode_Init(key, value, (BinTreeNode) res);
    res->height = 1;
    return res;
}

AVLTreeNode AVLTreeNode_Insert(AVLTreeNode root, AVLTreeNode node)
{
    AVLTreeNode res;
    res = (AVLTreeNode) BinTreeNode_Insert((BinTreeNode) root, (BinTreeNode) node);
    AVLTreeNode_Rebalance(res);
    return res;
}

int AVLTreeNode_Destroy(AVLTreeNode node)
{
    return BinTreeNode_Destroy((BinTreeNode) node);
}

int AVLTreeNode_DestroyGracefully(AVLTreeNode node)
{
    return BinTreeNode_DestroyGracefully((BinTreeNode) node);
}

int AVLTreeNode_SetParent(AVLTreeNode parent, AVLTreeNode child)
{
    return BinTreeNode_SetParent((BinTreeNode) parent, (BinTreeNode) child);
}

int AVLTreeNode_SetLeftChild(AVLTreeNode parent, AVLTreeNode lchild)
{
    return BinTreeNode_SetLeftChild((BinTreeNode) parent, (BinTreeNode) lchild);
}

int AVLTreeNode_SetRightChild(AVLTreeNode parent, AVLTreeNode rchild)
{
    return BinTreeNode_SetRightChild((BinTreeNode) parent, (BinTreeNode) rchild);
}

int AVLTreeNode_IsLeftChild(AVLTreeNode node)
{
    return BinTreeNode_IsLeftChild((BinTreeNode) node);
}

int AVLTreeNode_IsRightChild(AVLTreeNode node)
{
    return BinTreeNode_IsRightChild((BinTreeNode) node);
}

int AVLTreeNode_PrintSubTree(AVLTreeNode root, int level_limit)
{
    return BinTreeNode_PrintSubTree((BinTreeNode) root, level_limit);
}
AVLTreeNode AVLTreeNode_Prev(AVLTreeNode node)
{
    return (AVLTreeNode) BinTreeNode_Prev((BinTreeNode) node);
}

AVLTreeNode AVLTreeNode_Next(AVLTreeNode node)
{
    return (AVLTreeNode) BinTreeNode_Next((BinTreeNode) node);
}

int AVLTreeNode_AdjustHeight(AVLTreeNode node)
{
    int size, l_size, r_size;
    size = 1;
    if (!node)
    {
        PRINT_DBG("AVLTreeNode_AdjustHeight: node is NULL\n");
        return 0;
    }
    if (!node->left_child)
        l_size = 0;
    else
        l_size = node->left_child->height;
    if (!node->right_child)
        r_size = 0;
    else
        r_size = node->right_child->height;
    node->height = (size + ((l_size > r_size) ? l_size : r_size));
    AVLTreeNode_AdjustHeight(node->parent);
    return node->height;
}

AVLTreeNode AVLTreeNode_Remove(AVLTreeNode node)
{
    AVLTreeNode res;
    res = (AVLTreeNode) BinTreeNode_Remove((BinTreeNode) node);
    AVLTreeNode_Rebalance(res);
    return res;
}

AVLTreeNode AVLTreeNode_Find(AVLTreeNode root, int key)
{
    return (AVLTreeNode) BinTreeNode_Find((BinTreeNode) root, key);
}

int AVLTreeNode_RotateLeft(AVLTreeNode node)
{
    int res = BinTreeNode_RotateLeft((BinTreeNode) node);
    AVLTreeNode_AdjustHeight(node);
    return res;
}

int AVLTreeNode_RotateRight(AVLTreeNode node)
{
    int res = BinTreeNode_RotateRight((BinTreeNode) node);
    AVLTreeNode_AdjustHeight(node);
    return res;
}

int AVLTreeNode_GetHeight(AVLTreeNode node)
{
    PRINT_DBG("AVLTreeNode_GetHeight: node = %s\n", AVLTreeNode_Repr(node));
    int res = 0;
    if (node)
        res = node->height;
    PRINT_DBG("AVLTreeNode_GetHeight: %d\n", res);
    return res;
}

int AVLTreeNode_RebalanceLeft(AVLTreeNode node) {
    PRINT_DBG("AVLTreeNode_RebalanceLeft: node = %s\n", AVLTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("AVLTreeNode_RebalanceLeft: node is NULL\n");
        return -1;
    }
    AVLTreeNode rchild = node->right_child;
    if (rchild && AVLTreeNode_GetHeight(rchild->left_child) > AVLTreeNode_GetHeight(rchild->right_child))
        AVLTreeNode_RotateRight(rchild);
    return AVLTreeNode_RotateLeft(node);

}

int AVLTreeNode_RebalanceRight(AVLTreeNode node) {
    PRINT_DBG("AVLTreeNode_RebalanceRight: node = %s\n", AVLTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("AVLTreeNode_RebalanceRight: node is NULL\n");
        return -1;
    }
    AVLTreeNode lchild = node->left_child;
    if (lchild && AVLTreeNode_GetHeight(lchild->left_child) < AVLTreeNode_GetHeight(lchild->right_child))
        AVLTreeNode_RotateLeft(lchild);
    return AVLTreeNode_RotateRight(node);
}

int AVLTreeNode_Rebalance(AVLTreeNode node) {
    PRINT_DBG("AVLTreeNode_Rebalance: node = %s\n", AVLTreeNode_Repr(node));
    if (!node)
    {
        PRINT_DBG("AVLTreeNode_Rebalance: node is NULL\n");
        return -1;
    }
    AVLTreeNode p = node->parent;
    if (AVLTreeNode_GetHeight(node->left_child) > AVLTreeNode_GetHeight(node->right_child) + 1)
        AVLTreeNode_RebalanceRight(node);
    else if (AVLTreeNode_GetHeight(node->right_child) > AVLTreeNode_GetHeight(node->left_child) + 1)
        AVLTreeNode_RebalanceLeft(node);
    AVLTreeNode_AdjustHeight(node);
    AVLTreeNode_Rebalance(node->parent);
    return AVLTreeNode_GetHeight(node);
}


AVLTree AVLTree_Init(void) {
    AVLTree res = (AVLTree) malloc(sizeof(struct avl_tree));
    res->size = 0;
    res->root = NULL;
    return res;
}

int AVLTree_Destroy(AVLTree tree)
{
    PRINT_DBG("AVLTree_Destroy: destroying AVLTree at %p\n", tree);
    if (!tree)
    {
        PRINT_DBG("AVLTree_Destroy: Tree is NULL\n");
        return -1;
    }
    AVLTreeNode_DestroyGracefully(tree->root);
    free(tree);
    PRINT_DBG("AVLTree_Destroy: Tree destroyed\n");
    return 0;
}

void* AVLTree_Find(AVLTree tree, int key)
{
    return BinTree_Find((BinTree) tree, key);
}

int AVLTree_Insert(AVLTree tree, int key, void* value)
{
    AVLTreeNode n = AVLTreeNode_Find(tree->root, key);
    if (n && n-> key == key)
    {
        PRINT_DBG("AVLTree_Insert: Tree %p, key %d already exists\n", tree, key);
        return -1;
    }
    AVLTreeNode newNode = AVLTreeNode_Init(key, value);
    AVLTreeNode_Insert(tree->root, newNode);
    if (!tree->root)
        tree->root = newNode;
    ++(tree->size);
    return 0;
}

int AVLTree_Remove(AVLTree tree, int key)
{
    AVLTreeNode node, next;
    node = AVLTreeNode_Find(tree->root, key);
    if (!node || node->key != key)
    {
        PRINT_DBG("AVLTree_Remove: node not found\n");
        return -1;
    }
    PRINT_DBG("AVLTree_Remove: node = %s\n", AVLTreeNode_Repr(node));
    next = AVLTreeNode_Remove(node);
    if (node == tree->root)
        tree->root = next;
    --(tree->size);
    if (!tree->size)
        tree->root = NULL;
    AVLTreeNode_Destroy(node);
    return 0;
}

int AVLTree_PrintSubTree(AVLTree tree, int key, int levels)
{
    return BinTree_PrintSubTree((BinTree) tree, key, levels);
}
