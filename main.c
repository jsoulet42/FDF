/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:58 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/23 18:14:16 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_game *g, int i, double gamma);
void	rotate_x(t_game *g, int i, double alpha);
void	rotate_y(t_game *g, int i, double beta);
void	erase_img(t_game *g);
void ft_split_len(char **line, int *len);
void read_map_init(int fd, t_read_map *rm)
{
	rm->i = 0;
	rm->max_width = 0;
	rm->line2 = get_next_line(fd);
	rm->line = ft_split(rm->line2, ' ');
	rm->tokens = NULL;
	free(rm->line2);
}

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

int ft_atohex(char *str, char *basemin, char *basemaj)
{
	int i;
	int j;
	int n;

	i = 2;
	n = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && (str[i] != basemin[j] && str[i] != basemaj[j]))
			j++;
		n = n * 16 + j;
		i++;
		if (str[i] == '\n')
			break;
	}
	return (n);
}

void ft_free_gnl(char **line)
{
	int i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			free(line[i]);
			i++;
		}
		free(line);
	}
	return;
}

void read_map(t_game *g, int fd, t_read_map *rm)
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
				free(rm->tokens[0]);
				free(rm->tokens[1]);
				free(rm->tokens);
			}
			else
			{
				g->point[rm->idx]->z = ft_atoi(rm->line[rm->i]);
				g->point[rm->idx]->color = 0xFFFFFF;
			}
			g->point[rm->idx]->h = rm->i++;
			g->point[rm->idx]->l = rm->j;
			g->point[rm->idx]->x = g->point[rm->idx]->h;
			g->point[rm->idx]->y = g->point[rm->idx]->l;
			rm->idx++;
		}
		rm->j++;
		ft_free_gnl(rm->line);
		read_map_init(fd, rm);
	}
	free(rm);
}

int malloc_data(const char *argv, t_game *g)
{
	int fd;
	int i;
	char *line;
	char **line2;

	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	line2 = ft_split(line, ' ');
	ft_split_len(line2, &g->map.la);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	g->map.gamma = 0.523599;
	g->map.alpha = 0.523599;
	g->map.beta = 0.523599;
	close(fd);
	return (i);
}

void ft_split_len(char **line, int *len)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1][0] == '\n')
		i--;
	*len = i;
	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

