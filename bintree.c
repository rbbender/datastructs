#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"

BinTreeNode BinTreeNode_Init(int key, void* val_p)
{
    PRINT_DBG("BinTreeNode_Init: START: key = %d, val_p = %p\n", key, val_p);
    BinTreeNode res = (BinTreeNode) malloc(sizeof(struct bintree_node));
    res->key = key;
    res->value = val_p;
    res->parent = res->left_child = res->right_child = NULL;
    res->repr = (char*) malloc(DS_BINTREE_MAXREPR * sizeof(char));
    sprintf(res->repr, "%d: ", res->key);
    PRINT_DBG("BinTreeNode_Init: END: %s created\n", res->repr);
    return res;
}

int BinTreeNode_Destroy(BinTreeNode n)
{
    if (!n)
    {
        PRINT_DBG("BinTreeNode_Destroy: Called over NULL pointer\n");
        return -1;
    }
    PRINT_DBG("BinTreeNode_Destroy: START: %s\n", n->repr);
    free(n->repr);
    free(n);
    PRINT_DBG("BinTreeNode_Destroy: END: destroyed\n");
    return 0;
}
