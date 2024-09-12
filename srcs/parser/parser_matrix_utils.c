#include "../include/cub3D.h"

bool	is_map_row(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != FLOOR
			&& line[i] != WALL
			&& line[i] != NORTH
			&& line[i] != SOUTH
			&& line[i] != EAST
			&& line[i] != WEST
			&& !ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_info_line(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (true);
	return (false);
}

char	**build_new_matrix(int height, int width)
{
	char	**new_matrix;
	int		y;
	int		x;

	new_matrix = malloc(sizeof(char *) * (height + 1));
	if (!new_matrix)
		ft_exit_error(ERR_ALLOC_NEW_MATRIX_ROW);
	y = 0;
	while (y < height)
	{
		new_matrix[y] = malloc(width + 1);
		if (!new_matrix[y])
			ft_exit_error(ERR_ALLOC_NEW_MATRIX_COL);
		x = 0;
		while (x < width)
			new_matrix[y][x++] = 'H';
		new_matrix[y][x] = '\0';
		y++;
	}
	new_matrix[y] = NULL;
	return (new_matrix);
}
