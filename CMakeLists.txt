cmake_minimum_required(VERSION 3.24)

project(redis-clone VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Libraries
set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp")
add_library(redis-clone-lib ${LIB_SOURCES})
target_compile_features(redis-clone-lib
    PUBLIC
        cxx_std_17
)
target_include_directories(redis-clone-lib
    PUBLIC
        inc
)

# Main Executable
add_executable(redis-clone src/main.cpp)
target_link_libraries(redis-clone
    PRIVATE
        redis-clone-lib
)
target_compile_features(redis-clone
    PRIVATE
        cxx_std_17
)
