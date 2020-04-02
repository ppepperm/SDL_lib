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