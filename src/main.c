#include "doom_nukem.h"

int 	main(int ar, char **av)
{
	t_sdl_main		sdl;


	init_sdl(&sdl);
	if (!sdl.surface)
		ERROR("surface");
	sdl.texture = load_texture("../textures/2grivna.jpg", &sdl);
	if (!sdl.texture)
		ERROR("texture");
	SDL_RenderClear(sdl.renderer);
	SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);
	return (0);
}