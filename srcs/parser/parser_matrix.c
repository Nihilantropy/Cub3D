#include "../include/cub3D.h"

static void	set_map_start(t_game *game, const char **matrix);
static int	get_map_width(t_game *game, const char **matrix);
static int	get_map_height(t_game *game, const char **matrix);
static void	copy_matrix(t_game *game, char **matrix_dest, char **matrix_src, int len);

void	prepare_matrix_for_checks(t_game *game, char **matrix)
{
	char	**new_matrix;
	int		y;
	int		x;

	new_matrix = NULL;
	y = 0;
	set_map_start(game, (const char **)matrix);
	game->map.width = get_map_width(game, (const char **)matrix);
	game->map.height = get_map_height(game, (const char **)matrix);
	printf("matrix max width is: %d\n", game->map.width);
	printf("matrix max heigth is: %d\n", game->map.height);

	new_matrix = malloc(sizeof(char *) * game->map.height + 1);
	if (!new_matrix)
		ft_exit_error(ERR_ALLOC_NEW_MATRIX_ROW);
	while (y < game->map.height)
	{
		x = 0;
		new_matrix[y] = malloc(game->map.width + 1);
		if (!new_matrix[y])
			ft_exit_error(ERR_ALLOC_NEW_MATRIX_COL);
		while (x < game->map.width)
			new_matrix[y][x++] = 'H';
		y++;
	}
	new_matrix[y] = NULL;
	copy_matrix(game, new_matrix, matrix, game->map.height);
	print_matrix(new_matrix);
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

static int	get_map_height(t_game *game, const char **matrix)
{
	int	y;
	int	len;

	y = game->map.check.map_start_row;
	len = 1;
	while (matrix[y])
	{
		y++;
		len++;
	}
	return (len);
}

static void	copy_matrix(t_game *game, char **matrix_dest, char **matrix_src, int len)
{
	int	y;
	int	j;

	y = game->map.check.map_start_row;
	j = 0;
	while (y < (y + len))
	{
		ft_strlcpy(matrix_dest[j], matrix_src[y], ft_strlen(matrix_src[y]));
		y++;
		j++;
	}
}
