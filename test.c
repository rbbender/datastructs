#include <stdio.h>
#include <stdlib.h>
#include "logging.h"


int main(void)
{
    dslog_init_logging(1);
    dslog_open_file("debug.log");
    PRINT("Welcome, %s\n", "RbBender");
    dslog_close_file();
}