/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 12:02:38 by ppepperm          #+#    #+#             */
/*   Updated: 2020/03/08 12:02:40 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2D_ray.h"

t_line init_line(int x1, int y1, int x2, int y2)
{
	t_line line;

	line.a.x = x1;
	line.a.y = y1;
	line.b.x = x2;
	line.b.y = y2;
	return (line);
}

t_ray init_ray(int x1, int y1, int x2, int y2)
{
	t_ray ray;

	ray.st.x = x1;
	ray.st.y = y1;
	ray.dir.x = x2;
	ray.dir.y = y2;
	return (ray);
}

void draw_line(SDL_Renderer *renderer, t_line line, int colour)
{
	SDL_SetRenderDrawColor(renderer, (colour>>16)%256, (colour>>8)%256, colour%256, 255);
	SDL_RenderDrawLine(renderer, line.a.x + WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 - line.a.y, line.b.x + WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2  - line.b.y);
}

void draw_ray(SDL_Renderer *renderer, t_ray ray, int colour)
{
	SDL_SetRenderDrawColor(renderer, (colour>>16)%256, (colour>>8)%256, colour%256, 255);
	SDL_RenderDrawLine(renderer, ray.st.x + WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 - ray.st.y, ray.dir.x + WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2  - ray.dir.y);
}

int ray_cast(t_line line, t_ray ray,t_p2 *p)
{
	float t;
	float u;
	float denom;

	denom = (line.a.x - line.b.x)*(ray.st.y - ray.dir.y) - (line.a.y - line.b.y)*(ray.st.x - ray.dir.x);
	if (denom == 0)
		return 0;
	t = ((line.a.x - ray.st.x)*(ray.st.y - ray.dir.y) - (line.a.y - ray.st.y)*(ray.st.x - ray.dir.x)) / denom;
	u = -1 * ((line.a.x - line.b.x)*(line.a.y - ray.st.y) - (line.a.y - line.b.y)*(line.a.x - ray.st.x)) / denom;
	if (t >= 0 && t <= 1 && u >= 0)
	{
		p->x = line.a.x + t * (line.b.x - line.a.x);
		p->y = line.a.y + t * (line.b.y - line.a.y);
		return 1;
	}
	return 0;
}
