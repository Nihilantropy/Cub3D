#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
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
int	valid_check(int argc, char **argv);

/*** main ***/
inline t_game	init_game(void);
void			get_map(t_game game, char *map);


#endif