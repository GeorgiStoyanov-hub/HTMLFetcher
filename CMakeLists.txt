cmake_minimum_required(VERSION 3.20)
project(CurlFetcher VERSION 0.1.0 LANGUAGES C)

#find libcurl
find_package(CURL REQUIRED)

add_executable(CurlFetcher main.c header_functions.c error_check.c)

#link libcurl
target_link_libraries(CurlFetcher PRIVATE CURL::libcurl)
