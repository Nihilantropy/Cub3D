/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:01:16 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:01:58 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * @brief Calculates initial step and side distances for DDA algorithm.
 *
 * Determines step direction (+1/-1) and initial side distances based on
 * ray direction. Uses floor/ceil to handle grid cell boundaries.
 *
 * @param camera Camera structure storing ray and step data
 * @param pos Current position in world coordinates
 */
void	calculate_step_dist(t_camera *camera, t_pos *pos)
{
	if (camera->ray_dir_x < 0)
	{
		camera->step_x = -1;
		camera->side_dist_x = (pos->x - floor(pos->x)) * camera->delta_dist_x;
	}
	else
	{
		camera->step_x = 1;
		camera->side_dist_x = (ceil(pos->x) - pos->x) * camera->delta_dist_x;
	}
	if (camera->ray_dir_y < 0)
	{
		camera->step_y = -1;
		camera->side_dist_y = (pos->y - floor(pos->y)) * camera->delta_dist_y;
	}
	else
	{
		camera->step_y = 1;
		camera->side_dist_y = (ceil(pos->y) - pos->y) * camera->delta_dist_y;
	}
}

int	step_in_x_direction(t_camera *camera)
{
	camera->side_dist_x += camera->delta_dist_x;
	camera->map_x += camera->step_x;
	return (0);
}

int	step_in_y_direction(t_camera *camera)
{
	camera->side_dist_y += camera->delta_dist_y;
	camera->map_y += camera->step_y;
	return (1);
}

/**
 * @brief Calculates perpendicular wall distance for rendering.
 *
 * Computes the distance to wall impact point based on DDA results,
 * avoiding fisheye effect by using perpendicular distance.
 *
 * @param camera Camera structure containing ray and map info
 * @param pos Current position in world space
 * @param side Wall side hit (0 for X, 1 for Y)
 */
void	calculate_wall_dist(t_camera *camera, t_pos *pos, int side)
{
	double	original_dist;

	if (side == 0)
		original_dist = (camera->map_x - pos->x
				+ (1 - camera->step_x) / 2) / camera->ray_dir_x;
	else
		original_dist = (camera->map_y - pos->y
				+ (1 - camera->step_y) / 2) / camera->ray_dir_y;
	camera->perp_wall_dist = fabs(original_dist);
}
