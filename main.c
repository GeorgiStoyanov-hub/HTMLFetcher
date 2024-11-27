#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "config.h"
#include "header_functions.h"
#include "error_check.h"

int main(int argc, char* argv[]) 
{   

   if(argument_check(argc, argv) == EXIT_FAILURE)
   {
       return EXIT_FAILURE; 
   }

    const char* URL = argv[1];
    const char* output = argv[2];
    CURL *curl = curl_easy_init();

    if(!curl) 
    {
        fprintf(stderr, "Error: Failed to initialize cURL.\n");
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
    struct curl_slist *headers = NULL;

    if(argc == 4 && strcmp(argv[3], HEADER_GET_SET_ARG) == 0)
    {
        get_header_functions(argc, argv, &headers);
    }

    else if(argc == 4 && strcmp(argv[3], HEADER_POST_SET_ARG) == 0)
    {
        post_header_functions(argc, argv, &headers);
    }
    else
    {
        default_header_functions(argc, argv, &headers);
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
        else if(argc == 4 && strcmp(argv[3], HEADER_GET_SET_ARG) == 0 || argc == 4 && strcmp(argv[3], HEADER_POST_SET_ARG) == 0)
        {   
            if(argc == 4 && strcmp(argv[3], HEADER_POST_SET_ARG) == 0)
            {
                curl_easy_setopt(curl, CURLOPT_POST, 1L);

                printf("Enter POST data (leave empty for none): ");
                char* post_data = NULL;
                size_t post_data_size = 1024;
                post_data = (char*)malloc(post_data_size);
                if (post_data == NULL)
                {
                    fprintf(stderr, "Memory allocation failed for POST data!\n");
                    curl_slist_free_all(headers);
                    fclose(fl);
                    curl_easy_cleanup(curl);
                    return EXIT_FAILURE;
                }
                if (fgets(post_data, post_data_size, stdin) == NULL || strlen(post_data) == 1)
                {
                    printf("No POST data provided, sending empty body.\n");
                    post_data[0] = '\0';  
                }
                else post_data[strcspn(post_data, "\n")] = '\0';  

                
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

                printf("Headers and POST data successfully set.\n");
                printf("POST Data: %s\n", post_data);

                free(post_data); 
            }
            printf("Headers succesfully set.\n");
        }
        else if (argc == 4)
        {
            fprintf(stderr, "Error 3: Invalid Argument '%s'.\n", argv[3]);
            fprintf(stderr, "Valid arguments are:\n");
            fprintf(stderr, "  %s: Ignore SSL verification.\n", HEADER_IGNORE_ARG);
            fprintf(stderr, "  %s: Debug headers.\n", HEADER_DEBUG_ARG);
            fprintf(stderr, "  %s: Set GET headers.\n", HEADER_GET_SET_ARG);
            fprintf(stderr, "  %s: Set POST headers.\n", HEADER_POST_SET_ARG);
            curl_slist_free_all(headers);
            fclose(fl);
            curl_easy_cleanup(curl);
            return EXIT_FAILURE;
        }

        // TESTING STUFF

        ////////////////

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
