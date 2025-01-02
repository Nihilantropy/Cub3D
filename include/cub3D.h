#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include <stdbool.h>
# include <sys/time.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include "keys.h"
# include "messages.h"
# include "error.h"
# include "player.h"
# include "colors.h"
# include "render.h"

# define DISPLAY_NAME "Cub3D"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define TILE_SIZE 64

# define FRAME_TIME_MS 1000 / 60

/* enum for map tiles symbols */
typedef enum e_tiles
{
	FLOOR = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	MAP_FILLER = 'H',
	SPACE = ' ',
	TAB = '\t',
}	e_tiles;

/* keep track of the necessary map infos */
typedef struct s_info
{
	char			identifier;
	bool			found;
	int				index;
	char			*content;
	struct s_info	*next;
}	t_info;

/* checks for map validation */
typedef struct s_check
{
	bool	wrong_char;
	bool	wrong_info_char;
	bool	wrong_info_nbr;
	bool	map_started;
	bool	map_order;
	bool	map_infos_id;
	bool	map_infos_cont;
	bool	**visited;
	bool	map_island;
	bool	found_region;
	bool	map_open;
	int		player;
	bool	map_matrix;
	int		map_start_row;
	t_info	*info;
}	t_check;

typedef struct s_display
{
	int		width;
	int		height;
	bool	open;
}	t_display;

/* map */
typedef struct s_map
{
	t_check		check;
	int			width;
	int			height;
	char		**matrix;
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_display	display;
	t_player	player;
	t_textures	textures;
	bool		running;
	bool		changed;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_game;

/*** main ***/
/* main */
void	game_loop(t_game *game);
/* handle closure */
int		close_game(void *param);

/*** init ***/
/* init game */
void	init_game(t_game *game);
/* init game utils */
void	init_info_list(t_game *game);
/* init textures */
void	init_textures(t_game *game);

/*** check ***/
/* check arg */
bool	check_valid_arg(int argc, char **argv);
/* check map */
bool	check_valid_map(t_game *game, const char **matrix);
/* check map infos */
void	check_map_infos(t_game *game, const char **matrix);
/* check map matrix */
void	check_map_matrix(t_game *game, const char **matrix);
/* check map matrix dfs */
void	check_map_matrix_island(t_game *game, const char **matrix);
/* check map matrix borders */
void	check_map_matrix_borders(t_game *game, const char **matrix);

/*** parser ***/
/* parser get map */
bool	get_map(t_game *game, const char *map);
/* parser matrix */
bool	parse_matrix(t_game *game, const char **matrix);
/* parser get infos */
bool	parse_info(t_game *game, t_info *info, const char *line);
/* parser matrix utils */
bool	is_info_line(const char *line);
bool	is_map_row(const char *line);
char	**build_new_matrix(int height, int width);
/* parser get player */
void	get_player_infos(t_game *game);
bool	is_player_char(char player);
/* parser get player utils */
void	set_north_rot(t_game *game);
void	set_east_rot(t_game *game);
void	set_south_rot(t_game *game);
void	set_west_rot(t_game *game);

/*** display ***/
/* handle display */
bool	handle_display(t_game *game);
/* load textures */
bool	load_textures(t_game *game);
char	*find_texture_path(t_info *info, char identifier);
/* load floor and ceiling */
bool	load_floor_and_ceiling(t_game *game);
/* load floor and ceiling utils */
bool	check_rgb_values(const char **rgb);
int		create_rgb(const char **rgb);

/*** events ***/
void	handle_key_events(t_game *game);

/*** player ***/
/* player movement */
void	set_player_movement(t_game *game, int moving);
void	set_player_rot_angle(t_game *game, int rotating);
/* raycast */


/*** rendering ***/
/* render frame */
int		render_frame(t_game *game);
/* render walls */
void render_walls(t_game *game, t_render_state *state, int x);
/* render walls utils */
void calculate_wall_slice(t_wall_slice *slice, t_game *game, 
	double perp_wall_dist);
void select_wall_texture(t_wall_slice *slice, t_game *game, t_camera *cam);
void calculate_texture_coords(t_wall_slice *slice, t_game *game, t_camera *cam);
/* render floor and ceiling */
void	render_floor_ceiling(t_game *game, t_render_state *state);

/*** utils ***/
/* main utils */
void	free_all_and_exit(t_game *game, int status);
/* matrix utils */
void	print_matrix(const char **matrix);
void	free_matrix(char **matrix);
void	free_bool_matrix(bool **matrix);
char	**dup_matrix(const char **matrix);
size_t	matrix_len(const char **matrix);
/* info utils */
void	print_info_list(t_info *info);
void	free_info_list(t_info **info);
/* textures utils */
void	free_textures(t_game *game);

/*** test ***/
/* test */
bool	test_raycasting(t_game *game);


void cast_ray(t_game *game, t_player *player, int x);
void	init_ray(t_camera *camera, double ray_dir_x, double ray_dir_y, t_pos *pos);
void	calculate_step_dist(t_camera *camera, t_pos *pos);
void	set_y_step_dist(t_camera *camera, t_pos *pos);
int	step_in_x_direction(t_camera *camera);
int	step_in_y_direction(t_camera *camera);
int	check_wall_hit(t_game *game, t_camera *camera);
int	perform_dda(t_game *game, t_camera *camera);
void calculate_wall_dist(t_camera *camera, t_pos *pos, int side);
int	calculate_wall_height(t_game *game, double perp_wall_dist);
void render_floor_ceiling(t_game *game, t_render_state *state);


#endif