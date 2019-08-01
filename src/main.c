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
	sdl.surface = SDL_LoadBMP("textures/2grivna.jpg");
	if (!sdl.surface)
		ERROR("surface");
	sdl.texture = SDL_CreateTextureFromSurface(sdl.renderer, sdl.surface);
	if (!sdl.texture)
		ERROR("texture");
	SDL_FreeSurface(sdl.surface);
	SDL_RenderClear(sdl.renderer);
	SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
	return (0);
}