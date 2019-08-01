
#include "doom_nukem.h"

void	game(t_sdl_main *sdl)
{
	SDL_Event 		event;
	bool 			quit;
	const Uint8		*keyboard_state;

	keyboard_state = SDL_GetKeyboardState(NULL);
	quit = false;
	while(!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (keyboard_state[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT)
				quit = true;
			SDL_PumpEvents(); // обработчик событий
		}
	}
}

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
	game(&sdl);
	SDL_DestroyWindow(sdl.window); // Close and destroy the window
	SDL_Quit(); // Clean up
	return (0);
}
