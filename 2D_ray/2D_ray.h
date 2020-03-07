#ifndef RAYY
#define RAYY

typedef struct s_p2
{
	int x
	int y
}				t_p2;

typedef struct s_ray
{
	t_p2 st;
	t_p2 dir;
};

typedef struct s_line
{
	t_p2 a;
	t_p2 b;
}				t_line;

#endif