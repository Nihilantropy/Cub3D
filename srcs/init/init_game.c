#include "../include/cub3D.h"

void		init_minimap(t_game *game);
void		init_info_list(t_game *game);
static void	init_map(t_game *game);
static void	init_display(t_game *game);
static void	init_map_checks(t_game *game);
static void	init_player(t_game *game);

/** 
 *  @brief init game:
 *	initializing all variable in
 *	game structure
 */
void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->running = false;
	init_map(game);
	init_minimap(game);
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
	game->player.pos.x = 0.0;
	game->player.pos.y = 0.0;
	game->player.pos.x_screen = 0;
	game->player.pos.y_screen = 0;
	game->player.speed = 0.0;
	game->player.rot_speed = 0.0;
	game->player.moving.forward = false;
	game->player.moving.backward = false;
	game->player.rot.current_angle = -1;
	game->player.rot.left = false;
	game->player.rot.right = false;
	game->player.camera.fov = 0;
	game->player.camera.ray_dir_x = 0.0;
	game->player.camera.ray_dir_y = 0.0;
	game->player.camera.map_x = 0;
	game->player.camera.map_y = 0;
	game->player.camera.step_x = 0;
	game->player.camera.step_y = 0;
	game->player.camera.side_dist_x = 0.0;
	game->player.camera.side_dist_y = 0.0;
	game->player.camera.delta_dist_x = 0.0;
	game->player.camera.delta_dist_y = 0.0;
	game->player.camera.wall_hit_x = 0;
	game->player.camera.wall_hit_y = 0;
	game->player.camera.perp_wall_dist = 0.0;
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

