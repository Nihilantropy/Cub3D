/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:53:29 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:54:21 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void		append_info_node(t_info **info, t_info *new_node);
static t_info	*find_last_info_node(t_info *info);
static char		set_info_identifier(int i);

/**
 * @brief Initializes the map's info list with default nodes.
 *
 * @param game The game instance containing the map information.
 */
void	init_info_list(t_game *game)
{
	t_info	**info;
	t_info	*new_node;
	int		i;

	info = &game->map.check.info;
	i = 0;
	while (i < 6)
	{
		new_node = malloc(sizeof(t_info));
		if (!new_node)
			ft_exit_error(ERR_ALLOC_INFO);
		new_node->identifier = set_info_identifier(i);
		new_node->content = NULL;
		new_node->found = false;
		new_node->index = -1;
		append_info_node(info, new_node);
		i++;
	}
}

/**
 * @brief Assigns an identifier character based on the index.
 *
 * @param i The index corresponding to an identifier.
 * @return The character identifier ('N', 'S', 'E', 'W', 'F', or 'C').
 */
static char	set_info_identifier(int i)
{
	if (i == 0)
		return ('N');
	else if (i == 1)
		return ('S');
	else if (i == 2)
		return ('E');
	else if (i == 3)
		return ('W');
	else if (i == 4)
		return ('F');
	else if (i == 5)
		return ('C');
	return (0);
}

/**
 * @brief Appends a new node to the end of the info list.
 *
 * @param info Pointer to the head of the info list.
 * @param new_node The node to append to the list.
 */
static void	append_info_node(t_info **info, t_info *new_node)
{
	t_info	*last_node;

	if (!new_node)
		return ;
	if (!*info)
		*info = new_node;
	else
	{
		last_node = find_last_info_node(*info);
		last_node->next = new_node;
	}
	new_node->next = NULL;
}

/**
 * @brief Finds the last node in the info list.
 *
 * @param info The head of the info list.
 * @return The last node in the list.
 */
static t_info	*find_last_info_node(t_info *info)
{
	while (info->next)
		info = info->next;
	return (info);
}
