/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:40:48 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 13:40:50 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int			init_coordinates(t_i2 *complex, int fd)
{
	char	**nums;
	char	*line;

	line = NULL;
	get_next_line(fd, &line);
	if (!(nums = ft_strsplit(line, ' ')) || !nums[0])
	{
		ft_putstr("Incorrect coordinates\n");
		free(nums);
		free(line);
		return (0);
	}
	if (!nums[1])
		return (error_coordinates(nums, line));
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

static int	reading_line(t_data *data, char **nums, t_i2 *count)
{
	while (nums[count->x])
	{
		if (count->x >= data->size.x)
			return (error_map(data, count->y, "Incorrect width\n") + free_nums(nums, count->x));
		data->map[count->y][count->x] = ft_atoi(nums[count->x]);
		if ((data->map[count->y][count->x] == 0 && ft_strcmp(nums[count->x], "0") != 0) ///////////////////
			|| !check_cell(data, *count))
		{
			return (free_nums(nums, count->x));
		}
		if (data->map[count->y][count->x] == 10
			|| data->map[count->y][count->x] == 11)
			if (!(init_doors(data, *count)))
				return (error_map(data, count->y, "FTAM\n") + free_nums(nums, count->x));
		free(nums[count->x++]);
	}
	free(nums);
	if (count->x != data->size.x)
		return (error_map(data, count->y, "Incorrect width\n"));
	return (1);
}

int			init_map(t_data *data, int fd)
{
	char	*line;
	char	**nums;
	t_i2	count;

	if (!(data->map = (int**)malloc(sizeof(int*) * data->size.y)))
		return (0);
	count.y = -1;
	while (get_next_line(fd, &line))
	{
		if (!(data->map[++(count.y)] = (int*)malloc(4 * data->size.x)))
			return (free_line(line) + error_map(data, count.y, "FTAM\n"));
		if (count.y >= data->size.y)
			return (free_line(line) + error_map(data, count.y, "Inc height\n"));
		if (!(nums = ft_strsplit(line, ' ')))
			return (free_line(line) + error_map(data, count.y, "FTAM\n"));
		count.x = 0;
		if (!reading_line(data, nums, &count))
		{
			data->size.y = count.y + 1;
			return (free_line(line));
		}
		free(line);
	}
	if (count.y + 1 != data->size.y)
		return (error_map(data, count.y, "Inc height\n"));
	return (1);
}
