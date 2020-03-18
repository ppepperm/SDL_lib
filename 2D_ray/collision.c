/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:02:38 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:02:40 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2D_ray.h"
#include <stdio.h>

int	check_collision(t_line line, t_p2 pos)
{
	t_p2	pa;
	t_p2	pb;
	float	sin;
	float	s;
	float	cos;

	pa = comp_dif(line.a, pos);
	pb = comp_dif(line.b, pos);
	cos = (pa.x*pb.x + pa.y*pb.y)/sqrt((pa.x*pa.x + pa.y*pa.y)*(pb.x*pb.x + pb.y*pb.y));
	sin = sqrt(1 - cos*cos);
	s = sqrt((pa.x*pa.x + pa.y*pa.y)*(pb.x*pb.x + pb.y*pb.y))*sin;
	s = s/sqrt((line.b.x-line.a.x)*(line.b.x-line.a.x) + (line.b.y-line.a.y)*(line.b.y-line.a.y));
	if (cos < 0 && s <= 5)
	{
		//printf("%f %f\n", s, cos);
		return (1);
	}
	return (0);
}

t_p2	get_collision_speed(t_line line, t_p2 spd)
{
	t_p2 line_comp;

	line_comp = comp_dif(line.b, line.a);
	line_comp = init_p2(line_comp.x/sqrt(line_comp.x*line_comp.x + line_comp.y*line_comp.y),\
	-line_comp.y/sqrt(line_comp.x*line_comp.x + line_comp.y*line_comp.y));
	spd = comp_multiply(spd, line_comp);
	spd = init_p2(spd.x, 0);
	line_comp = init_p2(line_comp.x, -line_comp.y);
	spd = comp_multiply(spd, line_comp);
	return (spd);
}

int check_scene_collision(t_scene scene, t_p2 *res_spd)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (i < scene.wall_num)
	{
		if (check_collision(scene.map_array[i], scene.player.pos))
		{
 			*res_spd = get_collision_speed(scene.map_array[i], scene.player.spd);
			n += 1;
		}
		if (n > 1)
		{
			*res_spd = init_p2(0,0);
			return (1);
		}
		i++;
	}
	return (n);
}