#include "error_check.h"
#include "header_functions.h"
#include "config.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>


/**
 * Appends HTTP headers to a linked list to be passed to libcurl.
 *
 * This function takes a pointer to a linked list of headers, and
 * four strings representing the user agent, accept format, authorization
 * key, and content type respectively. If any of these strings are not
 * NULL, the function will append the appropriate header to the linked
 * list. It will then return the new linked list.
 *
 * @param headers A pointer to the linked list of headers to be modified.
 * @param user_agent The string to be used as the User-Agent header.
 * @param accept_format The string to be used as the Accept header.
 * @param authorization_key The string to be used as the Authorization header.
 * @param content_type The string to be used as the Content-Type header.
 *
 * @return A pointer to the modified linked list of headers.
 */
struct curl_slist *set_headers(struct curl_slist *headers, const char *user_agent, const char *accept_format, const char *authorization_key, const char* content_type)
{
    if (user_agent != NULL)
    {
        headers = curl_slist_append(headers, "User-Agent: ");
        headers = curl_slist_append(headers, user_agent);
    }

    if (accept_format != NULL)
    {
        headers = curl_slist_append(headers, "Accept: ");
        headers = curl_slist_append(headers, accept_format);
    }

    if (authorization_key != NULL)
    {
        headers = curl_slist_append(headers, "Authorization: ");
        headers = curl_slist_append(headers, authorization_key);
    }

    return headers;
}
///////////////////////////////////////////////////////////////////////////
/**
 * Asks the user to input a string for a specific header.
 * If the user does not enter anything, the function will
 * return the default value for that header.
 *
 * The function will dynamically allocate memory for
 * the string, and will check that the memory allocation
 * was successful before asking for user input.
 *
 * @return A pointer to a string containing the user's input,
 *         or the default value if the user did not enter anything.
 */
char *set_user_agent()
{
    char *_user_agent = NULL;
    size_t _user_agent_size = 128;

    _user_agent = (char*)malloc(_user_agent_size);
    if(get_headers_memory_errors(_user_agent) == EXIT_FAILURE)
    {
        return NULL;
    }

    printf("Enter user agent (leave empty for default): ");
    
    if (fgets(_user_agent, _user_agent_size, stdin) == NULL ||
            strlen(_user_agent) == 1)
        {
            strcpy(_user_agent, HEADER_DEFAULT_USER_AGENT);
        }
        else _user_agent[strcspn(_user_agent, "\n")] = '\0';    

    return _user_agent;
}
char *set_accept_format() {
    char *_accept_format = NULL;
    size_t _accept_format_size = 128;

    _accept_format = (char*)malloc(_accept_format_size);
    if(get_headers_memory_errors(_accept_format) == EXIT_FAILURE)
    {
        return NULL;
    }

    printf("Enter accept format (leave empty for default): ");
    
    if (fgets(_accept_format, _accept_format_size, stdin) == NULL ||
            strlen(_accept_format) == 1)
        {
            strcpy(_accept_format, HEADER_DEFAULT_ACCEPT);
        }
        else _accept_format[strcspn(_accept_format, "\n")] = '\0';    

    return _accept_format;
}
char *set_content_type()
{
    char *_content_type = NULL;
    size_t _content_type_size = 128;

    _content_type = (char*)malloc(_content_type_size);
    if(get_headers_memory_errors(_content_type) == EXIT_FAILURE)
    {
        return NULL;
    }

    printf("Enter content type (leave empty for default): ");
    
    if (fgets(_content_type, _content_type_size, stdin) == NULL ||
            strlen(_content_type) == 1)
        {
            strcpy(_content_type, HEADER_DEFAULT_CONTENT_TYPE);
        }
        else _content_type[strcspn(_content_type, "\n")] = '\0';

    return _content_type;
}
char *set_authorization_key() {
    char *_authorization_key = NULL;
    size_t _authorization_key_size = 128;

    _authorization_key = (char*)malloc(_authorization_key_size);
    if(get_headers_memory_errors(_authorization_key) == EXIT_FAILURE)
    {
        return NULL;
    }

    printf("Enter authorization key (leave empty for default): ");
    
    if (fgets(_authorization_key, _authorization_key_size, stdin) == NULL ||
            strlen(_authorization_key) == 1)
        {
            strcpy(_authorization_key, HEADER_DEFAULT_AUTHORIZATION);
        }
        else _authorization_key[strcspn(_authorization_key, "\n")] = '\0';    

    return _authorization_key;
}
///////////////////////////////////////////////////////////////////////////
/**
 * Sets custom headers for a GET request.
 *
 * This function prompts the user to input custom values for the User-Agent,
 * Accept Format, and Authorization Key headers when the command line argument
 * matches a specific GET header argument. It then uses these values to set
 * HTTP headers for a GET request.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @param headers A pointer to a pointer of a linked list of headers to be modified.
 */
void get_header_functions(int argc, char* argv[], struct curl_slist **headers)
{
    if(argc == 4 && strcmp(argv[3], HEADER_GET_SET_ARG) == 0)
    {
        printf("Custom Headers: Provide in order: User-Agent, Accept Format, Authorization Key >>\n");
        

        char *_user_agent = set_user_agent();
        char *_accept_format = set_accept_format();
        char *_authorization_key = set_authorization_key();

        *headers = set_headers(NULL, _user_agent, _accept_format, _authorization_key, NULL);

        free(_user_agent);
        free(_accept_format);
        free(_authorization_key);
    }
}
///////////////////////////////////////////////////////////////////////////
/**
 * Sets custom headers for a POST request.
 *
 * This function prompts the user to input a custom Content-Type header when the
 * command line argument matches a specific POST header argument. It then uses
 * this value to set the Content-Type header for a POST request.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @param headers A pointer to a pointer of a linked list of headers to be modified.
 */
void post_header_functions(int argc, char* argv[], struct curl_slist **headers)
{
    if(argc == 4 && strcmp(argv[3], HEADER_POST_SET_ARG) == 0)
    {
        printf("Custom Headers: Provide Content-Type (leave empty for default(JSON)) >>\n");
        
        char *_content_type = set_content_type();

        *headers = set_headers(NULL, NULL, NULL, NULL, _content_type);

        free(_content_type);
    }
}
///////////////////////////////////////////////////////////////////////////
/**
 * Applies the default headers to the linked list of headers.
 *
 * This function will be called if no header argument is provided. It will
 * set the default headers to the linked list, and print a message to the
 * console indicating that the default headers have been applied.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @param headers A pointer to a pointer of a linked list of headers to be modified.
 */
void default_header_functions(int argc, char* argv[], struct curl_slist **headers)
{   
    printf("DEFAULT HEADERS APPLIED!\n");
    *headers = set_headers(NULL, HEADER_DEFAULT_USER_AGENT, HEADER_DEFAULT_ACCEPT, HEADER_DEFAULT_AUTHORIZATION, NULL);
}
///////////////////////////////////////////////////////////////////////////
