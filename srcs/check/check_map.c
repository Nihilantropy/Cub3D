#include "../include/cub3D.h"

static void	check_map_order(t_game *game, const char **matrix, int y);

bool	check_valid_map(t_game *game, const char **matrix)
{
	int	y;

	y = 0;
	check_map_order(game, matrix, y);
	if (game->map.check.map_order == false)
		return (ft_bool_putstr_fd(ERR_MAP_ORDER, 2));
	if (game->map.check.map_started == false)
		return (ft_bool_putstr_fd(ERR_NO_MAP, 2));
	check_map_infos(game, matrix);
	if (game->map.check.map_infos == false)
		return (ft_bool_putstr_fd(ERR_NO_INFOS, 2));
	check_map_matrix(game, matrix);
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
		if (is_info_line(matrix[y]))
		{
			if (game->map.check.map_started)
				return ;
		}
		else if (is_map_row(matrix[y]))
			game->map.check.map_started = true;
		else
			return ;
		y++;
	}
	game->map.check.map_order = true;
}
