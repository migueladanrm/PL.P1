cmake_minimum_required(VERSION 3.13)
project(PL.P1 C)

set(CMAKE_C_STANDARD 11)

#option(CMAKE_THREADS_LIB)

#option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
find_package(Threads)

add_executable(PL.P1 main.c env_tests.c env_tests.h environment.c environment.h)

target_link_libraries(PL.P1 ${CMAKE_THREAD_LIBS_INIT} )