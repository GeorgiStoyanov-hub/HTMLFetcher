#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "config.h"

int main(int argc, char* argv[]) 
{   

    if(argc > 4)
    {
        fprintf(stderr, "\nUsage: %s <URL> <Output> [Arguments]\n", argv[0]);
        fprintf(stderr, "Error 1 : Too many arguments passed\n");
        return EXIT_FAILURE;
    }
    if(argc < 3)
    {
        fprintf(stderr, "\nUsage: %s <URL> <Output> [Arguments]\n", argv[0]);
        fprintf(stderr, "Error 2 : Must include at least 3 arguments\n");
        return EXIT_FAILURE;
    }

    const char* URL = argv[1];
    const char* output = argv[2];
    CURL *curl = curl_easy_init();

    if(!curl) 
    {
        fprintf(stderr, "failed to initialize cURL.\n");
        return EXIT_FAILURE;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE FILE vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    FILE *fl = fopen(output, "wb");

    if(!fl)
    {
        perror("\nError opening file.\n");
        curl_easy_cleanup(curl);
        return EXIT_FAILURE;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // SET HEADERS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    struct curl_slist *headers = NULL; //User Agent, Accept, Authorization
    if(argc == 4 && strcmp(argv[3], HEADER_SET_ARG) == 0)
    {
        printf("Custom Headers: Provide in order: User-Agent, Accept Format, Authorization Key >>\n");
        char *_user_agent = NULL, *_accept_format = NULL, *_authorization_key = NULL;
        size_t _user_agent_size = 128, _accept_format_size = 128, _authorization_key_size = 256;

        //////////////////////////////////////////////////////
        ////////////////// USER AGENT ////////////////////////
        _user_agent = (char*)malloc(_user_agent_size);
        if (_user_agent == NULL) 
        {
            fprintf(stderr, "Memory allocation failed for user agent!\n");
            free(_user_agent);
            fclose(fl);
            curl_easy_cleanup(curl);
            exit(EXIT_FAILURE);
        }

        printf("Enter user agent (leave empty for default): ");
        if (fgets(_user_agent, _user_agent_size, stdin) == NULL ||
            strlen(_user_agent) == 1)
        {
            strcpy(_user_agent, HEADER_DEFAULT_USER_AGENT);
        }
        else _user_agent[strcspn(_user_agent, "\n")] = '\0';    
        //////////////////////////////////////////////////////
        ///////////////// ACCEPT FORMAT //////////////////////
        _accept_format = (char*)malloc(_accept_format_size);
        if (_accept_format == NULL) 
        {
            fprintf(stderr, "Memory allocation failed for accept format!\n");
            free(_user_agent);
            free(_accept_format);
            fclose(fl);
            curl_easy_cleanup(curl);
            exit(EXIT_FAILURE);
        }

        printf("Enter Accept Format (leave empty for default): ");
        if (fgets(_accept_format, _accept_format_size, stdin) == NULL ||
            strlen(_accept_format) == 1)
        {
            strcpy(_accept_format, HEADER_DEFAULT_ACCEPT);
        }
        else _accept_format[strcspn(_accept_format, "\n")] = '\0';
        //////////////////////////////////////////////////////
        ///////////////// AUTHORIZATION KEY //////////////////
        _authorization_key = (char*)malloc(_authorization_key_size);
        if (_authorization_key == NULL) 
        {
            fprintf(stderr, "Memory allocation failed for authorization key!\n");
            free(_user_agent);
            free(_accept_format);
            free(_authorization_key);
            fclose(fl);
            curl_easy_cleanup(curl);
            exit(EXIT_FAILURE);
        }

        printf("Enter Authorization Key (leave empty for default): ");
        if(fgets(_authorization_key, _authorization_key_size, stdin) == NULL ||
            strlen(_authorization_key) == 1)
        {
            strcpy(_authorization_key, HEADER_DEFAULT_AUTHORIZATION);
        }
        else _authorization_key[strcspn(_authorization_key, "\n")] = '\0';


        char _header_user_agent[256], _header_accept_format[256], _header_authorization_key[256];

        snprintf(_header_user_agent, sizeof(_header_user_agent), "User-Agent: %s", _user_agent);
        snprintf(_header_accept_format, sizeof(_header_accept_format), "Accept: %s", _accept_format);
        snprintf(_header_authorization_key, sizeof(_header_authorization_key), "Authorization: %s", _authorization_key);

        headers = curl_slist_append(headers, _header_user_agent);
        headers = curl_slist_append(headers, _header_accept_format);
        headers = curl_slist_append(headers, _header_authorization_key);

        free(_user_agent);
        free(_accept_format);
        free(_authorization_key);
    }
    else
    {
        headers = curl_slist_append(headers, HEADER_DEFAULT_USER_AGENT);
        headers = curl_slist_append(headers, HEADER_DEFAULT_ACCEPT);
        headers = curl_slist_append(headers, HEADER_DEFAULT_AUTHORIZATION);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // SET OPTIONS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    printf("\nFetching URL: %s\n", URL);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 

        if (argc == 4 && strcmp(argv[3], HEADER_IGNORE_ARG) == 0)
        {
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            printf("SSL verification is disabled.\n");
        }
        else if (argc == 4 && strcmp(argv[3], HEADER_DEBUG_ARG) == 0)
        {   
            printf("Sending the following headers:\n");
            struct curl_slist *temp = headers;
            while(temp)
            {
                printf("%s\n", temp->data);
                temp = temp->next;
            }
        }
        else if(argc == 4 && strcmp(argv[3], HEADER_SET_ARG) == 0)
        {
            printf("Headers succesfully set.\n");
        }
        else if (argc == 4)
        {
            fprintf(stderr, "Error 3: Invalid Argument '%s'.\n", argv[3]);
            fprintf(stderr, "Valid arguments are:\n");
            fprintf(stderr, "  %s: Ignore SSL verification.\n", HEADER_IGNORE_ARG);
            fprintf(stderr, "  %s: Debug headers.\n", HEADER_DEBUG_ARG);
            fprintf(stderr, "  %s: Set headers.\n", HEADER_SET_ARG);
            curl_slist_free_all(headers);
            fclose(fl);
            curl_easy_cleanup(curl);
            return EXIT_FAILURE;
        }

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fl);
    printf("Saving to file: %s\n", output);
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // PERFORM vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    CURLcode result = curl_easy_perform(curl);

    if(result != CURLE_OK)
    {
        fprintf(stderr, "cURL request failed %s\n", curl_easy_strerror(result));
        curl_slist_free_all(headers);
        fclose(fl);
        curl_easy_cleanup(curl);
        return EXIT_FAILURE;
    }

    printf("Request succeeded. Response saved to '%s'.\n", output);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    printf("HTTP Status Code: %ld\n", http_code);
    if(http_code != 200)
    {
        printf("Request returned HTTP status code %ld.\n", http_code);
    }
    else
    {
        printf("Request was successful!\n");
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // FREE ALLOCATED RESOURCES vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    fclose(fl);
    return result == CURLE_OK ? EXIT_SUCCESS : EXIT_FAILURE;
    ///////////////////////////////////////////////////////////////////////////////////////////////////
}
