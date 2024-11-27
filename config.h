#ifndef CONFIG_H
#define CONFIG_H

// HEADER ARGUMENTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#define HEADER_GET_SET_ARG "-GHSET"
#define HEADER_POST_SET_ARG "-PHSET"
#define HEADER_IGNORE_ARG "-IGNORE"
#define HEADER_DEBUG_ARG "-HDEBUG"
///////////////////////////////////////////////////////////////////////////////////////////////////
// DEFAULT HEADER BEHAVIOUR vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#define HEADER_DEFAULT_USER_AGENT "curl/7.79.1"
#define HEADER_DEFAULT_ACCEPT "*/*"
#define HEADER_DEFAULT_AUTHORIZATION ""
#define HEADER_DEFAULT_CONTENT_TYPE "application/json"
///////////////////////////////////////////////////////////////////////////////////////////////////
#define MIN_ARGS 3
#define MAX_ARGS 4
#endif
