#include "doom_nukem.h"

int 	main(int ar, char **av)
{
	t_sdl_main		sdl;
	t_sdl_image		img;

	sdl.sdl_img = &img;
	init_sdl(&sdl);
	int request = SDL_GetDesktopDisplayMode(0, &display_mode);
	return (0);
}