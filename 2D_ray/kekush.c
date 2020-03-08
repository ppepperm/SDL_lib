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
	t_ray  ray;
	t_p2   cross;
	int cast;

	line = init_line(0, 100, 200, 0);
	ray = init_ray(0, 0, 30, 20);
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("2D_ray", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	draw_line(renderer,line,255 * 256 * 256 + 255 * 256 + 255);
	draw_ray(renderer, ray, 255*256*256);
	cast = ray_cast(line, ray, &cross);
	ray = init_ray(ray.st.x, ray.st.y, cross.x, cross.y);
	draw_ray(renderer, ray, 255*256);
	ft_putnbr(cast);
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
