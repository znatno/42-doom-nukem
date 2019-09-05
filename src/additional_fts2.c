#include "doom_nukem.h"

void		draw_ceil_floor(t_draw_screen_calc *ds, t_player *p, t_tex_i tex_i)
{

	int y;

	y = ds->i->y_top[ds->it->x];
	while (++y <= ds->i->y_bottom[ds->it->x])
	{
		if (y >= ds->i->cya && y <= ds->i->cyb)
		{
			y = ds->i->cyb;
			continue;
		}
		ds->f->hei = y < ds->i->cya ? ds->f->yceil : ds->f->yfloor;
		ds->f->mapz = ds->f->hei * H * V_FOV / ((H / 2 - (float)y)
												- p->yaw * H * V_FOV);
		ds->f->mapx = ds->f->mapz * (W / 2 - (float)ds->it->x) / (W * H_FOV);
		ds->f->rtx = ds->f->mapz * ds->f->pcos + ds->f->mapx * ds->f->psin;
		ds->f->rtz = ds->f->mapz * ds->f->psin - ds->f->mapx * ds->f->pcos;
		ds->f->mapx = ds->f->rtx + p->where.x;
		ds->f->mapz = ds->f->rtz + p->where.y;
		ds->i->txtx1 = (unsigned int)(ds->f->mapx * 256);
		ds->i->txtz = (unsigned int)(ds->f->mapz * 256);
		if (y < ds->i->cya)
			pix1(p, ds, y, tex_i);
		else
			pix2(p, ds, y, tex_i);
	}
}

int			exit_doom(t_game *g)
{
	if (g->error)
		ft_putendl_fd("text", 2);
	else
		ft_putendl("text");
	unload_data(g);
	SDL_Quit();
	TTF_Quit();
	exit(0);
}

int			scaler_next(t_scaler *i)
{
	i->cache += i->fd;
	while (i->cache >= i->ca)
	{
		i->result += i->bop;
		i->cache -= i->ca;
	}
	return (i->result);
}

t_scaler	scalar_init(int a, int b, int c, int d, int f)
{
	t_scaler	s;

	s.result = d + (b - 1 - a) * (f - d) / (c - a);
	s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
	s.fd = abs(f - d);
	s.ca = abs(c - a);
	s.cache = (int)((b - 1 - a) * abs(f - d)) % abs(c - a);
	return (s);
}

int			ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y)
{
	int		*pixel;

	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	return (*pixel);
}
