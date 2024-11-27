#ifndef HEADER_FUNCTIONS_H
#define HEADER_FUNCTIONS_H

#include <curl/curl.h>
struct curl_slist *set_headers(struct curl_slist *headers, const char *user_agent, const char *accept_format, const char *authorization_key, const char *content_type);
char *set_user_agent();
void get_header_functions(int argc, char* argv[], struct curl_slist **headers);
void post_header_functions(int argc, char* argv[], struct curl_slist **headers);
void default_header_functions(int argc, char* argv[], struct curl_slist **headers);


#endif
