#ifndef LIST_AVLTREENODE_H
#define LIST_AVLTREENODE_H
#define LISTAVLTREENODE_MAXNODES 300000

AVLTreeNode* listAVLTreeNode;

int listAVLTreeNode_size;

AVLTreeNode* listAVLTreeNode_Allocate(void);
int listAVLTreeNode_Add(AVLTreeNode);
int listAVLTreeNode_Find(int);
int listAVLTreeNode_Remove(int);
int listAVLTreeNode_cmp(const void*, const void*);

#endif