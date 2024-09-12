#include "../include/cub3D.h"

static bool	set_map_start(t_game *game, const char **matrix);
static int	get_map_width(const char **matrix);
static int	get_map_height(const char **matrix);
static void	copy_matrix(char **matrix_dest, char **matrix_src,
							int height, int width);

bool	parse_matrix(t_game *game, char **matrix)
{
	char	**new_matrix;

	new_matrix = NULL;
	if (set_map_start(game, (const char **)matrix) == false)
		return (ft_bool_putstr_fd(ERR_NO_MAP, 2));
	game->map.width = get_map_width((const char **)matrix + game->map.check.map_start_row);
	game->map.height = get_map_height((const char **)matrix + game->map.check.map_start_row);
	new_matrix = build_new_matrix(game->map.height, game->map.width);
	copy_matrix(new_matrix, matrix + game->map.check.map_start_row,
				game->map.height, game->map.width);
	print_matrix(new_matrix);
	game->map.matrix = new_matrix;
	return (true);
}

static bool	set_map_start(t_game *game, const char **matrix)
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
			return (true);
		}
		y++;
	}
	return (false);
}

static int	get_map_width(const char **matrix)
{
	int	y;
	int	x;
	int	width;

	y = 0;
	width = 0;
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

static int	get_map_height(const char **matrix)
{
	int	y;
	int	len;

	y = 0;
	len = 0;
	while (matrix[y] != NULL)
	{
		y++;
		len++;
	}
	return (len);
}

static void	copy_matrix(char **matrix_dest, char **matrix_src,
							int height, int width)
{
	int	y;
	int	x;

	y = 0;
	(void)width;
	while (y < height)
	{
		x = 0;
		while (matrix_src[y][x])
		{
			matrix_dest[y][x] = matrix_src[y][x];
			x++;
		}
		y++;
	}
}