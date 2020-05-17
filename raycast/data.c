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

void		init_doors(t_data *data, t_i2 count)
{
	t_door	*door_new;

	if (data->doors_num == 0)
	{
		data->doors = (t_door*)malloc(sizeof(t_door));
		data->doors->pos = count;
		data->doors->len = 1;
		data->doors->status = CLOSED;
		data->doors->next = NULL;
		data->doors->time = 0;
		data->doors_num += 1;
	}
	else
	{
		door_new = (t_door*)malloc(sizeof(t_door));
		door_new->pos = count;
		door_new->len = 1;
		door_new->status = CLOSED;
		door_new->next = data->doors;
		door_new->time = 0;
		data->doors = door_new;
		data->doors_num += 1;
	}
}

t_player	init_player(t_p2 pos, t_p2 dir)
{
	t_player	player;

	player.pos = pos;
	player.dir = dir;
	player.rot = 0;
	player.mov.x = 0;
	return (player);
}

int			init_data(char *fname, t_data *data)
{
	int	fd;

	fd = open(fname, O_RDWR);
	if (fd < 0)
	{
		ft_putstr("Wrong file name\n");
		return (0);
	}
	if (!init_coordinates(&(data->size), fd)
		|| !init_coordinates(&(data->start), fd) || !init_map(data, fd))
	{
		return (0);
	}
	data->window = SDL_CreateWindow("Woolf3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, 0);
	data->renderer = SDL_CreateRenderer(data->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 0);
	SDL_RenderClear(data->renderer);
	init_textures(data, data->renderer);
	init_textures_dark(data, data->renderer);
	init_skybox(data, data->renderer);
	return (1);
}
