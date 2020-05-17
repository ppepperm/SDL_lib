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
	t_door	*next;
	int		i;

	next = data.doors;
	while (next)
	{
		data.doors = next;
		next = next->next;
		free(data.doors);
	}
	while (i < 10)
	{
		SDL_DestroyTexture(data.textures[i]);
		SDL_DestroyTexture(data.textures_dark[i++]);
	}
	SDL_DestroyTexture(data.skybox);
	free(data.textures_dark);
	free(data.textures);
	free_map(&data, data.size.y - 1);
	SDL_DestroyRenderer(data.renderer);
	SDL_DestroyWindow(data.window);
	SDL_Quit();
}

int			main(int argc, char **argv)
{
	t_player	player;
	t_data		data;
	SDL_Event	event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	if (!init_data(argv[1], &data) || argc != 2)
		return (0);
	player = init_player(init_p2(data.start.x + 0.1, data.start.y + 0.1),
		init_p2(0, 1));
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
	return (EXIT_SUCCESS);
}
