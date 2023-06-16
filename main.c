/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:58 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/16 16:36:04 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map_init(int fd, t_read_map *rm)
{
	rm->i = 0;
	rm->max_width = 0;
	rm->line2 = get_next_line(fd);
	ft_printf("%s", rm->line2);
	rm->line = ft_split(rm->line2, ' ');
	rm->j = -1;
}

int	malloc_data2(const char *argv)
{
	int		fd;
	int		i;
	char	**line;

	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	i = 1;
	line = ft_split(get_next_line(fd), ' ');
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	close(fd);
	free(line);
	return (i);
}

/*char	**token_colors(t_read_map rm, char *argv)
{
	int **t_colors;

	t_colors = (int **)malloc(sizeof(int *) * (malloc_data(argv) * malloc_data2(argv)));
}*/

int in_str(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atohex(char *str, char *basemin, char *basemaj)
{
	int	i;
	int	j;
	int	n;

	i = 2;
	n = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] != basemin[j] && str[i] != basemaj[j])
			j++;
		n = n * 16 + j;
		i++;
	}
	return (n);
}

void	ft_free_gnl(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	read_map(t_game *g, int fd, t_read_map *rm)
{
	read_map_init(fd, rm);
	while (rm->line)
	{
		while (rm->line[rm->i])
		{
			if (in_str(rm->line[rm->i], ','))
			{
				rm->tokens = ft_split(rm->line[rm->i], ',');
				g->point[rm->idx]->z = ft_atoi(rm->tokens[0]);
				g->point[rm->idx]->color = ft_atohex(rm->tokens[1], bmin, bmaj);
			}
			else
			{
				g->point[rm->idx]->z = ft_atoi(rm->line[rm->i]);
				g->point[rm->idx]->color = 0xFFFFFF;
			}
			g->point[rm->idx]->x = rm->i++;
			g->point[rm->idx]->y = rm->i + WIDTH;
			g->point[rm->idx]->h = g->point[rm->idx]->x;
			g->point[rm->idx]->l = g->point[rm->idx]->y;
			rm->idx++;
		}
		ft_free_gnl(rm->line);
		read_map_init(fd , rm);
	}
}

int	malloc_data(const char *argv)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	free(line);
	return (i);
}

t_point	**draw_map(t_game *game, int ts, int i)
{
	int		c1;
	int		c2;

	c1 = ((WIDTH - (game->map.la * ts)) / 2) / 2;
	c2 = ((HEIGHT - (game->map.h * ts)) / 2) / 2;
	while (game->point[i])
	{
		game->point[i]->x = game->point[i]->x * ts + c1;
		game->point[i]->y = game->point[i]->y * ts + c2;
			i++;
	}
	return (game->point);
}

void	draw_map_02(t_point **p, t_game *game)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i + 1] && p[i]->l == p[i + 1]->l)
			draw_line(game, p[i], p[i + 1]);
		i++;
	}
}

void	draw_map_03(t_point **p, t_game *game)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (j <= (unsigned int)game->map.la)
	{
		i = j;
		while (i < (unsigned int)game->map.la
			* ((unsigned int)game->map.h - 1))
		{
			draw_line(game, p[i], p[i + game->map.la]);
			i += game->map.la;
		}
		j++;
	}
}

t_point	**t_point_init(t_game *game)
{
	int		len;

	len = game->map.la * game->map.h;
	game->point[len] = NULL;
	while (--len >= 0)
	{
		game->point[len] = (t_point *)malloc(sizeof(t_point));
		game->point[len]->x = 0;
		game->point[len]->y = 0;
		game->point[len]->z = 0;
		game->point[len]->h = 0;
		game->point[len]->l = 0;
		game->point[len]->color = 0;
	}
	return (game->point);
}

int	calc_tile_size(t_game *game)
{
	int	tile_size;

	tile_size = 0;
	if (game->map.la > game->map.h)
		tile_size = WIDTH / game->map.la;
	else
		tile_size = HEIGHT / game->map.h;
	if (tile_size <= 1)
		tile_size = 2;
	return (tile_size);
}

t_game	*initgame(char *argv[])
{
	int	fd;
	t_read_map	*rm;
	t_game	*g;

	g = (t_game *)malloc(sizeof(t_game));
	g->mlx_ptr = mlx_init();
	g->map.h = malloc_data(argv[1]);
	g->map.la = malloc_data2(argv[1]);
	g->point = (t_point **)malloc(sizeof(t_point) * (g->map.h * g->map.la));
	if (!g->point)
		exit(EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	g->point = t_point_init(g);
	rm = malloc(sizeof(t_read_map));
	if (!rm)
		exit(EXIT_FAILURE);
	rm->idx = 0;
	read_map(g, fd, rm);
	close(fd);
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIDTH, HEIGHT, "Map Viewer");
	g->img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bit_p, &g->line_length,
			&g->endian);
	g->point = draw_map(g, calc_tile_size(g), 0);
	return (g);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
		return (1);
	game = initgame(argv);
	if (!(*game).point)
		exit(EXIT_FAILURE);
	draw_map_03((*game).point, game);
	draw_map_02((*game).point, game);
	mlx_put_image_to_window((*game).mlx_ptr, (*game).win_ptr, (*game).img, 0, 0);
	mlx_hook((*game).win_ptr, 17, 0, (void *)close_cross_button, game);
	main_02(game);
	mlx_loop((*game).mlx_ptr);
	return (0);
}

void	main_02(t_game *game)
{
	if (!game)
		return ;
}

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_p / 8));
	*(unsigned int *)dst = color;
}

t_draw_line draw_line_init(t_draw_line dl, t_point *p0, t_point *p1)
{
	dl.dx = abs(p1->x - p0->x);
	dl.dy = abs(p1->y - p0->y);
	dl.err = dl.dx - dl.dy;
	dl.a = p0->x;
	dl.b = p0->y;
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
	t_draw_line dl;

	dl = draw_line_init(dl, p0, p1);
	while (dl.a != p1->x || dl.b != p1->y)
	{
		if (dl.a >= 0 && dl.a < WIDTH && dl.b >= 0 && dl.b < HEIGHT)
		{
			if (p0->z != 0 || p1->z != 0)
				my_mlx_pixel_put(game, dl.a, dl.b, 0xFF0000);
			else
				my_mlx_pixel_put(game, dl.a, dl.b, 0xFFFFFF);
		}
		dl.err2 = dl.err * 2;
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

