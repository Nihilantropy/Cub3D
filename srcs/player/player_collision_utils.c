#include "../include/cub3D.h"

static bool	check_corner_points(const char **matrix, double new_x, double new_y);
static bool	check_circle_points(const char **matrix, 
								double new_x, double new_y);
static bool	is_valid_grid_point(const char **matrix, double x, double y);

/**
 * @brief Validates if a position is valid within the map.
 *
 * Checks both corner points and circle points around the position
 * to ensure there are no collisions with walls.
 *
 * @param matrix Map matrix containing wall information
 * @param new_y Y coordinate to check
 * @param new_x X coordinate to check
 * @return true if position is valid, false if collision detected
 */
bool	is_valid_pos(const char **matrix, double new_y, double new_x)
{
	return (check_corner_points(matrix, new_x, new_y) && 
			check_circle_points(matrix, new_x, new_y));
}

/**
 * @brief Checks corners of player's collision box for wall collisions.
 *
 * Tests four corner points at player radius distance from center
 * position. Each point is checked against map grid for validity.
 *
 * @param matrix Map matrix containing wall information
 * @param new_x Center X coordinate to check
 * @param new_y Center Y coordinate to check
 * @return true if all corners are valid, false if any corner collides
 */
static bool	check_corner_points(const char **matrix, double new_x, double new_y)
{
	double	points[4][2];
	int		i;

	points[0][0] = new_x - PLAYER_RADIUS;
	points[0][1] = new_y - PLAYER_RADIUS;
	points[1][0] = new_x + PLAYER_RADIUS;
	points[1][1] = new_y - PLAYER_RADIUS;
	points[2][0] = new_x - PLAYER_RADIUS;
	points[2][1] = new_y + PLAYER_RADIUS;
	points[3][0] = new_x + PLAYER_RADIUS;
	points[3][1] = new_y + PLAYER_RADIUS;
	i = -1;
	while (++i < 4)
		if (!is_valid_grid_point(matrix, points[i][0], points[i][1]))
			return (false);
	return (true);
}

/**
 * @brief Checks points around player in a circular pattern for collisions.
 *
 * Tests eight points at 45-degree intervals on a circle slightly larger
 * than player radius. Ensures smooth collision detection with walls.
 *
 * @param matrix Map matrix containing wall information
 * @param new_x Center X coordinate to check
 * @param new_y Center Y coordinate to check
 * @return true if all circle points are valid, false if any point collides
 */
static bool	check_circle_points(const char **matrix, 
								double new_x, double new_y)
{
	double	check_radius;
	double	check_x;
	double	check_y;
	int		angle;

	check_radius = PLAYER_RADIUS + 0.1;
	angle = 0;
	while (angle < 360)
	{
		check_x = new_x + check_radius * cos(angle * M_PI / 180.0);
		check_y = new_y + check_radius * sin(angle * M_PI / 180.0);
		if (!is_valid_grid_point(matrix, check_x, check_y))
			return (false);
		angle += 45;
	}
	return (true);
}

/**
 * @brief Validates if a point on the grid is a valid position.
 *
 * Converts floating-point coordinates to grid positions and checks
 * for map boundaries and valid floor tiles. Ensures position is
 * within map bounds and not inside a wall.
 *
 * @param matrix Map matrix containing wall information
 * @param x X coordinate to check
 * @param y Y coordinate to check
 * @return true if point is valid floor space, false otherwise
 */
static bool	is_valid_grid_point(const char **matrix, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_y < 0 || matrix[grid_y] == NULL || 
		grid_x < 0 || matrix[grid_y][grid_x] == '\0')
		return (false);
	if (matrix[grid_y][grid_x] != FLOOR && 
		!is_player_char(matrix[grid_y][grid_x]))
		return (false);
	return (true);
}
