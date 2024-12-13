#include "../include/cub3D.h"

static void	init_map(t_game *game);
static void	init_display(t_game *game);
static void	init_map_checks(t_game *game);
static void	init_player(t_game *game);

/*	init game:
**	initializing all variable in
**	game structure
*/
void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	init_map(game);
	init_display(game);
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

static void	init_display(t_game *game)
{
	game->display.width = WIN_WIDTH;
	game->display.height = WIN_HEIGHT;
	game->display.open = false;
}

static void	init_player(t_game *game)
{
	game->player.face = 0;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.rot.current_angle = 0;
	game->player.rot.next_rotation = false;
}

static void	init_map_checks(t_game *game)
{
	game->map.check.wrong_char = false;
	game->map.check.map_started = false;
	game->map.check.map_order = false;
	game->map.check.map_infos = false;
	game->map.check.player = 0;
	game->map.check.visited = NULL;
	game->map.check.map_island = false;
	game->map.check.found_region = false;
	game->map.check.map_open = false;
	game->map.check.map_matrix = false;
	game->map.check.map_start_row = 0;
	game->map.check.info = NULL;
	init_info_list(game);
}

