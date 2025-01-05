#ifndef CHECKS_BONUS_H
# define CHECKS_BONUS_H

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

#endif