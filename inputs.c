/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:57:44 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/23 18:05:50 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



/*void ft_zoom_plus(t_point **point)
{
	int	i;

	i = 0;
	printf("%d\n", point[i]->z);
	while (point[i])
	{
		if (point[i]->z > 0)
		{
			point[i]->z += 1;
			printf("%d\n", point[i]->z);
		}
		i++;
	}
}*/

/*void ft_zoom_moin(t_point **point)
{
	int	i;

	i = 0;
	while (point[i])
	{
		if (point[i]->z > 0)
			point[i]->z -= 1;
		i--;
	}
}*/

int close_esc(t_game *img)
{
	int i;

	i = 0;
	if (img->img)
		mlx_destroy_image(img->mlx_ptr, img->img);
	while (img->point[i])
	{
		free(img->point[i]);
		i++;
	}
	free(img->point);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_display(img->mlx_ptr);
	mlx_loop_end(img->mlx_ptr);
	free(img->mlx_ptr);
	free(img);
	exit(0);
	return 0;
}
int			key_press(int key, void *param)
{
	t_game	*game;

	//ft_printf("key = %d\n", key);
	game = (t_game *)param;
	if (key == 65307)
		close_esc(game);
	else if (key == NUM_PAD_1 || key == NUM_PAD_2 || key == NUM_PAD_4
		|| key == NUM_PAD_6 || key == NUM_PAD_7 || key == NUM_PAD_8)
		{
			//ft_printf("key = %d\n", key);
			rotate(key, game);
		}
	else if (key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_UP
			|| key == ARROW_RIGHT)
		ft_move(key, game);
	else if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
		ft_z_plus(key, game);
	return (0);
}

void	ft_z_plus(int key, t_game *game)
{
	int i;

	i = 0;
	if (key == NUM_PAD_PLUS)
	{
		while (game->point[i])
		{
			if (game->point[i]->z0 > 0)
			{
				if (game->point[i]->z_plus < 19)
					game->point[i]->z_plus++;
			}
			i++;
		}
	}
	else if (key == NUM_PAD_MINUS)
	{
		while (game->point[i])
		{
			if (game->point[i]->z0 > 0)
			{
				if (game->point[i]->z_plus > -19)
					game->point[i]->z_plus--;
			}
			i++;
		}
	}
	erase_img(game);
	project_iso(game);
	draw_map_03(game->point, game);
	draw_map_02(game->point, game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
}

void	ft_move(int key, t_game *g)
{
	int deplacement;

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


	my_mlx_pixel_put(g, g->cx, g->cy, 0xFF0000);
	my_mlx_pixel_put(g, g->cx + 1, g->cy, 0xFF0000);
	my_mlx_pixel_put(g, g->cx, g->cy + 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx + 1, g->cy + 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx - 1, g->cy, 0xFF0000);
	my_mlx_pixel_put(g, g->cx, g->cy - 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx - 1, g->cy - 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx + 1, g->cy - 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx - 1, g->cy + 1, 0xFF0000);
	calc_centre(g);

	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img, 0, 0);
}

void	rotate(int key, t_game *g)
{
	double rot;

	rot = 0.05;
	if (key == NUM_PAD_2)
		g->map.alpha += rot;
	else if (key == NUM_PAD_8)
		g->map.alpha -= rot;
	else if (key == NUM_PAD_4)
		g->map.beta -= rot;
	else if (key == NUM_PAD_6)
		g->map.beta += rot;
	else if (key == NUM_PAD_1)
		g->map.gamma += rot;
	else if (key == NUM_PAD_7)
		g->map.gamma -= rot;
	erase_img(g);
	project_iso(g);
	draw_map_03(g->point, g);
	draw_map_02(g->point, g);



	my_mlx_pixel_put(g, g->cx, g->cy, 0xFF0000);
	my_mlx_pixel_put(g, g->cx + 1, g->cy, 0xFF0000);
	my_mlx_pixel_put(g, g->cx, g->cy + 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx + 1, g->cy + 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx - 1, g->cy, 0xFF0000);
	my_mlx_pixel_put(g, g->cx, g->cy - 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx - 1, g->cy - 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx + 1, g->cy - 1, 0xFF0000);
	my_mlx_pixel_put(g, g->cx - 1, g->cy + 1, 0xFF0000);


	//draw_line(g, g->point[0], g->point[g->map.la * g->map.h - 1]);
	//draw_line(g, g->point[(g->map.la * g->map.h - g->map.la)], g->point[g->map.la - 1]);



	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img, 0, 0);
}
void	*close_cross_button(t_game *img)
{
	int	i;

	i = 0;
	if (img->img)
		mlx_destroy_image(img->mlx_ptr, img->img);
	ft_printf("close_cross_button\n");
	while (img->point[i])
	{
		free(img->point[i]);
		i++;
	}
	free(img->point);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_display(img->mlx_ptr);
	mlx_loop_end(img->mlx_ptr);
	free(img->mlx_ptr);
	free(img);
	exit(0);
}
/*int mouse_event(int keycode, int x, int y, t_game *img)
{
	(void)img->point;
	(void)x;
	(void)y;
	clic gauche
	if (keycode == 1)
	{
		img->count_click += 1;
		printf("zoom = %d\n", img->count_click);
		ft_zoom_plus(point);

	}
	clic droit
	if (keycode == 3)
	{
		img->count_click -= 1;
		printf("zoom = %d\n", img->count_click);
		ft_zoom_moin(point);
	}
	return (0);
}*/

/*int	count_move(int keycode, t_game *img)
{
	touche W A S D
	if ((((keycode == 119) || keycode == 97) || keycode == 115) || keycode == 100)
	{
		img->count += 1;
		printf("number of movement = %d\n", img->count);
	}
	return (0);
}*/
