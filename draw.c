/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:11:59 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/26 19:23:11 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**draw_map(t_game *game, int ts, int i)
{
	int	c1;
	int	c2;

	c1 = ((WIDTH - game->map.la * ts) / 2) + ts + 200;
	c2 = ((HEIGHT - game->map.h * ts) / 2) + ts -300;
	game->zoom = ts;
	while (game->point[++i])
	{
		game->point[i]->x = game->point[i]->x * ts + c1;
		game->point[i]->y = game->point[i]->y * ts + c2;
		game->point[i]->x0 = game->point[i]->x;
		game->point[i]->y0 = game->point[i]->y;
		game->point[i]->z0 = game->point[i]->z;
	}
	return (game->point);
}

void	draw_map_02(t_point **p, t_game *game)
{
	int	i;

	i = -1;
	while (p[++i])
	{
		if (p[i + 1] && p[i]->l == p[i + 1]->l)
			draw_line(game, p[i], p[i + 1]);
	}
}

void	draw_map_03(t_point **p, t_game *game)
{
	unsigned int	i;
	unsigned int	j;

	j = -1;
	while (++j <= (unsigned int)game->map.la)
	{
		i = j;
		while (i < (unsigned int)game->map.la * ((unsigned int)game->map.h - 1))
		{
			draw_line(game, p[i], p[i + game->map.la]);
			i += game->map.la;
		}
	}
}

t_draw_line	draw_line_init(t_draw_line dl, t_point *p0, t_point *p1, t_game *g)
{
	if (!g)
		exit(EXIT_FAILURE);
	dl.dx = abs(p1->x - p0->x);
	dl.dy = abs(p1->y - p0->y);
	dl.err = dl.dx - dl.dy;
	dl.a = p0->x;
	dl.b = p0->y;
	dl.color = p0->color;
	if (p0->x < p1->x)
		dl.sx = 1;
	else
		dl.sx = -1;
	if (p0->y < p1->y)
		dl.sy = 1;
	else
		dl.sy = -1;
	return (dl);
}

int	draw_line(t_game *game, t_point *p0, t_point *p1)
{
	t_draw_line	dl;

	dl = draw_line_init(dl, p0, p1, game);
	while (dl.a != p1->x || dl.b != p1->y)
	{
		if (dl.a >= 0 && dl.a < WIDTH && dl.b >= 0 && dl.b < HEIGHT)
			my_mlx_pixel_put(game, dl.a, dl.b, dl.color);
		dl.err2 = dl.err * 1000;
		if (dl.err2 > dl.dy)
		{
			dl.err -= dl.dy;
			dl.a += dl.sx;
		}
		if (dl.err2 < dl.dx)
		{
			dl.err += dl.dx;
			dl.b += dl.sy;
		}
	}
	return (0);
}
