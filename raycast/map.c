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

static void	read_map(t_data *data, int fd)
{
	char	*line;
	char	**nums;
	t_i2	count;

	data->map = (int**)malloc(sizeof(int*) * data->size.y);
	count.y = 0;
	while(get_next_line(fd, &line))
	{
		data->map[count.y] = (int*)malloc(sizeof(int) * data->size.x);
		nums = ft_strsplit(line, ' ');
		count.x = 0;
		while (count.x < data->size.x)
		{
			data->map[count.y][count.x] = ft_atoi(nums[count.x]);
			free(nums[count.x++]);
		}
		free(nums);
		free(line);
		count.y++;
	}
}

static void	init_coordinates(t_i2 *complex, int fd)
{
	char	**nums;
	char	*line;

	get_next_line(fd, &line);
	nums = ft_strsplit(line, ' ');
	complex->x = ft_atoi(nums[0]);
	complex->y = ft_atoi(nums[1]);
	free(nums[0]);
	free(nums[1]);
	free(line);
	free(nums);
}

t_data		init_map(char *fname)
{
	int		fd;
	t_data	data;

	fd = open(fname, O_RDWR);
	init_coordinates(&(data.size), fd);
	init_coordinates(&(data.start), fd);
	read_map(&data, fd);
	data.window = SDL_CreateWindow("Woolf3D",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, 0);
	data.renderer = SDL_CreateRenderer(data.window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 0);
	SDL_RenderClear(data.renderer);
	init_textures(&data, data.renderer);
	init_textures_dark(&data, data.renderer);
	return (data);
}
