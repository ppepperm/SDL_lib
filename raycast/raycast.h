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
# define RAYCAST_H

# include <./SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <math.h>
# include "libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>

# define W_H		720.0
# define W_W		1080.0
# define FOV		65.0
# define SPD		0.1
# define W			0.04
# define CLOSED		0
# define OPENED		1
# define CLOSING	2
# define OPENING	3
# define GOING		0
# define DONE		1

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
	t_i2			map;
	double			phase;
	int				hit;
}					t_ray;

typedef struct		s_door
{
	t_i2			pos;
	char			status;
	double			len;
	struct s_door	*next;
	int 			time;
}					t_door;

typedef struct		s_parametrs
{
	int				x;
	int				side_wall;
	int				side;
	int				line_height;
	int				ray_status;
	double			dist;
	double			texture_x;
	t_door			*door;
	t_p2			dist_small_door;
}					t_parametrs;

typedef struct		s_data
{
	int				**map;
	int				doors_num;
	t_i2			size;
	t_i2			start;
	SDL_Texture		**textures;
	SDL_Texture		**textures_dark;
	SDL_Texture		*skybox;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	t_door			*doors;
	t_parametrs		param;

}					t_data;

t_p2				init_p2(double x, double y);
t_p2				comp_sum(t_p2 z1, t_p2 z2);
t_p2				comp_dif(t_p2 z1, t_p2 z2);
t_p2				comp_multiply(t_p2 z1, t_p2 z2);
double				d_abs(double num);
double				comp_dot(t_p2 z1, t_p2 z2);
void				raycast(t_data data, t_player player,
					SDL_Renderer *renderer);
void				doors_funk(t_door *doors);
int					draw_doors(t_data data, t_ray *ray, SDL_Renderer *renderer,
					t_player pl);
void				door_handling(t_data *data, t_player *player);
int					check_for_door(t_data data,int x, int y);
int					event_keydown(t_data *data, t_player *player,
					SDL_Event event);
void				event_keyup(t_player *player, SDL_Event event);
void				event_move(t_data *data, t_player *player);
int					init_data(char *fname, t_data *data);
t_player			init_player(t_p2 pos, t_p2 dir);
void				init_doors(t_data *data, t_i2 count);
int					init_map(t_data *data,int fd);
int					init_coordinates(t_i2 *complex, int fd);
int					check_cell(t_data *data, t_i2 count);
int					error_map(t_data *data, int y, char *message);
int					error_coordinates(char **nums, char *line);
void				free_coordinates(char **nums, char *line);
void				free_map(t_data *data, int y);
void				init_textures(t_data *data, SDL_Renderer *renderer);
void				init_textures_dark(t_data *data, SDL_Renderer *renderer);
void				init_skybox(t_data *data, SDL_Renderer *renderer);
int					processing_door_vertical(t_data data, t_ray *ray,
					SDL_Renderer *renderer, t_player player);
int					processing_door_horizontal(t_data data, t_ray *ray,
					SDL_Renderer *renderer, t_player player);
void				put_skybox(SDL_Renderer *renderer, t_data data,
					t_player player);
int					texture_selection(t_data *data, SDL_Renderer *renderer,
					t_ray *ray, t_player player);
void				put_texture(SDL_Renderer *renderer, int type, t_data data);

#endif
