#ifndef DATASTRUCTS_BINTREE_H
#define DATASTRUCTS_BINTREE_H

#define DS_BINTREE_MAXREPR 64

struct bintree_node
{
    int key;
    void* value;
    struct bintree_node* parent;
    struct bintree_node* left_child;
    struct bintree_node* right_child;
    char* repr;
};

typedef struct bintree_node* BinTreeNode;

struct bin_tree
{
    int size;
    BinTreeNode root;
};

typedef struct bin_tree* BinTree;
char* BinTreeNode_Repr(BinTreeNode);
int BinTreeNode_Print(BinTreeNode);
int BinTreeNode_PrintLink(BinTreeNode, BinTreeNode);
BinTreeNode BinTreeNode_Init(int, void*, BinTreeNode);
int BinTreeNode_Destroy(BinTreeNode);
int BinTreeNode_DestroyGracefully(BinTreeNode);
int BinTreeNode_SetParent(BinTreeNode, BinTreeNode);
int BinTreeNode_SetLeftChild(BinTreeNode, BinTreeNode);
int BinTreeNode_SetRightChild(BinTreeNode, BinTreeNode);
int BinTreeNode_IsLeftChild(BinTreeNode);
int BinTreeNode_IsRightChild(BinTreeNode);
int BinTreeNode_PrintSubTree(BinTreeNode, int);
BinTreeNode BinTreeNode_LeftAncestor(BinTreeNode);
BinTreeNode BinTreeNode_RightDescendant(BinTreeNode);
BinTreeNode BinTreeNode_RightAncestor(BinTreeNode);
BinTreeNode BinTreeNode_LeftDescendant(BinTreeNode);
BinTreeNode BinTreeNode_Prev(BinTreeNode);
BinTreeNode BinTreeNode_Next(BinTreeNode);
BinTreeNode BinTreeNode_Find(BinTreeNode, int);
BinTreeNode BinTreeNode_Insert(BinTreeNode, BinTreeNode);
BinTreeNode BinTreeNode_Remove(BinTreeNode);
void BinTreeNode_PrintInOrder(BinTreeNode);
int BinTreeNode_SetValue(BinTreeNode, void*);
int BinTreeNode_RotateLeft(BinTreeNode);
int BinTreeNode_RotateRight(BinTreeNode);
BinTreeNode BinTreeNode_FindRoot(BinTreeNode);

BinTree BinTree_Init(void);
int BinTree_Destroy(BinTree);
void* BinTree_Find(BinTree, int);
int BinTree_Insert(BinTree, int, void*);
int BinTree_Remove(BinTree, int);
int BinTree_SetValue(BinTree, int, void*);
int BinTree_PrintInOrder(BinTree);
int BinTree_PrintSubTree(BinTree, int, int);
void BinTree_PrintRange(BinTree, int, int);
#endif