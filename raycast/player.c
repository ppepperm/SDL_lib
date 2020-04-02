#include "raycast.h"

t_player init_player(t_p2 pos, t_p2 dir)
{
	t_player pl;

	pl.pos = pos;
	pl.dir = dir;
	return (pl);
}

t_ray init_ray(t_player pl, int x)
{
	t_ray ray;

	ray.phase = phase = -FOV*(x/W_W - 0.5)*0.0174533;
	ray.dir = comp_multiply(pl.dir, init_p2(cos(phase),sin(phase)));
	ray.mp.x = (int)pl.pos.x;
	ray.mp.y = MAP_H - 1 - (int)pl.pos.y;
	if (ray.dir.x == 0)
		ray.delta = init_p2(0, 1);
	else if (ray.dir.y == 0)
		ray.delta = init_p2(1, 0);
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
		ray.side.y = (pl.pos.y - ray.mp.y)*ray.delta.y;
		ray.step.y = 1;
	}
	else
	{
		ray.side.y = (1 + ray.mp.y - pl.pos.y) * ray.delta.y;
		ray.step.y = 1;
	}
	hit = 0;
}