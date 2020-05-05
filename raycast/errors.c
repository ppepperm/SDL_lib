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
