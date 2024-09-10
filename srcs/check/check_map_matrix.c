#include "../include/cub3D.h"

static bool	check_map_borders(const char **matrix, int *y, int *x);
static bool	check_matrix_top(const char **matrix, int *y, int *x);

void	check_map_matrix(t_game *game, const char **matrix)
{
	int		y;
	int		x;

	y = game->map.check.map_start_row;
	while (matrix[y])
	{
		if (!check_map_borders(matrix, &y, &x))
			return ;
		y++;
	}
	game->map.check.map_matrix = true;
}

static bool	check_map_borders(const char **matrix, int *y, int *x)
{
	if (matrix[*y + 1] == NULL)
		return (ft_bool_putstr_fd(ERR_MATRIX_LEN, 2));
	if (check_matrix_top(matrix, y, x) == false)
		return (ft_bool_putstr_fd(ERR_MATRIX_TOP, 2));
	//if (check_matrix_bot(matrix, y, x) == false)
	//	return (ft_bool_putstr_fd(ERR_MATRIX_BOT, 2));
	return (true);
}

static bool	check_matrix_top(const char **matrix, int *y, int *x)
{
//	if (matrix[*y][*x] != WALL)
//		return (false);
	while (matrix[*y][*x])
	{
		printf("%c\n", matrix[*y][*x]);
		if (matrix[*y][*x] != ' ' || matrix[*y][*x] != WALL)
			return (false);
		x++;
	}
	return (true);
}