cmake_minimum_required(VERSION 3.14)
project(doom-nukem C)

set(CMAKE_C_STANDARD 99)

<<<<<<< HEAD
<<<<<<< HEAD
# SDL2
set(SDL2_INCLUDE_DIR ~/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/Cellar/sdl2/2.0.9_1/lib/)
# SDL2 Mixer
set(SDL_MIXER_INCLUDE_DIR ~/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2/)
set(SDL_MIXER_LIBRARY ~/.brew/Cellar/sdl2_mixer/2.0.4/lib/)
# SDL2 Image
set(SDL_IMAGE_INCLUDE_DIR ~/.brew/Cellar/sdl2_image/2.0.5/include/SDL2/)
set(SDL_IMAGE_LIBRARY ~/.brew/Cellar/sdl2_image/2.0.5/lib/)
# SDL2 TTF
set(SDL_TTF_INCLUDE_DIR ~/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2/)
set(SDL_TTF_LIBRARY ~/.brew/Cellar/sdl2_ttf/2.0.15/lib/)


=======
=======
>>>>>>> editor_simple
set(SDL2_INCLUDE_DIR ~/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/)
set(SDL2_LIBRARY ~/.brew/Cellar/sdl2/2.0.9_1/lib/)

set(SDL_MIXER_INCLUDE_DIR ~/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2/)
set(SDL_MIXER_LIBRARY ~/.brew/Cellar/sdl2_mixer/2.0.4/lib/)

set(SDL_IMAGE_INCLUDE_DIR ~/.brew/Cellar/sdl2_image/2.0.5/include/SDL2/)
set(SDL_IMAGE_LIBRARY ~/.brew/Cellar/sdl2_image/2.0.5/lib/)

set(SDL_TTF_INCLUDE_DIR ~/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2/)
set(SDL_TTF_LIBRARY ~/.brew/Cellar/sdl2_ttf/2.0.15/lib/)

>>>>>>> map_editor
set(LIBFT_INCLUDE_DIR ./libft/include/)
set(LIBFT_LIBRARY ./libft/)

set(SOURCE ./src/)
set(INCLUDE ./include/)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL_MIXER_INCLUDE_DIR}
                    ${SDL_IMAGE_INCLUDE_DIR}
                    ${SDL_TTF_INCLUDE_DIR}
                    ${LIBFT_INCLUDE_DIR}
                    ${SOURCE}
                    ${INCLUDE})

link_directories(${SDL2_LIBRARY}
                 ${SDL_MIXER_LIBRARY}
<<<<<<< HEAD
                 ${SDL_IMAGE_LIBRARY}
                 ${SDL_TTF_LIBRARY}
=======
                 ${SDL_TTF_LIBRARY}
                 ${SDL_IMAGE_LIBRARY}
>>>>>>> map_editor
                 ${LIBFT_LIBRARY}
                 ${SOURCE})


<<<<<<< HEAD

file(GLOB all
        "${INCLUDE}*.h"
        "${SOURCE}*.c")
=======
#
#file(GLOB all
#        "${INCLUDE}*.h"
#        "${SOURCE}*.c")
>>>>>>> editor_simple

#include_directories(~/.brew/Cellar/sdl/1.2.15_1/include/SDL/)
#include_directories(~/.brew/include/SDL libft/include/)

#link_directories(~/.brew/Cellar/sdl/1.2.15_1/lib/)
#link_directories(~/.brew/lib libft/)
<<<<<<< HEAD
<<<<<<< HEAD

add_executable(doom-nukem   ${all})

#target_link_libraries(doom-nukem -lSDL)
target_link_libraries(doom-nukem -lft
                        -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
=======

add_executable(doom-nukem   ${all} src/main_b.c src/main_c.c src/main_d.c src/main_e.c src/main_f.c src/list_managing_b.c src/list_managing_c.c src/list_managing_d.c src/list_managing_e.c src/record_data_b.c)


#target_link_libraries(doom-nukem -lSDL)
target_link_libraries(doom-nukem -O2 -lft -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf) #-g -fsanitize=address)
>>>>>>> map_editor
=======

add_executable(doom-nukem   src/main.c
                            src/float_to_str.c
                            src/draw_line.c
                            src/record_data.c src/env_display.c
                            src/list_managing.c)


#target_link_libraries(doom-nukem -lSDL)
target_link_libraries(doom-nukem -g -fsanitize=address -lft -lSDL2 -lSDL2_image -lSDL2_mixer)
>>>>>>> editor_simple
#target_link_libraries(doom-nukem "-D_GNU_SOURCE=1" "-D_THREAD_SAFE" "-lSDLmain"
#"-lSDL -Wl,-framework,Cocoa" "-lft")