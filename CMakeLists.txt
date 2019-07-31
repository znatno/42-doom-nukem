cmake_minimum_required(VERSION 3.14)
project(doom-nukem C)

set(CMAKE_C_STANDARD 99)


set(SDL2_INCLUDE_DIR ~/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/Cellar/sdl2/2.0.9_1/lib/)

set(SDL_MIXER_INCLUDE_DIR ~/.brew/Cellar/sdl_mixer/1.2.12_3/include/SDL/)
set(SDL_MIXER_LIBRARY ~/.brew/Cellar/sdl_mixer/1.2.12_3/lib/)

set(SDL_IMAGE_INCLUDE_DIR ~/.brew/Cellar/sdl_image/1.2.12_7/include/SDL/)
set(SDL_IMAGE_LIBRARY ~/.brew/Cellar/sdl_image/1.2.12_7/lib)

set(LIBFT_INCLUDE_DIR ./libft/include/)
set(LIBFT_LIBRARY ./libft/)

set(SOURCE ./src/)
set(INCLUDE ./include/)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL_MIXER_INCLUDE_DIR}
                    ${SDL_IMAGE_INCLUDE_DIR}
                    ${LIBFT_INCLUDE_DIR}
                    ${SOURCE}
                    ${INCLUDE})

link_directories(${SDL2_LIBRARY}
                 ${SDL_MIXER_LIBRARY}
                 ${SDL_IMAGE_LIBRARY}
                 ${LIBFT_LIBRARY}
                 ${SOURCE})

file(GLOB all
        "${INCLUDE}*.h"
        "${SOURCE}*.c")

add_executable(doom-nukem ${all})

target_link_libraries(doom-nukem -lft -lSDL2 -lSDL_image -lSDL_mixer)