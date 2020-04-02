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
#include <math.h>
#include "libft/includes/libft.h"
#include <fcntl.h>
#include <stdio.h>

#define W_H 640.0
#define W_W 1080.0
#define MAP_W 24
#define MAP_H 24
#define FOV	  100.0

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
}				t_player;

typedef struct s_ray
{
	t_p2 dir;
	t_p2 side;
	t_p2 dir;
	t_i2 step;
	t_i2 mp;
	double phase;
	int hit;
}				t_ray;

t_p2	init_p2(double x, double y);
t_p2	comp_sum(t_p2 z1, t_p2 z2);
t_p2	comp_dif(t_p2 z1, t_p2 z2);
t_p2	comp_multiply(t_p2 z1, t_p2 z2);
double d_abs(double num);

t_rgb init_rgb(unsigned char r, unsigned char g, unsigned char b);
t_rgb mult_rgb(t_rgb colour, double k);

t_player init_player(t_p2 pos, t_p2 dir);

#endif