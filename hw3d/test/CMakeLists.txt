cmake_minimum_required (VERSION 3.16)
project ("3DLIB TEST" LANGUAGES CXX)

set (COMPILE_SETTINGS
    -Wall
    -Wextra
    -O2
    -DNDEBUG
)

set (EXEC_NAME "test.out")
set (SOURCE_FILES "tester.cpp")
set (GTEST_LIBS gtest gmock pthread)

add_executable (${EXEC_NAME} ${SOURCE_FILES})
target_include_directories (${EXEC_NAME} PRIVATE "../3dlib")
target_link_libraries (${EXEC_NAME} 3dlib ${GTEST_LIBS})
target_compile_options (${EXEC_NAME} PRIVATE ${COMPILE_SETTINGS})
