cmake_minimum_required(VERSION 3.10.2)
project(thread_lock)

find_package (Threads)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} Threads::Threads)