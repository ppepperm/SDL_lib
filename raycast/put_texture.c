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

#include "raycast.h"

void		put_skybox(SDL_Renderer *renderer, t_map data, t_player player)
{
	SDL_Rect	dst;
	SDL_Rect	src;
	double		angle;

	angle = acos(comp_dot(init_p2(0, 1), player.dir)) * 57.2957795131;
	if (player.dir.x < 0)
	{
		angle = 180 + (180 - angle);
	}
	src.x = angle;
	src.y = 0;
	src.w = 360;
	src.h = 90;

	dst.x = 0;
	dst.y = 0;
	dst.w = W_W;
	dst.h = W_H / 2;
	SDL_RenderCopy(renderer, data.skybox, &src, &dst);
}
