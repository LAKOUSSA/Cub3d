NAME		=	Cub3D

LIB			=	libft/libft.a

CC			=	@gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3

SRC_LIB		=	libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c \
				libft/ft_isprint.c libft/ft_strlen.c libft/ft_memset.c \
				libft/ft_memcpy.c libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c \
				libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c libft/ft_strrchr.c \
				libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strnstr.c \
				libft/ft_atoi.c libft/ft_strdup.c libft/ft_substr.c \
				libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
				libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
				libft/ft_putendl_fd.c libft/ft_putnbr_fd.c
SRC_GNL		=	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC_PARS	=	src/parsing/read_the_file.c src/parsing/parsing_utils.c src/parsing/check_map_tools.c \
				src/parsing/check_map.c src/parsing/ft_init.c src/parsing/check_textures.c src/parsing/check_colors.c
SRC_RAYC	=	src/raycasting/textures.c src/raycasting/raycasting.c src/raycasting/dda.c src/raycasting/hook.c src/raycasting/events.c src/raycasting/start.c
SRC			=	$(SRC_GNL) $(SRC_PARS) $(SRC_RAYC) src/cub3d.c

SRC_PARS_B	=	src_bonus/parsing/read_the_file.c src_bonus/parsing/parsing_utils.c src_bonus/parsing/check_map_tools.c \
				src_bonus/parsing/check_map.c src_bonus/parsing/ft_init.c src_bonus/parsing/check_textures.c src_bonus/parsing/check_colors.c
SRC_RAYC_B	=	src_bonus/raycasting/textures.c src_bonus/raycasting/raycasting.c src_bonus/raycasting/dda.c src_bonus/raycasting/hook.c src_bonus/raycasting/events.c src_bonus/raycasting/render.c src_bonus/raycasting/start.c
SRC_BONUS	=	$(SRC_GNL) $(SRC_PARS_B) $(SRC_RAYC_B) src_bonus/cub3d.c

OBJ_LIB		=	$(SRC_LIB:.c=.o)
OBJ			=	$(SRC:.c=.o)
OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(LIB)
	@printf "\e[38;5;236m \n ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎ COMPILING ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎\n\e[0m\n"
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIB) $(PRINT) -o $(NAME)
	@printf "\e[38;5;216m→	successfully build	✔︎\e[0m\n"

$(LIB)	:	$(SRC_LIB)
	@make -s -C libft
	@make -s -C libft bonus
	@make -s -C libft clean

bonus	:	$(OBJ_BONUS) $(LIB)
	@printf "\e[38;5;236m \n ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎BONUS COMPILING ⚡︎⚡︎⚡︎⚡︎⚡︎⚡︎\n\e[0m\n"
	$(CC) $(CFLAGS) $(OBJ_BONUS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(LIB) $(PRINT) -o $(NAME)
	@printf "\e[38;5;216m→	successfully bonus build	✔︎\e[0m\n"

clean	:
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)
	@make -s -C libft clean
	@printf "\e[38;5;206m→	Objects files deleted 🗑\e[0m\n"

fclean	: clean
	@rm -f $(NAME)
	@make -s -C libft fclean
	@printf "\e[38;5;206m→	All files was deleted 🗑\e[0m\n"

re		: fclean all
