/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:58 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/21 17:31:56 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_game *g, int i, double gamma);
void	rotate_x(t_game *g, int i, double alpha);
void	rotate_y(t_game *g, int i, double beta);
t_game	*project_iso(t_game *game);
void	erase_img(t_game *g);

void read_map_init(int fd, t_read_map *rm)
{
	rm->i = 0;
	rm->max_width = 0;
	rm->line2 = get_next_line(fd);
	rm->line = ft_split(rm->line2, ' ');
	rm->tokens = NULL;
	free(rm->line2);
}

int malloc_data2(const char *argv)
{
	int fd;
	int i;
	char **line;
	char *line2;

	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	i = 0;
	line2 = get_next_line(fd);
	line = ft_split(line2, ' ');
	while (line[i])
		free(line[i++]);
	close(fd);
	free(line2);
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

int malloc_data(const char *argv)
{
	int fd;
	int i;
	char *line;

	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

t_point **draw_map(t_game *game, int ts, int i)
{
	int c1;
	int c2;

	c1 = ((WIDTH - game->map.la * ts) / 2) + ts + 200;
	c2 = ((HEIGHT - game->map.h * ts) / 2) + ts - 300 ;
	//c1 = ((WIDTH - game->map.la * ts) / 2) + ts / 2;
	//c2 = ((HEIGHT - game->map.h * ts) / 2) + ts / 2;
	while (game->point[++i])
	{
		game->point[i]->x = game->point[i]->x * ts + c1;
		game->point[i]->y = game->point[i]->y * ts + c2;
	//	ft_printf("x = %d, y = %d\n", game->point[i]->x, game->point[i]->y);
	}
	return (game->point);
}

void draw_map_02(t_point **p, t_game *game)
{
	int i;

	i = -1;
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
	g->map.la = malloc_data2(argv[1]);
	g->map.h = malloc_data(argv[1]);
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
	//g = project_iso(g);
	//ZOOM
	g->point = draw_map(g, calc_tile_size(g), -1);
	g = project_iso_02(g);
	//g = project_iso(g);
	//g->point = draw_map(g, calc_tile_size(g), -1);
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
	mlx_key_hook(game->win_ptr, (void *)close_esc, game);
	//main_02(game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

/*void main_02(t_game *game)
{
	if (!game)
		return;
	erase_img(game);
	project_iso(game);
	//game->point = draw_map(game, calc_tile_size(game), -1);
	draw_map_03(game->point, game);
	draw_map_02(game->point, game);
	mlx_put_image_to_window(&game->mlx_ptr, &game->win_ptr, &game->img, 0, 0);
}*/

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

t_draw_line draw_line_init(t_draw_line dl, t_point *p0, t_point *p1)
{
	dl.dx = abs(p1->x - p0->x);
	dl.dy = abs(p1->y - p0->y);
	//ft_printf("dx = %d, dy = %d\n", dl.dx, dl.dy);
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
int debug_draw_line = 0;
int debug_draw_line_while = 0;

int draw_line(t_game *game, t_point *p0, t_point *p1)
{
	t_draw_line dl;

	dl = draw_line_init(dl, p0, p1);
	debug_draw_line_while = 0;

	while (dl.a != p1->x || dl.b != p1->y)
	{
//		ft_printf("dl.a = %d, dl.b = %d\n", dl.a, dl.b);
//		ft_printf("p1->x = %d, p1->y = %d\n", p1->x, p1->y);
		//ft_printf("dl.a - p1->x = %d, dl.b - p1->y = %d\n", dl.a - p1->x, dl.b - p1->y);
		if (debug_draw_line_while++ > 500)
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
		/*if (abs(dl.a - p1->x) <= 1 || abs(dl.b - p1->y) <= 1)
		{
			ft_printf("draw_line break\n");
			break;
		}*/
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
//		ft_printf("x = %d, y = %d\n", game->point[i]->x, game->point[i]->y);
		iso(&game->point[i]->x, &game->point[i]->y, game->point[i]->z);
//		ft_printf("z = %d\n", game->point[i]->z);
//		ft_printf("x = %d, y = %d\n\n", game->point[i]->x, game->point[i]->y);
		i++;
	}
	return (game);
}

/*t_game	*project_iso(t_game *game)
{
	int i;

	i = 0;
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
	while(game->point[i] != NULL)
	{
		game->point[i]->x0 = game->point[i]->x;
		game->point[i]->y0 = game->point[i]->y;
		game->point[i]->x = (game->point[i]->x0 - game->point[i]->y0) * cos(0.523599);
		game->point[i]->y = -game->point[i]->z + (game->point[i]->x0 + game->point[i]->y0) * sin(0.523599);
		i++;

	}
	return (game);
}*/

t_game	*project_iso(t_game *game)
{
	int i;

	i = 0;
	while(game->point[i] != NULL)
	{
		game->point[i]->x0 = game->point[i]->x;
		game->point[i]->y0 = game->point[i]->y;
		rotate_x(game, i, 0.523599);
		rotate_y(game, i, 0.523599);
		rotate_z(game, i, 0.523599);
		i++;
	}
	return (game);
}


void rotate_x(t_game *g, int i, double alpha)
{
	g->point[i]->y = g->point[i]->y0 * cos(alpha) + g->point[i]->z * sin(alpha);
	g->point[i]->z = -g->point[i]->y0 * sin(alpha) + g->point[i]->z * cos(alpha);
	//*y = previous_y * cos(alpha) + *z * sin(alpha);
	//*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(t_game *g, int i, double beta)
{
	g->point[i]->x = g->point[i]->x0 * cos(beta) + g->point[i]->z * sin(beta);
	g->point[i]->z = -g->point[i]->x0 * sin(beta) + g->point[i]->z * cos(beta);
	//*x = previous_x * cos(beta) + *z * sin(beta);
	//*z = -previous_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(t_game *g, int i, double gamma)
{

	g->point[i]->x0 = g->point[i]->x;
	g->point[i]->y0 = g->point[i]->y;

	g->point[i]->x = g->point[i]->x0 * cos(gamma) - g->point[i]->y0 * sin(gamma);
	g->point[i]->y = g->point[i]->x0 * sin(gamma) + g->point[i]->y0 * cos(gamma);
	//*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	//*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}


/*static void rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}*/



