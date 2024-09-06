#include "../include/cub3D.h"

/*	init game:
		initializing all variable in
		game structure
*/
inline t_game	init_game(void)
{
	return ((t_game)
	{
		.map.matrix = NULL,
	});
}