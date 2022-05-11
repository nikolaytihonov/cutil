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
)

set(SOURCES
    cutil.c
    list.c
    array.c
    bitmap.c
    endian.c
    struct.c
)

add_library(cutil STATIC ${SOURCES} ${HEADERS}
    "arch/${CMAKE_SYSTEM_PROCESSOR}.S"
)

add_executable(test test.c)
target_link_libraries(test cutil)