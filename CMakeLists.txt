cmake_minimum_required(VERSION 3.20)


project(<project name> LANGUAGES C CXX)

#find_package(fmt CONFIG REQUIRED)
find_package(CURL REQUIRED)

add_executable(<project name> main.c)

#target_link_libraries(<project name> PRIVATE fmt::fmt)
target_link_libraries(<project name> PRIVATE CURL::libcurl)
