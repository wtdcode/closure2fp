cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

add_library(mylib SHARED lib.c)
add_library(closure SHARED closure.c)

add_executable(main_cpp main.cpp)
add_executable(main main.c)
add_executable(main2 main2.c)
add_executable(main2_cpp main2.cpp)

target_link_libraries(main mylib)
target_link_libraries(main_cpp mylib)
target_link_libraries(main2 mylib closure)
target_link_libraries(main2_cpp mylib closure)