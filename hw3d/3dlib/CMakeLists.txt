cmake_minimum_required (VERSION 3.16)
project ("3DLIB" LANGUAGES CXX)

set (LIB_NAME "3dlib")

set (HEADER_FILES "3dlib.hpp")
set (SOURCE_FILES "3dlib.cpp")

add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})