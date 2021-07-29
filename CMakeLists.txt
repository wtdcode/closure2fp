cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

add_library(mylib SHARED lib.c)
add_library(closure SHARED closure.c)

add_executable(main_cpp main.cpp)
add_executable(main main.c)
add_executable(main_bad main_bad.c)
add_executable(main_bad_cpp main_bad.cpp)

target_link_libraries(main mylib)
target_link_libraries(main_cpp mylib)
target_link_libraries(main_bad mylib closure)
target_link_libraries(main_bad_cpp mylib closure)