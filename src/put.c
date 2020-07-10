/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:40:30 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 13:40:32 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int		put_texture(SDL_Renderer *renderer, int type, t_data data)
{
	SDL_Rect	dst;
	SDL_Rect	src;

	dst.x = data.param.x;
	dst.y = (W_H - data.param.line_height) / 2;
	dst.w = 1;
	dst.h = data.param.line_height;
	src.x = (int)(data.param.texture_x * 63.0);
	src.y = 0;
	src.h = 64;
	src.w = 1;
	if (data.param.side == 0)
	{
		if (SDL_RenderCopy(renderer,
			data.textures[type % 11 - 1], &src, &dst) < 0)
			return (0);
	}
	else if (data.param.side == 1)
		if (SDL_RenderCopy(renderer,
			data.textures_dark[type % 11 - 1], &src, &dst) < 0)
			return (0);
	return (1);
}

int		put_skybox(SDL_Renderer *renderer, t_data data, t_player player)
{
	SDL_Rect	dst;
	SDL_Rect	src;
	double		angle;

	angle = acos(comp_dot(init_p2(0, 1), player.dir)) * 57.2957795131;
	if (player.dir.x < 0)
	{
		angle = 180 + (180 - angle);
	}
	src.x = angle;
	src.y = 0;
	src.w = 360;
	src.h = 90;
	dst.x = 0;
	dst.y = 0;
	dst.w = W_W;
	dst.h = W_H / 2;
	if (SDL_RenderCopy(renderer, data.skybox, &src, &dst) < 0)
		return (0);
	return (1);
}

static int	processing_all_sides(t_data *data, SDL_Renderer *renderer,
								t_ray *ray)
{
	if (data->param.side == 0)
	{
		if (ray->dir.x > 0)
		{
			if (!put_texture(renderer, 1, *data))
				return (0);
		}
		else
			if (!put_texture(renderer, 2, *data))
				return (0);
	}
	else
	{
		if (ray->dir.y > 0)
		{
			if (!put_texture(renderer, 3, *data))
				return (0);
		}
		else
			if (!put_texture(renderer, 4, *data))
				return (0);
	}
	return (1);
}

static int	check_texture_door(t_data *data, SDL_Renderer *renderer, t_ray *ray,
							t_player player)
{
	if (data->map[data->size.y - 1 - (int)player.pos.y][(int)player.pos.x] == 10
		|| data->map[data->size.y - 1 - (int)player.pos.y]
		[(int)player.pos.x] == 11)
	{
		if ((abs(data->size.y - 1 - (int)player.pos.y - ray->map.y) == 1
			&& abs((int)player.pos.x - ray->map.x) < 1)
			|| (abs((int)player.pos.x - ray->map.x) == 1
			&& abs(data->size.y - 1 - (int)player.pos.y - ray->map.y) < 1))
		{
			if (!put_texture(renderer, 10, *data))
				return (0);
			data->param.ray_status = DONE;
			return (1);
		}
	}
	return (0);
}

int			texture_selection(t_data *data, SDL_Renderer *renderer, t_ray *ray,
							t_player player)
{
	if (check_texture_door(data, renderer, ray, player))
		return (1);
	if (ray->hit < 9 || ray->hit == 12)
	{
		if (!put_texture(renderer,
			data->map[ray->map.y][ray->map.x], *data))
			return (-1);
		else
			data->param.ray_status = DONE;
	}
	else if (ray->hit == 9)
	{
		if (!processing_all_sides(data, renderer, ray))
			return (-1);
		data->param.ray_status = DONE;
		return (1);
	}
	else
		if ((data->param.ray_status
			= draw_doors(*data, ray, renderer, player)) < 0)
			return (-1);
	return (0);
}
