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
		printf("%f %f\n", s, cos);
		return (1);
	}
	return (0);
}

int check_scene_collision(t_scene scene)
{
	int i;

	i = 0;
	while (i < scene.wall_num)
	{
		if (check_collision(scene.map_array[i], scene.player.pos))
		{
 			printf("collision %d \n", i);
			return (1);
		}
		printf("no collision\n");
		i++;
	}
	return (0);
}