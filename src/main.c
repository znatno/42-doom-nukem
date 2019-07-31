#include "doom_nukem.h"

int 	main(int ar, char **av)
{
	t_sdl_main		sdl;


	init_sdl(&sdl);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
							 "Missing file",
							 "File is missing. Please reinstall the program.",
							 NULL);
	SDL_RenderCopy(sdl.renderer, sdl.texture, &sdl.src_rect, &sdl.dst_rect);
	SDL_RenderPresent(sdl.renderer);
	sdl.texture = IMG_Load("textures/2grivna.jpg");
	SDL_Surface test;

	return (0);
}