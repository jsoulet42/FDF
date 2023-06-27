/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoulet <jsoulet@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:47:04 by jsoulet           #+#    #+#             */
/*   Updated: 2023/06/27 10:30:44 by jsoulet          ###   ########.fr       */
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
# define BMIN "0123456789abcdef"
# define BMAJ "0123456789ABCDEF"
# define NUM_PAD_0			65438
# define NUM_PAD_1			65436
# define NUM_PAD_2			65433
# define NUM_PAD_3			65435
# define NUM_PAD_4			65430
# define NUM_PAD_5			65437
# define NUM_PAD_6			65432
# define NUM_PAD_7			65429
# define NUM_PAD_8			65431
# define NUM_PAD_9			65434
# define NUM_PAD_PLUS		65451
# define NUM_PAD_MINUS		65453
# define ARROW_LEFT			65361
# define ARROW_UP			65362
# define ARROW_RIGHT		65363
# define ARROW_DOWN			65364

typedef struct s_map
{
	int		la;
	int		h;
	double	alpha;
	double	beta;
	double	gamma;
}				t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	x0;
	int	y0;
	int	z0;
	int	l;
	int	h;
	int	color;
	int	z_plus;
	int	zoom;

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
	int			z_coeff;
	int			cx;
	int			cy;
	int			zoom;
	int			in_color;
	t_map		map;
	t_point		**point;
}				t_game;

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
	int	color;
}				t_draw_line;

typedef struct s_previous
{
	int		x;
	int		y;
	int		z;
	int		l;
	int		h;
	int		color;
}				t_previous;

t_game		*initgame2(t_game *g);
void		read_map(t_game *game, int fd, t_read_map *rm);
t_point		**draw_map(t_game *game, int ts, int i);
void		my_mlx_pixel_put(t_game *data, int x, int y, int color);
void		*close_cross_button(t_game *img);
int			close_esc(t_game *img);
t_game		*initgame(char *argv[], int fd);
int			calc_tile_size(t_game *game);
int			draw_line(t_game *game, t_point *p0, t_point *p1);
t_point		**t_point_init(t_game *game);
void		draw_map_02(t_point **p, t_game *game);
void		draw_map_03(t_point **p, t_game *game);
int			malloc_data(const char *argv, t_game *game);
void		read_map_init(int fd, t_read_map *rm);
int			in_str(char *str, char c);
int			ft_atohex(char *str, char *basemin, char *basemaj);
void		ft_free_gnl(char **line);
t_game		*project_iso_02(t_game *game);
int			key_press(int key, void *param);
void		rotate(int key, t_game *game);
t_game		*erase_img(t_game *g);
void		ft_translate_x(t_game *game, int sens);
void		ft_translate_y(t_game *game, int sens);
t_game		*project_iso(t_game *game);
void		ft_move(int key, t_game *game);
t_draw_line	draw_line_init(t_draw_line dl, t_point *p0, t_point *p1, t_game *g);
void		ft_z_plus(int key, t_game *game);
void		rotate_z(t_game *g, int i, double gama);
void		rotate_x(t_game *g, int i, double a);
void		rotate_y(t_game *g, int i, double beta);
void		read_map_suite(t_game *g, t_read_map *rm);
void		ft_split_len(char **line, int *len);
void		color_map_empty(t_game *g);
int			color_attrib(t_game *g, int z);

#endif
