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

set(ARCHITECTURE "AArch64" CACHE STRING "cutil target architecture")

add_library(cutil STATIC ${SOURCES} ${HEADERS}
    "arch/${ARCHITECTURE}.S"
)

option(NOSTDLIB "compile cutil without stdlib" ON)
if (NOSTDLIB)
    target_compile_definitions(cutil PRIVATE CUTIL_NOSTDLIB)
    target_compile_options(cutil PRIVATE -nostdlib)
endif()

add_executable(test test.c)
target_link_libraries(test -static cutil)