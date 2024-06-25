cmake_minimum_required(VERSION 3.13)
project(Alba)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cpp)

# add_subdirectory(lib/)

add_executable(Alba ${SOURCE_FILES})

target_link_libraries(Alba PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2.lib)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(Alba copy_assets)


