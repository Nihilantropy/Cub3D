/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:53:32 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:54:49 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_map(t_game *game);
static void	init_display(t_game *game);
static void	init_map_checks(t_game *game);
static void	init_player(t_game *game);

/**
 * @brief Initializes all game components to their default values:
 * map, display settings, player state and textures. changed secure
 * first frame render without key event
 *
 * @param game Pointer to the game structure to be initialized
 */
void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->running = false;
	game->changed = true;
	init_map(game);
	init_display(game);
	init_player(game);
	init_textures(game);
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

static void	init_player(t_game *game)
{
	game->player.face = 0;
	game->player.pos.x = 0.0;
	game->player.pos.y = 0.0;
	game->player.pos.x_screen = 0;
	game->player.pos.y_screen = 0;
	game->player.speed = 0.0;
	game->player.rot_speed = 0.0;
	game->player.moving = m_still;
	game->player.rotating = r_still;
	game->player.camera.dir_x = 0.0;
	game->player.camera.dir_y = 0.0;
	game->player.camera.plane_x = 0.0;
	game->player.camera.plane_y = 0.0;
	game->player.camera.ray_dir_x = 0.0;
	game->player.camera.ray_dir_y = 0.0;
	game->player.camera.delta_dist_x = 0.0;
	game->player.camera.delta_dist_y = 0.0;
	game->player.camera.side_dist_x = 0.0;
	game->player.camera.side_dist_y = 0.0;
	game->player.camera.map_x = 0;
	game->player.camera.map_y = 0;
	game->player.camera.step_x = 0;
	game->player.camera.step_y = 0;
	game->player.camera.perp_wall_dist = 0.0;
	game->player.camera.side = 0;
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
