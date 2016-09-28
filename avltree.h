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
    int height;
};

typedef struct avltree_node* AVLTreeNode;

struct avl_tree
{
    int size;
    AVLTreeNode root;
};

typedef struct avl_tree* AVLTree;

char* AVLTreeNode_Repr(AVLTreeNode);
int AVLTreeNode_Print(AVLTreeNode);
int AVLTreeNode_PrintLink(AVLTreeNode, AVLTreeNode);
AVLTreeNode AVLTreeNode_Init(int, void*);
int AVLTreeNode_Destroy(AVLTreeNode);
int AVLTreeNode_DestroyGracefully(AVLTreeNode);
int AVLTreeNode_SetParent(AVLTreeNode, AVLTreeNode);
int AVLTreeNode_SetLeftChild(AVLTreeNode, AVLTreeNode);
int AVLTreeNode_SetRightChild(AVLTreeNode, AVLTreeNode);
int AVLTreeNode_IsLeftChild(AVLTreeNode);
int AVLTreeNode_IsRightChild(AVLTreeNode);
int AVLTreeNode_PrintSubTree(AVLTreeNode, int);
AVLTreeNode AVLTreeNode_LeftAncestor(AVLTreeNode);
AVLTreeNode AVLTreeNode_RightDescendant(AVLTreeNode);
AVLTreeNode AVLTreeNode_RightAncestor(AVLTreeNode);
AVLTreeNode AVLTreeNode_LeftDescendant(AVLTreeNode);
AVLTreeNode AVLTreeNode_Prev(AVLTreeNode);
AVLTreeNode AVLTreeNode_Next(AVLTreeNode);
AVLTreeNode AVLTreeNode_Insert(AVLTreeNode, AVLTreeNode);
void AVLTreeNode_PrintInOrder(AVLTreeNode);
int AVLTreeNode_SetValue(AVLTreeNode, void*);
int AVLTreeNode_RotateLeft(AVLTreeNode);
int AVLTreeNode_RotateRight(AVLTreeNode);
int AVLTreeNode_AdjustHeight(AVLTreeNode);
AVLTreeNode AVLTreeNode_Remove(AVLTreeNode);
AVLTreeNode AVLTreeNode_Find(AVLTreeNode, int);
int AVLTreeNode_RebalanceLeft(AVLTreeNode);
int AVLTreeNode_RebalanceRight(AVLTreeNode);
int AVLTreeNode_Rebalance(AVLTreeNode);
int AVLTreeNode_GetHeight(AVLTreeNode);
AVLTreeNode AVLTreeNode_FindRoot(AVLTreeNode);


AVLTree AVLTree_Init(void);
int AVLTree_Destroy(AVLTree tree);
void* AVLTree_Find(AVLTree tree, int key);
int AVLTree_Insert(AVLTree tree, int key, void* value);
int AVLTree_Remove(AVLTree tree, int key);
int AVLTree_PrintSubTree(AVLTree tree, int key, int levels);
void AVLTree_PrintRange(AVLTree, int, int);

#endif //DATASTRUCTS_AVLTREE_H
