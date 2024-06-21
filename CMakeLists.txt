cmake_minimum_required(VERSION 3.15)

project(mai-playdata
  LANGUAGES C
  VERSION 0.0.0
)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb -Wall -Wextra -Wpedantic -Werror")

file(GLOB SOURCE_FILES "src/*.c")
include_directories("include")

find_package(OpenSSL REQUIRED)
find_package(ZLIB)

add_executable(mai-playdata ${SOURCE_FILES})
target_sources(mai-playdata PRIVATE src/mai-playdata.c)
target_link_libraries(mai-playdata OpenSSL::SSL)
target_link_libraries(mai-playdata ZLIB::ZLIB)
