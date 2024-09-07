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
	bool	map_started;
	bool	map_order;
	bool	map_infos;
	bool	map_matrix;
	t_info	*info;
}	t_check;

/* map */
typedef struct s_map
{
	t_check	check;
	char	**matrix;
	char	**info;
}	t_map;

typedef struct s_game
{
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

/*** check ***/
/* check arg */
bool	check_valid_arg(int argc, char **argv);
/* check map */
bool	check_valid_map(t_game *game, const char **matrix);
bool	is_info_line(const char *line);
/* check map infos */
void	check_map_infos(t_game *game, const char **matrix);
/* check map matrix */
void	check_map_matrix(t_game *game, const char **matrix);

/*** main ***/
/* init game */
void	init_game(t_game *game);
/* init game utils */
void	init_info_list(t_game *game);

/*** utils ***/
/* print */
void	print_matrix(char **matrix);
void	print_info_list(t_info *info);
/* free */
void	free_matrix(char **matrix);
void	free_info_list(t_info **info);

/*** parser ***/
/* parser get map */
bool	get_map(t_game *game, const char *map);

/*** main utils ***/
int		get_map_info_len(char **matrix);


#endif