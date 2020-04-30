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

void		put_texture(SDL_Renderer *renderer, t_parametrs param, int type,
						t_data data)
{
	SDL_Rect	dst;
	SDL_Rect	src;

	dst.x = param.x;
	dst.y = (W_H - param.line_height) / 2;
	dst.w = 1;
	dst.h = param.line_height;
	src.x = (int)(param.texture_x * 63.0);
	src.y = 0;
	src.h = 64;
	src.w = 1;
	if (param.side == 0)
		SDL_RenderCopy(renderer, data.textures[type - 1], &src, &dst);
	else if (param.side == 1)
		SDL_RenderCopy(renderer, data.textures_dark[type - 1], &src, &dst);
}

static void	load_image(const char *path, int i, SDL_Texture **texture,
						SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	surface = IMG_Load(path);
	texture[i] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void		init_textures(t_data *map, SDL_Renderer *renderer)
{
	map->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 8);
	load_image("textures/bluestone.png", 0, map->textures, renderer);
	load_image("textures/colorstone.png", 1, map->textures, renderer);
	load_image("textures/eagle.png", 2, map->textures, renderer);
	load_image("textures/greystone.png", 3, map->textures, renderer);
	load_image("textures/mossy.png", 4, map->textures, renderer);
	load_image("textures/purplestone.png", 5, map->textures, renderer);
	load_image("textures/redbrick.png", 6, map->textures, renderer);
	load_image("textures/wood.png", 7, map->textures, renderer);
}

void		init_textures_dark(t_data *map, SDL_Renderer *renderer)
{
	map->textures_dark = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 8);
	load_image("textures_dark/bluestone.png", 0, map->textures_dark, renderer);
	load_image("textures_dark/colorstone.png", 1, map->textures_dark, renderer);
	load_image("textures_dark/eagle.png", 2, map->textures_dark, renderer);
	load_image("textures_dark/greystone.png", 3, map->textures_dark, renderer);
	load_image("textures_dark/mossy.png", 4, map->textures_dark, renderer);
	load_image("textures_dark/purplestone.png", 5, map->textures_dark, renderer);
	load_image("textures_dark/redbrick.png", 6, map->textures_dark, renderer);
	load_image("textures_dark/wood.png", 7, map->textures_dark, renderer);
}
