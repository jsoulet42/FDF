/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:58 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/13 15:30:32 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int calc_tile_size(t_game *game);
int drawLine(t_game *game, t_point *p0, t_point *p1);
t_point **t_point_init(t_game *game);
void draw_map_02(t_point **p, t_game *game);




void read_map(t_game *game, const char *filename)
{
	int fd;
	int i;
	char *line;
	int max_width = 0;
	int total_rows = 0;

	game->map.data = (int **)malloc(sizeof(int *) * 1000);
	if (!game->map.data)
	{
		perror("Error: could not allocate memory");
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		perror("Error: could not open file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		char **tokens = ft_split(line, ' ');
		int index = 0;
		while (tokens[index])
			index++;
		if (index > max_width)
			max_width = index;
		game->map.data[total_rows] = (int *)malloc(sizeof(int) * (index));
		if (!game->map.data[total_rows])
		{
			perror("Error: could not allocate memory");
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (i < index)
		{
			game->map.data[total_rows][i] = atoi(tokens[i]);
			ft_printf("%d ", game->map.data[total_rows][i]);
			free(tokens[i++]);
		}
		ft_printf("\n");
		total_rows++;
		free(tokens);
		line = get_next_line(fd);
	}
	game->map.height = total_rows;
	game->map.width = max_width;
	close(fd);
}

void draw_map(t_game *game, int ts, int y, int i)
{
	int x;
	int c1;
	int c2;
	t_point **p1;

	c1 = (WIDTH - (game->map.width * ts)) / 2;
	c2 = (HEIGHT - (game->map.height * ts)) / 2;
	p1 = t_point_init(game);
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (x * ts + c1 <= WIDTH && y * ts + c2 <= HEIGHT &&
				x * ts + c1 >= 0 && y * ts + c2 >= 0)
			{
				p1[i]->x = x * ts + c1;
				p1[i]->y = y * ts + c2;
				p1[i++]->z = game->map.data[y][x];
				//my_mlx_pixel_put(game, x * ts + c1, y * ts + c2, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
	draw_map_02(p1, game);
}

void draw_map_02(t_point **p, t_game *game)
{
	int i;
	int itemp;
	int ytemp;
	i = 0;
	if (!game)
		return ;

	while (p[i + 1])
	{
		ytemp = p[i]->y;
		itemp = i;
		while (p[itemp + 1] && p[itemp + 1]->y == ytemp)
		{
			drawLine(game, p[itemp], p[itemp + 1]);
			itemp += 2;
		}
		i++;
	}
}

void draw_map_03(t_point **p, t_game *game)
{

}

t_point **t_point_init(t_game *game)
{
	int	len;
	t_point **p;

	len = game->map.height * game->map.width;
	p = (t_point **)malloc(sizeof(t_point *) * len + 1);
	if (!p)
	{
		perror("Error: could not allocate memory");
		exit(EXIT_FAILURE);
	}
	p[len] = NULL;
	while (--len >= 0)
	{
		p[len] = (t_point *)malloc(sizeof(t_point));
		p[len]->x = 0;
		p[len]->y = 0;
		p[len]->z = 0;
	}
	return (p);
}

int calc_tile_size(t_game *game)
{
	int tile_size;

	tile_size = 0;
	if (game->map.width > game->map.height)
		tile_size = WIDTH / game->map.width;
	else
		tile_size = HEIGHT / game->map.height;
	tile_size /= 2;
	if (tile_size <= 1)
		tile_size = 2;
	return (tile_size);
}

int main(int argc, char *argv[])
{
	t_game game;

	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	game.mlx_ptr = mlx_init();
	game.map.width = 1;
	game.map.height = 1;
	read_map(&game, argv[1]);
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Map Viewer");
	game.img = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
	game.addr = mlx_get_data_addr(game.img, &game.bit_p, &game.line_length, &game.endian);
	draw_map(&game, calc_tile_size(&game), 0, 0);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.img, 0, 0);
	mlx_loop(game.mlx_ptr);
	return (0);
}

void my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
	{
		ft_printf("x: %d, y: %d\n", x, y);
		ft_printf("my_mlx_pixel_put: tentative de dessin en dehors de l'image\n");
		return;
	}
	dst = data->addr + (y * data->line_length + x * (data->bit_p / 8));
	*(unsigned int *)dst = color;
}

int drawLine(t_game *game, t_point *p0, t_point *p1)
{
	int dx = abs(p1->x - p0->x);
	int dy = abs(p1->y - p0->y);
	int sx = (p0->x < p1->x) ? 1 : -1;
	int sy = (p0->y < p1->y) ? 1 : -1;
	int err = dx - dy;
	if (p0->x > WIDTH || p1->x > WIDTH || p0->y > HEIGHT || p1->y > HEIGHT)
	{
		ft_printf("Erreur : les coordonnees sont en dehors de la fenetre\n");
		return (0);
	}
	while (p0->x != p1->x || p0->y != p1->y)
	{
		my_mlx_pixel_put(game, p0->x, p0->y, 0x0000FF);
		int err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			p0->x += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			p0->y += sy;
		}
	}
		//my_mlx_pixel_put(game, p0->x, p0->y, 0x0000FF);
	return (0);
}
