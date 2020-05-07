/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut1.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int draw_vert_ds(t_ray *ray, t_map map, SDL_Renderer *renderer, double tex_x, t_player pl, int x)
{
	t_p2 sw_ds;
	t_i2 count;
	double dist;

	sw_ds = sw_ds_ver(tex_x, *ray);
	ray->side.x += sw_ds.y;
	dist = ray->side.x * cos(ray->phase);
	count.x = 1;
	count.y = (int) (W_H / dist);
	tex_x = pl.pos.x + ray->side.x * ray->dir.x;
	tex_x -= floor(tex_x);
	put_texture(renderer, count, x, tex_x, 10, map);
	return (DONE);
}

int draw_hor_ds(t_ray *ray, t_map map, SDL_Renderer *renderer, double tex_x, t_player pl, int x)
{
	t_p2 sw_ds;
	t_i2 count;
	double dist;

	sw_ds = sw_ds_hor(tex_x, *ray);
	ray->side.y += sw_ds.x;
	dist = ray->side.y * cos(ray->phase);
	count.x = 0;
	count.y = (int) (W_H / dist);
	tex_x = pl.pos.y + ray->side.y * ray->dir.y;
	tex_x -= floor(tex_x);
	put_texture(renderer, count, x, tex_x, 10, map);
	return (DONE);
}

void hor_perp(t_ray *ray, t_player pl, double *tex_x, double *dist, t_i2 *count)
{
	t_p2 sw_ds;

	sw_ds = sw_ds_hor(*tex_x, *ray);
	ray->side.y += sw_ds.y;
	*dist = ray->side.y * cos(ray->phase);
	count->x = 1;
	count->y = (int) (W_H / *dist);
	*tex_x = pl.pos.x + ray->side.y * ray->dir.x;
	*tex_x -= floor(*tex_x);
}

void ver_perp(t_ray *ray, t_player pl, double *tex_x, double *dist, t_i2 *count)
{
	t_p2 sw_ds;

	sw_ds = sw_ds_ver(*tex_x, *ray);
	ray->side.x += sw_ds.x;
	*dist = ray->side.x * cos(ray->phase);
	count->x = 0;
	count->y = (int) (W_H / *dist);
	*tex_x = pl.pos.y + ray->side.x * ray->dir.y;
	*tex_x -= floor(*tex_x);
}