NAME		= cub3D

CUB3D_DIR	= ./srcs
CUB3D_HEAD	= ./include

MAIN_DIR	= ./main
CHECK_DIR	= ./check
PARSER_DIR	= ./parser
UTILS_DIR	= ./utils

SRCS		=	$(MAIN_DIR)/main.c \
				$(MAIN_DIR)/init_game.c \
				$(MAIN_DIR)/init_game_utils.c \
				$(UTILS_DIR)/print.c \
				$(UTILS_DIR)/free.c \
				$(CHECK_DIR)/check_arg.c \
				$(CHECK_DIR)/check_map.c \
				$(CHECK_DIR)/check_info.c \
				$(PARSER_DIR)/parser_get_map.c \
				$(PARSER_DIR)/parser_get_map_utils.c \


						
OBJS		= $(patsubst %.c, $(CUB3D_DIR)/%.o, $(SRCS))

SECRET_OBJS	= $(patsubst %.c, $(SECRET_DIR)/%.o, $(SECRET_SRCS))

LIBFT_DIR	= ./libft
LIBFT		= libft.a

MLX_DIR		= ./minilibx-linux
MLX_LIB		= libmlx_Linux.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM 			= rm -f
LINK 		= -lX11 -lXext -lm

# Include directory for header files
INC 		= -I$(CUB3D_HEAD) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Compilation rule for the program
$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(MAKE) -C $(MLX_DIR)
			$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux $(LINK) -o $(NAME)


# Rule to compile object files
%.o:		%.c
			$(CC) $(CFLAGS) $(INC) -c $< -o $@

all:		$(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(MAKE) -C $(MLX_DIR) clean

re:			fclean all

rec:		clean all

.PHONY:		all clean fclean re rec