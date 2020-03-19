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
	t_p2 coll_speed;
	int w = 0;
	int s = 0;
	int a = 0;
	int d = 0;

	pl = init_player(init_p2(-90,-20),90,FOV);
	scene = init_scene(pl, "map1.map");
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderClear(renderer);
	make_scene(&scene,renderer);
	SDL_RenderPresent(renderer);
	angle = 90;
	while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT))
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		coll_speed = init_p2(0,0);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				w = 1;
			if(event.key.keysym.scancode == SDL_SCANCODE_S)
				s = 1;
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				a = 1;
			if(event.key.keysym.scancode == SDL_SCANCODE_D)
				d = 1;
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_W)
				w = 0;
			else if(event.key.keysym.scancode == SDL_SCANCODE_S)
				s = 0;
			if(event.key.keysym.scancode == SDL_SCANCODE_A)
				a = 0;
			else if(event.key.keysym.scancode == SDL_SCANCODE_D)
				d = 0;
		}

		if (w && (s != 1))
			scene.player.spd = init_p2(cos(scene.player.dir)*SPD, sin(scene.player.dir)*SPD);
		else if(s && (w != 1))
			scene.player.spd = init_p2(-cos(scene.player.dir)*SPD, -sin(scene.player.dir)*SPD);
		else
			scene.player.spd = init_p2(0,0);
		if (a && (d != 1))
			angle += W_SPD;
		else if (d && (a != 1))
			angle -= W_SPD;
		if (angle == 360 || angle == -360)
			angle = 0;

		change_pos(comp_sum(scene.player.pos,scene.player.spd),angle, &(scene.player));
		if (check_scene_collision(scene, &coll_speed))
		{
			coll_speed = comp_dif(coll_speed, scene.player.spd);
			change_pos(comp_sum(scene.player.pos, coll_speed), angle, &(scene.player));
		}
		make_scene(&scene,renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
