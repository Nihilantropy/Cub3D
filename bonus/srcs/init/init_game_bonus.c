#include "../../include/cub3D_bonus.h"

static void	init_device(t_game *game);
static void	init_map(t_game *game);
static void	init_display(t_game *game);
static void	init_map_checks(t_game *game);

/**
 * @brief Initializes all game components to their default values:
 * map, display settings, player state and textures. changed secure
 * first frame render without key event
 *
 * @param game Pointer to the game structure to be initialized
 */
t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_exit_error(ERR_ALLOC_GAME);
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->running = false;
	game->changed = true;
	init_device(game);
    init_map(game);
	init_display(game);
	init_player(game);
	init_textures(game);
	init_minimap(game);
	init_door_system(game);
	return (game);
}

static void	init_map(t_game *game)
{
	game->map.matrix = NULL;
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

static void	init_map_checks(t_game *game)
{
	game->map.check.wrong_char = false;
	game->map.check.wrong_info_char = false;
	game->map.check.wrong_info_nbr = false;
	game->map.check.map_started = false;
	game->map.check.map_order = false;
	game->map.check.map_infos_id = false;
	game->map.check.map_infos_cont = false;
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

static void	init_device(t_game *game)
{
	game->keys.w_pressed = false;
	game->keys.s_pressed = false;
	game->keys.a_pressed = false;
	game->keys.d_pressed = false;
	game->keys.left_pressed = false;
	game->keys.right_pressed = false;
	game->keys.space_pressed = false;
	game->mouse.x = false;
	game->mouse.y = false;
	game->mouse.show = true;
	game->mouse.right = false;
	game->mouse.left = false;
}
