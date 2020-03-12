/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:45:27 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 16:45:28 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2D_ray.h"

t_player	init_player(t_p2 pos, float dir, float fov)
{
	t_player player;
	t_p2 rotor;
	t_p2 view_comp;
	int i;

	dir *= 0.0174533;
	fov *= 0.0174533;
	player.pos = pos;
	player.dir = dir;
	player.fov = fov;
	rotor = init_p2(cos(fov/RAYS_NUM), sin(fov/RAYS_NUM));
	view_comp = init_p2(cos(dir-fov/2)*5,sin(dir-fov/2)*5);
	player.cast_array = (t_ray*)malloc(sizeof(t_ray)*RAYS_NUM);
	i = 0;
	while (i < RAYS_NUM)
	{
		player.cast_array[i] = init_ray(player.pos.x, player.pos.y, player.pos.x + view_comp.x*5, player.pos.y + view_comp.y*5);
		view_comp = comp_multiply(view_comp, rotor);
		i++;
	}
	return (player);
}

t_scene init_scene(t_player player)
{
	t_scene scene;

	scene.player = player;
	scene.wall_num = 4;
	scene.map_array = (t_line*)malloc(sizeof(t_line)*scene.wall_num);
	scene.map_array[0] = init_line(0,100,300,0);
	scene.map_array[0] = init_line(300,0,0,-100);
	scene.map_array[0] = init_line(0,-100,-300,0);
	scene.map_array[0] = init_line(-300,0,0,100);
	return (scene);
}

void  make_scene(t_scene *scene, SDL_Renderer *renderer)
{
	int i;
	int j;
	t_p2 cross;

	i = 0;
	while(i < RAYS_NUM)
	{
		j = 0;
		while (j < scene->wall_num)
		{
			ray_cast(scene->map_array[j], &(scene->player.cast_array[i]), &cross);
			j++;
		}
		draw_ray(renderer,scene->player.cast_array[i], 255*256*256 + 256*255);
		i++;
	}
	j = 0;
	while (j < scene->wall_num)
	{
		draw_line(renderer,scene->map_array[j],255*256*256 + 256*255 + 255);
		j++;
	}
}
