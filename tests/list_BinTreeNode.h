#ifndef LIST_BINTREENODE_H
#define LIST_BINTREENODE_H
#define LISTBINTREENODE_MAXNODES 300000

BinTreeNode* listBinTreeNode;

int listBinTreeNode_size;

BinTreeNode* listBinTreeNode_Allocate(void);
int listBinTreeNode_Add(BinTreeNode);
int listBinTreeNode_Find(int);
int listBinTreeNode_Remove(int);
int listBinTreeNode_cmp(const void*, const void*);

#endif