/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:06:24 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:08:07 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
 * @brief Calculates visible wall height for rendering.
 *
 * Determines wall height on screen based on perpendicular distance,
 * clamped to screen height maximum.
 *
 * @param game Game structure with display height
 * @param perp_wall_dist Perpendicular distance to wall
 * @return Height of wall strip to render on screen
 */
int	calculate_wall_height(t_game *game, double perp_wall_dist)
{
	int	line_height;
	int	max_height;

	max_height = game->display.height;
	line_height = (int)(max_height / perp_wall_dist);
	if (line_height > max_height)
		return (max_height);
	return (line_height);
}

/**
* @brief Checks if position is within map boundaries
*
* @param camera Camera containing position data
* @param game Game containing map dimensions
* @return int -1 if out of bounds, 0 if valid
*/
int	check_map_bounds(t_camera *camera, t_game *game)
{
	if (camera->map_y < 0 || camera->map_y >= game->map.height
		|| camera->map_x < 0 || camera->map_x >= game->map.width)
		return (-1);
	return (0);
}
