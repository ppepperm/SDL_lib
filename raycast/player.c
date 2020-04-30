#include "raycast.h"

t_player init_player(t_p2 pos, t_p2 dir)
{
	t_player pl;

	pl.pos = pos;
	pl.dir = dir;
	pl.rot = 0;
	pl.mov.x = 0;
	return (pl);
}

t_ray init_ray(t_player pl, t_map map,int x)
{
	t_ray ray;

	ray.phase = -FOV*(x/W_W - 0.5)*0.0174533;
	ray.dir = comp_multiply(pl.dir, init_p2(cos(ray.phase),sin(ray.phase)));
	ray.mp.x = (int)pl.pos.x;
	ray.mp.y = map.size.y - 1 - (int)pl.pos.y;
	if (ray.dir.x == 0)
		ray.delta = init_p2(1000000000, 1);
	else if (ray.dir.y == 0)
		ray.delta = init_p2(1, 1000000000);
	else
		ray.delta = init_p2(d_abs(1.0/ray.dir.x), d_abs(1.0/ray.dir.y));
	if (ray.dir.x < 0)
	{
		ray.side.x = (pl.pos.x - ray.mp.x)*ray.delta.x;
		ray.step.x = -1;
	}
	else
	{
		ray.side.x = (1 + ray.mp.x - pl.pos.x) * ray.delta.x;
		ray.step.x = 1;
	}
	if (ray.dir.y < 0)
	{
		ray.side.y = (pl.pos.y - (int)pl.pos.y)*ray.delta.y;
		ray.step.y = 1;
	}
	else
	{
		ray.side.y = (1 + (int)pl.pos.y - pl.pos.y) * ray.delta.y;
		ray.step.y = -1;
	}
	ray.hit = 0;
	return (ray);
}

void put_texture(SDL_Renderer *renderer, t_i2 count, int x, double tex_x, int type, t_map map1)
{
	SDL_Rect dst;
	SDL_Rect src;

	dst.x = x;
	dst.y = (W_H - count.y)/2;
	dst.w = 1;
	dst.h = count.y;
	src.x = (int)(tex_x*63.0);
	src.y = 0;
	src.h = 64;
	src.w = 1;
	if (count.x == 0)
		SDL_RenderCopy(renderer, map1.texs[type - 1], &src, &dst);
	else if (count.x == 1)
		SDL_RenderCopy(renderer, map1.texsd[type - 1], &src, &dst);
}

