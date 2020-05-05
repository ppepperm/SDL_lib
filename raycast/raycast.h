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
#define FOV	65.0
#define SPD 0.1
#define W   0.04
#define CLOSED 0
#define OPENED 1
#define CLOSING 2
#define OPENING 3
#define GOING 0
#define DONE 1

typedef struct s_p2
{
	double x;
	double y;
}				t_p2;

typedef struct s_i2
{
	int x;
	int y;
}				t_i2;

typedef struct s_rgb
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_rgb;

typedef struct s_player
{
	t_p2 pos;
	t_p2 dir;
	t_i2 mov;
	int rot;
}				t_player;

typedef struct s_ray
{
	t_p2 dir;
	t_p2 side;
	t_p2 delta;
	t_i2 step;
	t_i2 mp;
	double phase;
	int hit;
}				t_ray;

typedef struct s_door
{
	t_i2	pos;
	char	status;
	double	len;
	struct s_door *next;
	int 	time;
}				t_door;


typedef struct s_map
{
	int **map;
	int  doors_num;
	t_i2 size;
	t_i2 start;
	SDL_Texture **texs;
	SDL_Texture **texsd;
	t_door		*doors;
	SDL_Window	*window;

}				t_map;

t_p2	init_p2(double x, double y);
t_p2	comp_sum(t_p2 z1, t_p2 z2);
t_p2	comp_dif(t_p2 z1, t_p2 z2);
t_p2	comp_multiply(t_p2 z1, t_p2 z2);
double d_abs(double num);

t_rgb init_rgb(unsigned char r, unsigned char g, unsigned char b);
t_rgb mult_rgb(t_rgb colour, double k);

t_player init_player(t_p2 pos, t_p2 dir);
t_ray init_ray(t_player pl,t_map map, int x);
void put_texture(SDL_Renderer *renderer, t_i2 count, int x, double tex_x, int type, t_map map1);
void raycast(t_map map1, t_player pl, SDL_Renderer *renderer);

t_door *get_door(t_map map, int posx, int posy);
void doors_funk(t_door *doors);
int	 draw_doors(t_map map, t_ray *ray, double tex_x, SDL_Renderer *renderer, int x, t_player pl);
void	dda(t_map map, t_ray *ray, t_i2 *count);
void	dist_texx_sq(double *tex_x, t_i2 *count, t_ray ray, t_player pl);

t_map init_map(char *fname);
void init_textures(t_map *map, SDL_Renderer *renderer);
void init_textures1(t_map *map, SDL_Renderer *renderer);

t_p2	sw_ds_hor(double tex_x, t_ray ray);
t_p2	sw_dr_ver(double tex_x, t_ray ray);
int		check_for_door(t_map map,int x, int y);

#endif