cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CPU_Tracker)

set(EXTERN_DIR "${PROJECT_SOURCE_DIR}/extern")
set(FMT_INCLUDE_DIR ${EXTERN_DIR}/fmt/include/)
set(FMT_LIBRARY_DIR ${EXTERN_DIR}/fmt/lib/)


file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/script.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE 
                                    -Wall -fexceptions -std=c++20 -Wpedantic -Werror 
                                    -Wno-unknown-pragmas -Wno-unused-function -Oo)
    target_link_options(${PROJECT_NAME} PRIVATE -s)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE 
                                    -Wall -fexceptions -std=c++20 -Wpedantic -Werror 
                                    -Wno-unknown-pragmas -Wno-unused-function -O3)
    target_link_options(${PROJECT_NAME} PRIVATE -s)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE 
                                    -Wall -fexceptions -std=c++20 -Wpedantic -Werror 
                                    -Wno-unknown-pragmas -Wno-unused-function -Oo)
    target_link_options(${PROJECT_NAME} PRIVATE -s)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE 
                                    -Wall -fexceptions -std=c++20 -Wpedantic -Werror 
                                    -Wno-unknown-pragmas -Wno-unused-function -O3)
    target_link_options(${PROJECT_NAME} PRIVATE -s)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE 
                                    /W4 /WX- /permissive- /std:c++20
                                    /TP /Gd /Gm- /RTC1 /Od /diagnostics:classic
                                    /fp:precise /EHsc)
    target_link_options(${PROJECT_NAME} PRIVATE /INCREMENTAL /MACHINE:X64)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" AND CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE 
                                    /W4 /WX- /permissive- /std:c++20
                                    /TP /Gd /Gm- /diagnostics:classic
                                    /fp:precise /EHsc /Ob2 /O2 /Oi)
    target_link_options(${PROJECT_NAME} PRIVATE /INCREMENTAL /MACHINE:X64)
endif()

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_include_directories(${PROJECT_NAME} PRIVATE ${FMT_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${FMT_LIBRARY_DIR}libfmt.a)
endif()