#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> // a virer avant de push
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 15
# endif

typedef struct s_list_GNL
{
	char			*content;
	struct s_list_GNL	*next;
}				t_GNL;


char *get_next_line(int fd);

int	chearch_endline(t_GNL *stack);

void	read_stack(int fd, t_GNL **stack);

void	go_to_stack(t_GNL **stack, char *buffer, int r_read);

t_GNL	*lst_getlast(t_GNL *stack);

int	ft_sstrlen(const char *s);

void	extract_line(t_GNL *stack, char **line);

void	generate_line(t_GNL *stack, char **line);

void	free_stack(t_GNL *stack);

void	clean_stack(t_GNL **stack);

#endif
