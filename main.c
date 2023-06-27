/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:12:58 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/27 10:16:38 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_game	*initgame2(t_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIDTH, HEIGHT, "Map Viewer");
	g->img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bit_p, &g->line_length,
			&g->endian);
	g->cx = (g->point[0]->x + g->point[g->map.la -1]->x
			+ g->point[g->map.h - 1]->x
			+ g->point[g->map.la * g->map.h - 1]->x) / 4;
	g->cy = (g->point[0]->y + g->point[g->map.la -1]->y
			+ g->point[g->map.h - 1]->y
			+ g->point[g->map.la * g->map.h - 1]->y) / 4;
	g->point = draw_map(g, calc_tile_size(g), -1);
	g = project_iso(g);
	return (g);
}

t_game	*initgame(char *argv[], int fd)
{
	t_read_map	*rm;
	t_game		*g;

	g = (t_game *)malloc(sizeof(t_game));
	if (!g)
		exit(EXIT_FAILURE);
	g->mlx_ptr = mlx_init();
	g->map.h = malloc_data(argv[1], g);
	g->z_coeff = 1;
	g->in_color = 0;
	g->point = (t_point **)malloc(sizeof(t_point) * (g->map.h * g->map.la + 1));
	if (!g->point)
		exit(EXIT_FAILURE);
	g->point[g->map.h * g->map.la + 1] = NULL;
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
	return (initgame2(g));
}

t_point	**t_point_init(t_game *game)
{
	int	i;
	int	len;

	i = -1;
	len = game->map.la * game->map.h;
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

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
		return (1);
	game = initgame(argv, open(argv[1], O_RDONLY));
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
