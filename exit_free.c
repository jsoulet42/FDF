/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lolefevr <lolefevr@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:06:47 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/24 18:24:06 by lolefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_esc(t_game *img)
{
	int	i;

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
	return (0);
}

void	*close_cross_button(t_game *img)
{
	int	i;

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
}

void	ft_free_gnl(char **line)
{
	int	i;

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
	return ;
}

t_game	*erase_img(t_game *g)
{
	if (g->img)
		mlx_destroy_image(g->mlx_ptr, g->img);
	g->img = mlx_new_image(g->mlx_ptr, WIDTH, HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bit_p, &g->line_length,
			&g->endian);
	return (g);
}
