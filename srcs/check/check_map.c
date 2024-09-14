#include "../include/cub3D.h"

static void	check_map_order(t_game *game, const char **matrix, int y);

/*	check valid map:
**	1) check the correct order of the map
**		infos and the map matrix
**	2) check if the map matrix is valid
**	3) check if all the infos are correct
*/
bool	check_valid_map(t_game *game, const char **matrix)
{
	int	y;

	y = 0;
	check_map_order(game, matrix, y);
	if (game->map.check.map_order == false)
		return (ft_bool_putstr_fd(ERR_MAP_ORDER, 2));
	check_map_infos(game, matrix);
	if (game->map.check.map_infos == false)
		return (ft_bool_putstr_fd(ERR_NO_INFOS, 2));
	check_map_matrix(game, game->map.matrix);
	if (game->map.check.map_matrix == false)
		return (false);
	return (true);
}

static void	check_map_order(t_game *game, const char **matrix, int y)
{
	int		x;

	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x] && ft_isspace(matrix[y][x]))
			x++;
		if (matrix[y][x] == '\0')
		{
			y++;
			continue ;
		}
		if (is_info_line(&matrix[y][x]) == true)
		{
			if (game->map.check.map_started)
				return ;
		}
		else if (is_map_row(matrix[y]) == true)
			game->map.check.map_started = true;
		y++;
	}
	game->map.check.map_order = true;
}
