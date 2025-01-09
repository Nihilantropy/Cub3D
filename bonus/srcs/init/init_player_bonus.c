/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:55:17 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:55:37 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	init_camera(t_game *game);

void	init_player(t_game *game)
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
	init_camera(game);
}

static void	init_camera(t_game *game)
{
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
	game->player.camera.perp_dist = 0.0;
	game->player.camera.hit_obj = -1;
	game->player.camera.side = 0;
}
