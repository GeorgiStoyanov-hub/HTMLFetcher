#include <curl/curl.h>
#include "header_functions.h"
#include "config.h"
#include <stdlib.h>

/**
 * Checks that the number of command line arguments is valid.
 *
 * @param argc The number of arguments passed in
 * @param argv The array of arguments
 *
 * @return EXIT_SUCCESS if the number of arguments is valid, EXIT_FAILURE otherwise
 *
 * Note: The minimum number of arguments is 3, and the maximum number of arguments is 4. (CURRENTLY)
 */
unsigned short int argument_check(int argc, char *argv[]) 
{
    if (argc < MIN_ARGS) 
    {
        fprintf(stderr, "Error: Insufficient arguments. Usage: %s <URL> <Output> [Arguments]\n", argv[0]);
        return EXIT_FAILURE;
    }

     if (argc > MAX_ARGS) 
    {
        fprintf(stderr, "Error: Too many arguments. Usage: %s <URL> <Output> [Arguments]\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////
/**
 * Checks if the provided header memory allocation was successful.
 *
 * @param some_header A pointer to the header string to check.
 * @return EXIT_SUCCESS if the memory allocation was successful, 
 *         otherwise returns EXIT_FAILURE if some_header is NULL.
 */
int get_headers_memory_errors(char *some_header)
{
    if(some_header == NULL)
    {   
        fprintf(stderr, "Memory allocation failed for user agent!\n");
        return EXIT_FAILURE;
    }
    else return EXIT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////
