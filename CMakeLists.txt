cmake_minimum_required(VERSION 3.14)
project(doom-nukem C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR ~/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/Cellar/sdl2/2.0.9_1/lib/)

set(SDL_MIXER_INCLUDE_DIR ~/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2/)
set(SDL_MIXER_LIBRARY ~/.brew/Cellar/sdl2_mixer/2.0.4/lib/)

set(SDL_IMAGE_INCLUDE_DIR ~/.brew/Cellar/sdl2_image/2.0.5/include/SDL2/)
set(SDL_IMAGE_LIBRARY ~/.brew/Cellar/sdl2_image/2.0.5/lib/)

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


#
#file(GLOB all
#        "${INCLUDE}*.h"
#        "${SOURCE}*.c")

#include_directories(~/.brew/Cellar/sdl/1.2.15_1/include/SDL/)
#include_directories(~/.brew/include/SDL libft/include/)

#link_directories(~/.brew/Cellar/sdl/1.2.15_1/lib/)
#link_directories(~/.brew/lib libft/)

add_executable(doom-nukem   src/main.c
                            src/float_to_str.c
                            src/draw_line.c
                            src/record_data.c src/env_display.c
                            src/list_managing.c src/stack_manipulation.c
                            )


#target_link_libraries(doom-nukem -lSDL)
target_link_libraries(doom-nukem -g -fsanitize=address -lft -lSDL2 -lSDL2_image -lSDL2_mixer)
#target_link_libraries(doom-nukem "-D_GNU_SOURCE=1" "-D_THREAD_SAFE" "-lSDLmain"
#"-lSDL -Wl,-framework,Cocoa" "-lft")