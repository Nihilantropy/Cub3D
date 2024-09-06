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

typedef struct s_map
{
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
bool	check_valid_arg(int argc, char **argv);
bool	check_valid_map(const char **matrix);

/*** main ***/
t_game	init_game(void);

/*** utils ***/
void	print_matrix(char **matrix);
void	free_matrix(char **matrix);

/*** parser ***/
bool	get_map(t_game *game, const char *map);

/*** main utils ***/
int		get_map_info_len(char **matrix);


#endif