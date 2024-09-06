NAME		= cub3D

CUB3D_DIR	= ./srcs
CUB3D_HEAD	= ./include

MAIN_DIR	= ./main
CHECK_DIR	= ./check

SRCS		=	$(MAIN_DIR)/main.c \
				$(CHECK_DIR)/check_arg.c \


						
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
INC 		= -I$(CUB3D_HEAD) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR)

# Compilation rule for the program
$(NAME): $(LIBFT) $(PRINTF_LIB) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux $(LINK) -o $(NAME)


# Rule to compile object files
$(CUB3D_DIR)/%.o: $(CUB3D_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Rule to make libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to make libmlx_Linux
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

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