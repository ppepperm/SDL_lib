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
#include "2D_ray.h"
#include <SDL2/SDL.h>

int main(void) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	t_player pl;
	t_scene scene;
	float angle;

	pl = init_player(init_p2(-90,-20),45,FOV);
	scene = init_scene(pl, "map1.map");
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderClear(renderer);
	make_scene(&scene,renderer);
	SDL_RenderPresent(renderer);
	angle = 0;
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				scene.player.spd = init_p2(cos(scene.player.dir)*SPD, sin(scene.player.dir)*SPD);
			if(event.key.keysym.scancode == SDL_SCANCODE_S)
				scene.player.spd = init_p2(-cos(scene.player.dir)*SPD, -sin(scene.player.dir)*SPD);
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				 angle += W_SPD;
			if(event.key.keysym.scancode == SDL_SCANCODE_D)
				 angle -= W_SPD;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				scene.player.spd = init_p2(0,0);
			else if(event.key.keysym.scancode == SDL_SCANCODE_S)
				scene.player.spd = init_p2(0,0);
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				scene.player.w = 0;
			if(event.key.keysym.scancode == SDL_SCANCODE_D)
				scene.player.w = 0;
		}
		if (angle == 360 || angle == -360)
			angle = 0;
		change_pos(comp_sum(scene.player.pos,scene.player.spd),angle, &(scene.player));
		make_scene(&scene,renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
