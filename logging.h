#ifndef DS_LOGGING
#define DS_LOGGING
#define DS_LOG_BUFFER_SIZE 256
#define DS_LOG_FILENAME_MAXSIZE 256
#define DS_VERBOSITY_STD 20
#define DS_VERBOSITY_DBG 30
FILE* debug_log_file;
#define PRINT_DBG(fmt, args...) print_log(DS_VERBOSITY_DBG, fmt, ## args)
#define PRINT(fmt, args...) print_log(DS_VERBOSITY_STD, fmt, ## args)
int init_log(char);
int fopen_log(char*);
int fclose_log(void);
int print_log(char, const char*, ...);
int set_log_level(char);
#endif