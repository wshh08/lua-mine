cmake_minimum_required(VERSION 3.5)
project(Lua)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -O2 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-E")

include_directories(lib)

add_subdirectory(lib)

add_executable(lua lua.c)
add_executable(luac luac.c)

target_link_libraries(lua llua m dl readline)
target_link_libraries(luac llua m dl readline)
