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

void	event_keyup(t_player *player, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_W)
			player->mov.x = 0;
		if (event.key.keysym.scancode == SDL_SCANCODE_S)
			player->mov.x = 0;
		if (event.key.keysym.scancode == SDL_SCANCODE_A)
			player->rot = 0;
		if (event.key.keysym.scancode == SDL_SCANCODE_D)
			player->rot = 0;
	}
}

void	event_keydown(t_data *data, t_player *player, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_F)
		{
			data->map[(int)(data->size.y - 1 - player->pos.y) - 1]
				[(int)(player->pos.x)] = 1;
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_W)
			player->mov.x = 1;
		if(event.key.keysym.scancode == SDL_SCANCODE_S)
			player->mov.x = -1;
		if(event.key.keysym.scancode == SDL_SCANCODE_A)
			player->rot = 1;
		if(event.key.keysym.scancode == SDL_SCANCODE_D)
			player->rot = -1;
	}
}

void	event_move(t_data *data, t_player *player)
{
	if (player->mov.x != 0)
	{
		if (data->map[data->size.y - 1 - (int)player->pos.y]
			[(int)(player->pos.x + player->dir.x * 0.4 * player->mov.x
			+ player->mov.x * player->dir.x * SPD)] == 0)
		{
			player->pos.x += player->mov.x * player->dir.x * SPD;
		}
		if (data->map[data->size.y - 1 - (int)(player->pos.y + player->dir.y
			* 0.4 * player->mov.x + SPD * player->dir.y * player->mov.x)]
			[(int) player->pos.x] == 0)
		{
			player->pos.y += player->mov.x * player->dir.y * SPD;
		}
	}
	if (player->rot != 0)
	{
		player->dir = comp_multiply(player->dir,
			init_p2(cos(W * player->rot), sin(W * player->rot)));
	}
}
