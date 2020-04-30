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

#ifndef RAYCAST_H
#define RAYCAST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "libft/includes/libft.h"
#include <fcntl.h>
#include <stdio.h>

#define W_H 600.0
#define W_W 800.0
#define FOV 65.0
#define SPD 0.1
#define W 0.04

typedef struct		s_p2
{
	double			x;
	double			y;
}					t_p2;

typedef struct		s_i2
{
	int				x;
	int				y;
}					t_i2;

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct		s_player
{
	t_p2			pos;
	t_p2			dir;
	t_i2			mov;
	int				rot;
}					t_player;

typedef struct		s_ray
{
	t_p2			dir;
	t_p2			side;
	t_p2			delta;
	t_i2			step;
	t_i2			mp;
	double			phase;
	int				hit;
}					t_ray;

typedef struct		s_parametrs
{
	int				x;
	int				side;
	int				line_height;
	double			dist;
	double			texture_x;
	t_p2			dist_small_door;
}					t_parametrs;

typedef struct		s_data
{
	int				**map;
	t_i2			size;
	t_i2			start;
	SDL_Texture 	**textures;
	SDL_Texture 	**textures_dark;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	t_parametrs		param;
}					t_data;

t_p2				init_p2(double x, double y);
t_p2				comp_sum(t_p2 z1, t_p2 z2);
t_p2				comp_dif(t_p2 z1, t_p2 z2);
t_p2				comp_multiply(t_p2 z1, t_p2 z2);
double				d_abs(double num);
t_rgb				init_rgb(unsigned char r, unsigned char g, unsigned char b);
t_rgb				mult_rgb(t_rgb colour, double k);
t_data				init_map(char *fname);
void				init_textures(t_data *map, SDL_Renderer *renderer);
void				init_textures_dark(t_data *map, SDL_Renderer *renderer);
void				raycast(t_data map1, t_player pl, SDL_Renderer *renderer);
void				put_texture(SDL_Renderer *renderer, t_parametrs param,
					int type, t_data data);
void				calculation_height(t_parametrs *param, t_ray ray,
					t_player player);
void				check_door(t_data *data, t_ray ray, SDL_Renderer *renderer,
					t_player player);
void				event_keyup(t_player *player, SDL_Event event);
void				event_keydown(t_data *data, t_player *player,
					SDL_Event event);
void				event_move(t_data *data, t_player *player);

#endif
