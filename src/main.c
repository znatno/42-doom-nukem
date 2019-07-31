#include <stdio.h>
#include "/Users/vopolonc/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/SDL.h"

int 	main(int ar, char **av)
{
	SDL_DisplayMode	display_mode;
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
		printf("Ah SHIT, here we go again");
	int request = SDL_GetDesktopDisplayMode(0, &display_mode);
	printf("eg");
	return (0);
}