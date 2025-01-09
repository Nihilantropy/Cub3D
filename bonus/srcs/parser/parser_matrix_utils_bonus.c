/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_matrix_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:00:20 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:00:21 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

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
	if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0
		|| ft_strncmp(line, "C", 1) == 0)
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
			new_matrix[y][x++] = MAP_FILLER;
		new_matrix[y][x] = '\0';
		y++;
	}
	new_matrix[y] = NULL;
	return (new_matrix);
}

size_t	matrix_len(const char **matrix)
{
	int	y;

	if (!matrix)
		return (-1);
	y = 0;
	while (matrix[y])
		y++;
	return (y);
}
