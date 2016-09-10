#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"


int main(void)
{
    init_log(DS_VERBOSITY_DBG);
    fopen_log("debug.log");
    PRINT("Welcome, %s\n", "RbBender");
    BinTree tree = BinTree_Init();
    BinTree_Insert(tree, 2, (void*) "node2");
    BinTree_Insert(tree, 3, (void*) "node3");
    BinTree_Insert(tree, 1, (void*) "node1");
    BinTree_PrintInOrder(tree);
    fclose_log();
}