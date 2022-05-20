cmake_minimum_required(VERSION 3.10)
project(cutil C ASM)

set(HEADERS
    cutypes.h
    cutil.h
    list.h
    array.h
    bitmap.h
    endian.h
    struct.h
    string.h
    heap.h
)

set(SOURCES
    cutil.c
    list.c
    array.c
    bitmap.c
    endian.c
    struct.c
    string.c
    heap.c
)

set(ARCHITECTURE "ARMv7" CACHE STRING "cutil target architecture")
set(ARM_PROFILE "m" CACHE STRING "cutil ARM architecture profile")

if ("${ARCHITECTURE}" STREQUAL "ARMv7")
    if ("${ARM_PROFILE}" STREQUAL "m")
        add_compile_options("-mcpu=cortex-m4")
        add_compile_options("-mthumb")
    else()
        add_compile_options("-march=armv7-${ARM_PROFILE}")
    endif()
endif()

add_library(cutil STATIC ${SOURCES} ${HEADERS}
    "arch/${ARCHITECTURE}.S"
)

option(NOSTDLIB "compile cutil without stdlib" ON)
if (NOSTDLIB)
    target_compile_definitions(cutil PRIVATE CUTIL_NOSTDLIB)
    target_compile_options(cutil PRIVATE "-nostdlib")
endif()

add_executable(test test.c)
target_link_libraries(test -static cutil)