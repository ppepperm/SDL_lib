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
#include <SDL2/SDL.h>

int main(void) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	t_player pl;
	t_scene scene;
	float i;

	pl = init_player(init_p2(-90,-20),45,FOV);
	scene = init_scene(pl, "map1.map");
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderClear(renderer);
	make_scene(&scene,renderer);
	SDL_RenderPresent(renderer);
	change_pos(init_p2(0,0), 90, &(scene.player));
	make_scene(&scene,renderer);
	SDL_RenderPresent(renderer);
	i = 0;
	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
		SDL_RenderClear(renderer);
		change_pos(init_p2(80*cos(0.06*i + 10),40*sin(0.04*i)), 90 + 2*i, &(scene.player));
		make_scene(&scene,renderer);
		SDL_RenderPresent(renderer);
		i+=1;
		SDL_Delay(1);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
