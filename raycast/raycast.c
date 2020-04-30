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

void		ray_direction(t_ray *ray, t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->side.x = (player.pos.x - ray->mp.x) * ray->delta.x;
		ray->step.x = -1;
	}
	else
	{
		ray->side.x = (1 + ray->mp.x - player.pos.x) * ray->delta.x;
		ray->step.x = 1;
	}
	if (ray->dir.y < 0)
	{
		ray->side.y = (player.pos.y - (int)player.pos.y) * ray->delta.y;
		ray->step.y = 1;
	}
	else
	{
		ray->side.y = (1 + (int)player.pos.y - player.pos.y) * ray->delta.y;
		ray->step.y = -1;
	}
}

t_ray		init_ray(t_player player, t_data data, int x)
{
	t_ray	ray;

	ray.phase = -FOV * (x / W_W - 0.5) * 0.0174533;
	ray.dir = comp_multiply(player.dir, init_p2(cos(ray.phase), sin(ray.phase)));
	ray.mp.x = (int)player.pos.x;
	ray.mp.y = data.size.y - 1 - (int)player.pos.y;
	if (ray.dir.x == 0)
		ray.delta = init_p2(1000000000, 1);
	else if (ray.dir.y == 0)
		ray.delta = init_p2(1, 1000000000);
	else
		ray.delta = init_p2(d_abs(1.0 / ray.dir.x), d_abs(1.0 / ray.dir.y));
	ray_direction(&ray, player);
	ray.hit = 0;
	return (ray);
}

void		search_hit(t_ray *ray, int *side, t_data data)
{
	while (ray->hit == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->mp.x += ray->step.x;
			*side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->mp.y += ray->step.y;
			*side = 1;
		}
		if (data.map[ray->mp.y][ray->mp.x] != 0)
		{
			ray->hit = 1;
		}
	}
	ray->side = comp_dif(ray->side, ray->delta);
}

void		raycast(t_data data, t_player player, SDL_Renderer *renderer)
{
	t_ray		ray;

	//
	data.param.x = 0;
	while (data.param.x <= W_W)
	{
		ray = init_ray(player, data, data.param.x);
		search_hit(&ray, &data.param.side, data);
		calculation_height(&data.param, ray, player);
		//
		if (data.map[ray.mp.y][ray.mp.x] < 9)
		{
			put_texture(renderer, data.param, data.map[ray.mp.y][ray.mp.x], data);
		}
		else
		{
			check_door(&data, ray, renderer, player);
		}
		data.param.x++;
	}
}

/*
	SDL_Surface *surface;
	surface = IMG_Load("textures/redbrick.png");
	SDL_Surface *f_surface = SDL_ConvertSurfaceFormat(surface,SDL_GetWindowPixelFormat(map.window), 0);
	SDL_Texture *newTex = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(map.window), SDL_TEXTUREACCESS_STREAMING,\
    f_surface->w, f_surface->h);
	void *pixels;
	int pitch;
	SDL_LockTexture(newTex, NULL, &pixels, &pitch);
	ft_memcpy(pixels, f_surface->pixels, f_surface->pitch*f_surface->h);
	SDL_UnlockTexture(newTex);*/



		/*
		SDL_LockTexture(newTex, NULL, &pixels, &pitch);
		double z = 1;
		unsigned char *pix = (unsigned char*)pixels;
		t_i2 pixel;
		while (z <= W_H/2 - param.line_height/2) {
			double P = W_H / (2 * (param.line_height / 2 + z));
			P = P / cos(ray.phase);
			pixel.x = (int) ((player.pos.x + P * ray.dir.x - floor(player.pos.x + P * ray.dir.x)) * 63);
			pixel.y = (int) ((player.pos.y + P * ray.dir.y - floor(player.pos.y + P * ray.dir.y)) * 63);
			//printf("%d %d\n", pixel.x, pixel.y);
			int b = pix[pitch*pixel.y + pixel.x];
			int g = pix[pitch*pixel.y + pixel.x + 1];
			int r = pix[pitch*pixel.y + pixel.x + 2];
			int a = pix[pitch*pixel.y + pixel.x + 3];
			SDL_SetRenderDrawColor(renderer,r,g,b,a);
			SDL_RenderDrawPoint(renderer, x, W_H / 2 + param.line_height / 2 + z);
			z++;
		}
		*/
