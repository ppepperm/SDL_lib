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


int main()
{
	t_player pl;
	t_map map1;
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	map1 = init_map("jopa.map");
	pl = init_player(init_p2(map1.start.x,map1.start.y), init_p2(0, 1));
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		raycast(map1, pl, renderer);
		SDL_RenderPresent(renderer);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				pl.mov.x = 1;
			if(event.key.keysym.scancode == SDL_SCANCODE_S)
				pl.mov.x = -1;
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				pl.rot = 1;//pl.dir = comp_multiply(pl.dir, init_p2(cos(0.1), sin(0.1)));
			if(event.key.keysym.scancode == SDL_SCANCODE_D)
				pl.rot = -1; //pl.dir = comp_multiply(pl.dir, init_p2(cos(-0.1), sin(-0.1));
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				pl.mov.x = 0;
			if (event.key.keysym.scancode == SDL_SCANCODE_S)
				pl.mov.x = 0;
			if (event.key.keysym.scancode == SDL_SCANCODE_A)
				pl.rot = 0;
			if (event.key.keysym.scancode == SDL_SCANCODE_D)
				pl.rot = 0;
		}
		if (pl.mov.x != 0)
		{
			if (map1.map[map1.size.y - 1 - (int) pl.pos.y][(int) (pl.pos.x + pl.mov.x*pl.dir.x * SPD)] == 0)
				pl.pos.x += pl.mov.x*pl.dir.x * SPD;
			if (map1.map[map1.size.y - 1 - (int) (pl.pos.y + SPD * pl.dir.y * pl.mov.x)][(int) pl.pos.x] == 0)
				pl.pos.y += pl.mov.x*pl.dir.y * SPD;
		}
		if (pl.rot != 0)
			pl.dir = comp_multiply(pl.dir, init_p2(cos(W * pl.rot), sin(W * pl.rot)));
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}