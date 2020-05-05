/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_door *get_door(t_map map, int posx, int posy)
{
	t_door *door;

	while (!(map.doors->pos.x == posx && map.doors->pos.y == posy))
	map.doors = map.doors->next;
	door = map.doors;
	return (door);
}

void doors_funk(t_door *doors)
{
	while (doors)
	{
		if ((doors->len == 1) && (doors->status == CLOSING))
			doors->status = CLOSED;
		else if ((doors->len > 0) && (doors->status == OPENING))
			doors->len -= 0.01;
		else if ((doors->len != 1) && (doors->status == CLOSING))
			doors->len += 0.01;
		else if ((doors->len < 0.01) && (doors->status == 3))
			doors->status = OPENED;

		if (doors->status == OPENED)
		{
			if(doors->time == 200)
			{
				doors->time = 0;
				doors->status = CLOSING;
			}
			else
				doors->time++;
		}
		doors = doors->next;
	}
}

void	dist_texx_sq(double *tex_x, t_i2 *count, t_ray ray, t_player pl)
{
	double dist;

	if (count->x == 0)
	{
		dist = ray.side.x * cos(ray.phase);
		*tex_x = pl.pos.y + ray.side.x * ray.dir.y;
		*tex_x -= floor(*tex_x);
	}
	else
	{
		dist = ray.side.y * cos(ray.phase);
		*tex_x = pl.pos.x + ray.side.y * ray.dir.x;
		*tex_x -= floor(*tex_x);
	}
	count->y = (int)(W_H/dist);
}

int	draw_doors(t_map map, t_ray *ray, double tex_x, SDL_Renderer *renderer, int x, t_player pl)
{
	t_p2 sw_ds;
	t_door *door;
	t_i2 count;
	double dist;

	if (map.map[ray->mp.y][ray->mp.x] == 9)
	{
		door = get_door(map, ray->mp.x, ray->mp.y);
		sw_ds = sw_ds_hor(tex_x, *ray);
		if (sw_ds.y < sw_ds.x) {
			ray->side.y += sw_ds.y;
			dist = ray->side.y * cos(ray->phase);
			count.x = 1;
			count.y = (int) (W_H / dist);
			tex_x = pl.pos.x + ray->side.y * ray->dir.x;
			tex_x -= floor(tex_x);
			put_texture(renderer, count, x, tex_x, 9, map);
			return (DONE);
		}
		else
		{
			ray->side.y += sw_ds.x;
			dist = ray->side.y * cos(ray->phase);
			count.x = 0;
			count.y = (int) (W_H / dist);
			tex_x = pl.pos.y + ray->side.y * ray->dir.y;
			tex_x -= floor(tex_x);
			put_texture(renderer, count, x, tex_x, 10, map);
			return (DONE);
		}
	}
	else if (map.map[ray->mp.y][ray->mp.x] == 10)
	{
		door = get_door(map, ray->mp.x, ray->mp.y);
		sw_ds = sw_dr_ver(tex_x, *ray);
		if (sw_ds.x < sw_ds.y) {
			ray->side.x += sw_ds.x;
			dist = ray->side.x * cos(ray->phase);
			count.x = 0;
			count.y = (int) (W_H / dist);
			tex_x = pl.pos.y + ray->side.x * ray->dir.y;
			tex_x -= floor(tex_x);
			if (tex_x > 1.0 - door->len)
			{
				tex_x = tex_x - 1 + door->len;
				put_texture(renderer, count, x, tex_x, 9, map);
				return (DONE);
			}
			else
			{
				sw_ds = sw_dr_ver(tex_x, *ray);
				if (sw_ds.x < sw_ds.y)
				{
					ray->side.x += sw_ds.x;
					ray->mp.x += ray->step.x;
				 	ray->hit = 0;
					ray->side = comp_sum(ray->side, ray->delta);
					return (GOING);
				}
				else
				{
					ray->side.x += sw_ds.y;
					dist = ray->side.x * cos(ray->phase);
					count.x = 1;
					count.y = (int) (W_H / dist);
					tex_x = pl.pos.x + ray->side.x * ray->dir.x;
					tex_x -= floor(tex_x);
					put_texture(renderer, count, x, tex_x, 10, map);
					return (DONE);
				}
			}

		}
		else
		{
			ray->side.x += sw_ds.y;
			dist = ray->side.x * cos(ray->phase);
			count.x = 1;
			count.y = (int) (W_H / dist);
			tex_x = pl.pos.x + ray->side.x * ray->dir.x;
			tex_x -= floor(tex_x);
			put_texture(renderer, count, x, tex_x, 10, map);
			return (DONE);
		}

	}
	return (DONE);
}