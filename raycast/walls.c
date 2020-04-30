/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void		calculation_height(t_parametrs *param, t_ray ray, t_player player)
{
	if (param->side == 0)
	{
		param->dist = ray.side.x * cos(ray.phase);
		param->texture_x = player.pos.y + ray.side.x * ray.dir.y;
		param->texture_x -= floor(param->texture_x);
	}
	else
	{
		param->dist = ray.side.y * cos(ray.phase);
		param->texture_x = player.pos.x + ray.side.y * ray.dir.x;
		param->texture_x -= floor(param->texture_x);
	}
	param->line_height = (int)(W_H / param->dist);
}

void	check_door(t_data *data, t_ray ray, SDL_Renderer *renderer, t_player player)
{
	if (data->map[ray.mp.y][ray.mp.x] == 9)
	{
		if (ray.dir.x > 0)
		{
			data->param.dist_small_door.x = (1 - data->param.texture_x) * ray.delta.x;
			data->param.dist_small_door.y = 0.5 * ray.delta.y;
		}
		else
			{
			data->param.dist_small_door.x = data->param.texture_x * ray.delta.x;
			data->param.dist_small_door.y = 0.5 * ray.delta.y;
		}
		if (data->param.dist_small_door.y < data->param.dist_small_door.x)
		{
			ray.side.y += data->param.dist_small_door.y;
			data->param.dist = ray.side.y * cos(ray.phase);
			data->param.side = 1;
			data->param.line_height = (int)(W_H / data->param.dist);
			data->param.texture_x = player.pos.x + ray.side.y * ray.dir.x;
			data->param.texture_x -= floor(data->param.texture_x);
			put_texture(renderer, data->param, 1, *data);
		}
		else
			{
			ray.side.y += data->param.dist_small_door.x;
			data->param.dist = ray.side.y * cos(ray.phase);
			data->param.side = 0;
			data->param.line_height = (int)(W_H / data->param.dist);
			data->param.texture_x = player.pos.y + ray.side.y * ray.dir.y;
			data->param.texture_x -= floor(data->param.texture_x);
			put_texture(renderer, data->param, 1, *data);
		}
	}
	else if (data->map[ray.mp.y][ray.mp.x] == 10)
	{
		if (ray.dir.y > 0)
		{
			data->param.dist_small_door.y = (1 - data->param.texture_x) * ray.delta.y;
			data->param.dist_small_door.x = 0.5 * ray.delta.x;
		}
		else
		{
			data->param.dist_small_door.y = data->param.texture_x * ray.delta.y;
			data->param.dist_small_door.x = 0.5 * ray.delta.x;
		}
		if (data->param.dist_small_door.x < data->param.dist_small_door.y) {
			ray.side.x += data->param.dist_small_door.x;
			data->param.dist = ray.side.x * cos(ray.phase);
			data->param.side = 0;
			data->param.line_height = (int)(W_H / data->param.dist);
			data->param.texture_x = player.pos.y + ray.side.x * ray.dir.y;
			data->param.texture_x -= floor(data->param.texture_x);
			put_texture(renderer, data->param, 1, *data);
		}
		else
		{
			ray.side.x += data->param.dist_small_door.y;
			data->param.dist = ray.side.x * cos(ray.phase);
			data->param.side = 1;
			data->param.line_height = (int)(W_H / data->param.dist);
			data->param.texture_x = player.pos.x + ray.side.x * ray.dir.x;
			data->param.texture_x -= floor(data->param.texture_x);
			put_texture(renderer, data->param, 1, *data);
		}
	}
}
