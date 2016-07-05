cmake_minimum_required(VERSION 3.2.2)
project(my_includeos_service)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target i686-elf -mstackrealign -fstack-protector-all -msse3 -O2 -Wall -Wextra -m32 -std=c++14 -D_LIBCPP_HAS_NO_THREADS=1 -D_GNU_SOURCE")
set(INCLUDEOS_INSTALL $ENV{HOME}/IncludeOS_Install)
set(SOURCE_FILES service.cpp)

include_directories(${INCLUDEOS_INSTALL}/libcxx/include
        ${INCLUDEOS_INSTALL}/api/sys
        ${INCLUDEOS_INSTALL}/newlib/include
        ${INCLUDEOS_INSTALL}/api
        ${INCLUDEOS_INSTALL}/mod/GSL/include)
add_library(service OBJECT ${SOURCE_FILES})

#[[
add_custom_target(Real_make ALL)
add_custom_command(TARGET Real_make
        DEPENDS service
        COMMAND ${CMAKE_MAKE_PROGRAM}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

]]#