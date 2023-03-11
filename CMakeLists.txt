cmake_minimum_required(VERSION 3.24)

project(RedisClone VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Libraries
set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/request.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp")
add_library(Server ${LIB_SOURCES})
target_compile_features(Server
    PUBLIC
        cxx_std_17
)
target_include_directories(Server
    PUBLIC
        inc
)

# Main Executable
add_executable(RedisServer src/main.cpp)
target_link_libraries(RedisServer
    PRIVATE
        Server
)
target_compile_features(RedisServer
    PRIVATE
        cxx_std_17
)
