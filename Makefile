### MANDATORY PART ###

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
RAYCAST_DIR	= ./raycast
UTILS_DIR	= ./utils
RENDER_DIR	= ./rendering

SRCS		=	$(MAIN_DIR)/main.c \
				$(MAIN_DIR)/handle_closure.c \
				$(INIT_DIR)/init_game.c \
				$(INIT_DIR)/init_game_utils.c \
				$(INIT_DIR)/init_textures.c \
				$(UTILS_DIR)/main_utils.c \
				$(UTILS_DIR)/matrix_utils.c \
				$(UTILS_DIR)/info_utils.c \
				$(UTILS_DIR)/textures_utils.c \
				$(CHECK_DIR)/check_arg.c \
				$(CHECK_DIR)/check_map.c \
				$(CHECK_DIR)/check_map_info.c \
				$(CHECK_DIR)/check_map_matrix.c \
				$(CHECK_DIR)/check_map_matrix_dfs.c \
				$(CHECK_DIR)/check_map_matrix_borders.c \
				$(PARSER_DIR)/parser_get_map.c \
				$(PARSER_DIR)/parser_matrix.c \
				$(PARSER_DIR)/parser_get_infos.c \
				$(PARSER_DIR)/parser_matrix_utils.c \
				$(PARSER_DIR)/parser_get_player.c \
				$(PARSER_DIR)/parser_get_player_utils.c \
				$(DISPLAY_DIR)/handle_display.c \
				$(DISPLAY_DIR)/load_textures.c \
				$(DISPLAY_DIR)/load_floor_and_ceiling.c \
				$(DISPLAY_DIR)/load_floor_and_ceiling_utils.c \
				$(EVENTS_DIR)/key_events.c \
				$(PLAYER_DIR)/player_movement.c \
				$(PLAYER_DIR)/player_collision_utils.c \
				$(RAYCAST_DIR)/raycast.c \
				$(RAYCAST_DIR)/ray_step.c \
				$(RAYCAST_DIR)/ray_dda.c \
				$(RAYCAST_DIR)/ray_render.c \
				$(RENDER_DIR)/render_walls.c \
				$(RENDER_DIR)/render_walls_utils.c \
				$(RENDER_DIR)/render_frame.c \
				$(RENDER_DIR)/render_floor_ceiling.c
						
OBJS		= $(patsubst %.c, $(CUB3D_DIR)/%.o, $(SRCS))

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


$(CUB3D_DIR)/%.o:	$(CUB3D_DIR)/%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME) $(NAME_BONUS)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(MAKE) -C $(MLX_DIR) clean

re:			fclean all

rec:		clean all

fc:			fclean

### BONUS PART ###

NAME_BONUS			= cub3D_bonus

BONUS_DIR			= bonus

CUB3D_BONUS_DIR		= $(BONUS_DIR)/srcs
CUB3D_BONUS_HEAD	= $(BONUS_DIR)/include

# Bonus subdirectories
MAIN_BONUS_DIR    	= ./main
INIT_BONUS_DIR    	= ./init
CHECK_BONUS_DIR   	= ./check
PARSER_BONUS_DIR  	= ./parser
DISPLAY_BONUS_DIR 	= ./display
EVENTS_BONUS_DIR  	= ./events
PLAYER_BONUS_DIR  	= ./player
RAYCAST_BONUS_DIR 	= ./raycast
UTILS_BONUS_DIR   	= ./utils
RENDER_BONUS_DIR  	= ./rendering
MINIMAP_BONUS_DIR	= ./minimap
DOOR_BONUS_DIR		= ./door

