#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"
# include "messages.h"
# include "error.h"

typedef struct s_map
{
	char	**matrix;
}	t_map;

typedef struct s_game
{
	t_map	map;
	void*	mlx_ptr;
	void*	win_ptr;
}	t_game;

/*** check ***/
int	valid_check(int argc, char **argv);

/*** main ***/


#endif