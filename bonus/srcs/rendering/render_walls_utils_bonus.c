/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:47 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 14:01:07 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
 * @brief Calculates dimensions for a wall slice on screen.
 *
 * Determines height and vertical boundaries of the wall slice based on distance.
 *
 * @param slice Wall slice to calculate dimensions for.
 * @param game Game state containing display parameters.
 * @param perp_wall_dist Perpendicular distance to the wall.
 */
void	calculate_slice(t_slice *slice, t_game *game,
	double perp_wall_dist)
{
	slice->height = (int)(game->display.height / perp_wall_dist);
	slice->start_y = -slice->height / 2 + game->display.height / 2;
	slice->end_y = slice->height / 2 + game->display.height / 2;
	if (slice->start_y < 0)
		slice->start_y = 0;
	if (slice->end_y >= game->display.height)
		slice->end_y = game->display.height - 1;
}

/**
 * @brief Calculates texture coordinates for wall rendering.
 *
 * Computes wall hit point and determines texture
 * x-coordinate based on ray direction.
 *
 * @param slice Wall slice to calculate texture coordinates for.
 * @param game Game state containing player position.
 * @param cam Camera data with ray and wall distance info.
 */
void	calculate_texture_coords(t_slice *slice, t_game *game, t_camera *cam)
{
	if (slice->side == 0)
		slice->wall_x = game->player.pos.y + cam->perp_dist * cam->ray_dir_y;
	else
		slice->wall_x = game->player.pos.x + cam->perp_dist * cam->ray_dir_x;
	slice->wall_x -= floor(slice->wall_x);
	slice->tex_x = (int)(slice->wall_x * TEXTURE_SIZE);
	if (slice->side == 0 && cam->ray_dir_x > 0)
		slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
	if (slice->side == 1 && cam->ray_dir_y < 0)
		slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
}
