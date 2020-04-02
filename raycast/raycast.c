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
	int map[MAP_H][MAP_W] =
			{
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
					{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,2,0,10,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
					{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,3,4,3,4,3,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,0,0,0,5,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,4,4,4,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,4,4,4,4,4,4,4,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
			};
	t_player pl;
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	t_i2 map_pos;
	int x;
	t_i2 step;
	t_p2 side;
	t_p2 delta;
	t_p2 ray;
	double phase;
	int type;
	t_rgb colour;
	double dist;
	int hit;
	int h;

	pl = init_player(init_p2(22, 12), init_p2(0, 1));
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		x = 0;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		while (x <= W_W)
		{
			phase = -FOV*(x/W_W - 0.5)*0.0174533;
			ray = comp_multiply(pl.dir, init_p2(cos(phase),sin(phase)));
			map_pos.x = (int)pl.pos.x;
			map_pos.y = MAP_H - 1 - (int)pl.pos.y;
			if (ray.x == 0)
				delta = init_p2(0, 1);
			else if (ray.y == 0)
				delta = init_p2(1, 0);
			else
				delta = init_p2(d_abs(1.0/ray.x), d_abs(1.0/ray.y));
			if (ray.x < 0)
			{
				side.x = (pl.pos.x - map_pos.x)*delta.x;
				step.x = -1;
			}
			else
			{
				side.x = (1 + map_pos.x - pl.pos.x) * delta.x;
				step.x = 1;
			}
			if (ray.y < 0)
			{
				side.y = (pl.pos.y - (int)pl.pos.y)*delta.y;
				step.y = 1;
			}
			else
			{
				side.y = (1 + (int)pl.pos.y - pl.pos.y) * delta.y;
				step.y = -1;
			}
			hit = 0;
			while (hit == 0)
			{
				if (side.x < side.y)
				{
					side.x += delta.x;
					map_pos.x += step.x;
					type = 0;
				}
				else
				{
					side.y += delta.y;
					map_pos.y += step.y;
					type = 1;
				}
				if (map[map_pos.y][map_pos.x] != 0)
					hit = 1;
			}
			side = comp_dif(side, delta);
			if (type == 0)
			{
				dist = side.x * cos(phase);
				//printf("x %f %f\n", side.x, dist);
			}
			else{
				dist = side.y * cos(phase);
				//printf("y %f %f\n", side.y, dist);
			}
			h = (int)(W_H/dist);
			if (map[map_pos.y][map_pos.x] == 1)
				colour = init_rgb(0, 0, 255);
			else if (map[map_pos.y][map_pos.x] == 2)
				colour = init_rgb(0, 255, 0);
			else if (map[map_pos.y][map_pos.x] == 3)
				colour = init_rgb(255, 0, 0);
			else
				colour = init_rgb(255,255,255);
			if (type == 1)
				colour = mult_rgb(colour, 2);
			SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
			SDL_RenderDrawLine(renderer,x, (W_H - h)/2, x, (W_H + h)/2);
			x++;
		}
		SDL_RenderPresent(renderer);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
			{
				if (map[MAP_H - 1 - (int)pl.pos.y][(int)(pl.pos.x + pl.dir.x * 0.2)] == 0)
					pl.pos.x += pl.dir.x * 0.2;
				if (map[MAP_H - 1 - (int)(pl.pos.y + 0.2 * pl.dir.y)][(int)pl.pos.x] == 0)
					pl.pos.y +=pl.dir.y * 0.2;
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_S)
			{
				if (map[MAP_H - 1 - (int)pl.pos.y][(int)(pl.pos.x - pl.dir.x * 0.2)] == 0)
					pl.pos.x -= pl.dir.x * 0.2;
				if (map[MAP_H - 1 - (int)(pl.pos.y - 0.2 * pl.dir.y)][(int)pl.pos.x] == 0)
					pl.pos.y -=pl.dir.y * 0.2;
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				pl.dir = comp_multiply(pl.dir, init_p2(cos(0.1), sin(0.1)));
			if(event.key.keysym.scancode == SDL_SCANCODE_D)
				pl.dir = comp_multiply(pl.dir, init_p2(cos(-0.1), sin(-0.1)));
		}
		//break;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}