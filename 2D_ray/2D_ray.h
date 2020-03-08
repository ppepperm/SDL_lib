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

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

t_line init_line(int x1, int y1, int x2, int y2);
void draw_line(SDL_Renderer *renderer, t_line line, int colour);

#endif