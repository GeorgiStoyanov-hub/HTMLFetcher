#ifndef ERROR_CHECK_H
#define ERROR_CHECK_H


#include <curl/curl.h>
#include "header_functions.h"
#include "config.h"

unsigned short int argument_check(int argc, char *argv[]);
int get_headers_memory_errors(char *some_header);

#endif
