/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_ray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:02:54 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:02:56 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYY
#define RAYY

#include "SDL2/SDL.h"
#include <math.h>
#include "libft/includes/libft.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 640

typedef struct s_p2
{
	int x;
	int y;
}				t_p2;

typedef struct s_ray
{
	t_p2 st;
	t_p2 dir;
}				t_ray;

typedef struct s_line
{
	t_p2 a;
	t_p2 b;
}				t_line;

typedef struct s_player
{
	t_p2	pos;
	float	dir;
	float	fow;
	t_ray	*cast_array;
}				t_player;

t_line init_line(int x1, int y1, int x2, int y2);
t_ray init_ray(int x1, int y1, int x2, int y2);
void draw_line(SDL_Renderer *renderer, t_line line, int colour);
void draw_ray(SDL_Renderer *renderer, t_ray ray, int colour);
int ray_cast(t_line line, t_ray ray,t_p2 *p);


#endif
