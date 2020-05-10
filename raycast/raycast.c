/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void		ray_direction(t_ray *ray, t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->side.x = (player.pos.x - ray->map.x) * ray->delta.x;
		ray->step.x = -1;
	}
	else
	{
		ray->side.x = (1 + ray->map.x - player.pos.x) * ray->delta.x;
		ray->step.x = 1;
	}
	if (ray->dir.y < 0)
	{
		ray->side.y = (player.pos.y - (int)player.pos.y) * ray->delta.y;
		ray->step.y = 1;
	}
	else
	{
		ray->side.y = (1 + (int)player.pos.y - player.pos.y) * ray->delta.y;
		ray->step.y = -1;
	}
}

static t_ray	init_ray(t_player player, t_data map,int x)
{
	t_ray	ray;

	ray.phase = -FOV * (x / W_W - 0.5) * 0.0174533;
	ray.dir = comp_multiply(player.dir, init_p2(cos(ray.phase), sin(ray.phase)));
	ray.map.x = (int)player.pos.x;
	ray.map.y = map.size.y - 1 - (int)player.pos.y;
	if (ray.dir.x == 0)
		ray.delta = init_p2(1000000000, 1);
	else if (ray.dir.y == 0)
		ray.delta = init_p2(1, 1000000000);
	else
		ray.delta = init_p2(d_abs(1.0 / ray.dir.x), d_abs(1.0 / ray.dir.y));
	ray_direction(&ray, player);
	ray.hit = 0;
	return (ray);
}

static void		dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->map.x += ray->step.x;
			data->param.side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->map.y += ray->step.y;
			data->param.side = 1;
		}
		if (data->map[ray->map.y][ray->map.x] != 0)
			ray->hit = data->map[ray->map.y][ray->map.x];
	}
	ray->side = comp_dif(ray->side, ray->delta);
}

static void		calculation_height(t_parametrs *param, t_ray ray, t_player player)
{
	double	dist;

	if (param->side == 0)
	{
		dist = ray.side.x * cos(ray.phase);
		param->texture_x = player.pos.y + ray.side.x * ray.dir.y;
		param->texture_x -= floor(param->texture_x);
	}
	else
	{
		dist = ray.side.y * cos(ray.phase);
		param->texture_x = player.pos.x + ray.side.y * ray.dir.x;
		param->texture_x -= floor(param->texture_x);
	}
	param->line_height = (int)(W_H / dist);
}

void			raycast(t_data data, t_player player, SDL_Renderer *renderer)
{
	t_ray	ray;

	data.param.x = 0;
	put_skybox(renderer, data, player);
	while (data.param.x <= W_W)
	{
		ray = init_ray(player, data, data.param.x);
		data.param.ray_status = GOING;
		while (data.param.ray_status == GOING)
		{
			dda(&data, &ray);
			calculation_height(&data.param, ray, player);
			if (texture_selection(&data, renderer, &ray, player))
				continue ;
		}
		data.param.x++;
	}
}
