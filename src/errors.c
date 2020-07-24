/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:45:55 by ppepperm          #+#    #+#             */
/*   Updated: 2020/05/19 11:46:02 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	error_coordinates(char **nums, char *line)
{
	ft_putstr("Incorrect coordinates\n");
	free_coordinates(nums, line);
	return (0);
}

int	error_map(t_data *data, int y, char *message)
{
	ft_putstr(message);
	free_map(data, y);
	return (0);
}

int	error_map_nums(t_data *data, t_i2 *count, char **nums, char *message)
{
	return (error_map(data, count->y, message) + free_nums(nums, count->x));
}
