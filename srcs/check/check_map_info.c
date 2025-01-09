/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:45:57 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:50:05 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	info_identifier_found(t_game *game, const char *line);
static bool	check_all_info_identifiers(t_info *info);
static char	get_identifier(const char *line);

/**
 * @brief Validates map information elements (textures paths and colors)
 * and tracks their presence through game state
 *
 * @param game Game structure containing validation state
 * @param matrix Map file content as 2D array
 */
void	check_map_infos(t_game *game, const char **matrix)
{
	int		y;
	int		x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x] && (matrix[y][x] == ' ' ||
			matrix[y][x] == '\t'))
			x++;
		if (matrix[y][x] == '\0')
		{
			y++;
			continue ;
		}
		if (is_info_line(&matrix[y][x]))
			if (info_identifier_found(game, &matrix[y][x]) == false)
				return ;
		y++;
	}
	game->map.check.map_infos_cont = true;
	if (check_all_info_identifiers(game->map.check.info) == true)
		game->map.check.map_infos_id = true;
}

/**
 * @brief Validates and parses an identifier line (NO, SO, WE, EA, F, C)
 *
 * @param game Game structure containing map data
 * @param line Line to parse
 * @return bool true if identifier is valid and parsed, false otherwise
 */
static bool	info_identifier_found(t_game *game, const char *line)
{
	t_info	*info;
	char	identifier;

	if (!game || !game->map.check.info || !line)
		return (false);
	identifier = get_identifier(line);
	if (!identifier)
		return (false);
	info = game->map.check.info;
	while (info)
	{
		if (info->identifier == identifier)
		{
			if (!parse_info(game, info, line))
				return (false);
			return (true);
		}
		info = info->next;
	}
	return (false);
}

static char	get_identifier(const char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0)
		return ('N');
	else if (ft_strncmp(line, "SO", 2) == 0)
		return ('S');
	else if (ft_strncmp(line, "EA", 2) == 0)
		return ('E');
	else if (ft_strncmp(line, "WE", 2) == 0)
		return ('W');
	else if (ft_strncmp(line, "F", 1) == 0)
		return ('F');
	else if (ft_strncmp(line, "C", 1) == 0)
		return ('C');
	return (0);
}

static bool	check_all_info_identifiers(t_info *info)
{
	t_info	*current_node;

	current_node = info;
	while (current_node)
	{
		if (current_node->found == false)
			return (false);
		current_node = current_node->next;
	}
	return (true);
}
