#include "doom_nukem.h"

/*
** Сирі і неробочі функції для переміщення (поки що)
**
** SDL_Rect — структура що містить в собі координати [x, y, w, h] вікна
** offset - крок
**
** Даний приклад був створений для переміщення картинки по вікну
*/

/*
void	move_forward(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.y -= offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}

void	move_backward(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.y += offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}

void	move_left(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.x -= offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}

void	move_right(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect &destrect, int offset = 5)
{
	destrect.x += offset;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, &destrect);
}
*/

void	render_update(t_sdl_main sdl, SDL_Texture* texture[], SDL_Rect* destrect[], int states[])
{
	SDL_RenderClear(sdl.renderer);
	if(states[0])
		SDL_RenderCopy(sdl.renderer, texture[0], NULL, destrect[0]);
	if(states[1])
		SDL_RenderCopy(sdl.renderer, texture[1], NULL, destrect[1]);
}