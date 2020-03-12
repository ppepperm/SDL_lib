/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kekush.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "2D_ray.h"

int main(void) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	t_line line;
	t_line line2;
	t_p2   cross;
	t_player pl;
	int i;

	i = 0;
	pl = init_player(init_p2(100,100),160,100);
	pl = pl;
	line = init_line(0, 100, 200, 0);
	line2 = init_line(100, 200, -200,100);
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	draw_line(renderer,line,255 * 256 * 256 + 255 * 256 + 255);
	draw_line(renderer,line2,255 * 256 * 256 + 255 * 256 + 255);
	while (i < RAYS_NUM)
	{
		ray_cast(line2, &(pl.cast_array[i]), &cross);
		ray_cast(line, &(pl.cast_array[i]), &cross);
		i++;
	}
	i = 0;
	while (i < RAYS_NUM)
	{
		draw_ray(renderer,pl.cast_array[i], 255*256*256 + 256*255);
		i++;
	}
	SDL_RenderPresent(renderer);
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
