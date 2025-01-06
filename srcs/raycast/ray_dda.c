#include "../include/cub3D.h"

static void    perform_dda_step(t_camera *camera, int *side);

/**
 * @brief Executes Digital Differential Analysis for ray casting.
 *
 * Performs DDA algorithm to find wall intersection point by stepping
 * through grid cells until a wall is hit or map bounds exceeded.
 *
 * @param game Game structure containing map data
 * @param camera Camera structure with ray information
 * @return Wall side hit (0 for X, 1 for Y) or -1 if no hit
 */
int	perform_dda(t_game *game, t_camera *camera)
{
	int	hit;
	int	side;
	int	iter;

	hit = 0;
	side = -1;
	iter = 0;
	while (hit == 0 && iter < game->map.width * game->map.height)
	{
		perform_dda_step(camera, &side);
		if (camera->map_y < 0 || camera->map_y >= game->map.height ||
			camera->map_x < 0 || camera->map_x >= game->map.width)
			return (-1);
		if (game->map.matrix[camera->map_y][camera->map_x] == WALL)
			hit = 1;
		iter++;
	}
	if (hit)
		return (side);
	return (-1);
}

/**
 * @brief Performs a single step in DDA algorithm.
 *
 * Updates ray position and side distances by stepping in either X or Y
 * direction depending on current side distances.
 *
 * @param camera Camera structure with ray and step info
 * @param side Pointer to store hit side (0 for X, 1 for Y)
 */
static void	perform_dda_step(t_camera *camera, int *side)
{
	if (camera->side_dist_x < camera->side_dist_y)
	{
		camera->side_dist_x += camera->delta_dist_x;
		camera->map_x += camera->step_x;
		*side = 0;
	}
	else
	{
		camera->side_dist_y += camera->delta_dist_y;
		camera->map_y += camera->step_y;
		*side = 1;
	}
}
