/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:01:13 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:01:14 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
