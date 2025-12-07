cmake_minimum_required(VERSION 3.18)

project(s2-hooking)

add_subdirectory(deps/minhook)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_library(${PROJECT_NAME} STATIC
    ${SOURCES}
)

target_compile_features(${PROJECT_NAME} PUBLIC
    cxx_std_23
)

target_link_libraries(${PROJECT_NAME}
    minhook
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
