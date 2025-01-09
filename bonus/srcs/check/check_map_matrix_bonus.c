/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_matrix_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:38:14 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:39:25 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	check_map_matrix_wrong_char(t_game *game,
				const char **matrix);
static bool	is_tile(char c);

/**
 * @brief Validates map matrix for wrong characters, isolated regions,
 * open borders and player count
 *
 * @param game Game structure containing map validation data
 * @param matrix Map content as 2D array
 */
void	check_map_matrix(t_game *game, const char **matrix)
{
	check_map_matrix_wrong_char(game, matrix);
	if (game->map.check.wrong_char == true)
		return (ft_putstr_fd(ERR_WRONG_CHAR, STDERR_FILENO));
	check_map_matrix_island(game, matrix);
	if (game->map.check.map_island == true)
		return (ft_putstr_fd(ERR_MAP_ISLAND, STDERR_FILENO));
	check_map_matrix_borders(game, matrix);
	if (game->map.check.map_open == true)
		return (ft_putstr_fd(ERR_MAP_BORDERS, STDERR_FILENO));
	if (game->map.check.player != 1)
		return (ft_putstr_fd(ERR_NBR_PLAYER, STDERR_FILENO));
	game->map.check.map_matrix = true;
}

static void	check_map_matrix_wrong_char(t_game *game,
										const char **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			if (!is_tile(matrix[y][x]) && matrix[y][x] != SPACE &&
				matrix[y][x] != TAB)
			{
				game->map.check.wrong_char = true;
				return ;
			}
			if (is_player_char(matrix[y][x]))
				game->map.check.player++;
			x++;
		}
		y++;
	}
}

static bool	is_tile(char c)
{
	return (c == FLOOR || c == WALL || c == NORTH || c == SOUTH
		|| c == EAST || c == WEST || c == MAP_FILLER || c == DOOR);
}
