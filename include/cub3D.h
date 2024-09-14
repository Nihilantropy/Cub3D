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
# include "messages.h"
# include "error.h"

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
	TAB = '\t'
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
	bool	map_island;
	bool	map_closed;
	bool	player;
	bool	map_matrix;
	int		map_start_row;
	t_info	*info;
}	t_check;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player
{
	char	face;
	t_pos	pos;
}	t_player;

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
	t_player	player;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_game;

/*** main ***/
/* init game */
void	init_game(t_game *game);
/* init game utils */
void	init_info_list(t_game *game);

/*** check ***/
/* check arg */
bool	check_valid_arg(int argc, char **argv);
/* check map */
bool	check_valid_map(t_game *game, const char **matrix);
/* check map infos */
void	check_map_infos(t_game *game, const char **matrix);
/* check map matrix */
void	check_map_matrix(t_game *game, const char **matrix);

/*** parser ***/
/* parser get map */
bool	get_map(t_game *game, const char *map);
/* parser matrix */
bool	parse_matrix(t_game *game, const char **matrix);
/* parser matrix utils */
bool	is_info_line(const char *line);
bool	is_map_row(const char *line);
char	**build_new_matrix(int height, int width);

/*** utils ***/
/* main */
void	free_all(t_game *game);
/* matrix */
void	print_matrix(const char **matrix);
void	free_matrix(char **matrix);
char	**dup_matrix(const char **matrix);
/* info */
void	print_info_list(t_info *info);
void	free_info_list(t_info **info);

#endif