#include "raycast.h"

void read_map(t_map *map,int fd)
{
	char *line;
	char **nums;
	t_i2 count;
	t_door *current;

	map->map = (int**)malloc(sizeof(int*) * map->size.y);
	map->doors_num = 0;
	count.y = 0;
	while(get_next_line(fd, &line))
	{
		map->map[count.y] = (int*)malloc(sizeof(int) * map->size.x);
		nums = ft_strsplit(line, ' ');
		count.x = 0;
		while (count.x < map->size.x)
		{
			map->map[count.y][count.x] = ft_atoi(nums[count.x]);
			if (map->map[count.y][count.x] == 9 || map->map[count.y][count.x] == 10)
			{
				if (map->doors_num == 0)
				{
					map->doors = (t_door*)malloc(sizeof(t_door));
					map->doors->pos = count;
					map->doors->len = 1;
					map->doors->status = CLOSED;
					map->doors->next = NULL;
					map->doors->time = 0;
					map->doors_num += 1;
				}
				else
				{
					current = (t_door*)malloc(sizeof(t_door));
					current->pos = count;
					current->len = 1;
					current->status = CLOSED;
					current->next = map->doors;
					current->time = 0;
					map->doors = current;
					map->doors_num += 1;
				}
			}
			free(nums[count.x++]);
		}
		free(nums);
		free(line);
		count.y++;
	}
}

void init_textures(t_map *map, SDL_Renderer *renderer)
{
	SDL_Surface *surface;

	map->texs = (SDL_Texture**)malloc(sizeof(SDL_Texture*)*10);
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
	surface = IMG_Load("textures/WALL98.png");
	map->texs[8] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/WALL100.png");
	map->texs[9] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

}

void init_textures1(t_map *map, SDL_Renderer *renderer)
{
	SDL_Surface *surface;

	map->texsd = (SDL_Texture**)malloc(sizeof(SDL_Texture*)*10);
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
	surface = IMG_Load("textures_dark/WALL99.png");
	map->texsd[8] = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures_dark/WALL101.png");
	map->texsd[9] = SDL_CreateTextureFromSurface(renderer, surface);
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