t_point **draw_map(t_game *game, int ts, int i)
{
	int c1;
	int c2;

	c1 = ((WIDTH - game->map.la * ts) / 2) + ts + 200;
	c2 = ((HEIGHT - game->map.h * ts) / 2) + ts - 300;
	//c1 = ((WIDTH - game->map.la * ts) / 2) + ts / 2;
	//c2 = ((HEIGHT - game->map.h * ts) / 2) + ts / 2;
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
void ft_print_point(t_point **p)
{
	int i;

	i = -1;
	while (p[++i])
		ft_printf("x = %d, y = %d, z = %d, l = %d, h = %d\n", p[i]->x, p[i]->y, p[i]->z, p[i]->l, p[i]->h);
}

void draw_map_02(t_point **p, t_game *game)
{
	int i;

	i = -1;
	//ft_print_point(p);
	while (p[++i])
	{
		if (p[i + 1] && p[i]->l == p[i + 1]->l)
			draw_line(game, p[i], p[i + 1]);
	}
}



void draw_map_03(t_point **p, t_game *game)
{
	unsigned int i;
	unsigned int j;

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

t_point **t_point_init(t_game *game)
{
	int i;
	int len;

	i = -1;
	len = game->map.la * game->map.h;
	ft_printf("largeur = %d, hauteur = %d, len = %d\n", game->map.la, game->map.h, len);
	while (++i <= len)
	{
		game->point[i] = (t_point *)malloc(sizeof(t_point));
		game->point[i]->x = 0;
		game->point[i]->y = 0;
		game->point[i]->z = 0;
		game->point[i]->h = 0;
		game->point[i]->l = 0;
		game->point[i]->z_plus = 1;
		game->point[i]->color = 0;
	}
	game->point[i] = NULL;
	return (game->point);
}

int calc_tile_size(t_game *game)
{
	int tile_size;

	tile_size = 0;
	if (game->map.la > game->map.h)
		tile_size = WIDTH / game->map.la / 2;
	else
		tile_size = HEIGHT / game->map.h / 2;
	if (tile_size <= 1)
		tile_size = 2;
	return (tile_size);
}

t_game *initgame(char *argv[])
{
	int fd;
	t_read_map *rm;
	t_game *g;

	g = (t_game *)malloc(sizeof(t_game));
	if (!g)
		exit(EXIT_FAILURE);
	g->mlx_ptr = mlx_init();
	g->map.h = malloc_data(argv[1], g);
	g->z_coeff = 1;
	g->point = (t_point **)malloc(sizeof(t_point) * (g->map.h * g->map.la + 1));
	if (!g->point)
		exit(EXIT_FAILURE);
	g->point[g->map.h * g->map.la + 1] = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	g->point = t_point_init(g);
	rm = malloc(sizeof(t_read_map));
	if (!rm)
		exit(EXIT_FAILURE);
	rm->idx = 0;
	rm->j = 0;
	read_map(g, fd, rm);
	close(fd);

	g->win_ptr = mlx_new_window(g->mlx_ptr, WIDTH, HEIGHT, "Map Viewer");
	g->img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bit_p, &g->line_length,
								&g->endian);
	//ZOOM
	g->cx = (g->point[0]->x + g->point[g->map.la -1]->x + g->point[g->map.h - 1]->x
		+ g->point[g->map.la * g->map.h - 1]->x) / 4;
	g->cy = (g->point[0]->y + g->point[g->map.la -1]->y + g->point[g->map.h - 1]->y
		+ g->point[g->map.la * g->map.h - 1]->y) / 4;
	g->point = draw_map(g, calc_tile_size(g), -1);
	calc_centre(g);

	//g->point = draw_map(g, calc_tile_size(g), -1);
	//g = project_iso_02(g);
	g = project_iso(g);
	return (g);
}

int main(int argc, char *argv[])
{
	t_game *game;

	if (argc != 2)
		return (1);
	game = initgame(argv);
	if (!game->point)
		exit(EXIT_FAILURE);
	draw_map_03(game->point, game);
	draw_map_02(game->point, game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
	mlx_hook(game->win_ptr, 17, 0, (void *)close_cross_button, game);
	mlx_key_hook(game->win_ptr, (void *)key_press, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

void	erase_img(t_game *g)
{	if (g->img)
		mlx_destroy_image(g->mlx_ptr, g->img);
	g->img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bit_p, &g->line_length,
								&g->endian);
}

void my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_p / 8));
	*(unsigned int *)dst = color;
}

t_draw_line draw_line_init(t_draw_line dl, t_point *p0, t_point *p1, t_game *g)
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

