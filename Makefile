### EXECUTABLE ###
NAME		=	fdf
### FOLDERS ###
LIBFT		=	INCLUDES/libft/libft.a
LIB			= ./INCLUDES/libft

LIBFTPRINTF	= INCLUDES/printf/libftprintf.a
LIBPRF		= ./INCLUDES/printf

GNL			=	INCLUDES/get_next_line/get_next_line.c\
				INCLUDES/get_next_line/get_next_line_utils.c

MLXFLAG	=		-LINCLUDES/mlx -lmlx -Imlx -lXext -lX11 -lm -lz
### SOURCES ###
SRCS	=	main.c\
			inputs.c\
			parsing.c \
			exit_free.c \
			projection.c \
			draw.c \
			utils1.c \
			iso.c \
			color.c



OBJS	=	$(SRCS:.c=.o) $(GNL:.c=.o)
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
###-fsanitize=address
INC	=	-I $(LIB) -I $(LIBPRF) -I INCLUDES/mlx
RM = rm -f


all:	$(LIBFT) $(LIBFTPRINTF) $(NAME)
	@echo $(NOC)Le projet fdf de a ete compile avec succes${NOC}

$(LIBFT):
		@echo $(GREEN)Construction de la libft$(NOC)
		@make -C $(LIB) bonus > /dev/null

$(LIBFTPRINTF):
		@echo $(GREEN)Construction de la libftprintf$(NOC)
		@make -C $(LIBPRF) > /dev/null

.c.o:
		@$(CC) $(CFLAGS) $(INC) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			@echo $(GREEN)Construction de FDF$(NOC)
			@$(CC) -o $(NAME) $(OBJS) -L ${LIB} -lft -L ${LIBPRF} -lftprintf $(MLXFLAG)

clean:
		@echo $(RED)Destruction des .o$(NOC)
		@$(RM) $(OBJS)
		@make -C $(LIB) clean > /dev/null
		@make -C $(LIBPRF) clean > /dev/null

fclean: clean
		@echo $(RED)Destruction des .a$(NOC)
		@$(RM) $(NAME)
		@make -C $(LIB) fclean > /dev/null
		@make -C $(LIBPRF) fclean > /dev/null

re:		fclean all

### COLORS ###

NOC			= "\033[0m"
BOLD		= "\033[1m"
UNDERLINE	= "\033[4m"
BLACK		= "\033[1;30m"
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
YELLOW		= "\033[1;33m"
BLUE		= "\033[1;34m"
VIOLET		= "\033[1;35m"
CYAN		= "\033[1;36m"
WHITE		= "\033[1;37m"
