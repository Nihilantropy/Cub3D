/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:56:40 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:58:14 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_matrix_len(const char *map);
static bool	build_matrixes(t_game *game, char **matrix, const char *map);

/**
 * @brief Loads and validates the map from the given file.
 *
 * Builds a matrix from the map, checks if the map is valid,
 * and returns a result.
 * @param game The game context.
 * @param map The map file content.
 * @return true if the map is valid, false otherwise.
 */
bool	get_map(t_game *game, const char *map)
{
	bool	flag;
	int		len;
	char	**matrix;

	matrix = NULL;
	len = get_matrix_len(map);
	if (!len)
	{
		ft_putstr_fd(ERR_EMPY_FILE, 2);
		return (false);
	}
	matrix = (char **)malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	if (build_matrixes(game, matrix, map) == false)
		flag = false;
	else if (check_valid_map(game, (const char **)matrix) == false)
		flag = false;
	else
		flag = true;
	free_matrix(matrix);
	return (flag);
}

/**
 * @brief Builds the matrix from the map file.
 *
 * Reads each line from the map file, trims it, and stores it in the matrix.
 * Parses the matrix to ensure the map is valid.
 * @param game The game context.
 * @param matrix The matrix to store the map data.
 * @param map The map file path.
 * @return true if the matrix is successfully built and parsed, false otherwise.
 */
static bool	build_matrixes(t_game *game, char **matrix, const char *map)
{
	char	*line;
	int		y;
	int		fd;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (false);
	}
	y = 0;
	while (line)
	{
		matrix[y] = ft_strtrim(line, "\r\v\n");
		free(line);
		line = get_next_line(fd);
		y++;
	}
	matrix[y] = NULL;
	close(fd);
	if (parse_matrix(game, (const char **)matrix) == false)
		return (false);
	return (true);
}

/**
 * @brief Returns the number of lines in the map file.
 *
 * Reads the map file line by line and counts the total number of lines.
 * @param map The map file path.
 * @return The number of lines in the map file.
 */
static int	get_matrix_len(const char *map)
{
	char	*line;
	int		y;
	int		fd;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	y = 0;
	while (line)
	{
		y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (y);
}
