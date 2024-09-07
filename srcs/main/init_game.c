#include "../include/cub3D.h"

static void	init_game_map(t_game *game);

/*	init game:
**	initializing all variable in
**	game structure
*/
void	init_game(t_game *game)
{
	init_game_map(game);
}

static void	init_game_map(t_game *game)
{
	game->map.check.map_started = false;
	game->map.check.map_order = false;
	game->map.check.map_infos = false;
	game->map.check.map_matrix = false;
	game->map.check.info = NULL;
	init_info_list(game);
}

