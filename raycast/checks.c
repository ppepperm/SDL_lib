/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:08:08 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:08:11 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	check_value(t_data *data, t_i2 count)
{
	if (data->map[count.y][count.x] < 0 || data->map[count.y][count.x] > 11)
	{
		return (error_map(data, count.y, "Invalid cell value\n"));
	}
	return (1);
}

static int	check_border(t_data *data, t_i2 count)
{
	if (data->map[count.y][count.x] == 0)
	{
		return (error_map(data, count.y, "No wall on the border\n"));
	}
	return (1);
}

static int	check_player(t_data *data, t_i2 count)
{
	if (data->start.x <= 1 || data->start.x >= data->size.x
		|| data->start.y <= 1 || data->start.y >= data->size.y)
	{
		return (error_map(data, count.y, "Player out of bounds\n"));
	}
	if (count.x == data->start.x - 1 && count.y == data->size.y - data->start.y)
	{
		if (data->map[count.y][count.x] != 0)
		{
			return (error_map(data, count.y, "Player hits an obstacle\n"));
		}
	}
	return (1);
}

int			check_cell(t_data *data, t_i2 count)
{
	if (!check_value(data, count))
	{
		return (0);
	}
	if (count.x == 0 || count.x == data->size.x - 1
		|| count.y == 0 || count.y == data->size.y - 1)
	{
		if (!check_border(data, count))
		{
			return (0);
		}
	}
	if (!check_player(data, count))
	{
		return (0);
	}
	return (1);
}
