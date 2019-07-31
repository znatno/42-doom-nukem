#include <stdio.h>
#include "SDL.h"
#include "doom_nukem.h"

int 	main(int ar, char **av)
{
	t_sdl_main		sdl;

	init_sdl(&sdl);
	SDL_RenderCopy(sdl.renderer, sdl.texture, &sdl.src_rect, &sdl.dst_rect);
	SDL_RenderPresent(sdl.renderer);
	return (0);
}