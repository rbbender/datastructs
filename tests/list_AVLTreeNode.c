#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "avltree.h"
#include "list_AVLTreeNode.h"

AVLTreeNode* listAVLTreeNode_Allocate(void)
{
    listAVLTreeNode = (AVLTreeNode*) malloc(LISTAVLTREENODE_MAXNODES * sizeof(AVLTreeNode));
    listAVLTreeNode_size = 0;
    return listAVLTreeNode;
}

int listAVLTreeNode_Find(int key)
{
    PRINT_DBG("listAVLTreeNode_Find: key = %d, current size = %d\n", key, listAVLTreeNode_size);
    int i, found;
    found = 0;
    for (i = 0; i < listAVLTreeNode_size; ++i)
    {
        if (listAVLTreeNode[i] && listAVLTreeNode[i]->key == key)
        {
            found = 1;
            PRINT_DBG("listAVLTreeNode_Find: found key = %d, position %d\n", key, i);
            break;
        }
    }
    if (found)
        return i;
    else
        return -1;
}

int listAVLTreeNode_Add(AVLTreeNode n)
{
    PRINT_DBG("listAVLTreeNode_Add: n = %p\n", n);
    if (!n)
    {
        PRINT_DBG("listAVLTreeNode_Add: n is NULL. Exiting.");
        return -1;
    }
    PRINT_DBG("listAVLTreeNode_Add: n->key = %d\n", n->key);
    int pos;
    if ((pos = listAVLTreeNode_Find(n->key)) > 0)
    {
        PRINT_DBG("listAVLTreeNode_Add: key %d found at position %d. Returning.\n", n->key, pos);
        return -1;
    }
    listAVLTreeNode[listAVLTreeNode_size++] = n;
    PRINT_DBG("listAVLTreeNode_Add: added key %d to position %d. New size is %d\n", n->key, listAVLTreeNode_size - 1,
        listAVLTreeNode_size);
    return listAVLTreeNode_size;
}

int listAVLTreeNode_Remove(int key)
{
    PRINT_DBG("listAVLTreeNode_Remove: key = %d\n", key);
    int pos;
    if ((pos = listAVLTreeNode_Find(key)) == -1)
    {
        PRINT_DBG("listAVLTreeNode_Remove: key %d not found. Returning\n", key);
        return -1;
    }
    listAVLTreeNode[pos] = listAVLTreeNode[listAVLTreeNode_size - 1];
    --listAVLTreeNode_size;
    PRINT_DBG("listAVLTreeNode_Remove: Removed element at position %d\n", pos);
    return listAVLTreeNode_size;
}

int listAVLTreeNode_cmp(const void* a, const void* b)
{
    return ((*(AVLTreeNode*)a)->key - (*(AVLTreeNode*)b)->key);
}