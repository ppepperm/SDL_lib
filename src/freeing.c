/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:48:03 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 11:48:05 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	free_coordinates(char **nums, char *line)
{
	if (nums)
	{
		if (nums[0])
			free(nums[0]);
		if (nums[1])
			free(nums[1]);
		free(nums);
	}
	if (line)
		free(line);
}

void	free_doors(t_door *doors)
{
	t_door	*del;

	if (!doors)
		return ;
	while (doors->next)
	{
		del = doors;
		doors = doors->next;
		free(del);
	}
	free(doors);
}

int		free_nums(char **nums, int i)
{
	if (nums)
	{
		while (nums[i])
		{
			if (nums[i])
				free(nums[i]);
			i++;
		}
		free(nums);
	}
	return (0);
}

int		free_line(char *line)
{
	if (line)
		free(line);

	return (0);
}

void	free_map(t_data *data, int y)
{
	if (data->map != NULL)
	{
		while (y >= 0) {
			if (data->map[y])
			{
				free(data->map[y]);
			}
			y--;
		}
		if (data->map)
			free(data->map);
		data->map = NULL;
	}
}
