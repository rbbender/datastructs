#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "logging.h"

extern FILE* debug_log_file;
static char LOG_LEVEL;
static char LOG_BUFFER[DS_LOG_BUFFER_SIZE];

int dslog_init_logging(char level)
{
    dslog_set_verbosity(level);
    return 0;
}

int dslog_open_file(char* log_file_name)
{
    debug_log_file = fopen(log_file_name, "w");
    if (debug_log_file)
        PRINT("LOG: File '%s' opened\n", log_file_name);
    else
        PRINT("LOG: Error opening file '%s'\n", log_file_name);
    return 0;
}

int dslog_close_file(void)
{
    int res = 0;
    if (debug_log_file != NULL)
    {

        PRINT("LOG: Closing log file\n");
        if ((res = fclose(debug_log_file)) == 0)
        {
            debug_log_file = NULL;
            PRINT("LOG: Log file closed\n");
        }
        else
            PRINT("LOG: Unable to close log file\n");
    }
    return res;
}

int dslog_print(char verb, const char* format, ...)
{
    if (verb > LOG_LEVEL)
        return 0;
    va_list args;
    va_start(args, format) ;
    vsprintf(LOG_BUFFER, format, args);
    va_end(args);
    printf("%s", LOG_BUFFER);
    if (debug_log_file)
        fprintf(debug_log_file, "%s", LOG_BUFFER);
    return 0;
}

int dslog_set_verbosity(char level)
{
    LOG_LEVEL = level;
    return 0;
}