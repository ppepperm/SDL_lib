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

void draw_line(SDL_Renderer *renderer, t_line line, int colour)
{
	SDL_SetRenderDrawColor(renderer, (colour>>16)%256, (colour>>8)%256, colour%256, 255);
	SDL_RenderDrawLine(renderer, line.a.x + WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2 - line.a.y, line.b.x + WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2  - line.b.y);
}

int ray_cast(t_line line, t_ray ray,t_p2 *p)
{
	float t;
	float u;
	float denom;

	denom = (ray.st.x - ray.dir.x)*(line.a.y - line.b.y) - (ray.st.y - ray.dir.y)*(line.a.x - line.b.x);
	if (denom == 0)
		return 0;
	t = (ray.st.x - line.a.x)*(line.a.y - line.b.y) - (ray.st.y - line.a.y)*(line.a.x - line.b.x);
	u = (ray.st.x - ray.dir.x)*(ray.st.y - line.a.y) - (ray.st.y - ray.dir.y)*(ray.st.x - line.a.x);
	t = t/denom;
	u = -1 * u/denom;
	if (t >= 0 && t <= 1 && u > 0)
		return 1;
	p->x = 0;
	p->y = 0;
	return 0;
}
