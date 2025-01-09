/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_player_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:00:16 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:00:17 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	set_north_rot(t_game *game)
{
	game->player.camera.dir_x = 0.0;
	game->player.camera.dir_y = -1.0;
	game->player.camera.plane_x = 0.66;
	game->player.camera.plane_y = 0.0;
}

void	set_east_rot(t_game *game)
{
	game->player.camera.dir_x = 1.0;
	game->player.camera.dir_y = 0.0;
	game->player.camera.plane_x = 0.0;
	game->player.camera.plane_y = 0.66;
}

void	set_south_rot(t_game *game)
{
	game->player.camera.dir_x = 0.0;
	game->player.camera.dir_y = 1.0;
	game->player.camera.plane_x = -0.66;
	game->player.camera.plane_y = 0.0;
}

void	set_west_rot(t_game *game)
{
	game->player.camera.dir_x = -1.0;
	game->player.camera.dir_y = 0.0;
	game->player.camera.plane_x = 0.0;
	game->player.camera.plane_y = -0.66;
}
