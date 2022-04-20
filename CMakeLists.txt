cmake_minimum_required(VERSION 3.10)
project(cutil)

set(HEADERS
    cutypes.h
    cutil.h
    list.h
    array.h
    bitmap.h
)

set(SOURCES
    cutil.c
    list.c
    array.c
    bitmap.c
)

add_compile_definitions(CU_64BIT)
add_library(cutil STATIC ${SOURCES} ${HEADERS})

add_executable(test test.c)
target_link_libraries(test cutil)