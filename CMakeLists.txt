cmake_minimum_required(VERSION 3.6)
project(get-password)

set(SOURCE_FILES
        loader/hook.cpp
        loader/hook.h
        loader/library.cpp
        loader/library.h
        loader/loader.cpp)

add_executable(get-password WIN32 ${SOURCE_FILES})
set_target_properties(get-password PROPERTIES
            CXX_STANDARD 11)
add_library(gettext SHARED gettext/gettext.cpp)
set_target_properties(gettext PROPERTIES
            PREFIX ""
            CXX_STANDARD 11)
