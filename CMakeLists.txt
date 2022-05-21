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
set(ARM_PROCESSOR "cortex-m4" CACHE STRING "cutil ARM processor")
set(ARM_PROFILE "a" CACHE STRING "cutil ARM architecture profile")

if ("${ARCHITECTURE}" MATCHES "ARM*")
    if ("${ARM_PROFILE}" STREQUAL "m")
        add_compile_options("-mcpu=${ARM_PROCESSOR}")
        add_compile_options("-mthumb")
        add_compile_options("-mfloat-abi=hard")
    else()
        string(TOLOWER "${ARCHITECTURE}" COMPILE_ARCHITECTURE)
        add_compile_options("-march=${COMPILE_ARCHITECTURE}-${ARM_PROFILE}")
    endif()
endif()

add_compile_definitions(ARM_PROCESSOR="${ARM_PROCESSOR}")
add_compile_definitions(ARM_PROFILE="${ARM_PROFILE}")

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