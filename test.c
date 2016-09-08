#include <stdio.h>
#include <stdlib.h>
#include "logging.h"
#include "bintree.h"


int main(void)
{
    init_log(DS_VERBOSITY_DBG);
    fopen_log("debug.log");
    PRINT("Welcome, %s\n", "RbBender");
    BinTreeNode q = BinTreeNode_Init(1, NULL);
    BinTreeNode_Destroy(q);
    fclose_log();
}