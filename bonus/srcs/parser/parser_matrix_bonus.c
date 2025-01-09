/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_matrix_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:00:18 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:01:44 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static bool	set_map_start(t_game *game, const char **matrix);
static int	get_map_max_width(const char **matrix);
static int	get_map_height(const char **matrix);
static void	copy_matrix(char **matrix_dest, const char **matrix_src);

/**
 * @brief Parses the map matrix and
 *  initializes the game map structure.
 *
 * Build a new matrix with FILLER_CHAR ('H') where no char is found,
 * creating a rectancle to keep controls simpler
 * @param game The game object.
 * @param matrix The map matrix to parse.
 * @return True if successful, otherwise false.
 */
bool	parse_matrix(t_game *game, const char **matrix)
{
	char	**new_matrix;

	new_matrix = NULL;
	if (set_map_start(game, matrix) == false)
		return (ft_bool_putstr_fd(ERR_NO_MAP, 2));
	game->map.width = get_map_max_width(matrix + game->map.check.map_start_row);
	game->map.height = get_map_height(matrix + game->map.check.map_start_row);
	new_matrix = build_new_matrix(game->map.height, game->map.width);
	copy_matrix(new_matrix, matrix + game->map.check.map_start_row);
	game->map.matrix = new_matrix;
	get_player_infos(game);
	get_doors(game);
	return (true);
}

/**
 * @brief Sets the starting row of the map in the matrix.
 *
 * @param game The game object.
 * @param matrix The map matrix.
 * @return True if a valid map row is found, otherwise false.
 */
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

/**
 * @brief Gets the max width of the map by finding the longest row in the matrix.
 *
 * @param matrix The map matrix.
 * @return The width of the map (longest row length).
 */
static int	get_map_max_width(const char **matrix)
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

/**
 * @brief Gets the height of the map by
 * counting the number of rows in the matrix.
 *
 * @param matrix The map matrix.
 * @return The height of the map (number of rows).
 */
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

static void	copy_matrix(char **matrix_dest, const char **matrix_src)
{
	int		y;
	int		x;

	y = 0;
	while (matrix_src[y])
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
