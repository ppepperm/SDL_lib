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

static t_p2	dist_small_door_horizontal(double texture_x, t_ray ray)
{
	t_p2	dist_small_door;

	if (ray.dir.x > 0)
	{
		dist_small_door.x = (1 - texture_x) * ray.delta.x;
		dist_small_door.y = 0.5 * ray.delta.y;
	}
	else
	{
		dist_small_door.x = texture_x * ray.delta.x;
		dist_small_door.y = 0.5 * ray.delta.y;
	}
	return (dist_small_door);
}

static int	draw_horizontal_door_side(t_ray *ray, t_data data,
										SDL_Renderer *renderer, t_player player)
{
	data.param.dist_small_door
		= dist_small_door_horizontal(data.param.texture_x, *ray);
	ray->side.y += data.param.dist_small_door.x;
	data.param.dist = ray->side.y * cos(ray->phase);
	data.param.side = 0;
	data.param.line_height = (int)(W_H / data.param.dist);
	data.param.texture_x = player.pos.y + ray->side.y * ray->dir.y;
	data.param.texture_x -= floor(data.param.texture_x);
	put_texture(renderer, 10, data);
	return (DONE);
}

static void	horizontal_preparations(t_ray *ray, t_player player,
									t_parametrs *param)
{
	param->dist_small_door = dist_small_door_horizontal(param->texture_x, *ray);
	ray->side.y += param->dist_small_door.y;
	param->dist = ray->side.y * cos(ray->phase);
	param->side = 1;
	param->line_height = (int)(W_H / param->dist);
	param->texture_x = player.pos.x + ray->side.y * ray->dir.x;
	param->texture_x -= floor(param->texture_x);
}

static int	name_horizontal(t_data data, t_ray *ray, SDL_Renderer *renderer,
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
		data.param.dist_small_door
			= dist_small_door_horizontal(data.param.texture_x, *ray);
		if (data.param.dist_small_door.y < data.param.dist_small_door.x)
		{
			ray->side.y += data.param.dist_small_door.y;
			ray->map.y += ray->step.y;
			ray->hit = 0;
			ray->side = comp_sum(ray->side, ray->delta);
			return (GOING);
		}
		else
			return (draw_horizontal_door_side(ray, data, renderer, player));
	}
}

int			processing_door_horizontal(t_data data, t_ray *ray, SDL_Renderer *renderer,
								t_player player)
{
	data.param.dist_small_door
		= dist_small_door_horizontal(data.param.texture_x, *ray);
	if (data.param.dist_small_door.y < data.param.dist_small_door.x)
	{
		horizontal_preparations(ray, player, &data.param);
		return (name_horizontal(data, ray, renderer, player));
	}
	else
		return (draw_horizontal_door_side(ray, data, renderer, player));
}
