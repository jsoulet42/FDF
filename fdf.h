/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:47:04 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/13 14:15:34 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "INCLUDES/mlx/mlx.h"
# include "INCLUDES/mlx/mlx_int.h"
# include "INCLUDES/libft/libft.h"
# include "INCLUDES/get_next_line/get_next_line.h"
# include "INCLUDES/printf/ft_printf.h"
# include "INCLUDES/printf/ft_printf.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>

#define TILE_SIZE 32
#define WIDTH 1200
#define HEIGHT 800

typedef struct	s_map
{
	int		width;
	int		height;
	int	**data;
}				t_map;

typedef struct	s_game
{
	void	*img;
	char	*addr;
	int		bit_p;
	int		line_length;
	int		endian;
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
}				t_game;

typedef struct	s_utils
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

}				t_utils;
typedef struct	s_point
{
	int	x;
	int	y;
	int	z;

}				t_point;

void	read_map(t_game *game, const char *filename);
void draw_map(t_game *game, int ts, int y, int i);
void	my_mlx_pixel_put(t_game *data, int x, int y, int color);
# endif
