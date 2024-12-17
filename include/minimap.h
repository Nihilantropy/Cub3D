#ifndef MINIMAP_H
# define MINIMAP_H

# define MINI_CELL_SIZE 64
# define MINI_PLAYER_SIZE 16

# include <stdbool.h>

typedef struct s_images
{
	void	*player;
	void	*wall;
	void	*floor;
	void	*unknown;
}	t_images;

typedef struct s_minimap
{
	t_images	images;
	bool		changed;
}	t_minimap;

#endif