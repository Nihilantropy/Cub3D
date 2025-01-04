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
