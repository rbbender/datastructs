#ifndef DS_LOGGING
#define DS_LOGGING
#define DS_LOG_BUFFER_SIZE 256
#define DS_VERBOSITY_STD 1
#define DS_VERBOSITY_DBG 2
FILE* debug_log_file;
#define PRINT_DBG(fmt, args...) dslog_print(DS_VERBOSITY_DBG, fmt, ## args)
#define PRINT(fmt, args...) dslog_print(DS_VERBOSITY_STD, fmt, ## args)
int dslog_init_logging(char);
int dslog_open_file(char*);
int dslog_close_file(void);
int dslog_print(char, const char*, ...);
int dslog_set_verbosity(char);
#endif