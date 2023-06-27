/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 09:49:08 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/27 10:25:37 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int a)
{
	if (a > 0)
		return (a);
	return (-a);
}

void	color_map_empty(t_game *g)
{
	extern struct s_col_name	mlx_col_name[];
	int							i;
	int							j;
	int							k;

	i = 0;
	j = 18;
	k = 0;
	while (g->point[i])
	{
		k = color_attrib(g, g->point[i]->z);
		if (k != 0)
			g->point[i]->color = k;
		else
			g->point[i]->color = mlx_col_name[j].color;
		i++;
		j = (j + 200) % 750;
	}
}

int	color_attrib(t_game *g, int z)
{
	int	i;

	i = 0;
	while (g->point[i])
	{
		if (ft_abs(g->point[i]->z - z) < 2)
		{
			if (g->point[i]->color != 0xFFFFFF)
				return (g->point[i]->color);
		}
		i++;
	}
	return (0);
}
