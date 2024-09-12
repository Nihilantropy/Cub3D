#include "../include/cub3D.h"

static void	check_map_wrong_char(t_game *game, const char **matrix);
static void	check_map_island(t_game *game, const char **matrix);

void	check_map_matrix(t_game *game, const char **matrix)
{
	check_map_wrong_char(game, matrix);
	if (game->map.check.wrong_char == true)
		return (ft_bool_putstr_fd(ERR_WRONG_CHAR, 2));
	check_map_island(game, matrix);
	if (game->map.check.map_island == true)
		return (ft_putstr_fd(ERR_MAP_ISLAND, 2));
}

static void	check_map_wrong_char(t_game *game, const char **matrix)
{
	// TODO read the map matrix. if an invalid char is found
	// activate the wrong_char flag
}

static void	check_map_island(t_game *game, const char **matrix)
{
	// TODO while we read a line in matrix (matrix[y]) if
	// we enconuter a sequence of space or tabs, we expect a '\0'.
	// if we encouter a wall activate the map_island flag 
}
