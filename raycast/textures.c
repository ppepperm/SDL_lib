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

static void	load_image(const char *path, int i, SDL_Texture **texture,
						SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	surface = IMG_Load(path);
	texture[i] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void		init_textures(t_data *data, SDL_Renderer *renderer)
{
	data->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
	load_image("textures/bluestone.png", 0, data->textures, renderer);
	load_image("textures/colorstone.png", 1, data->textures, renderer);
	load_image("textures/eagle.png", 2, data->textures, renderer);
	load_image("textures/greystone.png", 3, data->textures, renderer);
	load_image("textures/mossy.png", 4, data->textures, renderer);
	load_image("textures/purplestone.png", 5, data->textures, renderer);
	load_image("textures/redbrick.png", 6, data->textures, renderer);
	load_image("textures/wood.png", 7, data->textures, renderer);
	load_image("textures/door1.1.png", 8, data->textures, renderer);
	load_image("textures/door1.2.png", 9, data->textures, renderer);
}

void		init_textures_dark(t_data *data, SDL_Renderer *renderer)
{
	data->textures_dark = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
	load_image("textures_dark/bluestone.png", 0, data->textures_dark, renderer);
	load_image("textures_dark/colorstone.png", 1,
		data->textures_dark, renderer);
	load_image("textures_dark/eagle.png", 2, data->textures_dark, renderer);
	load_image("textures_dark/greystone.png", 3, data->textures_dark, renderer);
	load_image("textures_dark/mossy.png", 4, data->textures_dark, renderer);
	load_image("textures_dark/purplestone.png", 5,
		data->textures_dark, renderer);
	load_image("textures_dark/redbrick.png", 6, data->textures_dark, renderer);
	load_image("textures_dark/wood.png", 7, data->textures_dark, renderer);
	load_image("textures_dark/door1.1.png", 8, data->textures_dark, renderer);
	load_image("textures_dark/door1.2.png", 9, data->textures_dark, renderer);
}

void		init_skybox(t_data *data, SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	surface = IMG_Load("textures/skybox1440.png");
	data->skybox = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}
