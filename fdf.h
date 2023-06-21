/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:47:04 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/21 10:31:54 by jsoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "INCLUDES/mlx/mlx.h"
# include "INCLUDES/mlx/mlx_int.h"
# include "INCLUDES/libft/libft.h"
# include "INCLUDES/get_next_line/get_next_line.h"
# include "INCLUDES/printf/ft_printf.h"
# include <math.h>
# include <GL/gl.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define TILE_SIZE 32
# define WIDTH 1200
# define HEIGHT 800
# define bmin "0123456789abcdef"
# define bmaj "0123456789ABCDEF"

typedef struct s_map
{
	int		la;
	int		h;
}				t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int x0;
	int	y0;
	int	z0;
	int	l;
	int	h;
	int	color;

}				t_point;

typedef struct s_game
{
	void		*img;
	char		*addr;
	int			bit_p;
	int			line_length;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
//	int			count_click;
//	int			count;
//	int		**token_colors;
	t_map	map;
	t_point	**point;
}				t_game;

/*typedef struct s_utils
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

}				t_utils;*/

typedef struct s_read_map
{
	int		i;
	int		j;
	int		total_rows;
	int		idx;
	int		max_width;
	char	**line;
	char	*line2;
	char	**tokens;
}				t_read_map;

typedef struct s_draw_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	a;
	int	b;
	int	err2;
	int color;

}				t_draw_line;

typedef	struct s_previous
{
	int		x;
	int		y;
	int		z;
	int		l;
	int		h;
	int		color;
}				t_previous;


void		read_map(t_game *game, int fd, t_read_map *rm);
t_point		**draw_map(t_game *game, int ts, int i);
void		my_mlx_pixel_put(t_game *data, int x, int y, int color);
int			mouse_event(int keycode, int x, int y, t_game *img);
void		*close_cross_button(t_game *img);
int			close_esc(int keycode, t_game *img);
int			count_move(int keycode, t_game *img);
void		ft_zoom_plus(t_point **point);
void		ft_zoom_moin(t_point **point);
t_game		*initgame(char *argv[]);
void		main_02(t_game *game);
int			calc_tile_size(t_game *game);
int			draw_line(t_game *game, t_point *p0, t_point *p1);
t_point		**t_point_init(t_game *game);
void		draw_map_02(t_point **p, t_game *game);
void		draw_map_03(t_point **p, t_game *game);
int			malloc_data(const char *argv);
void		read_map_init(int fd, t_read_map *rm);
char		**token_colors(t_read_map rm, char *argv);
int 		in_str(char *str, char c);
int			ft_atohex(char *str, char *basemin, char *basemaj);
void		ft_free_gnl(char **line);
t_game		*project_iso_02(t_game *game);

#endif
