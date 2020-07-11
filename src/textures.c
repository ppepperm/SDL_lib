/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:08:02 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 12:08:04 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	load_image(const char *path, int i, SDL_Texture **texture,
						SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	if (!(surface = SDL_LoadBMP(path)))
	{
		return (0);
	}
	if (!(texture[i] = SDL_CreateTextureFromSurface(renderer, surface)))
	{
		SDL_FreeSurface(surface);
		return (0);
	}
	SDL_FreeSurface(surface);
	return (1);
}

int			init_textures(t_data *data, SDL_Renderer *renderer)
{
	if (!(data->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10))
		|| !load_image("textures/bluestone.bmp", 0, data->textures, renderer)
		|| !load_image("textures/colorstone.bmp", 1, data->textures, renderer)
		|| !load_image("textures/eagle.bmp", 2, data->textures, renderer)
		|| !load_image("textures/greystone.bmp", 3, data->textures, renderer)
		|| !load_image("textures/mossy.bmp", 4, data->textures, renderer)
		|| !load_image("textures/purplestone.bmp", 5, data->textures, renderer)
		|| !load_image("textures/redbrick.bmp", 6, data->textures, renderer)
		|| !load_image("textures/wood.bmp", 7, data->textures, renderer)
		|| !load_image("textures/door1.1.bmp", 8, data->textures, renderer)
		|| !load_image("textures/door1.2.bmp", 9, data->textures, renderer))
	{
		return (0);
	}
	return (1);
}

int			init_textures_dark(t_data *data, SDL_Renderer *renderer)
{
	if (!(data->textures_dark =\
		(SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10))
		|| !load_image("textures_dark/bluestone.bmp", 0, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/colorstone.bmp", 1,
		data->textures_dark, renderer)
		|| !load_image("textures_dark/eagle.bmp", 2, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/greystone.bmp", 3, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/mossy.bmp", 4, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/purplestone.bmp", 5,
		data->textures_dark, renderer)
		|| !load_image("textures_dark/redbrick.bmp", 6, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/wood.bmp", 7, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/door1.1.bmp", 8, data->textures_dark,
		renderer)
		|| !load_image("textures_dark/door1.2.bmp", 9, data->textures_dark,
		renderer))
		return (0);
	return (1);
}

int			init_skybox(t_data *data, SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	if (!(surface = SDL_LoadBMP("textures/skybox1440.bmp")))
	{
		return (0);
	}
	if (!(data->skybox = SDL_CreateTextureFromSurface(renderer, surface)))
	{
		SDL_FreeSurface(surface);
		return (0);
	}
	SDL_FreeSurface(surface);
	return (1);
}
