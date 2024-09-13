#include "../include/cub3D.h"

static void	check_map_wrong_char(t_game *game, const char **matrix);
static void	check_map_island(t_game *game, const char **matrix);
static bool	is_tile(char c);

/*	check map matrix:
**	1) check if there is a wrong char in
**		the map matrix
**	2) check if there is one and only one
**		map island
*/
void	check_map_matrix(t_game *game, const char **matrix)
{
	check_map_wrong_char(game, matrix);
	if (game->map.check.wrong_char == true)
		return (ft_putstr_fd(ERR_WRONG_CHAR, 2));
	check_map_island(game, matrix);
	if (game->map.check.map_island == true)
		return (ft_putstr_fd(ERR_MAP_ISLAND, 2));
}

static void	check_map_wrong_char(t_game *game, const char **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			if (!is_tile(matrix[y][x]) && matrix[y][x] != SPACE &&
				matrix[y][x] != TAB)
			{
				game->map.check.wrong_char = true;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	check_map_island(t_game *game, const char **matrix)
{
	(void)game;
	(void)matrix;
	// TODO while we read a line in matrix (matrix[y]) if
	// we enconuter a sequence of space or tabs, we expect a '\0'.
	// if we encouter a wall activate the map_island flag 
}

static bool	is_tile(char c)
{
	return (c == FLOOR || c == WALL || c == NORTH || c == SOUTH ||
			c == EAST || c == WEST || c == MAP_FILLER);
}
