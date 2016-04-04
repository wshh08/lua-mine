set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -O2 -Wall -Wextra -DLUA_COMPAT_5_2 -DLUA_USE_LINUX")
aux_source_directory(. DIR_SRCS_LIB)
add_library(llua ${DIR_SRCS_LIB})

