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

int			main()
{
	t_player	player;
	t_data		data;
	SDL_Event	event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	if (!init_data("level.map", &data))
		return (0);
	player = init_player(init_p2(data.start.x, data.start.y),
		init_p2(sqrt(0.5), sqrt(0.5)));
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		SDL_SetRenderDrawColor(data.renderer, 60, 60, 60, 255);
		SDL_RenderClear(data.renderer);
		if (!event_keydown(&data, &player, event))
			break ;
		event_keyup(&player, event);
		event_move(&data, &player);
		doors_funk(data.doors);
		raycast(data, player, data.renderer);
		SDL_RenderPresent(data.renderer);
	}
	sdl_end(data);
	return EXIT_SUCCESS;
}
