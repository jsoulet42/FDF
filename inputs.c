/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:57:44 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/27 10:19:50 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int key, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key == 65307)
		close_esc(game);
	else if (key == NUM_PAD_1 || key == NUM_PAD_2 || key == NUM_PAD_4
		|| key == NUM_PAD_6 || key == NUM_PAD_7 || key == NUM_PAD_8)
		rotate(key, game);
	else if (key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_UP
		|| key == ARROW_RIGHT)
		ft_move(key, game);
	else if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
		ft_z_plus(key, game);
	return (0);
}

void	ft_z_plus(int key, t_game *game)
{
	int	i;

	i = 0;
	if (key == NUM_PAD_PLUS)
	{
		while (game->point[i])
		{
			if (game->point[i]->z0 > 0 && game->point[i]->z_plus < 19)
				game->point[i]->z_plus++;
			i++;
		}
	}
	else if (key == NUM_PAD_MINUS)
	{
		while (game->point[i])
		{
			if (game->point[i]->z0 > 0 && game->point[i]->z_plus > -19)
				game->point[i]->z_plus--;
			i++;
		}
	}
	project_iso(erase_img(game));
	draw_map_03(game->point, game);
	draw_map_02(game->point, game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
}

void	ft_move(int key, t_game *g)
{
	int	deplacement;

	deplacement = 200;
	if (key == ARROW_DOWN)
		ft_translate_y(g, deplacement);
	else if (key == ARROW_UP)
		ft_translate_y(g, -deplacement);
	else if (key == ARROW_LEFT)
		ft_translate_x(g, -deplacement);
	else if (key == ARROW_RIGHT)
		ft_translate_x(g, deplacement);
	erase_img(g);
	draw_map_03(g->point, g);
	draw_map_02(g->point, g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img, 0, 0);
}

void	rotate(int key, t_game *g)
{
	double	rot;

	rot = 0.05;
	if (key == NUM_PAD_2)
		g->map.alpha += rot;
	else if (key == NUM_PAD_8)
		g->map.alpha -= rot;
	erase_img(g);
	project_iso(g);
	draw_map_03(g->point, g);
	draw_map_02(g->point, g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img, 0, 0);
}
