#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "logging.h"

extern FILE* debug_log_file;
static char log_level;
static char log_buffer[DS_LOG_BUFFER_SIZE];
static char log_file_name[DS_LOG_FILENAME_MAXSIZE];

int init_log(char level)
{
    set_log_level(level);
    return 0;
}

int fopen_log(char* file_name)
{
    PRINT("LOG: Opening log file '%s'...\n", file_name);
    int filename_len;
    filename_len = strlen(file_name);
    if (filename_len == 0)
    {
        PRINT("LOG: Empty filename for log file. Won't open any files.\n");
        debug_log_file = NULL;
        return -1;
    };
    if (filename_len >= DS_LOG_FILENAME_MAXSIZE)
    {
        PRINT_DBG("LOG: filename_len = %d, DS_LOG_FILENAME_MAXSIZE = %d\n", filename_len,
            DS_LOG_FILENAME_MAXSIZE);
        PRINT("LOG: Filename to create is too long. Won't open any files.\n");
        debug_log_file = NULL;
        return -1;
    }

    debug_log_file = fopen(file_name, "w");
    if (debug_log_file)
    {
        strcpy(log_file_name, file_name);
        PRINT("LOG: File '%s' opened\n", log_file_name);
    }
    else
        PRINT("LOG: Error opening file '%s'\n", file_name);
    return 0;
}

int fclose_log(void)
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

int print_log(char verb, const char* format, ...)
{
    if (verb > log_level)
        return 0;
    va_list args;
    va_start(args, format) ;
    vsprintf(log_buffer, format, args);
    va_end(args);
    printf("%s", log_buffer);
    if (debug_log_file)
        fprintf(debug_log_file, "%s", log_buffer);
    return 0;
}

int set_log_level(char level)
{
    log_level = level;
    return 0;
}