#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"
#include "list_BinTreeNode.h"

BinTreeNode* listBinTreeNode_Allocate(void)
{
    listBinTreeNode = (BinTreeNode*) malloc(LISTBINTREENODE_MAXNODES * sizeof(BinTreeNode));
    listBinTreeNode_size = 0;
    return listBinTreeNode;
}

int listBinTreeNode_Find(int key)
{
    PRINT_DBG("listBinTreeNode_Find: key = %d, current size = %d\n", key, listBinTreeNode_size);
    int i, found;
    found = 0;
    for (i = 0; i < listBinTreeNode_size; ++i)
    {
        if (listBinTreeNode[i] && listBinTreeNode[i]->key == key)
        {
            found = 1;
            PRINT_DBG("listBinTreeNode_Find: found key = %d, position %d\n", key, i);
            break;
        }
    }
    if (found)
        return i;
    else
        return -1;
}

int listBinTreeNode_Add(BinTreeNode n)
{
    PRINT_DBG("listBinTreeNode_Add: n = %p\n", n);
    if (!n)
    {
        PRINT_DBG("listBinTreeNode_Add: n is NULL. Exiting.");
        return -1;
    }
    PRINT_DBG("listBinTreeNode_Add: n->key = %d\n", n->key);
    int pos;
    if ((pos = listBinTreeNode_Find(n->key)) > 0)
    {
        PRINT_DBG("listBinTreeNode_Add: key %d found at position %d. Returning.\n", n->key, pos);
        return -1;
    }
    listBinTreeNode[listBinTreeNode_size++] = n;
    PRINT_DBG("listBinTreeNode_Add: added key %d to position %d. New size is %d\n", n->key, listBinTreeNode_size - 1,
        listBinTreeNode_size);
    return listBinTreeNode_size;
}

int listBinTreeNode_Remove(int key)
{
    PRINT_DBG("listBinTreeNode_Remove: key = %d\n", key);
    int pos;
    if ((pos = listBinTreeNode_Find(key)) == -1)
    {
        PRINT_DBG("listBinTreeNode_Remove: key %d not found. Returning\n", key);
        return -1;
    }
    listBinTreeNode[pos] = listBinTreeNode[listBinTreeNode_size - 1];
    --listBinTreeNode_size;
    PRINT_DBG("listBinTreeNode_Remove: Removed element at position %d\n", pos);
    return listBinTreeNode_size;
}

int listBinTreeNode_cmp(const void* a, const void* b)
{
    return ((*(BinTreeNode*)a)->key - (*(BinTreeNode*)b)->key);
}