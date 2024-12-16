#include "../include/cub3D.h"

static void	check_borders(t_game *game, const char **matrix, int y, int x);
static bool	is_invalid_border(char c);

/** 
 * @brief Check map matrix borders:
 * 1) Verify that all floor cells ('0') are surrounded
 *		by WALL ('1') or other floor cells
 * 2) Count the number of player cells and store
 *		it in game->map.check.player
 */
void	check_map_matrix_borders(t_game *game, const char **matrix)
{
	int y;
	int x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			if (game->map.check.map_open == true)
				break ;
			else if (matrix[y][x] == FLOOR)
				check_borders(game, matrix, y, x);
			x++;
		}
		y++;
	}
}

static void	check_borders(t_game *game, const char **matrix, int y, int x)
{
	if (x == 0 || x == game->map.width - 1 ||
		y == 0 || y == game->map.height - 1)
		game->map.check.map_open = true;
	else
	{
		if (is_invalid_border(matrix[y - 1][x]) ||
			is_invalid_border(matrix[y + 1][x]) ||
			is_invalid_border(matrix[y][x - 1]) ||
			is_invalid_border(matrix[y][x + 1]))
			game->map.check.map_open = true;
	}
}

static bool	is_invalid_border(char c)
{
	return (c == SPACE || c == TAB ||
			c == MAP_FILLER || c == '\0');
}
