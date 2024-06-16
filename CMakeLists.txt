cmake_minimum_required(VERSION 3.15)

project(mai-playdata
  LANGUAGES C
  VERSION 0.0.0
)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG} -O0 -ggdb -Wall -Wextra -Wpedantic -Werror")

file(GLOB SOURCE_FILES "src/*.c")
include_directories("include")

add_executable(server ${SOURCE_FILES})
target_sources(server PRIVATE server/server.c)

add_executable(client ${SOURCE_FILES})
target_sources(client PRIVATE client/client.c)