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

t_player	init_player(t_p2 pos, float dir, float fow)
{
	t_player player;
	t_p2 rotor;

	player.pos = pos;
	player.dir = dir;
	player.fow = fow;
	return (player);
}

