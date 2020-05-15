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

static t_p2	dist_small_door_vertical(double texture_x, t_ray ray)
{
	t_p2	dist_small_door;

	if (ray.dir.y > 0)
	{
		dist_small_door.y = (1 - texture_x) * ray.delta.y;
		dist_small_door.x = 0.5 * ray.delta.x;
	}
	else
	{
		dist_small_door.y = texture_x * ray.delta.y;
		dist_small_door.x = 0.5 * ray.delta.x;
	}
	return (dist_small_door);
}

static int	draw_vertical_door_side(t_ray *ray, t_data data,
									SDL_Renderer *renderer, t_player player)
{
	data.param.dist_small_door =
			dist_small_door_vertical(data.param.texture_x, *ray);
	ray->side.x += data.param.dist_small_door.y;
	data.param.dist = ray->side.x * cos(ray->phase);
	data.param.side = 1;
	data.param.line_height = (int)(W_H / data.param.dist);
	data.param.texture_x = player.pos.x + ray->side.x * ray->dir.x;
	data.param.texture_x -= floor(data.param.texture_x);
	put_texture(renderer, 10, data);
	return (DONE);
}

static void	vertical_preparations(t_ray *ray, t_player player,
								t_parametrs *param)
{
	param->dist_small_door = dist_small_door_vertical(param->texture_x, *ray);
	ray->side.x += param->dist_small_door.x;
	param->dist = ray->side.x * cos(ray->phase);
	param->side = 0;
	param->line_height = (int)(W_H / param->dist);
	param->texture_x = player.pos.y + ray->side.x * ray->dir.y;
	param->texture_x -= floor(param->texture_x);
}

static int	name_vertical(t_data data, t_ray *ray, SDL_Renderer *renderer,
					t_player player)
{
	if (data.param.texture_x > 1.0 - data.param.door->len)
	{
		data.param.texture_x = data.param.texture_x - 1 + data.param.door->len;
		put_texture(renderer, 9, data);
		return (DONE);
	}
	else
	{
		data.param.dist_small_door =
				dist_small_door_vertical(data.param.texture_x, *ray);
		if (data.param.dist_small_door.x < data.param.dist_small_door.y)
		{
			ray->side.x += data.param.dist_small_door.x;
			ray->map.x += ray->step.x;
			ray->hit = 0;
			ray->side = comp_sum(ray->side, ray->delta);
			return (GOING);
		}
		else
			return (draw_vertical_door_side(ray, data, renderer, player));
	}
}

int			processing_door_vertical(t_data data, t_ray *ray,
								SDL_Renderer *renderer, t_player player)
{
	data.param.dist_small_door =
			dist_small_door_vertical(data.param.texture_x, *ray);
	if (data.param.dist_small_door.x < data.param.dist_small_door.y)
	{
		vertical_preparations(ray, player, &data.param);
		return (name_vertical(data, ray, renderer, player));
	}
	else
		return (draw_vertical_door_side(ray, data, renderer, player));
}
