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
	//printf("null\n");
	player.dir = dir;
	player.fov = fov;
	rotor = init_p2(cos(fov/RAYS_NUM), sin(fov/RAYS_NUM));
	view_comp = init_p2(cos(dir-fov/2)*50,sin(dir-fov/2)*50);
	player.cast_array = (t_ray*)malloc(sizeof(t_ray)*RAYS_NUM);
	i = 0;
	while (i < RAYS_NUM)
	{
		player.cast_array[i] = init_ray(player.pos.x, player.pos.y, player.pos.x + view_comp.x*100, player.pos.y + view_comp.y*100);
		view_comp = comp_multiply(view_comp, rotor);
		i++;
	}
	return (player);
}

t_scene init_scene(t_player player,char *map_name)
{
	t_scene scene;
	char *str;
	char **nums;
	int fd;
	int i;

	scene.player = player;
	fd = open(map_name,O_RDWR);
	scene.wall_num = get_num(fd);
	scene.map_array = (t_line*)malloc(sizeof(t_line)*scene.wall_num);
	i = 0;
	while (get_next_line(fd, &str))
	{
		nums = ft_strsplit(str, ' ');
		scene.map_array[i++] = init_line(ft_atoi(nums[0]), ft_atoi(nums[1]), ft_atoi(nums[2]), ft_atoi(nums[3]));
		free(nums[0]);
		free(nums[1]);
		free(nums[2]);
		free(nums[3]);
		free(nums);
	}
	return (scene);
}

int get_num(int fd)
{
	char *str;
	int num;

	get_next_line(fd, &str);
	num = ft_atoi(str);
	free(str);
	return (num);
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
		draw_ray(renderer,scene->player.cast_array[i], 255*256);
		i++;
	}
	j = 0;
	while (j < scene->wall_num)
	{
		sdl_draw_line(renderer, scene->map_array[j].a, scene->map_array[j].b, 255*256*256 + 256*255 + 255);
		j++;
	}
}

void	change_pos(t_p2 pos, float dir, t_player *player)
{
	t_p2 rotor;
	t_p2 view_comp;
	int i;

	dir *= 0.0174533;
	player->pos = pos;
	player->dir = dir;
	rotor = init_p2(cos(player->fov/RAYS_NUM), sin(player->fov/RAYS_NUM));
	view_comp = init_p2(cos(player->dir-player->fov/2)*50,\
	sin(player->dir-player->fov/2)*50);
	i = 0;
	while (i < RAYS_NUM)
	{
		player->cast_array[i] = init_ray(player->pos.x, player->pos.y, player->pos.x + view_comp.x*100, player->pos.y + view_comp.y*100);
		view_comp = comp_multiply(view_comp, rotor);
		i++;
	}
}