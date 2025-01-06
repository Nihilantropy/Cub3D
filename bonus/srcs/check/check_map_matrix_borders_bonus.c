#include "../../include/cub3D_bonus.h"

static void	check_borders(t_game *game, const char **matrix, int y, int x);
static bool	is_valid_tile(char c);

/**
 * @brief Checks if map borders are closed by examining adjacent cells
 * around floor tiles and player position
 *
 * @param game Game structure for map validation
 * @param matrix Map content as 2D array
 */
void	check_map_matrix_borders(t_game *game, const char **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			if (matrix[y][x] == FLOOR || matrix[y][x] == DOOR
				|| is_player_char(matrix[y][x]))
				check_borders(game, matrix, y, x);
			if (game->map.check.map_open == true)
				return ;
			x++;
		}
		y++;
	}
}

static void	check_borders(t_game *game, const char **matrix, int y, int x)
{
	if (y == 0 || y == game->map.height - 1 || 
		x == 0 || x == game->map.width - 1)
	{
		game->map.check.map_open = true;
		return ;
	}
	if (!is_valid_tile(matrix[y - 1][x]) ||
		!is_valid_tile(matrix[y + 1][x]) ||
		!is_valid_tile(matrix[y][x - 1]) ||
		!is_valid_tile(matrix[y][x + 1]))
	{
		game->map.check.map_open = true;
		return ;
	}
}

static bool	is_valid_tile(char c)
{
	return (c == WALL ||
			c == FLOOR ||
			c == NORTH ||
			c == SOUTH || 
			c == EAST || 
			c == WEST ||
			c == DOOR);
}
