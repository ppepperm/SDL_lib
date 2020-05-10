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

int			init_coordinates(t_i2 *complex, int fd)
{
	char	**nums;
	char	*line;

	get_next_line(fd, &line);
	nums = ft_strsplit(line, ' ');
	if (!nums[1])
	{
		return (error_coordinates(nums, line));
	}
	complex->x = ft_atoi(nums[0]);
	complex->y = ft_atoi(nums[1]);
	if ((complex->x == 0 && ft_strcmp(nums[0], "0") != 0)
		|| (complex->y == 0 && ft_strcmp(nums[1], "0") != 0)
		|| nums[2])
	{
		return (error_coordinates(nums, line));
	}
	free_coordinates(nums, line);
	return (1);
}

static int	reading_line(t_data *data, char **nums, t_i2 count)
{
	while (nums[count.x])
	{
		if (count.x >= data->size.x)
		{
			return (error_map(data, count.y, "Incorrect width\n"));
		}
		data->map[count.y][count.x] = ft_atoi(nums[count.x]);
		if (!check_cell(data, count))
		{
			return (0);
		}
		if (data->map[count.y][count.x] == 10
			|| data->map[count.y][count.x] == 11)
		{
			init_doors(data, count);
		}
		free(nums[count.x++]);
	}
	free(nums);
	if (count.x != data->size.x)
	{
		return (error_map(data, count.y, "Incorrect width\n"));
	}
	return (1);
}

int			init_map(t_data *data,int fd)
{
	char	*line;
	char	**nums;
	t_i2	count;

	data->map = (int**)malloc(sizeof(int*) * data->size.y);
	count.y = 0;
	data->doors_num = 0;
	while(get_next_line(fd, &line))
	{
		data->map[count.y] = (int*)malloc(sizeof(int) * data->size.x);
		if (count.y >= data->size.y)
		{
			return (error_map(data, count.y, "Incorrect height\n"));
		}
		nums = ft_strsplit(line, ' ');
		count.x = 0;
		if (!reading_line(data, nums, count))
			return (0);
		free(line);
		count.y++;
	}
	if (count.y != data->size.y)
		return (error_map(data, count.y, "Incorrect height\n"));
	return (1);
}
