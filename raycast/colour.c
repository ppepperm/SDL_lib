/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

t_rgb init_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	t_rgb colour;

	colour.r = r;
	colour.g = g;
	colour.b = b;
	return (colour);
}

t_rgb mult_rgb(t_rgb colour, double k)
{
	return (init_rgb(colour.r/k, colour.g/k, colour.b/k));
}