SRCS_BONUS	=	$(MAIN_BONUS_DIR)/main_bonus.c \
				$(MAIN_BONUS_DIR)/handle_closure_bonus.c \
				$(INIT_BONUS_DIR)/init_game_bonus.c \
				$(INIT_BONUS_DIR)/init_game_utils_bonus.c \
				$(INIT_BONUS_DIR)/init_player_bonus.c \
				$(INIT_BONUS_DIR)/init_textures_bonus.c \
				$(INIT_BONUS_DIR)/init_minimap_bonus.c \
				$(INIT_BONUS_DIR)/init_door_system_bonus.c \
				$(UTILS_BONUS_DIR)/main_utils_bonus.c \
				$(UTILS_BONUS_DIR)/matrix_utils_bonus.c \
				$(UTILS_BONUS_DIR)/info_utils_bonus.c \
				$(UTILS_BONUS_DIR)/textures_utils_bonus.c \
				$(UTILS_BONUS_DIR)/door_utils_bonus.c \
				$(CHECK_BONUS_DIR)/check_arg_bonus.c \
				$(CHECK_BONUS_DIR)/check_map_bonus.c \
				$(CHECK_BONUS_DIR)/check_map_info_bonus.c \
				$(CHECK_BONUS_DIR)/check_map_matrix_bonus.c \
				$(CHECK_BONUS_DIR)/check_map_matrix_dfs_bonus.c \
				$(CHECK_BONUS_DIR)/check_map_matrix_borders_bonus.c \
				$(PARSER_BONUS_DIR)/parser_get_map_bonus.c \
				$(PARSER_BONUS_DIR)/parser_matrix_bonus.c \
				$(PARSER_BONUS_DIR)/parser_get_infos_bonus.c \
				$(PARSER_BONUS_DIR)/parser_matrix_utils_bonus.c \
				$(PARSER_BONUS_DIR)/parser_get_player_bonus.c \
				$(PARSER_BONUS_DIR)/parser_get_player_utils_bonus.c \
				$(PARSER_BONUS_DIR)/parser_get_door_bonus.c \
				$(DISPLAY_BONUS_DIR)/handle_display_bonus.c \
				$(DISPLAY_BONUS_DIR)/load_textures_bonus.c \
				$(DISPLAY_BONUS_DIR)/load_floor_and_ceiling_bonus.c \
				$(DISPLAY_BONUS_DIR)/load_floor_and_ceiling_utils_bonus.c \
				$(DISPLAY_BONUS_DIR)/load_door_textures_bonus.c \
				$(MINIMAP_BONUS_DIR)/minimap_bonus.c \
				$(DOOR_BONUS_DIR)/init_door_bonus.c \
				$(DOOR_BONUS_DIR)/door_state_bonus.c \
				$(DOOR_BONUS_DIR)/door_interaction_bonus.c \
				$(DOOR_BONUS_DIR)/door_animation_bonus.c \
				$(EVENTS_BONUS_DIR)/key_events_bonus.c \
				$(PLAYER_BONUS_DIR)/player_movement_bonus.c \
				$(PLAYER_BONUS_DIR)/player_collision_bonus.c \
				$(PLAYER_BONUS_DIR)/player_collision_utils_bonus.c \
				$(RAYCAST_BONUS_DIR)/raycast_bonus.c \
				$(RAYCAST_BONUS_DIR)/ray_step_bonus.c \
				$(RAYCAST_BONUS_DIR)/ray_dda_bonus.c \
				$(RAYCAST_BONUS_DIR)/ray_render_bonus.c \
				$(RENDER_BONUS_DIR)/render_walls_bonus.c \
				$(RENDER_BONUS_DIR)/render_walls_utils_bonus.c \
				$(RENDER_BONUS_DIR)/render_frame_bonus.c \
				$(RENDER_BONUS_DIR)/render_floor_ceiling_bonus.c \
				$(RENDER_BONUS_DIR)/render_minimap_bonus.c \
				$(RENDER_BONUS_DIR)/render_minimap_utils_bonus.c \
				$(RENDER_BONUS_DIR)/render_door_bonus.c \
				$(RENDER_BONUS_DIR)/render_manager_bonus.c \
				$(RENDER_BONUS_DIR)/render_3d_map_bonus.c \

OBJS_BONUS	= $(patsubst %.c, $(CUB3D_BONUS_DIR)/%.o, $(SRCS_BONUS))

# Include directory for header files
INC_BONUS 	= -I$(CUB3D_BONUS_HEAD) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Compilation rule for the program
$(NAME_BONUS):	$(OBJS_BONUS)
				$(MAKE) -C $(LIBFT_DIR)
				$(MAKE) -C $(MLX_DIR)
				$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux $(LINK) -o $(NAME_BONUS)

$(CUB3D_BONUS_DIR)/%.o:	$(CUB3D_BONUS_DIR)/%.c
						$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

bonus:		$(NAME_BONUS)

rebonus:	fc bonus

.PHONY:		all clean fclean re rec fc bonus rebonus