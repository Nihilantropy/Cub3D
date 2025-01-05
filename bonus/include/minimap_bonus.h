#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D_bonus.h"

/* Minimap size and position constants */
# define MINIMAP_SCALE 0.2
# define MINIMAP_BORDER_SIZE 2
# define MINIMAP_PADDING 20
# define PLAYER_DOT_SIZE 4
# define FOV_LINE_LENGTH 15
# define FOV_ANGLE 60

typedef struct s_minimap
{
	int		width;
	int		height;
	int		pos_x;
	int		pos_y;
	int		tile_size;
	int		player_x;
	int		player_y;
}	t_minimap;

#endif