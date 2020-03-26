/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:02:38 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:02:40 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2D_ray.h"

t_screen	get_screen(t_scene scene)
{

	t_screen screen;
	float angle;
	int i;

	i = 0;
	angle = 45;
	/*while (i < RAYS_NUM)
	{
		if (scene.player.cast_array[i].module > -1)
			num++;
		if (angle != scene.player.cast_array[i].module)
		{
			printf("%f\n", scene.player.cast_array[i].module);
			angle = scene.player.cast_array[i].module;
		}
		i++;
	}*/
	screen.size = RAYS_NUM;
	screen.center = 0;
	screen.vert_grid = (t_p2*)malloc(sizeof(t_p2) * RAYS_NUM);
	while (i < RAYS_NUM)
	{
		if(scene.player.cast_array[i].module != -1)
		{
			screen.vert_grid[i].y =  sqrt(scene.player.cast_array[i].module) * cos(angle * 0.0174533);
			screen.vert_grid[i].x =  sqrt(scene.player.cast_array[i].module) * sin(angle * 0.0174533);
		}
		else
		{
			screen.vert_grid[i].y = -1;
			screen.vert_grid[i].x = 0;
		}
		//printf("abs %f; y %f; x %f; angle %f \n",scene.player.cast_array[i].module,screen.vert_grid[i].y,screen.vert_grid[i].x, angle);
		angle -= FOV/RAYS_NUM;
		i++;

	}
	return (screen);
}


void normalize_screen(t_screen *screen)
{
	int i;
	float width;

	width =screen->vert_grid[0].x - screen->vert_grid[RAYS_NUM -1].x;
	width = WINDOW_WIDTH/width;
	i = 0;
	while (i < RAYS_NUM)
	{
		screen->vert_grid[i].x *= width;
		if (screen->vert_grid[i].y > 0)
			screen->vert_grid[i].y = WINDOW_HEIGHT*10/(screen->vert_grid[i].y - 4);
		//printf("%f %f \n", screen->vert_grid[i].x,screen->vert_grid[i].y);
		i++;
	}
	screen->center = screen->vert_grid[RAYS_NUM -1].x;
}

void draw_screen(t_screen screen, SDL_Renderer *renderer)
{
	SDL_Rect rect;
	int i;

	i = 0;
	while (i < RAYS_NUM - 1)
	{
		SDL_SetRenderDrawColor(renderer, 255*screen.vert_grid[i].y*2/WINDOW_HEIGHT, 255*screen.vert_grid[i].y*2/WINDOW_HEIGHT, 255*screen.vert_grid[i].y*2/WINDOW_HEIGHT, 255);
		rect.h = screen.vert_grid[i].y;
		rect.w = 30;
		rect.x = screen.vert_grid[i].x - screen.center;
		rect.y = WINDOW_HEIGHT/2 - (screen.vert_grid[i].y/2);
		//printf("%d %d \n", rect.x, rect.y);
		SDL_RenderFillRect(renderer, &rect);
		i++;
	}
}