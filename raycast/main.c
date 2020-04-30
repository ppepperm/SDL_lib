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

static void	sdl_end(t_data data)
{
	SDL_DestroyRenderer(data.renderer);
	SDL_DestroyWindow(data.window);
	SDL_Quit();
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

int			main()
{
	t_player	player;
	t_data		data;
	SDL_Event	event;

	SDL_Init(SDL_INIT_VIDEO);
	data = init_map("jopa.map");
	player = init_player(init_p2(data.start.x, data.start.y),
		init_p2(sqrt(0.5), sqrt(0.5)));
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		SDL_SetRenderDrawColor(data.renderer, 60, 60, 60, 255);
		SDL_RenderClear(data.renderer);
		event_keydown(&data, &player, event);
		event_keyup(&player, event);
		event_move(&data, &player);
		raycast(data, player, data.renderer);
		SDL_RenderPresent(data.renderer);
	}
	sdl_end(data);
	return EXIT_SUCCESS;
}
