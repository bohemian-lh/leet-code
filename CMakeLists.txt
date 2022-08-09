cmake_minimum_required(VERSION 3.22)
project(let_code)

set(CMAKE_CXX_STANDARD 14)

#???solution-class?????????????LEETCODE_SRC
aux_source_directory(./solution-class LEETCODE_SRC)

#???????
add_library(code-lib SHARED ${LEETCODE_SRC} solution-class/ListSolution01.cpp solution-class/MyLinkedList_707.cpp solution-class/Solution_206.cpp)

#???????????????
FILE(GLOB files case-test/*.cpp cpluspluspractice/*.cpp)
foreach(file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable(${exe} ${file} case-test/testleetcode.cpp)
    message(\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach()

#?test????code-lib
target_link_libraries(test code-lib)