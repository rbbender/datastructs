#include <stdio.h>
#include <stdlib.h>
#include "logging.h"


int main(void)
{
    init_log(DS_VERBOSITY_DBG);
    fopen_log("debug.log");
    PRINT("Welcome, %s\n", "RbBender");
    fclose_log();
}