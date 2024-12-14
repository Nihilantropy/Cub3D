NAME		= cub3D

CUB3D_DIR	= ./srcs
CUB3D_HEAD	= ./include

MAIN_DIR	= ./main
INIT_DIR	= ./init
CHECK_DIR	= ./check
PARSER_DIR	= ./parser
DISPLAY_DIR = ./display
EVENTS_DIR	= ./events
PLAYER_DIR	= ./player
UTILS_DIR	= ./utils

SRCS		=	$(MAIN_DIR)/main.c \
				$(MAIN_DIR)/handle_closure.c \
				$(INIT_DIR)/init_game.c \
				$(INIT_DIR)/init_game_utils.c \
				$(UTILS_DIR)/main.c \
				$(UTILS_DIR)/matrix.c \
				$(UTILS_DIR)/info.c \
				$(CHECK_DIR)/check_arg.c \
				$(CHECK_DIR)/check_map.c \
				$(CHECK_DIR)/check_map_info.c \
				$(CHECK_DIR)/check_map_matrix.c \
				$(CHECK_DIR)/check_map_matrix_dfs.c \
				$(CHECK_DIR)/check_map_matrix_borders.c \
				$(PARSER_DIR)/parser_get_map.c \
				$(PARSER_DIR)/parser_matrix.c \
				$(PARSER_DIR)/parser_matrix_utils.c \
				$(PARSER_DIR)/parser_get_player.c \
				$(DISPLAY_DIR)/handle_display.c \
				$(EVENTS_DIR)/key_events.c \
				$(PLAYER_DIR)/player_movement.c


						
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

fc:			fclean

.PHONY:		all clean fclean re rec fc