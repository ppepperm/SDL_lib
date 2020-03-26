/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:53:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 13:53:41 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2D_ray.h"
t_p2	init_sign(t_p2 st, t_p2 en)
{
	t_p2 sign;

	if (st.x < en.x)
		sign.x = 1;
	else
		sign.x = -1;
	if (st.y < en.y)
		sign.y = 1;
	else
		sign.y = -1;
	return (sign);
}

void sdl_draw_line(SDL_Renderer *renderer, t_p2 st, t_p2 en, int colour)
{
	int			deltax;
	int			deltay;
	t_p2	error;
	t_p2	sign;

	deltax = abs(en.x - st.x);
	deltay = abs(en.y - st.y);
	error.x = deltax - deltay;
	sign = init_sign(st, en);
	SDL_SetRenderDrawColor(renderer, (colour>>16)%256, (colour>>8)%256, colour%256, 255);
	SDL_RenderDrawPoint(renderer, en.x + WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 -  en.y);
	while (st.x != en.x || st.y != en.y)
	{
		SDL_RenderDrawPoint(renderer, st.x  + WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 -  st.y);
		error.y = error.x * 2;
		if (error.y > -deltay)
		{
			error.x -= deltay;
			st.x += sign.x;
		}
		if (error.y < deltax)
		{
			error.x += deltax;
			st.y += sign.y;
		}
	}

}