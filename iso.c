/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:19:12 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/27 10:19:40 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

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
	int	i;

	i = 0;
	while (game->point[i] != NULL)
	{
		iso(&game->point[i]->x, &game->point[i]->y, game->point[i]->z);
		i++;
	}
	return (game);
}

t_game	*project_iso(t_game *g)
{
	int	i;

	i = 0;
	while (g->point[i] != NULL)
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
