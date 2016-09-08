#ifndef DS_BINTREE
#define DS_BINTREE

#define DS_BINTREE_MAXREPR 64
struct bintree_node
{
    int key;
    void* value;
    struct tree_node* parent;
    struct tree_node* left_child;
    struct tree_node* right_child;
    char* repr;
};

typedef struct bintree_node* BinTreeNode;

struct bin_tree
{
    int size;
    BinTreeNode root;
};

typedef struct bin_tree* BinTree;
BinTreeNode BinTreeNode_Init(int, void*);
int BinTreeNode_Destroy(BinTreeNode);
int BinTreeNode_SetParent(BinTreeNode, BinTreeNode);
int BinTreeNode_SetLeftChild(BinTreeNode, BinTreeNode);
int BinTreeNode_SetRightChild(BinTreeNode, BinTreeNode);
BinTreeNode BinTreeNode_Find(int);
int BinTreeNode_SetValue(BinTreeNode, void*);

BinTree BinTree_Init(void);
int BinTree_Destroy(BinTree);
void* BinTree_Find(int);
int BinTree_Insert(int, void*);
int BinTree_Remove(int);
int BinTree_SetValue(int, void*);
#endif