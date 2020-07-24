/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:41:12 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 13:41:13 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int		event_keydown(t_data *data, t_player *player, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
		if (event.key.keysym.scancode == SDL_SCANCODE_W)
			player->mov.x = 1;
		if (event.key.keysym.scancode == SDL_SCANCODE_S)
			player->mov.x = -1;
		if (event.key.keysym.scancode == SDL_SCANCODE_A)
			player->rot = 1;
		if (event.key.keysym.scancode == SDL_SCANCODE_D)
			player->rot = -1;
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			door_handling(data, player);
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			return (0);
	}
	return (1);
}

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

void	event_move(t_data *data, t_player *player)
{
	int	temp;

	if (player->mov.x != 0)
	{
		temp = data->map[data->size.y - 1 - (int)player->pos.y]
			[(int)(player->pos.x + player->dir.x * 0.4 * player->mov.x
			+ player->mov.x * player->dir.x * SPD)];
		if (temp == 0 ||
		check_for_door(*data, (int)(player->pos.x + player->dir.x
				* 0.4 * player->mov.x + player->mov.x * player->dir.x * SPD),
				data->size.y - 1 - (int)player->pos.y) == 1)
			player->pos.x += player->mov.x * player->dir.x * SPD;
		temp = data->map[data->size.y - 1 - (int)(player->pos.y + player->dir.y
			* 0.4 * player->mov.x + SPD * player->dir.y * player->mov.x)]
			[(int)player->pos.x];
		if (temp == 0 ||
		check_for_door(*data, (int)player->pos.x, data->size.y - 1
				- (int)(player->pos.y + player->dir.y * 0.4 * player->mov.x
				+ SPD * player->dir.y * player->mov.x)) == 1)
			player->pos.y += player->mov.x * player->dir.y * SPD;
	}
	if (player->rot != 0)
		player->dir = comp_multiply(player->dir,
			init_p2(cos(W * player->rot), sin(W * player->rot)));
}
