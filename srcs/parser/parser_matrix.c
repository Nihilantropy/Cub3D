#include "../include/cub3D.h"

static void	set_map_start(t_game *game, const char **matrix);
static int	get_map_width(t_game *game, const char **matrix);

void	prepare_matrix_for_checks(t_game *game, char **matrix)
{
	int		width;
	char	**new_matrix;

	new_matrix = NULL;
	set_map_start(game, (const char **)matrix);
	width = get_map_width(game, (const char **)matrix);
	printf("matrix max width is: %d\n", width);
	(void)new_matrix;
	(void)width;
}

static void	set_map_start(t_game *game, const char **matrix)
{
	int		y;
	int		x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x] && ft_isspace(matrix[y][x]))
			x++;
		if (matrix[y][x] == '\0' || is_info_line(matrix[y]))
		{
			y++;
			continue ;
		}
		if (is_map_row(matrix[y]))
		{
			game->map.check.map_start_row = y;
			return ;
		}
		y++;
	}
}

static int	get_map_width(t_game *game, const char **matrix)
{
	int	y;
	int	x;
	int	width;

	y = game->map.check.map_start_row;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
			x++;
		if (x > width)
			width = x;
		y++;
	}
	return (width);
}