/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:46:05 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:47:56 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	check_map_order(t_game *game, const char **matrix, int x, int y);
static bool	is_valid_char(char c);

/**
 * @brief Validates complete map structure: info order, content,
 * identifiers and matrix format
 *
 * @param game Game structure containing map validation data
 * @param matrix Map file content as 2D array
 * @return bool true if map is valid, false on any validation error
 */
bool	check_valid_map(t_game *game, const char **matrix)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	check_map_order(game, matrix, x, y);
	if (game->map.check.wrong_info_char == true)
		return (ft_bool_putstr_fd(ERR_WRONG_INFO_CHAR, 2));
	if (game->map.check.map_order == false)
		return (ft_bool_putstr_fd(ERR_MAP_ORDER, 2));
	check_map_infos(game, matrix);
	if (game->map.check.wrong_info_nbr == true)
		return (ft_bool_putstr_fd(ERR_WRONG_INFO_NBR, 2));
	if (!game->map.check.map_infos_id || !game->map.check.map_infos_cont)
		return (ft_bool_putstr_fd(ERR_NO_INFOS, 2));
	check_map_matrix(game, (const char **)game->map.matrix);
	if (game->map.check.map_matrix == false)
		return (false);
	return (true);
}

/**
 * @brief Validates proper order of map elements and
 * identifies invalid characters
 *
 * @param game Game structure with map validation state
 * @param matrix Map file content as 2D array
 * @param x
 * @param y
 */
static void	check_map_order(t_game *game, const char **matrix, int x, int y)
{
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
		if (is_info_line(&matrix[y][x]) == true)
		{
			if (game->map.check.map_started)
				return ;
		}
		else if (is_map_row(matrix[y]) == true)
			game->map.check.map_started = true;
		else if (!is_valid_char(matrix[y][x]))
			game->map.check.wrong_info_char = true;
		y++;
	}
	game->map.check.map_order = true;
}

static bool	is_valid_char(char c)
{
	return (c == WALL);
}
