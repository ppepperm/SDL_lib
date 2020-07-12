/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:30:29 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 12:30:30 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	sdl_end(t_data data)
{
	int		i;

	free_doors(data.doors);
	i = 0;
	if (data.textures)
	{
		while (i < 10)
			SDL_DestroyTexture(data.textures[i++]);
		free(data.textures);
	}
	i = 0;
	if (data.textures_dark)
	{
		while (i < 10)
			SDL_DestroyTexture(data.textures_dark[i++]);
		free(data.textures_dark);
	}
	if (data.skybox)
		SDL_DestroyTexture(data.skybox);
	free_map(&data, data.size.y - 1);
	if (data.renderer)
		SDL_DestroyRenderer(data.renderer);
	if (data.window)
		SDL_DestroyWindow(data.window);
	SDL_Quit();
}

static void	reset_data(t_data *data)
{
	data->map = NULL;
	data->textures = NULL;
	data->textures_dark = NULL;
	data->skybox = NULL;
	data->window = NULL;
	data->renderer = NULL;
	data->doors = NULL;
}

static int	check_input(t_data *data, char **argv, int argc)
{
	reset_data(data);
	if (argc != 2)
		return (0);
	else if (!init_data(argv[1], data))
	{
		sdl_end(*data);
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_player	player;
	t_data		data;
	SDL_Event	event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0
		|| !check_input(&data, argv, argc))
		return (0);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	player = init_player(init_p2(data.start.x + 0.1, data.start.y + 0.1),
		init_p2(0, 1));
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		if (SDL_SetRenderDrawColor(data.renderer, 60, 60, 60, 255) < 0
			|| SDL_RenderClear(data.renderer) < 0
			|| !event_keydown(&data, &player, event))
			break ;
		event_keyup(&player, event);
		event_move(&data, &player);
		doors_funk(data.doors);
		if (!raycast(data, player, data.renderer))
			break ;
		SDL_RenderPresent(data.renderer);
	}
	sdl_end(data);
	return (EXIT_SUCCESS);
}
