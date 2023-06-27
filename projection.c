/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:24:46 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/27 10:18:37 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_game *g, int i, double a)
{
	int	p_y;
	int	new_y;
	int	new_z;

	p_y = g->point[i]->y;
	new_y = p_y * cos(a) + -(g->point[i]->z * g->point[i]->z_plus)
		* sin(a);
	new_z = -p_y * sin(a) + g->point[i]->z * cos(a);
	g->point[i]->y = new_y;
	g->point[i]->z = new_z;
}

void	rotate_y(t_game *g, int i, double beta)
{
	int	prev_x;
	int	new_x;
	int	new_z;

	prev_x = g->point[i]->x;
	new_x = prev_x * cos(beta) + g->point[i]->z * sin(beta);
	new_z = -prev_x * sin(beta) + g->point[i]->z * cos(beta);
	g->point[i]->x = new_x;
	g->point[i]->z = new_z * g->point[i]->z_plus;
}

void	rotate_z(t_game *g, int i, double gama)
{
	int	prev_x;
	int	prev_y;
	int	new_x;
	int	new_y;

	prev_x = g->point[i]->x;
	prev_y = g->point[i]->y;
	new_x = prev_x * cos(gama) - prev_y * sin(gama);
	new_y = prev_x * sin(gama) + prev_y * cos(gama);
	g->point[i]->x = new_x;
	g->point[i]->y = new_y;
}

void	ft_translate_x(t_game *g, int sens)
{
	int	i;

	i = 0;
	while (g->point[i] != NULL)
	{
		g->point[i]->x += sens;
		g->point[i]->x0 += sens;
		i++;
	}
}

void	ft_translate_y(t_game *g, int sens)
{
	int	i;

	i = 0;
	while (g->point[i] != NULL)
	{
		g->point[i]->y += sens;
		g->point[i]->y0 += sens;
		i++;
	}
}
