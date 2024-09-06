#include "../include/cub3D.h"

static bool	is_info_line(const char *line);
static bool	is_map_row(const char *line);

bool	check_valid_map(const char **matrix)
{
	bool	map_strarted;
	int		y;
	int		x;

	map_strarted = false;
	y = 0;
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
			if (map_strarted)
			{
				ft_putstr_fd(ERR_MAP_ORDER, 2);
				return (false);
			}
		}
		else if (is_map_row(matrix[y]))
			map_strarted = true;
		else
		{
			ft_putstr_fd(ERR_NO_MAP, 2);
			return (false);
		}
		y++;
	}
	if (!map_strarted)
	{
		ft_putstr_fd(ERR_INV_MAP, 2);
		return (false);
	}
	return (true);
}

static bool	is_map_row(const char *line)
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

static bool	is_info_line(const char *line)
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