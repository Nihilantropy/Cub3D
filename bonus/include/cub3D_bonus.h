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
# include "keys_bonus.h"
# include "messages_bonus.h"
# include "error_bonus.h"
# include "checks_bonus.h"
# include "player_bonus.h"
# include "colors_bonus.h"
# include "render_bonus.h"
# include "minimap_bonus.h"
# include "door_bonus.h"

# define DISPLAY_NAME "Cub3D"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define TILE_SIZE 64

# define FRAME_TIME_MS 1000 / 60

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
	t_map			map;
	t_display		display;
	t_player		player;
	t_textures		textures;
	t_minimap		minimap;
	t_door_system   door_system;
	bool			running;
	bool			changed;
	void			*mlx_ptr;
	void			*win_ptr;
}	t_game;

/*** main ***/
/* main */
void	game_loop(t_game *game);
/* handle closure */
int		close_game(void *param);

/*** init ***/
/* init game */
t_game	*init_game(void);
/* init game utils */
void	init_info_list(t_game *game);
/* init player */
void 	init_player(t_game *game);
/* init textures */
void	init_textures(t_game *game);
/* init minimap */
void	init_minimap(t_game *game);
/* init door system */
void	init_door_system(t_game *game);

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
/* parser get door */
bool	get_doors(t_game *game);

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
/* load door textures */
bool	load_door_texture(t_game *game);

/*** minimap ***/
/* minimap */
void	get_minimap_dimension(t_game *game);
/* minimap static texture */
bool	init_static_minimap_texture(t_game *game);
/* minimap static texture utils */
void	draw_horizontal_border(t_render_state *state, t_minimap *minimap,
			int y);
void	draw_vertical_border(t_render_state *state, t_minimap *minimap,
			int x);
/*** doors ***/
/* init doors */
void	init_doors(t_game *game);
/* door state */
bool	player_on_door_pos(t_player *player, t_door *door);
/* door interaction */
void	handle_door_interaction(t_game *game);
void	update_map_matrix(t_game *game, int y, int x, bool open);
/* door animation */
void	update_door_animation(t_game *game, t_door *door);

/*** events ***/
/* key events */
void	handle_key_events(t_game *game);

/*** player ***/
/* player movement */
void	set_player_movement(t_game *game, int moving);
void	set_player_rot_angle(t_game *game, int rotating);
/* player movement utils */
void	move_step_forward(t_player *player, double *step_x, double *step_y);
void	move_step_backward(t_player *player, double *step_x, double *step_y);
void	move_step_left(t_player *player, double *step_x, double *step_y);
void	move_step_right(t_player *player, double *step_x, double *step_y);
void	move_step_still(double *step_x, double *step_y);
/* player collision */
bool try_slide_movement(t_game *game, t_pos *new_pos, 
							double step_x, double step_y);
/* player collision utils */
bool	is_valid_pos(const char **matrix, double new_y, double new_x);

/*** raycast ***/
/* raycast */
void	cast_ray(t_game *game, t_player *player, int x);
void	init_ray(t_camera *camera, double ray_dir_x, 
		double ray_dir_y, t_pos *pos);
/* ray step */
void	calculate_step_dist(t_camera *camera, t_pos *pos);
int		step_in_x_direction(t_camera *camera);
int		step_in_y_direction(t_camera *camera);
double	calculate_perp_dist(t_camera *camera, t_pos *pos, int side);
/* ray dda */
int		perform_dda(t_game *game, t_camera *camera);
/* ray render */
int		calculate_wall_height(t_game *game, double perp_wall_dist);

/*** rendering ***/
/* render frame */
int		render_frame(t_game *game);
/* render manager */
void	*get_texture(t_game *game, t_camera *cam, int side);
void	get_texture_color(t_render_state *state, t_render_state *tex_data,
						t_wall_slice *slice, int position);
/* render 3d map */
void	render_3d_map(t_game *game, t_render_state *state, int x);
/* render walls */
void	render_textured_wall_slice(t_render_state *state, t_wall_slice *slice,
									t_game *game, int x);
bool	init_texture_rendering(t_wall_slice *slice, t_render_state *tex_data, 
								double *step);
bool	get_texture_data(t_wall_slice *slice, t_render_state *tex_data);
/* render walls utils */
void 	calculate_wall_slice(t_wall_slice *slice, t_game *game, 
	double perp_wall_dist);
void 	calculate_texture_coords(t_wall_slice *slice, t_game *game, t_camera *cam);
/* render door animation */
void	render_transparent_slice(t_render_state *state, t_wall_slice *slice,
								t_game *game, int x);
/* render floor and ceiling */
void	render_floor_ceiling(t_game *game, t_render_state *state);
/* render minimap */
void	render_minimap(t_game *game);
/* render minimap utils */
void	draw_minimap_player(t_game *game, t_minimap *minimap);
void	draw_player_fov(t_game *game, t_minimap *minimap);
void	draw_minimap_door(t_game *game, t_minimap *minimap);
/* render door */
void	*select_door_texture(t_game *game, t_door *door);
bool	is_door_collision(t_game *game, double x, double y);
t_door	*find_door_at_position(t_game *game, int x, int y);

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
/* door utils */
void	free_door_system(t_game *game);
/* minimap utils */
void	destroy_minimap_texture(t_game *game);


#endif