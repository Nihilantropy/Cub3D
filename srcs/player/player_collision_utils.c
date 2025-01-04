#include "../include/cub3D.h"

/**
 * @brief check if the new player position would be out of map
 * bounderies or on a wall
 * 
 * @param matrix stores map infos
 * @param new_y new y map position
 * @param new_x new x map position
 * @return true if new position is on FLOOR cell, false otherwise
 */
bool	is_valid_pos(const char **matrix, double new_y, double new_x)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)new_x;
	grid_y = (int)new_y;
	if (grid_y < 0 || matrix[grid_y] == NULL || 
		grid_x < 0 || matrix[grid_y][grid_x] == '\0')
		return (false);
	if (matrix[grid_y][grid_x] == WALL)
		return (false);
	return (true);
}
