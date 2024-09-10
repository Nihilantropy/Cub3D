#include "../include/cub3D.h"

static void	init_map(t_game *game);
static void	init_map_checks(t_game *game);
static void	init_player(t_game *game);

/*	init game:
**	initializing all variable in
**	game structure
*/
void	init_game(t_game *game)
{
	init_map(game);
	init_player(game);
}

static void	init_map(t_game *game)
{
	game->map.matrix = NULL;
	game->map.info = NULL;
	game->map.width = 0;
	game->map.height = 0;
	init_map_checks(game);
}

static void	init_player(t_game *game)
{
	game->player.face = 0;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
}

static void	init_map_checks(t_game *game)
{
	game->map.check.map_started = false;
	game->map.check.map_order = false;
	game->map.check.map_infos = false;
	game->map.check.matrix_top = false;
	game->map.check.matrix_bot = false;
	game->map.check.matrix_side = false;
	game->map.check.player = false;
	game->map.check.map_island = false;
	game->map.check.map_matrix = false;
	game->map.check.info = NULL;
	init_info_list(game);
}

