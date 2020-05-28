/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:09:26 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 13:09:28 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static t_door	*get_door(t_data data, int pos_x, int pos_y)
{
	t_door	*door;

	while (data.doors && !(data.doors->pos.x == pos_x
		&& data.doors->pos.y == pos_y))
	{
		data.doors = data.doors->next;
	}
	door = data.doors;
	return (door);
}

int				check_for_door(t_data data, int x, int y)
{
	t_door	*door;

	door = get_door(data, x, y);
	if (data.map[y][x] <= 9)
		return (0);
	if (door->status == OPENED && door)
		return (1);
	return (0);
}

void			door_handling(t_data *data, t_player *player)
{
	t_door	*door;
	double	spd;

	spd = SPD + 1;
	if (data->map
		[data->size.y - 1 - (int)(player->pos.y + spd * player->dir.y)]
		[(int)(player->pos.x + player->dir.x * spd)] == 10
		|| data->map
		[data->size.y - 1 - (int)(player->pos.y + spd * player->dir.y)]
		[(int)(player->pos.x + player->dir.x * spd)] == 11)
	{
		door = get_door(*data, (int)(player->pos.x + player->dir.x * spd),
			data->size.y - 1 - (int)(player->pos.y + spd * player->dir.y));
		if (door->status == OPENED)
			door->status = CLOSING;
		else if (door->status == CLOSED)
			door->status = OPENING;
	}
}

void			doors_funk(t_door *doors)
{
	while (doors)
	{
		if ((doors->len == 1) && (doors->status == CLOSING))
			doors->status = CLOSED;
		else if ((doors->len > 0) && (doors->status == OPENING))
			doors->len -= 0.02;
		else if ((doors->len != 1) && (doors->status == CLOSING))
			doors->len += 0.02;
		else if ((doors->len < 0.01) && (doors->status == 3))
			doors->status = OPENED;
		if (doors->status == OPENED)
		{
			if (doors->time == 300)
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

int				draw_doors(t_data data, t_ray *ray,
		SDL_Renderer *renderer, t_player player)
{
	data.param.door = get_door(data, ray->map.x, ray->map.y);
	if (data.map[ray->map.y][ray->map.x] == 11)
	{
		return (processing_door_horizontal(data, ray, renderer, player));
	}
	else if (data.map[ray->map.y][ray->map.x] == 10)
	{
		return (processing_door_vertical(data, ray, renderer, player));
	}
	return (DONE);
}
