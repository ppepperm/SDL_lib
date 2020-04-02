/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:53:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 13:53:41 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_p2	init_p2(double x, double y)
{
	t_p2 p2;
	p2.x = x;
	p2.y = y;
	return (p2);
}

t_p2	comp_sum(t_p2 z1, t_p2 z2)
{
	return (init_p2(z1.x + z2.x, z1.y + z2.y));
}

t_p2	comp_dif(t_p2 z1, t_p2 z2)
{
	return (init_p2(z1.x - z2.x, z1.y - z2.y));
}

t_p2	comp_multiply(t_p2 z1, t_p2 z2)
{
	return (init_p2(z1.x * z2.x - z1.y * z2.y,\
	z1.y * z2.x + z1.x * z2.y));
}

double d_abs(double num)
{
	if (num < 0)
		num *= -1;
	return (num);
}
