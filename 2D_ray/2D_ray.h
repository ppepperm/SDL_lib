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

#include <SDL2/SDL.h>
#include <math.h>
#include "libft/includes/libft.h"
#include <fcntl.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define RAYS_NUM	90
#define FOV			75

typedef struct s_p2
{
	float x;
	float y;
}				t_p2;

typedef struct s_ray
{
	t_p2 st;
	t_p2 dir;
	float module;
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
	float	fov;
	t_ray	*cast_array;
}				t_player;

typedef struct s_scene
{
	t_player player;
	t_line	*map_array;
	int		wall_num;
}				t_scene;

t_line init_line(int x1, int y1, int x2, int y2);
t_ray init_ray(int x1, int y1, int x2, int y2);
void draw_line(SDL_Renderer *renderer, t_line line, int colour);
void draw_ray(SDL_Renderer *renderer, t_ray ray, int colour);
int ray_cast(t_line line, t_ray *ray,t_p2 *p);

t_p2	init_p2(float x, float y);
t_p2	comp_sum(t_p2 z1, t_p2 z2);
t_p2	comp_dif(t_p2 z1, t_p2 z2);
t_p2	comp_multiply(t_p2 z1, t_p2 z2);

t_player	init_player(t_p2 pos, float dir, float fov);
t_scene init_scene(t_player player,char *map_name);
void  make_scene(t_scene *scene, SDL_Renderer *renderer);
int get_num(int fd);
void	change_pos(t_p2 pos, float dir, t_player *player);

#endif
