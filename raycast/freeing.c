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
	free(nums[0]);
	free(nums[1]);
	free(line);
	free(nums);
}

void	free_map(t_data *data, int y)
{
	while (y >= 0)
	{
		free(data->map[y]);
		y--;
	}
	free(data->map);
}
