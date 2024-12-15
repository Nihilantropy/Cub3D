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
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include "keys.h"
# include "messages.h"
# include "error.h"
# include "player.h"
# include "minimap.h"

# define DISPLAY_NAME "Cub3D"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define FRAME_TIME_MS 16

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
	struct s_info	*next;
}	t_info;

/* checks for map validation */
typedef struct s_check
{
	bool	wrong_char;
	bool	map_started;
	bool	map_order;
	bool	map_infos;
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
	const char	**matrix;
	const char	**info;
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_minimap	minimap;
	t_display	display;
	t_player	player;
	bool		running;
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
/* parser matrix utils */
bool	is_info_line(const char *line);
bool	is_map_row(const char *line);
char	**build_new_matrix(int height, int width);
/* parser get player */
void	get_player_infos(t_game *game);
bool	is_player_char(char player);

/*** display */
void	handle_display(t_game *game);

/*** events ***/
void	handle_key_events(t_game *game);

/*** player ***/
/* player movement */
void	set_player_movement(t_game *game, int moving);
void	set_player_rot_angle(t_game *game, int rotating);

/*** rendering ***/
/* drwa map 2d */
void	draw_map_2d(t_game *game);
/* draw player 2d */
void	draw_player_2d(t_game *game);
/* render frame */
int		render_frame(t_game *game);

/*** utils ***/
/* main */
void	free_all(t_game *game);
/* matrix */
void	print_matrix(const char **matrix);
void	free_matrix(char **matrix);
void	free_bool_matrix(bool **matrix);
char	**dup_matrix(const char **matrix);
/* info */
void	print_info_list(t_info *info);
void	free_info_list(t_info **info);
/* minimap */
void	free_minimap_images(t_game *game);

#endif