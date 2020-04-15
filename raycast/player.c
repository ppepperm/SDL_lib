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

void raycast(t_map map1, t_player pl, SDL_Renderer *renderer)
{
	int x;
	t_i2 count;
	t_ray ray;
	double dist;
	SDL_Rect dst;
	SDL_Rect src;
	double tex_x;

	x = 0;
	while (x <= W_W)
	{
		ray = init_ray(pl, map1, x);
		while (ray.hit == 0)
		{
			if (ray.side.x < ray.side.y)
			{
				ray.side.x += ray.delta.x;
				ray.mp.x += ray.step.x;
				count.x = 0;
			}
			else
			{
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
			tex_x = pl.pos.y + ray.side.x*ray.dir.y;
			tex_x -= floor(tex_x);
		}
		else
		{
			dist = ray.side.y * cos(ray.phase);
			tex_x = pl.pos.x + ray.side.y*ray.dir.x;
			tex_x -= floor(tex_x);
		}
		count.y = (int)(W_H/dist);

		dst.x = x;
		dst.y = (W_H - count.y)/2;
		dst.w = 1;
		dst.h = count.y;
		src.x = (int)(tex_x*63.0);
		src.y = 0;
		src.h = 64;
		src.w = 1;
		if (count.x == 0)
			SDL_RenderCopy(renderer, map1.texs[map1.map[ray.mp.y][ray.mp.x] - 1],\
		&src, &dst);
		else if (count.x == 1)
			SDL_RenderCopy(renderer, map1.texsd[map1.map[ray.mp.y][ray.mp.x] - 1],\
		&src, &dst);
		x++;
	}
}