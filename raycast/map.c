#include "raycast.h"

void read_map(t_map *map,int fd)
{
	char *line;
	char **nums;
	t_i2 count;

	map->map = (int**)malloc(sizeof(int*) * map->size.y);
	count.y = 0;
	while(get_next_line(fd, &line))
	{
		map->map[count.y] = (int*)malloc(sizeof(int) * map->size.x);
		nums = ft_strsplit(line, ' ');
		count.x = 0;
		while (count.x < map->size.x)
		{
			map->map[count.y][count.x] = ft_atoi(nums[count.x]);
			free(nums[count.x++]);
		}
		free(nums);
		free(line);
		count.y++;
	}
}

void		init_skybox(t_map *data, SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	surface = IMG_Load("textures/skybox720.png");
	data->skybox = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void init_textures(t_map *map, SDL_Renderer *renderer)
{
	SDL_Surface *surface;

	map->texs = (SDL_Texture**)malloc(sizeof(SDL_Texture*)*8);
	surface = IMG_Load("textures/bluestone.png");
	map->texs[0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/colorstone.png");
	map->texs[1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/eagle.png");
	map->texs[2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/greystone.png");
	map->texs[3] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/mossy.png");
	map->texs[4] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/purplestone.png");
	map->texs[5] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/redbrick.png");
	map->texs[6] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/wood.png");
	map->texs[7] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

}

void init_textures1(t_map *map, SDL_Renderer *renderer)
{
	SDL_Surface *surface;

	map->texsd = (SDL_Texture**)malloc(sizeof(SDL_Texture*)*8);
	surface = IMG_Load("textures_dark/bluestone.png");
	map->texsd[0] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/colorstone.png");
	map->texsd[1] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/eagle.png");
	map->texsd[2] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/greystone.png");
	map->texsd[3] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/mossy.png");
	map->texsd[4] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/purplestone.png");
	map->texsd[5] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/redbrick.png");
	map->texsd[6] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/wood.png");
	map->texsd[7] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

}

t_map init_map(char *fname)
{
	int fd;
	t_map map;
	char *line;
	char **nums;

	fd = open(fname, O_RDWR);
	get_next_line(fd, &line);
	nums = ft_strsplit(line, ' ');
	map.size.x = ft_atoi(nums[0]);
	map.size.y = ft_atoi(nums[1]);
	free(nums[0]);
	free(nums[1]);
	free(line);
	free(nums);
	get_next_line(fd, &line);
	nums = ft_strsplit(line, ' ');
	map.start.x = ft_atoi(nums[0]);
	map.start.y = ft_atoi(nums[1]);
	free(nums[0]);
	free(nums[1]);
	free(nums);
	free(line);
	read_map(&map, fd);
	return (map);
}

// static int	reading_line(t_data *data, char *line, char **nums, t_i2 count)
// {
// 	while (nums[count.x])
// 	{
// 		if (count.x >= data->size.x)
// 		{
// 			return (error_map(data, count.y, "Incorrect width\n"));
// 		}
// 		data->map[count.y][count.x] = ft_atoi(nums[count.x]);
// 		if (!check_cell(data, count))
// 		{
// 			return (0);
// 		}
// 		free(nums[count.x++]);
// 	}
// 	free(nums);
// 	free(line);
// 	if (count.x != data->size.x)
// 	{
// 		return (error_map(data, count.y, "Incorrect width\n"));
// 	}
// 	return (1);
// }

// static int	read_map(t_data *data, int fd)
// {
// 	char	*line;
// 	char	**nums;
// 	t_i2	count;

// 	data->map = (int**)malloc(sizeof(int*) * data->size.y);
// 	count.y = 0;
// 	while(get_next_line(fd, &line))
// 	{
// 		data->map[count.y] = (int*)malloc(sizeof(int) * data->size.x);
// 		if (count.y >= data->size.y)
// 		{
// 			return (error_map(data, count.y, "Incorrect height\n"));
// 		}
// 		nums = ft_strsplit(line, ' ');
// 		count.x = 0;
// 		if (!reading_line(data, line, nums, count))
// 		{
// 			return (0);
// 		}
// 		count.y++;
// 	}
// 	if (count.y != data->size.y)
// 		return (error_map(data, count.y, "Incorrect height\n"));
// 	return (1);
// }

// static int	init_coordinates(t_i2 *complex, int fd)
// {
// 	char	**nums;
// 	char	*line;

// 	get_next_line(fd, &line);
// 	nums = ft_strsplit(line, ' ');
// 	if (!nums[1])
// 	{
// 		return (error_coordinates(nums, line));
// 	}
// 	complex->x = ft_atoi(nums[0]);
// 	complex->y = ft_atoi(nums[1]);
// 	if ((complex->x == 0 && ft_strcmp(nums[0], "0") != 0)
// 		|| (complex->y == 0 && ft_strcmp(nums[1], "0") != 0)
// 		|| nums[2])
// 	{
// 		return (error_coordinates(nums, line));
// 	}
// 	free_coordinates(nums, line);
// 	return (1);
// }

// int			init_map(char *fname, t_data *data)
// {
// 	int		fd;

// 	fd = open(fname, O_RDWR);
// 	if (!init_coordinates(&(data->size), fd) || !init_coordinates(&(data->start), fd)
// 		|| !read_map(data, fd))
// 	{
// 		return (0);
// 	}
// 	data->window = SDL_CreateWindow("Woolf3D",
// 		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, 0);
// 	data->renderer = SDL_CreateRenderer(data->window, -1,
// 		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
// 	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 0);
// 	SDL_RenderClear(data->renderer);
// 	init_textures(data, data->renderer);
// 	init_textures_dark(data, data->renderer);
// 	return (1);
// }
