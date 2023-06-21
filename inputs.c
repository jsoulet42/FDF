/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:57:44 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/21 15:45:09 by jsoulet          ###   ########.fr       */
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

int	close_esc(int keycode, t_game  *img)
{
	int	i;

	i = 0;
	if (keycode == 65307)
	{
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
	}
	return 0;
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