int draw_line(t_game *game, t_point *p0, t_point *p1)
{
	t_draw_line dl;

	dl = draw_line_init(dl, p0, p1, game);
	int debug_draw_line_while = 0;

	while (dl.a != p1->x || dl.b != p1->y)
	{
		if (debug_draw_line_while++ > 50000)
		{
			ft_printf("draw_line infinite loop\n");
			break;
		}
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

static void	iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	if (z != 0)
		*y = -z + (previous_x + previous_y) * sin(0.523599);
	else
		*y = (previous_x + previous_y) * sin(0.523599);
}

t_game	*project_iso_02(t_game *game)
{
	int i;

	i = 0;
	while(game->point[i] != NULL)
	{
		iso(&game->point[i]->x, &game->point[i]->y, game->point[i]->z);
		i++;
	}
	return (game);
}

t_game	*project_iso(t_game *g)
{
	int i;

	i = 0;
	while(g->point[i] != NULL)
	{
		g->point[i]->x = g->point[i]->x0;
		g->point[i]->y = g->point[i]->y0;
		g->point[i]->z = g->point[i]->z0;
		rotate_x(g, i, g->map.alpha);
		rotate_y(g, i, g->map.beta);
		rotate_z(g, i, g->map.gamma);
		i++;
	}
	return (g);
}
void rotate_x(t_game *g, int i, double alpha)
{
	int previous_y;
	int new_y;
	int new_z;


	previous_y = g->point[i]->y;
	new_y = (previous_y - g->cx) * cos(alpha) + -(g->point[i]->z * g->point[i]->z_plus) * sin(alpha) + g->cx;
	new_z = -(previous_y - g->cx) * sin(alpha) + g->point[i]->z * cos(alpha);
	g->point[i]->y = new_y;
	g->point[i]->z = new_z;
}
void	rotate_y(t_game *g, int i, double beta)
{
	int	previous_x;
	int	new_x;
	int	new_z;

	previous_x = g->point[i]->x;
	new_x = (previous_x - g->cy) * cos(beta) + g->point[i]->z * sin(beta) + g->cy;
	new_z = -(previous_x - g->cy) * sin(beta) + g->point[i]->z * cos(beta);
	g->point[i]->x = new_x;
	g->point[i]->z = new_z * g->point[i]->z_plus;
}
void	rotate_z(t_game *g, int i, double gamma)
{
	int previous_x;
	int previous_y;
	int new_x;
	int new_y;

	previous_x = g->point[i]->x;
	previous_y = g->point[i]->y;
	new_x = (previous_x - g->cx) * cos(gamma) - (previous_y - g->cy) * sin(gamma) + g->cx;
	new_y = (previous_x - g->cx) * sin(gamma) + (previous_y - g->cy) * cos(gamma) + g->cy;
	g->point[i]->x = new_x;
	g->point[i]->y = new_y;
}

void ft_translate_x(t_game *g, int sens)
{
	int i;

	i = 0;
	while(g->point[i] != NULL)
	{
		g->point[i]->x += sens;
		g->point[i]->x0 += sens;
		i++;
	}
	calc_centre(g);


	//g->cx = (g->point[0]->x + g->point[g->map.la - 1]->x + g->point[g->map.h - 1]->x + g->point[g->map.la * g->map.h - 1]->x) / 4;
	//g->cy = (g->point[0]->y + g->point[g->map.la -1]->y + g->point[g->map.h - 1]->y
	//	+ g->point[g->map.la * g->map.h - 1]->y) / 4;

	/*draw_line(g, g->point[0], g->point[g->map.la * g->map.h - 1]);
	draw_line(g, g->point[g->map.la - 1], g->point[g->map.h - 1]);*/
}

void ft_translate_y(t_game *g, int sens)
{
	int i;

	i = 0;
	while(g->point[i] != NULL)
	{
		g->point[i]->y += sens;
		g->point[i]->y0 += sens;
		i++;
	}
	calc_centre(g);
}


void	calc_centre(t_game *g)
{
	int a1;
	int b1;
	int c1;
	int d1;
	int a2;
	int b2;
	int c2;
	int d2;

	a1 = g->point[0]->x;
	b1 = g->point[g->map.la * g->map.h - 1]->x;
	c1 = g->point[(g->map.la * g->map.h - g->map.la)]->x;
	d1 = g->point[g->map.la - 1]->x;

	a2 = g->point[0]->y;
	b2 = g->point[g->map.la * g->map.h - 1]->y;
	c2 = g->point[(g->map.la * g->map.h - g->map.la)]->y;
	d2 = g->point[g->map.la - 1]->y;

	g->cx = (a1 + b1 + c1 + d1) / 4;
	g->cy = (a2 + b2 + c2 + d2) / 4;
}
