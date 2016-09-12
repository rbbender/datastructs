#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"
#include "avltree.h"


int main(void)
{
    init_log(DS_VERBOSITY_DBG);
    fopen_log("debug.log");
    void* val;
    int res;
    BinTreeNode temp;
    BinTree tree = BinTree_Init();
    BinTree_Insert(tree, 2, (void*) "node2");
    BinTree_Insert(tree, 3, (void*) "node3");
    BinTree_Insert(tree, 1, (void*) "node1");
    BinTree_PrintInOrder(tree);
    val = BinTree_Find(tree, 4);
    PRINT("\tFind 4 result = %s\n", (char*) val);
    val = BinTree_Find(tree, 3);
    PRINT("\tFind 3 result = %s\n", (char*) val);
    val = BinTree_Find(tree, 2);
    PRINT("\tFind 2 result = %s\n", (char*) val);
    val = BinTree_Find(tree, 1);
    PRINT("\tFind 1 result = %s\n", (char*) val);
    res = BinTree_Remove(tree, 4);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 3);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 2);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 1);
    BinTree_PrintInOrder(tree);
    res = BinTree_Remove(tree, 4);
    BinTree_PrintInOrder(tree);
    BinTree_Insert(tree, 2, (void*) "node2-1");
    BinTree_Insert(tree, 1, (void*) "node1-1");
    BinTree_Insert(tree, 1, (void*) "node1-2");
    BinTree_Insert(tree, 4, (void*) "node4-1");
    BinTree_Insert(tree, 3, (void*) "node3-1");
    BinTree_Insert(tree, 5, (void*) "node5-1");
    BinTree_PrintSubTree(tree, 2, 3);
    temp = BinTreeNode_Find(tree->root, 4);
    BinTreeNode_RotateLeft(temp);
    BinTree_PrintSubTree(tree, 2, 3);
    temp = BinTreeNode_Find(tree->root, 5);
    BinTreeNode_RotateRight(temp);
    BinTree_PrintSubTree(tree, 2, 3);
    BinTree_PrintInOrder(tree);
    BinTree_Remove(tree, 2);
    BinTree_PrintInOrder(tree);
    BinTreeNode_PrintSubTree(tree->root, 3);
    BinTree_Destroy(tree);
    AVLTreeNode t1, t2;
    t1 = AVLTreeNode_Init(1, (void*) "avlnode1");
    t2 = AVLTreeNode_Init(2, (void*) "avlnode2");
    AVLTreeNode_Insert(t1, t2);
    BinTreeNode_PrintSubTree((BinTreeNode) t1, 1);
    PRINT_DBG("%d\n", t1->size);
    PRINT_DBG("%d\n", t2->size);
    fclose_log();
}