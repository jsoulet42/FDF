/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:14:34 by lolefevr          #+#    #+#             */
/*   Updated: 2023/06/27 09:59:58 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	malloc_data(const char *argv, t_game *g)
{
	int		fd;
	int		i;
	char	*line;
	char	**line2;

	fd = open(argv, O_RDONLY);
	if (fd <= 0)
		exit(EXIT_FAILURE);
	i = 0;
	line = get_next_line(fd);
	line2 = ft_split(line, ' ');
	ft_split_len(line2, &g->map.la);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	g->map.gamma = 0.523599;
	g->map.alpha = 0.523599;
	g->map.beta = 0.523599;
	close(fd);
	return (i);
}

void	ft_split_len(char **line, int *len)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1][0] == '\n')
		i--;
	*len = i;
	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

int	calc_tile_size(t_game *game)
{
	int	tile_size;

	tile_size = 0;
	if (game->map.la > game->map.h)
		tile_size = WIDTH / game->map.la / 2;
	else
		tile_size = HEIGHT / game->map.h / 2;
	if (tile_size <= 1)
		tile_size = 2;
	return (tile_size);
}

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bit_p / 8));
	*(unsigned int *)dst = color;
}
