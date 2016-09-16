cmake_minimum_required(VERSION 3.6)
project(get-password)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        loader/hook.cpp
        loader/hook.h
        loader/library.cpp
        loader/library.h
        loader/loader.cpp)

add_executable(get-password ${SOURCE_FILES})
add_library(gettext SHARED gettext/gettext.cpp)
set_target_properties(gettext PROPERTIES PREFIX "")