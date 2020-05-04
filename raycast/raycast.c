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
	pl = init_player(init_p2(map1.start.x,map1.start.y), init_p2(sqrt(0.5), sqrt(0.5)));
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	init_textures(&map1, renderer);
	init_textures1(&map1, renderer);
	map1.window = window;
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
		SDL_RenderClear(renderer);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				map1.map[(int)(map1.size.y - 1 - pl.pos.y) - 1][(int)(pl.pos.x)] = 1;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				pl.mov.x = 1;
			if(event.key.keysym.scancode == SDL_SCANCODE_S)
				pl.mov.x = -1;
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				pl.rot = 1;
			if(event.key.keysym.scancode == SDL_SCANCODE_D)
				pl.rot = -1;
			if(event.key.keysym.scancode == SDL_SCANCODE_G)
			{
				t_door *door;
				if (map1.map[map1.size.y - 1 - (int) (pl.pos.y + (SPD + 1.2) * pl.dir.y)][(int)(pl.pos.x + pl.dir.x * (SPD + 1.2))] >= 9)
				{
					door = get_door(map1, (int)(pl.pos.x + pl.dir.x * (SPD + 1.2)),\
					map1.size.y - 1 - (int) (pl.pos.y + (SPD + 1.2) * pl.dir.y));
					if (door->status == OPENED)
						door->status = CLOSING;
					else if(door->status == CLOSED)
						door->status = OPENING;
				}
			}

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
			if (map1.map[map1.size.y - 1 - (int) pl.pos.y][(int) (pl.pos.x +pl.dir.x*0.4*pl.mov.x+ pl.mov.x*pl.dir.x * SPD)] == 0)
				pl.pos.x += pl.mov.x*pl.dir.x * SPD;
			if (map1.map[map1.size.y - 1 - (int) (pl.pos.y + pl.dir.y*0.4*pl.mov.x +SPD * pl.dir.y * pl.mov.x)][(int) pl.pos.x] == 0)
				pl.pos.y += pl.mov.x*pl.dir.y * SPD;
		}
		if (pl.rot != 0)
			pl.dir = comp_multiply(pl.dir, init_p2(cos(W * pl.rot), sin(W * pl.rot)));
		doors_funk(map1.doors);
		raycast(map1, pl, renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}