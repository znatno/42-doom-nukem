cmake_minimum_required(VERSION 3.13)
project(doom-nukem C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR ~/.brew/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/lib/)
set(LIBFT_INCLUDE_DIR ./libft/include)
set(LIBFT_LIBRARY ./libft/)
set(SOURCE ./src/)
set(INCLUDE ./include/)
include_directories(${SDL2_INCLUDE_DIR}
                    ${LIBFT_INCLUDE_DIR}
                    ${SOURCE}
                    ${INCLUDE})

link_directories(${SDL2_LIBRARY}
                 ${LIBFT_LIBRARY}
                 ${SOURCE})

file(GLOB all
        "${INCLUDE}*.h"
        "${SOURCE}*.c")

add_executable(doom-nukem ${all})

target_link_libraries(doom-nukem -lft -lSDL2)