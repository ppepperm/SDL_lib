/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorssupp.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_p2	sw_ds_hor(double tex_x, t_ray ray)
{
	t_p2 sw_ds;

	if (ray.dir.x > 0)
	{
		sw_ds.x = (1 - tex_x) * ray.delta.x;
		sw_ds.y = 0.5 * ray.delta.y;
	}
	else
	{
		sw_ds.x = tex_x * ray.delta.x;
		sw_ds.y = 0.5 * ray.delta.y;
	}
	return (sw_ds);
}

t_p2 sw_dr_ver(double tex_x, t_ray ray)
{
	t_p2 sw_ds;

	if (ray.dir.y > 0)
	{
		sw_ds.y = (1 - tex_x) * ray.delta.y;
		sw_ds.x = 0.5 * ray.delta.x;
	}
	else
	{
		sw_ds.y = tex_x * ray.delta.y;
		sw_ds.x = 0.5 * ray.delta.x;
	}
	return (sw_ds);
}

int	check_for_door(t_map map,int x, int y)
{
	t_door *door;

	ft_putstr("no seg1\n");
	door = get_door(map, x, y);
	ft_putstr("no seg2\n");
	if (door->status == OPENED && door)
		return (1);
	return (0);
}