void raycast(t_map map1, t_player pl, SDL_Renderer *renderer)
{
	int x;
	t_i2 count;
	t_ray ray;
	double dist;
	double tex_x;
/*
	SDL_Surface *surface;
	surface = IMG_Load("textures/redbrick.png");
	SDL_Surface *f_surface = SDL_ConvertSurfaceFormat(surface,SDL_GetWindowPixelFormat(map1.window), 0);
	SDL_Texture *newTex = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(map1.window), SDL_TEXTUREACCESS_STREAMING,\
    f_surface->w, f_surface->h);
	void *pixels;
	int pitch;
	SDL_LockTexture(newTex, NULL, &pixels, &pitch);
	ft_memcpy(pixels, f_surface->pixels, f_surface->pitch*f_surface->h);
	SDL_UnlockTexture(newTex);*/
	x = 0;
	while (x <= W_W) {
		ray = init_ray(pl, map1, x);
		while (ray.hit == 0)
		{
			if (ray.side.x < ray.side.y) {
				ray.side.x += ray.delta.x;
				ray.mp.x += ray.step.x;
				count.x = 0;}
			else {
				ray.side.y += ray.delta.y;
				ray.mp.y += ray.step.y;
				count.x = 1;
			}
			if (map1.map[ray.mp.y][ray.mp.x] != 0)
				ray.hit = 1;
		}
		ray.side = comp_dif(ray.side, ray.delta);
		if (count.x == 0)
		{
			dist = ray.side.x * cos(ray.phase);
			tex_x = pl.pos.y + ray.side.x * ray.dir.y;
			tex_x -= floor(tex_x);
		}
		else
			{
			dist = ray.side.y * cos(ray.phase);
			tex_x = pl.pos.x + ray.side.y * ray.dir.x;
			tex_x -= floor(tex_x);
		}
		count.y = (int) (W_H/dist);
		//
		/*
		SDL_LockTexture(newTex, NULL, &pixels, &pitch);
		double z = 1;
		unsigned char *pix = (unsigned char*)pixels;
		t_i2 pixel;
		while (z <= W_H/2 - count.y/2) {
			double P = W_H / (2 * (count.y / 2 + z));
			P = P / cos(ray.phase);
			pixel.x = (int) ((pl.pos.x + P * ray.dir.x - floor(pl.pos.x + P * ray.dir.x)) * 63);
			pixel.y = (int) ((pl.pos.y + P * ray.dir.y - floor(pl.pos.y + P * ray.dir.y)) * 63);
			//printf("%d %d\n", pixel.x, pixel.y);
			int b = pix[pitch*pixel.y + pixel.x];
			int g = pix[pitch*pixel.y + pixel.x + 1];
			int r = pix[pitch*pixel.y + pixel.x + 2];
			int a = pix[pitch*pixel.y + pixel.x + 3];
			SDL_SetRenderDrawColor(renderer,r,g,b,a);
			SDL_RenderDrawPoint(renderer, x, W_H / 2 + count.y / 2 + z);
			z++;
		}
		*/
		//
		t_p2 sw_ds;
		if ( map1.map[ray.mp.y][ray.mp.x] < 9)
			put_texture(renderer, count, x, tex_x, map1.map[ray.mp.y][ray.mp.x], map1);
		else
		{
			if (map1.map[ray.mp.y][ray.mp.x] == 9)
			{
				if (ray.dir.x > 0)
				{
					sw_ds.x = (1 - tex_x) * ray.delta.x;
					sw_ds.y = 0.5 * ray.delta.y;
				}
				else
					{
					sw_ds.x = tex_x * ray.delta.x;
					sw_ds.y = 0.5 * ray.delta.y;
				}
				if (sw_ds.y < sw_ds.x) {
					ray.side.y += sw_ds.y;
					dist = ray.side.y * cos(ray.phase);
					count.x = 1;
					count.y = (int) (W_H / dist);
					tex_x = pl.pos.x + ray.side.y * ray.dir.x;
					tex_x -= floor(tex_x);
					put_texture(renderer, count, x, tex_x, 1, map1);
				}
				else
					{
					ray.side.y += sw_ds.x;
					dist = ray.side.y * cos(ray.phase);
					count.x = 0;
					count.y = (int) (W_H / dist);
					tex_x = pl.pos.y + ray.side.y * ray.dir.y;
					tex_x -= floor(tex_x);
					put_texture(renderer, count, x, tex_x, 1, map1);
				}
			}
			else if (map1.map[ray.mp.y][ray.mp.x] == 10)
			{
				if (ray.dir.y > 0)
				{
					sw_ds.y = (1 - tex_x) * ray.delta.y;
					sw_ds.x = 0.5 * ray.delta.x;
				}
				else
				{
					sw_ds.y = tex_x * ray.delta.y;
					sw_ds.x = 0.5 * ray.delta.x;
				}
				if (sw_ds.x < sw_ds.y) {
					ray.side.x += sw_ds.x;
					dist = ray.side.x * cos(ray.phase);
					count.x = 0;
					count.y = (int) (W_H / dist);
					tex_x = pl.pos.y + ray.side.x * ray.dir.y;
					tex_x -= floor(tex_x);
					put_texture(renderer, count, x, tex_x, 1, map1);
				}
				else
				{
					ray.side.x += sw_ds.y;
					dist = ray.side.x * cos(ray.phase);
					count.x = 1;
					count.y = (int) (W_H / dist);
					tex_x = pl.pos.x + ray.side.x * ray.dir.x;
					tex_x -= floor(tex_x);
					put_texture(renderer, count, x, tex_x, 1, map1);
				}

			}
		}

		x++;
	}
}