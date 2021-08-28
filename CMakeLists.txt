cmake_minimum_required(VERSION 3.20)
project(ldline C)

set(CMAKE_C_STANDARD 99)
set(SOURCES src/main/ldline.c)
set(HEADERS src/lib/libldline.h)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_library(lib_ldline src/lib/libldline.c ${HEADERS})
target_include_directories(lib_ldline PRIVATE ${lib})
add_executable(ldline ${SOURCES} ${HEADERS})
target_include_directories(ldline PRIVATE ${src})
target_link_libraries(ldline lib_ldline)

set_target_properties(ldline lib_ldline
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
