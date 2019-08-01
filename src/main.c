
#include "doom_nukem.h"

int		main(int ar, char **av)
{
	t_sdl_main		sdl;


	init_sdl(&sdl);
	sdl.texture = load_texture("../textures/2grivna.jpg", &sdl);
	if (!sdl.texture)
		ERROR("texture");
	SDL_RenderClear(sdl.renderer);
	SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
	SDL_RenderPresent(sdl.renderer);

	SDL_Event 		event;
	bool 			quit;
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

	quit = false;
	while(!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if ((event.key.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
				quit = true;
			SDL_PumpEvents(); // обработчик событий.
		}
	}
	// Close and destroy the window
	SDL_DestroyWindow(sdl.window);

	// Clean up
	SDL_Quit();
	return (0);
}
