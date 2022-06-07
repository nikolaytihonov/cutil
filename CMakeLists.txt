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

set(ARCHITECTURE "x86_64" CACHE STRING "cutil target architecture")

set(ARM_PROCESSOR "cortex-m4" CACHE STRING "cutil ARM processor")
set(ARM_PROFILE "a" CACHE STRING "cutil ARM architecture profile")

if ("${ARCHITECTURE}" MATCHES "ARM*")
    set(CUSTOM_STDLIB "" CACHE STRING "custom stdlib path")
    add_compile_definitions(ARM_PROCESSOR="${ARM_PROCESSOR}")
    add_compile_definitions(ARM_PROFILE="${ARM_PROFILE}")
    if ("${ARM_PROFILE}" STREQUAL "m")
        add_compile_options("-mcpu=${ARM_PROCESSOR}")
        add_compile_options("-mthumb")
        add_compile_options("-mfloat-abi=hard")
    else()
        string(TOLOWER "${ARCHITECTURE}" COMPILE_ARCHITECTURE)
        add_compile_options("-march=${COMPILE_ARCHITECTURE}-${ARM_PROFILE}")
        add_compile_options("-marm")
    endif()
elseif("${ARCHITECTURE}" MATCHES "SuperH4")
    set(CUSTOM_STDLIB "/opt/sh4-platform/lib" CACHE STRING "custom stdlib path")
    add_compile_options("-m4")
else()
    set(CUSTOM_STDLIB "" CACHE STRING "custom stdlib path")
endif()

add_library(cutil STATIC ${SOURCES} ${HEADERS}
    "arch/${ARCHITECTURE}.S"
)

option(NOSTDLIB "compile cutil without stdlib" OFF)
option(STATIC "compile test static" OFF)
if (NOSTDLIB)
    target_compile_definitions(cutil PRIVATE CUTIL_NOSTDLIB)
    target_compile_options(cutil PRIVATE "-nostdlib")
endif()

if(NOT "${CUSTOM_STDLIB}" STREQUAL "")
    add_compile_options("-nostdlib")
    set(CMAKE_EXE_LINKER_FLAGS "-L${CUSTOM_STDLIB} -l:libc.so.6")
elseif (STATIC)
    add_link_options(-static)    
endif()

add_executable(test test.c)
target_link_libraries(test cutil)