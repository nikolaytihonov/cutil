cmake_minimum_required(VERSION 3.10)
project(cutil)

set(HEADERS
    cutypes.h
    cutil.h
    list.h
    array.h
    bitmap.h
    endian.h
)

set(SOURCES
    cutil.c
    list.c
    array.c
    bitmap.c
    endian.c
)

add_library(cutil STATIC ${SOURCES} ${HEADERS})

add_executable(test test.c)
target_link_libraries(test cutil)